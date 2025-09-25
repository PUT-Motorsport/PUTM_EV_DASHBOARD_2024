#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>

#include <touchgfx/hal/HAL.hpp>
extern "C" 
{
#include "stm32u5xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "data.h"
}

uint32_t lastScreenSwitchMRTime = 0; ///< Global variable storing the time of the last screen switch (in milliseconds)

MainScreenPresenter::MainScreenPresenter(MainScreenView& v) : view(v) {}

void MainScreenPresenter::activate(){ screenStatus.MainScreen = true; }

void MainScreenPresenter::deactivate(){	screenStatus.MainScreen = false; }

void MainScreenPresenter::setClock(uint32_t time) { view.updateClock(time); }

void MainScreenPresenter::setConnection(bool status) { view.updateConnection(status); }

void MainScreenPresenter::setWarning(bool status) { view.updateWarning(status); }

void MainScreenPresenter::setRadio(bool status) { view.updateRadio(status); }

void MainScreenPresenter::setReadyToDrive(bool status) { view.updateReadyToDrive(status); }

void MainScreenPresenter::setInvertersStatus(bool inv_ready,
											 bool inv_FL_status,
											 bool inv_FR_status,
											 bool inv_RL_status,
											 bool inv_RR_status,
											 bool inv_FL_error,
											 bool inv_FR_error,
											 bool inv_RL_error,
											 bool inv_RR_error) { view.updateInvertersStatus(inv_ready,
													 	 	 	 	 	 	 	 	 	 	 inv_FL_status,
													 	 	 	 	 	 	 	 	 	 	 inv_FR_status,
																							 inv_RL_status,
																							 inv_RR_status,
																							 inv_FL_error,
																							 inv_FR_error,
																							 inv_RL_error,
																							 inv_RR_error); }

void MainScreenPresenter::setBatteryLVTemperature(uint8_t temperature) { view.updateBatteryLvTemperature(temperature); }

void MainScreenPresenter:: setMotorFrontLeftTemperature(uint8_t temperature) { view.updateMotorFrontLeftTemperature(temperature); }

void MainScreenPresenter:: setMotorFrontRightTemperature(uint8_t temperature) { view.updateMotorFrontRightTemperature(temperature);}

void MainScreenPresenter:: setMotorRearLeftTemperature(uint8_t temperature) { view.updateMotorRearLeftTemperature(temperature); }

void MainScreenPresenter:: setMotorRearRightTemperature(uint8_t temperature) { view.updateMotorRearRightTemperature(temperature); }

void MainScreenPresenter::setFrontBrakePressure(uint16_t pressure) { view.updateFrontBrakePressure(pressure); }

void MainScreenPresenter::setCoolantInTemperature(uint8_t temperature) { view.updateCoolantInTemperature(temperature); }

void MainScreenPresenter::setCoolantOutTemperature(uint8_t temperature) { view.updateCoolantOutTemperature(temperature); }

void MainScreenPresenter::setRearBrakePressure(uint16_t pressure) { view.updateRearBrakePressure(pressure); }

void MainScreenPresenter::setInverterTemperature(uint8_t inv_FL_temperature,
												 uint8_t inv_FR_temperature,
												 uint8_t inv_RL_temperature,
												 uint8_t inv_RR_temperature) { view.updateInverterTemperature(inv_FL_temperature,
														 	 	 	 	 	 	 	 	 	 	 	 	 	  inv_FR_temperature,
																											  inv_RL_temperature,
																											  inv_RR_temperature); }

void MainScreenPresenter::setSDC(SafetyData_TypeDef status) {view.updateSDC(status);}

void MainScreenPresenter::setRtdButtonPressed(bool status) {view.updateRtdButtonPressed(status);}

void MainScreenPresenter::setTsaButtonPressed(bool status) {view.updateTsaButtonPressed(status);}

void MainScreenPresenter::setPduPcStatus(uint8_t status) {view.updatePduPcStatus(status);}

void MainScreenPresenter::setPduFanStatus(uint8_t status) {view.updatePduFanStatus(status);}

void MainScreenPresenter::setPduPumpStatus(uint8_t status) {view.updatePduPumpStatus(status);}

void MainScreenPresenter::setPduInverterStatus(uint8_t status) {view.updatePduInverterStatus(status);}

void MainScreenPresenter::setPduFboxStatus(uint8_t status) {view.updatePduFboxStatus(status);}

void MainScreenPresenter::setPduSdcStatus(uint8_t status) {view.updatePduSdcStatus(status);}

void MainScreenPresenter::setPduDashStatus(uint8_t status) {view.updatePduDashStatus(status);}

void MainScreenPresenter::setPduTsalStatus(uint8_t status) {view.updatePduTsalStatus(status);}

void MainScreenPresenter::setPduRboxStatus(uint8_t status) {view.updatePduRboxStatus(status);}

void MainScreenPresenter::setPduAirStatus(uint8_t status) {view.updatePduAirStatus(status);}


void MainScreenPresenter::toggleElements() { view.toggleWarning(); }

void MainScreenPresenter::switchScreenMain2Race()
{

    static uint8_t previousButtonState = 0;
    uint8_t currentButtonState = interfaceData.cs_button;
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    if ((currentTime - lastScreenSwitchMRTime) < 1000)
    {
        previousButtonState = currentButtonState;
        return;
    }

    if (screenStatus.MainScreen && (previousButtonState == 1) && (currentButtonState == 0))
    {
        static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenNoTransition();
        screenStatus.MainScreen = false;
        lastScreenSwitchMRTime = currentTime;
    }

    previousButtonState = currentButtonState;
}

