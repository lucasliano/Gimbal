/**
  \file CONFIG.c
  \brief Se encuentran las rutinas configuración de pines a nivel de drivers.
  \author Grupo 8 - R2003
  \date 2019.10.19
  \version 1.2
*/
#include "all.h"



/********************************************************************************
	\fn  long map(long x, long in_min, long in_max, long out_min, long out_max);
	\brief Mapea linealmente valores.
 	\param long x: Valor a evaluar (IN)
 	\param long in_min:	Valor minimo de entrada
 	\param long in_max:	Valor máximo de entrada
 	\param long out_min:	Valor minimo de salida
 	\param long out_max:	Valor máximo de salida
	\return long: Retorna el valor del mapping
*/
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



/********************************************************************************
	\fn  void SetPINSEL (uint8_t puerto , uint8_t pin, uint8_t sel);
	\brief Selección de modo de los puertos (4 modos).
 	\param [in] puerto: port a configurar
 	\param [in] pin:	pin del port a configurar
 	\param [in] funcion:	selección de la funcion que tendra el pin  [0 - 3]
	\return void
*/
void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion )
{
	puerto = puerto * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ puerto ] = PINSEL[ puerto ] & ( ~ ( 3 << pin ) );
	PINSEL[ puerto ] = PINSEL[ puerto ] | ( funcion << pin );
}

/********************************************************************************
	\fn  void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
	\brief Selección de modo de los puertos cuando trabajan como entradas
	\author & date: Informatica II
 	\param [in] puerto: port a configurar
 	\param [in] pin:	pin del port a configurar
 	\param [in] funcion:	selección de la funcion que tendra el pin  [0 - 3]
	\return void
*/
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}

/********************************************************************************
	\fn  void SetPINMODE_OD( uint8_t puerto , uint8_t pin ,uint8_t modo)
	\brief Selección de modo de los puertos cuando trabajan como salidas
	\author & date: Lucas Liaño
 	\param [in] puerto: port a configurar
 	\param [in] pin:	pin del port a configurar
 	\param [in] funcion:	selección de la funcion que tendra el pin  [0 - 1]
	\return void
*/
void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion)
{
	PINMODE_OD[puerto] &= ~(1 << pin);	 		//Aseguo un 0
	PINMODE_OD[puerto] |= (funcion << pin);		//Le asigno el valor al puerto
}

/**
  \fn void MyInitPLL(void);
  \brief Rutina suministrada por ayudante de la materia. La misma inicializa el PLL (CLK = 100Mhz).
  \author Grupo 8 - R2003
  \date 2019.11.6
*/
//-----------------------------------------------------
void MyInitPLL(void)
{
	SCS       = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
		while ((SCS & (1<<6)) == 0);		/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      		/* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     		/* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    		/* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      		/* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             			/* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));			/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             			/* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             			/* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));			/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             			/* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        		/* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    		/* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}
