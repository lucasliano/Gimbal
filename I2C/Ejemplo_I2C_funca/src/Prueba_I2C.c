/**
 * Esto solo es una prueba de I2C con el LPC1769 revisión D
 *
 */

#include "func.h"
#include "Regs_LPC176x.h"

//-----------Variables Globales---------------------------------------------------------------------------------
volatile uint8_t txBuffer[I2C_TX_BUFF_SIZE];
volatile uint8_t rxBuff[I2C_RX_BUFF_SIZE];
volatile uint8_t estadoI2C = I2C_IDLE;
volatile uint8_t slaveAddr = 0;
volatile uint8_t txBuffSize = 0;
volatile uint8_t rxBuffSize = 0;
volatile uint8_t currentAdress = 0;
volatile uint8_t isDummyWrite = 0;


uint8_t datoSalida = 0;
//----------------------PROGRAMA----------------------------------------------------------------------------------
int main(void) {


	MyInitPLL();

	initI2C();



	uint8_t addr = 0x68;
	uint8_t data[1] = {0x75};			//Manda Who i am

	while(1)
	{
		/**
		 * 	Instrucciones:	(Siempre meter delay entre medio de cada cosa!)
		 *
		 * 		MODIFICAR REGISTRO:
		 * 			Tenes que hacer 	writeI2C(addr,W,RegisterAddr,1,0);
		 * 			y despues			writeI2C(addr,W,ValorNuevoRegistro,1,0);
		 *
		 * 			o podes cargar RegisterAddr y ValorNuevoRegistro en un uint8_t data[2];
		 * 			y hacer				writeI2C(addr,W,data,2,0);
		 *
		 * 		LEER REGISTRO:
		 * 			Podes hacer			writeI2C(addr,DW,RegisterAddr,1,1);
		 * 								readI2C(&datoSalida, BUFF_SIZE);
		 *
		 *
		 * 			o podes hacer		writeI2C(addr,W,RegisterAddr,1,0);
		 * 			y despues			writeI2C(addr,R,data,0,1);
		 * 			finalmente:			readI2C(&datoSalida, BUFF_SIZE);
		 */


		writeI2C(addr,DW,data,1,1);		//Esto es equivalente a hacer las lineas siguientes
		/**
		writeI2C(addr,W,data,1,0);
		myDelay(5000);
		writeI2C(addr,R,data,0,1);
		**/

		myDelay(5000);								//Los delay son obligatorios, hay que darle tiempo para que cargue los datos
		readI2C(&datoSalida, I2C_RX_BUFF_SIZE);		//Esto extrae el dato a nivel de app nomas
		myDelay(5000);

	}
}

void myDelay(uint16_t ms)
{
	for(int i = 0; i < ms * 1000; i++);	//Aproximado
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
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;

		case 0x10:					  				// A repeated START condition has been transmitted.
			I2C1DAT = slaveAddr;   					// Cargo SLA+W/R
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;

			//TRASMITTER MODE--------------------------------------------------------------------------------//
		case 0x18:						   			// SLA+W has been transmitted; ACK has been received.
			I2C1DAT = txBuffer[dataCount]; 			// Cargo primer dato.	(dataCount = 0)
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;

		case 0x20:		             				// SLA+W has been transmitted; NOT ACK has been received.
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET = (1 << I2EN)| (1 << STO);	// Seteo STO para arrancar proceso de STOP.
			estadoI2C = I2C_FAILED;  				// Informo de falla de transmision.
			dataCount = 0;
			break;

		case 0x28:									// Data byte in I2DAT has been transmitted; ACK has been received.
			dataCount++;		   					// Incremento el contador del buffer.
			if(dataCount >= txBuffSize)				// Pregunto si es el último dato.
			{
				I2C1CONCLR = (1 << STA) | (1 << SI);		// Apago STA, Limpio el flag de interrupcion.
				I2C1CONSET = (1 << (4 + isDummyWrite));  	// Seteo STO para proceso de STOP o STA para otra condicion de START.
				if(isDummyWrite)
				{
					slaveAddr |= 0x01;						// Retransmito en modo READ
				}else{
					estadoI2C = I2C_IDLE;					// Entro en modo oscioso
				}
				dataCount = 0;								// De cualquier modo reseteo el buffer
			}else{
				I2C1DAT = txBuffer[dataCount];	 			// Cargo dato.
				I2C1CONCLR = (1 << STA) | (1 << SI);		// Apago STA, Limpio el flag de interrupcion.
			}
			break;

		case 0x30:					  				// Data byte in I2DAT has been transmitted; NOT ACK has been received.
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET = (1 << I2EN)| (1 << STO);	// Seteo STO para arrancar proceso de STOP.
			estadoI2C = I2C_IDLE;	   				// Libero al periférico para nueva transmisión.
			dataCount = 0;
			break;

		case 0x38:									// Arbitration lost in SLA+R/W or Data bytes.
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			dataCount = 0;
			break;

			//RECEIVER MODE---------------------------------------------------------------------------------//
		case 0x40:									// SLA+R has been transmitted; ACK has been received.
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET = (1 << AA);					// Pongo el bit de ACK
			break;

		case 0x48:									// SLA+R has been transmitted; NOT ACK has been received.
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET = (1 << STO);				// Pongo el bit de STOP
			estadoI2C = I2C_FAILED; 				// Falló
			dataCount = 0;
			break;

		case 0x50:									// Data byte has been received; ACK has been returned.
			rxBuff[dataCount] = I2C1DAT;			// Guardo en el buffer el dato recibido
			dataCount++;
			if(dataCount >= rxBuffSize -1)			// Si se llenó el buffer
			{
				I2C1CONCLR = (1 << STA) | (1 << SI) | (1 << AA);	// APAGO START - LIMPIO FLAG - APAGO ACK
			}else{
				I2C1CONCLR = (1 << STA) | (1 << SI);				// Apago START - LIMPIO FLAG
				I2C1CONSET =  (1 << AA);							// Pongo el bit de ACK
			}
			break;

		case 0x58:									// Data byte has been received; NOT ACK has been returned.
			rxBuff[dataCount] = I2C1DAT;			// Recibo dato
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			I2C1CONSET =  (1 << STO);				// Pongo el bit de STOP
			estadoI2C = I2C_DATAV;					// Especifico que hay Data Available para I2C1_data_read
			dataCount = 0;
			break;

		default:
			I2C1CONCLR = (1 << STA) | (1 << SI);	// Apago STA, Limpio el flag de interrupcion.
			break;
	}
}


