/*******************************************************************************************************************************//**
 *
 * @file		PR_UART.c
 * @brief		Descripcion del modulo
 * @date		5 de oct. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/
#include "all.h"

#define MAX_DATOS	255

/**
	\fn int16_t Transmitir ( uint8_t com , const void * datos , uint8_t cant)
	\brief despacha los datos a transmitir
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t com: Puerto que sera utilizado
	\param [in] const void * datos: datos a transmitir
	\param [in] uint8_t cant: cantidad de datos a transmitir
	\return 0 por exito, -1 por Error (datos exedidos)
*/
int16_t Transmitir ( uint8_t com , const void * datos , uint8_t cant )
{
	uint8_t	i;

	if ( cant > MAX_DATOS )
		return -1;

	for ( i = 0 ; i < cant ; i++ )
	{
		switch ( com )
		{
			case UART_0:
				UART0_PushTX( * ( ( uint8_t * ) ( datos + i ) ) );
				break;
			case UART_1:
//				UART1_PushTX( * ( ( uint8_t * ) ( datos + i ) ) );
				break;
		}
	}
	return 0 ;
}

/**
	\fn  int16_t PopRX( void )
	\brief saca un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART_PopRX( uint8_t uart)
{
	switch(uart){

		case UART_0:
			return UART0_PopRX();
			break;

		case UART_1:
//			return UART1_PopRX();
			break;

		default:
			return -1;
	}
	return -1;
}
