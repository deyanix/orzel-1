#include <stm32l4xx_hal.h>

#ifndef SYS_H
#define SYS_H

void Error_Handler(void);
void SystemClock_Config(void);

void SYS_Init(void);
void SYS_HandleError(HAL_StatusTypeDef status);
#endif //SYS_H
