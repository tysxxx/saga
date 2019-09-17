
#define BUZZER_CONTROL
#include "buzzer.h"


void buzzerInit()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}


void buzzerControl()
{

}