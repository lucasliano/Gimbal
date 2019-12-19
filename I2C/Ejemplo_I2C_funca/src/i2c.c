#include "func.h"

/**
  \var volatile uint8_t txBuffer[I2C_TX_BUFF_SIZE];
  \brief Almacena los datos a enviar por el I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t txBuffer[I2C_TX_BUFF_SIZE];

/**
  \var volatile uint8_t rxBuff[I2C_RX_BUFF_SIZE];
  \brief Almacena los datos a recibidos por el I2C1..
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t rxBuff[I2C_RX_BUFF_SIZE];

/**
  \var volatile uint8_t estadoI2C;
  \brief Almacena el estado actual del periférico I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t estadoI2C;

/**
  \var volatile uint8_t slaveAddr;
  \brief Almacena la dirección de slave I2C a la que se le va a hablar.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t slaveAddr;

/**
  \var volatile uint8_t txBuffSize;
  \brief Almacena el tamaño de datos a enviar por el módulo I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t txBuffSize;

/**
  \var volatile uint8_t rxBuffSize;
  \brief Almacena el tamaño de datos a recibir por el módulo I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t rxBuffSize;

/**
  \var volatile uint8_t currentAdress;
  \brief Almacena la última dirección con la que se hablo.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t currentAdress;

/**
  \var volatile uint8_t isDummyWrite;
  \brief Flag para indicar escritura y lectura simultanea del periférico I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
extern volatile uint8_t isDummyWrite;


/**
  \fn void I2C1_IRQHandler(void);
  \brief Handler de la interrupcion para I2C1. Se encarga de generar la comunicación a partir de la información suminstrada por el registro I2C1STAT.
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
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


/*============================Declaracion de rutinas===============================================================*/



