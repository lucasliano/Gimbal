/*******************************************************************************************************************************//**
 *
 * @file		DR_UART.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		12 de oct. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERLPC_DR_UART0_H_
#define DRIVERLPC_DR_UART0_H_
#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "all.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define MAX_BUFF_RX		512
#define MAX_BUFF_TX		512

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void UART0_Inicializacion (uint32_t );
void UART0_PushRX( uint8_t dato );
int16_t UART0_PopRX( void );
void UART0_PushTX( uint8_t dato );
int16_t UART0_PopTX( void );


#ifdef __cplusplus
}
#endif
#endif /* DRIVERLPC_DR_UART0_H_ */
