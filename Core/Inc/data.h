/**
 ******************************************************************************
 * @file           : data.h
 * @brief          : Dashboard data
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
    _Bool ready_to_drive;
    _Bool inverters_ready;
    _Bool safety_front;
    _Bool safety_rear;
    uint8_t battery_temperature;
    uint8_t inverter_temperature;
    uint8_t oil_temperature;
    uint8_t oil_pressure;
    uint8_t coolant_temperature;
    uint8_t coolant_pressure;
    uint8_t speed;
    uint16_t soc;
    uint16_t rpm;
    uint8_t power;
    uint16_t distance;
    uint16_t range;
} Data_TypeDef;

typedef struct {
	uint32_t bms_hv_last_frame_time;
	uint32_t bms_lv_last_frame_time;
	uint32_t frontbox_last_frame_time;
	uint32_t rearbox_last_frame_time;
} TimeoutData_TypeDef;

typedef struct {
    int32_t pace;
    uint32_t current_lap;
    uint32_t last_lap;
    uint32_t best_lap;
} TimerData_TypeDef;

typedef struct {
    _Bool led_test;
    _Bool ams_led;
    _Bool fuse_led;
    _Bool safety_led;
    _Bool rtd_button;
    _Bool tsa_button;
    _Bool usr_button;
    _Bool previous_rtd_button;
    _Bool previous_tsa_button;
    _Bool previous_usr_button;
    uint32_t rtd_timer;
    uint32_t tsa_timer;
    uint32_t usr_timer;
} InterfaceData_TypeDef;

/* Public defines ------------------------------------------------------------*/
#define DASH_TIMEOUT_DURATION 800
#define DASH_RPM_MAX 20000
#define DASH_BUTTON_DEBOUNCING_TIME 1000
#define DASH_BUTTON_POOLING_RATE 25

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern Data_TypeDef sharedData;
extern TimeoutData_TypeDef timeoutData;
extern TimerData_TypeDef timerData;
extern InterfaceData_TypeDef interfaceData;

/* Public function prototypes ------------------------------------------------*/

#endif /* __DASH_H__ */
