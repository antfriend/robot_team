// tdeck_console.ino — LilyGo T-Deck, HANDHELD CONSOLE / field operator (A32 agent).
//
// Role: a mobile mini-orchestrator carried in-hand. The BlackBerry keyboard injects
// CMD toots and the 320x240 color screen shows the fleet, so an operator can drive
// and observe the swarm without the laptop. It is a full ESP-NOW Dream-Cycle
// participant like V4-B (pull, HMAC, dedup, want_ack ACK, TIME_SYNC adopt + @LAT99
// log, belief TTDB_PUT adopt + @LAT98 attestation, STATUS telemetry, PULSE), plus a
// console UI. The T-Deck also carries an SX1262, so it can join the LoRa spine later
// (USE_LORA) — the only handheld node that bridges color-screen+keyboard and LoRa.
//
// Built from the verified siblings (V4-B's network floor + the K10's mesh
// discipline): serve a TTDB burst from loop() (never the recv callback), pace ESP-NOW
// sends behind the TX-complete callback, dedup radio-only, re-ACK a dropped want_ack
// replay (TTN-RFC-0007 §5), and defer every flash write out of the WiFi task.
//
// Build/deploy with arduino-cli (see firmware/README.md), FQBN
// esp32:esp32:esp32s3:CDCOnBoot=cdc (native USB, like the V4/K10). TTDB in
// data/ttdb.md flashed to LittleFS separately (scripts/Upload-V4-FS.ps1 -Node
// tdeck_console — same esp32-core default 4 MB spiffs partition as the V4).
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
#include <Pulse.h>    // band tempo (PULSE_DEFAULT_BEAT_MS) lives in Pulse.h — 120 BPM
#include <Score.h>
#include <LinkPercept.h>  // SP0: every authenticated reception becomes a percept
#include <BleLink.h>      // SP0 near-range tier: BLE advert+scan -> PROTO_BLE percepts
#include <EntityPercept.h>  // SP0 entity tier: WiFi BSSID sightings -> @LAT96 percepts
#include <Nmea.h>         // SP2: portable NMEA GGA decode for the roaming GPS anchor
#include <RobotTeamConfig.h>
#include <Preferences.h>   // NVS: remember the song on/off across a power-cycle

// --- link percepts (semantic positioning SP0, ttn-semantic-positioning.md) ---
// Per-peer RSSI histograms fed from the ESP-NOW recv callback; flushed from
// loop() as one @LAT97 TTDB record per window (see LinkPercept.h). The roaming
// console is the fleet's moving measuring instrument (and, with its GPS, the
// SP2 ground-truth anchor).
static linkpercept::Log gLinkLog;

// Real T-Deck peripherals (ST7789 LCD + I2S speaker + I2C keyboard). Set to 0 to
// build/verify the network floor headless (byte-exact pull, HMAC reject, sync/belief)
// with a serial mock — exactly how the K10/V4 were first brought up (USE_K10_HW). At 1
// the console drives the color screen, sounds a "toot toot" on boot, and reads the
// keyboard. The floor works either way.
#define USE_TDECK_HW 1
#define USE_LORA 0        // Phase 4: the T-Deck's SX1262 can join the LoRa spine.
#define USE_PULSE 1       // follow the band clock so `band`/`monitor` see this node.
#define USE_GPS 1         // SP2: T-Deck Plus GPS as the roaming ground-truth anchor.
                          // Safe on a non-Plus unit (the UART just stays silent ->
                          // CMD_GET_GPS answers quality:0). Independent of USE_TDECK_HW.
#define USE_BLE 1         // SP0 near-range tier: advertise+scan over BLE (proto:ble).

// Feed a decoded, key-verified BLE fleet advert into the same link-percept histogram as
// ESP-NOW, tagged PROTO_BLE (runs in the BLE scan task — add() is increment-only/safe).
#if USE_BLE
static void onBleObserve(uint32_t peer, int rssi) {
  gLinkLog.add(peer, rssi, linkpercept::PROTO_BLE);
}
#endif

// SP0 entity tier: duty-cycled WiFi scan logging visible BSSIDs (@LAT96 lane). The
// roaming console is the fleet's MOVING observer, so its shifting AP set is an
// especially rich co-occurrence signal (it logs whichever room it is in). The ~2 s
// async scan hops channels, so it's kept rare and the ESP-NOW channel is re-asserted
// after; battery cost is one short scan / 10 min. Default off until serial-verified.
#define USE_WIFI_SCAN 1
#define WIFI_SCAN_PERIOD_MS 600000UL   // one ~2 s scan every 10 min

#if USE_WIFI_SCAN
static entitypercept::Log gEntityLog;
static uint32_t gLastScanKick = 0;
static bool gScanRunning = false;

// Non-blocking duty-cycled WiFi scan (see v4a_bridge.ino for the rationale). Coexists
// with BLE on the 3.x core the same way V4-A does (radio arbiter time-slices them).
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

// --- T-Deck board pin map (LilyGo T-Deck / T-Deck Plus) ---------------------
// Documented here (and in hardware_specs.md) even when USE_TDECK_HW is 0 so the
// board is ready to bring up. The display, LoRa and SD share ONE SPI bus.
static const int PIN_POWERON   = 10;  // board peripheral-power enable: MUST be HIGH
static const int PIN_SPI_SCLK  = 40;  // shared SPI clock (LCD + LoRa + SD)
static const int PIN_SPI_MOSI  = 41;
static const int PIN_SPI_MISO  = 38;
static const int PIN_TFT_CS    = 12;  // ST7789 320x240
static const int PIN_TFT_DC    = 11;
static const int PIN_TFT_BL    = 42;  // backlight (active HIGH)
static const int PIN_KBD_SDA   = 18;  // BlackBerry keyboard (own MCU) over I2C
static const int PIN_KBD_SCL   = 8;
static const uint8_t KBD_ADDR  = 0x55;  // reads one byte = ASCII of the pressed key
static const int PIN_TB_CLICK  = 0;   // trackball click (also BOOT)
static const int PIN_TB_UP     = 3;   // trackball roll: pulses a GPIO per direction
static const int PIN_TB_DN     = 15;
static const int PIN_TB_L      = 1;
static const int PIN_TB_R      = 2;
static const int PIN_LORA_CS   = 9;   // SX1262 (shared SPI): BUSY13 RST17 DIO1 45
static const int PIN_I2S_BCLK  = 7;   // MAX98357A speaker amp (I2S)
static const int PIN_I2S_WS    = 5;   // word select / LRCLK
static const int PIN_I2S_DOUT  = 6;   // data to amp
// T-Deck Plus GPS (u-blox MIA-M10Q) on UART1. GPIO43/44 are the S3's default UART0
// TXD0/RXD0, freed because the board runs native USB CDC — LilyGo wires the GPS there.
static const int PIN_GPS_RX    = 44;  // ESP32 RX  <- GPS module TX (NMEA in)
static const int PIN_GPS_TX    = 43;  // ESP32 TX  -> GPS module RX (config; unused here)

#if USE_TDECK_HW
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <ESP_I2S.h>
// The T-Deck LCD is an ST7789 on the shared SPI bus. We drive it with Adafruit_ST7789
// (pins passed at RUNTIME in the constructor / SPI.begin) rather than TFT_eSPI, whose
// pin map is compile-time in a single sketchbook User_Setup.h — which is already pinned
// to the K10's ILI9341 map (CLAUDE.md). Runtime pins sidestep that clash entirely, so
// the K10 and T-Deck never fight over one setup file.
static SPIClass gDispSpi(HSPI);
static Adafruit_ST7789 gTft(&gDispSpi, PIN_TFT_CS, PIN_TFT_DC, /*rst=*/-1);
// Speaker is a MAX98357A I2S amp (no analog/PWM path like the K10's Music lib), so a
// tone is synthesized as 16-bit I2S samples (see toneI2S).
static I2SClass gI2S;
// 8 kHz to match the V4 band voice (they run 8k; see companion.md §6). The T-Deck's
// integrated MAX98357A is happy at any rate, but matching keeps the square timbre identical.
static const uint32_t I2S_RATE = 8000;
#endif

