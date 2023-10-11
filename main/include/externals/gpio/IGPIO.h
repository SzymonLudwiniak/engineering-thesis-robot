#pragma once

#include <cstdint>

enum class PinMode {
    DISABLE,
    INPUT,
    OUTPUT,
};

class IGPIO {
   public:
    virtual ~IGPIO() {}
    virtual int getLevel() = 0;
    virtual void setLevel(uint32_t level) = 0;
};
