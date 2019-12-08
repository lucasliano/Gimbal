/**
  \file PR_timers.c
  \brief Se desarrollan las funciones relacionadas a la maquinaria de timers a nivel de primitivas.
  \author Grupo 8 - R2003
  \date 2019.11.24
  \version 1.2
*/

#include "all.h"


/**
	\fn void TimerStart(uint8_t event, uint32_t t, void (*handler)(void), uint8_t base)
	\brief Inicia un timer
 	\details Inicia el timer \a e al transcurrir el tiempo especificado por \a t se llama a la funcion apuntada por \a handler
 	\param uint8_t event: Numero de evento entre 0 y 31
 	\param uint32_t t: Tiempo del evento. Dependiente de la base de tiempos
 	\param void (*handler)(void): Callback del evento
 	\param uint8_t base: Base de tiempo (SEG, MS, etc.)
	\return void
*/
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base )
{
	switch ( base )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= SEGUNDOS;
			break;
		case MIN:
			time *= MINUTOS;
			break;
		case MS:
			time *= MILISEGUNDOS;
			break;
		case US:
			time *= DECIMA_MILISEGUNDOS;
			break;
	}

	Tmr_Base[event] = base;

	if(time != 0)	//si el tiempo no es 0, lo cargo
	{
		Tmr_Run[event] = time;
		TMR_Events[event] = 0;
	}
	else	//si el tiempo es cero, el timer vence automáticamente
	{
		Tmr_Run[event] = 0;
		TMR_Events[event] = 1;
	}
	TMR_handlers[event] = handler;
}

/**
	\fn void SetTimer( uint8_t event , uint32_t t )
	\brief Inicia un timer
 	\details Reinicia el timer con el valor t (no lo resetea)
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\return void
*/
void SetTimer( uint8_t event, uint32_t time )
{
	switch ( Tmr_Base[event] )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= SEGUNDOS;
			break;
		case MIN:
			time *= MINUTOS;
			break;
		case MS:
			time *= MILISEGUNDOS;
			break;
		case US:
			time *= DECIMA_MILISEGUNDOS;
			break;
	}
	Tmr_Run[event] = time;
}

/**
	\fn  GetTimer( uint8_t event )
	\brief Toma el valor al vuelo del timer en cuestion
 	\details Lee el timer
 	\param [in] event Numero de evento entre 0 y 31
 	\return valor del timer
*/
uint32_t GetTimer( uint8_t event )
{
	uint32_t time = Tmr_Run[event];

	switch ( Tmr_Base[event] )
	{
		case MS:
			time /= MILISEGUNDOS;
			break;
		case US:
			time /= DECIMA_MILISEGUNDOS;
			break;
		case DEC:
			time /= DECIMAS;
			break;
		case SEG:
			time /= SEGUNDOS;
			break;
		case MIN:
			time /= MINUTOS;
			break;

	}

	return time;
}

/**
	\fn  StandByTimer( uint8_t event , uint8_t accion)
	\brief Detiene/Arranca el timer, NO lo resetea
 	\details lo pone o lo saca de stand by
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] accion RUN lo arranca, PAUSE lo pone en stand by
 	\return void
*/
void StandByTimer( uint8_t event , uint8_t accion)
{
	TMR_StandBy[ event ] = accion;
}

/**
	\fn void TimerStop(Eventos e)
	\brief Detiene un timer
 	\details Detiene el timer \a e
 	\param [in] e Numero de evento entre 0 y 31
	\return void
*/
void TimerStop(uint8_t event)
{
	Tmr_Run[ event ] = 0;
	TMR_Events[ event ] = 0;
	TMR_handlers[ event ] = NULL;
	Tmr_Base[ event ] = 0;
	TMR_StandBy[ event ] = RUN;
}

/**
	\fn void TimerClose(void)
	\brief Detiene los timers
 	\details Detiene todos los timers
	\return void
*/
void TimerClose(void)
{
	uint32_t i;

	for( i=0 ; i < N_TIMERS ; i++ )
		TimerStop( i );
}
