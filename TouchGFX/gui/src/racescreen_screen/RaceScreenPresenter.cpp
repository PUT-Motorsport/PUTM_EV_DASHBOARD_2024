#include <gui/racescreen_screen/RaceScreenView.hpp>
#include <gui/racescreen_screen/RaceScreenPresenter.hpp>

#include <touchgfx/hal/HAL.hpp>

RaceScreenPresenter::RaceScreenPresenter(RaceScreenView& v)
    : view(v)
{

}

void RaceScreenPresenter::activate(){}

void RaceScreenPresenter::deactivate(){}

void RaceScreenPresenter::setReadyToDrive(bool status) {view.updateReadyToDrive(status);}

void RaceScreenPresenter::setInvertersReady(bool status) {view.updateInvertersReady(status);}

void RaceScreenPresenter::setSocLv(uint8_t soc) {view.updateSocLv(soc);}

void RaceScreenPresenter::setSocHv(uint8_t soc) {view.updateSocHv(soc);}

void RaceScreenPresenter::setTempHv(uint8_t temperature) {view.updateTempHv(temperature);}

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

void RaceScreenPresenter::switchScreenRM()
{
	if(1 == interfaceData.cs_button)
	{
		static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenCoverTransitionSouth();
		interfaceData.cs_button = false;
	}
}
