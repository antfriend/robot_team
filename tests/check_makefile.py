"""check_makefile.py -- prove every target in tests/Makefile actually builds from its own
variable. Run it before committing a Makefile change.

WHY THIS EXISTS. On 2026-08-09 this Makefile was found to reference FOUR undefined
variables (TSTREAM_SRCS, LG_SRCS, TF_SRCS, and then CIT_SRCS, added by the very session
that fixed the first three). Make expands an undefined variable to nothing and invokes the
compiler with no input files; because the recipe leaves the previous binary in place,
`make test` then runs a STALE .exe and reports PASS. The suite's own "12/12" was true of
three programs nobody had compiled.

⚠ THE FAILURE MODE IS THAT EVERYTHING LOOKS FINE. A missing variable produces a green run,
not a red one, which is why it survived long enough to happen four times. The check that
caught the fourth instance was itself fooled first: `grep -c test_citation Makefile`
returned 3 and looked like success -- it had counted the three REFERENCES to a variable
that was never DEFINED.

So this script does the only thing that cannot be fooled: it expands each variable the way
make would, refuses an empty expansion, and compiles it.

    python tests/check_makefile.py
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
LIB = "../firmware/libraries"
CXX = os.environ.get("CXX_CHECK", r"C:/tmp/toolchain/zig-windows-x86_64-0.13.0/zig.exe")
CXX_ARGS = ["c++"] if "zig" in os.path.basename(CXX).lower() else []


def load():
    with open(os.path.join(HERE, "Makefile"), encoding="utf-8") as f:
        return f.read()


def targets(mk):
    """-> [(variable, output)] straight from the build recipe, so a target added to the
    Makefile is checked automatically rather than when somebody remembers to list it."""
    return re.findall(r"\$\(CXX\)[^\n]*?\$\((\w+)\)\s+-o\s+(\S+)", mk)


def expand(mk, var, depth=0):
    m = re.search(r"^%s\s*:=[ \t]*((?:[^\n\\]|\\\n)*)" % re.escape(var), mk, re.M)
    if not m:
        return None                      # UNDEFINED -- the whole point of this script
    text = m.group(1).replace("\\\n", " ")
    # Resolve one level of nested variable (e.g. $(TS)), which is all this file uses.
    for nested in set(re.findall(r"\$\((\w+)\)", text)):
        if nested == "LIB":
            continue
        sub = expand(mk, nested, depth + 1)
        if sub is None:
            return None
        text = text.replace("$(%s)" % nested, " ".join(sub))
    text = text.replace("$(LIB)", LIB)
    return [t for t in text.split() if t.endswith((".cpp", ".c"))]


def main():
    mk = load()
    includes = re.search(r"^INCLUDES\s*:=[ \t]*(.*)$", mk, re.M).group(1)
    includes = includes.replace("$(LIB)", LIB).split()

    tg = targets(mk)
    if not tg:
        print("no compile targets found -- has the recipe format changed?")
        return 1

    listed = set(re.findall(r"^\t\./(\S+)", mk, re.M))
    bad = []
    print(f"{len(tg)} target(s) in the build recipe\n")
    for var, out in tg:
        srcs = expand(mk, var)
        if srcs is None:
            print(f"  {var:14s} -> {out:22s} UNDEFINED VARIABLE")
            bad.append(var)
            continue
        if not srcs:
            print(f"  {var:14s} -> {out:22s} EXPANDS TO NO SOURCES")
            bad.append(var)
            continue
        missing = [s for s in srcs if not os.path.exists(os.path.join(HERE, s))]
        if missing:
            print(f"  {var:14s} -> {out:22s} MISSING SOURCE {missing}")
            bad.append(var)
            continue
        cmd = ([CXX] + CXX_ARGS + ["-std=c++11", "-Wall", "-Wextra", "-O2"]
               + includes + srcs + ["-o", out + ".exe"])
        r = subprocess.run(cmd, cwd=HERE, capture_output=True, text=True)
        ok = r.returncode == 0
        run = " (in `make test`)" if out in listed else "  ⚠ NOT RUN by `make test`"
        print(f"  {var:14s} -> {out:22s} {'OK' if ok else 'BUILD FAIL'}{run}")
        if not ok:
            bad.append(var)
            for line in r.stderr.strip().split("\n")[:3]:
                print("      " + line)
        elif out not in listed:
            bad.append(out + " (built but never run)")

    print()
    if bad:
        print(f"{len(bad)} PROBLEM(S): " + ", ".join(bad))
        return 1
    print("every target builds from its own variable, and every one is run")
    return 0


if __name__ == "__main__":
    sys.exit(main())
