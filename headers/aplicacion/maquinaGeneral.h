/*Standar Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Bibliotecas propias*/
#include "headers/primitivas/bibliotecaInfoII.h"
#include "headers/aplicacion/timers.h"
#include "headers/aplicacion/maquinaControl.h"


/*Maquina principal*/
#define E_CALIBRANDO 5
#define E_FUNCIONANDO 6

/*Maquina_Funcionando*/   //Esto no se esta usando!
#define E_CONTROLANDO 7
#define E_EJECUTANDO 8



/*Declaracion de rutinas*/
  /*funciones*/
  void Inicializar();
  bool Recalibrar_Confirm();
  void F_Funcionando();
  void F_Ejecutando();      //f porque es una funcion y no una maquina

  /*maquinas*/
  void Maquina_General();
  void Maquina_TransDatos();
  void Maquina_Calibrando();
  void Maquina_Control();
