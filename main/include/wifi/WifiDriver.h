#pragma once

#include <string.h>

#include "IWifiDriver.h"
#include "defines.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "etl/string.h"
#include "freertos/event_groups.h"

class WifiDriver : public IWifiDriver {
   public:
    WifiDriver();
    ~WifiDriver();

    void sendRobotState() override;
    void init() override;

   private:
    static EventGroupHandle_t eventGroup;
    wifi_config_t wifiConfig;

    static void eventHandler(void* arg,
                             esp_event_base_t event_base,
                             int32_t event_id,
                             void* event_data);

    void sendPacket(const etl::string<MAX_PACKET_LEN>& data);
};

// void init_wifi();

// void event_handler(void* arg,
//                    esp_event_base_t event_base,
//                    int32_t event_id,
//                    void* event_data);

// void send_packet(const char* data, size_t len);

// void send_robot_state();
