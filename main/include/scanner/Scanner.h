#pragma once

#include "defines.h"
#include "IScanner.h"
#include "drivers/distanceSensor/IDistanceSensor.h"
#include "drivers/stepperMotor/IStepperMotor.h"

class Scanner : public IScanner {
   public:
    Scanner(IDistanceSensor& sensor, IStepperMotor& motor);
    ~Scanner();

    void scan() override;

   private:
    uint16_t _measurements[MEASURE_COUNT];

    IDistanceSensor& _sensor;
    IStepperMotor& _motor;

    int16_t _currentAngle;
};
