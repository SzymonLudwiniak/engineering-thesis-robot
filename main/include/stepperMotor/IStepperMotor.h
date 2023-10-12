#pragma once

#include <cstdint>

class IStepperMotor {
   public:
    ~IStepperMotor() {}
    virtual void rotateFor(int16_t degrees) = 0;
};
