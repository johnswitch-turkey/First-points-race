//#include "uart.h"
//#include "stm32f4xx_hal.h"



//extern UART_HandleTypeDef huart1;  // ȷ�� huart4 �Ѿ��������ط�����ͳ�ʼ��
//uint8_t receive_data[DATA_MAX_LEN];     // �������ݻ�����
//uint16_t receive_num;       // ��ǰ���յ��������ֽ���

//void UART1_IRQHandler(void)
//{
//    uint8_t Res;
//    
//    // ��� UART4 �Ƿ񴥷��˽��շǿ��ж�
//    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
//    {
//        // �� UART4 ��������
//        Res = (uint8_t)(huart1.Instance->DR & 0xFF);
//        
//        // �洢���յ������ݵ��������������ӽ��ռ���
//        receive_data[receive_num++] = Res;
//        
//        // ������շǿ��жϱ�־��ͨ����ȡ���ݼĴ����Զ������
//        __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
//    }
//    
//    // ��������� UART �ж���Ҫ�������������������Ӧ�Ĵ���
//}


//int Decode_UART_data(void)
//{
//	int retval = 0;

//	retval += (receive_data[1] - '0') * 100;
//	retval += (receive_data[2] - '0') * 10;
//	retval += (receive_data[3] - '0') * 1;
//	
//	if(receive_data[0] == '+')
//		return retval;
//	else 
//	{
//		retval *= -1;
//		return retval;
//	}
//}
