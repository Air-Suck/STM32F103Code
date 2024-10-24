#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Key.h"

int main(void){
	uint16_t Angle=0;   //5
	//初始化OLED、PWM、Key
	OLED_Init();
	PWM_Init();
	Key_Init();
	while(1){
		//当按键按下时
		if(Key_Has_Pressed()==1){
			OLED_ShowNum(1,1,Angle,5);
			PWM_AngleSet(Angle);
			//每次角度增加10度
			Angle+=10;
			//最大显示角度为180，上一次设置达到180时，这里判断的Angle就将变为190
			if(Angle>180){
				//设置为0是由Angle的类型（无符号）和封装的函数决定的
				Angle=0;
			}
			//未进行角度设置函数封装时
//			TIM_SetCompare1(TIM2,Angle);
//			Angle+=5;
//			if(Angle>25){
//				Angle=5;
//			}
		}
	}
}
