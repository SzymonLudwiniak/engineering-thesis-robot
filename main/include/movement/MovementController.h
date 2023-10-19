#pragma once

#include "IMovementController.h"
#include "drivers/hbridge/IHBridge.h"

class MovementController : public IMovementController {
   public:
    MovementController(IHBridge &bridge);
    ~MovementController();

    void moveFor(uint32_t millis, MovementDirection direction) override;
    void rotateFor(uint32_t millis, MovementDirection direction) override;

    int32_t getPose() override;

   private:
    IHBridge &_bridge;

    struct sPose {
        int32_t x;
        int32_t y;
        int16_t degrees;
    } _pose;

    void recalculatePosition(uint32_t millis);
    void recalculateAngle(uint32_t millis, MovementDirection dir);
};
