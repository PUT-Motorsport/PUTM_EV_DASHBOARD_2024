/**
 * @file communication_task.cpp
 * @brief Implements the Communication_Task function.
 *
 * This task is responsible for handling CAN communication. It sends CAN messages based on
 * changes in button states, receives various CAN data packets (from frontbox, rearbox, BMS, etc.),
 * updates shared and safety data structures accordingly, and refreshes the watchdog.
 *
 * The task continuously runs in a loop, periodically processing and updating data.
 */


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
extern osMutexId_t sdcDataMutexHandle;

void Communication_Task(void* argument) {
    for(;;) {
    	// TX: Determine which buttons have changed state and prepare a CAN frame
        bool send_rtd_button = false;
        bool send_tsa_button = false;
        bool send_drs_button = false;

        // Check RTD button state change
        if(interfaceData.rtd_button && !interfaceData.previous_rtd_button) {
            send_rtd_button = true;
        }
        interfaceData.previous_rtd_button = interfaceData.rtd_button;

        // Check TSA button state change
        if(interfaceData.tsa_button && !interfaceData.previous_tsa_button) {
            send_tsa_button = true;
        }
        interfaceData.previous_tsa_button = interfaceData.tsa_button;

        // Check DRS button state change
        if(interfaceData.drs_button && !interfaceData.previous_drs_button) {
            send_drs_button = true;
        }
        interfaceData.previous_drs_button = interfaceData.drs_button;

        // Create and send a CAN message with updated button states
        // Send only if any button state is updated
        PUTM_CAN::Dashboard frame = {
            .ready_to_drive_button = send_rtd_button,
            .ts_activation_button = send_tsa_button,
            .drs_button = send_drs_button,
        };
        auto message = PUTM_CAN::Can_tx_message<PUTM_CAN::Dashboard>(frame, PUTM_CAN::can_tx_header_DASHBOARD);

        message.send(hfdcan1);

        // RX: Get the current tick time for timeout management
        uint32_t current_tick_time = xTaskGetTickCount() * portTICK_PERIOD_MS;

/*
 Safety Note:
 TRUE state - One of the SDC systems activated - SDC circuit open
 FALSE state - SDC circuit close
 */

        //Frontbox Safety
		if(PUTM_CAN::can.get_front_data_main_new_data())
		{
			timeoutData.frontbox_safety_last_frame_time = current_tick_time;
			auto frontbox_safety_data = PUTM_CAN::can.get_front_data_main_data();


			if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
			{
				sharedData.warning = false;
				sharedData.safety_front = false;

				safetyData.sense_left_kill = frontbox_safety_data.sense_left_kill;
				safetyData.sense_right_kill = frontbox_safety_data.sense_right_kill;
				safetyData.sense_driver_kill = frontbox_safety_data.sense_driver_kill;
				safetyData.sense_inertia = frontbox_safety_data.sense_inertia;
				safetyData.sense_bspd = frontbox_safety_data.sense_bspd;
				safetyData.sense_apps = frontbox_safety_data.apps;
				safetyData.sense_overtravel = frontbox_safety_data.sense_overtravel;
				safetyData.sense_right_wheel = frontbox_safety_data.sense_right_wheel;
				safetyData.is_braking = frontbox_safety_data.is_braking;

				osMutexRelease(sdcDataMutexHandle);
			}
		}
		else if(current_tick_time - timeoutData.frontbox_safety_last_frame_time > DASH_TIMEOUT_DURATION)
		{
			if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
			{
				sharedData.warning = true;
				sharedData.safety_front = true;

				safetyData.sense_left_kill = false;
				safetyData.sense_right_kill = false;
				safetyData.sense_driver_kill = false;
				safetyData.sense_inertia = false;
				safetyData.sense_bspd = false;
				safetyData.sense_apps = false;
				safetyData.sense_overtravel = false;
				safetyData.sense_right_wheel = false;
				safetyData.is_braking = false;

				osMutexRelease(sdcDataMutexHandle);
			}
		}

		// Process Frontbox Brake Pressure data
				if(PUTM_CAN::can.get_driver_input_main_new_data())
				{
					timeoutData.frontbox_driver_input_last_frame_time = current_tick_time;
					auto frontbox_driver_data = PUTM_CAN::can.get_driver_input_main();


					if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
					{
						sharedData.warning = false;

						sharedData.front_brake_pressure = frontbox_driver_data.brakePressureFront;
						sharedData.rear_brake_pressure = frontbox_driver_data.brakePressureFront;


						osMutexRelease(sharedDataMutexHandle);
					}
				}
				else if(current_tick_time - timeoutData.frontbox_safety_last_frame_time > DASH_TIMEOUT_DURATION)
				{
					if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
					{
						sharedData.warning = true;

						sharedData.front_brake_pressure = 0;
						sharedData.rear_brake_pressure = 0;


						osMutexRelease(sharedDataMutexHandle);
					}
				}


		// Process Frontbox Brake Pressure data
        if(PUTM_CAN::can.get_rearbox_safety_new_data())
        {
        	timeoutData.rearbox_safety_last_frame_time = current_tick_time;
        	auto rearbox_safety_data = PUTM_CAN::can.get_rearbox_safety();

			if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
			{
				sharedData.warning = false;
				//we do not get data from the component so errors are not detected
				sharedData.safety_rear = false;

				safetyData.safety_rfu1 = rearbox_safety_data.safety_rfu1;
				safetyData.safety_rfu2 = rearbox_safety_data.safety_rfu2;
				safetyData.safety_asms = rearbox_safety_data.safety_asms;
				safetyData.safety_fw = rearbox_safety_data.safety_fw;
				safetyData.safety_hv = rearbox_safety_data.safety_hv;
				safetyData.safety_res = rearbox_safety_data.safety_res;
				safetyData.safety_hvd = rearbox_safety_data.safety_hvd;
				safetyData.safety_inv = rearbox_safety_data.safety_inv;
				safetyData.safety_wheel_fl = rearbox_safety_data.safety_wheel_fl;
				safetyData.safety_wheel_fr = rearbox_safety_data.safety_wheel_fr;
				safetyData.safety_wheel_rl = rearbox_safety_data.safety_wheel_rl;
				safetyData.safety_wheel_rr = rearbox_safety_data.safety_wheel_rr;

				osMutexRelease(sdcDataMutexHandle);
			}
		}
        else if(current_tick_time - timeoutData.rearbox_safety_last_frame_time > DASH_TIMEOUT_DURATION)
        		{
        			if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
        			{
        				sharedData.warning = true;
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

        				osMutexRelease(sdcDataMutexHandle);
        			}
        		}


        // Process RearBox Miscellaneous data (e.g., coolant pressure)
		if(PUTM_CAN::can.get_rearbox_miscellaneous_new_data()) {
			timeoutData.rearbox_miscellaneous_last_frame_time = current_tick_time;
			auto rearbox_miscellaneous_data = PUTM_CAN::can.get_rearbox_miscellaneous();

			if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
				sharedData.warning = false;

				sharedData.coolant_pressure = std::max(rearbox_miscellaneous_data.coolant_pressure_out, rearbox_miscellaneous_data.coolant_pressure_in);

				osMutexRelease(sharedDataMutexHandle);
			}
		} else if(current_tick_time - timeoutData.rearbox_miscellaneous_last_frame_time > DASH_TIMEOUT_DURATION) {
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
		} else if(current_tick_time - timeoutData.rearbox_temperatures_last_frame_time > DASH_TIMEOUT_DURATION) {
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

            if(bms_hv_main_data.precharge) {
                interfaceData.precharge_status = true;
            } else {
                interfaceData.precharge_status = false;
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


        // PC main data
        if(PUTM_CAN::can.get_pc_new_data())
        {
            timeoutData.pc_last_frame_time = current_tick_time;
            auto pc_data = PUTM_CAN::can.get_pc_main_data();


           if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
           {
              sharedData.warning = false;
              sharedData.connection = true;

              sharedData.ready_to_drive = pc_data.rtd;

              sharedData.inverters_ready = pc_data.invertersReady;
              sharedData.speed = pc_data.vehicleSpeed;
              sharedData.power = pc_data.torque_current;

              sharedData.inv_FL_status = pc_data.inv_FL_status;
              sharedData.inv_FR_status = pc_data.inv_FR_status;
              sharedData.inv_RL_status = pc_data.inv_RL_status;
              sharedData.inv_RR_status = pc_data.inv_RR_status;

              sharedData.inv_FL_error = pc_data.inv_FL_error;
              sharedData.inv_FR_error = pc_data.inv_FR_error;
              sharedData.inv_RL_error = pc_data.inv_RL_error;
              sharedData.inv_RR_error = pc_data.inv_RR_error;

  			 osMutexRelease(sharedDataMutexHandle);
		  }
	     }
        else if(current_tick_time - timeoutData.pc_last_frame_time > DASH_TIMEOUT_DURATION)
        {

		  if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
		  {
			sharedData.warning = true;
			sharedData.connection = false;

			sharedData.ready_to_drive = 0;

            sharedData.inverters_ready = 0;
            sharedData.speed = 0;
            sharedData.rpm = 0;

            sharedData.inv_FL_status = 0;
            sharedData.inv_FR_status = 0;
            sharedData.inv_RL_status = 0;
            sharedData.inv_RR_status = 0;

            sharedData.inv_FL_error = 0;
            sharedData.inv_FR_error = 0;
            sharedData.inv_RL_error = 0;
            sharedData.inv_RR_error = 0;

			osMutexRelease(sharedDataMutexHandle);
		  }
	     }

        //Pc temperature data
        if(PUTM_CAN::can.get_pc_temperature_data_new_data())
                {
                    timeoutData.pc_temp_last_frame_time = current_tick_time;
                    auto pc_temp_data = PUTM_CAN::can.get_pc_temperature_data();


                   if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
                   {
                      sharedData.warning = false;
                      sharedData.connection = true;

                      sharedData.frontRightInverterTemperature = pc_temp_data.rearLeftInverterTemperature;
                      sharedData.frontLeftInverterTemperature = pc_temp_data.frontLeftInverterTemperature;
                      sharedData.rearRightInverterTemperature = pc_temp_data.rearRightInverterTemperature;
                      sharedData.rearLeftInverterTemperature = pc_temp_data.rearLeftInverterTemperature;

                      sharedData.motor_front_left_temperature = pc_temp_data.frontLeftMotorTemperature;
                      sharedData.motor_front_right_temperature = pc_temp_data.frontRightMotorTemperature;
                      sharedData.motor_rear_left_temperature = pc_temp_data.rearLeftMotorTemperature;
                      sharedData.motor_rear_right_temperature = pc_temp_data.rearRightMotorTemperature;

          			 osMutexRelease(sharedDataMutexHandle);
        		  }
        	     }
                else if(current_tick_time - timeoutData.pc_temp_last_frame_time > DASH_TIMEOUT_DURATION)
                {

        		  if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
        		  {
        			sharedData.warning = true;
        			sharedData.connection = false;

                    sharedData.frontRightInverterTemperature = 0;
                    sharedData.frontLeftInverterTemperature = 0;
                    sharedData.rearRightInverterTemperature = 0;
                    sharedData.rearLeftInverterTemperature = 0;

                    sharedData.motor_front_left_temperature = 0;
                    sharedData.motor_front_right_temperature = 0;
                    sharedData.motor_rear_left_temperature = 0;
                    sharedData.motor_rear_right_temperature = 0;


        			osMutexRelease(sharedDataMutexHandle);
        		  }
        	     }

        //Pc LapTimer data
        if(PUTM_CAN::can.get_pc_lap_timer_data_new_data())
        {
              timeoutData.pc_laptimer_last_frame_time = current_tick_time;
              auto pc_laptimer_data = PUTM_CAN::can.get_pc_lap_timer_data();


              if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
              {
                    sharedData.warning = false;
                    sharedData.connection = true;

                    timerData.pace = pc_laptimer_data.delta_time;
                    timerData.current_lap = pc_laptimer_data.currentLapTime;
                    timerData.best_lap = pc_laptimer_data.bestLapTime;
                    timerData.lap_counter = pc_laptimer_data.lap_counter;

        			 osMutexRelease(sharedDataMutexHandle);
        	  }
          }
          else if(current_tick_time - timeoutData.pc_laptimer_last_frame_time > DASH_TIMEOUT_DURATION)
          {

        	  if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
        	  {
        		 sharedData.warning = true;
        		 sharedData.connection = false;

                 timerData.pace = 0;
                 timerData.current_lap = 0;
                 timerData.best_lap = 0;
                 timerData.lap_counter = 0;


        		 osMutexRelease(sharedDataMutexHandle);
        	   }
        }


        //Pdu channel
        if(PUTM_CAN::can.get_pdu_channel_new_data())
        {
              timeoutData.pdu_channel_last_frame_time = current_tick_time;
              auto pdu_channnel = PUTM_CAN::can.get_pdu_channel_data();


              if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
              {
                    sharedData.warning = false;

                    sharedData.pc_status = pdu_channnel.pc_status;
                    sharedData.fan_status = pdu_channnel.fan_status;
                    sharedData.pump_status = pdu_channnel.pump_status;
                    sharedData.inverter_status = pdu_channnel.inverter_status;
                    sharedData.fbox_status = pdu_channnel.fbox_status;
                    sharedData.sdc_status = pdu_channnel.sdc_status;
                    sharedData.dash_status = pdu_channnel.dash_status;
                    sharedData.tsal_hv_status = pdu_channnel.tsal_hv_status;
                    sharedData.rbox_diagport_brake_l_status = pdu_channnel.rbox_diagport_brake_l_status;
                    sharedData.brake_ir_air_status = pdu_channnel.brake_ir_air_status;




        			osMutexRelease(sharedDataMutexHandle);
        	  }
          }
          else if(current_tick_time - timeoutData.pdu_channel_last_frame_time > DASH_TIMEOUT_DURATION)
          {

        	  if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
        	  {
        		 sharedData.warning = true;

        		 sharedData.pc_status = false;
        		 sharedData.fan_status = false;
        		 sharedData.pump_status = false;
        		 sharedData.inverter_status = false;
        		 sharedData.fbox_status = false;
        		 sharedData.sdc_status = false;
        		 sharedData.dash_status = false;
        		 sharedData.tsal_hv_status = false;
        		 sharedData.rbox_diagport_brake_l_status = false;
        		 sharedData.brake_ir_air_status = false;

        		 osMutexRelease(sharedDataMutexHandle);
        	   }
        }



        HAL_IWDG_Refresh(&hiwdg); // Every 250 ms

        osDelay(100);
    }
}
