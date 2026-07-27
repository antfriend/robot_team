// cardputer_console.ino — M5Stack Cardputer ADV: SECOND HANDHELD + the fleet's EARS.
//
// Role: everything the T-Deck console is (a full ESP-NOW Dream-Cycle participant with
// a keyboard that injects CMD toots and a screen that draws the fleet as a TTCP globe)
// plus the two senses no other node in the fleet has:
//
//   * a **BMI270 accelerometer**, so this node can say whether it HELD STILL while a
//     percept window accumulated (@LAT95, MotionPercept.h). Every earlier tier quietly
//     assumed that; the 2026-07-07 walking range test showed the assumption failing.
//   * an **ES8311 codec + MEMS microphone**, so this node HEARS (@LAT94,
//     AcousticPercept.h). Sound is the first non-electromagnetic evidence tier — it
//     travels slowly enough to be a time-of-arrival measurement rather than an
//     amplitude one, which is the way out of the shadowing limit the 2026-07-10 garden
//     run ran into (ttn-semantic-positioning.md Phase 3).
//
// Built from the verified T-Deck console (tdeck_console.ino), which was itself built
// from V4-B's network floor: serve a TTDB burst from loop() (never the recv callback),
// pace ESP-NOW sends behind the TX-complete callback, dedup radio-only, re-ACK a
// dropped want_ack replay (TTN-RFC-0007 §5), defer every flash write out of the WiFi
// task. Those lessons are not re-derived here — they are load-bearing.
//
// What differs from the T-Deck, hardware-wise (hardware_specs.md):
//   * the keyboard is a **TCA8418 I2C matrix scanner** (0x34), not a keyboard MCU that
//     hands over ASCII — this sketch owns the keycode->character map;
//   * there is **no trackball**, so the arrow keys navigate and ENTER cycles globes —
//     and, because the IMU is right there, **tilting the device rolls the globe**;
//   * audio goes through a **codec**: nothing is heard or sounded until the ES8311's
//     registers are written (Es8311.h), and the same I2S bus carries both directions;
//   * there is **no LoRa and no GPS** — the T-Deck stays the roaming GPS anchor.
//
// Build/deploy with arduino-cli, FQBN
// esp32:esp32:esp32s3:CDCOnBoot=cdc,PartitionScheme=huge_app (native USB like the rest
// of the fleet; huge_app for the screen UI + BLE, exactly as the T-Deck).
// TTDB in data/ flashed to LittleFS separately: scripts/Upload-Cardputer-FS.ps1.
#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <Wire.h>
#include <SPI.h>

#include <Toot.h>
#include <TootSerial.h>
#include <TootEspNow.h>
#include <TTDB.h>
#include <TtdbShare.h>
#include <Pulse.h>    // band tempo (PULSE_DEFAULT_BEAT_MS) lives in Pulse.h — 120 BPM
#include <Score.h>
#include <HeroArc.h>  // the hero's-arc song: scene -> phrase tables for every role
#include <LinkPercept.h>     // SP0: every authenticated reception becomes a percept
#include <BleLink.h>         // SP0 near-range tier: BLE advert+scan -> PROTO_BLE
#include <EntityPercept.h>   // SP0 entity tier: WiFi BSSID sightings -> @LAT96
#include <MotionPercept.h>   // SP0 motion tier: was this node still? -> @LAT95
#include <AcousticPercept.h> // SP0 acoustic tier: what did it hear? -> @LAT94
#include <RobotTeamConfig.h>
#include <Preferences.h>     // NVS: remember the song on/off across a power-cycle

// Real Cardputer peripherals (ST7789 LCD + TCA8418 keyboard + ES8311 audio + BMI270).
// Set to 0 to bring the network floor up headless with a serial mock — the way every
// node in this fleet was first verified (USE_K10_HW / USE_TDECK_HW). The floor works
// either way, which is what makes a bad codec or a bad panel a non-blocking problem.
#define USE_CARD_HW 1
#define USE_PULSE   1     // follow the band clock so `band`/`monitor` see this node
#define USE_BLE     1     // SP0 near-range tier: advertise+scan over BLE (proto:ble)
#define USE_IMU     1     // SP0 motion tier (@LAT95) + tilt-to-roll the globe
#define USE_MIC     1     // SP0 acoustic tier (@LAT94) — needs the codec (USE_CARD_HW)

// SP0 entity tier: duty-cycled WiFi scan logging visible BSSIDs (@LAT96 lane). Like
// the T-Deck this is a MOVING observer, so its shifting AP set is a rich co-occurrence
// signal. The ~2 s async scan hops channels, so it is kept rare and the ESP-NOW channel
// is re-asserted after.
#define USE_WIFI_SCAN 1
#define WIFI_SCAN_PERIOD_MS 600000UL   // one ~2 s scan every 10 min

// --- Cardputer ADV pin map (M5Stack K132-Adv, Stamp-S3A) ---------------------
// Documented here and in hardware_specs.md. Three peripherals share ONE I2C bus
// (keyboard 0x34, codec 0x18, IMU 0x68); the LCD has its own SPI; the microSD has
// another (unused here, listed so nobody re-uses those pins).
static const int PIN_I2C_SDA   = 8;   // keyboard + codec + IMU
static const int PIN_I2C_SCL   = 9;
static const int PIN_KBD_INT   = 11;  // TCA8418 INT, active low
static const uint8_t KBD_ADDR  = 0x34;

static const int PIN_TFT_SCLK  = 36;  // ST7789V2, 240x135
static const int PIN_TFT_MOSI  = 35;
static const int PIN_TFT_CS    = 37;
static const int PIN_TFT_DC    = 34;
static const int PIN_TFT_RST   = 33;
static const int PIN_TFT_BL    = 38;  // display backlight (active HIGH)

static const int PIN_I2S_BCLK  = 41;  // ES8311 SCLK — also the codec's MCLK source
static const int PIN_I2S_WS    = 43;  // LRCK
static const int PIN_I2S_DOUT  = 42;  // DSDIN:  ESP -> codec DAC -> NS4150B -> speaker
static const int PIN_I2S_DIN   = 46;  // ASDOUT: codec ADC (MEMS mic) -> ESP

static const int PIN_IR_TX     = 44;  // IR emitter (unused)
static const int PIN_BAT_ADC   = 10;  // battery monitor
// microSD (unused): CS 12, MOSI 14, CLK 40, MISO 39.

static const uint32_t I2S_RATE = 8000;   // 8 kHz square = the fleet's band timbre

#if USE_CARD_HW
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <ESP_I2S.h>
#include <Es8311.h>
// Runtime-pinned ST7789, exactly as on the T-Deck and for the same reason: TFT_eSPI's
// pin map is compile-time in one shared sketchbook User_Setup.h that is already pinned
// to the K10's ILI9341 (CLAUDE.md). Runtime pins mean this board can never break that.
static SPIClass gDispSpi(FSPI);
static Adafruit_ST7789 gTft(&gDispSpi, PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RST);
// One full-duplex I2S port: TX to the codec DAC (the band voice), RX from the codec
// ADC (the microphone). Both directions ride the same BCLK/LRCK, which is also what
// lets the ES8311 derive its MCLK from BCLK (Es8311.h).
static I2SClass gI2S;
static bool gCodecOk = false;
#endif

#if USE_IMU
#include <SparkFun_BMI270_Arduino_Library.h>
static BMI270 gImu;
static bool gImuOk = false;
#endif

// --- percept logs (the four SP0 evidence tiers this node carries) ------------
static linkpercept::Log gLinkLog;        // @LAT97 radio ranging
#if USE_WIFI_SCAN
static entitypercept::Log gEntityLog;    // @LAT96 entity co-occurrence
static uint32_t gLastScanKick = 0;
static bool gScanRunning = false;
#endif
#if USE_IMU
static motionpercept::Log gMotionLog;    // @LAT95 was-this-node-still
#endif
#if USE_MIC && USE_CARD_HW
static acousticpercept::Log gAcousticLog;  // @LAT94 what it heard
#endif

#if USE_BLE
// Feed a decoded, key-verified BLE fleet advert into the same link-percept histogram
// as ESP-NOW, tagged PROTO_BLE (runs in the BLE scan task — add() is increment-only).
static void onBleObserve(uint32_t peer, int rssi) {
  gLinkLog.add(peer, rssi, linkpercept::PROTO_BLE);
}
#endif

static const uint32_t kNodeId = NODE_CARDPUTER_1;
static const char* kTtdbPath = "/ttdb.md";
static const char* kBeliefPath = "/belief.md";
static const char* kRfcTtdbPath = "/rfc.ttdb.md";
static const char* kFeelTtdbPath = "/feelings.ttdb.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

// Which node the keyboard drives, cycled with 't'. Default the T-Deck: two handhelds
// side by side is the pair an operator most wants to compare, and the T-Deck answers
// over the air (the V4-A bridge answers CMDs only over USB).
static const uint32_t kTargets[] = {NODE_TDECK_1, NODE_K10_1, NODE_V4B_RELAY,
                                    NODE_V4C_EDGE, NODE_V4A_BRIDGE};
static const int kNumTargets = sizeof(kTargets) / sizeof(kTargets[0]);
static int gTargetIdx = 0;
static uint32_t gCmdTarget = NODE_TDECK_1;

// This node's musical voice. `g`/`x` (or a received CMD_PLAY/STOP) toggle it; the
// on/off state is persisted in NVS so a power-cycle RESUMES the part.
static Preferences gPrefs;
static bool gLocalPlay = false;
static void setLocalPlay(bool on) {
  gLocalPlay = on;
  gPrefs.putBool("play", on);
}
static const uint32_t PULSE_TONE_MS = 180;   // staccato note (blocks; keep short)
// The Cardputer's PART in the hero's-arc song (HeroArc.h): the NEWCOMER — silent
// through the whole story, because it is the one that listens, and in for the finale.
static const score::Part& kPart = heroarc::kNewcomer;

static const char* nodeName(uint32_t id) {
  switch (id) {
    case NODE_V4A_BRIDGE:    return "V4-A";
    case NODE_V4B_RELAY:     return "V4-B";
    case NODE_V4C_EDGE:      return "V4-C";
    case NODE_K10_1:         return "K10";
    case NODE_TDECK_1:       return "T-Deck";
    case NODE_CARDPUTER_1:   return "Card";
    case NODE_BROADCAST:     return "ALL";
    default:                 return "?";
  }
}

