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
#include <Pulse.h>    // band tempo (PULSE_DEFAULT_BEAT_MS) lives in Pulse.h — 120 BPM
#include <Score.h>
#include <HeroArc.h>  // shared story scenes + pacing (SCENE_ALONE/ORDEAL, SCENE_HOLD_MS)
#include <LinkPercept.h>  // SP0: link-percept histograms -> @LAT97 records
#include <BleLink.h>      // SP0 near-range tier: BLE advert+scan (K10's FIRST direct percept)
#include <EntityPercept.h>  // SP0 entity tier: WiFi BSSID sightings -> @LAT96 percepts
#include <MotionPercept.h>    // SP0 motion tier: the K10's tilt -> @LAT95 still|moving, @LAT93
#include <AcousticPercept.h>  // SP0 acoustic tier: the K10's mic -> @LAT94 (the fleet's 2nd ear)
#include <TimeStreamNode.h>  // the team time stream -> @LAT90 (a timeline the fleet owns)
#include <LaneGenNode.h>     // @LAT100: a prune writes down the boundary it creates
#include <RobotTeamConfig.h>

// The three faces this node can show (CMD_SET_VIEW). Declared UP HERE, far from the
// renderers that use it, for one Arduino-specific reason: arduino-cli auto-generates
// prototypes for every function in the .ino and inserts them near the top of the file,
// so a function taking a type defined mid-sketch fails to compile against its own
// generated prototype. Any enum used as a PARAMETER type has to be declared before that
// insertion point. (Learned on the Cardputer, where `enum FaceView` sits in the same
// place for the same reason.)
enum K10View : uint8_t {
  K10_VIEW_EYE = 0,      // the resting face — screen-filling eyeball (the DEFAULT)
  K10_VIEW_STATUS = 1,   // identity, TTDB, band, cursor: what the old canvas screen said
  K10_VIEW_SENSES = 2,   // the two new organs, as instruments: tilt and mic
  K10_VIEW_COUNT = 3,
};

// Real UNIHIKER K10 onboard hardware (DFRobot `unihiker_k10` library). Set to 0
// to fall back to a serial-only mock if the library/board package isn't
// installed yet. API verified against the UNIHIKER K10 Arduino wiki:
//   temperature: aht20.getData(AHT20::eAHT20TempC)
//   RGB LED:     k10.rgb->write(-1, 0xRRGGBB)  /  k10.rgb->brightness(0..9)
#define USE_K10_HW 1
#if USE_K10_HW
#include "unihiker_k10.h"
#include <driver/i2s.h>   // direct I2S_NUM_0 access for the fleet square-wave voice (k10Tone)
static UNIHIKER_K10 k10;
static AHT20 aht20;
// Speaker: driven directly via k10Tone() (I2S_NUM_0, installed by k10.begin()->initI2S).
// We deliberately do NOT use DFRobot's Music::playTone — it is a fixed full-scale sine
// with no volume control; the fleet's voice is a square wave at a chosen amplitude.
//
// --- THE PANEL IS DRIVEN DIRECTLY, NOT THROUGH THE DFRobot CANVAS (2026-08-12) -------
//
// `k10.canvas` is an LVGL canvas, and every `lv_canvas_draw_*` call invalidates the
// WHOLE object — so each `updateCanvas()` flushes all 240x320 px. At this panel's 20 MHz
// that is 153,600 B ≈ 61 ms of SPI before LVGL has blended anything, i.e. ~70 ms of
// stall per frame. Fine for a 1 Hz text screen (which is all it ever did); hopeless for
// an eye, and it would wreck the band's step clock and the mesh's rtt on the way past.
//
// So the K10 joins the two handhelds in writing the display itself and repainting ONLY
// the pixels that changed — the same discipline, and the same reason, as the Cardputer's
// representor. `gTft` is a SECOND TFT_eSPI instance alongside the one inside the DFRobot
// library; that is safe because nothing here ever calls `lv_task_handler()` again after
// `initScreen()` (it runs only inside canvas ops, `setScreenBackground` and the camera
// task, none of which we use), so LVGL never touches the panel and there is exactly one
// writer. `creatCanvas()` is deliberately NOT called — it would allocate 1.2 MB of PSRAM
// for a buffer nothing draws into.
//
// ⚠ NO `#include <TFT_eSPI.h>` HERE, ON PURPOSE. `unihiker_k10.h` already includes it by
// RELATIVE path (`"../TFT_eSPI/TFT_eSPI.h"`, the core-bundled 2.5.34 header) while
// arduino-cli compiles the SKETCHBOOK copy (2.5.43) — an asymmetry that predates this
// file and demonstrably works. Adding an angle-bracket include would give this
// translation unit a different header from the one the DFRobot library's own `tft` was
// compiled against, which is how a class-layout mismatch gets built. Inherit the include
// the board library already made and the two instances stay identical.
static TFT_eSPI gTft = TFT_eSPI(240, 320);
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
toot::Reassembler gReasm;   // chunked-toot reassembly (TTN-RFC-0007 §6)
TootSerialLink gSerial(Serial);
Agent32 gAgent(&gDb);

// SP0 link percepts (semantic positioning). The K10's 2.x ESP-NOW recv callback carries
// no RSSI (why its ESP-NOW percept capture was deferred), so this histogram is fed ONLY
// by the BLE near-range tier below — giving the K10 its first DIRECT proximity percept
// (until now it was only OBSERVED by the 3.x nodes). Flushed to @LAT97 from loop().
static linkpercept::Log gLinkLog;
// K10 BLE is DISABLED: the DFRobot UNIHIKER 2.x core cannot run BLE + WiFi (ESP-NOW)
// concurrently — BLEDevice::init() aborts in coex_core_enable (WiFi/BT software
// coexistence is not enabled in its prebuilt SDK). Verified on hardware 2026-07-10:
// USE_BLE 1 crash-loops (abort on core 1 during setup). The K10 stays ESP-NOW-only and
// is mapped one-directionally by the 3.x nodes hearing it. Needs a 3.x core to enable.
#define USE_BLE 0
#if USE_BLE
// Called from the BLE scan task for each key-verified fleet advert (BleLink parses the
// raw payload, so no per-advert heap allocation — the T-Deck OOM lesson). add() is
// increment-only, safe off-task.
static void onBleObserve(uint32_t peer, int rssi) {
  gLinkLog.add(peer, rssi, linkpercept::PROTO_BLE);
}
#endif

// SP0 entity tier: duty-cycled WiFi scan logging visible BSSIDs (@LAT96 lane). Unlike
// BLE, a WiFi scan is pure WiFi — it does NOT need the BT coexistence the 2.x core
// lacks — so this is the K10's FIRST direct positioning percept (it already runs
// WIFI_STA for ESP-NOW). The ~2 s async scan hops channels, so it's kept rare and the
// ESP-NOW channel is re-asserted after. Default off until flashed + serial-verified.
#define USE_WIFI_SCAN 1
#define WIFI_SCAN_PERIOD_MS 600000UL   // one ~2 s scan every 10 min

#if USE_WIFI_SCAN
static entitypercept::Log gEntityLog;
static uint32_t gLastScanKick = 0;
static bool gScanRunning = false;

// Non-blocking duty-cycled WiFi scan (see v4a_bridge.ino for the rationale).
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
uint32_t gSeq = 1;

// --- wall clock (TTN-RFC-0008) ----------------------------------------------
// No RTC: synthesize epoch ms from millis() + an offset adopted on TIME_SYNC.
// Unsynced until the first TIME_SYNC; exactly-once adoption is gated on a
// monotonic sync_id (not transport dedup), so the un-deduped paths stay correct.
// --- the team time stream (TimeStreamNode.h) --------------------------------
// gTs owns BOTH facts now: which shared timeline this node is on, and whether that
// timeline knows the date. The old single `synced` bit could only ever answer the
// second, and answered it "no" for a fleet in perfect agreement with itself. The
// macros keep every reader below reading the way it always did; the difference is
// that they are callback-safe scalars refreshed once per loop(), never live reads of
// an engine the WiFi task must not touch.
static timestream::Node gTs;
#define gStamp         (gTs.stamp())
#define gStreamWallSec (gTs.wallSec())
#define gSynced        (gTs.wall())
#define gClockOffsetMs (gTs.clockOffsetMs())
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return gTs.nowEpochMs(); }

// A TIME_SYNC adopts the offset in the recv path (for timing accuracy) but defers
// the TTDB log-append to loop() (flash write + re-index, like the TTDB reply).
static volatile bool gSyncPending = false;
static uint32_t gPendSyncId = 0;
static uint64_t gPendEpochMs = 0;
static uint32_t gPendRecvMs = 0;

// Laptop CMD override of the indicator LED (companion.md §4b). When enabled, the
// loop paints this color after the agent acts, so the orchestrator's set-led wins
// over the local warm/cool indicator until a clear-led (or reboot).
static struct {
  bool enabled = false;
  uint32_t color = 0;
} gLedOverride;

// Deferred beep (CMD_BEEP): k10Tone() blocks ~dur_ms, so it must NOT run in the
// recv callback (WiFi task). handleToot stashes it (after ACK) and loop() plays it.
static volatile bool gBeepPending = false;
static int gBeepFreq = 0;
static uint32_t gBeepMs = 0;   // tone duration in ms (k10Tone streams SAMPLE_RATE*ms/1000 samples)

// --- fleet pulse + this node's PART (TTN-RFC-0010) ---------------------------
// The band time-base + conductor election lives in the portable Pulse engine; the
// shared grid is ~1 Hz. The ~50 ms tolerance is musical swing: each note lands a small
// humanize jitter after its step so the line breathes.
#define USE_PULSE 1
static pulse::Engine gPulse;
static const int      PULSE_TONE_MS = 180;       // staccato note (k10Tone blocks; keep short)
static const uint32_t PULSE_LED_MS = 160;        // note LED hold
static const uint32_t PULSE_HUMANIZE_MS = 6;     // jitter so the line breathes

// THE K10 IS BACK ON THE BAND ROSTER (2026-08-12), and rejoining meant deleting a tune
// rather than writing one. It used to carry a private `kLeadNotes` table — bare Ode to
// Joy on a loop, played in every scene — which was the right thing when it was the only
// pitched instrument in a fleet that had no story yet. It is the wrong thing now: the
// hero's arc is authored ONCE in HeroArc.h and every other member reads its line out of
// that table, so a node with its own copy of the melody is a node that cannot be silent
// when the score says silence and cannot follow when the score is revised.
//
// `heroarc::kPercept` was written on 2026-07-29 against the day this happened ("defined
// now so rejoining is a reflash, not a rewrite"). Taking it means the K10 is silent
// through ALONE..RETURN and enters on the FINALE harmony under the T-Deck's lead — and
// the silence is the part, not a broken speaker. The step clock runs through it either
// way, so the entrance lands on the grid.
static const score::Part& kPart = heroarc::kPercept;

// --- the duet: two nodes, by name, on the shared clock (CMD_DUET) -------------------
// Being invited into a duet overrides this node's PART for as long as it lasts. Not a
// chart scene (a scene is band-wide and would pull in every powered member; see Toot.h)
// and not persisted — the invitation belongs to the moment the console asked. Same shape
// as the other four nodes' copy, deliberately: the fifth should stay comparable line for
// line with the four it was ported from.
static uint8_t  gDuetRole = toot::DUET_OFF;
static uint32_t gDuetPeer = 0;
static uint8_t  gDuetSpeed = 1;      // 1 = as written, 2 = double time (set by the inviter)
static inline bool duetOn() { return gDuetRole != toot::DUET_OFF; }

// Can this phrase be taken at `speed`? Double time traverses the SAME note table in half
// as many steps, so every note must still land on a step the sequencer visits (noteAt is
// an exact match). Refuse rather than silently drop a note — kOdeLead's tied note at step
// 54 is exactly that case at ÷4. Computed once when a duet is set up, not per step.
static uint8_t validDuetSpeed(const score::Phrase& ph, uint8_t speed) {
  if (speed < 1) return 1;
  if (speed > toot::DUET_SPEED_MAX) speed = toot::DUET_SPEED_MAX;
  if (ph.steps % speed) return 1;
  for (uint16_t i = 0; i < ph.count; ++i)
    if (ph.notes[i].step % speed) return 1;
  return speed;
}

// Enter/leave a duet, validating the inviter's speed against the phrase our role names.
// Both voices must land on the same speed or they cover the phrase at different rates and
// come apart — which is why the inviter sends it rather than each side deciding.
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

// Apply a CMD_DUET payload. Roles ride on the wire, so nothing here assumes who invited
// whom. The inviter RE-ASSERTS a live duet every couple of seconds (a single ESP-NOW
// invitation gets dropped), so log only on a real change: an otherwise-identical repeat
// is the mechanism working, not noise worth printing.
static bool applyDuetCmd(const toot::Toot& t) {
  if (t.payload_len < 10) return false;
  uint32_t partner = toot::get_u32(t.payload + 5);
  uint8_t role = t.payload[9];
  // The speed byte is additive: a sender that predates it means "as written", the same
  // discipline the STATUS and PULSE tails use.
  uint8_t speed = (t.payload_len >= 11) ? t.payload[10] : 1;
  bool changed = (role != gDuetRole) || (gDuetSpeed != speed);
  setDuet(role, partner, speed);
  if (changed)
    Serial.printf("[duet] %s by 0x%08X (speed x%u)\n",
                  role == toot::DUET_OFF ? "dismissed"
                  : role == toot::DUET_LEAD ? "invited to LEAD" : "invited to HARM",
                  (unsigned)partner, gDuetSpeed);
  return true;
}

// Draw the melody on the RGB LED: pitch -> color (low warm, high cool).
static uint32_t pitchColor(uint16_t f) {
  if (f >= score::E5) return 0x3040FF;  // high — blue
  if (f >= score::C5) return 0x00E0FF;  // teal
  if (f >= score::G4) return 0x00FF40;  // green
  if (f >= score::E4) return 0xC0FF00;  // yellow-green
  if (f >= score::D4) return 0xFFA000;  // orange
  return 0xFF2000;                      // low — red
}

// A struck note is rendered after a humanize delay (deferred; k10Tone blocks).
static bool     gHitPending = false;
static uint32_t gHitDueMs = 0;
static int      gHitFreq = 0;
// Articulation scales with the duet speed so double time stays staccato instead of
// slurring into the next slot — carried on the hit because `speed` is only in scope
// where the note is chosen.
static uint32_t gHitMs = 0;
static uint32_t gHitColor = 0;
static uint32_t gLedClearMs = 0;     // 0 = LED not currently flashing
// The melody boots SILENT and only plays between CMD_PLAY and CMD_STOP (the T-Deck's
// g/x keys, or `companion.py cmd --op play/stop`). The step clock keeps running while
// stopped so the K10 stays in band phase; only the audible/LED hit is muted.
static bool     gPlayEnabled = false;
// Conductor fast-lock (§4.2): only beacon when a *new* neighbor appears, not every HELLO.
static uint32_t gNeighbors[8] = {0};
static uint32_t gNeighborSeen[8] = {0};
static int      gNeighborCount = 0;
// Fast-lock a neighbor that is brand-new OR returning after a gap (a power-cycle): as the
// conductor we then beacon immediately so the (re)joiner locks within a round trip instead
// of waiting up to PULSE_RESYNC_PERIOD for the next scheduled beacon. A steadily-present
// neighbor (HELLO ~every 2 s) does NOT retrigger it, so steady-state traffic stays minimal.
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
static inline uint32_t pulseHumanize() {  // small bounded jitter, cheap LCG
  static uint32_t s = 0x1234567u;
  s = s * 1664525u + 1013904223u;
  return (s >> 8) % (2 * PULSE_HUMANIZE_MS + 1);  // 0..2H -> centered below
}

