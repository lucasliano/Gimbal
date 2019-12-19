/**
  \file PR_timers.h
  \brief Se detallan todas las declaraciones correspondiente a la maquinaria de timers a nivel de primitivas.
  \author Grupo 8 - R2003
  \date 2019.11.24
  \version 1.2
*/

#ifndef PRIMITIVAS_PR_TIMERS_H_
#define PRIMITIVAS_PR_TIMERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"

#ifndef NULL
#define 	NULL	(( void *) 0)
#endif

//Base de tiempo para los timers
#define		US			0
#define		MS			1
#define 	DEC			2
#define 	SEG			3
#define 	MIN			4

//Defines para el funcionamiento del stand-by
#define 	RUN			0
#define 	PAUSE		1

//Unidades de tiempo para un SysTick a 100us
#define		DECIMA_MILISEGUNDOS		1
#define		MILISEGUNDOS			10	* DECIMA_MILISEGUNDOS
#define 	DECIMAS					100	* MILISEGUNDOS
#define 	SEGUNDOS				10 	* DECIMAS
#define 	MINUTOS					60 	* SEGUNDOS

/* Timers*/
#define TIMER_DELAY			0
#define READ_I2C_TIMER 		1
#define TIMER_IMU 			2	//FRECUENCIA_MEDICION_IMU_MS
#define TIMER_PLOT			3	//FRECUENCIA_PLOT_MS
#define TIMER_CONTROL 		4	//kTime	(en ms)
#define TIMER_PERIODO 		5	//kPeriodo (en ms)
#define TIMER_WATCHDOG		6



void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );	//Inicializa un timer
void SetTimer( uint8_t event, uint32_t time );											//Cambia el contador regresivo del timer
uint32_t GetTimer( uint8_t event );														//Devuelve el contador del timer
void StandByTimer( uint8_t event , uint8_t accion);										//Pause/Play
void TimerStop(uint8_t event);															//Deshabilita un timer (le saca el handler y los contadores)
void TimerClose(void);																	//Corre un timerStop de todos los timers
void myDelay(uint16_t ms);
void Watchdog(void);

void donothing( void );


#ifdef __cplusplus
}
#endif


#endif /* PRIMITIVAS_PR_TIMERS_H_ */