Ttdb gDb;         // fleet globe — the network-facing TTDB (shared/synced/attested)
Ttdb gRfcDb;      // RFC corpus globe — view-only (never shared over the mesh)
Ttdb gFeelDb;     // feelings globe — affective landscape + band overlay (view-only)
static bool gRfcLoaded = false;
static bool gFeelLoaded = false;
TtdbShare* gShare = nullptr;

// Globe views ENTER cycles through, matching the T-Deck so the two handhelds behave
// the same. Only the fleet TTDB touches the mesh — TTDB_REQ / @LAT99 sync / @LAT98
// belief always operate on gDb, never gViewDb.
enum GlobeView { VIEW_FEELINGS = 0, VIEW_FLEET, VIEW_RFC, VIEW_COUNT };
static int   gView = VIEW_FEELINGS;
static Ttdb* gViewDb = &gFeelDb;
static int   gViewSel[VIEW_COUNT] = {-1, -1, -1};
static inline const char* viewName(int v) {
  return v == VIEW_RFC ? "RFC" : v == VIEW_FLEET ? "SemPos" : "Feel";
}

toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);
static uint32_t gSeq = 1;

// Console state rendered on the screen (updated from loop() + the recv callback; the
// callback only flips gScreenDirty — no SPI/I2C from the WiFi task).
static uint32_t gEspRx = 0;
static uint32_t gServed = 0;
static uint32_t gCmdSent = 0;
static uint32_t gReplies = 0;
static uint32_t gLastReplySrc = 0;
static int16_t  gLastReplyTemp = 0;
static volatile bool gScreenDirty = true;

// --- console panes + event log (SP6-T, sized for a 240x135 panel) ------------
enum Pane { PANE_MAIN, PANE_CONSOLE };
static Pane gPane = PANE_MAIN;
static bool gPaneChanged = true;

#define LOG_LINES 4                  // the bottom half is short on this screen
static char gLog[LOG_LINES][40];
static int  gLogHead = 0, gLogCount = 0;
static void logLine(const char* s) {
  strncpy(gLog[gLogHead], s, 39);
  gLog[gLogHead][39] = 0;
  gLogHead = (gLogHead + 1) % LOG_LINES;
  if (gLogCount < LOG_LINES) gLogCount++;
  gScreenDirty = true;
}

static int gSel = -1;      // selected TTDB record (globe cursor)
static uint32_t gLastRenderMs = 0;   // cost of the last screen repaint (loop profile)

// --- wall clock (TTN-RFC-0008) ----------------------------------------------
static int64_t gClockOffsetMs = 0;
static bool gSynced = false;
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return (int64_t)millis() + gClockOffsetMs; }
static volatile bool gSyncPending = false;
static uint32_t gPendSyncId = 0;
static uint64_t gPendEpochMs = 0;
static uint32_t gPendRecvMs = 0;

// --- pushed belief (TTN-RFC-0009) -------------------------------------------
// Store + attest like V4-B / the T-Deck (no agent cadence to retune, so no DIRECTIVE
// action). Exactly-once on a monotonic belief_id.
static bool gBeliefAdopted = false;
static uint32_t gBeliefId = 0;
static bool gPutActive = false;
static uint32_t gPutId = 0, gPutTotal = 0, gPutCrc = 0, gPutNext = 0, gPutCrcRun = 0;
static volatile bool gBeliefSyncPending = false;
static uint32_t gPendBeliefId = 0, gPendBeliefBytes = 0, gPendBeliefCrc = 0;
static uint32_t gPendBeliefRecvMs = 0;

static bool handlePutSlice(const toot::Toot& t) {
  uint32_t target, bid, total, crc, off;
  const uint8_t* data;
  uint16_t len;
  if (!toot::parsePut(t, target, bid, total, crc, off, data, len)) return false;
  if (target != kNodeId) return false;
  if (gBeliefAdopted && bid == gBeliefId) return true;  // already adopted: re-ACK

  if (off == 0) {
    File f = LittleFS.open(kBeliefPath, "w");
    if (!f) return false;
    f.write(data, len);
    f.close();
    gPutActive = true; gPutId = bid; gPutTotal = total; gPutCrc = crc;
    gPutNext = len; gPutCrcRun = toot::crc32(0, data, len);
  } else if (gPutActive && bid == gPutId && off == gPutNext) {
    File f = LittleFS.open(kBeliefPath, "a");
    if (!f) return false;
    f.write(data, len);
    f.close();
    gPutNext += len; gPutCrcRun = toot::crc32(gPutCrcRun, data, len);
  } else if (gPutActive && bid == gPutId && off < gPutNext) {
    return true;                           // duplicate slice (ACK lost): idempotent
  } else {
    return false;                          // gap / unknown belief: force retransmit
  }

  if (gPutActive && bid == gPutId && gPutNext >= gPutTotal) {
    gPutActive = false;
    if (gPutCrcRun == gPutCrc) {
      gBeliefAdopted = true; gBeliefId = bid;
      gPendBeliefId = bid; gPendBeliefBytes = gPutTotal; gPendBeliefCrc = gPutCrc;
      gPendBeliefRecvMs = millis();
      gBeliefSyncPending = true;           // attest to the live TTDB from loop()
    } else {
      Serial.printf("[belief] id=%lu CRC MISMATCH got %08lX want %08lX (%luB)\n",
                    (unsigned long)bid, (unsigned long)gPutCrcRun,
                    (unsigned long)gPutCrc, (unsigned long)gPutTotal);
    }
  }
  return true;
}

// --- fleet pulse (TTN-RFC-0010) ---------------------------------------------
#if USE_PULSE
static pulse::Engine gPulse;
static uint32_t gNeighbors[8] = {0};
static uint32_t gNeighborSeen[8] = {0};
static int      gNeighborCount = 0;
static const uint32_t NEIGHBOR_REJOIN_GAP_MS = 3000;
// Fast-lock a neighbor that is brand-new OR returning after a gap (a power-cycle): if
// we hold the baton we beacon immediately so the (re)joiner locks within a round trip
// instead of waiting out PULSE_RESYNC_PERIOD. A steadily-present neighbor does not
// retrigger it, so steady-state traffic stays minimal.
static bool neighborNeedsLock(uint32_t src, uint32_t now) {
  for (int i = 0; i < gNeighborCount; ++i) {
    if (gNeighbors[i] == src) {
      bool rejoined = (uint32_t)(now - gNeighborSeen[i]) >= NEIGHBOR_REJOIN_GAP_MS;
      gNeighborSeen[i] = now;
      return rejoined;
    }
  }
  if (gNeighborCount < (int)(sizeof(gNeighbors) / sizeof(gNeighbors[0]))) {
    gNeighbors[gNeighborCount] = src;
    gNeighborSeen[gNeighborCount] = now;
    gNeighborCount++;
  }
  return true;   // brand new
}

// millis() of the last HELLO from `id` (0 = never) — the feelings globe reads this to
// show each band member's liveness beside its eyeball.
static uint32_t nodeLastSeen(uint32_t id) {
  for (int i = 0; i < gNeighborCount; ++i)
    if (gNeighbors[i] == id) return gNeighborSeen[i];
  return 0;
}
#endif

// --- transports -------------------------------------------------------------
// ESP-NOW TX is async with a shallow queue; a TTDB burst overruns it and drops all but
// the first frames. Gate each send on the prior frame's TX-complete callback so the
// whole stream survives the air (the K10's Phase-1b lesson).
static volatile bool gEspNowTxDone = true;
static ESPNOW_SEND_CB(onEspNowSend, mac, status) {
  (void)status;
  gEspNowTxDone = true;
}
static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  uint32_t t0 = millis();
  while (!gEspNowTxDone && millis() - t0 < 50) delay(1);
  gEspNowTxDone = false;
  bool ok = esp_now_send(kBroadcast, frame, len) == ESP_OK;
  delay(6);   // breathing room for the bridge to drain each frame to USB-CDC
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

// TTN-RFC-0007: ACK `orig` — for a freshly-accepted want_ack toot and for re-ACKing a
// dedup-dropped replay (§5).
static void emitAck(const toot::Toot& orig, uint8_t status,
                    TtdbShare::SendFn reply, void* ctx) {
  toot::Toot ack;
  toot::makeAck(orig, kNodeId, gSeq++, status, ack);
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(ack, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) reply(frame, flen, ctx);
}

// Inject a CMD toot — the console's operator function. Fire-and-forget (not want_ack):
// CMD_GET_STATUS is answered by the target's STATUS PERCEPT, which we collect.
static void emitCmdTo(uint8_t op, uint32_t target, const uint8_t* args, uint8_t argn) {
  uint8_t body[toot::MAX_BODY];
  body[0] = op;
  toot::put_u32(body + 1, target);
  if (argn && args) memcpy(body + 5, args, argn);
  emit(toot::CMD, body, (uint8_t)(5 + argn), sendEspNow, nullptr);
  gCmdSent++;
  gScreenDirty = true;
  char lg[40];
  snprintf(lg, sizeof(lg), "cmd op%u -> %s", op, nodeName(target));
  logLine(lg);
  Serial.printf("[cmd] op=%u -> 0x%08X (#%lu)\n", op, (unsigned)target,
                (unsigned long)gCmdSent);
}
static void emitCmd(uint8_t op, const uint8_t* args, uint8_t argn) {
  emitCmdTo(op, gCmdTarget, args, argn);
}

#if USE_PULSE
// Walk the hero's-arc story: broadcast CMD_SET_SCENE (only the conductor applies a
// scene change, so at most one node acts) and also try locally in case WE hold the
// baton (a broadcast does not loop back to its sender).
static void emitSetScene(uint16_t scene) {
  uint8_t a[2];
  toot::put_u16(a, scene);
  emitCmdTo(toot::CMD_SET_SCENE, NODE_BROADCAST, a, 2);
  gPulse.setScene(scene, millis());
  Serial.printf("[scene] requested scene %u %s\n", scene, heroarc::sceneName(scene));
}
#endif

