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
#define MOTOR_TEMPERATURE_MID 20
#define MOTOR_TEMPERATURE_MAX 60
#define INVERTER_TEMPERATURE_MIN 5
#define INVERTER_TEMPERATURE_MID 30
#define INVERTER_TEMPERATURE_MAX 40
//TODO: uzupełnić odpowiednimi parametrami
#define OIL_TEMPERATURE_MIN 5
#define OIL_TEMPERATURE_MID 30
#define OIL_TEMPERATURE_MAX 50
#define BRAKE_PRESSURE_MIN 200
#define BRAKE_PRESSURE_RTD_SET 900
#define BRAKE_PRESSURE_MAX 1100
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
    	rtdAcitve.setVisible(true);
    	rtdOff.setVisible(false);
    } else {
    	rtdAcitve.setVisible(false);
    	rtdOff.setVisible(true);
    }
    rtdAcitve.invalidate();
    rtdOff.invalidate();
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

    int errorCount = inv_FL_error + inv_FR_error + inv_RL_error + inv_RR_error;
    bool anyError = (errorCount > 0);
    bool allOK = inv_ready   && !anyError;
    bool allOff = !inv_ready  && !anyError;
    bool generalError = (errorCount > 1);
    bool singleError = (errorCount == 1);


    invOK.setVisible(allOK);
    invOff.setVisible(allOff);
    invError.setVisible(generalError);
    invFL_Error.setVisible(singleError && inv_FL_error);
    invFR_Error.setVisible(singleError && inv_FR_error);
    invRL_Error.setVisible(singleError && inv_RL_error);
    invRR_Error.setVisible(singleError && inv_RR_error);


    invOK.invalidate();
    invOff.invalidate();;
    invError.invalidate();;
    invFL_Error.invalidate();;
    invFR_Error.invalidate();;
    invRL_Error.invalidate();;
    invRR_Error.invalidate();;
}



void MainScreenView::updateBatteryLvTemperature(uint8_t temperature) {
    Unicode::snprintf(batLvTempTextBuffer, BATLVTEMPTEXT_SIZE, "%d", temperature);


    if(temperature >= BATTERY_LV_TEMPERATURE_MAX || temperature <= BATTERY_LV_TEMPERATURE_MIN)
    {
    	batLvTempIcon.setBitmap(Bitmap(BITMAP_BATTERYLV_CRIT_ID));
    	batLvTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(temperature > BATTERY_LV_TEMPERATURE_MID)
    {
    	batLvTempIcon.setBitmap(Bitmap(BITMAP_BATTERYLV_WARN_ID));
    	batLvTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
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
                                               uint8_t inv_RR_temperature)
{
    uint8_t inv_temp_highest = std::max({inv_FL_temperature, inv_FR_temperature, inv_RL_temperature, inv_RR_temperature});
    Unicode::snprintf(invTempTextBuffer, INVTEMPTEXT_SIZE, "%d", inv_temp_highest);


    if (inv_temp_highest >= INVERTER_TEMPERATURE_MAX || inv_temp_highest <= INVERTER_TEMPERATURE_MIN) {
         invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
         invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if (inv_temp_highest > INVERTER_TEMPERATURE_MID)
    {
         invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_WARN_ID));
         invTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
         invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_ID));
         invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }


    invTempIcon.setVisible(true);
    invTempText.setVisible(true);
    invTempIcon.invalidate();
    invTempText.invalidate();
}


