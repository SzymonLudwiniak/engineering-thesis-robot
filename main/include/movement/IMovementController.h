#pragma once

#include <cstdint>

enum class MovementDirection { FORWARD, BACKWARD, LEFT, RIGTH };

class IMovementController {
   public:
    virtual ~IMovementController(){};

    virtual void moveFor(uint32_t millis, MovementDirection direction) = 0;
    virtual void rotateFor(uint32_t millis, MovementDirection direction) = 0;
    virtual int32_t getPose() = 0;
};
