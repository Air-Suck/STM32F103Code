#include "stm32f10x.h"                  // Device header

//初始化蜂鸣器
void Buzzer_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	InitStructure.GPIO_Pin=GPIO_Pin_12;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Operator(int state){
	//为0(低电平)时将蜂鸣器打开
	if(state==0){
		//低电平时蜂鸣器启动
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
	else{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
}
