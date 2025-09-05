#ifndef PRZEMYSLAWZADODOWIECSCREENPRESENTER_HPP
#define PRZEMYSLAWZADODOWIECSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PrzemyslawZadodowiecScreenView;

class PrzemyslawZadodowiecScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PrzemyslawZadodowiecScreenPresenter(PrzemyslawZadodowiecScreenView& v);

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

    virtual ~PrzemyslawZadodowiecScreenPresenter() {}

private:
    PrzemyslawZadodowiecScreenPresenter();

    PrzemyslawZadodowiecScreenView& view;
};

#endif // PRZEMYSLAWZADODOWIECSCREENPRESENTER_HPP
