#include <gui/mainscreen_screen/MainScreenView.hpp>

#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#include <algorithm>

#define BATTERY_LV_TEMPERATURE_MIN 5
#define BATTERY_LV_TEMPERATURE_MID 30
#define BATTERY_LV_TEMPERATURE_MAX 35
#define BATTERY_LV_SOC_MIN 20
#define BATTERY_LV_SOC_MID 50
#define BATTERY_LV_SOC_MAX 90
#define MOTOR_TEMPERATURE_MIN 5
#define MOTOR_TEMPERATURE_MID 60
#define MOTOR_TEMPERATURE_MAX 80
#define INVERTER_TEMPERATURE_MIN 5
#define INVERTER_TEMPERATURE_MID 30
#define INVERTER_TEMPERATURE_MAX 40
//TODO: uzupełnić odpowiednimi parametrami
#define OIL_TEMPERATURE_MIN 5
#define OIL_TEMPERATURE_MID 30
#define OIL_TEMPERATURE_MAX 50
#define BRAKE_PRESSURE_MIN 1
#define BRAKE_PRESSURE_MID 5
#define BRAKE_PRESSURE_MAX 15
#define COOLANT_TEMPERATURE_MIN 5
#define COOLANT_TEMPERATURE_MID 30
#define COOLANT_TEMPERATURE_MAX 35

MainScreenView::MainScreenView() {}

void MainScreenView::setupScreen() { MainScreenViewBase::setupScreen(); }

void MainScreenView::tearDownScreen() { MainScreenViewBase::tearDownScreen(); }

void MainScreenView::updateClock(uint32_t time) {
    uint8_t hours = time / 3600;
    time %= 3600;
    uint8_t minutes = time / 60;
    clockWidget.setTime24Hour(hours, minutes, 0);
}

void MainScreenView::updateConnection(bool status) {
    if(status) {
        connIcon.setBitmap(Bitmap(BITMAP_CONN_ON_ID));
    } else {
        connIcon.setBitmap(Bitmap(BITMAP_CONN_OFF_ID));
    }
    connIcon.setVisible(true);
    connIcon.invalidate();
}

void MainScreenView::updateWarning(bool status) {
    if(status) {
        m_warning = true;
        warnIcon.setBitmap(Bitmap(BITMAP_WARN_ON_ID));
    } else {
        m_warning = false;
        warnIcon.setBitmap(Bitmap(BITMAP_WARN_OFF_ID));
        warnIcon.setVisible(true);
    }
    warnIcon.invalidate();
}

void MainScreenView::updateRadio(bool status) {
    if(status) {
        radioIcon.setBitmap(Bitmap(BITMAP_RADIO_ON_ID));
    } else {
        radioIcon.setBitmap(Bitmap(BITMAP_RADIO_OFF_ID));
    }
    radioIcon.invalidate();
}

void MainScreenView::updateReadyToDrive(bool status) {
    if(status) {
        rtdText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    } else {
        rtdText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }
    rtdText.invalidate();
}

void MainScreenView::updateInvertersStatus(bool inv_ready,
										   bool inv_FL_status,
										   bool inv_FR_status,
										   bool inv_RL_status,
										   bool inv_RR_status,
										   bool inv_FL_error,
										   bool inv_FR_error,
										   bool inv_RL_error,
										   bool inv_RR_error)
{

if(inv_ready)
{
	//Inv work correct
    invText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
}
else if (inv_FL_error || inv_FR_error || inv_RL_error || inv_RR_error)
{
	//Error inv
	invText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
}
else if (!inv_FL_status || !inv_FR_status || !inv_RL_status || !inv_RR_status)
{
	//Inv Unknown working status
	invText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
}

 invText.invalidate();

}

void MainScreenView::updateBatteryLvTemperature(uint8_t temperature) {
    Unicode::snprintf(batLvTempTextBuffer, BATLVTEMPTEXT_SIZE, "%d", temperature);
    if(temperature >= BATTERY_LV_TEMPERATURE_MAX || temperature <= BATTERY_LV_TEMPERATURE_MIN) {
    	batLvTempIcon.setBitmap(Bitmap(BITMAP_BATTERYLV_CRIT_ID));
    	batLvTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(temperature > BATTERY_LV_TEMPERATURE_MID) {
    	batLvTempIcon.setBitmap(Bitmap(BITMAP_BATTERYLV_WARN_ID));
    	batLvTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
    	batLvTempIcon.setBitmap(Bitmap(BITMAP_BATTERYLV_ID));
    	batLvTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    batLvTempIcon.setVisible(true);
    batLvTempText.setVisible(true);
    batLvTempIcon.invalidate();
    batLvTempText.invalidate();
}



void MainScreenView::updateInverterTemperature(uint8_t inv_FL_temperature,
											   uint8_t inv_FR_temperature,
											   uint8_t inv_RL_temperature,
											   uint8_t inv_RR_temperature) {

	uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});

    Unicode::snprintf(invTempTextBuffer, INVTEMPTEXT_SIZE, "%d", inv_temp_highest);
    if(inv_temp_highest >= INVERTER_TEMPERATURE_MAX || inv_temp_highest <= INVERTER_TEMPERATURE_MIN) {
        invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
        invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(inv_temp_highest > INVERTER_TEMPERATURE_MID) {
        invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_WARN_ID));
        invTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
        invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_ID));
        invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    invTempIcon.setVisible(true);
    invTempText.setVisible(true);
    invTempIcon.invalidate();
    invTempText.invalidate();
}

