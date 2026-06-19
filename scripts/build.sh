#!/usr/bin/env bash
# build.sh — compile one node sketch with arduino-cli.
#
#   scripts/build.sh <node> [fqbn]
#   node : k10_percept | v4a_bridge | v4b_relay | v4c_edge
#
# The shared libraries in firmware/libraries are added with --libraries so they
# need not be copied into ~/Arduino/libraries.
set -euo pipefail

NODE="${1:?usage: build.sh <node> [fqbn]}"
FQBN_DEFAULT="esp32:esp32:esp32s3"
FQBN="${2:-$FQBN_DEFAULT}"

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SKETCH="$ROOT/firmware/$NODE"
LIBS="$ROOT/firmware/libraries"

[ -d "$SKETCH" ] || { echo "no sketch: $SKETCH"; exit 1; }

echo "Compiling $NODE for $FQBN ..."
arduino-cli compile \
  --fqbn "$FQBN" \
  --libraries "$LIBS" \
  --warnings default \
  "$SKETCH"
echo "OK: $NODE compiled."
