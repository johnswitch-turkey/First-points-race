#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f4xx_hal.h"

#define DIR_PIN  GPIO_PIN_1  // 方向引脚
#define STEP_PIN GPIO_PIN_2  // 步进引脚
#define DIR_PORT GPIOB       // 方向引脚端口
#define STEP_PORT GPIOA      // 步进引脚端口


// 设置脉冲频率 (单位：Hz)
void Motor_SetPulseFreq(uint32_t freq);

// 设置脉冲数量 (0表示无限脉冲)
void Motor_SetPulseNum(uint16_t pulse_num);

// 启动脉冲输出
void Motor_PulseStart(void);

// 停止脉冲输出
void Motor_PulseStop(void);

// 检查脉冲是否结束
uint8_t Motor_PulseIsEnd(void);

// 设置电机方向 (1: 正转, 0: 反转)
void Motor_SetDirection(uint8_t direction);

// 主控制函数：设置频率和脉冲数
void Motor_Control(uint32_t freq, uint16_t pulse_num, uint8_t direction);

#endif