// STATUS telemetry for the `monitor` table. No sensor cursor/temp on a console, so
// those fields are 0; report the synced state + epoch, plus the PULSE tail for `band`.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, 0);
  p[6] = gSynced ? toot::STATUS_SYNCED : 0;
  toot::put_u64(p + 7, gSynced ? (uint64_t)nowEpochMs() : 0);
#if USE_PULSE
  uint32_t now = millis();
  uint8_t bib = 0; uint16_t ph = 0; uint32_t bc = 0;
  bool playing = gPulse.phaseNow(now, bib, ph, bc);
  const pulse::Chart& ch = gPulse.chart();
  toot::put_u32(p + 15, ch.conductor_id);
  toot::put_u32(p + 19, ch.era);
  toot::put_u16(p + 23, ch.beat_period_ms);
  toot::put_u64(p + 25, playing ? (uint64_t)gPulse.pulseNow(now) : 0);
  toot::put_u64(p + 33, ch.downbeat_epoch);
  p[41] = bib;
  p[42] = (playing ? toot::PSTATE_PLAYING : 0) |
          (gPulse.conductor() ? toot::PSTATE_CONDUCTOR : 0);
  toot::put_u16(p + 43, ch.scene_id);
  return (uint8_t)toot::STATUS_PULSE_PAYLOAD_LEN;
#else
  return (uint8_t)toot::STATUS_PAYLOAD_LEN;
#endif
}

// Serve a TTDB_REQ addressed to this node: belief mode streams the stored /belief.md
// (TTN-RFC-0009 §3 readback); any other mode streams the live TTDB. Both stream a
// burst, so radio callers must invoke this from loop().
static void serveTtdbReq(const toot::Toot& req, TtdbShare::SendFn send, void* ctx) {
  if (!gShare || TtdbShare::requestTarget(req) != kNodeId) return;
  if (req.payload_len >= 1 && req.payload[0] == toot::TTDB_REQ_BELIEF) {
    static uint8_t bbuf[1536];
    File f = LittleFS.open(kBeliefPath, "r");
    size_t n = f ? f.read(bbuf, sizeof(bbuf)) : 0;
    if (f) f.close();
    gShare->handleBufferRequest(bbuf, n, send, ctx);
  } else {
    gShare->handleRequest(req, send, ctx);
  }
  gServed++;
}

#if USE_CARD_HW
static void toneI2S(float freq, uint32_t ms, float amp);
#endif

// Prune every consumed percept lane. This node carries four tiers, so a
// CMD_CLEAR_PERCEPTS has four lanes to compact — all or nothing, so a partial prune
// is reported as a failure and the laptop retries (`proximity --clear` depends on it).
static bool clearPerceptLanes() {
  bool ok = gDb.removeLane(97);
  ok = gDb.removeLane(96) && ok;
  ok = gDb.removeLane(95) && ok;
  ok = gDb.removeLane(94) && ok;
  if (ok)
    Serial.printf("[percept] lanes 94-97 cleared (TTDB now %uB, %dr)\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  return ok;
}

// Dispatch a decoded, authenticated toot on any transport. `reply` is the transport to
// answer on. Dedup is radio-only (applied in onEspNowRecv before this), so the trusted
// USB link stays un-deduped and the laptop can retry.
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
  bool accepted = false;
  switch (t.type) {
    case toot::TTDB_REQ:
      serveTtdbReq(t, reply, ctx);   // the streamed reply is itself the confirmation
      break;
    case toot::TTDB_PUT:
      accepted = handlePutSlice(t);
      break;
    case toot::CMD:
      // The chart belongs to the CONDUCTOR, so only the conductor applies a scene
      // change. We are normally a follower and learn the scene from the next beacon —
      // which is also why broadcasting the command is safe.
      if (toot::cmdOp(t) == toot::CMD_SET_SCENE &&
          (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
#if USE_PULSE
        if (gPulse.conductor() && t.payload_len >= 7) {
          uint16_t want = toot::get_u16(t.payload + 5);
          gPulse.setScene(want, millis());
          accepted = (gPulse.scene() == want);   // ACK the achieved state
        }
#endif
        break;
      }
      // Band-wide play/stop honor the broadcast target; everything else is addressed.
      if ((toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP) &&
          toot::cmdTarget(t) == NODE_BROADCAST) {
        setLocalPlay(toot::cmdOp(t) == toot::CMD_PLAY);
#if USE_PULSE
        if (gLocalPlay) gPulse.armSong(heroarc::SCENE_ALONE, millis());
        else            gPulse.disarmSong();
#endif
        gScreenDirty = true;
        break;
      }
      if (toot::cmdTarget(t) == kNodeId) {
        bool ok = true;
        switch (toot::cmdOp(t)) {
          case toot::CMD_GET_STATUS: {
            uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
            uint8_t slen = buildStatus(body);
            emit(toot::PERCEPT, body, slen, reply, ctx);
            break;
          }
          case toot::CMD_BEEP: {
            // The Cardputer has a real speaker, so it answers a beep audibly (the
            // T-Deck's no-op default was for a node without one). Args: freq, ms.
#if USE_CARD_HW
            uint16_t f = t.payload_len >= 7 ? toot::get_u16(t.payload + 5) : 880;
            uint16_t d = t.payload_len >= 9 ? toot::get_u16(t.payload + 7) : 200;
            if (d > 1000) d = 1000;          // never block the loop for a whole second+
            if (gCodecOk) toneI2S((float)f, d, 12000.0f);
#endif
            break;
          }
          case toot::CMD_PLAY:
            setLocalPlay(true);
#if USE_PULSE
            gPulse.armSong(heroarc::SCENE_ALONE, millis());
#endif
            break;
          case toot::CMD_STOP:
            setLocalPlay(false);
#if USE_PULSE
            gPulse.disarmSong();
#endif
            break;
          case toot::CMD_CLEAR_PERCEPTS:
            // Flash rewrite: reaches here only from loop() (the radio path defers).
            // ACK only on success, so a failed prune is loud and the laptop retries.
            ok = clearPerceptLanes();
            break;
          default: break;                    // ping / set-* (no-op here)
        }
        accepted = ok;
        gScreenDirty = true;
      }
      break;
    case toot::PERCEPT: {
      // A collected reply from a node we queried: stash it for the fleet view.
      gReplies++;
      gLastReplySrc = t.src_node_id;
      if (t.payload_len >= 6) gLastReplyTemp = (int16_t)toot::get_u16(t.payload + 4);
      gScreenDirty = true;
      break;
    }
    case toot::TIME_SYNC: {
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          gClockOffsetMs = (int64_t)ems - (int64_t)recv_ms;
          gSynced = true;
          gLastSyncId = sid;
          gPendSyncId = sid; gPendEpochMs = ems; gPendRecvMs = recv_ms;
          gSyncPending = true;       // append @LAT99 log from loop()
        }
        accepted = true;             // ACK the want_ack TIME_SYNC (idempotent)
      }
      break;
    }
    case toot::TIME_REQ: {
      uint32_t pid, target;
      if (toot::parseTimeReq(t, pid, target) && target == kNodeId) {
        uint8_t body[toot::TIME_RESP_PAYLOAD_LEN];
        toot::put_u32(body + 0, pid);
        toot::put_u64(body + 4, (uint64_t)nowEpochMs());
        emit(toot::TIME_RESP, body, sizeof(body), reply, ctx);
      }
      break;
    }
#if USE_PULSE
    case toot::PULSE: {
      pulse::Chart c;
      uint64_t cond_epoch;
      if (toot::parsePulse(t, c.conductor_id, c.era, cond_epoch, c.downbeat_epoch,
                           c.beat_period_ms, c.meter_beats, c.flags, &c.scene_id))
        gPulse.onBeacon(c, cond_epoch, millis());
      break;
    }
    case toot::HELLO:
      if (neighborNeedsLock(t.src_node_id, millis())) gPulse.noteNeighbor(millis());
      break;
#endif
    default:
      break;
  }
  if (accepted && (t.flags & toot::FLAG_WANT_ACK))
    emitAck(t, toot::ACK_ACCEPTED, reply, ctx);
}

// A TTDB_REQ / TTDB_PUT arriving over ESP-NOW is stashed and served from loop(): a
// burst reply or a flash write must not run in the WiFi recv callback (K10 lessons).
static volatile bool gReqPending = false;
static toot::Toot gPendingReq;
static volatile bool gPutPending = false;
static toot::Toot gPendingPut;
static volatile bool gClearPending = false;
static toot::Toot gPendingClear;

static ESPNOW_RECV_CB_INFO(onEspNowRecv, info, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) return;
  // SP0 link percept: an authenticated frame is a distance measurement in disguise.
  // Logged BEFORE dedup — a retried duplicate is a real reception.
  gLinkLog.add(t.src_node_id, tootEspNowRssi(info), linkpercept::PROTO_ESPNOW);
  if (t.chunk_total > 1) return;            // no chunked consumer on the console
  if (gDedup.seen(t.src_node_id, t.toot_seq)) {
    if (t.flags & toot::FLAG_WANT_ACK)      // TTN-RFC-0007 §5: re-ACK a lost-ACK dup
      emitAck(t, toot::ACK_ACCEPTED, sendEspNow, nullptr);
    return;
  }
  gEspRx++;
  gScreenDirty = true;

  if (t.type == toot::TTDB_REQ) {
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }   // defer burst
    return;
  }
  if (t.type == toot::TTDB_PUT) {
    if (!gPutPending) { gPendingPut = t; gPutPending = true; }   // defer flash
    return;
  }
  if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
      toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
    if (!gClearPending) { gPendingClear = t; gClearPending = true; }
    return;
  }
  handleToot(t, sendEspNow, nullptr);       // cheap toots (TIME_*, CMD, PERCEPT, PULSE)
}

