/**
  \file DR_SysTick.c
  \brief Se desarrollan las funciones relacionadas al systick a nivel de drivers.
  \author Grupo 8 - R2003
  \date 2019.11.24
  \version 1.2
*/

#include "all.h"


volatile uint32_t systemTicks = 0;			//Mide el tiempo transcurrido en el sistema en ms

/**
	\fn void SysTick_Handler(void)
	\brief Handler asociado a la interrupción del SysTick. Llama a funciones temporizadas.
	\return void
*/
void SysTick_Handler(void)
{
//	uint32_t j = STCTRL;	//Limpio el flag del SysTick
	AnalizarTimers();
	Actualizar_Ticks();
}



/**
	\fn void InicializarSysTick ( void );
	\brief Inicializa el Systick en 100us
	\return void
*/
void InicializarSysTick ( void )			//Suponiendo el clock a 100Mhz	(0,00000001‬s)
{
	STRELOAD = ( STCALIB / 100);			//(999.999/100) = 9.999	==> 9.999*0,00000001‬s = 0,00001s = 100us
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}

/**
	\fn void Actualizar_Ticks(void)
	\brief Incrementa el tiempo. El valor del tiempo se resetea despues de aprox. 50 días (2^32 ms)
	\return void
*/
void Actualizar_Ticks(void)
{
	static uint8_t contador = 1;	//Arranca en 1 para que no incremente en la primer llamada
	if(contador == 0)				//Cuando sume 1ms
	{
		systemTicks++;
		systemTicks %= (uint32_t) pow(2,32);		//Se resetea despues de pasados 2^32 ms.. aproximadamente 50 días.
	}
	contador++;
	contador %= 10;					//Cuenta hasta 10 y resetea
}

/**
	\fn uint32_t GetTicks(void);
	\brief Devuelve el valor del tiempo del sistema.
	\return Devuelve la variable global 'systemTicks' propia al archivo systick.c
*/
uint32_t GetTicks(void)
{
	return systemTicks;
}
