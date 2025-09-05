#ifndef PDUSCREENVIEW_HPP
#define PDUSCREENVIEW_HPP

#include <gui_generated/pduscreen_screen/PduScreenViewBase.hpp>
#include <gui/pduscreen_screen/PduScreenPresenter.hpp>

class PduScreenView : public PduScreenViewBase
{
public:
    PduScreenView();
    virtual ~PduScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // PDUSCREENVIEW_HPP