int writeI2C(uint8_t addr, uint8_t modo, uint8_t* data, uint8_t sizet, uint8_t sizer)
{
	//Notas de uso de esta función
	/**
	 *	Depende del modo de uso:
	 *
	 *	R:	IMPORTANTE, SOLO FUNCIONA SI ANTES HICISTE WRITE
	 *		Carga la slaveAddr y el tamaño del buffer de lectura y escritura.
	 *		Pero no carga el bufferTx. Genera START.
	 *
	 *	W:	Carga la slaveAddr, el tamaño de los buffer y el bufferTx.
	 *		Genera START y aparte va a escribir el bufferTx.
	 *
	 *	DW:	Hace lo mismo que Write, pero carga un flag para que cuando termine
	 *		de recibir ACK (I2C1STAT = 0x28) retrasnmita en modo lectura.
	 *
	 */
	int salida = 1;
	uint8_t i = 0;
	if(estadoI2C != I2C_BUSY && estadoI2C != I2C_DATAV)		//Cuando se pueda escribir:
	{
		//Asignaciones
		currentAdress = addr;
		addr = ((addr << 1) & (0b11111110));  	//Meto en addr la slave_addr
		addr |= (modo & 0b01);					//Le cargo el modo (notese que si es Dummy_write, se va a ver como write)
		txBuffSize = sizet; 					//size transmisión
		rxBuffSize = sizer;						//size recepción

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

		I2C1CONCLR = 1 << SI;					//Limpio flag interrupcion
		I2C1CONSET = (1 << I2EN) | (1 << STA);	//Pongo en Enable y el STAR en 1
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
	//-----------Configuración Pines--------------------

	//SDA	(P0.19 - Expansión 5)
		SetPINSEL(P0,19,3);			//Habilitas el pin como SDA1
		SetPINMODE(P0,19,2);		//Configuras el pin como 'neither pull-up nor pull-down'
		SetPINMODE_OD(P0,19,1);		//Configuro el pin como Open Drain
	//SCL	(P0.20 - Expansión 10)
		SetPINSEL(P0,20,3);			//Habilitas el pin como SCL1
		SetPINMODE(P0,20,2);		//Configuras el pin como 'neither pull-up nor pull-down'
		SetPINMODE_OD(P0,20,1);		//Configuro el pin como Open Drain

	//-----------Configuración Registros I2C-------------
		PCONP |= 1 << 19; 			//Energizar I2C1

		// Le asigno el clock completo (como tengo inicializado el PLL --> 100 Mhz)

		PCLKSEL1 &= ~(3 << 6);		//Asegura 00 en la posicion correspondiente a I2C0 de PCLKSEL1
		PCLKSEL1 |= 1 << 6;			//Pone 01 en la posicion correspondiente a I2C0 de PCLKSEL1
		I2C1CONCLR = (1<<2) | (1<<3) | (1<<5) | (1<<6);

		I2C1SCLH =  500;			//Pongo un duty cycle de 50%
		I2C1SCLL =  500;			//La frecuencia de salida va a seguir la siguiente formula
									//f = PCLKI2C/(I2C1SCLH + I2C1SCLL)
									//Con nuestros valores: f = 100Mhz/(500+500) = 100Mhz/1000 = 100Khz

		ISER0 |= 1 << 11;			//Esto habilita la interrupción de I2C1

		I2C1CONSET = (1 << I2EN);	//Pongo en 1 el único valor para que funcione como Master Transmitter
									//Aseguro que todos los registros que nos interesan tengan 0
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

void MyInitPLL(void)
{
	SCS       = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
		while ((SCS & (1<<6)) == 0);		/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      		/* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     		/* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    		/* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      		/* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             			/* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));			/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             			/* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             			/* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));			/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             			/* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        		/* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    		/* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}
