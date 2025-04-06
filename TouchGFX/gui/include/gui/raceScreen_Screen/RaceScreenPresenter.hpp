/**
 * @file RaceScreenPresenter.hpp
 * @brief Declaration of the RaceScreenPresenter class.
 *
 * The RaceScreenPresenter class handles the logic for the race screen.
 * It implements the ModelListener interface to receive updates from the Model.
 */


#ifndef RACESCREENPRESENTER_HPP
#define RACESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RaceScreenView;

/**
 * @brief Presenter for the race screen.
*/

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

    /**
     * @brief Sets the ready-to-drive status.
     * @param status True if the vehicle is ready to drive, false otherwise.
     */
    void setReadyToDrive(bool status);


    /**
     * @brief Sets the DRS status.
     * @param status DRS system status.
     */
    void setDrsStatus(bool status);


    /**
     * @brief Sets the low-voltage battery SOC.
     * @param soc State Of Charge value.
     */
    void setSocLv(uint8_t soc);

    /**
     * @brief Sets the high-voltage battery SOC.
     * @param soc State Of Charge value.
     */
    void setSocHv(uint8_t soc);

    /**
     * @brief Sets the high-voltage battery temperature.
     * @param temperature Temperature of the high-voltage battery.
     */
    void setBatteryHVTemperature(uint8_t temperature);



    /**
     * @brief Sets the inverter temperatures.
     * @param inv_FL_temperature Temperature of the front left inverter.
     * @param inv_FR_temperature Temperature of the front right inverter.
     * @param inv_RL_temperature Temperature of the rear left inverter.
     * @param inv_RR_temperature Temperature of the rear right inverter.
     */
    void setInverterTemperature(uint8_t inv_FL_temperature,
								uint8_t inv_FR_temperature,
								uint8_t inv_RL_temperature,
								uint8_t inv_RR_temperature);



    /**
     * @brief Sets the race pace.
     * @param pace Race pace in system units.
     */
    void setPace(int16_t pace);



    /**
     * @brief Sets the engine temperatures.
     * @param temperatureMotorFL Temperature of the front left motor.
     * @param temperatureMotorFR Temperature of the front right motor.
     * @param temperatureMotorRL Temperature of the rear left motor.
     * @param temperatureMotorRR Temperature of the rear right motor.
     */
    void setMotorTemp(uint8_t temperatureMotorFL,
			   uint8_t temperatureMotorFR,
			   uint8_t temperatureMotorRL,
			   uint8_t temperatureMotorRR);

    /**
     * @brief Sets the lap number.
     * @param value Current lap number.
     */
    void setLap(uint8_t value);

    /**
     * @brief Sets the best lap time.
     * @param time Best lap time in milliseconds.
     */
    void setBestLap(uint32_t time);


    /**
     * @brief Switches from the race screen back to the main screen.
     */
    void switchScreenRM();

private:
    // Private default constructor to prevent unintended instantiation.
    RaceScreenPresenter();

    RaceScreenView& view; ///< Reference to the race screen view.
};

#endif // RACESCREENPRESENTER_HPP
