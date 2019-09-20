/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "utility.h"
#include "tim.h"
#include "motor.h"
#include "iHSV57.h"

extern const unsigned short motor_profile[];
extern const unsigned short cameraMotorProfile[];
extern const unsigned short cutMotorProfile[];

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) //系统滴答时钟中断
{
    static uint16_t time_100us = 0;
	if(timeDelay > 0)
		timeDelay--;

    if(++time_100us%10==0)
    {
        time_100us = 0;
        f_1ms = TRUE;
    }
}

//定时器TIM1中断处理
void TIM1_UP_IRQHandler()
{
    static uint8_t delay = 0;
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        
        if(cameraMotorStatus == CAMERA_RESET_IDLE_STATUS)
        {
            if(cameraPosition >= cameraMotorRange-1000)
            {
                CameraMotorStopEnable = TRUE;
                cameraMotorDstPeriodIndex = 1;
                cameraMotorStatus = CAMERA_STOP_STATUS;
            }
        }
				
//						if(cutValidPosition >= (8000) && f_cutCheckEnable) //300
//						//if(cutValidPosition >= (8000) && f_cutCheckEnable)
//						//if(cutValidPosition >= (8250) && f_cutCheckEnable) //100
//						{
//							f_cutCheckEnable = FALSE;
//							f_motorResumeEnable = TRUE;
//							//cutValidPosition = 0;
//							leftMotorControl(MOTOR_STOP, 0);
//							rightMotorControl(MOTOR_STOP, 0);
////							leftMotorEnable = FALSE;
////							rightMotorEnable = FALSE;
//							f_adjustMotorStop = TRUE;
//							stopDelay = 0;
//						}
    }
}

//TIM2中断处理 1us  周期2us:500kHz :设置脉冲的最大频率是500KHZ
void TIM2_IRQHandler()
{
    static uint8_t scount=0;
    
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    
        if(leftMotorEnable)
        {
            if(GPIO_ReadOutputDataBit(LEFT_ADJUST_MOTOR_GPIO_PORT, LEFT_ADJUST_MOTOR_PIN) == Bit_SET) //左边调速电机
            {
                GPIO_ResetBits(LEFT_ADJUST_MOTOR_GPIO_PORT, LEFT_ADJUST_MOTOR_PIN);
                if(leftMotorCurPeriod > leftMotorDstPeriod) //加速
                {
                    if(leftMotorCurPeriodIndex < 4000-1)
                        leftMotorCurPeriodIndex++;
                    leftMotorCurPeriod = motor_profile[leftMotorCurPeriodIndex];
                    setTIMxPeriod(TIM2, leftMotorCurPeriod); //改变周期
                }
                else if(leftMotorCurPeriod < leftMotorDstPeriod)//减速
                {
										if(f_adjustMotorStop)
										{
											if(leftMotorCurPeriodIndex >= 200)
													leftMotorCurPeriodIndex -= 200;
											else
												leftMotorCurPeriodIndex = 0;
										}
										else
										{
											if(leftMotorCurPeriodIndex > 0)
													leftMotorCurPeriodIndex--;
										}
                    leftMotorCurPeriod = motor_profile[leftMotorCurPeriodIndex];
                    setTIMxPeriod(TIM2, leftMotorCurPeriod); 
                }
                else
                {
                   if(leftMotorCurPeriod == motor_profile[0]) 
                   {
                       leftMotorEnable = FALSE;
                   }
                }
            }
            else
            {
                GPIO_SetBits(LEFT_ADJUST_MOTOR_GPIO_PORT, LEFT_ADJUST_MOTOR_PIN);
								if(f_cutCheckEnable)
								{
									cutValidPosition++;
								}
								if(f_motorStopAdjust)
								{
									spaceDistance++;
								}
								//for(int i = 0; i < QUEUE_MAX_SIZE; i++)
								{
									
								}
            }
        }
				
						//	if(cutValidPosition >= (6800) && f_cutCheckEnable)
						//if(cutValidPosition >= (7300) && f_cutCheckEnable)//400
						//if(cutValidPosition >= (7700) && f_cutCheckEnable) //300
					 //if(cutValidPosition >= (8000) && f_cutCheckEnable) //200
						if(cutValidPosition >= (8250) && f_cutCheckEnable) //100
						{
							f_cutCheckEnable = FALSE;
							f_motorResumeEnable = TRUE;
							//cutValidPosition = 0;
							leftMotorControl(MOTOR_STOP, 0);
							rightMotorControl(MOTOR_STOP, 0);
//							leftMotorEnable = FALSE;
//							rightMotorEnable = FALSE;
							f_adjustMotorStop = TRUE;
							stopDelay = 0;
						}
    }
}

