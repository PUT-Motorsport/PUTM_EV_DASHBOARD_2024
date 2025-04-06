/**
 * @file NotificationScreenPresenter.hpp
 * @brief Declaration of the NotificationScreenPresenter class.
 *
 * The NotificationScreenPresenter class handles the logic for the notification screen.
 * It responds to system error checks and updates the notification view accordingly.
 */

#ifndef NOTIFICATIONSCREENPRESENTER_HPP
#define NOTIFICATIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class NotificationScreenView;


/**
 * @brief Presenter for the notification screen.
 */
class NotificationScreenPresenter : public touchgfx::Presenter, public ModelListener {
  public:

    /**
     * @brief Constructor.
     * @param v Reference to the notification screen view.
     */
    NotificationScreenPresenter(NotificationScreenView& v);

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

    virtual ~NotificationScreenPresenter() {}


    /**
         * @brief Checks system errors and updates the notification view.
         *
         * This method analyzes various system parameters and determines whether
         * any errors exist that require user notification.
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
    virtual void setCheckErrors(bool bspd,
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

  private:
    // Private default constructor to prevent unintended instantiation.
    NotificationScreenPresenter();

    NotificationScreenView& view;///< Reference to the notification screen view.
};

#endif  // NOTIFICATIONSCREENPRESENTER_HPP
