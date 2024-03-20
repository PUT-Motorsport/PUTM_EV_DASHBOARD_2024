#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cmsis_os2.h>
#include <stdbool.h>

extern "C" {
extern osMessageQueueId_t communicationQueueHandle;
}

Model::Model() :
		modelListener(0) {

}

void Model::tick() {
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
	    int32_t pace;
	    uint8_t speed;
	    uint8_t soc;
	    uint16_t rpm;
	    uint8_t power;
	    uint16_t distance;
	    uint16_t range;
	    uint32_t current_lap;
	    uint32_t last_lap;
	    uint32_t best_lap;
	} Data_TypeDef;

	static Data_TypeDef data = {
	        .time = 49020,
	        .connection = false,
	        .warning = false,
	        .radio = false,
	        .battery_temperature = 10,
	        .inverter_temperature = 20,
	        .oil_temperature = 30,
	        .oil_pressure = 40,
	        .coolant_temperature = 50,
	        .coolant_pressure = 60,
	        .pace = -2123,
	        .speed = 120,
	        .soc = 100,
	        .rpm = 1500,
	        .power = 70,
	        .distance = 12000,
	        .range = 100,
	        .current_lap = 677876,
	        .last_lap = 1000,
	        .best_lap = 60000,
	};

	if (modelListener != 0) {
//		if (osMessageQueueGet(communicationQueueHandle, &data, 0, 0) == osOK) {
			modelListener->setClock(data.time);
			modelListener->setConnection(data.connection);
			modelListener->setWarning(data.connection);
			modelListener->setRadio(data.radio);
			modelListener->setBatteryTemperature(data.battery_temperature);
			modelListener->setInverterTemperature(data.inverter_temperature);
			modelListener->setOilTemperature(data.oil_temperature);
			modelListener->setOilPressure(data.oil_pressure);
			modelListener->setCoolantTemperature(data.coolant_temperature);
			modelListener->setCoolantPressure(data.coolant_pressure);
			modelListener->setPace(data.pace);
			modelListener->setSpeed(data.speed);
			modelListener->setSoc(data.soc);
			modelListener->setRpm(data.rpm);
			modelListener->setPower(data.power);
			modelListener->setDistance(data.distance);
			modelListener->setRange(data.range);
			modelListener->setCurrentLap(data.current_lap);
			modelListener->setLastLap(data.last_lap);
			modelListener->setBestLap(data.best_lap);
//		}
	}
}