// ============================================================================
// THE K10's TWO NEW SENSES (2026-08-12): the tilt and the microphone
// ============================================================================
//
// Both organs have been on this board since it arrived and neither was ever read. The
// K10 was the fleet's first node and the ONLY tier it ever authored for itself was the
// @LAT96 WiFi scan — LinkPercept was fed by a BLE radio the 2.x core cannot run
// (USE_BLE 0), so @LAT97 has always been empty here. It was, in the fleet's own words,
// a node that could only be OBSERVED.
//
// Reading these two changes something specific rather than adding decoration:
//
//   TILT (@LAT95/@LAT93) — until now the Cardputer was the fleet's ONLY stillness
//   witness, which is why `FACE_BELIEF` is Cardputer-only "structurally" (CLAUDE.md):
//   PerceptLearn Rule 1 arms solely off a still @LAT95 window. A second accelerometer
//   makes "the observer held still" checkable on a second node, and makes it checkable
//   on the one node that never moves.
//
//   MICROPHONE (@LAT94) — the Cardputer was the fleet's ONLY ear, and that single fact
//   is why Phase 3 TDoA is unexercised: one microphone cannot measure a time DIFFERENCE
//   of arrival. Two can. This does not perform TDoA — nothing on a node interprets a
//   percept — but it is the first time two nodes in this fleet can independently
//   timestamp the same clap on a shared clock, which is the whole precondition.
//
// ⚠ Neither tier is a display feature, and neither is gated on the screen. The eye reads
// them, but they run whether the eye is showing or not — a percept whose cadence depends
// on which view is up would be a percept the display gets a vote in.
//
// --- THE INDEX BUDGET, BECAUSE THIS NODE JUST WENT FROM ONE GROWING LANE TO FOUR -----
//
// `TTDB_MAX_RECORDS` (288) is a WHOLE-FILE budget every lane shares, and the per-lane caps
// deliberately over-subscribe it. Overflowing it is not a graceful degradation: records
// past the cap are invisible to every reader, and a lane prune walks the INDEX. So the
// arithmetic belongs here, next to the lanes that changed it, rather than in a commit
// message:
//
//   identity            2   (@LAT0LON0, @LAT10LON0 — fixed)
//   @LAT90  timeline   16   TIMESTREAM_MAX_LANE     (a stream change, not a period)
//   @LAT93  transition 32   MOTIONPERCEPT_MAX_TRANSITION_LANE  (only on a verdict flip)
//   @LAT94  acoustic   48   ACOUSTICPERCEPT_MAX_LANE  <- FILLS FIRST, in ~48 MINUTES:
//                           unlike @LAT95/@LAT96 it is NOT change-triggered, so every
//                           60 s window writes a record whether or not anything happened
//   @LAT95  motion     48   MOTIONPERCEPT_MAX_LANE  (change-triggered: ~24 h on a shelf)
//   @LAT96  entity     48   ENTITYPERCEPT_MAX_LANE  (change-triggered, 10-min scans)
//   @LAT97  link       48   LINKPERCEPT_MAX_LANE — UNREACHABLE on this board: its only
//                           feeder is BLE and USE_BLE is 0 (the 2.x core cannot run
//                           BLE + WiFi). Counted as 0, and that is a fact about THIS
//                           build, not about the cap.
//   @LAT100 lanegen    32   LANEGEN_MAX_LANE (one marker per prune, an operator action)
//   @LAT98/@LAT99      uncapped, but they only grow when the laptop pushes or syncs
//                        --------
//   reachable total    226 of 288, ~62 slots of margin for the sync/belief lanes.
//
// It fits, and the boot banner prints the live headroom + a saturation warning either
// way, because arithmetic done once at design time is not a substitute for the node
// saying what it actually holds. If a lane cap is ever raised here, redo this sum first:
// the whole point of the 2026-08-09 defect is that the per-lane check passes while the
// file-wide one is what silently deletes records.

// --- TILT: SC7A20H accelerometer, read by the board library's own 10 Hz task ---------
#define USE_TILT 1
#if USE_TILT
static motionpercept::Log gMotionLog;    // @LAT95 was-this-node-still

// The DFRobot library's `gesture_task` polls the chip every 100 ms and publishes
// k10.accX/Y/Z. We do NOT poll faster: those members ARE the sample rate available, so
// 10 Hz is the tier's rate and the eye's rate both. (The Cardputer runs its IMU at 50 Hz
// for the face and 20 Hz for the tier; here the board decides, and saying so beats
// pretending to a rate we cannot reach.)
static const uint32_t TILT_POLL_MS = 100;

// Raw counts -> milli-g. The chip is an LIS2DH-compatible part left at its reset
// full-scale (the library writes 0x21/0x22/0x24/0x30/0x32/0x33 and never touches 0x23,
// so FS = +/-2 g) and the library right-shifts the 16-bit registers by 4, giving 12-bit
// samples. At +/-2 g / 12 bit that is 1 mg per count.
//
// ⚠ THAT IS A DERIVATION, NOT A MEASUREMENT, so the node CHECKS IT OUT LOUD at boot: a
// board at rest must read |a| ~= 1000 mg. If the banner says 500 or 2000, this constant
// is wrong by that factor and every `dev_mg` in the @LAT95 lane is wrong with it — which
// would be invisible from the record, because a scaled threshold and a scaled signal
// still label windows plausibly (the "a lane's own label is not evidence" trap).
static const float TILT_MG_PER_LSB = 1.0f;

// --- THE REST-MAGNITUDE NULL, AND WHY @LAT95 NEEDED ONE (measured 2026-08-12) --------
//
// The check above PASSED and the tier was still wrong, which is the interesting part.
// First hardware run: `|a| 1069 mg` at the rest pose — 6.9% high, comfortably "about
// 1000", so TILT_MG_PER_LSB is right to within the part's spec. But `MotionPercept`
// scores `dev = | |a| - 1000 |` against **MOTIONPERCEPT_MOVING_MG 60**, and that 60 was
// MEASURED ON THE CARDPUTER'S BMI270 (see MotionPercept.h: "prune, then collect", p90
// 33 mg). A 69-87 mg STATIC error therefore sails straight over the line, and the very
// first window this node ever wrote said:
//
//     **MOTION** state:moving moving_permille:1000 dev_mean_mg:87 dev_max_mg:99
//
// ...about a picture frame sitting untouched on a desk. Not a noisy verdict — a
// CONFIDENT FALSE ONE, in the one lane whose entire job is to make "the observer held
// still" checkable rather than assumed. A tier that always says `moving` is worse than a
// tier that is switched off, because the records look like evidence.
//
// ⚠ THE FIX IS NOT TO RAISE THE THRESHOLD. `MOTIONPERCEPT_MOVING_MG` is a shared library
// default carrying a real measurement from a different chip; moving it here would move it
// for the Cardputer too and silently redefine that node's four-week-old lane.
//
// Instead the SKETCH normalises what it feeds the tier: each sample is scaled so that the
// magnitude this board reads AT REST maps to exactly 1000 mg. The library's `|mag - 1000|`
// then measures departure from *this board's own rest*, in normalised mg, and the 60 mg
// threshold recovers the meaning it was measured to have — a fraction of g, not a count.
//
// ⚠ WHAT THIS DOES AND DOES NOT CLAIM. A single-pose scalar CANNOT separate the part's
// gain error from its per-axis zero-g offset; a six-pose calibration would, and nothing
// here is one. It does not need to be: the null is re-derived at every adopted rest pose,
// so whatever mixture of gain and offset the pose produces is measured in that pose, and
// a frame set down at a new angle re-nulls there. That is a NULL, not a calibration, and
// it is only trustworthy near the pose it was taken in — which is where this board lives.
//
// ⚠ AND IT WEAKENS THE TIER'S INDEPENDENCE, WHICH THE NOTE BELOW USED TO DENY. Re-nulling
// the MAGNITUDE is not the same mistake as re-referencing the DIRECTION (that one would
// be fatal), because a node moving at constant velocity reads exactly 1 g and is already
// indistinguishable from rest by any magnitude test, corrected or not. What it does cost:
// a node that spends the whole 20 s adoption window under a steady non-gravity
// acceleration would null against it. Nothing in this fleet can do that for 20 s.
//
// 📎 The honest long answer is still MotionPercept.h's protocol — prune, collect an hour
// of genuinely untouched windows, look at the distribution, and set the number from it.
// This makes the tier tell the truth today; it does not make that measurement unnecessary.
static const float REST_MAG_MG = 1000.0f;     // what a rest magnitude is normalised TO
// Refuse the null outside this band: a "rest" magnitude this far from 1 g means the board
// was NOT at rest when it was taken (or the scale really is wrong), and a null derived
// from motion is worse than none. Outside it the sketch keeps scale 1.0 and says so.
static const float REST_MAG_MIN_MG = 700.0f;
static const float REST_MAG_MAX_MG = 1400.0f;
static float gRestScale = 1.0f;               // 1.0 until a rest pose has been measured
static bool  gRestScaleKnown = false;

// --- THE RESTING POSE IS A LEAN, NOT A LEVEL ----------------------------------------
//
// The K10 stands like a picture frame: tipped back on its foot, not lying flat and not
// upright. So gravity at rest is a DIAGONAL vector, and "no tilt" is that vector — not
// (0,0,1) and not (0,0,-1). Every naive eye written against this board would gaze
// permanently at the floor, and be right to, because the board really is leaning.
//
// The fix is that the reference is MEASURED rather than assumed: the eye looks straight
// ahead when the board is in whatever pose it has been left in, and the gaze is the
// DEPARTURE from that pose. Two arms:
//
//   1. At boot, after a settle, the first stable still stretch becomes the reference.
//   2. Thereafter, a NEW pose held still for RECENTER_HOLD_MS becomes the new reference.
//      This is not drift-correction dressed up — it is the same claim the picture-frame
//      note makes: straight-ahead is defined by how the frame is standing, so a frame
//      set down at a new angle has a new straight-ahead. A transient tip moves the gaze
//      and springs back; a deliberate reposition is adopted.
//
// The motion tier's DIRECTION is never re-referenced — that would make a node carried at
// a steady angle report `still`, the exact assumption the tier exists to falsify. Its
// MAGNITUDE null is re-derived here, and the difference between those two statements is
// argued in full at REST_MAG_MG above; it is not a loophole in this one.
static const uint32_t TILT_SETTLE_MS = 1500;      // ignore the first samples after boot
static const uint32_t RECENTER_HOLD_MS = 20000;   // a new pose held this long becomes rest
static const int      RECENTER_STILL_MG = 120;    // how close two samples must be to count
static const float    TILT_LP = 0.20f;            // low-pass: answer a lean, not a tremor

static int   gAccX = 0, gAccY = 0, gAccZ = 0;         // last raw counts
static float gTiltX = 0, gTiltY = 0, gTiltZ = 0;      // low-passed, milli-g
static float gRestX = 0, gRestY = 0, gRestZ = 1000;   // the picture-frame pose
static bool  gRestKnown = false;
static bool  gTiltOk = false;                         // has the chip ever answered?
#endif

// --- what the FACE reads, kept outside both sensor guards ----------------------------
// The gaze and the arousal are DISPLAY quantities that happen to be fed by the tilt and
// the mic. Declaring them inside `#if USE_TILT` / `#if USE_MIC` would make the eye fail to
// compile the moment either organ is switched off for a bring-up — and an eye that stares
// straight ahead with a flat pupil is the correct rendering of a node with no senses, not
// a build error. Left at their neutral values when nothing writes them.
static float gGazeX = 0, gGazeY = 0;   // -1..1, where the eye is looking (0,0 = ahead)
static float gArousal = 0.0f;          // 0..1, how wide the pupil is (0 = at rest)

// --- MICROPHONE: I2S_NUM_0 RX, the same port the speaker transmits on ----------------
#define USE_MIC 1
#if USE_MIC
static acousticpercept::Log gAcousticLog;   // @LAT94 what it heard

// The board library installs I2S_NUM_0 as MASTER|RX|TX at 16 kHz, 16-bit, stereo
// (initI2S). We do not reconfigure it: k10Tone already borrows the same port to speak,
// and a second configuration would fight it.
//
// ⚠ RX AND TX SHARE ONE CLOCK ON THIS PORT. `k10Tone` sets the sample rate to 8 kHz for
// the duration of a note and restores it — so a mic block read across a tone is sampled
// at the wrong rate AND is mostly our own speaker. Both are handled by muting the tier
// around a tone rather than by trying to filter it out: the acoustic lane's transient
// timestamp is a TDoA datum, and the node's own voice arriving at its own mic is exactly
// the false event that would poison it (the Cardputer learned this as REC_FLAG_SELF).
static const int    MIC_RATE = 16000;
static const size_t MIC_TIER_FRAMES = 128;      // what @LAT94 sees — matches the Cardputer's
static const size_t MIC_READ_FRAMES = 256;      // stereo frames per i2s_read
static const uint32_t MIC_POLL_MS = 16;         // ~4 blocks of DMA behind, never blocking
static const uint32_t MIC_SELF_MUTE_MS = 120;   // after our own voice stops, before we listen

static int16_t gMicCarry[MIC_READ_FRAMES + MIC_TIER_FRAMES];  // mono, awaiting a full block
static size_t  gMicCarryN = 0;
static uint32_t gToneUntilMs = 0;    // our own speaker is sounding until here
static int32_t  gMicLevel = 0;       // last block RMS — what the eye reads as loudness
static bool     gMicOk = false;      // has a read ever returned samples?
#endif

// --- pushed belief (TTN-RFC-0009) -------------------------------------------
// The companion re-authors fleet knowledge and pushes it back as offset-addressed
// TTDB_PUT slices, written to a SEPARATE file (never the live TTDB). On a
// CRC-verified commit the node appends a BELIEF-ADOPTED record to its own live TTDB
// — self-attestation that it integrated exactly those bytes. Exactly-once on a
// monotonic belief_id (like the sync_id gate), so the un-deduped USB/bridge path
// can retransmit a lost slice without double-adopting.
static const char* kBeliefPath = "/belief.md";
static bool gBeliefAdopted = false;   // committed at least one belief
static uint32_t gBeliefId = 0;        // last adopted belief id
static bool gPutActive = false;       // a transfer is mid-stream
static uint32_t gPutId = 0, gPutTotal = 0, gPutCrc = 0, gPutNext = 0, gPutCrcRun = 0;
// The live-TTDB BELIEF-ADOPTED append is deferred to loop() (flash write + re-index).
static volatile bool gBeliefSyncPending = false;
static uint32_t gPendBeliefId = 0, gPendBeliefBytes = 0, gPendBeliefCrc = 0;
static uint32_t gPendBeliefRecvMs = 0;