// Append an @LAT99 sync-log record (deferred from the recv path). n = count of existing
// lat-99 records so each is unique under collision_policy: reject.
static void appendSyncRecord() {
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == 99) ++n;
  uint32_t t_sec = (uint32_t)(gPendEpochMs / 1000ULL);
  int64_t offset = (int64_t)gPendEpochMs - (int64_t)gPendRecvMs;
  char rec[200];
  int m = snprintf(
      rec, sizeof(rec),
      "\n---\n\n@LAT99LON%d | created:%lu | updated:%lu | relates:logs@LAT0LON0"
      "\n\n**SYNC** id:%lu t_ms:%llu recv_ms:%lu offset_ms:%lld\n",
      n, (unsigned long)t_sec, (unsigned long)t_sec, (unsigned long)gPendSyncId,
      (unsigned long long)gPendEpochMs, (unsigned long)gPendRecvMs,
      (long long)offset);
  if (m > 0 && gDb.appendRecord(rec, (size_t)m))
    Serial.printf("[sync] id=%lu offset=%lldms logged @LAT99LON%d (TTDB now %uB)\n",
                  (unsigned long)gPendSyncId, (long long)offset, n,
                  (unsigned)gDb.fileSize());
  else
    Serial.println("[sync] appendRecord FAILED");
}

// Append a @LAT98 BELIEF-ADOPTED attestation (deferred). No DIRECTIVE to act on, so
// this records the integrated bytes/crc only.
static void appendBeliefRecord() {
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == 98) ++n;
  uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
  char rec[256];
  int m = snprintf(
      rec, sizeof(rec),
      "\n---\n\n@LAT98LON%d | created:%lu | updated:%lu | relates:adopts@LAT0LON0"
      "\n\n**BELIEF-ADOPTED** id:%lu bytes:%lu crc:%08lX recv_ms:%lu\n",
      n, (unsigned long)t_sec, (unsigned long)t_sec, (unsigned long)gPendBeliefId,
      (unsigned long)gPendBeliefBytes, (unsigned long)gPendBeliefCrc,
      (unsigned long)gPendBeliefRecvMs);
  if (m > 0 && gDb.appendRecord(rec, (size_t)m))
    Serial.printf("[belief] adopted id=%lu %luB crc=%08lX -> @LAT98LON%d (TTDB %uB)\n",
                  (unsigned long)gPendBeliefId, (unsigned long)gPendBeliefBytes,
                  (unsigned long)gPendBeliefCrc, n, (unsigned)gDb.fileSize());
  else
    Serial.println("[belief] appendRecord FAILED");
}

// Count existing records in a percept lane (the LON index of the next one).
static int laneCount(int lat) {
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == lat) ++n;
  return n;
}

#if USE_WIFI_SCAN
// Non-blocking duty-cycled WiFi scan (see v4a_bridge.ino for the rationale). Coexists
// with BLE the way V4-A does — the radio arbiter time-slices them.
static void serviceWifiScan() {
  uint32_t now = millis();
  if (!gScanRunning && (now - gLastScanKick >= WIFI_SCAN_PERIOD_MS || gLastScanKick == 0)) {
    if (WiFi.scanNetworks(true /*async*/, false /*show_hidden*/) == WIFI_SCAN_RUNNING) {
      gScanRunning = true;
      gLastScanKick = now;
    }
  }
  if (gScanRunning) {
    int found = WiFi.scanComplete();
    if (found >= 0) {
      for (int i = 0; i < found; ++i) {
        uint8_t* b = WiFi.BSSID(i);
        if (b) gEntityLog.add(b, (int)WiFi.RSSI(i), entitypercept::KIND_WIFI_AP);
      }
      WiFi.scanDelete();
      esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
      gScanRunning = false;
      Serial.printf("[wifi] scan: %d AP(s) folded into @LAT96 window\n", found);
    }
  }
}
#endif

// --- audio, keyboard, IMU, screen (all gated on the real board) --------------
#if USE_CARD_HW
// Synthesize a `ms`-long SQUARE wave at `freq` as 16-bit stereo samples (L=R). Square,
// not sine, to match the rest of the band: the V4s' hand-wired amps only reproduce
// squares, so the whole fleet plays one timbre on purpose. Blocks ~ms, so it runs from
// setup()/loop() only — never a callback.
static void toneI2S(float freq, uint32_t ms, float amp = 16000.0f) {
  if (!gCodecOk) return;
  const int N = 256;
  int16_t buf[N * 2];
  uint32_t total = (uint32_t)((uint64_t)I2S_RATE * ms / 1000);
  float phase = 0.0f, inc = 2.0f * (float)M_PI * freq / (float)I2S_RATE;
  uint32_t done = 0;
  while (done < total) {
    uint32_t n = total - done; if (n > (uint32_t)N) n = N;
    for (uint32_t i = 0; i < n; ++i) {
      int16_t s = (phase < (float)M_PI) ? (int16_t)amp : (int16_t)-amp;
      phase += inc; if (phase > 2.0f * (float)M_PI) phase -= 2.0f * (float)M_PI;
      buf[2 * i] = s; buf[2 * i + 1] = s;
    }
    gI2S.write((uint8_t*)buf, n * 2 * sizeof(int16_t));
    done += n;
  }
}

// The fleet's shared boot voice: two rising toots, C4 -> G4.
static const float STARTUP_TOOT_AMP = 6000.0f;
static void playStartupToot() {
  toneI2S(262.0f, 220, STARTUP_TOOT_AMP);
  delay(40);
  toneI2S(392.0f, 380, STARTUP_TOOT_AMP);
}

// --- TCA8418 keyboard --------------------------------------------------------
// The ADV scans its 56-key matrix with a TCA8418 (7 columns x 8 rows), which reports
// key numbers, not characters: key = col*10 + row + 1, and the FIFO byte carries the
// pressed flag in bit 7. The physical layout interleaves TCA rows, so the map below is
// written out row by row exactly as the keys sit on the deck — it is the one piece of
// this sketch that cannot be derived from anything, only tabulated.
static const uint8_t TCA_REG_CFG      = 0x01;
static const uint8_t TCA_REG_INT_STAT = 0x02;
static const uint8_t TCA_REG_KEY_LCK  = 0x03;   // key lock / event counter
static const uint8_t TCA_REG_FIFO     = 0x04;
static const uint8_t TCA_REG_GPI_EM1  = 0x09;
static const uint8_t TCA_REG_KP_GPIO1 = 0x1D;   // rows 0-7 as keypad
static const uint8_t TCA_REG_KP_GPIO2 = 0x1E;   // cols 0-7 as keypad
static const uint8_t TCA_REG_KP_GPIO3 = 0x1F;   // cols 8-9 (unused here)

static bool kbdWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(KBD_ADDR);
  Wire.write(reg);
  Wire.write(val);
  return Wire.endTransmission() == 0;
}
static int kbdRead(uint8_t reg) {
  Wire.beginTransmission(KBD_ADDR);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return -1;
  if (Wire.requestFrom((int)KBD_ADDR, 1) != 1) return -1;
  return Wire.read();
}

static bool kbdBegin() {
  // The controller boots asleep; these five writes are what wake it into autonomous
  // matrix scanning. GP1 = all 8 rows, GP2 = all 8 columns (7 used), GP3 unused.
  if (!kbdWrite(TCA_REG_KP_GPIO1, 0xFF)) return false;
  kbdWrite(TCA_REG_KP_GPIO2, 0xFF);
  kbdWrite(TCA_REG_KP_GPIO3, 0x00);
  kbdWrite(TCA_REG_GPI_EM1, 0x00);        // no GPIO event mode — keypad events only
  kbdWrite(TCA_REG_CFG, 0x3E);            // KE_IEN | INT_CFG | OVR_FLOW | K_LCK | AI
  // Drain anything the controller latched while it was waking.
  for (int i = 0; i < 16 && kbdRead(TCA_REG_FIFO) > 0; ++i) {}
  kbdWrite(TCA_REG_INT_STAT, 0x1F);       // clear all pending interrupt flags
  return true;
}

// Keycode -> character. Index is the TCA key number (1..68); 0 = no binding. Only the
// keys this console acts on need real characters, but the full alphanumeric map is
// filled in so the node is ready for text entry later. Arrows and ENTER get private
// codes above ASCII so the switch in loop() can dispatch them.
enum : char {
  KEY_UP_C    = 0x11,
  KEY_DOWN_C  = 0x12,
  KEY_LEFT_C  = 0x13,
  KEY_RIGHT_C = 0x14,
  KEY_ENTER_C = '\n',
  KEY_ESC_C   = 0x1B,
  KEY_BKSP_C  = 0x08,
  KEY_FN_C    = 0x01,   // modifiers are reported but not acted on
  KEY_SHIFT_C = 0x02,
  KEY_CTRL_C  = 0x03,
  KEY_OPT_C   = 0x04,
  KEY_ALT_C   = 0x05,
};

static char kbdMap(uint8_t key) {
  switch (key) {
    // row 1: esc 1 2 3 4 5 6 7 8 9 0 - = del
    case 1:  return KEY_ESC_C;
    case 5:  return '1';  case 11: return '2';  case 15: return '3';
    case 21: return '4';  case 25: return '5';  case 31: return '6';
    case 35: return '7';  case 41: return '8';  case 45: return '9';
    case 51: return '0';  case 55: return '-';  case 61: return '=';
    case 65: return KEY_BKSP_C;
    // row 2: tab q w e r t y u i o p [ ] backslash
    case 2:  return '\t';
    case 6:  return 'q';  case 12: return 'w';  case 16: return 'e';
    case 22: return 'r';  case 26: return 't';  case 32: return 'y';
    case 36: return 'u';  case 42: return 'i';  case 46: return 'o';
    case 52: return 'p';  case 56: return '[';  case 62: return ']';
    case 66: return '\\';
    // row 3: fn shift a s d f g h j k l up ' enter
    case 3:  return KEY_FN_C;    case 7:  return KEY_SHIFT_C;
    case 13: return 'a';  case 17: return 's';  case 23: return 'd';
    case 27: return 'f';  case 33: return 'g';  case 37: return 'h';
    case 43: return 'j';  case 47: return 'k';  case 53: return 'l';
    case 57: return KEY_UP_C;    case 63: return '\'';
    case 67: return KEY_ENTER_C;
    // row 4: ctrl opt alt z x c v b n m left down right space
    case 4:  return KEY_CTRL_C;  case 8:  return KEY_OPT_C;
    case 14: return KEY_ALT_C;
    case 18: return 'z';  case 24: return 'x';  case 28: return 'c';
    case 34: return 'v';  case 38: return 'b';  case 44: return 'n';
    case 48: return 'm';
    case 54: return KEY_LEFT_C;  case 58: return KEY_DOWN_C;
    case 64: return KEY_RIGHT_C; case 68: return ' ';
    default: return 0;
  }
}

