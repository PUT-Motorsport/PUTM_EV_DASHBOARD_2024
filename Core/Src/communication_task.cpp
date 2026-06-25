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
#include "PUTM_EV_CAN_LIBRARY/include/can_driver.hpp"
#include "PUTM_CAN_M.h"
#include "fdcan.h"

#include "iwdg.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "main.h"
#include "portable.h"
#include "task.h"

#include <algorithm>

extern osMutexId_t sharedDataMutexHandle;
extern osMutexId_t sdcDataMutexHandle;

// Flags for data reception
volatile bool front_data_flag{false};
volatile bool driver_input_flag{false};
volatile bool rearbox_safety_flag{false};
volatile bool rearbox_miscellaneous_flag{false};
volatile bool rearbox_temperature_flag{false};
volatile bool pc_main_data_flag{false};
volatile bool pc_temperature_data_flag{false};
volatile bool pc_lap_timer_data_flag{false};
volatile bool pdu_channel_flag{false};
volatile bool bms_lv_main_flag{false};
volatile bool bms_hv_main_flag{false};

// Data structures
volatile PUTM_CAN_M_front_data_t front_data{};
volatile PUTM_CAN_M_driver_input_t driver_input{};
volatile PUTM_CAN_M_rearbox_safety_t rearbox_safety{};
volatile PUTM_CAN_M_rearbox_miscellaneous_t rearbox_miscellaneous{};
volatile PUTM_CAN_M_rearbox_temperature_t rearbox_temperature{};
volatile PUTM_CAN_M_pc_main_data_t pc_main_data{};
volatile PUTM_CAN_M_pc_temperature_data_t pc_temperature_data{};
volatile PUTM_CAN_M_pc_lap_timer_data_t pc_lap_timer_data{};
volatile PUTM_CAN_M_pdu_channnel_t pdu_channel{};
volatile PUTM_CAN_M_bms_lv_main_t bms_lv_main{};
volatile PUTM_CAN_M_bms_hv_main_t bms_hv_main{};


