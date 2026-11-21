#!/usr/bin/env python3
"""Decompilation progress: bytes and functions of Capcom code compiled from matching C.

Usage:  tools/progress.py [target ...]        (default: all; groups: all, executables, overlays)

A function counts as decompiled when the linked ELF has no `NAME.NON_MATCHING` symbol for it
(splat's macro adds one to every function still in assembly, including INCLUDE_ASM and parked
ones). Code is attributed to source files by the yaml's code subsegments. PsyQ library objects
(psyq/...) and hand-written assembly (subsegments named asm_...) are reported but excluded from
the totals: neither is meant to become C. Build each target first.

One target gets a table per source file; several get one line each, and a total in which the
shared stage code (src/stage_common/, linked into several overlays) counts once.
"""

import subprocess
import sys
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
import targets  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
GROUPS = {"all": targets.TARGETS, "executables": targets.EXECUTABLES, "overlays": targets.OVERLAYS}
CODE_TYPES = {"c", "asm", "hasm"}


def subsegments(target):
    """[(start vram, end vram, name, type)] for the code segment's subsegments, in file order."""
    doc = yaml.safe_load((ROOT / f"config/{target}/{target}.yaml").read_text())
    main = next(s for s in doc["segments"] if isinstance(s, dict) and s.get("type") == "code")
    rom, vram = main["start"], main["vram"]
    rows = []
    for sub in main["subsegments"]:
        if isinstance(sub, dict):
            off, typ, name = sub["start"], sub.get("type"), sub.get("name", "")
        else:
            off, typ = sub[0], sub[1] if len(sub) > 1 else None
            name = sub[2] if len(sub) > 2 else f"{off:X}"
        rows.append((off, str(typ).lstrip("."), str(name)))
    # Each subsegment ends where the next one starts.
    out = []
    for (off, typ, name), nxt in zip(rows, rows[1:] + [(None, None, None)]):
        if typ in CODE_TYPES and nxt[0] is not None:
            out.append((vram + off - rom, vram + nxt[0] - rom, name, typ))
    return out


def functions(target):
    """({address: (size, name)} for FUNC symbols, set of names still in assembly)."""
    elf = ROOT / "build" / target / f"{target}.elf"
    if not elf.exists():
        sys.exit(f"{elf} not found: build {target} first")
    out = subprocess.run(["mips-linux-gnu-readelf", "-sW", str(elf)], capture_output=True, text=True,
                         check=True).stdout
    funcs, asm = {}, set()
    for line in out.splitlines():
        f = line.split()
        if len(f) < 8:
            continue
        name = f[7]
        if name.endswith(".NON_MATCHING"):
            asm.add(name[: -len(".NON_MATCHING")])
        elif f[3] == "FUNC":
            funcs[int(f[1], 16)] = (int(f[2], 0), name)
    # Fill in missing sizes from the next function's address.
    addrs = sorted(funcs)
    for i, a in enumerate(addrs):
        size, name = funcs[a]
        if size == 0 and i + 1 < len(addrs):
            funcs[a] = (addrs[i + 1] - a, name)
    return funcs, asm


def pct(a, b):
    return 100.0 * a / b if b else 0.0


def tally(target):
    """([(file, type, done bytes, bytes, done functions, functions)], {excluded kind: [bytes, n]})."""
    funcs, asm = functions(target)
    rows = []
    excluded = {"psyq": [0, 0], "hand-written": [0, 0]}
    for lo, hi, name, typ in subsegments(target):
        members = [(s, n) for a, (s, n) in funcs.items() if lo <= a < hi]
        size = sum(s for s, _ in members)
        if name.startswith("psyq/"):
            excluded["psyq"][0] += size
            excluded["psyq"][1] += len(members)
            continue
        if name.startswith("asm_"):
            excluded["hand-written"][0] += size
            excluded["hand-written"][1] += len(members)
            continue
        done = [(s, n) for s, n in members if n not in asm]
        rows.append((name, typ, sum(s for s, _ in done), size, len(done), len(members)))
    return rows, excluded


def total(rows):
    return [sum(r[i] for r in rows) for i in (2, 3, 4, 5)]


def line(label, d, size, fd, ft, mark=""):
    return (f"  {label:22} {d:>8}/{size:<8} {pct(d, size):6.2f}%   "
            f"{fd:>5}/{ft:<5} {pct(fd, ft):6.2f}%{mark}")


def report(target):
    import review  # tools/review.py: the owner's reviews

    rows, excluded = tally(target)
    d, size, fd, ft = total(rows)
    print(f"\n{target}")
    print(f"  {'file':22} {'bytes':>17}  {'%':>7}   {'functions':>11}  {'%':>7}")
    print(line("all Capcom code", d, size, fd, ft))
    for name, typ, d, size, fd, ft in sorted(rows, key=lambda r: (-pct(r[2], r[3]), r[0])):
        if size:
            print(line(name, d, size, fd, ft, "" if typ == "c" else "  (asm)"))
    for what, (size, n) in excluded.items():
        if n:
            print(f"  {'(excluded) ' + what:22} {size:>17}           {n:>11} functions")
    st = review.status(target)
    rev = sum(v == "Yes" for v in st.values())
    chg = len(st) - rev
    print(f"  reviewed: {rev}/{total(rows)[2]} functions with C" + (f", {chg} changed since review" if chg else ""))


def main():
    names = []
    for arg in sys.argv[1:] or ["all"]:
        if arg in GROUPS:
            names += GROUPS[arg]
        elif arg in targets.TARGETS:
            names.append(arg)
        else:
            sys.exit(f"unknown target {arg!r}: a target, or one of {', '.join(GROUPS)}")
    if len(names) == 1:
        report(names[0])
        return
    print(f"  {'target':22} {'bytes':>17}  {'%':>7}   {'functions':>11}  {'%':>7}")
    grand, shared = [], {}
    for t in names:
        rows, _ = tally(t)
        print(line(t, *total(rows)))
        common = set(targets.shared_files(t))
        grand += [r for r in rows if r[0] not in common]
        for r in rows:
            if r[0] in common:
                shared.setdefault(r[0], r)
    if shared:
        print(line("(shared stage code)", *total(shared.values())))
    print(line("all, each file once", *total(grand + list(shared.values()))))


if __name__ == "__main__":
    main()
