#include "stm32f4xx.h"                  // Device header
#include "Serial.h"

//PA9用于发送串口数据
//串口在APB2总线上，PA在AHB1总线上
//这个函数是初始化了usart外设，但是还没有去使能引脚，所以msp函数就是用来使能引脚的
void Serial_Init(unsigned int baud){
	//usart中的s代表的是同步，这种模式的串口配置会多一个时钟配置,这里只需要异步串口就足够了
	//就是用来指定一个usart的，instance的内容就是一个usart外设的寄存器
	huart.Instance=USART_UX;
	//设置波特率
	huart.Init.BaudRate=baud;
	//是否需要硬件流
	//如果说发送设备发送速度过快，接收设备就可以通过硬件流向发送设备发送信号
	//告知其停止发送数据，防止数据的流失
	//但是一般不使用,这里也选择不启用硬件流控制
	huart.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	//选择串口模式，说白了就是使能还是失能TX和RX，这里只使能TX
	huart.Init.Mode=UART_MODE_TX;
	//配置过采样率，就是在每一位内不止采样一次以保证数据正确不受噪声的干扰
	huart.Init.OverSampling=UART_OVERSAMPLING_16;
	//校验位,选择无校验
	huart.Init.Parity=UART_PARITY_NONE;
	//停止位长度,停止位长度为1
	huart.Init.StopBits=UART_STOPBITS_1;
	//字长，就是每一个数据帧中的数据位数（包括校验位）
	huart.Init.WordLength=UART_WORDLENGTH_8B;
	//直到初始化成功
	while(HAL_UART_Init(&huart) != HAL_OK);
}
//配置引脚，启动时钟等，也就是配置串口的硬件资源
void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
	//给端口赋默认值
	HAL_GPIO_DeInit(GPIOA,GPIO_PIN_9);
	//使能PA9
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//使能串口1
	__HAL_RCC_USART1_CLK_ENABLE(); 
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Alternate=GPIO_AF7_USART1;
	GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pin=GPIO_PIN_9;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);
	//启动串口
	__HAL_UART_ENABLE(huart);
}

void Serial_SendByte(uint8_t Byte){
	HAL_UART_Transmit(&huart,&Byte,1,HAL_MAX_DELAY);
}