// Parse the behavioral DIRECTIVE from /belief.md (TTN-RFC-0009 §5.2): the
// `**DIRECTIVE** sense_interval_ms:<N>` the node should adopt. Returns N, or 0 if the
// belief carries no directive. The belief is ~1 KB; read the head into a fixed buffer
// (the directive sits near the top) and scan — no String, no whole-file slurp.
static uint32_t parseBeliefDirective() {
  File f = LittleFS.open(kBeliefPath, "r");
  if (!f) return 0;
  static char buf[1536];
  size_t n = f.read((uint8_t*)buf, sizeof(buf) - 1);
  f.close();
  buf[n] = '\0';
  const char* key = "**DIRECTIVE** sense_interval_ms:";
  const char* p = strstr(buf, key);
  return p ? (uint32_t)strtoul(p + strlen(key), nullptr, 10) : 0;
}

// Write one TTDB_PUT slice into the belief file and, on completion, CRC-verify and
// schedule adoption. Returns true if the slice was accepted (so it is ACKed). The
// laptop streams strictly in offset order (stop-and-wait), so we track gPutNext and
// stay idempotent on retransmits (TTN-RFC-0009 §3). Runs in the caller's context —
// for the serial/bridge push path that is loop(), where flash writes are safe.
static bool handlePutSlice(const toot::Toot& t) {
  uint32_t target, bid, total, crc, off;
  const uint8_t* data;
  uint16_t len;
  if (!toot::parsePut(t, target, bid, total, crc, off, data, len)) return false;
  if (target != kNodeId) return false;
  // Already adopted this belief: re-ACK without rewriting (lost-final-ACK case).
  if (gBeliefAdopted && bid == gBeliefId) return true;

  if (off == 0) {                          // (re)start a fresh transfer
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
      gBeliefSyncPending = true;                  // log to live TTDB from loop()
    } else {
      Serial.printf("[belief] id=%lu CRC MISMATCH got %08lX want %08lX (%luB)\n",
                    (unsigned long)bid, (unsigned long)gPutCrcRun,
                    (unsigned long)gPutCrc, (unsigned long)gPutTotal);
    }
  }
  return true;
}

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

// How many records this TTDB holds in `lat`. Used by every lane cap and by the senses
// view; walks the in-RAM index, never the file.
static int laneCount(int16_t lat) {
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == lat) ++n;
  return n;
}

// Is this node's own voice sounding a part right now? Reported as the STATE that would
// sound a note rather than the instant of one, so a 2 s intero poll cannot fall between
// two beats and read false. Unlike the consoles there is no `!conductor()` term: this
// node's voice has never been gated on holding the baton (see loop()).
static bool voicingNow() {
#if USE_PULSE
  return duetOn() ||
         (gPlayEnabled && score::phraseForScene(kPart, gPulse.scene()) != nullptr);
#else
  return false;
#endif
}

// ============================================================================
// THE SCREEN — three views, and the eye is the one it wakes up in
// ============================================================================
//
// The K10 HAS NO REACHABLE BUTTON. The board library exposes buttonA/B, but on this unit
// they are not available to a hand, so the node cannot change its own view and nothing
// local can. That is the whole reason CMD_SET_VIEW exists: the console IS this node's
// buttons, over the air. It also means the DEFAULT view has to be the one that is worth
// looking at with nobody driving it — which is exactly the argument the Cardputer's
// representor makes for an eye (cardputer-sensorium.md §3.2): a scope with no sound is a
// flat line, a status page with nothing wrong is a wall of unchanged text, but an eye at
// rest is still a face.
//
// Views are NODE-LOCAL ids (Toot.h CMD_SET_VIEW). A console steps them with VIEW_NEXT
// without knowing what they are. `K10View` itself is declared at the TOP of this sketch
// — see the note there about arduino-cli's generated prototypes — and setView() lives
// OUTSIDE the USE_K10_HW guard on purpose: the command must be accepted and ACKed
// identically whether or not this build has a panel, or a serial-mock build would answer
// differently from the real one and the wire behaviour would depend on a display #define.
static K10View gView = K10_VIEW_EYE;
static bool    gViewEntered = false;     // has the current view painted its base yet?
static const char* viewName(K10View v) {
  return v == K10_VIEW_STATUS ? "STATUS"
       : v == K10_VIEW_SENSES ? "SENSES"
                              : "EYE";
}

// Switch the face this node is showing. `v` is a K10View, or toot::VIEW_NEXT to step.
// Called from the CMD path (the console pressing `v`) — never locally, because this
// board has no reachable button, which is the whole point of the op.
static void setView(uint8_t v) {
  K10View next = (v == toot::VIEW_NEXT)
                     ? (K10View)((gView + 1) % K10_VIEW_COUNT)
                     : (K10View)(v % K10_VIEW_COUNT);
  if (next == gView && v != toot::VIEW_NEXT) return;   // idempotent: no repaint
  gView = next;
  gViewEntered = false;      // the new view paints its own base on the next frame
  Serial.printf("[view] -> %u %s\n", (unsigned)gView, viewName(gView));
}

#if USE_K10_HW
// The fleet voice. Every other node (T-Deck + the V4s) synthesizes tones as a 50%
// SQUARE wave at 8 kHz over ESP_I2S — a shared chiptune timbre, and the volume knob
// the fleet standardized on (the DFRobot Music::playTone is a fixed full-scale sine
// with no amplitude parameter, so we bypass it). `amp` matches the T-Deck's toneI2S
// default (22000) so the K10 lead is as loud as the T-Deck. Writes I2S_NUM_0 directly,
// exactly as Music::playTone does (same already-installed driver) — synchronous, so
// call from setup()/loop() ONLY (it blocks ~ms), never a callback.
static const int   K10_I2S_RATE = 8000;    // matches the fleet's 8 kHz square timbre
static const int16_t K10_TONE_AMP = 22000; // == tdeck_console toneI2S default (same loudness)
static void k10Tone(int freq, uint32_t ms, int16_t amp = K10_TONE_AMP) {
#if USE_MIC
  // Deafen the acoustic tier for the duration plus a tail. TX and RX share this port's
  // clock, so everything read across a tone is BOTH our own voice and sampled at 8 kHz
  // instead of 16 — and a transient timestamp is only worth anything if it belongs to
  // an event that happened in the room. Set BEFORE the blocking write, not after, or the
  // samples captured during the note are already in the DMA ring unmuted.
  gToneUntilMs = millis() + ms + MIC_SELF_MUTE_MS;
#endif
  uint32_t clk = i2s_get_clk(I2S_NUM_0);
  i2s_set_sample_rates(I2S_NUM_0, K10_I2S_RATE);
  uint32_t total = (uint32_t)((uint64_t)K10_I2S_RATE * ms / 1000);
  float phase = 0.0f, inc = TWO_PI * (float)freq / (float)K10_I2S_RATE;
  int16_t buf[2];
  size_t wrote;
  for (uint32_t i = 0; i < total; ++i) {
    int16_t s = (phase < (float)PI) ? amp : (int16_t)-amp;   // 50% square, like the T-Deck
    buf[0] = buf[1] = s;                                     // L = R
    i2s_write(I2S_NUM_0, (char*)buf, sizeof(buf), &wrote, portMAX_DELAY);
    phase += inc;
    if (phase >= TWO_PI) phase -= TWO_PI;
  }
  i2s_zero_dma_buffer(I2S_NUM_0);
  i2s_set_sample_rates(I2S_NUM_0, clk);
}

// Two toots — the Toot-Toot signature — on startup (uses the K10 speaker via k10Tone).
// The boot toot plays at 25% of the fleet loudness (75% quieter) — the running melody /
// beeps keep the full K10_TONE_AMP; only the startup signature is softened.
static const int16_t K10_STARTUP_AMP = K10_TONE_AMP / 4;   // 22000 -> 5500
static void playStartupToot() {
  delay(50);                              // let the speaker settle after k10.begin()
  k10Tone(196, 250, K10_STARTUP_AMP);    // toot  (G3, 0.25 s)
  k10Tone(262, 500, K10_STARTUP_AMP);    // toot  (C4, 0.5 s)
}

// Panel geometry. initScreen(2)/setRotation(2) is portrait: 240 wide, 320 tall — the
// picture-frame orientation this board actually stands in.
static const int SCR_W = 240, SCR_H = 320;

static inline uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

// --- the eyeball --------------------------------------------------------------------
//
// GIANT: the ball is 304 px across on a 240x320 panel, so it bleeds off both sides and
// leaves 8 px of black at top and bottom. That reads as a close-up of an eye rather than
// a ball drawn on a screen — you can see the curve of the sclera at top and bottom while
// the sides run past the edge. Adafruit-style clipping is NOT free in TFT_eSPI, so every
// span below is clamped by hand.
static const int EYE_CX = SCR_W / 2;          // 120
static const int EYE_CY = SCR_H / 2;          // 160
static const int EYE_R  = 152;                // rows 8..312, columns clipped
// Iris/pupil keep the Cardputer's proportions (iris ~0.49 of the ball) so the two
// representors read as the same creature at two sizes.
static const int IRIS_R = 74;
static const int IRIS_OUTLINE = 8;            // thick black limbal ring
static const int IRIS_OUTER = IRIS_R + IRIS_OUTLINE;
static const int PUPIL_R_MIN = 20, PUPIL_R_MAX = 38;   // arousal (loudness) dilates it
// Travel is bounded by the OUTLINE's radius, not the iris's, or a full-tilt gaze pushes
// the black ring past the edge of the sclera.
static const int EYE_REACH = EYE_R - IRIS_OUTER - 2;
// The catchlight is a reflection of the ROOM's light source, so it belongs to the room:
// it stays put while the iris slides under it, which is why it is a screen coordinate
// and not an offset from the iris.
static const int GLINT_X = EYE_CX - (EYE_R * 45) / 100;
static const int GLINT_Y = EYE_CY - (EYE_R * 45) / 100;
static const int GLINT_R = 30;

// The face runs on the BEAT, not on a frame clock: rendering happens in a short pulse at
// the head of each beat and between beats the eye is entirely still — no gaze update, no
// SPI traffic. It is a creature with a pulse, not a needle on a meter. It also keeps the
// panel off the bus for most of every beat, which is what stops a 240x320 display from
// eating the step clock this node has to keep.
static const uint32_t EYE_PULSE_MS = 240;       // render window at each beat
static const uint32_t EYE_PULSE_FRAME_MS = 80;  // frames within that window
static const uint32_t BLINK_MS = EYE_PULSE_FRAME_MS - 10;   // exactly one frame shut
static const uint32_t BLINK_GAP_MS = 8000;

static const uint16_t COL_SCLERA = rgb565(238, 236, 228);
// RED, and the same red as the Cardputer's representor — so the fleet's two eyes read as
// two views of one creature rather than two devices that each happen to have a face.
static const uint16_t COL_IRIS   = rgb565(210, 40, 40);
// ...and gold while this node's own voice is sounding a part. It has to be far from the
// resting red to be legible across a room at a glance, which is the only distance this
// screen is ever read from.
static const uint16_t COL_IRIS_SING = rgb565(255, 190, 60);

static bool  gEyePainted = false;             // is the sclera currently on the panel?
static int   gIrisX = -1000, gIrisY = 0, gPupilR = -1;   // last painted iris
static bool  gBlinking = false;
static uint32_t gBlinkT0 = 0, gNextBlink = 0;

// Lay the sclera down across one row, in the two pieces either side of the disc at
// (ex, ey) that the iris is about to cover. Draws nothing if the row is entirely inside
// that disc.
static inline void scleraRow(int y, int x0, int x1, int ex, int ey, int e2) {
  int edy = y - ey;
  int ehw = (edy * edy < e2) ? (int)sqrtf((float)(e2 - edy * edy)) : -1;
  if (ehw < 0) { gTft.drawFastHLine(x0, y, x1 - x0 + 1, COL_SCLERA); return; }
  int ex0 = ex - ehw, ex1 = ex + ehw;
  if (x0 < ex0) {
    int e = (x1 < ex0 - 1) ? x1 : ex0 - 1;
    gTft.drawFastHLine(x0, y, e - x0 + 1, COL_SCLERA);
  }
  if (x1 > ex1) {
    int s = (x0 > ex1 + 1) ? x0 : ex1 + 1;
    gTft.drawFastHLine(s, y, x1 - s + 1, COL_SCLERA);
  }
}

// Entering the face (or opening from a blink): clear whatever was there AND lay the
// sclera down, writing every pixel at most once. `fillScreen` + a circle would paint
// over half the panel twice for no benefit.
//
// Wrapped in ONE startWrite/endWrite: `drawFastHLine` opens and closes its own SPI
// transaction, and for a shape made of ~300 spans that overhead — not the pixels — is
// the cost. Batching is what keeps a full repaint inside the frame budget (the same
// measurement the Cardputer's eyeSpans records: 17k px was 8 ms of data drawn in 22 ms
// span by span).
static void paintEyeBase(int ix, int iy) {
  const int r2 = EYE_R * EYE_R, e2 = IRIS_OUTER * IRIS_OUTER;
  gTft.startWrite();
  for (int y = 0; y < SCR_H; ++y) {
    int dy = y - EYE_CY;
    int hw = (dy * dy < r2) ? (int)sqrtf((float)(r2 - dy * dy)) : -1;
    int x0 = EYE_CX - hw, x1 = EYE_CX + hw;
    if (hw <= 0) { gTft.drawFastHLine(0, y, SCR_W, TFT_BLACK); continue; }
    if (x0 < 0) x0 = 0;
    if (x1 > SCR_W - 1) x1 = SCR_W - 1;
    if (x0 > 0) gTft.drawFastHLine(0, y, x0, TFT_BLACK);
    scleraRow(y, x0, x1, ix, iy, e2);
    if (x1 < SCR_W - 1) gTft.drawFastHLine(x1 + 1, y, SCR_W - 1 - x1, TFT_BLACK);
  }
  gTft.endWrite();
}

// Fill the whole ball with one colour — the eyelid coming down. A blink is simply the
// eye leaving the panel; there is no lid colour because the lid is the black surround.
static void paintEyeSolid(uint16_t color) {
  const int r2 = EYE_R * EYE_R;
  gTft.startWrite();
  for (int y = EYE_CY - EYE_R; y <= EYE_CY + EYE_R; ++y) {
    if (y < 0 || y >= SCR_H) continue;
    int dy = y - EYE_CY;
    int hw = (int)sqrtf((float)(r2 - dy * dy));
    int x0 = EYE_CX - hw, x1 = EYE_CX + hw;
    if (x0 < 0) x0 = 0;
    if (x1 > SCR_W - 1) x1 = SCR_W - 1;
    if (x1 >= x0) gTft.drawFastHLine(x0, y, x1 - x0 + 1, color);
  }
  gTft.endWrite();
}

// The catchlight, repainted after anything that may have covered it.
static void paintGlint() {
  gTft.fillCircle(GLINT_X, GLINT_Y, GLINT_R, rgb565(255, 255, 255));
}

