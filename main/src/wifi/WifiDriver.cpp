#include "wifi/WifiDriver.h"

#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "lwip/err.h"
#include "lwip/netdb.h"
#include "lwip/sys.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"


#define HOST_IP_ADDR "192.168.0.192"

#define PORT 49152

static const char *TAG = "example";

WifiDriver::WifiDriver() {}

WifiDriver::~WifiDriver() {}


void WifiDriver::init() {
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());

    _destinationAddress.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
    _destinationAddress.sin_family = AF_INET;
    _destinationAddress.sin_port = htons(PORT);
    _addrFamily = AF_INET;
    _ipProtocol = IPPROTO_IP;

    _socket = socket(_addrFamily, SOCK_DGRAM, _ipProtocol);
    if (_socket < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        return;
    }

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;
    setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);
}

void WifiDriver::sendPacket(const etl::string<MAX_PACKET_LEN> &data) {
    int err = sendto(_socket,
                     data.c_str(),
                     data.length(),
                     0,
                     (struct sockaddr *)&_destinationAddress,
                     sizeof(_destinationAddress));
    if (err < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        return;
    }
    ESP_LOGI(TAG, "Message sent");
}
