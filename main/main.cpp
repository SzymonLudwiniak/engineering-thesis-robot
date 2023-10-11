#include <cstdio>

#include "defines.h"
#include "externals/gpio/GPIO.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hbridge/L293D_HBridge.h"

extern "C" void app_main() {
    GPIO m1Enable(M1_ENABLE, PinMode::OUTPUT);
    GPIO m2Enable(M2_ENABLE, PinMode::OUTPUT);
    GPIO m1Controll1(M1_CONTROL_1, PinMode::OUTPUT);
    GPIO m1Controll2(M1_CONTROL_2, PinMode::OUTPUT);
    GPIO m2Controll1(M2_CONTROL_1, PinMode::OUTPUT);
    GPIO m2Controll2(M2_CONTROL_2, PinMode::OUTPUT);

    L293D_HBridge bridge(
        m1Enable, m2Enable, m1Controll1, m1Controll2, m2Controll1, m2Controll2);


    while (1) {
        bridge.setMotorState(Motor::BOTH, 1);
        bridge.start(Motor::BOTH, MotorDirection::FORWARD);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        bridge.setMotorState(Motor::MOTOR1, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        bridge.setMotorState(Motor::MOTOR2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
