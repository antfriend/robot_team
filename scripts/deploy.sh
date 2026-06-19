#!/usr/bin/env bash
# deploy.sh — compile + upload firmware for one node with arduino-cli.
#
#   scripts/deploy.sh <node> <port> [fqbn]
#
# This flashes firmware only. The TTDB filesystem image is flashed separately
# with scripts/upload-fs.sh (arduino-cli has no built-in filesystem upload).
set -euo pipefail

NODE="${1:?usage: deploy.sh <node> <port> [fqbn]}"
PORT="${2:?usage: deploy.sh <node> <port> [fqbn]}"
FQBN="${3:-esp32:esp32:esp32s3}"

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SKETCH="$ROOT/firmware/$NODE"
LIBS="$ROOT/firmware/libraries"

echo "Compiling + uploading $NODE to $PORT ($FQBN) ..."
arduino-cli compile --fqbn "$FQBN" --libraries "$LIBS" "$SKETCH"
arduino-cli upload --fqbn "$FQBN" --port "$PORT" "$SKETCH"
echo "OK: $NODE firmware on $PORT."
echo "Next: scripts/upload-fs.sh $NODE $PORT   # flash its TTDB to LittleFS"
