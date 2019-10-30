/**
 * Esto solo es una prueba de I2C con el LPC1769 revisión D
 *
 */

#include "func.h"

//Estos includes los mete el ejemplo MPU9250
#include <stdint.h>
#include <math.h>

//-----------Variables Globales---------------------------------------------------------------------------------
volatile uint8_t txBuffer[I2C_TX_BUFF_SIZE];
volatile uint8_t rxBuff[I2C_RX_BUFF_SIZE];
volatile uint8_t estadoI2C = I2C_IDLE;
volatile uint8_t slaveAddr = 0;
volatile uint8_t txBuffSize = 0;
volatile uint8_t rxBuffSize = 0;
volatile uint8_t currentAdress = 0;
volatile uint8_t isDummyWrite = 0;


//----------------------PROGRAMA----------------------------------------------------------------------------------
int main(void) {
	initI2C();

	while(1)
	{
		uint32_t i=0;
		//Esto solamente me estaría guardando en dato lo que lea cuando lo lea :D
		uint8_t dato[]={0xAA, 0xAA,0xAA};
		//readI2C(dato, I2C_RX_BUFF_SIZE);
	//	I2C1CONSET = (1 << 5);
	//	I2C1DAT = 0xAA;
	//	for(i=0;i<10000000;i++);
		writeI2C(0x41, W, dato, 3, 0);
	}
}


