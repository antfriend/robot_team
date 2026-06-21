// TootEspNow.h — ESP-NOW receive-callback signature that compiles on both
// arduino-esp32 2.x and 3.x.
//
// The UNIHIKER K10 core (UNIHIKER:esp32 0.0.3) is arduino-esp32 2.x, whose
// recv callback is void(const uint8_t* mac, const uint8_t* data, int len).
// The esp32:esp32 3.x core (Heltec V4) changed it to
// void(const esp_now_recv_info_t* info, const uint8_t* data, int len).
//
// Use:  static ESPNOW_RECV_CB(onEspNowRecv, data, len) { ...use data,len... }
#pragma once
#if defined(ARDUINO)
#include <Arduino.h>
#include <esp_now.h>

#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
#define ESPNOW_RECV_CB(fn, data, len) \
  void fn(const esp_now_recv_info_t*, const uint8_t* data, int len)
// 3.x send callback: void(const esp_now_send_info_t*, esp_now_send_status_t).
#define ESPNOW_SEND_CB(fn, mac, status) \
  void fn(const esp_now_send_info_t*, esp_now_send_status_t status)
#else
#define ESPNOW_RECV_CB(fn, data, len) \
  void fn(const uint8_t*, const uint8_t* data, int len)
// 2.x send callback: void(const uint8_t* mac_addr, esp_now_send_status_t).
#define ESPNOW_SEND_CB(fn, mac, status) \
  void fn(const uint8_t*, esp_now_send_status_t status)
#endif

#endif  // ARDUINO
