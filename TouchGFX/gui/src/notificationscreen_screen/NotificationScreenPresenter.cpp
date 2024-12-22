#include <gui/notificationscreen_screen/NotificationScreenPresenter.hpp>
#include <gui/notificationscreen_screen/NotificationScreenView.hpp>

NotificationScreenPresenter::NotificationScreenPresenter(NotificationScreenView& v) : view(v) {}

void NotificationScreenPresenter::activate() {screenStatus.NotificationScreen = true;}

void NotificationScreenPresenter::deactivate() {screenStatus.NotificationScreen = false;}

void NotificationScreenPresenter::setCheckErrors(){ view.updateCheckErrors(); }