void I2C1_IRQHandler(void)
{
	static uint8_t dataCount = 0;	// Contador Incremental del estado del envío
	uint8_t estado;					// El estado es uint8_t y se modifica cada vez que se interrumpe mediante este handler

	estado = I2C1STAT & 0xFF;		// El estado solmanete esta representado x los primeros 8bit de I2C1STAT

	switch(estado)
	{
		case 0x08:				     				// A START condition has been transmitted.
			I2C1DAT = slaveAddr;  					// Cargo SLA+W/R
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;

		case 0x10:					  				// A repeated START condition has been transmitted.
			I2C1DAT = slaveAddr;   					// Cargo SLA+W/R
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;

			//TRASMITTER MODE--------------------------------------------------------------------------------//
		case 0x18:						   			// SLA+W has been transmitted; ACK has been received.
			I2C1DAT = txBuffer[dataCount]; 			// Cargo primer dato.
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;

		case 0x20:		             				// SLA+W has been transmitted; NOT ACK has been received.
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET |= (1 << I2EN)| (1 << STO);	// Seteo STO para arrancar proceso de STOP.
			estadoI2C = I2C_FAILED;  				// Informo de falla de transmision.
			dataCount = 0;
			break;

		case 0x28:									// Data byte in I2DAT has been transmitted; ACK has been received.
			dataCount++;		   					// Incremento el contador del buffer.
			if(dataCount >= txBuffSize)				// Pregunto si es el último dato.
			{
				I2C1CONCLR |= (1 << STA) | (1 << SI);		// Apago STA, Limpio el flag de interrupcion.
				I2C1CONSET |= (1 << (4 + isDummyWrite));  	// Seteo STO para proceso de STOP o STA para otra condicion de START.
				if(isDummyWrite)
				{
					slaveAddr |= 0x01;						// Retransmito en modo READ
				}else{
					estadoI2C = I2C_IDLE;					// Entro en modo oscioso
				}
				dataCount = 0;								// De cualquier modo reseteo el buffer
			}else{
				I2C1DAT = txBuffer[dataCount];	 			// Cargo dato.
				I2C1CONCLR |= (1 << STA) | (1 << SI);		// Apago STA, Limpio el flag de interrupcion.
			}
			break;

		case 0x30:					  				// Data byte in I2DAT has been transmitted; NOT ACK has been received.
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET |= (1 << I2EN)| (1 << STO);	// Seteo STO para arrancar proceso de STOP.
			estadoI2C = I2C_IDLE;	   				// Libero al periférico para nueva transmisión.
			dataCount = 0;
			break;

		case 0x38:									// Arbitration lost in SLA+R/W or Data bytes.
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			dataCount = 0;
			break;

			//RECEIVER MODE---------------------------------------------------------------------------------//
		case 0x40:									// SLA+R has been transmitted; ACK has been received.
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET |=  (1 << AA);				// Pongo el bit de ACK
			break;

		case 0x48:									// SLA+R has been transmitted; NOT ACK has been received.
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET |=  (1 << STO);				// Pongo el bit de STOP
			estadoI2C = I2C_FAILED; 				// Falló
			dataCount = 0;
			break;

		case 0x50:									// Data byte has been received; ACK has been returned.
			rxBuff[dataCount] = I2C1DAT;			// Guardo en el buffer el dato recibido
			dataCount++;
			if(dataCount >= rxBuffSize -1)			// Si se llenó el buffer
			{
				I2C1CONCLR |= (1 << STA) | (1 << SI) | (1 << AA);	// APAGO START - LIMPIO FLAG - APAGO ACK
			}else{
				I2C1CONCLR |= (1 << STA) | (1 << SI);				// Apago START - LIMPIO FLAG
				I2C1CONSET |=  (1 << AA);							// Pongo el bit de ACK
			}
			break;

		case 0x58:									// Data byte has been received; NOT ACK has been returned.
			rxBuff[dataCount] = I2C1DAT;			// Recibo dato
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET |=  (1 << STO);				// Pongo el bit de STOP
			estadoI2C = I2C_DATAV;					// Especifico que hay Data Available para I2C1_data_read
			dataCount = 0;
			break;

		default:
			I2C1CONCLR |= (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;
	}
}


int writeI2C(uint8_t addr, uint8_t modo, uint8_t* data, uint8_t sizet, uint8_t sizer)
{
	//Esta función solo genera el start y carga el dato a enviar!
	int salida = 1;
	uint8_t i = 0;
	if(estadoI2C != I2C_BUSY)		//Cuando se pueda escribir:
	{
		//Asignaciones
		currentAdress = addr;
		addr = ((addr << 1) & (0b11111110));  	//Meto en addr la slave_addr
		addr |= (modo & 0b01);					//Le cargo el modo (notese que si es Dummy_write, se va a ver como write)
		txBuffSize = sizet; 					//size transmisión
		rxBuffSize = sizer;						//size recepción		//TODO: Ver que onda acá.. Capaz se puede reemplazar por un #define

		//Proceso
		slaveAddr = addr;						//Cargo en la variable global SLA + W/R
		if(modo == W || modo == DW)				//Cuando no este en lectura ni en oscioso
		{
			for(i = 0; i < sizet; i++)
			{
				txBuffer[i] = data[i];			//Lleno buffer de transmisión que LUEGO será transmitido en el handler
			}
		}

		if(modo == DW)							//Esto se ve reflejado en el handler
		{
			isDummyWrite = 1;
		}else{
			isDummyWrite = 0;
		}

		//Creo que como es SET no hace falta :I2C1CONSET &= ~(31 << AA);				//Aseguro el 0
		I2C1CONSET |= (1 << I2EN) | (1 << STA);	//Pongo en Enable y el STAR en 1
		estadoI2C = I2C_BUSY; 					//Ahora ya no se pueden solicitar mas mensajes

		//Salimos bien :D
		salida = 0;
	}else{

		salida = 1;
	}
	return salida;
}


void initI2C()
{

	PCONP |= 1 << 19; 			//Energizar I2C1
	// Le asigno el clock completo (como tengo inicializado el PLL --> 100 Mhz)

	PCLKSEL1 &= ~(3 << 6);		//Asegura 00 en la posicion correspondiente a I2C0 de PCLKSEL1
	PCLKSEL1 |= 1 << 6;			//Pone 01 en la posicion correspondiente a I2C0 de PCLKSEL1

	//-----------Configuración Pines--------------------

	//SDA	(P0.19 - Expansión 5)
		SetPINSEL(P0,19,3);			//Habilitas el pin como SDA1
		//SetDIR(P0,19,1);			//Salida
		SetPINMODE(P0,19,2);		//Configuras el pin como 'neither pull-up nor pull-down'
		SetPINMODE_OD(P0,19,1);		//Configuro el pin como Open Drain
	//SCL	(P0.20 - Expansión 10)
		SetPINSEL(P0,20,3);			//Habilitas el pin como SCL1
		//SetDIR(P0,20,1);			//Salida
		SetPINMODE(P0,20,2);		//Configuras el pin como 'neither pull-up nor pull-down'
		SetPINMODE_OD(P0,20,1);		//Configuro el pin como Open Drain

		I2C1SCLH =  500;	//Pongo un duty cycle de 50%
		I2C1SCLL =  500;	//La frecuencia de salida va a seguir la siguiente formula

	//-----------Configuración Registros I2C-------------
		ISER0 |= 1 << 11;			//Esto habilita la interrupción de I2C1


									//f = PCLKI2C/(I2C1SCLH + I2C1SCLL)
									//Con nuestros valores: f = 100Mhz/(500+500) = 100Mhz/1000 = 100Khz


		I2C1CONSET = (1 << I2EN);	//Pongo en 1 el único valor para que funcione como Master Transmitter
		//Creo que como es SET no hace falta :I2C1CONSET &= ~(31 << AA);	//Aseguro que todos los registros que nos interesan tengan 0


		//Si entendí bien, con esto ya deberíamos tener inicializado el periférico de I2C

}



uint8_t readI2C(uint8_t* data, uint8_t size)
{
	uint8_t i = 0;
	if(estadoI2C == I2C_DATAV) 		//Data available
	{
		for(i = 0; i < size; i++)
		{
			data[i] = rxBuff[i]; 	//Guardo en el vector de aplicación
			rxBuff[i] = 0; 			//Vacío el buffer
		}
	}
	estadoI2C = I2C_IDLE; 			//Ya vacié los datos --> IDLE
	i = currentAdress; 				//Se especifica en I2C1_master_mode
	currentAdress = 0;
	return i; 						//Devuelve de la address que recibí el dato
}

void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion )
{
	puerto = puerto * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ puerto ] = PINSEL[ puerto ] & ( ~ ( 3 << pin ) );
	PINSEL[ puerto ] = PINSEL[ puerto ] | ( funcion << pin );
}

void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}

void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion)
{
	PINMODE_OD[puerto] &= ~(1 << pin);	 		//Aseguo un 0
	PINMODE_OD[puerto] |= (funcion << pin);		//Le asigno el valor al puerto
}
