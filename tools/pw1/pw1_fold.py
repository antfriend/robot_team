"""PW-1: does learned precision pi separate channels, and stay put within one?

TTDB-RFC-0011 v0.1.2 section 8. Read-only over master/. Constants live in pw1_constants.py
and were committed before this file read the archive.

    python tools/pw1/pw1_fold.py master/ --report tools/pw1/PW1-REPORT.md

DECISIONS FIXED BEFORE ANY DATA WAS READ
  * The verdict is taken from the RUNS-EXPANDED computation (the brief: skipping the zeros
    biases pi low on change-triggered channels). The unexpanded computation is reported
    beside it; if its verdict differs, that is stated, not averaged in.
  * Separation = max - min over channels of (median pi over that channel's series).
  * Stability = share of series, with both halves >= MIN_RESIDUALS, whose fresh-folded
    half-series pi differ by <= STAB_TOL. Halves split the residual list by count.
  * Robustness compares channel rank order (by median pi, ties broken by channel name and
    reported) at each PI_SCALE in PI_SCALES_ROBUSTNESS.
  * Node = filename prefix up to the first '_' (records carry no node id).
  * Dedup key = (node, lane, stream, t_ms, sha1(body)). Lanes 94-97 only.
  * Series order: streamed records by (stream, t_ms); stream-less records in file-name
    order, a new segment wherever t_ms does not increase. Residuals never cross segments.
    One pi per (node, channel) folds the segments' residuals concatenated in that order.
"""
import argparse
import collections
import glob
import hashlib
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pw1_constants as K  # noqa: E402

REC = re.compile(r'^@LAT(-?\d+)LON(-?\d+)\s*\|', re.M)
CHANNELS = {94: 'acoustic', 95: 'motion', 96: 'entity', 97: 'link'}


# ---------------------------------------------------------------- the fold (RFC 4.3)
def fold_var(residuals):
    """Integer EWMA of r^2. `>>` on a negative int floors (arithmetic shift), as GCC does
    for a signed int on the ESP32."""
    var = 0
    for r in residuals:
        var += ((r * r) - var) >> K.PI_ALPHA
    return var


def pi_from_var(var, scale=K.PI_SCALE):
    return (255 * scale) // (scale + var)


def pi_ewma(residuals, scale=K.PI_SCALE):
    return pi_from_var(fold_var(residuals), scale)


