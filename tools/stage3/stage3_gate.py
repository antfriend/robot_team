"""Stage 3 gate: does every @LAT108 record re-derive, exactly, from the episodes in a pull?

docs/design/rfc0011-stage3.md §6. Read-only over the pull.

    python tools/stage3/stage3_gate.py tools/stage3/pulls/<pull>.md
    python tools/stage3/stage3_gate.py --replay <pull.md>        # fold every band, no records
    python tools/stage3/stage3_gate.py --fill-vectors tests/vectors/precision_vectors.txt

The PARSER (parse_record), the RESIDUALS (residuals_for -> _scalar/_entity/_link) and the
ARITHMETIC (fold_var/pi_from_var) are tools/pw1/pw1_fold.py's own, imported unmodified, with
PW-1b's spans (tools/pw1b.apply_spans). What is new here is only what stage 3 defines: which
episodes (a tier's LON band, file order), the `said: N | ` prefix, and the segment rule (§3).
"""
import argparse
import collections
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'pw1b'))
import pw1b_run as PB     # noqa: E402  (imports tools/pw1/pw1_fold as PB.F)
sys.path.insert(0, os.path.join(HERE, '..', '..', 'orchestrator'))
import fleet              # noqa: E402  (stage 1's [ew] reader, fleet.parse_ew)

F = PB.F
PB.apply_spans()          # acoustic 900, motion 60, link 90 — registered in 6fda802

TIER_SPAN = 8192
CHANS = ('link', 'entity', 'motion', 'acoustic')          # = semantic::Tier order
PW1_LANE = {'acoustic': 94, 'motion': 95, 'entity': 96, 'link': 97}
SAID = re.compile(r'(?m)^said: \d+ \| ')
REC = re.compile(r'^@LAT(-?\d+)LON(-?\d+)\s*\|', re.M)


def conf_from_n(n):
    """min(240, 16 * floor(log2(1 + n))) — design D4."""
    return min(240, 16 * ((1 + n).bit_length() - 1))


def records(text):
    """-> [(lat, lon, record text from its header to the next header)] in file order."""
    hits = list(REC.finditer(text))
    out = []
    for i, m in enumerate(hits):
        end = hits[i + 1].start() if i + 1 < len(hits) else len(text)
        out.append((int(m.group(1)), int(m.group(2)), text[m.start():end]))
    return out


def band(recs, chan):
    k = CHANS.index(chan)
    return [(lon, t) for lat, lon, t in recs if lat == 103 and k * TIER_SPAN <= lon < (k + 1) * TIER_SPAN]


def fold(chan, episodes):
    """episodes: [(lon, record text)] in file order -> the numbers a @LAT108 record carries."""
    lane = PW1_LANE[chan]
    notes = collections.Counter()
    excluded, segs, cur = 0, [], []
    order = []                                   # every parsed window, for the pw1 diagnostic
    for lon, text in episodes:
        body = SAID.sub('', text.split('\n', 1)[1] if '\n' in text else '')
        rec, _why = F.parse_record(lane, body)
        if rec is None:
            excluded += 1
            continue
        order.append(rec)
        prev = cur[-1] if cur else None
        if prev is None or rec['stream'] != prev['stream'] or rec['t'] <= prev['t']:
            if cur:
                segs.append(cur)
            cur = [rec]
        else:
            cur.append(rec)
    if cur:
        segs.append(cur)
    res = []
    for s in segs:
        res.extend(F.residuals_for(lane, s, notes)[0])     # [0] = runs expanded
    var = F.fold_var(res)
    return {'var': var, 'n': len(res), 'prec': F.pi_from_var(var), 'conf': conf_from_n(len(res)),
            'episodes': len(episodes), 'excluded': excluded, 'segments': len(segs),
            'peers_absent': notes['link_peer_not_in_previous_window'],
            'pw1_grouping_same': res == _pw1_grouping(lane, order)}


