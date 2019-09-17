#ifndef __MOTOR_H
#define __MOTOR_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef MOTOR_CONTROL
	#define MOTOR_EXTERN	extern
#else
	#define MOTOR_EXTERN 
#endif
	
#include "global.h"

//
#define LEFT_BASE_MOTOR_COUNT_MAX   100 //
#define LEFT_BASE_MOTOR_COUNT_MIN   2

//左右纠偏电机
#define LEFT_ADJUST_MOTOR_PIN			     GPIO_Pin_14
#define LEFT_ADJUST_MOTOR_GPIO_PORT          GPIOD
#define LEFT_ADJUST_MOTOR_PIN_SET()          GPIO_SetBits(LEFT_ADJUST_MOTOR_GPIO_PORT, LEFT_ADJUST_MOTOR_PIN)
#define LEFT_ADJUST_MOTOR_PIN_RESET()        GPIO_ResetBits(LEFT_ADJUST_MOTOR_GPIO_PORT, LEFT_ADJUST_MOTOR_PIN)
#define GET_LEFT_ADJUST_MOTOR_PIN_STATUS     GPIO_ReadOutputDataBit(LEFT_ADJUST_MOTOR_GPIO_PORT, LEFT_ADJUST_MOTOR_PIN)
    //方向
#define LEFT_ADJUST_MOTOR_DIR_PIN            GPIO_Pin_10
#define LEFT_ADJUST_MOTOR_DIR_GPIO_PORT      GPIOD    
#define LEFT_ADJUST_MOTOR_DIR_PIN_SET()      GPIO_SetBits(LEFT_ADJUST_MOTOR_DIR_GPIO_PORT, LEFT_ADJUST_MOTOR_DIR_PIN)
#define LEFT_ADJUST_MOTOR_DIR_PIN_RESET()    GPIO_ResetBits(LEFT_ADJUST_MOTOR_DIR_GPIO_PORT, LEFT_ADJUST_MOTOR_DIR_PIN)    
    
#define RIGHT_ADJUST_MOTOR_PIN			     GPIO_Pin_15
#define RIGHT_ADJUST_MOTOR_GPIO_PORT         GPIOD
#define RIGHT_ADJUST_MOTOR_PIN_SET()         GPIO_SetBits(RIGHT_ADJUST_MOTOR_GPIO_PORT, RIGHT_ADJUST_MOTOR_PIN)
#define RIGHT_ADJUST_MOTOR_PIN_RESET()       GPIO_ResetBits(RIGHT_ADJUST_MOTOR_GPIO_PORT, RIGHT_ADJUST_MOTOR_PIN)      
#define GET_RIGHT_ADJUST_MOTOR_PIN_STATUS    GPIO_ReadOutputDataBit(RIGHT_ADJUST_MOTOR_GPIO_PORT, RIGHT_ADJUST_MOTOR_PIN)
    //方向
#define RIGHT_ADJUST_MOTOR_DIR_PIN            GPIO_Pin_11
#define RIGHT_ADJUST_MOTOR_DIR_GPIO_PORT      GPIOD    
#define RIGHT_ADJUST_MOTOR_DIR_PIN_SET()      GPIO_SetBits(RIGHT_ADJUST_MOTOR_DIR_GPIO_PORT, RIGHT_ADJUST_MOTOR_DIR_PIN)
#define RIGHT_ADJUST_MOTOR_DIR_PIN_RESET()    GPIO_ResetBits(RIGHT_ADJUST_MOTOR_DIR_GPIO_PORT, RIGHT_ADJUST_MOTOR_DIR_PIN) 

#define ADJUST_MOTOR_GPIO_PORT               GPIOD

//送纸电机
#define PAPER_MOTOR_POSITIVE_PIN             GPIO_Pin_9
#define PAPER_MOTOR_POSITIVE_GPIO_PORT       GPIOA
#define PAPER_MOTOR_POSITIVE_SET()           GPIO_SetBits(PAPER_MOTOR_POSITIVE_GPIO_PORT, PAPER_MOTOR_POSITIVE_PIN)
#define PAPER_MOTOR_POSITIVE_RESET()         GPIO_ResetBits(PAPER_MOTOR_POSITIVE_GPIO_PORT, PAPER_MOTOR_POSITIVE_PIN) 

#define PAPER_MOTOR_NEGATIVE_PIN             GPIO_Pin_14
#define PAPER_MOTOR_NEGATIVE_GPIO_PORT       GPIOB
#define PAPER_MOTOR_NEGATIVE_SET()           GPIO_SetBits(PAPER_MOTOR_NEGATIVE_GPIO_PORT, PAPER_MOTOR_NEGATIVE_PIN)
#define PAPER_MOTOR_NEGATIVE_RESET()         GPIO_ResetBits(PAPER_MOTOR_NEGATIVE_GPIO_PORT, PAPER_MOTOR_NEGATIVE_PIN)

