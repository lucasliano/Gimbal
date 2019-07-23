/**
  \file main.c
  \brief Se encuentra la rutina principal del programa.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.1
*/




#include  "headers/main.h"

extern uint16_t set_Point;

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

    while(1)
    {
       TimerEvent();
       Maquina_General();
       Maquina_TransDatos();
       F_Ejecutando();        //Ejecutando va en paralelo
    }

    return 0;
}
