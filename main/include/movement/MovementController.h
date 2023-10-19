#pragma once

#include "IMovementController.h"
#include "drivers/hbridge/IHBridge.h"

class MovementController : public IMovementController {
   public:
    MovementController(IHbridge &bridge);
    ~MovementController();

    void moveFor(uint32_t millis, MovementDirection direction) override;
    void rotateFor(uint32_t millis, MovementDirection direction) override;

   private:
    IHBridge &_bridge;

    int32_t _posX;
    int32_t _posY;
    int16_t _degrees;
};
