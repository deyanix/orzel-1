#include <stm32l4xx_hal.h>
#include <stdio.h>
#include "sys.h"
#include "timer.h"

#ifndef IR_H
#define IR_H

#define IR_BUFFER_LEN   11

typedef enum {
    PULSE_SHORT,
    PULSE_HIGH,
    PULSE_UNKNOWN,
} IR_Pulse;

uint16_t IR_LastValue;
uint16_t IR_CurrentValue;
size_t IR_Counter;

IR_Pulse IR_DecodePulse(uint32_t pulseWidth);
void IR_Timer_CaptureCallback(TIM_HandleTypeDef *htim);
uint16_t IR_GetValue(void);

#endif //IR_H
