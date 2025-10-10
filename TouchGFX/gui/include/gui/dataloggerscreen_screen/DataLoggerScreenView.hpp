#ifndef DATALOGGERSCREENVIEW_HPP
#define DATALOGGERSCREENVIEW_HPP

#include <gui_generated/dataloggerscreen_screen/DataLoggerScreenViewBase.hpp>
#include <gui/dataloggerscreen_screen/DataLoggerScreenPresenter.hpp>

extern "C" 
{
#include "stm32u5xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "data.h"
}

class DataLoggerScreenView : public DataLoggerScreenViewBase
{
public:
    DataLoggerScreenView();
    virtual ~DataLoggerScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateTriggerVoltage(bool status);
    void updateTriggerCurrent(bool status);
    void updateLogStatus(bool status);
    void updateCurrent(uint16_t current);
    void updateVoltage(uint16_t voltage);
    void updatePower(uint16_t voltage, uint16_t current);
protected:
};

#endif // DATALOGGERSCREENVIEW_HPP
