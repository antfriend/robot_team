"""PW-2 and PW-4 offline replay (TTDB-RFC-0011 v0.1.4 section 8, stage 2).

Protocol and constants were committed (e3835e3) before this file existed. See
PW2-PW4-PROTOCOL.md. Read-only over master/. Scope, parsing and dedup are PW-1's:

    python tools/pw2/pw2_replay.py master --report tools/pw2/PW2-PW4-REPORT.md

Mechanics the protocol leaves open (fixed here, before any run):
  * Observation windows: runs are expanded (n windows = n-1 repeats of the previous value,
    then the current one), as in PW-1's verdict.
  * pi residuals for the online fold are |obs - previous obs of that channel| scaled to pe,
    as in PW-1; they never cross a segment. A belief's body persists across segments.
  * Link beliefs are per (node, peer, proto); a peer missing from a record ends that peer's
    sub-series.
  * Workspace clock: window index * 60000 ms. Decay: strength >> (dt // half_life), then
    a linear step toward the next halving. Attention gain a = 64 (unity).
  * Genuine step (PW-2 report item b): window i with pe(v_i, v_{i-1}) >= PE_AGREE whose next
    two windows stay within PE_AGREE of v_i. Latency = windows until that rule's rev rises,
    searched over the next 20.
"""
import argparse
import collections
import glob
import hashlib
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(os.path.dirname(HERE), 'pw1'))
import pw2_constants as C   # noqa: E402
import pw1_fold as P1       # noqa: E402
import pw1_constants as K1  # noqa: E402

SPAN = {'acoustic': K1.PE_SPAN_ACOUSTIC, 'motion': K1.PE_SPAN_MOTION, 'link': K1.PE_SPAN_LINK}
RANGE = {'acoustic': (0, 32767), 'motion': (0, 16000), 'link': (-120, -20)}
LANE_OF = {94: 'acoustic', 95: 'motion', 97: 'link'}


# ------------------------------------------------------------------ small helpers
def fnv1a(s):
    h = 0x811c9dc5
    for b in s.encode('utf-8'):
        h = ((h ^ b) * 0x01000193) & 0xFFFFFFFF
    return h


class Xorshift32:
    def __init__(self, seed):
        self.s = (seed & 0xFFFFFFFF) or 1

    def next(self):
        x = self.s
        x ^= (x << 13) & 0xFFFFFFFF
        x ^= x >> 17
        x ^= (x << 5) & 0xFFFFFFFF
        self.s = x
        return x