//定时器TIM3中断处理
void TIM3_IRQHandler()
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        
        if(rightMotorEnable)
        {
            if(GPIO_ReadOutputDataBit(RIGHT_ADJUST_MOTOR_GPIO_PORT, RIGHT_ADJUST_MOTOR_PIN) == Bit_SET) //右边调速电机
            {
                GPIO_ResetBits(RIGHT_ADJUST_MOTOR_GPIO_PORT, RIGHT_ADJUST_MOTOR_PIN);
                
                if(rightMotorCurPeriod > rightMotorDstPeriod) //加速
                {
                    if(rightMotorCurPeriodIndex < 4000-1)
                        rightMotorCurPeriodIndex++;
                    rightMotorCurPeriod = motor_profile[rightMotorCurPeriodIndex];
                    setTIMxPeriod(TIM3, rightMotorCurPeriod); //改变周期
                }
                else if(rightMotorCurPeriod < rightMotorDstPeriod)//减速
                {
										if(f_adjustMotorStop)
										{
											if(rightMotorCurPeriodIndex >= 200)
													rightMotorCurPeriodIndex -= 200;
											else
												rightMotorCurPeriodIndex = 0;
										}
										else
										{
											if(rightMotorCurPeriodIndex > 0)
													rightMotorCurPeriodIndex--;
										}
                    rightMotorCurPeriod = motor_profile[rightMotorCurPeriodIndex];
                    setTIMxPeriod(TIM3, rightMotorCurPeriod); 
                }
                else
                {
                   if(rightMotorCurPeriod == motor_profile[0]) 
                   {
                       rightMotorEnable = FALSE;
                   }
                }
            }
            else
            {
                GPIO_SetBits(RIGHT_ADJUST_MOTOR_GPIO_PORT, RIGHT_ADJUST_MOTOR_PIN);
            }
        }
    }
}

//定时器TIM4中断处理
void TIM4_IRQHandler() //摄像头
{
    static uint8_t delay = 0;
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        
        if(CameraMotorRunEnable)
        {
            if(CAMERA_MOTOR_STEP_PIN_STATUS() == Bit_SET)
            { 
                CAMERA_MOTOR_STEP_RESET();
                
                if(cameraMotorDstPeriodIndex > cameraMotorCurPeriodIndex) //加速
                {
                    if(cameraMotorCurPeriodIndex < 4000-1){
                        cameraMotorCurPeriodIndex++;
                    }
                    setTIMxPeriod(TIM4, cameraMotorProfile[cameraMotorCurPeriodIndex]);
                }
                else if(cameraMotorDstPeriodIndex < cameraMotorCurPeriodIndex) //加速
                {
                    if(CameraMotorStopEnable)
                    {
                        if(cameraMotorCurPeriodIndex > 20)
                        {
                            cameraMotorCurPeriodIndex -= 20;
                        }
                        else
                        {
                            cameraMotorCurPeriodIndex = cameraMotorDstPeriodIndex;
                        }
                    }
                    else
                    {
                        if(cameraMotorCurPeriodIndex > 0)
                        {
                            cameraMotorCurPeriodIndex--;
                        }
                    }
                    setTIMxPeriod(TIM4, cameraMotorProfile[cameraMotorCurPeriodIndex]);
                }
                else
                {
                    if(CameraMotorStopEnable)
                    {
                        CameraMotorRunEnable = FALSE;
                        CAMERA_MOTOR_DISABLE();
                        CAMERA_MOTOR_SLEEP();
                    }
                }
            }else{
                CAMERA_MOTOR_STEP_SET();
                if(cameraMotroDir)
                    cameraPosition++;
                else
                    cameraPosition--;
            }
        }
    }
}



