/**
  \file tiemrs.h
  \brief Almacena las definiciones de las rutinas realcionadas con timers a nivel de aplicación.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/
#ifndef TIMERS_H_
#define TIMERS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"


/*Funciones asociadas a timers*/
void Init_Timers();
void Stop_Timers();


#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