// --- GPS: the roaming ground-truth anchor (semantic positioning SP2) ---------
// The T-Deck Plus carries a u-blox GPS on UART1. It is the fleet's VERIFIER and
// second anchor: a GPS fix taken beside a static node pins the emergent relative map
// to absolute coordinates and resolves its mirror (ttn-semantic-positioning.md §3
// Phase 2). GPS is never fed into the inference — it only scores + anchors it. The
// fix is parsed continuously; the laptop reads it on demand with CMD_GET_GPS.
#if USE_GPS
static HardwareSerial gGpsSerial(1);
static nmea::Parser gGps;
static uint32_t gGpsFixMs = 0;          // millis() of the last GGA that carried a fix
// u-blox default is 38400; older modules ship at 9600. Probe a short list at boot and
// lock the first baud that speaks NMEA — bring-up shouldn't hinge on knowing the rate.
static const uint32_t kGpsBauds[] = {38400, 9600, 115200, 57600};
static uint32_t gGpsBaud = 0;

static void gpsProbeBaud() {
  for (unsigned bi = 0; bi < sizeof(kGpsBauds) / sizeof(kGpsBauds[0]); ++bi) {
    gGpsSerial.begin(kGpsBauds[bi], SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);
    delay(40);
    while (gGpsSerial.available()) gGpsSerial.read();   // flush partial line
    int dollars = 0;
    uint32_t t0 = millis();
    while (millis() - t0 < 900 && dollars < 3) {        // '$' framing = right baud
      while (gGpsSerial.available())
        if ((char)gGpsSerial.read() == '$') ++dollars;
      delay(2);
    }
    if (dollars >= 3) { gGpsBaud = kGpsBauds[bi]; return; }
    gGpsSerial.end();
  }
  gGpsBaud = kGpsBauds[0];   // nothing heard (cold module / no antenna): default + wait
  gGpsSerial.begin(gGpsBaud, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);
}

// Drain the UART into the parser; timestamp each live fix. Cheap, called every loop().
static void gpsPoll() {
  int guard = 0;
  while (gGpsSerial.available() && guard++ < 512)
    if (gGps.feed((char)gGpsSerial.read()) && gGps.fix().hasFix())
      gGpsFixMs = millis();
}
#endif  // USE_GPS

static const uint32_t kNodeId = NODE_TDECK_1;
static const char* kTtdbPath = "/ttdb.md";
static const char* kBeliefPath = "/belief.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

// Which node the keyboard drives. Cycled with the 't' key. Default K10: it plays the
// Ode-to-Joy lead, so `g`/`x` on it (plus the T-Deck's own harmony) is the duet. Both
// the K10 and V4-B answer a get-status over the air (the V4-A bridge does not — it only
// answers CMDs from the laptop over USB).
static const uint32_t kTargets[] = {NODE_K10_1, NODE_V4B_RELAY, NODE_V4A_BRIDGE};
static const int kNumTargets = sizeof(kTargets) / sizeof(kTargets[0]);
static int gTargetIdx = 0;
static uint32_t gCmdTarget = NODE_K10_1;

// The T-Deck's own musical part (part 2): a harmony a diatonic third below the K10's
// Ode-to-Joy lead, on the shared pulse step grid. `g`/`x` (or a received CMD_PLAY/STOP)
// toggle it, so one `g` starts both voices at once. The on/off state is persisted in NVS
// (setLocalPlay), so a power-cycle RESUMES the part — the T-Deck rejoins the song once it
// re-locks to the band (played only as an in-phase follower; see the harmony gate below).
static Preferences gPrefs;
static bool gLocalPlay = false;
static void setLocalPlay(bool on) {
  gLocalPlay = on;
  gPrefs.putBool("play", on);     // survive a reboot (screen refreshes within 1 s)
}
static const uint32_t PULSE_HARM_TONE_MS = 180;   // staccato note (blocks; keep short)
static const score::Note kHarmNotes[] = {
  {0,  score::C4, 4}, {4,  score::C4, 4}, {8,  score::D4, 4}, {12, score::E4, 4},
  {16, score::E4, 4}, {20, score::D4, 4}, {24, score::C4, 4}, {28, score::B3, 4},
  {32, score::A3, 4}, {36, score::A3, 4}, {40, score::B3, 4}, {44, score::C4, 4},
  {48, score::C4, 6}, {54, score::B3, 2}, {56, score::B3, 8},
};
static const score::Phrase kHarm = {
    kHarmNotes, sizeof(kHarmNotes) / sizeof(kHarmNotes[0]), 64};

// Friendly short name for a node id (for the screen).
static const char* nodeName(uint32_t id) {
  switch (id) {
    case NODE_V4A_BRIDGE: return "V4-A";
    case NODE_V4B_RELAY:  return "V4-B";
    case NODE_V4C_EDGE:   return "V4-C";
    case NODE_K10_1:      return "K10";
    case NODE_TDECK_1:    return "T-Deck";
    case NODE_BROADCAST:  return "ALL";
    default:              return "?";
  }
}

Ttdb gDb;                 // fleet globe — the network-facing TTDB (shared/synced/attested)
Ttdb gRfcDb;              // RFC corpus globe — view-only (never shared over the mesh)
static const char* kRfcTtdbPath = "/rfc.ttdb.md";
static bool gRfcLoaded = false;
TtdbShare* gShare = nullptr;

// Globe views the trackball click cycles through. VIEW_FLEET (Semantic Position) is the
// fleet TTDB; VIEW_RFC is the read-only RFC corpus. Only the fleet TTDB touches the mesh
// — TTDB_REQ / @LAT99 sync / @LAT98 belief always operate on gDb, never gViewDb.
enum GlobeView { VIEW_FLEET = 0, VIEW_RFC, VIEW_COUNT };
static int   gView = VIEW_FLEET;
static Ttdb* gViewDb = &gDb;                  // active globe for render + navigation
static int   gViewSel[VIEW_COUNT] = {-1, -1}; // remembered selection per view
static inline const char* viewName(int v) { return v == VIEW_RFC ? "RFC" : "SemPos"; }
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);
static uint32_t gSeq = 1;

// Console state rendered on the screen (updated from loop() + the recv callback;
// the callback only flips gScreenDirty — no SPI/I2C from the WiFi task).
static uint32_t gEspRx = 0;      // frames decoded off ESP-NOW
static uint32_t gServed = 0;     // TTDB_REQ replies served
static uint32_t gCmdSent = 0;    // CMD toots injected from the keyboard
static uint32_t gReplies = 0;    // STATUS/PERCEPT replies collected
static uint32_t gLastReplySrc = 0;   // src of the last STATUS/PERCEPT reply
static int16_t  gLastReplyTemp = 0;  // last reply temp*100 (fleet view)
static char     gLastKey = 0;        // last key pressed on the console keyboard
static volatile bool gScreenDirty = true;

// --- SP6-T console UI: panes + event log ------------------------------------
// The screen is a TTCP mini-render (PLAN.md SP6-T): a trackball-navigable globe
// (top half) + the selected record (bottom half); a keyboard toggle slides a
// console log over the bottom half (the non-touch analog of the reference site's
// swipe-up console). Globe/trackball live behind USE_TDECK_HW; this state is cheap
// and unguarded so handleToot() can log events regardless.
enum Pane { PANE_MAIN, PANE_CONSOLE };
static Pane gPane = PANE_MAIN;
static bool gPaneChanged = true;     // force a full bottom-half repaint on switch

