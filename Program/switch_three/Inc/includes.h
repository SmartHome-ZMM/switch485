
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include "main.h"
#include "stm32l0xx_hal.h"

#define BUFFER_SIZE 100
/* uart2 receive  parameter*/
extern uint8_t rx_buffer[];
extern uint8_t tx_buffer[];
extern uint16_t rx_len ;
extern uint8_t recv_end_flag;


void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_LPUART1_UART_Init(void);
void MX_USART2_UART_Init(void);


#endif

