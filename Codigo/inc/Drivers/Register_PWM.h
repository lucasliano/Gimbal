/*
 * Register_PWM.h
 *
 *  Created on: 21 ago. 2019
 *      Author: NicoCampos
 */

//****************************************************************
// NOTA: MR0 solo sirve para setear el valor del periodo para el
//	PWM y luego le cargo el valor en alto o dutty al Match que
//	quiero manejar. El PWM1.1 tiene asociado el MR1, el PWM1.2 tiene
//	asoiado el MR2 y asi sucesivamente.
//****************************************************************


#ifndef REGISTER_PWM_H_
#define REGISTER_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "all.h"

//!< 0x4001 8000UL: Dirección de inicio de los registros del PWM1
#define PWM1 (( registro *)0x40018000UL)

#define PWM_IR		PWM1[0]
#define PWM_TCR		PWM1[1]
#define PWM_TC		PWM1[2]
#define PWM_PR		PWM1[3]
#define PWM_PC		PWM1[4]
#define PWM_MCR		PWM1[5]
#define PWM_MR0		PWM1[6]
#define PWM_MR1		PWM1[7]
#define PWM_MR2		PWM1[8]
#define PWM_MR3		PWM1[9]
#define PWM_CCR		PWM1[10]
#define PWM_CR0		PWM1[11]
#define PWM_CR1		PWM1[12]
#define PWM_CR2		PWM1[13]
#define PWM_CR3		PWM1[14]
#define PWM_MR4		( ( registro  * )0x40018040UL)
#define PWM_MR5		PWM_MR4[1]
#define PWM_MR6		PWM_MR4[2]
#define PWM_PCR		PWM_MR4[3]
#define PWM_LER		PWM_MR4[4]
#define PWM_CTCR	( ( registro  * )0x40018070UL)


#ifdef __cplusplus
}
#endif
#endif /* REGISTER_PWM_H_ */