// Move the iris from wherever it was painted to (nx, ny) with pupil radius `pr`,
// touching only the union of the two discs. This is the ONLY per-frame cost when the eye
// is awake, and when the gaze has not moved and the pupil has not changed it is zero.
static void paintIris(int nx, int ny, int pr, uint16_t iris_col) {
  const bool moved = (nx != gIrisX || ny != gIrisY);
  const int e2 = IRIS_OUTER * IRIS_OUTER, r2 = EYE_R * EYE_R;
  if (moved && gIrisX > -1000) {
    // Restore sclera over the OLD disc, minus wherever the new disc will land.
    gTft.startWrite();
    for (int y = gIrisY - IRIS_OUTER; y <= gIrisY + IRIS_OUTER; ++y) {
      if (y < 0 || y >= SCR_H) continue;
      int ody = y - gIrisY;
      int ohw = (int)sqrtf((float)(e2 - ody * ody));
      int x0 = gIrisX - ohw, x1 = gIrisX + ohw;
      // Stay inside the ball: outside it the correct colour is black, not sclera.
      int dy = y - EYE_CY;
      int bhw = (dy * dy < r2) ? (int)sqrtf((float)(r2 - dy * dy)) : -1;
      if (bhw < 0) continue;
      if (x0 < EYE_CX - bhw) x0 = EYE_CX - bhw;
      if (x1 > EYE_CX + bhw) x1 = EYE_CX + bhw;
      if (x0 < 0) x0 = 0;
      if (x1 > SCR_W - 1) x1 = SCR_W - 1;
      if (x1 >= x0) scleraRow(y, x0, x1, nx, ny, e2);
    }
    gTft.endWrite();
    paintGlint();          // the old disc may have been sitting under the catchlight
  }
  if (moved || pr != gPupilR) {
    gTft.fillCircle(nx, ny, IRIS_OUTER, TFT_BLACK);   // limbal ring
    gTft.fillCircle(nx, ny, IRIS_R, iris_col);
    gTft.fillCircle(nx, ny, pr, TFT_BLACK);           // pupil
    // The catchlight sits ON the eye, so it wins over the iris wherever they overlap.
    int gdx = nx - GLINT_X, gdy = ny - GLINT_Y;
    if (gdx * gdx + gdy * gdy < (IRIS_OUTER + GLINT_R) * (IRIS_OUTER + GLINT_R))
      paintGlint();
  }
  gIrisX = nx; gIrisY = ny; gPupilR = pr;
}

// --- FACE: the eye ------------------------------------------------------------------
static void renderEye(uint32_t now) {
  if (!gViewEntered) {
    gViewEntered = true;
    gEyePainted = false;
    gIrisX = -1000; gPupilR = -1;
    gBlinking = false;
    gNextBlink = now + BLINK_GAP_MS;
  }

  // Blink: one frame shut, then the ball comes back whole.
  if (gBlinking) {
    if (now - gBlinkT0 < BLINK_MS) return;
    gBlinking = false;
    gEyePainted = false;                     // force a full repaint on the way open
    gNextBlink = now + BLINK_GAP_MS + (esp_random() % BLINK_GAP_MS);
  } else if (gEyePainted && (int32_t)(now - gNextBlink) >= 0) {
    gBlinking = true;
    gBlinkT0 = now;
    paintEyeSolid(TFT_BLACK);
    gIrisX = -1000; gPupilR = -1;            // nothing on the panel to erase from
    return;
  }

  // WHERE IT LOOKS: the departure of the board's pose from its resting lean, mapped
  // through a BOWL rather than a slope. Straight tilt is linear in sin(angle), which made
  // the Cardputer's first eye read as a spirit level; a bowl is steep in the middle and
  // flat toward the rim, so a subtle lean barely disturbs the ball and a deliberate one
  // runs it a long way. gGazeX/gGazeY are already eased and bowl-shaped by serviceTilt().
  float gx = gGazeX, gy = gGazeY;
  int ix = EYE_CX + (int)(gx * (float)EYE_REACH);
  int iy = EYE_CY + (int)(gy * (float)EYE_REACH);

  // HOW WIDE THE PUPIL IS: loudness. This is the microphone made VISIBLE without a
  // number anywhere on screen — the room gets loud and the eye opens up. It is the same
  // signal the @LAT94 tier is folding into its window, read at the display's own pace;
  // the tier's cadence is not affected by it (see serviceMic).
  int pr = PUPIL_R_MIN + (int)(gArousal * (float)(PUPIL_R_MAX - PUPIL_R_MIN));

  const uint16_t iris_col = voicingNow() ? COL_IRIS_SING : COL_IRIS;
  static uint16_t last_col = 0;

  if (!gEyePainted) {
    paintEyeBase(ix, iy);
    paintGlint();
    gEyePainted = true;
    gIrisX = -1000; gPupilR = -1;            // the base left no iris to erase
  }
  if (iris_col != last_col) { last_col = iris_col; gPupilR = -1; }  // force a redraw
  paintIris(ix, iy, pr, iris_col);
}

// --- STATUS: what the old canvas screen said, at a size you can read across a room ---
static void renderStatus(uint32_t now) {
  (void)now;
  char line[48];
  // Every line below is redrawn only when its text CHANGES: `drawString` with a background
  // colour overwrites exactly its own glyph box, so an unchanged row costs nothing on the
  // bus. Same reasoning as the canvas version this replaces, without the full-screen flush
  // that made it blink.
  struct Row { int y; uint16_t col; char last[48]; };
  static Row rows[7] = {
    {  70, rgb565(0, 255, 102), "" },   // TTDB
    {  94, rgb565(0, 255, 102), "" },   // temp
    { 118, rgb565(46, 125, 50), "" },   // cursor
    { 142, rgb565(255, 111, 0), "" },   // warm / LED
    { 176, rgb565(64, 196, 255), "" },  // band: scene + conductor
    { 200, rgb565(64, 196, 255), "" },  // stream
    { 224, rgb565(160, 160, 160), "" }, // lanes
  };
  if (!gViewEntered) {
    gViewEntered = true;
    gTft.fillScreen(TFT_BLACK);
    gTft.setTextColor(rgb565(0, 230, 118), TFT_BLACK);
    gTft.drawString("K10 PERCEPT", 8, 8, 4);
    gTft.setTextColor(rgb565(46, 125, 50), TFT_BLACK);
    snprintf(line, sizeof(line), "id 0x%08X", (unsigned)kNodeId);
    gTft.drawString(line, 8, 40, 2);
    // ⚠ INVALIDATE THE ROW CACHE. These statics outlive the view: leave them holding last
    // time's text and the fillScreen above wipes rows that then compare EQUAL and are never
    // redrawn — so coming back to this view shows a nearly blank screen with only the
    // handful of values that happened to change. The cache is a claim about what is ON THE
    // PANEL, so anything that clears the panel has to clear the cache with it.
    for (int i = 0; i < 7; ++i) rows[i].last[0] = '\0';
  }
  const char* txt[7];
  char buf[7][48];

  snprintf(buf[0], 48, "TTDB %uB %dr", (unsigned)gDb.fileSize(), gDb.recordCount());
  float t = gAgent.readingCount() > 0 ? gAgent.reading(0).value : 0.0f;
  snprintf(buf[1], 48, "temp %.1f C", t);
  snprintf(buf[2], 48, "cursor @LAT%dLON%d", gAgent.cursorLat(), gAgent.cursorLon());
  if (gLedOverride.enabled)
    snprintf(buf[3], 48, "LED laptop #%06X", (unsigned)gLedOverride.color);
  else
    snprintf(buf[3], 48, "%s", gAgent.matchedThisCycle() ? "WARM" : "cool");
#if USE_PULSE
  snprintf(buf[4], 48, "%s cond %04X%s", heroarc::sceneName(gPulse.scene()),
           (unsigned)(gPulse.chart().conductor_id & 0xFFFF),
           gPulse.conductor() ? "*" : "");
#else
  snprintf(buf[4], 48, "band off");
#endif
  snprintf(buf[5], 48, "stream %08lX %s", (unsigned long)gStamp.stream_id,
           gSynced ? "wall" : "local");
  snprintf(buf[6], 48, "94:%d 95:%d 96:%d", laneCount(94), laneCount(95), laneCount(96));
  for (int i = 0; i < 7; ++i) txt[i] = buf[i];

  for (int i = 0; i < 7; ++i) {
    if (!strcmp(txt[i], rows[i].last)) continue;
    strncpy(rows[i].last, txt[i], sizeof(rows[i].last) - 1);
    rows[i].last[sizeof(rows[i].last) - 1] = '\0';
    gTft.setTextColor(rows[i].col, TFT_BLACK);
    gTft.fillRect(0, rows[i].y, SCR_W, 22, TFT_BLACK);
    gTft.drawString(txt[i], 8, rows[i].y, 2);
  }
}

// --- SENSES: the two new organs as INSTRUMENTS ---------------------------------------
//
// Not a prettier eye: this is the view that answers "is the tilt reading anything, is
// the mic reading anything, and are the lanes filling?" — the questions a percept tier
// needs a face for. The eye shows the senses being FELT; this shows them being MEASURED,
// which is a different claim and deserves a different screen.
static void renderSenses(uint32_t now) {
  (void)now;
  const int BUBBLE_CX = SCR_W / 2, BUBBLE_CY = 118, BUBBLE_R = 78;
  struct Row { int y; uint16_t col; char last[48]; };
  static Row rows[4] = {
    {  40, rgb565(160, 200, 160), "" },   // tilt raw + rest
    { 196, rgb565(120, 160, 220), "" },   // mic header
    { 244, rgb565(160, 160, 160), "" },   // acoustic tier state
    { 272, rgb565(160, 160, 160), "" },   // motion tier state
  };
  static int lastBX = -1000, lastBY = 0;   // the tilt bubble's last painted position
  static int lastFill = -1;                // the mic bar's last painted width
  if (!gViewEntered) {
    gViewEntered = true;
    gTft.fillScreen(TFT_BLACK);
    gTft.setTextColor(rgb565(0, 230, 118), TFT_BLACK);
    gTft.drawString("SENSES", 8, 6, 4);
    // The tilt bubble's chrome: rim + crosshair. Centre is the RESTING pose, so the dot
    // sits in the middle when the board is in the picture-frame lean it lives in.
    gTft.drawCircle(BUBBLE_CX, BUBBLE_CY, BUBBLE_R, rgb565(40, 80, 40));
    gTft.drawCircle(BUBBLE_CX, BUBBLE_CY, BUBBLE_R / 2, rgb565(28, 56, 28));
    gTft.drawFastHLine(BUBBLE_CX - BUBBLE_R, BUBBLE_CY, BUBBLE_R * 2, rgb565(28, 56, 28));
    gTft.drawFastVLine(BUBBLE_CX, BUBBLE_CY - BUBBLE_R, BUBBLE_R * 2, rgb565(28, 56, 28));
    // ⚠ Invalidate every "what is on the panel" cache, for the reason spelled out in
    // renderStatus: the fillScreen above is what makes the stale ones lie.
    for (int i = 0; i < 4; ++i) rows[i].last[0] = '\0';
    lastBX = -1000;
    lastFill = -1;
  }

#if USE_TILT
  // The bubble: where the gaze is pointing, i.e. the DEPARTURE from the rest pose.
  int bx = BUBBLE_CX + (int)(gGazeX * (float)(BUBBLE_R - 8));
  int by = BUBBLE_CY + (int)(gGazeY * (float)(BUBBLE_R - 8));
  if (bx != lastBX || by != lastBY) {
    if (lastBX > -1000) {
      gTft.fillCircle(lastBX, lastBY, 7, TFT_BLACK);
      // Repair the chrome the erase just cut through.
      gTft.drawCircle(BUBBLE_CX, BUBBLE_CY, BUBBLE_R, rgb565(40, 80, 40));
      gTft.drawCircle(BUBBLE_CX, BUBBLE_CY, BUBBLE_R / 2, rgb565(28, 56, 28));
      gTft.drawFastHLine(BUBBLE_CX - BUBBLE_R, BUBBLE_CY, BUBBLE_R * 2, rgb565(28, 56, 28));
      gTft.drawFastVLine(BUBBLE_CX, BUBBLE_CY - BUBBLE_R, BUBBLE_R * 2, rgb565(28, 56, 28));
    }
    gTft.fillCircle(bx, by, 7, gMotionLog.moving(millis()) ? rgb565(255, 140, 0)
                                                          : rgb565(0, 220, 120));
    lastBX = bx; lastBY = by;
  }
#endif

  // The mic level, as a bar. Log-ish scaling: RMS spans four decades and a linear bar
  // would sit at zero all day and then peg.
  const int BAR_Y = 216, BAR_H = 20, BAR_X = 12, BAR_W = SCR_W - 24;
  int fill = 0;
#if USE_MIC
  {
    float lv = (float)gMicLevel;
    if (lv < 1.0f) lv = 1.0f;
    float f = (logf(lv) / logf(32768.0f));          // 0..1 over the 16-bit range
    if (f < 0) f = 0;
    if (f > 1) f = 1;
    fill = (int)(f * (float)BAR_W);
  }
#endif
  if (fill != lastFill) {
    gTft.fillRect(BAR_X, BAR_Y, fill, BAR_H, rgb565(60, 130, 210));
    gTft.fillRect(BAR_X + fill, BAR_Y, BAR_W - fill, BAR_H, rgb565(18, 24, 34));
    lastFill = fill;
  }

  char buf[4][48];
#if USE_TILT
  snprintf(buf[0], 48, gTiltOk ? "tilt %4d %4d %4d mg" : "tilt NO CHIP",
           (int)gTiltX, (int)gTiltY, (int)gTiltZ);
#else
  snprintf(buf[0], 48, "tilt off");
#endif
#if USE_MIC
  snprintf(buf[1], 48, gMicOk ? "mic rms %ld" : "mic SILENT (no i2s)",
           (long)gMicLevel);
  snprintf(buf[2], 48, "@LAT94 %d/%d  trans %ld", laneCount(94),
           ACOUSTICPERCEPT_MAX_LANE, (long)gAcousticLog.transients());
#else
  snprintf(buf[1], 48, "mic off");
  snprintf(buf[2], 48, "@LAT94 off");
#endif
#if USE_TILT
  // The null is on screen because it is the number that decides whether `still` means
  // anything on this board; `x1.000` with a `moving` verdict is the false-positive state.
  snprintf(buf[3], 48, "@LAT95 %d/%d %s x%.3f", laneCount(95), MOTIONPERCEPT_MAX_LANE,
           gMotionLog.moving(millis()) ? "MOVING" : "still", gRestScale);
#else
  snprintf(buf[3], 48, "@LAT95 off");
#endif
  for (int i = 0; i < 4; ++i) {
    if (!strcmp(buf[i], rows[i].last)) continue;
    strncpy(rows[i].last, buf[i], sizeof(rows[i].last) - 1);
    rows[i].last[sizeof(rows[i].last) - 1] = '\0';
    gTft.setTextColor(rows[i].col, TFT_BLACK);
    gTft.fillRect(0, rows[i].y, SCR_W, 20, TFT_BLACK);
    gTft.drawString(buf[i], 8, rows[i].y, 2);
  }
}

