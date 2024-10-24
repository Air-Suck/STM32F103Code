;;点亮GPIOA_Pin0引脚的LED灯
;;1.初始化RCC外设时钟
;RCC_BASE				EQU		0x40021000;RCC的内存基地址（查手册）
;RCC_APB2ENR_OFFSET		EQU		0x18;RCC_APB2ENR相对于RCC基地址的偏移量（查手册）
;RCC_APB2ENR				EQU		RCC_BASE+RCC_APB2ENR_OFFSET;RCC_APB2ENR的内存地址
;RCC_APB2ENR_ENABLE 		EQU		0x4;使能RCC_APB2ENR的PortA（如何取值查手册）
;;2.初始化GPIOA端口
;GPIOA_BASE				EQU		0x40010800;GPIOA的内存基地址（查手册）
;GPIOA_OFFSET 			EQU		0x00;GPIOA初始化寄存器相对GPIOA基地址的偏移量
;GPIO_Init_AD			EQU		GPIOA_BASE+GPIOA_OFFSET;GPIOA初始化寄存器的内存地址
;GPIOA_ENABLE 			EQU		0x44444443;设置GPIOA_Pin0口为推挽输出，50MHz模式（如何取值查手册）
;;3.设置GPIOA_Pin0口的电平
;LED_OFFSET 				EQU		0x0C;GPIOA输出数据寄存器相对于GPIOA基地址的偏移量
;LED_AD					EQU		GPIOA_BASE+LED_OFFSET;GPIOA输出数据寄存器的内存地址
;LED_ON 					EQU		0;令GPIOA_Pin0口输出低电平
;LED_OFF 				EQU		1;令GPIOA_Pin0口输出高电平

	;AREA |.test|,CODE,READONLY,ALIGN=2;用于声明代码块，表示当前文本名称为.test,是code类型的代码，只能读取，并且半字对齐
					;THUMB;使用thumb指令集
					;ENTRY;程序的入口
					;EXPORT __main;表示其他文件可以访问该记号内容
;__main;主函数
			;BL 		GPIO_Init;跳转至GPIO_Init函数并且将当前函数的地址记录到LR寄存器中
;loop;函数结尾的死循环
			;B 		loop
			
;GPIO_Init;GPIO_Init函数
			;;LDR、STR指令只能通过寄存器存储的地址来进行内存寻址，所以每次都要将改变值的寄存器地址存入R0
			;;1.初始化RCC外设时钟
			;LDR R0,=RCC_APB2ENR;获取RCC_APB2ENR寄存器的地址用于供LDR、STR指令修改对应的值
			;LDR R1,=RCC_APB2ENR_ENABLE;用R1记录使能RCC_APB2ENR的寄存器取值
			;STR R1,[R0];使能RCC_APB2ENR
			;;2.初始化GPIOA端口Pin0引脚
			;LDR R0,=GPIO_Init_AD;获取GPIO_Init寄存器的地址用于供LDR、STR指令修改对应的值
			;LDR R1,=GPIOA_ENABLE;用R1记录使能GPIO_Init的寄存器取值
			;STR R1,[R0];使能GPIOA_Pin0
			;;3.设置GPIOA_Pin0口的电平
			;LDR R0,=LED_AD;获取GPIOA数据输出寄存器的地址用于供LDR、STR指令修改对应的值
			;LDR R1,=LED_OFF;用R1记录使端口输出高电平的寄存器取值
			;STR R1,[R0];使PA0引脚输出高电平
			
			;BX  LR;通过LR寄存器地址回到主函数
			
			;ALIGN;对齐伪指令
			;END;代码结束