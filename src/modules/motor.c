#include "motor.h"

/**
 * Motor Driver 1
 * Speed PIN        = D3 (Arduino)  = PB3 (Nucleo L476RG)
 * Direction PIN    = D4 (Arduino)  = PB5 (Nucleo L476RG)
 */
Motor_TypeDef __motor1 = {
    .SpeedPin       = GPIO_D3,
    .DirectionPin   = GPIO_D4,
};

/**
 * Motor Driver 2
 * Speed PIN        = D11 (Arduino) = PA7 (Nucleo L476RG)
 * Direction PIN    = D12 (Arduino) = PA6 (Nucleo L476RG)
 */
Motor_TypeDef __motor2 = {
    .SpeedPin       = GPIO_D11,
    .DirectionPin   = GPIO_D12,
};

/**
 * Motor Driver 3
 * Speed PIN        = D5 (Arduino) = PB4 (Nucleo L476RG)
 * Direction PIN    = D8 (Arduino) = PA9 (Nucleo L476RG)
 */
Motor_TypeDef __motor3 = {
    .SpeedPin       = GPIO_D5,
    .DirectionPin   = GPIO_D8,
};

/**
 * Motor Driver 4
 * Speed PIN        = D6 (Arduino) = PB10 (Nucleo L476RG)
 * Direction PIN    = D7 (Arduino) = PA8 (Nucleo L476RG)
 */
Motor_TypeDef __motor4 = {
    .SpeedPin       = GPIO_D6,
    .DirectionPin   = GPIO_D7,
};

void Motor_Init(Motor_TypeDef* motor) {
    GPIO_InitPort(GPIOA);
    GPIO_InitPort(GPIOB);
    GPIO_Init(motor->SpeedPin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_LOW);
    GPIO_Init(motor->DirectionPin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_LOW);
}

inline void Motor_WriteSpeed(Motor_TypeDef* motor, GPIO_PinState speed) {
    GPIO_Write(motor->SpeedPin, speed);
}

inline void Motor_WriteDirection(Motor_TypeDef* motor, GPIO_PinState direction) {
    GPIO_Write(motor->DirectionPin, direction);
}

inline void Motor_Write(Motor_TypeDef* motor, GPIO_PinState direction, GPIO_PinState speed) {
    Motor_WriteDirection(motor, direction);
    Motor_WriteSpeed(motor, speed);
}

inline void Motor_Resume(Motor_TypeDef* motor) {
    Motor_WriteSpeed(motor, MOTOR_SPEED_START);
}

inline void Motor_Pause(Motor_TypeDef* motor) {
    Motor_WriteSpeed(motor, MOTOR_SPEED_STOP);
}