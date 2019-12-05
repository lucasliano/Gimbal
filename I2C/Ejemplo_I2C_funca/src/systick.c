//Este no hace falta que aclaremos si lo compilamos como c o como c++
#include "systick.h"

void InicializarSysTick ( void )
{
	STRELOAD = ( STCALIB / 10) - 1;			//Ponemos que el systick sea cada 1ms
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}

void SysTick_Handler(void)
{
	AnalizarTimers();
}



