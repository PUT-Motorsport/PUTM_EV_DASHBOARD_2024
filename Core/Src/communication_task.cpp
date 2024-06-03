#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "communication_task.h"
#include "dash.h"
#include "fdcan.h"
#include "cmsis_os2.h"

extern osMutexId_t sharedDataMutexHandle;
extern InterfaceData_TypeDef interfaceData;

void Communication_Task(void *argument) {
	for (;;) {
		PUTM_CAN::DashboardMain main = { .rtd_button = 0, };
		main.rtd_button = interfaceData.rtd_button;

		auto frame = PUTM_CAN::Can_tx_message<PUTM_CAN::DashboardMain>(main,
				PUTM_CAN::can_tx_header_DASHBOARD_MAIN);
		frame.send(hfdcan1);

		if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {

			osMutexRelease(sharedDataMutexHandle);
		}
		osDelay(100);
	}
}
