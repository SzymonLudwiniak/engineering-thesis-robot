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

#ifndef DEFINES_H
#define DEFINES_H


//////////////////////////////////
//                              //
//          WIFI DEFINES        //
//                              //
//////////////////////////////////


#define WIFI_SSID           "UPC2297375"
#define WIFI_PASS           "ncjuenfmuG4j"
#define MAXIMUM_RETRY       5

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


#define TRIGGER         GPIO_NUM_19
#define ECHO            GPIO_NUM_21

#define IN1             GPIO_NUM_27
#define IN2             GPIO_NUM_26
#define IN3             GPIO_NUM_25
#define IN4             GPIO_NUM_33

#define M1_ENABLE       GPIO_NUM_23
#define M2_ENABLE       GPIO_NUM_22

#define M1_CONTROL_1    GPIO_NUM_2
#define M1_CONTROL_2    GPIO_NUM_4 
#define M2_CONTROL_1    GPIO_NUM_5
#define M2_CONTROL_2    GPIO_NUM_18

#define HIGH 1
#define LOW 0


#endif // DEFINES_H
