#ifndef __BORDER_H
#define __BORDER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef BORDER_CONTROL
	#define BORDER_EXTERN	extern
#else
	#define BORDER_EXTERN 
#endif
	
#include "global.h"


//
#define LIMIT0_PIN											GPIO_Pin_5
#define LIMIT0_GPIO_PORT									GPIOE
#define LIMIT0_GPIO_CLK										RCC_APB2Periph_GPIOE 

#define LIMIT1_PIN											GPIO_Pin_4
#define LIMIT1_GPIO_PORT									GPIOE
#define LIMIT1_GPIO_CLK                  	                RCC_APB2Periph_GPIOE

#define LIMIT2_PIN												GPIO_Pin_3
#define LIMIT2_GPIO_PORT									GPIOE
#define LIMIT2_GPIO_CLK										RCC_APB2Periph_GPIOE 

#define LIMIT3_PIN												GPIO_Pin_2
#define LIMIT3_GPIO_PORT									GPIOE
#define LIMIT3_GPIO_CLK										RCC_APB2Periph_GPIOE

#define LIMIT4_PIN												GPIO_Pin_7
#define LIMIT4_GPIO_PORT									GPIOD
#define LIMIT4_GPIO_CLK										RCC_APB2Periph_GPIOD

#define LIMIT5_PIN												GPIO_Pin_6
#define LIMIT5_GPIO_PORT									GPIOD
#define LIMIT5_GPIO_CLK										RCC_APB2Periph_GPIOD

#define LIMIT6_PIN												GPIO_Pin_5
#define LIMIT6_GPIO_PORT									GPIOD
#define LIMIT6_GPIO_CLK										RCC_APB2Periph_GPIOD

#define LIMIT7_PIN												GPIO_Pin_4
#define LIMIT7_GPIO_PORT									GPIOD
#define LIMIT7_GPIO_CLK										RCC_APB2Periph_GPIOD

#if 0
//CAMER
#define CAM_ADC_PIN												GPIO_Pin_0
#define CAM_ADC_GPIO_PORT									GPIOC
#define CAM_ADC_GPIO_CLK									RCC_APB2Periph_GPIOC

#define CAM_IO_PIN												GPIO_Pin_1
#define CAM_IO_GPIO_PORT									GPIOC
#define CAM_IO_GPIO_CLK										RCC_APB2Periph_GPIOC

//BEEP
#define BEEP_PIN													GPIO_Pin_6
#define BEEP_GPIO_PORT										GPIOE
#define BEEP_GPIO_CLK											RCC_APB2Periph_GPIOE 

//A
#define A1_PIN														GPIO_Pin_6
#define A1_GPIO_PORT											GPIOC
#define A1_GPIO_CLK												RCC_APB2Periph_GPIOC 	

#define A2_PIN														GPIO_Pin_7
#define A2_GPIO_PORT											GPIOC
#define A2_GPIO_CLK												RCC_APB2Periph_GPIOC

#define A3_PIN														GPIO_Pin_8
#define A3_GPIO_PORT											GPIOC
#define A3_GPIO_CLK												RCC_APB2Periph_GPIOC

#define A4_PIN														GPIO_Pin_9
#define A4_GPIO_PORT											GPIOC
#define A4_GPIO_CLK												RCC_APB2Periph_GPIOC

#define A5_PIN														GPIO_Pin_10
#define A5_GPIO_PORT											GPIOC
#define A5_GPIO_CLK												RCC_APB2Periph_GPIOC

#define A6_PIN														GPIO_Pin_11
#define A6_GPIO_PORT											GPIOC
#define A6_GPIO_CLK												RCC_APB2Periph_GPIOC

#define A7_PIN														GPIO_Pin_12
#define A7_GPIO_PORT											GPIOC
#define A7_GPIO_CLK												RCC_APB2Periph_GPIOC

#define A8_PIN														GPIO_Pin_0
#define A8_GPIO_PORT											GPIOD
#define A8_GPIO_CLK												RCC_APB2Periph_GPIOD

#define A9_PIN														GPIO_Pin_1
#define A9_GPIO_PORT											GPIOD
#define A9_GPIO_CLK												RCC_APB2Periph_GPIOD

#define A10_PIN														GPIO_Pin_2
#define A10_GPIO_PORT											GPIOD
#define A10_GPIO_CLK											RCC_APB2Periph_GPIOD

#define A11_PIN														GPIO_Pin_3
#define A11_GPIO_PORT											GPIOD
#define A11_GPIO_CLK											RCC_APB2Periph_GPIOD