/**
  \fn void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion );
  \brief Se encarga de modificar el valor del registro PINSEL.
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion )
{
	puerto = puerto * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ puerto ] = PINSEL[ puerto ] & ( ~ ( 3 << pin ) );
	PINSEL[ puerto ] = PINSEL[ puerto ] | ( funcion << pin );
}

/**
  \fn void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo);
  \brief Se encarga de modificar el valor del registro PINMODE.
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}

/**
  \fn void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion);
  \brief Se encarga de modificar el valor del registro PINMODE_OD.
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion)
{
	PINMODE_OD[puerto] &= ~(1 << pin);	 		//Aseguo un 0
	PINMODE_OD[puerto] |= (funcion << pin);		//Le asigno el valor al puerto
}

/**
  \fn void MyInitPLL(void);
  \brief Rutina suministrada por ayudante de la materia. La misma inicializa el PLL (CLK = 100Mhz).
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
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


/**
  \fn void initI2C(void);
  \brief Rutina a nivel de Drivers encargada de inicializar el periférico I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
void initI2C(void)
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




/**
  \fn int8_t writeI2C_driver(uint8_t addr, uint8_t modo, uint8_t* data, uint8_t sizet, uint8_t sizer);
  \brief Funcion a nivel de Primitiva encargada de escribir en el periférico de I2C.
  \param uint8_t addr - Dirrecion del Slave donde se quiere W/R.
  \param uint8_t modo - Se elige que se quiere hacer, si Write, Read o DM(dummyRead) que es equivalente a escribir y leer.
  \param uint8_t* data - Buffer que se va a enviar. En caso de Read, no influye en nada.
  \param uint8_t sizet - Cantidad de elementos que se desean escribir del bufferTX.
  \param uint8_t sizer - Cantidad de elementos que se desean leer del bufferRx.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si (estadoI2C == I2C_BUSY || estadoI2C == I2C_DATAV)
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
int8_t writeI2C_driver(uint8_t addr, uint8_t modo, uint8_t* data, uint8_t sizet, uint8_t sizer)
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
	int salida = -1;
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

		salida = -1;
	}

	return salida;
}


/**
  \fn int8_t readI2C_driver(uint8_t* data, uint8_t size);
  \brief Funcion a nivel de Driver encargada de recoger todos datos del bufferRx de I2C.
  \param uint8_t* data - Buffer en el que se van a guardar los datos.
  \param uint8_t size - Cantidad de elementos que se desean leer del buffer.
  \return Se devuelve el -1 en caso de error y 0 en caso de acierto.
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
int8_t readI2C_driver(uint8_t* data, uint8_t size)
{
	uint8_t i = 0;
	uint8_t out = -1;
	if(estadoI2C == I2C_DATAV) 		//Data available
	{
		for(i = 0; i < size; i++)
		{
			data[i] = rxBuff[i]; 	//Guardo en el vector de aplicación
			rxBuff[i] = 0; 			//Vacío el buffer
		}
		out = 0;
	}
	estadoI2C = I2C_IDLE; 			//Ya vacié los datos --> IDLE

	return out;
}




/**
  \fn int8_t singleReadI2C(uint8_t addr, uint8_t RA, uint8_t* data);
  \brief Funcion a nivel de Primitiva encargada de leer un solo registro de un dispositivo en el periférico de I2C.
  \details Guarda el dato del registro RA en DATA[0] del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere leer.
  \param uint8_t RA - Direccion del registro que se pretende leer.
  \param uint8_t* data - Variable donde se va a guardar el dato.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t singleReadI2C(uint8_t addr, uint8_t RA, uint8_t* data)
{
	uint8_t salida = -1;
	uint8_t buffEnvio[1];
	uint16_t timeout = 10; 	//ms

	buffEnvio[0] = RA;

	if ( writeI2C_driver(addr, DW, buffEnvio, 1, 1) == 0)
	{
		myDelay(10);

		TimerStart(TIMER_DELAY, timeout, donothing , MS );
		while( GetTimer(TIMER_DELAY) != 0 && salida != 0)			//Pregunto hasta que pueda leer el dato o hasta que expire el tiempo
		{
			if(readI2C_driver(data, 1) == 0)
				salida = 0;											//Si pude leer el dato, salgo con 0, sino sigo con -1
		}
		TimerStop(TIMER_DELAY);
	}

	return salida;
}



/**
  \fn int8_t singleWriteI2C(uint8_t addr, uint8_t RA, uint8_t data);
  \brief Funcion a nivel de Primitiva encargada de escribir un solo registro de un dispositivo en el periférico de I2C.
  \details Escribe DATA en RA del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere escribir.
  \param uint8_t RA - Direccion del registro que se pretende escribir.
  \param uint8_t data - Dato que se quiere escribir.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t singleWriteI2C(uint8_t addr, uint8_t RA, uint8_t data)
{
	int8_t out = -1;
//	uint8_t aux[1];
	uint8_t buffEnvio[2];



	buffEnvio[0] = RA;
	buffEnvio[1] = data;
	if(writeI2C_driver(addr, W, buffEnvio, 2, 0) == 0)			//Modificamos el registro..
	{
//		myDelay(10);
//		if(singleReadI2C(addr, RA, aux) != -1)					//Leemos el registro que modificamos
//		{
//			if(aux[0] == data)									//Si se puede realizar la lectura, entonces comparamos el valor que se escribio con el que se debería haber guardado
//				out = 0;										//Si coinciden, devuelvo 0
//		}
		out = 0;
	}

	return out;
}


/**
  \fn int8_t burstReadI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size);
  \brief Funcion a nivel de Primitiva encargada de leer varios registros de un dispositivo en el periférico de I2C.
  \details Guarda los datos del registro RA[i] en DATA[i] del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere leer.
  \param uint8_t RA - Direccion del registro que se pretende leer.
  \param uint8_t* data - Dato que se quiere escribir.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t burstReadI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size)		//Guarda el dato del registro RA[i] en DATA[i] del dispositivo con direccion ADDR
{
	int8_t out = 0;

	for(int i = 0; i < size; i++)
	{
		if( singleReadI2C(addr, RA[i], &data[i]) == -1)					//Leemos todos los datos. Si alguno tuvo error se notifica en la salida.
			out = -1;
	}

	return out;
}



/**
  \fn int8_t burstWriteI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size);
  \brief Funcion a nivel de Primitiva encargada de escribir varios registro de un dispositivo en el periférico de I2C.
  \details Escribe DATA[i] en RA[i] del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere escribir.
  \param uint8_t* RA - Direccion de los registros que se pretende escribir.
  \param uint8_t* data - Variable donde se va a guardar los datos.
  \param uint8_t size - Cantidad de registos dentro de RA.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t burstWriteI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size)	//Escribe DATA[i] en el registro RA[i] del dispositivo con direccion ADDR
{
	int8_t out = 0;

	for(int i = 0; i < size; i++)
	{
		if( singleWriteI2C(addr, RA[i], data[i]) == -1)						//Escribimos todos los datos. Si alguno tuvo error se notifica en la salida.
			out = -1;
	}

	return out;
}



