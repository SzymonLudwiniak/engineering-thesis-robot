#include <cstdio>
#include <etl/vector.h>

#include "defines.h"
#include "drivers/gpio/GPIO.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "drivers/stepperMotor/ULN200X_StepperMotor.h"
#include "drivers/distanceSensor/HC_SR04_DistanceSensor.h"
#include "scanner/Scanner.h"

extern "C" void app_main() {
    GPIO A(IN1, PinMode::OUTPUT);
    GPIO B(IN2, PinMode::OUTPUT);
    GPIO C(IN3, PinMode::OUTPUT);
    GPIO D(IN4, PinMode::OUTPUT);

    GPIO ECHO_PIN(ECHO, PinMode::INPUT);
    GPIO TRIG_PIN(TRIGGER, PinMode::OUTPUT);

    HC_SR04_DistanceSensor sensor(ECHO_PIN, TRIG_PIN);
    ULN200X_StepperMotor stepper(A, B, C, D);

    Scanner scanner(sensor, stepper);

    vTaskDelay(4000 / portTICK_PERIOD_MS);
    for (int i = 0; i < 2; i++) {
        scanner.scan();
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}