//送纸传感器
#define PAPER_LIMIT_PIN                     GPIO_Pin_4
#define PAPER_LIMIT_GPIO_PORT               GPIOD
#define GET_PAPER_LIMIT_STATUS()            GPIO_ReadInputDataBit(PAPER_LIMIT_GPIO_PORT, PAPER_LIMIT_PIN)

//摄像头电机
#define CAMERA_MOTOR_STEP_PIN			    GPIO_Pin_4
#define CAMERA_MOTOR_EN_PIN					GPIO_Pin_5
#define CAMERA_MOTOR_DIR_PIN			    GPIO_Pin_6
#define CAMERA_MOTOR_SLEEP_PIN			    GPIO_Pin_7    
#define CAMERA_MOTOR_PORT                   GPIOC

#define CAMERA_MOTOR_VREF_PIN			    GPIO_Pin_10 //设置参考电压
#define CAMERA_MOTOR_VREF_PORT              GPIOA

#define CAMERA_MOTOR_STEP_SET()             GPIO_SetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_STEP_PIN)
#define CAMERA_MOTOR_STEP_RESET()           GPIO_ResetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_STEP_PIN)
#define CAMERA_MOTOR_STEP_PIN_STATUS()      GPIO_ReadOutputDataBit(CAMERA_MOTOR_PORT, CAMERA_MOTOR_STEP_PIN)

#define CAMERA_MOTOR_ENABLE()               GPIO_ResetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_EN_PIN)
#define CAMERA_MOTOR_DISABLE()              GPIO_SetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_EN_PIN)
#define CAMERA_MOTOR_SLEEP()                GPIO_ResetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_SLEEP_PIN)
#define CAMERA_MOTOR_UNSLEEP()              GPIO_SetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_SLEEP_PIN)
#define CAMERA_MOTOR_DIR_POSITIVE()         GPIO_ResetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_DIR_PIN)
#define CAMERA_MOTOR_DIR_NEGATIVE()         GPIO_SetBits(CAMERA_MOTOR_PORT, CAMERA_MOTOR_DIR_PIN)
#define CAMERA_MOTOR_DIR(a)                 if((a))CAMERA_MOTOR_DIR_POSITIVE();else CAMERA_MOTOR_DIR_NEGATIVE()

#define CAMERA_MOTOR_VREF_SET()             GPIO_SetBits(CAMERA_MOTOR_VREF_PORT, CAMERA_MOTOR_VREF_PIN)
#define CAMERA_MOTOR_VREF_RESET()           GPIO_ResetBits(CAMERA_MOTOR_VREF_PORT, CAMERA_MOTOR_VREF_PIN)

    //摄像头传感器
#define CAMERA_LIMIT_PIN                    GPIO_Pin_5
#define CAMERA_LIMIT_GPIO_PORT              GPIOD
#define GET_CAMERA_LIMIT_STATUS()           GPIO_ReadInputDataBit(CAMERA_LIMIT_GPIO_PORT, CAMERA_LIMIT_PIN)

//切割电机
    //切割移动电机
#define CUT_MOVE_MOTOR_PIN			        GPIO_Pin_12
#define CUT_MOVE_MOTOR_GPIO_PORT            GPIOD
#define CUT_MOVE_MOTOR_PIN_SET()            GPIO_SetBits(CUT_MOVE_MOTOR_GPIO_PORT, CUT_MOVE_MOTOR_PIN)
#define CUT_MOVE_MOTOR_PIN_RESET()          GPIO_ResetBits(CUT_MOVE_MOTOR_GPIO_PORT, CUT_MOVE_MOTOR_PIN)
#define GET_CUT_MOVE_MOTOR_PIN_STATUS()       GPIO_ReadOutputDataBit(CUT_MOVE_MOTOR_GPIO_PORT, CUT_MOVE_MOTOR_PIN)
    //方向
#define CUT_MOVE_MOTOR_DIR_PIN              GPIO_Pin_8
#define CUT_MOVE_MOTOR_DIR_GPIO_PORT        GPIOD    
#define CUT_MOVE_MOTOR_DIR_PIN_SET()        GPIO_SetBits(CUT_MOVE_MOTOR_DIR_GPIO_PORT, CUT_MOVE_MOTOR_DIR_PIN)
#define CUT_MOVE_MOTOR_DIR_PIN_RESET()      GPIO_ResetBits(CUT_MOVE_MOTOR_DIR_GPIO_PORT, CUT_MOVE_MOTOR_DIR_PIN)
#define CUT_MOVE_MOTOR_DIR(a)               if((a))CUT_MOVE_MOTOR_DIR_PIN_SET();else CUT_MOVE_MOTOR_DIR_PIN_RESET()

    //切割传感器
