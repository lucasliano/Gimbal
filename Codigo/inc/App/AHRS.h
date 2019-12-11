/**
  \file AHRS.h
  \brief Definiciones relacionadas a filtros utilizados para la obtención de angulos de Euler
  \author Grupo 8 - R2003
  \date 2019.12.06
  \version 1.2
*/


#ifndef APP_AHRS_H_
#define APP_AHRS_H_
#include "all.h"



#define FRECUENCIA_MEDICION_IMU_MS		10	//125			//Si no me equivoco serian 8Hz

//Envio de angulos
void enviarPlot(void);

//Relacionado a IMU
void IniciarIMU (void);
void CalibrarIMU (void);
void MedirIMU (void);

//Relacionado a Filtros
void FiltroPasaBajos(void);
void ActualizarAngulos(void);






#endif /* APP_AHRS_H_ */
