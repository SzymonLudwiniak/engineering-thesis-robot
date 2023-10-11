#include "externals/gpio/GPIO.h"


GPIO::GPIO(uint8_t gpioNum, PinMode mode) {
    _gpioNum = static_cast<gpio_num_t>(gpioNum);
    _mode = mode;

    switch (_mode) {
        case PinMode::DISABLE:
            gpio_set_direction(_gpioNum, GPIO_MODE_DISABLE);
            break;
        case PinMode::INPUT:
            gpio_set_direction(_gpioNum, GPIO_MODE_INPUT);
            break;
        case PinMode::OUTPUT:
            gpio_set_direction(_gpioNum, GPIO_MODE_OUTPUT);
            break;
    }
}

GPIO::~GPIO() {
    gpio_reset_pin(_gpioNum);
}

int GPIO::getLevel() {
    return gpio_get_level(_gpioNum);
}

void GPIO::setLevel(uint32_t level) {
    gpio_set_level(_gpioNum, level);
}