#define CUT_LIMIT_PIN                       GPIO_Pin_6
#define CUT_LIMIT_GPIO_PORT                 GPIOD
#define GET_CUT_LIMIT_STATUS()              GPIO_ReadInputDataBit(CUT_LIMIT_GPIO_PORT, CUT_LIMIT_PIN)

    //切割滚动电机
#define CUT_ROLL_MOTOR_PIN			        GPIO_Pin_13
#define CUT_ROLL_MOTOR_GPIO_PORT            GPIOD
#define CUT_ROLL_MOTOR_PIN_SET()            GPIO_SetBits(CUT_ROLL_MOTOR_GPIO_PORT, CUT_ROLL_MOTOR_PIN)
#define CUT_ROLL_MOTOR_PIN_RESET()          GPIO_ResetBits(CUT_ROLL_MOTOR_GPIO_PORT, CUT_ROLL_MOTOR_PIN)
#define GET_CUT_ROLL_MOTOR_PIN_STATUS()     GPIO_ReadOutputDataBit(CUT_ROLL_MOTOR_GPIO_PORT, CUT_ROLL_MOTOR_PIN)
    //方向
#define CUT_ROLL_MOTOR_DIR_PIN              GPIO_Pin_9
#define CUT_ROLL_MOTOR_DIR_GPIO_PORT        GPIOD    
#define CUT_ROLL_MOTOR_DIR_PIN_SET()        GPIO_SetBits(CUT_ROLL_MOTOR_DIR_GPIO_PORT, CUT_ROLL_MOTOR_DIR_PIN)
#define CUT_ROLL_MOTOR_DIR_PIN_RESET()      GPIO_ResetBits(CUT_ROLL_MOTOR_DIR_GPIO_PORT, CUT_ROLL_MOTOR_DIR_PIN) 
#define CUT_ROLL_MOTOR_DIR(a)               if((a))CUT_ROLL_MOTOR_DIR_PIN_SET();else CUT_ROLL_MOTOR_DIR_PIN_RESET()

#define CUT_MOTOR_GPIO_PORT                 GPIOD

typedef enum MOTORSPEEDLEVEL_T
{
  motorSpeedLevel1,
  motorSpeedLevel2,
  motorSpeedLevel3,
  motorSpeedLevel4,
  motorSpeedLevel5    
}MotorSpeedLevel_t;

MOTOR_EXTERN MotorSpeedLevel_t motorSpeedLevel;
    
typedef enum MOTOR_STATUS{
    MOTOR_START,
    MOTOR_ACCEL,
    MOTOR_RUN,
    MOTOR_DECEL,
    MOTOR_STOP
}MOTOR_STATUS_TYPE;

typedef enum PAPERSTATUS{
    IDLE_PAPER_STATUS,
    NO_PAPER_STATUS,
    HAS_PAPER_STATUS,
}PAPER_STATUS_TYPE;


typedef enum cameraMotorStatus_t{
    CAMERA_RESET_IDLE_STATUS = 1,
    CAMERA_BACKMOVE_STATUS,
    CAMERA_STOPWAIT_STATUS,
    CAMERA_MOVEORIGIN_STATUS,
    CAMERA_RESET_STATUS, //上电复位状态
    CAMERA_READY_STATUS,
    CAMERA_STARTFIND_STATUS,
    CAMERA_HADFOUND_STATUS,
    CAMERA_RUNING_STATUS,
    CAMERA_STOP_STATUS,
}CameraMotorStatus_type;

typedef enum cutMotorStatus_t{
		CUT_RESET_IDLE_STATUS = 1,
    CUT_BACKMOVE_STATUS,
    CUT_STOPWAIT_STATUS,
    CUT_MOVEORIGIN_STATUS,
    CUT_READY_STATUS,
    CUT_STARTFIND_STATUS,
    CUT_HADFOUND_STATUS,
    CUT_RUNING_STATUS,
    CUT_STOP_STATUS,
}CutMotorStatus_type;

MOTOR_EXTERN MOTOR_STATUS_TYPE leftMotorStatus;
MOTOR_EXTERN MOTOR_STATUS_TYPE rightMotorStatus;

MOTOR_EXTERN CameraMotorStatus_type cameraMotorStatus;
MOTOR_EXTERN CutMotorStatus_type cutMoveMotorStatus;

