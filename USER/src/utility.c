
#define UTILITY_CONTROL
#include "utility.h"

void delay_1us()
{ 
    uint8_t i = 1;
    //while(--i){
       __NOP;
    //}
}

//us延时
void delayUs(uint32_t us)
{
	for(uint16_t i=0; i < us; i++)
        delay_1us();
}


//ms延时
void delayMs(uint32_t ms)
{
    timeDelay = 10*ms;
	while(timeDelay !=0);
}


//系统滴答时钟初始化
//时钟源AHB
void sysTickInit()
{
	/*
		SystemCoreClock/1000  1ms
		SystemCoreClock/100000 10us
		SystemCoreClock/1000000 1us
	*/
	if(SysTick_Config(SystemCoreClock/10000)) //100us
	{
		while(1);
	}
}