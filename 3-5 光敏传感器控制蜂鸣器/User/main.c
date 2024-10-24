#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "Light.h"

int main(void){
	uint8_t Data;
	Buzzer_Init();
	Light_Init();
	while(1){
		//此时Data就代表光敏电阻的传入值，Data只有1和0两种情况，代表蜂鸣器传入高电平和低电平
		Data=Light_Listen();
		//直接将Data值传给蜂鸣器操作函数即可，传入高电平时蜂鸣器关闭，传入低电平时蜂鸣器打开
		Buzzer_Operator(Data);
	}
}
