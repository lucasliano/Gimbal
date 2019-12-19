/*******************************************************************************************************************************//**
 *
 * @file		DR_UART.c
 * @brief		Descripcion del modulo
 * @date		12 de oct. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "all.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
//!< /////////////		UARTs		///////////////////////////
//0x40010000UL : Registro de recepcion de la UART0:
#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )

#define		UART0RBR		DIR_UART0[0]	// Registro de Recepción RBR
#define		UART0THR		DIR_UART0[0]	// Registro de Transmisión THR
#define		UART0DLL		DIR_UART0[0]	// Parte baja del divisor de la UART0:
#define		UART0IER			DIR_UART0[1]	// Registro de Habilitación de interrupciones de la UART0:
#define		UART0DLM		DIR_UART0[1]	// Parte Alta del divisor de la UART0:
#define		UART0IIR			DIR_UART0[2]	// Registro de Identificación de interrupciones de la UART0:
#define		UART0LCR		DIR_UART0[3]	// Line CONTROL Register de la UART0:
#define		UART0LSR		DIR_UART0[5]	// Line STATUS Register de la UART0:

//Macros UART0
#define		UART0DLAB_OFF	(U0LCR & 0xEF)
#define		UART0DLAB_ON	(U0LCR | 0x80)

#define 	TX0			PORT0, 2	//Tx de la UART0
#define 	RX0			PORT0, 3	//Rx de la UART0

//0x40010000UL : Registro de recepcion de la UART1:
#define		DIR_UART1		( ( __RW uint32_t  * ) 0x40010000UL )

#define		UART1RBR		DIR_UART1[0]
#define		UART1THR		DIR_UART1[0]
#define		UART1DLL		DIR_UART1[0]
#define		UART1IER			DIR_UART1[1]
#define		UART1DLM		DIR_UART1[1]
#define		UART1IIR			DIR_UART1[2]
#define		UART1LCR		DIR_UART1[3]
#define		UART1LSR		DIR_UART1[5]

#define 	TX1				PORT0 , 15	//Tx de la UART1
#define 	RX1				PORT0 , 16	//Rx de la UART1

#define		TXD			1
#define		RXD			1


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile static uint8_t UART0_BufferRx[MAX_BUFF_RX];
volatile static uint8_t UART0_BufferTx[MAX_BUFF_TX];
volatile static uint8_t UART0_inRX , UART0_outRX , UART0_inTX, UART0_outTX;
volatile static int16_t UART0_flagTx;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/**
	\fn  void UART0_IRQHandler (void)
	\brief Interrupcion de UART0
 	\author Ing. Marcelo Trujillo
 	\date 31 de ago. de 2016
 	\param void
	\return void
*/
void UART0_IRQHandler (void)
{
	uint8_t iir, aux;
	int16_t datoTx;

	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = UART0IIR;

		if ( iir & 0x04 ) 							//Data ready
		{
			//Display_lcd ("LLEGO msj -UART0", 0 , 0);
			aux = UART0RBR;
			UART0_PushRX ( aux );   	//guardo en buffer e incremento índice
									//garantizo el buffer circular
		}

		if ( iir & 0x02 ) //THRE
		{
			datoTx = UART0_PopTX();
			if ( datoTx != -1 )
				UART0THR = (uint8_t) datoTx;
			else
				UART0_flagTx = 0;
		}
	}
	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entre a la ISR habia otra
						     	int. pendiente de atencion: b0=1 (ocurre unicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */
}

/**
	\fn  	void UART0_Inicializacion ( uint32_t baudios )
	\brief 	Inicializacion de UART0
 	\author Ing. Marcelo Trujillo
 	\date 	31 de ago. de 2016
  	\param 	[in] uint32_t baudios: Velocidad de Tranmision
	\return void
*/
void UART0_Inicializacion ( uint32_t baudios )
{
	//!< 1.- Registro PCONP - bit 3 en 1 prende la UART:
	PCONP |= 0x01	<<	3;

	//!< 2.- Registro PCLKSEL0 - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea CCLK/4:
	PCLKSEL0 &= ~(0x03<<6);			//!< con un CCLOK=100Mhz, nos queda PCLOCK=25Mhz

	//!< 3.- Registro U0LCR - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	UART0LCR = 0x00000083;

	//!< 4.- Registros U10DLL y U0DLM
	baudios =  25000000 / ( 16 * baudios );
	UART0DLM = (baudios >> 8 ) & 0x000000ff;
	UART0DLL = baudios & 0x000000ff;

	//!< 5.- Registros PINSEL0 y PINSEL1 - habilitan las funciones especiales de los pines:
	//!< TX0 : P0[2]	-> PINSEL0: 04:05
	SetPINSEL( TX0 , TXD );
	//!< RX0 : P0[3]	-> PINSEL0: 06:07
	SetPINSEL( RX0 , RXD );

	//!< 6.- Registro U0LCR, pongo DLAB en 0:
	UART0LCR = 0x00000003;

	//!< 7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	UART0IER = 0x00000003;
	ISER0 |= ( 1 << 5 );
}
/**
	\fn  void PushRX( uint8_t dato )
	\brief pone un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART0_PushRX( uint8_t dato )
{
	UART0_BufferRx[ UART0_inRX ] = dato;
	UART0_inRX ++;
	UART0_inRX %= MAX_BUFF_RX;
}

/**
	\fn  int16_t PopRX( void )
	\brief saca un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART0_PopRX( void )
{
	int16_t salida = -1;

	if ( UART0_inRX != UART0_outRX )
	{
		salida = UART0_BufferRx[ UART0_outRX ] ;

		UART0_outRX ++;
		UART0_outRX %= MAX_BUFF_RX;
	}
	return salida;
}
/**
	\fn  void PushTX( uint8_t dato )
	\brief pone un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART0_PushTX( uint8_t dato )
{
	if ( !UART0_flagTx )
	{
		UART0_flagTx = 1;
		UART0THR = dato;
		return;
	}

	UART0_BufferTx[ UART0_inTX ] = dato;
	UART0_inTX ++;
	UART0_inTX %= MAX_BUFF_TX;
}

/**
	\fn int16_t PopTX( void )
	\brief saca un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART0_PopTX( void )
{
	int16_t salida = -1;

	if ( UART0_inTX != UART0_outTX )
	{
		salida = UART0_BufferTx[ UART0_outTX ] ;

		UART0_outTX ++;
		UART0_outTX %= MAX_BUFF_TX;
	}
	return salida;
}
