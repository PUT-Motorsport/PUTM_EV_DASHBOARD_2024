#include "led_test_task.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "data.h"

extern InterfaceData_TypeDef interfaceData;

void Led_Test_Task(void* argument) {
    for(;;) {
        osDelay(pdMS_TO_TICKS(3000));

        interfaceData.led_test = false;

        osThreadTerminate(osThreadGetId());
    }
}
