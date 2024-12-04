#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "cmsis_os2.h"

#include <string.h>

extern "C" {
extern osMutexId_t sharedDataMutexHandle;
extern osMutexId_t timerDataMutexHandle;
}

Model::Model() : modelListener(0) {}

void Model::tick() {

    if(modelListener != 0) {
        modelListener->toggleElements();

        if(osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
            m_sharedData = sharedData;
            osMutexRelease(sharedDataMutexHandle);

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
            modelListener->setInvertersReady(m_sharedData.inverters_ready);

            m_sharedDataPrev.battery_hv_temperature = m_sharedData.battery_hv_temperature;
            modelListener->setBatteryHVTemperature(m_sharedData.battery_hv_temperature);

            m_sharedDataPrev.battery_lv_temperature = m_sharedData.battery_lv_temperature;
            modelListener->setBatteryLVTemperature(m_sharedData.battery_lv_temperature);

            m_sharedDataPrev.inverter_temperature = m_sharedData.inverter_temperature;
            modelListener->setInverterTemperature(m_sharedData.inverter_temperature);

            m_sharedDataPrev.oil_temperature = m_sharedData.oil_temperature;
            modelListener->setOilTemperature(m_sharedData.oil_temperature);

            m_sharedDataPrev.oil_pressure = m_sharedData.oil_pressure;
            modelListener->setOilPressure(m_sharedData.oil_pressure);

            m_sharedDataPrev.coolant_temperature = m_sharedData.coolant_temperature;
            modelListener->setCoolantTemperature(m_sharedData.coolant_temperature);

            m_sharedDataPrev.coolant_pressure = m_sharedData.coolant_pressure;
            modelListener->setCoolantPressure(m_sharedData.coolant_pressure);

            m_sharedDataPrev.motor_front_left_temperature = m_sharedData.motor_front_left_temperature;
            modelListener->setMotorFrontLeftTemperature(m_sharedData.motor_front_left_temperature);

            m_sharedDataPrev.motor_front_right_temperature = m_sharedData.motor_front_right_temperature;
            modelListener->setMotorFrontRightTemperature(m_sharedData.motor_front_right_temperature);

            m_sharedDataPrev.motor_rear_left_temperature = m_sharedData.motor_rear_left_temperature;
            modelListener->setMotorRearLeftTemperature(m_sharedData.motor_rear_left_temperature);

            m_sharedDataPrev.motor_rear_right_temperature = m_sharedData.motor_rear_right_temperature;
            modelListener->setMotorRearRightTemperature(m_sharedData.motor_rear_right_temperature);

            m_sharedDataPrev.soc_hv = m_sharedData.soc_hv;
            modelListener->setSocHv(m_sharedData.soc_hv);

            m_sharedDataPrev.soc_lv = m_sharedData.soc_lv;
            modelListener->setSocLv(m_sharedData.soc_lv);

            m_sharedDataPrev.rpm = m_sharedData.rpm;
            modelListener->setRpm(m_sharedData.rpm);

            m_sharedDataPrev.range = m_sharedData.range;
            modelListener->setRange(m_sharedData.range);

            //Safety
            m_sharedSafetyDataPrev.sense_left_kill = m_sharedSafetyData.sense_left_kill;
            modelListener->setSafetyLeftKill(m_sharedSafetyData.sense_left_kill);

            m_sharedSafetyDataPrev.sense_right_kill = m_sharedSafetyData.sense_right_kill;
            modelListener->setSafetyRightKill(m_sharedSafetyData.sense_right_kill);

            m_sharedSafetyDataPrev.sense_driver_kill = m_sharedSafetyData.sense_driver_kill;
            modelListener->setSafetyDriverKill(m_sharedSafetyData.sense_driver_kill);

            m_sharedSafetyDataPrev.sense_inertia = m_sharedSafetyData.sense_inertia;
            modelListener->setSafetyInertia(m_sharedSafetyData.sense_inertia);

            m_sharedSafetyDataPrev.sense_bspd = m_sharedSafetyData.sense_bspd;
            modelListener->setSafetyBspd(m_sharedSafetyData.sense_bspd);

            m_sharedSafetyDataPrev.sense_overtravel = m_sharedSafetyData.sense_overtravel;
            modelListener->setSafetyOvertravel(m_sharedSafetyData.sense_overtravel);

            m_sharedSafetyDataPrev.sense_right_wheel = m_sharedSafetyData.sense_right_wheel;
            modelListener->setSafetyRightWheel(m_sharedSafetyData.sense_right_wheel);

            m_sharedSafetyDataPrev.is_braking = m_sharedSafetyData.is_braking;
            modelListener->setSafetyIsBraking(m_sharedSafetyData.is_braking);

            m_sharedSafetyDataPrev.safety_rfu1 = m_sharedSafetyData.safety_rfu1;
            modelListener->setSafetyRuf1(m_sharedSafetyData.safety_rfu1);

            m_sharedSafetyDataPrev.safety_rfu2 = m_sharedSafetyData.safety_rfu2;
            modelListener->setSafetyRuf2(m_sharedSafetyData.safety_rfu2);

            m_sharedSafetyDataPrev.safety_asms = m_sharedSafetyData.safety_asms;
            modelListener->setSafetyAsms(m_sharedSafetyData.safety_asms);

            m_sharedSafetyDataPrev.safety_fw = m_sharedSafetyData.safety_fw;
            modelListener->setSafetyFw(m_sharedSafetyData.safety_fw);

            m_sharedSafetyDataPrev.safety_hv = m_sharedSafetyData.safety_hv;
            modelListener->setSafetyHv(m_sharedSafetyData.safety_hv);

            m_sharedSafetyDataPrev.safety_res = m_sharedSafetyData.safety_res;
            modelListener->setSafetyRes(m_sharedSafetyData.safety_res);

            m_sharedSafetyDataPrev.safety_hvd = m_sharedSafetyData.safety_hvd;
            modelListener->setSafetyHvd(m_sharedSafetyData.safety_hvd);

            m_sharedSafetyDataPrev.safety_inv = m_sharedSafetyData.safety_inv;
            modelListener->setSafetyInv(m_sharedSafetyData.safety_inv);
            //
            m_sharedSafetyDataPrev.safety_wheel_fl = m_sharedSafetyData.safety_wheel_fl;
            modelListener->setSafetyWheelFL(m_sharedSafetyData.safety_wheel_fl);

            m_sharedSafetyDataPrev.safety_wheel_fr = m_sharedSafetyData.safety_wheel_fr;
            modelListener->setSafetyWheelFR(m_sharedSafetyData.safety_wheel_fr);

            m_sharedSafetyDataPrev.safety_wheel_rl = m_sharedSafetyData.safety_wheel_rl;
            modelListener->setSafetyWheelRL(m_sharedSafetyData.safety_wheel_rl);

            m_sharedSafetyDataPrev.safety_wheel_rr = m_sharedSafetyData.safety_wheel_rr;
            modelListener->setSafetyWheelRR(m_sharedSafetyData.safety_wheel_rr);

        }

        if(osMutexAcquire(timerDataMutexHandle, osWaitForever) == osOK) {
            m_timerData = timerData;
            osMutexRelease(timerDataMutexHandle);

            m_timerDataPrev.pace = m_timerData.pace;
            modelListener->setPace(m_timerData.pace);

            m_timerDataPrev.current_lap = m_timerData.current_lap;
            modelListener->setCurrentLap(m_timerData.current_lap);

            m_timerDataPrev.last_lap = m_timerData.last_lap;
            modelListener->setLastLap(m_timerData.last_lap);

            m_timerDataPrev.best_lap = m_timerData.best_lap;
            modelListener->setBestLap(m_timerData.best_lap);
        }
    }
}
