#include <etl/vector.h>

#include <cstdio>

#include "defines.h"
#include "drivers/distanceSensor/HC_SR04_DistanceSensor.h"
#include "drivers/gpio/GPIO.h"
#include "drivers/hbridge/L293D_HBridge.h"
#include "drivers/stepperMotor/ULN200X_StepperMotor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "movement/MovementController.h"
#include "scanner/Scanner.h"
#include "wifi/WifiDriver.h"

GPIO A(IN1, PinMode::OUTPUT);
GPIO B(IN2, PinMode::OUTPUT);
GPIO C(IN3, PinMode::OUTPUT);
GPIO D(IN4, PinMode::OUTPUT);

GPIO m1Enable(M1_ENABLE, PinMode::OUTPUT);
GPIO m2Enable(M2_ENABLE, PinMode::OUTPUT);

GPIO m1Control1(M1_CONTROL_1, PinMode::OUTPUT);
GPIO m1Control2(M1_CONTROL_2, PinMode::OUTPUT);

GPIO m2Control1(M2_CONTROL_1, PinMode::OUTPUT);
GPIO m2Control2(M2_CONTROL_2, PinMode::OUTPUT);

GPIO ECHO_PIN(ECHO, PinMode::INPUT);
GPIO TRIG_PIN(TRIGGER, PinMode::OUTPUT);

L293D_HBridge bridge(
    m1Enable, m2Enable, m1Control1, m1Control2, m2Control1, m2Control2);

MovementController moveController(bridge);

HC_SR04_DistanceSensor sensor(ECHO_PIN, TRIG_PIN);
ULN200X_StepperMotor stepper(A, B, C, D);

Scanner scanner(sensor, stepper);

extern "C" void app_main() {
    // while(1) {
    // moveController.moveFor(1000, MovementDirection::FORWARD);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    // moveController.rotateFor(1000, MovementDirection::LEFT);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    // moveController.moveFor(1000, MovementDirection::BACKWARD);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    // moveController.rotateFor(1000, MovementDirection::RIGTH);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    // }
    WifiDriver wifi;
    wifi.init();

    while (1) {
        wifi.sendRobotState();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
