#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int main(void){
	OLED_Init();

	Encoder_Init();
	OLED_ShowString(1,3,"Hello World!");
	
	while(1){
		OLED_ShowNum(2,1,GetNum(),5);
	}
}
