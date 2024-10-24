#include "stm32f4xx.h"                  // Device header
#include "MyI2C.h"
#include "Serial.h"

#define MPU_ID 0x68<<1
#define MPU_OP 0x01

UART_HandleTypeDef huart;

extern void LED_Init(void);
//extern void Clock_Init(void);
extern void SYS_DELAY_MS(unsigned int milliseconds);
extern void SYSTICK_INIT(void);
extern void LED_ON(void);
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 84;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);


	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

}


int main(void)
{
	HAL_Init();
	SystemClock_Config();
//	uint8_t bit;
//	Clock_Init();
	My_I2C_Init();
	SYSTICK_INIT();
//	LED_Init();
//	My_I2C_Start();
//	My_I2C_W_Byte(MPU_ID);
//	bit = My_I2C_ReceiveACK();
//	
//	if(bit==0){
//		LED_ON();
//	}
	
	Serial_Init(115200);
	Serial_SendByte(0x44);
	while(1)
	{
		
	}
}
