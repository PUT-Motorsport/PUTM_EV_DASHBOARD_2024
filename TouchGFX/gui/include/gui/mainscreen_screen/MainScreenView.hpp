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
    void updateInvertersReady(bool status);
    void updateBatteryLvTemperature(uint8_t temperature);
    void updateInverterTemperature(uint8_t temperature);
    void updateMotorFrontLeftTemperature(uint8_t temperature);
    void updateMotorFrontRightTemperature(uint8_t temperature);
    void updateMotorRearLeftTemperature(uint8_t temperature);
    void updateMotorRearRightTemperature(uint8_t temperature);
    void updateOilTemperature(uint8_t temperature);
    void updateOilPressure(uint8_t pressure);
    void updateCoolantTemperature(uint8_t temperature);
    void updateCoolantPressure(uint8_t pressure);
    void updatePace(int32_t pace);
    void updateSpeed(uint8_t speed);
    void updateSoc(uint8_t soc);
    void updateRpm(uint16_t rpm);
    void updatePower(uint8_t power);
    void updateDistance(uint16_t distance);
    void updateRange(uint16_t range);
    void updateCurrentLap(uint32_t time);
    void updateLastLap(uint32_t time);
    void updateBestLap(uint32_t time);

    void toggleWarning();

  protected:
  private:
    unsigned int m_time;
    bool m_warning;
};

#endif  // MAINSCREENVIEW_HPP