// Pop one PRESS from the controller's FIFO (releases are discarded — this console acts
// on the falling edge, like the T-Deck's one-byte-per-press keyboard). Returns 0 when
// nothing is pending.
static char readKey() {
  int ev = kbdRead(TCA_REG_FIFO);
  if (ev <= 0) return 0;
  bool pressed = (ev & 0x80) != 0;
  uint8_t key = (uint8_t)(ev & 0x7F);
  if (!pressed) return 0;
  return kbdMap(key);
}
#endif  // USE_CARD_HW

#if USE_IMU
// Sample the accelerometer into the motion log. Called at ~20 Hz from loop(): fast
// enough to catch a stride, slow enough to cost nothing. Also returns the current tilt
// so the globe can be rolled by tipping the device.
static float gTiltX = 0.0f, gTiltY = 0.0f;    // low-passed, in g
static void serviceImu(uint32_t now) {
  static uint32_t last = 0;
  if (now - last < 50) return;                 // 20 Hz
  last = now;
  if (!gImuOk || gImu.getSensorData() != BMI2_OK) return;
  int ax = (int)(gImu.data.accelX * 1000.0f);  // g -> milli-g
  int ay = (int)(gImu.data.accelY * 1000.0f);
  int az = (int)(gImu.data.accelZ * 1000.0f);
  gMotionLog.add(ax, ay, az, now);
  // Heavy low-pass: the globe should answer a deliberate tilt, not a hand tremor.
  gTiltX += (gImu.data.accelX - gTiltX) * 0.12f;
  gTiltY += (gImu.data.accelY - gTiltY) * 0.12f;
}
#endif

#if USE_MIC && USE_CARD_HW
// Read whatever the codec's ADC has ready and fold it into the acoustic window. The
// I2S RX channel free-runs, so this drains rather than waits — a blocking read here
// would stall the mesh. Each block is timestamped on the FLEET clock when we are
// synced, because that timestamp is the entire point of the tier (TDoA).
static void serviceMic(uint32_t now) {
  if (!gCodecOk) return;
  static int16_t block[256];                   // 128 stereo frames @ 8 kHz = 16 ms
  int avail = gI2S.available();
  if (avail < (int)sizeof(block)) return;
  size_t got = gI2S.readBytes((char*)block, sizeof(block));
  if (got < sizeof(int16_t) * 2) return;
  // De-interleave to mono by taking the left slot (the codec is single-channel; both
  // slots carry the same mic).
  static int16_t mono[128];
  size_t frames = got / (sizeof(int16_t) * 2);
  if (frames > 128) frames = 128;
  for (size_t i = 0; i < frames; ++i) mono[i] = block[i * 2];
  uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)now;
  gAcousticLog.addBlock(mono, frames, t_ms, now);
}
#endif

#if USE_CARD_HW
// --- SP6-T screen geometry (240x135) ----------------------------------------
// A third of the T-Deck's pixels, so the layout is tighter: one status line, a globe
// canvas, and a four-line bottom pane that flips between the selected record and the
// console log.
static const int SCR_W = 240, SCR_H = 135;
static const int TEXT_COLS = 39;          // 39 * 6 px = 234, fits with a 3 px margin
static const int STATUS_Y  = 1;
static const int GLOBE_X   = 0,  GLOBE_Y = 12;
static const int GLOBE_W   = 240, GLOBE_H = 76;
static const int BOTTOM_Y  = 91;
static const int BOTTOM_H  = SCR_H - BOTTOM_Y;

// The globe is drawn into an off-screen canvas and block-pushed, so rotation is
// flicker-free (the K10 canvas-blink lesson). 240x76x2 = ~36 KB of internal RAM (the
// Stamp-S3A has no PSRAM), allocated once. Null-safe: a failed alloc falls back to a
// text top bar rather than a dead screen.
static GFXcanvas16* gGlobe = nullptr;
static float gRotLat = 0.0f, gRotLon = 0.0f;
static float gTgtLat = 0.0f, gTgtLon = 0.0f;
static bool  gAnim = false;
static const float kZoomLevels[5] = {1.15f, 2.0f, 2.85f, 4.05f, 5.75f};
static int   gZoomIdx = 1;
static float gZoom = kZoomLevels[1];
static const int kZoomMax = (int)(sizeof(kZoomLevels) / sizeof(kZoomLevels[0])) - 1;
static bool  gGlobeDirty = true;
static bool  gBottomDirty = true;

static inline uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}
// Deterministic per-record color (TTCP-RFC-0002 §3.3, hash of the record id).
static uint16_t nodeColor(int16_t lat, int16_t lon) {
  uint32_t h = (uint32_t)(lat * 73856093) ^ (uint32_t)(lon * 19349663);
  return rgb565(90 + (h & 0x7F), 90 + ((h >> 7) & 0x7F), 90 + ((h >> 14) & 0x7F));
}

// Draw one full-width padded row (opaque bg) at text size 1, so a re-print erases the
// whole line and never leaves trailing glyphs.
static void drawWide(int y, uint16_t color, const char* s) {
  char pad[TEXT_COLS + 2];
  snprintf(pad, sizeof(pad), "%-*s", TEXT_COLS, s);
  pad[TEXT_COLS] = 0;
  gTft.setTextColor(color, ST77XX_BLACK);
  gTft.setTextSize(1);
  gTft.setCursor(3, y);
  gTft.print(pad);
}

// Project a record's @LAT/LON (degrees, TTCP-RFC-0002 §2.1) through the current globe
// rotation to screen space. z>0 means the point faces the camera (front-face cull).
static void projectLL(float latDeg, float lonDeg, float R, int cx, int cy,
                      float sLat, float cLat, float sLon, float cLon,
                      int& sx, int& sy, float& z) {
  const float D2R = 0.01745329f;
  float la = latDeg * D2R, lo = lonDeg * D2R;
  float x = cosf(la) * sinf(lo), y = sinf(la), zz = cosf(la) * cosf(lo);
  float x1 = x * cLon - zz * sLon, z1 = x * sLon + zz * cLon, y1 = y;
  float y2 = y1 * cLat - z1 * sLat, z2 = y1 * sLat + z1 * cLat;
  sx = cx + (int)(x1 * R);
  sy = cy - (int)(y2 * R);
  z  = z2;
}

// True for records that are real navigable nodes (skip the -90 marker and the runtime
// percept/belief/sync lanes at lat 94-99 — the lat<90 bound covers all of them).
static inline bool isNodeRecord(const TtdbRecord& r) {
  return r.lat > -90 && r.lat < 90;
}

// Per-node belief attributes parsed once at load: friendly name (the globe label),
// position sigma in metres (the uncertainty ring), and the mesh node id that marks a
// live fleet member on the feelings globe.
static char  gNodeName[TTDB_MAX_RECORDS][12];
static float gNodeSigmaM[TTDB_MAX_RECORDS];
static uint32_t gNodeMeshId[TTDB_MAX_RECORDS];
// ...and the record's outgoing edges, cached the same way. `Ttdb::edgesAt()` re-OPENS
// the TTDB file on every call, so drawing edges straight from it costs one LittleFS
// open per record per frame — measured at 321-767 ms for a single repaint of the
// 45-record feelings globe, which showed up on the mesh as a 419 ms `verify` rtt (the
// toot link is serviced once per loop pass, so the slowest pass IS the response time).
// parseNodeAttrs already reads each record's header line, so caching the edges from
// that same buffer costs no extra I/O at all. Kept compact — only what the globe draws.
#define NODE_EDGE_MAX 4
struct CachedEdge { int16_t lat, lon; bool lora; };
static CachedEdge gNodeEdges[TTDB_MAX_RECORDS][NODE_EDGE_MAX];
static uint8_t    gNodeEdgeCount[TTDB_MAX_RECORDS];
static const float DEG_PER_M = 1.0f;         // companion.py fleetmap metres->degrees
static const float SIGMA_VIS_SCALE = 0.35f;

static void parseNodeAttrs() {
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    gNodeName[i][0] = 0;
    gNodeSigmaM[i] = 0.0f;
    gNodeMeshId[i] = 0;
    gNodeEdgeCount[i] = 0;
    if (!isNodeRecord(gViewDb->record(i))) continue;
    size_t off, len;
    if (!gViewDb->recordSpan(i, off, len)) continue;
    char buf[400];
    size_t n = len < sizeof(buf) - 1 ? len : sizeof(buf) - 1;
    n = gViewDb->readBytes(off, (uint8_t*)buf, n);
    buf[n] = 0;
    const char* p = strstr(buf, "name:");
    if (p) {
      p += 5; while (*p == ' ') p++;
      int k = 0;
      while (*p && *p != '\n' && *p != '\r' && k < 11) gNodeName[i][k++] = *p++;
      gNodeName[i][k] = 0;
    }
    const char* s = strstr(buf, "sigma_m:");
    if (s) gNodeSigmaM[i] = atof(s + 8);
    const char* q = strstr(buf, "node:");
    if (q) gNodeMeshId[i] = (uint32_t)strtoul(q + 5, nullptr, 0);

    // The `relates:` edges live on the record's header line, which is the start of the
    // buffer we just read — so parse them here rather than paying edgesAt()'s file open
    // once per record per frame.
    char hdr[256];
    size_t h = 0;
    while (h < sizeof(hdr) - 1 && h < n && buf[h] != '\n') { hdr[h] = buf[h]; ++h; }
    hdr[h] = 0;
    TtdbEdge es[NODE_EDGE_MAX];
    uint8_t ne = ttdbParseEdges(hdr, es, NODE_EDGE_MAX);
    for (uint8_t e = 0; e < ne; ++e) {
      gNodeEdges[i][e].lat  = es[e].target_lat;
      gNodeEdges[i][e].lon  = es[e].target_lon;
      gNodeEdges[i][e].lora = (strncmp(es[e].type, "lora", 4) == 0);
    }
    gNodeEdgeCount[i] = ne;
  }
}

// Colour a typed edge by its transport: green ESP-NOW, amber LoRa; `hot` brightens the
// selected node's incident links.
static uint16_t edgeColor(bool lora, bool hot) {
  if (lora) return hot ? rgb565(255, 190, 60) : rgb565(150, 110, 30);
  return hot ? rgb565(120, 230, 150) : rgb565(40, 110, 70);
}

