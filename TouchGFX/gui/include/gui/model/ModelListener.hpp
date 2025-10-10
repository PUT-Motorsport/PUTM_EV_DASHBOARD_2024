/**
 * @file ModelListener.hpp
 * @brief Definition of the ModelListener interface.
 *
 * The ModelListener interface defines methods that must be implemented
 * by objects that want to receive updates from the Model.
 */

#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <stdint.h>



/**
 * @brief The ModelListener interface.
 */
class ModelListener {
  public:

    /**
     * @brief Constructor.
     */
    ModelListener() : model(0) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~ModelListener() {}

    /**
     * @brief Binds the model to the listener.
     * @param m Pointer to the model.
     */
    void bind(Model* m) { model = m; }


    // Methods for set the UI (default implementation does nothing)
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
    virtual void setFrontBrakePressure(uint16_t pressure) {}
    virtual void setCoolantInTemperature(uint8_t temperature) {}
    virtual void setCoolantOutTemperature(uint8_t temperature) {}
    virtual void setRearBrakePressure(uint16_t pressure) {}
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
    virtual void setSDC(SafetyData_TypeDef status) {}

    virtual void setInverterTemperature(uint8_t inv_FL_temperature,
    									uint8_t inv_FR_temperature,
										uint8_t inv_RL_temperature,
										uint8_t inv_RR_temperature) {}

    virtual void setRtdButtonPressed(bool status) {}
    virtual void setTsaButtonPressed(bool status) {}

    virtual void setPduPcStatus(uint8_t status) {}
    virtual void setPduFanStatus(uint8_t status) {}
    virtual void setPduPumpStatus(uint8_t status) {}
    virtual void setPduInverterStatus(uint8_t status) {}
    virtual void setPduFboxStatus(uint8_t status) {}
    virtual void setPduSdcStatus(uint8_t status) {}
    virtual void setPduDashStatus(uint8_t status) {}
    virtual void setPduTsalStatus(uint8_t status) {}
    virtual void setPduRboxStatus(uint8_t status) {}
    virtual void setPduAirStatus(uint8_t status) {}



    //Race Screen
    virtual void setSocHv(uint8_t soc) {}
    virtual void setSocLv(uint8_t soc) {}
    virtual void setBatteryHVTemperature(uint8_t temperature) {}
    virtual void setPace(int16_t pace) {}
    virtual void setLap(uint8_t value) {}

    virtual void switchScreenMain2Race(){}
    virtual void switchScreenRace2Pdu(){}
    virtual void switchScreenPdu2Vp(){}
    virtual void switchScreenVp2Diag(){}
    virtual void switchScreenDiag2DataLog(){}
    virtual void switchScreenDataLog2Main(){}

    //Notification Screen
    virtual void setCheckErrors(bool bspd, bool apps){}
    virtual void switchScreen(bool bspd_status, bool apps_status){}

    //Pdu Screen

    /*
    virtual void setPduPcStatusText(bool status) {}
    virtual void setPduFanStatusText(bool status) {}
    virtual void setPduPumpStatusText(bool status) {}
    virtual void setPduInverterStatusText(bool status) {}
    virtual void setPduFboxStatusText(bool status) {}
    virtual void setPduSdcStatusText(bool status) {}
    virtual void setPduDashStatusText(bool status) {}
    virtual void setPduTsalStatusText(bool status) {}
    virtual void setPduRboxStatusText(bool status) {}
    virtual void setPduAirStatusText(bool status) {}
    */
    virtual void setPduPcCurrent(uint32_t current) {}
    virtual void setPduPumpCurrent(uint32_t current) {}
    virtual void setPduFanCurrent(uint32_t current) {}
    virtual void setPduInverterCurrent(uint32_t current) {}
    virtual void setPduFboxCurrent(uint32_t current) {}
    virtual void setPduSdcCurrent(uint32_t current) {}
    virtual void setPduTotalCurrent(uint32_t current) {}



    //DataLogger Screen
    virtual void setTriggerVoltage(bool status) {}
    virtual void setTriggerCurrent(bool status) {}
    virtual void setLogStatus(bool status) {}
    virtual void setCurrent(uint16_t current) {}
    virtual void setVoltage(uint16_t voltage) {}
    virtual void setPower(uint16_t voltage, uint16_t current) {}


  protected:
    Model* model; ///< Associated model.
};

#endif  // MODELLISTENER_HPP
