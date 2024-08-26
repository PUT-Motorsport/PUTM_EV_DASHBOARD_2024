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

            m_sharedDataPrev.battery_temperature = m_sharedData.battery_temperature;
            modelListener->setBatteryTemperature(m_sharedData.battery_temperature);

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

            m_sharedDataPrev.speed = m_sharedData.speed;
            modelListener->setSpeed(m_sharedData.speed);

            m_sharedDataPrev.soc = m_sharedData.soc;
            modelListener->setSoc(m_sharedData.soc);

            m_sharedDataPrev.rpm = m_sharedData.rpm;
            modelListener->setRpm(m_sharedData.rpm);

            m_sharedDataPrev.power = m_sharedData.power;
            modelListener->setPower(m_sharedData.power);

            m_sharedDataPrev.distance = m_sharedData.distance;
            modelListener->setDistance(m_sharedData.distance);

            m_sharedDataPrev.range = m_sharedData.range;
            modelListener->setRange(m_sharedData.range);
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
