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

private:
    RaceScreenPresenter();

    RaceScreenView& view;
};

#endif // RACESCREENPRESENTER_HPP
