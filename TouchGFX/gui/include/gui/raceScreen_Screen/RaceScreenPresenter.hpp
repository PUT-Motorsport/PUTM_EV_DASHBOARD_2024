#ifndef RACESCREENPRESENTER_HPP
#define RACESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RaceScreenView;

class RaceScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    RaceScreenPresenter(RaceScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~RaceScreenPresenter() {}

    void setReadyToDrive(bool status);
    void setInvertersReady(bool status);
    void setSocLv(uint8_t soc);
    void setSocHv(uint8_t soc);
    void setTempHv(uint8_t temperature);
    void setInverterTemperature(uint8_t temperature);
    void setPace(int32_t pace);
    void setRange(uint16_t range);
    void setMotorTemp(uint8_t temperatureMotorFL,
			   uint8_t temperatureMotorFR,
			   uint8_t temperatureMotorRL,
			   uint8_t temperatureMotorRR);
    void switchScreenRM();

private:
    RaceScreenPresenter();

    RaceScreenView& view;
};

#endif // RACESCREENPRESENTER_HPP
