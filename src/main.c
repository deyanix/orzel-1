#include <stm32l4xx_hal.h>
#include <stdio.h>
#include <string.h>

#include "modules/sys.h"
#include "modules/uart.h"
#include "modules/ir.h"
#include "modules/motor.h"
#include "modules/ultrasonic.h"

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
    UART_InitPerhiph(huart);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart) {
    UART_DeInitPerhiph(huart);
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

#define PILOT_ON    318
#define PILOT_TIMER 315
#define PILOT_MODE  317
#define PILOT_OFF   319

typedef enum {
    ROBOT_EXPLORE = 0x00,
    ROBOT_OBSERVE1 = 0x01,
    ROBOT_ROTATE1 = 0x02,
    ROBOT_SHIFT = 0x03,
    ROBOT_ROTATE2 = 0x09,
} Robot_State;

uint8_t RobotActive = 0x00;
Robot_State RobotState = ROBOT_EXPLORE;

int main(void) {
    HAL_Init();

    SystemClock_Config();
    Timer_Init();
    UART_Init();
    Ultrasonic_Init();
    Motor_Init(MOTOR_LEFT);
    Motor_Init(MOTOR_RIGHT);

    Timer_Start();

    char tx_data[128];
    printf("Start\n");
    while (1) {
        Ultrasonic_Request(ULTRASONIC_LEFT);
        Ultrasonic_Read(ULTRASONIC_LEFT);
        Ultrasonic_Request(ULTRASONIC_CENTER);
        Ultrasonic_Read(ULTRASONIC_CENTER);
        Ultrasonic_Request(ULTRASONIC_RIGHT);
        Ultrasonic_Read(ULTRASONIC_RIGHT);

        sprintf(tx_data, "%lu;%lu;%lu;%lu;%lu;%lu\n",
                ULTRASONIC_LEFT->Distance->NormalizedDistance,
                ULTRASONIC_LEFT->Distance->Variability,
                ULTRASONIC_CENTER->Distance->NormalizedDistance,
                ULTRASONIC_CENTER->Distance->Variability,
                ULTRASONIC_RIGHT->Distance->NormalizedDistance,
                ULTRASONIC_RIGHT->Distance->Variability);
        HAL_UART_Transmit(&huart2, (uint8_t*) tx_data, strlen(tx_data), HAL_MAX_DELAY);
        HAL_UART_Transmit(&huart4, (uint8_t*) tx_data, strlen(tx_data), HAL_MAX_DELAY);

        uint8_t variabilityLeft = ULTRASONIC_LEFT->Distance->Variability < 10 && ULTRASONIC_LEFT->Distance->NormalizedDistance < 400;
        uint8_t variabilityCenter = ULTRASONIC_CENTER->Distance->Variability < 10 && ULTRASONIC_CENTER->Distance->NormalizedDistance < 400;
        uint8_t variabilityRight = ULTRASONIC_RIGHT->Distance->Variability < 10 && ULTRASONIC_RIGHT->Distance->NormalizedDistance < 400;

        uint8_t distanceLeft = ULTRASONIC_LEFT->Distance->NormalizedDistance >= 30;
        uint8_t distanceCenter = ULTRASONIC_CENTER->Distance->NormalizedDistance >= 30;
        uint8_t distanceRight = ULTRASONIC_RIGHT->Distance->NormalizedDistance >= 30;

        if ((variabilityLeft && !distanceLeft) || (variabilityCenter && !distanceCenter) || (variabilityRight && !distanceRight)) {
            if (RobotState == ROBOT_EXPLORE) {
                RobotState = ROBOT_OBSERVE1;
                Timer_Measure_Start();
                Timer_Measure_Reset();
            } else if (RobotState == ROBOT_SHIFT) {
                RobotState = ROBOT_ROTATE2;
                Timer_Measure_Start();
                Timer_Measure_Reset();
            }
        } else if (variabilityLeft && variabilityCenter && variabilityRight) {
            if (RobotState == ROBOT_OBSERVE1) {
                RobotState = ROBOT_EXPLORE;
                Timer_Measure_Stop();
            }
        }

        switch (IR_GetValue()) {
            case PILOT_ON:
                RobotActive = 0x01;
                Timer_Measure_Start();
                break;
            case PILOT_OFF:
                RobotActive = 0x00;
                Timer_Measure_Stop();
                break;
            default:
                break;
        }

        if (RobotActive) {
            switch (RobotState) {
                case ROBOT_EXPLORE:
                    Motor_WriteSpeed(MOTOR_LEFT, MOTOR_SPEED_START);
                    Motor_WriteSpeed(MOTOR_RIGHT, MOTOR_SPEED_START);
                    Motor_WriteDirection(MOTOR_LEFT, MOTOR_DIR_FORWARD);
                    Motor_WriteDirection(MOTOR_RIGHT, MOTOR_DIR_FORWARD);
                    break;
                case ROBOT_SHIFT:
                    Motor_WriteSpeed(MOTOR_LEFT, MOTOR_SPEED_START);
                    Motor_WriteSpeed(MOTOR_RIGHT, MOTOR_SPEED_START);
                    Motor_WriteDirection(MOTOR_LEFT, MOTOR_DIR_FORWARD);
                    Motor_WriteDirection(MOTOR_RIGHT, MOTOR_DIR_FORWARD);
                    if (Timer_Measure_GetValue() > 1500) {
                        Timer_Measure_Stop();
                        RobotState = ROBOT_ROTATE2;
                    }
                    break;
                case ROBOT_OBSERVE1:
                    Motor_WriteSpeed(MOTOR_LEFT, MOTOR_SPEED_STOP);
                    Motor_WriteSpeed(MOTOR_RIGHT, MOTOR_SPEED_STOP);
                    if (Timer_Measure_GetValue() > 5000) {
                        Timer_Measure_Reset();
                        RobotState = ROBOT_ROTATE1;
                    }
                    break;
                case ROBOT_ROTATE1:
                    Motor_WriteSpeed(MOTOR_LEFT, MOTOR_SPEED_START);
                    Motor_WriteSpeed(MOTOR_RIGHT, MOTOR_SPEED_START);
                    Motor_WriteDirection(MOTOR_LEFT, MOTOR_DIR_BACKWARD);
                    Motor_WriteDirection(MOTOR_RIGHT, MOTOR_DIR_FORWARD);
                    if (Timer_Measure_GetValue() > 750) {
                        Timer_Measure_Reset();
                        RobotState = ROBOT_SHIFT;
                    }
                    break;
                case ROBOT_ROTATE2:
                    Motor_WriteSpeed(MOTOR_LEFT, MOTOR_SPEED_START);
                    Motor_WriteSpeed(MOTOR_RIGHT, MOTOR_SPEED_START);
                    Motor_WriteDirection(MOTOR_LEFT, MOTOR_DIR_BACKWARD);
                    Motor_WriteDirection(MOTOR_RIGHT, MOTOR_DIR_FORWARD);
                    if (Timer_Measure_GetValue() > 750) {
                        printf("STATE -> EXPLORE %lu\n", Timer_Measure_GetValue());
                        Timer_Measure_Reset();
                        RobotState = ROBOT_EXPLORE;
                    }
                    break;
                default:
                    break;
            }
        } else {
            Motor_WriteSpeed(MOTOR_LEFT, MOTOR_SPEED_STOP);
            Motor_WriteSpeed(MOTOR_RIGHT, MOTOR_SPEED_STOP);
        }
        HAL_Delay(100);
    }
}