// Paint whichever view is up, at the pace that view wants. The EYE runs on the BEAT (a
// short burst of frames at the head of each one, nothing in between); the two instrument
// views run on a plain 2 Hz clock, because a gauge that updates rhythmically is just a
// gauge that is sometimes stale.
static void serviceScreen(uint32_t now) {
  if (gView == K10_VIEW_EYE) {
    static uint32_t lastFrame = 0;
    bool due;
#if USE_PULSE
    uint8_t bib = 0; uint16_t ph = 0; uint32_t bc = 0;
    if (gPulse.phaseNow(now, bib, ph, bc))
      due = (ph < EYE_PULSE_MS) && (now - lastFrame >= EYE_PULSE_FRAME_MS);
    else
      due = (now - lastFrame >= EYE_PULSE_FRAME_MS);   // no chart: free-run, still alive
#else
    due = (now - lastFrame >= EYE_PULSE_FRAME_MS);
#endif
    if (!due) return;
    lastFrame = now;
    renderEye(now);
    return;
  }
  static uint32_t lastSlow = 0;
  if (now - lastSlow < 500) return;
  lastSlow = now;
  if (gView == K10_VIEW_STATUS) renderStatus(now);
  else                          renderSenses(now);
}
#endif  // USE_K10_HW

// ============================================================================
// READING THE TWO ORGANS
// ============================================================================

#if USE_TILT && USE_K10_HW
// Which way the eye looks when the frame is tipped. The SC7A20H's axes are not
// documented for this board in a form worth trusting, so the mapping is three constants
// rather than arithmetic buried in the renderer: if the gaze runs UPHILL, flip a sign;
// if it runs SIDEWAYS, set the swap. (Exactly the shape the Cardputer's eye needed, and
// both of ITS signs turned out to be wrong on first contact with hardware — so expect to
// change these once and then never again.)
#define EYE_SWAP_AXES 0
static const float EYE_GAZE_X = -1.0f;
static const float EYE_GAZE_Y =  1.0f;

// The gaze sits in a BOWL, not on a slope. Straight tilt is linear in sin(angle), so a
// linear map makes the iris slide off centre at the slightest lean and the face reads as
// a spirit level. A bowl is steep in the middle and flat toward the rim: a subtle tilt
// barely disturbs the ball, a deliberate one runs it a long way, and at the rim it stops.
//   r = (tilt / BOWL_FULL_MG) ^ BOWL_GAMMA, clamped to 1 = the rim.
static const float BOWL_GAMMA  = 2.0f;
static const float BOWL_FULL_MG = 800.0f;   // ~53 degrees off the resting lean

static void serviceTilt(uint32_t now) {
  static uint32_t last = 0, boot = 0, restSince = 0;
  static float candX = 0, candY = 0, candZ = 0;
  static bool primed = false;
  // ⚠ The null is the mean of PER-SAMPLE magnitudes, NOT |low-passed vector|. Those are
  // different numbers whenever there is noise (averaging a vector shrinks its length;
  // averaging lengths does not), and the tier sees per-sample magnitudes — so nulling
  // against the low-passed one leaves a systematic residual. Measured on this board: the
  // LP vector read 1069 mg while the tier's own dev_mean implied ~1087.
  static double magSum = 0.0;
  static uint32_t magN = 0;
  // `boot` is the first call to THIS function, not an absolute millis() reading. That is
  // deliberate and it is the shape `pulse::Engine` uses: an absolute settle window
  // silently assumes setup() is short, and on the Cardputer that assumption cost two
  // spurious @LAT90 records per boot because setup() there takes over six seconds. Here
  // the first call is the first loop pass, so the settle window starts when the node
  // actually begins reading the chip.
  if (boot == 0) boot = now;
  if (now - last < TILT_POLL_MS) return;
  last = now;

  const int ax = k10.getAccelerometerX();
  const int ay = k10.getAccelerometerY();
  const int az = k10.getAccelerometerZ();
  // The library's gesture_task publishes these; before its first successful read they
  // are all zero, which is not a pose any board can be in (gravity is always 1 g
  // somewhere). Treat it as "the chip has not answered yet" rather than as a reading.
  if (ax == 0 && ay == 0 && az == 0) return;
  gTiltOk = true;
  gAccX = ax; gAccY = ay; gAccZ = az;

  const float mx = (float)ax * TILT_MG_PER_LSB;
  const float my = (float)ay * TILT_MG_PER_LSB;
  const float mz = (float)az * TILT_MG_PER_LSB;

  // The @LAT95 tier gets the RAW sample, never the low-passed one: it measures the
  // deviation of the acceleration MAGNITUDE, and a filter tuned to ignore a hand tremor
  // is a filter that would erase exactly the evidence of motion the tier exists to
  // collect. It gets no rest-DIRECTION subtraction either — that would make a node
  // carried at a steady angle report `still`.
  //
  // It IS scaled by the rest-magnitude null (see REST_MAG_MG): unscaled, this board's
  // 6.9% high reading is a permanent 87 mg offset against a 60 mg threshold measured on
  // another chip, and every window says `moving` about a motionless picture frame.
  // ⚠ Before the first null is measured `gRestScale` is 1.0, so the settle window's own
  // samples are unscaled — they land in the first window and are the reason it may still
  // read `moving`. That is correct rather than convenient: those samples really were
  // taken before this board knew what its own rest looked like.
  //
  // Accumulate the per-sample magnitude either way; that mean is what the null is made of.
  const float smag = sqrtf(mx * mx + my * my + mz * mz);
  magSum += (double)smag;
  ++magN;
  if (now - boot >= TILT_SETTLE_MS)
    gMotionLog.add((int)(mx * gRestScale), (int)(my * gRestScale),
                   (int)(mz * gRestScale), now);

  if (!primed) {
    primed = true;
    gTiltX = mx; gTiltY = my; gTiltZ = mz;
    candX = mx; candY = my; candZ = mz;
    restSince = now;
    return;
  }
  gTiltX += (mx - gTiltX) * TILT_LP;
  gTiltY += (my - gTiltY) * TILT_LP;
  gTiltZ += (mz - gTiltZ) * TILT_LP;

  // --- adopt a new resting pose -------------------------------------------------
  // The candidate is the low-passed vector. While it stays within RECENTER_STILL_MG of
  // where it was, the clock runs; the moment it wanders, the clock restarts. So a
  // deliberate reposition is adopted after RECENTER_HOLD_MS and a tip-and-release is not
  // adopted at all. The FIRST adoption happens as soon as the settle window closes, so
  // the eye is centred within a couple of seconds of boot rather than staring at the
  // floor until someone moves the board.
  const float dcx = gTiltX - candX, dcy = gTiltY - candY, dcz = gTiltZ - candZ;
  if (fabsf(dcx) > RECENTER_STILL_MG || fabsf(dcy) > RECENTER_STILL_MG ||
      fabsf(dcz) > RECENTER_STILL_MG) {
    candX = gTiltX; candY = gTiltY; candZ = gTiltZ;
    restSince = now;
    magSum = 0.0; magN = 0;                 // the pose moved: the null must be re-measured
  } else if (!gRestKnown ? (now - boot >= TILT_SETTLE_MS)
                         : (now - restSince >= RECENTER_HOLD_MS)) {
    restSince = now;                        // whatever happens, the window starts over
    // ⚠ A BOARD THAT NEVER MOVES REACHES THIS BRANCH EVERY 20 s FOREVER. Only ADOPT — and
    // only announce — when the candidate is actually somewhere else; otherwise this line
    // prints "NEW resting pose" at a board sitting perfectly still on a shelf, which is
    // both a serial flood and a false statement about the world.
    const bool first = !gRestKnown;
    const bool same = !first && fabsf(candX - gRestX) <= RECENTER_STILL_MG &&
                      fabsf(candY - gRestY) <= RECENTER_STILL_MG &&
                      fabsf(candZ - gRestZ) <= RECENTER_STILL_MG;
    if (same) { magSum = 0.0; magN = 0; return; }   // nothing happened; restart the mean
    gRestX = candX; gRestY = candY; gRestZ = candZ;
    gRestKnown = true;

    // The magnitude null for THIS pose. Refused outside the sane band rather than
    // applied: a null taken while the board was moving is worse than no null at all,
    // and a silent refusal would look exactly like a working one.
    const uint32_t nUsed = magN;            // read BEFORE the reset, or the log says 0
    const float restMag = nUsed ? (float)(magSum / (double)nUsed) : 0.0f;
    magSum = 0.0; magN = 0;
    const bool ok = restMag >= REST_MAG_MIN_MG && restMag <= REST_MAG_MAX_MG;
    if (ok) { gRestScale = REST_MAG_MG / restMag; gRestScaleKnown = true; }
    Serial.printf("[tilt] %s pose %d %d %d mg | rest |a| %d mg over %lu samples -> "
                  "@LAT95 null x%.4f%s\n",
                  first ? "resting" : "NEW resting",
                  (int)gRestX, (int)gRestY, (int)gRestZ, (int)restMag,
                  (unsigned long)nUsed, gRestScale,
                  ok ? "" : "  <- REFUSED: |a| outside 700..1400 mg, keeping x1.0. The "
                            "board was not at rest, or TILT_MG_PER_LSB is wrong.");
  }

  // --- where the eye looks: the DEPARTURE from that pose ------------------------
  float dx = gTiltX - gRestX, dy = gTiltY - gRestY;
#if EYE_SWAP_AXES
  { float t = dx; dx = dy; dy = t; }
#endif
  const float sx = EYE_GAZE_X * dx, sy = EYE_GAZE_Y * dy;
  const float mag = sqrtf(sx * sx + sy * sy);
  if (mag < 1.0f) { gGazeX = 0.0f; gGazeY = 0.0f; return; }
  float r = mag / BOWL_FULL_MG;
  if (r > 1.0f) r = 1.0f;
  r = powf(r, BOWL_GAMMA);
  gGazeX = sx / mag * r;
  gGazeY = sy / mag * r;
}
#endif  // USE_TILT && USE_K10_HW

#if USE_MIC && USE_K10_HW
// Pull whatever the I2S RX ring has, feed the @LAT94 tier in fixed blocks, and keep a
// loudness figure for the eye. Non-blocking (ticks_to_wait 0) — a `portMAX_DELAY` read
// here would park the whole node on the microphone, and this loop has a band clock to
// keep.
static void serviceMic(uint32_t now) {
  static uint32_t last = 0;
  if (now - last < MIC_POLL_MS) return;
  last = now;

  static int16_t block[MIC_READ_FRAMES * 2];     // stereo frames as read off the bus

  // ⚠ DRAIN, DON'T SAMPLE. One read of MIC_READ_FRAMES every MIC_POLL_MS is EXACTLY the
  // capture rate, which means zero margin: any pass that runs late (a percept flush, a
  // blocking tone, a full sclera repaint) loses audio to DMA overwrite with nothing
  // saying so. The ring holds ~56 ms, so a bounded catch-up loop covers every stall this
  // node actually has. It is bounded rather than `while (got)` because an unbounded drain
  // would let a starved loop spend the whole pass on the microphone.
  for (int pass = 0; pass < 4; ++pass) {
    size_t got = 0;
    if (i2s_read(I2S_NUM_0, block, sizeof(block), &got, 0) != ESP_OK || got == 0) return;
    const size_t frames = got / (2 * sizeof(int16_t));
    if (!frames) return;
    gMicOk = true;

    // OUR OWN VOICE. Drop the whole block and empty the carry: a partial block that
    // straddled the mute boundary would put half a note into a window, and the sample
    // rate was 8 kHz for that half anyway. Dropping is honest — the window simply has
    // fewer blocks in it, which `blocks:` already reports.
    if ((int32_t)(now - gToneUntilMs) < 0) { gMicCarryN = 0; return; }

    // De-interleave to mono by taking the left slot. Both slots carry the same capsule on
    // this board, as they do on the Cardputer.
    if (gMicCarryN + frames > sizeof(gMicCarry) / sizeof(gMicCarry[0]))
      gMicCarryN = 0;                  // can't happen; if it does, drop rather than smear
    for (size_t i = 0; i < frames; ++i) gMicCarry[gMicCarryN + i] = block[i * 2];
    gMicCarryN += frames;

    // Loudness for the eye, computed on the block we just read rather than tapped out of
    // the tier: the tier's blocks are 128 frames for TDoA reasons that have nothing to do
    // with a screen, and the display must not get a vote in how the percept is timed.
    {
      uint64_t acc = 0;
      for (size_t i = 0; i < frames; ++i) {
        const int32_t s = block[i * 2];
        acc += (uint64_t)((int64_t)s * s);
      }
      gMicLevel = (int32_t)sqrt((double)(acc / frames));
    }

    // AROUSAL IS RELATIVE, NOT ABSOLUTE. A fixed loudness->pupil curve would sit pinned
    // open in a noisy room and pinned shut in a quiet one; what an eye actually answers
    // to is a room getting LOUDER than it was. So a slow EMA of the log level is the
    // baseline and arousal is the excess over it — the same argument AcousticPercept
    // makes for scaling its transient test off a running ambient rather than a per-site
    // threshold, and it means the pupil self-calibrates to whatever room it is left in.
    {
      float f = logf((float)(gMicLevel > 1 ? gMicLevel : 1)) / logf(32768.0f);
      static float amb = -1.0f;
      if (amb < 0.0f) amb = f;
      amb += (f - amb) * 0.01f;
      float exc = (f - amb) * 4.0f;
      if (exc < 0.0f) exc = 0.0f;
      if (exc > 1.0f) exc = 1.0f;
      gArousal += (exc - gArousal) * 0.25f;
    }

    // These samples end NOW; every block still behind them is that many frames older. The
    // transient timestamp is the Phase-3 TDoA datum, so it rides the TEAM TIME STREAM
    // rather than the wall clock: two nodes agreeing with EACH OTHER is what makes a
    // cross-correlation possible, and knowing the date is not.
    const uint64_t t_ms = gStamp.t_ms ? gStamp.t_ms : (uint64_t)now;
    while (gMicCarryN >= MIC_TIER_FRAMES) {
      const size_t rest = gMicCarryN - MIC_TIER_FRAMES;
      const uint64_t blk_t = t_ms - (uint64_t)((rest * 1000) / MIC_RATE);
      gAcousticLog.addBlock(gMicCarry, MIC_TIER_FRAMES, blk_t, now);
      memmove(gMicCarry, gMicCarry + MIC_TIER_FRAMES, rest * sizeof(int16_t));
      gMicCarryN = rest;
    }
    if (frames < MIC_READ_FRAMES) return;   // ring drained; nothing was waiting
  }
}
#endif  // USE_MIC && USE_K10_HW

// ============================================================================
// INTEROCEPTION — this node's sense of its own body (CMD_GET_INTERO)
// ============================================================================
//
// The K10 answers this now because it is back on the roster and the T-Deck's record pane
// polls it: a band member a console cannot ask "how are you" is a name on a list.
//
// This board has NO battery sense at all — it runs off USB — so bat_mv is 0 and bat_pct
// is 255 (unknown). That is the same honesty CMD_GET_GPS uses when it answers quality:0
// from a node with no GPS: a zeroed field that MEANS "no organ" beats silence, because
// silence is indistinguishable from a node that is down.
static const uint32_t INTERO_PERIOD_MS = 2000;
static int16_t  gDieC10 = 0;        // ESP32-S3 die temperature, tenths of a degree
static uint32_t gMaxAllocK = 0;     // largest CONTIGUOUS block, NOT free heap
static uint32_t gWorstLoopMs = 0;   // worst loop pass in the last published window
static uint32_t gLoopWorstRun = 0;  // accumulator for the window in progress

