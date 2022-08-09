/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct com_desc  {
    char command[64];
    uint32_t size;
    uint32_t type;
} commands_t;

commands_t cmds[] = {
    [0] = { .command = {'t','e','s','t'},
       .size = 4,
       .type = 1
    },
    [1] = { .command = {'l','e','d',' ','o','n'},
       .size = 6,
       .type = 2
    },
    [2] = { .command = {'l','e','d',' ','o','f','f'},
       .size = 7,
       .type = 3
    },
    [3] = { .command = {'l','e','d',' ','o','f','f',' ','a','l','l'},
       .size = 11,
       .type = 4
    },
    [4] = { .command = {'l','e','d',' ','o','n',' ','a','l','l'},
       .size = 10,
       .type = 5
    },
    [5] = { .command = {'s','u','m','m','a'},
       .size = 5,
       .type = 6
    },
    [6] = { .command = {'l', 'e', 'd', ' ', 't', 'o', 'g', 'g', 'l', 'e'},
        .size = 10,
        .type = 7
    },
    [7] = { .command = {'l', 'e', 'd', ' ', 't', 'o', 'g', 'g', 'l', 'e', ' ', 'a', 'l', 'l'},
        .size = 14,
        .type = 8
    },
    [8] = { .command = {'d','e','l','t','a'},
       .size = 5,
       .type = 9
    }
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
 char buffer[64];
 uint8_t text_buf[64];
 uint8_t usr_input[12] = {0};
 char res;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void Blue_LED_Blink(void);
void Green_LED_Blink(void);
void gpio(void);
void controller(void);
void LCD_GLASS_Clear();
void LCD_GLASS_DisplayString(unsigned char *ptr);
void LCD_GLASS_WriteChar(unsigned char *ch, unsigned char point, unsigned char column, unsigned char position);
void LCD_GLASS_ScrollSentence(unsigned char *ptr, unsigned int nScroll, unsigned int ScrollSpeed);
void tap_button_fire_led (void);
void Commander(char *buffer);

void GPIO_LCD_Pins_Init(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t counter = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    gpio();
    controller();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(LCD->SR & LCD_SR_UDR);
  LCD_GLASS_DisplayString("STM32L");
  LCD->SR |= LCD_SR_UDR;
  HAL_Delay(1000);
//  LCD_GLASS_Clear();
//  uint8_t data[] = "HELLO WORLD \r\n";

  	HAL_UART_Receive_DMA (&huart1,  usr_input, 1);

  while (1)
  {
//      LCD_GLASS_ScrollSentence("      [ https://www.facebook.com/MicroArena ]     ", 1, 200);
//	  tap_button_fire_led();
//	  while( HAL_UART_GetState (&huart1) == HAL_UART_STATE_BUSY_TX ) ;
//	  HAL_UART_Transmit_IT(&huart1, data, sizeof (data));
//	  HAL_Delay(500);


//	  if (HAL_UART_Receive_IT (&huart1, res, 2) == 1) {
//	             HAL_UART_Transmit_IT(&huart1, res, sizeof (res));
//	             strncat (buffer, &res, 1);
//	             if (res == '\r')  {
//	            	 snprintf(res, 2, "\n");
//	            	 HAL_UART_Transmit_IT(&huart1, res, sizeof (res));
//	                 Commander(&buffer[0]);
//	             }
//	         }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (*usr_input == '\r')  {
//		memset(usr_input, 0, 12);
		snprintf(usr_input, 12, "\r\n");
		HAL_UART_Transmit(&huart1, usr_input, 2, 100);
		Commander(buffer);
		} else {
		strncat (buffer, &usr_input, 1);
		HAL_UART_Transmit(&huart1, usr_input, 1, 100);
		}
	HAL_UART_Receive_DMA(&huart1, usr_input, 1);

//	HAL_UART_Transmit(&huart1, usr_input, 1, 100);
//	HAL_UART_Receive_DMA(&huart1, usr_input, 1);
}

void Commander(char *buffer)  {
    uint32_t i;
    uint32_t x;
    float a;
    float b;
    uint32_t cmd_success = 0;
    memset(text_buf, 0, 64);
    LCD_GLASS_Clear();

//    LCD_GLASS_DisplayString(buffer);
//    LCD_GLASS_ScrollSentence(buffer, 1, 200);

    for (i =0; i < sizeof(cmds)/sizeof(commands_t); i++)  {
        if (strncmp(buffer, cmds[i].command, cmds[i].size) == 0) {
            switch(cmds[i].type)  {
                case 1 :
//                	LCD_GLASS_DisplayString(buffer);
//                    LCD_GLASS_ScrollSentence(buffer, 1, 200);
                	snprintf(text_buf, 64, "TEST OK \r\n");
                    HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                    LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    cmd_success = 1;
                    break;
                case 2 :
                    if(isdigit(buffer[7])) {
                        sscanf(&buffer[6], "%d", &x);
                        if (x == 1) {
                        	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
                        } else if (x == 0) {
                        	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
                        } else {
                        	break;
                        }
                        snprintf(text_buf, 64, "LEDON_I OK \r\n");
                        HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                        cmd_success = 1;
                    }
                    break;
                case 3 :
                    if(isdigit(buffer[8])) {
                        sscanf(&buffer[7], "%d", &x);
                        if (x == 1) {
                        	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
                        } else if (x == 0) {
                        	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
                        } else {
                        	break;
                        }
                        snprintf(text_buf, 64, "LEDOFF_I OK \r\n");
                        HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                        LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                        cmd_success = 1;
                    }
                    break;
                case 4 :
                	snprintf(text_buf, 64, "LEDOFF_ALL OK \r\n");
                	HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
                	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
                	LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    cmd_success = 1;
                    break;
                case 5 :
                	snprintf(text_buf, 64, "LEDON_ALL OK \r\n");
                	HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
                	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
                	LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    cmd_success = 1;
                    break;
                case 6 :
//                	snprintf(text_buf, 64, "Summa OK \r\n");
//                	HAL_UART_Transmit(&huart1, text_buf, sizeof (text_buf), 100);
                    sscanf(&buffer[5], "%f %f", &a, &b);
                    a = a + b;
                    memset(buffer, 0, 64);
                    snprintf(text_buf, 64, "SUMMA: %f\r\n", a);
                    HAL_UART_Transmit(&huart1, text_buf, sizeof (text_buf), 100);
                    cmd_success = 1;
                    LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    break;
                case 7 :
                    if (isdigit(buffer[11])) {
                        snprintf(text_buf, 64, "LEDTOGGLE_I OK \r\n");
//                        HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                        HAL_UART_Transmit(&huart1, text_buf, sizeof (text_buf), 100);
                        sscanf(&buffer[10], "%d", &x);
                        if (x == 1) {
                        	HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_6);
                        } else if (x == 0) {
                        	HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_7);
                        } else {
                        	break;
                        }
                        LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                        cmd_success = 1;
                    }
                    break;
                case 8 :
                    snprintf(text_buf, 64, "LEDTOGGLE_ALL OK \r\n");
                    HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                    HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_6);
                    HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_7);
                    LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    cmd_success = 1;
                    break;
                case 9 :
//                    snprintf(text_buf, 64, "Delta OK \r\n");
//                    HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                    sscanf(&buffer[5], "%f %f", &a, &b);
                    a = a - b;
                    memset(buffer, 0, 64);
                    snprintf(text_buf, 64, "DELTA: %f\r\n", a);
                    HAL_UART_Transmit(&huart1, text_buf, sizeof (text_buf), 100);
                    LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    cmd_success = 1;
                    break;
                default :
                	snprintf(text_buf, 64, "UNKNOWN COMMAND \r\n");
                	HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
                	LCD_GLASS_ScrollSentence(text_buf, 1, 200);
                    break;
            }
            if (cmd_success == 1) {
                break;
            }
        }
    }
        if (i == sizeof(cmds)/sizeof(commands_t)) {
        	snprintf(text_buf, 64, "UNKNOWN COMMAND \r\n");
        	HAL_UART_Transmit_IT(&huart1, text_buf, sizeof (text_buf));
        	LCD_GLASS_ScrollSentence(text_buf, 1, 200);
        }
    memset(buffer,0,64);
}

