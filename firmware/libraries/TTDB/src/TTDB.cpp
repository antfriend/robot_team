#include "TTDB.h"

bool Ttdb::begin(fs::FS& fs, const char* path) {
  fs_ = &fs;
  strncpy(path_, path, sizeof(path_) - 1);
  path_[sizeof(path_) - 1] = '\0';

  File f = fs.open(path_, "r");
  if (!f) return false;

  file_size_ = f.size();
  record_count_ = 0;

  // Pass 1: index byte offsets of record headers. A record header is a line
  // whose first character is '@' (TTDB-RFC-0001 section 3).
  size_t off = 0;
  bool line_start = true;
  uint8_t buf[256];
  while (true) {
    int n = f.read(buf, sizeof(buf));
    if (n <= 0) break;
    for (int i = 0; i < n; ++i) {
      uint8_t c = buf[i];
      if (line_start && c == '@' && record_count_ < TTDB_MAX_RECORDS)
        records_[record_count_++].file_offset = off;
      line_start = (c == '\n');
      ++off;
    }
    yield();  // feed the watchdog during the boot scan
  }
  f.close();

  // Pass 2: parse each header line into coordinates/timestamps.
  char line[256];
  for (int i = 0; i < record_count_; ++i) {
    size_t fo = records_[i].file_offset;
    readLine(fo, line, sizeof(line));
    TtdbRecord r;
    if (ttdbParseHeader(line, r)) {
      r.file_offset = fo;
      records_[i] = r;
    }
    if ((i & 0x0F) == 0) yield();
  }
  return true;
}

bool Ttdb::appendRecord(const char* text, size_t len) {
  if (!fs_ || !text || len == 0) return false;
  File f = fs_->open(path_, "a");
  if (!f) return false;
  size_t w = f.write(reinterpret_cast<const uint8_t*>(text), len);
  f.close();
  if (w != len) return false;
  return begin(*fs_, path_);  // re-index: refreshes file_size_ + the record table
}

// Copy [off, off+len) from `in` to `out` in small chunks.
static bool copyRange(File& in, File& out, size_t off, size_t len) {
  if (len == 0) return true;
  if (!in.seek(off)) return false;
  uint8_t buf[128];
  while (len) {
    size_t want = len < sizeof(buf) ? len : sizeof(buf);
    int n = in.read(buf, want);
    if (n <= 0) return false;
    if (out.write(buf, (size_t)n) != (size_t)n) return false;
    len -= (size_t)n;
  }
  return true;
}

bool Ttdb::removeLane(int16_t lat) {
  if (!fs_) return false;
  bool any = false;
  for (int i = 0; i < record_count_; ++i)
    if (records_[i].lat == lat) { any = true; break; }
  if (!any) return true;  // idempotent: nothing to remove

  char tmp[72];
  snprintf(tmp, sizeof(tmp), "%s.tmp", path_);
  File in = fs_->open(path_, "r");
  if (!in) return false;
  File out = fs_->open(tmp, "w");
  if (!out) {
    in.close();
    return false;
  }

  // Preamble (mmpdb header + cursor block, everything before record 0), then
  // every kept record span in file order. A span runs to the NEXT record's
  // header (recordSpan), so the "---" separator that preceded a dropped record
  // stays attached to the record before it and the file stays well-formed.
  // (Dropping the final record leaves a trailing separator — harmless to the
  // '@'-line indexer and to the next appendRecord.)
  size_t pre = record_count_ ? records_[0].file_offset : file_size_;
  bool ok = copyRange(in, out, 0, pre);
  for (int i = 0; ok && i < record_count_; ++i) {
    if (records_[i].lat == lat) continue;
    size_t off, len;
    recordSpan(i, off, len);
    ok = copyRange(in, out, off, len);
    if ((i & 0x07) == 0) yield();
  }
  in.close();
  out.close();
  if (!ok) {
    fs_->remove(tmp);
    return false;
  }
  // Swap. Not power-loss-atomic (prototype): a cut between remove and rename
  // loses the TTDB and needs an FS reflash.
  if (!fs_->remove(path_)) {
    fs_->remove(tmp);
    return false;
  }
  if (!fs_->rename(tmp, path_)) return false;
  return begin(*fs_, path_);  // re-index: file_size_ + record table
}

size_t Ttdb::readBytes(size_t offset, uint8_t* buf, size_t len) {
  if (!fs_ || offset >= file_size_) return 0;
  File f = fs_->open(path_, "r");
  if (!f) return 0;
  if (!f.seek(offset)) {
    f.close();
    return 0;
  }
  size_t n = f.read(buf, len);
  f.close();
  return n;
}

bool Ttdb::recordSpan(int index, size_t& offset, size_t& length) const {
  if (index < 0 || index >= record_count_) return false;
  offset = records_[index].file_offset;
  size_t end =
      (index + 1 < record_count_) ? records_[index + 1].file_offset : file_size_;
  length = end - offset;
  return true;
}

uint8_t Ttdb::edgesAt(int index, TtdbEdge* out, uint8_t max) {
  if (index < 0 || index >= record_count_) return 0;
  char line[256];
  readLine(records_[index].file_offset, line, sizeof(line));
  return ttdbParseEdges(line, out, max);
}

size_t Ttdb::readLine(size_t offset, char* buf, size_t cap) {
  buf[0] = '\0';
  if (!fs_ || cap == 0) return 0;
  File f = fs_->open(path_, "r");
  if (!f) return 0;
  f.seek(offset);
  size_t i = 0;
  while (i < cap - 1) {
    int c = f.read();
    if (c < 0 || c == '\n') break;
    if (c != '\r') buf[i++] = (char)c;
  }
  buf[i] = '\0';
  f.close();
  return i;
}
