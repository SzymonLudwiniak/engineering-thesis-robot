#include "movement/MovementController.h"

#include <cmath>
#define _USE_MATH_DEFINES

#include "esp_timer.h"

MovementController::MovementController(IHBridge &bridge)
    : _bridge(bridge), _pose{0, 0, 0} {
    _bridge.setMotorState(Motor::BOTH, 1);
}

MovementController::~MovementController() {}

void MovementController::moveFor(uint32_t millis, MovementDirection direction) {
    uint64_t micro = millis * 1000;
    uint64_t time = esp_timer_get_time();

    if (direction == MovementDirection::BACKWARD) {
        _bridge.start(Motor::BOTH, MotorDirection::BACKWARD);
    } else {
        _bridge.start(Motor::BOTH, MotorDirection::FORWARD);
    }

    while (esp_timer_get_time() - time < micro)
        ;
    _bridge.stop(Motor::BOTH);
    recalculatePosition(millis);
}

void MovementController::rotateFor(uint32_t millis,
                                   MovementDirection direction) {
    uint64_t micro = millis * 1000;
    uint64_t time = esp_timer_get_time();

    if (direction == MovementDirection::LEFT) {
        _bridge.start(Motor::BOTH, MotorDirection::LEFT);
    } else {
        _bridge.start(Motor::BOTH, MotorDirection::RIGHT);
    }

    while (esp_timer_get_time() - time < micro)
        ;
    _bridge.stop(Motor::BOTH);
    recalculateAngle(millis, direction);
}

int32_t MovementController::getPose() {
    return _pose;
}

void MovementController::recalculatePosition(uint32_t millis,
                                             MovementDirection dir) {
    float theta = _pose.degrees*PI/180;
    _pose.x += millis * cosf(theta);
    _pose.y += millis * sinf(theta);
}

void MovementController::recalculateAngle(uint32_t millis,
                                          MovementDirection dir) {
    if (dir == MovementDirection::LEFT) {
        millis *= -1;
    }
    _pose.degrees += millis;
    if(_pose.degrees > 360) {
        _pose.degrees = _pose.degrees % 360;
    }

    while(_pose.degrees < 0) {
        _pose.degrees += 360;
    }
}
