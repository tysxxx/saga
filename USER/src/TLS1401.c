#include "utility.h"
#include "adc.h"
#include "string.h"
#include "iHsv57.h"
#include "motor.h"
#include "tim.h"
#define TLS1401_CONTROL
#include "TLS1401.h"

//延时
void TSL1401_Delay(uint32_t time)
{
    volatile uint32_t i = time;
    while(i--);
}

//SI
void TSL1401_SI(uint8_t state)
{
	if(state == 1)
		TSL1401_SI_SET();
	else if(state==0)
		TSL1401_SI_RESET();
}

//CLK
void TSL1401_CLK(uint8_t state)
{
	if(state==1)
		TSL1401_CLK_SET();
	else if(state==0)
		TSL1401_CLK_RESET();
}

//初始化
void TSL1401Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin = TSL1401_CLK_PIN | TSL1401_SI_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    TSL1401_SI_RESET();
    TSL1401_CLK_RESET();
}

//tsl1401,线性CCD采集图像
void tsl1401GetImg(void)
{
    //__disable_irq();
    TSL1401Sample();
    //__enable_irq();
    //memcpy(tls1401DataBuf, tls1401SampleBuf, 128);
    tsl1401Bin();
    filterBin();
    //usartSendData(USART2, tls1401BinBuf, 128);
    //USART_SendData(USART2, 0xff);
}


//采集的数据二值化处理
void tsl1401Bin()
{
    //将收集到的数据进行二值化处理
	uint8_t max=0, min=0, mid=0, n=0;
    
    //获取最大值
	for(n = 0; n < 128; n++)
		if(max<tls1401DataBuf[n])
		    max=tls1401DataBuf[n];	
    
    //获取最小值
	min = max;
	for(n = 0; n < 128; n++)
		if(min>tls1401DataBuf[n])    
		    min=tls1401DataBuf[n];
        
    //中间值
	mid = (max+min)/2;
        
    for(n = 0; n < 128; n++)
    {
      if(tls1401DataBuf[n] >= mid)
          tls1401DataBuf[n] = 0xfe;
      else
          tls1401DataBuf[n] = 0x00;
    }
}

//二值滤波
void filterBin(void)
{
     uint8_t i;
#if 1  
     for(i=1; i<127; i++)
     {
         if(tls1401DataBuf[i] == 0
             && tls1401DataBuf[i] != tls1401DataBuf[i-1]
             && tls1401DataBuf[i] != tls1401DataBuf[i+1])
         {
              tls1401DataBuf[i]=0xfe;
         } 

         else if(tls1401DataBuf[i] == 0xfe
             && tls1401DataBuf[i] != tls1401DataBuf[i-1]
             && tls1401DataBuf[i] != tls1401DataBuf[i+1])
         {
              tls1401DataBuf[i]=0;
         }
     }
      
     //当黑线上的点数超过三个时使用
     for(i=1; i<126; i++)
     {
          if(tls1401DataBuf[i] == 0
             && tls1401DataBuf[i] == tls1401DataBuf[i+1] 
             && tls1401DataBuf[i] != tls1401DataBuf[i-1]
             && tls1401DataBuf[i] != tls1401DataBuf[i+2])
          {
              tls1401DataBuf[i] = 0xfe;
              tls1401DataBuf[i+1] = 0xfe;
          }

          if(tls1401DataBuf[i] == 0xfe 
             && tls1401DataBuf[i] == tls1401DataBuf[i+1]
             && tls1401DataBuf[i] != tls1401DataBuf[i-1]
             && tls1401DataBuf[i] != tls1401DataBuf[i+2])            
          {
              tls1401DataBuf[i] = 0;
              tls1401DataBuf[i+1] = 0;
          }
      }
#endif     
      //保存二值化后的值
      memcpy(tls1401BinBuf, tls1401DataBuf, 128);
      
      //去掉头部数据
      for(i = 120; i < 128; i++)
      {
          tls1401BinBuf[i] = 0xfe;
      }
}


