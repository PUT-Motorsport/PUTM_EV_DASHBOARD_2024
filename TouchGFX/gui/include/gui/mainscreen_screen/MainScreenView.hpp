#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <array>

class MainScreenView : public MainScreenViewBase {
  public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateClock(uint32_t time);
    void updateConnection(bool status);
    void updateWarning(bool status);
    void updateRadio(bool status);
    void updateReadyToDrive(bool status);
    void updateInvertersStatus(bool inv_ready,
    						  bool inv_FL_status,
    						  bool inv_FR_status,
							  bool inv_RL_status,
							  bool inv_RR_status,
							  bool inv_FL_error,
							  bool inv_FR_error,
							  bool inv_RL_error,
							  bool inv_RR_error);
    void updateBatteryLvTemperature(uint8_t temperature);
    void updateBatteryHvTemperature(uint8_t temperature);
    void updateInverterTemperature(uint8_t inv_FL_temperature,
								   uint8_t inv_FR_temperature,
								   uint8_t inv_RL_temperature,
								   uint8_t inv_RR_temperature);
    void updateMotorFrontLeftTemperature(uint8_t temperature);
    void updateMotorFrontRightTemperature(uint8_t temperature);
    void updateMotorRearLeftTemperature(uint8_t temperature);
    void updateMotorRearRightTemperature(uint8_t temperature);
    void updateOilTemperature(uint8_t temperature);
    void updateRearBrakePressure(uint16_t pressure);
    void updateCoolantTemperature(uint8_t temperature);
    void updateFrontBrakePressure(uint16_t pressure);
    void updateRpm(uint16_t rpm);
    void updateCurrentLap(uint32_t time);
    void updateLastLap(uint32_t time);
    void updateBestLap(uint32_t time);
    void updateRtdButtonPressed(bool status);
    void updateTsaButtonPressed(bool status);

    void toggleWarning();

    //Safety display
    void displayError(int error_idx);
    void updateSDC(SafetyData_TypeDef status);

  protected:
  private:
    unsigned int m_time;
    bool m_warning;
};

#endif  // MAINSCREENVIEW_HPP