#define LOG_LINES 11                 // console ring: last N events (fits the bottom half)
static char gLog[LOG_LINES][40];
static int  gLogHead = 0, gLogCount = 0;
// Push one line into the console ring (and mirror to Serial). Safe from loop() only
// (it touches gScreenDirty + the ring); the recv callback stashes, loop() logs.
static void logLine(const char* s) {
  strncpy(gLog[gLogHead], s, 39);
  gLog[gLogHead][39] = 0;
  gLogHead = (gLogHead + 1) % LOG_LINES;
  if (gLogCount < LOG_LINES) gLogCount++;
  gScreenDirty = true;
}

// Globe selection: index of the selected TTDB record (the one shown in the record
// view). -1 until the first record is seated in setup(). Shared with the globe.
static int gSel = -1;

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
// Store + attest exactly like V4-B (no agent cadence to retune, so no DIRECTIVE
// action). Exactly-once on a monotonic belief_id.
static bool gBeliefAdopted = false;
static uint32_t gBeliefId = 0;
static bool gPutActive = false;
static uint32_t gPutId = 0, gPutTotal = 0, gPutCrc = 0, gPutNext = 0, gPutCrcRun = 0;
static volatile bool gBeliefSyncPending = false;
static uint32_t gPendBeliefId = 0, gPendBeliefBytes = 0, gPendBeliefCrc = 0;
static uint32_t gPendBeliefRecvMs = 0;

// Write one TTDB_PUT slice into /belief.md; on completion CRC-verify and schedule the
// adoption attestation. Idempotent on retransmit (laptop streams strictly in offset
// order, stop-and-wait). Runs in loop() so the flash write never blocks the WiFi task.
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

  if (gPutActive && bid == gPutId && gPutNext >= gPutTotal) {  // last slice
    gPutActive = false;
    if (gPutCrcRun == gPutCrc) {
      gBeliefAdopted = true; gBeliefId = bid;     // commit (exactly-once gate)
      gPendBeliefId = bid; gPendBeliefBytes = gPutTotal; gPendBeliefCrc = gPutCrc;
      gPendBeliefRecvMs = millis();
      gBeliefSyncPending = true;                  // attest to live TTDB from loop()
    } else {
      Serial.printf("[belief] id=%lu CRC MISMATCH got %08lX want %08lX (%luB)\n",
                    (unsigned long)bid, (unsigned long)gPutCrcRun,
                    (unsigned long)gPutCrc, (unsigned long)gPutTotal);
    }
  }
  return true;
}

// --- fleet pulse (TTN-RFC-0010) ---------------------------------------------
// The console is a silent band FOLLOWER: it adopts the shared chart, relays a beacon
// when due (so it helps the band converge), and shows the beat on-screen — but sounds
// no part. Lowest live id conducts, so it never takes the baton unless alone.
#if USE_PULSE
static pulse::Engine gPulse;
static uint32_t gNeighbors[8] = {0};
static int      gNeighborCount = 0;
static bool neighborIsNew(uint32_t src) {
  for (int i = 0; i < gNeighborCount; ++i)
    if (gNeighbors[i] == src) return false;
  if (gNeighborCount < (int)(sizeof(gNeighbors) / sizeof(gNeighbors[0])))
    gNeighbors[gNeighborCount++] = src;
  return true;
}
#endif

// --- transports -------------------------------------------------------------
// ESP-NOW TX is async with a shallow queue; a TTDB burst overruns it and drops all
// but the first frames. Gate each send on the prior frame's TX-complete callback so
// the whole stream survives the air (the K10's Phase-1b lesson).
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

// TTN-RFC-0007: ACK `orig` on `reply` — for a freshly-accepted want_ack toot and for
// re-ACKing a dedup-dropped replay (§5).
static void emitAck(const toot::Toot& orig, uint8_t status,
                    TtdbShare::SendFn reply, void* ctx) {
  toot::Toot ack;
  toot::makeAck(orig, kNodeId, gSeq++, status, ack);
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(ack, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) reply(frame, flen, ctx);
}

// Inject a CMD toot at gCmdTarget over ESP-NOW — the console's operator function. op
// is a CmdOp (Toot.h); the CMD payload is op | target(4) | args. Fire-and-forget
// (not want_ack): CMD_GET_STATUS is answered by the target's STATUS PERCEPT, which we
// collect for the fleet view; CMD_PING/CMD_BEEP just act.
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
// Targeted CMD at the selected node (get-status / beep / set-led / ping).
static void emitCmd(uint8_t op, const uint8_t* args, uint8_t argn) {
  emitCmdTo(op, gCmdTarget, args, argn);
}

// Build a GPS PERCEPT payload (Toot.h GPS_PERCEPT_PAYLOAD_LEN) from the last fix — the
// answer to CMD_GET_GPS (SP2). No flash/blocking, so it is safe from the recv path.
// Without a GPS (or before a lock) it honestly reports quality:0.
static uint8_t buildGps(uint8_t* p) {
#if USE_GPS
  const nmea::Fix& f = gGps.fix();
  toot::put_u32(p + 0, (uint32_t)f.lat_1e7);
  toot::put_u32(p + 4, (uint32_t)f.lon_1e7);
  toot::put_u32(p + 8, (uint32_t)f.alt_cm);
  p[12] = f.quality;
  p[13] = f.sats;
  toot::put_u16(p + 14, f.hdop_x10);
#else
  memset(p, 0, 16);
#endif
  toot::put_u64(p + 16, gSynced ? (uint64_t)nowEpochMs() : 0);
  return (uint8_t)toot::GPS_PERCEPT_PAYLOAD_LEN;
}

// STATUS telemetry for the `monitor` table. The console has no sensor cursor/temp, so
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
  toot::put_u16(p + 43, ch.scene_id);   // v2 tail: what the band is playing
  return (uint8_t)toot::STATUS_PULSE_PAYLOAD_LEN;
#else
  return (uint8_t)toot::STATUS_PAYLOAD_LEN;
#endif
}

// Serve a TTDB_REQ addressed to this node: belief mode streams the stored /belief.md
// (TTN-RFC-0009 §3 readback); any other mode streams the live TTDB. Both stream a
// burst, so radio callers must invoke this from loop() (see the deferral).
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

