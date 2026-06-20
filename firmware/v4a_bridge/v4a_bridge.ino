// v4a_bridge.ino — Heltec WiFi LoRa 32 V4, BRIDGE / head node (A32 agent).
//
// Role: the only path between the laptop companion and the mesh
// (toot_network_architecture.md). It:
//   - serves its OWN TTDB to the companion over USB-CDC serial;
//   - relays a companion TTDB_REQ from serial into the ESP-NOW (later LoRa)
//     mesh, and streams the mesh's TTDB_DATA replies back up the serial link.
//
// LoRa (SX1262) is gated behind USE_LORA so this compiles with just the esp32
// core. Enable in Phase 4 with RadioLib and the V4 pin map in hardware_specs.md.
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

#define USE_LORA 0  // Phase 4: set 1 and wire RadioLib SX1262 (GPIO 8/9/10/11).

static const uint32_t kNodeId = NODE_V4A_BRIDGE;
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
static bool sendSerial(const uint8_t* frame, size_t len, void*) {
  gSerial.writeFrame(frame, len);
  return true;
}

// Forward a verified frame across the mesh. (LoRa added in Phase 4.)
static void injectToMesh(const uint8_t* frame, size_t len) {
  esp_now_send(kBroadcast, frame, len);
}

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    return;
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;
  // Bridge mesh -> laptop: anything destined upward (TTDB_DATA, telemetry,
  // beliefs) is re-framed onto the serial link for the companion.
  if (t.type == toot::TTDB_DATA || t.type == toot::BELIEF ||
      t.type == toot::PERCEPT || t.type == toot::ACK) {
    gSerial.writeFrame(data, (size_t)len);
  } else if (t.type == toot::TTDB_REQ &&
             TtdbShare::requestTarget(t) == kNodeId) {
    if (gShare) gShare->handleRequest(t, sendEspNow, nullptr);
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
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

  Serial.printf("V4-A bridge 0x%08X online (LoRa %s)\n", kNodeId,
                USE_LORA ? "on" : "off");
}

void loop() {
  // Laptop -> mesh / self. A TTDB_REQ for this node is served locally; for any
  // other node it is injected into the mesh and replies flow back via
  // onEspNowRecv -> serial.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) {
      // A request addressed to the bridge is served locally over serial;
      // anything else is injected into the mesh, and replies come back via
      // onEspNowRecv -> serial.
      if (t.type == toot::TTDB_REQ && TtdbShare::requestTarget(t) == kNodeId) {
        if (gShare) gShare->handleRequest(t, sendSerial, nullptr);
      } else {
        injectToMesh(buf, n);
      }
    }
  }
}
