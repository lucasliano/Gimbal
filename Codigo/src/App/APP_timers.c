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
  \brief Se encarga de llamar por primera vez a los timers.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Init_Timers()
//-----------------------------------------------------
{
	TimerStart(TIMER_PLOT, FRECUENCIA_PLOT_MS, enviarPlot, MS);
	TimerStart(TIMER_CONTROL, kTime, donothing, US);
	TimerStart(TIMER_PERIODO, kPeriodo, donothing, US);
}


/**
  \fn void Stop_Timers();
  \brief Se encarga de apagar los timers exitentes.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Stop_Timers()
//-----------------------------------------------------
{
	TimerStop(TIMER_PLOT);
	TimerStop(TIMER_CONTROL);
	TimerStop(TIMER_PERIODO);

}
