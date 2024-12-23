#include <gui/notificationscreen_screen/NotificationScreenPresenter.hpp>
#include <gui/notificationscreen_screen/NotificationScreenView.hpp>

NotificationScreenPresenter::NotificationScreenPresenter(NotificationScreenView& v) : view(v) {}

void NotificationScreenPresenter::activate() {screenStatus.NotificationScreen = true;}

void NotificationScreenPresenter::deactivate() {screenStatus.NotificationScreen = false;}

void NotificationScreenPresenter::setCheckErrors(bool bspd,
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
												 uint8_t motor_rr_temp){ view.updateCheckErrors(bspd,
														 	 	 	 	 	 	 	 	 	    inv_FL_temperature,
																								inv_FR_temperature,
																								inv_RL_temperature,
																								inv_RR_temperature,
																								lv_temp,
																								hv_temp,
																								lv_soc,
																								hv_soc,
																								motor_fl_temp,
																								motor_fr_temp,
																								motor_rl_temp,
																								motor_rr_temp); }
