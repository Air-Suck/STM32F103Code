#ifndef __SERIAL_H
#define __SERIAL_H

    #define USART_UX  USART1
	extern UART_HandleTypeDef huart;
	void Serial_Init(unsigned int baud);
	void HAL_UART_MspInit(UART_HandleTypeDef* huart);
	void Serial_SendByte(uint8_t Byte);
	

#endif
