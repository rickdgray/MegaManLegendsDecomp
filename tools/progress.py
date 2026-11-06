#!/usr/bin/env python3
"""Decompilation progress: bytes and functions of Capcom code compiled from matching C.

Usage:  tools/progress.py [target ...]        (default: every target)

A function counts as decompiled when the linked ELF has no `NAME.NON_MATCHING` symbol for it
(splat's macro adds one to every function still in assembly, including INCLUDE_ASM and parked
ones). Code is attributed to source files by the yaml's code subsegments. PsyQ library objects
(psyq/...) and hand-written assembly (subsegments named asm_...) are reported but excluded from
the totals: neither is meant to become C. Build each target first.
"""

import subprocess
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
TARGETS = ["slus_006.03", "rock_neo.exe"]
VRAM_BASE, ROM_BASE = 0x80010000, 0x800
CODE_TYPES = {"c", "asm", "hasm"}


def subsegments(target):
    """[(start vram, end vram, name, type)] for the main segment's subsegments, in file order."""
    doc = yaml.safe_load((ROOT / f"{target}.yaml").read_text())
    main = next(s for s in doc["segments"] if isinstance(s, dict) and s.get("type") == "code")
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
            out.append((VRAM_BASE + off - ROM_BASE, VRAM_BASE + nxt[0] - ROM_BASE, name, typ))
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


def report(target):
    funcs, asm = functions(target)
    rows, tot = [], {"done": 0, "total": 0, "fdone": 0, "ftotal": 0}
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
        d = sum(s for s, _ in done)
        rows.append((name, typ, d, size, len(done), len(members)))
        tot["done"] += d
        tot["total"] += size
        tot["fdone"] += len(done)
        tot["ftotal"] += len(members)

    print(f"\n{target}")
    print(f"  {'file':22} {'bytes':>17}  {'%':>7}   {'functions':>11}  {'%':>7}")
    print(f"  {'all Capcom code':22} {tot['done']:>8}/{tot['total']:<8} {pct(tot['done'], tot['total']):6.2f}%   "
          f"{tot['fdone']:>5}/{tot['ftotal']:<5} {pct(tot['fdone'], tot['ftotal']):6.2f}%")
    for name, typ, d, size, fd, ft in sorted(rows, key=lambda r: (-pct(r[2], r[3]), r[0])):
        if size == 0:
            continue
        mark = "" if typ == "c" else "  (asm)"
        print(f"  {name:22} {d:>8}/{size:<8} {pct(d, size):6.2f}%   {fd:>5}/{ft:<5} {pct(fd, ft):6.2f}%{mark}")
    for what, (size, n) in excluded.items():
        if n:
            print(f"  {'(excluded) ' + what:22} {size:>17}           {n:>11} functions")
    return tot


def main():
    targets = sys.argv[1:] or TARGETS
    grand = {"done": 0, "total": 0}
    for t in targets:
        tot = report(t)
        grand["done"] += tot["done"]
        grand["total"] += tot["total"]
    if len(targets) > 1:
        print(f"\nall targets: {grand['done']}/{grand['total']} bytes, {pct(grand['done'], grand['total']):.2f}%")


if __name__ == "__main__":
    main()
