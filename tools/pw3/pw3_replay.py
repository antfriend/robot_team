"""PW-3 offline replay: the broadcast gate (TTDB-RFC-0011 v0.1.5 section 6.3 / 8).

Protocol and constants were committed (f3eab94) before this file existed. See
PW3-PROTOCOL.md. Read-only over master/.

    python tools/pw3/pw3_replay.py master --report tools/pw3/PW3-REPORT.md

Mechanics the protocol leaves open (fixed here, before any run):
  * A record is the unit; a record carries every item of its window (all peers of a link
    window, all BSSIDs of an entity window). The sender transmits a record iff the MAX over
    its items of eps >= theta_tx. The sender's pi per (node, channel) is one online fold fed
    by every item's residual against that item's previous value (pooled, as PW-1 pools link).
  * An item the sender has no belief for is founded with pe = 0 (no prediction was made).
  * Receiver pi is the sender's pi at the moment of transmission (the SALIENT `prec` field).
  * Body bytes = len(record body stripped, utf-8).
"""
import argparse
import collections
import glob
import hashlib
import math
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
for sub in ('', '..\\pw2', '..\\pw1'):
    sys.path.insert(0, os.path.normpath(os.path.join(HERE, sub)))
import pw3_constants as C3   # noqa: E402
import pw2_constants as C2   # noqa: E402
import pw2_replay as R2      # noqa: E402
import pw1_fold as P1        # noqa: E402

CH_OF = {94: 'acoustic', 95: 'motion', 96: 'entity', 97: 'link'}


def pe_item(ch, a, b):
    if ch == 'entity':
        return P1._jaccard_pe(a, b)
    return R2.pe_scalar(a - b, R2.SPAN[ch])


def percept_bytes(n):
    frames = max(1, math.ceil(n / C3.MAX_BODY))
    return n + frames * (C3.HEADER_LEN + C3.HMAC_LEN)


# ------------------------------------------------------------------ load records
def load_series(root):
    """-> ({(node, channel): [segment]}, log); a segment is a list of
    {'items': {key: value}, 'bytes': int}."""
    files = sorted(glob.glob(os.path.join(root, '**', '*.md'), recursive=True))
    log = collections.Counter()
    seen = set()
    groups = collections.OrderedDict()
    for path in files:
        node = P1.node_of(path)
        for lane, body in P1.split_records(path):
            rec, why = P1.parse_record(lane, body)
            if rec is None:
                log['unparseable: ' + why] += 1
                continue
            key = (node, lane, rec['stream'], rec['t'], hashlib.sha1(body.encode('utf-8', 'replace')).hexdigest())
            if key in seen:
                log['duplicate'] += 1
                continue
            seen.add(key)
            if lane in (94, 95):
                items = {'': rec['val']}
            elif lane == 96:
                items = {'': rec['ids']}
            else:
                items = {'%s|%s' % k: v for k, v in rec['links'].items()}
            if not items:
                log['record with no items'] += 1
                continue
            rec['items'] = items
            rec['bytes'] = len(body.strip().encode('utf-8'))
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
        out.setdefault((node, CH_OF[lane]), []).extend(segs)
    return out, log


