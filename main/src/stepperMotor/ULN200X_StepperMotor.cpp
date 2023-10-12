
#include "stepperMotor/ULN200X_StepperMotor.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

ULN200X_StepperMotor::ULN200X_StepperMotor(IGPIO &input1,
                                           IGPIO &input2,
                                           IGPIO &input3,
                                           IGPIO &input4)
    : _IN1(input1), _IN2(input2), _IN3(input3), _IN4(input4) {
    _currentAngle = 0;
}

ULN200X_StepperMotor::~ULN200X_StepperMotor() {}

void ULN200X_StepperMotor::rotateFor(int16_t degrees) {
    if (degrees + _currentAngle < 0 || degrees + _currentAngle > 180) {
        return;
    }

    _currentAngle += degrees;

    int16_t steps_x4 = 512 * degrees / 360;
    if (steps_x4 > 0) {
        for (int i = 0; i < steps_x4; i++) {
            commandAB();
            commandBC();
            commandCD();
            commandDA();
        }
    } else {
        steps_x4 *= -1;
        for (int i = 0; i < steps_x4; i++) {
            commandDA();
            commandCD();
            commandBC();
            commandAB();
        }
    }
}

// // every step is equal to 0.17578125 degree
// void ULN200X_StepperMotor::commandA() {
//     _IN1.setLevel(1);
//     vTaskDelay(1);
//     _IN1.setLevel(0);
// }

// void ULN200X_StepperMotor::commandB() {
//     _IN2.setLevel(1);
//     vTaskDelay(1);
//     _IN2.setLevel(0);
// }

// void ULN200X_StepperMotor::commandC() {
//     _IN3.setLevel(1);
//     vTaskDelay(1);
//     _IN3.setLevel(0);
// }

// void ULN200X_StepperMotor::commandD() {
//     _IN4.setLevel(1);
//     vTaskDelay(1);
//     _IN4.setLevel(0);
// }

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
