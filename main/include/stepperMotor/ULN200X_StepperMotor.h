#pragma once

#include "IStepperMotor.h"
#include "externals/gpio/IGPIO.h"

class ULN200X_StepperMotor : public IStepperMotor {
   public:
    ULN200X_StepperMotor(IGPIO &input1, IGPIO &input2, IGPIO &input3, IGPIO &input4);
    ~ULN200X_StepperMotor();

    // every step is equal to 0.17578125 degree
    void rotateFor(int16_t degrees) override;

   private:
    IGPIO &_IN1;
    IGPIO &_IN2;
    IGPIO &_IN3;
    IGPIO &_IN4;

    int16_t _currentAngle;

    // void commandA();
    // void commandB();
    // void commandC();
    // void commandD();
    void commandAB();
    void commandBC();
    void commandCD();
    void commandDA();
};
