#ifndef BOOTSCREENVIEW_HPP
#define BOOTSCREENVIEW_HPP

#include <gui_generated/bootscreen_screen/BootScreenViewBase.hpp>
#include <gui/bootscreen_screen/BootScreenPresenter.hpp>

class BootScreenView : public BootScreenViewBase
{
public:
    BootScreenView();
    virtual ~BootScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BOOTSCREENVIEW_HPP
