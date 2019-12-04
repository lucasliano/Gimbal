/**
  \file PWM.c
  \brief Se encuentran las rutinas de control PWM a nivel de drivers.
  \author Grupo 8 - R2003
  \date 2019.10.19
  \version 1.2
*/

#include "all.h"

float PWM;

/**
  \fn void Init_PWM(void);
  \brief Es la rutina a nivel de Drivers que inicializa el periferico PWM.
  \author Grupo 8 - R2003
  \date 2019.08.27
*/
void Init_PWM(void)
{
	PCONP |= 1 << 6; //Habilitar PWM1

	// Elijo el clock completo(como tengo inicializado el PLL --> 100 Mhz)
	PCLKSEL0 &= ~(3 << 12);		//Asegura 00 en la posicion correspondiente a PWM1 de PCLKSEL0
	PCLKSEL0 |= 1 << 12;		//Pone 01 en la posicion correspondiente a PWM1 de PCLKSEL0

	PWM_PCR = 0x00;		// Selecciono Single Edge PWM, que seria que empezar en alto la señal de PWM.

	PWM_PR = 100-1;		// para definir este valor hacemos (PCLK * PWM_Resolucion)-1 --> (100Mhz * 1uS)-1 = 100-1

	PWM_MR0 = 2500;	// 10000uS = 10mS

	PWM_MR1 = 1700;		// 1700uS = 1,7mS DUTTY

	PWM_MCR = 1 << 1;	// Restablecer PWM

	PWM_LER = (1<<1) | (1<<0);	// Actualizar valores de MR0 y MR1

	PWM_PCR = (1<<9);	// Habilitar salida PWM

	PWM_TCR = (1<<1);	// Reset PWM TC & PR

	PWM_TCR = (1<<0) | (1<<3);	// Habilitar contador y modo PWM

	Init_GPIO_PWM();
}

/**
  \fn void ActualizarValorPWM();
  \brief Es la rutina a nivel de Drivers que actualiza la PWM.
  \author Grupo 8 - R2003
  \date 2019.08.27
*/
void ActualizarValorPWM()
{
	PWM_MR1 = (uint32_t) PWM;
	PWM_MCR = 1 << 1;
	PWM_LER = (1<<1);
}
