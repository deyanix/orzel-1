#include <stm32l4xx_hal.h>
#include "sys.h"
#include "gpio.h"

#ifndef UART_H
#define UART_H


UART_HandleTypeDef huart2;
UART_HandleTypeDef huart4;

DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart4_tx;

int _write(int file, char *ptr, int len);
int __io_putchar(int ch);

void UART_Init(void);
void UART_InitPerhiph(UART_HandleTypeDef* huart);
void UART_DeInitPerhiph(UART_HandleTypeDef* huart);

void UART2_Init(void);
void UART2_InitPeriph(void);
void UART2_DeInitPeriph(void);

void UART4_Init(void);
void UART4_InitPeriph(void);
void UART4_DeInitPeriph(void);

#endif //UART_H
