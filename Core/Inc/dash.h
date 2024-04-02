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

/* Public defines ------------------------------------------------------------*/
typedef struct {
	uint32_t time;
	_Bool connection;
	_Bool warning;
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

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* __DASH_H__ */
