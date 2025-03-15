#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stm32f4xx_hal.h"

#define SPEED_MAX 30
#define SPEED_MIN -30

#define MOTOR_DIR_CW HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)		//顺时针
#define MOTOR_DIR_CCW HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)		//逆时针
#define MOTOR_STOP() HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3)					//停止转动
#define MOTOR_START() HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3)					//开始转动



void Setspeed(int speed);
void Limit( int16_t *speed);
int abs(int speed);

#endif
