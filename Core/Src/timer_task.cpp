#include "timer_task.h"
#include "cmsis_os2.h"

void Timer_Task(void *argument) {
	for (;;) {

		osDelay(100);
	}
}
