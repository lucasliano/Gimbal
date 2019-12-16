/**
  \file DR_Servo.h
  \brief Se encuentran las declaraciones de las rutinas asociadas al funcionamiento de los servomotores por GPIO.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/
#ifndef SERVOS_H_
#define SERVOS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"


void ActualizarServosGPIO(void);
void ModificarServo( uint8_t servo, uint16_t dato);
void InicializarServos(void);



#ifdef __cplusplus
}
#endif

#endif /* SERVOS_H_ */
