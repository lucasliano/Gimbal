/**
  \file DR_Servo.c
  \brief Se encuentran las rutinas asociada al funcionmamiento de los servomotores por GPIO.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/
#include "all.h"



uint8_t flagServo[2] = {0,0};
uint16_t proximoDuty[2] = {1500,1500};
uint16_t  duty[2] = {1500,1500};


void ActualizarServosGPIO(void)
{
   for( int i = 0; i < 2; i++)
   {
		if(flagServo[i] == 0)
		{
			SetPIN(1, i + 23, ON);			//Servo 1: P1.23 (expansion 3)		y Servo 2: P1.24 (expansion 13)
		}

		if(flagServo[i] >= duty[i])
		{
			SetPIN(1, i + 23, OFF);
		}

		flagServo[i]++;

		if(flagServo[i] >= 20 * MILISEGUNDOS)
		{
			flagServo[i] = 0;
			duty[i] = proximoDuty[i];
		}
   }
}


void ModificarServo( uint8_t servo, uint16_t dato)
{
	proximoDuty[servo] = dato / 100;		//1500 us = 15 decimas de ms

}


void InicializarServos(void)
{
	for(int i = 0; i < 2; i++)
	{
		SetPINSEL( 1 , 23 + i , 00 );
		SetPINMODE( 1 , 23 + i , 2);
		SetDIR( 1 , 23 + i , 1 );
		SetPIN(1, 23 + i, OFF);
	}
}
