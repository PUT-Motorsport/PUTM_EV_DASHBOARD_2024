#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>

#include <touchgfx/hal/HAL.hpp>
#include "stm32u5xx_hal.h"

MainScreenPresenter::MainScreenPresenter(MainScreenView& v) : view(v) {}

void MainScreenPresenter::activate(){ screenStatus.MainScreen = true; }

void MainScreenPresenter::deactivate(){	screenStatus.MainScreen = false; }

void MainScreenPresenter::setClock(uint32_t time) { view.updateClock(time); }

void MainScreenPresenter::setConnection(bool status) { view.updateConnection(status); }

void MainScreenPresenter::setWarning(bool status) { view.updateWarning(status); }

void MainScreenPresenter::setRadio(bool status) { view.updateRadio(status); }

void MainScreenPresenter::setReadyToDrive(bool status) { view.updateReadyToDrive(status); }

void MainScreenPresenter::setInvertersReady(bool status) { view.updateInvertersReady(status); }

void MainScreenPresenter::setBatteryLvTemperature(uint8_t temperature) { view.updateBatteryLvTemperature(temperature); }

void MainScreenPresenter::setInverterTemperature(uint8_t temperature) { view.updateInverterTemperature(temperature); }

void MainScreenPresenter:: setMotorFrontLeftTemperature(uint8_t temperature) { view.updateMotorFrontLeftTemperature(temperature); }

void MainScreenPresenter:: setMotorFrontRightTemperature(uint8_t temperature) { view.updateMotorFrontRightTemperature(temperature);}

void MainScreenPresenter:: setMotorRearLeftTemperature(uint8_t temperature) { view.updateMotorRearLeftTemperature(temperature); }

void MainScreenPresenter:: setMotorRearRightTemperature(uint8_t temperature) { view.updateMotorRearRightTemperature(temperature); }

void MainScreenPresenter::setOilTemperature(uint8_t temperature) { view.updateOilTemperature(temperature); }

void MainScreenPresenter::setOilPressure(uint8_t pressure) { view.updateOilPressure(pressure); }

void MainScreenPresenter::setCoolantTemperature(uint8_t temperature) { view.updateCoolantTemperature(temperature); }

void MainScreenPresenter::setCoolantPressure(uint8_t pressure) { view.updateCoolantPressure(pressure); }

void MainScreenPresenter::setRpm(uint16_t rpm) { view.updateRpm(rpm); }

void MainScreenPresenter::setCurrentLap(uint32_t time) { view.updateCurrentLap(time); }

void MainScreenPresenter::setLastLap(uint32_t time) { view.updateLastLap(time); }

void MainScreenPresenter::setBestLap(uint32_t time) { view.updateBestLap(time); }

void MainScreenPresenter::setSDC(SafetyData_TypeDef SafetyData) {view.updateSDC(&SafetyData);}

void MainScreenPresenter::toggleElements() { view.toggleWarning(); }

void MainScreenPresenter::switchScreenMR()
{
	if (screenStatus.MainScreen && interfaceData.cs_button == 1)
	{
        static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
        screenStatus.MainScreen = false;
	}
}

