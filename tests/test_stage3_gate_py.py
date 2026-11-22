#!/usr/bin/env python3
"""test_stage3_gate_py.py — the stage-3 gate (tools/stage3/stage3_gate.py), laptop half.

docs/design/rfc0011-stage3.md §6-§7. Three things:
  1. The gate's fold reproduces tests/vectors/precision_vectors.txt — the same file
     test_precision.cpp checks the FIRMWARE fold against. Both must agree.
  2. A record RENDERED BY THE C++ CODE (`test_precision --render-sample`) gates MATCH: the
     only check that the gate parses the format the firmware actually writes.
  3. The verdicts can each happen: a changed number FAILs, a missing episode is
     UNVERIFIABLE (never a pass), `skipped:` > 0 FAILs.

Needs tests/test_precision(.exe) built (run-all builds natives first). A missing binary is a
FAILURE, not a skip: a gate test that silently skipped its cross-language half would be the
hollow-green failure this repo has paid for twice ([[build-step-that-leaves-old-artefact]]).

Run: python tests/test_stage3_gate_py.py
"""
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "tools", "stage3"))
import stage3_gate as G  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    if not cond:
        print("FAIL: " + msg)
        fails += 1


def main():
    # 1. vectors
    cases, _ = G.load_vectors(os.path.join(HERE, "vectors", "precision_vectors.txt"))
    check(len(cases) >= 9, f"vector file holds the full case list (got {len(cases)})")
    for name, chan, eps, _at, want in cases:
        got = G.fold(chan, eps)
        check(sorted(want) == sorted(G.EXPECT_KEYS), f"{name}: expect line lists all fields")
        for k in G.EXPECT_KEYS:
            check(got[k] == want.get(k), f"{name}: {k} = {want.get(k)} (gate got {got[k]})")
        if name == "hand_worked_acoustic":
            check((got["var"], got["prec"], got["n"]) == (4090, 170, 5),
                  "hand_worked_acoustic is pw1's 4090 / 170 / 5")

    # 2. a C++-rendered record
    exe = None
    for cand in ("test_precision.exe", "test_precision"):
        p = os.path.join(HERE, cand)
        if os.path.exists(p):
            exe = p
            break
    check(exe is not None, "tests/test_precision binary exists (build natives first)")
    if exe:
        out = subprocess.run([exe, "--render-sample"], capture_output=True, text=True)
        check(out.returncode == 0, "test_precision --render-sample ran")
        sample = out.stdout
        res = G.gate(sample)
        check(res == [] or len(res) == 1, f"one @LAT108 record in the sample (got {len(res)})")
        check(len(res) == 1 and res[0][1] == "MATCH",
              f"the C++-rendered record gates MATCH (got {res})")

        # 3. each verdict can happen
        bad = sample.replace(" var:", " var:1", 1)
        check(G.gate(bad)[0][1] == "FAIL", "a changed var FAILs")
        cut = sample.split("\n---\n\n@LAT103LON16384", 1)
        gone = cut[0] + "\n---\n\n@LAT103LON9" + cut[1] if len(cut) == 2 else sample
        check(G.gate(gone)[0][1] == "UNVERIFIABLE", "a missing first episode is UNVERIFIABLE")
        sk = sample.replace(" skipped:0", " skipped:1", 1)
        check(G.gate(sk)[0][1] == "FAIL", "skipped > 0 FAILs")
        # gate() on a pull with only one channel is not the stage pass (main() says NOT YET)
        check(G.main([_tmp(sample)]) == 1, "one channel of four is not a gate pass")

    # 4. a record the D3b JOB wrote through the real Ttdb (append + removeCuts, rev 1 after
    #    the oldest episode was cut: design D7). test_precision_job leaves the store behind.
    jout = os.path.join(HERE, "test_precision_job.out.md")
    check(os.path.exists(jout), "tests/test_precision_job.out.md exists (run test_precision_job first)")
    if os.path.exists(jout):
        with open(jout, encoding="utf-8", newline="") as fh:
            store = fh.read()
        res = G.gate(store)
        check(len(res) == 1 and res[0][1] == "MATCH",
              f"the job-written record (rev 1, from moved) gates MATCH (got {res})")
        check("rev:1" in store and "from:@LAT103LON24577" in store,
              "the job store holds the D7 rewrite (rev 1, from @LAT103LON24577)")
        # 5. design §6 run-2 independence: a higher rev is a NEW-WRITE
        ind = dict((c, v) for c, v, _ in G.independence(store.replace("rev:1", "rev:0", 1), store))
        check(ind.get("acoustic") == "NEW-WRITE", f"rev 0 -> 1 is NEW-WRITE (got {ind})")
        check(ind.get("link") == "MISSING", "a channel with no record is MISSING")
        same = dict((c, v) for c, v, _ in G.independence(store, store))
        check(same.get("acoustic") == "UNMOVED",
              f"same rev, from still the band's oldest -> UNMOVED (got {same})")

        # 5b. D9: an episode missing from this pull is read from the earlier one; one that
        #     differs between pulls FAILs; one in no pull is UNVERIFIABLE.
        cut = store.split("\n---\n\n@LAT103LON24577 ", 1)
        if len(cut) == 2:
            rest = cut[1].split("\n---\n\n", 1)
            thin = cut[0] + ("\n---\n\n" + rest[1] if len(rest) == 2 else "")
            r = G.gate(thin, (store,))
            check(len(r) == 1 and r[0][1] == "MATCH" and "1 from earlier pull" in r[0][2],
                  f"D9: a missing episode is read from the earlier pull (got {r})")
            r = G.gate(thin, ("",))
            check(len(r) == 1 and r[0][1] == "UNVERIFIABLE", f"D9: in no pull -> UNVERIFIABLE (got {r})")
            r = G.gate(store, (store.replace("rms_mean:1036", "rms_mean:1037", 1),))
            check(len(r) == 1 and r[0][1] == "FAIL" and "differs" in r[0][2],
                  f"D9: an episode that changed between pulls FAILs (got {r})")
        else:
            check(False, "job store holds @LAT103LON24577")

    # 6. run 1's own two pulls (committed evidence): acoustic was NOT-INDEPENDENT, the
    #    other three UNMOVED — the finding that motivated D7.
    pulls = os.path.join(HERE, "..", "tools", "stage3", "pulls")
    p1 = os.path.join(pulls, "cardputer_20261122_1249_g1.md")
    p2 = os.path.join(pulls, "cardputer_20261122_1302_g2.md")
    if os.path.exists(p1) and os.path.exists(p2):
        r = dict((c, v) for c, v, _ in G.independence(open(p1, encoding="utf-8").read(),
                                                      open(p2, encoding="utf-8").read()))
        check(r == {"link": "UNMOVED", "entity": "UNMOVED", "motion": "UNMOVED",
                    "acoustic": "NOT-INDEPENDENT"}, f"run 1 independence reproduces (got {r})")
    else:
        check(False, "run 1 pulls present in tools/stage3/pulls/")

    print(f"stage3_gate: {len(cases)} vector case(s), {fails} failure(s)")
    return 1 if fails else 0


def _tmp(text):
    import tempfile
    fd, p = tempfile.mkstemp(suffix=".md")
    with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(text)
    return p


if __name__ == "__main__":
    sys.exit(main())
