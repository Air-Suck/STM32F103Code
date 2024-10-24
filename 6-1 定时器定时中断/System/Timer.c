#include "stm32f10x.h"                  // Device header

void Timer_Init(void){
	//1.设置RCC外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//2.选择时钟源（选择TIM2来启动内部时钟控制，此时的频率由STM32控制）
	TIM_InternalClockConfig(TIM2);
	
	//3.配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//配置滤波器（这个滤波器用来判断接收的信号是否是稳定的信号）
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; 
	//配置计数器的计数模式(这里选择上升计数)
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//配置自动装载器（设定计数阈值）
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;
	//配置预分频器
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;
	//配置重复计数器（用于高级定时器）
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//这里将更新中断位重置，防止更新分频器的时候触发中断（重新通电后计数从0开始）
	//这里的函数是用在除中断函数外的地方用于重置标志位的
	//中断函数中使用的函数是TIM_ClearITPendingBit（）
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	//4.中断输出控制
	//第一个参数选择时钟
	//第二个参数选择中断模式，这里选择的是更新中断
	//第三个参数选择使能还是失能
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//5.配置中断的NVIC
	//选择优先组（配置抢占和响应的位数）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	//选择中断通道
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	//中断通道使能还是失能
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	//配置抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	//配置响应优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	
	//6.启动定时器
	TIM_Cmd(TIM2, ENABLE);
}
