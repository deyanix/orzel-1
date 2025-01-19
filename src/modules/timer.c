#include "timer.h"

void Timer_Measure_Start(void) {
    if (htim7.State == HAL_TIM_STATE_READY) {
        Timer7_Start();
    }
}

void Timer_Measure_Stop(void) {
    Timer7_Stop();
}

void Timer_Measure_Reset(void) {
    __HAL_TIM_SET_COUNTER(&htim7, 0);
}

uint32_t Timer_Measure_GetValue(void) {
    return __HAL_TIM_GET_COUNTER(&htim7) / 10;
}

void Timer_DelayUs(uint32_t delay) {
    __HAL_TIM_SET_COUNTER(&htim6, 0);
    while (__HAL_TIM_GET_COUNTER(&htim6) < delay);
}

void Timer_Init(void) {
    Timer1_Init();
    Timer2_Init();
    Timer3_Init();
    Timer4_Init();
    Timer6_Init();
    Timer7_Init();
    //Timer8_Init();
    Timer15_Init();
}

void Timer_Base_Init(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        Timer1_Base_Init();
    } else if (htim->Instance == TIM2) {
        Timer2_Base_Init();
    } else if (htim->Instance == TIM3) {
        Timer3_Base_Init();
    } else if (htim->Instance == TIM4) {
        Timer4_Base_Init();
    } else if (htim->Instance == TIM6) {
        Timer6_Base_Init();
    } else if (htim->Instance == TIM7) {
        Timer7_Base_Init();
    } else if (htim->Instance == TIM8) {
        Timer8_Base_Init();
    } else if (htim->Instance == TIM15) {
        Timer15_Base_Init();
    }
}

void Timer_Base_DeInit(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        Timer1_Base_DeInit();
    } else if (htim->Instance == TIM2) {
        Timer2_Base_DeInit();
    } else if (htim->Instance == TIM3) {
        Timer3_Base_DeInit();
    } else if (htim->Instance == TIM4) {
        Timer4_Base_DeInit();
    } else if (htim->Instance == TIM6) {
        Timer6_Base_DeInit();
    } else if (htim->Instance == TIM7) {
        Timer7_Base_DeInit();
    } else if (htim->Instance == TIM8) {
        Timer8_Base_DeInit();
    } else if (htim->Instance == TIM15) {
        Timer15_Base_DeInit();
    }
}

void Timer_Start(void) {
    Timer1_Start();
    Timer2_Start();
    Timer3_Start();
    Timer4_Start();
    Timer6_Start();
    //Timer8_Start();
    Timer15_Start();
}

void Timer1_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 7999;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim1));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig));
    SYS_HandleError(HAL_TIM_IC_Init(&htim1));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_4));
}

void Timer1_Base_Init(void) {
    GPIO_InitPort(GPIO_PA10->Port);
    GPIO_InitAlternate(GPIO_PA10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF1_TIM1);

    __HAL_RCC_TIM1_CLK_ENABLE();
}

void Timer1_Base_DeInit(void) {
    __HAL_RCC_TIM1_CLK_DISABLE();

    GPIO_DeInit(GPIO_PA10);
}

void Timer1_Start(void) {
    HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_4);
}

void Timer2_Init(void) {
    TIM_ClockConfigTypeDef clockSourceConfig = {0};
    TIM_SlaveConfigTypeDef slaveConfig = {0};
    TIM_MasterConfigTypeDef masterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 79;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0xFFFFFFFF;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim2));

    clockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim2, &clockSourceConfig));
    SYS_HandleError(HAL_TIM_IC_Init(&htim2));

    slaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    slaveConfig.InputTrigger = TIM_TS_TI1F_ED;
    slaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    slaveConfig.TriggerFilter = 0;
    SYS_HandleError(HAL_TIM_SlaveConfigSynchro(&htim2, &slaveConfig));

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim2, &masterConfig));
}

void Timer2_Base_Init(void) {
    __HAL_RCC_TIM2_CLK_ENABLE();
}

void Timer2_Base_DeInit(void) {
    __HAL_RCC_TIM2_CLK_DISABLE();
}

void Timer2_Start(void) {
    SYS_HandleError(HAL_TIM_Base_Start(&htim2));
}

void Timer3_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 7999;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 65535;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim3));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig));
    SYS_HandleError(HAL_TIM_IC_Init(&htim3));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_2));
}

