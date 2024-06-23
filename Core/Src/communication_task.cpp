#include "communication_task.h"
#include "dash.h"
#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "fdcan.h"
#include "cmsis_os2.h"
#include <algorithm>

extern osMutexId_t sharedDataMutexHandle;
extern Data_TypeDef sharedData;
extern InterfaceData_TypeDef interfaceData;

void Communication_Task(void *argument) {
	for (;;) {
		bool send_rtd_button = false;
		bool send_tsa_button = false;
		bool send_usr_button = false;

		if (interfaceData.rtd_button && !interfaceData.previous_rtd_button) {
			send_rtd_button = true;
		}
		interfaceData.previous_rtd_button = interfaceData.rtd_button;

		if (interfaceData.tsa_button && !interfaceData.previous_tsa_button) {
			send_tsa_button = true;
		}
		interfaceData.previous_tsa_button = interfaceData.tsa_button;

		if (interfaceData.usr_button && !interfaceData.previous_usr_button) {
			send_usr_button = true;
		}
		interfaceData.previous_usr_button = interfaceData.usr_button;

		// Send only if any button state is updated
		PUTM_CAN::Dashboard frame = { .ready_to_drive_button = send_rtd_button,
				.ts_activation_button = send_tsa_button, .user_button =
						send_usr_button, };
		auto message = PUTM_CAN::Can_tx_message<PUTM_CAN::Dashboard>(frame,
				PUTM_CAN::can_tx_header_DASHBOARD);

		message.send(hfdcan1);

		// Receive
		if (PUTM_CAN::can.get_pc_new_data()) {
			auto pc_data = PUTM_CAN::can.get_pc_main_data();
			if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.speed = pc_data.vehicleSpeed;
				sharedData.ready_to_drive = pc_data.rtd;
				sharedData.inverters_ready = pc_data.inverters_ready;
				sharedData.inverter_temperature = std::max(
						std::max(pc_data.frontLeftInverterTemperature,
								pc_data.frontRightInverterTemperature),
						std::max(pc_data.rearLeftIverterTemperature,
								pc_data.rearRightIverterTemperature));
				osMutexRelease(sharedDataMutexHandle);
			}
		}

		if (PUTM_CAN::can.get_rearbox_temperature_new_data()) {
			auto rearbox_temperature_data =
					PUTM_CAN::can.get_rearbox_temperature();

			if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.oil_temperature = std::max(
						rearbox_temperature_data.oil_temperature_l,
						rearbox_temperature_data.oil_temperature_r);
				sharedData.coolant_temperature = std::max(
						rearbox_temperature_data.coolant_temperature_in,
						rearbox_temperature_data.coolant_temperature_out);

				osMutexRelease(sharedDataMutexHandle);
			}
		}

		if (PUTM_CAN::can.get_rearbox_miscellaneous_new_data()) {
			auto rearbox_miscellaneous_data =
					PUTM_CAN::can.get_rearbox_miscellaneous();

			if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.coolant_pressure = std::min(
						rearbox_miscellaneous_data.coolant_pressure_in,
						rearbox_miscellaneous_data.coolant_pressure_out);

				osMutexRelease(sharedDataMutexHandle);
			}
		}

		// TODO: Reset the watchdog
		//HAL_IWDG_Refresh(&hiwdg);

		osDelay(100);
	}
}
