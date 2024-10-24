#include "stm32f10x.h"                  // Device header
#include "Delay.h"


//按钮端口的初始化，初始化操作其实跟点灯操作的初始化端口是一样的
void Key_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	InitStructure.GPIO_Pin=GPIO_Pin_1;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&InitStructure);
}

//每次按下按钮灯的状态取反
uint8_t Key_Has_Pressed(void){
	uint8_t KeyPress=0;
	//如果调用函数时按钮按下了（就是端口输入0低电平时），就将灯的状态取反
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0){
		//按下按键时的防抖
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0);
		//按下按键后的防抖
		Delay_ms(20);
		//传递信息
		KeyPress=1;
	}
	return KeyPress;
}
