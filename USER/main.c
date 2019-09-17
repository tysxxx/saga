/**
  ******************************************************************************
  * @file    Project/sagaCut/main.c 
  * @author  tys
  * @version V1.0
  * @date    03-08-2019
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
 */  

#include "stm32f10x.h"
#include <stdio.h>
#include "gpio.h"
#include "sys.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "nvic.h"
#include "uart.h"
#include "utility.h"
#include "TLS1401.h"
#include "iHsv57.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"

int main(void)
{
	//初始化
	sysTickInit();
	NVICInit();
	gpioInit();
	adcInit();
	uartInit();
	timInit();
    TSL1401Init();
    motorInit();
    iHSV57Init();
    
    tsl1401Reset();
    systemStatus = SYSTEM_RESET;
    //cameraMotorStatus = CAMERA_RESET_START_STATUS;
    while (1)
    {
        if(f_1ms) //1ms
        {
            f_1ms = FALSE;
//            cameraLimitHandler();
//            paperLimitHandler();
//            cutLimitHandler();
            cameraMotorResetHandler();
						cutMotorResetHandler();
            
            time_1ms++;
            CCDTime++;
            if(time_1ms%5 == 0) //5ms
            {
                time_1ms = 0;
                if(f_cameraMotorStart)
                {
                    f_cameraMotorStart = FALSE;
                    cutMotorAxisMoveRel(motor3Device.motorInfo.step, 200, 200, 900);
                }
            }
            if(CCDTime%6 == 0) //定时采样CCD的值
            {
                CCDTime = 0;
                tsl1401GetImg();
                judgeValidFlag();        
            }
        }        
    }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
