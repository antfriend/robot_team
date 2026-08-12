#include "TTDB.h"

bool Ttdb::begin(fs::FS& fs, const char* path) {
  fs_ = &fs;
  strncpy(path_, path, sizeof(path_) - 1);
  path_[sizeof(path_) - 1] = '\0';

  File f = fs.open(path_, "r");
  if (!f) return false;

  file_size_ = f.size();
  record_count_ = 0;
  headers_seen_ = 0;
  tail_offset_ = file_size_;   // "no tail" — overwritten by the first header that
                               // does not fit, below.

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
      // ⚠ COUNT EVERY HEADER, INDEX ONLY WHAT FITS. The cap used to sit inside this
      // condition, so an over-cap file was indistinguishable from one that fitted:
      // the scan just stopped and begin() returned true.
      if (line_start && c == '@') {
        if (record_count_ < TTDB_MAX_RECORDS)
          records_[record_count_++].file_offset = off;
        else if (headers_seen_ == (uint32_t)record_count_)
          tail_offset_ = off;              // first header past the cap
        ++headers_seen_;
      }
      line_start = (c == '\n');
      ++off;
    }
    yield();  // feed the watchdog during the boot scan
  }
  // Pass 2: parse each header line into coordinates/timestamps. Reuses the handle from
  // pass 1 — `readLine()` OPENS AND CLOSES THE FILE PER CALL, so calling it once per
  // record turned this loop into one file open per record. On a node whose TTDB grows at
  // runtime that is the same defect that made `edgesAt()` cost 767 ms a frame
  // (companion.md §6): the per-call open, not the bytes.
  char line[256];
  for (int i = 0; i < record_count_; ++i) {
    size_t fo = records_[i].file_offset;
    readLineFrom(f, fo, line, sizeof(line));
    TtdbRecord r;
    if (ttdbParseHeader(line, r)) {
      r.file_offset = fo;
      records_[i] = r;
    }
    if ((i & 0x0F) == 0) yield();
  }
  f.close();
  return true;
}

