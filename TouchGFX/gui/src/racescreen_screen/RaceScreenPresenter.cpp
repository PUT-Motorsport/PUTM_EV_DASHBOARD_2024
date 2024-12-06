#include <gui/racescreen_screen/RaceScreenView.hpp>
#include <gui/racescreen_screen/RaceScreenPresenter.hpp>

#include <touchgfx/hal/HAL.hpp>
#include "stm32u5xx_hal.h"

RaceScreenPresenter::RaceScreenPresenter(RaceScreenView& v): view(v){}

void RaceScreenPresenter::activate(){screenStatus.RaceScreen = true;}

void RaceScreenPresenter::deactivate(){screenStatus.RaceScreen = false;}

void RaceScreenPresenter::setReadyToDrive(bool status) {view.updateReadyToDrive(status);}

void RaceScreenPresenter::setInvertersReady(bool status) {view.updateInvertersReady(status);}

void RaceScreenPresenter::setSocLv(uint8_t soc) {view.updateSocLv(soc);}

void RaceScreenPresenter::setSocHv(uint8_t soc) {view.updateSocHv(soc);}

void RaceScreenPresenter::setBatteryHVTemperature(uint8_t temperature) {view.updateBatteryHVTemperature(temperature);}

void RaceScreenPresenter::setInverterTemperature(uint8_t temperature) {view.updateInverterTemperature(temperature);}

void RaceScreenPresenter::setPace(int32_t pace) {view.updatePace(pace);}

void RaceScreenPresenter::setRange(uint16_t range) {view.updateRange(range);}

void RaceScreenPresenter::setMotorTemp(uint8_t temperatureMotorFL,
									   uint8_t temperatureMotorFR,
									   uint8_t temperatureMotorRL,
									   uint8_t temperatureMotorRR) {view.updateMotorTemp(temperatureMotorFL,
											   	   	   	   	   	   	   	   	   	   	   	 temperatureMotorFR,
																						 temperatureMotorRL,
																						 temperatureMotorRR);}

void RaceScreenPresenter::setLap(uint8_t value){view.updateLap(value);}

static uint32_t lastScreenSwitchTime = 0;
const uint32_t DEBOUNCE_TIME_MS = 500;

void RaceScreenPresenter::switchScreenRM()
{
	uint32_t currentTime = HAL_GetTick();

	if (screenStatus.RaceScreen &&
		interfaceData.cs_button == 1 &&
		(currentTime - lastScreenSwitchTime > DEBOUNCE_TIME_MS))
	{
		lastScreenSwitchTime = currentTime;
		static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
		screenStatus.RaceScreen = false;
	}
}