def _pw1_grouping(lane, order):
    """Residuals the way pw1's load_archive groups: per stream (first-appearance order), each
    streamed group SORTED by t_ms; stream-less records broken where t_ms does not increase."""
    groups = collections.OrderedDict()
    for r in order:
        groups.setdefault(r['stream'], []).append(r)
    notes = collections.Counter()
    res = []
    for stream, rs in groups.items():
        if stream is not None:
            segs = [sorted(rs, key=lambda r: r['t'])]
        else:
            segs, cur = [], []
            for r in rs:
                if cur and r['t'] <= cur[-1]['t']:
                    segs.append(cur)
                    cur = []
                cur.append(r)
            if cur:
                segs.append(cur)
        for s in segs:
            res.extend(F.residuals_for(lane, s, notes)[0])
    return res


FIELD = re.compile(r'\b(\w+):(@LAT\d+LON\d+|-?\d+|\w+)')


def parse_precision(text):
    """A @LAT108 record -> dict of its **PRECISION** / **FOLD** fields, or None."""
    out = {}
    for tag in ('**PRECISION**', '**FOLD**'):
        line = next((ln for ln in text.splitlines() if ln.startswith(tag)), None)
        if line is None:
            return None
        for k, v in FIELD.findall(line[len(tag):]):
            out[k] = v
    ew = fleet.parse_ew(text)
    out['ew_conf'] = str(ew['conf']) if ew['has_conf'] else None
    return out


def _succ(lon):
    k = lon // TIER_SPAN
    return k * TIER_SPAN + ((lon - k * TIER_SPAN + 1) % TIER_SPAN)


def gate(text, earlier=()):
    """-> [(chan, verdict, detail)] for every @LAT108 record in a pull.

    `earlier`: texts of earlier pulls (design §11 D9). Episodes are immutable, so a range
    episode missing from this pull may be read from an earlier one; one present in both
    with DIFFERENT text FAILs the record (an immutable record changed)."""
    recs = records(text)
    old = {}
    for e in earlier:
        for lat, lon, t in records(e):
            if lat == 103:
                old.setdefault(lon, t)
    if earlier:
        return _gate_d9(recs, old)
    out = []
    for lat, lon, t in recs:
        if lat != 108:
            continue
        p = parse_precision(t)
        if p is None or p.get('chan') not in CHANS:
            out.append(('?', 'FAIL', 'unparseable @LAT108LON%d' % lon))
            continue
        chan = p['chan']
        if int(p.get('skipped', 0)):
            out.append((chan, 'FAIL', 'skipped:%s episodes the node could not read' % p['skipped']))
            continue
        lo = int(p['from'].split('LON')[1])
        hi = int(p['through'].split('LON')[1])
        eps = band(recs, chan)
        lons = [e[0] for e in eps]
        if lo not in lons or hi not in lons:
            out.append((chan, 'UNVERIFIABLE', 'range @LAT103LON%d..%d not wholly in the pull' % (lo, hi)))
            continue
        a, b = lons.index(lo), lons.index(hi)
        sl = eps[a:b + 1] if a <= b else None
        ok = sl is not None and len(sl) == int(p['episodes']) and all(
            _succ(sl[i][0]) == sl[i + 1][0] for i in range(len(sl) - 1))
        if not ok:
            out.append((chan, 'UNVERIFIABLE', 'range not contiguous / count != episodes:%s' % p['episodes']))
            continue
        got = fold(chan, sl)
        want = {'var': int(p['var']), 'n': int(p['n']), 'prec': int(p['prec']),
                'conf': int(p['ew_conf']) if p['ew_conf'] else None,
                'episodes': int(p['episodes']), 'excluded': int(p['excluded']),
                'segments': int(p['segments'])}
        diff = {k: (want[k], got[k]) for k in want if want[k] != got[k]}
        detail = 'n %d var %d prec %d conf %d over %d episodes%s' % (
            got['n'], got['var'], got['prec'], got['conf'], got['episodes'],
            '' if got['pw1_grouping_same'] else '; ⚠ pw1 grouping would differ')
        out.append((chan, 'FAIL' if diff else 'MATCH',
                    detail if not diff else 'record vs refold: ' + ', '.join(
                        '%s %s != %s' % (k, w, g) for k, (w, g) in diff.items())))
    return out


def _norm(t):
    return t.replace('\r\n', '\n').rstrip()


