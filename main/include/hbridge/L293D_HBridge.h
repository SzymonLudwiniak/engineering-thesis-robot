#pragma once

#include "IHBridge.h"

#include "externals/gpio/GPIO.h"

class L293D_HBridge : public IHBridge{
   public:
    L293D_HBridge(GPIO &m1Enable,
                  GPIO &m2Enable,
                  GPIO &m1Controll1,
                  GPIO &m1Controll2,
                  GPIO &m2Controll1,
                  GPIO &m2Controll2);
    ~L293D_HBridge();

    void setMotorState(Motor motor, uint8_t state) override;
    void start(Motor motor, MotorDirection direction) override;
    void stop(Motor motor) override;

   private:
    GPIO &_m1Enable;
    GPIO &_m2Enable;
    GPIO &_m1Controll1;
    GPIO &_m1Controll2;
    GPIO &_m2Controll1;
    GPIO &_m2Controll2;
};
