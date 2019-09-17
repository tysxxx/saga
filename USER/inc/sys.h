#ifndef __BORDER_H
#define __BORDER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYS_CONTROL
	#define SYS_EXTERN	extern
#else
	#define SYS_EXTERN 
#endif
	
#include "global.h"
    
typedef enum SYSTEM_STATUS_T
{
    SYSTEM_IDLE,
    SYSTEM_RESET,
    SYSTEM_START,
    SYSTEM_RUN,
    SYSTEM_STOP
}SystemStatus_t;

SYS_EXTERN SystemStatus_t systemStatus;
    
	
void sysClockInit();




































#ifdef __cplusplus
}
#endif
#endif