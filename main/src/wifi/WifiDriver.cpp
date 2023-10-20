#include "wifi/WifiDriver.h"

void WifiDriver::eventHandler(void* arg,
                              esp_event_base_t event_base,
                              int32_t event_id,
                              void* event_data) {}

WifiDriver::WifiDriver()
    : wifiConfig{
          .sta =
              {
                  .ssid = WIFI_SSID,
                  .password = WIFI_PASS,
                  .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
                  .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
              },
      } {}

WifiDriver::~WifiDriver() {}

void WifiDriver::sendRobotState() {}

void WifiDriver::init() {
    esp_err_t err = nvs_flash_init();  // init heap for WIFI
    if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
        err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        err = nvs_flash_init();
    }

    if (err != 0) {
        ESP_LOGERR(TAG, "nvs initialization failed!\n");
        ESP_ERROR_CHECK(err);
    }

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");  // station (esp connects to AP);

    s_wifi_event_group = xEventGroupCreate();

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

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(
            TAG, "connected to AP SSID%s, password:%s", WIFI_SSID, WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG,
                 "Failed to connect to SSID:%s, password:%s",
                 WIFI_SSID,
                 WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

void WifiDriver::sendPacket(const etl::string<MAX_PACKET_LEN> &data) {
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;

    int err = getaddrinfo(DEST_IP_ADDR, NULL, &hints, &res);
    if (err != 0 || res == NULL) {
        ESP_LOGE(TAG, "Failed to resolve remote address");
        return;
    }

    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    addr->sin_port = htons(DEST_PORT);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(TAG, "Failed to create socket");
        freeaddrinfo(res);
        return;
    }

    ESP_LOGI(TAG, "Connecting to server...");
    if (connect(sock, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) != 0) {
        ESP_LOGE(TAG, "Failed to connect to server");
        close(sock);
        freeaddrinfo(res);
        return;
    }

    ESP_LOGI(TAG, "Sending packet...");
    if (send(sock, data, len, 0) < 0) {
        ESP_LOGE(TAG, "Failed to send packet");
    }

    close(sock);
    freeaddrinfo(res);
    ESP_LOGI(TAG, "Packet sent");
}
