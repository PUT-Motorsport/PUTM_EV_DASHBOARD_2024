/**
 * @file MainScreenView.hpp
 * @brief Declaration of the MainScreenView class.
 *
 * The MainScreenView class defines the user interface for the main screen.
 * It includes methods for updating various UI elements such as clock, connection status,
 * warnings, temperatures, pressures, and more.
 */

#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <array>


/**
 * @brief View for the main screen.
 */
class MainScreenView : public MainScreenViewBase {
  public:

    /**
     * @brief Constructor.
     */
    MainScreenView();

    /**
     * @brief Destructor.
     */
    virtual ~MainScreenView() {}

    /**
     * @brief Sets up the main screen.
     */
    virtual void setupScreen();

    /**
     * @brief Tears down the main screen.
     */
    virtual void tearDownScreen();


    // Methods to update UI elements:
    void updateClock(uint32_t time);
    void updateConnection(bool status);
    void updateWarning(bool status);
    void updateRadio(bool status);
    void updateReadyToDrive(bool status);
    void updateInvertersStatus(bool inv_ready,
    						  bool inv_FL_status,
    						  bool inv_FR_status,
							  bool inv_RL_status,
							  bool inv_RR_status,
							  bool inv_FL_error,
							  bool inv_FR_error,
							  bool inv_RL_error,
							  bool inv_RR_error);
    void updateBatteryLvTemperature(uint8_t temperature);
    void updateBatteryHvTemperature(uint8_t temperature);
    void updateInverterTemperature(uint8_t inv_FL_temperature,
								   uint8_t inv_FR_temperature,
								   uint8_t inv_RL_temperature,
								   uint8_t inv_RR_temperature);
    void updateMotorFrontLeftTemperature(uint8_t temperature);
    void updateMotorFrontRightTemperature(uint8_t temperature);
    void updateMotorRearLeftTemperature(uint8_t temperature);
    void updateMotorRearRightTemperature(uint8_t temperature);
    void updateOilTemperature(uint8_t temperature);
    void updateRearBrakePressure(uint16_t pressure);
    void updateCoolantInTemperature(uint8_t temperature);
    void updateCoolantOutTemperature(uint8_t temperature);
    void updateFrontBrakePressure(uint16_t pressure);
    void updateRtdButtonPressed(bool status);
    void updateTsaButtonPressed(bool status);

    void updatePduPcStatus(uint8_t status);
    void updatePduFanStatus(uint8_t status);
    void updatePduPumpStatus(uint8_t status);
    void updatePduInverterStatus(uint8_t status);
    void updatePduFboxStatus(uint8_t status);
    void updatePduSdcStatus(uint8_t status);
    void updatePduDashStatus(uint8_t status);
    void updatePduTsalStatus(uint8_t status);
    void updatePduRboxStatus(uint8_t status);
    void updatePduAirStatus(uint8_t status);


    /**
     * @brief Toggles the warning display.
     */
    void toggleWarning();

    /**
     * @brief Displays an error message.
     * @param error_idx The index of the error.
     */
    void displayError(int error_idx);

    /**
     * @brief Updates the safety display (SDC) based on the given status.
     * @param status Structure containing the safety data.
     */
    void updateSDC(SafetyData_TypeDef status);

  protected:
  private:
    unsigned int m_time; ///< Helper variable for toggling warnings.
    bool m_warning; ///< Flag indicating the warning status.
};

#endif  // MAINSCREENVIEW_HPP