MOTOR_EXTERN BOOL f_cameraMotorStatus;
MOTOR_EXTERN BOOL f_cameraMotorStop;

MOTOR_EXTERN BOOL leftMotorEnable;
MOTOR_EXTERN BOOL rightMotorEnable;
MOTOR_EXTERN BOOL CameraMotorRunEnable;
MOTOR_EXTERN BOOL CameraMotorStopEnable;
MOTOR_EXTERN BOOL rollMotorEnable;

#define MOTOR_RESOLUTION    1600
#define ONESTEP_DISTANCE    22.9/(MOTOR_RESOLUTION)  //电机转一步对应纸张的距离
#define MOTOR_SPEED(T)      ONESTEP_DISTANCE/(T)       //电机速度  T脉冲周期

MOTOR_EXTERN uint32_t leftMotorCurPeriod; //当前周期
MOTOR_EXTERN uint32_t rightMotorCurPeriod;

MOTOR_EXTERN uint32_t leftMotorDstPeriod; //目标周期
MOTOR_EXTERN uint32_t rightMotorDstPeriod;

MOTOR_EXTERN uint32_t leftMotorCurSpeed;
MOTOR_EXTERN uint32_t rightMotorCurSpeed;

MOTOR_EXTERN uint32_t leftMotorCurPeriodIndex;
MOTOR_EXTERN uint32_t rightMotorCurPeriodIndex;

MOTOR_EXTERN uint32_t CameraMotorCurPeriod;
MOTOR_EXTERN uint32_t CameraMotorDstPeriod;
MOTOR_EXTERN uint32_t cameraMotorCurPeriodIndex;
MOTOR_EXTERN uint32_t cameraMotorDstPeriodIndex;

MOTOR_EXTERN uint32_t cutRollMotorCurPeriod;
MOTOR_EXTERN uint32_t cutRollMotorDstPeriod;
MOTOR_EXTERN uint32_t cutRollMotorCurPeriodIndex;
MOTOR_EXTERN uint32_t cutRollMotorCurSpeed;

//摄像头电机
#define CAMERA_MOTOR_MAX_RANG   78800 
MOTOR_EXTERN BOOL f_cameraMotorStart;
MOTOR_EXTERN uint8_t cameraMotroDir;
MOTOR_EXTERN int32_t cameraPosition;
MOTOR_EXTERN int32_t cameraOriginPosition;
MOTOR_EXTERN int32_t cameraMotorRange; //总量程
MOTOR_EXTERN BOOL f_cameraCheckEnable;
MOTOR_EXTERN uint8_t validCount;


//切割电机
#define CUT_MOVE_MOTOR_MAX_RANG   0xabe0
MOTOR_EXTERN BOOL cutMoveMotorRunEnable;
MOTOR_EXTERN BOOL cutMoveMotorStopEnable;
MOTOR_EXTERN uint32_t cutMoveMotorCurPeriod;
MOTOR_EXTERN uint32_t cutMoveMotorDstPeriod;
MOTOR_EXTERN uint32_t cutMoveMotorCurPeriodIndex;
MOTOR_EXTERN uint32_t ccutMoveMotorDstPeriodIndex;

MOTOR_EXTERN uint8_t cutMoveMotroDir;
MOTOR_EXTERN int32_t cutMoveMotorPosition;
MOTOR_EXTERN int32_t cutMoveMotorOriginPosition;
MOTOR_EXTERN int32_t cutMoveMotorRange;
MOTOR_EXTERN BOOL f_cutMoveMotorStop;

//
MOTOR_EXTERN uint16_t paperMotorTime;
MOTOR_EXTERN BOOL f_paperMotorStart;
MOTOR_EXTERN BOOL f_paperMotorEnd;
MOTOR_EXTERN BOOL f_paperMotorTime;
MOTOR_EXTERN PAPER_STATUS_TYPE paperStatus;


uint32_t calculatePeriodBySpeed(uint32_t speed);
uint32_t calculateSpeedByPeriod(uint32_t period);
void motorInit();
void leftMotorControl(MOTOR_STATUS_TYPE status, uint32_t speed);
void rightMotorControl(MOTOR_STATUS_TYPE status, uint32_t speed);
void cameraMotorHandler();
void cameraLimitHandler();
void paperLimitHandler();
void cutLimitHandler();
void cameraMotorAxisMoveRel(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed);
void cameraMotorInterruptHandler();
void cameraMotorResetHandler();
void setCameraMotor(uint32_t curPeriodIndex, uint32_t dstPeriodIndex, uint8_t motorStatus);
void setCutMoveMotor(uint32_t speed, uint8_t motorStatus);
void cutMotorResetHandler();

#ifdef __cplusplus
}
#endif
#endif
