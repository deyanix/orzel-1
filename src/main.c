#include <stm32l4xx_hal.h>
#include <stdio.h>

#include "modules/sys.h"
#include "modules/uart.h"
#include "modules/ir.h"
#include "modules/motor.h"
#include "modules/ultrasonic.h"

uint8_t currentSensor = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    Ultrasonic_TypeDef *ultrasonic;

    if (htim->Instance == TIM8) {
        currentSensor = (currentSensor + 1) % ULTRASONIC_MAX_IDX;
        switch (currentSensor) {
            case ULTRASONIC_LEFT_IDX: ultrasonic = ULTRASONIC_LEFT; break;
            case ULTRASONIC_CENTER_IDX: ultrasonic = ULTRASONIC_CENTER; break;
            case ULTRASONIC_RIGHT_IDX: ultrasonic = ULTRASONIC_RIGHT; break;
            default: return;
        }

        Ultrasonic_Request(ultrasonic);
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    IR_Timer_CaptureCallback(htim);
}

void HAL_MspInit(void) {
    SYS_Init();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base) {
    Timer_Base_Init(htim_base);
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base) {
    Timer_Base_DeInit(htim_base);
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

#define PILOT_ON    318
#define PILOT_TIMER 315
#define PILOT_MODE  317
#define PILOT_OFF   319

int main(void) {
    HAL_Init();

    SystemClock_Config();
    Timer_Init();
    UART_Init();
    Ultrasonic_Init();
    Motor_Init(MOTOR_LEFT);
    Motor_Init(MOTOR_RIGHT);

    Timer_Start();

    uint32_t ir_value = 0;

    printf("Start\n");
    while (1) {
        ir_value = IR_GetValue();
        if (ir_value != 0) {
            printf("IR = %04lu\n", ir_value);
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