void Timer3_Base_Init(void) {
    GPIO_InitPort(GPIO_PC6->Port);
    GPIO_InitAlternate(GPIO_PC6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM3);

    __HAL_RCC_TIM3_CLK_ENABLE();
}

void Timer3_Base_DeInit(void) {
    __HAL_RCC_TIM3_CLK_DISABLE();

    GPIO_DeInit(GPIO_PC6);
}

void Timer3_Start(void) {
    HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2);
}

void Timer4_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 7999;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 65535;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim4));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig));
    SYS_HandleError(HAL_TIM_IC_Init(&htim4));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_2));
}

void Timer4_Base_Init(void) {
    GPIO_InitPort(GPIOB);
    GPIO_InitAlternate(GPIO_PB6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM4);

    __HAL_RCC_TIM4_CLK_ENABLE();
}

void Timer4_Base_DeInit(void) {
    __HAL_RCC_TIM4_CLK_DISABLE();

    GPIO_DeInit(GPIO_PB6);
}

void Timer4_Start(void) {
    HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_2);
}

void Timer6_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 79;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 0xFFFF;
    htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim6.Init.RepetitionCounter = 0;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim6));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim6, &sClockSourceConfig));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig));
}

void Timer6_Base_Init(void) {
    __HAL_RCC_TIM6_CLK_ENABLE();
}

void Timer6_Base_DeInit(void) {
    __HAL_RCC_TIM6_CLK_DISABLE();
}

void Timer6_Start(void) {
    SYS_HandleError(HAL_TIM_Base_Start(&htim6));
}

void Timer7_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 7999; // 10 kHz -> 0.1 ms
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim7.Init.Period = 0xFFFF;
    htim7.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim7.Init.RepetitionCounter = 0;
    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim7));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim7, &sClockSourceConfig));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig));
}

void Timer7_Base_Init(void) {
    __HAL_RCC_TIM7_CLK_ENABLE();
}

void Timer7_Base_DeInit(void) {
    __HAL_RCC_TIM7_CLK_DISABLE();
}

void Timer7_Start(void) {
    SYS_HandleError(HAL_TIM_Base_Start(&htim7));
}

void Timer7_Stop(void) {
    SYS_HandleError(HAL_TIM_Base_Stop(&htim7));
}

void Timer8_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 7999;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 0xFFFF;
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.RepetitionCounter = 0;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim8));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig));

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
    sBreakDeadTimeConfig.Break2Filter = 0;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    SYS_HandleError(HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig));
}

void Timer8_Base_Init(void) {
    __HAL_RCC_TIM8_CLK_ENABLE();
}

void Timer8_Base_DeInit(void) {
    __HAL_RCC_TIM8_CLK_DISABLE();
}

void Timer8_Start(void) {
    SYS_HandleError(HAL_TIM_Base_Start(&htim8));
}

void Timer15_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    htim15.Instance = TIM15;
    htim15.Init.Prescaler = 79;
    htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim15.Init.Period = 0xFFFF;
    htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim15.Init.RepetitionCounter = 0;
    htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    SYS_HandleError(HAL_TIM_Base_Init(&htim15));

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    SYS_HandleError(HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig));
    SYS_HandleError(HAL_TIM_IC_Init(&htim15));

    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    sSlaveConfig.InputTrigger = TIM_TS_TI1F_ED;
    sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sSlaveConfig.TriggerFilter = 0;
    SYS_HandleError(HAL_TIM_SlaveConfigSynchro(&htim15, &sSlaveConfig));

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    SYS_HandleError(HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig));

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    SYS_HandleError(HAL_TIM_IC_ConfigChannel(&htim15, &sConfigIC, TIM_CHANNEL_1));
}

void Timer15_Base_Init(void) {
    __HAL_RCC_TIM15_CLK_ENABLE();

    GPIO_InitPort(GPIOB);
    GPIO_InitAlternate(GPIO_PB14, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF14_TIM15);

    HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
}

void Timer15_Base_DeInit(void) {
    __HAL_RCC_TIM15_CLK_DISABLE();

    GPIO_DeInit(GPIO_PB14);
    HAL_NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn);
}

void Timer15_Start(void) {
    SYS_HandleError(HAL_TIM_Base_Start(&htim15));
    SYS_HandleError(HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1));
}

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim2);
}

void TIM6_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim6);
}

void TIM8_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim8);
}

void TIM1_BRK_TIM15_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim15);
}