//定时器TIM5中断处理
//0x133d0 = 78800 plus
//
void TIM5_IRQHandler() //摄像头电机
{
    __IO uint16_t tim_count = 0;
    uint16_t new_step_delay = 0;
    __IO static uint16_t last_accel_delay = 0;
    __IO static uint32_t step_count = 0;
    __IO static int32_t rest = 0;
    __IO static uint8_t i = 0;
    
    
    if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
#if 0        
        TIM_SetAutoreload(TIM5, cameraMotor.step_delay);
        if(cameraMotor.run_state != STOP){
            pluseCount++;
        }
        
        if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_4) == Bit_SET)
            GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        else
            GPIO_SetBits(GPIOC, GPIO_Pin_4);
      
      i++;      // 定时器中断次数计数值
      if(i==2)  // 2次，说明已经输出一个完整脉冲
      { 
        i = 0;
        switch(cameraMotor.run_state)  // 加减速曲线阶段
        {
          case STOP: //停止
            step_count = 0;
            rest = 0;
            last_accel_delay = 0;
            TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE);
            UsartSendArray(USART2, (uint8_t*)&pluseCount, 4);
            pluseCount = 0;
          
            f_cameraMotorStatus = 0;
            CAMERA_MOTOR_PULSE(0);
            CAMERA_MOTOR_DISABLE();
            CAMERA_MOTOR_SLEEP();
            break;

          case ACCEL: //加速
            step_count++; //步数加
            cameraMotor.accel_count++; // 加速计数值加1
            //计算新(下)一步脉冲周期(时间间隔)
            new_step_delay = cameraMotor.step_delay - (((2 * (long)cameraMotor.step_delay) + rest)/(4 * cameraMotor.accel_count + 1));
            //计算余数，下次计算补上余数，减少误差
            rest = ((2 * (long)cameraMotor.step_delay)+rest)%(4 * cameraMotor.accel_count + 1);
            
            // 检查是够应该开始减速
            if(step_count >= cameraMotor.decel_start || f_cameraMotorStop)
            {
                if(f_cameraMotorStop)
                {
                    f_cameraMotorStop = FALSE;
                    cameraMotor.accel_count = T1_FREQ/2*200*T1_FREQ/cameraMotor.step_delay/cameraMotor.step_delay*(-1);
                    int32_t date = -cameraMotor.accel_count;
                }else
                {
                    cameraMotor.accel_count = cameraMotor.decel_val; // 加速计数值为减速阶段计数值的初始值
                }
                cameraMotor.run_state = DECEL; // 下个脉冲进入减速阶段
            }
            else if(new_step_delay <= cameraMotor.min_delay) // 检查是否到达期望的最大速度
            {
                last_accel_delay = new_step_delay; // 保存加速过程中最后一次延时（脉冲周期）
                new_step_delay = cameraMotor.min_delay; // 使用min_delay（对应最大速度speed）
                rest = 0;  // 清零余值
                cameraMotor.run_state = RUN; // 设置为匀速运行状态
            }
            break;

          case RUN:
            step_count++; // 步数加1
            new_step_delay = cameraMotor.min_delay; // 使用min_delay（对应最大速度speed）
             // 需要开始减速
            if(step_count >= cameraMotor.decel_start || f_cameraMotorStop)
            {
                 if(f_cameraMotorStop)
                {
                    f_cameraMotorStop = FALSE;
                    cameraMotor.accel_count = T1_FREQ/2*200*T1_FREQ/cameraMotor.step_delay/cameraMotor.step_delay*(-1);
                }
                else{
                    cameraMotor.accel_count = cameraMotor.decel_val; //减速时所要执行的步数
                }
                new_step_delay = last_accel_delay; // 加阶段最后的延时做为减速阶段的起始延时(脉冲周期)
                cameraMotor.run_state = DECEL;  // 状态改变为减速
            }
            break;

          case DECEL:
            step_count++; // 步数加1
            cameraMotor.accel_count++; // 加速计数值加1
            //计算新(下)一步脉冲周期(时间间隔)
            new_step_delay = cameraMotor.step_delay - (((2 * (long)cameraMotor.step_delay) + rest)/(4 * cameraMotor.accel_count + 1));
            // 计算余数，下次计算补上余数，减少误差
            rest = ((2 * (long)cameraMotor.step_delay)+rest)%(4 * cameraMotor.accel_count + 1);
             //检查是否为最后一步
          
            if(f_cameraMotorStop)
            {
                f_cameraMotorStop = FALSE;
                cameraMotor.accel_count = T1_FREQ/2*200*T1_FREQ/cameraMotor.step_delay/cameraMotor.step_delay*(-1);
            }
            if(cameraMotor.accel_count >= 0)
            {
                cameraMotor.run_state = STOP;
            }
            break;
        }
        cameraMotor.step_delay = new_step_delay; //保存上一个周期的计数值 ,为下个(新的)延时(脉冲周期)赋值做准备
      }

