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
static Music music;
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

#if USE_K10_HW
// Two toots — the Toot-Toot signature — on startup (uses the K10 speaker).
// playTone(freq, beat): `beat` is the count of I2S samples at 8 kHz, so the
// duration is beat/8000 seconds — NOT milliseconds. (My earlier 400/600 were
// ~50-75 ms, inaudible.) These match the known-good k10_ttdb_navigator values:
// 2000 -> 0.25 s, 4000 -> 0.5 s.
static void playStartupToot() {
  delay(50);                  // let the speaker settle after k10.begin()
  music.playTone(196, 2000);  // toot  (G3, 0.25 s)
  music.playTone(262, 4000);  // toot  (C4, 0.5 s)
}

// Show TTDB identity + indexed records + live reasoning state on the LCD.
static void renderScreen(float tempC) {
  char line[40];
  k10.canvas->canvasClear(0x000000);
  k10.canvas->canvasText("K10 Percept Node", 1, 0x00E676);
  snprintf(line, sizeof(line), "id 0x%08X", (unsigned)kNodeId);
  k10.canvas->canvasText(String(line), 2, 0x2E7D32);
  snprintf(line, sizeof(line), "TTDB %uB  %d rec", (unsigned)gDb.fileSize(),
           gDb.recordCount());
  k10.canvas->canvasText(String(line), 4, 0x00FF66);

  int row = 6;
  for (int i = 0; i < gDb.recordCount() && row <= 10; ++i) {
    const TtdbRecord& r = gDb.record(i);
    snprintf(line, sizeof(line), "  @LAT%dLON%d", r.lat, r.lon);
    k10.canvas->canvasText(String(line), row++, 0x00FF66);
  }

  bool warm = gAgent.matchedThisCycle();
  snprintf(line, sizeof(line), "temp %.1f C", tempC);
  k10.canvas->canvasText(String(line), 12, 0x00FF66);
  snprintf(line, sizeof(line), "cursor @LAT%dLON%d", gAgent.cursorLat(),
           gAgent.cursorLon());
  k10.canvas->canvasText(String(line), 14, warm ? 0xCCFF90 : 0x2E7D32);
  k10.canvas->canvasText(warm ? "WARM - indicator ON" : "cool", 16,
                         warm ? 0xFF6F00 : 0x2E7D32);
  k10.canvas->updateCanvas();
}
#endif

// --- transports -------------------------------------------------------------
// ESP-NOW TX is asynchronous with a shallow queue. TtdbShare streams many
// TTDB_DATA frames back-to-back, which overruns the queue and silently drops all
// but the first few. Gate each send on the previous frame's TX-complete callback
// so the whole TTDB streams intact over the air.
static volatile bool gEspNowTxDone = true;
static ESPNOW_SEND_CB(onEspNowSend, mac, status) {
  (void)status;
  gEspNowTxDone = true;
}
static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  uint32_t t0 = millis();
  while (!gEspNowTxDone && millis() - t0 < 50) delay(1);  // await prior TX
  gEspNowTxDone = false;
  bool ok = esp_now_send(kBroadcast, frame, len) == ESP_OK;
  delay(6);  // breathing room for the bridge to drain each frame to USB-CDC
  return ok;
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
// the transport to answer on (ESP-NOW peer or serial). Dedup is a radio/mesh
// concern (replay attacks + forwarding loops), so it is NOT applied here — the
// trusted USB-CDC link is intentionally un-deduped so the laptop can retry a lost
// request. Radio callers gate on gDedup before calling in (see onEspNowRecv).
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
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

// A TTDB_REQ arriving over ESP-NOW is stashed here and served from loop(), not
// from the recv callback: streaming the whole reply from the WiFi task would
// block its own TX (the send-complete callback can't run), starving the burst.
static volatile bool gReqPending = false;
static toot::Toot gPendingReq;

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) return;
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;  // radio-path replay/loop guard
  if (t.type == toot::TTDB_REQ) {
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }  // defer to loop()
  } else {
    handleToot(t, sendEspNow, nullptr);                         // cheap, no burst
  }
}

// --- setup / loop -----------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(200);

#if USE_K10_HW
  k10.begin();              // inits onboard peripherals incl. AHT20 + rgb
  playStartupToot();        // "toot toot"
  k10.initScreen(2);        // 2 = default orientation
  k10.creatCanvas();
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
  esp_now_register_send_cb(onEspNowSend);   // paces TTDB_DATA bursts (see sendEspNow)
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

  // Serve an ESP-NOW TTDB_REQ deferred from the recv callback (so the reply
  // streams from the main task, where TX pacing via the send callback works).
  if (gReqPending) {
    gReqPending = false;
    if (gShare && TtdbShare::requestTarget(gPendingReq) == kNodeId)
      gShare->handleRequest(gPendingReq, sendEspNow, nullptr);
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
#if USE_K10_HW
    renderScreen(gAgent.readingCount() > 0 ? gAgent.reading(0).value : 0.0f);
#endif
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }
}
