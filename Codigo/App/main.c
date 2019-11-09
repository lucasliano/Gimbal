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


extern uint16_t timeControl;  //Ver si es necesario.. creo que no.. Hay que probar


//*****************************************************
int main()
//*****************************************************
{
    Inicializar();

    //Apaga el buzzer
    SetPINSEL(0,28,0);
    SetDIR(0,28,0);
    SetPIN(0,28,0);
    //-----------------


    Init_Timers();

    while(1)
    {
       TimerEvent();			//Se encarga de hacer funcionar la maquinaria de Timers.
       Maquina_General();		//Maquina mas importante.
       Maquina_TransDatos();  	//Se encarga de la comunicacion Serie.
       F_Ejecutando();        	//Ejecutando va en paralelo.
    }

    return 0;
}






