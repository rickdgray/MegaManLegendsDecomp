#!/usr/bin/env python3
"""Bank functions whose byte-identical twin is already decompiled (tier 1 duplicates).

Usage:  tools/twins.py [target] [--apply] [--unsolved]

Within one executable, two functions with the same bytes (jumps inside the function compared
relative to its start) do the same thing to the same globals and callees, so the banked twin's C
is the candidate's C. Without --apply, lists each still-INCLUDE_ASM function that has a banked
twin. With --apply, copies the twin's definition over each such INCLUDE_ASM line (renamed, with a
`// Same code as X.` comment), builds, and keeps it only if the build prints MATCH; otherwise the
file is restored and the function is reported as failed (a static of another file, a jump table
in .rodata, a $gp variable defined elsewhere, ...). No agent, no tokens.

--unsolved: also lists groups of twins that are all still in assembly, so a batch can take them
together (decompile one, then run this script).

Needs the target built (function boundaries come from build/<t>/<t>.elf, bytes from the disc
file, as find_dupes.py). Parked twins (NON_MATCHING) are not copied: only matched C is trusted.
Run `./tools/rebuild.sh <t>` afterwards if anything was banked (refreshes expected/ and
functions.csv).
"""

import argparse
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import find_dupes  # noqa: E402
import targets  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
INC = re.compile(r'^INCLUDE_ASM\("([^"]+)",\s*(\w+)\);\s*$')
HEADER = re.compile(r"^[A-Za-z_][\w\s\*]*?\b(\w+)\s*\([^;{]*\)\s*$")


def key(data, addr, size):
    """The function's words, with `j` targets inside the function made relative to its start."""
    off = addr - find_dupes.VRAM_BASE + find_dupes.HEADER
    out = []
    for (w,) in struct.iter_unpack("<I", data[off:off + size]):
        if w >> 26 == 2:
            t = (addr & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
            if addr <= t < addr + size:
                out.append(("j", t - addr))
                continue
        out.append(w)
    return tuple(out)


def scan_c(target):
    """name -> info for every function in the target's C files: kind is 'asm' (INCLUDE_ASM outside
    NON_MATCHING), 'parked' or 'c'; for 'c', the definition's text; for 'asm', the line."""
    funcs = {}
    for c in sorted((ROOT / find_dupes.TARGETS[target]["src"]).glob("**/*.c")):
        lines = c.read_text().split("\n")
        in_nm = False   # between #ifdef NON_MATCHING and its #else
        in_else = False
        i = 0
        while i < len(lines):
            s = lines[i]
            if s.startswith("#ifdef NON_MATCHING"):
                in_nm = True
            elif s.startswith("#else") and in_nm:
                in_nm, in_else = False, True
            elif s.startswith("#endif") and (in_nm or in_else):
                in_nm = in_else = False
            m = INC.match(s.strip())
            if m:
                funcs[m.group(2)] = {"kind": "parked" if in_else else "asm", "file": c,
                                     "line": s.strip()}
            elif not in_nm and not s.startswith(("#", "/", " ", "\t", "{", "}")) and \
                    i + 1 < len(lines) and lines[i + 1] == "{":
                h = HEADER.match(s)
                if h:
                    end = lines.index("}", i + 1)
                    funcs.setdefault(h.group(1), {"kind": "c", "file": c,
                                                  "text": "\n".join(lines[i:end + 1])})
                    i = end
            i += 1
    return funcs


def build_ok(target):
    r = subprocess.run(["./tools/build.sh", target], cwd=ROOT, capture_output=True, text=True)
    return "MATCH" in r.stdout and "MISMATCH" not in r.stdout


def main():
    targets.default_target()
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target", choices=targets.TARGETS)
    ap.add_argument("--apply", action="store_true", help="bank the twins (build-checked)")
    ap.add_argument("--unsolved", action="store_true", help="also list all-assembly twin groups")
    args = ap.parse_args()
    t = args.target

    data = (ROOT / find_dupes.TARGETS[t]["disc"]).read_bytes()
    groups = defaultdict(list)
    for addr, size, name in find_dupes.functions(t):
        groups[key(data, addr, size)].append((addr, size, name))
    cfuncs = scan_c(t)

    todo = []        # (candidate, twin, size)
    unsolved = []
    for members in groups.values():
        if len(members) < 2:
            continue
        kinds = {n: cfuncs.get(n, {}).get("kind") for _, _, n in members}
        banked = [n for _, _, n in members if kinds[n] == "c"]
        asm = [n for _, _, n in members if kinds[n] == "asm"]
        if banked:
            for n in asm:
                # Prefer a twin in the same file.
                same = [b for b in banked if cfuncs[b]["file"] == cfuncs[n]["file"]]
                todo.append((n, (same or banked)[0], members[0][1]))
        elif len(asm) >= 2:
            unsolved.append((members[0][1], asm))

    for n, twin, size in todo:
        print(f"{n} = {twin} (0x{size:X} bytes, {cfuncs[n]['file'].name})")
    print(f"{len(todo)} function(s) with a banked twin")
    if args.unsolved:
        print(f"\nall-assembly twin groups: {len(unsolved)}")
        for size, names in sorted(unsolved, reverse=True):
            print(f"  0x{size:X} bytes x {len(names)}: {', '.join(names)}")

    if not args.apply or not todo:
        return
    banked, failed = [], []
    for n, twin, _ in todo:
        f = cfuncs[n]["file"]
        old = f.read_text()
        text = re.sub(rf"\b{twin}\b", n, cfuncs[twin]["text"], count=1)
        new = old.replace(cfuncs[n]["line"] + "\n", f"// Same code as {twin}.\n{text}\n", 1)
        if new == old:
            failed.append((n, "INCLUDE_ASM line not found"))
            continue
        f.write_text(new)
        if build_ok(t):
            banked.append((n, twin))
            print(f"banked {n} (same code as {twin})")
        else:
            f.write_text(old)
            failed.append((n, f"build failed with {twin}'s C"))
            print(f"failed {n}: build failed with {twin}'s C")
    if failed:
        build_ok(t)   # leave build/ consistent with the restored files
    print(f"\n{len(banked)} banked, {len(failed)} failed")
    if banked:
        print(f"Next: ./tools/rebuild.sh {t}")


if __name__ == "__main__":
    main()
