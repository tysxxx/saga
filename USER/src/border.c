
#include "tim.h"
#define BORDER_CONTROL
#include "border.h"



void borderInit()
{


}


//检测送纸传感器
void paperLimit()
{
    static uint16_t noPapercount = 0, hasPapercount = 0;
 
    //检测有无纸状态
    if(paperLimitCheck() == Bit_RESET) //检测电机没有纸张,就要开始转动电机
    {
        hasPapercount = 0;
        if(noPapercount++ >= 10){
           noPapercount = 0;
           paperStatus = noPaperStatus;
        }
    }
    else //检测到有纸
    {
        noPapercount = 0;
        if(hasPapercount++ >= 10){
            hasPapercount = 0;
            paperStatus = hasPaperStatus;
        }
    }
    
    //根据状态做处理
    switch(paperStatus)
    {
        case idlePaperStatus:
            break;
        case noPaperStatus:
            if(!f_paperMotorStart) //没纸时电机一直转动
            {
                f_paperMotorStart = TRUE;
                f_paperMotorEnd = FALSE;
                f_paperMotorTime = FALSE;
                TIM_SetCompare2(TIM1, 800); //电机开始转动
            }
            break;
        case hasPaperStatus: //开始有纸时,设置继续转动电机的时间
            if(!f_paperMotorTime){
                paperMotorTime = 0;
                f_paperMotorTime = TRUE;
            }
            
            paperMotorTime++;
            if(paperMotorTime >= 100 && !f_paperMotorEnd)
            {
                f_paperMotorStart = FALSE;
                f_paperMotorEnd = TRUE;
                TIM_SetCompare2(TIM1, 1800-1); //电机停止
            }
            break;
    }
}

//摄像头电机限位检测
void cameraLimit()
{
   static uint16_t cameraMotorCount = 0;
    
   if(f_cameraMotorCheckEnable && (cameraLimitCheck() == Bit_SET)) //检测到限位,电机停止
   {
       if(cameraMotorCount++ >= 2 && !f_cameraMotorStop)
       {
           f_cameraMotorStop = TRUE;
           //设置电机停止转动
       }
   }
   else
   {
       cameraMotorCount = 0;
       f_cameraMotorStop = FALSE;
   }
}

//切割电机限位检测
void cutLimit()
{

}






