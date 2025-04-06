/**
 * @file NotificationScreenView.hpp
 * @brief Declaration of the NotificationScreenView class.
 *
 * The NotificationScreenView class defines the user interface for the notification screen.
 * It provides methods for updating the error notifications and toggling the display.
 */

#ifndef NOTIFICATIONSCREENVIEW_HPP
#define NOTIFICATIONSCREENVIEW_HPP

#include <gui/notificationscreen_screen/NotificationScreenPresenter.hpp>
#include <gui_generated/notificationscreen_screen/NotificationScreenViewBase.hpp>


/**
 * @brief View for the notification screen.
 */
class NotificationScreenView : public NotificationScreenViewBase {
  public:

    /**
     * @brief Constructor.
     */
    NotificationScreenView();


    /**
     * @brief Destructor.
     */
    virtual ~NotificationScreenView() {}

    /**
     * @brief Sets up the notification screen.
     */
    virtual void setupScreen();

    /**
     * @brief Tears down the notification screen.
     */
    virtual void tearDownScreen();


    /**
         * @brief Updates the notification view based on system error checks.
         *
         * @param bspd BSPD sensor status.
         * @param inv_FL_temperature Temperature of the front left inverter.
         * @param inv_FR_temperature Temperature of the front right inverter.
         * @param inv_RL_temperature Temperature of the rear left inverter.
         * @param inv_RR_temperature Temperature of the rear right inverter.
         * @param lv_temp Low-voltage battery temperature.
         * @param hv_temp High-voltage battery temperature.
         * @param lv_soc Low-voltage battery SOC.
         * @param hv_soc High-voltage battery SOC.
         * @param motor_fl_temp Temperature of the front left motor.
         * @param motor_fr_temp Temperature of the front right motor.
         * @param motor_rl_temp Temperature of the rear left motor.
         * @param motor_rr_temp Temperature of the rear right motor.
         */
    void updateCheckErrors(bool bspd,
	   	   	   	   	   	   uint8_t inv_FL_temperature,
						   uint8_t inv_FR_temperature,
						   uint8_t inv_RL_temperature,
						   uint8_t inv_RR_temperature,
						   uint8_t lv_temp,
						   uint8_t hv_temp,
						   uint8_t lv_soc,
						   uint8_t hv_soc,
						   uint8_t motor_fl_temp,
						   uint8_t motor_fr_temp,
						   uint8_t motor_rl_temp,
						   uint8_t motor_rr_temp);

    /**
     * @brief Toggles the notification screen view.
     */
    void toggleScreen();

  protected:
};

#endif  // NOTIFICATIONSCREENVIEW_HPP
