/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dash.h"
#include "communication_task.h"
#include "interface_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
Data_TypeDef sharedData = {
	.time = 0,
	.warning = true,
	.connection = false,
	.radio = false,
	.battery_temperature = 0,
	.inverter_temperature = 0,
	.oil_temperature = 0,
	.oil_pressure = 0,
	.coolant_temperature = 0,
	.coolant_pressure = 0,
	.speed = 0,
	.soc = 0,
	.rpm = 0,
	.power = 0,
	.distance = 0,
	.range = 0,
};

TimerData_TypeDef timerData = {
	.pace = 0,
	.current_lap = 0,
	.last_lap = 0,
	.best_lap = 0,
};

InterfaceData_TypeDef interfaceData = {
	.state_changed = false,
	.ams_led = true,
	.fuse_led = true,
	.safety_led = true,
	.rtd_button = false,
	.tsa_button = false,
	.usr_button = false,
	.previous_rtd_button = false,
	.previous_tsa_button = false,
	.previous_usr_button = false,
	.rtd_timer = 0,
	.tsa_timer = 0,
	.usr_timer = 0,
};
/* USER CODE END Variables */
/* Definitions for timerTask */
osThreadId_t timerTaskHandle;
const osThreadAttr_t timerTask_attributes = {
  .name = "timerTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for TouchGFXTask */
osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 8192 * 4
};
/* Definitions for communicationTask */
osThreadId_t communicationTaskHandle;
const osThreadAttr_t communicationTask_attributes = {
  .name = "communicationTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for interfaceTask */
osThreadId_t interfaceTaskHandle;
const osThreadAttr_t interfaceTask_attributes = {
  .name = "interfaceTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for sharedDataMutex */
osMutexId_t sharedDataMutexHandle;
const osMutexAttr_t sharedDataMutex_attributes = {
  .name = "sharedDataMutex"
};
/* Definitions for timerDataMutex */
osMutexId_t timerDataMutexHandle;
const osMutexAttr_t timerDataMutex_attributes = {
  .name = "timerDataMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Timer_Task(void *argument);
extern void TouchGFX_Task(void *argument);
extern void Communication_Task(void *argument);
extern void Interface_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName);

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void) {
	/* vApplicationMallocFailedHook() will only be called if
	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
	 function that will get called if a call to pvPortMalloc() fails.
	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
	 timer or semaphore is created. It is also called by various parts of the
	 demo application. If heap_1.c or heap_2.c are used, then the size of the
	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	 to query the size of free heap space that remains (although it does not
	 provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN 2 */
void vApplicationIdleHook(void) {
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
	 task. It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()). If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName) {
	/* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
	 called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* creation of sharedDataMutex */
  sharedDataMutexHandle = osMutexNew(&sharedDataMutex_attributes);

  /* creation of timerDataMutex */
  timerDataMutexHandle = osMutexNew(&timerDataMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of timerTask */
  timerTaskHandle = osThreadNew(Timer_Task, NULL, &timerTask_attributes);

  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

  /* creation of communicationTask */
  communicationTaskHandle = osThreadNew(Communication_Task, NULL, &communicationTask_attributes);

  /* creation of interfaceTask */
  interfaceTaskHandle = osThreadNew(Interface_Task, NULL, &interfaceTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_Timer_Task */
/**
* @brief Function implementing the timerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Timer_Task */
void Timer_Task(void *argument)
{
  /* USER CODE BEGIN timerTask */
  /* Infinite loop */
	for(;;) {
        if(osMutexAcquire(timerDataMutexHandle, osWaitForever) == osOK) {

            osMutexRelease(timerDataMutexHandle);
        }
		osDelay(100);
	}
  /* USER CODE END timerTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

