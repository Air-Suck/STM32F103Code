#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"


int main(void){
	uint8_t KeyNum;
	//初始化LED和Key的两个端口
	LED_Init();
	Key_Init();
	//按钮按下时亮灯，按钮松开时熄灯
//	while(1){
//		KeyNum=Key_Has_Pressed();
//		//如果按钮正在按下状态，就将灯点亮
//		if(KeyNum==1){
//			LED_Operator(1);
//		}
//		//如果按钮不在按下状态，就将灯熄灭
//		else{
//			LED_Operator(0);
//		}
//	}
	//按钮按下灯的状态取反
	while(1){
		KeyNum=Key_Has_Pressed1();
		if(KeyNum==1){
			LED_Turn();
		}
	}
}
