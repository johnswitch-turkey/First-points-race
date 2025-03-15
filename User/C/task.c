#include "task.h"
#include "stm32f4xx_hal.h"
#include "light.h"
#include "keyboard.h"
#include "main.h"
#include "bluetooth.h"
#include "motor.h"
#include "function.h"
#include "mpu6050.h"
#include "pid.h"

//操作句柄
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;

//外部变量
extern uint16_t light;    //0~1000
extern uint8_t up ;
extern int speed;

float target_angle = 0.0f;
float current_angle;
extern float pitch, roll, yaw;
float pid_params[4] = {1000.0f, 1.0f, 10.0f, 1000.0f};
uint8_t sta = 0;

//激光控制
void task1(void){
	switch (up){
		case 1:
			light += 100;
			Limit(&light);
			SetLightness(light);
			up = 0;
			break;
		case 2:
			light -= 100;
			Limit(&light);
			SetLightness(light);
			up = 0;
			break;
	}
	
	if (ON)
			LIGHT_STOP();
	if (OFF)
			LIGHT_START();
			
	}

	
	//电机速度控制
	void task2(void){
	switch (up){
		case 1:
			speed += 100;
			Setspeed(speed);
			up = 0;
			break;
		case 2:
			light -= 100;
			Setspeed(speed);
			up = 0;
			break;
	}
	
	
	if (ON)
			MOTOR_STOP();
	if (OFF)
			MOTOR_START();
	
}

//电机位置控制
void task3(void){
	if (sta == 0){
	HAL_TIM_Base_Start_IT(&htim5);
	} 
	else{
	MOTOR_START();
	mpu_dmp_get_data(&pitch, &roll, &yaw);
	current_angle = pitch;
	}
}

void task4(void){
}

void task5(void){
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if (htim == &htim5){
		if (speed != 1){
		Setspeed(abs(5));
		}
//				Setspeed(abs(1000));
		HAL_TIM_Base_Start_IT(&htim5);
	}
}
