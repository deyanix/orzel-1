#include <stm32l4xx_hal.h>
#include "sys.h"
#include "gpio.h"

#ifndef TIMER_H
#define TIMER_H

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim8;

void Timer_DelayUs(uint32_t delay);
void Timer_Init(void);
void Timer_Base_Init(TIM_HandleTypeDef *htim);
void Timer_Base_DeInit(TIM_HandleTypeDef *htim);
void Timer_Start(void);

void Timer2_Init(void);
void Timer2_Base_Init(void);
void Timer2_Base_DeInit(void);
void Timer2_Start(void);

void Timer6_Init(void);
void Timer6_Base_Init(void);
void Timer6_Base_DeInit(void);
void Timer6_Start(void);

void Timer8_Init(void);
void Timer8_Base_Init(void);
void Timer8_Base_DeInit(void);
void Timer8_Start(void);

void TIM2_IRQHandler(void);
void TIM6_IRQHandler(void);
void TIM8_IRQHandler(void);

#endif //TIMER_H