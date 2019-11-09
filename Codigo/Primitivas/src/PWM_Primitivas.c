#include "PWM_Primitivas.h"


/**
  \fn void Init_GPIO_PWM(void)
  \brief Es la rutina a nivel de Primitiva que inicializa el pin que se va usar para PWM.
  \author Grupo 8 - R2003
  \date 2019.08.27
*/
void Init_GPIO_PWM(void)
{
	SetPINSEL(PIN_PWM1_1_P1); //Configuro en el puerto 1, pin 18 como funcion de PWM

}

/**
  \fn void UpdatePWM(void);
  \brief Es la rutina a nivel de Primitiva que actualiza el valor PWM.
  \author Grupo 8 - R2003
  \date 2019.08.27
*/
void UpdatePWM(void){
	ActualizarValorPWM();
}

