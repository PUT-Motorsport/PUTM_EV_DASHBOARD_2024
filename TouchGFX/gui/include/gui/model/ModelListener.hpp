#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <stdint.h>

class ModelListener {
public:
	ModelListener(): model(0) {}
	virtual ~ModelListener() {}
	void bind(Model *m) { model = m; }

    virtual void setClock(uint32_t time) {}
    virtual void setConnection(bool status) {}
    virtual void setWarning(bool status) {}
    virtual void setRadio(bool status) {}
    virtual void setBatteryTemperature(uint8_t temperature) {}
    virtual void setInverterTemperature(uint8_t temperature) {}
    virtual void setOilTemperature(uint8_t temperature) {}
    virtual void setOilPressure(uint8_t pressure) {}
    virtual void setCoolantTemperature(uint8_t temperature) {}
    virtual void setCoolantPressure(uint8_t pressure) {}
    virtual void setPace(int32_t pace)  {}
    virtual void setSpeed(uint8_t speed) {}
    virtual void setSoc(uint8_t soc) {}
    virtual void setRpm(uint16_t rpm) {}
    virtual void setPower(uint8_t power) {}
    virtual void setDistance(uint16_t distance) {}
    virtual void setRange(uint16_t range) {}
    virtual void setCurrentLap(uint32_t time) {}
    virtual void setLastLap(uint32_t time) {}
    virtual void setBestLap(uint32_t time) {}

protected:
	Model *model;
};

#endif // MODELLISTENER_HPP
