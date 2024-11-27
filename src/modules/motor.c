#include "motor.h"

/**
 * Motor Driver 1
 * Speed PIN        = D3 (Arduino)  = PB3 (Nucleo L476RG)
 * Direction PIN    = D4 (Arduino)  = PB5 (Nucleo L476RG)
 */
const Motor_TypeDef __motor1 = {
    .SpeedPort      = GPIOB,
    .SpeedPin       = GPIO_PIN_3,
    .DirectionPort  = GPIOB,
    .DirectionPin   = GPIO_PIN_5,
};

/**
 * Motor Driver 2
 * Speed PIN        = D11 (Arduino) = PA7 (Nucleo L476RG)
 * Direction PIN    = D12 (Arduino) = PA6 (Nucleo L476RG)
 */
const Motor_TypeDef __motor2 = {
    .SpeedPort      = GPIOA,
    .SpeedPin       = GPIO_PIN_7,
    .DirectionPort  = GPIOA,
    .DirectionPin   = GPIO_PIN_6,
};

/**
 * Motor Driver 3
 * Speed PIN        = D5 (Arduino) = PB4 (Nucleo L476RG)
 * Direction PIN    = D8 (Arduino) = PA9 (Nucleo L476RG)
 */
const Motor_TypeDef __motor3 = {
    .SpeedPort      = GPIOB,
    .SpeedPin       = GPIO_PIN_4,
    .DirectionPort  = GPIOA,
    .DirectionPin   = GPIO_PIN_9,
};

/**
 * Motor Driver 4
 * Speed PIN        = D6 (Arduino) = PB10 (Nucleo L476RG)
 * Direction PIN    = D7 (Arduino) = PA8 (Nucleo L476RG)
 */
const Motor_TypeDef __motor4 = {
    .SpeedPort      = GPIOB,
    .SpeedPin       = GPIO_PIN_10,
    .DirectionPort  = GPIOA,
    .DirectionPin   = GPIO_PIN_8,
};

void Motor_Init(const Motor_TypeDef* motor) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_MotorSpeed;
    GPIO_MotorSpeed.Pin = motor->SpeedPin;
    GPIO_MotorSpeed.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_MotorSpeed.Pull = GPIO_NOPULL;
    GPIO_MotorSpeed.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(motor->SpeedPort, &GPIO_MotorSpeed);

    GPIO_InitTypeDef GPIO_MotorDirection;
    GPIO_MotorDirection.Pin = motor->DirectionPin;
    GPIO_MotorDirection.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_MotorDirection.Pull = GPIO_NOPULL;
    GPIO_MotorDirection.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(motor->DirectionPort, &GPIO_MotorDirection);

    Motor_Write(motor, MOTOR_DIR_FORWARD, MOTOR_SPEED_STOP);
}

inline void Motor_WriteSpeed(const Motor_TypeDef* motor, GPIO_PinState speed) {
    HAL_GPIO_WritePin(motor->SpeedPort, motor->SpeedPin, speed);
}

inline void Motor_WriteDirection(const Motor_TypeDef* motor, GPIO_PinState direction) {
    HAL_GPIO_WritePin(motor->DirectionPort, motor->DirectionPin, direction);
}

inline void Motor_Write(const Motor_TypeDef* motor, GPIO_PinState direction, GPIO_PinState speed) {
    Motor_WriteDirection(motor, direction);
    Motor_WriteSpeed(motor, speed);
}

inline void Motor_Resume(const Motor_TypeDef* motor) {
    Motor_WriteSpeed(motor, MOTOR_SPEED_START);
}

inline void Motor_Pause(const Motor_TypeDef* motor) {
    Motor_WriteSpeed(motor, MOTOR_SPEED_STOP);
}



