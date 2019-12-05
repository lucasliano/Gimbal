#ifndef TIMERS_H_
#define TIMERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Regs_LPC176x.h"

#ifndef NULL
#define 	NULL	(( void *) 0)
#endif



typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;



#define 	N_TIMERS		30		//Cantidad de timers disponibles

typedef void (*Timer_Handler)(void);

extern volatile 	uint32_t Tmr_Run[ N_TIMERS ];			//Valor actual del contador
extern volatile 	uint8_t  TMR_Events[ N_TIMERS ];		//Es el flag
extern void 	 	(* TMR_handlers [N_TIMERS]) (void);		//Array de punteros a funcion
extern volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];		//Esta en pausa?
extern volatile 	uint8_t  Tmr_Base[ N_TIMERS ];			//Unidad del timer

void AnalizarTimers(void);			//Decrementa los timers
void TimerEvent(void);				//Ejecuta las rutinas de los timers vencidos



//===============================================================================
//===============================================================================
#define		MS			0
#define 	DEC			1
#define 	SEG			2
#define 	MIN			3

#define 	RUN			0
#define 	PAUSE		1

//Timers
#define TIMER_DELAY			0
#define READ_I2C_TIMER 		1



void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );	//Inicializa un timer
void SetTimer( uint8_t event, uint32_t time );											//Cambia el contador regresivo del timer
uint32_t GetTimer( uint8_t event );														//Devuelve el contador del timer
void StandByTimer( uint8_t event , uint8_t accion);										//Pause/Play
void TimerStop(uint8_t event);															//Deshabilita un timer (le saca el handler y los contadores)
void TimerClose(void);																	//Corre un timerStop de todos los timers
void myDelay(uint16_t ms);

void donothing( void );


#ifdef __cplusplus
}
#endif

#endif /* TIMERS_H_ */