//判断是否是一个有效的标记
void judgeValidFlag()
{
    #define HEIDIAN_VALID_NUM_THRESHOLD_MAX   20  //阈值
    #define HEIDIAN_VALID_NUM_THRESHOLD_MIN   3
    
    uint8_t n = 0, i = 0;
    
    memset(heiDian.pos, 0, 128);
    memset(heiDian.validPoint[0], 0, 128);
    memset(heiDian.validPoint[1], 0, 128);
    heiDian.sum = 0;
    heiDian.num = 0;
    //判断是黑点,记录出现黑点的个数和对应位置
    for(i = 0; i < 128; i++)
    {
        if(tls1401BinBuf[i] == 0) 
        {
            heiDian.pos[n++] = i;
            heiDian.sum++; //总黑点数目
        }
    }

    //判断黑点的数目,黑点数目必须要超过一定范围才算有效
    if(heiDian.sum >= HEIDIAN_VALID_NUM_THRESHOLD_MIN && heiDian.sum <= HEIDIAN_VALID_NUM_THRESHOLD_MAX)
    {
        uint8_t f_flag = 0, num=0;
        uint8_t index = 0;
       

        //判断黑点是不是连续的
        for(uint8_t i = 1; i< heiDian.sum; i++)
        {
            if(heiDian.pos[i] - heiDian.pos[i-1] == 1) //判断是不是相邻的点
            {
                if(f_flag == 0){
                    f_flag = 1;
                    heiDian.startPos = i;
                }
                heiDian.num++;
            }
            else
            { 
                f_flag = 0;
                heiDian.num = 0;
                heiDian.startPos = 0;
                index++;
            }
            
            if(heiDian.num >= HEIDIAN_VALID_NUM_THRESHOLD_MIN) //相邻点并且数目超过一定数量,判断有效标记
            {
               memcpy(heiDian.validPoint[index], &heiDian.pos[heiDian.startPos], heiDian.num);
               heiDian.validPoint[index][128] = heiDian.num;
            }
        }       
        
        //当相邻点的黑点超过一定数目才算是有效的
        if(heiDian.validPoint[0][128] != 0)//&& leftMotorEnable && rightMotorEnable)
        {
            uint8_t heiDianMidPos = heiDian.validPoint[0][0] + heiDian.validPoint[0][128]/2;
            
            static uint8_t first = 0;
            static uint32_t leftPeriod = 0, rightPeriod = 0;
            uint8_t speed = 0;
            uint16_t curSpeed = 0;
            
           
            if(f_cameraCheckEnable && cameraPosition >= cameraOriginPosition+6400*3){
               
                if(validCount++ >= 8)
                {
                    validCount = 0;
                    if(cameraMotorStatus != CAMERA_HADFOUND_STATUS){
                        f_cameraCheckEnable = FALSE;
                        CameraMotorStopEnable = TRUE;
                        cameraMotorDstPeriodIndex = 1;
                        //USART_SendData(USART2, heiDianMidPos);
                        cameraMotorStatus = CAMERA_HADFOUND_STATUS;
                    }
                }
            }else
							validCount = 0;
            
             //USART_SendData(USART2, heiDianMidPos);
            
            if(leftMotorEnable && rightMotorEnable)
            {
                adjustHandler(&heiDianMidPos); 
                #if 0
                //判断黑点有效时的起始位置,从而决定电机的转动
                if(heiDianMidPos < 64-10)
                {
                    //50--->10
                    //80--->20
                    //100--->30
                    //150---->50
                    //200--->80
                    //250--->100
                    //300-->100
                   //leftMotorControl(MOTOR_RUN, 0x1e);
                   //rightMotorControl(MOTOR_RUN, 0x22);  
                   leftMotorControl(MOTOR_RUN, leftMotorCurSpeed);
                   rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+100);  
                }
                else if(heiDianMidPos > 64+10)
                {
                   //leftMotorControl(MOTOR_RUN, 0x22);
                   //rightMotorControl(MOTOR_RUN, 0x1e); 
                   leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+100);
                   rightMotorControl(MOTOR_RUN, rightMotorCurSpeed);  
                }
                else
                {
                   //leftMotorControl(MOTOR_RUN, 0x1e);
                   //rightMotorControl(MOTOR_RUN, 0x1e);
                   leftMotorControl(MOTOR_RUN, leftMotorCurSpeed);
                   rightMotorControl(MOTOR_RUN, rightMotorCurSpeed);                    
                }
                #endif
            }
        }else
        validCount =0;
    }
    
    #undef HEIDIAN_VALID_NUM_THRESHOLD_MIN    
    #undef HEIDIAN_VALID_NUM_THRESHOLD_MAX
}

void adjustHandlerLevel1(uint8_t* pos)
{
    //250
    uint8_t midPos = *pos;
    if(midPos < 64 - 3)
    {  
        if(midPos < 64-20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-20);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+50);  
        }
        else if(midPos < 64-50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-40);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+80);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-10);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+30);  
        }
    }
    else if(midPos > 64 - 3)
    {
        if(midPos > 64+20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+50);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-20);  
        }
        else if(midPos > 64+50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+80);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-40);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+30);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-10);  
        }
    }
    else
    {
        leftMotorControl(MOTOR_RUN, leftMotorCurSpeed);
        rightMotorControl(MOTOR_RUN, rightMotorCurSpeed);  
    }
}