#endif
    }
}

/*
*0xabe0+
*/

//定时器TIM6中断处理
void TIM6_IRQHandler() //纵切刀电机
{
     __IO uint16_t tim_count = 0;
    uint16_t new_step_delay = 0;
    __IO static uint16_t last_accel_delay = 0;
    __IO static uint32_t step_count = 0;
    __IO static int32_t rest = 0;
    __IO static uint8_t i = 0;
    
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
			
				//if(cutMoveMotorStatus == CUT_BACKMOVE_STATUS || cutMoveMotorStatus == CUT_STOPWAIT_STATUS)
				if(0)
				{
						if(cutMoveMotorRunEnable)
						{
								if(GET_CUT_MOVE_MOTOR_PIN_STATUS() == Bit_SET) //右边调速电机
								{
										CUT_MOVE_MOTOR_PIN_RESET();
										
										if(cutMoveMotorCurPeriod > cutMoveMotorDstPeriod) //加速
										{
												if(cutMoveMotorCurPeriodIndex < 4000-1)
														cutMoveMotorCurPeriodIndex++;
												cutMoveMotorCurPeriod = motor_profile[cutMoveMotorCurPeriodIndex];
												setTIMxPeriod(TIM6, cutMoveMotorCurPeriod); //改变周期
										}
										else if(cutMoveMotorCurPeriod < cutMoveMotorDstPeriod)//减速
										{
												if(cutMoveMotorStopEnable)
												{
//														if(cutMoveMotorCurPeriodIndex > 20)
//															cutMoveMotorCurPeriodIndex -= 20;
//														else
															cutMoveMotorCurPeriod = cutMoveMotorDstPeriod;
												}
												else
												{
													if(cutMoveMotorCurPeriodIndex > 0)
														cutMoveMotorCurPeriodIndex--;
													cutMoveMotorCurPeriod = motor_profile[cutMoveMotorCurPeriodIndex];
												}
												setTIMxPeriod(TIM6, cutMoveMotorCurPeriod);
										}
										else
										{
											 if(cutMoveMotorStopEnable) 
											 {
													 cutMoveMotorRunEnable = FALSE;
											 }
										}
								}
								else
								{
										CUT_MOVE_MOTOR_PIN_SET();
										if(cutMoveMotroDir)
											cutMoveMotorPosition++;
										else
											cutMoveMotorPosition--;
								}
							}
				}
				else //if(cutMoveMotorStatus == CUT_MOVEORIGIN_STATUS || cutMoveMotorStatus == CUT_READY_STATUS)
				{
#if 1       
        TIM_SetAutoreload(TIM6, cutMotor.step_delay);
        
        if(cutMotor.run_state != STOP){
//            if(GET_CUT_MOVE_MOTOR_PIN_STATUS() == Bit_SET)
//                CUT_MOVE_MOTOR_PIN_RESET();
//            else{
//                CUT_MOVE_MOTOR_PIN_SET();
//							cutMoveMotorPluseCount++;
//						}
					
						if(GET_LEFT_ADJUST_MOTOR_PIN_STATUS() == Bit_SET)
								LEFT_ADJUST_MOTOR_PIN_RESET();
						else
								LEFT_ADJUST_MOTOR_PIN_SET();
						
						if(GET_RIGHT_ADJUST_MOTOR_PIN_STATUS() == Bit_SET)
								RIGHT_ADJUST_MOTOR_PIN_RESET();
						else{
								RIGHT_ADJUST_MOTOR_PIN_SET();
							spaceDistance++;
						}
        }
        
      i++;      // 定时器中断次数计数值
      if(i==2)  // 2次，说明已经输出一个完整脉冲
      { 
        i = 0;
        switch(cutMotor.run_state)  // 加减速曲线阶段
        {
          case STOP: //停止
            step_count = 0;
            rest = 0;
            TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);
            CUT_MOVE_MOTOR_PIN_RESET();
				
						//UsartSendArray(USART2, (uint8_t*)&cutMoveMotorPluseCount, 4);
            cutMoveMotorPluseCount = 0;
						f_cutMoveMotorStop = TRUE;
						f_spaceStopExe = TRUE;
					
            break;

          case ACCEL: //加速
            step_count++; //步数加
            cutMotor.accel_count++; // 加速计数值加1
            //计算新(下)一步脉冲周期(时间间隔)
            new_step_delay = cutMotor.step_delay - (((2 * (long)cutMotor.step_delay) + rest)/(4 * cutMotor.accel_count + 1));
            //计算余数，下次计算补上余数，减少误差
            rest = ((2 * (long)cutMotor.step_delay)+rest)%(4 * cutMotor.accel_count + 1);
            // 检查是够应该开始减速
            if(step_count >= cutMotor.decel_start)
            {
                cutMotor.accel_count = cutMotor.decel_val; // 加速计数值为减速阶段计数值的初始值
                cutMotor.run_state = DECEL; // 下个脉冲进入减速阶段
            }
            else if(new_step_delay <= cutMotor.min_delay) // 检查是否到达期望的最大速度
            {
                last_accel_delay = new_step_delay; // 保存加速过程中最后一次延时（脉冲周期）
                new_step_delay = cutMotor.min_delay; // 使用min_delay（对应最大速度speed）
                rest = 0;  // 清零余值
                cutMotor.run_state = RUN; // 设置为匀速运行状态
            }
            break;

          case RUN:
            step_count++; // 步数加1
            new_step_delay = cutMotor.min_delay; // 使用min_delay（对应最大速度speed）
             // 需要开始减速
            if(step_count >= cutMotor.decel_start)
            {
                cutMotor.accel_count = cutMotor.decel_val; //减速时所要执行的步数
                new_step_delay = last_accel_delay; // 加阶段最后的延时做为减速阶段的起始延时(脉冲周期)
                cutMotor.run_state = DECEL;  // 状态改变为减速
            }
            break;

          case DECEL:
            step_count++; // 步数加1
            cutMotor.accel_count++; // 加速计数值加1
            //计算新(下)一步脉冲周期(时间间隔)
            new_step_delay = cutMotor.step_delay - (((2 * (long)cutMotor.step_delay) + rest)/(4 * cutMotor.accel_count + 1));
            // 计算余数，下次计算补上余数，减少误差
            rest = ((2 * (long)cutMotor.step_delay)+rest)%(4 * cutMotor.accel_count + 1);
             //检查是否为最后一步
            if(cutMotor.accel_count >= 0)
            {
                cutMotor.run_state = STOP;
            }
            break;
        }
        cutMotor.step_delay = new_step_delay; //保存上一个周期的计数值 ,为下个(新的)延时(脉冲周期)赋值做准备
      }
#endif 
		}			
    }
}


