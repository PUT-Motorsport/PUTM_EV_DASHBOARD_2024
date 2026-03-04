#ifndef DATALOGGERSCREENPRESENTER_HPP
#define DATALOGGERSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DataLoggerScreenView;

class DataLoggerScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DataLoggerScreenPresenter(DataLoggerScreenView& v);

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

    virtual ~DataLoggerScreenPresenter() {}

    void switchScreenDataLog2Main();
    void setTriggerVoltage(bool status);
    void setTriggerCurrent(bool status);
    void setLogStatus(bool status);
    void setCurrent(uint16_t current);
    void setVoltage(uint16_t voltage);
    void setPower(uint16_t voltage, uint16_t current);

private:
    DataLoggerScreenPresenter();

    DataLoggerScreenView& view;
};

#endif // DATALOGGERSCREENPRESENTER_HPP
