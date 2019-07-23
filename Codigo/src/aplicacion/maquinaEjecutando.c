/**
  \file maquinaEjecutando.c
  \brief Se encuentran las rutinas relacionadas con la creacion de la señal PWM. (Hasta ahora esta hecha las maquinas de LEDS)
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "headers/aplicacion/maquinaEjecutando.h"

/*Variables globales*/
extern uint16_t timePeriodo;
extern uint16_t actual;
extern uint16_t output;
extern uint16_t periodo;

/*Declaracion de rutinas*/

/**
  \fn void F_Ejecutando();
  \brief Es la rutina que hasta el momento implementa cual es la salida del sistema.
  \author Grupo 8 - R2003
  \date 2019.07.23\return TRUE si se pudo realizar la medición, FALSE si hubo algun fallo.
*/
void F_Ejecutando()
{
  if(timePeriodo >= periodo)
  {
    actual += output;
    SetTimer(TIMER_PERIODO);
  }
}
