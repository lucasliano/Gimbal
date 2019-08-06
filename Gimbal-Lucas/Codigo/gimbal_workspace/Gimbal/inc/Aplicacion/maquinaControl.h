/**
  \file maquinaControl.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el sistema de control y el sistema de medición.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/

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