def _gate_d9(recs, old):
    """gate() with episodes also drawn from earlier pulls (D9): the range is walked BY
    ORDINAL from `from` to `through` (wrapping at 8192) and must be `episodes:` long."""
    cur = {lon: t for lat, lon, t in recs if lat == 103}
    out = []
    for lat, lon, t in recs:
        if lat != 108:
            continue
        p = parse_precision(t)
        if p is None or p.get('chan') not in CHANS:
            out.append(('?', 'FAIL', 'unparseable @LAT108LON%d' % lon))
            continue
        chan = p['chan']
        if int(p.get('skipped', 0)):
            out.append((chan, 'FAIL', 'skipped:%s episodes the node could not read' % p['skipped']))
            continue
        lo = int(p['from'].split('LON')[1])
        hi = int(p['through'].split('LON')[1])
        want_n = int(p['episodes'])
        sl, from_old, changed, missing = [], 0, None, None
        o = lo
        for _ in range(want_n):
            a, b = cur.get(o), old.get(o)
            if a is not None and b is not None and _norm(a) != _norm(b):
                changed = o
                break
            if a is None and b is None:
                missing = o
                break
            if a is None:
                from_old += 1
            sl.append((o, a if a is not None else b))
            if o == hi:
                break
            o = _succ(o)
        if changed is not None:
            out.append((chan, 'FAIL', 'episode @LAT103LON%d differs between pulls' % changed))
            continue
        if missing is not None:
            out.append((chan, 'UNVERIFIABLE', 'episode @LAT103LON%d in no pull' % missing))
            continue
        if len(sl) != want_n or sl[-1][0] != hi:
            out.append((chan, 'UNVERIFIABLE', 'range @LAT103LON%d..%d is not episodes:%d long' % (
                lo, hi, want_n)))
            continue
        got = fold(chan, sl)
        want = {'var': int(p['var']), 'n': int(p['n']), 'prec': int(p['prec']),
                'conf': int(p['ew_conf']) if p['ew_conf'] else None,
                'episodes': want_n, 'excluded': int(p['excluded']),
                'segments': int(p['segments'])}
        diff = {k: (want[k], got[k]) for k in want if want[k] != got[k]}
        detail = 'n %d var %d prec %d conf %d over %d episodes%s%s' % (
            got['n'], got['var'], got['prec'], got['conf'], got['episodes'],
            ' (%d from earlier pull)' % from_old if from_old else '',
            '' if got['pw1_grouping_same'] else '; ⚠ pw1 grouping would differ')
        out.append((chan, 'FAIL' if diff else 'MATCH',
                    detail if not diff else 'record vs refold: ' + ', '.join(
                        '%s %s != %s' % (k, w, g) for k, (w, g) in diff.items())))
    return out


# ---- shared vectors (tests/vectors/precision_vectors.txt) ------------------------------------
def load_vectors(path):
    """-> [(name, chan, [(lon, text)], expect_line_index_or_None, expect_dict)]"""
    lines = open(path, encoding='utf-8').read().split('\n')
    cases, i = [], 0
    while i < len(lines):
        ln = lines[i]
        if ln.startswith('=== '):
            parts = ln[4:].split()
            name, chan = parts[0], parts[1].split(':', 1)[1]
            eps, j, exp_at, exp = [], i + 1, None, {}
            while j < len(lines) and not lines[j].startswith('=== '):
                if lines[j].startswith('--- episode lon:'):
                    lon, body, j = int(lines[j].split(':', 1)[1]), [], j + 1
                    while j < len(lines) and not lines[j].startswith('--- '):
                        body.append(lines[j])
                        j += 1
                    eps.append((lon, '\n'.join(body) + '\n'))
                    continue
                if lines[j].startswith('--- expect'):
                    exp_at = j
                    exp = dict(kv.split(':', 1) for kv in lines[j][len('--- expect'):].split())
                j += 1
            cases.append((name, chan, eps, exp_at, {k: int(v) for k, v in exp.items()}))
            i = j
            continue
        i += 1
    return cases, lines


EXPECT_KEYS = ('var', 'n', 'prec', 'conf', 'episodes', 'excluded', 'segments', 'peers_absent')


