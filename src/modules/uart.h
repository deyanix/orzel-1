#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef UART_H
#define UART_H

#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len);
int __io_putchar(int ch);

void UART_HandleInit(UART_HandleTypeDef* huart);
void UART_HandleDeInit(UART_HandleTypeDef* huart);
void UART_Init(void);

#endif //UART_H
