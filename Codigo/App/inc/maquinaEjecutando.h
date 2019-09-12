/**
  \file maquinaEjecutando.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el funcionamiento de la maquina de estado Ejecutando.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "timers.h"
#include "maquinaControl.h"
#include "PWM_Primitivas.h"

/*Declaracion de rutinas*/
  /*funciones*/
  void F_Ejecutando();
  int tostring(char*, int);
  void ActualizarValorPWM();
  void ActualizarDisplay();
