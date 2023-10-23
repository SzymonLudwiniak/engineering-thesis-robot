#pragma once

#include "IMovementController.h"
#include "drivers/hbridge/IHBridge.h"



class MovementController : public IMovementController {
   public:
    MovementController(IHBridge &bridge);
    ~MovementController();

    void moveFor(uint32_t millis, MovementDirection direction) override;
    void rotateFor(uint32_t millis, MovementDirection direction) override;

    sPose getPose() override;

   private:
    IHBridge &_bridge;

    sPose _pose;

    void recalculatePosition(uint32_t millis);
    void recalculateAngle(uint32_t millis, MovementDirection dir);
};
