
#include "drivers/stepperMotor/ULN200X_StepperMotor.h"

#include <cstdio>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

ULN200X_StepperMotor::ULN200X_StepperMotor(IGPIO &input1,
                                           IGPIO &input2,
                                           IGPIO &input3,
                                           IGPIO &input4)
    : _IN1(input1), _IN2(input2), _IN3(input3), _IN4(input4) {
    _stepStatus = 0;
}

ULN200X_StepperMotor::~ULN200X_StepperMotor() {}

bool ULN200X_StepperMotor::rotateFor(int16_t steps) {
    // if (steps + _stepStatus < 0 || steps + _stepStatus > 2048) {
    //     return false;
    // }

    _stepStatus += steps;

    if (steps > 0) {
        for (int i = 0; i < steps; i++) {
            switch (i % 4) {
                case 0:
                    commandAB();
                    break;
                case 1:
                    commandBC();
                    break;
                case 2:
                    commandCD();
                    break;
                case 3:
                    commandDA();
                    break;
            }
        }
    } else {
        steps *= -1;
        for (int i = 0; i < steps; i++) {
            switch (i % 4) {
                case 3:
                    commandAB();
                    break;
                case 2:
                    commandBC();
                    break;
                case 1:
                    commandCD();
                    break;
                case 0:
                    commandDA();
                    break;
            }
        }
    }
    return true;
}

void ULN200X_StepperMotor::commandAB() {
    _IN1.setLevel(1);
    _IN2.setLevel(1);
    vTaskDelay(1);
    _IN1.setLevel(0);
    _IN2.setLevel(0);
}

void ULN200X_StepperMotor::commandBC() {
    _IN2.setLevel(1);
    _IN3.setLevel(1);
    vTaskDelay(1);
    _IN2.setLevel(0);
    _IN3.setLevel(0);
}

void ULN200X_StepperMotor::commandCD() {
    _IN3.setLevel(1);
    _IN4.setLevel(1);
    vTaskDelay(1);
    _IN3.setLevel(0);
    _IN4.setLevel(0);
}

void ULN200X_StepperMotor::commandDA() {
    _IN4.setLevel(1);
    _IN1.setLevel(1);
    vTaskDelay(1);
    _IN4.setLevel(0);
    _IN1.setLevel(0);
}
