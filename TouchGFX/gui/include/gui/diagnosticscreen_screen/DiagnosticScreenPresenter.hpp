#ifndef DIAGNOSTICSCREENPRESENTER_HPP
#define DIAGNOSTICSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DiagnosticScreenView;

class DiagnosticScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DiagnosticScreenPresenter(DiagnosticScreenView& v);

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

    virtual ~DiagnosticScreenPresenter() {}

    void switchScreenDiag2DataLog();

private:
    DiagnosticScreenPresenter();

    DiagnosticScreenView& view;
};

#endif // DIAGNOSTICSCREENPRESENTER_HPP
