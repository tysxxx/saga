#ifndef __UART_H
#define __UART_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef UART_CONTROL
	#define UART_EXTERN	extern
#else
	#define UART_EXTERN 
#endif
	
#include "global.h"
    
#define UART_RS232_GPIO_PORT    GPIOA
#define UART_RS232_TX_PIN  GPIO_Pin_2
#define UART_RS232_RX_PIN  GPIO_Pin_3
    
//串口接收缓冲数组大小
#define UART_RX_BUFFER_SIZE 256     

//串口接收数组
UART_EXTERN uint8_t UART_RxBuffer[UART_RX_BUFFER_SIZE];
//串口接收数组指针
UART_EXTERN uint8_t UART_RxPtr;

void uartInit();
void usartSendData(USART_TypeDef* USART, uint8_t *buf, uint32_t size);


































#ifdef __cplusplus
}
#endif
#endif
