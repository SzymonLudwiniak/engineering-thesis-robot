#pragma once

#include "IDistanceSensor.h"
#include "externals/gpio/GPIO.h"

class HC_SR04_DistanceSensor : public IDistanceSensor {
   public:
    HC_SR04_DistanceSensor(GPIO &echo, GPIO &trigger);
    ~HC_SR04_DistanceSensor();

    uint64_t calculateDistanceCm() override;

   private:
    GPIO &_echo;
    GPIO &_trigger;

    uint64_t _delay;
    uint64_t _time;
};
