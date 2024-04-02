#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "communication_task.h"
#include "dash.h"
#include "fdcan.h"
#include "cmsis_os2.h"

extern osMutexId_t sharedDataMutexHandle;

void Communication_Task(void *argument) {
	for (;;) {
		PUTM_CAN::DashMain main = { .counter = 0, };

		auto frame = PUTM_CAN::Can_tx_message<PUTM_CAN::DashMain>(main,
				PUTM_CAN::can_tx_header_DASH_MAIN);
		frame.send(hfdcan1);

		if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
//			sharedData.time += 60;
//			sharedData.rpm += 100;
//			sharedData.rpm %= DASH_RPM_MAX;

			osMutexRelease(sharedDataMutexHandle);
		}
		osDelay(100);
	}
}
