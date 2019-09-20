#include "sys.h"
#include "cameraMotorConfig.h"
#include "motor_profile.h"
#include "cutMotorProfile.h"
#include "iHSV57.h"
#define MOTOR_CONTROL
#include "motor.h"


//初始化
void motorInit()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    //纠偏电机
		GPIO_InitStruct.GPIO_Pin = LEFT_ADJUST_MOTOR_PIN | RIGHT_ADJUST_MOTOR_PIN | LEFT_ADJUST_MOTOR_DIR_PIN | RIGHT_ADJUST_MOTOR_DIR_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ADJUST_MOTOR_GPIO_PORT, &GPIO_InitStruct);
    
    LEFT_ADJUST_MOTOR_PIN_RESET();
    LEFT_ADJUST_MOTOR_DIR_PIN_SET();
    RIGHT_ADJUST_MOTOR_PIN_RESET();
    RIGHT_ADJUST_MOTOR_DIR_PIN_SET();
    
    //送纸电机
    GPIO_InitStruct.GPIO_Pin = PAPER_MOTOR_POSITIVE_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(PAPER_MOTOR_POSITIVE_GPIO_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = PAPER_MOTOR_NEGATIVE_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(PAPER_MOTOR_NEGATIVE_GPIO_PORT, &GPIO_InitStruct);
    
    PAPER_MOTOR_POSITIVE_RESET();
    PAPER_MOTOR_NEGATIVE_RESET();
    
    //送纸传感器
    GPIO_InitStruct.GPIO_Pin = PAPER_LIMIT_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(PAPER_LIMIT_GPIO_PORT, &GPIO_InitStruct);
    
    //摄像头电机
		GPIO_InitStruct.GPIO_Pin = CAMERA_MOTOR_STEP_PIN | CAMERA_MOTOR_EN_PIN | CAMERA_MOTOR_DIR_PIN | CAMERA_MOTOR_SLEEP_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(CAMERA_MOTOR_PORT, &GPIO_InitStruct);

		GPIO_InitStruct.GPIO_Pin = CAMERA_MOTOR_VREF_PIN; //调整参考电压
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(CAMERA_MOTOR_VREF_PORT, &GPIO_InitStruct);
    
    CAMERA_MOTOR_STEP_RESET();
    CAMERA_MOTOR_DISABLE();
    CAMERA_MOTOR_SLEEP();
    CAMERA_MOTOR_DIR_NEGATIVE();
    cameraMotroDir = 0;
    
    //摄像头限位传感器
//    GPIO_InitStruct.GPIO_Pin = CAMERA_LIMIT_PIN;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //上拉输入
//    GPIO_Init(CAMERA_LIMIT_GPIO_PORT, &GPIO_InitStruct);
    
    //切割电机
		GPIO_InitStruct.GPIO_Pin = CUT_MOVE_MOTOR_PIN | CUT_MOVE_MOTOR_DIR_PIN | CUT_ROLL_MOTOR_PIN | CUT_ROLL_MOTOR_DIR_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(CUT_MOTOR_GPIO_PORT, &GPIO_InitStruct);
    
    //切割限位传感器
//    GPIO_InitStruct.GPIO_Pin = CUT_LIMIT_PIN;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(CUT_LIMIT_GPIO_PORT, &GPIO_InitStruct);
    
    CUT_MOVE_MOTOR_PIN_RESET();
    CUT_MOVE_MOTOR_DIR_PIN_RESET();
    CUT_ROLL_MOTOR_PIN_RESET();
    CUT_ROLL_MOTOR_DIR_PIN_SET();
    
    //other
    leftMotorEnable = FALSE;
    leftMotorCurPeriod = 0;
    f_cameraMotorStart = FALSE;
		cutMoveMotorPosition = 0;
		
    cameraMotor.run_state = STOP;
    cameraMotor.dir  = 0;    
    cameraMotor.step_delay = 0;
    cameraMotor.decel_start = 0;
    cameraMotor.decel_val = 0;
    cameraMotor.min_delay = 0;
    cameraMotor.accel_count = 0;
}

