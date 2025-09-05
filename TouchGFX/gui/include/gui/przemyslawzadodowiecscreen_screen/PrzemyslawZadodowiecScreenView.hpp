#ifndef PRZEMYSLAWZADODOWIECSCREENVIEW_HPP
#define PRZEMYSLAWZADODOWIECSCREENVIEW_HPP

#include <gui_generated/przemyslawzadodowiecscreen_screen/PrzemyslawZadodowiecScreenViewBase.hpp>
#include <gui/przemyslawzadodowiecscreen_screen/PrzemyslawZadodowiecScreenPresenter.hpp>

class PrzemyslawZadodowiecScreenView : public PrzemyslawZadodowiecScreenViewBase
{
public:
    PrzemyslawZadodowiecScreenView();
    virtual ~PrzemyslawZadodowiecScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // PRZEMYSLAWZADODOWIECSCREENVIEW_HPP
