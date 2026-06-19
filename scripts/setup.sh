#!/usr/bin/env bash
# setup.sh — one-time arduino-cli setup for robot_team.
# Installs the ESP32 core and the libraries needed beyond the shared ones in
# firmware/libraries (which are passed per-build with --libraries).
set -euo pipefail

command -v arduino-cli >/dev/null || {
  echo "arduino-cli not found. Install from https://arduino.github.io/arduino-cli/"
  exit 1
}

arduino-cli config init --overwrite
# ESP32 boards manager URL.
arduino-cli config add board_manager.additional_urls \
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32

echo
echo "Installed cores:"
arduino-cli core list
echo
echo "k10_percept needs the DFRobot 'unihiker_k10' library (AHT20 + RGB LED)."
echo "  It is distributed via the UNIHIKER K10 wiki, not the Arduino registry:"
echo "  install the zip there, or drop it in firmware/libraries/ (picked up by"
echo "  --libraries). To build without it, set USE_K10_HW 0 in the sketch."
echo
echo "Phase 4 (LoRa) will also need:  arduino-cli lib install RadioLib"
echo "Done. Build with scripts/build.sh, deploy with scripts/deploy.sh."
