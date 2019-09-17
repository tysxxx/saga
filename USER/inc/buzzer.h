#ifndef __BUZZER_H
#define __BUZZER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef BUZZER_CONTROL
	#define BUZZER_EXTERN	extern
#else
	#define BUZZER_EXTERN 
#endif
	
#include "global.h"
    

void buzzerInit();
void buzzerControl();




































#ifdef __cplusplus
}
#endif
#endif
