#ifndef PDUSCREENVIEW_HPP
#define PDUSCREENVIEW_HPP

#include <gui_generated/pduscreen_screen/PduScreenViewBase.hpp>
#include <gui/pduscreen_screen/PduScreenPresenter.hpp>

/**
 * @class PduScreenView
 * @brief Represents the graphical user interface (View) for displaying PDU current data.
 *
 * This class handles the visualization of current readings from a Power Distribution Unit (PDU).
 * It inherits from PduScreenViewBase, which contains the auto-generated UI elements
 * (like text areas, gauges, etc.) defined in the TouchGFX Designer.
 *
 * It provides methods for screen lifecycle management and asynchronous data updates
 * from the associated Presenter.
 */
class PduScreenView : public PduScreenViewBase
{
public:
    /**
     * @brief Constructor.
     *
     * Initializes a new instance of the PduScreenView.
     */
    PduScreenView();

    /**
     * @brief Virtual Destructor.
     *
     * Ensures proper cleanup and resource release when the view is destroyed.
     */
    virtual ~PduScreenView() {}

    /**
     * @brief Sets up and initializes the screen.
     *
     * This method is automatically called when the screen is entered. It's used
     * to perform any necessary custom initialization of the UI elements beyond
     * what's done in the base class.
     */
    virtual void setupScreen();

    /**
     * @brief Tears down and cleans up the screen.
     *
     * This method is automatically called when the screen is exited. It's used
     * to perform any necessary cleanup, such as resetting animations or stopping
     * timers.
     */
    virtual void tearDownScreen();

    /**
     * @brief Updates the displayed current for the PDU's PC (Computer) load.
     * @param current The current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduPcCurrent(uint32_t current);

    /**
     * @brief Updates the displayed current for the PDU's Pump load.
     * @param current The current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduPumpCurrent(uint32_t current);

    /**
     * @brief Updates the displayed current for the PDU's Fan load.
     * @param current The current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduFanCurrent(uint32_t current);

    /**
     * @brief Updates the displayed current for the PDU's Inverter load.
     * @param current The current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduInverterCurrent(uint32_t current);

    /**
     * @brief Updates the displayed current for the PDU's Fbox load.
     * @param current The current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduFboxCurrent(uint32_t current);

    /**
     * @brief Updates the displayed current for the PDU's SDC (Safety Disconnect Circuit) load.
     * @param current The current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduSdcCurrent(uint32_t current);

    /**
     * @brief Updates the displayed total current draw for the entire PDU.
     * @param current The total current value (e.g., in mA) to be displayed in the UI.
     */
    void updatePduTotalCurrent(uint32_t current);

protected:
    // Any protected members specific to this view implementation would go here.
};

#endif // PDUSCREENVIEW_HPP
