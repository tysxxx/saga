
#include "motor.h"
#define TIM_CONTROL
#include "tim.h"

//定时器初始化
void timInit()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7, ENABLE);
    
	//TIM1
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
    
	TIM_DeInit(TIM1);
	TIM_TimeBaseInitStruct.TIM_Period = 200-1;		    //周期(period+1)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;		//72M/(35+1)=2M
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
    
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;      
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct.TIM_Pulse = 50-1;						//占空比
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM1, &TIM_OCInitStruct);                   //参考电压
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 80-1;					
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC2Init(TIM1, &TIM_OCInitStruct);                   //灯管脚
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    
    //TIM2 72M
    /*360 100k
    /*600 60k
    *720 50k
    *1200 30k
    *720*2 25k
    *1800 20k
    *720*5 10k
    */
    timer2Period = 1800;//576;  //6-3600 ()
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitStruct.TIM_Period = 0x11e-1;//timer2Period-1;	//周期(period+1) 
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//0;		        //72M/(Prescaler+1)=72M
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    
    //TIM3
    timer3Period = 0x11e;
    TIM_DeInit(TIM3);
	TIM_TimeBaseInitStruct.TIM_Period = timer3Period-1;	
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    
    //TIM4
    TIM_DeInit(TIM4);
	TIM_TimeBaseInitStruct.TIM_Period = 0xffff-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);              
    
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    
    //TIM5
    TIM_DeInit(TIM5);
	TIM_TimeBaseInitStruct.TIM_Period = 0xffff-1;    
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
    
    //TIM_ARRPreloadConfig(TIM5, ENABLE);
    TIM_ClearFlag(TIM5, TIM_FLAG_Update);
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM5, ENABLE);
    
    //TIM6
    TIM_DeInit(TIM6);
	TIM_TimeBaseInitStruct.TIM_Period = 0xffff;    
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
    
    //TIM_ARRPreloadConfig(TIM6, ENABLE);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    //TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    
    
    //TIM7
		TIM_DeInit(TIM7);
		TIM_TimeBaseInitStruct.TIM_Period = 0xffff;    
		TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);

		TIM_ARRPreloadConfig(TIM7, ENABLE);
		TIM_ClearFlag(TIM7, TIM_FLAG_Update);
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM7, ENABLE);
}


//改变定时器的周期
void setTIMxPeriod(TIM_TypeDef* TIMx, uint16_t period)
{
    TIMx->ARR = period;
}













