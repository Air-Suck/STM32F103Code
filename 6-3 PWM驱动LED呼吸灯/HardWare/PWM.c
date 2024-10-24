#include "stm32f10x.h"                  // Device header

void PWM_Init(void){
	//1.RCC开启外设时钟
	//RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//RCC开启GPIO口用于输出PWM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//如果要将PA0引脚重映射为PA15引脚的话，要有下面的代码
//	//开启AFIO时钟来选择引脚
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	//第一个参数查手册可以看到复用的模式
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
//	//PA15引脚已经被作为了调试引脚
//	//所以这里要通过第一个参数关闭对应的调试模式，调试模式的对应关系查手册
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	//2.初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//配置滤波器，用来消除杂波
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	//配置计数模式，配置为上升计数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//下面两个参数和CCR（输入输出寄存器）共同决定PWM波的参数
	//这两个参数可以决定PWM的频率，频率越高PWM模拟效果越好，但是功耗越大
	//通常配置为1kHz
	//配置自动装载机阈值
	TIM_TimeBaseInitStruct.TIM_Period=100-1;
	//配置预分频器
	TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;
	//配置重复计数器，在高级时钟配置中会用到
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//3.选择时钟源，选择内部时钟
	TIM_InternalClockConfig(TIM2);
	
	//4.初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStruct;
	//这里需要使用复用推挽输出，将引脚控制权交给外设时钟
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//5.配置输出比较模块
	TIM_OCInitTypeDef TIM_OCInitStruct;
	//结构体中有许多参数是在使用高级时钟的时候才会使用
	//所以要通过结构体初始化函数为结构体赋一个初始值
	TIM_OCStructInit(&TIM_OCInitStruct);
	//输出比较模式配置为PWM1模式
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	//引脚极性配置为正极性（输入输出电平保持一致，反极性就是输入输出电平相反）
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	//时钟输出使能
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	//配置输入输出比较寄存器初值
	TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	
	//6.启动时钟
	TIM_Cmd(TIM2, ENABLE);
}

//封装改变CCR值的函数
void PWM_Set(int Num){
	TIM_SetCompare1(TIM2, Num);
}
