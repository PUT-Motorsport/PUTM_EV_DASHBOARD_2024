#ifndef VPSETTINGSSCREENVIEW_HPP
#define VPSETTINGSSCREENVIEW_HPP

#include <gui_generated/vpsettingsscreen_screen/VpSettingsScreenViewBase.hpp>
#include <gui/vpsettingsscreen_screen/VpSettingsScreenPresenter.hpp>

class VpSettingsScreenView : public VpSettingsScreenViewBase
{
public:
    VpSettingsScreenView();
    virtual ~VpSettingsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // VPSETTINGSSCREENVIEW_HPP
