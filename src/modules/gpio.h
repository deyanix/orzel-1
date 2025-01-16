#include <stm32l4xx_hal.h>
#include "sys.h"

#ifndef GPIO_H
#define GPIO_H

typedef const struct {
    GPIO_TypeDef* Port;
    uint32_t Pin;
} Gpio_PinTypeDef;

// GPIO Port A
extern Gpio_PinTypeDef __gpioPA0;
extern Gpio_PinTypeDef __gpioPA1;
extern Gpio_PinTypeDef __gpioPA2;
extern Gpio_PinTypeDef __gpioPA3;
extern Gpio_PinTypeDef __gpioPA4;
extern Gpio_PinTypeDef __gpioPA5;
extern Gpio_PinTypeDef __gpioPA6;
extern Gpio_PinTypeDef __gpioPA7;
extern Gpio_PinTypeDef __gpioPA8;
extern Gpio_PinTypeDef __gpioPA9;
extern Gpio_PinTypeDef __gpioPA10;
extern Gpio_PinTypeDef __gpioPA11;
extern Gpio_PinTypeDef __gpioPA12;
extern Gpio_PinTypeDef __gpioPA13;
extern Gpio_PinTypeDef __gpioPA14;
extern Gpio_PinTypeDef __gpioPA15;

// GPIO Port B
extern Gpio_PinTypeDef __gpioPB0;
extern Gpio_PinTypeDef __gpioPB1;
extern Gpio_PinTypeDef __gpioPB2;
extern Gpio_PinTypeDef __gpioPB3;
extern Gpio_PinTypeDef __gpioPB4;
extern Gpio_PinTypeDef __gpioPB5;
extern Gpio_PinTypeDef __gpioPB6;
extern Gpio_PinTypeDef __gpioPB7;
extern Gpio_PinTypeDef __gpioPB8;
extern Gpio_PinTypeDef __gpioPB9;
extern Gpio_PinTypeDef __gpioPB10;
extern Gpio_PinTypeDef __gpioPB11;
extern Gpio_PinTypeDef __gpioPB12;
extern Gpio_PinTypeDef __gpioPB13;
extern Gpio_PinTypeDef __gpioPB14;
extern Gpio_PinTypeDef __gpioPB15;

// GPIO Port C
extern Gpio_PinTypeDef __gpioPC0;
extern Gpio_PinTypeDef __gpioPC1;
extern Gpio_PinTypeDef __gpioPC2;
extern Gpio_PinTypeDef __gpioPC3;
extern Gpio_PinTypeDef __gpioPC4;
extern Gpio_PinTypeDef __gpioPC5;
extern Gpio_PinTypeDef __gpioPC6;
extern Gpio_PinTypeDef __gpioPC7;
extern Gpio_PinTypeDef __gpioPC8;
extern Gpio_PinTypeDef __gpioPC9;
extern Gpio_PinTypeDef __gpioPC10;
extern Gpio_PinTypeDef __gpioPC11;
extern Gpio_PinTypeDef __gpioPC12;
extern Gpio_PinTypeDef __gpioPC13;
extern Gpio_PinTypeDef __gpioPC14;
extern Gpio_PinTypeDef __gpioPC15;

// GPIO Port D
extern Gpio_PinTypeDef __gpioPD2;

// GPIO Port H
extern Gpio_PinTypeDef __gpioPH0;
extern Gpio_PinTypeDef __gpioPH1;