void Green_LED_Blink(void)	{
	  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	  HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_7);
	  HAL_Delay(100);
}

void Blue_LED_Blink(void)	{
	  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	  HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_6);
	  HAL_Delay(100);
}

void gpio(void)
{
RCC->AHBENR |= 0x7;
GPIOA->MODER |= 0x802A00A8;
GPIOB->MODER |= 0xAAAA0A80;
GPIOC->MODER |= 0xAAA0AA;
GPIOA->OTYPER &= ~0x870E;
GPIOB->OTYPER &= ~0xFF38;
GPIOC->OTYPER &= ~0xFCF;
GPIOA->PUPDR &= ~0xC03F00FC;
GPIOB->PUPDR &= ~0xFFFF0FC0;
GPIOC->PUPDR &= ~0xFFF0FF;
GPIOA->OSPEEDR &= ~0xC03F00FC;
GPIOB->OSPEEDR &= ~0xFFFF0FC0;
GPIOC->OSPEEDR &= ~0xFFFFF0FF;
GPIOA->AFR[0] |= 0xBBB0;
GPIOA->AFR[1] |= 0xB0000BBB;
GPIOB->AFR[0] |= 0xBBB000;
GPIOB->AFR[1] |= 0xBBBBBBBB;
GPIOC->AFR[0] |= 0xBB00BBBB;
GPIOC->AFR[1] |= 0xBBBB;
}

void controller(void)
{
RCC->APB1ENR |= 0x10000200;
PWR->CR |= 0x100;
RCC->CSR |= 0x800000;
RCC->CSR &= ~0x800000;
RCC->CSR |= 0x100;
while(!(RCC->CSR&RCC_CSR_LSERDY));
RCC->CSR |= 0x10000;
LCD->CR &= ~0x60;
LCD->CR |= 0x40;
LCD->CR &= ~0x1C;
LCD->CR |= 0xC;
LCD->CR |= 0x80;
LCD->FCR &= ~0x3C00000;
LCD->FCR &= ~0x3C0000;
LCD->FCR |= 0x1040000;
LCD->FCR &= ~0x1C00;
LCD->FCR |= 0x800;
while(!(LCD->SR&LCD_SR_FCRSR));
LCD->CR &= ~0x2;
LCD->CR |= 0x1;
while(!(LCD->SR&LCD_SR_RDY));
while(!(LCD->SR&LCD_SR_ENS));
}

void tap_button_fire_led (void)	{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)	{
			  LCD_GLASS_Clear();
			  counter++;
			  counter = counter % 3;
		  }

	switch (counter) {
		case 0:
		{
			LCD_GLASS_DisplayString("GREEN");
			Green_LED_Blink();
			break;
		}
		case 1:
		{
			LCD_GLASS_DisplayString("BLUE");
			Blue_LED_Blink();
			break;
		}
		case 2:
		{
			HAL_GPIO_WritePin (GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
			LCD_GLASS_DisplayString("PAUSE");
			break;
		}
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
