#include "interface_task.h"
#include "dash.h"
#include "fdcan.h"
#include "cmsis_os2.h"

void Interface_Task(void *argument) {
	for (;;) {
//		if(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port, RTD_BTN_Pin) == GPIO_PIN_RESET) {
//			HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, USR_LED_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, USR_LED_Pin, GPIO_PIN_SET);
//		} else {
//			HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, USR_LED_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, USR_LED_Pin, GPIO_PIN_RESET);
//		}

		osDelay(100);
	}
}
