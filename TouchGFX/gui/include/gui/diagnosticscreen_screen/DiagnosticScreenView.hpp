#ifndef DIAGNOSTICSCREENVIEW_HPP
#define DIAGNOSTICSCREENVIEW_HPP

#include <gui_generated/diagnosticscreen_screen/DiagnosticScreenViewBase.hpp>
#include <gui/diagnosticscreen_screen/DiagnosticScreenPresenter.hpp>

class DiagnosticScreenView : public DiagnosticScreenViewBase
{
public:
    DiagnosticScreenView();
    virtual ~DiagnosticScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DIAGNOSTICSCREENVIEW_HPP
