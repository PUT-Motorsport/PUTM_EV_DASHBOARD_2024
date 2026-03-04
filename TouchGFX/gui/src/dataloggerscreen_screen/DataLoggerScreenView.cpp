#include <gui/dataloggerscreen_screen/DataLoggerScreenView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

DataLoggerScreenView::DataLoggerScreenView()
{

}

void DataLoggerScreenView::setupScreen()
{
    DataLoggerScreenViewBase::setupScreen();
}

void DataLoggerScreenView::tearDownScreen()
{
    DataLoggerScreenViewBase::tearDownScreen();
}

void DataLoggerScreenView::updateTriggerCurrent(bool status)
{
  if(status)
  {
    triggerCurrentText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
  }
  else if(0 == status)
  {
    triggerCurrentText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
  }
  

    triggerCurrentText.setVisible(true);
    triggerCurrentText.invalidate();
}

void DataLoggerScreenView::updateTriggerVoltage(bool status)
{
   if(status)
  {
    triggerVoltageText.setColor(touchgfx::Color::getColorFromRGB(34, 176, 76));
  }
  else if(0 == status)
  {
    triggerVoltageText.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
  }
  

    triggerVoltageText.setVisible(true);
    triggerVoltageText.invalidate();
}

void DataLoggerScreenView::updateLogStatus(bool status)
{
   if(status)
  {
    OFFLoggingLabel.setVisible(false);
    OFFLoggingLabel.invalidate();
    ONLoggingLabel.setVisible(true);
    ONLoggingLabel.invalidate();
  }
  else if(0 == status)
  {
    OFFLoggingLabel.setVisible(true);
    OFFLoggingLabel.invalidate();
    ONLoggingLabel.setVisible(false);
    ONLoggingLabel.invalidate();
  }
  
}

void DataLoggerScreenView::updateCurrent(uint16_t current)
{
 Unicode::snprintf(CurrentTextBuffer, CURRENTTEXT_SIZE, "%d", current);
}

void DataLoggerScreenView::updateVoltage(uint16_t voltage)
{
 Unicode::snprintf(VoltageTextBuffer, VOLTAGETEXT_SIZE, "%d", voltage);
}

void DataLoggerScreenView::updatePower(uint16_t current, uint16_t voltage)
{
 uint16_t power = (uint16_t)((uint32_t)current * voltage);
 static uint16_t powerPeak = 0;

 uint32_t lastTime = 0;
 uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;


    if ((currentTime - lastTime) < 60000)
    {
        powerPeak = 0;
        lastTime = currentTime; // aktualizujemy 
    }

    if(power > powerPeak)
    {
      powerPeak = power;
    }

 Unicode::snprintf(PowerTextBuffer, POWERTEXT_SIZE, "%d", powerPeak);
 PowerText.setVisible(true);
 PowerText.invalidate();
}