#pragma once

#include "IStepperMotor.h"
#include "drivers/gpio/IGPIO.h"


class ULN200X_StepperMotor : public IStepperMotor {
   public:
    ULN200X_StepperMotor(IGPIO &input1, IGPIO &input2, IGPIO &input3, IGPIO &input4);
    ~ULN200X_StepperMotor();

    bool rotateFor(int16_t steps) override;

   private:
    IGPIO &_IN1;
    IGPIO &_IN2;
    IGPIO &_IN3;
    IGPIO &_IN4;

    int16_t _stepStatus;

    // void commandA();
    // void commandB();
    // void commandC();
    // void commandD();
    void commandAB();
    void commandBC();
    void commandCD();
    void commandDA();
};
