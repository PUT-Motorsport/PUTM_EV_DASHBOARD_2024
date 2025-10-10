#ifndef DATALOGGERSCREENVIEW_HPP
#define DATALOGGERSCREENVIEW_HPP

#include <gui_generated/dataloggerscreen_screen/DataLoggerScreenViewBase.hpp>
#include <gui/dataloggerscreen_screen/DataLoggerScreenPresenter.hpp>

class DataLoggerScreenView : public DataLoggerScreenViewBase
{
public:
    DataLoggerScreenView();
    virtual ~DataLoggerScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DATALOGGERSCREENVIEW_HPP
