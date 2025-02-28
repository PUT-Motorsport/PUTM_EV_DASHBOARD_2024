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

void RaceScreenView::updateDrsStatus(bool status)
{
	if(status)
	{
		drsText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
	}
	else
	{
		drsText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
	}

	drsText.invalidate();
}

void RaceScreenView::updateSocLv(uint8_t soc)
{
    Unicode::snprintf(lvSocValueTextBuffer, LVSOCVALUETEXT_SIZE, "%d", soc);


    if(soc <= BATTERY_LV_SOC_MIN)
    {
    	LvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    	lvSocValueText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(soc <= BATTERY_LV_SOC_MAX && soc > BATTERY_LV_SOC_MIN)
    {
    	LvSoCText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    	lvSocValueText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	LvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    	lvSocValueText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    lvSocValueText.setVisible(true);
    lvSocValueText.invalidate();
    LvSoCText.setVisible(true);
    LvSoCText.invalidate();
}

void RaceScreenView::updateSocHv(uint8_t soc)
{
    Unicode::snprintf(hvSocValueTextBuffer, HVSOCVALUETEXT_SIZE, "%d", soc);

    if(soc <= BATTERY_HV_SOC_MIN)
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    	hvSocValueText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(soc <= BATTERY_HV_SOC_MAX && soc > BATTERY_HV_SOC_MIN)
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    	hvSocValueText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	HvSoCText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    	hvSocValueText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    hvSocValueText.setVisible(true);
    hvSocValueText.invalidate();
    HvSoCText.setVisible(true);
    HvSoCText.invalidate();
}

void RaceScreenView::updateBatteryHVTemperature(uint8_t temperature)
{
    Unicode::snprintf(hvtemptextBuffer , HVTEMPTEXT_SIZE , "%d", temperature);

    if(temperature > BATTERY_HV_TEMPERATURE_MAX || temperature < BATTERY_HV_TEMPERATURE_MIN)
    {
    	hvtempimage.setBitmap(Bitmap(BITMAP_BATTERYHV_CRIT_ID));
    	hvtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature < BATTERY_HV_TEMPERATURE_MAX  && temperature > BATTERY_HV_TEMPERATURE_MID)
    {
    	hvtempimage.setBitmap(Bitmap(BITMAP_BATTERYHV_WARN_ID));
    	hvtemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	hvtempimage.setBitmap(Bitmap(BITMAP_BATTERYHV_ID));
    	hvtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }


    hvtemptext.setVisible(true);
    hvtemptext.invalidate();
    hvtempimage.setVisible(true);
    hvtempimage.invalidate();
}

void RaceScreenView::updateInverterTemperature(uint8_t inv_FL_temperature,
											   uint8_t inv_FR_temperature,
											   uint8_t inv_RL_temperature,
											   uint8_t inv_RR_temperature) {

uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});

Unicode::snprintf(invtemptextBuffer, INVTEMPTEXT_SIZE, "%d", inv_temp_highest);
if(inv_temp_highest > INVERTER_TEMPERATURE_MAX || inv_temp_highest < INVERTER_TEMPERATURE_MIN)
{
	invtempimage.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
	invtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
}
else if(inv_temp_highest > INVERTER_TEMPERATURE_MID)
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
 //TODO: Jeżeli detla wartość jest dodaatnia wyświetlać na zielono, jeżeli nie na czerwono
}

void RaceScreenView::updateLap(uint8_t value)
{
	Unicode::snprintf(LapValueTextBuffer, LAPVALUETEXT_SIZE, "%d", value);
	LapValueText.setVisible(true);
	LapValueText.invalidate();
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
    	motortempimage.setBitmap(Bitmap(BITMAP_ENGINE_CRIT_ID));
    	motortemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(highestTemperature > MOTOR_TEMPERATURE_MID)
    {
    	motortempimage.setBitmap(Bitmap(BITMAP_ENGINE_WARN_ID));
    	motortemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	motortempimage.setBitmap(Bitmap(BITMAP_ENGINE_ID));
    	motortemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }


    motortemptext.setVisible(true);
    motortempimage.setVisible(true);
    motortemptext.invalidate();
    motortempimage.invalidate();
}



