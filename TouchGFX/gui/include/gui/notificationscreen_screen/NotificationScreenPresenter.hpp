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
         */
    virtual void setCheckErrors(bool bspd, bool apps);

  private:
    // Private default constructor to prevent unintended instantiation.
    NotificationScreenPresenter();

    NotificationScreenView& view;///< Reference to the notification screen view.
};

#endif  // NOTIFICATIONSCREENPRESENTER_HPP
