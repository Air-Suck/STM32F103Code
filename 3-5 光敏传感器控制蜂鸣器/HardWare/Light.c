#include "stm32f10x.h"                  // Device header

//初始化光敏电阻
void Light_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	InitStructure.GPIO_Pin=GPIO_Pin_13;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitStructure);
}

uint8_t Light_Listen(void){
	uint8_t Data=0;
	//说明当前光敏电阻口传入高电平
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1){
		Data=1;
		return Data;
	}
	//否则就是光敏电阻传入低电平
	return Data;
}
