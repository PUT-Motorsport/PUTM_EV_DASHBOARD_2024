#include <gui/notificationscreen_screen/NotificationScreenView.hpp>
#include <algorithm>
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "portable.h"
#include "task.h"


uint32_t lastToggleTime;
ScreenStatus_TypeDef previousScreen; //Save previous screen

NotificationScreenView::NotificationScreenView() {}

void NotificationScreenView::setupScreen() { NotificationScreenViewBase::setupScreen(); }

void NotificationScreenView::tearDownScreen() { NotificationScreenViewBase::tearDownScreen(); }

void NotificationScreenView::updateCheckErrors(bool bspd, bool apps)
{
    // Combine BSPD and APPS into a single error condition
    bool errorActive = bspd || apps;

    // If an error is active and Notification Screen is not already shown, open it
    if (errorActive && !screenStatus.NotificationScreen) {
        // Save which screen was previously active
        previousScreen.RaceScreen = screenStatus.RaceScreen;
        previousScreen.MainScreen = screenStatus.MainScreen;

        // Switch to Notification Screen without transition
        screenStatus.NotificationScreen = true;
        static_cast<FrontendApplication*>(Application::getInstance())
            ->gotoNotificationScreenScreenNoTransition();
    }

    // If no errors are active and Notification Screen is shown, return to previous screen
    if (!errorActive && screenStatus.NotificationScreen) {
        screenStatus.NotificationScreen = false;

        // Return to the screen that was active before Notification Screen
        if (previousScreen.RaceScreen) {
            static_cast<FrontendApplication*>(Application::getInstance())
                ->gotoRaceScreenScreenNoTransition();
        } else if (previousScreen.MainScreen) {
            static_cast<FrontendApplication*>(Application::getInstance())
                ->gotoMainScreenScreenNoTransition();
        }
    }

    // Update UI elements based on error states
    if (screenStatus.NotificationScreen) {
        if (bspd && apps) {
            bspdErrorText.setVisible(false);
            bspdErrorText.invalidate();
            appsErrorText.setVisible(false);
            appsErrorText.invalidate();
            stopCarText.setVisible(true);
            stopCarText.invalidate();
        } else if (bspd) {
            bspdErrorText.setVisible(true);
            bspdErrorText.invalidate();
            appsErrorText.setVisible(false);
            appsErrorText.invalidate();
            stopCarText.setVisible(false);
            stopCarText.invalidate();
        } else if (apps) {
            bspdErrorText.setVisible(false);
            bspdErrorText.invalidate();
            appsErrorText.setVisible(true);
            appsErrorText.invalidate();
            stopCarText.setVisible(false);
            stopCarText.invalidate();
        } else {
            bspdErrorText.setVisible(false);
            bspdErrorText.invalidate();
            appsErrorText.setVisible(false);
            appsErrorText.invalidate();
            stopCarText.setVisible(false);
            stopCarText.invalidate();
        }
    }

    // Handle CS button hold logic for dismissing Notification Screen
    static uint32_t csHoldStart = 0;   /**< Timestamp when CS press was first detected */
    static bool     csPrevState = false; /**< Previous scan state of CS button */

    bool     csCurrState = interfaceData.cs_button;  // Current state of CS button
    uint32_t nowMs       = xTaskGetTickCount() * portTICK_PERIOD_MS;  // Current time in ms

    if (screenStatus.NotificationScreen) {
        // Detect rising edge of CS press
        if (csCurrState && !csPrevState) {
            csHoldStart = nowMs;
        }

        // If CS is held for 2000 ms or more, dismiss Notification Screen
        if (csCurrState && (nowMs - csHoldStart >= 2000)) {
            screenStatus.NotificationScreen = false;

            // Return to the screen that was active before Notification Screen
            if (previousScreen.RaceScreen) {
                static_cast<FrontendApplication*>(Application::getInstance())
                    ->gotoRaceScreenScreenNoTransition();
            } else if (previousScreen.MainScreen) {
                static_cast<FrontendApplication*>(Application::getInstance())
                    ->gotoMainScreenScreenNoTransition();
            }

            // Reset hold timer for next use
            csHoldStart = 0;
        }

        // Reset hold timer when CS is released
        if (!csCurrState) {
            csHoldStart = 0;
        }
    }

    // Store current CS state for next call comparison
    csPrevState = csCurrState;

}


