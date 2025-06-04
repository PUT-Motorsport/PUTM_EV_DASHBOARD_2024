#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "cmsis_os2.h"

#include <string.h>

extern "C" {
extern osMutexId_t sharedDataMutexHandle;
extern osMutexId_t timerDataMutexHandle;
extern osMutexId_t sdcDataMutexHandle;
}

Model::Model() : modelListener(0) {}

void Model::tick() {

    if(modelListener != 0) {
        modelListener->switchScreenMR();
        modelListener->switchScreenRM();


        if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
            m_sharedData = sharedData;

            m_sharedDataPrev.time = m_sharedData.time;
            modelListener->setClock(m_sharedData.time);

            m_sharedDataPrev.connection = m_sharedData.connection;
            modelListener->setConnection(m_sharedData.connection);

            m_sharedDataPrev.warning = m_sharedData.warning;
            modelListener->setWarning(m_sharedData.warning);

            m_sharedDataPrev.radio = m_sharedData.radio;
            modelListener->setRadio(m_sharedData.radio);

            m_sharedDataPrev.ready_to_drive = m_sharedData.ready_to_drive;
            modelListener->setReadyToDrive(m_sharedData.ready_to_drive);

            m_sharedDataPrev.inverters_ready = m_sharedData.inverters_ready;
            m_sharedDataPrev.inv_FL_status = m_sharedData.inv_FL_status;
            m_sharedDataPrev.inv_FR_status = m_sharedData.inv_FR_status;
            m_sharedDataPrev.inv_RL_status = m_sharedData.inv_RL_status;
            m_sharedDataPrev.inv_RR_status = m_sharedData.inv_RR_status;

            m_sharedDataPrev.inv_FL_error = m_sharedData.inv_FL_error;
            m_sharedDataPrev.inv_FR_error = m_sharedData.inv_FR_error;
            m_sharedDataPrev.inv_RL_error = m_sharedData.inv_RL_error;
            m_sharedDataPrev.inv_RR_error = m_sharedData.inv_RR_error;

            modelListener->setInvertersStatus(m_sharedData.inverters_ready,
            								  m_sharedData.inv_FL_status,
            								  m_sharedData.inv_FR_status,
											  m_sharedData.inv_RL_status,
											  m_sharedData.inv_RR_status,
											  m_sharedData.inv_FL_error,
											  m_sharedData.inv_FR_error,
											  m_sharedData.inv_RL_error,
											  m_sharedData.inv_RR_error);

            m_sharedDataPrev.battery_hv_temperature = m_sharedData.battery_hv_temperature;
            modelListener->setBatteryHVTemperature(m_sharedData.battery_hv_temperature);

            m_sharedDataPrev.battery_lv_temperature = m_sharedData.battery_lv_temperature;
            modelListener->setBatteryLVTemperature(m_sharedData.battery_lv_temperature);

            m_sharedDataPrev.frontRightInverterTemperature = m_sharedData.frontRightInverterTemperature;
            m_sharedDataPrev.frontLeftInverterTemperature = m_sharedData.frontLeftInverterTemperature;
            m_sharedDataPrev.rearRightInverterTemperature = m_sharedData.rearRightInverterTemperature;
            m_sharedDataPrev.rearLeftInverterTemperature = m_sharedData.rearLeftInverterTemperature;

            modelListener->setInverterTemperature(m_sharedData.frontLeftInverterTemperature,
            									  m_sharedData.frontRightInverterTemperature,
												  m_sharedData.rearLeftInverterTemperature,
												  m_sharedData.rearRightInverterTemperature);

            m_sharedDataPrev.front_brake_pressure = m_sharedData.front_brake_pressure;
            modelListener->setFrontBrakePressure(m_sharedData.front_brake_pressure);

            m_sharedDataPrev.coolant_in_temperature = m_sharedData.coolant_in_temperature;
            modelListener->setCoolantInTemperature(m_sharedData.coolant_in_temperature);

            m_sharedDataPrev.coolant_out_temperature = m_sharedData.coolant_out_temperature;
            modelListener->setCoolantOutTemperature(m_sharedData.coolant_out_temperature);

            m_sharedDataPrev.rear_brake_pressure = m_sharedData.rear_brake_pressure;
            modelListener->setRearBrakePressure(m_sharedData.rear_brake_pressure);

            m_sharedDataPrev.motor_front_left_temperature = m_sharedData.motor_front_left_temperature;
            modelListener->setMotorFrontLeftTemperature(m_sharedData.motor_front_left_temperature);

            m_sharedDataPrev.motor_front_right_temperature = m_sharedData.motor_front_right_temperature;
            modelListener->setMotorFrontRightTemperature(m_sharedData.motor_front_right_temperature);

            m_sharedDataPrev.motor_rear_left_temperature = m_sharedData.motor_rear_left_temperature;
            modelListener->setMotorRearLeftTemperature(m_sharedData.motor_rear_left_temperature);

            m_sharedDataPrev.motor_rear_right_temperature = m_sharedData.motor_rear_right_temperature;
            modelListener->setMotorRearRightTemperature(m_sharedData.motor_rear_right_temperature);

            modelListener->setMotorTemp(m_sharedData.motor_front_left_temperature,
            						    m_sharedData.motor_front_right_temperature,
										m_sharedData.motor_rear_left_temperature,
										m_sharedData.motor_rear_right_temperature);

            m_sharedDataPrev.soc_hv = m_sharedData.soc_hv;
            modelListener->setSocHv(m_sharedData.soc_hv);

            m_sharedDataPrev.soc_lv = m_sharedData.soc_lv;
            modelListener->setSocLv(m_sharedData.soc_lv);


            m_sharedDataPrev.rtd_button_pressed = m_sharedData.rtd_button_pressed;
            modelListener->setRtdButtonPressed(m_sharedData.rtd_button_pressed);

            m_sharedDataPrev.tsa_button_pressed = m_sharedData.tsa_button_pressed;
            modelListener->setTsaButtonPressed(m_sharedData.tsa_button_pressed);

            modelListener->setDrsStatus(interfaceData.drs_button);


            //PDU
            m_sharedDataPrev.pc_status = m_sharedData.pc_status;
            modelListener->setPduPcStatus(m_sharedData.pc_status);

            m_sharedDataPrev.fan_status = m_sharedData.fan_status;
            modelListener->setPduFanStatus(m_sharedData.fan_status);

            m_sharedDataPrev.pump_status = m_sharedData.pump_status;
            modelListener->setPduPumpStatus(m_sharedData.pump_status);

            m_sharedDataPrev.inverter_status = m_sharedData.inverter_status;
            modelListener->setPduInverterStatus(m_sharedData.inverter_status);

            m_sharedDataPrev.fbox_status = m_sharedData.fbox_status;
            modelListener->setPduFboxStatus(m_sharedData.fbox_status);

            m_sharedDataPrev.sdc_status = m_sharedData.sdc_status;
            modelListener->setPduSdcStatus(m_sharedData.sdc_status);

            m_sharedDataPrev.dash_status = m_sharedData.dash_status;
            modelListener->setPduDashStatus(m_sharedData.dash_status);

            m_sharedDataPrev.tsal_hv_status = m_sharedData.tsal_hv_status;
            modelListener->setPduTsalStatus(m_sharedData.tsal_hv_status);

            m_sharedDataPrev.rbox_diagport_brake_l_status = m_sharedData.rbox_diagport_brake_l_status;
            modelListener->setPduRboxStatus(m_sharedData.rbox_diagport_brake_l_status);

            m_sharedDataPrev.brake_ir_air_status = m_sharedData.brake_ir_air_status;
            modelListener->setPduAirStatus(m_sharedData.brake_ir_air_status);

            osMutexRelease(sharedDataMutexHandle);

        }

        if(osMutexAcquire(timerDataMutexHandle, osWaitForever) == osOK) {
            m_timerData = timerData;

            m_timerDataPrev.pace = m_timerData.pace;
            modelListener->setPace(m_timerData.pace);

            m_timerDataPrev.current_lap = m_timerData.current_lap;
            modelListener->setCurrentLap(m_timerData.current_lap);

            modelListener->setLastLap(m_timerData.current_lap);

            m_timerDataPrev.best_lap = m_timerData.best_lap;
            modelListener->setBestLap(m_timerData.best_lap);

            m_timerDataPrev.lap_counter = m_timerData.lap_counter;
            modelListener->setLap(m_timerData.lap_counter);

            osMutexRelease(timerDataMutexHandle);
        }

        if(osMutexAcquire(sdcDataMutexHandle, osWaitForever) == osOK)
        {

        	//SDC Data
        	m_sharedSafetyData = safetyData;


			m_sharedSafetyDataPrev.sense_left_kill = m_sharedSafetyData.sense_left_kill;
			m_sharedSafetyDataPrev.sense_right_kill = m_sharedSafetyData.sense_right_kill;
			m_sharedSafetyDataPrev.sense_driver_kill = m_sharedSafetyData.sense_driver_kill;
			m_sharedSafetyDataPrev.sense_inertia = m_sharedSafetyData.sense_inertia;
			m_sharedSafetyDataPrev.sense_bspd = m_sharedSafetyData.sense_bspd;
			m_sharedSafetyDataPrev.sense_apps = m_sharedSafetyData.sense_apps;
			m_sharedSafetyDataPrev.sense_overtravel = m_sharedSafetyData.sense_overtravel;
			m_sharedSafetyDataPrev.sense_right_wheel = m_sharedSafetyData.sense_right_wheel;
			m_sharedSafetyDataPrev.is_braking = m_sharedSafetyData.is_braking;
			m_sharedSafetyDataPrev.safety_rfu1 = m_sharedSafetyData.safety_rfu1;
			m_sharedSafetyDataPrev.safety_rfu2 = m_sharedSafetyData.safety_rfu2;
			m_sharedSafetyDataPrev.safety_asms = m_sharedSafetyData.safety_asms;
			m_sharedSafetyDataPrev.safety_fw = m_sharedSafetyData.safety_fw;
			m_sharedSafetyDataPrev.safety_hv = m_sharedSafetyData.safety_hv;
			m_sharedSafetyDataPrev.safety_res = m_sharedSafetyData.safety_res;
			m_sharedSafetyDataPrev.safety_hvd = m_sharedSafetyData.safety_hvd;
			m_sharedSafetyDataPrev.safety_inv = m_sharedSafetyData.safety_inv;
			m_sharedSafetyDataPrev.safety_wheel_fl = m_sharedSafetyData.safety_wheel_fl;
			m_sharedSafetyDataPrev.safety_wheel_fr = m_sharedSafetyData.safety_wheel_fr;
			m_sharedSafetyDataPrev.safety_wheel_rl = m_sharedSafetyData.safety_wheel_rl;
			m_sharedSafetyDataPrev.safety_wheel_rr = m_sharedSafetyData.safety_wheel_rr;


			modelListener->setSDC(m_sharedSafetyData);

			osMutexRelease(sdcDataMutexHandle);

        }

        //Error checking after reading all values
        modelListener->setCheckErrors(m_sharedSafetyData.sense_bspd, m_sharedSafetyData.sense_apps);
    }
}
