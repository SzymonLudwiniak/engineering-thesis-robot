#include "hbridge/L293D_HBridge.h"

L293D_HBridge::L293D_HBridge(IGPIO &m1Enable,
                             IGPIO &m2Enable,
                             IGPIO &m1Controll1,
                             IGPIO &m1Controll2,
                             IGPIO &m2Controll1,
                             IGPIO &m2Controll2)
    : _m1Enable(m1Enable),
      _m2Enable(m2Enable),
      _m1Controll1(m1Controll1),
      _m1Controll2(m1Controll2),
      _m2Controll1(m2Controll1),
      _m2Controll2(m2Controll2) {}

L293D_HBridge::~L293D_HBridge() {}

void L293D_HBridge::setMotorState(Motor motor, uint8_t state) {
    switch (motor) {
        case Motor::MOTOR1:
            _m1Enable.setLevel(state);
            break;
        case Motor::MOTOR2:
            _m2Enable.setLevel(state);
            break;
        case Motor::BOTH:
            _m1Enable.setLevel(state);
            _m2Enable.setLevel(state);
            break;
    }
}

void L293D_HBridge::start(Motor motor, MotorDirection direction) {
    if (direction == MotorDirection::FORWARD) {
        switch (motor) {
            case Motor::MOTOR1:
                _m1Controll1.setLevel(0);
                _m1Controll2.setLevel(1);
                break;
            case Motor::MOTOR2:
                _m2Controll1.setLevel(0);
                _m2Controll2.setLevel(1);
                break;
            case Motor::BOTH:
                _m1Controll1.setLevel(0);
                _m1Controll2.setLevel(1);
                _m2Controll1.setLevel(0);
                _m2Controll2.setLevel(1);
                break;
        }
        return;
    }

    switch (motor) {
        case Motor::MOTOR1:
            _m1Controll2.setLevel(0);
            _m1Controll1.setLevel(1);
            break;
        case Motor::MOTOR2:
            _m2Controll2.setLevel(0);
            _m2Controll1.setLevel(1);
            break;
        case Motor::BOTH:
            _m1Controll2.setLevel(0);
            _m1Controll1.setLevel(1);
            _m2Controll2.setLevel(0);
            _m2Controll1.setLevel(1);
            break;
    }
}

void L293D_HBridge::stop(Motor motor) {
    switch (motor) {
        case Motor::MOTOR1:
            _m1Controll1.setLevel(0);
            _m1Controll2.setLevel(0);
            break;
        case Motor::MOTOR2:
            _m2Controll1.setLevel(0);
            _m2Controll2.setLevel(0);
            break;
        case Motor::BOTH:
            _m1Controll1.setLevel(0);
            _m1Controll2.setLevel(0);
            _m2Controll1.setLevel(0);
            _m2Controll2.setLevel(0);
            break;
    }
}
