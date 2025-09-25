#ifndef VPSETTINGSSCREENPRESENTER_HPP
#define VPSETTINGSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class VpSettingsScreenView;

class VpSettingsScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    VpSettingsScreenPresenter(VpSettingsScreenView& v);

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

    virtual ~VpSettingsScreenPresenter() {}

    void switchScreenVp2Diag();

private:
    VpSettingsScreenPresenter();

    VpSettingsScreenView& view;
};

#endif // VPSETTINGSSCREENPRESENTER_HPP
