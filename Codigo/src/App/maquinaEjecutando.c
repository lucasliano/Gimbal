/**
  \file maquinaEjecutando.c
  \brief Se encuentran las rutinas relacionadas con la creacion de la señal PWM. (Hasta ahora esta hecha las maquinas de LEDS)
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "all.h"


/*Variables globales*/
extern EulerAngles euler;

extern uint16_t timePeriodo;
extern float actual;
extern float output;
extern uint16_t kPeriodo;
extern float PWM;

extern char bufferRx1[BUFFER_SIZE];
extern CircularBuffer bufferRx;

#define TRIGGER 2.5

/**
  \fn void F_Ejecutando();
  \brief Es la rutina que hasta el momento implementa cual es la salida del sistema.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return TRUE si se pudo realizar la medición, FALSE si hubo algun fallo.
*/
void F_Ejecutando()
{
	if(GetTimer(TIMER_PERIODO) == 0)      					//Si el tiempo transcurrido es mayor al tiempo del periodo (en unidad de TIMER_PERIODO) ==>
	{
//		actual = euler.roll;
		if(output > TRIGGER || output < -TRIGGER)
			actual += output;

//		kPeriodo = (actual * (0.12/60)) * 1000;				//El servo tiene una velocidad de 0.12s/60grados

		if(actual > 70)
			actual = 70;
		if(actual < -70)
			actual = -70;

		PWM = (float) map(actual, -90, 90, 450, 2350);		//Calculo de mapeo entre -90/90 a 450/2350
		UpdatePWM();

		SetTimer(TIMER_PERIODO, kPeriodo);					//Reseteo el TIMER_PERIODO
	}

}


