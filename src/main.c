#include <stm32l4xx_hal.h>
#include <stdio.h>

#include "modules/sys.h"
#include "modules/uart.h"
#include "modules/ir.h"
#include "modules/motor.h"
#include "modules/ultrasonic.h"

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
//    IR_HandleCapture(htim);
}

void HAL_MspInit(void) {
    SYS_Init();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base) {
    IR_TIM_Init(htim_base);

    if (htim_base->Instance == TIM8) {
        __HAL_RCC_TIM8_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();

        hdma_tim8_ch1.Instance = DMA2_Channel6;
        hdma_tim8_ch1.Init.Request = DMA_REQUEST_7;
        hdma_tim8_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_tim8_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_tim8_ch1.Init.MemInc = DMA_MINC_ENABLE;
        hdma_tim8_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;
        hdma_tim8_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;
        hdma_tim8_ch1.Init.Mode = DMA_CIRCULAR;
        hdma_tim8_ch1.Init.Priority = DMA_PRIORITY_HIGH;
        if (HAL_DMA_Init(&hdma_tim8_ch1) != HAL_OK) {
            Error_Handler();
        }

        __HAL_LINKDMA(htim_base, hdma[TIM_DMA_ID_CC1], hdma_tim8_ch1);
    }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base) {
//    IR_TIM_DeInit(htim_base);
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
//    HAL_TIM_IRQHandler(&ir_htim);
}

#define PILOT_ON    318
#define PILOT_TIMER 315
#define PILOT_MODE  317
#define PILOT_OFF   319

int main(void) {
    HAL_Init();

    SystemClock_Config();
    UART_Init();
//    IR_Init();
    US_Init();
    Motor_Init(MOTOR_LEFT);
    Motor_Init(MOTOR_RIGHT);

    uint32_t ir_value = 0;

    printf("Start\n");
    while (1) {
        ir_value = IR_GetValue();
        if (ir_value != 0) {
            printf("IR = %04lX\n", ir_value);
        }

        if (ir_value == PILOT_ON) {
            Motor_Write(MOTOR_LEFT, MOTOR_DIR_FORWARD, MOTOR_SPEED_START);
            Motor_Write(MOTOR_RIGHT, MOTOR_DIR_FORWARD, MOTOR_SPEED_START);
        } else if (ir_value == PILOT_MODE) {
            Motor_Write(MOTOR_LEFT, MOTOR_DIR_FORWARD, MOTOR_SPEED_START);
            Motor_Write(MOTOR_RIGHT, MOTOR_DIR_BACKWARD, MOTOR_SPEED_START);
        } else if (ir_value == PILOT_TIMER) {
            Motor_Write(MOTOR_LEFT, MOTOR_DIR_BACKWARD, MOTOR_SPEED_START);
            Motor_Write(MOTOR_RIGHT, MOTOR_DIR_FORWARD, MOTOR_SPEED_START);
        } else if (ir_value == PILOT_OFF) {
            Motor_Pause(MOTOR_LEFT);
            Motor_Pause(MOTOR_RIGHT);
        }
        HAL_Delay(100);
    }
}