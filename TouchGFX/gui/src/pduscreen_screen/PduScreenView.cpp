#include <gui/pduscreen_screen/PduScreenView.hpp>

PduScreenView::PduScreenView()
{

}

void PduScreenView::setupScreen()
{
    PduScreenViewBase::setupScreen();
}

void PduScreenView::tearDownScreen()
{
    PduScreenViewBase::tearDownScreen();
}

//dodać funkcje pokazujące stan kanału

void PduScreenView::updatePduPcCurrent(uint32_t current)
{
    Unicode::snprintf(PcCurrentTextBuffer, PCCURRENTTEXT_SIZE, "%d", current);
    PcCurrentText.invalidate();
    PcCurrentText.setVisible(true);
}

void PduScreenView::updatePduPumpCurrent(uint32_t current)
{
    Unicode::snprintf(PumpCurrentTextBuffer, PUMPCURRENTTEXT_SIZE, "%d", current);
    PumpCurrentText.invalidate();
    PumpCurrentText.setVisible(true);
}


void PduScreenView::updatePduFanCurrent(uint32_t current)
{
    Unicode::snprintf(FanCurrentTextBuffer, FANCURRENTTEXT_SIZE, "%d", current);
    FanCurrentText.invalidate();
    FanCurrentText.setVisible(true);
}

void PduScreenView::updatePduInverterCurrent(uint32_t current)
{
    Unicode::snprintf(InvCurrentTextBuffer, INVCURRENTTEXT_SIZE, "%d", current);
    InvCurrentText.invalidate();
    InvCurrentText.setVisible(true);
        
}

void PduScreenView::updatePduFboxCurrent(uint32_t current)
{
    Unicode::snprintf(FboxCurrentTextBuffer, FBOXCURRENTTEXT_SIZE, "%d", current);
    FboxCurrentText.invalidate();
    FboxCurrentText.setVisible(true);
}

void PduScreenView::updatePduSdcCurrent(uint32_t current)
{
    Unicode::snprintf(SdcCurrentTextBuffer, SDCCURRENTTEXT_SIZE, "%d", current);
    SdcCurrentText.invalidate();
    SdcCurrentText.setVisible(true);
}


void PduScreenView::updatePduTotalCurrent(uint32_t current)
{
    Unicode::snprintf(TotalCurrentValueTextBuffer, TOTALCURRENTVALUETEXT_SIZE, "%d", current);
    TotalCurrentValueText.invalidate();
    TotalCurrentValueText.setVisible(true);
}