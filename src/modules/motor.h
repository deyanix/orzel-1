#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef MOTOR_H
#define MOTOR_H

#define M1_SPEED_PIN GPIO_PIN_3
#define M1_SPEED_PORT GPIOB
#define M1_DIRECTION_PIN GPIO_PIN_5
#define M1_DIRECTION_PORT GPIOB
#define M2_SPEED_PIN GPIO_PIN_7
#define M2_SPEED_PORT GPIOA
#define M2_DIRECTION_PIN GPIO_PIN_6
#define M2_DIRECTION_PORT GPIOA

void Motor_Init(void);

#endif //MOTOR_H
