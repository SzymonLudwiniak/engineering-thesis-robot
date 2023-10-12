#pragma once

#include <cstdint>

class IDistanceSensor {
   public:
    ~IDistanceSensor() {}

    virtual uint16_t calculateDistanceCm() = 0;
};
