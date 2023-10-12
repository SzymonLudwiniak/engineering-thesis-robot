#pragma once

#include <cstdint>

class IScanner {
   public:
    ~IScanner() {}
    virtual void scan() = 0;
};
