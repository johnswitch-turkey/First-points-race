// bluetooth.c
#include "bluetooth.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

uint8_t up = 0,state = 0;

static UART_HandleTypeDef *huart1;    // ����ʹ�õ�UART���
static uint8_t rx_buffer[BT_RX_BUFFER_SIZE]; // ���ջ�����
static uint8_t rx_flag = 0;            // ������ɱ�־
static uint8_t rx_temp[BT_RX_BUFFER_SIZE]; // ��ʱ������
static uint8_t rx_index = 0;           // ��������

/**
 * @brief ��ʼ������ģ��
 * @param huart UART��������� &huart1��
 * @retval HAL״̬
 */
HAL_StatusTypeDef Bluetooth_Init(UART_HandleTypeDef *huart) {
    huart1 = huart;
    // ��ջ�����
    memset(rx_buffer, 0, BT_RX_BUFFER_SIZE);
    memset(rx_temp, 0, BT_RX_BUFFER_SIZE);
    rx_index = 0;
    rx_flag = 0;

    // ����UART�жϽ��գ�ÿ�ν���1�ֽ�
    return HAL_UART_Receive_IT(huart1, rx_buffer, 1);
}

/**
 * @brief ͨ��������������
 * @param huart UART���
 * @param data Ҫ���͵��ַ���
 * @retval HAL״̬
 */
HAL_StatusTypeDef Bluetooth_SendData(UART_HandleTypeDef *huart, const char *data) {
    return HAL_UART_Transmit(huart, (uint8_t *)data, strlen(data), HAL_MAX_DELAY);
}

/**
 * @brief �����Ƕ����֧�������ţ�
 * @param rx_buffer ���յ������ݻ�����
 * @param target_angle ��������Ŀ��Ƕ�
 * @retval HAL״̬
 */
HAL_StatusTypeDef Bluetooth_ProcessAngleCommand(uint8_t *rx_buffer, float *target_angle) {
    char cmd[BT_RX_BUFFER_SIZE];
    strncpy(cmd, (char *)rx_buffer, BT_RX_BUFFER_SIZE - 1);
    cmd[BT_RX_BUFFER_SIZE - 1] = '\0';

    // ������ʽ��A<������><�Ƕ�>���� A+30.5 �� A-60
    float angle_value;
    if (sscanf(cmd, "A%f", &angle_value) == 1) {
        *target_angle = angle_value; // sscanf ���Զ�ʶ��������
        char response[50];
        sprintf(response, "Set Angle: %.2f\r\n", *target_angle);
        return Bluetooth_SendData(huart1, response);
    } else {
        return Bluetooth_SendData(huart1, "Invalid Angle Command\r\n");
    }
}

/**
 * @brief �����ٶ�����
 * @param rx_buffer ���յ������ݻ�����
 * @param target_speed ��������Ŀ���ٶ�
 * @retval HAL״̬
 */
HAL_StatusTypeDef Bluetooth_ProcessSpeedCommand(uint8_t *rx_buffer, int *target_speed) {
    char cmd[BT_RX_BUFFER_SIZE];
    strncpy(cmd, (char *)rx_buffer, BT_RX_BUFFER_SIZE - 1);
    cmd[BT_RX_BUFFER_SIZE - 1] = '\0';

    // ������ʽ��S<�ٶ�>���� S100
    if (sscanf(cmd, "S%d", target_speed) == 1) {
        char response[50];
        sprintf(response, "Set Speed: %d\r\n", *target_speed);
        return Bluetooth_SendData(huart1, response);
    } else {
        return Bluetooth_SendData(huart1, "Invalid Speed Command\r\n");
    }
}

/**
 * @brief ��ȡ������ɱ�־
 * @retval ���ձ�־״̬ (1: �����, 0: δ���)
 */
uint8_t Bluetooth_GetRxFlag(void) {
    return rx_flag;
}

/**
 * @brief ���������ɱ�־
 */
void Bluetooth_ClearRxFlag(void) {
    rx_flag = 0;
}

/**
 * @brief UART������ɻص�����
 * @param huart UART���
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
        // �յ�һ���ֽڣ�������ʱ������
        if (rx_buffer[0] == '\n' || rx_buffer[0] == '\r') {
            // �������з�������������
            rx_temp[rx_index] = '\0'; // �ַ�������
            rx_index = 0;
            rx_flag = 1; // ���ý�����ɱ�־
            memcpy(rx_buffer, rx_temp, BT_RX_BUFFER_SIZE); // ���Ƶ���������
        } else if (rx_index < BT_RX_BUFFER_SIZE - 1) {
            rx_temp[rx_index++] = rx_buffer[0];
        }

        // ����������һ���ֽ�
        HAL_UART_Receive_IT(huart1, rx_buffer, 1);
    }
}

/**
 * @brief UART����ص���������ѡ��
 * @param huart UART���
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    if (huart == huart1) {
        // ��������ʱ������������
        HAL_UART_Receive_IT(huart1, rx_buffer, 1);
    }
}
