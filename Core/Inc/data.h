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
	//TODO: dodać zmienne potrzebne do dwóch wyświetlaczy
    uint32_t time;
    _Bool warning;
    _Bool connection;
    _Bool radio;
    _Bool ready_to_drive;
    _Bool inverters_ready;
//    _Bool safety_front;
//    _Bool safety_rear;
    uint8_t battery_hv_temperature;
    uint8_t battery_lv_temperature;
    uint8_t inverter_temperature;
    uint8_t oil_temperature;
    uint8_t oil_pressure;
    uint8_t coolant_temperature;
    uint8_t coolant_pressure;
    uint8_t motor_front_left_temperature;
    uint8_t motor_front_right_temperature;
    uint8_t motor_rear_left_temperature;
    uint8_t motor_rear_right_temperature;
    uint8_t speed;
    uint16_t soc_hv;
	uint16_t soc_lv;
    uint16_t rpm;
    uint8_t power;
    uint16_t distance;
    uint16_t range;
} Data_TypeDef;

typedef struct{
	//Frontbox Safety
	_Bool sense_left_kill;
	_Bool sense_right_kill;
	_Bool sense_driver_kill;
	_Bool sense_inertia;
	_Bool sense_bspd;
	_Bool sense_overtravel;
	_Bool sense_right_wheel;
	_Bool is_braking;
	//Rearbox Safety
	_Bool safety_rfu1;
	_Bool safety_rfu2;
	_Bool safety_asms;
	_Bool safety_fw;
	_Bool safety_hv;
	_Bool safety_res;
	_Bool safety_hvd;
	_Bool safety_inv;
	_Bool safety_wheel_fl;
	_Bool safety_wheel_fr;
	_Bool safety_wheel_rl;
	_Bool safety_wheel_rr;
}SafetyData_TypeDef;

typedef struct {
	uint32_t bms_hv_last_frame_time;
	uint32_t bms_lv_last_frame_time;
	uint32_t frontbox_last_frame_time;
	uint32_t rearbox_last_frame_time;
	uint32_t pc_last_frame_time;
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
extern SafetyData_TypeDef SafetyData;
extern TimeoutData_TypeDef timeoutData;
extern TimerData_TypeDef timerData;
extern InterfaceData_TypeDef interfaceData;

/* Public function prototypes ------------------------------------------------*/

#endif /* __DASH_H__ */
