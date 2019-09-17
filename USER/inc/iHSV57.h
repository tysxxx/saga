#ifndef __IHSV57_H
#define __IHSV57_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef IHSV57_CONTROL
	#define IHSV57_EXTERN	extern
#else
	#define IHSV57_EXTERN 
#endif
	
#include "global.h"

enum 
{
 	IDEL=0,       
 	FASTSEEK,     
	FASTSEEKSTOP, 
	FASTSEEKBACK, 
	SLOWSEEK,     
	SLOWSEEKSTOP, 
	MOVETOZERO    
};

typedef enum 
{
    CAMERA_MOTOR, //摄像头电机
    XCUT_MOTOR,   //横切刀电机
}MOTOR_TYPE;

typedef struct {
  uint8_t run_state ;//电机旋转状态
  uint8_t dir ;      //电机状态方向
  int32_t step_delay;//下一个脉冲周期(时间间隔),开始为加速度
  uint32_t decel_start;//开始减速的位置
  int32_t decel_val;//减速阶段的步数
  int32_t min_delay;//最小脉冲周期(最大速度, 即匀速时的速度)
  int32_t accel_count;//加减速阶段计数值
}speedRampData;

IHSV57_EXTERN speedRampData cameraMotor;
IHSV57_EXTERN speedRampData srd;
IHSV57_EXTERN speedRampData cutMotor;

typedef struct MOTOR_INFO{
    speedRampData srd;
    uint32_t accel; //设置加速度值
    uint32_t decel; //设置反加速度值
    uint32_t speed; //设置最大速度
    uint32_t max_s_lim; //达到最大速度时的步数
    uint32_t accel_lim; //必须开始减速的步数(如果加速没有达到最大速度)
    int32_t step; //需要移动步数
}motorInfoType;

typedef struct MOTOR_DEVICE{
    uint8_t numb;
    motorInfoType motorInfo;
    uint16_t new_step_delay; //保存下一个延时周期
    uint16_t last_accel_delay; // 加速过程中最后一次延时（脉冲周期）.
    uint32_t step_count;   // 总移动步数计数器  
    int32_t rest; // 记录new_step_delay中的余数，提高下一步计算的精度  
    uint8_t i;
    MOTOR_TYPE motorType;
}motorDeviceType;


IHSV57_EXTERN motorDeviceType motor1Device;
IHSV57_EXTERN motorDeviceType motor2Device;
IHSV57_EXTERN motorDeviceType motor3Device;
IHSV57_EXTERN motorDeviceType motor4Device;
IHSV57_EXTERN motorDeviceType cameraMotorDevice;
IHSV57_EXTERN motorDeviceType cutMoveMotorDevice;

IHSV57_EXTERN uint32_t pluseCount;
IHSV57_EXTERN uint32_t cutMoveMotorPluseCount;

IHSV57_EXTERN motorInfoType* motorInfo[4]; //电机的数目
IHSV57_EXTERN uint16_t motor1Delay, motor2Delay, motor3Delay, motor4Delay;
IHSV57_EXTERN BOOL f_motor1Start, f_motor2Start, f_motor3Start, f_motor4Start;

#define AXIS_TIMX_CLOCKCMD           RCC_APB1PeriphClockCmd
#define AXIS_TIMx_RCC_CLK            RCC_APB1Periph_TIM4
#define AXIS_TIMx                    TIM4
#define AXIS_TIMx_IRQn               TIM4_IRQn
#define AXIS_TIMx_IRQHandler         TIM4_IRQHandler
#define AXIS_TIMx_OCnInit            TIM_OC3Init
#define AXIS_TIM_SetCompareN         TIM_SetCompare3

#define AXIS_PULSE_CLK               RCC_APB2Periph_GPIOD
#define AXIS_PULSE_1                 GPIO_Pin_14       //脉冲输出引脚
#define AxisPulsePort                GPIOD

#define AXIS_DIR_CLK                 RCC_APB2Periph_GPIOD
#define AXIS_DIR_1                   GPIO_Pin_10        //方向控制引脚
#define AxisDirPort                  GPIOD
#define Axis_SETDIR_CW()             GPIO_SetBits(AxisDirPort, AXIS_DIR_1)
#define Axis_SETDIR_CCW()            GPIO_ResetBits(AxisDirPort, AXIS_DIR_1)

#define AXIS_LMTPOS_CLK              RCC_APB2Periph_GPIOC
#define AXIS_LMTPOS_1                GPIO_Pin_2        // 
#define AxisLmtPosPort               GPIOC

#define AXIS_LMTNEG_CLK              RCC_APB2Periph_GPIOC
#define AXIS_LMTNEG_1                GPIO_Pin_3        // 
#define AxisLmtNegPort               GPIOC

#define AXIS_HOME_CLK                RCC_APB2Periph_GPIOC
#define AXIS_HOME_1                  GPIO_Pin_4        // 
#define AxisHomePort                 GPIOC
#define AxisEXTI_PORTSource          GPIO_PortSourceGPIOC
#define AxisEXTIPinSource            GPIO_PinSource4
#define AxisEXTILine                 EXTI_Line4
#define AxisEXTI_IRQCHANNEL          EXTI4_IRQn
#define AxisEXTI_IRQHANDLER          EXTI4_IRQHandler

