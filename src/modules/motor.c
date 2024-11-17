#include "motor.h"

void Motor_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_M1_Speed;
    GPIO_M1_Speed.Pin = M1_SPEED_PIN;
    GPIO_M1_Speed.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_M1_Speed.Pull = GPIO_NOPULL;
    GPIO_M1_Speed.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(M1_SPEED_PORT, &GPIO_M1_Speed);

    GPIO_InitTypeDef GPIO_M1_Direction;
    GPIO_M1_Direction.Pin = M1_DIRECTION_PIN;
    GPIO_M1_Direction.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_M1_Direction.Pull = GPIO_NOPULL;
    GPIO_M1_Direction.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(M1_DIRECTION_PORT, &GPIO_M1_Direction);

    GPIO_InitTypeDef GPIO_M2_Speed;
    GPIO_M2_Speed.Pin = M2_SPEED_PIN;
    GPIO_M2_Speed.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_M2_Speed.Pull = GPIO_NOPULL;
    GPIO_M2_Speed.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(M2_SPEED_PORT, &GPIO_M2_Speed);

    GPIO_InitTypeDef GPIO_M2_Direction;
    GPIO_M2_Direction.Pin = M2_DIRECTION_PIN;
    GPIO_M2_Direction.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_M2_Direction.Pull = GPIO_NOPULL;
    GPIO_M2_Direction.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(M2_DIRECTION_PORT, &GPIO_M2_Direction);
}