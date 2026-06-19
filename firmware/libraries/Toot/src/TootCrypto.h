// TootCrypto.h — portable SHA-256 + HMAC-SHA256 for toot authentication.
//
// Self-contained (no mbedTLS, no Arduino) so the same code runs on the ESP32
// and in the native test harness, and interoperates byte-for-byte with the
// laptop companion's Python hmac/hashlib.
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace toot {

// 32-byte SHA-256 digest of `data`.
void sha256(const uint8_t* data, size_t len, uint8_t out[32]);

// Full 32-byte HMAC-SHA256(key, data).
void hmac_sha256(const uint8_t* key, size_t key_len,
                 const uint8_t* data, size_t data_len, uint8_t out[32]);

// First 8 bytes of HMAC-SHA256 — the toot frame's truncated tag.
void hmac_sha256_trunc(const uint8_t* key, size_t key_len,
                       const uint8_t* data, size_t data_len, uint8_t out[8]);

}  // namespace toot
