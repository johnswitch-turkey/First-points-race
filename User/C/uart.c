//#include "uart.h"
//#include "stm32f4xx_hal.h"



//extern UART_HandleTypeDef huart1;  // 确保 huart4 已经在其他地方定义和初始化
//uint8_t receive_data[DATA_MAX_LEN];     // 接收数据缓冲区
//uint16_t receive_num;       // 当前接收到的数据字节数

//void UART1_IRQHandler(void)
//{
//    uint8_t Res;
//    
//    // 检查 UART4 是否触发了接收非空中断
//    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
//    {
//        // 从 UART4 接收数据
//        Res = (uint8_t)(huart1.Instance->DR & 0xFF);
//        
//        // 存储接收到的数据到缓冲区，并增加接收计数
//        receive_data[receive_num++] = Res;
//        
//        // 清除接收非空中断标志（通过读取数据寄存器自动清除）
//        __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_RXNE);
//    }
//    
//    // 如果有其他 UART 中断需要处理，可以在这里添加相应的代码
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
