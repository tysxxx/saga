#include "motor.h"
#include "gpio.h"


//初始化GPIO
void gpioInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//使能端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
	//摄像头灯管脚
	GPIO_InitStruct.GPIO_Pin = CAMERA_LED_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAMERA_LED_GPIO_PORT, &GPIO_InitStruct);

	//摄像头限位管脚
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOD, &GPIO_InitStruct);
		
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource5 );
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource6);

	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line5 | EXTI_Line6;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}










