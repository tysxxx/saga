
#include "iHSV57.h"
#include "motor.h"
#define UART_CONTROL
#include "uart.h"


//初始化
void uartInit()
{
    //GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin = UART_RS232_TX_PIN;	//RS232 TX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART_RS232_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = UART_RS232_RX_PIN;	//RS232 RX
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART_RS232_GPIO_PORT, &GPIO_InitStruct);
    
    //UART
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3, ENABLE);
    USART_InitTypeDef USART_InitStruct;

    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;	
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件数据流控制
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStruct);

    USART_ClearFlag(USART2, USART_FLAG_RXNE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);
}

//发送数据
void usartSendData(USART_TypeDef* USART, uint8_t *buf, uint32_t size)
{
    for(uint32_t i=0; i < size; i++){
        USART_ClearFlag(USART, USART_FLAG_TXE);
        USART_SendData(USART, buf[i]);
        while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);//等待发送完成
    }
}

//发送一个字节
void UsartSendByte(USART_TypeDef* USART, uint8_t ch)
{
	USART_SendData(USART, ch);
	while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);	
}

//发送8位的数组
void UsartSendArray(USART_TypeDef* USART, uint8_t *array, uint16_t num)
{
    uint8_t i;

    for(i=0; i<num; i++)
    {
        UsartSendByte(USART, array[i]);	
    }
    /* 等待发送完成 */
    while(USART_GetFlagStatus(USART, USART_FLAG_TC)==RESET);
}

//发送字符串
void UsartSendString(USART_TypeDef* USART, char *str)
{
    uint32_t k=0;
    do 
    {
      UsartSendByte( USART, *(str + k));
      k++;
    } while(*(str + k)!='\0');

    /* 等待发送完成 */
    while(USART_GetFlagStatus(USART,USART_FLAG_TC)==RESET);
}

//usart2串口中断
void USART2_IRQHandler()
{
    uint16_t recvData;
    static uint8_t index = 0;
	//接收到数据
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        recvData = USART_ReceiveData(USART2);

        UART_RxBuffer[index] = recvData;   
        if(UART_RxBuffer[index-1] == 0x77 && UART_RxBuffer[index] == 0x66)
        {
            index = 0;
            if(UART_RxBuffer[0] == 0x55){
                leftMotorCurSpeed = UART_RxBuffer[1] << 8;
                leftMotorCurSpeed |= UART_RxBuffer[2];
                leftMotorControl(MOTOR_START, leftMotorCurSpeed);
                rightMotorCurSpeed = UART_RxBuffer[3] << 8;
                rightMotorCurSpeed |= UART_RxBuffer[4];
                rightMotorControl(MOTOR_START, rightMotorCurSpeed);
            }
            else if(UART_RxBuffer[0] == 0x88){
                leftMotorControl(MOTOR_RUN, UART_RxBuffer[1]);
                rightMotorControl(MOTOR_RUN, UART_RxBuffer[2]);
            }else if(UART_RxBuffer[0] == 0xaa){
                leftMotorControl(MOTOR_STOP, 0);
                rightMotorControl(MOTOR_STOP, 0);
            }else if(UART_RxBuffer[0] == 0x11)
            {
//                motor3Device.motorInfo.step = cutMoveMotorDevice.motorInfo.step = UART_RxBuffer[1] << 16;
//                motor3Device.motorInfo.step = cutMoveMotorDevice.motorInfo.step |= UART_RxBuffer[2] << 8;
//                motor3Device.motorInfo.step = cutMoveMotorDevice.motorInfo.step |= UART_RxBuffer[3];
               
//                motor3Device.motorInfo.step = UART_RxBuffer[1] << 16;
//                motor3Device.motorInfo.step |= UART_RxBuffer[2] << 8;
//                motor3Device.motorInfo.step |= UART_RxBuffer[3];
//                f_cameraMotorStart = TRUE;
                
                cameraMotorStatus = CAMERA_BACKMOVE_STATUS;
								//cutMoveMotorStatus = CUT_BACKMOVE_STATUS;

            }
            else if(UART_RxBuffer[0] == 0x22)
            {
                cameraMotorStatus = CAMERA_STARTFIND_STATUS;
            }
            else if(UART_RxBuffer[0] == 0x33)
            {
                cutRollMotorCurSpeed = UART_RxBuffer[1] << 8;
                cutRollMotorCurSpeed |= UART_RxBuffer[2];
                rollMotorControl(MOTOR_START, cutRollMotorCurSpeed);
            }
            else if(UART_RxBuffer[0] == 0x44)
            {
                rollMotorControl(MOTOR_STOP, 0);
            }
        }else{
            index++;
        }
	}
}


//usart3串口中断
void USART3_IRQHandler()
{
    
}













