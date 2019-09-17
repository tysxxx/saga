#ifndef __ADC_H
#define __ADC_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ADC_CONTROL
	#define ADC_EXTERN	extern
#else
	#define ADC_EXTERN 
#endif
	
#include "global.h"
    
#define ADC_GPIO_PORT    GPIOC
#define ADC_GPIO_PIN     GPIO_Pin_0

ADC_EXTERN uint16_t adcConversionValue;
ADC_EXTERN uint8_t f_adcConvSuccess;    
    
void adcInit();
void adcConfig();
uint16_t adcSample();
uint16_t adcAverageValue(uint8_t count);    


































#ifdef __cplusplus
}
#endif
#endif