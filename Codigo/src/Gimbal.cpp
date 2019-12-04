/**
  \file main.c
  \brief Se encuentra la rutina principal del programa.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/


#include "all.h"

extern float setPoint;
extern float actual;


extern uint16_t timeControl;  //Ver si es necesario.. creo que no.. Hay que probar


//*****************************************************
int main()
//*****************************************************
{
    Inicializar();

    //Apaga el buzzer	NOTA: El led RGB no se puede apagar porque esta conectado a la salida PWM que usamos :(
    SetPINSEL(0,28,0);
    SetDIR(0,28,0);
    SetPIN(0,28,0);
    //-----------------


    Init_Timers();				//Inicia los timers

    while(1)
    {
       TimerEvent();			//Se encarga de hacer funcionar la maquinaria de Timers.
       Maquina_General();		//Maquina mas importante.
       Maquina_TransDatos();  	//Se encarga de la comunicacion Serie.
       F_Ejecutando();        	//Ejecutando va en paralelo.
    }

    return 0;
}