void Communication_Task(void* argument) {
    putm_ev_can::CanDriver can_m;

    if (!can_m.Init(&hfdcan1)){
        Error_Handler();
    }

    // Front Data Callback
    can_m.RegisterCallback<PUTM_CAN_M_front_data_t>(PUTM_CAN_M_FRONT_DATA_FRAME_ID,
        [](const PUTM_CAN_M_front_data_t& front_data_new){
        front_data_flag = true;
        front_data.apps = front_data_new.apps;
        front_data.apps_implausibility = front_data_new.apps_implausibility;
        front_data.brake_potentiometer = front_data_new.brake_potentiometer;
        front_data.is_braking = front_data_new.is_braking;
        front_data.safety_suspension_fl = front_data_new.safety_suspension_fl;
        front_data.safety_suspension_fr = front_data_new.safety_suspension_fr;
        front_data.sense_bspd = front_data_new.sense_bspd;
        front_data.sense_driver_kill = front_data_new.sense_driver_kill;
        front_data.sense_left_kill = front_data_new.sense_left_kill;
        front_data.sense_right_kill = front_data_new.sense_right_kill;
        front_data.sense_inertia = front_data_new.sense_inertia;
        front_data.sense_overtravel = front_data_new.sense_overtravel;
    });
    
    // Driver Input Callback
    can_m.RegisterCallback<PUTM_CAN_M_driver_input_t>(PUTM_CAN_M_DRIVER_INPUT_FRAME_ID,
        [](const PUTM_CAN_M_driver_input_t& new_data){
        driver_input_flag = true;
        driver_input.brake_pressure_front = new_data.brake_pressure_front;
        driver_input.brake_pressure_rear = new_data.brake_pressure_rear;
    });

    // Rearbox Safety Callback
    can_m.RegisterCallback<PUTM_CAN_M_rearbox_safety_t>(PUTM_CAN_M_REARBOX_SAFETY_FRAME_ID,
        [](const PUTM_CAN_M_rearbox_safety_t& new_data){
        rearbox_safety_flag = true;
        rearbox_safety.safety_hv_battery = new_data.safety_hv_battery;
        rearbox_safety.safety_hvd = new_data.safety_hvd;
        rearbox_safety.safety_inv = new_data.safety_inv;
        rearbox_safety.safety_inv_hv = new_data.safety_inv_hv;
        rearbox_safety.safety_motor_front = new_data.safety_motor_front;
        rearbox_safety.safety_rfu = new_data.safety_rfu;
        rearbox_safety.safety_suspension_rl = new_data.safety_suspension_rl;
        rearbox_safety.safety_suspension_rr = new_data.safety_suspension_rr;
        rearbox_safety.safety_wheel_fl = new_data.safety_wheel_fl;
        rearbox_safety.safety_wheel_fr = new_data.safety_wheel_fr;
        rearbox_safety.safety_wheel_rl = new_data.safety_wheel_rl;
        rearbox_safety.safety_wheel_rr = new_data.safety_wheel_rr;
        rearbox_safety.safety_tsmp = new_data.safety_tsmp;
    });

    // Rearbox Miscellaneous Callback
    can_m.RegisterCallback<PUTM_CAN_M_rearbox_miscellaneous_t>(PUTM_CAN_M_REARBOX_MISCELLANEOUS_FRAME_ID,
        [](const PUTM_CAN_M_rearbox_miscellaneous_t& new_data){
        rearbox_miscellaneous_flag = true;
        rearbox_miscellaneous.coolant_pressure_in = new_data.coolant_pressure_in;
        rearbox_miscellaneous.coolant_pressure_out = new_data.coolant_pressure_out;
    });

    // Rearbox Temperature Callback
    can_m.RegisterCallback<PUTM_CAN_M_rearbox_temperature_t>(PUTM_CAN_M_REARBOX_TEMPERATURE_FRAME_ID,
        [](const PUTM_CAN_M_rearbox_temperature_t& new_data){
        rearbox_temperature_flag = true;
        rearbox_temperature.mono_temperature = new_data.mono_temperature;
        rearbox_temperature.coolant_temperature_in = new_data.coolant_temperature_in;
        rearbox_temperature.coolant_temperature_out = new_data.coolant_temperature_out;
        rearbox_temperature.oil_temperature_l = new_data.oil_temperature_l;
        rearbox_temperature.oil_temperature_r = new_data.oil_temperature_r;
    });

    // PC Main Data Callback
    can_m.RegisterCallback<PUTM_CAN_M_pc_main_data_t>(PUTM_CAN_M_PC_MAIN_DATA_FRAME_ID,
        [](const PUTM_CAN_M_pc_main_data_t& new_data){
        pc_main_data_flag = true;
        pc_main_data.vehicle_speed = new_data.vehicle_speed;
        pc_main_data.torque_current = new_data.torque_current;
        pc_main_data.inverters_ready = new_data.inverters_ready;
        pc_main_data.rtd = new_data.rtd;
        pc_main_data.inv_fl_status = new_data.inv_fl_status;
        pc_main_data.inv_fr_status = new_data.inv_fr_status;
        pc_main_data.inv_rl_status = new_data.inv_rl_status;
        pc_main_data.inv_rr_status = new_data.inv_rr_status;
        pc_main_data.inv_fl_error = new_data.inv_fl_error;
        pc_main_data.inv_fr_error = new_data.inv_fr_error;
        pc_main_data.inv_rl_error = new_data.inv_rl_error;
        pc_main_data.inv_rr_error = new_data.inv_rr_error;
    });

    // PC Temperature Data Callback
    can_m.RegisterCallback<PUTM_CAN_M_pc_temperature_data_t>(PUTM_CAN_M_PC_TEMPERATURE_DATA_FRAME_ID,
        [](const PUTM_CAN_M_pc_temperature_data_t& new_data){
        pc_temperature_data_flag = true;
        pc_temperature_data.rear_right_inverter_temperature = new_data.rear_right_inverter_temperature;
        pc_temperature_data.rear_left_inverter_temperature = new_data.rear_left_inverter_temperature;
        pc_temperature_data.rear_right_motor_temperature = new_data.rear_right_motor_temperature;
        pc_temperature_data.rear_left_motor_temperature = new_data.rear_left_motor_temperature;
        pc_temperature_data.front_right_inverter_temperature = new_data.front_right_inverter_temperature;
        pc_temperature_data.front_left_inverter_temperature = new_data.front_left_inverter_temperature;
        pc_temperature_data.front_right_motor_temperature = new_data.front_right_motor_temperature;
        pc_temperature_data.front_left_motor_temperature = new_data.front_left_motor_temperature;
    });

    // PC Lap Timer Data Callback
    can_m.RegisterCallback<PUTM_CAN_M_pc_lap_timer_data_t>(PUTM_CAN_M_PC_LAP_TIMER_DATA_FRAME_ID,
        [](const PUTM_CAN_M_pc_lap_timer_data_t& new_data){
        pc_lap_timer_data_flag = true;
        pc_lap_timer_data.current_lap_time = new_data.current_lap_time;
        pc_lap_timer_data.best_lap_time = new_data.best_lap_time;
        pc_lap_timer_data.delta_time = new_data.delta_time;
        pc_lap_timer_data.lap_counter = new_data.lap_counter;
    });

    // PDU Channel Callback
    can_m.RegisterCallback<PUTM_CAN_M_pdu_channnel_t>(PUTM_CAN_M_PDU_CHANNNEL_FRAME_ID,
        [](const PUTM_CAN_M_pdu_channnel_t& new_data){
        pdu_channel_flag = true;
        pdu_channel.pc_status = new_data.pc_status;
        pdu_channel.fan_status = new_data.fan_status;
        pdu_channel.pump_status = new_data.pump_status;
        pdu_channel.inverter_status = new_data.inverter_status;
        pdu_channel.fbox_status = new_data.fbox_status;
        pdu_channel.sdc_status = new_data.sdc_status;
        pdu_channel.dash_status = new_data.dash_status;
        pdu_channel.tsal_hv_status = new_data.tsal_hv_status;
        pdu_channel.rbox_diagport_brake_l_status = new_data.rbox_diagport_brake_l_status;
        pdu_channel.brake_ir_air_status = new_data.brake_ir_air_status;
    });

    // BMS LV Main Callback
    can_m.RegisterCallback<PUTM_CAN_M_bms_lv_main_t>(PUTM_CAN_M_BMS_LV_MAIN_FRAME_ID,
        [](const PUTM_CAN_M_bms_lv_main_t& new_data){
        bms_lv_main_flag = true;
        bms_lv_main.voltage_sum = new_data.voltage_sum;
        bms_lv_main.soc = new_data.soc;
        bms_lv_main.temp_avg = new_data.temp_avg;
        bms_lv_main.current = new_data.current;
        bms_lv_main.device_state = new_data.device_state;
    });

    // BMS HV Main Callback
    can_m.RegisterCallback<PUTM_CAN_M_bms_hv_main_t>(PUTM_CAN_M_BMS_HV_MAIN_FRAME_ID,
        [](const PUTM_CAN_M_bms_hv_main_t& new_data){
        bms_hv_main_flag = true;
        bms_hv_main.voltage_sum = new_data.voltage_sum;
        bms_hv_main.current = new_data.current;
        bms_hv_main.temp_max = new_data.temp_max;
        bms_hv_main.temp_avg = new_data.temp_avg;
        bms_hv_main.soc = new_data.soc;
        bms_hv_main.ok = new_data.ok;
        bms_hv_main.precharge = new_data.precharge;
    });

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
        PUTM_CAN_M_dashboard_t frame{
            .ready_to_drive_button = send_rtd_button,
            .ts_activation_button = send_tsa_button,
            .drs_button = send_drs_button,
        };

        can_m.Send(PUTM_CAN_M_DASHBOARD_FRAME_ID, frame);


        // RX: Get the current tick time for timeout management
        uint32_t current_tick_time = xTaskGetTickCount() * portTICK_PERIOD_MS;

/*
 Safety Note:
 TRUE state - One of the SDC systems activated - SDC circuit open
 FALSE state - SDC circuit close
 */

        //Frontbox Safety
        if(front_data_flag == true)
        {
            front_data_flag = false;
            timeoutData.frontbox_safety_last_frame_time = current_tick_time;

            if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
            {
                sharedData.warning = false;
                sharedData.safety_front = false;

                safetyData.sense_left_kill = front_data.sense_left_kill;
                safetyData.sense_right_kill = front_data.sense_right_kill;
                safetyData.sense_driver_kill = front_data.sense_driver_kill;
                safetyData.sense_inertia = front_data.sense_inertia;
                safetyData.sense_bspd = front_data.sense_bspd;
                safetyData.sense_apps = front_data.apps;
                safetyData.sense_overtravel = front_data.sense_overtravel;
                safetyData.is_braking = front_data.is_braking;
                safetyData.safety_suspension_fl = front_data.safety_suspension_fl;
                safetyData.safety_suspension_fr = front_data.safety_suspension_fr;

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
                safetyData.is_braking = false;
                safetyData.safety_suspension_fl = false;
                safetyData.safety_suspension_fr = false;

                osMutexRelease(sdcDataMutexHandle);
            }
        }

        // Process Frontbox Brake Pressure data
        if(driver_input_flag == true)
        {
            driver_input_flag = false;
            timeoutData.frontbox_driver_input_last_frame_time = current_tick_time;

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
            {
                sharedData.warning = false;

                sharedData.front_brake_pressure = driver_input.brake_pressure_front;
                sharedData.rear_brake_pressure = driver_input.brake_pressure_rear;

                osMutexRelease(sharedDataMutexHandle);
            }
        }
        else if(current_tick_time - timeoutData.frontbox_driver_input_last_frame_time > DASH_TIMEOUT_DURATION)
        {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
            {
                sharedData.warning = true;

                sharedData.front_brake_pressure = 0;
                sharedData.rear_brake_pressure = 0;

                osMutexRelease(sharedDataMutexHandle);
            }
        }

        // Process Rearbox Safety data
        if(rearbox_safety_flag == true)
        {
            rearbox_safety_flag = false;
            timeoutData.rearbox_safety_last_frame_time = current_tick_time;

            if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
            {
                sharedData.warning = false;
                sharedData.safety_rear = false;

                safetyData.safety_tsmp = rearbox_safety.safety_tsmp;
                safetyData.safety_hv_battery = rearbox_safety.safety_hv_battery;
                safetyData.safety_inv_hv = rearbox_safety.safety_inv_hv;
                safetyData.safety_hvd = rearbox_safety.safety_hvd;
                safetyData.safety_inv = rearbox_safety.safety_inv;
                safetyData.safety_wheel_fl = rearbox_safety.safety_wheel_fl;
                safetyData.safety_wheel_fr = rearbox_safety.safety_wheel_fr;
                safetyData.safety_wheel_rl = rearbox_safety.safety_wheel_rl;
                safetyData.safety_wheel_rr = rearbox_safety.safety_wheel_rr;
                safetyData.safety_suspension_rl = rearbox_safety.safety_suspension_rl;
                safetyData.safety_suspension_rr = rearbox_safety.safety_suspension_rr;
                safetyData.safety_motor_front = rearbox_safety.safety_motor_front;

                osMutexRelease(sdcDataMutexHandle);
            }
        }
        else if(current_tick_time - timeoutData.rearbox_safety_last_frame_time > DASH_TIMEOUT_DURATION)
        {
            if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
            {
                sharedData.warning = true;
                sharedData.safety_rear = true;

                safetyData.safety_tsmp = false;
                safetyData.safety_hv_battery = false;
                safetyData.safety_inv_hv = false;
                safetyData.safety_hvd = false;
                safetyData.safety_inv = false;
                safetyData.safety_wheel_fl = false;
                safetyData.safety_wheel_fr = false;
                safetyData.safety_wheel_rl = false;
                safetyData.safety_wheel_rr = false;
                safetyData.safety_suspension_rl = false;
                safetyData.safety_suspension_rr = false;
                safetyData.safety_motor_front = false;

                osMutexRelease(sdcDataMutexHandle);
            }
        }

        // Process RearBox Miscellaneous data (e.g., coolant pressure)
        if(rearbox_miscellaneous_flag == true) {
            rearbox_miscellaneous_flag = false;
            timeoutData.rearbox_miscellaneous_last_frame_time = current_tick_time;

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = false;

                sharedData.coolant_pressure = std::max(rearbox_miscellaneous.coolant_pressure_out, rearbox_miscellaneous.coolant_pressure_in);

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
        if(rearbox_temperature_flag == true) {
            rearbox_temperature_flag = false;
            timeoutData.rearbox_temperatures_last_frame_time = current_tick_time;

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = false;

                sharedData.coolant_out_temperature = rearbox_temperature.coolant_temperature_out;
                sharedData.coolant_in_temperature = rearbox_temperature.coolant_temperature_in;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.rearbox_temperatures_last_frame_time > DASH_TIMEOUT_DURATION) {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = true;

                sharedData.coolant_out_temperature = 0;
                sharedData.coolant_in_temperature = 0;

                osMutexRelease(sharedDataMutexHandle);
            }
        }

        // BMS LV
        if(bms_lv_main_flag == true) {
            bms_lv_main_flag = false;
            timeoutData.bms_lv_last_frame_time = current_tick_time;

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = false;
                sharedData.battery_lv_temperature = bms_lv_main.temp_avg;
                sharedData.soc_lv = bms_lv_main.soc;

                osMutexRelease(sharedDataMutexHandle);
            }
        } else if(current_tick_time - timeoutData.bms_lv_last_frame_time > DASH_TIMEOUT_DURATION) {
            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = true;
                sharedData.battery_lv_temperature = 0;
                sharedData.soc_lv = 0;

                osMutexRelease(sharedDataMutexHandle);
            }
        }

        // BMS HV
        if(bms_hv_main_flag == true) {
            bms_hv_main_flag = false;
            timeoutData.bms_hv_last_frame_time = current_tick_time;

            if(bms_hv_main.ok) {
                interfaceData.ams_led = false;
            } else {
                interfaceData.ams_led = true;
            }

            if(bms_hv_main.precharge) {
                interfaceData.precharge_status = true;
            } else {
                interfaceData.precharge_status = false;
            }

            if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                sharedData.warning = false;
                sharedData.soc_hv = bms_hv_main.soc / 10;
                sharedData.battery_hv_temperature = bms_hv_main.temp_max;

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
        if(pc_main_data_flag == true)
        {
            pc_main_data_flag = false;
            timeoutData.pc_last_frame_time = current_tick_time;

           if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK)
           {
              sharedData.warning = false;
              sharedData.connection = true;

              sharedData.ready_to_drive = pc_main_data.rtd;

              sharedData.inverters_ready = pc_main_data.inverters_ready;
              sharedData.speed = pc_main_data.vehicle_speed;
              sharedData.power = pc_main_data.torque_current;

              sharedData.inv_FL_status = pc_main_data.inv_fl_status;
              sharedData.inv_FR_status = pc_main_data.inv_fr_status;
              sharedData.inv_RL_status = pc_main_data.inv_rl_status;
              sharedData.inv_RR_status = pc_main_data.inv_rr_status;

              sharedData.inv_FL_error = pc_main_data.inv_fl_error;
              sharedData.inv_FR_error = pc_main_data.inv_fr_error;
              sharedData.inv_RL_error = pc_main_data.inv_rl_error;
              sharedData.inv_RR_error = pc_main_data.inv_rr_error;

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

        //PC temperature data
        if(pc_temperature_data_flag == true) {
            pc_temperature_data_flag = false;
            timeoutData.pc_temp_last_frame_time = current_tick_time;

           if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
              sharedData.warning = false;
              sharedData.connection = true;

              sharedData.frontRightInverterTemperature = pc_temperature_data.front_right_inverter_temperature;
              sharedData.frontLeftInverterTemperature = pc_temperature_data.front_left_inverter_temperature;
              sharedData.rearRightInverterTemperature = pc_temperature_data.rear_right_inverter_temperature;
              sharedData.rearLeftInverterTemperature = pc_temperature_data.rear_left_inverter_temperature;

              sharedData.motor_front_left_temperature = pc_temperature_data.front_left_motor_temperature;
              sharedData.motor_front_right_temperature = pc_temperature_data.front_right_motor_temperature;
              sharedData.motor_rear_left_temperature = pc_temperature_data.rear_left_motor_temperature;
              sharedData.motor_rear_right_temperature = pc_temperature_data.rear_right_motor_temperature;

                       osMutexRelease(sharedDataMutexHandle);
                  }
                 }
                else if(current_tick_time - timeoutData.pc_temp_last_frame_time > DASH_TIMEOUT_DURATION) {
                  if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
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

        //PC LapTimer data
        if(pc_lap_timer_data_flag == true) {
              pc_lap_timer_data_flag = false;
              timeoutData.pc_laptimer_last_frame_time = current_tick_time;

              if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                    sharedData.warning = false;
                    sharedData.connection = true;

                    timerData.pace = pc_lap_timer_data.delta_time;
                    timerData.current_lap = pc_lap_timer_data.current_lap_time;
                    timerData.best_lap = pc_lap_timer_data.best_lap_time;
                    timerData.lap_counter = pc_lap_timer_data.lap_counter;

                     osMutexRelease(sharedDataMutexHandle);
              }
          }
          else if(current_tick_time - timeoutData.pc_laptimer_last_frame_time > DASH_TIMEOUT_DURATION) {
              if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                 sharedData.warning = true;
                 sharedData.connection = false;

                 timerData.pace = 0;
                 timerData.current_lap = 0;
                 timerData.best_lap = 0;
                 timerData.lap_counter = 0;

                 osMutexRelease(sharedDataMutexHandle);
               }
        }

        //PDU channel
        if(pdu_channel_flag == true) {
              pdu_channel_flag = false;
              timeoutData.pdu_channel_last_frame_time = current_tick_time;

              if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                    sharedData.warning = false;

                    sharedData.pc_status = pdu_channel.pc_status;
                    sharedData.fan_status = pdu_channel.fan_status;
                    sharedData.pump_status = pdu_channel.pump_status;
                    sharedData.inverter_status = pdu_channel.inverter_status;
                    sharedData.fbox_status = pdu_channel.fbox_status;
                    sharedData.sdc_status = pdu_channel.sdc_status;
                    sharedData.dash_status = pdu_channel.dash_status;
                    sharedData.tsal_hv_status = pdu_channel.tsal_hv_status;
                    sharedData.rbox_diagport_brake_l_status = pdu_channel.rbox_diagport_brake_l_status;
                    sharedData.brake_ir_air_status = pdu_channel.brake_ir_air_status;

                    osMutexRelease(sharedDataMutexHandle);
              }
          }
          else if(current_tick_time - timeoutData.pdu_channel_last_frame_time > DASH_TIMEOUT_DURATION) {
              if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
                 sharedData.warning = true;

                 sharedData.pc_status = 0;
                 sharedData.fan_status = 0;
                 sharedData.pump_status = 0;
                 sharedData.inverter_status = 0;
                 sharedData.fbox_status = 0;
                 sharedData.sdc_status = 0;
                 sharedData.dash_status = 0;
                 sharedData.tsal_hv_status = 0;
                 sharedData.rbox_diagport_brake_l_status = 0;
                 sharedData.brake_ir_air_status = 0;

                 osMutexRelease(sharedDataMutexHandle);
               }
        }

        HAL_IWDG_Refresh(&hiwdg); // Every 250 ms

        osDelay(100);
    }
}
