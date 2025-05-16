/**
 * @file MainScreenPresenter.hpp
 * @brief Declaration of the MainScreenPresenter class.
 *
 * The MainScreenPresenter class handles the logic for the main screen,
 * communicating with the Model and updating the view accordingly.
 */

#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainScreenView;


/**
 * @brief Presenter for the main screen.
 */
class MainScreenPresenter : public touchgfx::Presenter, public ModelListener {
  public:
    MainScreenPresenter(MainScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainScreenPresenter() {}

//    virtual void tick();


    // Methods to set the view
    void setClock(uint32_t time);
    void setConnection(bool status);
    void setWarning(bool status);
    void setRadio(bool status);
    void setReadyToDrive(bool status);
    void setInvertersStatus(bool inv_ready,
    						bool inv_FL_status,
    					    bool inv_FR_status,
							bool inv_RL_status,
							bool inv_RR_status,
							bool inv_FL_error,
							bool inv_FR_error,
							bool inv_RL_error,
							bool inv_RR_error);
    void setBatteryHvTemperature(uint8_t temperature);
    void setBatteryLVTemperature(uint8_t temperature);
    void setMotorFrontLeftTemperature(uint8_t temperature);
    void setMotorFrontRightTemperature(uint8_t temperature);
    void setMotorRearLeftTemperature(uint8_t temperature);
    void setMotorRearRightTemperature(uint8_t temperature);
    void setOilTemperature(uint8_t temperature);
    void setFrontBrakePressure(uint16_t pressure);
    void setCoolantTemperature(uint8_t temperature);
    void setRearBrakePressure(uint16_t pressure);
//    void setRpm(uint16_t rpm);
    void setCurrentLap(uint32_t time);
    void setLastLap(uint32_t time);
    void setBestLap(uint32_t time);
    void setSDC(SafetyData_TypeDef status);
    void setInverterTemperature(uint8_t inv_FL_temperature,
       							uint8_t inv_FR_temperature,
   								uint8_t inv_RL_temperature,
   								uint8_t inv_RR_temperature);
    void setPduPcStatus(uint8_t status);
    void setPduFanStatus(uint8_t status);
    void setPduPumpStatus(uint8_t status);
    void setPduInverterStatus(uint8_t status);
    void setPduFboxStatus(uint8_t status);
    void setPduSdcStatus(uint8_t status);
    void setPduDashStatus(uint8_t status);
    void setPduTsalStatus(uint8_t status);
    void setPduRboxStatus(uint8_t status);
    void setPduAirStatus(uint8_t status);
    void setRtdButtonPressed(bool status);
    void setTsaButtonPressed(bool status);

    /**
     * @brief Switches from the main screen to the race screen.
     */
    void switchScreenMR();


    /**
     * @brief Toggles warning elements.
     */
    void toggleElements();

  private:
    MainScreenPresenter();

    MainScreenView& view; ///< Reference to the main screen view.
};

#endif  // MAINSCREENPRESENTER_HPP
