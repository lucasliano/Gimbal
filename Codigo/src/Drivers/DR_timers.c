/**
  \file DR_timers.h
  \brief Almacena todas las declaraciones correspondientes a la maquinaria de timers a nivel de drivers.
  \author Grupo 8 - R2003
  \date 2019.11.24
  \version 1.2
*/

#include "all.h"



volatile 	uint32_t Tmr_Run[ N_TIMERS ];
volatile 	uint8_t  TMR_Events[ N_TIMERS ];
void 	 	(* TMR_handlers [N_TIMERS]) (void);
volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
volatile 	uint8_t  Tmr_Base[ N_TIMERS ];


/**
  \fn void donothing( void );
  \brief No hace nada. Se utiliza en el timer del delay, para que la rutina asociada a la interrupción no haga nada :D
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
void donothing( void )
{

}


/**
  \fn void myDelay(uint16_t ms);
  \brief Rutina bloqueante que genera un delay de la cantidad indicada de milisegundos
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
void myDelay(uint16_t ms)						//Nota, le pifia por algunos ms... me tira 4,71seg cuando deberian ser 5seg
{
	TimerStart(TIMER_DELAY, ms, donothing , MS );
	while(GetTimer(TIMER_DELAY) != 0);
	TimerStop(TIMER_DELAY);
}




/**
	\fn void AnalizarTimers(void)
	\brief Decremento periodico de los contadores
 	\details Decrementa los contadores de los timers en ejecucion. Debe ser llamada periodicamente con la base de tiempos
	\return void
*/
void AnalizarTimers(void)
{
	uint32_t i;
	for(i = 0; i < N_TIMERS ; i++)
	{
		if(Tmr_Run[ i ])
		{
			if ( !TMR_StandBy[ i ] )
			{
				Tmr_Run[ i ]--;
				if(!Tmr_Run[ i ])
					TMR_Events[ i ] = 1;
			}
		}
	}

}

/**
	\fn void TimerEvent(void)
	\brief Chequeo de timers vencidos
 	\details Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
	\return void
*/
void TimerEvent(void)
{
	uint8_t i;
	for( i=0 ; i < N_TIMERS ; i++ )
	{
		if(TMR_Events[ i ])
		{
			TMR_handlers[ i ]( );
			TMR_Events[ i ] = 0;
		}
	}
}