// Dispatch a decoded, authenticated toot on any transport. `reply` is the transport
// to answer on. Dedup is radio-only (applied in onEspNowRecv before this), so the
// trusted USB link stays un-deduped and the laptop can retry.
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
  bool accepted = false;
  switch (t.type) {
    case toot::TTDB_REQ:
      serveTtdbReq(t, reply, ctx);   // the streamed reply is itself the confirmation
      break;
    case toot::TTDB_PUT:
      accepted = handlePutSlice(t);  // belief slice; ACK each
      break;
    case toot::CMD:
      // Move the band to a scene of the song. The chart belongs to the CONDUCTOR, so
      // only the conductor applies + ACKs this. The console is a follower by design
      // (highest id), so this normally declines and it learns the scene from the next
      // beacon — which is also why broadcasting the command is safe.
      if (toot::cmdOp(t) == toot::CMD_SET_SCENE &&
          (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
#if USE_PULSE
        if (gPulse.conductor() && t.payload_len >= 7) {
          uint16_t want = toot::get_u16(t.payload + 5);
          gPulse.setScene(want, millis());
          accepted = (gPulse.scene() == want);  // ACK the achieved state (idempotent)
        }
#endif
        break;
      }
      if (toot::cmdTarget(t) == kNodeId) {
        bool ok = true;
        switch (toot::cmdOp(t)) {
          case toot::CMD_GET_STATUS: {
            uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
            uint8_t slen = buildStatus(body);
            emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
            break;
          }
          case toot::CMD_GET_GPS: {
            uint8_t body[toot::GPS_PERCEPT_PAYLOAD_LEN];
            uint8_t glen = buildGps(body);
            emit(toot::PERCEPT, body, glen, reply, ctx);  // GPS PERCEPT is the answer
            break;
          }
          case toot::CMD_PLAY: setLocalPlay(true);  break;  // start our harmony part
          case toot::CMD_STOP: setLocalPlay(false); break;
          case toot::CMD_CLEAR_PERCEPTS:
            // Flash rewrite: reaches here only from loop() (radio path defers).
            // ACK only on success, so a failed prune is loud (laptop retries).
            ok = gDb.removeLane(97);
            if (ok)
              Serial.printf("[link] @LAT97 lane cleared (TTDB now %uB, %dr)\n",
                            (unsigned)gDb.fileSize(), gDb.recordCount());
            break;
          default: break;                                   // ping / set-* (no-op here)
        }
        accepted = ok;
        gScreenDirty = true;
      }
      break;
    case toot::PERCEPT: {
      // A collected reply from a node the console queried: stash it for the fleet
      // view (temp is field 4, temp*100 — see buildStatus on the leaf nodes).
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
      if (neighborIsNew(t.src_node_id)) gPulse.noteNeighbor(millis());
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
  // SP0 link percept: an authenticated frame is a distance measurement in
  // disguise. Logged BEFORE dedup — a retried duplicate is a real reception.
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
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }   // defer burst to loop()
    return;
  }
  if (t.type == toot::TTDB_PUT) {
    if (!gPutPending) { gPendingPut = t; gPutPending = true; }   // defer flash to loop()
    return;
  }
  if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
      toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
    if (!gClearPending) { gPendingClear = t; gClearPending = true; }  // flash: loop()
    return;
  }
  handleToot(t, sendEspNow, nullptr);       // cheap toots (TIME_*, CMD, PERCEPT, PULSE)
}

// Append an @LAT99 sync-log record (deferred from the recv path). n = count of
// existing lat-99 records so each is unique under collision_policy: reject.
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

// --- console UI + audio (gated) ---------------------------------------------
#if USE_TDECK_HW
// Synthesize a `ms`-long SQUARE wave at `freq` as 16-bit stereo samples (L=R; the MAX98357A
// is mono but takes stereo frames). Square, not sine, to match the V4 band voice (their hand-
// wired amps only reproduce squares; the T-Deck's clean amp does either, so we match on purpose
// for one unified timbre). Blocks ~ms, so it runs from setup()/loop() only — never a callback.
// amp 22000 (not the V4s' 11000): the T-Deck's integrated amp/speaker is ~half as loud as the
// V4 hand-wired rigs at the same level, so it runs 2x hotter to match the band's perceived volume.
static void toneI2S(float freq, uint32_t ms, float amp = 22000.0f) {
  const int N = 256;                          // samples per write chunk
  int16_t buf[N * 2];                         // interleaved L,R
  uint32_t total = (uint32_t)((uint64_t)I2S_RATE * ms / 1000);
  float phase = 0.0f, inc = 2.0f * (float)M_PI * freq / (float)I2S_RATE;
  uint32_t done = 0;
  while (done < total) {
    uint32_t n = total - done; if (n > (uint32_t)N) n = N;
    for (uint32_t i = 0; i < n; ++i) {
      int16_t s = (phase < (float)M_PI) ? (int16_t)amp : (int16_t)-amp;  // 50% square
      phase += inc; if (phase > 2.0f * (float)M_PI) phase -= 2.0f * (float)M_PI;
      buf[2 * i] = s; buf[2 * i + 1] = s;
    }
    gI2S.write((uint8_t*)buf, n * 2 * sizeof(int16_t));
    done += n;
  }
}

// The Toot-Toot signature on boot — two rising toots, C4 -> G4 (a rising fifth), matching the
// V4 fleet's toot so the whole band shares one boot voice.
// Boot toot plays at 25% of fleet loudness (75% quieter); the harmony melody keeps full amp.
static const float STARTUP_TOOT_AMP = 5500.0f;   // 22000 / 4
static void playStartupToot() {
  toneI2S(262.0f, 220, STARTUP_TOOT_AMP);   // toot  (C4)
  delay(40);
  toneI2S(392.0f, 380, STARTUP_TOOT_AMP);   // toot  (G4)
}

// Read one keycode from the BlackBerry keyboard (its own MCU answers on I2C 0x55; a
// read of 0 means no key). Returns 0 if nothing pending.
static char readKey() {
  if (Wire.requestFrom((int)KBD_ADDR, 1) != 1) return 0;
  int c = Wire.read();
  return (c > 0) ? (char)c : 0;
}

// Draw one full-width padded row (opaque bg) at text size 1 — 52 chars ~= 312px, so
// a re-print erases the whole line and never leaves trailing glyphs.
static void drawWide(int y, uint16_t color, const char* s) {
  char pad[54];
  snprintf(pad, sizeof(pad), "%-52s", s);
  pad[52] = 0;
  gTft.setTextColor(color, ST77XX_BLACK);
  gTft.setTextSize(1);
  gTft.setCursor(4, y);
  gTft.print(pad);
}

// --- SP6-T screen geometry (320x240, rotation 3) ----------------------------
static const int STATUS_Y  = 2;     // thin identity/target bar
static const int GLOBE_X   = 0,  GLOBE_Y = 14;
static const int GLOBE_W   = 320, GLOBE_H = 116;   // top half: the globe
static const int BOTTOM_Y  = 132;                  // record view / console pane
static const int BOTTOM_H  = 240 - BOTTOM_Y;

// The globe is drawn into an off-screen 16-bit canvas and block-pushed, so rotation
// is flicker-free (the K10 canvas-blink lesson). 320x116x2 = ~74KB — allocated once
// at setup (PSRAM when PSRAM=opi is in the FQBN; see PLAN.md SP6-T). If the alloc
// fails, gGlobe stays null and renderScreen falls back to a text top bar.
static GFXcanvas16* gGlobe = nullptr;
static float gRotLat = 0.0f, gRotLon = 0.0f;   // current globe rotation
static float gTgtLat = 0.0f, gTgtLon = 0.0f;   // selection-animation target
static bool  gAnim = false;                    // easing rotation toward a selection
// 3 zoom levels (TTCP-RFC-0002 §2.3): level 0 = the whole globe (furthest, the
// original view), level 2 = front face filling the screen (closest; diameter
// 54*2.85*2 = 308 px < 320, so never wider than the screen). Default = middle.
static const float kZoomLevels[3] = {1.15f, 2.0f, 2.85f};
static int   gZoomIdx = 1;
static float gZoom = kZoomLevels[1];
static bool  gGlobeDirty = true;               // repaint the globe canvas
static bool  gBottomDirty = true;              // repaint the bottom half

// --- trackball: the only pointer (non-touch panel) --------------------------
// The 5-way trackball pulses four GPIOs as it rolls and grounds one on click. We
// count falling edges per direction in ISRs; loop() converts the accumulated counts
// into globe rotation (roll) and a select action (click). GPIO0 is also BOOT — safe
// to read/interrupt after boot.
static volatile uint16_t gTbUp = 0, gTbDn = 0, gTbL = 0, gTbR = 0;
static volatile bool gTbClick = false;
static void IRAM_ATTR isrTbUp()   { gTbUp++; }
static void IRAM_ATTR isrTbDn()   { gTbDn++; }
static void IRAM_ATTR isrTbL()    { gTbL++; }
static void IRAM_ATTR isrTbR()    { gTbR++; }
static void IRAM_ATTR isrTbClick(){ gTbClick = true; }