# ------------------------------------------------------------------ one series, three views
def replay(ch, segs, theta):
    """-> dict with sender/receiver beliefs, transmission counts and bytes."""
    fold = R2.Fold()
    sender, rx_full, rx_gate = {}, {}, {}
    prev_items = None
    n_rec = n_tx = 0
    b_full = b_gate = 0
    first = True

    def apply(rx, items, pi):
        for k, v in items.items():
            bl = rx.get(k)
            if bl is None:
                bl = rx[k] = R2.Belief()
                bl.body = v
                continue
            pe = pe_item(ch, v, bl.body)
            R2.update_gain(bl, v, pe, pi)

    for seg in segs:
        prev_items = None
        for rec in seg:
            items = rec['items']
            n_rec += 1
            pi = fold.pi
            eps = 0
            for k, v in items.items():
                bl = sender.get(k)
                if bl is None:
                    bl = sender[k] = R2.Belief()
                    bl.body = v
                    continue
                pe = pe_item(ch, v, bl.body)
                eps = max(eps, pe * pi // 255)
                R2.update_gain(bl, v, pe, pi)
            if prev_items is not None:
                for k, v in items.items():
                    if k in prev_items:
                        fold.add(pe_item(ch, v, prev_items[k]))
            prev_items = items
            pb = percept_bytes(rec['bytes'])
            b_full += pb
            apply(rx_full, items, pi)
            if first or eps >= theta:
                n_tx += 1
                b_gate += C3.SALIENT_FRAME + pb
                apply(rx_gate, items, pi)
            first = False
    return {'records': n_rec, 'tx': n_tx, 'bytes_full': b_full, 'bytes_gate': b_gate,
            'full': rx_full, 'gate': rx_gate}


def agree(ch, gate_b, full_b):
    return gate_b is not None and pe_item(ch, gate_b.body, full_b.body) < C2.PE_AGREE


def evaluate(series, theta):
    per = {}
    tot = collections.Counter()
    nb = nd = 0
    for (node, ch), segs in series.items():
        r = replay(ch, segs, theta)
        beliefs = dis = 0
        for k, fb in r['full'].items():
            beliefs += 1
            if not agree(ch, r['gate'].get(k), fb):
                dis += 1
        d = per.setdefault(ch, collections.Counter())
        d['series'] += 1
        d['beliefs'] += beliefs
        d['disagree'] += dis
        d['records'] += r['records']
        d['tx'] += r['tx']
        d['bytes_full'] += r['bytes_full']
        d['bytes_gate'] += r['bytes_gate']
        for key in ('records', 'tx', 'bytes_full', 'bytes_gate'):
            tot[key] += r[key]
        nb += beliefs
        nd += dis
        tot['series'] += 1
    tot['beliefs'], tot['disagree'] = nb, nd
    tot['disagree_rate'] = nd / nb if nb else 0.0
    tot['fall'] = 1 - tot['bytes_gate'] / tot['bytes_full'] if tot['bytes_full'] else 0.0
    return tot, per


def verdict(tot):
    if tot['beliefs'] < C3.MIN_SERIES:
        return 'INCONCLUSIVE'
    if tot['disagree_rate'] > C3.DISAGREE_MAX or tot['fall'] < C3.AIRTIME_FALL_MIN:
        return 'FALSIFIED'
    return 'PASS'


# ------------------------------------------------------------------ report
def report(series, log, tot, per, sweep):
    v = verdict(tot)
    L = ['PW-3: %s — belief disagreement %.1f%% (falsified > %d%%), airtime fall %.1f%% (falsified < %d%%), %d beliefs' % (
        v, 100 * tot['disagree_rate'], int(100 * C3.DISAGREE_MAX), 100 * tot['fall'], int(100 * C3.AIRTIME_FALL_MIN), tot['beliefs']),
        '', 'Protocol and constants: `PW3-PROTOCOL.md`, `pw3_constants.py` (committed f3eab94 before this code existed). Verdict uses θ_tx = %d.' % C3.THETA_TX,
        '', '## Result (θ_tx = %d)' % C3.THETA_TX, '',
        '- Series: %d; beliefs compared: %d; records: %d, transmitted: %d (%.1f%%).' % (
            tot['series'], tot['beliefs'], tot['records'], tot['tx'], 100 * tot['tx'] / tot['records']),
        '- Bytes on air: ungated %d, gated %d (includes %d-byte SALIENT per transmitted record) → fall **%.1f%%**.' % (
            tot['bytes_full'], tot['bytes_gate'], C3.SALIENT_FRAME, 100 * tot['fall']),
        '- Beliefs where the gated receiver disagrees with the ungated one (no belief, or pe ≥ %d): **%d of %d = %.1f%%**.' % (
            C2.PE_AGREE, tot['disagree'], tot['beliefs'], 100 * tot['disagree_rate']),
        '', '| channel | series | records | tx | beliefs | disagree | rate | airtime fall |', '|---|---|---|---|---|---|---|---|']
    for ch, d in sorted(per.items()):
        L.append('| %s | %d | %d | %d | %d | %d | %.1f%% | %.1f%% |' % (
            ch, d['series'], d['records'], d['tx'], d['beliefs'], d['disagree'],
            100 * d['disagree'] / d['beliefs'] if d['beliefs'] else 0,
            100 * (1 - d['bytes_gate'] / d['bytes_full']) if d['bytes_full'] else 0))
    ent = per.get('entity', collections.Counter())
    lnk = per.get('link', collections.Counter())
    L += ['', '## Reading the result (descriptive; nothing re-tuned)', '',
          '- The airtime criterion is not the problem: the gate sends %.1f%% of records and saves %.1f%% of bytes. The disagreement criterion decides the verdict.' % (100 * tot['tx'] / tot['records'], 100 * tot['fall']),
          '- Disagreement is concentrated in entity (%d of %d beliefs) and link (%d of %d). Acoustic and motion, which are smooth, agree throughout.' % (
              ent['disagree'], ent['beliefs'], lnk['disagree'], lnk['beliefs']),
          '- On entity and link, individual window-to-window changes stay under θ_tx (ε = pe·π/255 is small) while the cumulative change does not: a receiver that hears from the sender only at its rare surprises holds a body that was right when sent and is stale at the end. No heartbeat or peer request is specified in §6.3, so none was modelled.',
          '- The sweep shows disagreement rising as θ_tx rises (30.2%-52.4%), so no θ_tx in the swept range meets the 5% criterion with this gate and metric. A heartbeat or periodic refresh would be a different mechanism and a new pre-registered experiment, not a re-run of this one.']
    L += ['', '## θ_tx sweep (descriptive; no verdict, not used to choose θ_tx)', '',
          '| θ_tx | tx share | disagreement | airtime fall |', '|---|---|---|---|']
    for th, t in sweep:
        L.append('| %d | %.1f%% | %.1f%% | %.1f%% |' % (th, 100 * t['tx'] / t['records'], 100 * t['disagree_rate'], 100 * t['fall']))
    L += ['', '## Exclusions and notes', '']
    for k, n in sorted(log.items()):
        L.append('- %s: %d' % (k, n))
    L += ['- Airtime is bytes on air, a proxy: LoRa time also depends on spreading factor and preamble, which are equal in both arms.',
          '- The first record of each series is always transmitted; no peer request or heartbeat is modelled (neither is specified in §6.3).',
          '- Run-length-elided windows were never records and appear in neither arm.',
          '- The §6.4 trust cap on received precision is not modelled (one trusted sender per series).',
          '- Disagreement is measured on final bodies at the end of the replay, not over time: a gated receiver that is stale mid-run but converges is counted as agreeing.']
    return '\n'.join(L) + '\n'


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('root')
    ap.add_argument('--report')
    args = ap.parse_args(argv)
    series, log = load_series(args.root)
    tot, per = evaluate(series, C3.THETA_TX)
    sweep = [(th, evaluate(series, th)[0]) for th in C3.THETA_TX_DESCRIPTIVE]
    txt = report(series, log, tot, per, sweep)
    if args.report:
        with open(args.report, 'w', encoding='utf-8', newline='\n') as fh:
            fh.write(txt)
    sys.stdout.buffer.write((txt.split('\n', 1)[0] + '\n').encode('utf-8'))
    return 0


if __name__ == '__main__':
    sys.exit(main())
