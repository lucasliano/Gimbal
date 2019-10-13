/*
 * Inic.c
 *
 *  Created on: 21 ago. 2019
 *      Author: NicoCampos
 */


#include "main.h"
#include "PWM.h"

void inicializar(void)
{
	InicPLL();	// Para que el CCLK = 100Mhz
	Init_Timers();

	Init_GPIO_PWM();
	Init_PWM();
}

void Init_GPIO_PWM(void)
{
	SetPINSEL(PIN_PWM1_1_P1); //Configuro en el puerto 1, pin 18 como funcion de PWM

}

void Init_PWM(void)
{
	PCONP |= 1 << 6; //Habilitar PWM1

	// Elijo el clock completo(como tengo inicializado el PLL --> 100 Mhz)
	PCLKSEL0 &= ~(3 << 12);
	PCLKSEL0 |= 1 << 12;

	PWM_PCR = 0x00;		// Selecciono Single Edge PWM, que seria que empezar en alto la señal de PWM.

	PWM_PR = 100-1;		// para definir este valor hacemos (PCLK * PWM_Resolucion)-1 --> (100Mhz * 1uS)-1 = 100-1

	PWM_MR0 = 2500;	// 10000uS = 10mS

	PWM_MR1 = 1700;		// 1700uS = 1,7mS DUTTY

	PWM_MCR = 1 << 1;	// Restablecer PWM

	PWM_LER = (1<<1) | (1<<0);	// Actualizar valores de MR0 y MR1

	PWM_PCR = (1<<9);	// Habilitar salida PWM

	PWM_TCR = (1<<1);	// Reset PWM TC & PR

	PWM_TCR = (1<<0) | (1<<3);	// Habilitar contador y modo PWM
}
