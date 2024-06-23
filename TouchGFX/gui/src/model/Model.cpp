#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "cmsis_os2.h"

#include <string.h>

extern "C" {
	extern osMutexId_t sharedDataMutexHandle;
	extern osMutexId_t timerDataMutexHandle;
	extern Data_TypeDef sharedData;
	extern TimerData_TypeDef timerData;
}

Model::Model() : modelListener(0) { }

void Model::tick() {
	if (modelListener != 0) {
		modelListener->toggleElements();

		// TODO: Use templates
		if (osMutexAcquire(sharedDataMutexHandle, osWaitForever) == osOK) {
			m_sharedData = sharedData;
			osMutexRelease(sharedDataMutexHandle);

			if (memcmp(&m_sharedData.time, &m_sharedDataPrev.time,
					sizeof(m_sharedData.time)) != 0 || m_firstIter) {
				m_sharedDataPrev.time = m_sharedData.time;
				modelListener->setClock(m_sharedData.time);
			}

			if (memcmp(&m_sharedData.connection, &m_sharedDataPrev.connection,
					sizeof(m_sharedData.connection)) != 0 || m_firstIter) {
				m_sharedDataPrev.connection = m_sharedData.connection;
				modelListener->setConnection(m_sharedData.connection);
			}

			if (memcmp(&m_sharedData.warning, &m_sharedDataPrev.warning,
					sizeof(m_sharedData.warning)) != 0 || m_firstIter) {
				m_sharedDataPrev.warning = m_sharedData.warning;
				modelListener->setWarning(m_sharedData.warning);
			}

			if (memcmp(&m_sharedData.radio, &m_sharedDataPrev.radio,
					sizeof(m_sharedData.radio)) != 0 || m_firstIter) {
				m_sharedDataPrev.radio = m_sharedData.radio;
				modelListener->setRadio(m_sharedData.radio);
			}

			if (memcmp(&m_sharedData.ready_to_drive, &m_sharedDataPrev.ready_to_drive,
					sizeof(m_sharedData.ready_to_drive)) != 0 || m_firstIter) {
				m_sharedDataPrev.ready_to_drive = m_sharedData.ready_to_drive;
				modelListener->setReadyToDrive(m_sharedData.ready_to_drive);
			}

			if (memcmp(&m_sharedData.inverters_ready, &m_sharedDataPrev.inverters_ready,
					sizeof(m_sharedData.inverters_ready)) != 0 || m_firstIter) {
				m_sharedDataPrev.inverters_ready = m_sharedData.inverters_ready;
				modelListener->setInvertersReady(m_sharedData.inverters_ready);
			}

			if (memcmp(&m_sharedData.battery_temperature,
					&m_sharedDataPrev.battery_temperature,
					sizeof(m_sharedData.battery_temperature)) != 0 || m_firstIter) {
				m_sharedDataPrev.battery_temperature =
						m_sharedData.battery_temperature;
				modelListener->setBatteryTemperature(
						m_sharedData.battery_temperature);
			}

			if (memcmp(&m_sharedData.inverter_temperature,
					&m_sharedDataPrev.inverter_temperature,
					sizeof(m_sharedData.inverter_temperature)) != 0 || m_firstIter) {
				m_sharedDataPrev.inverter_temperature =
						m_sharedData.inverter_temperature;
				modelListener->setInverterTemperature(
						m_sharedData.inverter_temperature);
			}

			if (memcmp(&m_sharedData.oil_temperature,
					&m_sharedDataPrev.oil_temperature,
					sizeof(m_sharedData.oil_temperature)) != 0 || m_firstIter) {
				m_sharedDataPrev.oil_temperature = m_sharedData.oil_temperature;
				modelListener->setOilTemperature(m_sharedData.oil_temperature);
			}

			if (memcmp(&m_sharedData.oil_pressure,
					&m_sharedDataPrev.oil_pressure,
					sizeof(m_sharedData.oil_pressure)) != 0 || m_firstIter) {
				m_sharedDataPrev.oil_pressure = m_sharedData.oil_pressure;
				modelListener->setOilPressure(m_sharedData.oil_pressure);
			}

			if (memcmp(&m_sharedData.coolant_temperature,
					&m_sharedDataPrev.coolant_temperature,
					sizeof(m_sharedData.coolant_temperature)) != 0 || m_firstIter) {
				m_sharedDataPrev.coolant_temperature =
						m_sharedData.coolant_temperature;
				modelListener->setCoolantTemperature(
						m_sharedData.coolant_temperature);
			}

			if (memcmp(&m_sharedData.coolant_pressure,
					&m_sharedDataPrev.coolant_pressure,
					sizeof(m_sharedData.coolant_pressure)) != 0 || m_firstIter) {
				m_sharedDataPrev.coolant_pressure =
						m_sharedData.coolant_pressure;
				modelListener->setCoolantPressure(
						m_sharedData.coolant_pressure);
			}

			if (memcmp(&m_sharedData.speed, &m_sharedDataPrev.speed,
					sizeof(m_sharedData.speed)) != 0 || m_firstIter) {
				m_sharedDataPrev.speed = m_sharedData.speed;
				modelListener->setSpeed(m_sharedData.speed);
			}

			if (memcmp(&m_sharedData.soc, &m_sharedDataPrev.soc,
					sizeof(m_sharedData.soc)) != 0 || m_firstIter) {
				m_sharedDataPrev.soc = m_sharedData.soc;
				modelListener->setSoc(m_sharedData.soc);
			}

			if (memcmp(&m_sharedData.rpm, &m_sharedDataPrev.rpm,
					sizeof(m_sharedData.rpm)) != 0 || m_firstIter) {
				m_sharedDataPrev.rpm = m_sharedData.rpm;
				modelListener->setRpm(m_sharedData.rpm);
			}

			if (memcmp(&m_sharedData.power, &m_sharedDataPrev.power,
					sizeof(m_sharedData.power)) != 0 || m_firstIter) {
				m_sharedDataPrev.power = m_sharedData.power;
				modelListener->setPower(m_sharedData.power);
			}

			if (memcmp(&m_sharedData.distance, &m_sharedDataPrev.distance,
					sizeof(m_sharedData.distance)) != 0 || m_firstIter) {
				m_sharedDataPrev.distance = m_sharedData.distance;
				modelListener->setDistance(m_sharedData.distance);
			}

			if (memcmp(&m_sharedData.range, &m_sharedDataPrev.range,
					sizeof(m_sharedData.range)) != 0 || m_firstIter) {
				m_sharedDataPrev.range = m_sharedData.range;
				modelListener->setRange(m_sharedData.range);
			}
		}

		if (osMutexAcquire(timerDataMutexHandle, osWaitForever) == osOK) {
			m_timerData = timerData;
			osMutexRelease(timerDataMutexHandle);

			if (memcmp(&m_timerData.pace, &m_timerDataPrev.pace,
					sizeof(m_timerData.pace)) != 0 || m_firstIter) {
				m_timerDataPrev.pace = m_timerData.pace;
				modelListener->setPace(m_timerData.pace);
			}

			if (memcmp(&m_timerData.current_lap, &m_timerDataPrev.current_lap,
					sizeof(m_timerData.current_lap)) != 0 || m_firstIter) {
				m_timerDataPrev.current_lap = m_timerData.current_lap;
				modelListener->setCurrentLap(m_timerData.current_lap);
			}

			if (memcmp(&m_timerData.last_lap, &m_timerDataPrev.last_lap,
					sizeof(m_timerData.last_lap)) != 0 || m_firstIter) {
				m_timerDataPrev.last_lap = m_timerData.last_lap;
				modelListener->setLastLap(m_timerData.last_lap);
			}

			if (memcmp(&m_timerData.best_lap, &m_timerDataPrev.best_lap,
					sizeof(m_timerData.best_lap)) != 0 || m_firstIter) {
				m_timerDataPrev.best_lap = m_timerData.best_lap;
				modelListener->setBestLap(m_timerData.best_lap);
			}
		}
	}
}
