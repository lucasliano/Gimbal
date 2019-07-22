/*Bibliotecas propias*/
#include "headers/aplicacion/maquinaGeneral.h"


/*Variables globales*/

extern uint16_t timeControl;   //Hago extern pq esta en timers.c
uint16_t kTime = 1;    //cte de tiempo. Es 1 pq el TIMER_CONTROL es en DEC(100ms)
uint16_t set_Point;

/*Declaracion de rutinas*/

//-----------------------------------------------------
void Inicializar()
//-----------------------------------------------------
{
  Inicializacion();
  //Inicializar el resto de las cosas, sea display,etc
}

//-----------------------------------------------------
bool Recalibrar_Confirm()
//-----------------------------------------------------
{
  int res = FALSE;
  uint8_t tecla = GetKey();
  if (tecla != N0_KEY)    //Hay que ver si queremos el "NO_KEY", o que sea una tecla especifica
  {
    res = TRUE;
  }
    return res;
}

//-----------------------------------------------------
void Maquina_General()
//-----------------------------------------------------
{
  static int estado = E_CALIBRANDO;
    /*
        set_Point=0;
        ESTE SET POINT CREO QUE EN REALIDAD LO VA A MODIFICAR
        LA MAQUINA DE CALIBRACION ASI QUE NO LO ESTARIA VIENDO YO
    */
  switch (estado)
  {
      case E_CALIBRANDO:
        int aux;
        aux = Maquina_Calibrando(); //ingreso a la submaquina de estado calibrando
        //Transiciones:
        if(aux==TRUE)
        {
          estado = E_FUNCIONANDO;
          SetTimer(TIMER_CONTROL);  //Ponemos en 0 el timer de control. Esto se tendria que hacer
                                    //Adentro de E_FUNCIONANDO
        }

        //Auto-transicion
        //No hace nada porque MAquina_Calibrando se ejecuta al principio.
        break;

      case E_FUNCIONANDO:
        if(Recalibrar_Confirm() == TRUE)
        {
         estado = E_CALIBRANDO;
        }

        //Auto-Transicion
        F_Funcionando();  //Ingreso a la 'Maquina' Funcionando

        break;
    //  default: DESARRROLLARLO!!
  }
}

//-----------------------------------------------------
void F_Funcionando()
//-----------------------------------------------------
{
  /*
    Por el momento, eso no va a ser una máquina.
    Solo vamos a llamar a control. Si por algun motivo necesitamos que se alterne la parte de control
    con otra funcion, entonces modificamos esto para que sea una maquina de estados.

    IMPORTANTE: Si nos damos cuentas de que en este 'Maquina_Funcionando' solo vamos a llamar a funciones,
                entonces copiemos todas las funciones a Maquina_General para que sea mas legible el code
  */
  Maquina_Control();
}

//-----------------------------------------------------
void Maquina_Control()
//-----------------------------------------------------
{
  /*
    Nota: En el diagrama, cuando arranca en E_MIDIENDO se SetTimer(TIMER_CONTROL);
          Esto lo hago desde maquina general en la transicion. Leer ahi el comentario!

    Aka:  timeControl arranca en 0
  */
  static int estado = E_MIDIENDO;
  switch(estado)
  {
      case E_MIDIENDO:
        /*Transicion*/
        if(timeControl >= kTime && Maquina_Medir() == TRUE)
        {
          estado = E_CALCULANDO;
        }

        /*Auto-Transicion*/
        break;

      case E_CALCULANDO:
        /*Transicion*/
        if(F_Calculando() == TRUE)
        {
          SetTimer(TIMER_CONTROL);
          estado = E_MIDIENDO;
        }

        /*Auto-Transicion*/
        break;

      default:
        SetTimer(TIMER_CONTROL);
        estado = E_MIDIENDO;

  }
}