void MainScreenView::updateOilTemperature(uint8_t temperature) {
    Unicode::snprintf(oilTempTextBuffer, OILTEMPTEXT_SIZE, "%d", temperature);
    if(temperature >= OIL_TEMPERATURE_MAX || temperature <= OIL_TEMPERATURE_MIN) {
        oilTempIcon.setBitmap(Bitmap(BITMAP_OIL_CRIT_ID));
        oilTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(temperature > OIL_TEMPERATURE_MID) {
        oilTempIcon.setBitmap(Bitmap(BITMAP_OIL_WARN_ID));
        oilTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
        oilTempIcon.setBitmap(Bitmap(BITMAP_OIL_ID));
        oilTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    oilTempIcon.setVisible(true);
    oilTempText.setVisible(true);
    oilTempIcon.invalidate();
    oilTempText.invalidate();
}

void MainScreenView::updateFrontBrakePressure(uint16_t pressure) {
    Unicode::snprintf(FrontBrakePressTextBuffer, FRONTBRAKEPRESSTEXT_SIZE, "%d", pressure);
    if(pressure >= BRAKE_PRESSURE_MAX || pressure <= BRAKE_PRESSURE_MIN) {
    	PressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_CRIT_ID));
        FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(pressure > BRAKE_PRESSURE_MID) {
    	PressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_WARN_ID));
        FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
    	PressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_ID));
        FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    PressIcon.setVisible(true);
    FrontBrakePressText.setVisible(true);
    PressIcon.invalidate();
    FrontBrakePressText.invalidate();
}

void MainScreenView::updateRearBrakePressure(uint16_t pressure) {
    Unicode::snprintf(RearBrakePressTextBuffer, REARBRAKEPRESSTEXT_SIZE, "%d", pressure);
    if(pressure >= BRAKE_PRESSURE_MAX || pressure <= BRAKE_PRESSURE_MIN) {
    	PressIcon.setBitmap(Bitmap(BITMAP_COOLANT_PRESSURE_CRIT_ID));
    	FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(pressure > BRAKE_PRESSURE_MID) {
    	PressIcon.setBitmap(Bitmap(BITMAP_COOLANT_PRESSURE_WARN_ID));
    	FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
    	PressIcon.setBitmap(Bitmap(BITMAP_COOLANT_PRESSURE_ID));
    	FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    PressIcon.setVisible(true);
    FrontBrakePressText.setVisible(true);
    PressIcon.invalidate();
    FrontBrakePressText.invalidate();
}

void MainScreenView::updateCoolantTemperature(uint8_t temperature) {
    Unicode::snprintf(coolTempTextBuffer, COOLTEMPTEXT_SIZE, "%d", temperature);
    if(temperature >= COOLANT_TEMPERATURE_MAX || temperature <= COOLANT_TEMPERATURE_MIN) {
        coolTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_CRIT_ID));
        coolTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(temperature > COOLANT_TEMPERATURE_MID) {
        coolTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_WARN_ID));
        coolTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
        coolTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_ID));
        coolTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    coolTempIcon.setVisible(true);
    coolTempText.setVisible(true);
    coolTempIcon.invalidate();
    coolTempText.invalidate();
}



void MainScreenView::updateRpm(uint16_t rpm) {
    uint8_t value = (rpm * 100) / DASH_RPM_MAX;
    rpmProgress.setValue(value);
}


void MainScreenView::updateCurrentLap(uint32_t time) {
    uint8_t minutes = time / (1000 * 60);
    time %= (1000 * 60);
    uint8_t seconds = time / 1000;
    time %= 1000;

    Unicode::snprintf(currentLapTextBuffer, CURRENTLAPTEXT_SIZE, "%02d:%02d.%03d", minutes, seconds, time);
    currentLapText.invalidate();
}

void MainScreenView::updateLastLap(uint32_t time) {
    uint8_t minutes = time / (1000 * 60);
    time %= (1000 * 60);
    uint8_t seconds = time / 1000;
    time %= 1000;

    Unicode::snprintf(lastLapTextBuffer, LASTLAPTEXT_SIZE, "%02d:%02d.%03d", minutes, seconds, time);
    lastLapText.invalidate();
}

void MainScreenView::updateBestLap(uint32_t time) {
    uint8_t minutes = time / (1000 * 60);
    time %= (1000 * 60);
    uint8_t seconds = time / 1000;
    time %= 1000;

    Unicode::snprintf(bestLapTextBuffer, BESTLAPTEXT_SIZE, "%02d:%02d.%03d", minutes, seconds, time);
    bestLapText.invalidate();
}

