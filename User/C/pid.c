#include "pid.h"
#include "mpu6050.h"
#include "motor.h"

//传感器数据变量
int Encoder_Left,Encoder_Right;
float pitch,roll,yaw;
short gyrox,gyroy,gyroz;
short	aacx,aacy,aacz;
int speed = 1;

//闭环控制中间变量
int16_t Vertical_out = 20;


//参数
float Vertical_Kp=4,Vertical_Kd=0.01;

extern TIM_HandleTypeDef htim2;



//角度环PD控制器
//输入：期望角度、真实角度、角速度
//int Vertical(float Med,float Angle,float gyro_Y)
//{
//	int temp;
//	temp=Vertical_Kp*(Angle-Med);
//	return temp;
//}

int16_t Control(float pitch,short gyrox){

//		MPU_Get_Accelerometer(&gyrox,&gyroy,&gyroz);
//		mpu_dmp_get_data(&pitch,&roll,&yaw);
		Vertical_out = Vertical_Kp*(pitch-0) + Vertical_Kd*gyrox;
	  Limit(&Vertical_out);
			

	if(Vertical_out<0){
		MOTOR_DIR_CCW;
	}
	else{
		MOTOR_DIR_CW;
	}
	if (Vertical_out != 0){
		speed = Vertical_out;
	}
	

	return Vertical_out;
}
