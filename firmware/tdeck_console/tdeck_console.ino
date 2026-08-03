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
#include <HeroArc.h>  // the hero's-arc song: scene -> phrase tables for every role
#include <LinkPercept.h>  // SP0: every authenticated reception becomes a percept
#include <BleLink.h>      // SP0 near-range tier: BLE advert+scan -> PROTO_BLE percepts
#include <EntityPercept.h>  // SP0 entity tier: WiFi BSSID sightings -> @LAT96 percepts
#include <TimeStreamNode.h>  // the team time stream -> @LAT90 (a timeline the fleet owns)
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
// Battery sense for interoception. GPIO4 is ADC1_CH3 (WiFi-safe) and is where LilyGo's
// own board support reads the pack, through a 1:1 resistive divider — hence x2. BOTH of
// those are ASSUMPTIONS taken from LilyGo's utilities.h, not from a meter on this unit,
// so the sampler prints the RAW pin millivolts beside the derived pack voltage on its
// first sample: put a meter on the JST lead and change this one constant if they
// disagree. Exactly the Cardputer's discipline (BAT_DIVIDER there) and for the same
// reason — the number the laptop cannot check is a named constant, not buried arithmetic.
static const int PIN_BAT_ADC   = 4;
static const float BAT_DIVIDER = 2.0f;

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

// Which node the keyboard drives. Cycled with the 't' key. The band no longer rides on
// this (`g`/`x` broadcast, so one press starts every member), so the target is now purely
// "who do the addressed keys talk to". Every entry answers a get-status over the air
// EXCEPT the V4-A bridge, which answers CMDs only from the laptop over USB.
// The K10 left this list when it left the mesh map (it still runs v1 firmware and is off
// the band roster); the Cardputer took its place and leads, being the node most worth
// driving from here — it is the fleet's sense organ and the only one that answers
// CMD_GET_INTERO, so it is what the record pane's interoception view watches.
static const uint32_t kTargets[] = {NODE_CARDPUTER_1, NODE_V4B_RELAY, NODE_V4C_EDGE,
                                    NODE_V4A_BRIDGE};
static const int kNumTargets = sizeof(kTargets) / sizeof(kTargets[0]);
static int gTargetIdx = 0;
static uint32_t gCmdTarget = NODE_CARDPUTER_1;

// The T-Deck's own musical voice. `g`/`x` (or a received CMD_PLAY/STOP) toggle it, so
// one `g` starts the whole band at once. The on/off state is persisted in NVS
// (setLocalPlay), so a power-cycle RESUMES the part — the T-Deck rejoins the song once
// it re-locks to the band (played only as an in-phase follower; see the gate below).
static Preferences gPrefs;
static bool gLocalPlay = false;
static void setLocalPlay(bool on) {
  gLocalPlay = on;
  gPrefs.putBool("play", on);     // survive a reboot (screen refreshes within 1 s)
}
static const uint32_t PULSE_HARM_TONE_MS = 180;   // staccato note (blocks; keep short)

// --- the duet: two nodes, by name, on the shared clock (CMD_DUET) --------------------
// Deliberately NOT a chart scene. A scene is the whole band's shared position in the song,
// so putting the pair into SCENE_FINALE would pull in every powered member and produce a
// finale rather than a duet. A duet instead overrides only these two nodes' PARTS, leaves
// the chart's scene exactly where it was, and rides the same pulse step clock the band
// already shares — which is what makes the two voices land together. It changes what each
// node plays, never when.
//
// Not persisted in NVS, unlike the song: `d` is a momentary thing an operator does while
// looking at a particular node, and a console that resumed a duet on boot would start
// singing the lead at a partner that may not be there.
static uint8_t  gDuetRole = toot::DUET_OFF;
static uint32_t gDuetPeer = 0;
static uint8_t  gDuetSpeed = 1;                   // 1 = as written, 2 = double time
static inline bool duetOn() { return gDuetRole != toot::DUET_OFF; }

// The duet plays in DOUBLE TIME by default: the pair covers the phrase in half the steps, so
// it reads as twice as fast while the band's beat period — and therefore everyone else's
// timing — is completely untouched. To go back to the written tempo, make this 1.
static const uint8_t DUET_DEFAULT_SPEED = 2;

// Can this phrase be taken at `speed`? Double time works by traversing the SAME note table in
// half as many steps, so every note's position must still fall on a step the sequencer
// actually visits (score::noteAt is an exact match). If any note would land between slots we
// refuse the speed instead of quietly dropping a note out of the melody — kOdeLead's tied note
// at step 54 is exactly that case at ÷4. Cheap, and computed once when a duet is set up.
static uint8_t validDuetSpeed(const score::Phrase& ph, uint8_t speed) {
  if (speed < 1) return 1;
  if (speed > toot::DUET_SPEED_MAX) speed = toot::DUET_SPEED_MAX;
  if (ph.steps % speed) return 1;
  for (uint16_t i = 0; i < ph.count; ++i)
    if (ph.notes[i].step % speed) return 1;
  return speed;
}

// Enter/leave a duet, validating the requested speed against the phrase our role names.
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
// The T-Deck's PART in the hero's-arc song (HeroArc.h, TTN-RFC-0010 §7): the RETURNING
// ROAMER — silent through scenes 0-3, back with the Ode-to-Joy HARMONY in scene 4 (the
// song's first pitched voice), then carrying the LEAD in the finale. Which scenes play
// what is authored in the score table, not here.
static const score::Part& kPart = heroarc::kConsole;

// Friendly short name for a node id (for the screen).
static const char* nodeName(uint32_t id) {
  switch (id) {
    case NODE_V4A_BRIDGE: return "V4-A";
    case NODE_V4B_RELAY:  return "V4-B";
    case NODE_V4C_EDGE:   return "V4-C";
    case NODE_K10_1:      return "K10";
    case NODE_TDECK_1:    return "T-Deck";
    case NODE_CARDPUTER_1: return "Card";
    case NODE_BROADCAST:  return "ALL";
    default:              return "?";
  }
}

// The inverse, over the SLUG a fleet-map record carries. The two globes name nodes
// differently and both are legitimate: the feelings globe writes `node: 0x10` (authored by
// hand for the band overlay) while the fleet map writes `node: cardputer_1` (authored by
// `companion.py fleetmap` from positions.md, where a node IS its slug). Resolving both
// means a fleet-map record knows which live mesh member it depicts — which is what turns
// "the record for cardputer_1" into "that node over there, ask it how it feels".
static uint32_t nodeIdFromSlug(const char* s) {
  if (!s) return 0;
  if (!strncmp(s, "v4a_bridge", 10))   return NODE_V4A_BRIDGE;
  if (!strncmp(s, "v4b_relay", 9))     return NODE_V4B_RELAY;
  if (!strncmp(s, "v4c_edge", 8))      return NODE_V4C_EDGE;
  if (!strncmp(s, "cardputer_1", 11))  return NODE_CARDPUTER_1;
  if (!strncmp(s, "tdeck_1", 7))       return NODE_TDECK_1;
  if (!strncmp(s, "k10_1", 5))         return NODE_K10_1;
  return 0;
}

Ttdb gDb;                 // fleet globe — the network-facing TTDB (shared/synced/attested)
Ttdb gRfcDb;              // RFC corpus globe — view-only (never shared over the mesh)
Ttdb gFeelDb;             // feelings globe — affective landscape + the band overlay (view-only)
static const char* kRfcTtdbPath = "/rfc.ttdb.md";
static const char* kFeelTtdbPath = "/feelings.ttdb.md";
static bool gRfcLoaded = false;
static bool gFeelLoaded = false;
TtdbShare* gShare = nullptr;

// Globe views the trackball click cycles through. VIEW_FEELINGS (the affective landscape
// with the three other band members overlaid as live eyeballs) is the DEFAULT power-up
// view; VIEW_FLEET (Semantic Position) is the fleet TTDB; VIEW_RFC is the read-only RFC
// corpus. Only the fleet TTDB touches the mesh — TTDB_REQ / @LAT99 sync / @LAT98 belief
// always operate on gDb, never gViewDb.
enum GlobeView { VIEW_FEELINGS = 0, VIEW_FLEET, VIEW_RFC, VIEW_COUNT };
static int   gView = VIEW_FEELINGS;
static Ttdb* gViewDb = &gFeelDb;                  // active globe for render + navigation
static int   gViewSel[VIEW_COUNT] = {-1, -1, -1}; // remembered selection per view
static inline const char* viewName(int v) {
  return v == VIEW_RFC ? "RFC" : v == VIEW_FLEET ? "SemPos" : "Feelings";
}
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
// Which page of the selected record's body the pane is showing. Records run to 2666 B on
// the RFC globe and the pane holds ~10 lines, so a long record is several pages; `1`/`2`
// walk them and both directions wrap. Reset whenever the selection changes.
// `gRecPages` is published by renderRecord so the key handler can wrap without re-wrapping
// the body itself — the page count is only knowable after the text has been laid out.
static int gRecPage = 0;
static int gRecPages = 1;

