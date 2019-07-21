#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include  "bibliotecaInfoII.h"
#include  "maquina_General.h"

uint16_t set_Point;
int aux;
uint16_t control_Time=1000; //ESTE ES EL K TIME(MODIFICALO VOS LUCAS)
uint16_t ext_Tcontrol;

void Inicializar()
{
  Inicializacion();
  //Inicializar el resto de las cosas, sea display,etc
}
bool Recalibar_Confirm() //PORQUE ES UN BOTON EN LOGICA NAHUEL
{
  int res = FALSE;
  uint8_t tecla = GetKey();
  if (tecla!=N0_KEY)
  {
    res = TRUE;
  }
    return res;
}
/*Funciones asociadas a los timers*/
void Init_Timers()
{
  TimerStart(TIMER_CONTROL,1,ActualizarExt_TControl,DEC);
}
void SetTimer(uint16_t timer)
{
  switch (timer)
  {
    case TIMER_CONTROL:
         ext_Tcontrol=0;
         break;
  }
}
void ActualizarExt_TControl()
{
  ext_Tcontrol= ext_Tcontrol+100;
  TimerStart(TIMER_CONTROL,1,ActualizarExt_TControl,DEC);
}

void Maquina_General()
{
  static int estado = CALIBRANDO;
/*  set_Point=0; ESTE SET POINT CREO QUE EN REALIDAD LO VA A
MODIFICAR LA MAQUINA DE CALIBRACION ASI QUE NO LO ESTARIA VIENDO YO*/
  switch (estado)
  {
      case CALIBRANDO:
           aux = Maquina_Calibrando();
           //ingreso a la submaquina de estado calibrando
           if(aux==TRUE)
           {
             estado = E_FUNCIONANDO;
           }
           //Autoretencion
           else
           {
             //ingreso a la sub_maquina funcionando
             Maquina_Funcionando();
             estado= E_CALIBRANDO;
           }
           break;
      case FUNCIONANDO:
           if(Recalibar_Confirm()!=TRUE)
           {
             estado = E_FUNCIONANDO;
           }
           else
           {
             estado=E_CALIBRANDO;
           }
           break;
    //  default: DESARRROLLARLO!!
  }
}

void Maquina_Funcionando()
{
  static int estado = E_CONTROLANDO;
  switch(estado)
  {
      case E_CONTROLANDO:
           Maquina_Control();
           if(ext_Tcontrol<control_Time)
           {
             estado = E_CONTROLANDO;
           }
           else
           {
             SetTimer(TIMER_CONTROL);//pongo en 0 la ext tcontrol
             estado = E_EJECUTANDO;
//aclaracion, no llamo a m_ejecutando porque no es una maquina, es una funcion
           }
           break;
      case E_EJECUTANDO:
           if(F_Ejecutando()!=TRUE)
           {
             estado = E_EJECUTANDO;
           }
           else
           {
              estado = E_CONTROLANDO;
           }
           break;
      //default: DESARROLLARLO !!!
  }
}

void Maquina_Control()
{
  static int estado = E_MIDIENDO;
  switch(estado)
  {
     case E_MIDIENDO:
          
  }
}
