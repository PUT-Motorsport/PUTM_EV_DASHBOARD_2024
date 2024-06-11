#include "interface_task.h"
#include "dash.h"
#include "fdcan.h"
#include "cmsis_os2.h"

extern InterfaceData_TypeDef interfaceData;

void Interface_Task(void *argument) {
	for (;;) {
		// LEDs
//		 if(interfaceData.ams_led) {
//				 HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_SET);
//		 } else {
//				 HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_RESET);
//		 }

        if(interfaceData.safety_led) {
                HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_SET);
        } else {
                HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_RESET);
        }

        if(interfaceData.fuse_led) {
                HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_SET);
        } else {
                HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_RESET);
        }

        // Buttons
		if(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port, RTD_BTN_Pin) == GPIO_PIN_RESET) {
			if(interfaceData.rtd_debouncing_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
				interfaceData.ready_to_drive_button = true;
			} else {
				interfaceData.rtd_debouncing_timer += 25;
			}
		} else {
			interfaceData.ready_to_drive_button = false;
			interfaceData.rtd_debouncing_timer = 0;
		}

		if(HAL_GPIO_ReadPin(TSA_BTN_GPIO_Port, TSA_BTN_Pin) == GPIO_PIN_RESET) {
			if(interfaceData.tsa_debouncing_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
				interfaceData.ts_activation_button = true;
			} else {
				interfaceData.tsa_debouncing_timer += 25;
			}
		} else {
			interfaceData.ts_activation_button = false;
			interfaceData.tsa_debouncing_timer = 0;
		}

		if(HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin) == GPIO_PIN_RESET) {
			if(interfaceData.usr_debouncing_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
				interfaceData.user_button = true;
			} else {
				interfaceData.usr_debouncing_timer += 25;
			}
		} else {
			interfaceData.user_button = false;
			interfaceData.usr_debouncing_timer = 0;
		}

		osDelay(25);
	}
}
