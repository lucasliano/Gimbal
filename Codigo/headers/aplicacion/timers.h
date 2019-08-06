/**
  \file tiemrs.h
  \brief Almacena las definiciones de las rutinas realcionadas con timers a nivel de aplicación.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/* Timers*/
#define TIMER_DEC 1   //100ms
#define TIMER_SEG 2   //1000ms
#define TIMER_MIN 3   //60000ms

/*Nombre de timers transparentes*/
#define TIMER_CONTROL 1
#define TIMER_BOTON 2
#define TIMER_PERIODO 3


/*Funciones asociadas a timers*/
void Init_Timers();
void ActualizarDec();
void ActualizarSeg();
void ActualizarMin();
void SetTimer(uint16_t timer);