def pe_scalar(diff, span):
    return min(255, abs(diff) * 255 // span)


class Fold:
    """Online RFC 4.3 fold for one channel stream."""
    def __init__(self):
        self.var = 0
        self.n = 0

    def add(self, r):
        self.var += ((r * r) - self.var) >> C.PI_ALPHA
        self.n += 1

    @property
    def pi(self):
        if self.n < C.MIN_RESIDUALS:
            return C.PREC_DEFAULT
        return (255 * C.PI_SCALE) // (C.PI_SCALE + self.var)


# ------------------------------------------------------------------ workspace (RFC 5)
class Workspace:
    def __init__(self):
        self.t = {}            # target -> [strength, last_ms]
        self.ignitions = 0
        self.reclaims = 0
        self.rejected = 0

    def _decayed(self, tr, now):
        s, last = tr
        dt = max(0, now - last)
        n, rem = divmod(dt, C.WORKSPACE_HALF_LIFE_MS)
        s >>= n
        return s - (s * rem) // (2 * C.WORKSPACE_HALF_LIFE_MS)

    def offer(self, target, eps, now):
        for k in list(self.t):                       # evaluate decay; hysteresis drop
            if self._decayed(self.t[k], now) < C.THETA_OFF:
                del self.t[k]
        if target in self.t:
            if eps >= C.THETA_IGN:
                self.t[target] = [max(eps, self._decayed(self.t[target], now)), now]
            return
        if eps < C.THETA_IGN:
            return
        if len(self.t) < C.WORKSPACE_W:
            self.t[target] = [eps, now]
            self.ignitions += 1
            return
        weakest = min(self.t, key=lambda k: (self._decayed(self.t[k], now), self.t[k][1]))
        if eps > self._decayed(self.t[weakest], now):
            del self.t[weakest]
            self.t[target] = [eps, now]
            self.ignitions += 1
            self.reclaims += 1
        else:
            self.rejected += 1


# ------------------------------------------------------------------ the two update rules
class Belief:
    __slots__ = ('body', 'conf', 'rev', 'flag', 'contra')

    def __init__(self):
        self.body = None
        self.conf = C.CONF_BASELINE
        self.rev = 0
        self.flag = False
        self.contra = 0          # contradictions since the last revision


def update_fixed(b, obs, pe):
    if pe >= C.PE_AGREE:
        b.body = obs
        b.rev += 1
        b.conf = max(b.conf - C.CONF_DECREMENT, 0)
        return True, True
    b.conf = min(b.conf + C.CONF_INCREMENT, 255)
    return False, False


def update_gain(b, obs, pe, pi, ws=None, canary=False, key=None):
    """RFC 3.4. `ws` is passed so the canary can misbehave; the real rule never reads it.
    CANARY = the confirmation loop RFC 5.4 forbids: attended targets learn at doubled pi."""
    if canary and ws is not None and key in ws.t:
        pi = min(255, pi * 2)
    k = 128 if (pi + b.conf) == 0 else (255 * pi) // (pi + b.conf)
    if pe < C.PE_AGREE:
        b.conf += ((255 - b.conf) * pi) // 510
        return False, False
    if k >= C.K_REVISE:
        b.body = obs
        b.rev = min(b.rev + 1, 65535)
        b.conf = pi // 2
        return True, True
    b.conf -= (b.conf * k) // 255
    b.flag = True
    return False, True


# ------------------------------------------------------------------ series from the archive
def build_series(root):
    """-> {(node, channel, sub): [segment, ...]} with each segment a list of window values
    (runs expanded), and an exclusion log."""
    files = sorted(glob.glob(os.path.join(root, '**', '*.md'), recursive=True))
    log = collections.Counter()
    seen = set()
    groups = collections.OrderedDict()
    for path in files:
        node = P1.node_of(path)
        for lane, body in P1.split_records(path):
            if lane not in LANE_OF:
                continue
            rec, why = P1.parse_record(lane, body)
            if rec is None:
                log['unparseable: ' + why] += 1
                continue
            key = (node, lane, rec['stream'], rec['t'], hashlib.sha1(body.encode('utf-8', 'replace')).hexdigest())
            if key in seen:
                log['duplicate'] += 1
                continue
            seen.add(key)
            groups.setdefault((node, lane, rec['stream']), []).append(rec)
    out = collections.OrderedDict()
    for (node, lane, stream), recs in groups.items():
        if stream is not None:
            segs = [sorted(recs, key=lambda r: r['t'])]
        else:
            segs, cur = [], []
            for r in recs:
                if cur and r['t'] <= cur[-1]['t']:
                    segs.append(cur)
                    cur = []
                cur.append(r)
            if cur:
                segs.append(cur)
        ch = LANE_OF[lane]
        for seg in segs:
            if ch in ('acoustic', 'motion'):
                vals, prev = [], None
                for r in seg:
                    if prev is not None:
                        vals.extend([prev] * (r['run'] - 1))
                    vals.append(r['val'])
                    prev = r['val']
                out.setdefault((node, ch, ''), []).append(vals)
            else:
                open_ = {}
                for r in seg:
                    for k, v in r['links'].items():
                        open_.setdefault(k, []).append(v)
                    for k in [k for k in open_ if k not in r['links']]:
                        out.setdefault((node, ch, '%s|%s' % k), []).append(open_.pop(k))
                for k, vals in open_.items():
                    out.setdefault((node, ch, '%s|%s' % k), []).append(vals)
    return out, log


# ------------------------------------------------------------------ replay one series
def replay_series(name, ch, segs, rule, inject, ws, canary=False):
    span = SPAN[ch]
    lo, hi = RANGE[ch]
    b = Belief()
    f_real, f_twin = Fold(), Fold()
    rng = Xorshift32(C.PW2_NOISE_SEED ^ fnv1a(name))
    idx = 0
    snap = None
    rev_hist = []
    stats = {'contra_to_revise': [], 'steps': []}
    vals_flat = []
    for seg in segs:
        prev_real = prev_twin = None
        for v in seg:
            vals_flat.append(v)
            if idx == C.PW2_INJECT_AT:
                snap = (b.conf, b.rev)
            if b.body is None:
                b.body = v
                prev_real = v
                rev_hist.append(b.rev)
                idx += 1
                continue
            events = [(v, f_real, 'real')]
            if inject and idx >= C.PW2_INJECT_AT:
                mag = rng.next() % (span * C.PW2_NOISE_FRACTION_NUM // C.PW2_NOISE_FRACTION_DEN)
                sign = -1 if (rng.next() & 1) else 1
                events.append((max(lo, min(hi, v + sign * mag)), f_twin, 'twin'))
            for obs, fold, who in events:
                pe = pe_scalar(obs - b.body, span)
                pi = fold.pi
                if rule == 'fixed':
                    flipped, contra = update_fixed(b, obs, pe)
                else:
                    flipped, contra = update_gain(b, obs, pe, pi, ws, canary, name)
                if contra:
                    b.contra += 1
                if flipped:
                    if snap is not None:
                        stats['contra_to_revise'].append(b.contra)
                    b.contra = 0
                if ws is not None:
                    ws.offer(name, pe * pi // 255, idx * 60000)
                prev = prev_real if who == 'real' else prev_twin
                if prev is not None:
                    fold.add(pe_scalar(obs - prev, span))
                if who == 'real':
                    prev_real = obs
                else:
                    prev_twin = obs
            rev_hist.append(b.rev)
            idx += 1
    stats['rev_hist'] = rev_hist
    stats['snap'] = snap
    stats['vals'] = vals_flat
    stats['final'] = (b.body, b.conf, b.rev, b.flag)
    return stats


def genuine_steps(vals, span):
    out = []
    for i in range(1, len(vals) - 2):
        if (pe_scalar(vals[i] - vals[i - 1], span) >= C.PE_AGREE
                and pe_scalar(vals[i + 1] - vals[i], span) < C.PE_AGREE
                and pe_scalar(vals[i + 2] - vals[i], span) < C.PE_AGREE):
            out.append(i)
    return out


def store_hash(res):
    rows = sorted((k, r['final']) for k, r in res.items())
    return hashlib.sha256(json.dumps(rows, sort_keys=True, default=str).encode()).hexdigest()


def run_all(series, rule, inject, use_ws, canary=False):
    res, wsl = {}, []
    for (node, ch, sub), segs in series.items():
        name = '%s|%s|%s' % (node, ch, sub)
        ws = Workspace() if use_ws else None
        res[name] = replay_series(name, ch, segs, rule, inject, ws, canary)
        res[name]['ch'] = ch
        if ws:
            wsl.append(ws)
    return res, wsl


def med(xs):
    return P1.median(xs) if xs else None


# ------------------------------------------------------------------ verdicts
def pw2(series):
    fx, _ = run_all(series, 'fixed', True, False)
    gn, _ = run_all(series, 'gain', True, False)
    fx0, _ = run_all(series, 'fixed', False, False)
    gn0, _ = run_all(series, 'gain', False, False)
    coh = [k for k in fx if fx[k]['snap'] and gn[k]['snap']
           and fx[k]['snap'][0] >= C.PW2_HIGH_CONF and gn[k]['snap'][0] >= C.PW2_HIGH_CONF]
    flips = lambda R, ks: sum(R[k]['final'][2] - R[k]['snap'][1] for k in ks)
    f_fixed, f_gain = flips(fx, coh), flips(gn, coh)
    by_ch = collections.defaultdict(lambda: [0, 0, 0])
    for k in coh:
        c = by_ch[fx[k]['ch']]
        c[0] += 1
        c[1] += fx[k]['final'][2] - fx[k]['snap'][1]
        c[2] += gn[k]['final'][2] - gn[k]['snap'][1]
    if len(coh) < C.PW2_MIN_COHORT:
        verdict = 'INCONCLUSIVE'
    elif f_gain >= f_fixed:
        verdict = 'KILL'
    elif f_gain <= C.PW2_PASS_RATIO * f_fixed:
        verdict = 'PASS'
    else:
        verdict = 'INCONCLUSIVE'
    c2r = [n for k in coh for n in gn[k]['contra_to_revise']]
    # (a) genuine tracking with no injection; (b) latency on genuine steps
    lat = {'fixed': [], 'gain': []}
    nsteps = 0
    for k in fx0:
        steps = genuine_steps(fx0[k]['vals'], SPAN[fx0[k]['ch']])
        nsteps += len(steps)
        for rule, R in (('fixed', fx0), ('gain', gn0)):
            h = R[k]['rev_hist']
            for i in steps:
                base = h[i - 1]
                j = next((j for j in range(i, min(i + 21, len(h))) if h[j] > base), None)
                lat[rule].append(None if j is None else j - i)
    return {'verdict': verdict, 'cohort': len(coh), 'flips_fixed': f_fixed, 'flips_gain': f_gain,
            'by_ch': dict(by_ch), 'c2r': c2r, 'series': len(fx),
            'noinject_flips': {'fixed': sum(r['final'][2] for r in fx0.values()),
                               'gain': sum(r['final'][2] for r in gn0.values())},
            'steps': nsteps,
            'lat': {r: (sum(1 for x in v if x is not None), med([x for x in v if x is not None])) for r, v in lat.items()}}


def pw4(series):
    pairs, rows = True, []
    ign = 0
    for rule in ('fixed', 'gain'):
        for inject in (False, True):
            off, _ = run_all(series, rule, inject, False)
            on, wsl = run_all(series, rule, inject, True)
            ign += sum(w.ignitions for w in wsl)
            same = store_hash(off) == store_hash(on)
            pairs &= same
            rows.append((rule, 'injected' if inject else 'archive', same, sum(w.ignitions for w in wsl)))
    off, _ = run_all(series, 'gain', True, False)
    can, _ = run_all(series, 'gain', True, True, canary=True)
    canary_caught = store_hash(off) != store_hash(can)
    if not pairs:
        verdict = 'KILL'
    elif C.PW4_CANARY_REQUIRED and not canary_caught:
        verdict = 'INCONCLUSIVE'
    else:
        verdict = 'PASS'
    return {'verdict': verdict, 'rows': rows, 'canary': canary_caught, 'ignitions': ign}


# ------------------------------------------------------------------ report
def report(series, log, a, b):
    L = []
    L.append('PW-2: %s — gain-scaled flips %d vs fixed-step %d on %d high-conf beliefs (pass ≤ %.1f, kill ≥ %d)' % (
        a['verdict'], a['flips_gain'], a['flips_fixed'], a['cohort'], C.PW2_PASS_RATIO * a['flips_fixed'], a['flips_fixed']))
    L.append('PW-4: %s — %d of %d workspace on/off pairs identical; canary %s; %d ignitions' % (
        b['verdict'], sum(1 for r in b['rows'] if r[2]), len(b['rows']),
        'caught' if b['canary'] else 'NOT caught', b['ignitions']))
    L += ['', 'Protocol and constants: `PW2-PW4-PROTOCOL.md`, `pw2_constants.py` (committed e3835e3 before this code existed).', '',
          '## PW-2 — gain protects settled beliefs', '',
          '- Series replayed: %d (acoustic, motion, link; entity excluded). Cohort (conf ≥ %d at window %d under both rules): **%d**.' % (
              a['series'], C.PW2_HIGH_CONF, C.PW2_INJECT_AT, a['cohort']),
          '- Flips after injection, summed over the cohort: fixed-step **%d**, gain-scaled **%d**.' % (a['flips_fixed'], a['flips_gain']),
          '', '| channel | cohort | fixed flips | gain flips |', '|---|---|---|---|']
    for ch, (n, f, g) in sorted(a['by_ch'].items()):
        L.append('| %s | %d | %d | %d |' % (ch, n, f, g))
    L += ['', '**Immunity check.** Contradictions a cohort belief absorbed before §3.4 revised it: median %s over %d revisions (min %s, max %s).' % (
        med(a['c2r']), len(a['c2r']), min(a['c2r']) if a['c2r'] else '-', max(a['c2r']) if a['c2r'] else '-'),
          '', '**Genuine change (no injection, reported, no verdict).** Total body rewrites over all series: fixed %d, gain %d. Genuine persistent steps found in the data: %d; revised within 20 windows — fixed %d (median latency %s), gain %d (median latency %s).' % (
              a['noinject_flips']['fixed'], a['noinject_flips']['gain'], a['steps'],
              a['lat']['fixed'][0], a['lat']['fixed'][1], a['lat']['gain'][0], a['lat']['gain'][1]),
          '', '**Reading the result (descriptive; nothing re-tuned).** The cohort is dominated by link beliefs (%d of %d); acoustic and motion contribute %d and %d. The fixed-step rule rewrites a body on every contradiction by construction, so a large fixed-step count is expected; the informative numbers are that §3.4 still rewrote %d bodies under noise (it is protection, not immunity), and that without injection it revised %d of %d genuine steps against %d for fixed-step, i.e. it follows real change a little less often.' % (
              a['by_ch'].get('link', [0])[0], a['cohort'], a['by_ch'].get('acoustic', [0])[0], a['by_ch'].get('motion', [0])[0],
              a['flips_gain'], a['lat']['gain'][0], a['steps'], a['lat']['fixed'][0]),
          '', '## PW-4 — empty workspace changes no answer', '',
          '| rule | replay | store identical (off vs on) | ignitions |', '|---|---|---|---|']
    for rule, kind, same, ign in b['rows']:
        L.append('| %s | %s | %s | %d |' % (rule, kind, 'yes' if same else '**NO**', ign))
    L += ['', 'Canary (update path deliberately reads the workspace): store %s.' % (
        'differed, so the test can fail' if b['canary'] else 'did NOT differ, so the test cannot fail'),
          '', '## Exclusions and notes', '']
    for k, v in sorted(log.items()):
        L.append('- %s: %d' % (k, v))
    short = sorted(k for k, segs in series.items() if sum(len(s) for s in segs) <= C.PW2_INJECT_AT)
    L.append('- Series with ≤ %d windows (no snapshot, outside every cohort): %d of %d' % (C.PW2_INJECT_AT, len(short), len(series)))
    L += ['- PW-4 is a test of this reference implementation: the update functions take the workspace as an argument only so the canary can misuse it. It shows the specified update rule does not depend on workspace state; it cannot show that firmware code never will.']
    return '\n'.join(L) + '\n'


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('root')
    ap.add_argument('--report')
    args = ap.parse_args(argv)
    series, log = build_series(args.root)
    a, b = pw2(series), pw4(series)
    txt = report(series, log, a, b)
    if args.report:
        with open(args.report, 'w', encoding='utf-8', newline='\n') as fh:
            fh.write(txt)
    sys.stdout.buffer.write((txt.split('\n', 2)[0] + '\n' + txt.split('\n', 2)[1] + '\n').encode('utf-8'))
    return 0


if __name__ == '__main__':
    sys.exit(main())
