#include <gui/notificationscreen_screen/NotificationScreenView.hpp>
#include <algorithm>
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "portable.h"
#include "task.h"

//TODO: Uzupełnić realnymi wartościami
#define HV_CRIT_TEMP 45
#define HV_CRIT_SOC 80
#define LV_CRIT_TEMP 35
#define LV_CRIT_SOC 10
#define MOTOR_CRIT_TEMP 80
#define INV_CRIT_TEMP 40

uint32_t lastToggleTime;
ScreenStatus_TypeDef previousScreen; //Save previous screen

NotificationScreenView::NotificationScreenView() {}

void NotificationScreenView::setupScreen() { NotificationScreenViewBase::setupScreen(); }

void NotificationScreenView::tearDownScreen() { NotificationScreenViewBase::tearDownScreen(); }

void NotificationScreenView::updateCheckErrors(bool bspd)
{
    // 1) tylko BSPD uruchamia Notification Screen:
    bool bspdError = (bspd == 1);
    if (bspdError && !screenStatus.NotificationScreen)
    {
        // zapamiętaj poprzedni ekran
        previousScreen.RaceScreen = screenStatus.RaceScreen;
        previousScreen.MainScreen = screenStatus.MainScreen;
        // wejdź na Notification Screen
        screenStatus.NotificationScreen = true;
        static_cast<FrontendApplication*>(Application::getInstance())
            ->gotoNotificationScreenScreenNoTransition();
    }

    // 2) logika zamykania przy przytrzymaniu CS ≥ 2 s:
    static uint32_t csHoldStart   = 0;
    static bool     csPrevState   = false;
    bool             csCurrState  = interfaceData.cs_button;      // global z interface_task.cpp :contentReference[oaicite:4]{index=4}:contentReference[oaicite:5]{index=5}
    uint32_t         nowMs        = xTaskGetTickCount() * portTICK_PERIOD_MS;

    if (screenStatus.NotificationScreen)
    {
        // wykrycie zbocza narastającego
        if (csCurrState && !csPrevState)
        {
            csHoldStart = nowMs;
        }
        // jeżeli trzymamy CS ≥ 2000 ms → zamknij Notification
        if (csCurrState && (nowMs - csHoldStart >= 2000))
        {
            screenStatus.NotificationScreen = false;
            // powrót do wcześniejszego ekranu
            if (previousScreen.RaceScreen)
            {
                static_cast<FrontendApplication*>(Application::getInstance())
                    ->gotoRaceScreenScreenNoTransition();
            }
            else if (previousScreen.MainScreen)
            {
                static_cast<FrontendApplication*>(Application::getInstance())
                    ->gotoMainScreenScreenNoTransition();
            }
            // reset dla kolejnego użycia
            csHoldStart = 0;
        }
        // zerowanie przy puszczeniu
        if (!csCurrState)
        {
            csHoldStart = 0;
        }
    }
    csPrevState = csCurrState;
}


