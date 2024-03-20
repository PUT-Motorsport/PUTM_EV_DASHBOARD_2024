#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::setClock(uint32_t time) {
    view.updateClock(time);
}

void MainScreenPresenter::setConnection(bool status) {
    view.updateConnection(status);
}

void MainScreenPresenter::setWarning(bool status) {
    view.updateWarning(status);
}

void MainScreenPresenter::setRadio(bool status) {
    view.updateRadio(status);
}

void MainScreenPresenter::setBatteryTemperature(uint8_t temperature) {
    view.updateBatteryTemperature(temperature);
}

void MainScreenPresenter::setInverterTemperature(uint8_t temperature) {
    view.updateInverterTemperature(temperature);
}

void MainScreenPresenter::setOilTemperature(uint8_t temperature) {
    view.updateOilTemperature(temperature);
}

void MainScreenPresenter::setOilPressure(uint8_t pressure) {
    view.updateOilPressure(pressure);
}

void MainScreenPresenter::setCoolantTemperature(uint8_t temperature) {
    view.updateCoolantTemperature(temperature);
}

void MainScreenPresenter::setCoolantPressure(uint8_t pressure) {
    view.updateCoolantPressure(pressure);
}

void MainScreenPresenter::setPace(int32_t pace) {
    view.updatePace(pace);
}

void MainScreenPresenter::setSpeed(uint8_t speed) {
    view.updateSpeed(speed);
}

void MainScreenPresenter::setSoc(uint8_t soc) {
    view.updateSoc(soc);
}

void MainScreenPresenter::setRpm(uint16_t rpm) {
    view.updateRpm(rpm);
}

void MainScreenPresenter::setPower(uint8_t power) {
    view.updatePower(power);
}

void MainScreenPresenter::setDistance(uint16_t distance) {
    view.updateDistance(distance);
}

void MainScreenPresenter::setRange(uint16_t range) {
    view.updateRange(range);
}

void MainScreenPresenter::setCurrentLap(uint32_t time) {
    view.updateCurrentLap(time);
}

void MainScreenPresenter::setLastLap(uint32_t time) {
    view.updateLastLap(time);
}

void MainScreenPresenter::setBestLap(uint32_t time) {
    view.updateBestLap(time);
}
