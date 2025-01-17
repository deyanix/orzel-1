#include "ultrasonic.h"

/**
 * Ultrasonic Left
 */
Ultrasonic_Distance __ultrasonicLeftDistance = {0};
Ultrasonic_TypeDef __ultrasonicLeft = {
    .TriggerPin             = GPIO_PB13,
    .EchoPin                = GPIO_PA10,
    .Timer                  = &htim1,
    .TimerChannelRising     = TIM_CHANNEL_3,
    .TimerChannelFalling    = TIM_CHANNEL_4,
    .Distance               = &__ultrasonicLeftDistance,
};

/**
 * Ultrasonic Center
 */
Ultrasonic_Distance __ultrasonicCenterDistance = {0};
Ultrasonic_TypeDef __ultrasonicCenter = {
    .TriggerPin             = GPIO_PB14,
    .EchoPin                = GPIO_PB6,
    .Timer                  = &htim4,
    .TimerChannelRising     = TIM_CHANNEL_1,
    .TimerChannelFalling    = TIM_CHANNEL_2,
    .Distance               = &__ultrasonicCenterDistance,
};

/**
 * Ultrasonic Right
 */
Ultrasonic_Distance __ultrasonicRightDistance = {0};
Ultrasonic_TypeDef __ultrasonicRight = {
    .TriggerPin             = GPIO_PB15,
    .EchoPin                = GPIO_PC6,
    .Timer                  = &htim3,
    .TimerChannelRising     = TIM_CHANNEL_1,
    .TimerChannelFalling    = TIM_CHANNEL_2,
    .Distance               = &__ultrasonicRightDistance,
};

void Ultrasonic_Init(void) {
    GPIO_InitPort(GPIOB);
    GPIO_Init(ULTRASONIC_LEFT->TriggerPin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_FREQ_VERY_HIGH);
    GPIO_Init(ULTRASONIC_CENTER->TriggerPin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_FREQ_VERY_HIGH);
    GPIO_Init(ULTRASONIC_RIGHT->TriggerPin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_FREQ_VERY_HIGH);
}

void Ultrasonic_Request(Ultrasonic_TypeDef *ultrasonic) {
    GPIO_Write(ultrasonic->TriggerPin, GPIO_PIN_SET);
    Timer_DelayUs(10);
    GPIO_Write(ultrasonic->TriggerPin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COUNTER(ultrasonic->Timer, 0);
}

void Ultrasonic_Read(Ultrasonic_TypeDef *ultrasonic) {
    uint32_t start = HAL_TIM_ReadCapturedValue(ultrasonic->Timer, ultrasonic->TimerChannelRising);
    uint32_t stop = HAL_TIM_ReadCapturedValue(ultrasonic->Timer, ultrasonic->TimerChannelFalling);

    uint32_t timeOverAir = stop - start;
    uint32_t distance = (timeOverAir * 34) / 10 / 2;
    int32_t diff = (int32_t) (distance - ultrasonic->Distance->Distance);
    uint32_t diffAbs = (uint32_t) (diff >= 0 ? diff : -diff);

    float alpha = 0.8f;

    Ultrasonic_Distance *ultrasonicDistance = ultrasonic->Distance;
    ultrasonicDistance->TimeOverAir = timeOverAir;
    ultrasonicDistance->Distance = distance;
    ultrasonicDistance->NormalizedDistance = (1-alpha) * (ultrasonicDistance->Distance) + alpha * distance;
    ultrasonicDistance->Variability = (1-alpha) * (ultrasonicDistance->Variability) + alpha * diffAbs;
}