//定时器TIM7中断处理
void TIM7_IRQHandler()
{
     if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        
        if(rollMotorEnable)
        {
            if(GET_CUT_ROLL_MOTOR_PIN_STATUS() == Bit_SET) //右边调速电机
            {
                CUT_ROLL_MOTOR_PIN_RESET();
                
                if(cutRollMotorCurPeriod > cutRollMotorDstPeriod) //加速
                {
                    if(cutRollMotorCurPeriodIndex < 4000-1)
                        cutRollMotorCurPeriodIndex++;
                    cutRollMotorCurPeriod = motor_profile[cutRollMotorCurPeriodIndex];
                    setTIMxPeriod(TIM7, cutRollMotorCurPeriod); //改变周期
                }
                else if(cutRollMotorCurPeriod < cutRollMotorDstPeriod)//减速
                {
                    if(cutRollMotorCurPeriodIndex > 0)
                        cutRollMotorCurPeriodIndex--;
                    cutRollMotorCurPeriod = motor_profile[cutRollMotorCurPeriodIndex];
                    setTIMxPeriod(TIM7, cutRollMotorCurPeriod); 
                }
                else
                {
                   if(cutRollMotorCurPeriod == motor_profile[0]) 
                   {
                       rollMotorEnable = FALSE;
											f_testMotorStop = FALSE;
                   }
                }
								
								if(f_testMotorStop)
								{
									testMotorStopPluseCount++;
								}
            }
            else
            {
                CUT_ROLL_MOTOR_PIN_SET();
            }
        }
    }
}

