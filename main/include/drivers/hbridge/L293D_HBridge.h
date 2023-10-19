#pragma once

#include "IHBridge.h"

#include "drivers/gpio/IGPIO.h"

class L293D_HBridge : public IHBridge{
   public:
    L293D_HBridge(IGPIO &m1Enable,
                  IGPIO &m2Enable,
                  IGPIO &m1Controll1,
                  IGPIO &m1Controll2,
                  IGPIO &m2Controll1,
                  IGPIO &m2Controll2);
    ~L293D_HBridge();

    void setMotorState(Motor motor, uint8_t state) override;
    void start(Motor motor, MotorDirection direction) override;
    void stop(Motor motor) override;

   private:
    IGPIO &_m1Enable;
    IGPIO &_m2Enable;
    IGPIO &_m1Controll1;
    IGPIO &_m1Controll2;
    IGPIO &_m2Controll1;
    IGPIO &_m2Controll2;

    void startForward();
    void startBackward();
    void startLeft();
    void startRight();
};
