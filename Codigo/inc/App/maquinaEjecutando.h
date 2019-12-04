/**
  \file maquinaEjecutando.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el funcionamiento de la maquina de estado Ejecutando.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

#ifndef MAQUINAEJECUTANDO_H_
#define MAQUINAEJECUTANDO_H_


#ifdef __cplusplus
extern "C" {
#endif



/*Bibliotecas propias*/
#include "all.h"

/*Declaracion de rutinas*/
  /*funciones*/
  void F_Ejecutando();
  int tostring(char*, int);
  void ActualizarValorPWM();
  void ActualizarDisplay();


#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
