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
// Variant that NAMES the info parameter, for callbacks that read per-frame RX
// metadata (RSSI for semantic positioning SP0 — ttn-semantic-positioning.md).
#define ESPNOW_RECV_CB_INFO(fn, info, data, len) \
  void fn(const esp_now_recv_info_t* info, const uint8_t* data, int len)
// Per-frame RSSI (dBm, negative) of the received ESP-NOW frame. 3.x exposes it
// on the recv-info rx_ctrl; 0 = unknown.
static inline int tootEspNowRssi(const esp_now_recv_info_t* info) {
  return (info && info->rx_ctrl) ? info->rx_ctrl->rssi : 0;
}
// 3.x send callback: void(const esp_now_send_info_t*, esp_now_send_status_t).
#define ESPNOW_SEND_CB(fn, mac, status) \
  void fn(const esp_now_send_info_t*, esp_now_send_status_t status)
#else
#define ESPNOW_RECV_CB(fn, data, len) \
  void fn(const uint8_t*, const uint8_t* data, int len)
#define ESPNOW_RECV_CB_INFO(fn, info, data, len) \
  void fn(const uint8_t* info, const uint8_t* data, int len)
// 2.x (UNIHIKER K10 core): the recv callback carries no rx metadata, so per-frame
// RSSI is unavailable here (would need the promiscuous-RX trick — a later SP0
// sub-step). 0 = unknown; LinkPercept::add ignores rssi 0.
static inline int tootEspNowRssi(const uint8_t*) { return 0; }
// 2.x send callback: void(const uint8_t* mac_addr, esp_now_send_status_t).
#define ESPNOW_SEND_CB(fn, mac, status) \
  void fn(const uint8_t*, esp_now_send_status_t status)
#endif

#endif  // ARDUINO