static void serviceIntero(uint32_t now) {
  static uint32_t last = 0;
  static bool first = true;
  if (!first && now - last < INTERO_PERIOD_MS) return;
  last = now;
  // Die temperature, not ambient — the AHT20 already reports ambient through the agent's
  // sensor path, and these are different measurements of different things. The die reads
  // high with WiFi up millimetres away, so it measures how hard the node is working as
  // much as it measures the room.
  gDieC10 = (int16_t)lroundf(temperatureRead() * 10.0f);
  gMaxAllocK = ESP.getMaxAllocHeap() / 1024;
  if (first) {
    first = false;
    Serial.printf("[intero] die %.1fC | maxalloc %luK | no battery sense on this board\n",
                  gDieC10 / 10.0f, (unsigned long)gMaxAllocK);
  }
}

// INTERO PERCEPT — the answer to CMD_GET_INTERO (Toot.h INTERO_PERCEPT_PAYLOAD_LEN).
// Reads NOTHING: every field is the last sample serviceIntero() took on its own 2 s
// cadence, so this is safe from the recv callback and cheap enough for a remote console
// to poll while it watches us — which is exactly the use case.
static uint8_t buildIntero(uint8_t* p) {
  toot::put_u16(p + 0, 0);            // no pack: 0 mV means "this node has no battery sense"
  p[2] = 255;                         // ...and therefore no percentage to invent
  p[3] = 0;
  toot::put_u16(p + 4, (uint16_t)gDieC10);
  toot::put_u16(p + 6, (uint16_t)gMaxAllocK);
  toot::put_u32(p + 8, millis() / 1000);
  toot::put_u16(p + 12, (uint16_t)(gWorstLoopMs > 65535 ? 65535 : gWorstLoopMs));
#if USE_PULSE
  const pulse::Chart& ch = gPulse.chart();
  toot::put_u16(p + 14, ch.beat_period_ms);
  toot::put_u32(p + 16, ch.conductor_id);
  p[20] = (gSynced ? toot::INTERO_SYNCED : 0) |
          (gPulse.conductor() ? toot::INTERO_CONDUCTOR : 0) |
          (gPulse.playing() ? toot::INTERO_PLAYING : 0) |
          (voicingNow() ? toot::INTERO_VOICING : 0);
#else
  toot::put_u16(p + 14, 0);
  toot::put_u32(p + 16, 0);
  p[20] = gSynced ? toot::INTERO_SYNCED : 0;
#endif
  return (uint8_t)toot::INTERO_PERCEPT_PAYLOAD_LEN;
}

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

// TTN-RFC-0007: acknowledge `orig` back to its sender on `reply`. Used both for a
// freshly-accepted want_ack toot and for re-ACKing a dedup-dropped replay (§5).
static void emitAck(const toot::Toot& orig, uint8_t status,
                    TtdbShare::SendFn reply, void* ctx) {
  toot::Toot ack;
  toot::makeAck(orig, kNodeId, gSeq++, status, ack);
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(ack, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) reply(frame, flen, ctx);
}

// Pack this node's live telemetry into a STATUS payload (Toot.h) — answered as a
// PERCEPT to CMD_GET_STATUS. Uses the last sensed reading (no I2C from a callback).
static uint8_t buildStatus(uint8_t* p) {
  float t = gAgent.readingCount() > 0 ? gAgent.reading(0).value : 0.0f;
  uint8_t flags = 0;
  if (gAgent.matchedThisCycle()) flags |= toot::STATUS_WARM;
  if (gLedOverride.enabled) flags |= toot::STATUS_LED_OVERRIDE;
  if (gSynced) flags |= toot::STATUS_SYNCED;
  toot::put_u16(p + 0, (uint16_t)(int16_t)gAgent.cursorLat());
  toot::put_u16(p + 2, (uint16_t)(int16_t)gAgent.cursorLon());
  toot::put_u16(p + 4, (uint16_t)(int16_t)(t * 100.0f));
  p[6] = flags;
  toot::put_u64(p + 7, gSynced ? (uint64_t)nowEpochMs() : 0);
#if USE_PULSE
  // Append PULSE telemetry (TTN-RFC-0010 §8) so `companion.py band` can measure phase.
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

// Serve a TTDB_REQ addressed to this node. TTDB_REQ_BELIEF streams the stored
// belief object (/belief.md) so the companion can byte-diff what we actually wrote
// (TTN-RFC-0009 §3); any other mode streams the live TTDB via the offset index.
// Both stream a TTDB_DATA burst, so radio callers must invoke this from loop()
// (not the recv callback) — see the gReqPending deferral.
static void serveTtdbReq(const toot::Toot& req, TtdbShare::SendFn send, void* ctx) {
  if (!gShare || TtdbShare::requestTarget(req) != kNodeId) return;
  if (req.payload_len >= 1 && req.payload[0] == toot::TTDB_REQ_BELIEF) {
    static uint8_t bbuf[1536];
    File f = LittleFS.open(kBeliefPath, "r");
    size_t n = f ? f.read(bbuf, sizeof(bbuf)) : 0;  // 0 bytes if no belief yet
    if (f) f.close();
    gShare->handleBufferRequest(bbuf, n, send, ctx);
  } else {
    gShare->handleRequest(req, send, ctx);
  }
}

// Dispatch a decoded, authenticated toot arriving on any transport. `reply` is
// the transport to answer on (ESP-NOW peer or serial). Dedup is a radio/mesh
// concern (replay attacks + forwarding loops), so it is NOT applied here — the
// trusted USB-CDC link is intentionally un-deduped so the laptop can retry a lost
// request. Radio callers gate on gDedup before calling in (see onEspNowRecv).
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
  bool accepted = false;
  switch (t.type) {
    case toot::TTDB_REQ:
      // The streamed TTDB_DATA reply is itself the confirmation, so a TTDB_REQ is
      // not separately ACKed. Mode selects live TTDB vs stored belief (serveTtdbReq).
      serveTtdbReq(t, reply, ctx);
      break;
    case toot::TTDB_PUT:
      // Companion pushes a re-authored belief, one offset-addressed slice per toot
      // (TTN-RFC-0009). Accept -> ACK each slice; commit + adopt on the last.
      accepted = handlePutSlice(t);
      break;
    case toot::CMD:
      // Orchestrator directive. Only the addressed node acts + ACKs, so a broadcast
      // CMD doesn't draw an ACK from every hearer. CMD is want_ack -> ACK on accept.
      // Band-wide exception: PLAY/STOP addressed to NODE_BROADCAST act on every node, so one
      // T-Deck press starts/stops the whole fleet. (Targeted PLAY/STOP still work below.)
      if (toot::cmdTarget(t) == NODE_BROADCAST &&
          (toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP)) {
        gPlayEnabled = (toot::cmdOp(t) == toot::CMD_PLAY);
        if (!gPlayEnabled) gHitPending = false;   // drop any already-scheduled note
#if USE_PULSE
        // CMD_PLAY arms the story to walk itself: as conductor we auto-advance the early
        // scenes and hold at the grief (ORDEAL) for the returning roamer (see serviceSong).
        if (gPlayEnabled) gPulse.armSong(heroarc::SCENE_ALONE, millis());
        else              gPulse.disarmSong();
#endif
        break;
      }
      // Move the band to a scene of the song. The chart belongs to the CONDUCTOR, so
      // only the conductor applies + ACKs this; everyone else ignores it and learns the
      // scene from the next beacon. That is exactly why it is safe to broadcast: at
      // most one node answers, so the operator needn't know who holds the baton.
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
        // An addressed CMD is ACKed unless a handler says otherwise. Most ops cannot
        // fail; the two that can — a duet with a malformed payload and a prune with no
        // room for its boundary marker — must NOT be ACKed, or the operator is told a
        // thing happened that did not. Hence a flag rather than the flat `accepted =
        // true` this used to end with.
        bool cmd_ok = true;
        switch (toot::cmdOp(t)) {
          case toot::CMD_SET_LED:
            if (t.payload_len >= 8) {  // op + target(4) + R,G,B
              gLedOverride.color = ((uint32_t)t.payload[5] << 16) |
                                   ((uint32_t)t.payload[6] << 8) | t.payload[7];
              gLedOverride.enabled = true;
            }
            break;
          case toot::CMD_CLEAR_LED:
            gLedOverride.enabled = false;
            break;
          case toot::CMD_GET_STATUS: {
            uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
            uint8_t slen = buildStatus(body);
            emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
            break;
          }
          case toot::CMD_GET_INTERO: {
            // "Show me your body", from the T-Deck's record pane over the air, or from
            // `companion.py intero` over the cable. buildIntero reads nothing (all cached
            // by serviceIntero) and the reply is ONE frame, so unlike a TTDB burst it is
            // safe to answer straight from the recv callback.
            uint8_t body[toot::INTERO_PERCEPT_PAYLOAD_LEN];
            uint8_t ilen = buildIntero(body);
            emit(toot::PERCEPT, body, ilen, reply, ctx);
            break;
          }
          case toot::CMD_DUET:
            // "You and I, now." Overrides this node's PART, never the chart's scene.
            cmd_ok = applyDuetCmd(t);
            break;
          case toot::CMD_SET_VIEW:
            // The console pressing `v`. This board has no reachable button, so this is
            // the ONLY way its screen ever changes. Cheap (no flash, no sensor), so it
            // runs here rather than being deferred.
            setView(toot::cmdView(t));
            break;
          case toot::CMD_CLEAR_PERCEPTS: {
            // SP1 prune, and the reason it finally exists on this board: until 2026-08-12
            // the K10 authored ONE percept lane and had no way to clear it ("reflash to
            // reset"). It now authors three, so a node with no prune path would fill
            // @LAT94/@LAT95/@LAT96 and go quietly blind — the exact failure the fleet has
            // already hit twice.
            //
            // Flash rewrite, so this reaches here only from loop(): the radio path defers
            // it (see onEspNowRecv) and the serial path already runs in loop(). ACK only
            // on success, so a failed prune is loud rather than silent.
            uint8_t lane = toot::cmdClearLane(t);   // 0 = every percept lane
            cmd_ok = (lane == TIMESTREAM_LANE)
                         ? lanegen::pruneTimeline(gDb, gStamp, kNodeId, gStreamWallSec)
                         : lanegen::prune(gDb, lane, gStamp, kNodeId, gStreamWallSec);
            if (cmd_ok)
              Serial.printf("[prune] percept lane %s cleared (TTDB now %uB, %dr)\n",
                            lane ? String(lane).c_str() : "ALL",
                            (unsigned)gDb.fileSize(), gDb.recordCount());
            else
              Serial.println("[prune] REFUSED (bad lane, or no room for the @LAT100 "
                             "boundary marker — no prune without a marker)");
            break;
          }
          case toot::CMD_BEEP: {
            int freq = 880, dur = 200;            // defaults
            if (t.payload_len >= 9) {             // op + target(4) + freq(2) + dur(2)
              freq = toot::get_u16(t.payload + 5);
              dur = toot::get_u16(t.payload + 7);
            }
            if (dur > 5000) dur = 5000;           // cap so the loop isn't stalled long
            gBeepFreq = freq;
            gBeepMs = (uint32_t)dur;
            gBeepPending = true;                  // played from loop() (k10Tone blocks)
            break;
          }
          case toot::CMD_SET_INTERVAL:
            if (t.payload_len >= 7) {
              uint16_t ms = toot::get_u16(t.payload + 5);
              if (ms < 100) ms = 100;             // floor: don't starve the loop
              gAgent.setInterval(ms);
            }
            break;
          case toot::CMD_PLAY:                    // start the song (boots silent)
            gPlayEnabled = true;
#if USE_PULSE
            gPulse.armSong(heroarc::SCENE_ALONE, millis());  // walk the story if we conduct
#endif
            break;
          case toot::CMD_STOP:                    // stop the song
            gPlayEnabled = false;
            gHitPending = false;                  // drop any already-scheduled note
#if USE_PULSE
            gPulse.disarmSong();
#endif
            break;
          default:  // CMD_PING / unknown: nothing to do but ACK
            break;
        }
        accepted = cmd_ok;  // a CMD addressed to us is acknowledged when it succeeded
      }
      break;
    case toot::TIME_SYNC: {
      // Adopt the offset here (recv-time millis() is most accurate); defer the
      // TTDB append to loop(). Exactly-once on a monotonic sync_id (TTN-RFC-0008
      // §3.1) — independent of dedup, so a retry can't double-append.
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          // The laptop supplies the DATE. It does not supply the timeline — the fleet
          // already has one — so this ANCHORS the stream instead of replacing its
          // clock. Latched here, applied by gTs.service() from loop().
          gTs.onTimeSync(ems, recv_ms, t.src_node_id);
          gLastSyncId = sid;
          gPendSyncId = sid;
          gPendEpochMs = ems;
          gPendRecvMs = recv_ms;
          gSyncPending = true;
        }
        accepted = true;  // ACK the want_ack TIME_SYNC (idempotent on replay)
      }
      break;
    }
    case toot::TIME_REQ: {
      // Skew probe: only the addressed node answers, sampling its epoch as late as
      // possible. Not want_ack — the TIME_RESP is itself the reply.
      uint32_t pid, target;
      if (toot::parseTimeReq(t, pid, target) && target == kNodeId) {
        uint8_t body[toot::TIME_RESP_PAYLOAD_LEN];
        toot::put_u32(body + 0, pid);
        toot::put_u64(body + 4, (uint64_t)nowEpochMs());
        emit(toot::TIME_RESP, body, sizeof(body), reply, ctx);
      }
      break;
    }
    case toot::PULSE: {
      // Band time-base beacon (TTN-RFC-0010). Adoption is cheap (no flash) so it
      // runs here in the recv path, where millis() is the accurate receipt time —
      // the offset adopted is conductor_epoch - recv_ms. Rendering the beat is
      // deferred to loop() (playTone blocks). Not want_ack: a miss is corrected by
      // the next beacon, so we never ACK it.
#if USE_PULSE
      pulse::Chart c;
      uint64_t cond_epoch;
      if (toot::parsePulse(t, c.conductor_id, c.era, cond_epoch, c.downbeat_epoch,
                           c.beat_period_ms, c.meter_beats, c.flags, &c.scene_id))
        gPulse.onBeacon(c, cond_epoch, millis());
#endif
      break;
    }
    case toot::HELLO:
      // A neighbor announced itself: if we conduct, fast-lock a newcomer with an
      // extra beacon (§4.2) so it joins the beat within a round trip.
#if USE_PULSE
      if (neighborNeedsLock(t.src_node_id, millis())) gPulse.noteNeighbor(millis());
