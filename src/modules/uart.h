#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef UART_H
#define UART_H

UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len);
int __io_putchar(int ch);

void UART_HandleInit(UART_HandleTypeDef* huart);
void UART_HandleDeInit(UART_HandleTypeDef* huart);
void UART_Init(void);

#endif //UART_H
