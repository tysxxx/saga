#define SYS_CONTROL
#include "sys.h"


//初始化时钟
void sysClockInit()
{
	ErrorStatus HSEStartUpStatus;
	//复位状态
	RCC_DeInit();

	//使能外部晶振
	RCC_HSEConfig(RCC_HSE_ON);

	//等待晶振稳定
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	if(SUCCESS == HSEStartUpStatus)
	{
		//AHB clock = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		//APB1 APB1 clock = HCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div2);
		
		//APB2 APB2 clock = HCLK/1
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//PLLCLK 8M*9=72M
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		
		//PLLCLK ENABLE
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//配置系统时钟源 72M
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		while(RCC_GetSYSCLKSource() != 0x08);
		
		RCC_ClockSecuritySystemCmd(ENABLE);
	}
	else{
		while(1)
		{
		}
	}
}