// --- the team time stream (TimeStreamNode.h) + the wall clock (TTN-RFC-0008) -
// gTs owns BOTH facts now: which shared timeline this node is on, and whether that
// timeline knows the date. The old single `synced` bit could only ever answer the
// second, and answered it "no" for a fleet that was in perfect agreement with itself.
// The macros keep every existing reader below reading the way it always did; the
// difference is that they are now callback-safe scalars refreshed once per loop(),
// never live reads of an engine the WiFi task must not touch.
static timestream::Node gTs;
#define gStamp         (gTs.stamp())
#define gStreamWallSec (gTs.wallSec())
#define gSynced        (gTs.wall())
#define gClockOffsetMs (gTs.clockOffsetMs())
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return gTs.nowEpochMs(); }
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
static uint32_t gNeighborSeen[8] = {0};
static int      gNeighborCount = 0;
// Fast-lock a neighbor that is brand-new OR returning after a gap (a power-cycle): as the
// conductor we then beacon immediately so the (re)joiner locks within a round trip instead
// of waiting up to PULSE_RESYNC_PERIOD for the next scheduled beacon. A steadily-present
// neighbor (HELLO ~every 2 s) does NOT retrigger it, so steady-state traffic stays minimal.
// The console is normally a follower (highest id), but it DOES take the baton when the
// lower-id nodes drop — observed conducting at era 7 on 2026-07-18 — so it needs this too.
static const uint32_t NEIGHBOR_REJOIN_GAP_MS = 3000;
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

// millis() of the last HELLO heard from `id` (0 if never seen) — the feelings globe reads
// this to show each band member's liveness (seen 2s ago / LOST) beside its eyeball.
static uint32_t nodeLastSeen(uint32_t id) {
  for (int i = 0; i < gNeighborCount; ++i)
    if (gNeighbors[i] == id) return gNeighborSeen[i];
  return 0;
}

// The T-Deck is the RETURNING ROAMER: the one actor that drives the story past the ORDEAL
// gate the conductor holds at. When we are present and the band is dwelling in the grief,
// we call the RETURN, then the FINALE — so `g` plays the whole song, yet the band waits at
// grief whenever we are away and rejoins its part the instant we are back (a power-cycle
// resumes from NVS + the adopted chart). gSceneEnteredMs times our dwell in the current
// scene; the two latches fire each call exactly once per episode.
static uint32_t gSceneEnteredMs = 0;
static bool gTurnRequested = false;
static bool gFinaleRequested = false;
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

// Ask a node for its body (CMD_GET_INTERO), QUIETLY. A poll is not an operator action: it
// must not push a line into the console ring or bump the cmd counter every few seconds, or
// the log the operator actually reads fills up with the screen refreshing itself.
static const uint32_t INTERO_POLL_MS = 3000;
static void pollIntero(uint32_t target) {
  uint8_t body[5];
  body[0] = toot::CMD_GET_INTERO;
  toot::put_u32(body + 1, target);
  emit(toot::CMD, body, 5, sendEspNow, nullptr);
}

// Invite `peer` into a duet (or dismiss it): CMD_DUET carries who its partner is and which
// line to take. Fire-and-forget, deliberately NOT want_ack — a node that starts playing
// misses the ACK window because the tone call blocks, so an ACK here would report a false
// negative on a duet that is audibly working (@LAT90LON70). The honest confirmation is the
// partner's own body: its INTERO_VOICING bit, which the record pane is already polling.
static void sendDuet(uint32_t peer, uint8_t peer_role, uint8_t speed) {
  uint8_t body[11];
  body[0] = toot::CMD_DUET;
  toot::put_u32(body + 1, peer);
  toot::put_u32(body + 5, kNodeId);      // partner = us
  body[9] = peer_role;
  body[10] = speed;                      // both voices must agree, or they come apart
  emit(toot::CMD, body, sizeof(body), sendEspNow, nullptr);
}

// ONE invitation is not enough. ESP-NOW drops frames — that is why every other reliable path
// in this fleet either wants an ACK or re-asserts itself — and a lost CMD_DUET leaves the
// console singing the lead at a partner that never heard the ask. Observed exactly that on
// hardware: the T-Deck logged `we LEAD, they HARMONISE` and played four clean phrases while the
// Cardputer printed nothing at all.
//
// So the duet is re-asserted like the PULSE chart: cheap, idempotent state repeated on a slow
// timer rather than an event delivered once. This costs one small toot every 2 s while a duet is
// up, and it buys three things a want_ack retry would not: a partner that missed the invitation
// joins on the next tick, a partner that REBOOTS mid-duet rejoins by itself, and any transient
// disagreement about the SPEED corrects within one interval instead of lasting the whole song
// (two voices on different speeds is precisely the half-time-ping-pong failure).
static const uint32_t DUET_ASSERT_MS = 2000;
static uint32_t gDuetAsserted = 0;
static uint8_t  gDuetOffRepeats = 0;   // ending must be reliable too (see endDuet)

// Leave any duet we are in and tell the partner. Idempotent; safe to call when not in one.
static void endDuet() {
  if (!duetOn()) return;
  Serial.printf("[duet] ended with %s\n", nodeName(gDuetPeer));
  // A dropped OFF would leave the partner singing forever, so schedule a few repeats rather
  // than sending once. gDuetPeer is kept for them; setDuet clears our own role immediately.
  if (gDuetPeer) gDuetOffRepeats = 3;
  uint32_t peer = gDuetPeer;
  setDuet(toot::DUET_OFF, 0, 1);
  gDuetPeer = peer;                    // retained only to address the OFF repeats
  gScreenDirty = true;
}

// Called every loop pass: keep a live duet asserted, and drain any pending dismissals.
static void serviceDuet(uint32_t now) {
  if (gDuetOffRepeats && now - gDuetAsserted >= 150) {
    gDuetAsserted = now;
    if (gDuetPeer) sendDuet(gDuetPeer, toot::DUET_OFF, 1);
    if (--gDuetOffRepeats == 0) gDuetPeer = 0;
    return;
  }
  if (!duetOn() || now - gDuetAsserted < DUET_ASSERT_MS) return;
  gDuetAsserted = now;
  // Re-send the partner's role + speed. setDuet on their side is a plain state assignment with
  // no phase reset, so repeating it is inaudible.
  sendDuet(gDuetPeer, gDuetRole == toot::DUET_LEAD ? toot::DUET_HARM : toot::DUET_LEAD,
           gDuetSpeed);
}

#if USE_PULSE
// Walk the hero's-arc story to a scene: broadcast CMD_SET_SCENE (only the conductor
// applies a scene change, so at most one node acts — the operator needn't know who
// holds the baton) and also try locally, in case WE are the one counting (a broadcast
// doesn't loop back to its sender; setScene is a no-op on a follower).
static void emitSetScene(uint16_t scene) {
  uint8_t a[2];
  toot::put_u16(a, scene);
  emitCmdTo(toot::CMD_SET_SCENE, NODE_BROADCAST, a, 2);
  gPulse.setScene(scene, millis());
  Serial.printf("[scene] requested scene %u %s\n", scene, heroarc::sceneName(scene));
}
#endif

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

// --- INTEROCEPTION: this console's sense of its own body ----------------------
// The T-Deck's half of "look inward", ported from the Cardputer's phase S4
// (cardputer-sensorium.md §4.5). Four slow, cheap interior signals — how much ENERGY is
// left, how HOT the die is, how much contiguous RAM is left to think in, and how fast it
// is currently thinking — sampled HERE in loop context rather than in the renderer, for
// the same two reasons that hold on the Cardputer: the number must exist whether or not
// anyone is looking at the screen, and a renderer that reads a sensor is a renderer whose
// frame cost depends on that sensor.
//
// It is also what makes the console's own record pane possible. Every other node's body
// arrives as 21 bytes over the air; ours has to come from somewhere, and a screen that can
// show four other nodes' vitals but not its own is a strange instrument to be holding.
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
static float    gBatSlow  = 0.0f;   // slow EMA — the fill/drain reference
static int8_t   gBatTrend = 0;      // +1 filling, -1 draining, 0 steady
static uint8_t  gBatPct   = 0;
static int16_t  gDieC10   = 0;      // ESP32-S3 die temperature, tenths of a degree
static uint32_t gMaxAllocK = 0;     // largest CONTIGUOUS block, NOT free heap
static uint32_t gWorstLoopMs = 0;   // worst loop pass in the current window (our own rtt)
static uint32_t gLoopWorstRun = 0;  // accumulator for the window in progress

// Above this, the number on the pin is NOT a 1S pack voltage — a Li-ion cell tops out at
// 4.20 V, so a higher reading means we are measuring the charge rail with no pack on it (or
// the divider ratio is wrong). Either way a state-of-charge percentage would be a fiction,
// so the pane reports the volts and says EXT instead of claiming 100%. This board read
// 4.716 V on its first sample with the cable in — found by reading it back from the laptop,
// which is the only place a wrong assumption at a boundary shows up (see the units note on
// buildStatus for the same lesson in the other direction).
static const uint16_t BAT_LIION_CEILING_MV = 4250;

