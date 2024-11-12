#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>

#include <touchgfx/hal/HAL.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v) : view(v) {}

void MainScreenPresenter::activate() {}

void MainScreenPresenter::deactivate() {}

void MainScreenPresenter::setClock(uint32_t time) { view.updateClock(time); }

void MainScreenPresenter::setConnection(bool status) { view.updateConnection(status); }

void MainScreenPresenter::setWarning(bool status) { view.updateWarning(status); }

void MainScreenPresenter::setRadio(bool status) { view.updateRadio(status); }

void MainScreenPresenter::setReadyToDrive(bool status) { view.updateReadyToDrive(status); }

void MainScreenPresenter::setInvertersReady(bool status) { view.updateInvertersReady(status); }

void MainScreenPresenter::setBatteryLvTemperature(uint8_t temperature) { view.updateBatteryLvTemperature(temperature); }

void MainScreenPresenter::setInverterTemperature(uint8_t temperature) { view.updateInverterTemperature(temperature); }

void MainScreenPresenter:: setMotorFrontLeftTemperature(uint8_t temperature) { view.updateMotorFrontLeftTemperature(temperature); }

void MainScreenPresenter:: setMotorFrontRightTemperature(uint8_t temperature) { view.updateMotorFrontRightTemperature(temperature);}

void MainScreenPresenter:: setMotorRearLeftTemperature(uint8_t temperature) { view.updateMotorRearLeftTemperature(temperature); }

void MainScreenPresenter:: setMotorRearRightTemperature(uint8_t temperature) { view.updateMotorRearRightTemperature(temperature); }

void MainScreenPresenter::setOilTemperature(uint8_t temperature) { view.updateOilTemperature(temperature); }

void MainScreenPresenter::setOilPressure(uint8_t pressure) { view.updateOilPressure(pressure); }

void MainScreenPresenter::setCoolantTemperature(uint8_t temperature) { view.updateCoolantTemperature(temperature); }

void MainScreenPresenter::setCoolantPressure(uint8_t pressure) { view.updateCoolantPressure(pressure); }

void MainScreenPresenter::setRpm(uint16_t rpm) { view.updateRpm(rpm); }

void MainScreenPresenter::setCurrentLap(uint32_t time) { view.updateCurrentLap(time); }

void MainScreenPresenter::setLastLap(uint32_t time) { view.updateLastLap(time); }

void MainScreenPresenter::setBestLap(uint32_t time) { view.updateBestLap(time); }

void MainScreenPresenter::setSDC(SafetyData_TypeDef SafetyData)
{
	//Frontbox Safety
	view.updateSafetyFrontboxLeftKill(SafetyData.sense_left_kill);
	view.updateSafetyFrontboxRightKill(SafetyData.sense_right_kill);
	view.updateSafetyFrontboxDriverKill(SafetyData.sense_driver_kill);
	view.updateSafetyFrontboxInertia(SafetyData.sense_inertia);
	view.updateSafetyFrontboxBSPD(SafetyData.sense_bspd);
	view.updateSafetyFrontboxOvertravel(SafetyData.sense_overtravel);
	view.updateSafetyFrontboxRightWheel(SafetyData.sense_right_wheel);
	view.updateSafetyFrontboxIsBraking(SafetyData.is_braking);

	//RearBox Safety
	view.updateSafetyRearBoxRuf1(SafetyData.safety_rfu1);
	view.updateSafetyRearBoxRuf2(SafetyData.safety_rfu2);
	view.updateSafetyRearBoxAsms(SafetyData.safety_asms);
	view.updateSafetyRearBoxFw(SafetyData.safety_fw);
	view.updateSafetyRearBoxHv(SafetyData.safety_hv);
	view.updateSafetyRearBoxRes(SafetyData.safety_res);
	view.updateSafetyRearBoxHvd(SafetyData.safety_hvd);
	view.updateSafetyRearBoxInv(SafetyData.safety_inv);
	view.updateSafetyRearBoxWheelFl(SafetyData.safety_wheel_fl);
	view.updateSafetyRearBoxWheelFr(SafetyData.safety_wheel_fr);
	view.updateSafetyRearBoxWheelRl(SafetyData.safety_wheel_rl);
	view.updateSafetyRearBoxWheelRr(SafetyData.safety_wheel_rr);
}

void MainScreenPresenter::switchScreenMR()
{
	if(interfaceData.usr_button)
	{
		//FIXME: SPrawdizć czy ta zależność poprawnie działa i ewentualnie szuakć innego rozwiązania
		static_cast<FrontendApplication*>(Application::getInstance())->gotoRaceScreenScreenCoverTransitionSouth();
		interfaceData.usr_button = false;
	}
}


void MainScreenPresenter::toggleElements() { view.toggleWarning(); }
