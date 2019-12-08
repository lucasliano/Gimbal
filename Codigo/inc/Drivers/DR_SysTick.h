/**
  \file DR_SysTick.h
  \brief Almacena todas las declaraciones correspondientes al systick a nivel de drivers.
  \author Grupo 8 - R2003
  \date 2019.11.24
  \version 1.2
*/

#ifndef DR_SYSTICK_H_
#define DR_SYSTICK_H_

#ifdef __cplusplus
extern "C" {		//En este archivo hace falta aclarar si lo vamos a compilar como C o C++
#endif				//Como vamos a programar c acá, entonces lo declaramos como C

#include "all.h"



void InicializarSysTick ( void );
void Actualizar_Ticks(void);
uint32_t GetTicks(void);


#ifdef __cplusplus
}
#endif
#endif /* DR_SYSTICK_H_ */
