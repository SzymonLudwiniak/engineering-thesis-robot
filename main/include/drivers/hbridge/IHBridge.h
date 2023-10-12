#pragma once

#include <cstdint>

enum class Motor { MOTOR1, MOTOR2, BOTH };

enum class MotorDirection { FORWARD, BACKWARD };


class IHBridge {
   public:
    virtual ~IHBridge() {}

    virtual void setMotorState(Motor motor, uint8_t state) = 0;
    virtual void start(Motor motor, MotorDirection direction) = 0;
    virtual void stop(Motor motor) = 0;
};
