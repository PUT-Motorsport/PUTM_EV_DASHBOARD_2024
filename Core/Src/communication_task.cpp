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

                sharedData.rpm = pc_data.rpm;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.frontbox_last_frame_time > DASH_TIMEOUT_DURATION) {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = true;
                sharedData.inverter_temperature = 0;
                sharedData.oil_temperature = 0;
                sharedData.rpm = 0;


                osMutexRelease(sharedDataMutexHandle);
            }
		}

        //Frontbox Safety
		if(PUTM_CAN::can.get_front_data_main_new_data())
		{
			timeoutData.frontbox_safety_last_frame_time = current_tick_time;
			auto frontbox_safety_data = PUTM_CAN::can.get_front_data_main_data();


			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
			{
				sharedData.warning = false;
				sharedData.safety_front = false;

				safetyData.sense_left_kill = frontbox_safety_data.sense_left_kill;
				safetyData.sense_right_kill = frontbox_safety_data.sense_right_kill;
				safetyData.sense_driver_kill = frontbox_safety_data.sense_driver_kill;
				safetyData.sense_inertia = frontbox_safety_data.sense_inertia;
				safetyData.sense_bspd = frontbox_safety_data.sense_bspd;
				safetyData.sense_overtravel = frontbox_safety_data.sense_overtravel;
				safetyData.sense_right_wheel = frontbox_safety_data.sense_right_wheel;
				safetyData.is_braking = frontbox_safety_data.is_braking;

				osMutexRelease(sharedDataMutexHandle);
			}
		}
		else if(current_tick_time - timeoutData.frontbox_last_frame_time > DASH_TIMEOUT_DURATION)
		{
			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
			{
				sharedData.warning = true;
				sharedData.safety_front = true;

				safetyData.sense_left_kill = false;
				safetyData.sense_right_kill = false;
				safetyData.sense_driver_kill = false;
				safetyData.sense_inertia = false;
				safetyData.sense_bspd = false;
				safetyData.sense_overtravel = false;
				safetyData.sense_right_wheel = false;
				safetyData.is_braking = false;


				osMutexRelease(sharedDataMutexHandle);
			}
		}
        else if(current_tick_time - timeoutData.frontbox_last_frame_time > DASH_TIMEOUT_DURATION)
        {
			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
			{
				sharedData.warning = true;
				//we do not get data from the component so errors are not detected
				sharedData.safety_rear = true;

				safetyData.safety_rfu1 = false;
				safetyData.safety_rfu2 = false;
				safetyData.safety_asms = false;
				safetyData.safety_fw = false;
				safetyData.safety_hv = false;
				safetyData.safety_res = false;
				safetyData.safety_hvd = false;
				safetyData.safety_inv = false;
				safetyData.safety_wheel_fl = false;
				safetyData.safety_wheel_fr = false;
				safetyData.safety_wheel_rl = false;
				safetyData.safety_wheel_rr = false;

				osMutexRelease(sharedDataMutexHandle);
			}
		}


		// RearBox Miscellaneous
		if(PUTM_CAN::can.get_rearbox_miscellaneous_new_data()) {
			timeoutData.rearbox_miscellaneous_last_frame_time = current_tick_time;
			auto rearbox_miscellaneous_data = PUTM_CAN::can.get_rearbox_miscellaneous();

			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.warning = false;

				sharedData.coolant_pressure = std::max(rearbox_miscellaneous_data.coolant_pressure_out, rearbox_miscellaneous_data.coolant_pressure_in);

				osMutexRelease(sharedDataMutexHandle);
			}
		} else if(current_tick_time - timeoutData.bms_lv_last_frame_time > DASH_TIMEOUT_DURATION) {
			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.warning = true;

				sharedData.coolant_pressure = 0;

				osMutexRelease(sharedDataMutexHandle);
			}
		}

		// RearBox Temperature
		if(PUTM_CAN::can.get_rearbox_temperature_new_data()) {
			timeoutData.rearbox_temperatures_last_frame_time = current_tick_time;
			auto rearbox_temperatures_data = PUTM_CAN::can.get_rearbox_temperature();

			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.warning = false;

				sharedData.coolant_temperature = std::max(rearbox_temperatures_data.coolant_temperature_out, rearbox_temperatures_data.coolant_temperature_in);
				sharedData.oil_temperature = std::max(rearbox_temperatures_data.oil_temperature_l, rearbox_temperatures_data.oil_temperature_r);

				osMutexRelease(sharedDataMutexHandle);
			}
		} else if(current_tick_time - timeoutData.bms_lv_last_frame_time > DASH_TIMEOUT_DURATION) {
			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.warning = true;

				sharedData.coolant_temperature = 0;
				sharedData.oil_temperature = 0;

				osMutexRelease(sharedDataMutexHandle);
			}
		}

        // BMS LV
        if(PUTM_CAN::can.get_bms_lv_main_new_data()) {
            timeoutData.bms_lv_last_frame_time = current_tick_time;
            auto bms_lv_main_data = PUTM_CAN::can.get_bms_lv_main();

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
            	sharedData.warning = false;
                //sharedData.coolant_temperature = bms_lv_main_data.temp_avg;
                sharedData.battery_lv_temperature = bms_lv_main_data.temp_avg;
                sharedData.soc_lv = bms_lv_main_data.soc;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.bms_lv_last_frame_time > DASH_TIMEOUT_DURATION) {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
            	sharedData.warning = true;
                //sharedData.coolant_temperature = 0;
                sharedData.battery_lv_temperature = 0;
                sharedData.soc_lv = 0;

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
            	sharedData.warning = false;
                sharedData.soc_hv = bms_hv_main_data.soc / 10;
                sharedData.battery_hv_temperature = bms_hv_main_data.temp_max;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.bms_hv_last_frame_time > DASH_TIMEOUT_DURATION) {
			interfaceData.ams_led = true;

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
            	sharedData.warning = true;
                sharedData.soc_hv = 0;
                sharedData.battery_hv_temperature = 0;

                osMutexRelease(sharedDataMutexHandle);
            }

		}


        // PC
        if(PUTM_CAN::can.get_pc_new_data())
        {
            timeoutData.pc_last_frame_time = current_tick_time;
            auto pc_data = PUTM_CAN::can.get_pc_main_data();


           if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
           {
              sharedData.warning = false;
              sharedData.connection = false;

              //FIXME: Brakuje danych z PC
              //sharedData.motor_front_left_temperature =
              //sharedData.motor_front_right_temperature =
			  sharedData.motor_rear_right_temperature = pc_data.rearRightMotorTemperature;
			  sharedData.motor_rear_left_temperature = pc_data.rearLeftMotorTemperature;
			  sharedData.rpm = pc_data.rpm;

			  sharedData.speed = pc_data.vehicleSpeed;
			  sharedData.power = pc_data.power;

  			 osMutexRelease(sharedDataMutexHandle);
		  }
	     }
        else if(current_tick_time - timeoutData.pc_last_frame_time > DASH_TIMEOUT_DURATION)
        {

		  if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
		  {
			sharedData.warning = true;
			sharedData.connection = true;
			sharedData.motor_rear_right_temperature = 0;
			sharedData.motor_rear_left_temperature = 0;
			sharedData.rpm = 0;
			sharedData.speed = 0;
			sharedData.power = 0;

			osMutexRelease(sharedDataMutexHandle);
		  }
	     }


        HAL_IWDG_Refresh(&hiwdg); // Every 250 ms

        osDelay(100);
    }
}
