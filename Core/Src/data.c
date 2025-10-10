/**
 ******************************************************************************
 * @file           : data.c
 * @brief          : Dashboard data
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "data.h"

/* Typedefs ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
Data_TypeDef sharedData = {
    .time = 0,
    .warning = true,
    .connection = false,
    .radio = false,
    .ready_to_drive = false,
    .rtd_button_pressed = false,
	.tsa_button_pressed = false,

    // Inverters
    .inverters_ready = false,
    .inv_FL_status = false,
    .inv_FR_status = false,
    .inv_RL_status = false,
    .inv_RR_status = false,
    .inv_FL_error = false,
    .inv_FR_error = false,
    .inv_RL_error = false,
    .inv_RR_error = false,

    // Safety
    .safety_front = false,
    .safety_rear = false,

    //PDU
    .pc_status = 0,
    .fan_status = 0,
    .pump_status = 0,
    .inverter_status = 0,
    .fbox_status = 0,
    .sdc_status = 0,
    .dash_status = 0,
    .tsal_hv_status = 0,
    .rbox_diagport_brake_l_status = 0,
    .brake_ir_air_status = 0,

    .pc_current = 0,
    .pump_current = 0,
    .fan_current = 0,
    .inverter_current = 0,
    .fbox_current = 0,
    .sdc_current = 0,
    .total_current = 0,

    //Miscellaneous
    .oil_pressure = 0,
    .coolant_pressure = 0,
	.front_brake_pressure = 0,
	.rear_brake_pressure = 0,
    .speed = 0,
    .rpm = 0,
    .power = 0,
    .distance = 0,
    .range = 0,

    //Soc
    .soc_hv = 0,
    .soc_lv = 0,

    //DataLogger
    .triggerVoltage = 0,
    .triggerCurrent = 0,
    .LogStatus = 0,
    .current = 0,
    .voltage = 0,
};

TemperatureData_TypeDef temperatureData =
{
    //Motors
    .motor_front_left_temperature = 0,
    .motor_front_right_temperature = 0,
    .motor_rear_left_temperature = 0,
    .motor_rear_right_temperature = 0,
    //Inverters
    .frontRightInverterTemperature = 0,
    .frontLeftInverterTemperature = 0,
    .rearRightInverterTemperature = 0,
    .rearLeftInverterTemperature = 0,
    //Coolant
    .coolant_in_temperature = 0,
    .coolant_out_temperature = 0,
    //Battery
    .battery_hv_temperature = 0,
    .battery_lv_temperature = 0,
    //Oil
    .oil_temperature = 0,
};

SafetyData_TypeDef safetyData =
{
	//Frontbox Safety
	.sense_left_kill = 0,
	.sense_right_kill = 0,
	.sense_driver_kill = 0,
	.sense_inertia = 0,
	.sense_bspd = 0,
	.sense_apps = 0,
	.sense_overtravel = 0,
	.is_braking = 0,
	.safety_suspension_fl = 0,
	.safety_suspension_fr = 0,
	//Rearbox Safety
	.safety_tsmp = 0,
	.safety_hv_battery = 0,
	.safety_inv_hv = 0,
	.safety_hvd = 0,
	.safety_inv = 0,
	.safety_wheel_fl = 0,
	.safety_wheel_fr = 0,
	.safety_wheel_rl = 0,
	.safety_wheel_rr = 0,
	.safety_suspension_rl = 0,
	.safety_suspension_rr = 0,
	.safety_motor_front = 0,
};

TimeoutData_TypeDef timeoutData = {
    .bms_hv_last_frame_time = 0,
    .bms_lv_last_frame_time = 0,
    .frontbox_last_frame_time = 0,
	.frontbox_safety_last_frame_time = 0,
	.frontbox_driver_input_last_frame_time = 0,
    .rearbox_last_frame_time = 0,
	.rearbox_safety_last_frame_time = 0,
	.rearbox_miscellaneous_last_frame_time = 0,
	.rearbox_temperatures_last_frame_time = 0,
	.pc_last_frame_time = 0,
	.pc_temp_last_frame_time = 0,
	.pc_laptimer_last_frame_time = 0,
    .pdu_data_last_frame_time = 0,
	.pdu_channel_last_frame_time = 0,
    .dataLogger_last_frame_time = 0,
};

TimerData_TypeDef timerData = {
    .pace = 0,
    .current_lap = 0,
    .last_lap = 0,
    .best_lap = 0,
	.lap_counter = 0,
};

InterfaceData_TypeDef interfaceData = {
    .led_test = true,
    .ams_led = false,
    .fuse_led = false,
    .safety_led = false,
    .rtd_button = false,
    .tsa_button = false,
    .cs_button = false,
    .drs_button = false,
    .usr_button = false,
    .previous_rtd_button = false,
    .previous_tsa_button = false,
    .previous_usr_button = false,
	.precharge_status = false,
	.drs_status = false,
    .rtd_timer = 0,
    .tsa_timer = 0,
    .usr_timer = 0,
	.drs_timer = 0,
	.cs_timer = 0,
};

ScreenStatus_TypeDef screenStatus = {
	.MainScreen = false,
	.RaceScreen = false,
	.NotificationScreen = false,
	.DiagnosticScreen = false,
    .PduScreen = false,
    .VpSettingsScreen = false,
    .DataLoggerScreen = false
};



/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
