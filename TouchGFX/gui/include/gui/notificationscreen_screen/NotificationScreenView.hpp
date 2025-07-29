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
    */
    void updateCheckErrors(bool bspd, bool apps);



    /**
    * @brief Function responsible for starting the screen
    *
    * @param BSPD & APPS sensor status
    */
    void switchScreen(bool bspd_status, bool apps_status);

  protected:
};

#endif  // NOTIFICATIONSCREENVIEW_HPP
