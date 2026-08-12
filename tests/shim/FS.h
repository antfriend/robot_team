// FS.h — native stand-in for the Arduino filesystem API, backed by stdio.
//
// Scope is deliberately the surface TTDB.cpp actually uses: open/close/read/write/
// seek/size on File, and open/remove/rename on FS. Everything else is absent so that a
// future TTDB.cpp reaching for more filesystem fails to COMPILE here rather than
// silently going untested.
//
// ⚠ ALL MODES ARE BINARY. On Windows a text-mode handle rewrites "\n" as "\r\n" on the
// way out and collapses it coming back, which would move every byte offset in the index
// — the one thing this file must not do to a test about byte offsets.
#pragma once
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstddef>

namespace fs {

class File {
 public:
  File() {}
  explicit File(std::FILE* f) : f_(f) {}

  // Copyable with pointer semantics, like Arduino's File. TTDB.cpp always closes
  // explicitly and never copies a handle it still uses, so this is safe here; there is
  // deliberately no destructor-close, which would double-close a copy.
  explicit operator bool() const { return f_ != nullptr; }

  int read(uint8_t* buf, size_t len) {
    if (!f_) return -1;
    size_t n = std::fread(buf, 1, len, f_);
    return (int)n;
  }
  // Single-byte read, -1 at EOF (Stream::read). Used by readLineFrom().
  int read() {
    if (!f_) return -1;
    int c = std::fgetc(f_);
    return c == EOF ? -1 : c;
  }
  size_t write(const uint8_t* buf, size_t len) {
    return f_ ? std::fwrite(buf, 1, len, f_) : 0;
  }
  bool seek(size_t off) {
    return f_ && std::fseek(f_, (long)off, SEEK_SET) == 0;
  }
  size_t size() {
    if (!f_) return 0;
    long cur = std::ftell(f_);
    std::fseek(f_, 0, SEEK_END);
    long end = std::ftell(f_);
    std::fseek(f_, cur < 0 ? 0 : cur, SEEK_SET);
    return end < 0 ? 0 : (size_t)end;
  }
  void close() {
    if (f_) std::fclose(f_);
    f_ = nullptr;
  }

 private:
  std::FILE* f_ = nullptr;
};

class FS {
 public:
  File open(const char* path, const char* mode) {
    char m[4] = {0};
    // Map Arduino's "r"/"w"/"a" onto binary stdio modes.
    m[0] = mode && mode[0] ? mode[0] : 'r';
    m[1] = 'b';
    return File(std::fopen(path, m));
  }
  bool remove(const char* path) { return std::remove(path) == 0; }
  bool rename(const char* from, const char* to) {
    std::remove(to);                     // POSIX rename replaces; Win32 refuses.
    return std::rename(from, to) == 0;
  }
};

}  // namespace fs

using fs::File;
