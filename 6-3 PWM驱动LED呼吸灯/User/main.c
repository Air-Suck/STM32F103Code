#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

int main(void){
	OLED_Init();
	//初始化PWM波的输出
	PWM_Init();

	uint16_t Num;
	while(1){
		//通过循环来调整CCR的值，即调整占空比，进而控制亮度
		for(Num=0;Num<=100;Num++){
			PWM_Set(Num);
			//防止灯呼吸过快
			Delay_ms(10);
		}
		for(Num=0;Num<=100;Num++){
			PWM_Set(100-Num);
			//防止灯呼吸过快
			Delay_ms(10);
		}
//		//无符号数与0比大小会报警告，所以不建议用这种办法,可以用向上递增然后作差的方法
//		for(;Num>=0;Num--){
//			TIM_SetCompare1(TIM2, Num);
//			Delay_ms(10);
//		}
	}
}
