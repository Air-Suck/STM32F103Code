#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure0;
	GPIO_InitStructure0.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure0.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure0.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure0);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
	//GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	//GPIO_Write(GPIOA,1);
	while(1){
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		Delay_ms(1000);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		Delay_ms(1000);
	}
}
