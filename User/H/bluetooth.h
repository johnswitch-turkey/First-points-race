
#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "stm32f4xx_hal.h"

// 定义蓝牙缓冲区大小
#define BT_RX_BUFFER_SIZE 20

// 蓝牙初始化
HAL_StatusTypeDef Bluetooth_Init(UART_HandleTypeDef *huart);

// 发送数据到蓝牙终端
HAL_StatusTypeDef Bluetooth_SendData(UART_HandleTypeDef *huart, const char *data);

// 解析角度命令（支持正负号）
HAL_StatusTypeDef Bluetooth_ProcessAngleCommand(uint8_t *rx_buffer, float *target_angle);

// 解析速度命令
HAL_StatusTypeDef Bluetooth_ProcessSpeedCommand(uint8_t *rx_buffer, int *target_speed);

// 获取接收完成标志
uint8_t Bluetooth_GetRxFlag(void);
// 清除接收完成标志
void Bluetooth_ClearRxFlag(void);

#endif
