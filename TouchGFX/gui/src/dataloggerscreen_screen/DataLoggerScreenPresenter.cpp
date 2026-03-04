#include <gui/dataloggerscreen_screen/DataLoggerScreenView.hpp>
#include <gui/dataloggerscreen_screen/DataLoggerScreenPresenter.hpp>

extern "C" 
{
#include "stm32u5xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "data.h"
}

uint32_t lastScreenSwitchDLTime = 0; ///< Global variable storing the time of the last screen switch (in milliseconds)

DataLoggerScreenPresenter::DataLoggerScreenPresenter(DataLoggerScreenView& v)
    : view(v)
{

}

void DataLoggerScreenPresenter::activate()
{
    screenStatus.DataLoggerScreen = true;
}

void DataLoggerScreenPresenter::deactivate()
{
    screenStatus.DataLoggerScreen = false;
}

void DataLoggerScreenPresenter::setTriggerCurrent(bool status) {view.updateTriggerCurrent(status);}

void DataLoggerScreenPresenter::setTriggerVoltage(bool status) {view.updateTriggerVoltage(status);}

void DataLoggerScreenPresenter::setLogStatus(bool status) {view.updateLogStatus(status);}

void DataLoggerScreenPresenter::setCurrent(uint16_t current) {view.updateCurrent(current);}

void DataLoggerScreenPresenter::setVoltage(uint16_t voltage) {view.updateVoltage(voltage);}

void DataLoggerScreenPresenter::setPower(uint16_t voltage, uint16_t current) {view.updatePower(voltage, current);}

void DataLoggerScreenPresenter::switchScreenDataLog2Main()
{
    // Statyczna zmienna przechowująca poprzedni stan przycisku
    static uint8_t previousButtonState = 0;
    // Odczytujemy bieżący stan przycisku
    uint8_t currentButtonState = interfaceData.cs_button;

    // Pobieramy aktualny czas (w ms)
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    // Zapobiegamy przełączaniu ekranów, jeśli od ostatniego przełączenia minęło mniej niż 1000 ms
    if ((currentTime - lastScreenSwitchDLTime) < 1000)
    {
        previousButtonState = currentButtonState; // aktualizujemy stan
        return;
    }

    // Wykrywanie opadającego zbocza: poprzedni stan był 1, a bieżący jest 0
    if (screenStatus.DataLoggerScreen && (previousButtonState == 1) && (currentButtonState == 0))
    {
        static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
        screenStatus.DataLoggerScreen = false;
        lastScreenSwitchDLTime = currentTime;
    }

    // Zaktualizuj poprzedni stan przycisku do bieżącego stanu
    previousButtonState = currentButtonState;
}