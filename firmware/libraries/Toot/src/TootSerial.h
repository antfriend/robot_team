// TootSerial.h — length-prefixed framing so a node can exchange toots with the
// laptop companion over a byte stream (USB-CDC Serial).
//
// On-wire serial framing: 0xAB 0xCD <len_lo> <len_hi> <len bytes of toot frame>.
// The 2-byte sync lets the reader resync after noise; the toot's own HMAC is
// the real integrity check. This is intentionally identical to the framing in
// orchestrator/companion.py so the two interoperate.
#pragma once
#if defined(ARDUINO)
#include <Arduino.h>
#include "Toot.h"

class TootSerialLink {
 public:
  explicit TootSerialLink(Stream& s) : s_(s) {}

  void writeFrame(const uint8_t* frame, size_t len) {
    s_.write((uint8_t)0xAB);
    s_.write((uint8_t)0xCD);
    s_.write((uint8_t)(len & 0xff));
    s_.write((uint8_t)((len >> 8) & 0xff));
    s_.write(frame, len);
  }

  // Non-blocking. Drains available bytes; returns true and fills buf/outLen
  // when a complete frame has arrived.
  bool poll(uint8_t* buf, size_t cap, size_t& outLen) {
    while (s_.available()) {
      int c = s_.read();
      if (c < 0) break;
      switch (st_) {
        case WAIT0: st_ = (c == 0xAB) ? WAIT1 : WAIT0; break;
        case WAIT1: st_ = (c == 0xCD) ? LEN0 : WAIT0; break;
        case LEN0: need_ = (uint16_t)c; st_ = LEN1; break;
        case LEN1:
          need_ |= (uint16_t)(c << 8);
          got_ = 0;
          st_ = (need_ == 0 || need_ > cap) ? WAIT0 : DATA;
          break;
        case DATA:
          buf[got_++] = (uint8_t)c;
          if (got_ >= need_) {
            outLen = need_;
            st_ = WAIT0;
            return true;
          }
          break;
      }
    }
    return false;
  }

 private:
  enum State { WAIT0, WAIT1, LEN0, LEN1, DATA };
  Stream& s_;
  State st_ = WAIT0;
  uint16_t need_ = 0;
  uint16_t got_ = 0;
};
#endif  // ARDUINO
