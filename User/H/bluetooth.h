
#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "stm32f4xx_hal.h"

// ����������������С
#define BT_RX_BUFFER_SIZE 20

// ������ʼ��
HAL_StatusTypeDef Bluetooth_Init(UART_HandleTypeDef *huart);

// �������ݵ������ն�
HAL_StatusTypeDef Bluetooth_SendData(UART_HandleTypeDef *huart, const char *data);

// �����Ƕ����֧�������ţ�
HAL_StatusTypeDef Bluetooth_ProcessAngleCommand(uint8_t *rx_buffer, float *target_angle);

// �����ٶ�����
HAL_StatusTypeDef Bluetooth_ProcessSpeedCommand(uint8_t *rx_buffer, int *target_speed);

// ��ȡ������ɱ�־
uint8_t Bluetooth_GetRxFlag(void);
// ���������ɱ�־
void Bluetooth_ClearRxFlag(void);

#endif
