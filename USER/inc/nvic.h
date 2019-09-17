#ifndef __NVIC_H
#define __NVIC_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef NVIC_CONTROL
	#define NVIC_EXTERN	extern
#else
	#define NVIC_EXTERN 
#endif
	
#include "global.h"



void NVICInit();

































#ifdef __cplusplus
}
#endif
#endif