//电机脉冲管脚和方向管脚
#define MOTOR1_PULSE_PIN            GPIO_Pin_14
#define MOTOR1_PULSE_Port           GPIOD
#define MOTOR1_DIR_PIN              GPIO_Pin_10
#define MOTOR1_DIR_Port             GPIOD 
#define MOTOR1_DIR(dir)             do{ if(dir)\
                                            GPIO_SetBits(MOTOR1_DIR_Port, MOTOR1_DIR_PIN);\
                                        else    \
                                            GPIO_ResetBits(MOTOR1_DIR_Port, MOTOR1_DIR_PIN);\
                                    }while(0)

#define MOTOR2_PULSE_PIN            GPIO_Pin_15
#define MOTOR2_PULSE_Port           GPIOD
#define MOTOR2_DIR_PIN              GPIO_Pin_11
#define MOTOR2_DIR_Port             GPIOD                                    
#define MOTOR2_DIR(dir)             do{ if(dir)\
                                            GPIO_SetBits(MOTOR2_DIR_Port, MOTOR2_DIR_PIN);\
                                        else    \
                                            GPIO_ResetBits(MOTOR2_DIR_Port, MOTOR2_DIR_PIN);\
                                    }while(0)

#define MOTOR3_PULSE_PIN            GPIO_Pin_12
#define MOTOR3_PULSE_Port           GPIOD
#define MOTOR3_DIR_PIN              GPIO_Pin_8
#define MOTOR3_DIR_Port             GPIOD                                    
#define MOTOR3_DIR(dir)             do{ if(dir)\
                                            GPIO_SetBits(MOTOR3_DIR_Port, MOTOR3_DIR_PIN);\
                                        else    \
                                            GPIO_ResetBits(MOTOR3_DIR_Port, MOTOR3_DIR_PIN);\
                                    }while(0)

#define MOTOR4_PULSE_PIN            GPIO_Pin_13
#define MOTOR4_PULSE_Port           GPIOD
#define MOTOR4_DIR_PIN              GPIO_Pin_9
#define MOTOR4_DIR_Port             GPIOD                                    
#define MOTOR4_DIR(dir)             do{ if(dir)\
                                            GPIO_SetBits(MOTOR4_DIR_Port, MOTOR4_DIR_PIN);\
                                        else    \
                                            GPIO_ResetBits(MOTOR4_DIR_Port, MOTOR4_DIR_PIN);\
                                    }while(0)                                    
                                    
#define CAMERA_MOTOR_PULSE_PIN            GPIO_Pin_4
#define CAMERA_MOTOR_PULSE_Port           GPIOC
#define CAMERA_MOTOR_PULSE(dir)             do{ if(dir)\
                                            GPIO_SetBits(CAMERA_MOTOR_PULSE_Port, CAMERA_MOTOR_PULSE_PIN);\
                                        else    \
                                            GPIO_ResetBits(CAMERA_MOTOR_PULSE_Port, CAMERA_MOTOR_PULSE_PIN);\
                                        }while(0)                                     
//#define CAMERA_MOTOR_DIR_PIN              GPIO_Pin_6
//#define CAMERA_MOTOR_DIR_Port             GPIOC                                    
//#define CAMERA_MOTOR_DIR(dir)             do{ if(dir)\
//                                            GPIO_SetBits(CAMERA_MOTOR_DIR_Port, CAMERA_MOTOR_DIR_PIN);\
//                                        else    \
//                                            GPIO_ResetBits(CAMERA_MOTOR_DIR_Port, CAMERA_MOTOR_DIR_PIN);\
//                                        }while(0) 

#define POSITIVE	                   1       //正方向
#define NEGATIVE	                   0      //反方向

//
#define STEPMOTOR_TIM_PRESCALER               35

// 定义定时器周期，输出比较模式周期设置为0xFFFF
//#define STEPMOTOR_TIM_PERIOD                  0xFFFF

#define FALSE                                 0
#define TRUE                                  1
#define CW                                    0 // 顺时针
#define CCW                                   1 // 逆时针

#define STOP                                  0 // 加减速曲线状态：停止
#define ACCEL                                 1 // 加减速曲线状态：加速阶段
#define DECEL                                 2 // 加减速曲线状态：减速阶段
#define RUN                                   3 // 加减速曲线状态：匀速阶段
                                    
#define T1_FREQ                               (SystemCoreClock/(STEPMOTOR_TIM_PRESCALER+1)) // 频率ft值
#define FSPR                                  200         //步进电机单圈步数
#define MICRO_STEP                            1600        //步进电机驱动器细分数
#define SPR                                   (FSPR*MICRO_STEP)   //旋转一圈需要的脉冲数

// 数学常数
#define ALPHA                                 ((float)(2*3.14159/SPR))       // α= 2*pi/spr 步距角(一个脉冲的走动的距离)
#define A_T_x100                              ((float)(100*ALPHA*T1_FREQ))  
#define T1_FREQ_148                           ((float)((T1_FREQ*0.676)/100)) // 0.676为误差修正值
#define A_SQ                                  ((float)(2*10000000000*ALPHA)) 
#define A_x20000                              ((float)(2*10000*ALPHA))


extern int32_t  ZeroDir;
extern uint32_t accel;         //加速度
extern uint32_t decel;         //减速度


void iHSV57Init();
void cameraAxisMoveRel(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed);
void cutMotorAxisMoveRel(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed);
void AxisMoveRel(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed);

























#ifdef __cplusplus
}
#endif
#endif
