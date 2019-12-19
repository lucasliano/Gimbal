#ifndef DRIVERS_DR_CONFIG_H_
#define DRIVERS_DR_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "all.h"

#define 	ALTO	1
#define 	BAJO	0
#define 	SALIDA	1
#define 	ENTRADA	0

#define 	FUNCION_GPIO		0
#define 	FUNCION_1			1
#define 	FUNCION_2			2
#define 	FUNCION_3			3

#define 	PULLUP				0
#define 	REPEATER			1
#define 	NONE				2
#define 	PULLDOWN			3

void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion );
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo);
void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion);
void MyInitPLL(void);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_DR_CONFIG_H_ */
