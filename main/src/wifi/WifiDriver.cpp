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
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "nvs_flash.h"


EventGroupHandle_t WifiDriver::eventGroup = nullptr;

void WifiDriver::eventHandler(void *arg,
                              esp_event_base_t event_base,
                              int32_t event_id,
                              void *event_data) {
    static uint32_t retryNum = 0;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT &&
               event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retryNum < MAXIMUM_RETRY) {
            esp_wifi_connect();
            retryNum++;
            ESP_LOGI("WIFI", "retry to connect to AP");
        } else {
            xEventGroupSetBits(WifiDriver::eventGroup, WIFI_FAIL_BIT);
        }
        ESP_LOGI("WIFI", "connect to AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI("WIFI", "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        retryNum = 0;
        xEventGroupSetBits(WifiDriver::eventGroup, WIFI_CONNECTED_BIT);
    }
}

WifiDriver::WifiDriver() : wifiConfig{0}{
    int i = 0;
    while (char c = WIFI_SSID[i]) {
        if (i > MAX_SSID_LEN)
            break;
        wifiConfig.sta.ssid[i++] = c;
    }

    i = 0;
    while (char c = WIFI_PASS[i]) {
        if (i > MAX_PASS_LEN)
            break;
        wifiConfig.sta.password[i++] = c;
    }

    ESP_LOGE("WIFI", "ssid: %s, password: %s", wifiConfig.sta.ssid, wifiConfig.sta.password);

    wifiConfig.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    wifiConfig.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;
}

WifiDriver::~WifiDriver() {}

void WifiDriver::sendRobotState() {
    sendPacket("hello");
}

void WifiDriver::init() {
    esp_err_t err = nvs_flash_init();  // init heap for WIFI
    if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
        err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        err = nvs_flash_init();
    }

    if (err != 0) {
        ESP_LOGE("WIFI", "nvs initialization failed!\n");
        ESP_ERROR_CHECK(err);
    }

    ESP_LOGI("WIFI", "ESP_WIFI_MODE_STA");  // station (esp connects to AP);

    WifiDriver::eventGroup = xEventGroupCreate();

    esp_netif_init();  // init underlaying stack

    esp_event_loop_create_default();      // create default event loop
    esp_netif_create_default_wifi_sta();  // create default STA

    wifi_init_config_t wifiInitConfig = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifiInitConfig);  // Finally initialize WIFI driver

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    esp_event_handler_instance_register(WIFI_EVENT,
                                        ESP_EVENT_ANY_ID,
                                        &WifiDriver::eventHandler,
                                        NULL,
                                        &instance_any_id);
    esp_event_handler_instance_register(IP_EVENT,
                                        IP_EVENT_STA_GOT_IP,
                                        &WifiDriver::eventHandler,
                                        NULL,
                                        &instance_got_ip);

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifiConfig);
    esp_wifi_start();

    ESP_LOGI("WIFI", "wifi_init_sta finished.");

    EventBits_t bits = xEventGroupWaitBits(WifiDriver::eventGroup,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI("WIFI",
                 "connected to AP SSID: %s, password: %s",
                 WIFI_SSID,
                 WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI("WIFI",
                 "Failed to connect to SSID:%s, password:%s",
                 WIFI_SSID,
                 WIFI_PASS);
    } else {
        ESP_LOGE("WIFI", "UNEXPECTED EVENT");
    }
}

void WifiDriver::sendPacket(const etl::string<MAX_PACKET_LEN> &data) {
    addrinfo hints;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo *res;

    int err = getaddrinfo(DEST_IP_ADDR, NULL, &hints, &res);
    if (err != 0 || res == NULL) {
        ESP_LOGE("WIFI", "Failed to resolve remote address");
        return;
    }

    sockaddr_in *addr = (sockaddr_in *)res->ai_addr;
    addr->sin_port = htons(DEST_PORT);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE("WIFI", "Failed to create socket");
        freeaddrinfo(res);
        return;
    }

    ESP_LOGI("WIFI", "Connecting to server...");
    if (connect(sock, (sockaddr *)addr, sizeof(sockaddr_in)) != 0) {
        ESP_LOGE("WIFI", "Failed to connect to server");
        close(sock);
        freeaddrinfo(res);
        return;
    }

    ESP_LOGI("WIFI", "Sending packet...");
    if (send(sock,
             reinterpret_cast<const void *>(data.c_str()),
             data.length(),
             0) < 0) {
        ESP_LOGE("WIFI", "Failed to send packet");
    }

    close(sock);
    freeaddrinfo(res);
    ESP_LOGI("WIFI", "Packet sent");
}
