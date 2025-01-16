#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

typedef enum {
    ULTRASONIC_RESET             = 0x00,
    ULTRASONIC_READY             = 0x01,
    ULTRASONIC_BUSY              = 0x02,
} Ultrasonic_StateTypeDef;

typedef const struct {
    GPIO_TypeDef* TriggerPort;
    uint32_t TriggerPin;
    GPIO_TypeDef* EchoPort;
    uint32_t EchoPin;
    Ultrasonic_StateTypeDef State;
} Ultrasonic_TypeDef;

extern Ultrasonic_TypeDef __ultrasonicLeft;
extern Ultrasonic_TypeDef __ultrasonicCenter;
extern Ultrasonic_TypeDef __ultrasonicRight;

#define ULTRASONIC_MAX_IDX       3

#define ULTRASONIC_LEFT         (&__ultrasonicLeft)
#define ULTRASONIC_LEFT_IDX     0

#define ULTRASONIC_CENTER       (&__ultrasonicCenter)
#define ULTRASONIC_CENTER_IDX   1

#define ULTRASONIC_RIGHT        (&__ultrasonicRight)
#define ULTRASONIC_RIGHT_IDX    2

void US_Init(void);
void Ultrasonic_Request(Ultrasonic_TypeDef *ultrasonic);

#endif //ULTRASONIC_H
