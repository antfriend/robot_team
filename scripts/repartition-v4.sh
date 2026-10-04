#!/usr/bin/env bash
# repartition-v4.sh — move a Heltec V4 from the default 4MB table to huge_app, keeping its
# LittleFS store byte-exact (first done on V4-A, 2026-10-04; see CLAUDE.md).
#
#   scripts/repartition-v4.sh <PORT> <sketch> <node> <build-dir>
#   e.g. scripts/repartition-v4.sh COM9 v4b_relay v4b_relay /c/tmp/b_v4b_h
#
# <build-dir> must hold a huge_app build of <sketch> (arduino-cli compile --build-path …
# --fqbn "esp32:esp32:esp32s3:CDCOnBoot=cdc,PartitionScheme=huge_app"). Identify the
# board by MAC and read its banner BEFORE running this. Stops at the first mismatch.
set -euo pipefail
PORT=$1 SKETCH=$2 NODE=$3 B=$4
W=scratchpad/repart_${NODE}
MK=$(find /c/Users/antfr/AppData/Local/Arduino15/packages/esp32/tools -name mklittlefs.exe | head -1)
mkdir -p "$W"

# The new table must be what we think: FS at 0x310000, 0xE0000; nvs unmoved.
python - "$B/$SKETCH.ino.partitions.bin" <<'EOF'
import struct, sys
d = open(sys.argv[1], "rb").read()
t = {}
for i in range(0, len(d), 32):
    e = d[i:i + 32]
    if e[:2] != b"\xaa\x50":
        break
    t[e[12:28].rstrip(b"\0").decode()] = struct.unpack("<II", e[4:12])
assert t.get("spiffs") == (0x310000, 0xE0000), t
assert t.get("nvs") == (0x9000, 0x5000), t
print("partition table OK:", {k: (hex(a), hex(b)) for k, (a, b) in t.items()})
EOF

# 1. Back up the old FS partition raw and unpack every file.
python -m esptool --chip esp32s3 --port "$PORT" --baud 460800 read-flash 0x290000 0x160000 "$W/spiffs_old.bin"
[ "$(stat -c %s "$W/spiffs_old.bin")" = "1441792" ] || { echo "short read"; exit 1; }
rm -rf "$W/files" && "$MK" -u "$W/files" -p 256 -b 4096 -s 0x160000 "$W/spiffs_old.bin"
[ -s "$W/files/ttdb.md" ] || { echo "no ttdb.md in the old FS"; exit 1; }

# Cross-check against the node's own pull (a second, independent path).
python orchestrator/fleet.py pull --port "$PORT" --node "$NODE" --out "master/${NODE}_pre_repartition_$(date +%F).md"
cmp "$W/files/ttdb.md" "master/${NODE}_pre_repartition_$(date +%F).md"
echo "backup: raw unpack == pull"

# 2. New image at the huge_app size; must round-trip.
"$MK" -c "$W/files" -p 256 -b 4096 -s 0xE0000 "$W/spiffs_new.bin"
rm -rf "$W/check" && "$MK" -u "$W/check" -p 256 -b 4096 -s 0xE0000 "$W/spiffs_new.bin" >/dev/null
diff -r "$W/files" "$W/check"
echo "new image round-trips"

# 3. Everything in ONE session, so the new app never boots against an empty store.
python -m esptool --chip esp32s3 --port "$PORT" --baud 460800 --before default-reset --after hard-reset \
  write-flash -z --flash-mode keep --flash-freq keep --flash-size keep \
  0x0 "$B/$SKETCH.ino.bootloader.bin" 0x8000 "$B/$SKETCH.ino.partitions.bin" \
  0xe000 "$B/boot_app0.bin" 0x10000 "$B/$SKETCH.ino.bin" 0x310000 "$W/spiffs_new.bin"
echo "flashed. Now boot-count: the banner must show TTDB loaded: $(stat -c %s "$W/files/ttdb.md") bytes"
