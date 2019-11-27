#ifndef SYSTICK_H_
#define SYSTICK_H_

#ifdef __cplusplus
extern "C" {		//En este archivo hace falta aclarar si lo vamos a compilar como C o C++
#endif				//Como vamos a programar c acá, entonces lo declaramos como C

#include "Regs_LPC176x.h"
#include "timers.h"

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;

//#define 	SYSTICK		( (systick_t *) 0xE000E010UL )
//
//#define		STCTRL		SYSTICK->_STCTRL
//
//	#define	ENABLE			SYSTICK->bits._ENABLE
//	#define	TICKINT			SYSTICK->bits._TICKINT
//	#define	CLKSOURCE		SYSTICK->bits._CLKSOURCE
//	#define	COUNTFLAG		SYSTICK->bits._COUNTFLAG
//
//#define		STRELOAD	SYSTICK->_STRELOAD
//#define		STCURR		SYSTICK->_STCURR
//#define		STCALIB		SYSTICK->_STCALIB
//
//typedef struct
//{
//	union{
//		__RW uint32_t _STCTRL;
//		struct{
//			__RW uint32_t _ENABLE:1;
//			__RW uint32_t _TICKINT:1;
//			__RW uint32_t _CLKSOURCE:1;
//			__RW uint32_t _RESERVED0:13;
//			__RW uint32_t _COUNTFLAG:1;
//			__RW uint32_t _RESERVED1:15;
//		}bits;
//	};
//	__RW uint32_t _STRELOAD;
//	__RW uint32_t _STCURR;
//	__R uint32_t  _STCALIB;
//}systick_t;
//

void InicializarSysTick ( void );





#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
