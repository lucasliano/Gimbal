/**
  \file maquinaControl.c
  \brief Se encuentran las rutinas relacionadas con el sistema de control.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "headers/aplicacion/maquinaControl.h"


/*Variables globales*/

/**
  \var uint16_t actual
  \brief Almacena el valor de la posición actual del gimbal (solo para leds).
  \details none.
*/
uint16_t actual;

/**
  \var uint16_t set_Point
  \brief Almacena el valor de setpoint deseado.
  \details none.
*/
uint16_t setPoint;

/**
  \var uint16_t output
  \brief Almacena el valor de salida del sistema.
  \details none.
*/
uint16_t output;

/**
  \var uint16_t duty
  \brief Almacena el valor correspondiente al ciclo de trabajo del motor.
  \details none.
*/
uint16_t duty;

/**
  \var uint16_t periodo
  \brief Almacena cual es el periodo maximo del PWM del motor.
  \details none.
*/
uint16_t periodo = 2;  //La unidad de tiempo depende del TIMER_PERIODO

/**
  \var uint16_t kTime
  \brief Almacena una constante de control.
  \details Esta constante permite variar cada cuanto quiero que se ejecute la rutina de control.
*/
uint16_t kTime = 1;

/**
  \var uint16_t kp
  \brief Almacena una constante de control.
  \details Esta constante permite la componente proporcional del sistema de control. Varia que tan brusca es la respuesta inmediata.
*/
uint16_t kp = 1;

/**
  \var uint16_t kd
  \brief Almacena una constante de control.
  \details Esta constante permite variar que tanta importancia se le da a la componente de control derivativa.
*/
uint16_t kd = 0;

/**
  \var uint16_t ki
  \brief Almacena una constante de control.
  \details Esta constante permite variar que tanta importancia se le da a la componente de control integral.
*/
uint16_t ki = 0;

uint16_t limite = 3;    //limite en segundos para el boton para LEDS
int escala = 100;       //Escala de la perturbacion solo para LEDS

extern uint16_t timeBoton;  //Acumulador del boton


/*Declaracion de rutinas*/

/**
  \fn bool Maquina_Medir();
  \brief Es la máquina de estados encargada de realizar la medición del giróscopo. Hasta ahora solo implementada para la prueba con LEDS.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return TRUE si se pudo realizar la medición, FALSE si hubo algun fallo.
*/
int Maquina_Medir()
{
  static int estado = E_PAUSA;
  switch (estado)
  {
    case E_PAUSA:

      if(hayBoton() == TRUE)
      {
        estado = E_PRESIONANDO;
        SetTimer(TIMER_BOTON);
      }
      return FALSE;
      break;

    case E_PRESIONANDO:

      if(hayBoton() == FALSE || timeBoton >= limite)
      {
        actual += timeBoton * escala;
        estado = E_PAUSA;
        return TRUE;      //Solo devueve TRUE cuando se haya soltado el boton
      }
      return FALSE;
      break;

    default:
      estado = E_PAUSA;
      return FALSE;
  }
}

/**
  \fn bool F_Calculando();
  \brief Se encarga de realizar los caluclos pertinentes al sistema de control.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return FALSE mientras se este calculando. TRUE cuando se haya terminado de calcular.
*/
int F_Calculando()
{
  static int res;  //Si se lo implementa como máquina de estados es necesario que esto se modifique.
  res = FALSE;

  uint16_t dif;
  dif = actual - setPoint;
  output = kp * (dif/(periodo))
  res = TRUE;

  /* Siempre devuelve TRUE hasta ahora. */
  return res;
}


/**
  \fn bool hayBoton();
  \brief Se fija si algun boton fue presionado.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return FALSE si no hay ninguno presionado, y TRUE si alguno se presiono o esta siendo presionado.
*/
int hayBoton()     //Es la misma funcion que Recalibrar_Confirm() hasta ahora!
{
  int res = FALSE;
  uint8_t tecla = GetKey();
  if (tecla != N0_KEY)    //Hay que ver si queremos el "NO_KEY", o que sea una tecla especifica
  {
    res = TRUE;
  }
  return res;
}
