#include <gui/mainscreen_screen/MainScreenView.hpp>

#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

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

void MainScreenView::updateBatteryTemperature(uint8_t temperature) {
	Unicode::snprintf(batTempTextBuffer, BATTEMPTEXT_SIZE, "%d", temperature);
	if(temperature > 50) {
		batTempIcon.setBitmap(Bitmap(BITMAP_BATTERY_CRIT_ID));
		batTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else if (temperature > 30) {
		batTempIcon.setBitmap(Bitmap(BITMAP_BATTERY_WARN_ID));
		batTempText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
	} else {
		batTempIcon.setBitmap(Bitmap(BITMAP_BATTERY_ID));
		batTempText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	batTempIcon.setVisible(true);
	batTempText.setVisible(true);
	batTempIcon.invalidate();
	batTempText.invalidate();
}

void MainScreenView::updateInverterTemperature(uint8_t temperature) {
	Unicode::snprintf(invTempTextBuffer, INVTEMPTEXT_SIZE, "%d", temperature);
	if(temperature > 50) {
		invTempIcon.setBitmap(Bitmap(BITMAP_INVERTER_CRIT_ID));
		invTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else if (temperature > 30) {
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
	if(temperature > 50) {
		oilTempIcon.setBitmap(Bitmap(BITMAP_OIL_CRIT_ID));
		oilTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else if (temperature > 30) {
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

void MainScreenView::updateOilPressure(uint8_t pressure) {
	Unicode::snprintf(oilPressTextBuffer, OILPRESSTEXT_SIZE, "%d", pressure);
	if(pressure > 50) {
		oilPressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_CRIT_ID));
		oilPressText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else if (pressure > 30) {
		oilPressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_WARN_ID));
		oilPressText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
	} else {
		oilPressIcon.setBitmap(Bitmap(BITMAP_OIL_PRESSURE_ID));
		oilPressText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	oilPressIcon.setVisible(true);
	oilPressText.setVisible(true);
	oilPressIcon.invalidate();
	oilPressText.invalidate();
}

void MainScreenView::updateCoolantTemperature(uint8_t temperature) {
	Unicode::snprintf(coolTempTextBuffer, COOLTEMPTEXT_SIZE, "%d", temperature);
	if(temperature > 50) {
		coolTempIcon.setBitmap(Bitmap(BITMAP_COOLANT_CRIT_ID));
		coolTempText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else if (temperature > 30) {
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

void MainScreenView::updateCoolantPressure(uint8_t pressure) {
	Unicode::snprintf(coolPressTextBuffer, COOLPRESSTEXT_SIZE, "%d", pressure);
	if(pressure > 50) {
		coolPressIcon.setBitmap(Bitmap(BITMAP_COOLANT_PRESSURE_CRIT_ID));
		coolPressText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else if (pressure > 30) {
		coolPressIcon.setBitmap(Bitmap(BITMAP_COOLANT_PRESSURE_WARN_ID));
		coolPressText.setColor(touchgfx::Color::getColorFromRGB(163, 146, 46));
	} else {
		coolPressIcon.setBitmap(Bitmap(BITMAP_COOLANT_PRESSURE_ID));
		coolPressText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	coolPressIcon.setVisible(true);
	coolPressText.setVisible(true);
	coolPressIcon.invalidate();
	coolPressText.invalidate();
}

void MainScreenView::updatePace(int32_t pace) {
	if(pace > 0) {
		paceBackground.setBitmap(Bitmap(BITMAP_PACEREDBACKGROUND_ID));
	} else if (pace < 0) {
		paceBackground.setBitmap(Bitmap(BITMAP_PACEGREENBACKGROUND_ID));
	} else {
		paceBackground.setBitmap(Bitmap(BITMAP_PACEYELLOWBACKGROUND_ID));
	}
	paceBackground.invalidate();

	float seconds = static_cast<float>(pace) / 1000.0f;
	Unicode::snprintfFloat(paceTextBuffer, PACETEXT_SIZE, "%+#.3f", seconds);
	paceText.setVisible(true);
	paceText.invalidate();
}

void MainScreenView::updateSpeed(uint8_t speed) {
	Unicode::snprintf(speedTextBuffer, SPEEDTEXT_SIZE, "%d", speed);
	speedText.invalidate();
}

void MainScreenView::updateSoc(uint8_t soc) {
	Unicode::snprintf(socTextBuffer, SOCTEXT_SIZE, "%d", soc);
	socText.invalidate();
}

void MainScreenView::updateRpm(uint16_t rpm) {
	uint8_t value = (rpm * 100) / DASH_RPM_MAX;
	rpmProgress.setValue(value);
}

void MainScreenView::updatePower(uint8_t power) {
	Unicode::snprintf(powerTextBuffer, POWERTEXT_SIZE, "%d", power);
	powerText.invalidate();
}

void MainScreenView::updateDistance(uint16_t distance) {
	float kilometers = static_cast<float>(distance) / 1000.0f;

	Unicode::snprintfFloat(distanceTextBuffer, DISTANCETEXT_SIZE, "%#.2f", kilometers);
	distanceText.invalidate();
}

void MainScreenView::updateRange(uint16_t range) {
	if(range < 2000) {
		rangeText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	} else {
		rangeText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}

	float kilometers = static_cast<float>(range) / 1000.0f;

	Unicode::snprintfFloat(rangeTextBuffer, RANGETEXT_SIZE, "%#.2f", kilometers);
	rangeText.invalidate();
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
