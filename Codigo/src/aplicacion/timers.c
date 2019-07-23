/**
  \file timers.c
  \brief Se encuentran las rutinas relacionadas con los timers.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.1
*/

/*
    Alejo leete esto:
      Puse timers que dependan de cada cuanto los actualizas
      y entonces junto todos los timers que se actualicen
      cada 1 seg, o cada 1 dec , etc.

      Y lo que hago es hacer variables globales que
      vayan acumulando. Cuando quieras hacer un reset, solo
      le pasas el identificador y atr.

      Fijate si entendes lo que hice, y que te parece.
*/

/*Bibliotecas propias*/
#include "headers/aplicacion/timers.h"


/*Acumuladores*/
/**
  \var uint16_t timeControl
  \brief Es el acumulador relacionado al TIMER_CONTROL.
  \details none.
*/
uint16_t timeControl = 0;


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
  TimerStart(TIMER_DEC,1,ActualizarDec,DEC);
  TimerStart(TIMER_SEG,1,ActualizarSeg,SEG);
  TimerStart(TIMER_MIN,1,ActualizarMin,MIN);
}

/**
  \fn void ActualizarDec();
  \brief Rutina encargada de incrementar los acumuladores que tengan como unidad de tiempo a DEC.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void ActualizarDec()
//-----------------------------------------------------
{
  //Acá se actualizan todos los acumuladores
  timeControl = timeControl + 100;


  //Se vuelve a activar el timer
  TimerStart(TIMER_DEC,1,ActualizarDec,DEC);
}

/**
  \fn void ActualizarSeg();
  \brief Rutina encargada de incrementar los acumuladores que tengan como unidad de tiempo a SEG.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void ActualizarSeg()
//-----------------------------------------------------
{
  //Acá se actualizan todos los acumuladores



  //Se vuelve a activar el timer
  TimerStart(TIMER_SEG,1,ActualizarSeg,SEG);
}

/**
  \fn void ActualizarMin();
  \brief Rutina encargada de incrementar los acumuladores que tengan como unidad de tiempo a MIN.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void ActualizarMin()
//-----------------------------------------------------
{
  //Acá se actualizan todos los acumuladores



  //Se vuelve a activar el timer
  TimerStart(TIMER_MIN,1,ActualizarMin,MIN);
}


/**
  \fn void SetTimer(uint16_t timer);
  \brief Rutina encargada de resetear el valor de los acumuladores relacionados con los timers transparentes.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \param Recibe como parámetro un timer transparente, es decir aquellos timers que no nos interesa el valor de la unidad de tiempo. Ejemplo: TIMER_CONTROL
*/
//-----------------------------------------------------
void SetTimer(uint16_t timer)   //Le pasas el timer transparente
//-----------------------------------------------------
{
  /*
    Esta funcion asocia los acumuladores con los Timer
    transparentes. No depende de la unidad de tiempo!
  */
  switch (timer)
  {
    case TIMER_CONTROL:
         timeControl = 0;
         break;
  }
}
