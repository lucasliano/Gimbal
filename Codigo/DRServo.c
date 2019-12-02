#include "Aplicacion.h"
uint8_t flagServo;
uint8_t proximoDuty[2];

void SystickHandler(void)
{
   uint8_t static dutyI=1500;
   uint8_t static dutyII=1500;
   flagServoI=0;
   flagServoII=0;

   if(flagServoI==0)
   {
     setPin(macro1,ON);
   }

   if(flagServoI>=dutyI)
   {
      setPin(macro1,OFF);
   }

   if(flagServoI>=20MS)
   {
      flagServoI=0;
      dutyI = proximoDuty[0];
   }
   
//SERVOII
if(flagServoII==0)
{
  setPin(macro2,ON);
}
/*if(flagServo<DUTY)
{
   flagServo++;
}*/
if(flagServoII>=dutyII)
{
   setPin(macro2,OFF);
}
/* if(flagServo<20MS)
{
   flagServo++;
}*/
if(flagServoII>=20MS)
{
   flagServoII=0;
   dutyII = proximoDuty[1];
}

   flagServoI++;
   flagServoII++;
}
//Asumo que duty es menor que el tiempo de 20ms

/*Para la segunda parte que me pedis que consulte por
el estado en el que se encuentra el duty, yo haria
una maquina de estados pero no se si ahi adentro del
systick es posible de hacer*/

/*Duty 1000<t<2000 us */
