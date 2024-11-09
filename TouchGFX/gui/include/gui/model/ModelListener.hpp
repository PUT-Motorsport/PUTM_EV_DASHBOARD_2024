#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <stdint.h>

class ModelListener {
  public:
    ModelListener() : model(0) {}
    virtual ~ModelListener() {}
    void bind(Model* m) { model = m; }

    virtual void setClock(uint32_t time) {}
    virtual void setConnection(bool status) {}
    virtual void setWarning(bool status) {}
    virtual void setRadio(bool status) {}
    virtual void setReadyToDrive(bool status) {}
    virtual void setInvertersReady(bool status) {}
    virtual void setBatteryLVTemperature(uint8_t temperature) {}
    virtual void setBatteryHVTemperature(uint8_t temperature) {}
    virtual void setInverterTemperature(uint8_t temperature) {}
    virtual void setOilTemperature(uint8_t temperature) {}
    virtual void setOilPressure(uint8_t pressure) {}
    virtual void setCoolantTemperature(uint8_t temperature) {}
    virtual void setCoolantPressure(uint8_t pressure) {}
    virtual void setPace(int32_t pace) {}

    virtual void setMotorFrontLeftTemperature(uint8_t temperature) {}
    virtual void setMotorFrontRightTemperature(uint8_t temperature) {}
    virtual void setMotorRearLeftTemperature(uint8_t temperature) {}
    virtual void setMotorRearRightTemperature(uint8_t temperature) {}

    virtual void setSocHv(uint8_t soc) {}
    virtual void setSocLv(uint8_t soc) {}
    virtual void setRpm(uint16_t rpm) {}
    virtual void setRange(uint16_t range) {}
    virtual void setCurrentLap(uint32_t time) {}
    virtual void setLastLap(uint32_t time) {}
    virtual void setBestLap(uint32_t time) {}

    //Safety
    virtual void setSafetyLeftKill(bool status){}
    virtual void setSafetyRightKill(bool status) {}
    virtual void setSafetyDriverKill(bool status){}
    virtual void setSafetyInertia(bool status) {}
    virtual void setSafetyBspd(bool status){}
    virtual void setSafetyOvertravel(bool status) {}
    virtual void setSafetyRightWheel(bool status){}
    virtual void setSafetyIsBraking(bool status) {}
    virtual void setSafetyRuf1(bool status){}
    virtual void setSafetyRuf2(bool status) {}
    virtual void setSafetyAsms(bool status){}
    virtual void setSafetyFw(bool status) {}
    virtual void setSafetyHv(bool status){}
    virtual void setSafetyRes(bool status) {}
    virtual void setSafetyHvd(bool status){}
    virtual void setSafetyInv(bool status) {}
    virtual void setSafetyWheelFL(bool status){}
    virtual void setSafetyWheelFR(bool status) {}
    virtual void setSafetyWheelRL(bool status){}
    virtual void setSafetyWheelRR(bool status) {}


    virtual void toggleElements() {}

  protected:
    Model* model;
};

#endif  // MODELLISTENER_HPP
