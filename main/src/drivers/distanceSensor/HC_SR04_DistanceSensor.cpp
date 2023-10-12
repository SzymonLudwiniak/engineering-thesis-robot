#include "drivers/distanceSensor/HC_SR04_DistanceSensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

HC_SR04_DistanceSensor::HC_SR04_DistanceSensor(IGPIO &echo, IGPIO &trigger)
    : _echo(echo), _trigger(trigger) {
    _delay = 0;
    _time = 0;

    _trigger.setLevel(0);
}

HC_SR04_DistanceSensor::~HC_SR04_DistanceSensor() {}

uint16_t HC_SR04_DistanceSensor::calculateDistanceCm() {
    _trigger.setLevel(1);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    _trigger.setLevel(0);

    while (_echo.getLevel() == 0) {
    }
    
    _time = esp_timer_get_time();

    while (_echo.getLevel() == 1) {
    }
    _delay = esp_timer_get_time() - _time;

    return static_cast<uint16_t>(_delay / 58); 
}
