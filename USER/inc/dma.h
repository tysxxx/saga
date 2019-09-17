#ifndef __DMA_H
#define __DMA_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef DMA_CONTROL
	#define DMA_EXTERN	extern
#else
	#define DMA_EXTERN 
#endif
	
#include "global.h"

#define ADC1_DR_Address    ((uint32_t)0x40012400+0x4c)
DMA_EXTERN uint16_t ADCConvertedValue;
	
#define UART2_DR_Address    ((uint32_t)0x40004400+0x04)
DMA_EXTERN uint8_t uart2SendValue[100];
DMA_EXTERN uint8_t uart2RecvValue;
	
void DMAInit();


































#ifdef __cplusplus
}
#endif
#endif