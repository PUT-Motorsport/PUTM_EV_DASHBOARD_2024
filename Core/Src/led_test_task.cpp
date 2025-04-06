/**
 * @file led_test_task.cpp
 * @brief Implements the Led_Test_Task function.
 *
 * This task is used to test the LED functionality. After a delay of 3000 ms,
 * it clears the led_test flag in the interfaceData and then terminates itself.
 */

#include "led_test_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"

extern InterfaceData_TypeDef interfaceData;

void Led_Test_Task(void* argument) {
    for(;;) {

    	// Wait for 3000 ms before turning off the LED test flag
        osDelay(pdMS_TO_TICKS(3000));

        interfaceData.led_test = false;

        // Terminate the task after testing the LED
        osThreadTerminate(osThreadGetId());
    }
}
