#include "stm32f10x.h"                  // Device header
#include "Delay.h"


//按钮端口的初始化，初始化操作其实跟点灯操作的初始化端口是一样的
void Key_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	InitStructure.GPIO_Pin=GPIO_Pin_11;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitStructure);
}


//按下按钮灯亮，松开按钮灯灭
uint8_t Key_Has_Pressed(void){
	uint8_t KeyPress;
	//如果调用函数时按钮在按下状态（就是端口输入0低电平时），就将灯点亮
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0){
		//防抖，应该在按钮按下松开时都防抖的，但是这里想让按下时灯亮，松开时灯灭，所以只要前面防抖就好了
		Delay_ms(20);
		//传递信息
		KeyPress=1;
	}
	//如果调用函数时按钮不在按下状态（就是端口输入1高电平时），就不将灯点亮
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==1){
		//防抖，应该在按钮按下松开时都防抖的，但是这里想让按下时灯亮，松开时灯灭，所以只要前面防抖就好了
		Delay_ms(20);
		//传递信息
		KeyPress=0;
	}
	return KeyPress;
}
//每次按下按钮灯的状态取反
uint8_t Key_Has_Pressed1(void){
	uint8_t KeyPress=0;
	//如果调用函数时按钮按下了（就是端口输入0低电平时），就将灯的状态取反
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0){
		//按下按键时的防抖
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0);
		//按下按键后的防抖
		Delay_ms(20);
		//传递信息
		KeyPress=1;
	}
	return KeyPress;
}
