#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "bibliotecaInfoII.h"
#include "Gimbal.h"

extern uint16_t set_Point;
extern int aux;

int main()
{
    Inicializar();
    Init_Timers();

    while(1)
    {
       TimerEvent();
       Maquina_General();
       Maquina_TransDatos();
    }

    return 0;
}
