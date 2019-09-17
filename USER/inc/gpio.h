#ifndef __GPIO_H
#define __GPIO_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef GPIO_CONTROL
	#define GPIO_EXTERN	extern
#else
	#define GPIO_EXTERN 
#endif

#include "global.h"
	
    
#define CAMERA_LED_PIN			     GPIO_Pin_0
#define CAMERA_LED_GPIO_PORT         GPIOB   
    
void gpioInit();







































#ifdef __cplusplus
}
#endif
#endif