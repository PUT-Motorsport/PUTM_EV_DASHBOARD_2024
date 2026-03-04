/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body - Final Fix for TIM15 & HardFault
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os2.h"
#include "adc.h"
#include "cordic.h"
#include "crc.h"
#include "dac.h"
#include "dcache.h"
#include "dma2d.h"
#include "fdcan.h"
#include "gpu2d.h"
#include "hash.h"
#include "i2c.h"
#include "icache.h"
#include "iwdg.h"
#include "lptim.h"
#include "ltdc.h"
#include "octospi.h"
#include "rng.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mx25lm51245g.h" // Sterownik Flash zewnętrznego
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
#ifdef __cplusplus
extern "C" {
#endif
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void SystemPower_Config(void);
void MX_FREERTOS_Init(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
#ifdef __cplusplus
}
#endif
/* USER CODE END PFP */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* Configure the System Power & Clocks */
  SystemPower_Config();
  SystemClock_Config();
  PeriphCommonClock_Config();

  /* Initialize all configured peripherals (MUST BE BEFORE TOUCHGFX) */
  MX_GPIO_Init();
  MX_DCACHE1_Init();
  MX_DCACHE2_Init();
  MX_ICACHE_Init();
  
  // Te peryferia są krytyczne dla wyświetlacza i pamięci
  MX_DMA2D_Init();
  MX_GPU2D_Init();
  MX_OCTOSPI1_Init(); 
  
  // POPRAWKA: Inicjalizacja TIM15 musi być PRZED użyciem go w sekcji 2
  MX_TIM15_Init();    
  MX_LTDC_Init();

  /* USER CODE BEGIN 2 */
  // 1. Inicjalizacja fizycznej kości Flash MX25LM (Tryb Memory Mapped)
  // Musi być przed MX_TouchGFX_Init(), aby zasoby graficzne były dostępne
  MX25LM51245G_ResetMemory(&hospi1, MX25LM51245G_SPI_MODE, MX25LM51245G_STR_TRANSFER);
  if (MX25LM51245G_EnableSTRMemoryMappedMode(&hospi1, MX25LM51245G_OPI_MODE, MX25LM51245G_4BYTES_SIZE) != MX25LM51245G_OK) 
  {
      Error_Handler(); 
  }

  // 2. Konfiguracja sprzętowa LCD - TERAZ BEZPIECZNA (htim15 nie jest już NULL)
  if(HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1) != HAL_OK) {
      Error_Handler();
  }
  __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 100); // Jasność 60%
  HAL_GPIO_WritePin(LCD_DISP_RESET_GPIO_Port, LCD_DISP_RESET_Pin, GPIO_PIN_SET);

  // 3. Pozostałe LEDy diagnostyczne
  HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  // Inicjalizacja pozostałych peryferiów
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_CORDIC_Init();
  MX_CRC_Init();
  MX_DAC1_Init();
  MX_FDCAN1_Init();
  MX_HASH_Init();
  MX_I2C1_Init();
  MX_I2C4_Init();
  MX_LPTIM2_Init();
  MX_RNG_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_USB_OTG_HS_USB_Init();
  
  // MX_IWDG_Init(); // Wyłączony dla stabilności podczas startu

  /* Initialize TouchGFX */
  MX_TouchGFX_Init();
  MX_TouchGFX_PreOSInit();

  /* USER CODE BEGIN 2_CAN */
  // Konfiguracja filtrów CAN (po MX_FDCAN1_Init)
  FDCAN_FilterTypeDef sFilterConfig;
  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = 0;
  sFilterConfig.FilterID2 = 0;
  if(HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK) {
      Error_Handler();
  }
  if(HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
      Error_Handler();
  }
  if(HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
      Error_Handler();
  }
  /* USER CODE END 2_CAN */

  /* Initialize interrupts */
  MX_NVIC_Init();

  /* Init scheduler */
  osKernelInitialize();
  
  /* Call init function for freertos objects */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here */
  while (1) {
  }
}

/**
  * @brief System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                              |RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = 8;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

void PeriphCommonClock_Config(void) {}

static void SystemPower_Config(void)
{
  HAL_PWREx_EnableVddIO2();
  PWR_PVDTypeDef sConfigPVD = {0};
  sConfigPVD.PVDLevel = PWR_PVDLEVEL_0;
  sConfigPVD.Mode = PWR_PVD_MODE_NORMAL;
  HAL_PWR_ConfigPVD(&sConfigPVD);
  HAL_PWR_EnablePVD();
  HAL_PWREx_DisableUCPDDeadBattery();

  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_NVIC_Init(void)
{
  HAL_NVIC_SetPriority(EXTI6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI6_IRQn);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    HAL_IncTick();
  }
}

void Error_Handler(void)
{
  HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_SET);
  __disable_irq();
  while(1) {}
}