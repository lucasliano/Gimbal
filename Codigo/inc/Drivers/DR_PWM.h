#ifndef PWM_H_
#define PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"

// Declaracion de pines de salida de PWM1

#define PIN_PWM1_1_P1	1,18,2	// funcion 2
#define PIN_PWM1_1_P2	2,0,1	// funcion 1

#define PIN_PWM1_2_P1	1,20,2	// funcion 2
#define PIN_PWM1_2_P2	2,1,1	// funcion 1
#define PIN_PWM1_2_P3	3,25,3	// funcion 3

#define PIN_PWM1_3_P1	1,21,2	// funcion 2
#define PIN_PWM1_3_P2	2,2,1	// funcion 1
#define PIN_PWM1_3_P3	3,26,3	// funcion 3

#define PIN_PWM1_4_P1	1,23,2	// funcion 2
#define PIN_PWM1_4_P2	2,3,1	// funcion 1

#define PIN_PWM1_5_P1	1,24,2	// funcion 2
#define PIN_PWM1_5_P2	2,4,1	// funcion 1

#define PIN_PWM1_6_P1	1,26,2	// funcion 2
#define PIN_PWM1_6_P2	2,5,1	// funcion 1





void Init_PWM(void);
void ActualizarValorPWM();

#ifdef __cplusplus
}
#endif
#endif /* PWM_H_ */
