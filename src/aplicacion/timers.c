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
uint16_t timeControl = 0;


/*Funciones asociadas a los timers*/

//-----------------------------------------------------
void Init_Timers()
//-----------------------------------------------------
{
  TimerStart(TIMER_DEC,1,ActualizarDec,DEC);
  TimerStart(TIMER_SEG,1,ActualizarSeg,SEG);
  TimerStart(TIMER_MIN,1,ActualizarMin,MIN);
}

//-----------------------------------------------------
void ActualizarDec()
//-----------------------------------------------------
{
  //Acá se actualizan todos los acumuladores
  timeControl = timeControl + 100;


  //Se vuelve a activar el timer
  TimerStart(TIMER_DEC,1,ActualizarDec,DEC);
}

//-----------------------------------------------------
void ActualizarSeg()
//-----------------------------------------------------
{
  //Acá se actualizan todos los acumuladores



  //Se vuelve a activar el timer
  TimerStart(TIMER_SEG,1,ActualizarSeg,SEG);
}

//-----------------------------------------------------
void ActualizarMin()
//-----------------------------------------------------
{
  //Acá se actualizan todos los acumuladores



  //Se vuelve a activar el timer
  TimerStart(TIMER_MIN,1,ActualizarMin,MIN);
}

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