void MainScreenView::toggleWarning() {
    if(m_time > 9) {
        if(m_warning) {
            warnIcon.isVisible() ? warnIcon.setVisible(false) : warnIcon.setVisible(true);
            warnIcon.invalidate();
        }
        m_time = 0;
    } else {
        m_time++;
    }
}

void MainScreenView::updateMotorFrontLeftTemperature(uint8_t temperature)
{
    Unicode::snprintf(motorFrontLefttextBuffer, MOTORFRONTLEFTTEXT_SIZE, "%d", temperature);
    if(temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
    {
    	motorFrontLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature > MOTOR_TEMPERATURE_MID)
    {
    	motorFrontLefttext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	motorFrontLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    carImage.setVisible(true);
    motorFrontLefttext.setVisible(true);
    carImage.invalidate();
    motorFrontLefttext.invalidate();
}

void MainScreenView::updateMotorFrontRightTemperature(uint8_t temperature)
{
    Unicode::snprintf(motorFrontRighttextBuffer, MOTORFRONTRIGHTTEXT_SIZE, "%d", temperature);
    if(temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
    {
    	motorFrontRighttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature > MOTOR_TEMPERATURE_MID)
    {
    	motorFrontRighttext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	motorFrontLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    carImage.setVisible(true);
    motorFrontRighttext.setVisible(true);
    carImage.invalidate();
    motorFrontRighttext.invalidate();
}

void MainScreenView::updateMotorRearLeftTemperature(uint8_t temperature)
{
    Unicode::snprintf(motorRearLefttextBuffer, MOTORREARLEFTTEXT_SIZE, "%d", temperature);
    if(temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
    {
    	motorRearLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature > MOTOR_TEMPERATURE_MID)
    {
    	motorRearLefttext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	motorFrontLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    carImage.setVisible(true);
    motorRearLefttext.setVisible(true);
    carImage.invalidate();
    motorRearLefttext.invalidate();
}

void MainScreenView::updateMotorRearRightTemperature(uint8_t temperature)
{
    Unicode::snprintf(motorRearRighttextBuffer, MOTORREARRIGHTTEXT_SIZE, "%d", temperature);
    if(temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
    {
    	motorRearRighttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(temperature > MOTOR_TEMPERATURE_MID)
    {
    	motorRearRighttext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
    	motorRearRighttext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    carImage.setVisible(true);
    motorRearRighttext.setVisible(true);
    carImage.invalidate();
    motorRearRighttext.invalidate();
}


//Safety display
void MainScreenView::setSafetyStatus(const char* text, uint8_t red, uint8_t green, uint8_t blue)
{
    Unicode::snprintf(sdcStatusLabelTextBuffer, SDCSTATUSLABELTEXT_SIZE, "%s", "SDC Status");
    sdcStatusLabelText.setColor(touchgfx::Color::getColorFromRGB(red, green, blue));

    Unicode::snprintf(sdcTextBuffer, SDCTEXT_SIZE, "%s", text);
    sdcText.setColor(touchgfx::Color::getColorFromRGB(red, green, blue));

	sdcText.setVisible(true);
	sdcText.invalidate();

	sdcStatusLabelText.setVisible(true);
	sdcStatusLabelText.invalidate();
}



void MainScreenView::updateSDC(SafetyData_TypeDef status)
{
    std::array<bool, 14> fields = {
        status.safety_wheel_rl,  // Rear Left Wheel Sensor
        status.safety_wheel_rr,  // Rear Right Wheel Sensor
        status.safety_wheel_fr,  // Front Right Wheel Sensor
        status.safety_wheel_fl,  // Front Left Wheel Sensor
        status.safety_hv,        // High Voltage System Safety
        status.safety_inv,       // Inverter Safety
        status.safety_asms,      // AMS (Accumulator Management System)
        status.sense_right_kill, // Right Kill Switch
        status.sense_left_kill,  // Left Kill Switch
        status.sense_driver_kill,// Cockpit Kill Switch
        status.sense_inertia,    // Inertia Switch
        status.sense_bspd,       // BSPD
        status.sense_overtravel, // BOTS
        status.safety_hvd        // HVD
    };

    std::array<const char*, 14> error_names = {
        "WRL", "WRR", "WFR", "WFL",
        "HV", "INV", "ASMS",
        "RK", "LK", "DK",
        "INE", "BSPD", "ORT", "HVD"
    };

    int first_error_index = -1;
    for (int i = 0; i < fields.size(); i++) {
        if (fields[i]) {
            first_error_index = i;
            break;
        }
    }

    if (first_error_index == -1) {
        // Brak błędów - wyświetlamy "OK"
        setSafetyStatus("OK", 255, 255, 255);
    } else {
        // Wyświetlamy pierwszy wykryty błąd
        setSafetyStatus(error_names[first_error_index], 255, 0, 0);
    }
}









