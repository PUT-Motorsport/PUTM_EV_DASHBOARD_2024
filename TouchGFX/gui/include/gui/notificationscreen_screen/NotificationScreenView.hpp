#ifndef NOTIFICATIONSCREENVIEW_HPP
#define NOTIFICATIONSCREENVIEW_HPP

#include <gui/notificationscreen_screen/NotificationScreenPresenter.hpp>
#include <gui_generated/notificationscreen_screen/NotificationScreenViewBase.hpp>

class NotificationScreenView : public NotificationScreenViewBase {
  public:
    NotificationScreenView();
    virtual ~NotificationScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

  protected:
};

#endif  // NOTIFICATIONSCREENVIEW_HPP
