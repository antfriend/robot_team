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
};
