#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f4xx_hal.h"

#define DIR_PIN  GPIO_PIN_1  // ��������
#define STEP_PIN GPIO_PIN_2  // ��������
#define DIR_PORT GPIOB       // �������Ŷ˿�
#define STEP_PORT GPIOA      // �������Ŷ˿�


// ��������Ƶ�� (��λ��Hz)
void Motor_SetPulseFreq(uint32_t freq);

// ������������ (0��ʾ��������)
void Motor_SetPulseNum(uint16_t pulse_num);

// �����������
void Motor_PulseStart(void);

// ֹͣ�������
void Motor_PulseStop(void);

// ��������Ƿ����
uint8_t Motor_PulseIsEnd(void);

// ���õ������ (1: ��ת, 0: ��ת)
void Motor_SetDirection(uint8_t direction);

// �����ƺ���������Ƶ�ʺ�������
void Motor_Control(uint32_t freq, uint16_t pulse_num, uint8_t direction);

#endif
