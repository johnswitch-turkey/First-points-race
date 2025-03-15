// bluetooth.c
#include "bluetooth.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

uint8_t up = 0,state = 0;

static UART_HandleTypeDef *huart1;    // 蓝牙使用的UART句柄
static uint8_t rx_buffer[BT_RX_BUFFER_SIZE]; // 接收缓冲区
static uint8_t rx_flag = 0;            // 接收完成标志
static uint8_t rx_temp[BT_RX_BUFFER_SIZE]; // 临时缓冲区
static uint8_t rx_index = 0;           // 接收索引

/**
 * @brief 初始化蓝牙模块
 * @param huart UART句柄（例如 &huart1）
 * @retval HAL状态
 */
HAL_StatusTypeDef Bluetooth_Init(UART_HandleTypeDef *huart) {
    huart1 = huart;
    // 清空缓冲区
    memset(rx_buffer, 0, BT_RX_BUFFER_SIZE);
    memset(rx_temp, 0, BT_RX_BUFFER_SIZE);
    rx_index = 0;
    rx_flag = 0;

    // 启动UART中断接收，每次接收1字节
    return HAL_UART_Receive_IT(huart1, rx_buffer, 1);
}

/**
 * @brief 通过蓝牙发送数据
 * @param huart UART句柄
 * @param data 要发送的字符串
 * @retval HAL状态
 */
HAL_StatusTypeDef Bluetooth_SendData(UART_HandleTypeDef *huart, const char *data) {
    return HAL_UART_Transmit(huart, (uint8_t *)data, strlen(data), HAL_MAX_DELAY);
}

/**
 * @brief 解析角度命令（支持正负号）
 * @param rx_buffer 接收到的数据缓冲区
 * @param target_angle 解析出的目标角度
 * @retval HAL状态
 */
HAL_StatusTypeDef Bluetooth_ProcessAngleCommand(uint8_t *rx_buffer, float *target_angle) {
    char cmd[BT_RX_BUFFER_SIZE];
    strncpy(cmd, (char *)rx_buffer, BT_RX_BUFFER_SIZE - 1);
    cmd[BT_RX_BUFFER_SIZE - 1] = '\0';

    // 期望格式：A<正负号><角度>，如 A+30.5 或 A-60
    float angle_value;
    if (sscanf(cmd, "A%f", &angle_value) == 1) {
        *target_angle = angle_value; // sscanf 会自动识别正负号
        char response[50];
        sprintf(response, "Set Angle: %.2f\r\n", *target_angle);
        return Bluetooth_SendData(huart1, response);
    } else {
        return Bluetooth_SendData(huart1, "Invalid Angle Command\r\n");
    }
}

/**
 * @brief 解析速度命令
 * @param rx_buffer 接收到的数据缓冲区
 * @param target_speed 解析出的目标速度
 * @retval HAL状态
 */
HAL_StatusTypeDef Bluetooth_ProcessSpeedCommand(uint8_t *rx_buffer, int *target_speed) {
    char cmd[BT_RX_BUFFER_SIZE];
    strncpy(cmd, (char *)rx_buffer, BT_RX_BUFFER_SIZE - 1);
    cmd[BT_RX_BUFFER_SIZE - 1] = '\0';

    // 期望格式：S<速度>，如 S100
    if (sscanf(cmd, "S%d", target_speed) == 1) {
        char response[50];
        sprintf(response, "Set Speed: %d\r\n", *target_speed);
        return Bluetooth_SendData(huart1, response);
    } else {
        return Bluetooth_SendData(huart1, "Invalid Speed Command\r\n");
    }
}

/**
 * @brief 获取接收完成标志
 * @retval 接收标志状态 (1: 已完成, 0: 未完成)
 */
uint8_t Bluetooth_GetRxFlag(void) {
    return rx_flag;
}

/**
 * @brief 清除接收完成标志
 */
void Bluetooth_ClearRxFlag(void) {
    rx_flag = 0;
}

/**
 * @brief UART接收完成回调函数
 * @param huart UART句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == huart1) {
			state = rx_buffer[0];
		if(state==0x00) up = 1;
		else if (state==0x01) up = 2;
		else if (state==0x01) up = 3;
		else if (state==0x01) up = 4;
		else if (state==0x01) up = 5;
		else if (state==0x01) up = 6;
		else if (state==0x01) up = 7;
        // 收到一个字节，存入临时缓冲区
        if (rx_buffer[0] == '\n' || rx_buffer[0] == '\r') {
            // 遇到换行符，命令接收完成
            rx_temp[rx_index] = '\0'; // 字符串结束
            rx_index = 0;
            rx_flag = 1; // 设置接收完成标志
            memcpy(rx_buffer, rx_temp, BT_RX_BUFFER_SIZE); // 复制到主缓冲区
        } else if (rx_index < BT_RX_BUFFER_SIZE - 1) {
            rx_temp[rx_index++] = rx_buffer[0];
        }

        // 继续接收下一个字节
        HAL_UART_Receive_IT(huart1, rx_buffer, 1);
    }
}

/**
 * @brief UART错误回调函数（可选）
 * @param huart UART句柄
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    if (huart == huart1) {
        // 发生错误时重新启动接收
        HAL_UART_Receive_IT(huart1, rx_buffer, 1);
    }
}
