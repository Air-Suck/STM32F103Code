#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void){
	OLED_Init();
	
	//数据的显示都是覆盖的模式，每次输出都会将先前该位置的数据覆盖
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"Hello World!");
	//若位数小于实际位数，将舍弃高位；若位数大于实际位数，将在高位补0(所有数字类的显示都是如此)
	OLED_ShowNum(2,1,12345,5);
	OLED_ShowSignedNum(2,7,-66,2);
	OLED_ShowHexNum(3,1,0xAA55,4);
	OLED_ShowBinNum(4,1,0xAA55,16);
	
	Delay_s(10);
	//清屏
	OLED_Clear();
	
	while(1){
		
	}
}
