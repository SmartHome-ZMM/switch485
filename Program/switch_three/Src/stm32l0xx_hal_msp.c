/**
  ******************************************************************************
  * File Name          : stm32l0xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization
  *                      and de-Initialization codes.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
extern DMA_HandleTypeDef hdma_lpuart1_rx;
extern DMA_HandleTypeDef hdma_lpuart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

extern void _Error_Handler(char *, int);
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	/* System interrupt init*/
	/* SVC_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SVC_IRQn, 0, 0);
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	if(huart->Instance == LPUART1)
	{
		/* USER CODE BEGIN LPUART1_MspInit 0 */

		/* USER CODE END LPUART1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_DMA1_CLK_ENABLE();
		__HAL_RCC_LPUART1_CLK_ENABLE();

		/**LPUART1 GPIO Configuration
		PA0-CK_IN     ------> LPUART1_RX
		PA1     ------> LPUART1_TX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_LPUART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* LPUART1 DMA Init */
		/* LPUART1_RX Init */
		hdma_lpuart1_rx.Instance = DMA1_Channel3;
		hdma_lpuart1_rx.Init.Request = DMA_REQUEST_5;
		hdma_lpuart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_lpuart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_lpuart1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_lpuart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_lpuart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_lpuart1_rx.Init.Mode = DMA_NORMAL;
		hdma_lpuart1_rx.Init.Priority = DMA_PRIORITY_LOW;

		if (HAL_DMA_Init(&hdma_lpuart1_rx) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(huart, hdmarx, hdma_lpuart1_rx);
		
		/* LPUART1_RX Init */
		hdma_lpuart1_tx.Instance = DMA1_Channel2;
		hdma_lpuart1_tx.Init.Request = DMA_REQUEST_5;
		hdma_lpuart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_lpuart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_lpuart1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_lpuart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_lpuart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_lpuart1_tx.Init.Mode = DMA_NORMAL;
		hdma_lpuart1_tx.Init.Priority = DMA_PRIORITY_LOW;

		if (HAL_DMA_Init(&hdma_lpuart1_tx) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(huart, hdmatx, hdma_lpuart1_tx);

		/* LPUART1 interrupt Init */
		
		HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
		
		HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(LPUART1_IRQn);
		/* USER CODE BEGIN LPUART1_MspInit 1 */

		/* USER CODE END LPUART1_MspInit 1 */
	}
	else if(huart->Instance == USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		/**USART2 GPIO Configuration
		PA9     ------> USART2_TX
		PA10     ------> USART2_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART2 DMA Init */
		/* USART2_RX Init */
		hdma_usart2_rx.Instance = DMA1_Channel5;
		hdma_usart2_rx.Init.Request = DMA_REQUEST_4;
		hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart2_rx.Init.Mode = DMA_NORMAL;
		hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;

		if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(huart, hdmarx, hdma_usart2_rx);

		/* USART2_RX Init */
		hdma_usart2_tx.Instance = DMA1_Channel4;
		hdma_usart2_tx.Init.Request = DMA_REQUEST_4;
		hdma_usart2_tx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart2_tx.Init.Mode = DMA_NORMAL;
		hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;

		if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(huart, hdmatx, hdma_usart2_tx);
		/* USART2 interrupt Init */
		HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */
	}

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

	if(huart->Instance == LPUART1)
	{
		/* USER CODE BEGIN LPUART1_MspDeInit 0 */

		/* USER CODE END LPUART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_LPUART1_CLK_DISABLE();

		/**LPUART1 GPIO Configuration
		PA0-CK_IN     ------> LPUART1_RX
		PA1     ------> LPUART1_TX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);

		/* LPUART1 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmarx);

		/* LPUART1 interrupt DeInit */
		HAL_NVIC_DisableIRQ(AES_RNG_LPUART1_IRQn);
		/* USER CODE BEGIN LPUART1_MspDeInit 1 */

		/* USER CODE END LPUART1_MspDeInit 1 */
	}
	else if(huart->Instance == USART2)
	{
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
		PA9     ------> USART2_TX
		PA10     ------> USART2_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

		/* USART2 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmarx);

		/* USART2 interrupt DeInit */
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
