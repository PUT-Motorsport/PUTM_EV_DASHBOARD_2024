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
    _Bool rtd_button_pressed;
	_Bool tsa_button_pressed;

    // Inverters
    _Bool inverters_ready;
    _Bool inv_FL_status;
    _Bool inv_FR_status;
    _Bool inv_RL_status;
    _Bool inv_RR_status;
    _Bool inv_FL_error;
    _Bool inv_FR_error;
    _Bool inv_RL_error;
    _Bool inv_RR_error;

    // Safety
    _Bool safety_front;
    _Bool safety_rear;

    //PDU
    uint8_t pc_status;
    uint8_t fan_status;
    uint8_t pump_status;
    uint8_t inverter_status;
    uint8_t fbox_status;
    uint8_t sdc_status;
    uint8_t dash_status;
    uint8_t tsal_hv_status;
    uint8_t rbox_diagport_brake_l_status;
    uint8_t brake_ir_air_status;

    //Miscellaneous
    uint8_t oil_pressure;
    uint8_t coolant_pressure;
    uint16_t front_brake_pressure;
    uint16_t rear_brake_pressure;
    uint8_t speed;
    uint16_t rpm;
    uint16_t power;
    uint16_t distance;
    uint16_t range;

    //Soc
    uint16_t soc_hv;
	uint16_t soc_lv;
} Data_TypeDef;

typedef struct {
    //Motors
    uint8_t motor_front_left_temperature;
    uint8_t motor_front_right_temperature;
    uint8_t motor_rear_left_temperature;
    uint8_t motor_rear_right_temperature;
    //Inverters
    uint8_t frontRightInverterTemperature;
    uint8_t frontLeftInverterTemperature;
    uint8_t rearRightInverterTemperature;
    uint8_t rearLeftInverterTemperature;
    //Coolant
    uint8_t coolant_in_temperature;
    uint8_t coolant_out_temperature;
    //Battery
    uint8_t battery_hv_temperature;
    uint8_t battery_lv_temperature;
    //Oil
    uint8_t oil_temperature;
} TemperatureData_TypeDef;

typedef struct{
	//Frontbox Safety
	_Bool sense_left_kill;
	_Bool sense_right_kill;
	_Bool sense_driver_kill;
	_Bool sense_inertia;
	_Bool sense_bspd;
	_Bool sense_apps;
	_Bool sense_overtravel;
	_Bool is_braking;
	_Bool safety_suspension_fl;
	_Bool safety_suspension_fr;
	//Rearbox Safety
	_Bool safety_tsmp;
	_Bool safety_hv_battery;
	_Bool safety_inv_hv;
	_Bool safety_hvd;
	_Bool safety_inv;
	_Bool safety_wheel_fl;
	_Bool safety_wheel_fr;
	_Bool safety_wheel_rl;
	_Bool safety_wheel_rr;
	_Bool safety_suspension_rl;
	_Bool safety_suspension_rr;
	_Bool safety_motor_front;
}SafetyData_TypeDef;

typedef struct {
	uint32_t bms_hv_last_frame_time;
	uint32_t bms_lv_last_frame_time;
	uint32_t frontbox_last_frame_time;
	uint32_t frontbox_safety_last_frame_time;
	uint32_t frontbox_driver_input_last_frame_time;
	uint32_t rearbox_last_frame_time;
	uint32_t rearbox_safety_last_frame_time;
	uint32_t rearbox_miscellaneous_last_frame_time;
	uint32_t rearbox_temperatures_last_frame_time;
	uint32_t pc_last_frame_time;
	uint32_t pc_temp_last_frame_time;
	uint32_t pc_laptimer_last_frame_time;
	uint32_t pdu_data_last_frame_time;
	uint32_t pdu_channel_last_frame_time;
} TimeoutData_TypeDef;

typedef struct {
    int16_t pace;
    uint16_t current_lap;
    uint16_t last_lap;
    uint16_t best_lap;
    uint8_t lap_counter;
} TimerData_TypeDef;

typedef struct {
    _Bool led_test;
    _Bool ams_led;
    _Bool fuse_led;
    _Bool safety_led;
    _Bool rtd_button;
    _Bool tsa_button;
    _Bool cs_button;
    _Bool drs_button;
    _Bool usr_button;
    _Bool previous_rtd_button;
    _Bool previous_tsa_button;
    _Bool previous_usr_button;
    _Bool previous_cs_button;
    _Bool previous_drs_button;
    _Bool drs_status;
    _Bool precharge_status;
    uint32_t rtd_timer;
    uint32_t tsa_timer;
    uint32_t usr_timer;
    uint32_t drs_timer;
    uint32_t cs_timer;
} InterfaceData_TypeDef;

typedef struct{
	_Bool MainScreen;
	_Bool RaceScreen;
	_Bool NotificationScreen;
    _Bool DiagnosticScreen;
    _Bool PduScreen;
    _Bool VpSettingsScreen;
}ScreenStatus_TypeDef;



/* Public defines ------------------------------------------------------------*/
#define DASH_TIMEOUT_DURATION 800
#define DASH_RPM_MAX 20000
#define DASH_BUTTON_DEBOUNCING_TIME 1000
#define DASH_BUTTON_POOLING_RATE 25

/* Public macros -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern Data_TypeDef sharedData;
extern TemperatureData_TypeDef temperatureData;
extern SafetyData_TypeDef safetyData;
extern TimeoutData_TypeDef timeoutData;
extern TimerData_TypeDef timerData;
extern InterfaceData_TypeDef interfaceData;
extern ScreenStatus_TypeDef screenStatus;


/* Public function prototypes ------------------------------------------------*/

#endif /* __DASH_H__ */