static inline uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}
// Deterministic per-record color (TTCP-RFC-0002 §3.3, hash of the record id).
static uint16_t nodeColor(int16_t lat, int16_t lon) {
  uint32_t h = (uint32_t)(lat * 73856093) ^ (uint32_t)(lon * 19349663);
  return rgb565(90 + (h & 0x7F), 90 + ((h >> 7) & 0x7F), 90 + ((h >> 14) & 0x7F));
}

// Project a record's @LAT/LON (degrees, TTCP-RFC-0002 §2.1) through the current globe
// rotation to screen space. z>0 means the point faces the camera (front-face cull).
static void projectLL(float latDeg, float lonDeg, float R, int cx, int cy,
                      float sLat, float cLat, float sLon, float cLon,
                      int& sx, int& sy, float& z) {
  const float D2R = 0.01745329f;
  float la = latDeg * D2R, lo = lonDeg * D2R;
  float x = cosf(la) * sinf(lo), y = sinf(la), zz = cosf(la) * cosf(lo);
  float x1 = x * cLon - zz * sLon, z1 = x * sLon + zz * cLon, y1 = y;   // yaw (lon)
  float y2 = y1 * cLat - z1 * sLat, z2 = y1 * sLat + z1 * cLat;         // pitch (lat)
  sx = cx + (int)(x1 * R);
  sy = cy - (int)(y2 * R);
  z  = z2;
}

// True for records that are real navigable nodes (skip the -90 special marker and the
// runtime percept/belief/sync lanes at lat 96/97/98/99 — the lat<90 bound covers all
// of them, incl. the new @LAT96 entity lane — TTCP-RFC-0001 §8).
static inline bool isNodeRecord(const TtdbRecord& r) {
  return r.lat > -90 && r.lat < 90;
}

// Per-node belief attributes parsed once at load (fleet map, SP6): friendly name (the
// globe label) + position sigma in metres (the uncertainty ring), indexed by record.
// Filled from each record body's `name:` / `sigma_m:` lines by parseNodeAttrs().
static char  gNodeName[TTDB_MAX_RECORDS][12];
static float gNodeSigmaM[TTDB_MAX_RECORDS];
static const float DEG_PER_M = 1.0f;      // companion.py fleetmap metres->degrees scale
static const float SIGMA_VIS_SCALE = 0.35f;  // shrink the (honestly huge) sigma rings

static void parseNodeAttrs() {
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    gNodeName[i][0] = 0;
    gNodeSigmaM[i] = 0.0f;
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
  }
}

// Colour a typed edge by its transport: the edge type IS the transport (gen-fleetmap.py
// emits `espnow@...` / `lora@...`). Green = ESP-NOW, amber = LoRa; `hot` brightens the
// selected node's incident links.
static uint16_t edgeColor(const char* type, bool hot) {
  bool lora = strncmp(type, "lora", 4) == 0;
  if (lora) return hot ? rgb565(255, 190, 60) : rgb565(150, 110, 30);
  return hot ? rgb565(120, 230, 150) : rgb565(40, 110, 70);
}

// Render the globe into the off-screen canvas: sphere outline + graticule, every link
// coloured by transport, each node's sigma uncertainty ring, then the nodes (selected =
// eyeball, front = labeled dot, back = muted dot). Pushed to the panel by renderScreen().
static void renderGlobe() {
  if (!gGlobe) return;
  GFXcanvas16& c = *gGlobe;
  c.fillScreen(ST77XX_BLACK);
  const int cx = GLOBE_W / 2, cy = GLOBE_H / 2;
  const float R = (GLOBE_H / 2.0f - 4) * gZoom;
  c.drawCircle(cx, cy, (int)R, rgb565(24, 34, 52));   // sphere silhouette
  const float sLat = sinf(gRotLat), cLat = cosf(gRotLat);
  const float sLon = sinf(gRotLon), cLon = cosf(gRotLon);

  // Graticule (TTCP-RFC-0002 §12): faint parallels every 30 deg + meridians every
  // 30 deg as front-facing dots, drawn behind the edges and nodes for orientation.
  const uint16_t grat = rgb565(20, 28, 42);
  int gx, gy; float gz;
  for (int glat = -60; glat <= 60; glat += 30)
    for (int glon = 0; glon < 360; glon += 8) {
      projectLL(glat, glon, R, cx, cy, sLat, cLat, sLon, cLon, gx, gy, gz);
      if (gz > 0) c.drawPixel(gx, gy, grat);
    }
  for (int glon = 0; glon < 360; glon += 30)
    for (int glat = -78; glat <= 78; glat += 8) {
      projectLL(glat, glon, R, cx, cy, sLat, cLat, sLon, cLon, gx, gy, gz);
      if (gz > 0) c.drawPixel(gx, gy, grat);
    }

  // Fleet links (TTCP-RFC-0002 §4), every node's typed edges coloured by transport
  // (green ESP-NOW / amber LoRa); the selected node's links are brightened. Drawn when
  // both ends face the camera. A-B/B-A double-draw is harmless (same line).
  const int selLat = (gSel >= 0 && gSel < gViewDb->recordCount()) ? gViewDb->record(gSel).lat : 32767;
  const int selLon = (gSel >= 0 && gSel < gViewDb->recordCount()) ? gViewDb->record(gSel).lon : 32767;
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r)) continue;
    int sx0, sy0; float sz0;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx0, sy0, sz0);
    TtdbEdge edges[8];
    uint8_t ne = gViewDb->edgesAt(i, edges, 8);
    for (uint8_t e = 0; e < ne; ++e) {
      int tx, ty; float tz;
      projectLL(edges[e].target_lat, edges[e].target_lon, R, cx, cy,
                sLat, cLat, sLon, cLon, tx, ty, tz);
      if (sz0 > 0 && tz > 0) {
        bool hot = (r.lat == selLat && r.lon == selLon) ||
                   (edges[e].target_lat == selLat && edges[e].target_lon == selLon);
        c.drawLine(sx0, sy0, tx, ty, edgeColor(edges[e].type, hot));
      }
    }
  }

  // Sigma rings: each front node's position uncertainty, radius = sigma_m at the same
  // metres->degrees scale as the positions (so a large RSSI sigma reads as a large ring).
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r) || gNodeSigmaM[i] <= 0.0f) continue;
    int sx, sy; float z;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx, sy, z);
    if (z <= 0) continue;
    int rr = (int)(gNodeSigmaM[i] * DEG_PER_M * R * 0.01745329f * SIGMA_VIS_SCALE);
    int cap = (int)(R * 0.7f);
    if (rr > cap) rr = cap;                 // clamp so a huge sigma doesn't swamp the map
    if (rr > 1) c.drawCircle(sx, sy, rr, rgb565(34, 46, 34));
  }

  // Nodes. No discovery gating (removed by request): every node record is always drawn
  // and labeled with its fleet name — front nodes get a colored dot + label, the
  // selected one an eyeball, back-facing ones a muted dot (occluded, so unlabeled).
  c.setTextSize(1);
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r)) continue;
    int sx, sy; float z;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx, sy, z);
    uint16_t col = nodeColor(r.lat, r.lon);
    char id[20];
    if (gNodeName[i][0]) snprintf(id, sizeof(id), "%s", gNodeName[i]);
    else                 snprintf(id, sizeof(id), "@%d,%d", r.lat, r.lon);
    if (i == gSel) {
      int er = GLOBE_H / 14; if (er < 5) er = 5;         // eyeball (TTCP-RFC-0002 §3.2)
      int irisR  = er - 2;                               // iris radius
      int pupilR = er / 2 > 1 ? er / 2 : 2;              // pupil radius
      c.fillCircle(sx, sy, er, ST77XX_WHITE);            // sclera
      // Gaze toward the globe center: iris and pupil both slide along the look
      // direction, each clamped so its own outer edge never crosses the white
      // sclera (looks inward, but never spills past the eye).
      float gvx = cx - sx, gvy = cy - sy;
      float gl = sqrtf(gvx * gvx + gvy * gvy);
      float ux = 0.0f, uy = 0.0f;
      if (gl > 0.001f) { ux = gvx / gl; uy = gvy / gl; }
      float look     = gl * 0.22f;                       // desired look distance (px)
      float irisOff  = look < (float)(er - irisR)  ? look : (float)(er - irisR);
      float pupilOff = look < (float)(er - pupilR) ? look : (float)(er - pupilR);
      c.fillCircle(sx + (int)(ux * irisOff),  sy + (int)(uy * irisOff),  irisR,  col);
      int px = sx + (int)(ux * pupilOff);
      int py = sy + (int)(uy * pupilOff);
      c.fillCircle(px, py, pupilR, ST77XX_BLACK);
      c.drawPixel(sx - er / 3, sy - er / 3, ST77XX_WHITE);  // shine
      c.setTextColor(ST77XX_WHITE);
      c.setCursor(sx + er + 2, sy - 3);
      c.print(id);
    } else if (z > 0) {
      c.fillCircle(sx, sy, 3, col);                      // front node
      c.setTextColor(col);
      c.setCursor(sx + 5, sy - 3);
      c.print(id);
    } else {
      c.drawPixel(sx, sy, rgb565(60, 66, 78));           // back-facing indicator
    }
  }
}

