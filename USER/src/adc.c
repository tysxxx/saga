#include "uart.h"
#define ADC_CONTROL
#include "adc.h"


//初始化ADC端口
void adcInit()
{
    //GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin = ADC_GPIO_PIN;  //PC0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStruct);
	
    //ADC
    ADC_InitTypeDef ADC_InitStructure;
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //ADC clock = PCLK2/6	 12M
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能外设时钟
	
	ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	    //单通道转换
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //单次转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //非外部触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//通道数
    ADC_Init(ADC1, &ADC_InitStructure);
    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_1Cycles5);
    
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    //ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    
    //ADC_SoftwareStartConvCmd(ADC1, ENABLE); //软件触发转换
}

//采样数据
uint16_t adcSample()
{
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

//多次采样求平均值
uint16_t adcAverageValue(uint8_t count)
{
	uint32_t temp=0;
    if(count==0)
        count = 1;
	for(uint8_t i=0; i< count; i++)
	{
		temp += adcSample();
	}
	return temp/count;
}

//adc中断处理函数
void ADC1_2_IRQHandler()
{
    if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET) //转换结束
    {
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
        adcConversionValue = ADC_GetConversionValue(ADC1);
        f_adcConvSuccess = 1;
    }
}
