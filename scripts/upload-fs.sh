#!/usr/bin/env bash
# upload-fs.sh — build a LittleFS image from a node's data/ and flash it.
#
#   scripts/upload-fs.sh <node> <port> [fs_size_bytes] [fs_offset]
#
# arduino-cli does not upload filesystems, so we use mklittlefs + esptool
# directly. Defaults assume a 16 MB module with a common partition layout; for a
# non-default partition table, pass the size/offset from your partitions CSV.
set -euo pipefail

NODE="${1:?usage: upload-fs.sh <node> <port> [size] [offset]}"
PORT="${2:?usage: upload-fs.sh <node> <port> [size] [offset]}"
FS_SIZE="${3:-0x180000}"     # 1.5 MB LittleFS (default_16MB.csv spiffs region)
FS_OFFSET="${4:-0x670000}"   # offset of that region; verify against your CSV

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DATADIR="$ROOT/firmware/$NODE/data"
IMG="$ROOT/firmware/$NODE/littlefs.bin"

command -v mklittlefs >/dev/null || {
  echo "mklittlefs not found. It ships with the arduino-esp32 tools; add it to PATH"
  echo "or install from https://github.com/earlephilhower/mklittlefs"
  exit 1
}
command -v esptool.py >/dev/null || command -v esptool >/dev/null || {
  echo "esptool not found. pip install esptool"
  exit 1
}
ESPTOOL="$(command -v esptool.py || command -v esptool)"

echo "Building LittleFS image from $DATADIR (size $FS_SIZE) ..."
mklittlefs -c "$DATADIR" -s "$((FS_SIZE))" "$IMG"

echo "Flashing $IMG to $PORT at $FS_OFFSET ..."
"$ESPTOOL" --chip esp32s3 --port "$PORT" --baud 921600 \
  write_flash "$FS_OFFSET" "$IMG"
echo "OK: $NODE TTDB flashed. Verify offsets against the board's partition CSV."