// Bottom half — the selected record (title + first body lines), TTCP-RFC-0001 §5.
static void renderRecord() {
  if (gBottomDirty) gTft.fillRect(0, BOTTOM_Y, 320, BOTTOM_H, ST77XX_BLACK);
  char l[54];
  if (gSel < 0 || gSel >= gViewDb->recordCount()) {
    drawWide(BOTTOM_Y, ST77XX_YELLOW, "(no record selected)");
    return;
  }
  const TtdbRecord& r = gViewDb->record(gSel);
  snprintf(l, sizeof(l), "@LAT%dLON%d   record %d/%d", r.lat, r.lon, gSel + 1,
           gViewDb->recordCount());
  drawWide(BOTTOM_Y, nodeColor(r.lat, r.lon), l);

  // Stream the body: read the record span, skip the header line, print the next lines
  // wrapped to the screen width. Only redrawn on selection/pane change (gBottomDirty),
  // so this streaming read is not per-frame.
  if (!gBottomDirty) return;
  size_t off, len;
  if (!gViewDb->recordSpan(gSel, off, len)) return;
  static char body[520];
  size_t n = len < sizeof(body) - 1 ? len : sizeof(body) - 1;
  n = gViewDb->readBytes(off, (uint8_t*)body, n);
  body[n] = 0;
  const char* p = strchr(body, '\n');       // skip the header line
  p = p ? p + 1 : body;
  int y = BOTTOM_Y + 14, col = 0;
  char line[54];
  while (*p && y < 240 - 8) {
    if (*p == '\n') {                        // blank line -> small gap, new row
      if (col > 0) { line[col] = 0; drawWide(y, ST77XX_WHITE, line); y += 10; col = 0; }
      p++;
      continue;
    }
    line[col++] = *p++;
    if (col >= 52) { line[col] = 0; drawWide(y, ST77XX_WHITE, line); y += 10; col = 0; }
  }
  if (col > 0 && y < 240 - 8) { line[col] = 0; drawWide(y, ST77XX_WHITE, line); }
}

// Bottom half — the console log pane (the swipe-up analog; toggled by SPACE). Shows
// live counters + the last LOG_LINES events, TTCP link-styled by color.
static void renderConsole() {
  if (gBottomDirty) gTft.fillRect(0, BOTTOM_Y, 320, BOTTOM_H, ST77XX_BLACK);
  char l[54];
  snprintf(l, sizeof(l), "CONSOLE  drive>%s  cmd%lu rx%lu rly%lu",
           nodeName(gCmdTarget), (unsigned long)gCmdSent, (unsigned long)gEspRx,
           (unsigned long)gReplies);
  drawWide(BOTTOM_Y, ST77XX_CYAN, l);
  int y = BOTTOM_Y + 12;
  for (int k = 0; k < gLogCount; ++k) {
    int idx = (gLogHead - gLogCount + k + LOG_LINES * 2) % LOG_LINES;
    drawWide(y, ST77XX_GREEN, gLog[idx]);
    y += 10;
  }
}

// Frame dispatcher: thin status bar, globe (top), then the active bottom pane.
static void renderScreen() {
  char l[54];
  snprintf(l, sizeof(l), "T-DECK 0x%X %s sync%s drive>%s z%d %c", (unsigned)kNodeId,
           viewName(gView), gSynced ? "+" : "-", nodeName(gCmdTarget),
           gZoomIdx + 1, gPane == PANE_CONSOLE ? 'C' : 'M');
  drawWide(STATUS_Y, ST77XX_WHITE, l);

  if (gGlobe) {
    if (gGlobeDirty) {
      renderGlobe();
      gTft.drawRGBBitmap(GLOBE_X, GLOBE_Y, gGlobe->getBuffer(), GLOBE_W, GLOBE_H);
      gGlobeDirty = false;
    }
  } else if (gBottomDirty || gGlobeDirty) {   // no canvas: text fallback in the top half
    gTft.fillRect(0, GLOBE_Y, 320, GLOBE_H, ST77XX_BLACK);
    drawWide(GLOBE_Y + 40, ST77XX_YELLOW, "(globe canvas unavailable - low RAM)");
    gGlobeDirty = false;
  }

  if (gPane == PANE_CONSOLE) renderConsole();
  else                       renderRecord();
  gBottomDirty = false;
}

// Select a record: seat the cursor, mark the bottom half dirty, and animate the globe
// to bring the node to front-center (TTCP-RFC-0002 §6.2/§6.3).
static void selectRecord(int i) {
  if (i < 0 || i >= gViewDb->recordCount()) return;
  gSel = i;
  const TtdbRecord& r = gViewDb->record(i);
  gTgtLon = -(r.lon * 0.01745329f);   // bring @lon to the meridian facing us
  gTgtLat = (r.lat * 0.01745329f);
  gAnim = true;
  gBottomDirty = true;
  gGlobeDirty = true;
}

// Advance selection to the next navigable node record (wraps). Used by trackball click.
static void selectNextNode() {
  int n = gViewDb->recordCount();
  for (int step = 1; step <= n; ++step) {
    int i = (gSel + step) % n;
    if (isNodeRecord(gViewDb->record(i))) { selectRecord(i); return; }
  }
}

// Point render + navigation at a globe (VIEW_FLEET / VIEW_RFC): swap the active TTDB,
// re-derive its node labels, and restore that view's remembered selection (seating the
// first navigable node the first time the view is shown). The mesh is untouched — only
// what the screen draws and the trackball/'t' key drive changes.
static void activateView(int v) {
  gView   = v;
  gViewDb = (v == VIEW_RFC) ? &gRfcDb : &gDb;
  parseNodeAttrs();                        // refill gNodeName/gNodeSigmaM for this db
  int sel = gViewSel[v];
  if (sel < 0 || sel >= gViewDb->recordCount() || !isNodeRecord(gViewDb->record(sel))) {
    sel = -1;
    for (int i = 0; i < gViewDb->recordCount(); ++i)
      if (isNodeRecord(gViewDb->record(i))) { sel = i; break; }
  }
  gSel = gViewSel[v] = sel;
  if (sel >= 0) {                           // center the globe on the selection, no ease
    gRotLat = gTgtLat = gViewDb->record(sel).lat * 0.01745329f;
    gRotLon = gTgtLon = -(gViewDb->record(sel).lon * 0.01745329f);
  }
  gAnim = false;
  gGlobeDirty = gBottomDirty = gScreenDirty = true;
}

