/**
  \file maquinaControl.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el sistema de control y el sistema de medición.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/
#ifndef MAQUINACONTROL_H_
#define MAQUINACONTROL_H_


#ifdef __cplusplus
extern "C" {
#endif



/*Bibliotecas propias*/
#include "all.h"

/*Maquina_Control*/
#define E_MIDIENDO 9
#define E_CALCULANDO 10

/*Maquina midiendo*/
#define E_PAUSA 1
#define E_PRESIONANDO 2

/*Declaracion de rutinas*/
  /*funciones*/
 int  F_Calculando();
 int  hayBoton();

  /*maquinas*/
  int Maquina_Medir();
  void Maquina_Control();


#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
