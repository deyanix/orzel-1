#include <stm32l4xx_hal.h>
#include "sys.h"
#include "gpio.h"

#ifndef MOTOR_H
#define MOTOR_H

typedef const enum {
    MOTOR_BLOCKED = 0x00,
    MOTOR_UNBLOCKED = 0x01,
} Motor_State;

typedef struct {
    Gpio_PinTypeDef *SpeedPin;
    Gpio_PinTypeDef *DirectionPin;
    Motor_State State;
} Motor_TypeDef;

extern Motor_TypeDef __motor1;
extern Motor_TypeDef __motor2;
extern Motor_TypeDef __motor3;
extern Motor_TypeDef __motor4;

#define MOTOR_DIR_FORWARD   GPIO_PIN_RESET
#define MOTOR_DIR_BACKWARD  GPIO_PIN_SET
#define MOTOR_SPEED_START   GPIO_PIN_SET
#define MOTOR_SPEED_STOP    GPIO_PIN_RESET

#define MOTOR1              (&__motor1)
#define MOTOR2              (&__motor2)
#define MOTOR3              (&__motor3)
#define MOTOR4              (&__motor4)

#define MOTOR_LEFT          MOTOR2
#define MOTOR_RIGHT         MOTOR4

void Motor_Init(const Motor_TypeDef* motor);
void Motor_WriteSpeed(const Motor_TypeDef* motor, GPIO_PinState speed);
void Motor_WriteDirection(const Motor_TypeDef* motor, GPIO_PinState speed);
void Motor_Write(const Motor_TypeDef* motor, GPIO_PinState direction, GPIO_PinState speed);
void Motor_Resume(const Motor_TypeDef* motor);
void Motor_Pause(const Motor_TypeDef* motor);

#endif //MOTOR_H
