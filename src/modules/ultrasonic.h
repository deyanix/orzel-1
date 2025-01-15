#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#define US1_TRIG_PIN GPIO_PIN_9
#define US1_TRIG_PORT GPIOA
#define US1_ECHO_PIN GPIO_PIN_7
#define US1_ECHO_PORT GPIOC

TIM_HandleTypeDef htim4;

void US_Init(void);

#endif //ULTRASONIC_H