//定时器TIM8中断处理
void TIM8_UP_IRQHandler()
{

}

//外部管脚
void EXTI9_5_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        EXTI_ClearITPendingBit(EXTI_Line5);
        if(cameraMotorStatus != CAMERA_RESET_IDLE_STATUS)
        {
            f_cameraMotorStop = TRUE; //停止
            CameraMotorStopEnable = TRUE;
            cameraMotorDstPeriodIndex = 1;

        }
        if(cameraMotorStatus == CAMERA_READY_STATUS)
        {
            cameraOriginPosition = cameraPosition;
            cameraMotorRange = cameraOriginPosition + CAMERA_MOTOR_MAX_RANG; 
        }
    }
		
		if(EXTI_GetITStatus(EXTI_Line6) == SET)
    {
        EXTI_ClearITPendingBit(EXTI_Line6);
			
				if(cutMoveMotorStatus == CUT_BACKMOVE_STATUS || cutMoveMotorStatus == CUT_STOPWAIT_STATUS)
			  {
					cutMoveMotorStopEnable = TRUE;
					cutMoveMotorDstPeriod = motor_profile[0];
					
					cutMoveMotorOriginPosition = cutMoveMotorPosition;
					cutMoveMotorRange = cutMoveMotorOriginPosition + CUT_MOVE_MOTOR_MAX_RANG; 
				}
			
//			if(cutMoveMotorStatus == CUT_READY_STATUS)
//			{
//					cutMoveMotorOriginPosition = cutMoveMotorPosition;
//					cutMoveMotorRange = cutMoveMotorOriginPosition + CAMERA_MOTOR_MAX_RANG; 
//			}
        
    }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
