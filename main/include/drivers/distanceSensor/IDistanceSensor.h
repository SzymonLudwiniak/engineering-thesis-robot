#pragma once

#include <cstdint>

class IDistanceSensor {
   public:
    ~IDistanceSensor() {}

    virtual uint64_t calculateDistanceCm() = 0;
};
