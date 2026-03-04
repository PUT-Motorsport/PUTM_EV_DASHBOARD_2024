#ifndef BOOTSCREENVIEW_HPP
#define BOOTSCREENVIEW_HPP

#include <gui/bootscreen_screen/BootScreenPresenter.hpp>
#include <gui_generated/bootscreen_screen/BootScreenViewBase.hpp>

class BootScreenView : public BootScreenViewBase {
  public:
    BootScreenView();
    virtual ~BootScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

  protected:
};

#endif  // BOOTSCREENVIEW_HPP
