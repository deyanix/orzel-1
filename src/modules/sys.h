#include <stm32l4xx_hal.h>

#ifndef SYS_H
#define SYS_H

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim8;

void Error_Handler(void);
void SystemClock_Config(void);

void SYS_Init(void);
void SYS_HandleError(HAL_StatusTypeDef status);
void SYS_DelayUs(uint32_t delay);
#endif //SYS_H
