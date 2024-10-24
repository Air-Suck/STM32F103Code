#include "stm32f10x.h"   
//#include "OLED.h"

// Device header
//用于显示数据
uint16_t Num=100;

//外部中断引脚的初始化
void Encoder_Init(void){
	
	//1.通过RCC开启外设时钟（只需要开启一次）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//2.初始化GPIO引脚
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	//同时初始化两个引脚
	InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitStructure);
	//3.初始化AFIO（初始化两条线路）
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	//4.初始化EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	//初始化两条中断线
	EXTI_InitStruct.EXTI_Line=EXTI_Line12|EXTI_Line14;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	//中断模式
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	//下降沿模式
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//5.初始化NVIC（选择抢占优先级和响应优先级）
	//中断分组（一个芯片只需要初始化一次）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//对两条中断线路进行优先级定义
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
}


uint16_t GetNum(void){
	return Num;
}

//外部中断函数
//不需要考虑方波函数的周期，因为下降沿只有四种情况：
//1.12号引脚触发下降沿，14号引脚为低电平
//2.12号引脚触发下降沿，14号引脚为高电平
//3.14号引脚触发下降沿，12号引脚为低电平
//4.14号引脚触发下降沿，12号引脚为高电平
//其中1、4等价，2、3等价
//若使用1、2或者3、4方案就只需要初始化一个引脚，但是会出现up最开始说的情况
void EXTI15_10_IRQHandler(void){
	//推荐使用这种方式
	//正转情况下12号脚触发外部中断信号，14号脚处于低电平
	if(EXTI_GetITStatus(EXTI_Line12)==SET){
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)==0){
			Num++;
		}
		//将外部中断标志清除
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	
	//反转情况下14号脚触发外部中断信号，12号脚处于低电平
	if(EXTI_GetITStatus(EXTI_Line14)==SET){
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==0){
			Num--;
		}
		//将外部中断标志清除
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	//EXTI_ClearITPendingBit(EXTI_Line12);
	
	//这种情况可以不将14号引脚置为外部中断引脚
//	if(EXTI_GetITStatus(EXTI_Line12)==SET){
//		//正转情况下12号脚触发外部中断信号，14号脚处于低电平
//		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)==0){
//			Num++;
//		}
//		//反转情况下12号脚触发外部中断信号，14号脚处于高电平
//		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)==1){
//			Num--;
//		}
//		//将外部中断标志清除（在判断是否有中断信号的if语句中清除）
//		EXTI_ClearITPendingBit(EXTI_Line12);
//	}
//	
//	//仍然要考虑14号脚触发中断的情况，因为可能会因为14号脚未重置中断信号导致中断卡死
//	if(EXTI_GetITStatus(EXTI_Line14)==SET){
//		EXTI_ClearITPendingBit(EXTI_Line14);
//	}
}