#endif
      break;
    case toot::PERCEPT:
    case toot::BELIEF:
      // Neighborhood awareness lands here; nothing to do for the floor demo.
      break;
    default:
      break;
  }
  // TTN-RFC-0007: acknowledge an accepted want_ack toot exactly once on this path.
  // A replay arriving over the radio is re-ACKed in onEspNowRecv without reaching
  // here (§5), so the body is processed once and the ACK stays idempotent.
  // The time-stream anchor rides on HELLO — every node emits one every 2 s and its
  // payload was EMPTY until now, so this is purely additive: a node still on old
  // firmware sends 0 bytes and parseAnchor declines, making it a non-participant
  // rather than a parse error. Outside the USE_PULSE guard on purpose: the band is
  // optional, a shared timeline is not.
  gTs.onHello(t, millis());

  // ⚠ RECORD WHAT THIS EXECUTION DECIDED, then answer. The dedup ring replays this for a
  // retry of the same (src,seq); without it a duplicate is answered ACCEPTED regardless,
  // which reports success for work that failed (2026-08-13, CMD_CLEAR_PERCEPTS).
  // setOutcome is update-only, so the un-deduped USB path has no entry and stays that way.
  if (t.flags & toot::FLAG_WANT_ACK) {
    gDedup.setOutcome(t.src_node_id, t.toot_seq,
                      accepted ? toot::DEDUP_ACKED : toot::DEDUP_REFUSED);
    if (accepted) emitAck(t, toot::ACK_ACCEPTED, reply, ctx);
  }
}

// A chunk of a logical toot (chunk_total > 1) goes to the Reassembler, which owns
// per-chunk dedup and emits the per-chunk ACK status (TTN-RFC-0007 §6). Each call
// sends at most one ACK frame, so running it in the recv callback is not a burst.
static void handleChunk(const toot::Toot& t) {
  toot::Reassembler::Result r = gReasm.offer(t, millis());
  uint8_t status;
  switch (r) {
    case toot::Reassembler::NEED_MORE:
    case toot::Reassembler::DUPLICATE:
      status = toot::ACK_REASSEMBLY_PENDING;
      break;
    case toot::Reassembler::COMPLETE:
      Serial.printf("[reasm] (0x%08X,%u) assembled %u bytes\n",
                    (unsigned)t.src_node_id, (unsigned)t.toot_seq,
                    (unsigned)gReasm.bodyLen());
      status = toot::ACK_ACCEPTED;  // no large-toot consumer yet (Phase 6 BELIEF)
      break;
    case toot::Reassembler::COMPLETED_DUP:
      status = toot::ACK_ACCEPTED;
      break;
    case toot::Reassembler::NO_RESOURCE:
      status = toot::ACK_DROPPED_NO_RESRC;
      break;
    default:  // BAD
      return;
  }
  if (t.flags & toot::FLAG_WANT_ACK) emitAck(t, status, sendEspNow, nullptr);
}

// A TTDB_REQ arriving over ESP-NOW is stashed here and served from loop(), not
// from the recv callback: streaming the whole reply from the WiFi task would
// block its own TX (the send-complete callback can't run), starving the burst.
static volatile bool gReqPending = false;
static toot::Toot gPendingReq;

// A TTDB_PUT slice (belief push) is likewise deferred: handlePutSlice writes the
// slice to LittleFS (and the last one re-indexes), which must not run in the WiFi
// recv callback. The sender serializes slices (waits for each ACK before the next,
// TTN-RFC-0009), so a single pending slot suffices; a retransmit of an already-seen
// slice is caught by the (src,seq) dedup below and re-ACKed without touching this.
static volatile bool gPutPending = false;
static toot::Toot gPendingPut;

// CMD_CLEAR_PERCEPTS rewrites the whole TTDB file and re-indexes it, so it gets the same
// treatment: stashed here by the recv callback and run from loop(). The serial path
// already runs in loop() and does not need this.
static volatile bool gClearPending = false;
static toot::Toot gPendingClear;

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) return;
  // Chunked toots bypass the (src,seq) dedup (which would collapse sibling chunks)
  // and go to the Reassembler, which dedups per (src,seq,chunk_idx).
  if (t.chunk_total > 1) { handleChunk(t); return; }
  if (gDedup.seen(t.src_node_id, t.toot_seq)) {  // radio-path replay/loop guard
    // TTN-RFC-0007 §5: the original ACK was evidently lost (the sender retried),
    // so re-ACK the duplicate without re-processing its body.
    // ⚠ "a fresh ACCEPTED ACK is correct for an unchunked toot" — WHICH WAS WRONG, and
    // exactly the reasoning that produced the bug. It is correct only when the first
    // execution ACCEPTED. Replay that answer, including when it was silence: on
    // 2026-08-13 this path reported a failed CMD_CLEAR_PERCEPTS as APPLIED. A dup whose
    // first run refused, or has not finished, gets nothing — a false negative is loud and
    // recoverable, a false positive reads as done and stops anyone looking.
    if ((t.flags & toot::FLAG_WANT_ACK) &&
        gDedup.outcome(t.src_node_id, t.toot_seq) == toot::DEDUP_ACKED)
      emitAck(t, toot::ACK_ACCEPTED, sendEspNow, nullptr);
    return;
  }
  if (t.type == toot::TTDB_REQ) {
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }  // defer to loop()
  } else if (t.type == toot::TTDB_PUT) {
    if (!gPutPending) { gPendingPut = t; gPutPending = true; }  // flash write -> loop()
  } else if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
             toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
    if (!gClearPending) { gPendingClear = t; gClearPending = true; }  // flash -> loop()
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
#if STARTUP_TOOT
  // Boot is silent by default (RobotTeamConfig.h). Kept HERE, before initScreen(), on
  // purpose: this call playing while later tones are silent is the signature of a bad
  // TFT_BL 45 seizing the speaker pin.
  playStartupToot();        // "toot toot"
#endif
  // initScreen() is kept for what it does BESIDES LVGL: it drives eLCD_BLK high (the
  // backlight is on the mainboard power chip, not a GPIO this sketch can name) and runs
  // the panel's own init sequence. `creatCanvas()` is deliberately NOT called — it would
  // allocate 1.2 MB of PSRAM for a buffer nothing draws into, and nothing calls
  // lv_task_handler() after this line, so LVGL never touches the panel again.
  k10.initScreen(2);        // 2 = portrait, the picture-frame orientation
  k10.rgb->brightness(5);   // 0-9
  // ...and from here the panel is ours. NOTE: the K10's TFT is driven by the sketchbook
  // TFT_eSPI whose User_Setup.h must hold the K10 SPI pins (MOSI 21 / SCLK 12 / CS 14 /
  // DC 13); generic ESP32-S3 defaults there leave the panel lit but blank.
  gTft.init();
  gTft.setRotation(2);
  gTft.fillScreen(TFT_BLACK);
  gTft.setTextColor(rgb565(0, 230, 118), TFT_BLACK);
  gTft.drawString("K10", 8, 8, 4);
  gTft.setTextColor(rgb565(0, 255, 102), TFT_BLACK);
  gTft.drawString("booting...", 8, 44, 2);
#endif

  if (!LittleFS.begin(true, "/littlefs", 10, kFsLabel)) {
    Serial.println("FATAL: LittleFS mount failed");
  } else if (!gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d/%d records indexed (%d free)\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount(),
                  TTDB_MAX_RECORDS, gDb.indexHeadroom());
    // The index is a whole-FILE budget shared by every lane, so a lane with room in
    // its own cap can still be refused - and until 2026-08-11 nothing said so.
    // Saturation is worse than a refusal: records past the cap are invisible to every
    // reader, and a lane prune walks the INDEX, so before the tail-carry fix the next
    // rewrite deleted them outright. That is how five @LAT101 records died once.
    if (gDb.indexSaturated())
      Serial.printf("!! TTDB INDEX SATURATED: file holds %u records, %u INVISIBLE to\n"
                    "   every reader. Prune a lane to surface them.\n",
                    (unsigned)gDb.headersSeen(), (unsigned)gDb.droppedRecords());
    else if (gDb.indexHeadroom() <= TTDB_INDEX_WARN_SLOTS)
      Serial.printf("!! TTDB INDEX NEARLY FULL: %d slot(s) left; at 0 EVERY lane\n"
                    "   stops accepting records whatever its own cap says.\n",
                    gDb.indexHeadroom());
  }
#if USE_WIFI_SCAN
  // The board declares its own @LAT96 build at boot. ENTITYPERCEPT_MAX_RUN lives in
  // EntityPercept.cpp, a separate translation unit, so it can only be set by a BUILD
  // PROPERTY, and a build property is invisible from outside. max_run:1 is the
  // MEASUREMENT build (every window writes its own record); the default 6 folds them
  // into runs. An entity SURVEY needs both of its nodes unfolded, so which build a
  // board carries stopped being a question only the Cardputer had to answer.
  Serial.printf("[entity] @LAT96 build: max_run:%d core:%d-of-%d scan:%lus%s\n",
                ENTITYPERCEPT_MAX_RUN, ENTITYPERCEPT_CORE_N, ENTITYPERCEPT_CORE_M,
                (unsigned long)(WIFI_SCAN_PERIOD_MS / 1000),
                ENTITYPERCEPT_MAX_RUN == 1 ? "  <- MEASUREMENT BUILD (no folding)" : "");
#endif
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId,
                         gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  // Keep the WiFi radio always-on (default STA power-save adds ESP-NOW RX latency/drops);
  // helps the pulse/mesh stay responsive. (The melody-silence bug was a GPIO45 pin clash,
  // not power-save — see the TFT_BL note in CLAUDE.md / TFT_eSPI User_Setup.h.)
  esp_wifi_set_ps(WIFI_PS_NONE);
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

#if USE_BLE
  // Near-range tier: advertise + passive-scan over BLE, feeding RSSI into @LAT97 (proto:ble).
  // The K10's first direct percept source. shouldParse=false inside BleLink avoids the heap
  // churn that OOM-crashed the T-Deck — important here (camera + LCD leave little free heap).
  blelink::begin(kNodeId, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, onBleObserve);
  Serial.println("BLE near-range tier up (advert + passive scan)");
#endif

  gAgent.registerSensor(&kTempSensor);
  gAgent.registerActuator(&kIndicator);
  gAgent.setInterval(1000);
  gAgent.setMatchThreshold(8);
#if USE_PULSE
  gPulse.begin(kNodeId, millis());  // first node up conducts after the listen window
#endif

  // The time stream starts EMPTY, not with a stream of our own: this node listens for
  // TIMESTREAM_LISTEN_MS first (gTs.service), because joining an older stream is free
  // and forking one costs a merge. Independent of USE_PULSE — the band is optional, a
  // shared timeline is not.
  gTs.begin(kNodeId, &gDb, millis());

  // Declare the two new organs at boot, next to the @LAT96 build line, for the same
  // reason that line exists: what a board can actually sense is otherwise invisible from
  // outside, and a tier that is compiled out looks exactly like a tier that is quiet.
  // The scale check on the tilt is the load-bearing part — see TILT_MG_PER_LSB.
#if USE_TILT
  Serial.printf("[tilt] @LAT95/@LAT93 up: SC7A20H @0x19 via the board task, %lu Hz, "
                "%.1f mg/LSB, moving>%d mg\n",
                (unsigned long)(1000UL / TILT_POLL_MS), TILT_MG_PER_LSB,
                MOTIONPERCEPT_MOVING_MG);
#endif
#if USE_MIC
  Serial.printf("[mic] @LAT94 up: I2S_NUM_0 RX %d Hz, %u-frame blocks (the fleet's "
                "SECOND ear -- TDoA needs two)\n",
                MIC_RATE, (unsigned)MIC_TIER_FRAMES);
#endif
  Serial.printf("[view] boot view %u %s (no local button: CMD_SET_VIEW is the only way "
                "this screen changes)\n", (unsigned)gView, viewName(gView));
  Serial.printf("K10 percept node 0x%08X online\n", kNodeId);
}

void loop() {
  const uint32_t loop_t0 = millis();
  serviceIntero(loop_t0);

  // FIRST, before anything reads a clock: settle which timeline this node is on and
  // refresh gStamp. Every tier below stamps from that one snapshot, so records flushed
  // in the same pass carry the same instant rather than separate readings of a clock
  // that moved between them.
  gTs.service(millis());
  // Serve TTDB-share / commands arriving from the laptop over USB-CDC.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
      handleToot(t, sendSerial, nullptr);
  }

#if USE_PULSE
  // --- fleet pulse (TTN-RFC-0010): keep time; glance at the conductor rarely -----
  {
    uint32_t pnow = millis();
    // Emit a chart beacon only when due (drift-paced, §5) or to fast-lock a newcomer
    // (§4.2) — never one per beat. As a lone node this fires once, then every 30 s.
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags, oc.scene_id);
      emit(toot::PULSE, body, blen, sendEspNow, nullptr);
      Serial.printf("[pulse] beacon era=%lu cond=0x%08X period=%ums scene=%u%s\n",
                    (unsigned long)oc.era, (unsigned)oc.conductor_id,
                    oc.beat_period_ms, oc.scene_id,
                    gPulse.conductor() ? " (conductor)" : "");
    }
    // As conductor, walk the story: auto-advance the early scenes on SCENE_HOLD_MS and
    // hold at the grief (ORDEAL) until the returning T-Deck drives the RETURN/FINALE.
    gPulse.serviceSong(pnow, heroarc::SCENE_HOLD_MS, heroarc::SCENE_ORDEAL);
    // The chart's scene moved (or we just joined a band mid-song): this is the seam
    // where this node re-selects the phrase it plays, via score::phraseForScene below.
    uint16_t new_scene;
    if (gPulse.sceneChanged(new_scene))
      Serial.printf("[scene] scene %u %s (era %lu cond 0x%08X)\n", new_scene,
                    heroarc::sceneName(new_scene),
                    (unsigned long)gPulse.chart().era,
                    (unsigned)gPulse.chart().conductor_id);
    // OUR PART: the scene selects the phrase (HeroArc.h — no row means SILENT in that
    // scene, and for the percept leaf that is every scene but the finale). The step clock
    // runs through the silent scenes, so the entrance lands on the grid rather than
    // wherever the node happened to notice.
    //
    // A DUET overrides the phrase AND the scene's silence for as long as it lasts: the
    // pair was asked for by name, and the step clock underneath is the same one the band
    // is counting.
    const score::Phrase* ph;
    bool voice;
    uint8_t speed = 1;
    if (duetOn()) {
      ph = (gDuetRole == toot::DUET_LEAD) ? &heroarc::kOdeLead : &heroarc::kOdeHarm;
      voice = true;
      speed = gDuetSpeed;             // already validated against this phrase by setDuet
    } else {
      ph = score::phraseForScene(kPart, gPulse.scene());
      voice = gPlayEnabled;           // boots silent; only between CMD_PLAY and CMD_STOP
    }
    // DOUBLE TIME is these two lines: wrap the phrase in `steps/speed` slots and look the
    // note up at `sip*speed`. The pulse clock and beat period are untouched, so the pair
    // covers the written phrase in half the steps while staying locked to the beat the
    // rest of the fleet counts. ONE stepTick per pass — the call consumes the tick.
    const uint16_t steps = ph ? (uint16_t)(ph->steps / speed) : 16;
    uint16_t sip;
    uint32_t sc;
    static uint32_t prev_step = 0;
    static bool have_prev = false;
    if (gPulse.stepTick(pnow, steps, sip, sc)) {
      // Catch up over any steps this pass jumped, so a stalled pass cannot swallow the
      // note that fell in the gap. Defensive, and this node needs it more than most: a
      // percept flush, a blocking tone AND a full eye repaint can each exceed one step.
      const score::Note* nt = nullptr;
      if (ph)
        nt = (have_prev && sc > prev_step + 1)
                 ? score::noteForCrossedSteps(*ph, prev_step, sc, speed, steps)
                 : score::noteAt(*ph, (uint16_t)(sip * speed));
      prev_step = sc;
      have_prev = true;
      if (voice && nt && nt->freq != score::REST) {
        gHitFreq = nt->freq;
        gHitMs = PULSE_TONE_MS / speed;
        if (gHitMs < 80) gHitMs = 80;
        gHitColor = pitchColor(nt->freq);
        gHitDueMs = pnow + pulseHumanize();
        gHitPending = true;
        if (duetOn())
          Serial.printf("[part] step %2u/%u  %4uHz (%s x%u)\n", sip, steps, nt->freq,
                        gDuetRole == toot::DUET_LEAD ? "duet-lead" : "duet-harm", speed);
        else
          Serial.printf("[part] step %2u/%u  %4uHz  scene %s cond=0x%08X era=%lu\n",
                        sip, steps, nt->freq, heroarc::sceneName(gPulse.scene()),
                        (unsigned)gPulse.chart().conductor_id,
                        (unsigned long)gPulse.chart().era);
      }
    }
    // Fire a scheduled hit: toot (via the deferred-beep path) + LED flash.
    if (gHitPending && (int32_t)(pnow - gHitDueMs) >= 0) {
      gHitPending = false;
      gBeepFreq = gHitFreq;
      gBeepMs = gHitMs;               // k10Tone takes ms directly
      gBeepPending = true;            // played from the deferred-beep block below
#if USE_K10_HW
      if (!gLedOverride.enabled) {    // a laptop set-led still wins (RFC §7.2)
        k10.rgb->write(-1, gHitColor);
        gLedClearMs = pnow + PULSE_LED_MS;
      }
#endif
    }
    // Clear the LED flash after its window (non-blocking).
    if (gLedClearMs && (int32_t)(pnow - gLedClearMs) >= 0) {
      gLedClearMs = 0;
#if USE_K10_HW
      if (!gLedOverride.enabled) k10.rgb->write(-1, 0x000000);
#endif
    }
  }