#define GPIO_PA0    (&__gpioPA0)
#define GPIO_PA1    (&__gpioPA1)
#define GPIO_PA2    (&__gpioPA2)
#define GPIO_PA3    (&__gpioPA3)
#define GPIO_PA4    (&__gpioPA4)
#define GPIO_PA5    (&__gpioPA5)
#define GPIO_PA6    (&__gpioPA6)
#define GPIO_PA7    (&__gpioPA7)
#define GPIO_PA8    (&__gpioPA8)
#define GPIO_PA9    (&__gpioPA9)
#define GPIO_PA10   (&__gpioPA10)
#define GPIO_PA11   (&__gpioPA11)
#define GPIO_PA12   (&__gpioPA12)
#define GPIO_PA13   (&__gpioPA13)
#define GPIO_PA14   (&__gpioPA14)
#define GPIO_PA15   (&__gpioPA15)
#define GPIO_PB0    (&__gpioPB0)
#define GPIO_PB1    (&__gpioPB1)
#define GPIO_PB2    (&__gpioPB2)
#define GPIO_PB3    (&__gpioPB3)
#define GPIO_PB4    (&__gpioPB4)
#define GPIO_PB5    (&__gpioPB5)
#define GPIO_PB6    (&__gpioPB6)
#define GPIO_PB7    (&__gpioPB7)
#define GPIO_PB8    (&__gpioPB8)
#define GPIO_PB9    (&__gpioPB9)
#define GPIO_PB10   (&__gpioPB10)
#define GPIO_PB11   (&__gpioPB11)
#define GPIO_PB12   (&__gpioPB12)
#define GPIO_PB13   (&__gpioPB13)
#define GPIO_PB14   (&__gpioPB14)
#define GPIO_PB15   (&__gpioPB15)
#define GPIO_PC0    (&__gpioPC0)
#define GPIO_PC1    (&__gpioPC1)
#define GPIO_PC2    (&__gpioPC2)
#define GPIO_PC3    (&__gpioPC3)
#define GPIO_PC4    (&__gpioPC4)
#define GPIO_PC5    (&__gpioPC5)
#define GPIO_PC6    (&__gpioPC6)
#define GPIO_PC7    (&__gpioPC7)
#define GPIO_PC8    (&__gpioPC8)
#define GPIO_PC9    (&__gpioPC9)
#define GPIO_PC10   (&__gpioPC10)
#define GPIO_PC11   (&__gpioPC11)
#define GPIO_PC12   (&__gpioPC12)
#define GPIO_PC13   (&__gpioPC13)
#define GPIO_PC14   (&__gpioPC14)
#define GPIO_PC15   (&__gpioPC15)
#define GPIO_PD2    (&__gpioPD2)
#define GPIO_PH0    (&__gpioPH0)
#define GPIO_PH1    (&__gpioPH1)

#define GPIO_D0     GPIO_PA3
#define GPIO_D1     GPIO_PA2
#define GPIO_D2     GPIO_PA10
#define GPIO_D3     GPIO_PB3
#define GPIO_D4     GPIO_PB5
#define GPIO_D5     GPIO_PB4
#define GPIO_D6     GPIO_PB10
#define GPIO_D7     GPIO_PA8
#define GPIO_D8     GPIO_PA9
#define GPIO_D9     GPIO_PC7
#define GPIO_D10    GPIO_PB6
#define GPIO_D11    GPIO_PA7
#define GPIO_D12    GPIO_PA6
#define GPIO_D13    GPIO_PA5
#define GPIO_D14    GPIO_PB9
#define GPIO_D15    GPIO_PB8
#define GPIO_A0     GPIO_PA0
#define GPIO_A1     GPIO_PA1
#define GPIO_A2     GPIO_PA4
#define GPIO_A3     GPIO_PB0
#define GPIO_A4     GPIO_PC1
#define GPIO_A5     GPIO_PC0


void GPIO_InitPort(GPIO_TypeDef *port);
void GPIO_DeInitPort(GPIO_TypeDef *port);

void GPIO_Init(Gpio_PinTypeDef *pin, uint32_t mode, uint32_t pull, uint32_t speed);
void GPIO_InitAlternate(Gpio_PinTypeDef *pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate);
void GPIO_DeInit(Gpio_PinTypeDef *pin);

GPIO_PinState GPIO_Read(Gpio_PinTypeDef *pin);
void GPIO_Write(Gpio_PinTypeDef *pin, GPIO_PinState state);
void GPIO_Toggle(Gpio_PinTypeDef *pin);

#endif //GPIO_H