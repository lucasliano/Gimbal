#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecaInfoII.h"

/*Maquina principal*/
#define E_CALIBRANDO     5
#define E_FUNCIONANDO   6
/*Maquina_Funcionando*/
#define E_CONTROLANDO  7
#define E_EJECUTANDO   8
/*Maquina_Control*/
#define E_MIDIENDO    9
#define E_CALCULANDO  10


/*Constantes y timers*/
#define TIMER_CONTROL 1

#define TRUE 0
#define FALSE 1

/*Declaracion de funciones*/
void Inicializar();
bool Recalibar_Confirm();

/*Funciones asociadas a timers*/
void Init_Timers();
void ActualizarExt_TControl();
void SetTimer(uint16_t timer);


void Maquina_General();
void Maquina_TransDatos();
void Maquina_Calibrando();
void Maquina_Funcionando();
void F_Ejecutando();//f porque es una funcion y no una maquina
void Maquina_Control();
