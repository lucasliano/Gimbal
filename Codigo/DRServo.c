#incldue "Aplicacion.h"
extern uint8_t flagServo;

void SystickHandler(void)
{
   flagServo=0;
   if(flagServo==0)
   {
     setPin(macro,ON);
   }
   /*if(flagServo<DUTY)
   {
      flagServo++;
   }*/
   if(flagServoON>=DUTY)
   {
      setPin(macro,OFF);
   }
  /* if(flagServo<20MS)
   {
      flagServo++;
   }*/
   if(flagServoOFF>=20MS)
   {
      flagServo=0;
      DUTY = PROXIMODUTY;
   }
   flagServo++;
}
//Asumo que duty es menor que el tiempo de 20ms

/*Para la segunda parte que me pedis que consulte por
el estado en el que se encuentra el duty, yo haria
una maquina de estados pero no se si ahi adentro del
systick es posible de hacer*/

/*Duty 1000<t<2000 us */
