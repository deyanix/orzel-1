#include "ir.h"

IR_Pulse IR_DecodePulse(uint32_t pulseWidth) {
    if (pulseWidth < 300)
        return PULSE_UNKNOWN;
    if (pulseWidth < 900)
        return PULSE_SHORT;
    if (pulseWidth < 1800)
        return PULSE_HIGH;

    return PULSE_UNKNOWN;
}

void IR_Timer_CaptureCallback(TIM_HandleTypeDef *htim) {
    uint32_t pulseWidth;
    IR_Pulse pulse;

    if (htim == &htim2) {
        switch (HAL_TIM_GetActiveChannel(&htim2)) {
            case HAL_TIM_ACTIVE_CHANNEL_1:
                pulseWidth = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
                pulse = IR_DecodePulse(pulseWidth);
                if (pulse != PULSE_UNKNOWN) {
                    IR_CurrentValue <<= 1;
                    if (pulse == PULSE_HIGH) {
                        IR_CurrentValue |= 1;
                    }

                    if (++IR_Counter == IR_BUFFER_LEN) {
                        if (IR_LastValue != IR_CurrentValue) {
                            IR_LastValue = IR_CurrentValue;
                        }
                        IR_Counter = 0;
                        IR_CurrentValue = 0;
                    }
                } else {
                    IR_Counter = 0;
                    IR_CurrentValue = 0;
                }
                break;
            default:
                break;
        }
    }
}

uint16_t IR_GetValue(void) {
    uint16_t value = IR_LastValue;
    IR_LastValue = 0;
    return value;
}