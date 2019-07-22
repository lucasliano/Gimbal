/*Standar Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Bibliotecas propias*/
#include "headers/primitivas/bibliotecaInfoII.h"
#include "headers/aplicacion/timers.h"
#include "headers/aplicacion/maquinaGeneral.h"

/*Maquina_Control*/
#define E_MIDIENDO 9
#define E_CALCULANDO 10

/*Declaracion de rutinas*/
  /*funciones*/
  bool F_Calculando();
  
  /*maquinas*/
  bool Maquina_Medir();
