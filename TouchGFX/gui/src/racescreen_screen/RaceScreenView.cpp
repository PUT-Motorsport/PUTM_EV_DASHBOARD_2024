
#include <gui/racescreen_screen/RaceScreenView.hpp>

#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#include <algorithm>


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
    	hvtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    	HvTempLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature < BATTERY_HV_TEMPERATURE_MAX  && temperature > BATTERY_HV_TEMPERATURE_MID)
    {
    	hvtemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    	HvTempLabelText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	hvtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    	HvTempLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    hvtemptext.setVisible(true);
    hvtemptext.invalidate();
    HvTempLabelText.setVisible(true);
    HvTempLabelText.invalidate();
}

void RaceScreenView::updateInverterTemperature(uint8_t inv_FL_temperature,
                                               uint8_t inv_FR_temperature,
                                               uint8_t inv_RL_temperature,
                                               uint8_t inv_RR_temperature)
{
   uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});
   Unicode::snprintf(invtemptextBuffer, INVTEMPTEXT_SIZE, "%d", inv_temp_highest);

   if (inv_temp_highest > INVERTER_TEMPERATURE_MAX || inv_temp_highest < INVERTER_TEMPERATURE_MIN)
   {
      InvTempLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
      invtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
   }
   else if (inv_temp_highest > INVERTER_TEMPERATURE_MID)
   {
       InvTempLabelText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
       invtemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
   }
   else
   {
       InvTempLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
       invtemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
   }


    InvTempLabelText.setVisible(true);
    invtemptext.setVisible(true);
    InvTempLabelText.invalidate();
    invtemptext.invalidate();
}


void RaceScreenView::updatePace(int16_t pace)
{
    // Set the appropriate background bitmap and format the pace text based on the sign of the pace value.
    if (pace > 0)
    {
        // For positive pace: set the red feedback background and prepend a '+' sign.
        paceBackground.setBitmap(Bitmap(BITMAP_PACEREDBACKGROUND_ID));
    }
    else if (pace < 0)
    {
        // For negative pace: set the green background and prepend a '-' sign.
        paceBackground.setBitmap(Bitmap(BITMAP_PACEGREENBACKGROUND_ID));
    }
    else
    {
        // For zero pace: set the yellow background and display "00.000".
        paceBackground.setBitmap(Bitmap(BITMAP_PACEYELLOWBACKGROUND_ID));
    }

    paceBackground.setVisible(true);
    paceBackground.invalidate();



    // The "pace" value sent by the lap timer is multiplied by 1000
    // to avoid sending a floating-point number.
    // First, we obtain the absolute value to properly split it into seconds and milliseconds.
    int absPace = static_cast<int>(abs(pace));
    volatile int seconds = static_cast<int>(absPace / 1000);     // Whole part: seconds
    volatile int milliseconds = static_cast<int>(absPace % 1000); // Fractional part: milliseconds

    Unicode::snprintf(PaceTextBuffer, PACETEXT_SIZE, "%+02d.%02d", seconds, milliseconds);
    PaceText.setVisible(true);
    PaceText.invalidate();

}


void RaceScreenView::updateLap(uint8_t value)
{
    Unicode::snprintf(LapValueTextBuffer, LAPVALUETEXT_SIZE, "%d", value);

    LapValueText.setVisible(true);
    LapValueText.invalidate();
}

void RaceScreenView::updateBestLap(uint32_t time)
{
    uint8_t minutes = time / (1000 * 60);
    time %= (1000 * 60);
    uint8_t seconds = time / 1000;
    time %= 1000;

    Unicode::snprintf(bestLapTextBuffer, BESTLAPTEXT_SIZE, "%02d:%02d.%03d", minutes, seconds, time);
    bestLapText.invalidate();
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

    if (highestTemperature > MOTOR_TEMPERATURE_MAX || highestTemperature < MOTOR_TEMPERATURE_MIN)
    {
     	MotorTempLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
        motortemptext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if (highestTemperature > MOTOR_TEMPERATURE_MID)
    {
      	MotorTempLabelText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
        motortemptext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
      	MotorTempLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        motortemptext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    motortemptext.setVisible(true);
    MotorTempLabelText.setVisible(true);
    motortemptext.invalidate();
    MotorTempLabelText.invalidate();
}




