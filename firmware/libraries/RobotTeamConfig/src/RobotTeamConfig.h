// RobotTeamConfig.h — shared, swarm-wide constants.
//
// PROTOTYPE KEY: replace ROBOT_TEAM_KEY before any deployment outside the bench.
// It must match the key in orchestrator/companion.py for the companion to
// verify and request TTDB from a node.
#pragma once
#include <stdint.h>

// 16-byte shared HMAC key. Keep in sync with companion.py NETWORK_KEY.
static const uint8_t ROBOT_TEAM_KEY[16] = {
    0x72, 0x6f, 0x62, 0x6f, 0x74, 0x5f, 0x74, 0x65,
    0x61, 0x6d, 0x5f, 0x6b, 0x65, 0x79, 0x30, 0x31};
static const uint8_t ROBOT_TEAM_KEY_LEN = 16;

// Prototype: pin every board to one ESP-NOW channel (no AP). See
// toot_network_architecture.md section 3.
static const uint8_t ROBOT_TEAM_ESPNOW_CHANNEL = 1;

// --- boot voice --------------------------------------------------------------
// THE FLEET BOOTS SILENTLY. One switch for every node — flip to 1 and reflash to get
// the "toot toot" signature back on all six.
//
// This gates only the AUTOMATIC play at boot. Every node's `playStartupToot()` and its
// whole tone path stay compiled and callable, deliberately, because **the boot toot is
// the fleet's audio smoke test and each board's audio was hard-won in a different way**:
//
//   K10        GPIO45 is the I2S SPEAKER, not the LCD backlight. Defining TFT_BL 45 in
//              the shared TFT_eSPI User_Setup.h makes tft.begin() seize the pin and
//              silence everything after initScreen() — and the tell is that the startup
//              toot, which runs BEFORE initScreen, still plays. That diagnostic only
//              works if the toot is available; keep it one #define away.
//   V4 a/b/c   The hand-wired MAX98357A only reproduces SQUARE waves at 8 kHz; sine
//              stutters and clicks.
//   T-Deck     I2S MAX98357A via the core's ESP_I2S — no analog tone path at all, and
//              the speaker rail depends on PIN_POWERON being asserted first.
//   Cardputer  Everything goes through an ES8311 codec that must be register-configured
//              before the speaker exists. The board routes NO MCLK, so the codec derives
//              it from BCLK, which only holds while I2S runs 16-bit STEREO. DAC volume
//              (reg 0x32) is 0.5 dB/step with unity at 0xBF, NOT a linear 0..255.
//
// Re-enabling is one line. Re-deriving any of the above is not. Do not delete the
// disabled path, and do not #if out the functions themselves — keeping them compiled is
// what stops them rotting when a tone signature changes.
#ifndef STARTUP_TOOT
#define STARTUP_TOOT 0
#endif

// Stable logical node ids (src_node_id in the toot header). Not MAC-derived so
// they survive board swaps.
enum RobotTeamNodeId : uint32_t {
  NODE_ORCHESTRATOR = 0x00000001,
  NODE_V4A_BRIDGE = 0x00000010,
  NODE_V4B_RELAY = 0x00000011,
  NODE_V4C_EDGE = 0x00000012,
  NODE_K10_1 = 0x00000100,
  NODE_K10_2 = 0x00000101,
  NODE_K10_3 = 0x00000102,
  NODE_TDECK_1 = 0x00000200,  // LilyGo T-Deck handheld console / field operator
  NODE_CARDPUTER_1 = 0x00000300,  // M5Stack Cardputer ADV — 2nd handheld; the fleet's
                                  // motion + acoustic sense organ (BMI270 + ES8311 mic)
  // Wildcard CMD target: a CMD addressed here is honored by every node, not one. Only
  // band-wide ops (CMD_PLAY / CMD_STOP) act on it; targeted ops (get-status, set-led,
  // beep) still require an exact node id so a broadcast doesn't storm replies/ACKs.
  NODE_BROADCAST = 0xFFFFFFFF,
};
