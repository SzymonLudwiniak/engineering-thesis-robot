#pragma once

#include "IDistanceSensor.h"
#include "drivers/gpio/IGPIO.h"

class HC_SR04_DistanceSensor : public IDistanceSensor {
   public:
    HC_SR04_DistanceSensor(IGPIO &echo, IGPIO &trigger);
    ~HC_SR04_DistanceSensor();

    uint16_t calculateDistanceCm() override;

   private:
    IGPIO &_echo;
    IGPIO &_trigger;

    uint64_t _delay;
    uint64_t _time;
};