void MainScreenView::updateFrontBrakePressure(uint16_t pressure) {

	// Konwersja wartości czujnika do reprezentacji stałoprzecinkowej (skalowanej razy 100)
	    const int Pmax_fixed = 12000;  // SENSOR_PMAX * 100 (120.00)
	    const int Pmin_fixed = 20;     // SENSOR_PMIN * 100 (0.20)
	    const int Vmax_fixed = 450;    // SENSOR_VMAX * 100 (4.50)
	    const int Vmin_fixed = 50;     // SENSOR_VMIN * 100 (0.50)
	    const int adc_max = 4095;      // Maksymalna wartość ADC (12-bitowy)

	    // Obliczamy napięcie z ADC w jednostkach setnych woltów.
	    // 3.3 V (referencyjne) * 100 = 330
	    int voltage_fixed = (330 * pressure) / adc_max;

	    // Obliczamy ciśnienie w setnych barów wg równania:
	    // pressure_bar = ((Pmax - Pmin)/(Vmax - Vmin)) * (napięcie - Vmin) + Pmin
	    int pressureHundredths = ((Pmax_fixed - Pmin_fixed) * (voltage_fixed - Vmin_fixed))
	                             / (Vmax_fixed - Vmin_fixed) + Pmin_fixed;

	    // Rozdzielenie części całkowitej i ułamkowej (setne)
	    int pressureWhole = pressureHundredths / 100;
	    int pressureFrac  = pressureHundredths % 100;

	    // Formatowanie tekstu "XX.XX"
	    Unicode::snprintf(FrontBrakePressTextBuffer, FRONTBRAKEPRESSTEXT_SIZE, "%02d.%02d", pressureWhole, pressureFrac);

        PressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_ID));

	    if(pressure >= BRAKE_PRESSURE_RTD_SET)
	    {
	        FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
	        FrontBrakePressLabel.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));

	    }
	    else if(pressure < BRAKE_PRESSURE_MIN ||  pressure > BRAKE_PRESSURE_MAX)
	    {
	        FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	        FrontBrakePressLabel.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	    }
	    else
	    {
	        FrontBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	        FrontBrakePressLabel.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	    }

	    PressIcon.setVisible(true);
	    PressIcon.invalidate();

	    FrontBrakePressText.setVisible(true);
	    FrontBrakePressText.invalidate();

	    FrontBrakePressLabel.setVisible(true);
	    FrontBrakePressLabel.invalidate();
}

void MainScreenView::updateRearBrakePressure(uint16_t pressure) {

	// Konwersja wartości czujnika do reprezentacji stałoprzecinkowej (skalowanej razy 100)
	    const int Pmax_fixed = 12000;  // SENSOR_PMAX * 100 (120.00)
	    const int Pmin_fixed = 20;     // SENSOR_PMIN * 100 (0.20)
	    const int Vmax_fixed = 450;    // SENSOR_VMAX * 100 (4.50)
	    const int Vmin_fixed = 50;     // SENSOR_VMIN * 100 (0.50)
	    const int adc_max = 4095;      // Maksymalna wartość ADC (12-bitowy)

	    // Obliczamy napięcie z ADC w jednostkach setnych woltów.
	    // 3.3 V (referencyjne) * 100 = 330
	    int voltage_fixed = (330 * pressure) / adc_max;

	    // Obliczamy ciśnienie w setnych barów wg równania:
	    // pressure_bar = ((Pmax - Pmin)/(Vmax - Vmin)) * (napięcie - Vmin) + Pmin
	    int pressureHundredths = ((Pmax_fixed - Pmin_fixed) * (voltage_fixed - Vmin_fixed))
	                             / (Vmax_fixed - Vmin_fixed) + Pmin_fixed;

	    // Rozdzielenie części całkowitej i ułamkowej (setne)
	    int pressureWhole = pressureHundredths / 100;
	    int pressureFrac  = pressureHundredths % 100;

    Unicode::snprintf(RearBrakePressTextBuffer, REARBRAKEPRESSTEXT_SIZE, "%02d.%02d", pressureWhole,pressureFrac);

    PressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_ID));

    if(pressure >= BRAKE_PRESSURE_RTD_SET)
    {
    	RearBrakePressText.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
    	RearBrakePressLabel.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));

    }
    else if(pressure < BRAKE_PRESSURE_MIN ||  pressure > BRAKE_PRESSURE_MAX)
    {
    	RearBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
        RearBrakePressLabel.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else
    {
    	RearBrakePressText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        RearBrakePressLabel.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    PressIcon.setVisible(true);
    PressIcon.invalidate();

    RearBrakePressText.setVisible(true);
    RearBrakePressText.invalidate();

    RearBrakePressLabel.setVisible(true);
    RearBrakePressLabel.invalidate();
}

void MainScreenView::updateCoolantInTemperature(uint8_t temperature) {
    //Unicode::snprintf(coolinTempTextBuffer, COOLINTEMPTEXT_SIZE, "%d", temperature);

	Unicode::snprintf(coolinTempTextBuffer, COOLINTEMPTEXT_SIZE, "%d", 20);

    if(temperature >= COOLANT_TEMPERATURE_MAX || temperature <= COOLANT_TEMPERATURE_MIN) {
    	coolinTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_CRIT_ID));
    	coolinTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(temperature > COOLANT_TEMPERATURE_MID) {
    	coolinTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_WARN_ID));
    	coolinTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
    	coolinTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_ID));
        coolinTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    coolinTempIcon.setVisible(true);
    coolinTempText.setVisible(true);
    coolinTempIcon.invalidate();
    coolinTempText.invalidate();
}

