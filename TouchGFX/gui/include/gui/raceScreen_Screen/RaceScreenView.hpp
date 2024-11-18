#ifndef RACESCREENVIEW_HPP
#define RACESCREENVIEW_HPP

#include <gui_generated/racescreen_screen/RaceScreenViewBase.hpp>
#include <gui/racescreen_screen/RaceScreenPresenter.hpp>

class RaceScreenView : public RaceScreenViewBase
{
public:
    RaceScreenView();
    virtual ~RaceScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateReadyToDrive(bool status);
    void updateInvertersReady(bool status);
    void updateSocLv(uint8_t soc);
    void updateSocHv(uint8_t soc);
    void updateTempHv(uint8_t temperature);
    void updateInverterTemperature(uint8_t temperature);
    void updatePace(int32_t pace);
    void updateRange(uint16_t range);
    void updateMotorTemp(uint8_t temperatureMotorFL,
    					 uint8_t temperatureMotorFR,
						 uint8_t temperatureMotorRL,
						 uint8_t temperatureMotorRR);
    void updateLap(uint8_t value);
protected:
};

#endif // RACESCREENVIEW_HPP
