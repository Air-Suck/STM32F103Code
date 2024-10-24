#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//流水灯（实际上就是反复点灯）
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	//通过按位或的方式初始化多个引脚，实际上每一个引脚对应一个二进制位
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	//Write函数中第二个参数实际上就是控制对应端口的编号，应该用十六进制来表示端口编号
	//GPIO_Write(GPIOA,~0x0001);
	//主循环中控制端口的输入输出
	while(1){
		/*让所有灯交替点亮熄灭,也可以将输入函数改为其他的函数
		比如write函数，适合处理所有端口
		*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	}
}
