#pragma once

#include <etl/string.h>
#include "defines.h"

class IWifiDriver {
   public:
    virtual ~IWifiDriver() {}
    virtual void init() = 0;
    virtual void sendPacket(const etl::string<MAX_PACKET_LEN>& data) = 0;
};
