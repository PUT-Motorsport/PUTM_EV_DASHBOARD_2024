#include <gui/pduscreen_screen/PduScreenView.hpp>
#include <gui/pduscreen_screen/PduScreenPresenter.hpp>

#include <touchgfx/hal/HAL.hpp>
extern "C" 
{
#include "stm32u5xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "data.h"
}

uint32_t lastScreenSwitchPVTime = 0; ///< Global variable storing the time of the last screen switch (in milliseconds)

PduScreenPresenter::PduScreenPresenter(PduScreenView& v)
    : view(v)
{

}

void PduScreenPresenter::activate()
{
    screenStatus.PduScreen = true;
}

void PduScreenPresenter::deactivate()
{
    screenStatus.PduScreen = false;
}

void PduScreenPresenter::switchScreenPdu2Vp()
{
    // Statyczna zmienna przechowująca poprzedni stan przycisku
    static uint8_t previousButtonState = 0;
    // Odczytujemy bieżący stan przycisku
    uint8_t currentButtonState = interfaceData.cs_button;

    // Pobieramy aktualny czas (w ms)
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    // Zapobiegamy przełączaniu ekranów, jeśli od ostatniego przełączenia minęło mniej niż 1000 ms
    if ((currentTime - lastScreenSwitchPVTime) < 1000)
    {
        previousButtonState = currentButtonState; // aktualizujemy stan
        return;
    }

    // Wykrywanie opadającego zbocza: poprzedni stan był 1, a bieżący jest 0
    if (screenStatus.PduScreen && (previousButtonState == 1) && (currentButtonState == 0))
    {
        static_cast<FrontendApplication*>(Application::getInstance())->gotoVpSettingsScreenScreenNoTransition();
        screenStatus.PduScreen = false;
        lastScreenSwitchPVTime = currentTime;
    }

    // Zaktualizuj poprzedni stan przycisku do bieżącego stanu
    previousButtonState = currentButtonState;
}
