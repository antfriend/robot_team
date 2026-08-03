#!/usr/bin/env bash
# Build + run the native suite without GNU make, which is not on this machine either.
#
# The dev box has no g++ and no make; the portable `zig c++` lives at the path below,
# now under c:/tmp (NOT the session scratchpad, which is wiped between sessions — that
# is why the toolchain has had to be re-downloaded three times, see
# [[no-host-cpp-toolchain]]).
#
#   scratchpad/t.sh              # build + run everything
#   scratchpad/t.sh perceptlearn # just one
set -u
cd "$(dirname "$0")/.."

ZIG="${ZIG:-/c/tmp/toolchain/zig-windows-x86_64-0.13.0/zig.exe}"
[ -x "$ZIG" ] || { echo "no zig at $ZIG"; exit 1; }
LIB=firmware/libraries
INC="-I$LIB/Toot/src -I$LIB/TTDB/src -I$LIB/LinkPercept/src -I$LIB/EntityPercept/src
     -I$LIB/MotionPercept/src -I$LIB/PerceptLearn/src -I$LIB/Gps/src -I$LIB/Pulse/src
     -I$LIB/TimeStream/src -I$LIB/LaneGen/src"
FLAGS="-std=c++11 -Wall -Wextra -O2"

# name : extra sources (test_<name>.cpp is implied)
build_one() {
  local name="$1"; shift
  # shellcheck disable=SC2086
  "$ZIG" c++ $FLAGS $INC "tests/test_$name.cpp" "$@" -o "tests/test_$name.exe" || return 1
}

declare -a NAMES=(toot linkpercept entitypercept motionpercept perceptlearn
                  rfc_ttdb symmetric_edges nmea pulse timestream lanegen)
declare -A SRCS=(
  [toot]="$LIB/Toot/src/Toot.cpp $LIB/Toot/src/TootCrypto.cpp $LIB/TTDB/src/TtdbParse.cpp"
  [linkpercept]="$LIB/TimeStream/src/TimeStream.cpp $LIB/LinkPercept/src/LinkPercept.cpp"
  [entitypercept]="$LIB/TimeStream/src/TimeStream.cpp $LIB/EntityPercept/src/EntityPercept.cpp"
  [motionpercept]="$LIB/TimeStream/src/TimeStream.cpp $LIB/MotionPercept/src/MotionPercept.cpp"
  [perceptlearn]="$LIB/TimeStream/src/TimeStream.cpp $LIB/PerceptLearn/src/PerceptLearn.cpp"
  [rfc_ttdb]="$LIB/TTDB/src/TtdbParse.cpp"
  [symmetric_edges]="$LIB/TTDB/src/TtdbParse.cpp"
  [nmea]="$LIB/Gps/src/Nmea.cpp"
  [pulse]="$LIB/Toot/src/Toot.cpp $LIB/Toot/src/TootCrypto.cpp $LIB/Pulse/src/Pulse.cpp"
  [timestream]="$LIB/TimeStream/src/TimeStream.cpp"
  [lanegen]="$LIB/TimeStream/src/TimeStream.cpp $LIB/LaneGen/src/LaneGen.cpp"
)

if [ $# -gt 0 ]; then NAMES=("$@"); fi

fail=0
for n in "${NAMES[@]}"; do
  printf '=== %s ===\n' "$n"
  # shellcheck disable=SC2086
  if ! build_one "$n" ${SRCS[$n]}; then echo "BUILD FAILED: $n"; fail=1; continue; fi
  ( cd tests && "./test_$n.exe" ) || { echo "RUN FAILED: $n"; fail=1; }
done
exit $fail
