#include "ir.h"

ir_pulse_t IR_DecodePulse(uint32_t pulseWidth) {
    if (pulseWidth < 300)
        return PULSE_UNKNOWN;
    if (pulseWidth < 900)
        return PULSE_SHORT;
    if (pulseWidth < 1800)
        return PULSE_HIGH;

    return PULSE_UNKNOWN;
}

void IR_Init(void) {
    ir_htim.Instance = TIM2;
    ir_htim.Init.Prescaler = 79;
    ir_htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    ir_htim.Init.Period = 0xFFFFFFFF;
    ir_htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    ir_htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&ir_htim));

    TIM_ClockConfigTypeDef clockSourceConfig = {0};
    clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&ir_htim, &clockSourceConfig));
    SYS_HandleError(HAL_TIM_IC_Init(&ir_htim));

    TIM_SlaveConfigTypeDef slaveConfig = {0};
    slaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    slaveConfig.InputTrigger = TIM_TS_TI1F_ED;
    slaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    slaveConfig.TriggerFilter = 0;
    SYS_HandleError(HAL_TIM_SlaveConfigSynchro(&ir_htim, &slaveConfig));

    TIM_MasterConfigTypeDef masterConfig = {0};
    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&ir_htim, &masterConfig));

    TIM_IC_InitTypeDef configIC = {0};
    configIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    configIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    configIC.ICPrescaler = TIM_ICPSC_DIV1;
    configIC.ICFilter = 0;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&ir_htim, &configIC, TIM_CHANNEL_1));

    SYS_HandleError(HAL_TIM_Base_Start(&ir_htim));
    SYS_HandleError(HAL_TIM_IC_Start_IT(&ir_htim, TIM_CHANNEL_1));
}

void IR_TIM_Init(TIM_HandleTypeDef* htim_base) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (htim_base->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

void IR_TIM_DeInit(TIM_HandleTypeDef* htim_base) {
    if (htim_base->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
        HAL_NVIC_DisableIRQ(TIM2_IRQn);
    }
}

void IR_HandleCapture(TIM_HandleTypeDef *htim) {
    uint32_t pulseWidth;
    ir_pulse_t pulse;

    if (htim == &ir_htim) {
        switch (HAL_TIM_GetActiveChannel(&ir_htim)) {
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