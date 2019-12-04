/**
  \file maquinaComSerie.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el funcionamiento de funciones relacionados a la comunicación Serie a nivel de App.
  \author Grupo 8 - R2003
  \date 2019.10.14
  \version 1.2
*/
#ifndef MAQUINACOMSERIE_H_
#define MAQUINACOMSERIE_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"

//------------Defines-------------------
#define MSG_SIZE 15

//-----------Estados--------------------
#define ESPERANDO_INICIO 0
#define ESPERANDO_TIPO 1
#define RECIBIENDO_DATOS 2


//------------Funciones------------------
void Maquina_TransDatos(void);
void initComSerie(void);
void analizarTrama(KeyType* trama);



#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */

