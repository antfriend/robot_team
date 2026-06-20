// v4b_relay.ino — Heltec WiFi LoRa 32 V4, RELAY / midpoint node (A32 agent).
//
// Role: pure store-and-forward (toot_network_architecture.md). Decrement ttl,
// dedup on (src,seq), re-emit. Solar-powered, external antenna. Still serves
// its own TTDB to the companion on request via TtdbShare.
//
// LoRa is gated behind USE_LORA; with it off this forwards over ESP-NOW so the
// forwarding logic (ttl/dedup) can be validated before the radio is wired.
#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include <Toot.h>
#include <TootSerial.h>
#include <TootEspNow.h>
#include <TTDB.h>
#include <TtdbShare.h>
#include <RobotTeamConfig.h>

#define USE_LORA 0  // Phase 4: SX1262 long hops to V4-A and V4-C.

static const uint32_t kNodeId = NODE_V4B_RELAY;
static const char* kTtdbPath = "/ttdb.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(256);
TootSerialLink gSerial(Serial);
uint32_t gForwarded = 0;

static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  return esp_now_send(kBroadcast, frame, len) == ESP_OK;
}

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    return;
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;  // drop loops/dupes

  if (t.type == toot::TTDB_REQ) {
    if (gShare && TtdbShare::requestTarget(t) == kNodeId)
      gShare->handleRequest(t, sendEspNow, nullptr);
    return;
  }
  // Store-and-forward: decrement ttl, re-sign, re-emit.
  if (t.ttl > 0) {
    t.ttl--;
    if (t.ttl > 0) {
      uint8_t frame[toot::MAX_FRAME];
      size_t flen = toot::encode(t, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame,
                                 sizeof(frame));
      if (flen && sendEspNow(frame, flen, nullptr)) ++gForwarded;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath))
    Serial.println("FATAL: TTDB load failed");
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId,
                         gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_now_init();
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);
  Serial.printf("V4-B relay 0x%08X online\n", kNodeId);
}

void loop() {
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t) &&
        t.type == toot::TTDB_REQ && gShare &&
        TtdbShare::requestTarget(t) == kNodeId) {
      gShare->handleRequest(t, [](const uint8_t* f, size_t l, void*) {
        gSerial.writeFrame(f, l);
        return true;
      }, nullptr);
    }
  }
  // OLED link-health (RSSI to A/C, forward count) is added with the radio.
}
