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
#include <PerceptLearn.h>    // Learning from Action Rules 1+2: predict, then testify -> @LAT92
#include <AcousticPercept.h> // SP0 acoustic tier: what did it hear? -> @LAT94
#include <TimeStreamNode.h>  // the team time stream: a timeline the fleet owns -> @LAT90
#include <LaneGenNode.h>   // lane generations: a prune writes down its own boundary -> @LAT100
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

// The representor's views (cardputer-sensorium.md §4). Declared UP HERE, far from the
// renderers that use it, for one Arduino-specific reason: arduino-cli auto-generates
// prototypes for every function in the .ino and inserts them near the top of the file,
// so a function taking a type defined mid-sketch fails to compile against its own
// generated prototype. Any enum used as a PARAMETER type has to be declared before that
// insertion point. (`enum Pane` below gets away with sitting mid-file only because
// nothing takes one as an argument.)
enum FaceView : uint8_t { FACE_EYE = 0, FACE_SCOPE = 1, FACE_INTERO = 2,
                          FACE_BELIEF = 3, FACE_VIEW_COUNT = 4 };

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
// The percept-learning loop. Armed by a `still` @LAT95 window, scored by the next
// @LAT97 window, testified to @LAT92. It never edits anything (Rule 2).
static perceptlearn::Loop gLearn;        // @LAT92 outcome side log
// How often the Dream Cycle re-reads the outcome lane and reconciles @LAT91. Slower than
// the 60 s percept windows on purpose: a lane rewrite is a whole-TTDB flash operation, and
// Rule 2 wants reconciliation to be a separate phase from testimony, not a side effect of
// it. 3 min gives a few new outcomes per cycle during an experiment.
#define DREAM_RECONCILE_MS 180000
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
// (The K10 is parked as of 2026-07-31 — v1 firmware, off the band roster and off the
// T-Deck's mesh map. Cycling onto it only sent CMDs at a node that never answers.)
static const uint32_t kTargets[] = {NODE_TDECK_1, NODE_V4B_RELAY,
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

// --- the duet (CMD_DUET) -------------------------------------------------------------
// Being invited into a duet overrides this node's PART for as long as it lasts — the
// newcomer's part is to listen, and a duet is somebody asking it to sing anyway. Not a
// chart scene (a scene would pull in the whole band; see Toot.h) and not persisted: the
// invitation belongs to the moment the other console asked.
static uint8_t  gDuetRole = toot::DUET_OFF;
static uint32_t gDuetPeer = 0;
static uint8_t  gDuetSpeed = 1;      // 1 = as written, 2 = double time (set by the inviter)
static inline bool duetOn() { return gDuetRole != toot::DUET_OFF; }

// Can this phrase be taken at `speed`? Double time traverses the SAME note table in half as
// many steps, so every note must still land on a step the sequencer visits (score::noteAt is
// an exact match). Refuse rather than silently drop a note — kOdeLead's tied note at step 54
// is exactly that case at ÷4. Computed once when a duet is set up, not per step.
static uint8_t validDuetSpeed(const score::Phrase& ph, uint8_t speed) {
  if (speed < 1) return 1;
  if (speed > toot::DUET_SPEED_MAX) speed = toot::DUET_SPEED_MAX;
  if (ph.steps % speed) return 1;
  for (uint16_t i = 0; i < ph.count; ++i)
    if (ph.notes[i].step % speed) return 1;
  return speed;
}

// Enter/leave a duet, validating the inviter's speed against the phrase our role names. Both
// voices must end up on the same speed or they traverse the phrase at different rates and come
// apart — which is why the inviter sends it rather than each side deciding.
static void setDuet(uint8_t role, uint32_t partner, uint8_t speed) {
  if (role == toot::DUET_OFF) {
    gDuetRole = toot::DUET_OFF;
    gDuetPeer = 0;
    gDuetSpeed = 1;
    return;
  }
  gDuetRole = role;
  gDuetPeer = partner;
  const score::Phrase& ph =
      (role == toot::DUET_LEAD) ? heroarc::kOdeLead : heroarc::kOdeHarm;
  gDuetSpeed = validDuetSpeed(ph, speed);
  if (gDuetSpeed != speed)
    Serial.printf("[duet] speed x%u refused (a note would be dropped) -> x%u\n",
                  speed, gDuetSpeed);
}

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
// Which page of the selected record's body the bottom pane is showing, and how many there
// are. This panel holds four lines, so anything but a stub record is multi-page; `1`/`2`
// walk them while the globes hold the screen, both directions wrapping. `gRecPages` is
// published by renderRecord because the page count is only knowable after the body has
// been laid out, and the key handler must not re-wrap it just to clamp.
static int gRecPage = 0;
static int gRecPages = 1;
static uint32_t gLastRenderMs = 0;   // cost of the last screen repaint (loop profile)
// ...and the worst one in the reporting window. The LAST render is nearly useless as a
// budget check for a view that only repaints what changed: a still deck writes zero
// pixels, so the number printed is almost always 0 and says nothing about the frame
// that actually costs (a blink, a full sclera repaint). Track the max (§3.4).
static uint32_t gWorstRenderMs = 0;
static uint32_t gPassRenderMs = 0;   // render cost inside the CURRENT loop pass
static uint32_t gRenderCount = 0;    // frames drawn this profiler window

// Section profiler. "Worst pass 42 ms, of which render 12 ms" says the other 30 ms is
// somewhere else and stops there; this says WHERE. Stamps are taken at a handful of
// points through loop() and the widest gap in the worst pass is what gets reported —
// the same discipline that found the edgesAt defect (companion.md §6): instrument the
// mechanism, do not chain hypotheses off timings.
static const char* const kSectionNames[] = {"link", "linkperc", "entity", "imu",
                                            "mic", "nav", "pulse", "intero", "render"};
static const int kNumSections = 9;
static uint32_t gSectMark[kNumSections + 1];
static int gSectN = 0;
static inline void sectMark() {
  if (gSectN <= kNumSections) gSectMark[gSectN++] = millis();
}

// --- the team time stream (TimeStream.h) + the wall clock (TTN-RFC-0008) -----
// gStream owns BOTH facts now: which shared timeline this node is on, and whether that
// timeline knows the date. The old single `synced` bit could only ever answer the
// second, and answered it "no" for a fleet in a garden that was in perfect agreement
// with itself.
static timestream::Node gTs;

// Shorthands, so the tiers below read the way they always did. gStamp is the ONE
// snapshot every record in a pass is stamped from — four tiers flushing in the same
// loop() pass carry the same instant, rather than four readings of a clock that moved
// between them.
#define gStamp         (gTs.stamp())
#define gStreamWallSec (gTs.wallSec())
#define gSynced        (gTs.wall())
#define gClockOffsetMs (gTs.clockOffsetMs())
static inline int64_t nowEpochMs() { return gTs.nowEpochMs(); }

static uint32_t gLastSyncId = 0;
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

// --- INTEROCEPTION: the node's sense of its own body (sensorium §4.5, phase S4) ----
//
// Three interior signals, all slow and all cheap: how much ENERGY is left (the pack, via
// the G10 divider), how HOT the die is, and how much contiguous RAM is left to think in.
//
// Sampled HERE, in loop context, rather than inside the renderer — for two reasons that
// are not style. (1) The STATUS reply needs the temperature whether or not anybody is
// looking at the screen: this node has been sending a literal 0 in the fleet's
// `temp_c_x100` field since it joined, which is the hole phase S4 exists to fill. (2) A
// renderer that reads a sensor is a renderer whose frame cost depends on that sensor,
// and this view's whole claim is that it costs almost nothing at rest (§3.4).
//
// ⚠ THE DIVIDER RATIO IS AN ASSUMPTION, and it is the one number here that cannot be
// checked from the laptop. G10 reads the pack through a resistive divider; 1:1 (so
// double it) is what M5's own code does for this family, but nothing on hand proves it
// for the ADV. So the RAW pin millivolts are printed alongside the derived pack voltage
// on every sample line — put a meter on the JST battery lead, compare, and change this
// one constant if they disagree. Same discipline as the eye's gaze axes: the thing the
// bench must confirm is a named constant at the top, not arithmetic buried in a renderer.
static const float BAT_DIVIDER = 2.0f;
static const uint32_t INTERO_PERIOD_MS = 2000;   // these signals move in minutes

// ⚠ Have-we-sampled is its OWN flag, never `gBatMv != 0`. A measurement must not double as
// its own validity flag: 0 mV is a perfectly legitimate reading (no pack on the lead, or a
// divider left disconnected), and using the value as the sentinel makes the sampler re-run
// AND re-print its one-time boot line on every loop pass. On a V4 that serial flood reported
// as a 2-4 s worst loop pass — a fake performance number sitting right on top of a real and
// still-unexplained one (companion.md §6). Latent rather than active here, because this
// board has never read 0 — which is exactly why it survived this long.
static bool     gBatSampled = false;
static uint16_t gBatMv    = 0;      // pack millivolts (0 = no pack / divider open)
static float    gBatSlow  = 0.0f;   // slow EMA of the above — the fill/drain reference
static int8_t   gBatTrend = 0;      // +1 filling, -1 draining, 0 steady
static uint8_t  gBatPct   = 0;
static int16_t  gDieC10   = 0;      // ESP32-S3 die temperature, tenths of a degree
static uint32_t gMaxAllocK = 0;     // largest CONTIGUOUS block, not free heap (§6)
static uint32_t gWorstLoopMs = 0;   // published by the loop profiler: our own slowness

// Voltage -> state of charge for a 1S Li-ion, linear between measured curve points.
// Deliberately coarse: the flat middle of a Li-ion curve means any percentage between
// 3.7 and 3.9 V is a guess, and pretending otherwise with more decimals would be worse.
static uint8_t batPercent(uint16_t mv) {
  static const uint16_t kV[] = {3300, 3500, 3680, 3730, 3760, 3790,
                                3820, 3870, 3950, 4000, 4100, 4200};
  static const uint8_t  kP[] = {   0,    5,   10,   20,   30,   40,
                                  50,   60,   70,   80,   90,  100};
  const int n = sizeof(kP) / sizeof(kP[0]);
  if (mv <= kV[0]) return 0;
  if (mv >= kV[n - 1]) return 100;
  for (int i = 1; i < n; ++i) {
    if (mv < kV[i]) {
      int span = kV[i] - kV[i - 1];
      return (uint8_t)(kP[i - 1] + (int)(kP[i] - kP[i - 1]) * (mv - kV[i - 1]) / span);
    }
  }
  return 100;
}

static void serviceIntero(uint32_t now) {
  static uint32_t last = 0;
  if (gBatSampled && now - last < INTERO_PERIOD_MS) return;
  last = now;

  // Four reads averaged. One 12-bit sample of a divided pack sitting behind a switching
  // charger is noisy at exactly the millivolt scale the trend arrow reads, and the whole
  // burst costs well under a millisecond once per 2 s.
  uint32_t acc = 0;
  for (int i = 0; i < 4; ++i) acc += analogReadMilliVolts(PIN_BAT_ADC);
  uint32_t pin_mv = acc / 4;
  uint16_t mv = (uint16_t)(pin_mv * BAT_DIVIDER);

  bool first = !gBatSampled;
  gBatSampled = true;
  gBatMv = mv;
  gBatPct = batPercent(mv);
  // Am I filling or draining? A ~2-minute EMA is the reference, so the arrow reports the
  // direction of the PACK rather than of the last sample's noise. This is the honest
  // version of "am I charging": we have no VBUS sense pin, so we do not claim one — we
  // report the only thing actually measured, which is which way the voltage is going.
  if (first) gBatSlow = (float)mv;
  else       gBatSlow += ((float)mv - gBatSlow) * 0.03f;
  float d = (float)mv - gBatSlow;
  gBatTrend = (d > 12.0f) ? 1 : (d < -12.0f) ? -1 : 0;

  // Die temperature, not ambient: there is no ambient sensor on this board. It reads
  // high (40-55 C is normal) because WiFi and BLE are up a few millimetres away, so it
  // is a measure of how hard the node is working as much as of the room.
  gDieC10 = (int16_t)lroundf(temperatureRead() * 10.0f);

  gMaxAllocK = ESP.getMaxAllocHeap() / 1024;

  if (first) {
    Serial.printf("[intero] pin %lumV x%.2f = pack %umV (%u%%) | die %.1fC | "
                  "maxalloc %luK  <- CHECK THE PACK VOLTAGE AGAINST A METER\n",
                  (unsigned long)pin_mv, BAT_DIVIDER, mv, gBatPct,
                  gDieC10 / 10.0f, (unsigned long)gMaxAllocK);
  }
}

// STATUS telemetry for the `monitor` table. No sensor cursor on a console, so those
// fields are 0; report the synced state + epoch, plus the PULSE tail for `band`.
//
// The temperature field is NO LONGER 0 (phase S4): it carries this node's die
// temperature. Toot.h calls the field "ambient", and this is not that — but a die
// reading is a real measurement of a real body, and an empty field is not. `monitor`
// showing 47.2 C for cardputer_1 means "the Cardputer is warm", which is true and was
// previously unsayable.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, (uint16_t)(gDieC10 * 10));   // tenths here, HUNDREDTHS on the wire
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

// INTERO PERCEPT — the answer to CMD_GET_INTERO (Toot.h INTERO_PERCEPT_PAYLOAD_LEN).
//
// This is the interoception VIEW's data without the view: the same numbers §4.5 draws on
// this node's own panel, shipped as 21 bytes so another console can draw the same body in
// its own idiom. Nothing here is display-shaped — no colours, no bar widths, no strings —
// because the receiver has a different panel, a different palette and a different amount
// of room, and the thing worth sending across a mesh is the measurement, not the pixels.
//
// Reads NOTHING: every field is the last sample serviceIntero() already took on its own
// 2 s cadence, so this is safe from the recv path and cheap enough for a remote console
// to poll while it watches us — which is exactly the use case (the T-Deck's record pane).
static uint8_t buildIntero(uint8_t* p) {
  toot::put_u16(p + 0, gBatMv);
  p[2] = gBatSampled ? gBatPct : 255;            // 255 = never sampled, not "0%"
  p[3] = (uint8_t)(int8_t)gBatTrend;
  toot::put_u16(p + 4, (uint16_t)gDieC10);
  toot::put_u16(p + 6, (uint16_t)gMaxAllocK);
  toot::put_u32(p + 8, millis() / 1000);
  toot::put_u16(p + 12, (uint16_t)(gWorstLoopMs > 65535 ? 65535 : gWorstLoopMs));
#if USE_PULSE
  const pulse::Chart& ch = gPulse.chart();
  toot::put_u16(p + 14, ch.beat_period_ms);
  toot::put_u32(p + 16, ch.conductor_id);
  // VOICING = "am I singing", which PLAYING does not say (that only means the band clock is
  // running, and this node's part is silent in every scene but the finale). Reported as the
  // STATE that would sound a note, not the instant of one, so a poll cannot land between two
  // notes and read false — this is how the T-Deck sees a duet actually start.
  bool voicing = duetOn() ||
                 (gLocalPlay && !gPulse.conductor() &&
                  score::phraseForScene(kPart, gPulse.scene()) != nullptr);
  p[20] = (gSynced ? toot::INTERO_SYNCED : 0) |
          (gPulse.conductor() ? toot::INTERO_CONDUCTOR : 0) |
          (gPulse.playing() ? toot::INTERO_PLAYING : 0) |
          (voicing ? toot::INTERO_VOICING : 0);
#else
  toot::put_u16(p + 14, 0);
  toot::put_u32(p + 16, 0);
  p[20] = gSynced ? toot::INTERO_SYNCED : 0;
#endif
  return (uint8_t)toot::INTERO_PERCEPT_PAYLOAD_LEN;
}

// Serve a TTDB_REQ addressed to this node: belief mode streams the stored /belief.md
// (TTN-RFC-0009 §3 readback); any other mode streams the live TTDB. Both stream a
// burst, so radio callers must invoke this from loop().
static void serveTtdbReq(const toot::Toot& req, TtdbShare::SendFn send, void* ctx) {
  if (!gShare || TtdbShare::requestTarget(req) != kNodeId) return;
  if (req.payload_len >= 1 && req.payload[0] == toot::TTDB_REQ_RECORDING) {
    const uint8_t* rec = nullptr;
    size_t n = recordingObject(&rec);
    gShare->handleBufferRequest(rec, n, send, ctx);   // 0 bytes = "nothing captured"
  } else if (req.payload_len >= 1 && req.payload[0] == toot::TTDB_REQ_BELIEF) {
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

// Prune consumed percept lanes. This node carries all four tiers, so it had been
// compacting them with four sequential removeLane() calls — four whole-file rewrites,
// and four separate windows in which the file moved under any concurrent reader (the
// stitched-pull hazard, companion.md §6). removePerceptLanes() does it in ONE rewrite.
// `lane` is the wire byte: 0 = every percept lane, else exactly that one.
// The outcome lane's boundary block: what the generation about to be destroyed had
// accumulated, and what it concluded. Built here because it is the only place that can
// fold @LAT92 — LaneGen must not depend on PerceptLearn.
//
// ⚠ THIS RUNS BEFORE THE PRUNE AND FROM THE LANE ITSELF, not from `gRecon`'s current
// contents. gRecon is whatever the last Dream Cycle left, which may be minutes stale and
// may have been folded from a lane that has grown since. The boundary has to describe
// the records actually being dropped.
//
// ⚠ The line tokens are deliberately NOT `**OBSERVED**`/`**COVERED**`. Those are
// Reconciler::foldRecord's needles, and a boundary carrying them would be folded as
// testimony the next time the lane was read — the node would re-learn from its own
// gravestone. Same needle-collision family as `prev_stream:` in @LAT90 and the bare ids
// in **STREAMS-EXPLAINED**.
// One record's worth of @LAT92, read off flash. SHARED by the two places that fold the
// outcome lane (the Dream Cycle and the prune boundary) because they are never
// concurrent and PERCEPTLEARN_BUF is 2624 B — two copies would cost more RAM than the
// whole feature. ⚠ Do not make it a local: it is far too big for the loop stack.
static uint8_t gLaneReadBuf[PERCEPTLEARN_BUF];

static size_t buildOutcomeCarried(char* out, size_t cap) {
  perceptlearn::Reconciler R;
  R.begin();
  long windows = 0;
  int records = 0;
  for (int i = 0; i < gDb.recordCount(); ++i) {
    if (gDb.record(i).lat != PERCEPTLEARN_LANE) continue;
    ++records;
    size_t start = gDb.record(i).file_offset;
    size_t end = (i + 1 < gDb.recordCount()) ? gDb.record(i + 1).file_offset
                                             : gDb.fileSize();
    size_t len = end - start;
    if (len > sizeof(gLaneReadBuf)) len = sizeof(gLaneReadBuf);
    size_t got = gDb.readBytes(start, gLaneReadBuf, len);
    if (got) R.foldRecord((const char*)gLaneReadBuf, got);
    yield();
  }
  // The denominator, reconstructed the way run-length requires: a record is NOT a
  // window. Summed off the folded tallies rather than off the record count, because
  // since 2026-08-04 one record can stand for up to PERCEPTLEARN_MAX_RUN of them.
  long met = 0, violated = 0, unobserved = 0;
  for (int i = 0; i < R.beliefCount(); ++i) {
    met += R.belief(i).met;
    violated += R.belief(i).violated;
    unobserved += R.belief(i).unobserved;
  }
  const int nb = R.beliefCount();
  // The most windows any single claim was tested over. NOT a mean across beliefs: the
  // claim set changes as peers come and go, so a mean would report a number no claim
  // actually experienced. `max` answers the question a reader has — "how long did the
  // best-evidenced belief have to form?" — and the per-belief lines below give the rest.
  for (int i = 0; i < nb; ++i) {
    const long w = R.belief(i).met + R.belief(i).violated + R.belief(i).unobserved;
    if (w > windows) windows = w;
  }

  int n = snprintf(out, cap,
                   "**OUTCOMES-CARRIED** records:%d windows_max:%ld beliefs:%d "
                   "met:%ld violated:%ld unobserved:%ld baseline_conf:%d rule:+%d/-%d\n",
                   records, windows, nb, met, violated, unobserved,
                   PERCEPTLEARN_BASELINE_CONF, PERCEPTLEARN_CONF_MET,
                   PERCEPTLEARN_CONF_VIOLATED);
  if (n <= 0 || (size_t)n >= cap) return 0;
  size_t len = (size_t)n;
  for (int i = 0; i < nb; ++i) {
    const perceptlearn::Belief& b = R.belief(i);
    n = snprintf(out + len, cap - len,
                 "**BELIEF-AT-BOUNDARY** peer:0x%08lX proto:%d conf:%ld sal:%ld "
                 "met:%ld violated:%ld unobserved:%ld max_streak:%ld contradiction:%d\n",
                 (unsigned long)b.peer, (int)b.proto, (long)b.conf, (long)b.sal,
                 (long)b.met, (long)b.violated, (long)b.unobserved,
                 (long)b.max_streak, b.contradiction ? 1 : 0);
    // Nothing rather than a truncation: a short list understates the evidence the
    // boundary is standing in for, which is the failure it exists to prevent.
    if (n <= 0 || (size_t)n >= cap - len) return 0;
    len += (size_t)n;
  }
  return len;
}

static bool clearPerceptLanes(uint8_t lane) {
  // LaneGen names @LAT92 itself so it need not include PerceptLearn. If the two ever
  // disagree the prune would empty a lane nobody asked for, so fail the BUILD.
  static_assert(LANEGEN_OUTCOME_LANE == PERCEPTLEARN_LANE,
                "LANEGEN_OUTCOME_LANE must be PERCEPTLEARN_LANE");
  bool ok;
  if (lane == TIMESTREAM_LANE) {
    ok = lanegen::pruneTimeline(gDb, gStamp, kNodeId, gStreamWallSec);
  } else if (lane == PERCEPTLEARN_LANE) {
    static char carried[LANEGEN_CARRIED_BUF];
    const size_t cm = buildOutcomeCarried(carried, sizeof(carried));
    if (!cm) {
      Serial.printf("[percept] @LAT%d NOT pruned — its boundary tally would not fit "
                    "LANEGEN_CARRIED_BUF (%d). Pruning without it would drop every "
                    "belief back to baseline with nothing saying why.\n",
                    PERCEPTLEARN_LANE, LANEGEN_CARRIED_BUF);
      return false;
    }
    ok = lanegen::pruneOutcomes(gDb, gStamp, kNodeId, gStreamWallSec, carried);
    if (ok) {
      // The beliefs are now folded from an empty lane, so they will read baseline on the
      // next Dream Cycle. Say it out loud: a silent fall from 106 to 128 is
      // indistinguishable from a node that never learned anything.
      Serial.printf("[percept] @LAT%d pruned — @LAT%d beliefs will return to baseline "
                    "%d on the next Dream Cycle. That is the design (a belief is as "
                    "strong as the evidence retained), not a fault.\n",
                    PERCEPTLEARN_LANE, PERCEPTLEARN_BELIEF_LANE,
                    PERCEPTLEARN_BASELINE_CONF);
      gLearn.reset();   // no lane to testify into means no run to be mid-way through
    }
  } else {
    ok = lanegen::prune(gDb, lane, gStamp, kNodeId, gStreamWallSec);
  }
  if (ok)
    Serial.printf("[percept] lane %s cleared (TTDB now %uB, %dr)\n",
                  lane ? String(lane).c_str() : "ALL (94-97)",
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
      // CMD_RECORD is band-wide by nature: the entire value of it is that several nodes
      // capture the SAME window, so a broadcast is the normal case rather than a
      // convenience. Armed here in the recv path deliberately — arming is a few stores
      // and no I/O, and deferring it to loop() could push it past the start instant on a
      // pass that happens to be doing a percept flush (60-220 ms, half a beat).
      if (toot::cmdOp(t) == toot::CMD_RECORD &&
          (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
#if USE_MIC && USE_CARD_HW && USE_PULSE
        if (t.payload_len >= 15)
          accepted = armRecord(toot::get_u64(t.payload + 5),
                               toot::get_u16(t.payload + 13));
#endif
        // Addressed requests still ACK (accepted stays false if we declined); a
        // broadcast must not, or every node answers at once.
        if (toot::cmdTarget(t) == NODE_BROADCAST) return;
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
          case toot::CMD_GET_INTERO: {
            // "Show me your body." The T-Deck's record pane draws this node's
            // interoception from these 21 bytes, so the fleet's sense organ is also the
            // first node another console can look INSIDE (companion.md §6).
            uint8_t body[toot::INTERO_PERCEPT_PAYLOAD_LEN];
            uint8_t ilen = buildIntero(body);
            emit(toot::PERCEPT, body, ilen, reply, ctx);
            break;
          }
          case toot::CMD_BEEP: {
            // The Cardputer has a real speaker, so it answers a beep audibly (the
            // T-Deck's no-op default was for a node without one). Args: freq, ms.
#if USE_CARD_HW
            uint16_t f = t.payload_len >= 7 ? toot::get_u16(t.payload + 5) : 880;
            uint16_t d = t.payload_len >= 9 ? toot::get_u16(t.payload + 7) : 200;
            if (d > 1000) d = 1000;          // never block the loop for a whole second+
            if (gCodecOk) toneI2S((float)f, d, 22000.0f);   // scaled with the new default
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
            setDuet(toot::DUET_OFF, 0, 1);   // stop means stop, duet included
#if USE_PULSE
            gPulse.disarmSong();
#endif
            break;
          case toot::CMD_DUET:
            // Roles ride on the wire, so nothing here assumes who invited whom — this node
            // can lead a duet as readily as harmonise one.
            if (t.payload_len >= 10) {
              uint32_t partner = toot::get_u32(t.payload + 5);
              uint8_t role = t.payload[9];
              // The speed byte is additive: a sender that predates it means "as written",
              // the same discipline the STATUS and PULSE tails use.
              uint8_t speed = (t.payload_len >= 11) ? t.payload[10] : 1;
              // The inviter RE-ASSERTS a live duet every couple of seconds (a single ESP-NOW
              // invitation gets dropped), so log only when something actually changed — an
              // otherwise-identical repeat is the mechanism working, not an event.
              bool changed = (role != gDuetRole) || (gDuetSpeed != speed);
              setDuet(role, partner, speed);
              if (changed)
                Serial.printf("[duet] %s by %s (speed x%u)\n",
                              role == toot::DUET_OFF ? "dismissed"
                              : role == toot::DUET_LEAD ? "invited to LEAD" : "invited to HARM",
                              nodeName(partner), gDuetSpeed);
            } else {
              ok = false;
            }
            break;
          case toot::CMD_CLEAR_PERCEPTS:
            // Flash rewrite: reaches here only from loop() (the radio path defers).
            // ACK only on success, so a failed prune is loud and the laptop retries.
            ok = clearPerceptLanes(toot::cmdClearLane(t));
            break;
          case toot::CMD_PING:
            // A ping otherwise does nothing but ACK, which is exactly what makes it the
            // right thing to overload as a FIELD MARKER. During a walk experiment the
            // operator is across the house holding the T-Deck and cannot reach the
            // laptop, so `p` on its keyboard (whose default target is this node) drops a
            // timestamped label straight into this node's serial log. The alternative is
            // the operator's memory of when they moved, and that is precisely what
            // invalidated the first attempt at a labelled run — the shape claim needs
            // ground truth that does NOT come from the RSSI it is being tested against.
            Serial.printf("[mark] FIELD MARK from 0x%08X\n", (unsigned)t.src_node_id);
            break;
          default: break;                    // set-* (no-op here)
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
          // The laptop supplies the DATE. It does not supply the timeline — the fleet
          // already has one — so this anchors the stream rather than replacing its
          // clock. gTs.onTimeSync() only latches; gTs.service() applies it from loop(),
          // because it mutates gStream and this runs in the WiFi task.
          gLastSyncId = sid;
          gPendSyncId = sid; gPendEpochMs = ems; gPendRecvMs = recv_ms;
          gTs.onTimeSync(ems, recv_ms, t.src_node_id);
          gSyncPending = true;       // append the @LAT99 log from loop()
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

  // The time-stream anchor rides on HELLO — every node emits one every 2 s, and its
  // payload was empty until now, so this is purely additive: a node still on old
  // firmware sends 0 bytes and parseAnchor declines, which makes it a non-participant
  // rather than a parse error. Handled OUTSIDE the USE_PULSE guard on purpose: the
  // band is optional, a shared timeline is not.
  gTs.onHello(t, millis());
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
  // The stream is anchored to the date by gTs.service() (which ran before this, at
  // the top of loop()), so `created:` below is already real. Note the laptop is
  // telling the fleet what DAY it is, not what TIME it is — those became separate
  // facts on 2026-08-03, and only the first is the laptop's to say.
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

// --- Stage D: the Dream Cycle's reconciliation pre-phase (Rule 3) ------------------
// Re-reads the @LAT92 outcome lane OFF FLASH, folds every claim through Rule 3 from a
// fixed baseline, and rewrites the @LAT91 belief lane if the result changed.
//
// It deliberately does NOT keep a running total as outcomes are scored, even though that
// would be free and would give the same numbers. The belief has to be a pure function of
// the records on flash, so that anyone re-reading the same lane arrives at the same conf.
// A counter would make this the node REMEMBERING; re-reading makes it the store
// RECONCILING, which is the only version that answers TTE Draft 06's standing caveat that
// "the reconciliation was performed by hand, by an outside reader".
//
// Runs from loop(), never a callback: it can rewrite the whole TTDB.
static perceptlearn::Reconciler gRecon;
static int32_t gLastConf[PERCEPTLEARN_MAX_BELIEFS];
static int gLastConfN = -1;      // -1 = never reconciled this boot
static int gBeliefRev = 0;

static void reconcileBeliefs() {
  // Timed in three phases because they fail differently and the section profiler cannot
  // tell them apart (the whole Dream Cycle sits inside "linkperc"). `fold` re-reads the
  // outcome lane off flash EVERY cycle even when nothing changed — that cost is paid
  // forever, so it is worth its own number. `rewrite` is the removeLane whole-TTDB
  // rewrite the handoff flagged as a plausible new source of a multi-second stall.
  const uint32_t t_enter = millis();
  gRecon.begin();
  // Fold the outcome lane in record order — order matters, because the +2 saturates and
  // the -16 floors, and a clamp does not commute with a sum.
  for (int i = 0; i < gDb.recordCount(); ++i) {
    if (gDb.record(i).lat != PERCEPTLEARN_LANE) continue;
    size_t start = gDb.record(i).file_offset;
    size_t end = (i + 1 < gDb.recordCount()) ? gDb.record(i + 1).file_offset
                                             : gDb.fileSize();
    size_t len = end - start;
    if (len > sizeof(gLaneReadBuf)) len = sizeof(gLaneReadBuf);
    size_t got = gDb.readBytes(start, gLaneReadBuf, len);
    if (got) gRecon.foldRecord((const char*)gLaneReadBuf, got);
    yield();
  }

  const uint32_t t_fold = millis();
  const int n = gRecon.beliefCount();
  // A dropped claim biases conf from a subset of the lane while looking like a complete
  // fold, so it is reported before anything else this cycle prints.
  if (gRecon.claimsDropped())
    Serial.printf("[dream] ⚠ %d claim(s) DROPPED - belief slots full "
                  "(PERCEPTLEARN_MAX_BELIEFS %d): conf below is folded from a SUBSET "
                  "of @LAT%d\n",
                  gRecon.claimsDropped(), PERCEPTLEARN_MAX_BELIEFS, PERCEPTLEARN_LANE);
  if (n == 0) return;

  // Skip the rewrite when nothing moved. Re-running the reconciliation is supposed to be
  // a no-op, and a lane rewrite is a whole-TTDB flash operation — doing it every cycle
  // regardless would burn flash to write identical bytes.
  bool changed = (gLastConfN != n);
  if (!changed)
    for (int i = 0; i < n; ++i)
      if (gLastConf[i] != gRecon.belief(i).conf) { changed = true; break; }
  if (!changed) {
    Serial.printf("[dream] reconciled %d outcome record(s) -> no change (conf steady) "
                  "| fold %lums (TTDB %uB)\n",
                  gRecon.recordsFolded(), (unsigned long)(t_fold - t_enter),
                  (unsigned)gDb.fileSize());
    return;
  }

  ++gBeliefRev;
  const uint32_t bytes_before = (unsigned)gDb.fileSize();
  const uint32_t t_rm0 = millis();
  if (!gDb.removeLane(PERCEPTLEARN_BELIEF_LANE)) {
    Serial.println("[dream] belief lane rewrite FAILED (removeLane)");
    return;
  }
  const uint32_t t_rm = millis();
  // `touched:` (Unix seconds, TTDB-RFC-0005) and the **TOUCHED** stream stamp are the
  // same instant in two frames. The second is the one that works with no laptop, which
  // is the whole reason the belief can now decay at all.
  static char brec[PERCEPTLEARN_BUF];
  for (int i = 0; i < n; ++i) {
    size_t m = gRecon.buildBelief(brec, sizeof(brec), i, i, gStreamWallSec, kNodeId,
                                  gBeliefRev, gStamp);
    if (m && gDb.appendRecord(brec, m)) {
      const perceptlearn::Belief& b = gRecon.belief(i);
      Serial.printf("[dream] @LAT%dLON%d peer:0x%lx %s conf:%ld sal:%ld "
                    "(met:%ld violated:%ld%s) rev:%d\n",
                    PERCEPTLEARN_BELIEF_LANE, i, (unsigned long)b.peer,
                    b.proto == 0 ? "espnow" : (b.proto == 1 ? "lora" : "ble"),
                    (long)b.conf, (long)b.sal, (long)b.met, (long)b.violated,
                    b.contradiction ? " CONTRADICTION" : "", gBeliefRev);
    }
    gLastConf[i] = gRecon.belief(i).conf;
    yield();
  }
  gLastConfN = n;
  const uint32_t t_end = millis();
  Serial.printf("[dream] reconciled %d outcome record(s) -> %d belief(s), TTDB %uB\n",
                gRecon.recordsFolded(), n, (unsigned)gDb.fileSize());
  // The number companion.md owes the handoff. Printed on the CHANGING path only, which
  // is the path that had never been observed. "It seemed fine" is not a result.
  Serial.printf("[dream] TIMING fold %lums rewrite %lums append %lums TOTAL %lums "
                "(%luB -> %luB, %d records)\n",
                (unsigned long)(t_fold - t_enter), (unsigned long)(t_rm - t_rm0),
                (unsigned long)(t_end - t_rm), (unsigned long)(t_end - t_enter),
                (unsigned long)bytes_before, (unsigned long)gDb.fileSize(),
                gDb.recordCount());
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

// --- what the representor reads (cardputer-sensorium.md §4.1) ----------------
// The sense services publish here; the face only reads. Keeping the coupling one-way
// is what lets the eyeball cost nothing while it is off screen, and it keeps the
// percept tiers unaware that anything is watching them.
static float gTiltX = 0.0f, gTiltY = 0.0f;   // low-passed accel, in g: where gravity is
static float gSacX = 0.0f, gSacY = 0.0f;     // gyro saccade, leaky-integrated, ~-1..1
static int   gDevMg = 0;                     // ||accel| - 1 g| in mg: shove/tap energy
static uint32_t gTapAt = 0;                  // millis() of the last hard tap (0 = none)
static float gSndHot = 0.0f;                 // 0..1: how far sound is over its ambient
static float gSndAmb = 0.0f;                 // slow room baseline (mean |sample|)
// Raw PCM for the oscilloscope (§4.2). ONE SCREEN COLUMN PER SAMPLE: the panel is 240
// px wide and the mic's DMA descriptor is 240 frames, which at 8 kHz is exactly 30 ms —
// so a sweep is one descriptor. The sweep length was not chosen, it fell out of the
// audio path (see serviceMic's descriptor note).
//
// TWO blocks are kept, not one, because the TRIGGER needs slack: the renderer hunts a
// rising edge in the older block and then draws 240 samples from wherever it found it.
// Without that slack there is nothing to slide, and a whistled note smears instead of
// standing still.
static const size_t SCOPE_SPAN = 240;
static int16_t  gScopeRing[SCOPE_SPAN * 2];  // [0..239] older block, [240..479] newest
static int32_t  gTransCount = 0;             // @LAT94 transients this window, as logged
static uint32_t gTransAt = 0;                // millis() of the last one that wasn't us

// The beat-scheduled capture buffer (CMD_RECORD). Sized at ONE BAR — 4 beats at 120 BPM
// is 2 s, which at 8 kHz/16-bit mono is 32,000 bytes. That number is not a coincidence
// worth ignoring: the largest contiguous block this node can allocate once WiFi and BLE
// are up is ~45 KB (measured — it is why the oscilloscope's canvas was refused), so one
// bar fits in RAM with room and needs no filesystem, no repartition and no SD card.
// Static rather than allocated, for the same reason the scope's row buffer is: a
// feature whose allocation can fail is a feature that can vanish.
static const uint32_t REC_MAX_SAMPLES = 16000;
static uint8_t  gRecObj[toot::RECHDR_LEN + REC_MAX_SAMPLES * 2];
static bool     gRecArmed = false, gRecActive = false;
static uint32_t gRecWant = 0, gRecHave = 0;
static uint64_t gRecReqEpoch = 0;            // the instant we were asked for
static uint8_t  gRecFlags = 0;

// The capture as a servable object, reached through a FUNCTION rather than the buffer
// directly because the reader (serveTtdbReq) sits earlier in the file — arduino-cli
// auto-prototypes functions but not variables, so a function is the thing that can be
// used before it is defined.
//
// Returns 0 bytes while a capture is armed or running. Serving a half-filled buffer
// would hand the companion audio whose tail is the PREVIOUS capture's samples, and it
// would look entirely plausible — the worst kind of wrong on a measurement path.
static size_t recordingObject(const uint8_t** out) {
  *out = gRecObj;
  if (gRecArmed || gRecActive) return 0;
  uint32_t n = toot::get_u32(gRecObj + 12);
  if (!n || toot::get_u32(gRecObj + 0) != toot::RECHDR_MAGIC) return 0;
  return toot::RECHDR_LEN + (size_t)n * 2;
}
// Our own speaker is sounding until here. The node has a mic AND sings, so without a
// gate every note it plays is a stimulus to itself (§3.3). This gate covers the FACE
// only — phase S0 still owes the same gate to the @LAT94 transient log.
static uint32_t gToneUntilMs = 0;

// --- audio, keyboard, IMU, screen (all gated on the real board) --------------
#if USE_CARD_HW
// Synthesize a `ms`-long SQUARE wave at `freq` as 16-bit stereo samples (L=R). Square,
// not sine, to match the rest of the band: the V4s' hand-wired amps only reproduce
// squares, so the whole fleet plays one timbre on purpose. Blocks ~ms, so it runs from
// setup()/loop() only — never a callback.
//
// The default amplitude is deliberately just under full scale, NOT at it. A square wave
// through the DAC's reconstruction filter overshoots its own edges by roughly 9%
// (Gibbs), so a nominal 32767 would clip on every transition and buzz; 30000 puts those
// overshoots at the rail instead of through it. That is 1 dB given away to get a clean
// edge, against the 5.5 dB this default gained when it went up from 16000 — this node
// is the quietest voice in the fleet (8 ohm 1 W speaker) and was sitting 6 dB down for
// no reason. The other 6.5 dB came from the codec (Es8311.h, DAC_VOL_0DB).
static void toneI2S(float freq, uint32_t ms, float amp = 30000.0f) {
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
  // The write is buffered, so the speaker is still sounding after this returns; hold
  // the self-noise gate open a little past the end of the note (§3.3).
  gToneUntilMs = millis() + ms / 4 + 50;
}

// The fleet's shared boot voice: two rising toots, C4 -> G4. Scaled with the new default
// so the boot toot keeps its intended place in the mix — it is meant to be noticeably
// softer than a band note, not softer by an accident of absolute numbers.
static const float STARTUP_TOOT_AMP = 11000.0f;
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
//
// The BMI270 is a 6-axis part and the SparkFun driver enables BOTH features in
// begin(), so the gyro has always been free here — we were reading half the sensor.
// Angular velocity is a perceptually different quantity from tilt (a flick, not a
// lean), and it is what makes the eyeball dart instead of sweep (§2, §4.1).
// THE FACE AND THE TIER NOW SAMPLE AT DIFFERENT RATES, deliberately. Reflexes need a
// fast eye; the @LAT95 percept does not, and its window statistics must not be quietly
// redefined by a display change. So the chip is polled at 50 Hz for the face and the
// motion log is still fed at exactly 20 Hz, as it always was.
//
// 50 Hz is what makes a twitch survive: a flick lasts ~100 ms, which at the old 20 Hz
// was two samples — barely enough to charge the saccade integrator before it decayed.
static const uint32_t IMU_POLL_MS = 20;   // 50 Hz: the face's reflexes
static const uint32_t IMU_TIER_MS = 50;   // 20 Hz: what @LAT95 sees, UNCHANGED
// Angular velocity is a perceptually different quantity from tilt (a flick, not a lean),
// and it is what makes the eyeball dart instead of sweep (§2, §4.1).
static const float SAC_GAIN  = 0.00075f;  // deg/s -> gaze units, per 20 ms sample
static const float SAC_DECAY = 0.88f;     // per 20 ms sample: a flick springs back ~160 ms
// Linear acceleration — gravity removed — kicks the eye too. The gyro only sees ROTATION,
// so before this a shove, a tap, or setting the deck down hard moved the eye not at all
// unless it happened to twist on the way. An eye that ignores being shoved is not
// responsive to movement, it is responsive to one KIND of movement.
static const float ACC_KICK  = 0.09f;     // g of non-gravity accel -> gaze units
static const int   TAP_MG    = 320;       // deviation from 1 g that counts as a tap
static void serviceImu(uint32_t now) {
  static uint32_t last = 0, lastTier = 0;
  if (now - last < IMU_POLL_MS) return;
  last = now;
  if (!gImuOk || gImu.getSensorData() != BMI2_OK) return;
  int ax = (int)(gImu.data.accelX * 1000.0f);  // g -> milli-g
  int ay = (int)(gImu.data.accelY * 1000.0f);
  int az = (int)(gImu.data.accelZ * 1000.0f);
  if (now - lastTier >= IMU_TIER_MS) { lastTier = now; gMotionLog.add(ax, ay, az, now); }

  // Heavy low-pass: the globe should answer a deliberate tilt, not a hand tremor. The
  // COEFFICIENT dropped 0.12 -> 0.05 with the faster poll purely to hold the time
  // constant where it was (~390 ms). This filter has a second job now — it is the
  // gravity estimate the linear-acceleration kick below subtracts — and letting it speed
  // up would have let it chase the very transients that kick is trying to isolate.
  float hpX = gImu.data.accelX - gTiltX;       // what is left after gravity: a shove
  float hpY = gImu.data.accelY - gTiltY;
  gTiltX += hpX * 0.05f;
  gTiltY += hpY * 0.05f;

  // Saccade + tap, sampled here at 50 Hz rather than in the renderer, so a quick flick
  // between two frames still lands. Gravity-invariant, like the motion tier's own
  // statistic: this is acceleration, not orientation.
  float mag = sqrtf((float)ax * ax + (float)ay * ay + (float)az * az);
  gDevMg = (int)fabsf(mag - 1000.0f);
  if (gDevMg > TAP_MG) gTapAt = now;
  gSacX = gSacX * SAC_DECAY + gImu.data.gyroY * SAC_GAIN + hpX * ACC_KICK;
  gSacY = gSacY * SAC_DECAY + gImu.data.gyroX * SAC_GAIN + hpY * ACC_KICK;
  if (gSacX >  0.85f) gSacX =  0.85f;
  if (gSacX < -0.85f) gSacX = -0.85f;
  if (gSacY >  0.85f) gSacY =  0.85f;
  if (gSacY < -0.85f) gSacY = -0.85f;
}
#endif

#if USE_MIC && USE_CARD_HW
// Read a block of the codec's ADC and fold it into the acoustic window. Each block is
// timestamped on the FLEET clock when we are synced, because that timestamp is the
// entire point of the tier (TDoA).
//
// READ ALIGNED TO THE DMA, FED TO THE TIER UNCHANGED. That split is the whole point of
// the function's shape, and it is not optional — three facts about ESP_I2S force it:
//
//   1. `I2SClass::available()` is a STUB. It returns the constant I2S_READ_CHUNK_SIZE
//      (1920) regardless of what is actually buffered, so the `if (avail < sizeof(block))
//      return;` guard that used to sit here could never fire — it was dead code that read
//      like a non-blocking guard.
//   2. `readBytes()` loops until it has the FULL request, blocking on the DMA.
//   3. **The RX DMA is configured `dma_frame_num = 240`**, and nothing becomes readable
//      until a whole descriptor completes. At 8 kHz that descriptor is exactly **30 ms**
//      of audio — which is precisely the 29-30 ms this section was measured at.
//
// So a 128-frame (16 ms) request waited for the full 30 ms descriptor no matter when it
// was asked; the main loop spent 30 ms per pass waiting for the microphone. The toot link
// is serviced once per pass, so whatever the loop waits on, the whole fleet waits on
// (companion.md §6). Pacing alone does NOT fix this: any request smaller than a descriptor
// still waits for the descriptor.
//
// The fix reads **exactly one descriptor** and only once per descriptor period, so the
// data has already landed when we ask and the read returns at once. What the tier sees is
// then decoupled from that: the samples go through a small carry buffer and are handed to
// `@LAT94` in the **same 128-frame blocks at the same 16 ms spacing as before**, with each
// block's fleet-clock timestamp derived from how many frames still sit behind it. The
// TDoA datum is untouched — only what waits for what has changed.
// --- beat-scheduled capture (CMD_RECORD -> TTDB_REQ_RECORDING) ---------------
//
// A recording that starts on a BEAT rather than on a threshold. Broadcast one command
// and every node captures the same window of wall-clock time, because the band clock is
// already a shared time base the whole fleet agrees on (TTN-RFC-0010). Two nodes that
// heard the same clap can then be cross-correlated directly — no threshold in the path,
// which is precisely the weakness §6 identifies in the @LAT94 transient timestamps: a
// threshold fires at a different point on the waveform depending on distance and gain,
// so its error is the shape of the sound rather than the geometry.
//
// SIZED AT ONE BAR, and that is not arbitrary: 4 beats at 120 BPM is 2 s, which at
// 8 kHz/16-bit mono is 32,000 bytes. The largest contiguous block this node can actually
// allocate once WiFi and BLE are up is ~45 KB (measured — it is why the oscilloscope's
// canvas was refused), so one bar fits in RAM with room and needs no filesystem, no
// repartition and no SD card. It is a static buffer for the same reason the scope's row
// buffer is: an allocation that can fail is a feature that can vanish.
// (the buffer + its state live up with the other published sense state, because
// serveTtdbReq reads them and sits earlier in the file than this)

// Arm a capture. Refuses rather than guesses: a node with no chart has no idea when the
// requested instant IS, and a buffer stamped with a clock we do not really hold is worse
// than no buffer at all — the entire hypothesis rests on those timestamps being true.
static bool armRecord(uint64_t start_band_epoch_ms, uint16_t dur_beats) {
#if USE_PULSE
  if (!gPulse.playing()) { Serial.println("[rec] declined: no chart"); return false; }
  // A broadcast is sent more than once so a node cannot silently miss it, which means
  // duplicates are NORMAL. Re-arming for an instant we are already committed to must be
  // a no-op — without this a second copy arriving mid-capture would restart the buffer
  // and we would return the tail of the window as though it were the whole of it.
  if ((gRecArmed || gRecActive) && gRecReqEpoch == start_band_epoch_ms) return true;
  uint32_t per = gPulse.chart().beat_period_ms ? gPulse.chart().beat_period_ms
                                               : PULSE_DEFAULT_BEAT_MS;
  uint64_t want = (uint64_t)dur_beats * per * I2S_RATE / 1000;
  if (want == 0 || want > REC_MAX_SAMPLES) want = REC_MAX_SAMPLES;
  gRecWant = (uint32_t)want;
  gRecReqEpoch = start_band_epoch_ms;
  gRecHave = 0;
  gRecFlags = 0;
  gRecActive = false;
  gRecArmed = true;
  Serial.printf("[rec] armed: start %llu (in %lld ms) %u beats = %lu samples\n",
                (unsigned long long)start_band_epoch_ms,
                (long long)((int64_t)start_band_epoch_ms - gPulse.pulseNow(millis())),
                dur_beats, (unsigned long)gRecWant);
  return true;
#else
  (void)start_band_epoch_ms; (void)dur_beats;
  return false;
#endif
}

// Called with every mic block. Copies the slice of it that belongs to the capture.
static void serviceRecord(const int16_t* block, size_t frames, uint32_t now) {
#if USE_PULSE
  if (!gRecArmed && !gRecActive) return;
  if (!gPulse.playing()) { gRecArmed = gRecActive = false; return; }

  // The block we were just handed ENDS about now, so it spans [tStart, tEnd] on the band
  // clock. Everything below is in that frame.
  int64_t tEnd = gPulse.pulseNow(now);
  int64_t tStart = tEnd - (int64_t)((frames * 1000) / I2S_RATE);

  size_t i0 = 0;
  if (gRecArmed) {
    if ((int64_t)gRecReqEpoch > tEnd) return;            // still in the future: wait
    if ((int64_t)gRecReqEpoch > tStart) {
      // The start lands INSIDE this block — begin at that sample, not at the block edge.
      i0 = (size_t)((((int64_t)gRecReqEpoch - tStart) * (int64_t)I2S_RATE) / 1000);
      if (i0 >= frames) return;
    } else {
      gRecFlags |= toot::REC_FLAG_LATE;   // we missed it; say so rather than pretend
    }
    gRecArmed = false;
    gRecActive = true;
    gRecHave = 0;

    // Stamp what we BELIEVE, at sample 0. This is the header's whole purpose: the fleet
    // wanders together by 15-25 ms, and a reported clock is a correctable offset whereas
    // an assumed one is permanent error.
    uint64_t start = (uint64_t)(tStart + (int64_t)((i0 * 1000) / I2S_RATE));
    uint8_t* h = gRecObj;
    toot::put_u32(h + 0, toot::RECHDR_MAGIC);
    toot::put_u32(h + 4, kNodeId);
    toot::put_u32(h + 8, I2S_RATE);
    toot::put_u32(h + 12, 0);                            // samples: filled at the end
    toot::put_u64(h + 16, start);
    toot::put_u64(h + 24, gRecReqEpoch);
    toot::put_u64(h + 32, (uint64_t)gPulse.offsetMs());
    toot::put_u64(h + 40, gSynced ? (uint64_t)nowEpochMs() : 0);
    toot::put_u32(h + 48, gPulse.chart().era);
    toot::put_u32(h + 52, gPulse.chart().conductor_id);
    toot::put_u16(h + 56, gPulse.chart().beat_period_ms);
    if (gSynced) gRecFlags |= toot::REC_FLAG_SYNCED;
    for (size_t i = 58; i < toot::RECHDR_LEN; ++i) h[i] = 0;
  }

  // Our own speaker sounding during the window is not a failure — it is a fact the
  // companion needs, because a node that sang into its own capture will cross-correlate
  // against its own voice rather than the event (§3.3).
  if (now < gToneUntilMs) gRecFlags |= toot::REC_FLAG_SELF;

  int16_t* pcm = (int16_t*)(gRecObj + toot::RECHDR_LEN);
  for (size_t i = i0; i < frames && gRecHave < gRecWant; ++i)
    pcm[gRecHave++] = block[i * 2];                      // left slot = the mic
  if (gRecHave >= gRecWant) {
    gRecActive = false;
    toot::put_u32(gRecObj + 12, gRecHave);
    gRecObj[58] = gRecFlags;
    Serial.printf("[rec] captured %lu samples, flags 0x%02X\n",
                  (unsigned long)gRecHave, gRecFlags);
  }
#else
  (void)block; (void)frames; (void)now;
#endif
}

static const size_t   MIC_TIER_FRAMES = 128;                  // what @LAT94 sees: UNCHANGED
static const size_t   MIC_DMA_FRAMES  = 240;                  // ESP_I2S dma_frame_num
static const uint32_t MIC_POLL_MS = (MIC_DMA_FRAMES * 1000) / I2S_RATE;   // 30 ms
static int16_t gMicCarry[MIC_DMA_FRAMES + MIC_TIER_FRAMES];   // mono, awaiting a full block
static size_t  gMicCarryN = 0;
static void serviceMic(uint32_t now) {
  if (!gCodecOk) return;
  static uint32_t lastRead = 0;
  if (now - lastRead < MIC_POLL_MS) return;
  lastRead = now;
  static int16_t block[MIC_DMA_FRAMES * 2];
  size_t got = gI2S.readBytes((char*)block, sizeof(block));
  size_t frames = got / (sizeof(int16_t) * 2);
  if (!frames) return;
  if (frames > MIC_DMA_FRAMES) frames = MIC_DMA_FRAMES;
  // De-interleave to mono by taking the left slot (the codec is single-channel; both
  // slots carry the same mic).
  if (gMicCarryN + frames > sizeof(gMicCarry) / sizeof(gMicCarry[0]))
    gMicCarryN = 0;                      // can't happen; if it does, drop rather than smear
  for (size_t i = 0; i < frames; ++i) gMicCarry[gMicCarryN + i] = block[i * 2];
  gMicCarryN += frames;

  serviceRecord(block, frames, now);      // beat-scheduled capture, if one is armed

  // Publish the same samples for the scope (§4.2), shifted in as one sweep. This is a
  // copy, not a tap on the tier: the tier's blocks are 128 frames on a 16 ms cadence
  // for TDoA reasons that have nothing to do with a screen, and the display must not
  // get a vote in how the percept is timed.
  {
    size_t keep = frames < SCOPE_SPAN ? frames : SCOPE_SPAN;
    memmove(gScopeRing, gScopeRing + keep, (SCOPE_SPAN * 2 - keep) * sizeof(int16_t));
    for (size_t i = 0; i < keep; ++i)
      gScopeRing[SCOPE_SPAN * 2 - keep + i] = block[i * 2];
  }

  // These samples end NOW; every block still behind them is that many frames older.
  // The transient timestamp is the Phase-3 TDoA datum, so it rides the TEAM TIME
  // STREAM rather than the wall clock: two nodes agreeing with each other is what
  // makes a cross-correlation possible, and knowing the date is not.
  const uint64_t t_ms = gStamp.t_ms ? gStamp.t_ms : (uint64_t)now;
  while (gMicCarryN >= MIC_TIER_FRAMES) {
    size_t rest = gMicCarryN - MIC_TIER_FRAMES;
    uint64_t blk_t = t_ms - (uint64_t)((rest * 1000) / I2S_RATE);
    gAcousticLog.addBlock(gMicCarry, MIC_TIER_FRAMES, blk_t, now);
    memmove(gMicCarry, gMicCarry + MIC_TIER_FRAMES, rest * sizeof(int16_t));
    gMicCarryN = rest;
  }

  // Watch the tier's OWN transient counter rather than re-deciding what a transient is.
  // §4.2 asks the border to flash on "the exact event the @LAT94 log just recorded" — a
  // second threshold in the renderer would flash on a different set of events and quietly
  // lie about the log. `transients()` is already public and resets with the window, so a
  // rise is a new one and a fall is a window boundary.
  {
    int32_t tc = gAcousticLog.transients();
    if (tc > gTransCount && now >= gToneUntilMs) gTransAt = now;   // not our own voice
    gTransCount = tc;
  }

  // Instantaneous loudness for the face. The @LAT94 log keeps window statistics (60 s)
  // which are the wrong timescale for a screen, so this is a separate, cheap mean-|s|
  // over the samples just read — expressed against a slow room baseline, because "loud"
  // only means anything relative to the room this node is standing in (§3.1).
  uint32_t acc = 0;
  for (size_t i = 0; i < frames; ++i) {
    int16_t s = block[i * 2];
    acc += (uint32_t)(s < 0 ? -s : s);
  }
  float lvl = (float)acc / (float)frames;
  gSndAmb += (lvl - gSndAmb) * 0.02f;         // our own voice still feeds the baseline
  if (now < gToneUntilMs) {
    gSndHot *= 0.7f;                          // we are the noise: fully explained (§3.3)
  } else {
    float over = (gSndAmb > 30.0f) ? (lvl / gSndAmb - 1.0f) * 0.5f : 0.0f;
    if (over < 0.0f) over = 0.0f;
    if (over > 1.0f) over = 1.0f;
    gSndHot = (over > gSndHot) ? over : gSndHot * 0.85f;   // fast attack, slow release
  }
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

  // A new selection starts at the top of its record.
  static int lastSel = -2;
  if (gSel != lastSel) { lastSel = gSel; gRecPage = 0; }

  if (!gBottomDirty) return;
  size_t off, len;
  if (!gViewDb->recordSpan(gSel, off, len)) return;
  // ⚠ 520 B here was a READ limit, not a scroll limit — bytes past it never left flash.
  // This panel is worse off than the T-Deck's: four lines of 39 columns is ~156 characters
  // against an RFC-globe record averaging 1036 B and reaching 2666 B, so the pane was
  // showing roughly the first 15% of a record with nothing on screen to say so.
  static char body[3072];
  bool clipped = len > sizeof(body) - 1;
  size_t n = clipped ? sizeof(body) - 1 : len;
  n = gViewDb->readBytes(off, (uint8_t*)body, n);
  body[n] = 0;
  const char* p = strchr(body, '\n');       // skip the header line
  p = p ? p + 1 : body;

  // Wrap the whole body, then draw one page of it, so the page count is honest.
  const int kLineH = 10, kTop = BOTTOM_Y + 11;
  const int kPerPage = (SCR_H - 8 - kTop) / kLineH;
  static const char* ls[160];
  static uint8_t ll[160];
  int nl = 0, col = 0;
  const char* start = p;
  while (*p && nl < 160) {
    if (*p == '\n') {
      if (col > 0) { ls[nl] = start; ll[nl] = (uint8_t)col; ++nl; }
      ++p; start = p; col = 0;
      continue;
    }
    ++col; ++p;
    if (col >= TEXT_COLS) { ls[nl] = start; ll[nl] = (uint8_t)col; ++nl; start = p; col = 0; }
  }
  if (col > 0 && nl < 160) { ls[nl] = start; ll[nl] = (uint8_t)col; ++nl; }

  int pages = (nl + kPerPage - 1) / kPerPage;
  if (pages < 1) pages = 1;
  gRecPages = pages;                        // published for the wrapping key handler
  if (gRecPage >= pages) gRecPage = pages - 1;
  if (gRecPage < 0) gRecPage = 0;

  snprintf(l, sizeof(l), "@LAT%dLON%d %d/%d pg%d/%d%s", r.lat, r.lon, gSel + 1,
           gViewDb->recordCount(), gRecPage + 1, pages, clipped ? "+" : "");
  drawWide(BOTTOM_Y, nodeColor(r.lat, r.lon), l);

  char line[TEXT_COLS + 2];
  int y = kTop;
  for (int i = gRecPage * kPerPage; i < nl && i < (gRecPage + 1) * kPerPage; ++i) {
    int c = ll[i] < TEXT_COLS ? ll[i] : TEXT_COLS;
    memcpy(line, ls[i], c);
    line[c] = 0;
    drawWide(y, ST77XX_WHITE, line);
    y += kLineH;
  }
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

// --- REPRESENTOR: the eyeball resting face (cardputer-sensorium.md §4.1) -----
//
// The first face of the representor. The other modality views (scope, console,
// constellation) and the EPS arbiter that chooses between them are NOT built yet
// (§7 phases S1/S2) — so for now the eye simply is the screen, which is exactly the
// argument for starting here (§3.2): the eye is the only view that reads correctly
// when nothing is happening. A scope with no sound is a flat line; an eye at rest is
// still a face.
//
// Drawn straight to the panel: no canvas, no filesystem, and only the pixels that
// actually changed (§3.4). A frame that moves the iris repaints ~5k pixels; a full
// sclera repaint (entering the face, opening from a blink) ~13k. A frame where the
// deck is sitting still writes ZERO pixels. All of it is far inside the 25 ms budget.
static const int EYE_CX = SCR_W / 2;          // 120
static const int EYE_CY = SCR_H / 2;          // 67
// The eye is now WIDER THAN THE SCREEN IS TALL (148 px on a 135 px panel), so it is
// cropped a few pixels top and bottom — deliberately: it reads as a close-up of an eye
// rather than a ball drawn on a screen. Adafruit_GFX clips every span for us.
static const int EYE_R  = 74;                 // rows -7..141
// Iris and pupil are sized by AREA, not radius: +15% area is radius x sqrt(1.15) =
// x1.072, which is why these are 36/10/18 and not 39/10/20. Growing the radius by 15%
// would have been a 32% bigger iris on the panel.
static const int IRIS_R = 36;                 // +15% area (was 34)
static const int IRIS_OUTLINE = 4;            // thick black limbal ring
static const int IRIS_OUTER = IRIS_R + IRIS_OUTLINE;
static const int PUPIL_R_MIN = 10, PUPIL_R_MAX = 18;  // arousal; +15% area (was 9/17)
// How far the pupil swings on a beat. At rest this is ONE PIXEL — the face breathes
// rather than performs, and you have to look to see it. Arousal opens the swing up.
static const int PUPIL_BEAT_MIN = 1, PUPIL_BEAT_MAX = 7;
// Travel is bounded by the OUTLINE's radius, not the iris's, or a full-tilt gaze pushes
// the black ring past the edge of the sclera.
static const int EYE_REACH = EYE_R - IRIS_OUTER - 2;
// The face does not run on a frame clock — it runs on the BEAT. Rendering happens only
// inside a short pulse at the head of each beat, and between beats the eye is entirely
// still: no gaze update, no repaint, nothing on the SPI bus. Every change the eye has to
// show is consolidated into these few frames.
//
// At the fleet's 120 BPM that is 4 frames per 500 ms instead of a free-running 5, and
// they arrive in a burst rather than a drip. The visible consequence is deliberate: the
// gaze now moves in beat-quantized steps, so the eye tracks a tilt rhythmically instead
// of smoothly. It is a creature with a pulse, not a needle on a meter.
static const uint32_t EYE_PULSE_MS = 220;       // the render window at each beat
static const uint32_t EYE_PULSE_FRAME_MS = 70;  // frames within that window
// Exactly one frame shut. A blink is quantized to the render grid whatever this says, so
// it is DERIVED from the frame interval rather than set in absolute time — the blink
// stays one frame long if the pulse window is ever retimed. One frame is also the floor:
// blinking faster means rendering off the beat, which is the thing this view no longer
// does. Blinks now land ON a beat, which is a better place for them to be anyway.
static const uint32_t BLINK_MS = EYE_PULSE_FRAME_MS - 10;
static const uint32_t BLINK_GAP_MS = 8000;    // idle blink every 8-16 s

// The catchlight: a specular reflection of the room's light source, so it belongs to
// the ROOM, not to the eye — it stays put while the iris slides under it, and is only
// visible when something dark is beneath it. That is why it is a screen coordinate
// and not an offset from the iris.
static const int GLINT_X = EYE_CX - (EYE_R * 45) / 100;   // up and to the left
static const int GLINT_Y = EYE_CY - (EYE_R * 45) / 100;
static const int GLINT_R = 18;

// Which way the eye looks when the deck is tipped. The BMI270's axes are not
// documented for this board in a form worth trusting (its I2C address wasn't either),
// so the mapping is three constants rather than arithmetic buried in the renderer: if
// the gaze runs uphill, flip a sign; if it runs sideways, set the swap.
// **Both signs flipped 2026-07-28** — on hardware the eye ran uphill, so the chip's
// accelerometer frame is opposite to the assumption made blind. The saccade is scaled
// by the SAME constants (the gyro shares the chip's frame), so a flick darts the way
// the lean leans and one flip still fixes an axis end to end.
#define EYE_SWAP_AXES 0
static const float EYE_GAZE_X = -1.0f;
static const float EYE_GAZE_Y =  1.0f;

// The gaze sits in a BOWL, not on a slope. Straight accelerometer tilt is linear in
// sin(angle), so the iris slid off centre at the slightest lean and the face read as a
// spirit level. A bowl is steep in the middle and flat toward the rim: a subtle tilt
// barely disturbs the ball, a steeper tilt runs it a long way, and at the rim it stops.
//
// Response: r = (tilt / BOWL_FULL_G) ^ BOWL_GAMMA, clamped to 1 = the rim.
//   - GAMMA 1.0 is the old linear behaviour (a parabolic bowl); >1 makes the centre a
//     resting place. At 2.0, half a full tilt gets you a quarter of the way out.
//   - FULL_G is the tilt that pins the iris to the rim, in g (sin of the angle): 0.80
//     is ~53 degrees, so the eye can reach the edge without standing the deck up.
// The rim clamp is not new — EYE_REACH already stopped the limbal ring at the sclera's
// edge. What is new is that the ball now *arrives* there rather than getting there early
// and sitting on it.
//
// Only the TILT goes through the bowl. The gyro saccade is a kick, not a lean, and is
// added on top afterwards: sending a flick through a squaring curve would swallow it,
// and the dart is the whole difference between a face and a gauge (§4.1).
static const float BOWL_GAMMA  = 2.0f;
static const float BOWL_FULL_G = 0.80f;
// ...and the saccade's curve, which bends the other way. See renderEye.
static const float SAC_GAMMA   = 0.60f;

// The representor is a set of views now, not just the eye (§4). `gFaceOn` is whether it
// holds the screen at all (vs the inherited globes); `gFaceView` is which sense is
// showing. The EPS arbiter (§7 S1) will eventually own gFaceView; until it does, the
// keyboard does. (`FaceView` itself is declared at the top of the sketch — see the note
// there about arduino-cli's generated prototypes.)
static bool     gFaceOn = true;               // boot into the resting face (§1)
static FaceView gFaceView = FACE_EYE;
static const char* faceViewName(FaceView v) {
  return (v == FACE_SCOPE)  ? "REPRESENTOR (oscilloscope)"
       : (v == FACE_INTERO) ? "REPRESENTOR (interoception)"
       : (v == FACE_BELIEF) ? "REPRESENTOR (link beliefs)"
                            : "REPRESENTOR (eyeball)";
}

static bool  gEyePainted = false;             // is the sclera currently on the panel?
static float gGazeX = 0.0f, gGazeY = 0.0f;    // eased gaze, -1..1
static float gArousal = 0.0f;                 // 0..1 -> pupil dilation
static int   gIrisX = -1000, gIrisY = 0, gPupilR = -1;   // last painted iris
static bool  gBlinking = false;
static uint32_t gBlinkT0 = 0, gNextBlink = 0, gTapSeen = 0;

static const uint16_t COL_SCLERA = rgb565(238, 236, 228);
static const uint16_t COL_IRIS   = rgb565(210, 40, 40);
// (no lid colour: the eyelid is black, so a blink simply takes the eye off the panel)

// Fill the sclera's horizontal spans between two rows. Adafruit_GFX has no clipping,
// so this is how the eyelid stays inside the eye instead of painting the black corners.
//
// Wrapped in ONE startWrite/endWrite. `drawFastHLine` opens and closes its own SPI
// transaction — for a shape made of ~150 spans that overhead, not the pixels, is the
// cost: at 32 MHz the sclera's 17k pixels are ~8 ms of data but measured 22 ms drawn
// span-by-span. Batching is what keeps a full repaint inside the frame budget (§3.4).
static void eyeSpans(int y0, int y1, uint16_t color) {
  if (y0 < EYE_CY - EYE_R) y0 = EYE_CY - EYE_R;
  if (y1 > EYE_CY + EYE_R) y1 = EYE_CY + EYE_R;
  gTft.startWrite();
  for (int y = y0; y <= y1; ++y) {
    int dy = y - EYE_CY;
    int hw = (int)sqrtf((float)(EYE_R * EYE_R - dy * dy));
    if (hw > 0) gTft.writeFastHLine(EYE_CX - hw, y, hw * 2 + 1, color);
  }
  gTft.endWrite();
}

// Lay the sclera down across one row, in the two pieces either side of the disc at
// (ex, ey) that the iris is about to cover. Returns nothing drawn if the row is
// entirely inside that disc.
static inline void scleraRow(int y, int x0, int x1, int ex, int ey, int e2) {
  int edy = y - ey;
  int ehw = (edy * edy < e2) ? (int)sqrtf((float)(e2 - edy * edy)) : -1;
  if (ehw < 0) { gTft.writeFastHLine(x0, y, x1 - x0 + 1, COL_SCLERA); return; }
  int ex0 = ex - ehw, ex1 = ex + ehw;
  if (x0 < ex0) {
    int e = (x1 < ex0 - 1) ? x1 : ex0 - 1;
    gTft.writeFastHLine(x0, y, e - x0 + 1, COL_SCLERA);
  }
  if (x1 > ex1) {
    int s = (x0 > ex1 + 1) ? x0 : ex1 + 1;
    gTft.writeFastHLine(s, y, x1 - s + 1, COL_SCLERA);
  }
}

// Entering the face: clear whatever the globe left AND lay the sclera down, writing
// every pixel at most once. `fillScreen` + `eyeSpans` painted the middle of the screen
// twice — over half the panel — for no benefit.
static void paintEyeBase(int ix, int iy) {
  const int r2 = EYE_R * EYE_R, e2 = IRIS_OUTER * IRIS_OUTER;
  gTft.startWrite();
  for (int y = 0; y < SCR_H; ++y) {
    int dy = y - EYE_CY;
    int hw = (dy * dy < r2) ? (int)sqrtf((float)(r2 - dy * dy)) : -1;
    if (hw <= 0) { gTft.writeFastHLine(0, y, SCR_W, ST77XX_BLACK); continue; }
    int x0 = EYE_CX - hw, x1 = EYE_CX + hw;
    if (x0 > 0) gTft.writeFastHLine(0, y, x0, ST77XX_BLACK);
    scleraRow(y, x0, x1, ix, iy, e2);
    if (x1 < SCR_W - 1) gTft.writeFastHLine(x1 + 1, y, SCR_W - 1 - x1, ST77XX_BLACK);
  }
  gTft.endWrite();
}

// Opening from a blink: the lids covered the whole eye, so the whole sclera comes back
// — minus the disc the iris is about to land on.
static void paintSclera(int ix, int iy) {
  const int r2 = EYE_R * EYE_R, e2 = IRIS_OUTER * IRIS_OUTER;
  gTft.startWrite();
  for (int y = EYE_CY - EYE_R; y <= EYE_CY + EYE_R; ++y) {
    int dy = y - EYE_CY;
    int hw = (int)sqrtf((float)(r2 - dy * dy));
    if (hw > 0) scleraRow(y, EYE_CX - hw, EYE_CX + hw, ix, iy, e2);
  }
  gTft.endWrite();
}

// Erase the crescent the iris vacated: the rows of the OLD iris the NEW one does not
// cover. The new iris is painted FIRST and only the leftover cleared, so the eye never
// flashes white between the erase and the redraw — the K10 canvas-blink lesson applied
// to a view that draws direct to the panel.
//
// Works on the OUTLINE's radius, not the iris's: the black ring is the outermost thing
// that moves, and clearing only the red would leave a crescent of ring behind it.
static void eraseIrisCrescent(int ox, int oy, int nx, int ny) {
  const int r2 = IRIS_OUTER * IRIS_OUTER;
  gTft.startWrite();
  for (int y = oy - IRIS_OUTER; y <= oy + IRIS_OUTER; ++y) {
    int dy = y - oy;
    int hw = (int)sqrtf((float)(r2 - dy * dy));
    int x0 = ox - hw, x1 = ox + hw;
    int ndy = y - ny;
    int nhw = (ndy * ndy <= r2) ? (int)sqrtf((float)(r2 - ndy * ndy)) : -1;
    if (nhw < 0) { gTft.writeFastHLine(x0, y, x1 - x0 + 1, COL_SCLERA); continue; }
    int nx0 = nx - nhw, nx1 = nx + nhw;
    if (x0 < nx0) {
      int e = (x1 < nx0 - 1) ? x1 : nx0 - 1;
      gTft.writeFastHLine(x0, y, e - x0 + 1, COL_SCLERA);
    }
    if (x1 > nx1) {
      int s = (x0 > nx1 + 1) ? x0 : nx1 + 1;
      gTft.writeFastHLine(s, y, x1 - s + 1, COL_SCLERA);
    }
  }
  gTft.endWrite();
}

// Paint ONLY the ring between two radii, never the disc inside it.
//
// This exists because of a visible artifact: `Adafruit_GFX::fillCircle` fills with
// VERTICAL spans, so painting a big black disc and then covering it with red showed the
// black infill sweeping through as vertical bars for the moment before it was covered.
// Filling a circle you are about to cover costs those pixels twice AND you can see it.
// Every ring in this view is now drawn as a ring.
static void drawRing(int cx, int cy, int rIn, int rOut, uint16_t color) {
  if (rOut <= rIn) return;
  const int o2 = rOut * rOut, i2 = rIn * rIn;
  gTft.startWrite();
  for (int y = cy - rOut; y <= cy + rOut; ++y) {
    int dy = y - cy;
    int ho = (int)sqrtf((float)(o2 - dy * dy));
    if (ho <= 0) continue;
    int hi = (dy * dy < i2) ? (int)sqrtf((float)(i2 - dy * dy)) : -1;
    if (hi < 0) { gTft.writeFastHLine(cx - ho, y, ho * 2 + 1, color); continue; }
    gTft.writeFastHLine(cx - ho, y, ho - hi, color);       // left arc
    gTft.writeFastHLine(cx + hi + 1, y, ho - hi, color);   // right arc
  }
  gTft.endWrite();
}

static void drawIris(int x, int y, int pr) {
  gTft.fillCircle(x, y, IRIS_R, COL_IRIS);              // red disc
  drawRing(x, y, IRIS_R, IRIS_OUTER, ST77XX_BLACK);     // limbal ring, ring only
  gTft.fillCircle(x, y, pr, ST77XX_BLACK);              // pupil
}

// Painted last, after the vacated crescent has been cleared — otherwise an iris moving
// out from under the catchlight erases it on the way past.
static void drawGlint() {
  gTft.fillCircle(GLINT_X, GLINT_Y, GLINT_R, ST77XX_WHITE);
}

// Where the beat is: ms into the current beat, and whether it is a downbeat. This is the
// face's entire clock, so it must never stop — when the band has no chart (no conductor,
// nobody playing) it falls back to a free-running local pulse at the fleet's tempo. A
// creature does not stop having a heartbeat because nobody is playing; it just stops
// having someone else's.
static void eyeBeatPhase(uint32_t now, uint32_t& phase_ms, bool& downbeat) {
#if USE_PULSE
  uint8_t bib; uint16_t ph; uint32_t bc;
  if (gPulse.phaseNow(now, bib, ph, bc)) {
    phase_ms = ph;
    downbeat = (bib == 0);
    return;
  }
#endif
  phase_ms = now % PULSE_DEFAULT_BEAT_MS;
  downbeat = ((now / PULSE_DEFAULT_BEAT_MS) % 4) == 0;
}

// The only thing that lets the face draw.
//
// TWO CLOCKS, and which one is running is itself expressive. At rest the face runs on
// the BEAT: four frames in a pulse at the head of each beat, then nothing — a creature
// keeping time, and zero pixels on the SPI bus. The moment the deck is actually moved it
// switches to a fast free-running clock and tracks.
//
// This is not a compromise of the beat design, it is what saves it. At 120 BPM the beat
// gate leaves 280 ms of every 500 ms in which the eye cannot draw AT ALL, and a flick
// lasts about 100 ms — so a twitch that started just after a pulse was over before the
// eye was next allowed to move, and the face read as laggy rather than rhythmic. Keeping
// time is only legible when the eye is otherwise responsive.
static const uint32_t EYE_LIVE_FRAME_MS = 40;   // 25 Hz while something is happening
// How much stir it takes to break the beat gate. Above the resting noise of the gyro and
// the accelerometer, below a deliberate movement — if this is too low the face never goes
// quiet and the "zero pixels when held still" property is lost, which is worth more than
// a few extra frames.
static const float EYE_STIR = 0.10f;

static bool eyeFrameDue(uint32_t now) {
  static uint32_t last = 0;
  if (!gEyePainted) { last = now; return true; }   // entry must not wait for a beat
  float stir = fabsf(gSacX) + fabsf(gSacY) + (float)gDevMg / 600.0f;
  if (stir > EYE_STIR) {                            // moving: track it
    if (now - last < EYE_LIVE_FRAME_MS) return false;
    last = now;
    return true;
  }
  uint32_t ph; bool db;
  eyeBeatPhase(now, ph, db);
  if (ph >= EYE_PULSE_MS) return false;             // still, between beats: hold
  if (now - last < EYE_PULSE_FRAME_MS) return false;
  last = now;
  return true;
}

// One frame of the resting face.
//
// The geometry is worked out BEFORE anything is painted, so the two expensive repaints
// (entering the face, opening from a blink) can skip the disc the iris is about to
// cover. Never paint a pixel you are about to paint over: that is what keeps the
// blink-open frame inside the 25 ms budget now that the limbal ring made the iris
// bigger — it measured 26 ms drawn in the naive order.
static void renderEye(uint32_t now) {
  // Gaze follows gravity, so the eye looks DOWNHILL: tip the deck and it turns its
  // attention that way. The saccade rides on top — the gyro displaces the pupil
  // sharply and it springs back, which is the whole difference between a gauge and a
  // face.
#if EYE_SWAP_AXES
  float tx = gTiltY * EYE_GAZE_X, ty = gTiltX * EYE_GAZE_Y;
  float sx = gSacY  * EYE_GAZE_X, sy = gSacX  * EYE_GAZE_Y;
#else
  float tx = gTiltX * EYE_GAZE_X, ty = gTiltY * EYE_GAZE_Y;
  float sx = gSacX  * EYE_GAZE_X, sy = gSacY  * EYE_GAZE_Y;
#endif
  // Roll the ball down the bowl: keep the tilt's DIRECTION, replace its magnitude with
  // the bowl's response to it. Scaling the axes independently would bend the gaze away
  // from downhill on the diagonals.
  float tm = sqrtf(tx * tx + ty * ty);
  if (tm > 1e-4f) {
    float n = tm / BOWL_FULL_G;
    if (n > 1.0f) n = 1.0f;                  // past the rim the ball just sits there
    float r = powf(n, BOWL_GAMMA);
    tx = tx / tm * r;
    ty = ty / tm * r;
  } else {
    tx = ty = 0.0f;                          // dead flat: the ball is in the middle
  }

  // The saccade gets the OPPOSITE curve to the bowl, and for the opposite reason. The
  // bowl is expansive (gamma > 1) so that a lean has to be meant before the eye answers
  // it. A twitch is never "meant" — it is small by nature, and the whole point of it is
  // that you can see the eye react. So the saccade is COMPRESSIVE (gamma < 1): a small
  // flick already throws the pupil a long way, and a violent one saturates instead of
  // scaling on forever. Magnitude only, direction untouched, same as the bowl.
  float sm = sqrtf(sx * sx + sy * sy);
  if (sm > 1e-4f) {
    float n = (sm > 1.0f) ? 1.0f : sm;
    float r = powf(n, SAC_GAMMA);
    sx = sx / sm * r;
    sy = sy / sm * r;
  }

  // Ease toward the target. Faster than it was (0.35), because at 25 Hz the old constant
  // spent most of a dart catching up with itself — the eye arrived after the flick was
  // over. A dart should land inside about three frames.
  float gx = tx + sx, gy = ty + sy;
  gGazeX += (gx - gGazeX) * 0.55f;
  gGazeY += (gy - gGazeY) * 0.55f;
  float ex = gGazeX, ey = gGazeY;
  float m = sqrtf(ex * ex + ey * ey);
  if (m > 1.0f) { ex /= m; ey /= m; }

  // Pupil dilation carries TWO things at once: how aroused the node is, and where the
  // band is in the bar. Arousal is a STAND-IN for the arbiter's summed EPS (§3.1,
  // phase S1) — two raw terms, each already against its own baseline; when the arbiter
  // lands this becomes one line reading its total.
  float want = gSndHot;
  float mot = (float)gDevMg / 400.0f;
  if (mot > 1.0f) mot = 1.0f;
  if (mot > want) want = mot;
  gArousal = (want > gArousal) ? want : gArousal * 0.88f;

  // The beat rides on top as a swing that decays across the pulse window. With nothing
  // else happening the swing is a single pixel: the eye is doing one thing, quietly, and
  // that one thing is keeping time. Arousal is what makes the beat visible.
  uint32_t ph; bool downbeat;
  eyeBeatPhase(now, ph, downbeat);
  float env = (ph < EYE_PULSE_MS) ? (1.0f - (float)ph / (float)EYE_PULSE_MS) : 0.0f;
  if (!downbeat) env *= 0.55f;
  float swing = PUPIL_BEAT_MIN + gArousal * (PUPIL_BEAT_MAX - PUPIL_BEAT_MIN);

  int ix = EYE_CX + (int)(ex * EYE_REACH);
  int iy = EYE_CY + (int)(ey * EYE_REACH);
  int pr = PUPIL_R_MIN + (int)(gArousal * (PUPIL_R_MAX - PUPIL_R_MIN)
                               + env * swing + 0.5f);

  if (!gEyePainted) {                     // entering the face, or recovering from one
    paintEyeBase(ix, iy);
    gEyePainted = true;
    gIrisX = -1000;                       // force the iris to paint
    gPupilR = -1;
    gBlinking = false;
    gNextBlink = now + BLINK_GAP_MS + (uint32_t)random(BLINK_GAP_MS);
  }

  // Blink: on a hard tap, and idly every 8-16 s so a resting eye is alive without
  // fidgeting. One frame shut, one frame open — the lids go straight to fully closed
  // because on this frame grid a partial phase would eat the entire blink. The gaze
  // above keeps tracking behind the closed lids, so the eye opens looking the right way.
  //
  // A blink may only START in the first half of the pulse window, or its opening frame
  // falls outside the window and the eye stays shut until the next beat.
  if (!gBlinking) {
    bool tapped = (gTapAt != 0 && gTapAt != gTapSeen && now - gTapAt < 400);
    if (gTapAt != 0) gTapSeen = gTapAt;
    if ((tapped || (int32_t)(now - gNextBlink) >= 0) && ph < EYE_PULSE_MS / 2) {
      gBlinking = true;
      gBlinkT0 = now;
    }
  }
  if (gBlinking) {
    if (now - gBlinkT0 < BLINK_MS) {
      eyeSpans(EYE_CY - EYE_R, EYE_CY + EYE_R, ST77XX_BLACK);
      return;                             // the iris is behind the lids
    }
    gBlinking = false;
    gNextBlink = now + BLINK_GAP_MS + (uint32_t)random(BLINK_GAP_MS);
    paintSclera(ix, iy);
    gIrisX = -1000;
  }

  if (ix != gIrisX || iy != gIrisY) {          // the gaze moved: the whole iris follows
    int ox = gIrisX, oy = gIrisY;
    drawIris(ix, iy, pr);
    if (ox > -999) eraseIrisCrescent(ox, oy, ix, iy);
    drawGlint();
    gIrisX = ix; gIrisY = iy; gPupilR = pr;
  } else if (pr != gPupilR) {
    // The pupil breathed but the eye is looking where it was. Touch NOTHING but the
    // circumference between the two radii: black outward to dilate, iris-red inward to
    // constrict. This is the resting case — a one-pixel ring on the beat — so it has to
    // be the cheapest and quietest thing the face does, not a repaint of the whole iris.
    int rIn  = (pr < gPupilR) ? pr : gPupilR;
    int rOut = (pr > gPupilR) ? pr : gPupilR;
    drawRing(ix, iy, rIn, rOut, (pr > gPupilR) ? ST77XX_BLACK : COL_IRIS);
    gPupilR = pr;
    // The catchlight is in room coordinates, so the ring can pass under it. Put it back
    // only when it actually did.
    int gdx = GLINT_X - ix, gdy = GLINT_Y - iy, reach = GLINT_R + rOut;
    if (gdx * gdx + gdy * gdy <= reach * reach) drawGlint();
  }
}

// ===================== 4.2 the oscilloscope — sound (green) ==================
//
// The second representor view. Where the eye is a creature, this is an instrument: it
// shows the microphone's actual waveform, 240 columns = 240 samples = one 30 ms sweep.
//
// THE RENDERING STRATEGY IS THE OPPOSITE OF THE EYE'S, on purpose. The eye paints
// straight to the panel and touches only what moved, because almost nothing moves. A
// scope changes in every column of every frame, so "only what changed" buys nothing —
// the eye's own rule (never paint a pixel twice) would degenerate into ~500 separate
// spans, and it is the per-span `setAddrWindow`, not the pixels, that costs (§7 S2).
//
// So the scope opens ONE address window over the band of rows that can have changed and
// streams it row by row, straight from a 480-byte row buffer. One `setAddrWindow` for
// the whole frame: the per-span overhead that dominates the eye's cost disappears
// entirely, and what remains is only the pixels themselves. A quiet room deflects into
// a thin band around the centre line and pushes ~20 rows; a loud one pushes the lot.
// Loud sound costs more than quiet sound, which is the right way round.
//
// ⚠ THIS DELIBERATELY DOES NOT USE A CANVAS, and §6's budget line for one is wrong.
// The first build did allocate the 64,800 B full-screen canvas §6 budgets "against
// 249 KB free heap" — and it **failed on hardware**: `[scope] canvas alloc failed`. The
// static free-heap figure is not the number that matters. By the time this view can be
// opened, WiFi, BLE (Bluedroid), ESP-NOW and the 36 KB globe canvas are all up, and what
// is missing is a *contiguous* 65 KB block, not 65 KB. Streaming rows needs 480 bytes
// and cannot fail, which is a better property than fitting today.
#if USE_MIC && USE_CARD_HW
static const int SCOPE_HDR_H = 12;                    // rows 0..11: the readout
static const int SCOPE_Y0 = SCOPE_HDR_H;              // trace area, rows 12..134
static const int SCOPE_Y1 = SCR_H - 1;
static const int SCOPE_CY = (SCOPE_Y0 + SCOPE_Y1) / 2;
static const int SCOPE_HALF = SCOPE_CY - SCOPE_Y0 - 2;   // deflection limit, px

static const uint16_t COL_TRACE = rgb565(0, 255, 90);
static const uint16_t COL_GHOST = rgb565(0, 88, 32);   // peak-hold, behind the trace
static const uint16_t COL_AXIS  = rgb565(0, 48, 18);
static const uint16_t COL_FRAME = rgb565(0, 110, 44);
static const uint16_t COL_FLASH = rgb565(190, 255, 190);   // a logged @LAT94 transient
static const uint16_t COL_SELF  = rgb565(180, 120, 0);     // ...but that noise is us

static bool     gScopePainted = false;
static uint8_t  gGhost[SCOPE_SPAN];           // peak-hold envelope, px of deflection
static uint8_t  gTrA[SCOPE_SPAN], gTrB[SCOPE_SPAN];   // this frame's trace span per column
static int      gScopeDY0 = SCOPE_CY, gScopeDY1 = SCOPE_CY;   // last frame's dirty band
static float    gScopePk = 400.0f;            // auto-gain reference (peak envelope)
static uint16_t gScopeFrameCol = COL_FRAME;   // last painted border colour
static uint16_t gScopeRow[SCR_W];             // the entire framebuffer this view needs

// The scope's only text, painted ONCE on entry and never again.
//
// This is not a style choice, it is the budget. `Adafruit_GFX::drawChar` with a
// background colour writes every pixel of the glyph cell INDIVIDUALLY — 40 separate
// `setAddrWindow`+1-pixel transactions per character. A 42-character live readout
// measured **~20 ms per frame**, nearly as much as streaming the entire waveform, for
// four numbers nobody reads at 10 Hz. Everything that actually changes is already in the
// picture: the trace shows the level, the ghost shows recent peaks, and the border
// colour carries both the transient flash and the self-noise gate.
static void scopeChrome() {
  gTft.fillScreen(ST77XX_BLACK);
  gTft.setTextSize(1);
  gTft.setTextColor(COL_FRAME);              // transparent: nothing under it but black
  gTft.setCursor(2, 2);
  gTft.print("SCOPE 30ms sweep @8kHz  peak-hold 1s");
}

// One frame every 100 ms — 10 Hz, per §3.4. Deliberately NOT the eye's beat clock: the
// eye keeps time because it is a creature, the scope reports what the room is doing and
// should not stutter to a tempo the room knows nothing about.
static bool scopeFrameDue(uint32_t now) {
  static uint32_t last = 0;
  if (!gScopePainted) { last = now; return true; }   // entry must not wait
  if (now - last < 100) return false;
  last = now;
  return true;
}

static void renderScope(uint32_t now) {
  // --- trigger ---------------------------------------------------------------
  // Free-running, the trace is an unreadable smear: each sweep starts at an arbitrary
  // point in the waveform and the whole thing walks sideways. An armed rising-edge
  // trigger (fall below zero to arm, then cross the level going up) locks the sweep to
  // the same point of the same cycle every frame, and a whistled note stands still.
  //
  // The level rides the room's own baseline, not an absolute number: in a quiet room a
  // fixed threshold never fires and the trigger is dead; in a loud one it fires on
  // noise. This is the one place the tier's `ambient` mean is the right statistic.
  int trig = (int)(gSndAmb * 1.5f) + 60;
  if (trig > 6000) trig = 6000;
  size_t t0 = 0;
  bool armed = false;
  for (size_t i = 0; i < SCOPE_SPAN; ++i) {
    if (gScopeRing[i] < 0) armed = true;
    else if (armed && gScopeRing[i] >= trig) { t0 = i; break; }
  }

  // --- auto-gain -------------------------------------------------------------
  // Fast attack, slow release on the PEAK, not the mean. §4.2 says auto-gain off the
  // tier's ambient baseline; a scope actually clips on peaks, so the mean would let a
  // transient run off the top of the screen. The floor is what keeps a silent room
  // showing a living trace instead of a flat line.
  int32_t pk = 0;
  for (size_t i = 0; i < SCOPE_SPAN; ++i) {
    int32_t a = gScopeRing[t0 + i];
    if (a < 0) a = -a;
    if (a > pk) pk = a;
  }
  gScopePk += ((float)pk - gScopePk) * (((float)pk > gScopePk) ? 0.5f : 0.04f);
  float ref = (gScopePk < 300.0f) ? 300.0f : gScopePk;
  float gain = (float)(SCOPE_HALF - 1) / ref;

  // The border carries the two things a waveform cannot say for itself:
  //   FLASH — a transient the @LAT94 log actually recorded, still fresh. This is the one
  //           moment the screen and the percept file are showing you the same event.
  //   SELF  — we are making this noise ourselves (§3.3). The trace is honest about what
  //           the mic hears, and this says whose voice it is.
  bool flash = (gTransAt != 0 && now - gTransAt < 300);
  bool selfNoise = (now < gToneUntilMs);
  const uint16_t frameCol = flash ? COL_FLASH : (selfNoise ? COL_SELF : COL_FRAME);

  // --- work out the geometry, one column at a time ---------------------------
  // Nothing is painted here: the trace span and the ghost envelope are recorded per
  // column first, because the panel is written in ROW order and the waveform arrives in
  // column order. This is the same discipline the eye ended up at for a different
  // reason — settle the geometry, then paint once.
  int prevY = SCOPE_CY;
  int dy0 = SCOPE_CY, dy1 = SCOPE_CY;
  for (int x = 0; x < (int)SCOPE_SPAN; ++x) {
    // Peak-hold ghost, decayed ~15% per frame: at 10 Hz that is a ~1 s tail, so a bang
    // leaves a visible mark instead of flashing past between two frames.
    int g = (gGhost[x] * 218) >> 8;

    int32_t s = gScopeRing[t0 + x];
    int y = SCOPE_CY - (int)(s * gain);
    if (y < SCOPE_Y0 + 1) y = SCOPE_Y0 + 1;
    if (y > SCOPE_Y1 - 1) y = SCOPE_Y1 - 1;
    int d = (y > SCOPE_CY) ? (y - SCOPE_CY) : (SCOPE_CY - y);
    if (d > g) g = d;
    gGhost[x] = (uint8_t)g;
    if (x == 0) prevY = y;      // or column 0 draws a spurious segment from the centre

    // The trace is a SEGMENT from the previous sample to this one, not a dot: at 8 kHz a
    // steep edge jumps tens of rows between columns, and unconnected dots read as a
    // dotted cloud rather than a waveform.
    gTrA[x] = (uint8_t)((prevY < y) ? prevY : y);
    gTrB[x] = (uint8_t)((prevY < y) ? y : prevY);
    prevY = y;

    // The ghost bounds the trace, so it alone defines the rows that can have changed.
    if (SCOPE_CY - g < dy0) dy0 = SCOPE_CY - g;
    if (SCOPE_CY + g > dy1) dy1 = SCOPE_CY + g;
  }

  // Union with last frame's band, or the trace leaves its own tail behind it. Entry and
  // a border change need the whole area: the frame rectangle lives on the outermost rows.
  int p0 = (dy0 < gScopeDY0) ? dy0 : gScopeDY0;
  int p1 = (dy1 > gScopeDY1) ? dy1 : gScopeDY1;
  bool full = (!gScopePainted || frameCol != gScopeFrameCol);
  if (full) { p0 = SCOPE_Y0; p1 = SCOPE_Y1; }
  if (p0 < SCOPE_Y0) p0 = SCOPE_Y0;
  if (p1 > SCOPE_Y1) p1 = SCOPE_Y1;

  // --- stream the band: ONE address window, one row buffer -------------------
  gTft.startWrite();
  gTft.setAddrWindow(0, p0, SCR_W, p1 - p0 + 1);
  for (int y = p0; y <= p1; ++y) {
    if (y == SCOPE_Y0 || y == SCOPE_Y1) {          // top/bottom of the frame rectangle
      for (int x = 0; x < SCR_W; ++x) gScopeRow[x] = frameCol;
    } else {
      int ad = (y > SCOPE_CY) ? (y - SCOPE_CY) : (SCOPE_CY - y);
      bool axis = (y == SCOPE_CY);
      for (int x = 0; x < SCR_W; ++x) {
        uint16_t col = ST77XX_BLACK;
        if (axis && (x & 3) == 0)          col = COL_AXIS;
        if (x < (int)SCOPE_SPAN) {
          if (ad <= gGhost[x])             col = COL_GHOST;
          if (y >= gTrA[x] && y <= gTrB[x]) col = COL_TRACE;
        }
        gScopeRow[x] = col;
      }
      gScopeRow[0] = gScopeRow[SCR_W - 1] = frameCol;   // left/right of the frame
    }
    gTft.writePixels(gScopeRow, SCR_W);
  }
  gTft.endWrite();
  gScopeDY0 = dy0; gScopeDY1 = dy1;
  gScopeFrameCol = frameCol;
  gScopePainted = true;
}
#endif  // USE_MIC && USE_CARD_HW

// ============ 4.5 interoception — the body (blue/amber/red) ==================
//
// The third representor view, and the only one that looks INWARD. The eye is what the
// node's senses do with the world and the scope is the room's own signal; this is the
// node reporting on itself: energy, heat, the room it has left to think in, how fast it
// is currently thinking, and its heartbeat.
//
// (Sensorium §4.5 argued interoception should only ever be ambient colouring on the
// other views, never a view of its own. That was wrong in one specific way: a creature
// that can look at the world but never at itself is exactly as half-finished as the doc
// says a creature with no interoception is. The ambient version is still worth building
// on top of the eye — a battery ring on the sclera — but it is a SUMMARY, and a summary
// is not a place you can go and read a number.)
//
// RENDERING STRATEGY: the eye's, not the scope's. Almost nothing here changes between
// frames — the battery moves in minutes, the die temperature in tens of seconds — so
// every element is compared against what is already on the panel and skipped if it
// still matches. At rest this view paints ONLY the heartbeat.
//
// ⚠ TEXT IS THE EXPENSIVE THING IN THIS VIEW, and it is the reason it is built the way
// it is. `Adafruit_GFX::drawChar` issues one `setAddrWindow`+write per glyph pixel, and
// the scope measured a 42-character live readout at ~20 ms — nearly the cost of the
// entire waveform (§4.2). Two consequences, both load-bearing:
//   1. Every LABEL is painted once on entry, from the key handler, never in a frame.
//   2. Every VALUE is redrawn only when its rendered STRING changes. A frame where the
//      voltage still reads "4.02V" writes nothing at all for that row. This is what
//      makes a text-heavy view affordable at 10 Hz — the strings, not the numbers, are
//      the thing compared.
// Values are drawn with a TRANSPARENT background over a one-`fillRect` erase, which is
// ~3x cheaper than opaque text: `drawChar` writes background pixels individually too,
// but a fillRect is a single address window for the whole box.
static const int IN_TITLE_Y = 2;
static const int IN_ROW_Y[3] = {24, 56, 88};      // top of each gauge row
static const int IN_LBL_X  = 3;                   // "BAT" / "DIE" / "MEM", size 1
static const int IN_VAL_X  = 28;                  // the number, size 2
static const int IN_VAL_W  = 76;
static const int IN_BAR_X  = 108, IN_BAR_W = 128, IN_BAR_H = 14;
static const int IN_FILL_W = IN_BAR_W - 2, IN_FILL_H = IN_BAR_H - 2;
static const int IN_FOOT_Y = 118;
static const int HEART_CX  = 224, HEART_CY = 9;   // the beat, top right
static const int HEART_MIN = 3, HEART_MAX = 8;

static const uint16_t IN_COL_TITLE = rgb565(70, 110, 140);
static const uint16_t IN_COL_LBL   = rgb565(130, 145, 165);
static const uint16_t IN_COL_FRAME = rgb565(48, 62, 80);
static const uint16_t IN_COL_FOOT  = rgb565(140, 155, 175);
static const uint16_t IN_COL_HEART = rgb565(210, 40, 60);

// One band per gauge, so a glance is enough: the colour IS the reading. The number is
// for when you want to know how bad, the colour is for whether to care.
static const uint16_t IN_COL_GOOD  = rgb565(40, 210, 120);
static const uint16_t IN_COL_WARN  = rgb565(240, 175, 40);
static const uint16_t IN_COL_BAD   = rgb565(235, 60, 50);
static const uint16_t IN_COL_COOL  = rgb565(60, 190, 225);
static const uint16_t IN_COL_MIND  = rgb565(130, 145, 245);

static bool     gInPainted = false;
static char     gInVal[3][10] = {{0}, {0}, {0}};     // last strings on the panel
static uint16_t gInCol[3] = {0, 0, 0};               // last colours on the panel
static int      gInFill[3] = {-1, -1, -1};           // last fill widths, px
static char     gInFoot[42] = {0};
static int      gInHeart = -1;

// The chrome: everything that never changes. Painted once, on entry, from the key
// handler — a key press can afford 20 ms, a render frame cannot (§4.2).
static void interoChrome() {
  gTft.fillScreen(ST77XX_BLACK);
  gTft.setTextSize(1);
  gTft.setTextColor(IN_COL_TITLE);
  gTft.setCursor(IN_LBL_X, IN_TITLE_Y);
  gTft.print("INTEROCEPTION");
  static const char* kLbl[3] = {"BAT", "DIE", "MEM"};
  gTft.setTextColor(IN_COL_LBL);
  for (int i = 0; i < 3; ++i) {
    gTft.setCursor(IN_LBL_X, IN_ROW_Y[i] + 5);
    gTft.print(kLbl[i]);
    gTft.drawRect(IN_BAR_X, IN_ROW_Y[i] + 1, IN_BAR_W, IN_BAR_H, IN_COL_FRAME);
  }
  gTft.drawFastHLine(0, IN_FOOT_Y - 6, SCR_W, IN_COL_FRAME);
}

// Flat 10 Hz. Unlike the eye this view does not run on the beat — it is an instrument
// reporting on a body, and a body's temperature does not have a tempo. The HEARTBEAT
// inside it does, and it reads the same never-stopping clock the eye does.
static bool interoFrameDue(uint32_t now) {
  static uint32_t last = 0;
  if (!gInPainted) { last = now; return true; }
  if (now - last < 100) return false;
  last = now;
  return true;
}

// Repaint one gauge row, but only the parts of it that actually differ from the panel.
static void interoRow(int i, const char* val, uint16_t col, int pct) {
  if (col != gInCol[i] || strcmp(val, gInVal[i]) != 0) {
    gTft.fillRect(IN_VAL_X, IN_ROW_Y[i] + 1, IN_VAL_W, 16, ST77XX_BLACK);
    gTft.setTextSize(2);
    gTft.setTextColor(col);                     // transparent: the box is already black
    gTft.setCursor(IN_VAL_X, IN_ROW_Y[i] + 2);
    gTft.print(val);
    gTft.setTextSize(1);
    snprintf(gInVal[i], sizeof(gInVal[i]), "%s", val);
  }
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  int w = (IN_FILL_W * pct) / 100;
  const int x = IN_BAR_X + 1, y = IN_ROW_Y[i] + 2;
  if (col != gInCol[i]) {                       // banded across: repaint the whole fill
    if (w) gTft.fillRect(x, y, w, IN_FILL_H, col);
    if (w < IN_FILL_W) gTft.fillRect(x + w, y, IN_FILL_W - w, IN_FILL_H, ST77XX_BLACK);
  } else if (w > gInFill[i]) {                  // grew: paint only the new part
    gTft.fillRect(x + gInFill[i], y, w - gInFill[i], IN_FILL_H, col);
  } else if (w < gInFill[i]) {                  // shrank: black out only what it lost
    gTft.fillRect(x + w, y, gInFill[i] - w, IN_FILL_H, ST77XX_BLACK);
  }
  gInFill[i] = w;
  gInCol[i] = col;
}

static void renderIntero(uint32_t now) {
  char v[10];

  // --- energy ---------------------------------------------------------------
  // The trend arrow is appended to the voltage rather than given its own glyph position,
  // so it costs nothing extra: it is part of a string that is already being compared.
  uint16_t mv = gBatMv;
  snprintf(v, sizeof(v), "%u.%02u%c", mv / 1000, (mv % 1000) / 10,
           gBatTrend > 0 ? '^' : gBatTrend < 0 ? 'v' : ' ');
  uint16_t bcol = (gBatPct > 50) ? IN_COL_GOOD : (gBatPct > 20) ? IN_COL_WARN
                                                                : IN_COL_BAD;
  interoRow(0, v, bcol, gBatPct);

  // --- heat -----------------------------------------------------------------
  // 20-80 C across the bar. The die idles in the forties with the radios up, so the
  // resting bar sits around a third — deliberately, so a real climb is visible as one.
  snprintf(v, sizeof(v), "%d.%dC", gDieC10 / 10, abs(gDieC10 % 10));
  uint16_t tcol = (gDieC10 < 450) ? IN_COL_COOL : (gDieC10 < 600) ? IN_COL_WARN
                                                                  : IN_COL_BAD;
  interoRow(1, v, tcol, (int)((gDieC10 / 10 - 20) * 100 / 60));

  // --- room to think --------------------------------------------------------
  // maxalloc, NOT free heap. The free-heap number reads ~245 KB and is a lie about what
  // can actually be allocated: the oscilloscope's 65 KB canvas was refused at exactly
  // that number (companion.md §6). 64 KB is full scale.
  snprintf(v, sizeof(v), "%luK", (unsigned long)gMaxAllocK);
  uint16_t mcol = (gMaxAllocK > 32) ? IN_COL_MIND : (gMaxAllocK > 16) ? IN_COL_WARN
                                                                      : IN_COL_BAD;
  interoRow(2, v, mcol, (int)(gMaxAllocK * 100 / 64));

  // --- the footer: uptime, own slowness, the band, the clock ----------------
  // `lp` is this node's sense of its OWN response time — the worst loop pass in the
  // current profiler window, which is exactly what the mesh feels as rtt (§3.4). It
  // belongs on the interoception screen more than anywhere else: it is the node
  // noticing that it has become sluggish.
  char f[42];
  uint32_t up = now / 1000;
#if USE_PULSE
  const pulse::Chart& ch = gPulse.chart();
  unsigned bpm = ch.beat_period_ms ? (unsigned)(60000UL / ch.beat_period_ms) : 0;
  if (up < 3600) snprintf(f, sizeof(f), "up %lum%02lus  lp%lums  %ubpm %s%s %s",
                          (unsigned long)(up / 60), (unsigned long)(up % 60),
                          (unsigned long)gWorstLoopMs, bpm,
                          nodeName(ch.conductor_id), gPulse.conductor() ? "*" : "",
                          gSynced ? "clk+" : "clk-");
  else snprintf(f, sizeof(f), "up %luh%02lum  lp%lums  %ubpm %s%s %s",
                (unsigned long)(up / 3600), (unsigned long)((up % 3600) / 60),
                (unsigned long)gWorstLoopMs, bpm,
                nodeName(ch.conductor_id), gPulse.conductor() ? "*" : "",
                gSynced ? "clk+" : "clk-");
#else
  snprintf(f, sizeof(f), "up %lum%02lus  lp%lums  %s",
           (unsigned long)(up / 60), (unsigned long)(up % 60),
           (unsigned long)gWorstLoopMs, gSynced ? "clk+" : "clk-");
#endif
  if (strcmp(f, gInFoot) != 0) {
    gTft.fillRect(0, IN_FOOT_Y, SCR_W, 10, ST77XX_BLACK);
    gTft.setTextSize(1);
    gTft.setTextColor(IN_COL_FOOT);
    gTft.setCursor(IN_LBL_X, IN_FOOT_Y);
    gTft.print(f);
    snprintf(gInFoot, sizeof(gInFoot), "%s", f);
  }

  // --- the heartbeat --------------------------------------------------------
  // The one thing here that moves every frame, and the cheapest: a disc that swells on
  // the beat and relaxes between them, painted as the RING between the old radius and
  // the new one (never a disc you are about to cover — §4.1's rule, same reason). It
  // runs on the same clock the eye's pupil does, including the free-running local
  // fallback: a body does not stop having a pulse because the conductor died.
  uint32_t ph; bool db;
  eyeBeatPhase(now, ph, db);
  float env = (ph < 240) ? (1.0f - (float)ph / 240.0f) : 0.0f;
  if (!db) env *= 0.55f;                        // the downbeat is the strong one
  int r = HEART_MIN + (int)((HEART_MAX - HEART_MIN) * env + 0.5f);
  if (r != gInHeart) {
    if (gInHeart < 0) gTft.fillCircle(HEART_CX, HEART_CY, r, IN_COL_HEART);
    else if (r > gInHeart) drawRing(HEART_CX, HEART_CY, gInHeart, r, IN_COL_HEART);
    else drawRing(HEART_CX, HEART_CY, r, gInHeart, ST77XX_BLACK);
    gInHeart = r;
  }
  gInPainted = true;
}

// --- FACE_BELIEF: what this node has CONCLUDED about its own links -----------------
//
// The `@LAT91` lane holds the only records on this fleet that carry a TBEW `[ew]` block,
// and until this view existed they could be seen NOWHERE on the fleet's glass — only by
// pulling the TTDB to the laptop. The globes cannot show them: `isNodeRecord()` bounds
// navigation to `lat < 90` (deliberately, to keep the runtime percept/belief/sync lanes
// out of a map), and that bound catches 90-93 as well. A globe is a map of PLACES and a
// belief is not a place, so this is its own view rather than a promotion into that range.
//
// It belongs in the representor stack for the same reason interoception does: both are
// the node reporting on itself. Interoception is the body; this is what the body has
// learned.
struct BeliefRow {
  uint32_t peer;
  char     proto[4];
  int      conf, sal, met, vio;
  bool     contradiction;
};
static BeliefRow gBel[PERCEPTLEARN_MAX_BELIEFS];
static int  gBelN = 0;
static int  gBelRevSeen = -1;
static bool gBelPainted = false;

// Read an integer field. `key` should include the delimiter that makes it unambiguous —
// "\nconf:" and not "conf:", because `**TALLY**` also carries `baseline_conf:`.
static int belField(const char* s, const char* key, int dflt) {
  const char* p = strstr(s, key);
  return p ? atoi(p + strlen(key)) : dflt;
}

// Re-read the lane off flash. ⚠ Called ONLY when the belief revision changes or the view
// is entered — never per frame. Eight records x (recordSpan + readBytes) is exactly the
// per-frame file I/O that cost 767 ms/repaint in the `edgesAt` defect (companion.md §6).
static void readBeliefs() {
  gBelN = 0;
  static char buf[768];
  for (int i = 0; i < gDb.recordCount() && gBelN < PERCEPTLEARN_MAX_BELIEFS; ++i) {
    if (gDb.record(i).lat != PERCEPTLEARN_BELIEF_LANE) continue;
    size_t off, len;
    if (!gDb.recordSpan(i, off, len)) continue;
    size_t n = len < sizeof(buf) - 1 ? len : sizeof(buf) - 1;
    n = gDb.readBytes(off, (uint8_t*)buf, n);
    buf[n] = 0;
    const char* pk = strstr(buf, "peer:0x");
    if (!pk) continue;                       // not a LINK-STABLE body: skip, do not guess
    BeliefRow& b = gBel[gBelN];
    b.peer = (uint32_t)strtoul(pk + 7, nullptr, 16);
    const char* pr = strstr(buf, "proto:");
    snprintf(b.proto, sizeof(b.proto), "%.3s", pr ? pr + 6 : "?");
    b.conf = belField(buf, "\nconf:", 0);
    b.sal  = belField(buf, "\nsal:", 0);
    b.met  = belField(buf, "met:", 0);
    b.vio  = belField(buf, "violated:", 0);
    b.contradiction = belField(buf, "contradiction:", 0) != 0;
    ++gBelN;
    yield();
  }
}

static void beliefChrome() {
  gTft.fillScreen(ST77XX_BLACK);
  gBelPainted = false;
  gBelRevSeen = -1;                          // force a re-read on entry
}

// Beliefs move only when the Dream Cycle rewrites the lane (every 3 min at most), so this
// view repaints on CHANGE rather than on a clock. A static panel costs nothing.
static bool beliefFrameDue(uint32_t now) {
  (void)now;
  return !gBelPainted || gBeliefRev != gBelRevSeen;
}

static void renderBelief(uint32_t now) {
  (void)now;
  if (!gBelPainted || gBeliefRev != gBelRevSeen) {
    readBeliefs();
    gBelRevSeen = gBeliefRev;
    gTft.fillRect(0, 10, SCR_W, SCR_H - 10, ST77XX_BLACK);
  }
  char l[TEXT_COLS + 2];
  snprintf(l, sizeof(l), "LINK BELIEFS @LAT91  %d  rev%d", gBelN, gBeliefRev);
  drawWide(0, rgb565(150, 190, 255), l);

  if (gBelN == 0) {
    // Say WHY it is empty. A blank panel here would look identical to a broken view, and
    // on a freshly imaged filesystem empty is the correct and expected state.
    drawWide(20, rgb565(240, 200, 90), "no belief yet");
    drawWide(32, rgb565(150, 150, 150), "the Dream Cycle writes @LAT91 from");
    drawWide(42, rgb565(150, 150, 150), "@LAT92 testimony; needs a still");
    drawWide(52, rgb565(150, 150, 150), "window + a peer, then <=3 min.");
    gBelPainted = true;
    return;
  }

  const int kRowH = 14, kTop = 16, kBarX = 46, kBarW = 96;
  gTft.setTextSize(1);
  for (int i = 0; i < gBelN; ++i) {
    const int y = kTop + i * kRowH;
    if (y + 9 > SCR_H) break;
    const BeliefRow& b = gBel[i];
    // Colour carries the same meaning as the conf number so the panel reads at a glance:
    // red is not "low" but "the world contradicted this twice running".
    const uint16_t col = b.contradiction ? rgb565(240, 90, 90)
                       : b.conf >= 170   ? rgb565(80, 220, 120)
                       : b.conf >= 100   ? rgb565(240, 200, 90)
                                         : rgb565(240, 140, 90);
    gTft.setTextColor(col, ST77XX_BLACK);
    gTft.setCursor(0, y);
    snprintf(l, sizeof(l), "%03X %-3s", (unsigned)(b.peer & 0xFFF), b.proto);
    gTft.print(l);

    gTft.drawRect(kBarX, y - 1, kBarW, 9, rgb565(60, 66, 78));
    const int w = ((kBarW - 2) * (b.conf < 0 ? 0 : b.conf > 255 ? 255 : b.conf)) / 255;
    if (w) gTft.fillRect(kBarX + 1, y, w, 7, col);
    if (w < kBarW - 2) gTft.fillRect(kBarX + 1 + w, y, kBarW - 2 - w, 7, ST77XX_BLACK);

    gTft.setCursor(kBarX + kBarW + 4, y);
    snprintf(l, sizeof(l), "%3d %2d/%-2d%s", b.conf, b.met, b.vio,
             b.contradiction ? "!" : "");
    gTft.print(l);
  }
  gBelPainted = true;
}

// `t` switches between the representor and the inherited globes (§5). Leaving the face
// hands a clean panel back to the globe renderer, which paints in dirty-rect pieces
// and would otherwise draw over the sclera.
// Lay down whatever the incoming representor view needs before its first frame. The
// eye's entry repaint is part of its own renderer (it has to skip the disc the iris is
// about to cover); the scope's is its one and only text, which belongs here precisely
// BECAUSE it is expensive — a key press can afford 20 ms, a render frame cannot.
static void enterFaceView() {
#if USE_MIC && USE_CARD_HW
  gScopePainted = false;
  gScopeDY0 = gScopeDY1 = SCOPE_CY;
#endif
  // Interoception forgets everything it believes is on the panel, or the first frame
  // after re-entry skips every element that "hasn't changed" and leaves a blank screen.
  gInPainted = false;
  gInHeart = -1;
  gInFoot[0] = 0;
  for (int i = 0; i < 3; ++i) { gInVal[i][0] = 0; gInCol[i] = 0; gInFill[i] = 0; }
  if (gFaceView == FACE_INTERO) { interoChrome(); return; }
  if (gFaceView == FACE_BELIEF) { beliefChrome(); return; }
#if USE_MIC && USE_CARD_HW
  if (gFaceView == FACE_SCOPE) { scopeChrome(); return; }
#endif
  // NO fillScreen for the eye: `paintEyeBase` writes every pixel of the panel exactly
  // once (sclera inside the disc, black outside), so clearing first would paint over
  // half the screen twice — the very thing that was measured out of the entry frame.
  gEyePainted = false;
}

static void setFace(bool on) {
  gFaceOn = on;
  gEyePainted = false;
  if (on) {
    enterFaceView();
  } else {
    gTft.fillScreen(ST77XX_BLACK);
    gGlobeDirty = gBottomDirty = gScreenDirty = true;
  }
  Serial.printf("[face] %s\n", on ? faceViewName(gFaceView) : "globe views");
}

// Switch between representor views. Until the EPS arbiter lands (§7 S1) this is the
// only thing that chooses a view, which is why §5 reserves the number keys for it: the
// arbiter by definition only ever shows you the LOUDEST sense, so without a manual
// selection there is no way to watch a quiet one.
static void setFaceView(FaceView v) {
#if !(USE_MIC && USE_CARD_HW)
  if (v == FACE_SCOPE) v = FACE_EYE;          // no mic, no scope
#endif
  if (v == gFaceView && gFaceOn) return;
  gFaceView = v;
  if (!gFaceOn) { setFace(true); return; }    // setFace lays the new view's chrome down
  enterFaceView();                            // the two views share no chrome at all
  Serial.printf("[face] %s\n", faceViewName(gFaceView));
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
    // Read the DAC volume back rather than trusting the write. 0xBF is unity; anything
    // lower is attenuation this node cannot afford (it is the fleet's quietest voice)
    // and anything higher is digital gain that clips a full-scale square (Es8311.h).
    // Printed because a volume that silently failed to take looks exactly like a speaker
    // that is just small.
    Serial.printf("[codec] DAC vol reg 0x32 = 0x%02X (0xBF = unity/0dB), tone amp %u/32767\n",
                  (unsigned)es8311::readReg(0x32), 30000u);
    gI2S.setPins(PIN_I2S_BCLK, PIN_I2S_WS, PIN_I2S_DOUT, PIN_I2S_DIN, -1);
    if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT,
                   I2S_SLOT_MODE_STEREO)) {
      // The codec is configured and I2S is up either way — the mic (@LAT94) and the
      // band voice both need it. Only the boot signature is gated (STARTUP_TOOT).
      // ⚠ Do NOT "simplify" this to mono or another bit width to save a silent boot:
      // the ES8311 derives MCLK from BCLK here, which only holds at 16-bit STEREO.
#if STARTUP_TOOT
      playStartupToot();
#endif
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
  // 40 MHz, not the library's 24 MHz default. The ST7789V2 is specified well above this
  // and the trace is a few cm on the PCB, so the old default was leaving 40% of the bus
  // on the table. It matters because the ONE cost that cannot be optimized away is pixel
  // data: the oscilloscope (§4.2) pushes a full-height band of 29k pixels on a loud
  // frame, which is 22 ms at 24 MHz and 13 ms at 40. The eye and the globes get faster
  // for free. ⚠ If this panel ever shows torn or speckled pixels, this line is the first
  // suspect — drop it back to 24 MHz before suspecting a renderer.
  gTft.setSPISpeed(40000000);
  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH);
  gTft.fillScreen(ST77XX_BLACK);
  gTft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  gTft.setTextSize(2);
  gTft.setCursor(4, 4);
  gTft.print("CARDPUTER");

  // What this node actually has to spend, printed rather than assumed. The heap FIGURE
  // is not the useful one — `maxalloc` is: the oscilloscope's first build asked for a
  // contiguous 64,800 B canvas and was refused while plenty of heap was free
  // (cardputer-sensorium.md §4.2). Anything sizing a buffer on this board should read
  // this line first.
  Serial.printf("[mem] heap %lu free, maxalloc %lu, psram %lu\n",
                (unsigned long)ESP.getFreeHeap(), (unsigned long)ESP.getMaxAllocHeap(),
                (unsigned long)ESP.getPsramSize());

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

  // The time stream starts EMPTY, not with a stream of our own: this node listens for
  // TIMESTREAM_LISTEN_MS first (gTs.service), because joining an older stream is
  // free and forking one costs a merge. Independent of USE_PULSE — the band is
  // optional, a shared timeline is not.
  gTs.begin(kNodeId, &gDb, millis());

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

  // Take the body's first reading here, AFTER WiFi/BLE/ESP-NOW are up: `maxalloc` before
  // the radios is a number that never comes back, and the first STATUS reply can be
  // asked for immediately. This is also the line that prints the raw ADC millivolts for
  // the divider check (see BAT_DIVIDER).
  serviceIntero(millis());
}

void loop() {
  const uint32_t now = millis();
  gSectN = 0;
  sectMark();                       // [0] top of the pass

  // FIRST, before anything reads a clock: settle which timeline this node is on and
  // refresh gStamp. Every tier below stamps from that one snapshot, so four records
  // flushed in one pass carry the same instant instead of four readings of a clock
  // that moved between them.
  gTs.service(now);

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

  sectMark();                       // [1] end of "link": serial toot + deferred work

  // --- the four percept tiers: sample continuously, flush one record per window ---
  // Every flush is a flash write, so it happens here in loop() and never in a callback,
  // and every lane is capped until SP1 pruning takes it (CMD_CLEAR_PERCEPTS).
  if (gLinkLog.due(now)) {
    int lane = laneCount(97);
    if (lane >= LINKPERCEPT_MAX_LANE) {
      // No @LAT97 record will be written, so an outstanding expectation has nothing to
      // cite as the observation that answered it. Drop it rather than testify with
      // provenance pointing at a record that does not exist.
      gLearn.disarm();
      gLinkLog.reset(now);
    } else {
      // Stage this window's medians BEFORE buildRecord() clears the histograms. They do
      // double duty: they SCORE the expectation armed last window, and they are the
      // basis for the next one (Rule 1 — re-derived from current state, every window).
      gLearn.stageBegin(lane);
      for (int s = 0; s < gLinkLog.peerCount(); ++s) {
        uint32_t pr; uint8_t pt; uint32_t pn; int rmin, rmed, rmax;
        if (gLinkLog.stats(s, pr, pt, pn, rmin, rmed, rmax)) gLearn.stage(pr, pt, rmed);
      }
      // ⚠ Say so when the claim house is full. An overflowed (peer, proto) is scored
      // VERDICT_UNOBSERVED, which is the SAME verdict a peer that genuinely went quiet
      // gets — so without this line a cap that is one slot short looks like the fleet
      // going intermittent. 4 nodes x {espnow, ble} needs exactly PERCEPTLEARN_MAX_CLAIMS,
      // so this is live the moment the V4s come up, not a theoretical limit.
      if (gLearn.stagedOverflow())
        Serial.printf("[learn] %d peer-observation(s) DROPPED - staged claim house full "
                      "(PERCEPTLEARN_MAX_CLAIMS %d): they will score as 'unobserved' and "
                      "are NOT missing peers\n",
                      gLearn.stagedOverflow(), PERCEPTLEARN_MAX_CLAIMS);
      char rec[1024];
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, now);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[link] percept window -> @LAT97LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());

      // Rule 2: the world has answered — score the prediction and TESTIFY. Appended to
      // a side lane; nothing here edits any record's [ew]. That is Stage D's job, and
      // doing it from the live loop is the exact violation Rule 2 names (and the one
      // LOCUS committed).
      if (gLearn.score(gStamp, gStreamWallSec)) {
        if (!gLearn.outcomePending()) {
          // Run-length: this window's verdicts matched the record before it, so it is
          // FOLDED, not written. Say so — a lane that has gone quiet because nothing is
          // changing looks identical to one that has stopped testifying, and the whole
          // reason @LAT92 has a cap is that it used to do the latter silently.
          static uint32_t last_fold_log = 0;
          if (now - last_fold_log > 300000 || last_fold_log == 0) {
            last_fold_log = now;
            Serial.printf("[learn] %d window(s) folded into the run (met:%d violated:%d) "
                          "- unchanged verdicts write no record\n",
                          gLearn.coveredWindows(), gLearn.metCount(),
                          gLearn.violatedCount());
          }
        } else {
          // static: 2624 B is far too much to add to this loop's stack next to the
          // other tiers' buffers (see PERCEPTLEARN_BUF).
          static char orec[PERCEPTLEARN_BUF];
          int olane = laneCount(PERCEPTLEARN_LANE);
          // ⚠ Read the run length BEFORE rendering: buildOutcome adopts the run, which
          // resets the counter to 1. Logging it afterwards would report every record as
          // covering a single window, i.e. exactly as if run-length were not working.
          const int covers = gLearn.windowsSinceLast();
          // ⚠ RENDER EVEN WHEN THE LANE IS FULL, then throw the bytes away. buildOutcome
          // is what adopts the run — skipping it would leave the just-closed run still
          // open, so the NEXT window would compare against a stale verdict vector and a
          // real change could be folded away as "unchanged". A record dropped for want
          // of lane space must not also corrupt the run accounting.
          size_t om = gLearn.buildOutcome(orec, sizeof(orec), olane, kNodeId);
          if (olane >= PERCEPTLEARN_MAX_LANE) {
            Serial.printf("[learn] outcome DROPPED - @LAT%d lane full (%d): the loop is "
                          "still predicting but no longer testifying\n",
                          PERCEPTLEARN_LANE, olane);
          } else if (om && gDb.appendRecord(orec, om)) {
            Serial.printf("[learn] outcome -> @LAT%dLON%d met:%d violated:%d streak:%d "
                          "covers:%d (%uB, TTDB %uB)\n",
                          PERCEPTLEARN_LANE, olane, gLearn.metCount(),
                          gLearn.violatedCount(), gLearn.violationStreak(),
                          covers, (unsigned)om, (unsigned)gDb.fileSize());
          }
        }
      }
    }
  }

  // Stage D: the Dream Cycle's reconciliation pre-phase. Deliberately NOT run from the
  // scoring path — Rule 2 says the live loop testifies and never mutates, so the belief
  // lane moves on its own cadence, reading the testimony back the way a reader would.
  {
    static uint32_t last_dream = 0;
    if (now - last_dream >= DREAM_RECONCILE_MS || last_dream == 0) {
      last_dream = now;
      reconcileBeliefs();
    }
  }

  sectMark();                       // [2] end of "linkperc": the @LAT97 tier

#if USE_WIFI_SCAN
  serviceWifiScan();
  if (gEntityLog.due(now)) {
    int lane = laneCount(96);
    if (lane >= ENTITYPERCEPT_MAX_LANE) {
      gEntityLog.reset(now);
    } else {
      char rec[1024];
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                        gStamp, now);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[entity] percept window -> @LAT96LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

  sectMark();                       // [3] end of "entity": WiFi scan + @LAT96 tier

#if USE_IMU
  serviceImu(now);
  if (gMotionLog.due(now)) {
    int lane = laneCount(95);
    if (lane >= MOTIONPERCEPT_MAX_LANE) {
      // ⚠ SAY THIS OUT LOUD. This path used to be silent, and a silent full lane looks
      // exactly like a healthy node: percept windows keep flushing on the other tiers
      // while the learning loop is disarmed every single window and testifies nothing.
      // That is precisely how it failed on 2026-08-02 — @LAT95 hit 48/48 after 48
      // minutes, four @LAT92 outcomes had been written, and the loop then went quiet
      // with no error anywhere. The motion lane fills ~2x faster than the link lane
      // (motion flushes with no peers in range; link needs an observation), so it is
      // always the first cap to bite.
      static uint32_t last_full_log = 0;
      if (now - last_full_log > 300000 || last_full_log == 0) {
        last_full_log = now;
        Serial.printf("[motion] @LAT95 lane FULL (%d/%d) - windows are being DISCARDED "
                      "and the learning loop is disarmed. Prune with `companion.py cmd "
                      "--op clear-percepts`. (Since run-length landed this should take "
                      "~24 h of uptime, not 48 min - if it is fast, the node is moving "
                      "or flapping at the %d mg threshold.)\n",
                      lane, MOTIONPERCEPT_MAX_LANE, MOTIONPERCEPT_MOVING_MG);
      }
      gMotionLog.reset(now);
      gLearn.disarm();   // no acting record to cite; make no claim
    } else {
      char rec[MOTIONPERCEPT_RECORD_BUF];
      size_t m = gMotionLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                        gStamp, now);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[motion] percept window -> @LAT95LON%d covers:%d (TTDB %uB)\n",
                      lane, gMotionLog.runOffset() + 1, (unsigned)gDb.fileSize());

      // Rule 1: ARM the next expectation, but only on a positive claim. A `still`
      // window asserts the node was anchored for 60 s; that assertion is what makes
      // "the next window's RSSI to each peer will land within the band" a prediction
      // the world can refute. A `moving` window asserts nothing, so it earns no
      // expectation — and any outstanding one is dropped UNSCORED rather than judged
      // against a claim the node never made.
      //
      // The medians come from the link flush earlier in THIS pass (section [2]); if
      // that did not run, arm() refuses rather than predicting from a stale window.
      //
      // ⚠ BRANCH ON lastClose(), NOT ON `m`. Under run-length a still window that
      // matches the one before it writes 0 bytes and is completely normal — it is the
      // common case on a shelf. Disarming on `m == 0`, which is what this line used to
      // do, would silence Rule 1 for 29 windows out of every 30 and the loop would look
      // healthy while testifying to nothing. The window is still a real observation; it
      // is cited as (covering record, offset into its run) rather than by ordinal alone.
      const motionpercept::Close close = gMotionLog.lastClose();
      if (close == motionpercept::CLOSE_EMPTY) {
        gLearn.disarm();
      } else if (gMotionLog.lastWindow().moving) {
        gLearn.disarm();
      } else if (gLearn.arm(gMotionLog.coveringLane(), gMotionLog.runOffset())) {
        Serial.printf("[learn] expectation armed from @LAT95LON%d+%d (still): peers "
                      "hold within +/-%d dBm\n", gMotionLog.coveringLane(),
                      gMotionLog.runOffset(), PERCEPTLEARN_RSSI_BAND);
      }

      // The transition form (TTDB-RFC-0006 §5). The window above is a STATE; this is
      // the DIFFERENCE between it and the window before it, and per §5.2 the difference
      // is the datum — the thing a prediction could ever be wrong about. Written only
      // on a verdict change, so a node sitting still on a shelf writes none at all.
      // Must run before the next buildRecord(), which would overwrite the `after` half.
      if (gMotionLog.transitionPending()) {
        int tlane = laneCount(MOTIONPERCEPT_TRANSITION_LANE);
        if (tlane >= MOTIONPERCEPT_MAX_TRANSITION_LANE) {
          // Lane full. Say so out loud: silently dropping transitions would look
          // exactly like a node that never moved, which is the opposite claim.
          Serial.printf("[motion] transition DROPPED — @LAT%d lane full (%d)\n",
                        MOTIONPERCEPT_TRANSITION_LANE, tlane);
        } else {
          char trec[MOTIONPERCEPT_TRANSITION_BUF];
          size_t tm = gMotionLog.buildTransition(trec, sizeof(trec), tlane, kNodeId);
          if (tm && gDb.appendRecord(trec, tm))
            Serial.printf("[motion] %s -> %s TRANSITION -> @LAT%dLON%d (%uB, TTDB %uB)\n",
                          gMotionLog.pendingBefore().moving ? "moving" : "still",
                          gMotionLog.lastWindow().moving ? "moving" : "still",
                          MOTIONPERCEPT_TRANSITION_LANE, tlane, (unsigned)tm,
                          (unsigned)gDb.fileSize());
        }
      }
    }
  }
#endif

  sectMark();                       // [4] end of "imu": BMI270 + @LAT95 tier

#if USE_MIC && USE_CARD_HW
  serviceMic(now);
  if (gAcousticLog.due(now)) {
    int lane = laneCount(94);
    if (lane >= ACOUSTICPERCEPT_MAX_LANE) {
      gAcousticLog.reset(now);
    } else {
      char rec[400];
      size_t m = gAcousticLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                          gStamp, now, I2S_RATE);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[acoustic] percept window -> @LAT94LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

  sectMark();                       // [5] end of "mic": ES8311 read + @LAT94 tier

#if USE_CARD_HW
  // Tilt rolls the globe — this board has no trackball, and the IMU is a better
  // pointer anyway: tip the deck and the world turns. Dead-zoned so a hand at rest
  // holds the view still.
#if USE_IMU
  if (gImuOk && gGlobe && !gFaceOn) {       // in the resting face the tilt aims the gaze
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
  //   t = REPRESENTOR (eyeball) <-> globe views   n = next node (+ next comm target)
  //   s = get-status   p = ping   b = beep   SPACE = toggle the console pane
  //   g = play the song (whole band)   x = stop   o = onward a scene   r = restart
  //   +/= zoom in      -/_ zoom out
  char k = readKey();
  // In the representor the globe-navigation keys have nothing to steer. The fleet keys
  // (n/p/b/s/g/x/o/r) still work, so the face is never a dead end. ENTER is NOT filtered
  // here — §5 gives it the second job of cycling representor views, and the switch below
  // routes it to whichever is on screen.
  if (k && gFaceOn && (k == KEY_LEFT_C || k == KEY_RIGHT_C || k == KEY_UP_C ||
                       k == KEY_DOWN_C || k == '+' || k == '=' ||
                       k == '-' || k == '_')) k = 0;
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
      // ENTER cycles globes when the globes hold the screen, and representor views when
      // the representor does — one key, whichever stack you are actually looking at (§5).
      case KEY_ENTER_C:
        if (gFaceOn) setFaceView((FaceView)((gFaceView + 1) % FACE_VIEW_COUNT));
        else         toggleGlobeView();
        break;
      case 't': setFace(!gFaceOn); break;
      // §5's direct modality pins. With no arbiter yet these ARE the arbiter; when S1
      // lands they become the pin that overrides it, which is the same binding.
      // 1 and 2 mean whichever stack you are actually looking at — the same rule ENTER
      // already follows above. With the FACE up they are §5's direct modality pins; with
      // the GLOBES up there is no face to pin, and what the reader needs instead is a way
      // through a record body that does not fit in four lines. 3 stays the modality pin in
      // both stacks, so there is always one key that takes you back into the face.
      case '1':
        if (gFaceOn) { setFaceView(FACE_EYE); }
        else { gRecPage = (gRecPage + 1) % (gRecPages > 0 ? gRecPages : 1);
               gBottomDirty = gScreenDirty = true; }
        break;
      case '2':
        if (gFaceOn) { setFaceView(FACE_SCOPE); }
        else { gRecPage = (gRecPage + (gRecPages > 0 ? gRecPages : 1) - 1)
                          % (gRecPages > 0 ? gRecPages : 1);
               gBottomDirty = gScreenDirty = true; }
        break;
      case '3': setFaceView(FACE_INTERO); break;
      // 4 is the belief view. Like 3 it works from either stack, because it is the only
      // way to see the @LAT91 lane at all — the globes exclude it by the lat < 90 bound.
      case '4': setFaceView(FACE_BELIEF); break;
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
      // `n` inherits what `t` used to do — `t` now owns the face toggle (§5). SPACE
      // keeps the console pane, so nothing was lost in the move.
      case 'n':
        selectNextNode();
        if (gView == VIEW_FLEET) {
          gTargetIdx = (gTargetIdx + 1) % kNumTargets;
          gCmdTarget = kTargets[gTargetIdx];
        }
        gScreenDirty = true;
        break;
      case ' ':
        gPane = (gPane == PANE_MAIN) ? PANE_CONSOLE : PANE_MAIN;
        gBottomDirty = true;
        gScreenDirty = true;
        break;
      case 's': emitCmd(toot::CMD_GET_STATUS, nullptr, 0); break;
      default: break;                    // modifiers and unbound keys: ignored
    }
  }
#endif  // USE_CARD_HW
  sectMark();                       // [6] end of "nav": tilt/anim + keyboard

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
    // A DUET overrides the phrase, and sounds even while we hold the baton. The
    // conductor-silence guard is there so a self-appointed node that has not yet found the
    // band cannot play out of phase against it; that cannot happen in a duet, because a
    // conductor IS the phase reference and because the pair was asked for explicitly. With
    // only the two handhelds powered one of them necessarily conducts, so without this
    // exception the duet would always come out a solo.
    const score::Phrase* ph;
    bool voice;
    uint8_t speed = 1;
    if (duetOn()) {
      ph = (gDuetRole == toot::DUET_LEAD) ? &heroarc::kOdeLead : &heroarc::kOdeHarm;
      voice = true;
      speed = gDuetSpeed;             // already validated against this phrase by setDuet
    } else {
      ph = score::phraseForScene(kPart, gPulse.scene());
      voice = gLocalPlay && !gPulse.conductor();
    }
    // DOUBLE TIME is these two lines: wrap the phrase in `steps/speed` slots and look the note
    // up at `sip*speed`. The pulse clock and beat period are untouched — the pair covers the
    // written phrase in half the steps, so it plays twice as fast while staying locked to the
    // beat the rest of the fleet counts.
    // ONE stepTick per pass, whichever phrase is live — the call consumes the tick.
    const uint16_t steps = ph ? (uint16_t)(ph->steps / speed) : 16;
    uint16_t sip;
    uint32_t sc;
    static uint32_t prev_step = 0;
    static bool have_prev = false;
    if (gPulse.stepTick(now, steps, sip, sc)) {
      // Catch up over any steps this pass jumped so a stalled pass cannot swallow the note
      // that fell in the gap. Defensive: no dropped note has actually been observed at double
      // time (4.0 s/phrase, all 15 notes every cycle), but a duet's notes are 2 steps apart
      // and a percept flush runs 60-220 ms. See score::noteForCrossedSteps.
      const score::Note* nt = nullptr;
      if (ph)
        nt = (have_prev && sc > prev_step + 1)
                 ? score::noteForCrossedSteps(*ph, prev_step, sc, speed, steps)
                 : score::noteAt(*ph, (uint16_t)(sip * speed));
      prev_step = sc;
      have_prev = true;
      if (nt && voice && nt->freq != score::REST) {
        // Articulation scales with speed: staccato rather than a slur, and it halves the
        // blocking duty cycle of a tone call that would otherwise fill 72% of each note slot.
        uint32_t ms = PULSE_TONE_MS / speed;
        if (ms < 80) ms = 80;
#if USE_CARD_HW
        toneI2S((float)nt->freq, ms);
#endif
        Serial.printf("[part] step %2u/%u  %4uHz (%s x%u)\n", sip, steps, nt->freq,
                      duetOn() ? (gDuetRole == toot::DUET_LEAD ? "duet-lead" : "duet-harm")
                               : heroarc::sceneName(gPulse.scene()), speed);
      }
    }
  }
#endif

  sectMark();                       // [7] end of "pulse": band clock + our voice

  // The body's own senses (§4.5). Cheap and rare — four ADC reads and a die-temperature
  // read once per 2 s — but it gets its own profiler section rather than being folded
  // into a neighbour's, because a section that quietly carries somebody else's cost is
  // how a profiler starts lying (companion.md §6: instrument the mechanism).
  serviceIntero(now);

  sectMark();                       // [8] end of "intero": battery + die temp + heap

  // Periodic HELLO beacon — now also the carrier for the time-stream anchor. The
  // anchor is sampled HERE rather than reused from gStamp so `stream_ms` is the value
  // at transmit: a receiver adopts (stream_ms - its recv millis), and any staleness in
  // the number lands directly in its clock as an error.
  static uint32_t lastBeacon = 0;
  if (now - lastBeacon >= 2000) {
    lastBeacon = now;
    uint8_t body[timestream::ANCHOR_LEN];
    size_t bn = gTs.helloPayload(body, sizeof(body), millis());
    emit(toot::HELLO, bn ? body : nullptr, bn, sendEspNow, nullptr);
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
  if (gFaceOn) {
    // Each representor view owns its own frame clock, and both are far cheaper than the
    // 1 Hz feelings-globe repaint they replaced. The eye runs on the BEAT while it is
    // held still and on a fast free clock while it is moved (§4.1); the scope runs at a
    // flat 10 Hz because the room it is reporting on does not know the tempo.
    bool due = false;
    switch (gFaceView) {
#if USE_MIC && USE_CARD_HW
      case FACE_SCOPE:  due = scopeFrameDue(now);  break;
#endif
      case FACE_INTERO: due = interoFrameDue(now); break;
      // Beliefs move only when the Dream Cycle rewrites the lane, so this one is
      // change-driven rather than clocked — it asks for a frame and then goes quiet.
      case FACE_BELIEF: due = beliefFrameDue(now); break;
      default:          due = eyeFrameDue(now);    break;
    }
    if (due) {
      uint32_t r0 = millis();
#if USE_MIC && USE_CARD_HW
      if (gFaceView == FACE_SCOPE)       renderScope(now);
      else if (gFaceView == FACE_INTERO) renderIntero(now);
      else if (gFaceView == FACE_BELIEF) renderBelief(now);
      else                               renderEye(now);
#else
      if (gFaceView == FACE_INTERO)      renderIntero(now);
      else if (gFaceView == FACE_BELIEF) renderBelief(now);
      else                               renderEye(now);
#endif
      gLastRenderMs = gPassRenderMs = millis() - r0;
      if (gLastRenderMs > gWorstRenderMs) gWorstRenderMs = gLastRenderMs;
      gRenderCount++;
    }
  } else if (gScreenDirty || gGlobeDirty || now - lastRender >= 1000) {
    lastRender = now;
    gScreenDirty = false;
    // Band members carry live status on the feelings globe, so repaint on the 1 Hz
    // heartbeat to age it even without a navigation change.
    if (gView == VIEW_FEELINGS) gGlobeDirty = true;
    uint32_t r0 = millis();
    renderScreen();
    gLastRenderMs = gPassRenderMs = millis() - r0;
    if (gLastRenderMs > gWorstRenderMs) gWorstRenderMs = gLastRenderMs;
  }
#endif

  // Loop-latency profile. The toot link is serviced once per pass, so the SLOWEST pass
  // is the node's worst-case response time — which is exactly what `verify`/`band`
  // measure as rtt. Printed rarely, and only the extremes, so it costs nothing to
  // leave on: when a future change makes this node sluggish on the mesh, the number
  // that explains it is already on the wire.
  {
    sectMark();                     // [9] end of "render": the screen
    static uint32_t loopStart = 0, worst = 0, worstOwnRender = 0, lastReport = 0;
    static uint32_t worstSect = 0;
    static const char* worstSectName = "-";
    // Measured from gSectMark[0] — the stamp taken at the TOP of THIS pass — not from a
    // stamp left at the end of the previous one. ⚠ The old form was
    // `static loopStart = 0; if (loopStart) { d = millis() - loopStart; ... }`, which
    // skipped the FIRST pass entirely (it had no previous stamp to subtract). That is
    // precisely the pass that does the one-time boot work: the first Dream Cycle runs
    // there (`last_dream == 0`) and cost a measured 1089 ms, while the profiler covering
    // that window serenely reported `worst pass 18ms`. A profiler blind to the most
    // expensive pass in the run is worse than no profiler.
    {
      uint32_t d = millis() - gSectMark[0];
      // Carry the render cost OF THAT PASS along with it. "Worst pass 53 ms, worst
      // render 24 ms" is ambiguous — they may be different passes — and the whole
      // point of this profiler is to stop us guessing which.
      if (d > worst) {
        worst = d;
        // Published so the node can SEE its own response time (§4.5 footer). This is the
        // number the mesh feels as rtt, and the interoception view is the right place
        // for a body to notice it has become slow.
        gWorstLoopMs = worst;
        worstOwnRender = gPassRenderMs;
        worstSect = 0;
        worstSectName = "-";
        for (int i = 0; i + 1 < gSectN; ++i) {
          uint32_t s = gSectMark[i + 1] - gSectMark[i];
          if (s > worstSect) { worstSect = s; worstSectName = kSectionNames[i]; }
        }
      }
    }
    gPassRenderMs = 0;
    loopStart = millis();
    if (loopStart - lastReport >= 30000) {
      lastReport = loopStart;
      // `frames` is how many times the face actually drew in the window. It is here
      // because the eye's whole design rests on a claim that is otherwise invisible from
      // the laptop: held still it should draw only in the beat pulse (~8/s), and moved it
      // should track (~25/s). A resting node quietly burning 25 fps would look identical
      // on every other number in this line.
      Serial.printf("[loop] worst pass %lums (render %lums, widest section %s %lums) "
                    "| worst render %lums | frames %lu | maxalloc %luK\n",
                    (unsigned long)worst, (unsigned long)worstOwnRender,
                    worstSectName, (unsigned long)worstSect,
                    (unsigned long)gWorstRenderMs, (unsigned long)gRenderCount,
                    (unsigned long)(ESP.getMaxAllocHeap() / 1024));
      gRenderCount = 0;
      worst = 0;
      gWorstLoopMs = 0;              // per-window, like every other number on that line
      worstOwnRender = 0;
      worstSect = 0;
      worstSectName = "-";
      gWorstRenderMs = 0;
    }
  }
}
