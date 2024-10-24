#include "stm32f4xx.h"                  // Device header

//使用GPIOA pin1当做SCL，使用GPIOA pin2当做SDA
#define MY_SCL_PORT GPIOC
#define MY_SCL_PIN GPIO_PIN_10
#define MY_SDA_PORT GPIOC
#define MY_SDA_PIN GPIO_PIN_11
typedef uint8_t u8;


extern void SYS_DELAY_MS(unsigned int milliseconds);


void My_I2CSCL_W_Bit(u8 WriteBit){
	HAL_GPIO_WritePin(MY_SCL_PORT,MY_SCL_PIN,(GPIO_PinState)WriteBit);
	SYS_DELAY_MS(1);
}

void My_I2CSDA_W_Bit(u8 WriteBit){
	HAL_GPIO_WritePin(MY_SDA_PORT,MY_SDA_PIN,(GPIO_PinState)WriteBit);
	SYS_DELAY_MS(1);
}

void My_I2C_Start(void){
	//先拉高SDA是防止传输过程中的起始位（如果进入起始位的时候都是低电平）被判定成结束位
	My_I2CSDA_W_Bit(1);
	My_I2CSCL_W_Bit(1);
	My_I2CSDA_W_Bit(0);
	My_I2CSCL_W_Bit(0);
}

void My_I2C_Stop(void){
	My_I2CSDA_W_Bit(0);
	My_I2CSCL_W_Bit(1);
	My_I2CSDA_W_Bit(1);
}
//SCL和SDA初始化函数
void My_I2C_Init(void){
	//开启总线时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	HAL_GPIO_DeInit(MY_SCL_PORT,MY_SCL_PIN);/*将GPIOAPin1引脚恢复默认状态*/
	HAL_GPIO_DeInit(MY_SDA_PORT,MY_SDA_PIN);/*将GPIOAPin2引脚恢复默认状态*/
	//初始化SCL线
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_OD;/*开漏输出（开漏的情况下也可以读入数据）*/
	GPIO_InitStructure.Pin=MY_SCL_PIN;/*选中SCL引脚*/
	GPIO_InitStructure.Pull=GPIO_PULLUP;/*配置为上拉模式（输出弱上拉电平）,因为SCL和SDA引脚空闲状态都是高电平*/
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;/*高速*/
	HAL_GPIO_Init(MY_SCL_PORT,&GPIO_InitStructure);
	//初始化SDA线（除了引脚参数其他的应该都是一样的）
	GPIO_InitStructure.Pin=MY_SDA_PIN;/*选中SDA引脚*/
	HAL_GPIO_Init(MY_SDA_PORT,&GPIO_InitStructure);
	
	My_I2C_Stop();
}

u8 My_I2CSDA_R_Bit(void){
	u8 ReadBit;
	ReadBit=(u8)HAL_GPIO_ReadPin(MY_SDA_PORT,MY_SDA_PIN);
	SYS_DELAY_MS(1);
	return ReadBit;
}


void My_I2C_W_Byte(u8 Data){
	u8 i;
	for(i=0;i<8;i++){
		My_I2CSDA_W_Bit(Data&(0x80>>i));
		My_I2CSCL_W_Bit(1);
		My_I2CSCL_W_Bit(0);
	}
}

u8 My_I2C_R_Byte(void){
	u8 i,Data=0x00;
	//主机释放SDA
	My_I2CSDA_W_Bit(1);
	for(i=0;i<8;i++){
		//SCL置为高电平开始读取数据
		My_I2CSCL_W_Bit(1);
		if(My_I2CSDA_R_Bit()==1){
			Data|=(0x80>>i);
		}
		//SCL置为低电平开始给SDA线传输数据
		My_I2CSCL_W_Bit(0);
	}
	return Data;
}

void My_I2C_SendACK(u8 ACKBit){
	My_I2CSDA_W_Bit(ACKBit);
	My_I2CSCL_W_Bit(1);
	My_I2CSCL_W_Bit(0);
}

u8 My_I2C_ReceiveACK(void){
	u8 ACKBit;
	//主机释放SDA
	My_I2CSDA_W_Bit(1);
	//SCL置为高电平开始读取数据
	My_I2CSCL_W_Bit(1);
	ACKBit = My_I2CSDA_R_Bit();
	My_I2CSCL_W_Bit(0);
	return ACKBit;
}
