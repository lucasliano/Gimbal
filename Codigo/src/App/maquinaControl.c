/**
  \file maquinaControl.c
  \brief Se encuentran las rutinas relacionadas con el sistema de control.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "all.h"



/*Variables globales*/

/**
  \var float actual
  \brief Almacena el valor de la posición actual del gimbal (solo para leds).
  \details none.
*/
float actual = 0;

/**
  \var float set_Point
  \brief Almacena el valor de setpoint deseado.
  \details none.
*/
float setPoint = 0;

/**
  \var float output
  \brief Almacena el valor de salida del sistema.
  \details none.
*/
float output;

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
uint16_t periodo = 1;

/**
  \var float kTime
  \brief Almacena una constante de control.
  \details Esta constante permite variar cada cuanto quiero que se ejecute la rutina de control.
*/
float kTime = 2;
/*
 * Curva Normal: Ktime < = 5*periodo
 * Oscilacion Decreciente: 5*perido < kTime < 10*periodo
 * Oscilacion armonica: kTime = 10*periodo
 * Oscilacion creciente: kTime >10*periodo
*/

/**
  \var float kp
  \brief Almacena una constante de control.
  \details Esta constante permite la componente proporcional del sistema de control. Varia que tan brusca es la respuesta inmediata.
*/
float kp = 1;

/**
  \var float kd
  \brief Almacena una constante de control.
  \details Esta constante permite variar que tanta importancia se le da a la componente de control derivativa.
*/
float kd = 0;

/**
  \var float ki
  \brief Almacena una constante de control.
  \details Esta constante permite variar que tanta importancia se le da a la componente de control integral.
*/
float ki = 0;

uint16_t limite = 5;    //limite en segundos para el boton para SIMULACION
int escala = 18;       //Escala de la perturbacion solo para SIMULACION
float kreac = 5;		//SOLO PARA LA SIMULACION

extern uint16_t timeBoton;  //Acumulador del boton
extern uint8_t tecla; //Valor de la tecla apretada
extern uint16_t timeControl;   //Hago extern pq esta en timers.c

/*Declaracion de rutinas*/

/**
  \fn int Maquina_Medir();
  \brief Es la máquina de estados encargada de realizar la medición del giróscopo. Hasta ahora solo implementada para la prueba con LEDS.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return TRUE si se pudo realizar la medición, FALSE si hubo algun fallo.
*/
int Maquina_Medir()
{
	//Hay que modificar acá




//  static int estado = E_PAUSA;
//  switch (estado)
//  {
//    case E_PAUSA:
//
//      if(tecla == SW7)
//      {
//        estado = E_PRESIONANDO;
//        ReiniciarTimer(TIMER_BOTON);
//      }
//      return FALSE;
//      break;
//
//    case E_PRESIONANDO:
//
//      if(tecla == SW7 || tecla == SW4 || timeBoton >= limite)
//      {
//    	float perturbacion = timeBoton * escala;
//    	if(tecla == SW4)
//    	{
//    		perturbacion = perturbacion * -1;
//    	}
//    	if(actual + perturbacion < 90 && actual + perturbacion > -90)
//    	{
//    		actual += perturbacion;
//    	}else{
//    		if(actual + perturbacion >= 90)
//    		{
//    			actual = 90;
//    		}else{
//    			actual = -90;
//    		}
//    	}
//
//        estado = E_PAUSA;
//        return TRUE;      //Solo devueve TRUE cuando se haya soltado el boton
//      }
//      return FALSE;
//      break;
//
//    default:
//      estado = E_PAUSA;
//      return FALSE;
//  }
	return TRUE;
}

/**
  \fn int F_Calculando();
  \brief Se encarga de realizar los caluclos pertinentes al sistema de control.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return FALSE mientras se este calculando. TRUE cuando se haya terminado de calcular.
*/
int F_Calculando()
{
  static int res = FALSE;  //Si se lo implementa como máquina de estados es necesario que esto se modifique.
  float dif;


  dif = setPoint - actual;
  output = kp * (dif/(kreac));	//kreac se opone al control


  res = TRUE;
  /* Siempre devuelve TRUE hasta ahora. */
  return res;
}


/**
  \fn void Maquina_Control();
  \brief Es la máquina de estados que regula el correcto funcionamiento del sistema de control. Se ejecuta dentro de la máquina General.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Maquina_Control()
//-----------------------------------------------------
{
  /*
    Nota: En el diagrama, cuando arranca en E_MIDIENDO se ReiniciarTimer(TIMER_CONTROL);
          Esto lo hago desde maquina general en la transicion. Leer ahi el comentario!

    Aka:  timeControl arranca en 0
  */
  static int estado = E_MIDIENDO;
  switch(estado)
  {
      case E_MIDIENDO:
        /*Transicion*/
        if(timeControl >= kTime || Maquina_Medir() == TRUE)
        {
          estado = E_CALCULANDO;
        }

        /*Auto-Transicion*/
        break;

      case E_CALCULANDO:
        /*Transicion*/
        if(F_Calculando() == TRUE)
        {
          ReiniciarTimer(TIMER_CONTROL);
          estado = E_MIDIENDO;
        }

        /*Auto-Transicion*/
        break;

      default:
        ReiniciarTimer(TIMER_CONTROL);
        estado = E_MIDIENDO;

  }
}
