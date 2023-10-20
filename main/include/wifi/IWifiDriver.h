#pragma once

class IWifiDriver {
   public:
    virtual ~IWifiDriver() {}
    virtual void sendRobotState() = 0;
    virtual void init() = 0;
};