// Draw a gazing eyeball (TTCP-RFC-0002 §3.2) looking toward the globe centre.
static void drawEyeball(int sx, int sy, int cx, int cy, uint16_t col, const char* label) {
  if (!gGlobe) return;
  GFXcanvas16& c = *gGlobe;
  int er = (int)(3.5f * gZoom); if (er < 4) er = 4;
  int irisR  = er - 2 > 1 ? er - 2 : 1;
  int pupilR = er / 2 > 1 ? er / 2 : 1;
  c.fillCircle(sx, sy, er, ST77XX_WHITE);
  float gvx = cx - sx, gvy = cy - sy;
  float gl = sqrtf(gvx * gvx + gvy * gvy);
  float ux = 0.0f, uy = 0.0f;
  if (gl > 0.001f) { ux = gvx / gl; uy = gvy / gl; }
  float look     = gl * 0.22f;
  float irisOff  = look < (float)(er - irisR)  ? look : (float)(er - irisR);
  float pupilOff = look < (float)(er - pupilR) ? look : (float)(er - pupilR);
  c.fillCircle(sx + (int)(ux * irisOff),  sy + (int)(uy * irisOff),  irisR,  col);
  c.fillCircle(sx + (int)(ux * pupilOff), sy + (int)(uy * pupilOff), pupilR, ST77XX_BLACK);
  c.drawPixel(sx - er / 3, sy - er / 3, ST77XX_WHITE);
  if (label && label[0]) {
    c.setTextColor(ST77XX_WHITE);
    c.setCursor(sx + er + 2, sy - 3);
    c.print(label);
  }
}

// A band member's eyeball label on the feelings globe: name + conductor star + how long
// since its last HELLO (or LOST).
static void bandLabel(int rec, char* out, size_t n) {
#if USE_PULSE
  uint32_t seen = nodeLastSeen(gNodeMeshId[rec]);
  bool cond = (gPulse.chart().conductor_id == gNodeMeshId[rec]);
  char age[8];
  if (seen == 0) {
    strncpy(age, "--", sizeof(age));
  } else {
    uint32_t a = (millis() - seen) / 1000;
    if (a > 9) strncpy(age, "LOST", sizeof(age));
    else snprintf(age, sizeof(age), "%lus", (unsigned long)a);
  }
  snprintf(out, n, "%s%s %s", gNodeName[rec], cond ? "*" : "", age);
#else
  snprintf(out, n, "%s", gNodeName[rec]);
#endif
}

// Render the globe into the off-screen canvas: sphere + graticule, links coloured by
// transport, sigma rings, then the nodes.
static void renderGlobe() {
  if (!gGlobe) return;
  GFXcanvas16& c = *gGlobe;
  c.fillScreen(ST77XX_BLACK);
  const int cx = GLOBE_W / 2, cy = GLOBE_H / 2;
  const float R = (GLOBE_H / 2.0f - 3) * gZoom;
  c.drawCircle(cx, cy, (int)R, rgb565(24, 34, 52));
  const float sLat = sinf(gRotLat), cLat = cosf(gRotLat);
  const float sLon = sinf(gRotLon), cLon = cosf(gRotLon);

  const uint16_t grat = rgb565(20, 28, 42);
  int gx, gy; float gz;
  for (int glat = -60; glat <= 60; glat += 30)
    for (int glon = 0; glon < 360; glon += 10) {
      projectLL(glat, glon, R, cx, cy, sLat, cLat, sLon, cLon, gx, gy, gz);
      if (gz > 0) c.drawPixel(gx, gy, grat);
    }
  for (int glon = 0; glon < 360; glon += 30)
    for (int glat = -78; glat <= 78; glat += 10) {
      projectLL(glat, glon, R, cx, cy, sLat, cLat, sLon, cLon, gx, gy, gz);
      if (gz > 0) c.drawPixel(gx, gy, grat);
    }

  const int selLat = (gSel >= 0 && gSel < gViewDb->recordCount()) ? gViewDb->record(gSel).lat : 32767;
  const int selLon = (gSel >= 0 && gSel < gViewDb->recordCount()) ? gViewDb->record(gSel).lon : 32767;
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r)) continue;
    int sx0, sy0; float sz0;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx0, sy0, sz0);
    for (uint8_t e = 0; e < gNodeEdgeCount[i]; ++e) {
      const CachedEdge& ed = gNodeEdges[i][e];
      int tx, ty; float tz;
      projectLL(ed.lat, ed.lon, R, cx, cy, sLat, cLat, sLon, cLon, tx, ty, tz);
      if (sz0 > 0 && tz > 0) {
        bool hot = (r.lat == selLat && r.lon == selLon) ||
                   (ed.lat == selLat && ed.lon == selLon);
        c.drawLine(sx0, sy0, tx, ty, edgeColor(ed.lora, hot));
      }
    }
  }

  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r) || gNodeSigmaM[i] <= 0.0f) continue;
    int sx, sy; float z;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx, sy, z);
    if (z <= 0) continue;
    int rr = (int)(gNodeSigmaM[i] * DEG_PER_M * R * 0.01745329f * SIGMA_VIS_SCALE);
    int cap = (int)(R * 0.7f);
    if (rr > cap) rr = cap;
    if (rr > 1) c.drawCircle(sx, sy, rr, rgb565(34, 46, 34));
  }

  const bool feelView = (gViewDb == &gFeelDb);
  const int dotR = (int)(1.5f * gZoom) < 2 ? 2 : (int)(1.5f * gZoom);
  c.setTextSize(1);
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r)) continue;
    int sx, sy; float z;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx, sy, z);
    uint16_t col = nodeColor(r.lat, r.lon);
    const bool isBand = feelView && gNodeMeshId[i] != 0;
    char id[28];
    if (isBand)                 bandLabel(i, id, sizeof(id));
    else if (gNodeName[i][0])   snprintf(id, sizeof(id), "%s", gNodeName[i]);
    else                        snprintf(id, sizeof(id), "@%d,%d", r.lat, r.lon);

    if (i == gSel || isBand) {
      drawEyeball(sx, sy, cx, cy, col, id);
    } else if (feelView) {
      int fr = dotR - 1 < 1 ? 1 : dotR - 1;
      if (z > 0) c.fillCircle(sx, sy, fr, rgb565(50, 56, 78));
    } else if (z > 0) {
      c.fillCircle(sx, sy, dotR, col);
      c.setTextColor(col);
      c.setCursor(sx + dotR + 2, sy - 3);
      c.print(id);
    } else {
      c.drawPixel(sx, sy, rgb565(60, 66, 78));
    }
  }
}

// Bottom pane — the selected record (TTCP-RFC-0001 §5). Four lines on this panel.
static void renderRecord() {
  if (gBottomDirty) gTft.fillRect(0, BOTTOM_Y, SCR_W, BOTTOM_H, ST77XX_BLACK);
  char l[TEXT_COLS + 2];
  if (gSel < 0 || gSel >= gViewDb->recordCount()) {
    drawWide(BOTTOM_Y, ST77XX_YELLOW, "(no record selected)");
    return;
  }
  const TtdbRecord& r = gViewDb->record(gSel);
  snprintf(l, sizeof(l), "@LAT%dLON%d  %d/%d", r.lat, r.lon, gSel + 1,
           gViewDb->recordCount());
  drawWide(BOTTOM_Y, nodeColor(r.lat, r.lon), l);

  if (!gBottomDirty) return;
  size_t off, len;
  if (!gViewDb->recordSpan(gSel, off, len)) return;
  static char body[520];
  size_t n = len < sizeof(body) - 1 ? len : sizeof(body) - 1;
  n = gViewDb->readBytes(off, (uint8_t*)body, n);
  body[n] = 0;
  const char* p = strchr(body, '\n');       // skip the header line
  p = p ? p + 1 : body;
  int y = BOTTOM_Y + 11, col = 0;
  char line[TEXT_COLS + 2];
  while (*p && y < SCR_H - 8) {
    if (*p == '\n') {
      if (col > 0) { line[col] = 0; drawWide(y, ST77XX_WHITE, line); y += 10; col = 0; }
      p++;
      continue;
    }
    line[col++] = *p++;
    if (col >= TEXT_COLS) { line[col] = 0; drawWide(y, ST77XX_WHITE, line); y += 10; col = 0; }
  }
  if (col > 0 && y < SCR_H - 8) { line[col] = 0; drawWide(y, ST77XX_WHITE, line); }
}

// Bottom pane — the console log, plus the two things only this node knows: whether it
// is holding still, and what it is hearing.
static void renderConsole() {
  if (gBottomDirty) gTft.fillRect(0, BOTTOM_Y, SCR_W, BOTTOM_H, ST77XX_BLACK);
  char l[TEXT_COLS + 2];
  const char* mstate = "?";
#if USE_IMU
  mstate = gImuOk ? (gMotionLog.moving(millis()) ? "MOVING" : "still") : "no imu";
#endif
  int heard = 0;
#if USE_MIC && USE_CARD_HW
  heard = (int)gAcousticLog.rmsMax();
#endif
  snprintf(l, sizeof(l), "%s  hear%d  cmd%lu rx%lu", mstate, heard,
           (unsigned long)gCmdSent, (unsigned long)gEspRx);
  drawWide(BOTTOM_Y, ST77XX_CYAN, l);
  int y = BOTTOM_Y + 11;
  for (int k = 0; k < gLogCount && y < SCR_H - 8; ++k) {
    int idx = (gLogHead - gLogCount + k + LOG_LINES * 2) % LOG_LINES;
    drawWide(y, ST77XX_GREEN, gLog[idx]);
    y += 10;
  }
}