// Append a record block and index it INCREMENTALLY.
//
// This used to end with `return begin(*fs_, path_)` — a full re-scan and re-parse of the
// whole file on every append. On the K10 and the bridge, whose TTDBs are written rarely,
// that was invisible. On the Cardputer, which appends a percept window every 60 s across
// four tiers, it was the node's single worst loop pass: measured at **676 ms with a 68 KB
// TTDB and 3.1 s at 81 KB**, growing without bound because the file grows every window.
// The append is O(1) work; the re-index was O(file) and did not need doing at all — we
// know exactly what we just wrote and where it landed.
//
// Anything unexpected in the appended text falls back to the authoritative full scan, so
// the index can never silently drift from the file.
bool Ttdb::appendRecord(const char* text, size_t len) {
  if (!fs_ || !text || len == 0) return false;
  // ⚠ REFUSE A FULL INDEX BEFORE WRITING A BYTE. The old order wrote the block, then
  // noticed the index was full mid-scan, rolled back to a full begin() — WHICH RETURNS
  // TRUE — so the caller believed the append succeeded while the record sat on flash
  // OUTSIDE the index, invisible to every reader and destroyed by the next lane rewrite
  // (removeLaneRange copies indexed spans only). Found on hardware 2026-08-09: the
  // Cardputer's file is legitimately AT the cap (its lane caps sum there), five @LAT101
  // records were appended "successfully", and the next Dream Cycle's belief-lane rewrite
  // silently erased them. Count the headers in the block first; a block that cannot be
  // indexed whole is refused whole.
  {
    int headers = 0;
    bool ls = false;   // text[0]=='@' is rejected below anyway; a block starts "\n---"
    for (size_t i = 0; i < len; ++i) {
      if (ls && text[i] == '@') ++headers;
      ls = (text[i] == '\n');
    }
    if (record_count_ + headers > TTDB_MAX_RECORDS) return false;
  }
  File f = fs_->open(path_, "a");
  if (!f) return false;
  const size_t base = f.size();     // authoritative, not the cached file_size_
  size_t w = f.write(reinterpret_cast<const uint8_t*>(text), len);
  f.close();
  if (w != len) return false;

  // A record header is a line whose first character is '@'. Offset 0 of the block would
  // need the file's last byte to know whether it starts a line, so a block beginning with
  // '@' is handed to the full scan; a well-formed block starts with the "\n---\n\n"
  // separator, so this never fires in practice.
  const int start_count = record_count_;
  int added = 0;
  bool ok = (base == file_size_) && (text[0] != '@');
  bool line_start = false;
  char line[256];
  for (size_t i = 0; ok && i < len; ++i) {
    if (line_start && text[i] == '@') {
      if (record_count_ >= TTDB_MAX_RECORDS) { ok = false; break; }
      size_t j = i, k = 0;
      while (j < len && text[j] != '\n' && k < sizeof(line) - 1) {
        if (text[j] != '\r') line[k++] = text[j];
        ++j;
      }
      line[k] = '\0';
      TtdbRecord r;
      if (!ttdbParseHeader(line, r)) { ok = false; break; }
      r.file_offset = base + i;
      records_[record_count_++] = r;
      ++added;
    }
    line_start = (text[i] == '\n');
  }
  if (!ok || added == 0) {
    record_count_ = start_count;      // roll back a partial index
    return begin(*fs_, path_);
  }
  file_size_ = base + len;
  return true;
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

bool Ttdb::removeLane(int16_t lat) { return removeLaneRange(lat, lat); }

bool Ttdb::removePerceptLanes(uint8_t lane) {
  if (lane == 0)
    return removeLaneRange(TTDB_PERCEPT_LANE_LO, TTDB_PERCEPT_LANE_HI);
  // Refuse anything outside the percept range rather than clamping: a caller
  // asking for @LAT99 has a bug or bad intent, and silently pruning a different
  // lane than the one requested would be worse than saying no.
  if (lane < TTDB_PERCEPT_LANE_LO || lane > TTDB_PERCEPT_LANE_HI) return false;
  return removeLane((int16_t)lane);
}

bool Ttdb::removeLaneRange(int16_t lo, int16_t hi) {
  if (!fs_ || lo > hi) return false;
  bool any = false;
  for (int i = 0; i < record_count_; ++i)
    if (records_[i].lat >= lo && records_[i].lat <= hi) { any = true; break; }
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
    if (records_[i].lat >= lo && records_[i].lat <= hi) continue;
    size_t off, len;
    recordSpan(i, off, len);
    ok = copyRange(in, out, off, len);
    if ((i & 0x07) == 0) yield();
  }
  // ⚠ CARRY THE UNINDEXED TAIL VERBATIM. Records past TTDB_MAX_RECORDS are invisible to
  // the loop above — it walks the INDEX, not the file — so before this they were simply
  // not copied, and a prune silently deleted them. We cannot tell whether they belong to
  // the pruned lane (we never parsed their headers), and the safe direction is obvious:
  // keeping a record that should have gone costs one stale record, dropping one that
  // should have stayed destroys evidence. Once the prune frees index slots the next
  // begin() sees these records properly, so repeated prunes converge instead of eating
  // the tail. No-op on a file that fits (tail_offset_ == file_size_).
  if (ok && tail_offset_ < file_size_)
    ok = copyRange(in, out, tail_offset_, file_size_ - tail_offset_);
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
  // ⚠ The LAST indexed record ends at `tail_offset_`, not at EOF. They are the same
  // thing whenever the file fits the index (tail_offset_ == file_size_), but when it
  // does NOT, ending at EOF made the last record's span swallow every unindexed record
  // behind it — so `removeLaneRange` deleted them all if that record's lane was pruned.
  size_t end =
      (index + 1 < record_count_) ? records_[index + 1].file_offset : tail_offset_;
  length = end - offset;
  return true;
}

uint8_t Ttdb::edgesAt(int index, TtdbEdge* out, uint8_t max) {
  if (index < 0 || index >= record_count_) return 0;
  char line[256];
  readLine(records_[index].file_offset, line, sizeof(line));
  return ttdbParseEdges(line, out, max);
}

// Read one line through an ALREADY-OPEN handle. Every caller that reads more than one
// line must use this: the open, not the bytes, is what costs.
size_t Ttdb::readLineFrom(File& f, size_t offset, char* buf, size_t cap) {
  buf[0] = '\0';
  if (cap == 0 || !f) return 0;
  if (!f.seek(offset)) return 0;
  size_t i = 0;
  while (i < cap - 1) {
    int c = f.read();
    if (c < 0 || c == '\n') break;
    if (c != '\r') buf[i++] = (char)c;
  }
  buf[i] = '\0';
  return i;
}

size_t Ttdb::readLine(size_t offset, char* buf, size_t cap) {
  buf[0] = '\0';
  if (!fs_ || cap == 0) return 0;
  File f = fs_->open(path_, "r");
  if (!f) return 0;
  size_t i = readLineFrom(f, offset, buf, cap);
  f.close();
  return i;
}
