
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

/**
  \file main.c
  \brief Se encuentra la rutina principal del programa.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/


#include  "main.h"

extern float setPoint;
extern float actual;

/**
  \var int aux
  \brief Variable multiuso.
  \details Se utiliza en la función Maquina_General()
*/
extern int aux;

//*****************************************************
int main()
//*****************************************************
{
    Inicializar();
    Init_Timers();
    LedsRGB(1,0);
    LedsRGB(2,0);
    LedsRGB(0,0);

    while(1)
    {
       TimerEvent();
       Maquina_General();
       Maquina_TransDatos();
       F_Ejecutando();        //Ejecutando va en paralelo
    }

    return 0;
}

void Maquina_TransDatos()
{

}

