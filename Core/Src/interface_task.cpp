#include "interface_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"
#include "gpio.h"
#include "main.h"

void Interface_Task(void* argument) {

	volatile uint32_t last_button_cs_press = 0;

    for(;;) {
        // LEDs
        if(interfaceData.ams_led || interfaceData.led_test) {
            HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_RESET);
        }

        if(sharedData.safety_front || sharedData.safety_rear) {
            HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_RESET);
        }

        if(interfaceData.precharge_status) {
            HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_RESET);
        }



        // Buttons
        //RDT button
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

        //TSA button
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

        //Change screen button
        if(HAL_GPIO_ReadPin(CS_BTN_GPIO_Port, CS_BTN_Pin) == GPIO_PIN_RESET)
        {
            	uint32_t current_time = HAL_GetTick();

            		if((current_time - last_button_cs_press) >= 1000)
            		{
            			interfaceData.cs_button = true;
            			last_button_cs_press = current_time;
            		}
            		else
            		{
            			interfaceData.cs_button = false;
            		}
         }


        //Usr button (free)
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

        //DRS button
        if(HAL_GPIO_ReadPin(DRS_BTN_GPIO_Port, DRS_BTN_Pin) == GPIO_PIN_RESET)
        {
            if(interfaceData.drs_timer >= DASH_BUTTON_DEBOUNCING_TIME)
            {
                interfaceData.drs_button = !interfaceData.drs_button;
            }
            else
            {
                interfaceData.drs_timer += DASH_BUTTON_POOLING_RATE;
            }
        }


        osDelay(pdMS_TO_TICKS(DASH_BUTTON_POOLING_RATE));
    }
}
