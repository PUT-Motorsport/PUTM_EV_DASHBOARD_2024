#include <gui/racescreen_screen/RaceScreenView.hpp>

#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#define RANGE_MIN 5
#define LV_SOC_MIN 25
#define LV_SOC_MID 50
#define LV_SOC_MAX 85
#define HV_SOC_MIN 30
#define HV_SOC_MID 60
#define HV_SOC_MAX 85
#define MOTOR_TEMPERATURE_MIN 60
#define MOTOR_TEMPERATURE_MID 90
#define MOTOR_TEMPERATURE_MAX 110
#define HV_TEMP_MIN 30
#define HV_TEMP_MID 60
#define HV_TEMP_MAX 85
#define INVERTER_TEMPERATURE_MIN 20
#define INVERTER_TEMPERATURE_MID 80
#define INVERTER_TEMPERATURE_MAX 100


RaceScreenView::RaceScreenView() {}

void RaceScreenView::setupScreen()
{
    RaceScreenViewBase::setupScreen();
}

void RaceScreenView::tearDownScreen()
{
    RaceScreenViewBase::tearDownScreen();
}

void RaceScreenView::updateReadyToDrive(bool status) {
    if(status) {
        rtdText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    } else {
        rtdText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }
    rtdText.invalidate();
}

void RaceScreenView::updateInvertersReady(bool status) {
    if(status) {
        invText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    } else {
        invText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }
    invText.invalidate();
}

void RaceScreenView::updateSocLv(uint8_t soc) {
//    Unicode::snprintf(batLvSoCTextBuffer, BATLVSOCTEXT_SIZE, "%d", soc);
//    batLvTempText.invalidate();
//
//    if(soc > BATTERY_LV_SOC_MAX || temperature < BATTERY_LV_SOC_MIN) {
//        batLvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
//    } else if(temperature > BATTERY_LV_SOC_MID) {
//        batLvSoCText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
//    } else {
//        batLvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
//    }
//    batLvSoCText.setVisible(true);
//    batLvSoCText.invalidate();
}

void RaceScreenView::updateSocHv(uint8_t soc) {

}

void RaceScreenView::updateTempHv(uint8_t temperature) {

}

void RaceScreenView::updateInverterTemperature(uint8_t temperature) {
//    Unicode::snprintf(invTempTextBuffer, INVTEMPTEXT_SIZE, "%d", temperature);
//    if(temperature > INVERTER_TEMPERATURE_MAX || temperature < INVERTER_TEMPERATURE_MIN) {
//        invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
//        invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
//    } else if(temperature > INVERTER_TEMPERATURE_MID) {
//        invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_WARN_ID));
//        invTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
//    } else {
//        invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_ID));
//        invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
//    }
//    invTempIcon.setVisible(true);
//    invTempText.setVisible(true);
//    invTempIcon.invalidate();
//    invTempText.invalidate();
}

void RaceScreenView::updatePace(int32_t pace) {
//    if(pace > 0) {
//        paceBackground.setBitmap(Bitmap(BITMAP_PACEREDBACKGROUND_ID));
//    } else if(pace < 0) {
//        paceBackground.setBitmap(Bitmap(BITMAP_PACEGREENBACKGROUND_ID));
//    } else {
//        paceBackground.setBitmap(Bitmap(BITMAP_PACEYELLOWBACKGROUND_ID));
//    }
//    paceBackground.invalidate();
//
//    float seconds = static_cast<float>(pace) / 1000.0f;
//    Unicode::snprintfFloat(paceTextBuffer, PACETEXT_SIZE, "%+#.3f", seconds);
//    paceText.setVisible(true);
//    paceText.invalidate();
}

void RaceScreenView::updateRange(uint16_t range) {

}

void RaceScreenView::updateMotorTemp(uint8_t temperatureMotorFL,
									 uint8_t temperatureMotorFR,
									 uint8_t temperatureMotorRL,
									 uint8_t temperatureMotorRR) {

}
