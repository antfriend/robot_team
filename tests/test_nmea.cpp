// test_nmea.cpp — native gate for the portable NMEA GGA parser (firmware/libraries/Gps).
// Proves the fix decode the T-Deck GPS anchor relies on (semantic positioning SP2):
// checksum validation, GGA field decode (lat/lon 1e7, quality, sats, HDOP, alt, UTC),
// hemisphere signs, no-fix handling, non-GGA rejection, and byte-stream framing
// (leading noise + a mid-sentence '$' restart). No Arduino, no hardware.
//
// Build/run: part of tests/Makefile (`make`), or:
//   zig c++ -I../firmware/libraries/Gps/src test_nmea.cpp \
//           ../firmware/libraries/Gps/src/Nmea.cpp -o test_nmea && ./test_nmea
#include "Nmea.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>

static int failures = 0;
static void check(bool cond, const char* msg) {
  printf("%s%s\n", cond ? "pass: " : "FAIL: ", msg);
  if (!cond) ++failures;
}

// Feed a whole C-string through the parser; return true if some feed() reported a GGA
// update (mirrors how the sketch drains the UART byte by byte).
static bool feedStr(nmea::Parser& p, const char* s) {
  bool updated = false;
  for (const char* c = s; *c; ++c)
    if (p.feed(*c)) updated = true;
  return updated;
}

// Wrap `body` (the chars between '$' and '*') as a full sentence with a correct,
// independently-computed checksum: "$<body>*HH\r\n".
static void withChecksum(char* out, size_t osz, const char* body) {
  uint8_t cs = 0;
  for (const char* c = body; *c; ++c) cs ^= (uint8_t)*c;
  snprintf(out, osz, "$%s*%02X\r\n", body, cs);
}

int main() {
  // 1) Textbook GGA with its well-known literal checksum (*47) — catches any
  //    systematic decode/checksum bug against a value we did not generate ourselves.
  {
    nmea::Parser p;
    bool up = feedStr(
        p, "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n");
    check(up, "textbook GGA parsed (feed reported an update)");
    const nmea::Fix& f = p.fix();
    check(f.quality == 1, "textbook quality == 1");
    check(f.sats == 8, "textbook sats == 8");
    check(f.hdop_x10 == 9, "textbook HDOP == 0.9");
    check(f.hasFix(), "textbook hasFix() true");
    // 48 deg 07.038' N = 48.1173 deg -> 481173000 (1e-7 deg).
    check(f.lat_1e7 > 481172998 && f.lat_1e7 < 481173002,
          "textbook latitude decoded (~48.1173 N)");
    // 011 deg 31.000' E = 11.516667 deg -> 115166667.
    check(f.lon_1e7 > 115166665 && f.lon_1e7 < 115166669,
          "textbook longitude decoded (~11.5167 E)");
    check(f.alt_cm == 54540, "textbook altitude 545.4 m -> 54540 cm");
    check(f.utc_ms == 45319000u, "textbook UTC 12:35:19 -> 45319000 ms");
    check(p.ggaCount() == 1, "one GGA counted");
  }

  // 2) No-fix GNGGA (quality 0, empty lat/lon) is still a valid, counted sentence.
  {
    nmea::Parser p;
    char s[128];
    withChecksum(s, sizeof(s), "GNGGA,000000,,,,,0,00,99.99,,M,,M,,");
    bool up = feedStr(p, s);
    check(up, "no-fix GNGGA parsed");
    check(p.fix().quality == 0 && !p.fix().hasFix(), "no-fix -> quality 0, hasFix false");
    check(p.fix().lat_1e7 == 0 && p.fix().lon_1e7 == 0, "no-fix -> lat/lon 0");
    check(p.ggaCount() == 1, "no-fix GGA is still counted (liveness signal)");
  }

  // 3) Corrupt checksum is rejected; fix() and ggaCount() are untouched.
  {
    nmea::Parser p;
    feedStr(p, "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n");
    int32_t lat_before = p.fix().lat_1e7;
    // Same sentence body, wrong checksum (*00).
    bool up = feedStr(
        p, "$GPGGA,223519,1234.567,S,09876.543,W,1,05,1.5,10.0,M,,M,,*00\r\n");
    check(!up, "bad-checksum sentence returns no update");
    check(p.fix().lat_1e7 == lat_before, "bad-checksum sentence does not mutate the fix");
    check(p.ggaCount() == 1, "bad-checksum sentence is not counted");
  }

  // 4) A well-formed non-GGA sentence (RMC) is framed-valid but ignored.
  {
    nmea::Parser p;
    char s[128];
    withChecksum(s, sizeof(s),
                 "GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W");
    bool up = feedStr(p, s);
    check(!up, "valid RMC returns no update (not a GGA)");
    check(p.ggaCount() == 0, "RMC is not counted as a GGA");
  }

  // 5) Southern / Western hemisphere -> negative lat/lon.
  {
    nmea::Parser p;
    char s[128];
    withChecksum(s, sizeof(s), "GPGGA,000000,3345.678,S,15012.345,W,2,10,1.2,10.0,M,,M,,");
    check(feedStr(p, s), "S/W GGA parsed");
    const nmea::Fix& f = p.fix();
    // 33 deg 45.678' S = -33.7613 deg; 150 deg 12.345' W = -150.20575 deg.
    check(f.lat_1e7 < 0 && f.lat_1e7 > -337613002 && f.lat_1e7 < -337612998,
          "southern latitude is negative (~-33.7613)");
    check(f.lon_1e7 < 0 && f.lon_1e7 > -1502057502 && f.lon_1e7 < -1502057498,
          "western longitude is negative (~-150.2058)");
    check(f.quality == 2, "DGPS quality == 2");
  }

  // 6) Framing robustness: leading noise then a mid-sentence '$' restart. The partial
  //    "$GPGGA,999," must be dropped when the real sentence's '$' arrives.
  {
    nmea::Parser p;
    char good[128];
    withChecksum(good, sizeof(good),
                 "GPGGA,010203,5000.000,N,00500.000,E,1,07,1.0,100.0,M,,M,,");
    feedStr(p, "  \xFF garbage before any dollar \r\n");   // pre-'$' noise ignored
    feedStr(p, "$GPGGA,999,partial");                       // interrupted, no terminator
    bool up = feedStr(p, good);                             // its '$' drops the partial
    check(up, "sentence after noise + a dropped partial still parses");
    check(p.fix().quality == 1 && p.fix().sats == 7, "restart parsed the good sentence");
    // 50 deg exactly, 5 deg exactly.
    check(p.fix().lat_1e7 == 500000000, "restart latitude exactly 50 N");
    check(p.fix().lon_1e7 == 50000000, "restart longitude exactly 5 E");
  }

  printf("\n");
  if (failures) {
    printf("%d FAILURE(S)\n", failures);
    return 1;
  }
  printf("all nmea tests passed\n");
  return 0;
}
