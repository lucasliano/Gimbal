/**
  \file all.h
  \brief Archivo que contiene todos los .h para facilitar.
  \author Grupo 8 - R2003
  \date 2019.11.09
  \version 1.2
*/


#ifndef ALL_H_

#define ALL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Standar Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cr_section_macros.h>

/*Own Libraries*/
//Drivers
#include "main.h"
#include "Regs_LPC176x.h"
#include "Register_PWM.h"
#include "PWM.h"
#include "DR_sysTick.h"
#include "I2C.h"
#include "DR_timers.h"
#include "APP_timers.h"
#include "DR_Config.h"
#include "DR_lcd.h"
#include "DR_Infotronic.h"
#include "DR_gpio.h"
#include "DR_UART0.h"
//Primitivas
#include "comunicaciones.h"
#include "PWM_Primitivas.h"
#include "PR_timers.h"
#include "PR_lcd.h"
#include "PR_UART.h"
//App
#include "circularBuffer.h"
#include "maquinaComSerie.h"
#include "maquinaControl.h"
#include "maquinaEjecutando.h"
#include "maquinaGeneral.h"








#ifdef __cplusplus
}
#endif

#endif /* ALL_H_ */
