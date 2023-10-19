#include "movement/MovementController.h"

#include "esp_timer.h"

MovementController::MovementController(IHBridge &bridge) : _bridge(bridge) {
    _posX = 0;
    _posY = 0;
    _degrees = 0;
    _bridge.setMotorState(Motor::BOTH, 1);
}

MovementController::~MovementController() {}

void MovementController::moveFor(uint32_t millis, MovementDirection direction) {

    uint64_t micro = millis*1000;
    uint64_t time = esp_timer_get_time();

    if (direction == MovementDirection::BACKWARD) {
        _bridge.start(Motor::BOTH, MotorDirection::BACKWARD);
    } else {
        _bridge.start(Motor::BOTH, MotorDirection::FORWARD);
    }

    while (esp_timer_get_time() - time < micro)
        ;
    _bridge.stop(Motor::BOTH);
}

void MovementController::rotateFor(uint32_t millis,
                                   MovementDirection direction) {
    uint64_t micro = millis*1000;
    uint64_t time = esp_timer_get_time();

    if (direction == MovementDirection::LEFT) {
        _bridge.start(Motor::BOTH, MotorDirection::LEFT);
    } else {
        _bridge.start(Motor::BOTH, MotorDirection::RIGHT);
    }

    while (esp_timer_get_time() - time < micro)
        ;
    _bridge.stop(Motor::BOTH);
}
