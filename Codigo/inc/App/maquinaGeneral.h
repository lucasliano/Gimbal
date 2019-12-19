/**
  \file maquinaGeneral.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el funcionamiento de las máquinas de estados. En particular de la máquina maquinaGeneral().
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/
#ifndef MAQUINAGENERAL_H_
#define MAQUINAGENERAL_H_


#ifdef __cplusplus
extern "C" {
#endif


/*Bibliotecas propias*/
#include "all.h"


/*Maquina principal*/
#define E_CALIBRANDO 5
#define E_FUNCIONANDO 6

/*Maquina_Funcionando*/   //Esto no se esta usando!
#define E_CONTROLANDO 7
#define E_EJECUTANDO 8



/*Declaracion de rutinas*/
  /*funciones*/
  void Inicializar_HW();
  int8_t  Recalibrar_Confirm();
  void F_Funcionando();


  /*maquinas*/
  void Maquina_General();
  int Maquina_Calibrando();


#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
