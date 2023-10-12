#include <cstdio>

#include "defines.h"
#include "externals/gpio/GPIO.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stepperMotor/ULN200X_StepperMotor.h"

extern "C" void app_main() {
    GPIO A(IN1, PinMode::OUTPUT);
    GPIO B(IN2, PinMode::OUTPUT);
    GPIO C(IN3, PinMode::OUTPUT);
    GPIO D(IN4, PinMode::OUTPUT);

    ULN200X_StepperMotor stepper(A, B, C, D);

    while (1) {
        stepper.rotateFor(180);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        stepper.rotateFor(-180);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
