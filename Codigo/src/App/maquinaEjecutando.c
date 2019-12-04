/**
  \file maquinaEjecutando.c
  \brief Se encuentran las rutinas relacionadas con la creacion de la señal PWM. (Hasta ahora esta hecha las maquinas de LEDS)
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "all.h"


/*Variables globales*/
extern uint16_t timePeriodo;
extern float actual;
extern float output;
extern uint16_t periodo;
extern uint16_t timeLCD;
extern float PWM;

extern char bufferRx1[BUFFER_SIZE];
extern CircularBuffer bufferRx;

/**
  \fn void F_Ejecutando();
  \brief Es la rutina que hasta el momento implementa cual es la salida del sistema.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return TRUE si se pudo realizar la medición, FALSE si hubo algun fallo.
*/
void F_Ejecutando()
{
  if(timePeriodo >= periodo)      //Si el tiempo transcurrido es mayor al tiempo del periodo (en unidad de TIMER_PERIODO) ==>
  {
    actual += output;

    PWM = (float) map(actual, -90, 90, 450, 2350);		//Calculo de mapeo entre -90/90 a 450/2350
    UpdatePWM();

    ReiniciarTimer(TIMER_PERIODO);
  }

  ActualizarDisplay();
}


/**
  \fn void ActualizarDisplay();
  \brief Es la rutina de aplicación que se encarga de actualizar el valor que muestra el display
  \author Grupo 8 - R2003
  \date 2019.09.11
*/
void ActualizarDisplay()
{
	if(timeLCD >= 1)				//Esto es cada cuanto actualizo el LCD (En unidades de TIMER_LCD)
	  {

		  char str[6];

		  LCD_Display("POS:", DSP0, 0);
		  LCD_Display("PWM:", DSP1, 0);

		  tostring(str,(int)actual);		//Esto me imprime la posición
		  LCD_Display(str, DSP0, 4);


		  tostring(str,(int)PWM);			//Esto imprime la corrección de posicion
		  LCD_Display(str, DSP1, 4);



/**
		LCD_Display((char*) bufferRx1, DSP1,0);

		LCD_Display("MENSAJE:",DSP0,0);
**/
		ReiniciarTimer(TIMER_LCD);
	  }
}




/**
  \fn void tostring();
  \brief Es la rutina que convierte int a char*. Funciona estaticamente con numeros de hasta 5 digitos.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return 0 en todos los casos.
*/
int tostring(char* str, int num)
{
    int i, rem, len = 0, n, flag=0;

    if(num == 0)
	{
    	str[0] = ' ';
    	str[1] = '0';
    	for ( i = 2; i < 7; i++){

    		str[i] = ' ';
    	}

		str[7] = '\0';
		return 0;
	}


    if(num < 0)
    {
    	flag = 1;
    	num = num*(-1);
    }

    n = num;

    while (n != 0)
    {
        len++;
        n /= 10;
    }

    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[(len) - (i)] = rem + '0';
    }

    if(len < 5)
    {
    	for(i=len; i < 6;i++)
    	{
    		str[i+1]=' ';
    	}
    }

    str[6]='\0';

    if(flag == 1)
    {
    	str[0] = '-';
    }else{
    	 str[0]= ' ';
    }
    return 0;
}
