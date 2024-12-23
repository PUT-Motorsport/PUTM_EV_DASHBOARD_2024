#include <gui/notificationscreen_screen/NotificationScreenView.hpp>

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

void NotificationScreenView::updateCheckErrors()
{
//    int errorCount = 0; // Dnager counter
//    const char* lastErrorMessage = nullptr; // Storing the last danger message
//    ScreenStatus_TypeDef previousScreen; //Save previous screen
//
//    // Helper function for danger handling
//    auto checkError = [&](bool condition, const char* errorMessage) {
//        if (condition) {
//            errorCount++;
//            lastErrorMessage = errorMessage;
//        }
//    };
//
//    // Check all errors
//    checkError(m_sharedSafetyData.sense_bspd == 1, "BSPD");
//    checkError(HV_CRIT_TEMP <= m_sharedData.battery_hv_temperature, "HV TEMP");
//    checkError(HV_CRIT_SOC >= m_sharedData.soc_hv, "HV SOC");
//    checkError(LV_CRIT_TEMP <= m_sharedData.battery_lv_temperature, "LV TEMP");
//    checkError(LV_CRIT_SOC >= m_sharedData.soc_lv, "LV SOC");
//    checkError(INV_CRIT_TEMP <= m_sharedData.inverter_temperature, "INV TEMP");
//    checkError(MOTOR_CRIT_TEMP <= std::max({m_sharedData.motor_front_left_temperature,
//                                            m_sharedData.motor_front_right_temperature,
//                                            m_sharedData.motor_rear_left_temperature,
//                                            m_sharedData.motor_rear_right_temperature}), "MOTOR TEMP");
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
//    if (errorCount > 0)
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
//        // Display danger
//        static_cast<FrontendApplication*>(Application::getInstance())->gotoNotificationScreenScreenNoTransition();
//        Unicode::snprintf(notificationTextBuffer, NOTIFICATIONTEXT_SIZE, "%s", lastErrorMessage);
//        notificationText.setVisible(true);
//        notificationText.invalidate();
//    }
//    else
//    {
//    	//check previous display
//    	if(1 == previousScreen.RaceScreen)
//    	{
//    		static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
//    	}
//    	else if(1 == previousScreen.MainScreen)
//    	{
//    		static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenScreenNoTransition();
//    	}
//    }
}