//根据速度计算对应的周期时间
uint32_t calculatePeriodBySpeed(uint32_t speed)
{
    if(speed == 0)
        speed = 1;
    uint32_t tmp1 = 22.9*1000000;
    uint32_t tmp2 = speed*2*MOTOR_RESOLUTION;
    uint32_t ret = tmp1/tmp2;
    if(ret < 5)
        ret = 5;
    if(ret > motor_profile[0])
        ret = motor_profile[0];
    return ret;
}

//根据周期得到当前的速度值
uint32_t calculateSpeedByPeriod(uint32_t period)
{
    uint32_t tmp1 = 22.9*1000000;
    uint32_t tmp2 = period*2*MOTOR_RESOLUTION;
    uint32_t ret = tmp1/tmp2;
    if(ret > 1400)
        ret = 1400;
    return ret;
}


//左边电机
void leftMotorControl(MOTOR_STATUS_TYPE status, uint32_t speed)
{
    switch(status)
    {
        case MOTOR_START: //启动时设置
            leftMotorCurPeriodIndex = 1;
            leftMotorCurPeriod = motor_profile[leftMotorCurPeriodIndex];
            leftMotorDstPeriod = calculatePeriodBySpeed(speed);
            leftMotorEnable = TRUE;
            break;
        case MOTOR_RUN:
            leftMotorDstPeriod = calculatePeriodBySpeed(speed);
            break;
        case MOTOR_STOP:
            leftMotorDstPeriod = motor_profile[0];
            break;
    }
}

//右边电机
void rightMotorControl(MOTOR_STATUS_TYPE status, uint32_t speed)
{
    switch(status)
    {
        case MOTOR_START: //启动时设置
            rightMotorCurPeriodIndex = 1;
            rightMotorCurPeriod = motor_profile[rightMotorCurPeriodIndex];
            rightMotorDstPeriod = calculatePeriodBySpeed(speed);
            rightMotorEnable = TRUE;
            break;
        case MOTOR_RUN:
            rightMotorDstPeriod = calculatePeriodBySpeed(speed);
            break;
        case MOTOR_STOP:
            rightMotorDstPeriod = motor_profile[0];
            break;
    }
}

//滚动电机
void rollMotorControl(MOTOR_STATUS_TYPE status, uint32_t speed)
{
    switch(status)
    {
        case MOTOR_START: //启动时设置
            cutRollMotorCurPeriodIndex = 1;
            cutRollMotorCurPeriod = motor_profile[cutRollMotorCurPeriodIndex];
            cutRollMotorDstPeriod = calculatePeriodBySpeed(speed);
            rollMotorEnable = TRUE;
            break;
        case MOTOR_RUN:
            cutRollMotorDstPeriod = calculatePeriodBySpeed(speed);
            break;
        case MOTOR_STOP:
            cutRollMotorDstPeriod = motor_profile[0];
            break;
    }
}

//滚动电机
void cutMOveMotorControl(MOTOR_STATUS_TYPE status, uint32_t speed)
{
    switch(status)
    {
        case MOTOR_START: //启动时设置
            cutMoveMotorCurPeriodIndex = 1;
            cutMoveMotorCurPeriod = motor_profile[cutMoveMotorCurPeriodIndex];
            cutMoveMotorDstPeriod = calculatePeriodBySpeed(speed);
            cutMoveMotorRunEnable = TRUE;
            break;
        case MOTOR_RUN:
            cutMoveMotorDstPeriod = calculatePeriodBySpeed(speed);
            break;
        case MOTOR_STOP:
            cutMoveMotorDstPeriod = motor_profile[0];
            break;
				default:
					break;
    }
}


//摄像头限位检测
void cameraLimitHandler()
{
}


