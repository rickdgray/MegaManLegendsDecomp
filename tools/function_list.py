#!/usr/bin/env python3
"""Write the game's function list as a CSV: File, Function, Name, Decompiled, Matched.

Usage:  tools/function_list.py [-o functions.csv]

One row per Capcom function, in address order per program:
- slus_006.03 and rock_neo.exe: FUNC symbols from the linked ELFs (build both first). File is the
  yaml subsegment (`rock_neo.exe/cd`, `rock_neo.exe/code_80014AC0`, ...): rock_neo_files.md's
  proposed split, so it changes as boundaries are settled. PsyQ objects and hand-written
  assembly (`asm_*`) are left out; neither becomes C.
- Overlays: split into functions by dupe_scan.py (run tools/extract_overlays.py first). File is
  the overlay (`ST03`) until it is split into source files. Byte-identical copies (ST03B, ...)
  are left out: they build from the same source.

Function = splat's default name (`func_<ADDRESS>`); Name = the name it was given, blank if none.
Decompiled = the function has C: matching, or parked in a `#ifdef NON_MATCHING` block.
Matched = its C builds byte-identical (no NAME.NON_MATCHING symbol in the ELF).
"""

import argparse
import csv
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dupe_scan  # noqa: E402
import progress  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
TARGET_OF = {"SLUS": "slus_006.03", "ROCK_NEO": "rock_neo.exe"}
PARKED = re.compile(r"#ifdef NON_MATCHING\b(.*?)#endif", re.S)
INCLUDE = re.compile(r'INCLUDE_ASM\("[^"]*",\s*(\w+)\);')


def parked(target):
    """Names of functions with a parked C attempt in src/<target>/."""
    names = set()
    for c in (ROOT / "src" / target).glob("**/*.c"):
        for block in PARKED.findall(c.read_text()):
            names.update(INCLUDE.findall(block))
    return names


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("-o", "--out", default="functions.csv", help="output file (default: functions.csv)")
    args = ap.parse_args()

    rows = []
    for prog, ws, base, funcs, _local in dupe_scan.programs():
        target = TARGET_OF.get(prog)
        if target is None:
            for f, e, name, matched in funcs:
                rows.append((prog, name, "", "No", "No"))
            continue
        subs = progress.subsegments(target)
        attempts = parked(target)
        for f, e, name, matched in funcs:
            addr = base + f * 4
            sub = next((s for s in subs if s[0] <= addr < s[1]), None)
            if sub is None or sub[2].startswith(("psyq/", "asm_")):
                continue
            decompiled = matched or name in attempts
            default = f"func_{addr:08X}"
            rows.append((f"{target}/{sub[2]}", default, "" if name == default else name,
                         "Yes" if decompiled else "No", "Yes" if matched else "No"))

    with open(ROOT / args.out if not Path(args.out).is_absolute() else args.out, "w",
              newline="") as fh:
        w = csv.writer(fh)
        w.writerow(["File", "Function", "Name", "Decompiled", "Matched"])
        w.writerows(rows)

    dec = sum(r[3] == "Yes" for r in rows)
    mat = sum(r[4] == "Yes" for r in rows)
    print(f"wrote {args.out}: {len(rows)} functions, {dec} decompiled, {mat} matched, "
          f"{len({r[0] for r in rows})} files")


if __name__ == "__main__":
    main()
