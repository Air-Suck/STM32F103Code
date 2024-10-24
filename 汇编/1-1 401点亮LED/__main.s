;各种基地址
RCC_BASE			EQU		0x40023800
GPIOA_BASE			EQU		0x40020000
TIM2_BASE			EQU		0x40000000
NVIC_BASE			EQU		0xE000E100

;使用GPIOA_Pin_5
;不能使用GPIOB_Pin_13是由于该口仅在使用F302板子的时候关闭（导通）
;RCC_AHB1ENR寄存器配置，使能GPIOA端口
RCC_AHB1ENR_OFFSET	EQU		0x30
RCC_AHB1_ENR		EQU		RCC_AHB1ENR_OFFSET+RCC_BASE
RCC_AHB1_GPIOA_ENR	EQU		1<<0
;GPIOx_MODER寄存器配置,将端口A设置为通用输出模式
GPIOA_MODER_OFFSET	EQU		0x00
GPIOA_MODER			EQU		GPIOA_BASE+GPIOA_MODER_OFFSET
GPIOA_PIN_OUTPUT	EQU		1<<10
;GPIOx_OTYPER寄存器配置，将端口A的输出类型改为推挽输出模式
GPIOA_OTYPER_OFFSET	EQU		0x04
GPIOA_OTYPER		EQU		GPIOA_BASE+GPIOA_OTYPER_OFFSET
GPIOA_MODE			EQU		~(1<<5)
;GPIOx_OSPEEDR寄存器配置，将端口A的输出速度改为高速模式
GPIOA_OSPEEDR_OFFSET	EQU		 0x08
GPIOA_OSPEEDR		EQU		GPIOA_BASE+GPIOA_OSPEEDR_OFFSET
GPIOA_HIGH			EQU		1<<11
;GPIOx_ODR寄存器设置，修改端口的输出电平	
GPIOA_ODR_OFFSET	EQU		0x14
GPIOA_ODR			EQU		GPIOA_BASE+GPIOA_ODR_OFFSET
LED_ON				EQU		1<<5
LED_OFF				EQU		~(1<<5)

