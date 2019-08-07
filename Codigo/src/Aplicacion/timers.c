/**
  \file timers.c
  \brief Se encuentran las rutinas relacionadas con los timers.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "timers.h"


/*Acumuladores*/
/**
  \var uint16_t timeControl
  \brief Es el acumulador relacionado al TIMER_CONTROL.
  \details none.
*/
uint16_t timeControl = 0;
/**
  \var uint16_t timeBoton
  \brief Es el acumulador relacionado al TIMER_BOTON.
  \details none.
*/
uint16_t timeBoton = 0;
/**
  \var uint16_t timePeriodo
  \brief Es el acumulador relacionado al TIMER_PERIODO.
  \details none.
*/
uint16_t timePeriodo = 0;
/**
  \var uint16_t timeLCD
  \brief Es el acumulador relacionado al TIMER_LCD.
  \details none.
*/
uint16_t timeLCD = 0;

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
  timeControl += 1;
  timePeriodo += 1;
  timeLCD += 1;

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
  timeBoton += 1;
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
void ReiniciarTimer(uint16_t timer)   //Le pasas el timer transparente
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
    case TIMER_BOTON:
         timeBoton = 0;
         break;
    case TIMER_PERIODO:
        timePeriodo = 0;
        break;
    case TIMER_LCD:
    	timeLCD = 0;
		break;
  }
}
