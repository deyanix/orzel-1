#include <stm32l4xx_hal.h>
#include "sys.h"
#include "timer.h"

#ifndef ULTRASONIC_H
#define ULTRASONIC_H


typedef struct {
    uint32_t TimeOverAir; // ??
    uint32_t Distance; // cm
    uint32_t NormalizedDistance;
    int32_t Variability;
} Ultrasonic_Distance;

typedef const struct {
    Gpio_PinTypeDef *TriggerPin;
    Gpio_PinTypeDef *EchoPin;
    TIM_HandleTypeDef *Timer;
    uint32_t TimerChannelRising;
    uint32_t TimerChannelFalling;
    Ultrasonic_Distance *Distance;
} Ultrasonic_TypeDef;

extern Ultrasonic_TypeDef __ultrasonicLeft;
extern Ultrasonic_Distance __ultrasonicLeftDistance;
extern Ultrasonic_TypeDef __ultrasonicCenter;
extern Ultrasonic_Distance __ultrasonicCenterDistance;
extern Ultrasonic_TypeDef __ultrasonicRight;
extern Ultrasonic_Distance __ultrasonicRightDistance;

#define ULTRASONIC_MAX_IDX          3

#define ULTRASONIC_LEFT             (&__ultrasonicLeft)
#define ULTRASONIC_LEFT_DISTANCE    (&__ultrasonicLeftDistance)
#define ULTRASONIC_LEFT_IDX         0

#define ULTRASONIC_CENTER           (&__ultrasonicCenter)
#define ULTRASONIC_CENTER_DISTANCE  (&__ultrasonicCenterDistance)
#define ULTRASONIC_CENTER_IDX       1

#define ULTRASONIC_RIGHT            (&__ultrasonicRight)
#define ULTRASONIC_RIGHT_DISTANCE   (&__ultrasonicRightDistance)
#define ULTRASONIC_RIGHT_IDX        2

void Ultrasonic_Init(void);
void Ultrasonic_Request(Ultrasonic_TypeDef *ultrasonic);
void Ultrasonic_Read(Ultrasonic_TypeDef *ultrasonic);

#endif //ULTRASONIC_H
