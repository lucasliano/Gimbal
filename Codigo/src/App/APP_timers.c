/**
  \file timers.c
  \brief Se encuentran las rutinas relacionadas con los timers.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas Propias*/
#include "all.h"


extern float kTime;
extern uint16_t kPeriodo;


/*Funciones asociadas a los timers*/


/**
  \fn void Init_Timers();
  \brief Se encarga de llamar por primera vez a los tres timers TIMER_DEC, TIMER_SEG, TIMER_MIN.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Init_Timers()
//-----------------------------------------------------
{
	TimerStart(TIMER_IMU, FRECUENCIA_MEDICION_IMU_MS, MedirIMU, MS);
	TimerStart(TIMER_PLOT, FRECUENCIA_PLOT_MS, enviarPlot, MS);
	TimerStart(TIMER_CONTROL, kTime, donothing, US);
	TimerStart(TIMER_PERIODO, kPeriodo, donothing, US);
}


