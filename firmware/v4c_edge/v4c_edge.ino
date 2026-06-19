// v4c_edge.ino — Heltec WiFi LoRa 32 V4, EDGE / tail node (A32 agent).
//
// Role: gateway for the most remote ESP-NOW cluster
// (toot_network_architecture.md). Aggregates/summarizes the local K10 percepts
// before spending LoRa airtime; optional GNSS stamps real @LATxLONy. Serves its
// own TTDB to the companion via TtdbShare.
//
// LoRa is gated behind USE_LORA. With it off, this acts as a local ESP-NOW
// cluster gateway and TTDB-share responder.
#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include <Toot.h>
#include <TootSerial.h>
#include <TTDB.h>
#include <TtdbShare.h>
#include <RobotTeamConfig.h>

#define USE_LORA 0  // Phase 4: long haul back to V4-B.
#define USE_GNSS 0  // Optional: SH1.25-8P GPS for @LATxLONy stamping.

static const uint32_t kNodeId = NODE_V4C_EDGE;
static const char* kTtdbPath = "/ttdb.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);

static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  return esp_now_send(kBroadcast, frame, len) == ESP_OK;
}

static void onEspNowRecv(const esp_now_recv_info_t*, const uint8_t* data,
                         int len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    return;
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;

  if (t.type == toot::TTDB_REQ) {
    if (gShare && TtdbShare::requestTarget(t) == kNodeId)
      gShare->handleRequest(t, sendEspNow, nullptr);
  } else if (t.type == toot::PERCEPT) {
    // Aggregate/summarize cluster-C percepts here before forwarding over LoRa
    // (airtime is scarcest at the tail). Summarization is a Phase 3 task.
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
  Serial.printf("V4-C edge 0x%08X online (GNSS %s)\n", kNodeId,
                USE_GNSS ? "on" : "off");
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
}
