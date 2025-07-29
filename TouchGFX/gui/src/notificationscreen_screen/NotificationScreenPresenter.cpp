#include <gui/notificationscreen_screen/NotificationScreenPresenter.hpp>
#include <gui/notificationscreen_screen/NotificationScreenView.hpp>

NotificationScreenPresenter::NotificationScreenPresenter(NotificationScreenView& v) : view(v) {}

void NotificationScreenPresenter::activate() {screenStatus.NotificationScreen = true;}

void NotificationScreenPresenter::deactivate() {screenStatus.NotificationScreen = false;}

void NotificationScreenPresenter::setCheckErrors(bool bspd, bool apps){ view.updateCheckErrors(bspd, apps); }

void NotificationScreenPresenter::switchScreen(bool bspd_status, bool apps_status)
{
 if(bspd_status || apps_status)
 {
	 setCheckErrors(bspd_status, apps_status);
 }
}
