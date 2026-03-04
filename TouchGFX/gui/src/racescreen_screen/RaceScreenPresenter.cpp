#include <gui/racescreen_screen/RaceScreenView.hpp>
#include <gui/racescreen_screen/RaceScreenPresenter.hpp>

#include <touchgfx/hal/HAL.hpp>
#include "stm32u5xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"

uint32_t lastScreenSwitchRPTime = 0; ///< Global variable storing the time of the last screen switch (in milliseconds)

RaceScreenPresenter::RaceScreenPresenter(RaceScreenView& v): view(v){}

void RaceScreenPresenter::activate(){screenStatus.RaceScreen = true;}

void RaceScreenPresenter::deactivate(){screenStatus.RaceScreen = false;}

void RaceScreenPresenter::setReadyToDrive(bool status) {view.updateReadyToDrive(status);}

void RaceScreenPresenter::setDrsStatus(bool status) {view.updateDrsStatus(status);}

void RaceScreenPresenter::setSocLv(uint8_t soc) {view.updateSocLv(soc);}

void RaceScreenPresenter::setSocHv(uint8_t soc) {view.updateSocHv(soc);}

void RaceScreenPresenter::setBatteryHVTemperature(uint8_t temperature) {view.updateBatteryHVTemperature(temperature);}

void RaceScreenPresenter::setInverterTemperature(uint8_t inv_FL_temperature,
												 uint8_t inv_FR_temperature,
												 uint8_t inv_RL_temperature,
												 uint8_t inv_RR_temperature) { view.updateInverterTemperature(inv_FL_temperature,
				 	 	 	 	 	 	 	 	 	 	 	 	 	  	  	  	  	  	  	  	  	  	  	  inv_FR_temperature,
																											  inv_RL_temperature,
																											  inv_RR_temperature); }

void RaceScreenPresenter::setMotorTemp(uint8_t temperatureMotorFL,
									   uint8_t temperatureMotorFR,
									   uint8_t temperatureMotorRL,
									   uint8_t temperatureMotorRR) {view.updateMotorTemp(temperatureMotorFL,
											   	   	   	   	   	   	   	   	   	   	   	 temperatureMotorFR,
																						 temperatureMotorRL,
																						 temperatureMotorRR);}

void RaceScreenPresenter::setPace(int16_t pace) {view.updatePace(pace);}

void RaceScreenPresenter::setLap(uint8_t value){view.updateLap(value);}

void RaceScreenPresenter::setBestLap(uint32_t time){view.updateBestLap(time);}


void RaceScreenPresenter::switchScreenRace2Pdu()
{
    // Statyczna zmienna przechowująca poprzedni stan przycisku
    static uint8_t previousButtonState = 0;
    // Odczytujemy bieżący stan przycisku
    uint8_t currentButtonState = interfaceData.cs_button;

    // Pobieramy aktualny czas (w ms)
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    // Zapobiegamy przełączaniu ekranów, jeśli od ostatniego przełączenia minęło mniej niż 1000 ms
    if ((currentTime - lastScreenSwitchRPTime) < 1000)
    {
        previousButtonState = currentButtonState; // aktualizujemy stan
        return;
    }

    // Wykrywanie opadającego zbocza: poprzedni stan był 1, a bieżący jest 0
    if (screenStatus.RaceScreen && (previousButtonState == 1) && (currentButtonState == 0))
    {
        static_cast<FrontendApplication*>(Application::getInstance())->gotoPduScreenScreenNoTransition();
        screenStatus.RaceScreen = false;
        lastScreenSwitchRPTime = currentTime;
    }

    // Zaktualizuj poprzedni stan przycisku do bieżącego stanu
    previousButtonState = currentButtonState;
}