// Voltage -> state of charge for a 1S Li-ion, linear between curve points. Deliberately
// coarse: the flat middle of a Li-ion curve means any percentage between 3.7 and 3.9 V is
// a guess, and more decimals would only dress that up.
static uint8_t batPercent(uint16_t mv) {
  static const uint16_t kV[] = {3300, 3500, 3680, 3730, 3760, 3790,
                                3820, 3870, 3950, 4000, 4100, 4200};
  static const uint8_t  kP[] = {   0,    5,   10,   20,   30,   40,
                                  50,   60,   70,   80,   90,  100};
  const int n = sizeof(kP) / sizeof(kP[0]);
  if (mv <= kV[0]) return 0;
  if (mv >= kV[n - 1]) return 100;
  for (int i = 1; i < n; ++i)
    if (mv < kV[i]) {
      int span = kV[i] - kV[i - 1];
      return (uint8_t)(kP[i - 1] + (int)(kP[i] - kP[i - 1]) * (mv - kV[i - 1]) / span);
    }
  return 100;
}

static void serviceIntero(uint32_t now) {
  static uint32_t last = 0;
  if (gBatSampled && now - last < INTERO_PERIOD_MS) return;
  last = now;

  // Four reads averaged: one 12-bit sample of a divided pack behind a switching charger is
  // noisy at exactly the millivolt scale the trend arrow reads, and the burst costs well
  // under a millisecond once per 2 s.
  uint32_t acc = 0;
  for (int i = 0; i < 4; ++i) acc += analogReadMilliVolts(PIN_BAT_ADC);
  uint32_t pin_mv = acc / 4;
  uint16_t mv = (uint16_t)(pin_mv * BAT_DIVIDER);

  bool first = !gBatSampled;
  gBatSampled = true;
  gBatMv = mv;
  // 255 = "there is a voltage but it is not a pack" (see BAT_LIION_CEILING_MV). The
  // measurement is still reported; only the percentage is withheld, because that is the
  // part that would be made up.
  gBatPct = (mv > BAT_LIION_CEILING_MV) ? 255 : batPercent(mv);
  // Filling or draining? A ~2-minute EMA is the reference, so the arrow reports the
  // direction of the PACK rather than of the last sample's noise. We have no VBUS sense
  // pin, so no charge state is claimed — only which way the voltage is actually moving.
  if (first) gBatSlow = (float)mv;
  else       gBatSlow += ((float)mv - gBatSlow) * 0.03f;
  float d = (float)mv - gBatSlow;
  gBatTrend = (d > 12.0f) ? 1 : (d < -12.0f) ? -1 : 0;

  // Die temperature, not ambient: there is no ambient sensor here either. It reads high
  // (40-55 C is normal) with WiFi/BLE up millimetres away, so it measures how hard the
  // node is working as much as it measures the room.
  gDieC10 = (int16_t)lroundf(temperatureRead() * 10.0f);
  gMaxAllocK = ESP.getMaxAllocHeap() / 1024;

  if (first)
    Serial.printf("[intero] pin %lumV x%.2f = pack %umV (%u%%) | die %.1fC | "
                  "maxalloc %luK  <- CHECK THE PACK VOLTAGE AGAINST A METER\n",
                  (unsigned long)pin_mv, BAT_DIVIDER, mv, gBatPct,
                  gDieC10 / 10.0f, (unsigned long)gMaxAllocK);
}

