#pragma once

enum class MovementDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGTH
}

class IMovementController {
   public:
    virtual ~IMovementController() {};

    virtual void startMovement(MovementDirection direction) = 0;
    virtual void stopMovement() = 0;
    virtual void moveFor(uint32_t millis, MovementDirection direction) = 0;
    virtual void rotateFor(uint32_t millis, MovementDirection direction) = 0;
};
