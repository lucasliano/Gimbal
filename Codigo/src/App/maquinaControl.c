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
  \brief Almacena el valor de la posición actual del gimbal.
  \details none.
*/
float actual = 0;

/**
  \var float setPoint
  \brief Almacena el valor de setpoint deseado.
  \details none.
*/
float setPoint = 0;

/**
  \var float output
  \brief Almacena el valor de salida del sistema.
  \details none.
*/
float output = 0;


/**
  \var uint16_t periodo
  \brief Almacena cual es el periodo maximo del PWM del motor.
  \details none.
*/
uint16_t kPeriodo = 1 * DECIMAS;

/**
  \var float kTime
  \brief Almacena una constante de control.
  \details Esta constante permite variar cada cuanto quiero que se ejecute la rutina de control.
*/
float kTime = 10;
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
//float kreac = 5;		//SOLO PARA LA SIMULACION

extern uint16_t timeBoton;  	//Acumulador del boton
extern uint16_t timeControl;   	//Hago extern pq esta en timers.c
extern EulerAngles euler;		//Angulos de Euler
extern EulerAngles eulerOffset;
/*Declaracion de rutinas*/


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
        if(Maquina_Medir() == TRUE)				//Siempre va a poder medir, porque solo actualiza los valores de las variables globales con filtros!
        {
          estado = E_CALCULANDO;
        }

        /*Auto-Transicion*/
        break;

      case E_CALCULANDO:
        /*Transicion*/
    	if( GetTimer(TIMER_CONTROL) == 0)		//Si ya expiro el TIMER_CONTROL
    	{
    		if(F_Calculando() == TRUE)			//F_Calculando no tiene porque ser bloqueante (aunque lo va a ser, salvo que lo optimice dsps)
			{
			  SetTimer(TIMER_CONTROL, kTime);	//Reseteo el timer de control
			}
    	}
    	//Siempre volvemos a intentar medir
    	estado = E_MIDIENDO;

        /*Auto-Transicion*/
        break;

      default:
    	SetTimer(TIMER_CONTROL, kTime);	//Reseteo el timer de control
        estado = E_MIDIENDO;

  }
}



/**
  \fn int Maquina_Medir();
  \brief Es la máquina de estados encargada de realizar la medición del giróscopo. Hasta ahora solo implementada para la prueba con LEDS.
  \author Grupo 8 - R2003
  \date 2019.07.23 jkfdkf
  \return TRUE si se pudo realizar la medición, FALSE si hubo algun fallo.
*/
int Maquina_Medir()
{
	//Acá es donde se tienen que hacer los filtros epicos que necesitan capacidad de computo

	ActualizarAngulos();	//Actualizo los angulos de Euler.. Se fueron midiendo desde el systick

 	euler.pitch -= eulerOffset.pitch;
	euler.roll -= eulerOffset.roll;


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
	int salidaDeFuncion = FALSE;  	//Si se lo implementa como máquina de estados es necesario que esto se modifique.

	Controlador_PID();

	salidaDeFuncion = TRUE;
	/* Siempre devuelve TRUE hasta ahora. */
	return salidaDeFuncion;
}




void Controlador_PID( void )
{
	static float Integral = 0;		//Guarda el valor integral del sistema
	static float errorAnterior = 0;	//Guarda el valor anterior del error
	float error;
	float Proporcional = 0;
	float Derivativo = 0;
	float deltaError = 0;

	error = setPoint - euler.roll;						//Calculo de error
	deltaError = (error - errorAnterior);				//Calculo de la pendiente del D

	Proporcional = error * kp;							//P
	Integral = Integral + (error * ki * kTime);			//I		-		Integra en el periodo
	Derivativo = ( deltaError * kd ) / kTime;			//D		-		Deriva en el periodo

	errorAnterior = error;								//Actualizo el valor anterior, para calcular la prox pendiente
	if (error > ANTIWINDUP_THRESHOLD) Integral = 0;		//I		-		Anti-WindUp

	output = (Proporcional + Integral + Derivativo) ;		//Calculo la salida del Control H()


}
