/*
 * GPIO.c
 *
 *  Created on: 25 de ago. de 2017
 *      Author: saitama
 */

#include "main.h"



/*
void SetDIR( uint8_t puerto , uint8_t pin , uint8_t dir )
{
	puerto = puerto * 8;

	GPIOs[ puerto ] = GPIOs[ puerto ] & ( ~ ( 1 << pin ) );
	GPIOs[ puerto ] = GPIOs[ puerto ] | ( dir << pin );
}



void SetPIN( uint8_t puerto , uint8_t pin , uint8_t estado )
{
	puerto = puerto * 8 + 5;

	GPIOs[ puerto ] = GPIOs[ puerto ] & ( ~ ( 1 << pin ) );
	GPIOs[ puerto ] = GPIOs[ puerto ] | ( estado << pin );
}


uint8_t GetPIN( uint8_t puerto , uint8_t pin , uint8_t actividad )
{
	puerto = puerto * 8 + 5;

	return ( ( ( GPIOs[ puerto ] >> pin ) & 1 ) == actividad ) ? 1 : 0;

}
*/
