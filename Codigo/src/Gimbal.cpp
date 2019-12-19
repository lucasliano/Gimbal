/**
  \file main.c
  \brief Se encuentra la rutina principal del programa.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/


#include "all.h"

//*****************************************************
int main()
//*****************************************************
{
    Inicializar_HW();

    IniciarIMU();


    while(1)
    {
    	TimerEvent();			//Llamo a los handler de los timers expirados!
		Maquina_General();		//Maquina mas importante.
		Maquina_TransDatos();  	//Se encarga de la comunicacion Serie.
		F_Ejecutando();        	//Ejecutando va en paralelo.
    }

    return 0;
}




