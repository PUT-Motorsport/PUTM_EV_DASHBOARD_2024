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
protected:
};

#endif // RACESCREENVIEW_HPP
