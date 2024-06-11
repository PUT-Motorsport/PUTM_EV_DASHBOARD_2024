/**
 ******************************************************************************
 * @file           : dash.h
 * @brief          : Dashboard library
 *
 ******************************************************************************
 */

#ifndef __DASH_H__
#define __DASH_H__

/* Public includes -----------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Public typedefs -----------------------------------------------------------*/
typedef struct {
	uint32_t time;
	_Bool warning;
	_Bool connection;
	_Bool radio;
	uint8_t battery_temperature;
	uint8_t inverter_temperature;
	uint8_t oil_temperature;
	uint8_t oil_pressure;
	uint8_t coolant_temperature;
	uint8_t coolant_pressure;
	uint8_t speed;
	uint8_t soc;
	uint16_t rpm;
	uint8_t power;
	uint16_t distance;
	uint16_t range;
} Data_TypeDef;

typedef struct {
	int32_t pace;
	uint32_t current_lap;
	uint32_t last_lap;
	uint32_t best_lap;
} TimerData_TypeDef;

typedef struct {
	_Bool ams_led;
	_Bool fuse_led;
	_Bool safety_led;
    _Bool ready_to_drive_button;
    _Bool ts_activation_button;
    _Bool user_button;
    uint32_t rtd_debouncing_timer;
    uint32_t tsa_debouncing_timer;
    uint32_t usr_debouncing_timer;
} InterfaceData_TypeDef;

/* Public defines ------------------------------------------------------------*/
#define DASH_RPM_MAX 3000
#define DASH_BUTTON_DEBOUNCING_TIME 1000

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __DASH_H__ */
