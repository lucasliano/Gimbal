#ifndef DRIVERS_PR_TIMERS_H_
#define DRIVERS_PR_TIMERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"

#ifndef NULL
#define 	NULL	(( void *) 0)
#endif



#define 	N_TIMERS		30		//Cantidad de timers disponibles

typedef void (*Timer_Handler)(void);

extern volatile 	uint32_t Tmr_Run[ N_TIMERS ];			//Valor actual del contador
extern volatile 	uint8_t  TMR_Events[ N_TIMERS ];		//Es el flag
extern void 	 	(* TMR_handlers [N_TIMERS]) (void);		//Array de punteros a funcion
extern volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];		//Esta en pausa?
extern volatile 	uint8_t  Tmr_Base[ N_TIMERS ];			//Unidad del timer

void AnalizarTimers(void);			//Decrementa los timers
void TimerEvent(void);				//Ejecuta las rutinas de los timers vencidos



#ifdef __cplusplus
}
#endif

#endif /* TIMERS_H_ */