//送纸限位检测
void paperLimitHandler()
{
    static uint16_t noPapercount = 0, hasPapercount = 0;
    
    //检测传感器
    if(GET_PAPER_LIMIT_STATUS() == Bit_RESET) //检测到无纸张
    {
        hasPapercount = 0;
        if(noPapercount++ >= 10){
           noPapercount = 0;
           paperStatus = NO_PAPER_STATUS;
        }
    }
    else //检测到有纸
    {
        noPapercount = 0;
        if(hasPapercount++ >= 10){
            hasPapercount = 0;
            paperStatus = HAS_PAPER_STATUS;
        }
    }
    
    //根据状态做处理
    switch(paperStatus)
    {
        case IDLE_PAPER_STATUS:
            break;
        case NO_PAPER_STATUS:
            if(!f_paperMotorStart) //无纸时电机开始转动
            {
                f_paperMotorStart = TRUE;
                f_paperMotorEnd = FALSE;
                f_paperMotorTime = FALSE;
                PAPER_MOTOR_POSITIVE_SET(); //电机开始动
                PAPER_MOTOR_NEGATIVE_RESET();
            }
            break;
        case HAS_PAPER_STATUS: //开始有纸时,设置延时转动时间
            if(!f_paperMotorTime){
                paperMotorTime = 0;
                f_paperMotorTime = TRUE;
            }
            
            paperMotorTime++;
            if(paperMotorTime >= 100 && !f_paperMotorEnd)
            {
                f_paperMotorStart = FALSE;
                f_paperMotorEnd = TRUE;
                PAPER_MOTOR_POSITIVE_RESET(); //电机停止
                PAPER_MOTOR_NEGATIVE_RESET();
            }
            break;
    }
}

//切刀限位检测
void cutLimitHandler()
{
    if(GET_CUT_LIMIT_STATUS() == Bit_RESET)
    {
    
    }
}

void setCutMoveMotor(uint32_t speed, uint8_t motorStatus)
{
    if(motorStatus)
    {
				cutMoveMotorStopEnable = TRUE;
        cutMoveMotorDstPeriod = motor_profile[0];
    }
    else
    {
				cutMoveMotorCurPeriodIndex = 1;
				cutMoveMotorCurPeriod = motor_profile[cutMoveMotorCurPeriodIndex];
				//cutMoveMotorDstPeriod = calculatePeriodBySpeed(speed);
				cutMoveMotorDstPeriod = motor_profile[2];
				cutMoveMotorRunEnable = TRUE;
    }
}


void setCameraMotor(uint32_t curPeriodIndex, uint32_t dstPeriodIndex, uint8_t motorStatus)
{
    cameraMotorCurPeriodIndex = curPeriodIndex;
    CameraMotorCurPeriod = cameraMotorProfile[curPeriodIndex];
    cameraMotorDstPeriodIndex = dstPeriodIndex;
    CameraMotorDstPeriod = cameraMotorProfile[dstPeriodIndex];
    
    if(motorStatus)
    {
        CameraMotorStopEnable = TRUE;
        cameraMotorDstPeriodIndex = 1;
        CameraMotorDstPeriod = cameraMotorProfile[1];
    }
    else
    {
        CAMERA_MOTOR_ENABLE();
        CAMERA_MOTOR_UNSLEEP();
        CameraMotorRunEnable = TRUE;
        CameraMotorStopEnable = FALSE;
    }
}

