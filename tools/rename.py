#!/usr/bin/env python3
"""Rename symbols in one target: updates symbol_addrs_<target>.txt, src/<target>/, include/ and
notes/ in one step.

Usage:
    tools/rename.py <target> OLD NEW [attr ...]   one rename, e.g.  slus_006.03 func_80011940 Movie_start
    tools/rename.py <target> -f renames.txt       a batch (one "OLD NEW [attr ...]" per line, # comments)
    add -n / --dry-run to only show what would change

target: slus_006.03 or rock_neo.exe.

attr: splat attributes for the registry line, e.g. size:0x24 or type:func.

The address comes from the registry line when OLD is already registered, otherwise from a splat
default name (func_XXXXXXXX, D_XXXXXXXX, jtbl_XXXXXXXX). New lines get type:func for func_
names, and absolute:True for addresses outside the target's image (see IMAGE below): scratchpad,
hardware registers, and RAM no section of the executable covers (e.g. ROCK_NEO's 0x801F8300).

Afterwards run ./tools/rebuild.sh <target> (split, build, refresh expected/).
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TARGETS = ["slus_006.03", "rock_neo.exe"]
REGISTRY = None  # symbol_addrs_<target>.txt, set in main()

LINE = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")
DEFAULT = re.compile(r"^(func|D|jtbl)_([0-9A-Fa-f]{8})$")
IDENT = re.compile(r"^[A-Za-z_]\w*$")

# Where each executable's image (code, data and BSS) lives; anything outside is absolute.
IMAGE = {
    "slus_006.03": (0x80010000, 0x8005DA40),
    "rock_neo.exe": (0x80010000, 0x800D9000),
}


class Entry:
    def __init__(self, name, addr, attrs):
        self.name, self.addr, self.attrs = name, addr, attrs  # attrs: dict key -> value

    def render(self):
        line = f"{self.name} = 0x{self.addr:08X};"
        if self.attrs:
            line += " // " + " ".join(f"{k}:{v}" for k, v in self.attrs.items())
        return line


def parse_attrs(tokens):
    attrs = {}
    for tok in tokens:
        if ":" not in tok:
            sys.exit(f"bad attribute {tok!r} (expected key:value)")
        k, v = tok.split(":", 1)
        attrs[k] = v
    return attrs


def load_registry():
    lines = REGISTRY.read_text().splitlines()
    entries = {}  # line index -> Entry
    for i, line in enumerate(lines):
        m = LINE.match(line)
        if m:
            entries[i] = Entry(m.group(1), int(m.group(2), 16), parse_attrs((m.group(3) or "").split()))
    return lines, entries


def rename_registry(lines, entries, old, new, extra, target="rock_neo.exe"):
    """Update or insert the registry line. Returns a description of the change."""
    by_name = {e.name: i for i, e in entries.items()}
    if new in by_name and new != old:
        sys.exit(f"{new}: already in {REGISTRY.name} (line {by_name[new] + 1})")

    if old in by_name:
        i = by_name[old]
        e = entries[i]
        e.name = new
        e.attrs.update(extra)
        lines[i] = e.render()
        return f"registry line {i + 1}: renamed"

    m = DEFAULT.match(old)
    if not m:
        sys.exit(f"{old}: not in {REGISTRY.name} and not a splat default name; add its line by hand")
    addr = int(m.group(2), 16)

    for i, e in entries.items():
        if e.addr == addr:
            sys.exit(f"{old}: address 0x{addr:08X} is already registered as {e.name} (line {i + 1})")

    attrs = {}
    if m.group(1) == "func":
        attrs["type"] = "func"
    lo, hi = IMAGE[target]
    if addr < 0x80000000 or not (lo <= addr < hi):
        attrs["absolute"] = "True"
    attrs.update(extra)
    e = Entry(new, addr, attrs)

    # Insert before the first non-absolute line with a higher address (keeps the file in order).
    pos = len(lines)
    for i in sorted(entries):
        other = entries[i]
        if other.addr >= 0x80000000 and other.addr > addr:
            pos = i
            break
    lines.insert(pos, e.render())
    # Shift indices of entries after the insertion point.
    shifted = {}
    for i, ent in entries.items():
        shifted[i + 1 if i >= pos else i] = ent
    shifted[pos] = e
    entries.clear()
    entries.update(shifted)
    return f"registry: added {e.render()}"


def main():
    global REGISTRY
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target", choices=TARGETS)
    ap.add_argument("old", nargs="?")
    ap.add_argument("new", nargs="?")
    ap.add_argument("attrs", nargs="*")
    ap.add_argument("-f", "--file", help="batch file: one 'OLD NEW [attr ...]' per line")
    ap.add_argument("-n", "--dry-run", action="store_true")
    args = ap.parse_args()

    jobs = []
    if args.file:
        for n, raw in enumerate(Path(args.file).read_text().splitlines(), 1):
            line = raw.split("#", 1)[0].strip()
            if line:
                parts = line.split()
                if len(parts) < 2:
                    sys.exit(f"{args.file}:{n}: expected 'OLD NEW [attr ...]'")
                jobs.append((parts[0], parts[1], parse_attrs(parts[2:])))
    elif args.old and args.new:
        jobs.append((args.old, args.new, parse_attrs(args.attrs)))
    else:
        ap.error("give OLD NEW, or -f FILE")

    for old, new, _ in jobs:
        if not IDENT.match(new):
            sys.exit(f"{new}: not a valid C identifier")

    REGISTRY = ROOT / f"symbol_addrs_{args.target}.txt"
    text_globs = [f"src/{args.target}/**/*.c", f"src/{args.target}/**/*.h", "include/**/*.h", "notes/**/*.md"]
    lines, entries = load_registry()
    files = sorted({p for g in text_globs for p in ROOT.glob(g)})
    texts = {p: p.read_text() for p in files}

    for old, new, extra in jobs:
        print(f"{old} -> {new}")
        print("   ", rename_registry(lines, entries, old, new, extra, target=args.target))
        pattern = re.compile(rf"\b{re.escape(old)}\b")
        hits = 0
        for p in files:
            texts[p], count = pattern.subn(new, texts[p])
            if count:
                hits += count
                print(f"    {p.relative_to(ROOT)}: {count}")
        if hits == 0:
            print("    (no uses in src/, include/ or notes/)")

    if args.dry_run:
        print("\nDry run: nothing written.")
        return

    REGISTRY.write_text("\n".join(lines) + "\n")
    for p in files:
        if texts[p] != p.read_text():
            p.write_text(texts[p])
    print(f"\nDone. Next: ./tools/rebuild.sh {args.target}")


if __name__ == "__main__":
    main()
