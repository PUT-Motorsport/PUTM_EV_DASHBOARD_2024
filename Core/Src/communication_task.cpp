#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "communication_task.h"
#include "dash.h"
#include "fdcan.h"
#include "cmsis_os2.h"

extern osMutexId_t sharedDataMutexHandle;
extern InterfaceData_TypeDef interfaceData;
extern Data_TypeDef sharedData;

void Communication_Task(void *argument) {
	for (;;) {
		PUTM_CAN::Dashboard frame = {
				.ready_to_drive_button = interfaceData.ready_to_drive_button,
				.ts_activation_button = interfaceData.ts_activation_button,
				.user_button = interfaceData.user_button,
		};
		auto message = PUTM_CAN::Can_tx_message<PUTM_CAN::Dashboard>(frame,
				PUTM_CAN::can_tx_header_DASHBOARD);

		message.send(hfdcan1);

		// Receive
		if (PUTM_CAN::can.get_pc_new_data()) {
			auto pc_data = PUTM_CAN::can.get_pc_main_data();
			if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.time += 1;
				sharedData.speed = pc_data.vehicleSpeed;
				osMutexRelease(sharedDataMutexHandle);
			}
		}

		osDelay(100);
	}
}