#endif

  // Serve an ESP-NOW TTDB_REQ deferred from the recv callback (so the reply
  // streams from the main task, where TX pacing via the send callback works).
  if (gReqPending) {
    gReqPending = false;
    serveTtdbReq(gPendingReq, sendEspNow, nullptr);  // live TTDB or belief, by mode
  }

  // Serve an ESP-NOW TTDB_PUT (belief slice) deferred from the recv callback: the
  // slice write (and, on the final slice, the CRC-verify + re-index) is a flash op
  // that must run on the main task. handleToot writes the slice and ACKs it back
  // over ESP-NOW; the live-TTDB adoption append is itself deferred via gBeliefSyncPending.
  if (gPutPending) {
    gPutPending = false;
    handleToot(gPendingPut, sendEspNow, nullptr);
  }

  // Serve an ESP-NOW CMD_CLEAR_PERCEPTS deferred from the recv callback: a prune is a
  // whole-file rewrite plus a re-index plus the @LAT100 boundary append, none of which
  // may run on the WiFi task.
  if (gClearPending) {
    gClearPending = false;
    handleToot(gPendingClear, sendEspNow, nullptr);
  }

#if USE_TILT && USE_K10_HW
  // --- SP0 MOTION TIER: was this node standing still? (@LAT95, and @LAT93 for the edge)
  serviceTilt(millis());
  if (gMotionLog.due(millis())) {
    const uint32_t mnow = millis();
    int lane = laneCount(95);
    if (lane >= MOTIONPERCEPT_MAX_LANE) {
      // SAY THIS OUT LOUD. A full motion lane looks exactly like a healthy node: the
      // other tiers keep flushing and the windows are dropped in silence. On this board
      // it should take ~24 h of uptime to reach the cap (the lane is change-triggered
      // with run-length); if it fills fast, the frame is being knocked or is flapping at
      // the threshold, which is itself the finding.
      static uint32_t last_mot_full_log = 0;
      if (mnow - last_mot_full_log > 300000 || last_mot_full_log == 0) {
        last_mot_full_log = mnow;
        Serial.printf("[motion] @LAT95 lane FULL (%d/%d) - windows are being DISCARDED. "
                      "Prune with `companion.py cmd --op clear-percepts --lane 95`. "
                      "(threshold %d mg)\n",
                      lane, MOTIONPERCEPT_MAX_LANE, MOTIONPERCEPT_MOVING_MG);
      }
      gMotionLog.reset(mnow);
    } else {
      char rec[MOTIONPERCEPT_RECORD_BUF];
      size_t m = gMotionLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                        gStamp, mnow);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[motion] percept window -> @LAT95LON%d covers:%d (TTDB %uB)\n",
                      lane, gMotionLog.runOffset() + 1, (unsigned)gDb.fileSize());
      else if (gMotionLog.lastClose() == motionpercept::CLOSE_COVERED)
        // ⚠ Under run-length "wrote nothing" is the NORMAL case for a picture frame on a
        // shelf — which is what this node is, nearly always. Branch on lastClose(), never
        // on the byte count, and say the run length out loud so a working fold can be
        // told from a dead tier.
        Serial.printf("[motion] window covered (run %d)\n", gMotionLog.runOffset() + 1);

      // The TRANSITION form (TTDB-RFC-0006 §5): the window above is a STATE, this is the
      // DIFFERENCE between it and the one before — and per §5.2 the difference is the
      // datum. Written only on a verdict change, so a frame that has not been touched
      // writes none at all. Must run before the next buildRecord(), which would overwrite
      // the `after` half.
      if (gMotionLog.transitionPending()) {
        int tlane = laneCount(MOTIONPERCEPT_TRANSITION_LANE);
        if (tlane >= MOTIONPERCEPT_MAX_TRANSITION_LANE) {
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

#if USE_MIC && USE_K10_HW
  // --- SP0 ACOUSTIC TIER: what this node heard (@LAT94) -------------------------------
  // The fleet's SECOND ear. Everything about this block is a copy of the Cardputer's,
  // deliberately, because the value is in the two lanes being comparable: a transient
  // logged here and a transient logged there are the same measurement of the same event
  // only if they were computed the same way.
  serviceMic(millis());
  if (gAcousticLog.due(millis())) {
    const uint32_t anow = millis();
    int lane = laneCount(94);
    if (lane >= ACOUSTICPERCEPT_MAX_LANE) {
      static uint32_t last_ac_full_log = 0;
      if (anow - last_ac_full_log > 300000 || last_ac_full_log == 0) {
        last_ac_full_log = anow;
        Serial.printf("[acoustic] @LAT94 lane FULL (%d/%d) - windows are being "
                      "DISCARDED. Prune with `companion.py cmd --op clear-percepts "
                      "--lane 94`.\n", lane, ACOUSTICPERCEPT_MAX_LANE);
      }
      gAcousticLog.reset(anow);
    } else {
      char rec[400];
      size_t m = gAcousticLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                          gStamp, anow, MIC_RATE);
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[acoustic] percept window -> @LAT94LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

#if USE_BLE
  // SP0: flush the BLE link-percept window into the @LAT97 lane. Flash write, so it runs
  // from loop() (never the BLE scan task). Lane-capped; pruned by CMD_CLEAR_PERCEPTS
  // --lane 97 like every other tier. The K10's first self-authored proximity evidence.
  if (gLinkLog.due(millis())) {
    int lane = laneCount(97);
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
#endif

#if USE_WIFI_SCAN
  // SP0 entity tier: run the duty-cycled scan, then flush its window into the @LAT96
  // lane (same defer-to-loop + lane-cap discipline as the @LAT97 link lane). The K10's
  // first self-authored proximity evidence, and until 2026-08-12 its only one.
  serviceWifiScan();
  if (gEntityLog.due(millis())) {
    int lane = laneCount(96);
    if (lane >= ENTITYPERCEPT_MAX_LANE) {
      // SAY THIS OUT LOUD -- the same argument @LAT95 got after 2026-08-02, and it
      // cost a live debugging session on 2026-08-10 to notice @LAT96 never got it.
      // A full entity lane looks EXACTLY like a healthy node: the scan still runs and
      // prints, the other tiers still flush, and the window is dropped in silence.
      // Rate-limited to one line per 5 min so it informs without flooding.
      static uint32_t last_ent_full_log = 0;
      uint32_t nowf = millis();
      if (nowf - last_ent_full_log > 300000 || last_ent_full_log == 0) {
        last_ent_full_log = nowf;
        Serial.printf("[entity] @LAT96 lane FULL (%d/%d) - windows are being "
                      "DISCARDED. Prune with `companion.py cmd --op clear-percepts "
                      "--lane 96`.\n", lane, ENTITYPERCEPT_MAX_LANE);
      }
      gEntityLog.reset(nowf);      // lane full: drop the window, keep observing
    } else {
      // static + ENTITYPERCEPT_RECORD_BUF: since @LAT96 became change-triggered a
      // record can carry a **CORE** list and the run's **COVERED** union (worst
      // case 2322 B, pinned in tests/test_entitypercept.cpp). That fits neither the
      // old 1024 nor the loop task's stack, and buildRecord writes NOTHING rather
      // than truncating -- so an undersized buffer here loses windows silently.
      static char rec[ENTITYPERCEPT_RECORD_BUF];
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[entity] percept window -> @LAT96LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
      else if (gEntityLog.lastClose() == entitypercept::CLOSE_COVERED)
        // SAY THIS OUT LOUD. Under run-length "wrote nothing" is the NORMAL case
        // for a node in a stable environment, and a lane that silently does nothing
        // is this corpus's least favourite failure mode. The run length and core
        // size are how an operator tells a working fold from a dead tier.
        Serial.printf("[entity] window covered (run %d, core %d)\n",
                      gEntityLog.runLength(), gEntityLog.coreCount());
    }
  }
#endif

  // Write the TIME_SYNC log record deferred from the recv path (TTN-RFC-0008 §4):
  // a new @LAT99LON<n> record, where n is the count of existing lat-99 records so
  // each is unique under collision_policy: reject. Header times are unix seconds
  // (timestamp_kind: unix); ms precision lives in the body.
  if (gSyncPending) {
    gSyncPending = false;
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

  // Log a CRC-verified pushed belief to the live TTDB (TTN-RFC-0009 §4), deferred
  // from the recv/put path: a new @LAT98LON<n> record (n = count of existing lat-98
  // records, unique under collision_policy: reject). The belief bytes themselves
  // live in /belief.md; this is the node's append-only attestation of adoption.
  if (gBeliefSyncPending) {
    gBeliefSyncPending = false;
    // Act on the belief's DIRECTIVE — this is the Dream Cycle closing: a pushed,
    // re-authored belief changes node behavior, not just stored state (Phase 6).
    // Retune the sense->reason->act cadence; the attestation records what took effect.
    uint32_t interval = parseBeliefDirective();
    if (interval >= 100)              // floor: don't starve the loop / watchdog
      gAgent.setInterval(interval);
    uint32_t effective = gAgent.intervalMs();
    int n = 0;
    for (int i = 0; i < gDb.recordCount(); ++i)
      if (gDb.record(i).lat == 98) ++n;
    uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
    char rec[256];
    int m = snprintf(
        rec, sizeof(rec),
        "\n---\n\n@LAT98LON%d | created:%lu | updated:%lu | relates:adopts@LAT0LON0"
        "\n\n**BELIEF-ADOPTED** id:%lu bytes:%lu crc:%08lX recv_ms:%lu "
        "applied:interval_ms:%lu\n",
        n, (unsigned long)t_sec, (unsigned long)t_sec,
        (unsigned long)gPendBeliefId, (unsigned long)gPendBeliefBytes,
        (unsigned long)gPendBeliefCrc, (unsigned long)gPendBeliefRecvMs,
        (unsigned long)effective);
    if (m > 0 && gDb.appendRecord(rec, (size_t)m))
      Serial.printf("[belief] adopted id=%lu %luB crc=%08lX -> @LAT98LON%d "
                    "(TTDB %uB) cadence=%lums\n",
                    (unsigned long)gPendBeliefId, (unsigned long)gPendBeliefBytes,
                    (unsigned long)gPendBeliefCrc, n, (unsigned)gDb.fileSize(),
                    (unsigned long)effective);
    else
      Serial.println("[belief] appendRecord FAILED");
  }

  // Play a deferred CMD_BEEP / melody hit from the main task (k10Tone blocks ~ms).
  if (gBeepPending) {
    gBeepPending = false;
#if USE_K10_HW
    k10Tone(gBeepFreq, gBeepMs);   // fleet square voice @ T-Deck loudness
#endif
    Serial.printf("[beep] %d Hz, %lu ms\n", gBeepFreq, (unsigned long)gBeepMs);
  }

  // Periodic HELLO beacon + percept tick.
  static uint32_t last = 0;
  if (millis() - last >= gAgent.intervalMs()) {
    last = millis();
    indicatorClear();   // LEDs off unless this cycle's TTDB trigger re-lights
    gAgent.sense();
    gAgent.reason();
    gAgent.act();
#if USE_K10_HW
    // A laptop set-led overrides the local indicator until clear-led (companion.md
    // §4b) — applied after act() so the orchestrator's command wins this cycle.
    if (gLedOverride.enabled) k10.rgb->write(-1, gLedOverride.color);
#endif
    Serial.printf("[cycle] cursor @LAT%dLON%d match=%d led=%s\n", gAgent.cursorLat(),
                  gAgent.cursorLon(), gAgent.matchedThisCycle(),
                  gLedOverride.enabled ? "laptop" : "agent");
    uint8_t hb[timestream::ANCHOR_LEN];
    size_t hn = gTs.helloPayload(hb, sizeof(hb), millis());
    emit(toot::HELLO, hn ? hb : nullptr, hn, sendEspNow, nullptr);
  }

#if USE_K10_HW
  // The screen runs on its OWN clock, no longer on the agent's sense/act cadence. Those
  // two were fused only because the old canvas screen showed the agent and nothing else;
  // the eye answers to the beat and to two sensors that have nothing to do with a
  // reasoning cycle, and `set-interval` must not be able to change how alive the face is.
  serviceScreen(millis());
#endif

  // Close the profiler window. Published every 10 s so `lp` reports a RECENT worst case
  // rather than a boot spike that never clears — the same per-window discipline the other
  // four nodes use, which is what makes their `lp` numbers comparable to this one's.
  //
  // ⚠ EXPECT THIS NODE'S `lp` TO RISE WITH THE EYE. A full sclera repaint is ~70k pixels
  // at 20 MHz ≈ 56 ms of SPI, and it happens on entering the view and on every blink.
  // That is a real cost, it is bounded, and it is worth knowing rather than hiding: a
  // blink you can see in the loop profiler is a blink you can rule out as a cause.
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
