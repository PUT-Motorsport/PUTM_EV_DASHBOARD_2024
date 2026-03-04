/**
 * @file RaceScreenView.hpp
 * @brief Declaration of the RaceScreenView class.
 *
 * The RaceScreenView class defines the user interface for the race screen.
 * It includes methods for updating various UI elements.
 */

#ifndef RACESCREENVIEW_HPP
#define RACESCREENVIEW_HPP

#include <gui_generated/racescreen_screen/RaceScreenViewBase.hpp>
#include <gui/racescreen_screen/RaceScreenPresenter.hpp>


/**
 * @brief View for the race screen.
 */
class RaceScreenView : public RaceScreenViewBase
{
public:
    /**
     * @brief Constructor.
     */
    RaceScreenView();

    /**
     * @brief Destructor.
     */
    virtual ~RaceScreenView() {}

    /**
     * @brief Sets up the race screen.
     */
    virtual void setupScreen();

    /**
     * @brief Tears down the race screen.
     */
    virtual void tearDownScreen();


    /**
     * @brief Updates the ready-to-drive indicator.
     * @param status True if the vehicle is ready to drive, false otherwise.
     */
    void updateReadyToDrive(bool status);

    /**
     * @brief Updates the DRS status indicator.
     * @param status DRS system status.
     */
    void updateDrsStatus(bool status);

    /**
     * @brief Updates the low-voltage battery SOC.
     * @param soc State Of Charge value.
     */
    void updateSocLv(uint8_t soc);


    /**
     * @brief Updates the high-voltage battery SOC.
     * @param soc State Of Charge value.
     */
    void updateSocHv(uint8_t soc);

    /**
     * @brief Updates the high-voltage battery temperature.
     * @param temperature Battery temperature.
     */
    void updateBatteryHVTemperature(uint8_t temperature);


    /**
     * @brief Updates the inverter temperatures.
     * @param inv_FL_temperature Temperature of the front left inverter.
     * @param inv_FR_temperature Temperature of the front right inverter.
     * @param inv_RL_temperature Temperature of the rear left inverter.
     * @param inv_RR_temperature Temperature of the rear right inverter.
     */
    void updateInverterTemperature(uint8_t inv_FL_temperature,
			   	   	   	   	   	   uint8_t inv_FR_temperature,
								   uint8_t inv_RL_temperature,
								   uint8_t inv_RR_temperature);

    /**
     * @brief Updates the engine temperatures.
     * @param temperatureMotorFL Temperature of the front left motor.
     * @param temperatureMotorFR Temperature of the front right motor.
     * @param temperatureMotorRL Temperature of the rear left motor.
     * @param temperatureMotorRR Temperature of the rear right motor.
     */
    void updateMotorTemp(uint8_t temperatureMotorFL,
    					 uint8_t temperatureMotorFR,
						 uint8_t temperatureMotorRL,
						 uint8_t temperatureMotorRR);

    /**
     * @brief Updates the race pace.
     * @param pace Race pace in system units.
     */
    void updatePace(int16_t pace);

    /**
     * @brief Updates the lap number.
     * @param value Lap number.
     */
    void updateLap(uint8_t value);

    /**
     * @brief Updates the best lap time.
     * @param time Best lap time in milliseconds.
     */
    void updateBestLap(uint32_t time);
protected:
};

#endif // RACESCREENVIEW_HPP
