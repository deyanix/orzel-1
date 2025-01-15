#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef IR_H
#define IR_H

#define IR_BUFFER_LEN   11

typedef enum {
    PULSE_SHORT,
    PULSE_HIGH,
    PULSE_UNKNOWN,
} ir_pulse_t;

TIM_HandleTypeDef ir_htim;

uint16_t IR_LastValue;
uint16_t IR_CurrentValue;
size_t IR_Counter;

ir_pulse_t IR_DecodePulse(uint32_t pulseWidth);
void IR_Init(void);
void IR_TIM_Init(TIM_HandleTypeDef* htim_base);
void IR_TIM_DeInit(TIM_HandleTypeDef* htim_base);
void IR_HandleCapture(TIM_HandleTypeDef *htim);
uint16_t IR_GetValue(void);

#endif //IR_H
