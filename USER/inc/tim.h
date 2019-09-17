#ifndef __TIM_H
#define __TIM_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIM_CONTROL
	#define TIM_EXTERN	extern
#else
	#define TIM_EXTERN 
#endif
	
#include "global.h"

TIM_EXTERN BOOL f_1ms;
TIM_EXTERN uint32_t time_1us;    
TIM_EXTERN uint32_t time_1ms;
TIM_EXTERN uint32_t time_20ms;
TIM_EXTERN uint32_t CCDTime;    
TIM_EXTERN uint32_t timer1Period;
TIM_EXTERN uint32_t timer2Period; 
TIM_EXTERN uint32_t timer3Period; 
TIM_EXTERN uint32_t timer4Period;     
    
void timInit();
void TIM1Init();
void TIM2Init();
void TIM3Init();    
void TIM4Init();
void setTIMxPeriod(TIM_TypeDef* TIMx, uint16_t period);

































#ifdef __cplusplus
}
#endif
#endif
