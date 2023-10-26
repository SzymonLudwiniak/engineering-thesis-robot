#pragma once

#include <string.h>

#include "IWifiDriver.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "freertos/event_groups.h"
#include "lwip/sockets.h"

class WifiDriver : public IWifiDriver {
   public:
    WifiDriver();
    ~WifiDriver();

    void init() override;
    void sendPacket(const etl::string<MAX_PACKET_LEN>& data);

   private:
    int _addrFamily;
    int _ipProtocol;
    int _socket;
    sockaddr_in _destinationAddress;
};
