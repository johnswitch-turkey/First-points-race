#include "motor.h"
#include "pid.h"


extern TIM_HandleTypeDef htim2;
extern float pitch;


void Setspeed(int speed){
//	PERIODIC(70);
		__HAL_TIM_SET_AUTORELOAD(&htim2,1000000/speed-1);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,(1000000/speed-1)/2);
	}

//	MOTOR_START();
//	speed--;
//	if (speed == 0){
//		MOTOR_STOP();
//	}


void Limit( int16_t *speed){
	if(*speed>SPEED_MAX)*speed=SPEED_MAX;
	if(*speed<SPEED_MIN)*speed=SPEED_MIN;
}


int abs(int speed){
	if (speed > 0){
		return speed;
	}
	else{
		return -speed;
	}


}
