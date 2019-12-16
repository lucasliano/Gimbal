/**
  \file comunicaciones.h
  \brief Se encuentran los prototipos y defines acordes a las rutinas relacionadas al funcionamiento de la comunicacion serie a nivel de primitivas.
  \author Grupo 8 - R2003
  \date 2019.11.09
  \version 1.2
*/

#ifndef INC_COMUNICACIONES_H_
#define INC_COMUNICACIONES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"
//============TIPOS DE MENSAJE==============================
#define PIT 0
#define RLL 1
#define YAW 2
#define DEB 3
#define OUT 4
#define ACC 5
#define GYR 6

//============DEFINES IMPORTANTES===========================
#define CANT_MAX_ENVIO_UART 50
#define FRECUENCIA_PLOT_MS	5


void reenviar(uint8_t dato);
char enviarUART(uint8_t* dato, uint8_t size, uint8_t type);

#ifdef __cplusplus
}
#endif

#endif /* INC_COMUNICACIONES_H_ */