void MainScreenView::updateCoolantOutTemperature(uint8_t temperature) {
	//Unicode::snprintf(cooloutTempTextBuffer, COOLOUTTEMPTEXT_SIZE, "%d", temperature);

	Unicode::snprintf(cooloutTempTextBuffer, COOLOUTTEMPTEXT_SIZE, "%d", 25);

    if(temperature >= COOLANT_TEMPERATURE_MAX || temperature <= COOLANT_TEMPERATURE_MIN) {
    	cooloutTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_CRIT_ID));
    	cooloutTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    } else if(temperature > COOLANT_TEMPERATURE_MID) {
    	cooloutTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_WARN_ID));
    	cooloutTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    } else {
    	cooloutTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_ID));
    	cooloutTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }
    cooloutTempIcon.setVisible(true);
    cooloutTempText.setVisible(true);
    cooloutTempIcon.invalidate();
    cooloutTempText.invalidate();
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


	 if (temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
	 {
	   motorFrontLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	 }
	 else if (temperature > MOTOR_TEMPERATURE_MID)
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


    if (temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
    {
      motorFrontRighttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if (temperature > MOTOR_TEMPERATURE_MID)
    {
      motorFrontRighttext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
    }
    else
    {
      motorFrontRighttext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    }

    carImage.setVisible(true);
    motorFrontRighttext.setVisible(true);
    carImage.invalidate();
    motorFrontRighttext.invalidate();
}

void MainScreenView::updateMotorRearLeftTemperature(uint8_t temperature)
{

   Unicode::snprintf(motorRearLefttextBuffer, MOTORREARLEFTTEXT_SIZE, "%d", temperature);


   if (temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
   {
     motorRearLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
   }
   else if (temperature > MOTOR_TEMPERATURE_MID)
   {
     motorRearLefttext.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
   }
   else
   {
     motorRearLefttext.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
   }


    carImage.setVisible(true);
    motorRearLefttext.setVisible(true);
    carImage.invalidate();
    motorRearLefttext.invalidate();
}

void MainScreenView::updateMotorRearRightTemperature(uint8_t temperature)
{
   Unicode::snprintf(motorRearRighttextBuffer, MOTORREARRIGHTTEXT_SIZE, "%d", temperature);


   if (temperature >= MOTOR_TEMPERATURE_MAX || temperature <= MOTOR_TEMPERATURE_MIN)
   {
     motorRearRighttext.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
   }
   else if (temperature > MOTOR_TEMPERATURE_MID)
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

void MainScreenView::displayError(int error_idx)
{
	using namespace touchgfx;

	    TextAreaWithOneWildcard* texts[] = {
	        &safety_wheel_rl_Text,  // 0
	        &safety_wheel_rr_Text,  // 1
	        &safety_wheel_fr_Text,  // 2
	        &safety_wheel_fl_Text,  // 3
	        &safety_hv_Text,        // 4
	        &safety_inv_Text,       // 5
	        //&safety_asms_Text,     // 6
	        &sense_right_kill_Text, // 7
	        &sense_left_kill_Text,  // 8
	        &sense_driver_kill_Text,// 9
	        &sense_inertia_Text,    // 10
	        &sense_bspd_Text,       // 11
	        &sense_overtravel_Text, // 12
	        &safety_hvd_Text        // 13
	    };

	    const size_t num_texts = sizeof(texts) / sizeof(texts[0]);

	    // Najpierw wyłączamy widoczność wszystkich elementów
	    for (size_t i = 0; i < num_texts; ++i)
	    {
	        texts[i]->setVisible(false);
	        texts[i]->invalidate();
	    }

	    // Jeśli error_idx jest poprawnym indeksem (>= 0 i < num_texts), włączamy widoczność odpowiadającego elementu.
	    if (error_idx >= 0 && static_cast<size_t>(error_idx) < num_texts)
	    {
	        texts[error_idx]->setVisible(true);
	        texts[error_idx]->invalidate();
	    }
}



//Safety display
void MainScreenView::updateSDC(SafetyData_TypeDef status)
{
    std::array<bool, 13> fields = {
        status.safety_wheel_rl,  // Rear Left Wheel Sensor
        status.safety_wheel_rr,  // Rear Right Wheel Sensor
        status.safety_wheel_fr,  // Front Right Wheel Sensor
        status.safety_wheel_fl,  // Front Left Wheel Sensor
        status.safety_hv,        // High Voltage System Safety
        status.safety_inv,       // Inverter Safety
        //status.safety_asms,    // AMS (Accumulator Management System)
        status.sense_right_kill, // Right Kill Switch
        status.sense_left_kill,  // Left Kill Switch
        status.sense_driver_kill,// Cockpit Kill Switch
        status.sense_inertia,    // Inertia Switch
        status.sense_bspd,       // BSPD
        status.sense_overtravel, // Overtravel (BOTS)
        status.safety_hvd        // HVD
    };

    int first_error_index = -1;

    // Używamy std::size_t do iteracji:
    for (std::size_t i = 0; i < fields.size(); i++)
    {
        if (fields[i])
        {
            // Jeśli potrzebujemy zapisać w int, rzutujemy:
            first_error_index = static_cast<int>(i);
            break;
        }
    }

    // Wyświetlamy tylko skrót błędu lub komunikat "OK"
    if (first_error_index == -1)
    {
        sdcStatusLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        //Unicode::snprintf(sdcTextBuffer, SDCTEXT_SIZE, "%s", "OK");
        sdcText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

        displayError(first_error_index);

        sdcText.setVisible(true);
        sdcText.invalidate();
        sdcStatusLabelText.setVisible(true);
        sdcStatusLabelText.invalidate();
    }
    else
    {
        sdcStatusLabelText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));

        sdcStatusLabelText.setVisible(true);
        sdcStatusLabelText.invalidate();

        sdcText.setVisible(false);
        sdcText.invalidate();

        displayError(first_error_index);
    }
}





void MainScreenView::updateRtdButtonPressed(bool status)
{
    if(status)
    {
    	RTD_Led.setVisible(true);
    	RTD_Led.invalidate();
    }
    else
    {
    	RTD_Led.setVisible(false);
    	RTD_Led.invalidate();
    }
}


void MainScreenView::updateTsaButtonPressed(bool status)
{
    if(status)
    {
    	TSA_Led.setVisible(true);
    	TSA_Led.invalidate();
    }
    else
    {
    	TSA_Led.setVisible(false);
    	TSA_Led.invalidate();
    }
}

void MainScreenView::updatePduPcStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	PcPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	PcPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	PcPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	PcPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    PcPduText.setVisible(true);
    PcPduText.invalidate();
}

void MainScreenView::updatePduFanStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	FanPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	FanPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	FanPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	FanPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    FanPduText.setVisible(true);
    FanPduText.invalidate();
}

