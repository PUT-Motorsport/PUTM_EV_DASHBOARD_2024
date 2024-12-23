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

  protected:
};

#endif  // NOTIFICATIONSCREENVIEW_HPP