#define A12_PIN														GPIO_Pin_3
#define A12_GPIO_PORT											GPIOB
#define A12_GPIO_CLK											RCC_APB2Periph_GPIOB

#define A13_PIN														GPIO_Pin_4
#define A13_GPIO_PORT											GPIOB
#define A13_GPIO_CLK											RCC_APB2Periph_GPIOB

#define A14_PIN														GPIO_Pin_5
#define A14_GPIO_PORT											GPIOB
#define A14_GPIO_CLK											RCC_APB2Periph_GPIOB

//MOTOR_DIR_IN
#define MOT1_DIR_IN_PIN									  GPIO_Pin_10
#define MOT1_DIR_IN_GPIO_PORT							GPIOD
#define MOT1_DIR_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

#define MOT2_DIR_IN_PIN									  GPIO_Pin_11
#define MOT2_DIR_IN_GPIO_PORT							GPIOD
#define MOT2_DIR_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

#define MOT3_DIR_IN_PIN									  GPIO_Pin_8
#define MOT3_DIR_IN_GPIO_PORT							GPIOD
#define MOT3_DIR_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

#define MOT4_DIR_IN_PIN									  GPIO_Pin_9
#define MOT4_DIR_IN_GPIO_PORT							GPIOD
#define MOT4_DIR_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

//MOTOR_PWM_IN
#define MOT1_PWM_IN_PIN									  GPIO_Pin_14
#define MOT1_PWM_IN_GPIO_PORT							GPIOD
#define MOT1_PWM_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

#define MOT2_PWM_IN_PIN									  GPIO_Pin_15
#define MOT2_PWM_IN_GPIO_PORT							GPIOD
#define MOT2_PWM_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

#define MOT3_PWM_IN_PIN									  GPIO_Pin_12
#define MOT3_PWM_IN_GPIO_PORT							GPIOD
#define MOT3_PWM_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

#define MOT4_PWM_IN_PIN									  GPIO_Pin_13
#define MOT4_PWM_IN_GPIO_PORT							GPIOD
#define MOT4_PWM_IN_GPIO_CLK							RCC_APB2Periph_GPIOD

//OUT
#define OUT0_PIN									  			GPIO_Pin_4
#define OUT0_GPIO_PORT										GPIOA
#define OUT0_GPIO_CLK											RCC_APB2Periph_GPIOA

#define OUT1_PIN									  			GPIO_Pin_5
#define OUT1_GPIO_PORT										GPIOA
#define OUT1_GPIO_CLK											RCC_APB2Periph_GPIOA

#define OUT2_PIN									  			GPIO_Pin_0
#define OUT2_GPIO_PORT										GPIOB
#define OUT2_GPIO_CLK											RCC_APB2Periph_GPIOB

#define OUT3_PIN									  			GPIO_Pin_1
#define OUT3_GPIO_PORT										GPIOB
#define OUT3_GPIO_CLK											RCC_APB2Periph_GPIOB

#define OUT4_PIN									  			GPIO_Pin_8
#define OUT4_GPIO_PORT										GPIOE
#define OUT4_GPIO_CLK											RCC_APB2Periph_GPIOE

#define OUT5_PIN									  			GPIO_Pin_9
#define OUT5_GPIO_PORT										GPIOE
#define OUT5_GPIO_CLK											RCC_APB2Periph_GPIOE

#define OUT6_PIN									  			GPIO_Pin_10
#define OUT6_GPIO_PORT										GPIOE
#define OUT6_GPIO_CLK											RCC_APB2Periph_GPIOE

#define OUT7_PIN									  			GPIO_Pin_11
#define OUT7_GPIO_PORT										GPIOE
#define OUT7_GPIO_CLK											RCC_APB2Periph_GPIOE

#define OUT8_PIN									  			GPIO_Pin_7
#define OUT8_GPIO_PORT										GPIOE
#define OUT8_GPIO_CLK											RCC_APB2Periph_GPIOE



//Y
#define Y_PIN									  			GPIO_Pin_14
#define Y_GPIO_PORT											GPIOE
#define Y_GPIO_CLK											RCC_APB2Periph_GPIOE


//encoder
#define XQEPA_PIN									  		  GPIO_Pin_0
#define XQEPA_GPIO_PORT										GPIOA
#define XQEPA_GPIO_CLK									  RCC_APB2Periph_GPIOA

#define XQEPB_PIN									  		  GPIO_Pin_1
#define XQEPB_GPIO_PORT										GPIOA
#define XQEPB_GPIO_CLK									  RCC_APB2Periph_GPIOA

