#include "light.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim4;

int light = 999;

void SetLightness(int light){
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,light);
}

void LimitLight(int *light)
{
	if(*light>PWM_MAX)*light=PWM_MAX;
	if(*light<PWM_MIN)*light=PWM_MIN;
}
