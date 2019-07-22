#include  "headers/main.h"

extern uint16_t set_Point;
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
