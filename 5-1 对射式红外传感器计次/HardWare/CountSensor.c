#include "stm32f10x.h"                  // Device header
//用于显示数据
uint16_t Num;

//外部中断引脚的初始化
void CountSensor_Init(void){
	//1.通过RCC开启外设时钟（只需要开启GPIO和AFIO的时钟，EXTI和NVIC默认开启）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//2.初始化GPIO引脚
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	InitStructure.GPIO_Pin=GPIO_Pin_12;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitStructure);
	//3.初始化AFIO（从哪个引脚来的）
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
	//4.初始化EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line=EXTI_Line12;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	//中断模式
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	//上升沿模式
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	//5.初始化NVIC（选择抢占优先级和响应优先级）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
}

uint16_t GetNum(void){
	return Num;
}

//外部中断函数（函数名在头文件中找）
void EXTI15_10_IRQHandler(void){
	//若设置的引脚出现了外部中断
	if(EXTI_GetITStatus(EXTI_Line12)==SET){
		Num++;
		//将外部中断标志清除
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}
