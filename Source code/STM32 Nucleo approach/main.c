/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body (Digital sensor + Buzzer + LED + LCD)
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_host.h"
#include "lcd-i2c.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

int count = 0;   // Counter for detected cars

/* USER CODE BEGIN PV */
// --- Pin configuration (you can change if needed) ---
// Digital presence sensor connected to PE2
#define SENSOR_PIN  GPIO_PIN_2
#define SENSOR_PORT GPIOE

// LED connected to PD14
#define LED_PIN     GPIO_PIN_14
#define LED_PORT    GPIOD

// Buzzer connected to PD13
#define BUZZER_PIN  GPIO_PIN_13
#define BUZZER_PORT GPIOD
/* USER CODE END PV */

/* Function prototypes -------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
void MX_USB_HOST_Process(void);

int main(void)
{
  /* Initialize HAL library (reset peripherals, init flash and Systick) */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_HOST_Init();
  MX_I2C1_Init();

  /* Initialize LCD */
  lcd16x2_i2c_init(&hi2c1);
  lcd16x2_i2c_printf("Detecting Car...");
  HAL_Delay(2500);

  lcd16x2_i2c_clear();
  lcd16x2_i2c_printf("Car detected:");
  lcd16x2_i2c_setCursor(1,0);
  lcd16x2_i2c_printf("%d", count);

  /* Infinite loop */
  while (1)
  {
    MX_USB_HOST_Process();

    /* Read digital sensor state */
    if (HAL_GPIO_ReadPin(SENSOR_PORT, SENSOR_PIN) == GPIO_PIN_SET) 
    {
      // Object detected
      count++;

      // Update LCD with new count
      lcd16x2_i2c_clear();
      lcd16x2_i2c_printf("Car detected:");
      lcd16x2_i2c_setCursor(1,0);
      lcd16x2_i2c_printf("%d", count);

      // Turn ON LED and Buzzer
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
      HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);

      HAL_Delay(500); // Hold alert and debounce
    }
    else
    {
      // No object -> turn OFF LED and Buzzer
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
    }
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators (HSE used as PLL source) */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @retval None
  */
static void MX_I2C1_Init(void)
{
  hi2c1.Instance             = I2C1;
  hi2c1.Init.ClockSpeed      = 100000;
  hi2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1     = 0;
  hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2     = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* Configure sensor pin as input */
  GPIO_InitStruct.Pin  = SENSOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL; // or GPIO_PULLDOWN depending on sensor
  HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);

  /* Configure LED and Buzzer pins as output */
  GPIO_InitStruct.Pin   = LED_PIN | BUZZER_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/**
  * @brief  Error Handler
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
    // Stay here if error
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  // Example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
   
