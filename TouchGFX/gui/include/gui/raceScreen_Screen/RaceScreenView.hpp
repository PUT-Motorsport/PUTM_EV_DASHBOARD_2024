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
    void updateDrsStatus(bool status);
    void updateSocLv(uint8_t soc);
    void updateSocHv(uint8_t soc);
    void updateBatteryHVTemperature(uint8_t temperature);
    void updateInverterTemperature(uint8_t inv_FL_temperature,
			   	   	   	   	   	   uint8_t inv_FR_temperature,
								   uint8_t inv_RL_temperature,
								   uint8_t inv_RR_temperature);
    void updateMotorTemp(uint8_t temperatureMotorFL,
    					 uint8_t temperatureMotorFR,
						 uint8_t temperatureMotorRL,
						 uint8_t temperatureMotorRR);
    void updatePace(int16_t pace);
    void updateLap(uint8_t value);
    void updateBestLap(uint32_t time);
protected:
};

#endif // RACESCREENVIEW_HPP
