#include <gui/racescreen_screen/RaceScreenView.hpp>

#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#include <algorithm>

#define RANGE_MIN 5
#define BATTERY_LV_SOC_MIN 25
#define BATTERY_LV_SOC_MID 50
#define BATTERY_LV_SOC_MAX 85
#define BATTERY_HV_SOC_MIN 30
#define BATTERY_HV_SOC_MID 60
#define BATTERY_HV_SOC_MAX 85
#define MOTOR_TEMPERATURE_MIN 60
#define MOTOR_TEMPERATURE_MID 90
#define MOTOR_TEMPERATURE_MAX 110
#define BATTERY_HV_TEMPERATURE_MIN 30
#define BATTERY_HV_TEMPERATURE_MID 60
#define BATTERY_HV_TEMPERATURE_MAX 85
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

void RaceScreenView::updateReadyToDrive(bool status)
{
    if(status)
    {
        rtdText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
        rtdText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }
    rtdText.invalidate();
}

void RaceScreenView::updateInvertersReady(bool status)
{
    if(status)
    {
        invText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
        invText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }
    invText.invalidate();
}

void RaceScreenView::updateSocLv(uint8_t soc)
{
    Unicode::snprintf(HvSoCTextBuffer, HVSOCTEXT_SIZE, "%d", soc);
    LvSoCText.invalidate();

    if(soc < BATTERY_LV_SOC_MIN)
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(soc < BATTERY_LV_SOC_MAX && soc > BATTERY_LV_SOC_MID)
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    HvSoCText.setVisible(true);
    HvSoCText.invalidate();
}

void RaceScreenView::updateSocHv(uint8_t soc)
{
    Unicode::snprintf(HvSoCTextBuffer, HVSOCTEXT_SIZE, "%d", soc);
    HvSoCText.invalidate();

    if(soc < BATTERY_HV_SOC_MIN)
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(soc < BATTERY_HV_SOC_MAX && soc > BATTERY_HV_SOC_MID)
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    HvSoCText.setVisible(true);
    HvSoCText.invalidate();
}

void RaceScreenView::updateTempHv(uint8_t temperature)
{
    Unicode::snprintf(hvtemptextBuffer , HVTEMPTEXT_SIZE , "%d", temperature);

    if(temperature > BATTERY_HV_TEMPERATURE_MAX || temperature < BATTERY_HV_TEMPERATURE_MIN)
    {
    	hvtempimage.setBitmap(Bitmap(BITMAP_BATTERYLV_CRIT_ID));
        HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature < BATTERY_HV_TEMPERATURE_MAX  && temperature > BATTERY_HV_TEMPERATURE_MID)
    {
    	hvtempimage.setBitmap(Bitmap(BITMAP_BATTERYLV_WARN_ID));
        HvSoCText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	hvtempimage.setBitmap(Bitmap(BITMAP_BATTERYLV_ID));
        HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    hvtempimage.setVisible(true);
    HvSoCText.setVisible(true);
    hvtempimage.invalidate();
    HvSoCText.invalidate();
}

void RaceScreenView::updateInverterTemperature(uint8_t temperature)
{
    Unicode::snprintf(invtemptextBuffer, INVTEMPTEXT_SIZE, "%d", temperature);

    if(temperature > INVERTER_TEMPERATURE_MAX || temperature < INVERTER_TEMPERATURE_MIN)
    {
    	invtempimage.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
    	invtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature > INVERTER_TEMPERATURE_MID)
    {
    	invtempimage.setBitmap(Bitmap(BITMAP_INVERTER_WARN_ID));
        invtemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	invtempimage.setBitmap(Bitmap(BITMAP_INVERTER_ID));
        invtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    invtempimage.setVisible(true);
    invtemptext.setVisible(true);
    invtempimage.invalidate();
    invtemptext.invalidate();
}

void RaceScreenView::updatePace(int32_t pace)
{
    if(pace > 0)
    {
    	paceBackground.setBitmap(Bitmap(BITMAP_PACEREDBACKGROUND_ID));
    }
    else if(pace < 0)
    {
    	paceBackground.setBitmap(Bitmap(BITMAP_PACEGREENBACKGROUND_ID));
    }
    else
    {
    	paceBackground.setBitmap(Bitmap(BITMAP_PACEYELLOWBACKGROUND_ID));
    }

    paceBackground.invalidate();

    float seconds = static_cast<float>(pace) / 1000.0f;
    Unicode::snprintfFloat(paceTextBuffer, PACETEXT_SIZE, "%+#.3f", seconds);
    paceText.setVisible(true);
    paceText.invalidate();
}

void RaceScreenView::updateRange(uint16_t range)
{
 //TODO: opracowanie sposobu wyznaczanie realnej wartości
}

void RaceScreenView::updateMotorTemp(uint8_t temperatureMotorFL,
									 uint8_t temperatureMotorFR,
									 uint8_t temperatureMotorRL,
									 uint8_t temperatureMotorRR)
{
	uint8_t frontMotor = std::max(temperatureMotorFL, temperatureMotorFR);
	uint8_t rearMotor = std::max(temperatureMotorRL, temperatureMotorRR);

	uint8_t highestTemperature = std::max(frontMotor, rearMotor);

    Unicode::snprintf(motortemptextBuffer, MOTORTEMPTEXT_SIZE, "%d", highestTemperature);

    if(highestTemperature > MOTOR_TEMPERATURE_MAX || highestTemperature < MOTOR_TEMPERATURE_MIN)
    {
    	motortempimage.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
    	motortemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(highestTemperature > MOTOR_TEMPERATURE_MID)
    {
    	motortempimage.setBitmap(Bitmap(BITMAP_INVERTER_WARN_ID));
    	motortemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	motortempimage.setBitmap(Bitmap(BITMAP_INVERTER_ID));
    	motortemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    motortempimage.setVisible(true);
    motortemptext.setVisible(true);
    motortempimage.invalidate();
    motortemptext.invalidate();

}
