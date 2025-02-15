#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <stdint.h>

class ModelListener {
  public:
    ModelListener() : model(0) {}
    virtual ~ModelListener() {}
    void bind(Model* m) { model = m; }

    //Main Screen
    virtual void setClock(uint32_t time) {}
    virtual void setConnection(bool status) {}
    virtual void setWarning(bool status) {}
    virtual void setRadio(bool status) {}
    virtual void setReadyToDrive(bool status) {}
    virtual void setInvertersStatus(bool inv_ready,
    							    bool inv_FL_status,
									bool inv_FR_status,
									bool inv_RL_status,
									bool inv_RR_status,
									bool inv_FL_error,
									bool inv_FR_error,
									bool inv_RL_error,
									bool inv_RR_error) {}
    virtual void setDrsStatus(bool status) {}
    virtual void setBatteryLVTemperature(uint8_t temperature) {}
    virtual void setOilTemperature(uint8_t temperature) {}
    virtual void setOilPressure(uint8_t pressure) {}
    virtual void setCoolantTemperature(uint8_t temperature) {}
    virtual void setCoolantPressure(uint8_t pressure) {}
    virtual void setCurrentLap(uint32_t time) {}
    virtual void setLastLap(uint32_t time) {}
    virtual void setBestLap(uint32_t time) {}
    virtual void setMotorFrontLeftTemperature(uint8_t temperature) {}
    virtual void setMotorFrontRightTemperature(uint8_t temperature) {}
    virtual void setMotorRearLeftTemperature(uint8_t temperature) {}
    virtual void setMotorTemp(uint8_t temperatureMotorFL,
    						  uint8_t temperatureMotorFR,
    						  uint8_t temperatureMotorRL,
    					      uint8_t temperatureMotorRR){}
    virtual void setMotorRearRightTemperature(uint8_t temperature) {}
    virtual void setSDC(SafetyData_TypeDef& safetyData) {}

    virtual void setInverterTemperature(uint8_t inv_FL_temperature,
    									uint8_t inv_FR_temperature,
										uint8_t inv_RL_temperature,
										uint8_t inv_RR_temperature) {}

    //Race Screen
    virtual void setSocHv(uint8_t soc) {}
    virtual void setSocLv(uint8_t soc) {}
    virtual void setRpm(uint16_t rpm) {}
    virtual void setRange(uint16_t range) {}
    virtual void setBatteryHVTemperature(uint8_t temperature) {}
    virtual void setPace(int32_t pace) {}

    virtual void switchScreenRM(){}
    virtual void switchScreenMR(){}

    //Notification Screen
    virtual void setCheckErrors(bool bspd,
	   	   	   	   	   	        uint8_t inv_FL_temperature,
								uint8_t inv_FR_temperature,
								uint8_t inv_RL_temperature,
								uint8_t inv_RR_temperature,
								uint8_t lv_temp,
								uint8_t hv_temp,
								uint8_t lv_soc,
								uint8_t hv_soc,
								uint8_t motor_fl_temp,
								uint8_t motor_fr_temp,
								uint8_t motor_rl_temp,
								uint8_t motor_rr_temp){}
    virtual void toggleElements(){}


  protected:
    Model* model;
};

#endif  // MODELLISTENER_HPP
