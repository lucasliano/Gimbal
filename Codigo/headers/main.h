/**
  \file main.h
  \brief Almacena las definiciones mas genericas que se van a utilizar en el desarrollo del programa. 
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.1
*/

/*Standar Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Bibliotecas propias*/
#include "headers/primitivas/bibliotecaInfoII.h"
#include "headers/aplicacion/timers.h"
#include "headers/aplicacion/maquinaGeneral.h"

/*Constantes*/
#define TRUE 0
#define FALSE 1

/*Definicion de rutinas*/
void F_Ejecutando();       //f porque es una funcion y no una maquina
void Maquina_TransDatos();
