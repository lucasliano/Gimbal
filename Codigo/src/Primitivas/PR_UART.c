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
