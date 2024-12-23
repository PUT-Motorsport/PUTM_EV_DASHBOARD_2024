#ifndef NOTIFICATIONSCREENPRESENTER_HPP
#define NOTIFICATIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class NotificationScreenView;

class NotificationScreenPresenter : public touchgfx::Presenter, public ModelListener {
  public:
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
    NotificationScreenPresenter();

    NotificationScreenView& view;
};

#endif  // NOTIFICATIONSCREENPRESENTER_HPP
