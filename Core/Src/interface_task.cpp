/**
 * @file interface_task.cpp
 * @brief Implements the Interface_Task function.
 *
 * This task handles the user interface aspects such as reading button states
 * and controlling the status of LEDs. It debounces button inputs and updates
 * the interfaceData and sharedData structures accordingly.
 */

#include "interface_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"
#include "gpio.h"
#include "main.h"

void Interface_Task(void* argument) {

	volatile uint32_t last_button_cs_press = 0;

    for(;;) {
        // LEDs update:
        // Set AMS LED based on ams_led flag or led_test flag.
        if(interfaceData.ams_led || interfaceData.led_test) {
            HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_RESET);
        }


        // Set SAFETY LED based on safety status.
        if(sharedData.safety_front || sharedData.safety_rear) {
            HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(SAFETY_LED_GPIO_Port, SAFETY_LED_Pin, GPIO_PIN_RESET);
        }


        // Set FUSE LED based on precharge status.
        if(interfaceData.precharge_status) {
            HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(FUSE_LED_GPIO_Port, FUSE_LED_Pin, GPIO_PIN_RESET);
        }



        // Buttons processing:
        // RTD button
        if(HAL_GPIO_ReadPin(RTD_BTN_GPIO_Port, RTD_BTN_Pin) == GPIO_PIN_RESET) {
            if(interfaceData.rtd_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
                interfaceData.rtd_button = true;
                sharedData.rtd_button_pressed = true;
            } else {
                interfaceData.rtd_timer += DASH_BUTTON_POOLING_RATE;
            }
        } else {
            interfaceData.rtd_button = false;
            sharedData.rtd_button_pressed = false;
            interfaceData.rtd_timer = 0;
        }

        // TSA button
        if(HAL_GPIO_ReadPin(TSA_BTN_GPIO_Port, TSA_BTN_Pin) == GPIO_PIN_RESET) {
            if(interfaceData.tsa_timer >= DASH_BUTTON_DEBOUNCING_TIME) {
                interfaceData.tsa_button = true;
                sharedData.tsa_button_pressed = true;
            } else {
                interfaceData.tsa_timer += DASH_BUTTON_POOLING_RATE;
            }
        } else {
            interfaceData.tsa_button = false;
            sharedData.tsa_button_pressed = false;
            interfaceData.tsa_timer = 0;
        }

        // Change screen (CS) button with debouncing
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

        // DRS button: toggles its state when pressed
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

        // Delay between polling cycles
        osDelay(pdMS_TO_TICKS(DASH_BUTTON_POOLING_RATE));
    }
}
