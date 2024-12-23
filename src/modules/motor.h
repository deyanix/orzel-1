#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef MOTOR_H
#define MOTOR_H

typedef struct {
    GPIO_TypeDef* SpeedPort;
    uint32_t SpeedPin;
    GPIO_TypeDef* DirectionPort;
    uint32_t DirectionPin;
} Motor_TypeDef;

extern const Motor_TypeDef __motor1;
extern const Motor_TypeDef __motor2;
extern const Motor_TypeDef __motor3;
extern const Motor_TypeDef __motor4;

#define MOTOR_DIR_FORWARD   GPIO_PIN_RESET
#define MOTOR_DIR_BACKWARD  GPIO_PIN_SET
#define MOTOR_SPEED_START   GPIO_PIN_SET
#define MOTOR_SPEED_STOP    GPIO_PIN_RESET

#define MOTOR1              (&__motor1)
#define MOTOR2              (&__motor2)
#define MOTOR3              (&__motor3)
#define MOTOR4              (&__motor4)

#define MOTOR_LEFT          MOTOR1
#define MOTOR_RIGHT         MOTOR4

void Motor_Init(const Motor_TypeDef* motor);
void Motor_WriteSpeed(const Motor_TypeDef* motor, GPIO_PinState speed);
void Motor_WriteDirection(const Motor_TypeDef* motor, GPIO_PinState speed);
void Motor_Write(const Motor_TypeDef* motor, GPIO_PinState direction, GPIO_PinState speed);
void Motor_Resume(const Motor_TypeDef* motor);
void Motor_Pause(const Motor_TypeDef* motor);

#endif //MOTOR_H