// Frame dispatcher: status line, globe, then the active bottom pane.
static void renderScreen() {
  char l[TEXT_COLS + 2];
  snprintf(l, sizeof(l), "CARD %s s%s >%s z%d %c %s", viewName(gView),
           gSynced ? "+" : "-", nodeName(gCmdTarget), gZoomIdx + 1,
           gPane == PANE_CONSOLE ? 'C' : 'M',
#if USE_PULSE
           heroarc::sceneName(gPulse.scene())
#else
           ""
#endif
           );
  drawWide(STATUS_Y, ST77XX_WHITE, l);

  if (gGlobe) {
    if (gGlobeDirty) {
      renderGlobe();
      gTft.drawRGBBitmap(GLOBE_X, GLOBE_Y, gGlobe->getBuffer(), GLOBE_W, GLOBE_H);
      gGlobeDirty = false;
    }
  } else if (gBottomDirty || gGlobeDirty) {
    gTft.fillRect(0, GLOBE_Y, SCR_W, GLOBE_H, ST77XX_BLACK);
    drawWide(GLOBE_Y + 30, ST77XX_YELLOW, "(globe canvas unavailable)");
    gGlobeDirty = false;
  }

  if (gPane == PANE_CONSOLE) renderConsole();
  else                       renderRecord();
  gBottomDirty = false;
}

// Select a record: seat the cursor and animate the globe to bring it front-centre
// (TTCP-RFC-0002 §6.2/§6.3).
static void selectRecord(int i) {
  if (i < 0 || i >= gViewDb->recordCount()) return;
  gSel = i;
  const TtdbRecord& r = gViewDb->record(i);
  gTgtLon = -(r.lon * 0.01745329f);
  gTgtLat = (r.lat * 0.01745329f);
  gAnim = true;
  gBottomDirty = true;
  gGlobeDirty = true;
}

static void selectNextNode() {
  int n = gViewDb->recordCount();
  for (int step = 1; step <= n; ++step) {
    int i = (gSel + step) % n;
    if (isNodeRecord(gViewDb->record(i))) { selectRecord(i); return; }
  }
}

// Point render + navigation at a globe. The mesh is untouched — only what the screen
// draws and what the keys navigate changes.
static void activateView(int v) {
  gView   = v;
  gViewDb = (v == VIEW_RFC) ? &gRfcDb : (v == VIEW_FEELINGS) ? &gFeelDb : &gDb;
  parseNodeAttrs();
  int sel = gViewSel[v];
  if (sel < 0 || sel >= gViewDb->recordCount() || !isNodeRecord(gViewDb->record(sel))) {
    sel = -1;
    for (int i = 0; i < gViewDb->recordCount(); ++i)
      if (isNodeRecord(gViewDb->record(i))) { sel = i; break; }
  }
  gSel = gViewSel[v] = sel;
  if (sel >= 0) {
    gRotLat = gTgtLat = gViewDb->record(sel).lat * 0.01745329f;
    gRotLon = gTgtLon = -(gViewDb->record(sel).lon * 0.01745329f);
  }
  gAnim = false;
  gGlobeDirty = gBottomDirty = gScreenDirty = true;
}

// ENTER cycles the globe view (the T-Deck does this with its trackball click),
// skipping any globe that never loaded.
static void toggleGlobeView() {
  gViewSel[gView] = gSel;
  int nv = gView;
  for (int k = 0; k < VIEW_COUNT; ++k) {
    nv = (nv + 1) % VIEW_COUNT;
    if (nv == VIEW_RFC && !gRfcLoaded) continue;
    if (nv == VIEW_FEELINGS && !gFeelLoaded) continue;
    break;
  }
  activateView(nv);
}
#endif  // USE_CARD_HW

void setup() {
  Serial.begin(115200);
  delay(200);

  // Restore the song on/off state so a power-cycle rejoins the song (the follower gate
  // below holds it silent until we re-lock to the band).
  gPrefs.begin("card", false);
  gLocalPlay = gPrefs.getBool("play", false);

#if USE_CARD_HW
  // One I2C bus, three devices: keyboard (0x34), codec (0x18), IMU (0x68). 400 kHz —
  // the TCA8418's register init is chatty and the IMU is polled at 20 Hz.
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000);

  // Audio first, so the boot toot is the earliest sign of life (the K10 pattern). The
  // codec must be configured BEFORE I2S starts clocking, or the DAC never un-mutes.
  gCodecOk = es8311::begin(Wire, I2S_RATE);
  if (gCodecOk) {
    gI2S.setPins(PIN_I2S_BCLK, PIN_I2S_WS, PIN_I2S_DOUT, PIN_I2S_DIN, -1);
    if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT,
                   I2S_SLOT_MODE_STEREO)) {
      playStartupToot();
    } else {
      Serial.println("I2S begin failed");
      gCodecOk = false;
    }
  } else {
    Serial.println("ES8311 not found at 0x18 - node runs mute and deaf");
  }

  if (!kbdBegin()) Serial.println("TCA8418 keyboard not found at 0x34");
  pinMode(PIN_KBD_INT, INPUT_PULLUP);   // level read as a cheap "events pending" hint

  gDispSpi.begin(PIN_TFT_SCLK, -1 /*miso*/, PIN_TFT_MOSI, PIN_TFT_CS);
  gTft.init(135, 240);          // ST7789V2 native portrait; rotation makes it 240x135
  // Landscape, keyboard toward the operator. **3, not 1** — rotation 1 renders this
  // panel upside-down (confirmed on hardware 2026-07-27). The T-Deck's ST7789 needed
  // exactly the same correction, so treat 3 as the fleet's default for these panels
  // and only revisit it on a board that actually disagrees.
  gTft.setRotation(3);
  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH);
  gTft.fillScreen(ST77XX_BLACK);
  gTft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  gTft.setTextSize(2);
  gTft.setCursor(4, 4);
  gTft.print("CARDPUTER");

  // Off-screen globe canvas (~36 KB, internal RAM — this board has no PSRAM).
  gGlobe = new GFXcanvas16(GLOBE_W, GLOBE_H);
  if (!gGlobe || !gGlobe->getBuffer()) {
    if (gGlobe) { delete gGlobe; gGlobe = nullptr; }
    Serial.println("globe canvas alloc failed - text fallback");
  }
#endif

#if USE_IMU
  // BMI270 on the shared I2C bus. The library uploads the sensor's config blob, which
  // is why it is a dependency rather than a dozen register writes. The address depends
  // on how the board strapped SDO — try both documented ones rather than trusting one
  // (the ADV's published pin map names the bus but not the strap).
  gImuOk = (gImu.beginI2C(BMI2_I2C_PRIM_ADDR, Wire) == BMI2_OK);
  if (!gImuOk) gImuOk = (gImu.beginI2C(BMI2_I2C_SEC_ADDR, Wire) == BMI2_OK);
  Serial.printf("BMI270 %s\n", gImuOk ? "up (motion tier @LAT95 live)"
                                      : "NOT FOUND - motion tier disabled");
  // When something on the shared bus is missing, say what IS there. Three devices ride
  // this bus and a silent one is the difference between a broken tier and a wrong
  // constant — the scan turns that into a one-line answer at the bench.
  if (!gImuOk) {
    Serial.print("[i2c] devices:");
    for (uint8_t a = 1; a < 0x7F; ++a) {
      Wire.beginTransmission(a);
      if (Wire.endTransmission() == 0) Serial.printf(" 0x%02X", a);
    }
    Serial.println();
  }
#endif

  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
  // Filesystem headroom. This node's TTDB GROWS at runtime — four percept tiers append
  // to it every window — so "how much room is left" is a live question here, not a
  // build-time one. Reported at boot so the answer never has to be estimated.
  Serial.printf("LittleFS: %u / %u bytes used (%u free)\n",
                (unsigned)LittleFS.usedBytes(), (unsigned)LittleFS.totalBytes(),
                (unsigned)(LittleFS.totalBytes() - LittleFS.usedBytes()));
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId, gLocus);

  // The two view-only globes, exactly as on the T-Deck: they never join the mesh.
  if (gRfcDb.begin(LittleFS, kRfcTtdbPath)) {
    gRfcLoaded = true;
    Serial.printf("RFC globe loaded: %u bytes, %d records\n",
                  (unsigned)gRfcDb.fileSize(), gRfcDb.recordCount());
  } else {
    Serial.println("RFC globe (/rfc.ttdb.md) not found - skipped in the view cycle");
  }
  if (gFeelDb.begin(LittleFS, kFeelTtdbPath)) {
    gFeelLoaded = true;
    Serial.printf("Feelings globe loaded: %u bytes, %d records\n",
                  (unsigned)gFeelDb.fileSize(), gFeelDb.recordCount());
  } else {
    Serial.println("Feelings globe (/feelings.ttdb.md) not found - fleet view default");
  }

#if USE_CARD_HW
  activateView(gFeelLoaded ? VIEW_FEELINGS : VIEW_FLEET);
#endif

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_ps(WIFI_PS_NONE);   // keep RX hot for the mesh (K10 lesson)
  if (esp_now_init() != ESP_OK) Serial.println("FATAL: esp_now_init failed");
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_register_send_cb(onEspNowSend);
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

#if USE_PULSE
  gPulse.begin(kNodeId, millis());   // highest id in the fleet: a follower by default
#endif

#if USE_BLE
  blelink::begin(kNodeId, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, onBleObserve);
  Serial.println("BLE near-range tier up (advert + passive scan)");
#endif

  Serial.printf("Cardputer console 0x%08X online (hw %s, codec %s, imu %s)\n", kNodeId,
                USE_CARD_HW ? "on" : "off",
#if USE_CARD_HW
                gCodecOk ? "on" : "FAILED",
#else
                "off",
#endif
#if USE_IMU
                gImuOk ? "on" : "FAILED"
#else
                "off"
#endif
                );
}

void loop() {
  const uint32_t now = millis();

  // Serve TTDB-share / commands arriving from the laptop over USB-CDC (direct pull,
  // negchecks). Trusted, un-deduped link.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) {
      gScreenDirty = true;
      handleToot(t, sendSerial, nullptr);
    }
  }

  // Deferred work off the recv callback: bursts and flash writes on the main task.
  if (gReqPending)   { gReqPending = false;   serveTtdbReq(gPendingReq, sendEspNow, nullptr); }
  if (gPutPending)   { gPutPending = false;   handleToot(gPendingPut, sendEspNow, nullptr); }
  if (gClearPending) { gClearPending = false; handleToot(gPendingClear, sendEspNow, nullptr); }
  if (gSyncPending)  { gSyncPending = false;  appendSyncRecord(); }
  if (gBeliefSyncPending) { gBeliefSyncPending = false; appendBeliefRecord(); }

  // --- the four percept tiers: sample continuously, flush one record per window ---
  // Every flush is a flash write, so it happens here in loop() and never in a callback,
  // and every lane is capped until SP1 pruning takes it (CMD_CLEAR_PERCEPTS).
  if (gLinkLog.due(now)) {
    int lane = laneCount(97);
    if (lane >= LINKPERCEPT_MAX_LANE) {
      gLinkLog.reset(now);
    } else {
      char rec[1024];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)now;
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms, gSynced, now);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[link] percept window -> @LAT97LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }

#if USE_WIFI_SCAN
  serviceWifiScan();
  if (gEntityLog.due(now)) {
    int lane = laneCount(96);
    if (lane >= ENTITYPERCEPT_MAX_LANE) {
      gEntityLog.reset(now);
    } else {
      char rec[1024];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)now;
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms, gSynced, now);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[entity] percept window -> @LAT96LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

#if USE_IMU
  serviceImu(now);
  if (gMotionLog.due(now)) {
    int lane = laneCount(95);
    if (lane >= MOTIONPERCEPT_MAX_LANE) {
      gMotionLog.reset(now);
    } else {
      char rec[320];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)now;
      size_t m = gMotionLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms, gSynced, now);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[motion] percept window -> @LAT95LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

#if USE_MIC && USE_CARD_HW
  serviceMic(now);
  if (gAcousticLog.due(now)) {
    int lane = laneCount(94);
    if (lane >= ACOUSTICPERCEPT_MAX_LANE) {
      gAcousticLog.reset(now);
    } else {
      char rec[400];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)now;
      size_t m = gAcousticLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms, gSynced,
                                          now, I2S_RATE);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[acoustic] percept window -> @LAT94LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

#if USE_CARD_HW
  // Tilt rolls the globe — this board has no trackball, and the IMU is a better
  // pointer anyway: tip the deck and the world turns. Dead-zoned so a hand at rest
  // holds the view still.
#if USE_IMU
  if (gImuOk && gGlobe) {
    const float DEAD = 0.12f;
    float tx = gTiltX, ty = gTiltY;
    if (fabsf(tx) > DEAD || fabsf(ty) > DEAD) {
      gRotLon += (fabsf(tx) > DEAD ? tx : 0.0f) * 0.05f;
      gRotLat += (fabsf(ty) > DEAD ? ty : 0.0f) * 0.05f;
      if (gRotLat > 1.52f) gRotLat = 1.52f;
      if (gRotLat < -1.52f) gRotLat = -1.52f;
      gAnim = false;                 // a deliberate tilt cancels a selection ease
      gGlobeDirty = true;
    }
  }
#endif
  // Ease the globe toward a selected node (TTCP-RFC-0002 §6.3).
  if (gAnim) {
    float dLat = gTgtLat - gRotLat, dLon = gTgtLon - gRotLon;
    gRotLat += dLat * 0.15f;
    gRotLon += dLon * 0.15f;
    gGlobeDirty = true;
    if (fabsf(dLat) < 0.01f && fabsf(dLon) < 0.01f) {
      gRotLat = gTgtLat; gRotLon = gTgtLon; gAnim = false;
    }
  }

  // Keyboard — the operator function. Every press acts immediately (no enter-to-send):
  //   arrows = roll the globe        ENTER = next globe (Feel / SemPos / RFC)
  //   t = next node (+ next comm target in the SemPos view)
  //   s = get-status   p = ping   b = beep   SPACE = toggle the console pane
  //   g = play the song (whole band)   x = stop   o = onward a scene   r = restart
  //   +/= zoom in      -/_ zoom out
  char k = readKey();
  if (k) {
    switch (k) {
      case KEY_LEFT_C:  gRotLon += 0.20f; gGlobeDirty = true; gAnim = false; break;
      case KEY_RIGHT_C: gRotLon -= 0.20f; gGlobeDirty = true; gAnim = false; break;
      case KEY_UP_C:
        gRotLat -= 0.20f; if (gRotLat < -1.52f) gRotLat = -1.52f;
        gGlobeDirty = true; gAnim = false; break;
      case KEY_DOWN_C:
        gRotLat += 0.20f; if (gRotLat > 1.52f) gRotLat = 1.52f;
        gGlobeDirty = true; gAnim = false; break;
      case KEY_ENTER_C: toggleGlobeView(); break;
      case 't':
        selectNextNode();
        if (gView == VIEW_FLEET) {
          gTargetIdx = (gTargetIdx + 1) % kNumTargets;
          gCmdTarget = kTargets[gTargetIdx];
        }
        gScreenDirty = true;
        break;
      case '+': case '=':
        if (gZoomIdx < kZoomMax) { gZoomIdx++; gZoom = kZoomLevels[gZoomIdx]; }
        gGlobeDirty = true; gScreenDirty = true;
        break;
      case '-': case '_':
        if (gZoomIdx > 0) { gZoomIdx--; gZoom = kZoomLevels[gZoomIdx]; }
        gGlobeDirty = true; gScreenDirty = true;
        break;
      case 'p': emitCmd(toot::CMD_PING, nullptr, 0); break;
      case 'b': { uint8_t a[4]; toot::put_u16(a, 880); toot::put_u16(a + 2, 200);
                  emitCmd(toot::CMD_BEEP, a, 4); break; }
      // Play/stop are band-wide: one press starts/stops the whole fleet (and our part).
      case 'g': setLocalPlay(true);
#if USE_PULSE
                gPulse.armSong(heroarc::SCENE_ALONE, now);
#endif
                emitCmdTo(toot::CMD_PLAY, NODE_BROADCAST, nullptr, 0); break;
      case 'x': setLocalPlay(false);
#if USE_PULSE
                gPulse.disarmSong();
#endif
                emitCmdTo(toot::CMD_STOP, NODE_BROADCAST, nullptr, 0); break;
#if USE_PULSE
      case 'o': {
        uint16_t next = gPulse.scene() + 1;
        if (next >= heroarc::SCENE_COUNT) next = heroarc::SCENE_COUNT - 1;
        emitSetScene(next);
        break;
      }
      case 'r': emitSetScene(0); break;
#endif
      case ' ':
      case 'n':
        gPane = (gPane == PANE_MAIN) ? PANE_CONSOLE : PANE_MAIN;
        gBottomDirty = true;
        gScreenDirty = true;
        break;
      case 's': emitCmd(toot::CMD_GET_STATUS, nullptr, 0); break;
      default: break;                    // modifiers and unbound keys: ignored
    }
  }
#endif  // USE_CARD_HW

#if USE_PULSE
  {
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(now, oc, oepoch)) {
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags, oc.scene_id);
      emit(toot::PULSE, body, blen, sendEspNow, nullptr);
    }
    // If we somehow hold the baton (alone on the bench), walk the early scenes and
    // hold at the grief, like every other node that can conduct.
    gPulse.serviceSong(now, heroarc::SCENE_HOLD_MS, heroarc::SCENE_ORDEAL);

    uint16_t new_scene;
    if (gPulse.sceneChanged(new_scene)) {
      Serial.printf("[scene] scene %u %s (era %lu cond 0x%08X)\n", new_scene,
                    heroarc::sceneName(new_scene), (unsigned long)gPulse.chart().era,
                    (unsigned)gPulse.chart().conductor_id);
      gScreenDirty = true;
    }

    // Our voice: the scene selects the phrase (HeroArc.h — silent until the finale,
    // because listening is this node's part). Play only when the song is on AND we are
    // locked to the band as a FOLLOWER; while self-appointed (just rebooted, not yet
    // re-locked) we stay silent so the voice never plays out of phase. The step clock
    // runs through the silent scenes, so the entrance lands on the grid.
    const score::Phrase* ph = score::phraseForScene(kPart, gPulse.scene());
    uint16_t sip;
    uint32_t sc;
    if (gPulse.stepTick(now, ph ? ph->steps : 16, sip, sc) && ph &&
        gLocalPlay && !gPulse.conductor()) {
      const score::Note* nt = score::noteAt(*ph, sip);
      if (nt && nt->freq != score::REST) {
#if USE_CARD_HW
        toneI2S((float)nt->freq, PULSE_TONE_MS);
#endif
        Serial.printf("[part] step %2u/%u  %4uHz (%s)\n", sip, ph->steps, nt->freq,
                      heroarc::sceneName(gPulse.scene()));
      }
    }
  }
#endif

  // Periodic HELLO beacon.
  static uint32_t lastBeacon = 0;
  if (now - lastBeacon >= 2000) {
    lastBeacon = now;
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }

#if USE_CARD_HW
  // Log new replies into the console ring from loop context (never the recv callback).
  static uint32_t lastLoggedReplies = 0;
  if (gReplies != lastLoggedReplies) {
    lastLoggedReplies = gReplies;
    char lg[40];
    snprintf(lg, sizeof(lg), "reply %s %.1fC", nodeName(gLastReplySrc),
             gLastReplyTemp / 100.0f);
    logLine(lg);
  }
  static uint32_t lastRender = 0;
  if (gScreenDirty || gGlobeDirty || now - lastRender >= 1000) {
    lastRender = now;
    gScreenDirty = false;
    // Band members carry live status on the feelings globe, so repaint on the 1 Hz
    // heartbeat to age it even without a navigation change.
    if (gView == VIEW_FEELINGS) gGlobeDirty = true;
    uint32_t r0 = millis();
    renderScreen();
    gLastRenderMs = millis() - r0;
  }
#endif

  // Loop-latency profile. The toot link is serviced once per pass, so the SLOWEST pass
  // is the node's worst-case response time — which is exactly what `verify`/`band`
  // measure as rtt. Printed rarely, and only the extremes, so it costs nothing to
  // leave on: when a future change makes this node sluggish on the mesh, the number
  // that explains it is already on the wire.
  {
    static uint32_t loopStart = 0, worst = 0, lastReport = 0;
    if (loopStart) {
      uint32_t d = millis() - loopStart;
      if (d > worst) worst = d;
    }
    loopStart = millis();
    if (loopStart - lastReport >= 30000) {
      lastReport = loopStart;
      Serial.printf("[loop] worst pass %lums (last render %lums)\n",
                    (unsigned long)worst, (unsigned long)gLastRenderMs);
      worst = 0;
    }
  }
}