def pi_mean(residuals, scale=K.PI_SCALE):
    return pi_from_var(sum(r * r for r in residuals) // len(residuals), scale)


# ---------------------------------------------------------------- parsing
def split_records(path):
    """Yield (lane, body) for lanes 94-97 only. Lane 101 (FIELD) is never parsed."""
    with open(path, 'r', encoding='utf-8', errors='replace') as fh:   # read-only
        txt = fh.read()
    hits = list(REC.finditer(txt))
    for i, m in enumerate(hits):
        lane = int(m.group(1))
        if lane not in K.LANES:
            continue
        end = hits[i + 1].start() if i + 1 < len(hits) else len(txt)
        rec = txt[m.start():end]
        yield lane, (rec.split('\n', 1)[1] if '\n' in rec else '')


def node_of(path):
    stem = os.path.splitext(os.path.basename(path))[0]
    return stem.split('_', 1)[0]


def parse_head(body):
    b = re.sub(r'prev_stream:0x[0-9a-fA-F]+', '', body)   # CLAUDE.md: strip it first
    t = re.search(r'\bt_ms:(\d+)', b)
    s = re.search(r'\bstream:0x([0-9a-fA-F]+)', b)
    return (int(t.group(1)) if t else None), (int(s.group(1), 16) if s else None)


def _int(pat, body):
    m = re.search(pat, body)
    return int(m.group(1)) if m else None


def parse_record(lane, body):
    """-> dict(t, stream, run, val | ids | links), or (None, reason)."""
    t, stream = parse_head(body)
    if t is None:
        return None, 'no t_ms'
    rec = {'t': t, 'stream': stream}
    run = _int(r'\*\*RUN\*\*[^\n]*?\bwindows_since_last:(\d+)', body)
    rec['run'] = run if run else 1
    if lane == 94:
        if '**ACOUSTICWIN**' not in body:
            return None, 'not an ACOUSTICWIN record'
        v = _int(r'\*\*ACOUSTIC\*\*[^\n]*?\brms_mean:(-?\d+)', body)
        if v is None:
            return None, 'no rms_mean'
        rec['val'] = v
    elif lane == 95:
        if '**MOTIONWIN**' not in body:
            return None, 'not a MOTIONWIN record'
        v = _int(r'\*\*MOTION\*\*[^\n]*?\bdev_mean_mg:(-?\d+)', body)
        if v is None:
            return None, 'no dev_mean_mg'
        rec['val'] = v
    elif lane == 96:
        if '**ENTWIN**' not in body:
            return None, 'not an ENTWIN record'
        rec['ids'] = frozenset(re.findall(r'^\*\*ENTITY\*\*[^\n]*?\bid:([0-9a-fA-F]+)', body, re.M))
    elif lane == 97:
        if '**LINKWIN**' not in body:
            return None, 'not a LINKWIN record (e.g. BELIEF-PUSH)'
        links = {}
        for m in re.finditer(r'^\*\*LINK\*\*\s+peer:(\S+)\s+proto:(\S+)[^\n]*?\brssi_med:(-?\d+)', body, re.M):
            links[(m.group(1), m.group(2))] = int(m.group(3))
        rec['links'] = links
    return rec, None


# ---------------------------------------------------------------- residuals
def _pe(diff, span):
    return min(255, abs(diff) * 255 // span)


def _scalar(seg, span):
    """Expanded and unexpanded residuals for a segment of scalar records."""
    exp, unexp = [], []
    prev = None
    for r in seg:
        if prev is not None:
            exp.extend([0] * (r['run'] - 1))      # a run of n windows = n-1 zero residuals
            d = _pe(r['val'] - prev['val'], span)
            exp.append(d)
            unexp.append(d)
        prev = r
    return exp, unexp


def _jaccard_pe(a, b):
    u = len(a | b)
    if u == 0:
        return 0
    return min(255, 255 * (u - len(a & b)) // u)


def _entity(seg):
    exp, unexp = [], []
    prev = None
    for r in seg:
        if prev is not None:
            exp.extend([0] * (r['run'] - 1))
            d = _jaccard_pe(prev['ids'], r['ids'])
            exp.append(d)
            unexp.append(d)
        prev = r
    return exp, unexp


def _link(seg, notes):
    out = []
    prev = None
    for r in seg:
        if prev is not None:
            for k in sorted(r['links']):
                if k in prev['links']:
                    out.append(_pe(r['links'][k] - prev['links'][k], K.PE_SPAN_LINK))
                else:
                    notes['link_peer_not_in_previous_window'] += 1
        prev = r
    return out, list(out)


def residuals_for(lane, seg, notes):
    if lane == 94:
        return _scalar(seg, K.PE_SPAN_ACOUSTIC)
    if lane == 95:
        return _scalar(seg, K.PE_SPAN_MOTION)
    if lane == 96:
        return _entity(seg)
    return _link(seg, notes)


# ---------------------------------------------------------------- archive -> series
def load_archive(root):
    """-> (series, log). series[(node, channel)] = {'exp': [...], 'unexp': [...]}"""
    files = sorted(glob.glob(os.path.join(root, '**', '*.md'), recursive=True))
    log = {'files': len(files), 'excluded': collections.Counter(), 'dups': collections.Counter(),
           'notes': collections.Counter(), 'streamless_break': collections.Counter(),
           'records': collections.Counter(), 'files_no_lane': []}
    seen = set()
    groups = collections.OrderedDict()     # (node, lane, stream|None) -> [rec] in encounter order
    for path in files:
        rel = os.path.relpath(path, root)
        node = node_of(path)
        n_here = 0
        for lane, body in split_records(path):
            n_here += 1
            rec, why = parse_record(lane, body)
            if rec is None:
                log['excluded'][(rel, lane, why)] += 1
                continue
            key = (node, lane, rec['stream'], rec['t'], hashlib.sha1(body.encode('utf-8', 'replace')).hexdigest())
            if key in seen:
                log['dups'][rel] += 1
                continue
            seen.add(key)
            log['records'][lane] += 1
            groups.setdefault((node, lane, rec['stream']), []).append(rec)
        if n_here == 0:
            log['files_no_lane'].append(rel)

    series = {}
    for (node, lane, stream), recs in groups.items():
        if stream is not None:
            segs = [sorted(recs, key=lambda r: r['t'])]
        else:
            segs, cur = [], []
            for r in recs:
                if cur and r['t'] <= cur[-1]['t']:
                    segs.append(cur)
                    cur = []
                    log['streamless_break'][(node, lane)] += 1
                cur.append(r)
            if cur:
                segs.append(cur)
        s = series.setdefault((node, CHANNELS[lane]), {'exp': [], 'unexp': [], 'segments': 0})
        for seg in segs:
            e, u = residuals_for(lane, seg, log['notes'])
            s['exp'].extend(e)
            s['unexp'].extend(u)
            s['segments'] += 1
    return series, log


# ---------------------------------------------------------------- analysis
def median(xs):
    xs = sorted(xs)
    n = len(xs)
    return xs[n // 2] if n % 2 else (xs[n // 2 - 1] + xs[n // 2]) // 2


def row(res, scale=K.PI_SCALE):
    h = len(res) // 2
    r1, r2 = res[:h], res[h:]
    ok = len(r1) >= K.MIN_RESIDUALS and len(r2) >= K.MIN_RESIDUALS
    pe_, pm = pi_ewma(res, scale), pi_mean(res, scale)
    return {'n': len(res), 'pi': pe_, 'pim': pm, 'drift': abs(pe_ - pm) > K.DRIFT_FLAG,
            'pi1': pi_ewma(r1, scale) if ok else None, 'pi2': pi_ewma(r2, scale) if ok else None}


def analyze(series, mode):
    """mode 'exp' or 'unexp'. -> dict of rows and the three checks."""
    rows = {}
    for (node, ch), s in sorted(series.items()):
        res = s[mode]
        if len(res) >= K.MIN_RESIDUALS:
            rows[(node, ch)] = row(res)
    chans = sorted({ch for _, ch in rows})
    med = {}
    for sc in K.PI_SCALES_ROBUSTNESS:
        med[sc] = {ch: median([row(series[k][mode], sc)['pi'] for k in rows if k[1] == ch]) for ch in chans}
    m8 = med[K.PI_SCALE]
    sep = (max(m8.values()) - min(m8.values())) if m8 else 0
    both = [r for r in rows.values() if r['pi1'] is not None]
    stable = sum(1 for r in both if abs(r['pi1'] - r['pi2']) <= K.STAB_TOL)
    stab = (stable / len(both)) if both else 0.0
    ranks = {sc: tuple(sorted(m, key=lambda c: (m[c], c))) for sc, m in med.items()}
    rob_same = len(set(ranks.values())) == 1
    ties = [sc for sc, m in med.items() if len(set(m.values())) < len(m)]
    sep_v = 'PASS' if sep > K.SEP_PASS else ('KILL' if sep <= K.SEP_KILL else 'MID')
    stab_v = 'PASS' if (both and stab >= K.STAB_PASS) else ('KILL' if stab < K.STAB_KILL else 'MID')
    rob_v = 'PASS' if rob_same and chans else 'FAIL'
    if sep_v == 'KILL' or stab_v == 'KILL':
        verdict = 'KILL'
    elif sep_v == 'PASS' and stab_v == 'PASS' and rob_v == 'PASS':
        verdict = 'PASS'
    else:
        verdict = 'INCONCLUSIVE'
    return {'rows': rows, 'channels': chans, 'median': med, 'sep': sep, 'sep_v': sep_v,
            'stab': stab, 'stab_n': len(both), 'stab_ok': stable, 'stab_v': stab_v,
            'ranks': ranks, 'rob_v': rob_v, 'ties': ties, 'verdict': verdict}


def deciding(a):
    if a['verdict'] == 'KILL':
        bits = []
        if a['sep_v'] == 'KILL':
            bits.append('separation %d <= %d' % (a['sep'], K.SEP_KILL))
        if a['stab_v'] == 'KILL':
            bits.append('stability %.1f%% < %d%%' % (100 * a['stab'], int(100 * K.STAB_KILL)))
        return '; '.join(bits)
    return 'separation %d (pass > %d), stability %.1f%% (pass >= %d%%), robustness %s' % (
        a['sep'], K.SEP_PASS, 100 * a['stab'], int(100 * K.STAB_PASS), a['rob_v'])


# ---------------------------------------------------------------- report
def table(a):
    out = ['| node | channel | n | π (EWMA) | π (mean) | π₁ | π₂ | drift |', '|---|---|---|---|---|---|---|---|']
    for (node, ch), r in a['rows'].items():
        out.append('| %s | %s | %d | %d | %d | %s | %s | %s |' % (
            node, ch, r['n'], r['pi'], r['pim'],
            '-' if r['pi1'] is None else r['pi1'], '-' if r['pi2'] is None else r['pi2'],
            'DRIFT' if r['drift'] else ''))
    return out


def checks(a):
    out = ['| check | value | result |', '|---|---|---|',
           '| Separation (range of per-channel median π, PI_SCALE=%d) | %d | %s |' % (K.PI_SCALE, a['sep'], a['sep_v']),
           '| Stability (split-half within %d; %d of %d series) | %.1f%% | %s |' % (
               K.STAB_TOL, a['stab_ok'], a['stab_n'], 100 * a['stab'], a['stab_v']),
           '| Robustness (rank order at %s) | %s | %s |' % (
               '/'.join(map(str, K.PI_SCALES_ROBUSTNESS)),
               ' | '.join('%d: %s' % (sc, '<'.join(r)) for sc, r in a['ranks'].items()), a['rob_v'])]
    out.append('')
    out.append('Per-channel median π: ' + '; '.join(
        '@%d %s' % (sc, ', '.join('%s %d' % (c, v) for c, v in m.items())) for sc, m in a['median'].items()))
    if a['ties']:
        out.append('Tied medians at PI_SCALE %s (ties broken by channel name).' % a['ties'])
    return out


def report(series, log, ex, un):
    L = []
    L.append('PW-1: %s — %s' % (ex['verdict'], deciding(ex)))
    L.append('')
    L.append('Verdict is from the runs-expanded computation (fixed in advance). Runs-unexpanded verdict: **%s** — %s.%s' % (
        un['verdict'], deciding(un),
        '' if un['verdict'] == ex['verdict'] else ' **The two disagree.**'))
    L.append('')
    L.append('## Pre-registered constants (committed in 055364d before any archive read)')
    L += ['', '| constant | value | source |', '|---|---|---|',
          '| pe_span acoustic | %d | `AcousticPercept.h:76` — int16 samples |' % K.PE_SPAN_ACOUSTIC,
          '| pe_span motion | %d mg | BMI270 ±8 g datasheet default; firmware sets no range (`cardputer_console.ino` ~3874); confirmed by Dan Ray |' % K.PE_SPAN_MOTION,
          '| pe_span link | %d dB | brief: −120 to −20 dBm |' % K.PE_SPAN_LINK,
          '| pe entity | Jaccard × 255 | already 0–1 |',
          '| PI_SCALE | %d (robustness %s) | brief |' % (K.PI_SCALE, K.PI_SCALES_ROBUSTNESS),
          '| thresholds | sep >%d / ≤%d; stab ≥%d%% / <%d%%, tol %d; min n %d | brief |' % (
              K.SEP_PASS, K.SEP_KILL, 100 * K.STAB_PASS, 100 * K.STAB_KILL, K.STAB_TOL, K.MIN_RESIDUALS)]
    L += ['', '## Scope', '',
          '- Files under `master/` (`**/*.md`): **%d** (the RFC assumed 78; the archive has grown). Deduplicated on (node, lane, stream, t_ms, body digest).' % log['files'],
          '- Distinct records kept: ' + ', '.join('@LAT%d %d' % (k, v) for k, v in sorted(log['records'].items())),
          '- Duplicate records dropped: %d, across %d files.' % (sum(log['dups'].values()), len(log['dups'])),
          '- Lanes 94–97 only; `@LAT101` is never parsed.',
          '- Node = filename prefix before the first `_` (records carry no node id).',
          '- Primary scalars used: acoustic `rms_mean`; motion `dev_mean_mg`; link `rssi_med` per (peer, proto), pooled per node; entity = set of `ENTITY id`.']
    L += ['', '## Checks — runs expanded (verdict)', ''] + checks(ex)
    L += ['', '## Checks — runs not expanded', ''] + checks(un)
    L += ['', '## Series — runs expanded', ''] + table(ex)
    L += ['', '## Series — runs not expanded', ''] + table(un)
    m8 = ex['median'][K.PI_SCALE]
    sat = sorted(c for c, v in m8.items() if v >= 250)
    L += ['', '## Reading the result (descriptive; no threshold was changed)', '',
          '- Channels whose median π is >= 250 (saturated near the 255 ceiling): %s. Of the %d channels, the separation figure is the gap between the lowest median (%s, %d) and the highest (%s, %d).' % (
              ', '.join(sat) or 'none', len(m8), min(m8, key=lambda c: (m8[c], c)), min(m8.values()),
              max(m8, key=lambda c: (m8[c], c)), max(m8.values())),
          '- Saturated channels are mutually indistinguishable at this resolution, and the robustness check ties on them; the rank order among them rests on name tie-breaking. The pre-registered rule is met as written, but a pass resting on one channel separating from the rest is weaker evidence for per-channel gain than separation spread across all four.',
          '- Series flagged DRIFT (EWMA vs mean π differ by > %d): %s.' % (K.DRIFT_FLAG, ', '.join('%s/%s' % k for k, r in ex['rows'].items() if r['drift']) or 'none')]
    L += ['', '## Exclusions and notes', '']
    short = sorted((k, len(s['exp'])) for k, s in series.items() if len(s['exp']) < K.MIN_RESIDUALS)
    L.append('- Series below %d residuals (excluded): %s' % (K.MIN_RESIDUALS, '; '.join('%s/%s n=%d' % (k[0], k[1], n) for k, n in short) or 'none'))
    L.append('- Series dropped from stability (a half < %d): %s' % (K.MIN_RESIDUALS, '; '.join(
        '%s/%s' % k for k, r in ex['rows'].items() if r['pi1'] is None) or 'none'))
    L.append('- Files with no lane 94–97 records: %s' % (', '.join(log['files_no_lane']) or 'none'))
    L.append('- Unparseable / non-window records (not guessed at): %d' % sum(log['excluded'].values()))
    for (rel, lane, why), n in sorted(log['excluded'].items()):
        L.append('  - `%s` @LAT%d: %d × %s' % (rel, lane, n, why))
    L.append('- Stream-less t_ms resets treated as segment breaks: ' + (
        ', '.join('%s @LAT%d ×%d' % (k[0], k[1], v) for k, v in sorted(log['streamless_break'].items())) or 'none'))
    L.append('- Link peers absent from the previous window (no residual): %d' % log['notes']['link_peer_not_in_previous_window'])
    L.append('- Duplicates dropped per file:')
    for rel, n in sorted(log['dups'].items()):
        L.append('  - `%s`: %d' % (rel, n))
    L += ['', '## Limitations (not corrected, only recorded)', '',
          '- "Chronological" split-half = segment encounter order (file-name sorted, then t_ms); t_ms restarts at each boot and records carry no wall time, so this is only as chronological as the file names.',
          '- Missing windows (gaps in t_ms) are not detected for @LAT94/@LAT97: the previous record is taken as the previous window.',
          '- `rms_mean` is RMS, so the int16 full-scale span makes acoustic residuals small by construction; this affects π for that channel and is part of what PW-1 measures.']
    return '\n'.join(L) + '\n'


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('root', help='path to master/ (read-only)')
    ap.add_argument('--report', help='write PW1-REPORT.md here')
    args = ap.parse_args(argv)
    series, log = load_archive(args.root)
    ex, un = analyze(series, 'exp'), analyze(series, 'unexp')
    txt = report(series, log, ex, un)
    if args.report:
        with open(args.report, 'w', encoding='utf-8', newline='\n') as fh:
            fh.write(txt)
    print(txt.split('\n', 1)[0])
    return 0


if __name__ == '__main__':
    sys.exit(main())
