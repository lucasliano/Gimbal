/*******************************************************************************************************************************//**
 * @details		Proyecto: TK1681-Horno Combi
 * @file		FW_lcd.c
 * @brief		DESCRIPCION ---------------
 * @date		8/11/2016
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

volatile uint32_t lcdDelay;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint8_t lcdBuffer[LCD_BUFFER_SIZE];
volatile uint32_t lcdInxIn;
volatile uint32_t lcdInxOut;
volatile uint32_t lcdDataCount;

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
	@fn  		void LCD_Startup(void)
	@brief 		Inicializacion del LCD
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param 		void
	@return void
*/
void InicializarLCD(void)
{
	uint8_t i;

	SetDIR( LCD_RS , SALIDA );
	SetDIR( LCD_EN , SALIDA );
	SetDIR( LCD_D4 , SALIDA );
	SetDIR( LCD_D5 , SALIDA );
	SetDIR( LCD_D6 , SALIDA );
	SetDIR( LCD_D7 , SALIDA );

	SetPIN( LCD_EN , OFF );

	lcdDelay = 50;				// Demora inicial
	while (lcdDelay);

	for( i = 0 ; i < 3 ; i++ )
	{
		SetPIN( LCD_D4 , 1 );	// Configuracion en 8 bits
		SetPIN( LCD_D5 , 1 );
		SetPIN( LCD_D6 , 0 );
		SetPIN( LCD_D7 , 0 );

		SetPIN( LCD_RS , 0);
		SetPIN( LCD_EN , 1);
		SetPIN( LCD_EN , 0);
		lcdDelay = 5;
		while (lcdDelay);
	}

	// Configuracion en 4 bits
	SetPIN( LCD_D4 , 0 );
	SetPIN( LCD_D5 , 1 );
	SetPIN( LCD_D6 , 0 );
	SetPIN( LCD_D7 , 0 );

	SetPIN( LCD_RS , 0 );
	SetPIN( LCD_EN , 1 );
	SetPIN( LCD_EN , 0 );

	lcdDelay = 3;	// Demora inicial
	while (lcdDelay);

	// A partir de aca el LCD pasa a 4 bits !!!
	LCD_Push( 0x28 , LCD_CONTROL );	// DL = 0: 4 bits de datos
									// N = 1 : 2 lineas
									// F = 0 : 5x7 puntos

	LCD_Push( 0x08 , LCD_CONTROL);	// D = 0 : display OFF
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF

	LCD_Push( 0x01 , LCD_CONTROL);	// clear display

	LCD_Push( 0x06 , LCD_CONTROL);	// I/D = 1 : Incrementa puntero
									// S = 0 : NO Shift Display

	// Activo el LCD y listo para usar !
	LCD_Push( 0x0C , LCD_CONTROL);	// D = 1 : display ON
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF
}
/**
	@fn  		int8_t LCD_Push( uint8_t data , uint8_t control )
	@brief 		Coloca los datos a imprimir en el LCD en el buffer circular
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param [in] data: dato a almacenar
 	@param [in] control: indica si es dato o control
	@return 0 por Exito, -1 por Error
*/
int8_t LCD_Push( uint8_t data , uint8_t control )
{
//	if ( lcdDataCount >= LCD_BUFFER_SIZE )
//		return -1;


	lcdBuffer [ lcdInxIn ] = ( data >> 4 ) & 0x0f;
	if ( control == LCD_CONTROL )
		lcdBuffer [ lcdInxIn ] |= 0x80;

	lcdInxIn ++;

	lcdBuffer [ lcdInxIn ] = data & 0x0f;
	if ( control == LCD_CONTROL )
		lcdBuffer [ lcdInxIn ] |= 0x80;
	lcdDataCount += 2;

	lcdInxIn ++;
	lcdInxIn %= LCD_BUFFER_SIZE;

	return 0;
}

/**
	@fn  		int16_t LCD_Pop( void )
	@brief 		Toma los  datos a imprimir en el LCD del buffer circular
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param 		void
	@return 	dato por Exito, -1 por Error
*/
int16_t LCD_Pop( void )
{
	uint8_t dato;

//	if ( lcdDataCount == 0 )
//		return -1;
	if ( lcdInxOut == lcdInxIn )
		return -1;

	dato = lcdBuffer [ lcdInxOut ] ;

	lcdDataCount --;

	lcdInxOut ++;
	lcdInxOut %= LCD_BUFFER_SIZE;

	return dato;
}

/**
	@fn  		int16_t LCD_Pop( void )
	@brief 		enviael dato al LCD
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param 		void
	@return 	void
*/
void EscrituraLCD( void )
{
	int16_t data;

	if ( lcdDelay )
		lcdDelay--;

	if ( ( data = LCD_Pop( ) ) == -1 )
		return;

	SetPIN( LCD_D4 ,( (uint8_t) data) >> 0 & 0x01 );
	SetPIN( LCD_D5 ,( (uint8_t) data) >> 1 & 0x01 );
	SetPIN( LCD_D6 ,( (uint8_t) data) >> 2 & 0x01 );
	SetPIN( LCD_D7 ,( (uint8_t) data) >> 3 & 0x01 );

	if( ( (uint8_t) data ) & 0x80 )
		SetPIN( LCD_RS , 0 );
	else
		SetPIN( LCD_RS , 1 );

	SetPIN( LCD_EN , ON );
	SetPIN( LCD_EN , ON );
	SetPIN( LCD_EN , ON );
	SetPIN( LCD_EN , ON );

	SetPIN( LCD_EN , OFF );
	SetPIN( LCD_EN , OFF );
	SetPIN( LCD_EN , OFF );
	SetPIN( LCD_EN , OFF );
}