#define YQEPA_PIN									  		  GPIO_Pin_6
#define YQEPA_GPIO_PORT										GPIOA
#define YQEPA_GPIO_CLK									  RCC_APB2Periph_GPIOA

#define YQEPB_PIN									  		  GPIO_Pin_7
#define YQEPB_GPIO_PORT										GPIOA
#define YQEPB_GPIO_CLK									  RCC_APB2Periph_GPIOA

//HB1
#define HB1_H_PIN									  		  GPIO_Pin_8
#define HB1_H_GPIO_PORT										GPIOA
#define HB1_H_GPIO_CLK									  RCC_APB2Periph_GPIOA

#define HB1_L_PIN									  		  GPIO_Pin_13
#define HB1_L_GPIO_PORT										GPIOB
#define HB1_L_GPIO_CLK									  RCC_APB2Periph_GPIOB

//HB2
#define HB2_H_PIN									  		  GPIO_Pin_9
#define HB2_H_GPIO_PORT										GPIOA
#define HB2_H_GPIO_CLK									  RCC_APB2Periph_GPIOA

#define HB2_L_PIN									  		  GPIO_Pin_14
#define HB2_L_GPIO_PORT										GPIOB
#define HB2_L_GPIO_CLK									  RCC_APB2Periph_GPIOB

//USB
#define USB_CS_PIN									  		GPIO_Pin_8
#define USB_CS_GPIO_PORT									GPIOA
#define USB_CS_GPIO_CLK									  RCC_APB2Periph_GPIOA


//RS485 RX TX
#define RS485_OE_PIN									  	GPIO_Pin_15
#define RS485_OE_GPIO_PORT								GPIOB
#define RS485_OE_GPIO_CLK									RCC_APB2Periph_GPIOB

#endif

//BUZZER
#define BUZZER_IN_PIN									  	GPIO_Pin_12
#define BUZZER_IN_GPIO_PORT								GPIOB
#define BUZZER_IN_GPIO_CLK								RCC_APB2Periph_GPIOB

//读取限位器的状态
#define limit0Check()           GPIO_ReadInputDataBit(LIMIT0_GPIO_PORT, LIMIT0_PIN)
#define limit1Check()           GPIO_ReadInputDataBit(LIMIT1_GPIO_PORT, LIMIT1_PIN)
#define limit2Check()           GPIO_ReadInputDataBit(LIMIT2_GPIO_PORT, LIMIT2_PIN)
#define limit3Check()           GPIO_ReadInputDataBit(LIMIT3_GPIO_PORT, LIMIT3_PIN)
#define limit4Check()           GPIO_ReadInputDataBit(LIMIT4_GPIO_PORT, LIMIT4_PIN)
#define limit5Check()           GPIO_ReadInputDataBit(LIMIT5_GPIO_PORT, LIMIT5_PIN)
#define limit6Check()           GPIO_ReadInputDataBit(LIMIT6_GPIO_PORT, LIMIT6_PIN)
#define limit7Check()           GPIO_ReadInputDataBit(LIMIT7_GPIO_PORT, LIMIT7_PIN)

//送纸电机
#define PAPERMOTOR_PERIOD 3600-1
#define PAPERMOTOR_DUTY PAPERMOTOR_PERIOD/2-1
#define paperLimitCheck()           GPIO_ReadInputDataBit(LIMIT7_GPIO_PORT, LIMIT7_PIN)

typedef enum PAPERSTATUS{
    idlePaperStatus,
    noPaperStatus,
    hasPaperStatus
}paperStatusType;

BORDER_EXTERN uint16_t paperMotorTime;
BORDER_EXTERN BOOL f_paperMotorStart;
BORDER_EXTERN BOOL f_paperMotorEnd;
BORDER_EXTERN BOOL f_paperMotorTime;
BORDER_EXTERN paperStatusType paperStatus;

void paperLimit();

//摄像头电机
#define cameraLimitCheck()           GPIO_ReadInputDataBit(LIMIT7_GPIO_PORT, LIMIT7_PIN)

BORDER_EXTERN BOOL f_cameraMotorCheckEnable;
BORDER_EXTERN BOOL f_cameraMotorStop;
BORDER_EXTERN BOOL F_camerMotorEnable;
BORDER_EXTERN uint16_t camerMotorDelay;
BORDER_EXTERN uint16_t camerMotorCount;



void borderInit();
void paperMotorDisable();
void paperMotorPositive();
void paperMotorNegative();







#ifdef __cplusplus
}
#endif
#endif