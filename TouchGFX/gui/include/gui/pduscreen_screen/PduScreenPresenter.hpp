#ifndef PDUSCREENPRESENTER_HPP
#define PDUSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PduScreenView;

/**
 * @class PduScreenPresenter
 * @brief The Presenter for the PDU Screen View.
 *
 * This class acts as the mediator in the Model-View-Presenter (MVP) pattern
 * for the PDU screen. It is responsible for business logic, fetching data
 * from the Model (via ModelListener inheritance), and updating the View
 * (PduScreenView) with the received data.
 */
class PduScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    /**
     * @brief Constructor for PduScreenPresenter.
     * @param v A reference to the view object that this presenter will manage.
     */
    PduScreenPresenter(PduScreenView& v);

    /**
     * @brief Screen activation function.
     *
     * Called automatically when this screen is "switched in" (made active).
     * Initialization logic should be placed here, such as subscribing to Model
     * events or fetching initial data to display.
     */
    virtual void activate();

    /**
     * @brief Screen deactivation function.
     *
     * Called automatically when this screen is "switched out" (made inactive).
     * Teardown functionality should be placed here, such as unsubscribing from
     * Model events to prevent unnecessary updates.
     */
    virtual void deactivate();

    /**
     * @brief Virtual Destructor.
     */
    virtual ~PduScreenPresenter() {}

    /**
     * @brief Initiates a request to switch to the second PDU view screen.
     *
     * This method typically signals the framework's navigation controller to
     * perform a screen transition (e.g., to PduScreen2View/Presenter).
     */
    void switchScreenPdu2Vp();

    // The following methods act as event handlers/callbacks from the Model via the ModelListener interface.

    /**
     * @brief Sets the new current value for the PC load and updates the View.
     * @param current The new current value (e.g., in mA) received from the Model.
     */
    void setPduPcCurrent(uint32_t current);

    /**
     * @brief Sets the new current value for the Pump load and updates the View.
     * @param current The new current value (e.g., in mA) received from the Model.
     */
    void setPduPumpCurrent(uint32_t current);

    /**
     * @brief Sets the new current value for the Fan load and updates the View.
     * @param current The new current value (e.g., in mA) received from the Model.
     */
    void setPduFanCurrent(uint32_t current);

    /**
     * @brief Sets the new current value for the Inverter load and updates the View.
     * @param current The new current value (e.g., in mA) received from the Model.
     */
    void setPduInverterCurrent(uint32_t current);

    /**
     * @brief Sets the new current value for the Fbox load and updates the View.
     * @param current The new current value (e.g., in mA) received from the Model.
     */
    void setPduFboxCurrent(uint32_t current);

    /**
     * @brief Sets the new current value for the SDC load and updates the View.
     * @param current The new current value (e.g., in mA) received from the Model.
     */
    void setPduSdcCurrent(uint32_t current);

    /**
     * @brief Sets the new total current value for the PDU and updates the View.
     * @param current The new total current value (e.g., in mA) received from the Model.
     */
    void setPduTotalCurrent(uint32_t current);

private:
    /**
     * @brief Private default constructor.
     *
     * Prevents the creation of a PduScreenPresenter object without an associated View reference.
     */
    PduScreenPresenter();

    /**
     * @brief Reference to the View managed by this presenter.
     *
     * Used to call the update methods on the PduScreenView whenever new data
     * is received from the Model.
     */
    PduScreenView& view;
};

#endif // PDUSCREENPRESENTER_HPP