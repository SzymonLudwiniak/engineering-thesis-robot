/*
 * =====================================================================================
 *
 *       Filename:  defines.h
 *
 *    Description:  header for all defines, pinouts etc.
 *
 *        Version:  1.0
 *        Created:  15.08.2023 11:43:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Szymon Ludwiniak (), szymon.ludwiniak4ti@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#pragma once


//////////////////////////////////
//                              //
//          WIFI DEFINES        //
//                              //
//////////////////////////////////


#define WIFI_SSID           "UPC2297375"
#define WIFI_PASS           "ncjuenfmuG4j"

#define HOST_IP_ADDR "192.168.0.192"
#define PORT 49152

#define MAX_SSID_LEN        32
#define MAX_PASS_LEN        64

#define MAXIMUM_RETRY       10

#define MAX_PACKET_LEN      64

#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_FAIL_BIT       BIT1

#define DEST_PORT           80
#define DEST_IP_ADDR        "192.168.0.192"

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

//////////////////////////////////////


#define TRIGGER         19
#define ECHO            21

#define IN1             27
#define IN2             26
#define IN3             25
#define IN4             33

#define M1_ENABLE       23
#define M2_ENABLE       22

#define M1_CONTROL_1    2
#define M1_CONTROL_2    4 
#define M2_CONTROL_1    5
#define M2_CONTROL_2    18

#define HIGH 1
#define LOW 0

#define MEASURE_COUNT   181

#define PI 3.14159265