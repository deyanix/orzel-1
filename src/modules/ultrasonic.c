#include "ultrasonic.h"

/**
 * Ultrasonic Left
 */
Ultrasonic_TypeDef __ultrasonicLeft = {
    .TriggerPin       = GPIO_PB13,
    .State            = ULTRASONIC_RESET,
};

/**
 * Ultrasonic Center
 */
Ultrasonic_TypeDef __ultrasonicCenter = {
    .TriggerPin       = GPIO_PB14,
    .State            = ULTRASONIC_RESET,
};

/**
 * Ultrasonic Right
 */
Ultrasonic_TypeDef __ultrasonicRight = {
    .TriggerPin       = GPIO_PB15,
    .State            = ULTRASONIC_RESET,
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
}