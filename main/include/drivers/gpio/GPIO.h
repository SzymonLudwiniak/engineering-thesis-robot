#pragma once

#include "IGPIO.h"

#include "driver/gpio.h"

class GPIO : public IGPIO {
   public:
    GPIO(uint8_t gpioNum, PinMode mode);
    ~GPIO();

    int getLevel();
    void setLevel(uint32_t level);

   private:
    gpio_num_t _gpioNum;
    PinMode _mode;
};
