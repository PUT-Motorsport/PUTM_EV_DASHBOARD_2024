#include "communication_task.h"
#include "data.h"
#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"

#include "fdcan.h"
#include "iwdg.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "portable.h"
#include "task.h"

#include <algorithm>

extern osMutexId_t sharedDataMutexHandle;

void Communication_Task(void* argument) {
    for(;;) {
        // TX
        bool send_rtd_button = false;
        bool send_tsa_button = false;
        bool send_usr_button = false;

        if(interfaceData.rtd_button && !interfaceData.previous_rtd_button) {
            send_rtd_button = true;
        }
        interfaceData.previous_rtd_button = interfaceData.rtd_button;

        if(interfaceData.tsa_button && !interfaceData.previous_tsa_button) {
            send_tsa_button = true;
        }
        interfaceData.previous_tsa_button = interfaceData.tsa_button;

        if(interfaceData.usr_button && !interfaceData.previous_usr_button) {
            send_usr_button = true;
        }
        interfaceData.previous_usr_button = interfaceData.usr_button;

        // Send only if any button state is updated
        PUTM_CAN::Dashboard frame = {
            .ready_to_drive_button = send_rtd_button,
            .ts_activation_button = send_tsa_button,
            .user_button = send_usr_button,
        };
        auto message = PUTM_CAN::Can_tx_message<PUTM_CAN::Dashboard>(frame, PUTM_CAN::can_tx_header_DASHBOARD);

        message.send(hfdcan1);

        // RX
        uint32_t current_tick_time = xTaskGetTickCount() * portTICK_PERIOD_MS;

        // Frontbox
        if(PUTM_CAN::can.get_pc_new_data()) {
            timeoutData.frontbox_last_frame_time = current_tick_time;
            auto pc_data = PUTM_CAN::can.get_pc_main_data();

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = false;
                sharedData.ready_to_drive = pc_data.rtd;
                sharedData.inverters_ready = pc_data.invertersReady;
                sharedData.inverter_temperature = std::max(pc_data.rearRightInverterTemperature, pc_data.rearLeftInverterTemperature);
                sharedData.oil_temperature = std::max(pc_data.rearRightMotorTemperature, pc_data.rearLeftMotorTemperature);
                sharedData.speed = pc_data.vehicleSpeed;
                sharedData.rpm = pc_data.rpm;
                sharedData.power = pc_data.power;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.frontbox_last_frame_time > DASH_TIMEOUT_DURATION) {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = true;
                sharedData.inverter_temperature = 0;
                sharedData.oil_temperature = 0;
                sharedData.speed = 0;
                sharedData.rpm = 0;
                sharedData.power = 0;

                osMutexRelease(sharedDataMutexHandle);
            }
		}

        // BMS LV
        if(PUTM_CAN::can.get_bms_lv_main_new_data()) {
            timeoutData.bms_lv_last_frame_time = current_tick_time;
            auto bms_lv_main_data = PUTM_CAN::can.get_bms_lv_main();

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.coolant_temperature = bms_lv_main_data.temp_avg;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.bms_lv_last_frame_time > DASH_TIMEOUT_DURATION) {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.coolant_temperature = 0;

                osMutexRelease(sharedDataMutexHandle);
            }
		}

        // BMS HV
        if(PUTM_CAN::can.get_bms_hv_main_new_data()) {
            timeoutData.bms_hv_last_frame_time = current_tick_time;
            auto bms_hv_main_data = PUTM_CAN::can.get_bms_hv_main();

            if(bms_hv_main_data.ok) {
                interfaceData.ams_led = false;
            } else {
                interfaceData.ams_led = true;
            }

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.soc = bms_hv_main_data.soc / 10;
                sharedData.battery_temperature = bms_hv_main_data.temp_max;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.bms_hv_last_frame_time > DASH_TIMEOUT_DURATION) {
			interfaceData.ams_led = true;

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.soc = 0;
                sharedData.battery_temperature = 0;

                osMutexRelease(sharedDataMutexHandle);
            }

		}

        HAL_IWDG_Refresh(&hiwdg); // Every 250 ms

        osDelay(100);
    }
}
