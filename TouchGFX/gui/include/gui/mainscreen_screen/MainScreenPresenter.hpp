#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainScreenView;

class MainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainScreenPresenter(MainScreenView& v);

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

    virtual ~MainScreenPresenter() {}

    void setClock(uint32_t time);
    void setConnection(bool status);
    void setWarning(bool status);
    void setRadio(bool status);
    void setBatteryTemperature(uint8_t temperature);
    void setInverterTemperature(uint8_t temperature);
    void setOilTemperature(uint8_t temperature);
    void setOilPressure(uint8_t pressure);
    void setCoolantTemperature(uint8_t temperature);
    void setCoolantPressure(uint8_t pressure);
    void setPace(int32_t pace);
    void setSpeed(uint8_t speed);
    void setSoc(uint8_t soc);
    void setRpm(uint16_t rpm);
    void setPower(uint8_t power);
    void setDistance(uint16_t distance);
    void setRange(uint16_t range);
    void setCurrentLap(uint32_t time);
    void setLastLap(uint32_t time);
    void setBestLap(uint32_t time);

    void toggleElements();

    void setToggleWarning(bool toggle);

private:
    MainScreenPresenter();

    MainScreenView& view;

    unsigned int m_time;
    bool m_toggleWarning;
};

#endif // MAINSCREENPRESENTER_HPP
