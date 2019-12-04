#ifndef PR_PWM_H_
#define PR_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "all.h"

void Init_GPIO_PWM(void);
void UpdatePWM(void);
int8_t ActualizarServo(uint8_t nServo,uint8_t tiempo);

#ifdef __cplusplus
}
#endif

#endif /* PR_PWM_H_ */
