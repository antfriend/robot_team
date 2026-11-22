#!/usr/bin/env python3
"""test_ew_py.py — TTDB-RFC-0011 stage 1, laptop half: fleet.parse_ew() reads [ew] + prec.

The SAME vectors as tests/test_ew.cpp (tests/vectors/ew_vectors.txt), so the firmware and
laptop readers are proven to agree case by case (TTDB-RFC-0010 §7.2: test the pair). The
format is described at the top of that file; this loader must stay a line-for-line twin of
the one in test_ew.cpp.

Also reads every [ew] block in the archive's @LAT91 lane (read-only) as the pre-RFC
corpus: all must parse, and none may carry `prec`, because nothing has ever written it.

Run: python tests/test_ew_py.py
"""
import glob
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "orchestrator"))
import fleet as c  # noqa: E402

KEYS = ("present", "conf", "rev", "sal", "touched", "prec",
        "has_conf", "has_rev", "has_sal", "has_touched", "has_prec")
fails = 0


def check(cond, msg):
    global fails
    if not cond:
        print("FAIL: " + msg)
        fails += 1


def load_cases(path):
    raw = open(path, "rb").read()
    if b"\r" in raw:
        raise SystemExit(f"FAIL: {path} contains CR bytes — it must be checked out eol=lf")
    cases, body, name, flags = [], None, None, ()
    for line in raw.decode("utf-8").split("\n"):
        if body is None:
            if line.startswith("=== "):
                parts = line[4:].split(" ")
                name, flags, body = parts[0], parts[1:], []
            continue
        if line.startswith("--- expect "):
            sep = "\r\n" if "crlf" in flags else "\n"
            text = sep.join(body) + ("" if "noeol" in flags else sep)
            expect = {}
            for tok in line[len("--- expect "):].split(" "):
                if ":" in tok:
                    k, v = tok.split(":", 1)
                    expect[k] = int(v)
            cases.append((name, text, expect))
            body = None
            continue
        body.append(line)
    return cases


def main():
    cases = load_cases(os.path.join(HERE, "vectors", "ew_vectors.txt"))
    check(len(cases) >= 25, f"vector file holds the full case list (got {len(cases)})")
    for name, text, expect in cases:
        check(sorted(expect) == sorted(KEYS), f"{name}: expect line lists all 11 keys")
        got = c.parse_ew(text)
        for k in KEYS:
            check(int(got[k]) == expect.get(k), f"{name}: {k} = {expect.get(k)} (got {got[k]})")

    # The archive (read-only): every @LAT91 record is the pre-RFC shape.
    master = os.path.join(HERE, "..", "master")
    n = 0
    for path in glob.glob(os.path.join(master, "**", "*.md"), recursive=True):
        text = open(path, encoding="utf-8", errors="replace").read()
        for rec in text.split("\n---\n"):
            rec = rec.lstrip("\n")
            if not rec.startswith("@LAT91LON") or "\n[ew]\n" not in rec[:400]:
                continue
            n += 1
            w = c.parse_ew(rec)
            check(w["present"] and w["has_conf"] and w["has_rev"] and w["has_sal"]
                  and w["has_touched"], f"{os.path.basename(path)}: @LAT91 [ew] parses")
            check(not w["has_prec"] and w["prec"] == 128,
                  f"{os.path.basename(path)}: pre-RFC record carries no prec")
    if os.path.isdir(master):
        check(n > 0, "archive @LAT91 [ew] blocks found (master/ present)")
    print(f"parse_ew: {len(cases)} shared vector case(s), {n} archived @LAT91 block(s), "
          f"{fails} failure(s)")
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
