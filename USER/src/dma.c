
#define DMA_CONTROL
#include "dma.h"


//DMA初始化
void DMAInit()
{
	DMA_InitTypeDef DMA_InitStruct; 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	//adc dma
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));//ADC1_DR_Address; //外设地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue; //内存地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;	//方向: 外设到内存
	DMA_InitStruct.DMA_BufferSize = 1;	//传输大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不自增
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;	//内存地址不自增
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //外围数据大小单位,半字16bit
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内存数据单位
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;	//循环模式
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;	//禁止内存到内存的传输
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);

	//uart dma
	//TX
	DMA_InitStruct.DMA_PeripheralBaseAddr = UART2_DR_Address; //外设地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)uart2SendValue; //发射数据地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;	//发射: 内存到外设
	DMA_InitStruct.DMA_BufferSize = 10;	//传输大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不自增
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址不自增
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外围数据大小单位,8bit
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte; //内存数据单位
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;	//正常模式
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;	//禁止内存到内存的传输
	DMA_Init(DMA1_Channel7, &DMA_InitStruct);
	
	//RX
//	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&uart2RecvValue; //接收数据地址
//	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;	//接收: 外设到内存
//	DMA_Init(DMA1_Channel6, &DMA_InitStruct);
	
	/* Enable DMA1 channel1 */
	//DMA_Cmd(DMA1_Channel1, ENABLE);
	//DMA_Cmd(DMA1_Channel6, ENABLE);
	DMA_Cmd(DMA1_Channel7, ENABLE);
	//DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
}