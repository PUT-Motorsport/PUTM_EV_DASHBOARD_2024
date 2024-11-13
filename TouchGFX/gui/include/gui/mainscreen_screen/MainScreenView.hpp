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
    void updateBatteryHvTemperature(uint8_t temperature);
    void updateInverterTemperature(uint8_t temperature);
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

//    void updateSafetyFrontboxLeftKill(bool status);
//    void updateSafetyFrontboxRightKill(bool status);
//    void updateSafetyFrontboxDriverKill(bool status);
//    void updateSafetyFrontboxInertia(bool status);
//    void updateSafetyFrontboxBSPD(bool status);
//    void updateSafetyFrontboxOvertravel(bool status);
//    void updateSafetyFrontboxRightWheel(bool status);
//    void updateSafetyFrontboxIsBraking(bool status);
//
//    void updateSafetyRearBoxRuf1(bool status);
//    void updateSafetyRearBoxRuf2(bool status);
//    void updateSafetyRearBoxAsms(bool status);
//    void updateSafetyRearBoxFw(bool status);
//    void updateSafetyRearBoxHv(bool status);
//    void updateSafetyRearBoxRes(bool status);
//    void updateSafetyRearBoxHvd(bool status);
//    void updateSafetyRearBoxInv(bool status);
//    void updateSafetyRearBoxWheelFl(bool status);
//    void updateSafetyRearBoxWheelFr(bool status);
//    void updateSafetyRearBoxWheelRl(bool status);
//    void updateSafetyRearBoxWheelRr(bool status);

    void setSafetyStatus(const char* text, uint8_t red, uint8_t green, uint8_t blue);
    void updateSDC(SafetyData_TypeDef *status);

    void toggleWarning();

  protected:
  private:
    unsigned int m_time;
    bool m_warning;
};

#endif  // MAINSCREENVIEW_HPP
