#ifndef __LED_H
#define __LED_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LED_CONTROL
	#define LED_EXTERN	extern
#else
	#define LED_EXTERN 
#endif
	
#include "global.h"
    
//R G B
#define R_PIN									  			GPIO_Pin_15
#define R_GPIO_PORT											GPIOE
#define R_GPIO_CLK											RCC_APB2Periph_GPIOE

#define G_PIN									  			GPIO_Pin_13
#define G_GPIO_PORT										    GPIOE
#define G_GPIO_CLK											RCC_APB2Periph_GPIOE

#define B_PIN									  			GPIO_Pin_12
#define B_GPIO_PORT										    GPIOE
#define B_GPIO_CLK											RCC_APB2Periph_GPIOE

#define colorRed(status)  do {if(status) GPIO_SetBits(R_GPIO_PORT, R_PIN);\
                              else GPIO_ResetBits(R_GPIO_PORT, R_PIN);\
                          }while(0)
#define colorGreen(status)  do {if(status) GPIO_SetBits(G_GPIO_PORT, G_PIN);\
                              else GPIO_ResetBits(G_GPIO_PORT, G_PIN);\
                          }while(0)
#define colorBlue(status)  do {if(status) GPIO_SetBits(B_GPIO_PORT, B_PIN);\
                              else GPIO_ResetBits(B_GPIO_PORT, B_PIN);\
                          }while(0)
                              
#define ColorOff()  do {GPIO_ResetBits(R_GPIO_PORT, R_PIN);\
                        GPIO_ResetBits(G_GPIO_PORT, G_PIN);\
                        GPIO_ResetBits(B_GPIO_PORT, B_PIN);\
                    }while(0)                          
                          
typedef enum LED_TYPE_T{
    RED,
    GREEN,
    BLUE,
    ALL_OFF,
}LED_TYPE;
void ledInit();
void ledControl(LED_TYPE ledType, BOOL status);




































#ifdef __cplusplus
}
#endif
#endif
