#ifndef __PID_H__
#define __PID_H__

#include "stm32f4xx_hal.h"

#define PERIODIC(T) \
static uint32_t nxt = 0; \
if (HAL_GetTick() < nxt) return; \
nxt += (T);

int16_t Control(float pitch,short gyrox);	//每隔10ms调用一次

#endif
