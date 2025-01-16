#include "gpio.h"

Gpio_PinTypeDef __gpioPA0   = { .Pin = GPIO_PIN_0,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA1   = { .Pin = GPIO_PIN_1,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA2   = { .Pin = GPIO_PIN_2,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA3   = { .Pin = GPIO_PIN_3,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA4   = { .Pin = GPIO_PIN_4,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA5   = { .Pin = GPIO_PIN_5,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA6   = { .Pin = GPIO_PIN_6,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA7   = { .Pin = GPIO_PIN_7,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA8   = { .Pin = GPIO_PIN_8,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA9   = { .Pin = GPIO_PIN_9,  .Port = GPIOA };
Gpio_PinTypeDef __gpioPA10  = { .Pin = GPIO_PIN_10, .Port = GPIOA };
Gpio_PinTypeDef __gpioPA11  = { .Pin = GPIO_PIN_11, .Port = GPIOA };
Gpio_PinTypeDef __gpioPA12  = { .Pin = GPIO_PIN_12, .Port = GPIOA };
Gpio_PinTypeDef __gpioPA13  = { .Pin = GPIO_PIN_13, .Port = GPIOA };
Gpio_PinTypeDef __gpioPA14  = { .Pin = GPIO_PIN_14, .Port = GPIOA };
Gpio_PinTypeDef __gpioPA15  = { .Pin = GPIO_PIN_15, .Port = GPIOA };
Gpio_PinTypeDef __gpioPB0   = { .Pin = GPIO_PIN_0,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB1   = { .Pin = GPIO_PIN_1,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB2   = { .Pin = GPIO_PIN_2,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB3   = { .Pin = GPIO_PIN_3,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB4   = { .Pin = GPIO_PIN_4,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB5   = { .Pin = GPIO_PIN_5,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB6   = { .Pin = GPIO_PIN_6,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB7   = { .Pin = GPIO_PIN_7,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB8   = { .Pin = GPIO_PIN_8,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB9   = { .Pin = GPIO_PIN_9,  .Port = GPIOB };
Gpio_PinTypeDef __gpioPB10  = { .Pin = GPIO_PIN_10, .Port = GPIOB };
Gpio_PinTypeDef __gpioPB11  = { .Pin = GPIO_PIN_11, .Port = GPIOB };
Gpio_PinTypeDef __gpioPB12  = { .Pin = GPIO_PIN_12, .Port = GPIOB };
Gpio_PinTypeDef __gpioPB13  = { .Pin = GPIO_PIN_13, .Port = GPIOB };
Gpio_PinTypeDef __gpioPB14  = { .Pin = GPIO_PIN_14, .Port = GPIOB };
Gpio_PinTypeDef __gpioPB15  = { .Pin = GPIO_PIN_15, .Port = GPIOB };
Gpio_PinTypeDef __gpioPC0   = { .Pin = GPIO_PIN_0,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC1   = { .Pin = GPIO_PIN_1,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC2   = { .Pin = GPIO_PIN_2,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC3   = { .Pin = GPIO_PIN_3,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC4   = { .Pin = GPIO_PIN_4,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC5   = { .Pin = GPIO_PIN_5,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC6   = { .Pin = GPIO_PIN_6,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC7   = { .Pin = GPIO_PIN_7,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC8   = { .Pin = GPIO_PIN_8,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC9   = { .Pin = GPIO_PIN_9,  .Port = GPIOC };
Gpio_PinTypeDef __gpioPC10  = { .Pin = GPIO_PIN_10, .Port = GPIOC };
Gpio_PinTypeDef __gpioPC11  = { .Pin = GPIO_PIN_11, .Port = GPIOC };
Gpio_PinTypeDef __gpioPC12  = { .Pin = GPIO_PIN_12, .Port = GPIOC };
Gpio_PinTypeDef __gpioPC13  = { .Pin = GPIO_PIN_13, .Port = GPIOC };
Gpio_PinTypeDef __gpioPC14  = { .Pin = GPIO_PIN_14, .Port = GPIOC };
Gpio_PinTypeDef __gpioPC15  = { .Pin = GPIO_PIN_15, .Port = GPIOC };
Gpio_PinTypeDef __gpioPD2   = { .Pin = GPIO_PIN_2,  .Port = GPIOD };
Gpio_PinTypeDef __gpioPH0   = { .Pin = GPIO_PIN_0,  .Port = GPIOH };
Gpio_PinTypeDef __gpioPH1   = { .Pin = GPIO_PIN_1,  .Port = GPIOH };

void GPIO_InitPort(GPIO_TypeDef *port) {
    if (port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    }
}

void GPIO_DeInitPort(GPIO_TypeDef *port) {
    if (port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_DISABLE();
    } else if (port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_DISABLE();
    } else if (port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_DISABLE();
    } else if (port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_DISABLE();
    } else if (port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_DISABLE();
    }
}

void GPIO_Init(Gpio_PinTypeDef *pin, uint32_t mode, uint32_t pull, uint32_t speed) {
    GPIO_InitAlternate(pin, mode, pull, speed, GPIO_AF0_TRACE);
}

void GPIO_InitAlternate(Gpio_PinTypeDef *pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin->Pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = speed;
    GPIO_InitStruct.Alternate = alternate;
    HAL_GPIO_Init(pin->Port, &GPIO_InitStruct);
}

void GPIO_DeInit(Gpio_PinTypeDef *pin) {
    HAL_GPIO_DeInit(pin->Port, pin->Pin);
}

GPIO_PinState GPIO_Read(Gpio_PinTypeDef *pin) {
    return HAL_GPIO_ReadPin(pin->Port, pin->Pin);
}

void GPIO_Write(Gpio_PinTypeDef *pin, GPIO_PinState state) {
    HAL_GPIO_WritePin(pin->Port, pin->Pin, state);
}

void GPIO_Toggle(Gpio_PinTypeDef *pin) {
    HAL_GPIO_TogglePin(pin->Port, pin->Pin);
}