#ifndef __MYIIC_H
#define __MYIIC_H

typedef uint8_t u8;

void My_I2C_Init(void);
void My_I2CSCL_W_Bit(u8 WriteBit);
void My_I2CSDA_W_Bit(u8 WriteBit);
uint8_t My_I2CSDA_R_Bit(void);
void My_I2C_Start(void);
void My_I2C_Stop(void);
void My_I2C_W_Byte(u8 Data);
u8 My_I2C_R_Byte(void);
void My_I2C_SendACK(u8 ACKBit);
u8 My_I2C_ReceiveACK(void);

#endif