def fill_vectors(path):
    cases, lines = load_vectors(path)
    for name, chan, eps, at, _ in cases:
        r = fold(chan, eps)
        line = '--- expect ' + ' '.join('%s:%d' % (k, r[k]) for k in EXPECT_KEYS)
        if at is None:
            raise SystemExit('%s: no --- expect line to fill' % name)
        lines[at] = line
    with open(path, 'w', encoding='utf-8', newline='\n') as fh:
        fh.write('\n'.join(lines))
    print('filled %d case(s)' % len(cases))


def _p108(text):
    """chan -> (rev, from_lon) for each @LAT108 record of a pull."""
    out = {}
    for lat, _lon, t in records(text):
        if lat != 108:
            continue
        p = parse_precision(t)
        if not p or 'chan' not in p:
            continue
        ew = fleet.parse_ew(t)
        m = re.match(r'@LAT103LON(\d+)$', p.get('from', ''))
        out[p['chan']] = (ew['rev'] if ew['has_rev'] else None, int(m.group(1)) if m else None)
    return out


def independence(prev_text, text):
    """Design §6, run 2 onward: is each channel's record in `text` an INDEPENDENT check
    against the pull before it? -> [(chan, verdict, detail)], verdict one of
    NEW-WRITE (higher rev), UNMOVED (from is still the band's oldest episode in this pull,
    i.e. what D7 leaves unrewritten), NOT-INDEPENDENT, or MISSING."""
    before, now = _p108(prev_text), _p108(text)
    recs = records(text)
    out = []
    for chan in CHANS:
        if chan not in now:
            out.append((chan, 'MISSING', 'no @LAT108 record in this pull'))
            continue
        rev, frm = now[chan]
        prev_rev = before.get(chan, (None, None))[0]
        eps = band(recs, chan)
        oldest = eps[0][0] if eps else None
        if rev is not None and (prev_rev is None or rev > prev_rev):
            out.append((chan, 'NEW-WRITE', 'rev %s -> %s' % (prev_rev, rev)))
        elif frm is not None and frm == oldest:
            out.append((chan, 'UNMOVED', 'rev %s, from @LAT103LON%d is the oldest' % (rev, frm)))
        else:
            out.append((chan, 'NOT-INDEPENDENT',
                        'rev %s unchanged, from %s but oldest is %s' % (rev, frm, oldest)))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('pull', nargs='?')
    ap.add_argument('--previous', help='the earlier pull: also check design §6 run-2 '
                    'independence (each record a new write, or its window unmoved)')
    ap.add_argument('--replay', help='fold every tier band of this file (no @LAT108 needed)')
    ap.add_argument('--fill-vectors')
    a = ap.parse_args(argv)
    if a.fill_vectors:
        fill_vectors(a.fill_vectors)
        return 0
    if a.replay:
        text = open(a.replay, encoding='utf-8', errors='replace').read()
        recs = records(text)
        for chan in CHANS:
            r = fold(chan, band(recs, chan))
            print('%s %s' % (chan, ' '.join('%s:%d' % (k, r[k]) for k in EXPECT_KEYS)))
        return 0
    text = open(a.pull, encoding='utf-8', errors='replace').read()
    prev = open(a.previous, encoding='utf-8', errors='replace').read() if a.previous else None
    res = gate(text, (prev,) if prev is not None else ())   # D9: episodes from the earlier pull
    for chan, v, d in res:
        print('%-8s %-12s %s' % (chan, v, d))
    chans = {c for c, v, _ in res if v == 'MATCH'}
    allok = res and all(v == 'MATCH' for _, v, _ in res) and chans == set(CHANS)
    print('GATE (this pull): %s — %d record(s), MATCH on %s' % (
        'MATCH x4' if allok else 'NOT YET', len(res), ', '.join(sorted(chans)) or 'none'))
    if a.previous:
        ind = independence(prev, text)
        for chan, v, d in ind:
            print('%-8s %-15s %s' % (chan, v, d))
        indep = all(v in ('NEW-WRITE', 'UNMOVED') for _, v, _ in ind)
        print('INDEPENDENCE (vs %s): %s' % (os.path.basename(a.previous),
                                             'OK x4' if indep else 'NOT INDEPENDENT'))
        allok = allok and indep
    return 0 if allok else 1


if __name__ == '__main__':
    sys.exit(main())
