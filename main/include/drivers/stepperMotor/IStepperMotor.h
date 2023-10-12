#pragma once

#include <cstdint>

class IStepperMotor {
   public:
    ~IStepperMotor() {}
    virtual bool rotateFor(int16_t steps) = 0;
};
