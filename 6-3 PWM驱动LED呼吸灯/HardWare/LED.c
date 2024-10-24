#include "stm32f10x.h"                  // Device header


//灯端口初始化，这跟之前的点灯操作是一样的，默认不让灯亮
void LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef InitStructure;
	InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	InitStructure.GPIO_Pin=GPIO_Pin_0;
	InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

//通过信息传递来控制开关灯
void LED_Operator(int state){
	//1表示开灯
	if(state==1){
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}
	//0表示关灯
	else{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	}
}

void LED_Turn(void){
	//如果此时灯灭
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==1){
		//就将灯调亮
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}
	//如果此时灯亮
	else{
		//就将灯调灭
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	}
}
