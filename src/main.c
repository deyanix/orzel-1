#include <stm32l476xx.h>
#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_tim.h>

TIM_HandleTypeDef htim2;

// 3 -> PB3
#define M1_SPEED_PIN GPIO_PIN_3
#define M1_SPEED_PORT GPIOB
// 4 -> PB_5
#define M1_DIRECTION_PIN GPIO_PIN_5
#define M1_DIRECTION_PORT GPIOB
// 11 -> PA_7
#define M2_SPEED_PIN GPIO_PIN_7
#define M2_SPEED_PORT GPIOA
// 12 -> PA_6
#define M2_DIRECTION_PIN GPIO_PIN_6
#define M2_DIRECTION_PORT GPIOA

#define N_VAL   64
volatile uint64_t ir_value = 0;
size_t counter = 0;


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    uint32_t new_val;

    if (htim == &htim2) {
        switch (HAL_TIM_GetActiveChannel(&htim2)) {
            case HAL_TIM_ACTIVE_CHANNEL_1:
                new_val = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
                if (counter < N_VAL) {
                    ir_value |= (new_val < 600 ? 1 : 0) << (counter++);
                } else {
                    counter = 0;
                }
                break;
            default:
                break;
        }
    }
}

void HAL_MspInit(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (htim_base->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim2);
}

void Error_Handler(void) {
    __disable_irq();
    while (1);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
        Error_Handler();
    }

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 10;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        Error_Handler();
    }
}


void MX_GPIO_Init(void) {
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

void MX_TIM2_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 79;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 4294967295;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_IC_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    sSlaveConfig.InputTrigger = TIM_TS_TI1F_ED;
    sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sSlaveConfig.TriggerFilter = 0;
    if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
}

int main(void) {
    HAL_Init();

    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM2_Init();

    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

    HAL_GPIO_TogglePin(M1_SPEED_PORT, M1_SPEED_PIN);
    HAL_GPIO_TogglePin(M2_SPEED_PORT, M2_SPEED_PIN);
    HAL_GPIO_TogglePin(M1_DIRECTION_PORT, M1_DIRECTION_PIN);

    while (1) {
        HAL_GPIO_TogglePin(M1_DIRECTION_PORT, M1_DIRECTION_PIN);
        HAL_GPIO_TogglePin(M2_DIRECTION_PORT, M2_DIRECTION_PIN);
        HAL_Delay(1000);
    }
}