void adjustHandlerLevel2(uint8_t* pos)
{
    //300
    uint8_t midPos = *pos;
    if(midPos < 64 - 5)
    {  
        if(midPos < 64-20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-20);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+50);  
        }
        else if(midPos < 64-50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-40);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+80);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-10);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+30);  
        }
    }
    else if(midPos > 64 - 5)
    {
        if(midPos > 64+20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+50);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-20);  
        }
        else if(midPos > 64+50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+80);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-40);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+30);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-10);  
        }
    }
    else
    {
        leftMotorControl(MOTOR_RUN, leftMotorCurSpeed);
        rightMotorControl(MOTOR_RUN, rightMotorCurSpeed);  
    }
}

void adjustHandlerLevel3(uint8_t* pos)
{
    //350
    uint8_t midPos = *pos;
    if(midPos < 64 - 5)
    {  
        if(midPos < 64-20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-20);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+50);  
        }
        else if(midPos < 64-50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-40);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+80);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-10);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+30);  
        }
    }
    else if(midPos > 64 - 5)
    {
        if(midPos > 64+20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+50);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-20);  
        }
        else if(midPos > 64+50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+80);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-40);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+30);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-10);  
        }
    }
    else
    {
        leftMotorControl(MOTOR_RUN, leftMotorCurSpeed);
        rightMotorControl(MOTOR_RUN, rightMotorCurSpeed);  
    }
}

void adjustHandlerLevel4(uint8_t* pos)
{
    //350
    uint8_t midPos = *pos;
    if(midPos < 64 - 5)
    {  
        if(midPos < 64-20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-30);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+30);  
        }
        else if(midPos < 64-50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-50);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+50);
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed-20);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed+20);  
        }
    }
    else if(midPos > 64 - 5)
    {
        if(midPos > 64+20)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+30);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-30);  
        }
        else if(midPos > 64+50)
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+50);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-50);  
        }else
        {
            leftMotorControl(MOTOR_RUN, leftMotorCurSpeed+15);
            rightMotorControl(MOTOR_RUN, rightMotorCurSpeed-15);  
        }
    }
    else
    {
        leftMotorControl(MOTOR_RUN, leftMotorCurSpeed);
        rightMotorControl(MOTOR_RUN, rightMotorCurSpeed);  
    }
}



//处理纠偏
void adjustHandler(uint8_t* midPos)
{
    motorSpeedLevel = motorSpeedLevel1; //600ms/s
    switch(motorSpeedLevel)
    {
        case motorSpeedLevel1:
            adjustHandlerLevel1(midPos);
            break;
        case motorSpeedLevel2:
            adjustHandlerLevel2(midPos);
            break;
        case motorSpeedLevel3:
            adjustHandlerLevel3(midPos);
            break;
        case motorSpeedLevel4:
            adjustHandlerLevel4(midPos);
            break;
        case motorSpeedLevel5:
            break;
    }
}

//采集图像
void TSL1401Sample(void)
{
#define TSL1401_TIME   10   //延时时间

    uint8_t n = TSL1401_SIZE, k = 0;
    uint8_t i;

    TSL1401_CLK(0);             //CLK = 0
    TSL1401_Delay(TSL1401_TIME);
    TSL1401_SI(1);              //SI  = 1
    TSL1401_Delay(TSL1401_TIME);
    TSL1401_CLK(1);             //CLK = 1
    TSL1401_Delay(TSL1401_TIME);

    TSL1401_SI(0);              //SI  = 0
    TSL1401_Delay(TSL1401_TIME);

    while(n--)
    {
        TSL1401_CLK(0);        //CLK = 0
        tls1401DataBuf[k] = ((adcSample(1)&0xff0) >> 4);
        TSL1401_CLK(1);        //CLK = 1
        TSL1401_Delay(TSL1401_TIME);
        k++;
    }
#undef TSL1401_TIME
}

//用于调整曝光时间
void tsl1401Reset()
{
#define TSL1401_RETIME   1

    uint8_t n = TSL1401_SIZE;

    TSL1401_CLK(0);             //CLK = 0
    TSL1401_Delay(TSL1401_RETIME);
    TSL1401_SI(1);              //SI  = 1
    TSL1401_Delay(TSL1401_RETIME);
    TSL1401_CLK(1);             //CLK = 1
    TSL1401_Delay(TSL1401_RETIME);
    TSL1401_SI(0);              //SI  = 0
    TSL1401_Delay(TSL1401_RETIME);

    while(n--)
    {
        TSL1401_CLK(0);             //CLK = 0
        TSL1401_Delay(TSL1401_RETIME);
        TSL1401_CLK(1);             //CLK = 1
        TSL1401_Delay(TSL1401_RETIME);
    }
#undef TSL1401_RETIME
}    
   