// Trackball click: cycle to the next globe view (skipping the RFC globe if it never
// loaded). Remembers where the cursor was in the view we are leaving.
static void toggleGlobeView() {
  gViewSel[gView] = gSel;
  int nv = (gView + 1) % VIEW_COUNT;
  if (nv == VIEW_RFC && !gRfcLoaded) nv = VIEW_FLEET;   // no RFC globe -> stay on fleet
  activateView(nv);
}
#endif

void setup() {
  Serial.begin(115200);
  delay(200);

  // T-Deck peripheral power rail: keyboard, LCD, LoRa and SD are all dead until this
  // is HIGH. Safe to assert even headless (USE_TDECK_HW 0) so LoRa can be enabled.
  pinMode(PIN_POWERON, OUTPUT);
  digitalWrite(PIN_POWERON, HIGH);
  delay(100);

  // Restore the song on/off state so a power-cycle rejoins the song (the harmony gate
  // holds it silent until we re-lock to the band as a follower).
  gPrefs.begin("tdeck", false);
  gLocalPlay = gPrefs.getBool("play", false);

#if USE_TDECK_HW
  // Audio first: bring up I2S and sound the boot "toot toot" (before the screen, like
  // the K10). The MAX98357A speaker rail is powered by PIN_POWERON (asserted above).
  gI2S.setPins(PIN_I2S_BCLK, PIN_I2S_WS, PIN_I2S_DOUT);
  if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO))
    playStartupToot();
  else
    Serial.println("I2S begin failed");

  // Keyboard I2C + the ST7789 on its own HSPI bus (shared with LoRa/SD, both idle here).
  Wire.begin(PIN_KBD_SDA, PIN_KBD_SCL);
  gDispSpi.begin(PIN_SPI_SCLK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_TFT_CS);
  gTft.init(240, 320);            // ST7789 native res; setRotation makes it 320x240
  gTft.setRotation(3);            // landscape (T-Deck: USB on the left, keyboard up)
  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH); // backlight on
  gTft.fillScreen(ST77XX_BLACK);
  gTft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  gTft.setTextSize(2);
  gTft.setCursor(4, 4);
  gTft.print("T-DECK booting");

  // Trackball (the only pointer on this non-touch panel): count falling edges per
  // direction; loop() turns them into globe rotation + a select on click.
  pinMode(PIN_TB_UP, INPUT_PULLUP);
  pinMode(PIN_TB_DN, INPUT_PULLUP);
  pinMode(PIN_TB_L, INPUT_PULLUP);
  pinMode(PIN_TB_R, INPUT_PULLUP);
  pinMode(PIN_TB_CLICK, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_TB_UP), isrTbUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_TB_DN), isrTbDn, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_TB_L), isrTbL, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_TB_R), isrTbR, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_TB_CLICK), isrTbClick, FALLING);

  // Off-screen globe canvas — PSRAM when the FQBN carries PSRAM=opi (PLAN.md SP6-T).
  // Null-safe: if the alloc fails, renderScreen() falls back to a text top bar.
  gGlobe = new GFXcanvas16(GLOBE_W, GLOBE_H);
  if (!gGlobe || !gGlobe->getBuffer()) {
    if (gGlobe) { delete gGlobe; gGlobe = nullptr; }
    Serial.println("globe canvas alloc failed - text fallback");
  }
#endif

  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId, gLocus);

  // Second globe: the read-only RFC corpus (RFCs/rfc.ttdb.md), toggled in with the
  // trackball click. View-only — it never joins the mesh or gets shared/attested.
  if (gRfcDb.begin(LittleFS, kRfcTtdbPath)) {
    gRfcLoaded = true;
    Serial.printf("RFC globe loaded: %u bytes, %d records\n",
                  (unsigned)gRfcDb.fileSize(), gRfcDb.recordCount());
  } else {
    Serial.println("RFC globe (/rfc.ttdb.md) not found - fleet view only");
  }

#if USE_TDECK_HW
  // Seat the fleet globe: derive node labels, seat the cursor on the first navigable
  // record and center on it with no boot animation (TTCP-RFC-0002 §6.1).
  activateView(VIEW_FLEET);
#endif

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_ps(WIFI_PS_NONE);   // keep RX hot for the mesh (K10 lesson)
  if (esp_now_init() != ESP_OK) Serial.println("FATAL: esp_now_init failed");
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_register_send_cb(onEspNowSend);   // paces TTDB_DATA bursts (see sendEspNow)
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

#if USE_PULSE
  gPulse.begin(kNodeId, millis());   // silent follower (highest-ish id never conducts)
#endif

#if USE_GPS
  gpsProbeBaud();   // ~1 s: lock the NMEA baud (SP2 roaming anchor). No fix needed here.
  Serial.printf("GPS UART1 (rx %d tx %d) @ %lu baud\n", PIN_GPS_RX, PIN_GPS_TX,
                (unsigned long)gGpsBaud);
#endif

#if USE_BLE
  // Near-range tier: advertise this node + passively scan peers over BLE, feeding RSSI
  // into the same @LAT97 lane as ESP-NOW (proto:ble). The roaming console is the most
  // valuable BLE node — near-range RSSI holds up where far ESP-NOW ranging degrades.
  blelink::begin(kNodeId, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, onBleObserve);
  Serial.println("BLE near-range tier up (advert + passive scan)");
#endif

  Serial.printf("T-Deck console 0x%08X online (hw %s, LoRa %s, GPS %s)\n", kNodeId,
                USE_TDECK_HW ? "on" : "off", USE_LORA ? "on" : "off",
                USE_GPS ? "on" : "off");
}

void loop() {
#if USE_GPS
  gpsPoll();   // drain NMEA into the parser; the fix is read on CMD_GET_GPS (SP2)
#endif

  // Serve TTDB-share / commands arriving from the laptop over USB-CDC (direct pull,
  // negchecks). Un-deduped trusted link.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) {
      gScreenDirty = true;
      handleToot(t, sendSerial, nullptr);
    }
  }

  // Serve a deferred ESP-NOW TTDB_REQ (burst streams from the main task).
  if (gReqPending) {
    gReqPending = false;
    serveTtdbReq(gPendingReq, sendEspNow, nullptr);
  }
  // Serve a deferred ESP-NOW TTDB_PUT (belief slice): flash write on the main task.
  if (gPutPending) {
    gPutPending = false;
    handleToot(gPendingPut, sendEspNow, nullptr);
  }
  // Serve a deferred CMD_CLEAR_PERCEPTS (TTDB rewrite on the main task).
  if (gClearPending) {
    gClearPending = false;
    handleToot(gPendingClear, sendEspNow, nullptr);
  }
  // Append the deferred TTDB log records (flash write + re-index).
  if (gSyncPending) { gSyncPending = false; appendSyncRecord(); }

  // SP0: flush the link-percept window into the @LAT97 lane (flash write from
  // loop(), never the recv callback). Lane-capped until SP1 adds pruning.
  if (gLinkLog.due(millis())) {
    int lane = 0;
    for (int i = 0; i < gDb.recordCount(); ++i)
      if (gDb.record(i).lat == 97) ++lane;
    if (lane >= LINKPERCEPT_MAX_LANE) {
      gLinkLog.reset(millis());  // lane full: drop the window, keep observing
    } else {
      char rec[1024];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)millis();
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms,
                                      gSynced, millis());
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[link] percept window -> @LAT97LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }

