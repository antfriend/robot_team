// Arduino.h — minimal native shim so the REAL TTDB.cpp can be compiled and tested off
// hardware. Not an Arduino emulation: it provides exactly what TTDB.cpp touches.
//
// WHY THIS EXISTS. `tests/test_rfc_ttdb.cpp` had to REPLICATE Ttdb::begin()'s two-pass
// scan in native code because it could not call it — and a replica of a function is a
// second implementation that drifts. It already had: the replica carries
// `#define TTDB_MAX_RECORDS 256` while the firmware moved to 288 on 2026-08-09. A test
// that re-implements the thing it is testing cannot catch a bug in the original.
#pragma once
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstring>

// The watchdog feed. On hardware this yields to FreeRTOS; here the loops just run.
inline void yield() {}
