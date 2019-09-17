#ifndef __UTILITY_H
#define __UTILITY_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef UTILITY_CONTROL
	#define UTILITY_EXTERN	extern
#else
	#define UTILITY_EXTERN 
#endif
	
#include "global.h"

UTILITY_EXTERN uint32_t timeDelay;
    
void delayUs(uint32_t us);
void delayMs(uint32_t ms);
void sysTickInit();































#ifdef __cplusplus
}
#endif
#endif
