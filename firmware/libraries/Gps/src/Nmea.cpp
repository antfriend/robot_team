// Nmea.cpp — see Nmea.h. Portable, allocation-free NMEA GGA decode.
#include "Nmea.h"

#include <stdlib.h>
#include <string.h>

namespace nmea {

static int hexVal(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  return -1;
}

// Copy comma-separated field `idx` of `s` (null-terminated) into `out`. Returns true
// if the field exists (it may still be empty, e.g. lat with no fix). No allocation.
static bool getField(const char* s, int idx, char* out, int outsz) {
  int field = 0;
  const char* p = s;
  while (field < idx) {
    while (*p && *p != ',') ++p;
    if (*p != ',') { out[0] = '\0'; return false; }  // fewer fields than idx
    ++p;
    ++field;
  }
  int oi = 0;
  while (*p && *p != ',' && oi < outsz - 1) out[oi++] = *p++;
  out[oi] = '\0';
  return true;
}

// "ddmm.mmmm" (NMEA lat/lon) -> degrees * 1e7. Empty field -> 0. `deg_digits` is 2 for
// latitude (ddmm.mmmm) and 3 for longitude (dddmm.mmmm) — everything before the last
// two whole-number digits is degrees, the rest is decimal minutes.
static int32_t degMinTo1e7(const char* f, char hemi) {
  if (!f[0]) return 0;
  double raw = strtod(f, nullptr);      // e.g. 4807.038 = 48 deg 07.038'
  double deg = (double)(long)(raw / 100.0);
  double minutes = raw - deg * 100.0;
  double val = deg + minutes / 60.0;
  if (hemi == 'S' || hemi == 'W') val = -val;
  double scaled = val * 1e7;
  return (int32_t)(scaled + (scaled >= 0 ? 0.5 : -0.5));
}

void Parser::reset() {
  len_ = 0;
  started_ = false;
  overflow_ = false;
  gga_count_ = 0;
  fix_ = Fix();
}

bool Parser::feed(char c) {
  if (c == '$') {                    // start of a fresh sentence (drop any partial)
    len_ = 0;
    started_ = true;
    overflow_ = false;
    return false;
  }
  if (!started_) return false;       // ignore noise before the first '$'
  if (c == '\r' || c == '\n') {      // end of sentence
    bool updated = (len_ > 0 && !overflow_) ? consumeLine_() : false;
    len_ = 0;
    started_ = false;
    overflow_ = false;
    return updated;
  }
  if (len_ >= kMaxLine - 1) { overflow_ = true; return false; }
  line_[len_++] = c;
  return false;
}

bool Parser::consumeLine_() {
  line_[len_] = '\0';

  // Locate the '*' checksum delimiter and validate it (XOR of chars before '*').
  int star = -1;
  for (int i = 0; i < len_; ++i)
    if (line_[i] == '*') { star = i; break; }
  if (star < 0 || star + 2 >= len_) return false;   // need two hex digits after '*'
  int hi = hexVal(line_[star + 1]), lo = hexVal(line_[star + 2]);
  if (hi < 0 || lo < 0) return false;
  uint8_t want = (uint8_t)((hi << 4) | lo);
  uint8_t have = 0;
  for (int i = 0; i < star; ++i) have ^= (uint8_t)line_[i];
  if (have != want) return false;                   // corrupt sentence: drop

  // Sentence type is field 0; the last 3 chars are the message id. Only GGA carries a
  // fix in one shot ("$GPGGA", "$GNGGA", ...). Terminate the body at '*' for field parse.
  int comma0 = -1;
  for (int i = 0; i < star; ++i)
    if (line_[i] == ',') { comma0 = i; break; }
  if (comma0 < 3) return false;
  if (memcmp(line_ + comma0 - 3, "GGA", 3) != 0) return false;
  line_[star] = '\0';
  return parseGGA_(line_);
}

bool Parser::parseGGA_(const char* body) {
  char f[16];
  Fix nf;

  // Field 1: UTC hhmmss.sss -> ms since midnight (best-effort; 0 if empty/short).
  if (getField(body, 1, f, sizeof(f)) && strlen(f) >= 6) {
    double t = strtod(f, nullptr);                  // hhmmss.sss as a number
    int hh = (int)(t / 10000.0);
    int mm = ((int)(t / 100.0)) % 100;
    double ss = t - hh * 10000.0 - mm * 100.0;
    nf.utc_ms = (uint32_t)(((hh * 60 + mm) * 60) * 1000UL + (uint32_t)(ss * 1000.0 + 0.5));
  }

  // Fields 2-5: lat / N-S / lon / E-W.
  char ns[4] = {0}, ew[4] = {0}, latf[16] = {0}, lonf[16] = {0};
  getField(body, 2, latf, sizeof(latf));
  getField(body, 3, ns, sizeof(ns));
  getField(body, 4, lonf, sizeof(lonf));
  getField(body, 5, ew, sizeof(ew));
  nf.lat_1e7 = degMinTo1e7(latf, ns[0]);
  nf.lon_1e7 = degMinTo1e7(lonf, ew[0]);

  // Field 6: quality. 7: sats. 8: HDOP. 9: altitude (metres MSL).
  if (getField(body, 6, f, sizeof(f))) nf.quality = (uint8_t)atoi(f);
  if (getField(body, 7, f, sizeof(f))) nf.sats = (uint8_t)atoi(f);
  if (getField(body, 8, f, sizeof(f))) {
    double h = strtod(f, nullptr);
    nf.hdop_x10 = (uint16_t)(h * 10.0 + 0.5);
  }
  if (getField(body, 9, f, sizeof(f)) && f[0]) {
    double a = strtod(f, nullptr);
    nf.alt_cm = (int32_t)(a * 100.0 + (a >= 0 ? 0.5 : -0.5));
  }

  fix_ = nf;
  ++gga_count_;
  return true;
}

}  // namespace nmea
