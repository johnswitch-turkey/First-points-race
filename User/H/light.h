#ifndef __LIGHT_H
#define __LIGHT_H

#define PWM_MAX 1000
#define PWM_MIN 0

#define LIGHT_STOP() HAL_TIM_Base_Stop(&htim4)
#define LIGHT_START() HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2)

void LimitLight(int *speed);
void SetLightness(int light);

#endif
