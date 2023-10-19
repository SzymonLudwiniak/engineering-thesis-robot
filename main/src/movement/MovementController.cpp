#include "movement/MovementController.h"

#include "esp_timer.h"

MovementController::MovementController(IHbridge &bridge) : _bridge(bridge) {
    _posX = 0;
    _posY = 0;
    _degrees = 0;
    _bridge.setMotorState(Motor::BOTH, 1);
}

MovementController::~MovementController() {}

void MovementController::startMovement(MovementDirection direction) {
    if (direction == MotorDirection::BACKWARD) {
        _bridge.start(Motor::BOTH, MotorDirection::BACKWARD);
        return;
    }
    _bridge.start(Motor::BOTH, MotorDirection::FORWARD);
}

void MovementController::stopMovement() {
    _bridge.setMotorState(Motor::BOTH, 0);
}

void MovementController::moveFor(uint32_t millis, MovementDirection direction) {
    if (direction != MovementDirection::BACKWARD &&
        direction != MovementDirection::BACKWARD) {
        return;
    }
    uint64_t time = esp_timer_get_time();

    if (direction == MovementDirection::BACKWARD) {
        _bridge.start(Motor::BOTH, MotorDirection::BACKWARD);
    } else {
        _bridge.start(Motor::BOTH, MotorDirection::FORWARD);
    }

    while (esp_timer_get_time() - time >= millis)
        ;
    stopMovement();
}

void MovementController::rotateFor(uint32_t millis,
                                   MovementDirection direction) {
    uint64_t time = esp_timer_get_time();

    if (direction == MovementDirection::LEFT) {
        _bridge.start(Motor::BOTH, MotorDirection::LEFT);
    } else {
        _bridge.start(Motor::BOTH, MotorDirection::RIGHT);
    }

    while (esp_timer_get_time() - time >= millis)
        ;
    stopMovement();
}
