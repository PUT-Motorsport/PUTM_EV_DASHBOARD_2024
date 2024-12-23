#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>

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
    void updateOilPressure(uint8_t pressure);
    void updateCoolantTemperature(uint8_t temperature);
    void updateCoolantPressure(uint8_t pressure);
    void updateRpm(uint16_t rpm);
    void updateCurrentLap(uint32_t time);
    void updateLastLap(uint32_t time);
    void updateBestLap(uint32_t time);
    //Safety display
    void updateSafetyFrontbox(bool status);
    void updateSafetyRearBox(bool status);

    void toggleWarning();
    void setSafetyStatus(const char* text, uint8_t red, uint8_t green, uint8_t blue);
    void updateSDC(SafetyData_TypeDef *status);

  protected:
  private:
    unsigned int m_time;
    bool m_warning;
};

#endif  // MAINSCREENVIEW_HPP
