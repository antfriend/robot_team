// Nmea.h — portable NMEA-0183 GGA parser for the fleet's roaming GPS anchor.
//
// Semantic positioning SP2 (ttn-semantic-positioning.md §3 Phase 2): the T-Deck Plus
// GPS is the fleet's roaming ground-truth anchor + verifier. This decodes a byte stream
// of NMEA sentences into a position fix. It parses $--GGA only (Global positioning
// system fix data) — one sentence carries lat, lon, quality, sats, HDOP and MSL
// altitude, which is everything the anchoring math needs. Other sentences (RMC, GSV,
// VTG, ...) are validated for framing and ignored.
//
// No Arduino, no heap, no float exceptions on bad input: feed() takes one char at a
// time and returns true only when a checksum-valid GGA with a live fix updated fix().
// The sketch owns the UART and just pushes bytes in; the decode is native-testable
// (tests/test_nmea.cpp), like every other portable lib here.
#ifndef ROBOT_TEAM_NMEA_H
#define ROBOT_TEAM_NMEA_H

#include <stdint.h>
#include <stddef.h>

namespace nmea {

// A decoded GGA fix. Angles are in 1e-7 degrees (int32, == u-blox/NMEA native scaling:
// covers +/-180 deg with ~1.1 cm resolution). alt_cm is MSL altitude in centimetres.
struct Fix {
  int32_t lat_1e7 = 0;    // latitude  * 1e7 (deg); + = north
  int32_t lon_1e7 = 0;    // longitude * 1e7 (deg); + = east
  int32_t alt_cm = 0;     // altitude above mean sea level, cm
  uint8_t quality = 0;    // GGA fix quality: 0 = no fix, 1 = GPS, 2 = DGPS, ...
  uint8_t sats = 0;       // satellites used in the fix
  uint16_t hdop_x10 = 0;  // horizontal dilution of precision * 10
  uint32_t utc_ms = 0;    // UTC time-of-day from the GGA (ms since midnight); 0 unknown

  bool hasFix() const { return quality != 0; }
};

// Line-oriented NMEA reader. Accumulates one sentence, validates its `*hh` checksum,
// and — if it is a GGA — decodes it into fix_.
class Parser {
 public:
  Parser() { reset(); }
  void reset();

  // Feed one received byte. Returns true when a checksum-valid GGA sentence just
  // updated fix() (whether or not it carried a live fix — quality may be 0). Bytes
  // outside a sentence, malformed sentences, and non-GGA sentences return false.
  bool feed(char c);

  const Fix& fix() const { return fix_; }
  // Count of checksum-valid GGA sentences decoded (fix or not) — a liveness signal
  // for auto-baud / "is the module even talking" without needing a sky-view lock.
  uint32_t ggaCount() const { return gga_count_; }

 private:
  static const int kMaxLine = 100;   // NMEA sentences are <= 82 chars incl. CRLF
  char line_[kMaxLine];
  int len_;
  bool started_;                     // seen a '$'; ignore bytes until then
  bool overflow_;                    // sentence exceeded kMaxLine: drop it
  Fix fix_;
  uint32_t gga_count_;

  bool consumeLine_();               // validate checksum + dispatch; returns GGA-updated
  bool parseGGA_(const char* body);  // body = between '$' and '*', checksum already ok
};

}  // namespace nmea

#endif  // ROBOT_TEAM_NMEA_H