// Build our own INTERO PERCEPT (Toot.h INTERO_PERCEPT_PAYLOAD_LEN) — the answer to a
// CMD_GET_INTERO addressed at us, and also what renderIntero() draws for our own record.
// Reads nothing: every field is the last sample serviceIntero() took.
static uint8_t buildIntero(uint8_t* p) {
  toot::put_u16(p + 0, gBatMv);
  p[2] = gBatSampled ? gBatPct : 255;   // 255 = unknown (never sampled / above the ceiling)
  p[3] = (uint8_t)(int8_t)gBatTrend;
  toot::put_u16(p + 4, (uint16_t)gDieC10);
  toot::put_u16(p + 6, (uint16_t)gMaxAllocK);
  toot::put_u32(p + 8, millis() / 1000);
  toot::put_u16(p + 12, (uint16_t)(gWorstLoopMs > 65535 ? 65535 : gWorstLoopMs));
#if USE_PULSE
  const pulse::Chart& ch = gPulse.chart();
  toot::put_u16(p + 14, ch.beat_period_ms);
  toot::put_u32(p + 16, ch.conductor_id);
  // VOICING answers "is it singing", which PLAYING does not: PLAYING only means the band
  // clock is running, and most parts are silent in most scenes. Reported as the STATE that
  // would sound a note (duet on, or the song on with a phrase for this scene) rather than
  // as the instant of a note, so a 2 s poll can't fall between two notes and read false.
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

// --- other nodes' bodies, as they told us ------------------------------------
// One decoded INTERO PERCEPT per node we have asked. Small and fixed (the fleet is six
// nodes); `rx_ms` is what makes the pane honest — a body we heard about 40 s ago is stale
// data on the screen unless the screen says so, and a node that has stopped answering must
// read as "no reply", never as its last-known vitals frozen in place and looking live.
struct InteroSnapshot {
  uint32_t node_id = 0;
  uint32_t rx_ms = 0;           // millis() when this snapshot arrived (0 = never)
  uint16_t bat_mv = 0;
  uint8_t  bat_pct = 255;
  int8_t   bat_trend = 0;
  int16_t  die_c10 = 0;
  uint16_t maxalloc_kb = 0;
  uint32_t uptime_s = 0;
  uint16_t worst_loop_ms = 0;
  uint16_t beat_period_ms = 0;
  uint32_t conductor_id = 0;
  uint8_t  flags = 0;
};
#define INTERO_PEERS 6
static InteroSnapshot gIntero[INTERO_PEERS];

// Returns the slot INDEX rather than a pointer on purpose: the .ino preprocessor hoists
// generated prototypes above every definition in the sketch, so a free function whose
// signature names a sketch-local struct fails to compile ("does not name a type"). Ints
// cross that boundary; struct pointers do not.
static int interoSlot(uint32_t id) {
  for (int i = 0; i < INTERO_PEERS; ++i)
    if (gIntero[i].node_id == id) return i;
  for (int i = 0; i < INTERO_PEERS; ++i)
    if (gIntero[i].node_id == 0) { gIntero[i].node_id = id; return i; }
  return 0;                       // full: overwrite the oldest slot we bothered to keep
}

// Decode a 21-byte INTERO PERCEPT into that node's slot. Called from the PERCEPT case,
// which runs in the recv path — stores only, no I/O, no screen.
static void noteIntero(uint32_t src, const uint8_t* p) {
  InteroSnapshot* s = &gIntero[interoSlot(src)];
  s->rx_ms = millis();
  s->bat_mv = toot::get_u16(p + 0);
  s->bat_pct = p[2];
  s->bat_trend = (int8_t)p[3];
  s->die_c10 = (int16_t)toot::get_u16(p + 4);
  s->maxalloc_kb = toot::get_u16(p + 6);
  s->uptime_s = toot::get_u32(p + 8);
  s->worst_loop_ms = toot::get_u16(p + 12);
  s->beat_period_ms = toot::get_u16(p + 14);
  s->conductor_id = toot::get_u32(p + 16);
  s->flags = p[20];
}

// STATUS telemetry for the `monitor` table. The console has no sensor cursor/temp, so
// those fields are 0; report the synced state + epoch, plus the PULSE tail for `band`.
// The temperature field is no longer 0 on this node either: it carries the die reading the
// interoception sampler now takes, so `monitor` says "the T-Deck is warm" instead of
// saying nothing. Toot.h calls the field "ambient" and a die reading is not that — but it
// is a real measurement of a real body, and an empty field is not. ⚠ The field is
// HUNDREDTHS of a degree and gDieC10 is TENTHS: the x10 is the whole reason the Cardputer's
// first build printed 4.8C for a 48 C die (companion.md §6). Do not drop it.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, (uint16_t)(gDieC10 * 10));
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
          case toot::CMD_GET_INTERO: {
            uint8_t body[toot::INTERO_PERCEPT_PAYLOAD_LEN];
            uint8_t ilen = buildIntero(body);
            emit(toot::PERCEPT, body, ilen, reply, ctx);  // INTERO PERCEPT is the answer
            break;
          }
          case toot::CMD_PLAY:                      // start the song (+ our harmony part)
            setLocalPlay(true);
#if USE_PULSE
            gPulse.armSong(heroarc::SCENE_ALONE, millis());  // walk the story if we conduct
#endif
            break;
          case toot::CMD_STOP:
            setLocalPlay(false);
            setDuet(toot::DUET_OFF, 0, 1);   // stop means stop; don't echo an OFF back
#if USE_PULSE
            gPulse.disarmSong();
#endif
            break;
          case toot::CMD_DUET:
            // We can be the INVITED voice as well as the inviter — the roles ride on the
            // wire, so nothing here assumes the console is the one that started it.
            if (t.payload_len >= 10) {
              uint32_t partner = toot::get_u32(t.payload + 5);
              uint8_t role = t.payload[9];
              // The speed byte is additive: a sender that predates it just means "as
              // written", the same discipline the STATUS and PULSE tails use.
              uint8_t speed = (t.payload_len >= 11) ? t.payload[10] : 1;
              // An inviter re-asserts a live duet every couple of seconds, so log only real
              // changes; an identical repeat is the delivery mechanism, not an event.
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
          case toot::CMD_CLEAR_PERCEPTS: {
            // Flash rewrite: reaches here only from loop() (radio path defers).
            // ACK only on success, so a failed prune is loud (laptop retries).
            uint8_t lane = toot::cmdClearLane(t);   // 0 = every percept lane
            ok = gDb.removePerceptLanes(lane);
            if (ok)
              Serial.printf("[link] percept lane %s cleared (TTDB now %uB, %dr)\n",
                            lane ? String(lane).c_str() : "ALL",
                            (unsigned)gDb.fileSize(), gDb.recordCount());
            break;
          }
          default: break;                                   // ping / set-* (no-op here)
        }
        accepted = ok;
        gScreenDirty = true;
      }
      break;
    case toot::PERCEPT: {
      // A collected reply from a node the console queried. PERCEPT is a family of payload
      // conventions distinguished by LENGTH (Toot.h): 15/43/45 = STATUS, 24 = GPS,
      // 21 = INTERO. Decode the one we recognise and fall through to the STATUS-shaped
      // stash for the rest, so an older node's reply still reads as it always did.
      gReplies++;
      gLastReplySrc = t.src_node_id;
      if (t.payload_len == toot::INTERO_PERCEPT_PAYLOAD_LEN) {
        noteIntero(t.src_node_id, t.payload);      // that node's body, as it reported it
      } else if (t.payload_len >= 6) {
        gLastReplyTemp = (int16_t)toot::get_u16(t.payload + 4);
      }
      gScreenDirty = true;
      break;
    }
    case toot::TIME_SYNC: {
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          // The laptop supplies the DATE. It does not supply the timeline — the fleet
          // already has one — so this ANCHORS the stream instead of replacing its
          // clock. Latched here, applied by gTs.service() from loop().
          gTs.onTimeSync(ems, recv_ms, t.src_node_id);
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

  // The time-stream anchor rides on HELLO — every node emits one every 2 s and its
  // payload was EMPTY until now, so this is purely additive: a node still on old
  // firmware sends 0 bytes and parseAnchor declines, making it a non-participant
  // rather than a parse error. Outside the USE_PULSE guard on purpose: the band is
  // optional, a shared timeline is not.
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
// 5 zoom levels (TTCP-RFC-0002 §2.3): level 0 = the whole globe (furthest), level 2 =
// front face filling the screen, levels 3-4 push in further to inspect one node up close
// (~1.42x per step). The node dots + eyeballs scale with the zoom (see renderGlobe /
// drawEyeball) so a magnified globe keeps proportional marks. Default = middle (level 1).
static const float kZoomLevels[5] = {1.15f, 2.0f, 2.85f, 4.05f, 5.75f};
static int   gZoomIdx = 1;
static float gZoom = kZoomLevels[1];
static const int kZoomMax = (int)(sizeof(kZoomLevels) / sizeof(kZoomLevels[0])) - 1;
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
// Mesh node id parsed from a record's `node:` line (0 if none). Non-zero marks a live
// fleet member on the feelings globe — drawn as an always-on eyeball with mesh status.
static uint32_t gNodeMeshId[TTDB_MAX_RECORDS];
// ...and the record's outgoing edges, cached the same way — ported from the Cardputer,
// which measured the defect this fixes. `Ttdb::edgesAt()` re-OPENS the TTDB file on every
// call, so drawing edges straight from it costs one LittleFS open per record per frame:
// 321-767 ms for a single repaint of a 45-record globe, which surfaced on the mesh as a
// 419 ms `verify` rtt (the toot link is serviced once per loop pass, so the slowest pass IS
// the response time). parseNodeAttrs already reads each record's header line, so caching
// the edges out of that same buffer costs no extra I/O whatsoever.
#define NODE_EDGE_MAX 6
struct CachedEdge { int16_t lat, lon; bool lora; };
static CachedEdge gNodeEdges[TTDB_MAX_RECORDS][NODE_EDGE_MAX];
static uint8_t    gNodeEdgeCount[TTDB_MAX_RECORDS];
static const float DEG_PER_M = 1.0f;      // companion.py fleetmap metres->degrees scale
static const float SIGMA_VIS_SCALE = 0.35f;  // shrink the (honestly huge) sigma rings

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
    // `node:` marks the record as depicting a live mesh member, written either as a hex id
    // (`node: 0x10`, the hand-authored feelings globe) or as a slug (`node: cardputer_1`,
    // what companion.py fleetmap emits). Accept both — see nodeIdFromSlug.
    const char* q = strstr(buf, "node:");
    if (q) {
      q += 5; while (*q == ' ') q++;
      gNodeMeshId[i] = (*q >= '0' && *q <= '9') ? (uint32_t)strtoul(q, nullptr, 0)
                                                : nodeIdFromSlug(q);
    }

    // The `relates:` edges live on the record's HEADER line, which is the start of the
    // buffer just read — so parse them here instead of paying edgesAt()'s file open once
    // per record per frame (see the cache note above).
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

// Colour a typed edge by its transport: the edge type IS the transport (gen-fleetmap.py
// emits `espnow@...` / `lora@...`). Green = ESP-NOW, amber = LoRa; `hot` brightens the
// selected node's incident links.
static uint16_t edgeColor(bool lora, bool hot) {
  if (lora) return hot ? rgb565(255, 190, 60) : rgb565(150, 110, 30);
  return hot ? rgb565(120, 230, 150) : rgb565(40, 110, 70);
}

// Draw a gazing eyeball (TTCP-RFC-0002 §3.2) at sx,sy looking toward the globe centre,
// with an optional label to its right. Used for the selected node in any view and for
// every band member on the feelings globe (so all three read as living eyes at once).
static void drawEyeball(int sx, int sy, int cx, int cy, uint16_t col, const char* label) {
  if (!gGlobe) return;
  GFXcanvas16& c = *gGlobe;
  int er = (int)(4.0f * gZoom); if (er < 5) er = 5;   // eye radius scales with zoom (~8 @ z1)
  int irisR  = er - 2;
  int pupilR = er / 2 > 1 ? er / 2 : 2;
  c.fillCircle(sx, sy, er, ST77XX_WHITE);      // sclera
  float gvx = cx - sx, gvy = cy - sy;
  float gl = sqrtf(gvx * gvx + gvy * gvy);
  float ux = 0.0f, uy = 0.0f;
  if (gl > 0.001f) { ux = gvx / gl; uy = gvy / gl; }
  float look     = gl * 0.22f;                 // gaze inward, clamped inside the sclera
  float irisOff  = look < (float)(er - irisR)  ? look : (float)(er - irisR);
  float pupilOff = look < (float)(er - pupilR) ? look : (float)(er - pupilR);
  c.fillCircle(sx + (int)(ux * irisOff),  sy + (int)(uy * irisOff),  irisR,  col);
  c.fillCircle(sx + (int)(ux * pupilOff), sy + (int)(uy * pupilOff), pupilR, ST77XX_BLACK);
  c.drawPixel(sx - er / 3, sy - er / 3, ST77XX_WHITE);   // shine
  if (label && label[0]) {
    c.setTextColor(ST77XX_WHITE);
    c.setCursor(sx + er + 2, sy - 3);
    c.print(label);
  }
}

// Build a band member's eyeball label for the feelings globe: name + a conductor star +
// its mesh liveness (how long since its last HELLO, or LOST). This is the live "status
// info" the console shows for the three other players. Falls back to the bare name if
// pulse tracking is compiled out.
static void bandLabel(int rec, char* out, size_t n) {
#if USE_PULSE
  uint32_t seen = nodeLastSeen(gNodeMeshId[rec]);
  bool cond = (gPulse.chart().conductor_id == gNodeMeshId[rec]);
  char age[8];
  if (seen == 0) {
    strncpy(age, "--", sizeof(age));
  } else {
    uint32_t a = (millis() - seen) / 1000;
    if (a > 9) strncpy(age, "LOST", sizeof(age));   // >9 s since a 2 s HELLO = gone
    else snprintf(age, sizeof(age), "%lus", (unsigned long)a);
  }
  snprintf(out, n, "%s%s %s", gNodeName[rec], cond ? "*" : "", age);
#else
  snprintf(out, n, "%s", gNodeName[rec]);
#endif
}

// Render the globe into the off-screen canvas: sphere outline + graticule, every link
// coloured by transport, each node's sigma uncertainty ring, then the nodes. In the
// feelings view the band members are always eyeballs (name + live status) and the
// affective records are dim dots; in the other views the selected node is the eyeball,
// front nodes are labeled dots, back nodes muted. Pushed to the panel by renderScreen().
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
    for (uint8_t e = 0; e < gNodeEdgeCount[i]; ++e) {
      const CachedEdge& ed = gNodeEdges[i][e];      // cached at view load, not read here
      int tx, ty; float tz;
      projectLL(ed.lat, ed.lon, R, cx, cy, sLat, cLat, sLon, cLon, tx, ty, tz);
      if (sz0 > 0 && tz > 0) {
        bool hot = (r.lat == selLat && r.lon == selLon) ||
                   (ed.lat == selLat && ed.lon == selLon);
        c.drawLine(sx0, sy0, tx, ty, edgeColor(ed.lora, hot));
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

  // Nodes. In the feelings view the three band members are always eyeballs (name + live
  // mesh status) and the affective records are dim, unlabeled dots — so the globe reads
  // as "the band, watching, over the field of feelings." In the fleet/RFC views every
  // node is drawn and labeled: front nodes a colored dot + label, the selected one an
  // eyeball, back-facing ones a muted dot.
  const bool feelView = (gViewDb == &gFeelDb);
  const int dotR = (int)(1.5f * gZoom) < 2 ? 2 : (int)(1.5f * gZoom);  // node dot scales w/ zoom (3 @ z1)
  c.setTextSize(1);
  for (int i = 0; i < gViewDb->recordCount(); ++i) {
    const TtdbRecord& r = gViewDb->record(i);
    if (!isNodeRecord(r)) continue;
    int sx, sy; float z;
    projectLL(r.lat, r.lon, R, cx, cy, sLat, cLat, sLon, cLon, sx, sy, z);
    uint16_t col = nodeColor(r.lat, r.lon);
    const bool isBand = feelView && gNodeMeshId[i] != 0;
    char id[28];
    if (isBand)                 bandLabel(i, id, sizeof(id));   // name + live status
    else if (gNodeName[i][0])   snprintf(id, sizeof(id), "%s", gNodeName[i]);
    else                        snprintf(id, sizeof(id), "@%d,%d", r.lat, r.lon);

    if (i == gSel || isBand) {
      drawEyeball(sx, sy, cx, cy, col, id);      // living eye (selected, or a band member)
    } else if (feelView) {
      int fr = dotR - 1 < 1 ? 1 : dotR - 1;
      if (z > 0) c.fillCircle(sx, sy, fr, rgb565(50, 56, 78));  // dim, unlabeled feeling
    } else if (z > 0) {
      c.fillCircle(sx, sy, dotR, col);                   // front node
      c.setTextColor(col);
      c.setCursor(sx + dotR + 2, sy - 3);
      c.print(id);
    } else {
      c.drawPixel(sx, sy, rgb565(60, 66, 78));           // back-facing indicator
    }
  }
}

// --- the record pane as an INTEROCEPTION view --------------------------------
// When the selected record on the mesh map names a live node, the bottom half stops being
// "the text of a belief record" and becomes that node's BODY: energy, heat, room to think,
// its own slowness, the band it hears, its clock. For our own record the numbers come from
// serviceIntero(); for anybody else they arrive as a 21-byte INTERO PERCEPT, so the console
// draws a remote body in its own idiom — the same reading, not the same pixels.
//
// Rendering follows the Cardputer's §4.5 discipline, which exists because TEXT is the
// expensive thing here: `Adafruit_GFX::drawChar` issues a write per glyph pixel, and a
// full-width readout measured ~20 ms on that node. So chrome (the labels, the bar frames) is
// painted once per entry, and every value is compared against WHAT IS ALREADY ON THE PANEL —
// on its rendered STRING, not its number — and skipped when it matches. A pane whose
// voltage still reads "4.02v" writes nothing for that row. Without this the pane would cost
// tens of milliseconds on the 1 Hz heartbeat, and the slowest loop pass is what the mesh
// feels as rtt (the edgesAt lesson, one screen up).
static const int IN_ROW_Y[3] = {148, 168, 188};
static const int IN_LBL_X  = 4;
static const int IN_VAL_X  = 32;
static const int IN_VAL_W  = 84;
static const int IN_BAR_X  = 122, IN_BAR_W = 192, IN_BAR_H = 14;
static const int IN_FILL_W = IN_BAR_W - 2, IN_FILL_H = IN_BAR_H - 2;
static const int IN_FOOT_Y = 210, IN_FOOT2_Y = 224;

static const uint16_t IN_COL_LBL   = rgb565(130, 145, 165);
static const uint16_t IN_COL_FRAME = rgb565(48, 62, 80);
static const uint16_t IN_COL_FOOT  = rgb565(140, 155, 175);
static const uint16_t IN_COL_GOOD  = rgb565(40, 210, 120);
static const uint16_t IN_COL_WARN  = rgb565(240, 175, 40);
static const uint16_t IN_COL_BAD   = rgb565(235, 60, 50);
static const uint16_t IN_COL_COOL  = rgb565(60, 190, 225);
static const uint16_t IN_COL_MIND  = rgb565(130, 145, 245);
static const uint16_t IN_COL_STALE = rgb565(120, 120, 130);

// What is currently on the panel, so a frame can write only the difference.
static char     gInVal[3][10] = {{0}, {0}, {0}};
static uint16_t gInCol[3] = {0, 0, 0};
static int      gInFill[3] = {-1, -1, -1};
static char     gInHead[54] = {0};
static char     gInFoot[54] = {0};
static char     gInFoot2[54] = {0};

// Forget the panel's contents: called on any pane/selection change, or the first frame
// after re-entry skips every element that "hasn't changed" and leaves a blank pane.
static void interoForget() {
  for (int i = 0; i < 3; ++i) { gInVal[i][0] = 0; gInCol[i] = 0; gInFill[i] = -1; }
  gInHead[0] = gInFoot[0] = gInFoot2[0] = 0;
}

// The chrome — labels and bar frames, everything that never changes.
static void interoChrome() {
  static const char* kLbl[3] = {"BAT", "DIE", "MEM"};
  gTft.setTextSize(1);
  gTft.setTextColor(IN_COL_LBL, ST77XX_BLACK);
  for (int i = 0; i < 3; ++i) {
    gTft.setCursor(IN_LBL_X, IN_ROW_Y[i] + 4);
    gTft.print(kLbl[i]);
    gTft.drawRect(IN_BAR_X, IN_ROW_Y[i], IN_BAR_W, IN_BAR_H, IN_COL_FRAME);
  }
}

// Repaint one gauge row, but only the parts that differ from the panel.
static void interoRow(int i, const char* val, uint16_t col, int pct) {
  if (col != gInCol[i] || strcmp(val, gInVal[i]) != 0) {
    gTft.fillRect(IN_VAL_X, IN_ROW_Y[i] - 1, IN_VAL_W, 17, ST77XX_BLACK);
    gTft.setTextSize(2);
    gTft.setTextColor(col);                    // transparent: the box is already black
    gTft.setCursor(IN_VAL_X, IN_ROW_Y[i]);
    gTft.print(val);
    gTft.setTextSize(1);
    snprintf(gInVal[i], sizeof(gInVal[i]), "%s", val);
  }
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  int w = (IN_FILL_W * pct) / 100;
  const int x = IN_BAR_X + 1, y = IN_ROW_Y[i] + 1;
  if (col != gInCol[i]) {                      // banded across: repaint the whole fill
    if (w) gTft.fillRect(x, y, w, IN_FILL_H, col);
    if (w < IN_FILL_W) gTft.fillRect(x + w, y, IN_FILL_W - w, IN_FILL_H, ST77XX_BLACK);
  } else if (w > gInFill[i]) {                 // grew: paint only the new part
    gTft.fillRect(x + gInFill[i], y, w - gInFill[i], IN_FILL_H, col);
  } else if (w < gInFill[i]) {                 // shrank: black out only what it lost
    gTft.fillRect(x + w, y, gInFill[i] - w, IN_FILL_H, ST77XX_BLACK);
  }
  gInFill[i] = w;
  gInCol[i] = col;
}

// Draw a line only when its text changed — and draw it the cheap way: one fillRect erase
// (a single address window for the whole box) then TRANSPARENT text, rather than drawWide's
// padded opaque print, which makes drawChar write a background pixel per glyph pixel too
// and costs ~3x for the same result. This matters because the footer's uptime changes every
// second, so this line is the one thing here that really does repaint on the heartbeat.
static void interoLine(int y, uint16_t col, const char* s, char* cache, size_t cap) {
  if (strcmp(s, cache) == 0) return;
  gTft.fillRect(0, y, 320, 8, ST77XX_BLACK);
  gTft.setTextSize(1);
  gTft.setTextColor(col);
  gTft.setCursor(IN_LBL_X, y);
  gTft.print(s);
  snprintf(cache, cap, "%s", s);
}

// The body of `id`, drawn in the record pane. `self` reads our own live sampler; anything
// else reads the last INTERO PERCEPT that node sent, with its AGE on screen — a body we
// heard about 40 s ago must not look live, and a node that never answered must say so
// rather than showing three zeroed gauges that look like a flat battery and a cold die.
static void renderIntero(int rec, uint32_t id) {
  const bool self = (id == kNodeId);
  const InteroSnapshot* s = nullptr;
  uint32_t age_s = 0;
  if (!self) {
    for (int i = 0; i < INTERO_PEERS; ++i)
      if (gIntero[i].node_id == id && gIntero[i].rx_ms) { s = &gIntero[i]; break; }
    if (s) age_s = (millis() - s->rx_ms) / 1000;
  }
  const bool stale = (!self && (!s || age_s > 12));    // ~4 missed polls
  char l[54], v[10];

  uint16_t bat_mv       = self ? gBatMv        : (s ? s->bat_mv : 0);
  uint8_t  bat_pct      = self ? (gBatSampled ? gBatPct : 255) : (s ? s->bat_pct : 255);
  int8_t   bat_trend    = self ? gBatTrend     : (s ? s->bat_trend : 0);
  int16_t  die_c10      = self ? gDieC10       : (s ? s->die_c10 : 0);
  uint16_t maxalloc_kb  = self ? (uint16_t)gMaxAllocK : (s ? s->maxalloc_kb : 0);
  uint32_t uptime_s     = self ? millis() / 1000 : (s ? s->uptime_s : 0);
  uint16_t worst_loop   = self ? (uint16_t)gWorstLoopMs : (s ? s->worst_loop_ms : 0);
  uint16_t beat_ms      = 0;
  uint32_t cond_id      = 0;
  bool     synced = false, conductor = false, voicing = false;
  if (self) {
#if USE_PULSE
    beat_ms = gPulse.chart().beat_period_ms;
    cond_id = gPulse.chart().conductor_id;
    conductor = gPulse.conductor();
    voicing = duetOn() || (gLocalPlay && !gPulse.conductor() &&
                           score::phraseForScene(kPart, gPulse.scene()) != nullptr);
#endif
    synced = gSynced;
  } else if (s) {
    beat_ms = s->beat_period_ms;
    cond_id = s->conductor_id;
    synced    = (s->flags & toot::INTERO_SYNCED) != 0;
    conductor = (s->flags & toot::INTERO_CONDUCTOR) != 0;
    voicing   = (s->flags & toot::INTERO_VOICING) != 0;
  }

  // Header: whose body, and how fresh. Deliberately NOT a per-second age readout — that
  // would repaint this line every frame for no information (we poll every few seconds, so
  // it would just count 0,1,2,0,1,2). Fresh reads "live"; only a body that has gone stale
  // states its age, and in 5 s buckets so even that line is mostly still.
  if (self)       snprintf(l, sizeof(l), "%s INTEROCEPTION   self", nodeName(id));
  else if (!s)    snprintf(l, sizeof(l), "%s INTEROCEPTION   asking...", nodeName(id));
  else if (!stale) snprintf(l, sizeof(l), "%s INTEROCEPTION   live", nodeName(id));
  else            snprintf(l, sizeof(l), "%s INTEROCEPTION   no reply %lus", nodeName(id),
                           (unsigned long)(age_s / 5 * 5));
  interoLine(BOTTOM_Y, stale ? IN_COL_STALE : nodeColor(gViewDb->record(rec).lat,
                                                        gViewDb->record(rec).lon),
             l, gInHead, sizeof(gInHead));

  // --- energy: volts + a measured trend arrow, and % of a 1S Li-ion curve. A pct of 255
  // means the node measured a voltage it refuses to call a state of charge (no pack on the
  // rail, or a divider ratio that does not hold) — so the bar stays EMPTY and the colour
  // goes neutral, rather than a 4.7 V charge rail reading as a beautifully full battery.
  if (!bat_mv) snprintf(v, sizeof(v), "--");
  else snprintf(v, sizeof(v), "%u.%02u%c", bat_mv / 1000, (bat_mv % 1000) / 10,
                bat_trend > 0 ? '^' : bat_trend < 0 ? 'v' : ' ');
  uint16_t bcol = (stale || !bat_mv || bat_pct == 255) ? IN_COL_STALE
                : (bat_pct > 50) ? IN_COL_GOOD : (bat_pct > 20) ? IN_COL_WARN : IN_COL_BAD;
  interoRow(0, v, bcol, bat_pct == 255 ? 0 : bat_pct);

  // --- heat: 20-80 C across the bar. The die idles in the forties with the radios up,
  // so a resting bar around a third is correct — a real climb then reads as one.
  if (!s && !self) snprintf(v, sizeof(v), "--");
  else snprintf(v, sizeof(v), "%d.%dC", die_c10 / 10, abs(die_c10 % 10));
  uint16_t tcol = stale ? IN_COL_STALE
                : (die_c10 < 450) ? IN_COL_COOL : (die_c10 < 600) ? IN_COL_WARN : IN_COL_BAD;
  interoRow(1, v, tcol, (int)((die_c10 / 10 - 20) * 100 / 60));

  // --- room to think: maxalloc, NOT free heap (which reads ~5x higher and refuses the
  // allocation anyway — companion.md §6). 64 KB is full scale.
  if (!s && !self) snprintf(v, sizeof(v), "--");
  else snprintf(v, sizeof(v), "%uK", maxalloc_kb);
  uint16_t mcol = stale ? IN_COL_STALE
                : (maxalloc_kb > 32) ? IN_COL_MIND : (maxalloc_kb > 16) ? IN_COL_WARN
                                                                        : IN_COL_BAD;
  interoRow(2, v, mcol, (int)(maxalloc_kb * 100 / 64));

  // Footer: uptime, the node's OWN slowness, and the band it hears. `lp` is the worst loop
  // pass in that node's current window — exactly what the mesh feels as rtt, which is why
  // it belongs on a body view rather than in a log nobody reads.
  if (!s && !self) {
    snprintf(l, sizeof(l), "no INTERO reply - node may predate CMD op 12");
  } else if (uptime_s < 3600) {
    snprintf(l, sizeof(l), "up %lum%02lus  lp%ums  %ubpm %s%s %s%s",
             (unsigned long)(uptime_s / 60), (unsigned long)(uptime_s % 60), worst_loop,
             beat_ms ? (unsigned)(60000UL / beat_ms) : 0,
             cond_id ? nodeName(cond_id) : "-", conductor ? "*" : "",
             synced ? "clk+" : "clk-", voicing ? " SINGING" : "");
  } else {
    snprintf(l, sizeof(l), "up %luh%02lum  lp%ums  %ubpm %s%s %s%s",
             (unsigned long)(uptime_s / 3600), (unsigned long)((uptime_s % 3600) / 60),
             worst_loop, beat_ms ? (unsigned)(60000UL / beat_ms) : 0,
             cond_id ? nodeName(cond_id) : "-", conductor ? "*" : "",
             synced ? "clk+" : "clk-", voicing ? " SINGING" : "");
  }
  interoLine(IN_FOOT_Y, stale ? IN_COL_STALE : IN_COL_FOOT, l, gInFoot, sizeof(gInFoot));

  // ...and keep the TTCP context the pane replaced: which record this body belongs to, and
  // how sure the map is of where it stands. The body view is still a view OF a record.
  const TtdbRecord& r = gViewDb->record(rec);
  snprintf(l, sizeof(l), "@LAT%dLON%d  sigma %.1fm   record %d/%d", r.lat, r.lon,
           gNodeSigmaM[rec], rec + 1, gViewDb->recordCount());
  interoLine(IN_FOOT2_Y, IN_COL_FRAME, l, gInFoot2, sizeof(gInFoot2));
}

// Bottom half — the selected record (title + first body lines), TTCP-RFC-0001 §5. On the
// mesh map a record that names a live node renders as that node's BODY instead (see
// renderIntero); the feelings and RFC globes keep showing record text, which is what those
// globes are for.
static void renderRecord() {
  if (gBottomDirty) {
    gTft.fillRect(0, BOTTOM_Y, 320, BOTTOM_H, ST77XX_BLACK);
    interoForget();
  }
  char l[54];
  if (gSel < 0 || gSel >= gViewDb->recordCount()) {
    drawWide(BOTTOM_Y, ST77XX_YELLOW, "(no record selected)");
    return;
  }
  if (gView == VIEW_FLEET && gNodeMeshId[gSel]) {
    if (gBottomDirty) interoChrome();
    renderIntero(gSel, gNodeMeshId[gSel]);
    return;
  }
  const TtdbRecord& r = gViewDb->record(gSel);

  // A new selection starts at the top of its record.
  static int lastSel = -2;
  if (gSel != lastSel) { lastSel = gSel; gRecPage = 0; }

  // Read the body. ⚠ This buffer was 520 B, which was NOT a scroll limitation but a READ
  // limitation: bytes past it never left flash. The RFC globe's records average 1036 B and
  // reach 2666 B, so the pane was silently showing the first 40% of a record with nothing
  // on screen to say so — and TTDB-RFC-0003's `opposes` (body offset 865) was physically
  // unreachable, which is what blocked the on-glass spec check. 3 KB covers every record
  // the fleet currently carries with headroom, and anything longer now says `+` in the
  // title rather than vanishing.
  if (!gBottomDirty) return;
  size_t off, len;
  if (!gViewDb->recordSpan(gSel, off, len)) return;
  static char body[3072];
  bool clipped = len > sizeof(body) - 1;
  size_t n = clipped ? sizeof(body) - 1 : len;
  n = gViewDb->readBytes(off, (uint8_t*)body, n);
  body[n] = 0;
  const char* p = strchr(body, '\n');       // skip the header line
  p = p ? p + 1 : body;

  // Wrap the whole body to screen width first, then draw only the requested page. Wrapping
  // every line (rather than stopping at the pane bottom) is what makes the page count
  // honest — the reader can see there IS more.
  const int kLineH = 10, kTop = BOTTOM_Y + 14;
  const int kPerPage = (240 - 8 - kTop) / kLineH;
  static const char* ls[128];
  static uint8_t ll[128];
  int nl = 0, col = 0;
  const char* start = p;
  while (*p && nl < 128) {
    if (*p == '\n') {                        // blank line -> small gap, new row
      if (col > 0) { ls[nl] = start; ll[nl] = (uint8_t)col; ++nl; }
      ++p; start = p; col = 0;
      continue;
    }
    ++col; ++p;
    if (col >= 52) { ls[nl] = start; ll[nl] = (uint8_t)col; ++nl; start = p; col = 0; }
  }
  if (col > 0 && nl < 128) { ls[nl] = start; ll[nl] = (uint8_t)col; ++nl; }

  int pages = (nl + kPerPage - 1) / kPerPage;
  if (pages < 1) pages = 1;
  gRecPages = pages;                        // published for the wrapping key handler
  if (gRecPage >= pages) gRecPage = pages - 1;
  if (gRecPage < 0) gRecPage = 0;

  snprintf(l, sizeof(l), "@LAT%dLON%d  rec %d/%d  pg %d/%d%s", r.lat, r.lon, gSel + 1,
           gViewDb->recordCount(), gRecPage + 1, pages, clipped ? "+" : "");
  drawWide(BOTTOM_Y, nodeColor(r.lat, r.lon), l);

  char line[54];
  int y = kTop;
  for (int i = gRecPage * kPerPage; i < nl && i < (gRecPage + 1) * kPerPage; ++i) {
    int c = ll[i] < 52 ? ll[i] : 52;
    memcpy(line, ls[i], c);
    line[c] = 0;
    drawWide(y, ST77XX_WHITE, line);
    y += kLineH;
  }
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
  // While a duet is on it replaces the scene name in the status bar: the scene is not what
  // this node is playing any more, and showing a scene it is ignoring would be a small lie.
  char duet[20] = {0};
  if (duetOn())
    snprintf(duet, sizeof(duet), "DUET>%s%s x%u", nodeName(gDuetPeer),
             gDuetRole == toot::DUET_LEAD ? "" : "(h)", gDuetSpeed);
  snprintf(l, sizeof(l), "T-DECK 0x%X %s sync%s drive>%s z%d %c %s", (unsigned)kNodeId,
           viewName(gView), gSynced ? "+" : "-", nodeName(gCmdTarget),
           gZoomIdx + 1, gPane == PANE_CONSOLE ? 'C' : 'M',
           duetOn() ? duet :
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
  gViewDb = (v == VIEW_RFC) ? &gRfcDb : (v == VIEW_FEELINGS) ? &gFeelDb : &gDb;
  parseNodeAttrs();                        // refill gNodeName/gNodeSigmaM/gNodeMeshId
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

// Trackball click: cycle to the next globe view (Feelings -> Semantic Position -> RFC),
// skipping any globe that never loaded. Remembers where the cursor was in the view we
// are leaving.
static void toggleGlobeView() {
  gViewSel[gView] = gSel;
  int nv = gView;
  for (int k = 0; k < VIEW_COUNT; ++k) {
    nv = (nv + 1) % VIEW_COUNT;
    if (nv == VIEW_RFC && !gRfcLoaded) continue;
    if (nv == VIEW_FEELINGS && !gFeelLoaded) continue;
    break;                                  // landed on a loadable view
  }
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
  if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO)) {
    // I2S comes up either way — the speaker must be ready for band notes and CMD_BEEP.
    // Only the boot signature is gated (STARTUP_TOOT, RobotTeamConfig.h): silent fleet.
#if STARTUP_TOOT
    playStartupToot();
#endif
  } else {
    Serial.println("I2S begin failed");
  }

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

  // Third globe: the feelings landscape with the band overlaid (the default power-up
  // view). View-only — like the RFC globe, it never joins the mesh or gets shared.
  if (gFeelDb.begin(LittleFS, kFeelTtdbPath)) {
    gFeelLoaded = true;
    Serial.printf("Feelings globe loaded: %u bytes, %d records\n",
                  (unsigned)gFeelDb.fileSize(), gFeelDb.recordCount());
  } else {
    Serial.println("Feelings globe (/feelings.ttdb.md) not found - fleet view default");
  }

#if USE_TDECK_HW
  // Seat the default globe: the feelings view on power-up (fall back to the fleet globe
  // if its TTDB is missing). Derives node labels, seats the cursor on the first navigable
  // record and centers on it with no boot animation (TTCP-RFC-0002 §6.1).
  activateView(gFeelLoaded ? VIEW_FEELINGS : VIEW_FLEET);
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

  // The time stream starts EMPTY, not with a stream of our own: this node listens for
  // TIMESTREAM_LISTEN_MS first (gTs.service), because joining an older stream is free
  // and forking one costs a merge. Independent of USE_PULSE — the band is optional, a
  // shared timeline is not.
  gTs.begin(kNodeId, &gDb, millis());

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

  // FIRST, before anything reads a clock: settle which timeline this node is on and
  // refresh gStamp. Every tier below stamps from that one snapshot, so records flushed
  // in the same pass carry the same instant rather than separate readings of a clock
  // that moved between them.
  gTs.service(millis());
  // Time this pass. The toot link is serviced once per loop pass, so the SLOWEST pass is
  // what the mesh feels as rtt — which makes `lp` on the interoception pane this node's own
  // sense of having gone sluggish, rather than something only the laptop can tell it.
  const uint32_t loop_t0 = millis();

#if USE_GPS
  gpsPoll();   // drain NMEA into the parser; the fix is read on CMD_GET_GPS (SP2)
#endif

  // Interior signals, on their own slow cadence (see serviceIntero: sampled here and not in
  // the renderer, so the STATUS temperature exists whether or not anyone is looking).
  serviceIntero(loop_t0);

  // Keep a live duet asserted over a lossy radio, and drain pending dismissals.
  serviceDuet(loop_t0);

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
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
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
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
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
  //   g = play (start the band)  x = stop (band AND duet)   SPACE = toggle console pane
  //   d = duet with the node currently selected on SemPos (we lead, they harmonise);
  //       press again to end. Contextual, so there is no separate partner to choose.
  //   o = onward (next scene of the hero's-arc song)   r = restart the tale (scene 0)
  //   1 / 2 = next / previous page of the selected record's body, both wrapping
  //           (title shows pg n/m)
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
        if (gZoomIdx < kZoomMax) { gZoomIdx++; gZoom = kZoomLevels[gZoomIdx]; }
        gGlobeDirty = true; gScreenDirty = true;
        break;
      case '-': case '_':                        // zoom out (further)
        if (gZoomIdx > 0) { gZoomIdx--; gZoom = kZoomLevels[gZoomIdx]; }
        gGlobeDirty = true; gScreenDirty = true;
        break;
      // Page through a long record body. Without these the pane shows only the first
      // ~10 wrapped lines of a record that may run to 2666 B, which is how TTDB-RFC-0003's
      // `opposes` clause stayed invisible on the glass. BOTH directions wrap: a record is
      // a small ring, and dead-ending at the last page just makes the reader press again
      // and wonder whether the key registered.
      case '1':                                        // forward, wrapping
        gRecPage = (gRecPage + 1) % (gRecPages > 0 ? gRecPages : 1);
        gBottomDirty = gScreenDirty = true;
        break;
      case '2':                                        // back, wrapping
        gRecPage = (gRecPage + (gRecPages > 0 ? gRecPages : 1) - 1)
                   % (gRecPages > 0 ? gRecPages : 1);
        gBottomDirty = gScreenDirty = true;
        break;
      case 'p': emitCmd(toot::CMD_PING, nullptr, 0); break;
      case 'b': { uint8_t a[4]; toot::put_u16(a, 880); toot::put_u16(a + 2, 200);
                  emitCmd(toot::CMD_BEEP, a, 4); break; }
      // Play/stop are band-wide: broadcast so ONE press starts/stops the whole fleet (+ our
      // part). `g` also arms the story to WALK ITSELF — the conductor auto-advances the
      // early scenes and holds at the grief; we (the roamer) bring the RETURN + FINALE, so
      // one press plays the song end to end with no further keys.
      case 'g': setLocalPlay(true);
#if USE_PULSE
                gPulse.armSong(heroarc::SCENE_ALONE, millis());
#endif
                emitCmdTo(toot::CMD_PLAY, NODE_BROADCAST, nullptr, 0); break;
      case 'x': setLocalPlay(false);
                endDuet();                     // stop means stop, duet included
#if USE_PULSE
                gPulse.disarmSong();
#endif
                emitCmdTo(toot::CMD_STOP, NODE_BROADCAST, nullptr, 0); break;
      // 'd' — DUET with whoever we are looking at. Contextual on purpose: the console is
      // already showing that node's body in the record pane, so "the node I am examining"
      // is an unambiguous referent and needs no target selection of its own. We take the
      // lead, the partner takes the harmony (both from HeroArc.h — the finale's pairing,
      // which is where this duet's two lines already live). Press again to end it.
      case 'd': {
        if (duetOn()) { endDuet(); break; }
        uint32_t peer = (gView == VIEW_FLEET && gSel >= 0) ? gNodeMeshId[gSel] : 0;
        if (!peer || peer == kNodeId) {
          // Say why nothing happened rather than sit silent: on the mesh map with a REMOTE
          // node selected is the whole precondition, and our own record is not a partner.
          logLine(peer == kNodeId ? "duet: that's us - pick another node"
                                  : "duet: select a node on SemPos first");
          gScreenDirty = true;
          break;
        }
        setDuet(toot::DUET_LEAD, peer, DUET_DEFAULT_SPEED);
        sendDuet(peer, toot::DUET_HARM, DUET_DEFAULT_SPEED);
        gDuetAsserted = millis();       // the re-assert timer starts from this first ask
        char lg[40];
        snprintf(lg, sizeof(lg), "duet with %s (we lead, x%u)", nodeName(peer),
                 gDuetSpeed);
        logLine(lg);
        Serial.printf("[duet] with %s 0x%08X: we LEAD, they HARMONISE, speed x%u\n",
                      nodeName(peer), (unsigned)peer, gDuetSpeed);
        gScreenDirty = true;
        break;
      }
#if USE_PULSE
      // Walk the hero's-arc story from the handheld: o = onward one scene (capped at
      // the finale — re-issuing the current scene is idempotent), r = back to the top.
      case 'o': {
        uint16_t next = gPulse.scene() + 1;
        if (next >= heroarc::SCENE_COUNT) next = heroarc::SCENE_COUNT - 1;
        emitSetScene(next);
        break;
      }
      case 'r': emitSetScene(0); break;
#endif
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
    // If WE somehow hold the baton (alone on the bench), walk the early scenes ourselves
    // and hold at the grief; normally a V4/K10 conducts and this is a no-op on us.
    gPulse.serviceSong(pnow, heroarc::SCENE_HOLD_MS, heroarc::SCENE_ORDEAL);

    // The chart's scene moved (or we just joined a band mid-song): this is the seam
    // where a node re-selects the phrase it plays, via score::phraseForScene. Parts
    // are still single-scene, so for now it only reports the move (and repaints, so
    // the console screen can show the band's place in the song).
    uint16_t new_scene;
    if (gPulse.sceneChanged(new_scene)) {
      gSceneEnteredMs = pnow;                 // restart our dwell timer for the new scene
      if (new_scene != heroarc::SCENE_ORDEAL) gTurnRequested = false;   // re-arm latches
      if (new_scene != heroarc::SCENE_RETURN) gFinaleRequested = false;
      Serial.printf("[scene] scene %u %s (era %lu cond 0x%08X)\n", new_scene,
                    heroarc::sceneName(new_scene),
                    (unsigned long)gPulse.chart().era,
                    (unsigned)gPulse.chart().conductor_id);
      gScreenDirty = true;
    }

    // Narrative driver — the roamer's return. When the song is on and we are locked to a
    // band that is holding at the ORDEAL (grief), dwell a moment, then call the RETURN;
    // once its harmony has played, call the FINALE. emitSetScene broadcasts (the conductor
    // applies it) AND sets it locally (if we conduct), so this works either way. Because
    // WE are the only actor that drives past the ORDEAL, the band waits at grief whenever
    // the T-Deck is absent — and a power-cycled T-Deck, once it re-locks and sees the grief
    // still held, picks up right here and brings the turn (gLocalPlay is restored from NVS).
    if (gLocalPlay && gPulse.playing()) {
      uint32_t dwell = pnow - gSceneEnteredMs;
      uint16_t sc = gPulse.scene();
      if (sc == heroarc::SCENE_ORDEAL && !gTurnRequested && dwell >= heroarc::ORDEAL_HOLD_MS) {
        emitSetScene(heroarc::SCENE_RETURN);
        gTurnRequested = true;
      } else if (sc == heroarc::SCENE_RETURN && !gFinaleRequested &&
                 dwell >= heroarc::RETURN_HOLD_MS) {
        emitSetScene(heroarc::SCENE_FINALE);
        gFinaleRequested = true;
      }
    }
    // The console's voice: the scene selects the phrase (HeroArc.h — silent until the
    // RETURN, harmony there, lead in the FINALE). On each new step, sound its note (if
    // playing) on the I2S speaker; toneI2S blocks ~PULSE_HARM_TONE_MS (deferred-tone
    // discipline, fine in loop()). Play only when the song is on AND we're locked to
    // the band as a FOLLOWER — while self-appointed (just rebooted, not yet re-locked)
    // we stay silent so the voice never plays out of phase; it resumes the moment we
    // adopt the conductor's chart. This is what makes a power-cycled T-Deck rejoin
    // cleanly. The step clock runs in silent scenes too, so entrances land on the grid.
    // A DUET overrides the phrase (and only the phrase): our role names the line, the scene
    // is ignored, and — unlike the song — we sound it even while holding the baton. The
    // conductor-silence guard exists so a just-rebooted, self-appointed node cannot play
    // out of phase against a band it hasn't found yet; that risk does not exist here,
    // because a conductor IS the phase reference and because an operator explicitly asked
    // for these two voices. Without this exception the duet would be a solo whenever the
    // console holds the baton — which, with the two handhelds alone on the bench, is
    // exactly what happens (0x200 is the lowest live id, so it conducts).
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
    // DOUBLE TIME lives entirely in these two lines: wrap the phrase in `steps/speed` slots
    // and look the note up at `sip*speed`. The pulse clock and the beat period are untouched
    // — the pair just covers the written phrase in half the steps, so it plays twice as fast
    // while staying locked to the beat the rest of the fleet is counting.
    // ONE stepTick per pass, whichever phrase is live: the call consumes the tick, so asking
    // twice would silently eat half the steps.
    const uint16_t steps = ph ? (uint16_t)(ph->steps / speed) : 16;
    uint16_t sip;
    uint32_t sc;
    static uint32_t prev_step = 0;
    static bool have_prev = false;
    if (gPulse.stepTick(pnow, steps, sip, sc)) {
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
        // Articulation scales with the speed, so double time is staccato rather than a
        // slur — and it halves the blocking duty cycle of a tone call that would otherwise
        // occupy 72% of every note slot (the loop carries the mesh; see `lp`).
        uint32_t ms = PULSE_HARM_TONE_MS / speed;
        if (ms < 80) ms = 80;
#if USE_TDECK_HW
        toneI2S((float)nt->freq, ms);
#endif
        Serial.printf("[part] step %2u/%u  %4uHz (%s x%u)\n", sip, steps, nt->freq,
                      duetOn() ? (gDuetRole == toot::DUET_LEAD ? "duet-lead" : "duet-harm")
                               : heroarc::sceneName(gPulse.scene()), speed);
      }
    }
  }
#endif

  // Periodic HELLO beacon + screen heartbeat.
  static uint32_t lastBeacon = 0;
  if (millis() - lastBeacon >= 2000) {
    lastBeacon = millis();
    uint8_t hb[timestream::ANCHOR_LEN];
    size_t hn = gTs.helloPayload(hb, sizeof(hb), millis());
    emit(toot::HELLO, hn ? hb : nullptr, hn, sendEspNow, nullptr);
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
  // Keep the selected node's BODY fresh while we are looking at it. Polled only while the
  // mesh map's record pane is showing a REMOTE node, so a live interoception view costs one
  // small toot each way every few seconds and stops the instant the operator navigates
  // away, opens the console pane, or switches to a globe that isn't the mesh.
  {
    static uint32_t lastPoll = 0;
    static int lastSel = -1;
    uint32_t want = (gPane == PANE_MAIN && gView == VIEW_FLEET && gSel >= 0)
                        ? gNodeMeshId[gSel] : 0;
    if (want == kNodeId) want = 0;                          // our own body needs no toot
    if (gSel != lastSel) { lastSel = gSel; lastPoll = 0; }   // ask a new selection at once
    if (want && (lastPoll == 0 || millis() - lastPoll >= INTERO_POLL_MS)) {
      lastPoll = millis();
      pollIntero(want);
    }
    // Report each remote body ONCE per node, from loop context (never the recv callback —
    // noteIntero only stores). Not for the operator, who can read the pane: this is so the
    // over-the-air leg is checkable from a serial tail, since the pane itself is the one
    // part of this feature that only eyes can confirm.
    static uint32_t announced[INTERO_PEERS] = {0};
    for (int i = 0; i < INTERO_PEERS; ++i) {
      if (!gIntero[i].node_id || !gIntero[i].rx_ms) continue;
      if (announced[i] == gIntero[i].node_id) continue;
      announced[i] = gIntero[i].node_id;
      Serial.printf("[intero] %s body: %umV %u%% | die %.1fC | maxalloc %uK | up %lus | "
                    "lp %ums\n", nodeName(gIntero[i].node_id), gIntero[i].bat_mv,
                    gIntero[i].bat_pct, gIntero[i].die_c10 / 10.0f,
                    gIntero[i].maxalloc_kb, (unsigned long)gIntero[i].uptime_s,
                    gIntero[i].worst_loop_ms);
    }
  }

  static uint32_t lastRender = 0;
  if (gScreenDirty || gGlobeDirty || millis() - lastRender >= 1000) {
    lastRender = millis();
    gScreenDirty = false;
    // On the feelings globe the band members carry live status (seen 2s / LOST / *cond),
    // so repaint the globe on the 1 Hz heartbeat to age it even without a nav change.
    if (gView == VIEW_FEELINGS) gGlobeDirty = true;
    renderScreen();
  }
#endif

  // Close the profiler window. Published every 10 s so `lp` reports a recent worst case
  // rather than a spike from boot that never clears — the same per-window discipline the
  // Cardputer's profiler uses.
  {
    uint32_t dt = millis() - loop_t0;
    if (dt > gLoopWorstRun) gLoopWorstRun = dt;
    static uint32_t windowStart = 0;
    if (millis() - windowStart >= 10000) {
      windowStart = millis();
      gWorstLoopMs = gLoopWorstRun;
      gLoopWorstRun = 0;
    }
  }
}
