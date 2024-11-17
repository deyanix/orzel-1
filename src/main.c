#include <stm32l4xx_hal.h>
#include <memory.h>
#include <stdio.h>

#include "modules/sys.h"
#include "modules/uart.h"
#include "modules/ir.h"
#include "modules/motor.h"

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    IR_HandleCapture(htim);
}

void HAL_MspInit(void) {
    SYS_Init();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base) {
    IR_TIM_Init(htim_base);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    UART_HandleInit(huart);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart) {
    UART_HandleDeInit(huart);
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&ir_htim);
}

int main(void) {
    HAL_Init();

    SystemClock_Config();
    UART_Init();
    IR_Init();
    Motor_Init();

    while (1) {
        HAL_Delay(500);
    }
}