void MainScreenView::updatePduPumpStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	PumpPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	PumpPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	PumpPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	PumpPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    PumpPduText.setVisible(true);
    PumpPduText.invalidate();
}


void MainScreenView::updatePduInverterStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	InvPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	InvPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	InvPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	InvPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    InvPduText.setVisible(true);
    InvPduText.invalidate();
}

void MainScreenView::updatePduFboxStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	FboxPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	FboxPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	FboxPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	FboxPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    FboxPduText.setVisible(true);
    FboxPduText.invalidate();
}

void MainScreenView::updatePduSdcStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	SdcPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	SdcPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	SdcPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	SdcPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    SdcPduText.setVisible(true);
    SdcPduText.invalidate();
}

void MainScreenView::updatePduDashStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	DashPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	DashPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	DashPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	DashPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    DashPduText.setVisible(true);
    DashPduText.invalidate();
}

void MainScreenView::updatePduTsalStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	TsalPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	TsalPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	TsalPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	TsalPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    TsalPduText.setVisible(true);
    TsalPduText.invalidate();
}

void MainScreenView::updatePduRboxStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	RboxPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	RboxPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	RboxPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	RboxPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    RboxPduText.setVisible(true);
    RboxPduText.invalidate();
}

void MainScreenView::updatePduAirStatus(uint8_t status)
{
    if(status == 0)
    {
    	//Off
    	AirPduText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else if(status == 2)
    {
    	//Error
    	AirPduText.setColor(touchgfx::Color::getColorFromRGB(222, 107, 40));
    }
    else if(status == 1)
    {
    	//ok
    	AirPduText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
    }
    else
    {
    	AirPduText.setColor(touchgfx::Color::getColorFromRGB(102, 102, 102));
    }

    AirPduText.setVisible(true);
    AirPduText.invalidate();
}










