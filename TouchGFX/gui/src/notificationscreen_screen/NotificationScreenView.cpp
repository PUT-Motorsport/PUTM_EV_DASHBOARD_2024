#include <gui/notificationscreen_screen/NotificationScreenView.hpp>
#include <algorithm>

//TODO: Uzupełnić realnymi wartościami
#define HV_CRIT_TEMP 60
#define HV_CRIT_SOC 20
#define LV_CRIT_TEMP 35
#define LV_CRIT_SOC 15
#define MOTOR_CRIT_TEMP 95
#define INV_CRIT_TEMP 100

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
    int errorCount = 0; // Dnager counter
    const char* lastErrorMessage = nullptr; // Storing the last danger message
    ScreenStatus_TypeDef previousScreen; //Save previous screen

    // Helper function for danger handling
    auto checkError = [&](bool condition, const char* errorMessage) {
        if (condition) {
            errorCount++;
            lastErrorMessage = errorMessage;
        }
    };

    uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});

    uint8_t motor_temp_highest = std::max({motor_fl_temp, motor_fr_temp, motor_rl_temp, motor_rr_temp});


    // Check all errors
    checkError(1 == bspd, "BSPD");
    checkError(HV_CRIT_TEMP <= hv_temp, "HV TEMP");
    checkError(HV_CRIT_SOC >= hv_soc, "HV SOC");
    checkError(LV_CRIT_TEMP <= lv_temp, "LV TEMP");
    checkError(LV_CRIT_SOC >= lv_soc, "LV SOC");
    checkError(INV_CRIT_TEMP <= inv_temp_highest, "INV TEMP");
    checkError(MOTOR_CRIT_TEMP <= motor_temp_highest, "MOTOR TEMP");

    if (errorCount > 2)
    {
    	//check previous display
    	if(1 == screenStatus.RaceScreen)
    	{
    		previousScreen.RaceScreen = 1;
    		previousScreen.MainScreen = 0;
    	}
    	else if(1 == screenStatus.MainScreen)
    	{
    		previousScreen.RaceScreen = 0;
    		previousScreen.MainScreen = 1;
    	}

        lastErrorMessage = "STOP CAR";
        // Display danger
        static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
        Unicode::snprintf(notificationTextBuffer, NOTIFICATIONTEXT_SIZE, "%s", lastErrorMessage);
        notificationText.setVisible(true);
        notificationText.invalidate();
    }

    if (errorCount > 0)
    {
    	//check previous display
    	if(1 == screenStatus.RaceScreen)
    	{
    		previousScreen.RaceScreen = 1;
    		previousScreen.MainScreen = 0;
    	}
    	else if(1 == screenStatus.MainScreen)
    	{
    		previousScreen.RaceScreen = 0;
    		previousScreen.MainScreen = 1;
    	}

        // Display danger
        static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
        Unicode::snprintf(notificationTextBuffer, NOTIFICATIONTEXT_SIZE, "%s", lastErrorMessage);
        notificationText.setVisible(true);
        notificationText.invalidate();
    }
    else
    {
    	//check previous display
    	if(1 == previousScreen.RaceScreen)
    	{
    		static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
    	}
    	else if(1 == previousScreen.MainScreen)
    	{
    		static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
    	}
    }
}



