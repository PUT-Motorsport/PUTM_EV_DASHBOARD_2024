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

void NotificationScreenView::updateCheckErrors(bool bspd,
		   	   	   	   	   	   	   	   	   	   uint8_t inv_FL_temperature,
											   uint8_t inv_FR_temperature,
											   uint8_t inv_RL_temperature,
											   uint8_t inv_RR_temperature,
											   uint8_t lv_temp,
											   uint8_t hv_temp,
											   uint8_t lv_soc,
											   uint8_t hv_soc,
											   uint8_t motor_fl_temp,
											   uint8_t motor_fr_temp,
											   uint8_t motor_rl_temp,
											   uint8_t motor_rr_temp)
{
//    int errorCount = 0; // Danger counter
//    const char* lastErrorMessage = nullptr; // Storing the last danger message
//
//    // Helper function for danger handling
//    auto checkError = [&](bool condition, const char* errorMessage) {
//        if (condition) {
//            errorCount++;
//            lastErrorMessage = errorMessage;
//        }
//    };
//
//    uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});
//
//    uint8_t motor_temp_highest = std::max({motor_fl_temp, motor_fr_temp, motor_rl_temp, motor_rr_temp});
//
//
//    // Check all errors
//    checkError(1 == bspd, "BSPD");
//    checkError(HV_CRIT_TEMP <= hv_temp, "HV TEMP");
//    checkError(HV_CRIT_SOC >= hv_soc, "HV SOC");
//    checkError(LV_CRIT_TEMP <= lv_temp, "LV TEMP");
//    checkError(LV_CRIT_SOC >= lv_soc, "LV SOC");
//    checkError(INV_CRIT_TEMP <= inv_temp_highest, "INV TEMP");
//    checkError(MOTOR_CRIT_TEMP <= motor_temp_highest, "MOTOR TEMP");
//
//    if (errorCount > 2)
//    {
//    	//check previous display
//    	if(1 == screenStatus.RaceScreen)
//    	{
//    		previousScreen.RaceScreen = 1;
//    		previousScreen.MainScreen = 0;
//    	}
//    	else if(1 == screenStatus.MainScreen)
//    	{
//    		previousScreen.RaceScreen = 0;
//    		previousScreen.MainScreen = 1;
//    	}
//
//        lastErrorMessage = "STOP CAR";
//        // Display danger
//        static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
//        Unicode::snprintf(notificationTextBuffer, NOTIFICATIONTEXT_SIZE, "%s", lastErrorMessage);
//        notificationText.setVisible(true);
//        notificationText.invalidate();
//    }
//
//    if (errorCount > 0) {
//            if (!screenStatus.NotificationScreen) {
//                // Save the previous screen state
//                previousScreen.RaceScreen = screenStatus.RaceScreen;
//                previousScreen.MainScreen = screenStatus.MainScreen;
//
//                // Display the Notification Screen
//                screenStatus.NotificationScreen = true;
//                lastToggleTime = xTaskGetTickCount() * portTICK_PERIOD_MS; // Record the current time
//
//                static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
//                Unicode::snprintf(notificationTextBuffer, NOTIFICATIONTEXT_SIZE, "%s", lastErrorMessage);
//                notificationText.setVisible(true);
//                notificationText.invalidate();
//            } else {
//                // Check if it's time to toggle the screen
//                if ((xTaskGetTickCount() * portTICK_PERIOD_MS) - lastToggleTime >= 1000) { // 1000 ms = 1 second
//                    lastToggleTime = xTaskGetTickCount() * portTICK_PERIOD_MS; // Update the time
//                    toggleScreen();
//                }
//            }
//        } else {
//            if (screenStatus.NotificationScreen) {
//                // Stop notification and return to the previous screen
//            	screenStatus.NotificationScreen = false;
//                if (previousScreen.RaceScreen) {
//                    static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
//                } else if (previousScreen.MainScreen) {
//                    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
//                }
//            }
//        }

	int errorCount = 0;

	// Determine the highest temperatures for inverters and motors
	uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});
	uint8_t motor_temp_highest = std::max({motor_fl_temp, motor_fr_temp, motor_rl_temp, motor_rr_temp});

	// Set flags for individual errors
	bool bspdError      = (1 == bspd);
	bool hvTempError    = (HV_CRIT_TEMP <= hv_temp);
	bool hvSocError     = (HV_CRIT_SOC >= hv_soc);
	bool lvTempError    = (LV_CRIT_TEMP <= lv_temp);
	bool lvSocError     = (LV_CRIT_SOC >= lv_soc);
	bool invTempError   = (INV_CRIT_TEMP <= inv_temp_highest);
	bool motorTempError = (MOTOR_CRIT_TEMP <= motor_temp_highest);

	// Count detected errors
	if(bspdError)      errorCount++;
	if(hvTempError)    errorCount++;
	if(hvSocError)     errorCount++;
	if(lvTempError)    errorCount++;
	if(lvSocError)     errorCount++;
	if(invTempError)   errorCount++;
	if(motorTempError) errorCount++;

	// Prepare an array of pointers to error messages and their corresponding conditions
	// Priority is set as follows: MOTOR TEMP > INV TEMP > LV SOC > LV TEMP > HV SOC > HV TEMP > BSPD.
	TextAreaWithOneWildcard* errorTexts[] = {
	    &motorTempErrorText,  // priority 0
	    &invErrorText,        // priority 1
	    &lvSocErrorText,      // priority 2
	    &lvTempErrorText,     // priority 3
	    &hvSocErrorText,      // priority 4
	    &hvTempErrorText,     // priority 5
	    &bspdErrorText        // priority 6
	};

	const bool errorConditions[] = {
	    motorTempError,
	    invTempError,
	    lvSocError,
	    lvTempError,
	    hvSocError,
	    hvTempError,
	    bspdError
	};
	const size_t numErrors = sizeof(errorTexts) / sizeof(errorTexts[0]);

	// First, hide all error messages using a loop
	for (size_t i = 0; i < numErrors; ++i)
	{
	    errorTexts[i]->setVisible(false);
	    errorTexts[i]->invalidate();
	}
	// Also hide the "STOP CAR" message
	stopCarText.setVisible(false);
	stopCarText.invalidate();

	// If two or more errors are detected, show only the "STOP CAR" message
	if (errorCount >= 2)
	{
	    stopCarText.setVisible(true);
	    stopCarText.invalidate();
	}
	// If one error is detected
	else if (errorCount > 0 || errorCount < 2)
	{
	    // Select the first active error message according to the defined priority
	    for (size_t i = 0; i < numErrors; ++i)
	    {
	        if (errorConditions[i])
	        {
	            errorTexts[i]->setVisible(true);
	            errorTexts[i]->invalidate();
	            break;
	        }
	    }

	    // Update the notification screen
	    if (!screenStatus.NotificationScreen)
	    {
	        previousScreen.RaceScreen = screenStatus.RaceScreen;
	        previousScreen.MainScreen = screenStatus.MainScreen;
	        screenStatus.NotificationScreen = true;
	        lastToggleTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
	        static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
	    }

	    // Toggle the screen every second if the notification screen is already visible
	    if ((xTaskGetTickCount() * portTICK_PERIOD_MS) - lastToggleTime >= 1000)
	    {
	        lastToggleTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
	        toggleScreen();
	    }
	}
	// If no errors are detected, hide the notification screen and all error messages
	else
	{
	    if (screenStatus.NotificationScreen)
	    {
	        screenStatus.NotificationScreen = false;
	        // Return to the previous screen based on the saved state
	        if (previousScreen.RaceScreen)
	        {
	            static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
	        }
	        else if (previousScreen.MainScreen)
	        {
	            static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
	        }
	    }
	}


}


void NotificationScreenView::toggleScreen()
{
    if (screenStatus.NotificationScreen) {
        // Go back to the previous screen
        if (previousScreen.RaceScreen) {
            static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
        } else if (previousScreen.MainScreen) {
            static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
        }
    } else {
        // Display the Notification Screen
        static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
    }
}


