/**
  \file DR_I2C.h
  \brief Almacena todas las definiciones correspondientes a las primitivas del periferico I2C1.
  \author Grupo 8 - R2003
  \date 2019.10.19
  \version 1.2
*/

#ifndef PRIMITIVAS_PR_I2C_H_
#define PRIMITIVAS_PR_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "all.h"


#define TIMEOUT_I2C 	5	//ms



//Primitivas
int8_t singleReadI2C(uint8_t addr, uint8_t RA, uint8_t* data);					//Guarda el dato del registro RA en DATA[0] del disposito con direccion ADDR
int8_t singleWriteI2C(uint8_t addr, uint8_t RA, uint8_t data);					//Escribe DATA en RA del disposito con direccion ADDR
int8_t burstReadI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size);	//Guarda el dato del registro RA[i] en DATA[i] del dispositivo con direccion ADDR
int8_t burstWriteI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size);	//Escribe DATA[i] en el registro RA[i] del dispositivo con direccion ADDR


#ifdef __cplusplus
}
#endif

#endif /* PRIMITIVAS_PR_I2C_H_ */
