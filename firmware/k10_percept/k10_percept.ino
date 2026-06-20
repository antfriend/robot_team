// k10_percept.ino — UNIHIKER K10 percept node (A32 agent).
//
// Role: @PERCEPT capture leaf on the ESP-NOW cluster (toot_network_architecture
// .md section 1). No LoRa. Shares its TTDB with the companion two ways:
//   - over ESP-NOW, when a peer sends a TTDB_REQ toot;
//   - over USB-CDC serial, when the laptop companion.py sends a TTDB_REQ.
//
// Build/deploy with arduino-cli (see firmware/README.md). The TTDB lives in
// data/ttdb.md and is flashed to LittleFS separately.
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
#include <Agent32.h>
#include <RobotTeamConfig.h>

// Real UNIHIKER K10 onboard hardware (DFRobot `unihiker_k10` library). Set to 0
// to fall back to a serial-only mock if the library/board package isn't
// installed yet. API verified against the UNIHIKER K10 Arduino wiki:
//   temperature: aht20.getData(AHT20::eAHT20TempC)
//   RGB LED:     k10.rgb->write(-1, 0xRRGGBB)  /  k10.rgb->brightness(0..9)
#define USE_K10_HW 1
#if USE_K10_HW
#include "unihiker_k10.h"
static UNIHIKER_K10 k10;
static AHT20 aht20;
#endif

static const uint32_t kNodeId = NODE_K10_1;
static const char* kTtdbPath = "/ttdb.md";
// The K10's large_spiffs_16MB scheme has no partition named "spiffs"; its only
// LittleFS-capable partition is "model" (subtype spiffs, @0x510000, ~4.5MB),
// normally used for AI models (unused on a percept node). Mount it by label.
static const char* kFsLabel = "model";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Packed @LATxLONy locus this node reports in its toot headers. Until a real
// fix is known, advertise the K10's home node from its TTDB (filled at boot).
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(64);
TootSerialLink gSerial(Serial);
Agent32 gAgent(&gDb);
uint32_t gSeq = 1;

// --- sense/act bindings -----------------------------------------------------
// Sensor: onboard ambient temperature (AHT20), nominal range -20..60 C, mapped
// to (lat 10, lon 0) so a warm reading drives the cursor to the @LAT10LON0
// record in data/ttdb.md and fires its triggers edge.
static float readAmbientTempC() {
#if USE_K10_HW
  return aht20.getData(AHT20::eAHT20TempC);
#else
  return -20.0f + (float)((millis() / 1000) % 80);  // sawtooth mock
#endif
}
static const A32Sensor kTempSensor = {
    "ambient_temp", readAmbientTempC, /*map_lat=*/10, /*map_lon=*/0,
    /*range_min=*/-20.0f, /*range_max=*/60.0f};

// Actuator at (10,0): the three onboard RGB LEDs. A triggers@LAT10LON0 edge
// fires this with value 1.0 -> red (warm); the loop clears the LEDs each cycle
// so a cold cycle (no trigger) leaves them off.
static void setIndicator(float v) {
#if USE_K10_HW
  k10.rgb->write(-1, v > 0.5f ? 0xFF0000 : 0x000000);  // -1 = all LEDs
#else
  Serial.printf("[ACT] indicator -> %.1f\n", v);
#endif
}
static const A32Actuator kIndicator = {"indicator", setIndicator,
                                       /*map_lat=*/10, /*map_lon=*/0};

static inline void indicatorClear() {
#if USE_K10_HW
  k10.rgb->write(-1, 0x000000);
#endif
}

// --- transports -------------------------------------------------------------
static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  return esp_now_send(kBroadcast, frame, len) == ESP_OK;
}
static bool sendSerial(const uint8_t* frame, size_t len, void*) {
  gSerial.writeFrame(frame, len);
  return true;
}

static void emit(toot::Type type, const uint8_t* body, uint8_t n,
                 TtdbShare::SendFn send, void* ctx) {
  toot::Toot t;
  t.type = type;
  t.src_node_id = kNodeId;
  t.toot_seq = gSeq++;
  memcpy(t.locus, gLocus, toot::LOCUS_LEN);
  if (n && body) memcpy(t.payload, body, n);
  t.payload_len = n;
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(t, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) send(frame, flen, ctx);
}

// Dispatch a decoded, authenticated toot arriving on any transport. `reply` is
// the transport to answer on (ESP-NOW peer or serial).
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;
  switch (t.type) {
    case toot::TTDB_REQ:
      if (gShare && TtdbShare::requestTarget(t) == kNodeId)
        gShare->handleRequest(t, reply, ctx);
      break;
    case toot::HELLO:
    case toot::PERCEPT:
    case toot::BELIEF:
      // Neighborhood awareness lands here; nothing to do for the floor demo.
      break;
    default:
      break;
  }
}

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    handleToot(t, sendEspNow, nullptr);
}

// --- setup / loop -----------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(200);

#if USE_K10_HW
  k10.begin();              // inits onboard peripherals incl. AHT20 + rgb
  k10.rgb->brightness(5);   // 0-9
#endif

  if (!LittleFS.begin(true, "/littlefs", 10, kFsLabel)) {
    Serial.println("FATAL: LittleFS mount failed");
  } else if (!gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId,
                         gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  if (esp_now_init() != ESP_OK) {
    Serial.println("FATAL: esp_now_init failed");
  }
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

  gAgent.registerSensor(&kTempSensor);
  gAgent.registerActuator(&kIndicator);
  gAgent.setInterval(1000);
  gAgent.setMatchThreshold(8);
  Serial.printf("K10 percept node 0x%08X online\n", kNodeId);
}

void loop() {
  // Serve TTDB-share / commands arriving from the laptop over USB-CDC.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
      handleToot(t, sendSerial, nullptr);
  }

  // Periodic HELLO beacon + percept tick.
  static uint32_t last = 0;
  if (millis() - last >= gAgent.intervalMs()) {
    last = millis();
    indicatorClear();   // LEDs off unless this cycle's TTDB trigger re-lights
    gAgent.sense();
    gAgent.reason();
    gAgent.act();
    Serial.printf("[cycle] cursor @LAT%dLON%d match=%d\n", gAgent.cursorLat(),
                  gAgent.cursorLon(), gAgent.matchedThisCycle());
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }
}