#if USE_WIFI_SCAN
  // SP0 entity tier: run the duty-cycled scan, then flush its window into the @LAT96
  // lane (same defer-to-loop + lane-cap discipline as @LAT97). @LAT96 is skipped by the
  // globe's isNodeRecord (lat<90), so it never renders as a spurious node dot.
  serviceWifiScan();
  if (gEntityLog.due(millis())) {
    int lane = 0;
    for (int i = 0; i < gDb.recordCount(); ++i)
      if (gDb.record(i).lat == 96) ++lane;
    if (lane >= ENTITYPERCEPT_MAX_LANE) {
      gEntityLog.reset(millis());  // lane full: drop the window, keep observing
    } else {
      char rec[1024];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)millis();
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms,
                                        gSynced, millis());
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[entity] percept window -> @LAT96LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

  if (gBeliefSyncPending) { gBeliefSyncPending = false; appendBeliefRecord(); }

#if USE_TDECK_HW
  // Trackball — the globe's pointer (non-touch panel). Roll rotates the globe; a
  // click toggles the globe view (Semantic Position <-> RFC corpus). Node stepping
  // moved to the 't' key.
  {
    int dx = (int)gTbR - (int)gTbL;
    int dy = (int)gTbUp - (int)gTbDn;   // up/down inverted (operator preference)
    gTbR = gTbL = gTbDn = gTbUp = 0;
    if (dx || dy) {
      // Negated so the globe surface follows the roll (drag-to-move feel) — the roll
      // pulses read the opposite sense on this trackball (confirmed on hardware).
      gRotLon -= dx * 0.16f;
      gRotLat -= dy * 0.16f;
      if (gRotLat > 1.52f) gRotLat = 1.52f;      // clamp near the poles (TTCP §5.1)
      if (gRotLat < -1.52f) gRotLat = -1.52f;
      gAnim = false;                             // manual roll cancels a selection ease
      gGlobeDirty = true;
    }
    if (gTbClick) { gTbClick = false; toggleGlobeView(); }
  }
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

  // Console keyboard — the operator function. Each key injects a CMD at gCmdTarget
  // (no "enter"; every press sends immediately):
  //   t = next node (both globes; also cycles the comm target in Semantic Position view)
  //   s = get-status   p = ping   b = beep
  //   g = play (start the target's song)  x = stop   SPACE = toggle console pane
  //   +/= = zoom in (closer)   -/_ = zoom out (further)
  // Any other key defaults to a status query. See the on-screen legend.
  char k = readKey();
  if (k) {
    gLastKey = k;
    switch (k) {
      case 't':
        selectNextNode();                        // step the selection in the active globe
        if (gView == VIEW_FLEET) {               // Semantic Position view also cycles the
          gTargetIdx = (gTargetIdx + 1) % kNumTargets;   // keyboard's comm target
          gCmdTarget = kTargets[gTargetIdx];
        }
        gScreenDirty = true;
        break;
      case '+': case '=':                        // zoom in (closer)
        if (gZoomIdx < 2) { gZoomIdx++; gZoom = kZoomLevels[gZoomIdx]; }
        gGlobeDirty = true; gScreenDirty = true;
        break;
      case '-': case '_':                        // zoom out (further)
        if (gZoomIdx > 0) { gZoomIdx--; gZoom = kZoomLevels[gZoomIdx]; }
        gGlobeDirty = true; gScreenDirty = true;
        break;
      case 'p': emitCmd(toot::CMD_PING, nullptr, 0); break;
      case 'b': { uint8_t a[4]; toot::put_u16(a, 880); toot::put_u16(a + 2, 200);
                  emitCmd(toot::CMD_BEEP, a, 4); break; }
      // Play/stop are band-wide: broadcast so ONE press starts/stops the whole fleet (+ our part).
      case 'g': setLocalPlay(true);  emitCmdTo(toot::CMD_PLAY, NODE_BROADCAST, nullptr, 0); break;
      case 'x': setLocalPlay(false); emitCmdTo(toot::CMD_STOP, NODE_BROADCAST, nullptr, 0); break;
      case ' ':                                  // swipe-up analog: toggle the console
      case 'n':
        gPane = (gPane == PANE_MAIN) ? PANE_CONSOLE : PANE_MAIN;
        gBottomDirty = true;
        gScreenDirty = true;
        break;
      case 's':
      default:  emitCmd(toot::CMD_GET_STATUS, nullptr, 0); break;
    }
  }
#endif

#if USE_PULSE
  // Relay a chart beacon when due (drift-paced / on-join) so the console helps the
  // band converge; it plays no audible part.
  {
    uint32_t pnow = millis();
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags, oc.scene_id);
      emit(toot::PULSE, body, blen, sendEspNow, nullptr);
    }
    // The chart's scene moved (or we just joined a band mid-song): this is the seam
    // where a node re-selects the phrase it plays, via score::phraseForScene. Parts
    // are still single-scene, so for now it only reports the move (and repaints, so
    // the console screen can show the band's place in the song).
    uint16_t new_scene;
    if (gPulse.sceneChanged(new_scene)) {
      Serial.printf("[scene] scene %u (era %lu cond 0x%08X)\n", new_scene,
                    (unsigned long)gPulse.chart().era,
                    (unsigned)gPulse.chart().conductor_id);
      gScreenDirty = true;
    }
    // Part 2: the harmony line. On each new step, sound its note (if playing) on the I2S
    // speaker — same shared clock as the K10 lead, so the two voices lock. toneI2S blocks
    // ~PULSE_HARM_TONE_MS, which is the K10's deferred-tone discipline (fine in loop()).
    // Play only when the song is on AND we're locked to the band as a FOLLOWER — i.e. in
    // phase with the K10 lead. While self-appointed (just rebooted, not yet re-locked) we
    // stay silent so the harmony never plays out of phase; it resumes the moment we adopt
    // the conductor's chart. This is what makes a power-cycled T-Deck rejoin cleanly.
    uint16_t sip;
    uint32_t sc;
    if (gPulse.stepTick(pnow, kHarm.steps, sip, sc) && gLocalPlay && !gPulse.conductor()) {
      const score::Note* nt = score::noteAt(kHarm, sip);
      if (nt && nt->freq != score::REST) {
#if USE_TDECK_HW
        toneI2S((float)nt->freq, PULSE_HARM_TONE_MS);
#endif
        Serial.printf("[harmony] step %2u/%u  %4uHz\n", sip, kHarm.steps, nt->freq);
      }
    }
  }
#endif

  // Periodic HELLO beacon + screen heartbeat.
  static uint32_t lastBeacon = 0;
  if (millis() - lastBeacon >= 2000) {
    lastBeacon = millis();
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }
#if USE_TDECK_HW
  // Log new replies into the console ring from loop context (never the recv callback).
  static uint32_t lastLoggedReplies = 0;
  if (gReplies != lastLoggedReplies) {
    lastLoggedReplies = gReplies;
    char lg[40];
    snprintf(lg, sizeof(lg), "reply %s  %.1fC", nodeName(gLastReplySrc),
             gLastReplyTemp / 100.0f);
    logLine(lg);
  }
  static uint32_t lastRender = 0;
  if (gScreenDirty || gGlobeDirty || millis() - lastRender >= 1000) {
    lastRender = millis();
    gScreenDirty = false;
    renderScreen();
  }
#endif
}
