#include "scanner/Scanner.h"

#include <cstdio>

Scanner::Scanner(IDistanceSensor& sensor, IStepperMotor& motor)
    : _measurements{0}, _sensor(sensor), _motor(motor) {
    _currentAngle = 0;
}

Scanner::~Scanner() {}


void Scanner::scan() {
    printf("starting scanning!\n");
    _motor.rotateFor(-_currentAngle);   //it puts it in starting position
    _currentAngle = 0;

    for (int i = 0; i < MEASURE_COUNT; i++) {
        _measurements[i] = _sensor.calculateDistanceCm();
        _motor.rotateFor(8);    // 8 steps
        _currentAngle += 8;
        printf("reading [%d]: %d\n", i, _measurements[i]);
    }
    printf("scan finished!\n");
}
