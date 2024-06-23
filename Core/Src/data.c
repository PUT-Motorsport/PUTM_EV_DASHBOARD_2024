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
	.battery_temperature = 0,
	.inverter_temperature = 0,
	.oil_temperature = 0,
	.oil_pressure = 0,
	.coolant_temperature = 0,
	.coolant_pressure = 0,
	.speed = 0,
	.soc = 0,
	.rpm = 0,
	.power = 0,
	.distance = 0,
	.range = 0,
};

TimerData_TypeDef timerData = {
	.pace = 0,
	.current_lap = 0,
	.last_lap = 0,
	.best_lap = 0,
};

InterfaceData_TypeDef interfaceData = {
	.ams_led = true,
	.fuse_led = true,
	.safety_led = true,
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
