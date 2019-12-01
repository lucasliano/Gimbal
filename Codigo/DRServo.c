#incldue "Aplicacion.h"
extern uint8_t flagServoON;
extern uint8_t flagServoOFF;

void SystickHandler(void)
{
   flagServoON=0;
   flagServoOFF=0;
   if(flagServo<DUTY)
   {
      flagServoON++;
   }
   if(flagServoON>=DUTY)
   {
      flagServoOFF++;
      flagServoON=0;
   }
   if(flagServoOFF<ELOTROTIEMPO)
   {
      flagServoOFF++;
   }
   if(flagServoOFF>=ELOTROTIEMPO)
   {
      flagServoOFF=0;
      flagServoON++;
   }
}
