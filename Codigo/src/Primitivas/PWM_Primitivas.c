#include "all.h"

extern uint8_t proximoDuty[2];


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

/**
 * ActualizarServo
 * @param  tiempo [en microsegundos]
 * @param  nservo [el numero de servo (1 o 2)]
 * @return        [-1 error,0 ok]
 */
int8_t ActualizarServo(uint8_t nServo,uint8_t tiempo)
{
		if(tiempo<1000 || tiempo>2000)
		{
			//eror
			return -1;
		}
		else{
			proximoDuty[nServo] = tiempo;
			return 0;
		}

}