//摄像头电机复位处理
void cameraMotorResetHandler()
{
    static uint32_t delayCount = 0;
    
    switch(cameraMotorStatus)
    {
        case CAMERA_RESET_IDLE_STATUS:
            break;
        case CAMERA_BACKMOVE_STATUS: //不在原点时,往后原点方向移动
            setCameraMotor(1, 3900, 0);
            CAMERA_MOTOR_DIR_NEGATIVE();
            cameraMotroDir = 0;
            cameraMotorStatus = CAMERA_STOPWAIT_STATUS;
            delayCount = 0;
            break;
        case CAMERA_STOPWAIT_STATUS: //碰到限位开关,等待一会
            if(CameraMotorStopEnable)
            {
                if(delayCount++ <= 1000)
                    return;
                delayCount = 0;
                cameraMotorStatus = CAMERA_MOVEORIGIN_STATUS;
            }
            break;
        case CAMERA_MOVEORIGIN_STATUS: //移动到原点
            setCameraMotor(1, 1000, 0);
            CAMERA_MOTOR_DIR_POSITIVE();
            cameraMotroDir = 1;
            cameraMotorStatus = CAMERA_READY_STATUS;
            delayCount = 0;
            break;
        case CAMERA_READY_STATUS:
            if(CameraMotorStopEnable)
            {
                if(delayCount++ <= 2000)
                    return;
                delayCount = 0;
                cameraMotorStatus = CAMERA_STARTFIND_STATUS;
            }
            break;
        case CAMERA_STARTFIND_STATUS:
            cameraMotorStatus = CAMERA_RESET_IDLE_STATUS;
            validCount = 0;
            CAMERA_MOTOR_DIR_POSITIVE();
            cameraMotroDir = 1;
            setCameraMotor(1, 3500, 0);           
            f_cameraCheckEnable = TRUE;
            delayCount = 0;
            break;
        case CAMERA_HADFOUND_STATUS:
            if(CameraMotorStopEnable)
            {
                if(delayCount++ <= 1000*1)
                    return;
                delayCount = 0;
               
                cameraMotorStatus = CAMERA_RUNING_STATUS;
                leftMotorCurSpeed = 0x32;//0x1f4;
                leftMotorControl(MOTOR_START, leftMotorCurSpeed);
                rightMotorCurSpeed = 0x32;//0x1f4;
                rightMotorControl(MOTOR_START, rightMotorCurSpeed);
            }
        case CAMERA_RUNING_STATUS:
            break;
        case CAMERA_STOP_STATUS:
            if(CameraMotorStopEnable)
            {
                if(delayCount++ <= 1000)
                    return;
                delayCount = 0;
                cameraMotorStatus = CAMERA_BACKMOVE_STATUS;
            }
            break;
				default:
					break;
    }
}

void cutMotorResetHandler()
{
	static uint32_t cutMotorDelayCount = 0;
	 switch(cutMoveMotorStatus)
	 {
		 case CUT_BACKMOVE_STATUS:
			setCutMoveMotor(20, 0);
			CUT_MOVE_MOTOR_DIR(0);
			cutMoveMotroDir = 0;
			cutMoveMotorStatus = CUT_STOPWAIT_STATUS;
			cutMotorDelayCount = 0;
			 break;
		 case CUT_STOPWAIT_STATUS:
			if(cutMoveMotorStopEnable)
			{
				if(cutMotorDelayCount++ <= 1000)
						return;
				cutMotorDelayCount = 0;
				cutMoveMotorStatus = CUT_MOVEORIGIN_STATUS;
				
				TIM_ARRPreloadConfig(TIM6, DISABLE);
				TIM_ClearFlag(TIM6, TIM_FLAG_Update);
				TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
				TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);
				TIM6->PSC = 36-1;
				
				motor3Device.motorInfo.step = CUT_MOVE_MOTOR_MAX_RANG;//cutMoveMotorRange;//-200;
				f_cameraMotorStart = TRUE;
				f_cutMoveMotorStop = FALSE;
			}
			 break;
		 case CUT_MOVEORIGIN_STATUS:
			 if(f_cutMoveMotorStop)
			 {
					motor3Device.motorInfo.step = -CUT_MOVE_MOTOR_MAX_RANG;
					f_cameraMotorStart = TRUE;
					f_cutMoveMotorStop = FALSE;
					cutMoveMotorStatus = CUT_READY_STATUS;
			 }
			 break;
		 case CUT_READY_STATUS:
			 if(f_cutMoveMotorStop)
			 {
					motor3Device.motorInfo.step = CUT_MOVE_MOTOR_MAX_RANG;
					f_cameraMotorStart = TRUE;
					f_cutMoveMotorStop = FALSE;
					cutMoveMotorStatus = CUT_MOVEORIGIN_STATUS;
			 }
			 break;
		 default:
			 break;
	 }
}




