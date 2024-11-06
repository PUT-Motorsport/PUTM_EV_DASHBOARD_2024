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
    .inverters_ready = false,
    .safety_front = true,
    .safety_rear = true,
    .battery_hv_temperature = 0,
	.battery_lv_temperature = 0,
    .inverter_temperature = 0,
    .oil_temperature = 0,
    .oil_pressure = 0,
    .coolant_temperature = 0,
    .coolant_pressure = 0,
	.motor_front_left_temperature = 0,
	.motor_front_right_temperature = 0,
	.motor_rear_left_temperature = 0,
	.motor_rear_right_temperature = 0,
    .speed = 0,
    .soc_hv = 0,
	.soc_lv = 0,
    .rpm = 0,
    .power = 0,
    .distance = 0,
    .range = 0,
};

SafetyData_TypeDef safetyData =
{
	//Frontbox Safety
	.sense_left_kill = 0,
	.sense_right_kill = 0,
	.sense_driver_kill = 0,
	.sense_inertia = 0,
	.sense_bspd = 0,
	.sense_overtravel = 0,
	.sense_right_wheel = 0,
	.is_braking = 0,
	//Rearbox Safety
	.safety_rfu1 = 0,
	.safety_rfu2 = 0,
	.safety_asms = 0,
	.safety_fw = 0,
	.safety_hv = 0,
	.safety_res = 0,
	.safety_hvd = 0,
	.safety_inv = 0,
	.safety_wheel_fl = 0,
	.safety_wheel_fr = 0,
	.safety_wheel_rl  = 0,
	.safety_wheel_rr = 0,
};

TimeoutData_TypeDef timeoutData = {
    .bms_hv_last_frame_time = 0,
    .bms_lv_last_frame_time = 0,
    .frontbox_last_frame_time = 0,
	.frontbox_safety_last_frame_time = 0,
    .rearbox_last_frame_time = 0,
	.rearbox_safety_last_frame_time = 0,
	.pc_last_frame_time = 0,
};

TimerData_TypeDef timerData = {
    .pace = 0,
    .current_lap = 0,
    .last_lap = 0,
    .best_lap = 0,
};

InterfaceData_TypeDef interfaceData = {
    .led_test = true,
    .ams_led = false,
    .fuse_led = false,
    .safety_led = false,
    .rtd_button = false,
    .tsa_button = false,
    .usr_button = false,
    .previous_rtd_button = false,
    .previous_tsa_button = false,
    .previous_usr_button = false,
    .rtd_timer = 0,
    .tsa_timer = 0,
    .usr_timer = 0,
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
