#include "uart.h"

int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return 1;
}

void UART_Init(void) {
    UART2_Init();
    UART4_Init();
}

void UART_InitPerhiph(UART_HandleTypeDef* huart) {
    if (huart->Instance == USART2) {
        UART2_InitPeriph();
    } else if (huart->Instance == UART4) {
        UART4_InitPeriph();
    }
}

void UART_DeInitPerhiph(UART_HandleTypeDef* huart) {
    if (huart->Instance == USART2) {
        UART2_DeInitPeriph();
    } else if (huart->Instance == UART4) {
        UART4_DeInitPeriph();
    }
}

void UART2_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    SYS_HandleError(HAL_UART_Init(&huart2));
}

void UART2_InitPeriph(void) {
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    SYS_HandleError(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit));

    __HAL_RCC_USART2_CLK_ENABLE();
    GPIO_InitPort(GPIOA);
    GPIO_InitAlternate(GPIO_PA2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART2);
    GPIO_InitAlternate(GPIO_PA3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART2);
}

void UART2_DeInitPeriph(void) {
    __HAL_RCC_USART2_CLK_DISABLE();
    GPIO_DeInit(GPIO_PA2);
    GPIO_DeInit(GPIO_PA3);
}

void UART4_Init(void) {
    huart4.Instance = UART4;
    huart4.Init.BaudRate = 115200;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    SYS_HandleError(HAL_UART_Init(&huart4));
}

void UART4_InitPeriph(void) {
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART4;
    PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
    SYS_HandleError(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit));

    __HAL_RCC_UART4_CLK_ENABLE();
    GPIO_InitPort(GPIOA);
    GPIO_InitAlternate(GPIO_PA0, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF8_UART4);
    GPIO_InitAlternate(GPIO_PA1, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF8_UART4);

    __HAL_RCC_DMA2_CLK_ENABLE();
    hdma_uart4_rx.Instance = DMA2_Channel5;
    hdma_uart4_rx.Init.Request = DMA_REQUEST_2;
    hdma_uart4_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_uart4_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart4_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart4_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart4_rx.Init.Mode = DMA_NORMAL;
    hdma_uart4_rx.Init.Priority = DMA_PRIORITY_LOW;
    SYS_HandleError(HAL_DMA_Init(&hdma_uart4_rx));
    __HAL_LINKDMA(&huart4, hdmarx, hdma_uart4_rx);

    hdma_uart4_tx.Instance = DMA2_Channel3;
    hdma_uart4_tx.Init.Request = DMA_REQUEST_2;
    hdma_uart4_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_uart4_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart4_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart4_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart4_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart4_tx.Init.Mode = DMA_NORMAL;
    hdma_uart4_tx.Init.Priority = DMA_PRIORITY_LOW;
    SYS_HandleError(HAL_DMA_Init(&hdma_uart4_tx));
    __HAL_LINKDMA(&huart4, hdmatx, hdma_uart4_tx);
}

void UART4_DeInitPeriph(void) {
    GPIO_DeInit(GPIO_PA0);
    GPIO_DeInit(GPIO_PA1);

    __HAL_RCC_UART4_CLK_DISABLE();
    HAL_DMA_DeInit(huart4.hdmarx);
    HAL_DMA_DeInit(huart4.hdmatx);
}