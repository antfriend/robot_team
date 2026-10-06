#!/usr/bin/env bash
# flash_count.sh <sketch> <port> <banner-literal> <fqbn> [tag]
# Compile+upload, then reset 5x and catch each boot: banner present, crash lines.
set -u
export PYTHONIOENCODING=utf-8
S=$1; P=$2; B=$3; F=$4; T=${5:-settle5}
ACLI="/c/Program Files/Arduino CLI/arduino-cli.exe"
"$ACLI" compile --upload -p "$P" --fqbn "$F" --libraries firmware/libraries "firmware/$S" 2>&1 \
  | grep -E "Sketch uses|Hash of data verified|error|Failed" | head -3
for i in 1 2 3 4 5; do
  python -m esptool --chip esp32s3 --port "$P" --after hard-reset chip-id >/dev/null 2>&1
  python scratchpad/catchboot.py "$P" 20 > "scratchpad/${S}_${T}_boot$i.txt" 2>&1
  echo "boot $i: $(grep -a -c "$B" "scratchpad/${S}_${T}_boot$i.txt") banner, $(grep -a -c -E 'abort|panic|Guru|Backtrace|canary' "scratchpad/${S}_${T}_boot$i.txt") crash"
done
grep -a -E "TTDB loaded|@LAT96 build|cap [0-9]+" "scratchpad/${S}_${T}_boot5.txt" | grep -o -E "TTDB loaded: [^(]*\([0-9]+ free\)|max_run:[0-9]+|cap [0-9]+" | head -3
grep -a -o -E "\[grammar\] 0x[0-9a-f]+.*" "scratchpad/${S}_${T}_boot5.txt" | head -1
