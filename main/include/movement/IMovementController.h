#pragma once

#include <cstdint>

enum class MovementDirection { FORWARD, BACKWARD, LEFT, RIGTH };

struct sPose {
    int32_t x;
    int32_t y;
    int16_t degrees;
};

class IMovementController {
   public:
    virtual ~IMovementController(){};

    virtual void moveFor(uint32_t millis, MovementDirection direction) = 0;
    virtual void rotateFor(uint32_t millis, MovementDirection direction) = 0;
    virtual sPose getPose() = 0;
};
