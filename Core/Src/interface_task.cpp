#include "interface_task.h"
#include "cmsis_os2.h"
#include "data.h"
#include "fdcan.h"

extern InterfaceData_TypeDef interfaceData;

void Interface_Task(void* argument) {
    for(;;) {
        // LEDs
        if(interfaceData.ams_led) {
            HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_RESET);
        }

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
            if(interfaceData.rtd_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
                interfaceData.rtd_button = true;
            } else {
                interfaceData.rtd_timer += DASH_BUTTON_POOLING_RATE;
            }
        } else {
            interfaceData.rtd_button = false;
            interfaceData.rtd_timer = 0;
        }

        if(HAL_GPIO_ReadPin(TSA_BTN_GPIO_Port, TSA_BTN_Pin) == GPIO_PIN_RESET) {
            if(interfaceData.tsa_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
                interfaceData.tsa_button = true;
            } else {
                interfaceData.tsa_timer += DASH_BUTTON_POOLING_RATE;
            }
        } else {
            interfaceData.tsa_button = false;
            interfaceData.tsa_timer = 0;
        }

        if(HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin) == GPIO_PIN_RESET) {
            if(interfaceData.usr_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
                interfaceData.usr_button = true;
            } else {
                interfaceData.usr_timer += DASH_BUTTON_POOLING_RATE;
            }
        } else {
            interfaceData.usr_button = false;
            interfaceData.usr_timer = 0;
        }

        osDelay(DASH_BUTTON_POOLING_RATE);
    }
}
