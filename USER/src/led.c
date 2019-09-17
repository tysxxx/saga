

#define LED_CONTROL
#include "led.h"

//初始化灯的管脚
void ledInit()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}


//控制灯
void ledControl(LED_TYPE ledType, BOOL status)
{
    switch(ledType)
    {
        case RED:
            colorRed(status);
            break;
        case GREEN:
            colorGreen(status);
            break;
        case BLUE:
            colorBlue(status);
            break;
        case ALL_OFF:
            ColorOff();
            break;
        default:
            break;
    }
}