;配置TIM2时钟
;外设时钟TIM2使能(TIM2是挂载在APB1外设总线上的
RCC_APB1_OFFSET		EQU		0x40
RCC_APB1			EQU		RCC_BASE+RCC_APB1_OFFSET
RCC_TIM2_ENR		EQU		1<<0;TIM2外设时钟使能
;配置时基单元(时基单元是在外设时钟内部的，输入的时钟频率为APB1总线的时钟频率)
;配置分频器
TIM2_PSC_OFFSET		EQU		0x28
TIM2_PSC			EQU		TIM2_BASE+TIM2_PSC_OFFSET
TIM2_PSC_CONFIG		EQU		8400-1
;配置自动装载值
TIM2_ARR_OFFSET		EQU		0x2C
TIM2_ARR			EQU		TIM2_ARR_OFFSET+TIM2_BASE
TIM2_ARR_CONFIG		EQU		10000-1
;配置计数器	
TIM2_CNT_OFFSET		EQU		0x24
TIM2_CNT			EQU		TIM2_BASE+TIM2_CNT_OFFSET
TIM2_CNT_CONFIG		EQU		0
;配置APB1总线的分频系数
RCC_CFGR_OFFSET		EQU		0x08
RCC_CFGR			EQU		RCC_BASE+RCC_CFGR_OFFSET
RCC_CFGR_CNF		EQU		1<<12
;配置时钟控制寄存器，选择计数模式并且使能时钟计数器开始计时
TIM2_CR1_OFFSET		EQU		0x00
TIM2_CR1			EQU		TIM2_CR1_OFFSET+TIM2_BASE
TIM2_CR1_UPCONT		EQU		~(1<<4);向上计数模式
TIM2_CR1_CEN		EQU		1<<0;计数器使能

;修改PLL_M的分频
;RCC_CR用于使能/失能PLL
SYS_CLK_HSI			EQU		0x03
RCC_CR_OFFSET		EQU		0x00
RCC_CR				EQU		RCC_BASE+RCC_CR_OFFSET
PLL_DISABLE			EQU		1<<24
PLL_M_DIV8			EQU		0x8
SYS_CLK_PLL			EQU		1<<1
PLL_ENABLE			EQU		1<<24
;RCC_PLLCFGR用于配置PLL的参数
RCC_PLLCFGR_OFFSET	EQU		0x04
RCC_PLLCFGR			EQU		RCC_BASE+RCC_PLLCFGR_OFFSET

;时钟的更新中断使能
TIM2_DIER_OFFSET	EQU		0x0C
TIM2_DIER			EQU		TIM2_BASE+TIM2_DIER_OFFSET
TIM2_UI_EN			EQU		1<<0
;更新中断标志清除（发生一次计数器更新时TIM2的状态寄存器的更新中断位会被置为1）
TIM2_SR_OFFSET		EQU		0x10
TIM2_SR				EQU		TIM2_BASE+TIM2_SR_OFFSET
TIM2_SR_UIF_CLEAR	EQU		~(1<<0)
TIM2_UIF_FLAG		EQU		0x01
;使能NVIC通道
NVIC_ISER0_OFFSET	EQU		0;手册上的OFFSTE很怪
NVIC_ISER0			EQU		NVIC_BASE+NVIC_ISER0_OFFSET
NVIC_TIM2_EN		EQU		1<<28


GPIOA_BSRR			EQU		GPIOA_BASE+0x18



				AREA	|.test|,CODE,READONLY,ALIGN=2
				THUMB
				ENTRY
				EXPORT __main
__main
				BL	GPIOA_Init
				
				BL	TIM2_Init

loop			
				B	loop

;GPIOA的初始化
GPIOA_Init		PROC
				PUSH{R0,R1,LR}
				;使能GPIOA端口
				LDR R0,=RCC_AHB1_ENR
				LDR R1,[R0]
				ORR R1,#RCC_AHB1_GPIOA_ENR
				STR R1,[R0]
				;将端口模式修改为通用输出模式
				LDR R0,=GPIOA_MODER
				LDR R1,[R0]
				ORR R1,#GPIOA_PIN_OUTPUT
				STR R1,[R0]
				;将端口的输出类型修改为推挽输出
				LDR R0,=GPIOA_OTYPER
				LDR R1,[R0]
				AND R1,#GPIOA_MODE
				STR R1,[R0]
				;将端口的输出速度设置为高速
				LDR R0,=GPIOA_OSPEEDR
				LDR R1,[R0]
				ORR R1,#GPIOA_HIGH
				STR R1,[R0]
				
				POP{R0,R1,PC}

				ENDP
;中断函数
TIM2_IRQHandler	PROC
				EXPORT	TIM2_IRQHandler
				PUSH{R0,R1,R2,LR}
				
				LDR R0,=GPIOA_ODR
				;R1的值用于进行判断
				LDR R1,[R0]
				;R2的值用于后续的存储
				LDR	R2,[R0]
				AND	R1,#LED_ON
				CMP	R1,#LED_ON
				;IT指令用于条件判断和分支选择
				ITE	EQ
				;相等的情况下
				ANDEQ	R2,#LED_OFF
				;不相等的情况下
				ORRNE	R2,#LED_ON
				STR R2,[R0]
				
				;将更新中断的标志位清零
				LDR R0,=TIM2_SR
				LDR	R1,[R0]
				AND	R1,#TIM2_SR_UIF_CLEAR
				STR R1,[R0]
				
				POP{R0,R1,R2,PC}
				ENDP

;用于实现不使用中断闪烁的延时效果
__wait			PROC
				PUSH{R0,R1,LR}
				LDR R0,=TIM2_SR
lp				LDR	R1,[R0]
				AND	R1,#TIM2_UIF_FLAG
				CMP	R1,#0x00
				BEQ	lp
				
				LDR R0,=TIM2_SR
				LDR	R1,[R0]
				AND	R1,#TIM2_SR_UIF_CLEAR
				STR R1,[R0]
				
				POP{R0,R1,PC}
				
				ENDP



;TIM2的初始化
TIM2_Init		PROC
				PUSH{R0,R1,LR}
				;TIM2使能
				LDR	R0,=RCC_APB1
				LDR R1,[R0]
				ORR R1,#RCC_TIM2_ENR
				STR R1,[R0]
				;设置TIM2的分频器
				LDR	R0,=TIM2_PSC
				LDR R1,[R0]
				MOVW	R1,#TIM2_PSC_CONFIG;设置为8400-1
				STR R1,[R0]
				;设置TIM2的计数器
				LDR	R0,=TIM2_ARR
				LDR	R1,[R0]
				MOVW R1,#TIM2_ARR_CONFIG;设置为10000-1
				STR R1,[R0]
				;清空TIM2计数器的值
				LDR R0,=TIM2_CNT
				LDR R1,[R0]
				MOVW	R1,#TIM2_CNT_CONFIG
				STR R1,[R0]
				;设置APB1的预分频系数为2（实际上在启动文件中已经设置了）
				LDR	R0,=RCC_CFGR
				LDR	R1,[R0]
				ORR	R1,#RCC_CFGR_CNF
				STR	R1,[R0]
				
				BL	PLL_CNF;重新配置PLL
				
				;设置计数器的计数模式，并且启动计数器
				LDR R0,=TIM2_CR1
				LDR R1,[R0]
				AND	R1,#TIM2_CR1_UPCONT;默认是向上计数
				ORR R1,#TIM2_CR1_CEN
				STR R1,[R0]
				
				BL	IT_CNF
				
				POP{R0,R1,PC}
				ENDP

;中断配置
IT_CNF			PROC
				PUSH{R0,R1,LR}
				;更新中断使能
				LDR	R0,=TIM2_DIER
				LDR	R1,[R0]
				ORR	R1,#TIM2_UI_EN
				STR	R1,[R0]
				;还能NVIC的通道（这里简化了许多，没有设置中断优先级等）
				LDR	R0,=NVIC_ISER0
				LDR	R1,[R0]
				ORR	R1,#NVIC_TIM2_EN
				STR	R1,[R0]
				
				POP{R0,R1,PC}
				ENDP

;修改PLL详见子为博客
PLL_CNF			PROC
				PUSH{R0,R1,LR}
				;更换系统时钟源为内部时钟
				LDR	R0,=RCC_CFGR
				LDR	R1,[R0]
				BIC	R1,R1,#SYS_CLK_HSI
				STR	R1,[R0]
				;关闭PLL
				LDR	R0,=RCC_CR
				LDR	R1,[R0]
				BIC	R1,R1,#PLL_DISABLE
				STR	R1,[R0]
				;将PLL_M的分频修改为8
				LDR	R0,=RCC_PLLCFGR
				LDR	R1,[R0]
				BIC	R1,R1,#0x3F
				ORR	R1,#PLL_M_DIV8
				STR	R1,[R0]
				;将PLL选为系统时钟
				LDR	R0,=RCC_CFGR
				LDR	R1,[R0]
				ORR	R1,#SYS_CLK_PLL
				STR	R1,[R0]
				;使能PLL
				LDR	R0,=RCC_CR
				LDR	R1,[R0]
				ORR	R1,#PLL_ENABLE
				STR	R1,[R0]

				POP{R0,R1,PC}
				ENDP
				
				END
					