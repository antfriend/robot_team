"""PW-1b: PW-1 re-run with pe_span from rule R1/R2 (TTDB-RFC-0011 open question 6).

Protocol and constants: PW1B-PROTOCOL.md, pw1b_constants.py (committed 6fda802 before
this file existed). Read-only over master/.

    python tools/pw1b/pw1b_run.py master/ --report tools/pw1b/PW1B-REPORT.md

The fold, parser, series rules and decision rule are tools/pw1/pw1_fold.py, imported
UNMODIFIED. The only change is the three span constants, replaced in memory on its
constants module before anything is read (apply_spans).
"""
import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, '..', 'pw1'))
import pw1_fold as F            # noqa: E402
import pw1b_constants as B      # noqa: E402

K = F.K                          # pw1's constants module, shared by every pw1 function
SCALARS = ('acoustic', 'motion', 'link')
PW1_MEDIANS = {'acoustic': 255, 'motion': 255, 'link': 250, 'entity': 132}   # RFC §8.1


def apply_spans():
    """Swap in PW-1b's spans. Returns PW-1's, for the report and the tests."""
    old = (K.PE_SPAN_ACOUSTIC, K.PE_SPAN_MOTION, K.PE_SPAN_LINK)
    K.PE_SPAN_ACOUSTIC, K.PE_SPAN_MOTION, K.PE_SPAN_LINK = (
        B.PE_SPAN_ACOUSTIC, B.PE_SPAN_MOTION, B.PE_SPAN_LINK)
    return old


def q6(ex):
    """Per scalar channel: (median pi, saturated?, reading). Missing channel -> None."""
    m8 = ex['median'][K.PI_SCALE]
    out = {}
    for ch in SCALARS:
        if ch not in m8:
            out[ch] = None
            continue
        sat = m8[ch] >= B.SATURATED_AT
        out[ch] = (m8[ch], sat, 'quiet at its declared scale' if sat
                   else "PW-1's span was too wide for this channel")
    return out


def distinct_pairs(ex):
    m8 = ex['median'][K.PI_SCALE]
    chans = [c for c in SCALARS if c in m8]
    return [(a, b, abs(m8[a] - m8[b]) > B.DISTINCT_BY, abs(m8[a] - m8[b]))
            for i, a in enumerate(chans) for b in chans[i + 1:]]


def report(series, log, ex, un, old):
    L = ['PW-1b: %s — %s' % (ex['verdict'], F.deciding(ex)), '',
         'Verdict from the runs-expanded computation (fixed in advance). Runs-unexpanded: '
         '**%s** — %s.%s' % (un['verdict'], F.deciding(un),
                             '' if un['verdict'] == ex['verdict'] else ' **The two disagree.**'),
         '', '## Open question 6 (pre-registered: saturated iff median π ≥ %d)' % B.SATURATED_AT, '',
         '| channel | PW-1 span | PW-1b span | PW-1 median π | PW-1b median π | saturated | reading |',
         '|---|---|---|---|---|---|---|']
    spans = dict(zip(SCALARS, zip(old, (B.PE_SPAN_ACOUSTIC, B.PE_SPAN_MOTION, B.PE_SPAN_LINK))))
    for ch, r in q6(ex).items():
        if r is None:
            L.append('| %s | %d | %d | %d | — | — | no series with ≥ %d residuals |' % (
                ch, spans[ch][0], spans[ch][1], PW1_MEDIANS[ch], K.MIN_RESIDUALS))
        else:
            L.append('| %s | %d | %d | %d | %d | %s | %s |' % (
                ch, spans[ch][0], spans[ch][1], PW1_MEDIANS[ch], r[0], 'yes' if r[1] else 'no', r[2]))
    L += ['', 'Distinguishability (descriptive, medians differ by > %d): ' % B.DISTINCT_BY + '; '.join(
        '%s/%s %s (Δ %d)' % (a, b, 'distinct' if d else 'not distinct', g)
        for a, b, d, g in distinct_pairs(ex)), '']
    L += ['## Constants', '', '| constant | value | rule / source |', '|---|---|---|',
          '| pe_span acoustic | %d | R1 `ACOUSTICPERCEPT_TRANSIENT_FLOOR` |' % B.PE_SPAN_ACOUSTIC,
          '| pe_span motion | %d mg | R1 `MOTIONPERCEPT_MOVING_MG` |' % B.PE_SPAN_MOTION,
          '| pe_span link | %d dB | R2 LinkPercept clamp [−100, −10]; R1 `PERCEPTLEARN_RSSI_BAND` excluded (archive-derived) |' % B.PE_SPAN_LINK,
          '| everything else | PW-1 | `tools/pw1/pw1_constants.py`, unchanged |', '',
          '## Scope', '',
          '- Files: %d; distinct records: %s; duplicates dropped: %d.' % (
              log['files'], ', '.join('@LAT%d %d' % kv for kv in sorted(log['records'].items())),
              sum(log['dups'].values())),
          '- Same scope, dedup and series rules as PW-1 (lanes 94–97; `@LAT103` is outside it).',
          '', '## Checks — runs expanded (verdict)', ''] + F.checks(ex)
    L += ['', '## Checks — runs not expanded', ''] + F.checks(un)
    L += ['', '## Series — runs expanded', ''] + F.table(ex)
    L += ['', '## Series — runs not expanded', ''] + F.table(un)
    L += ['', '## Exclusions and notes', '']
    short = sorted((k, len(s['exp'])) for k, s in series.items() if len(s['exp']) < K.MIN_RESIDUALS)
    L.append('- Series below %d residuals (excluded): %s' % (K.MIN_RESIDUALS, '; '.join(
        '%s/%s n=%d' % (k[0], k[1], n) for k, n in short) or 'none'))
    L.append('- Series dropped from stability (a half < %d): %s' % (K.MIN_RESIDUALS, '; '.join(
        '%s/%s' % k for k, r in ex['rows'].items() if r['pi1'] is None) or 'none'))
    L.append('- Unparseable / non-window records (not guessed at): %d' % sum(log['excluded'].values()))
    for (rel, lane, why), n in sorted(log['excluded'].items()):
        L.append('  - `%s` @LAT%d: %d × %s' % (rel, lane, n, why))
    L.append('- Stream-less t_ms resets treated as segment breaks: ' + (', '.join(
        '%s @LAT%d ×%d' % (k[0], k[1], v) for k, v in sorted(log['streamless_break'].items())) or 'none'))
    L.append('- Link peers absent from the previous window (no residual): %d'
             % log['notes']['link_peer_not_in_previous_window'])
    L.append('- Files with no lane 94–97 records: %d (listed in PW1-REPORT.md; same archive)'
             % len(log['files_no_lane']))
    return '\n'.join(L) + '\n'


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('root', help='path to master/ (read-only)')
    ap.add_argument('--report', help='write PW1B-REPORT.md here')
    args = ap.parse_args(argv)
    old = apply_spans()
    series, log = F.load_archive(args.root)
    ex, un = F.analyze(series, 'exp'), F.analyze(series, 'unexp')
    txt = report(series, log, ex, un, old)
    if args.report:
        with open(args.report, 'w', encoding='utf-8', newline='\n') as fh:
            fh.write(txt)
    print(txt.split('\n', 1)[0])
    return 0


if __name__ == '__main__':
    sys.exit(main())
