#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num=10;

int main(void){
	Timer_Init();
	OLED_Init();
	
	while(1){
		OLED_ShowNum(1,1,Num,5);
		OLED_ShowNum(2,1,GetCountNum(),5);
	}
}

void TIM2_IRQHandler(void){
	//判断是否发生中断
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)==SET){
		Num++;
		//重置中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
