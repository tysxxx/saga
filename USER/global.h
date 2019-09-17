#ifndef __GLOBAL_H
#define __GLOBAL_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLOBAL_CONTROL
	#define GLOBAL_EXTERN	extern
#else
	#define GLOBAL_EXTERN 
#endif
	
#include "stm32f10x.h"

//基座电机
#define BASE_MOTOR_RESOLUTION       1600                //基座电机细分数
#define BASE_MOTOR_ONE_SETP_DISTANCE     22.9/1600           //基座电机移动一步的距离(mm)
#define BASE_MOTOR_STEPS(a)     (a)*1600/22.9       //根据距离移动步数(a为距离)
#define ONE_PIXEL_DISTANCE      5
#define ONE_PIXEL_STEP          BASE_MOTOR_STEPS(ONE_PIXEL_DISTANCE)//一个像素对应移动的距离

//摄像头电机
#define CAMERA_MOTOR_RESOLUTION   1600                //基座电机细分数
#define CAMERA_MOTOR_ONE_SETP     22.9/1600           //基座电机移动一步的距离(mm)
#define CAMERA_MOTOR_STEPS(a)     (a)*1600/22.9       //根据距离移动步数


typedef enum BOOL_T
{
   FALSE = 0,
   TRUE=!FALSE,
}BOOL;



























#ifdef __cplusplus
}
#endif
#endif
