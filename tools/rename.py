#!/usr/bin/env python3
"""Rename symbols in one target: updates config/<target>/symbol_addrs.txt, the C and headers that
can name the target's symbols, and notes/, in one step.

Usage:
    tools/rename.py [target] OLD NEW [attr ...]   one rename, e.g.  slus_006.03 func_80011940 Movie_start
    tools/rename.py [target] -f renames.txt       a batch (one "OLD NEW [attr ...]" per line, # comments)
    add -n / --dry-run to only show what would change

target: slus_006.03, rock_neo.exe, or an overlay (r3_st05, r3_shl0d, r3_sup, ...; its folder in config/).

attr: splat attributes for the registry line, e.g. size:0x24 or type:func.

The address comes from the registry line when OLD is already registered, otherwise from a splat
default name (func_XXXXXXXX, D_XXXXXXXX, jtbl_XXXXXXXX). New lines get type:func for func_
names, and absolute:True for addresses outside the target's image (targets.image): scratchpad,
hardware registers, and RAM no section of the program covers (e.g. ROCK_NEO's 0x801F8300).

What gets rewritten (whole words only):
  - slus_006.03: src/slus_006.03/, the shared and executable headers in include/, notes/.
  - rock_neo.exe: the same for ROCK_NEO, plus the overlay sources and headers (src/r3_*/,
    src/stage_common/, include/r3_*/, include/stage_common/, include/shl/), which link against
    ROCK_NEO's registry. An overlay whose own address range holds the symbol's address is skipped
    (its splat default names can repeat ROCK_NEO's).
  - an overlay: src/<t>/, include/<t>/ and notes/. A name from the shared stage code (registered
    under the same name in every overlay that links it) is renamed in every one of those registries
    and in src/stage_common/, include/stage_common/ and include/shl/. A splat default name stays
    within the overlay, and notes/ is only listed, not changed: every stage overlay loads at
    0x80100000, so the same default name means a different function in another overlay.

The new name must not already exist in the target's registry, in ROCK_NEO's (overlays link
against it), or, for a ROCK_NEO rename, in any overlay's.

Afterwards run the ./tools/rebuild.sh line printed at the end: every target whose files or
registry changed (split, build, refresh expected/).
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import targets  # noqa: E402  (tools/targets.py)

ROOT = targets.ROOT

LINE = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")
DEFAULT = re.compile(r"^(func|D|jtbl)_([0-9A-Fa-f]{8})$")
IDENT = re.compile(r"^[A-Za-z_]\w*$")
OVERLAY_DIRS = ["src/r3_*", targets.SHARED_SRC, "include/r3_*", "include/stage_common", "include/shl"]


class Entry:
    def __init__(self, name, addr, attrs, note=""):
        self.name, self.addr, self.attrs = name, addr, attrs  # attrs: dict key -> value
        self.note = note    # free text after the attributes (ST02_ANIM[14]), kept as written

    def render(self):
        line = f"{self.name} = 0x{self.addr:08X};"
        comment = " ".join([f"{k}:{v}" for k, v in self.attrs.items()] + ([self.note] if self.note else []))
        if comment:
            line += " // " + comment
        return line


def split_comment(text):
    """A registry line's comment: (splat attributes, any other text, kept as written)."""
    attrs, rest = {}, []
    for tok in text.split():
        if ":" in tok and not rest:
            k, v = tok.split(":", 1)
            attrs[k] = v
        else:
            rest.append(tok)
    return attrs, " ".join(rest)


def parse_attrs(tokens):
    attrs = {}
    for tok in tokens:
        if ":" not in tok:
            sys.exit(f"bad attribute {tok!r} (expected key:value)")
        k, v = tok.split(":", 1)
        attrs[k] = v
    return attrs


class Registry:
    def __init__(self, target):
        self.target = target
        self.path = targets.registry(target)
        self.lines = self.path.read_text().splitlines()
        self.original = list(self.lines)
        self.entries = {}  # line index -> Entry
        for i, line in enumerate(self.lines):
            m = LINE.match(line)
            if m:
                attrs, note = split_comment(m.group(3) or "")
                self.entries[i] = Entry(m.group(1), int(m.group(2), 16), attrs, note)

    def label(self):
        return str(self.path.relative_to(ROOT))

    def find(self, name):
        for i, e in self.entries.items():
            if e.name == name:
                return i
        return None

    def address_of(self, name):
        i = self.find(name)
        return self.entries[i].addr if i is not None else None

    def changed(self):
        return self.lines != self.original

    def rename(self, old, new, extra, insert_default=True):
        """Update or insert the registry line. Returns a description of the change."""
        if new != old and self.find(new) is not None:
            sys.exit(f"{new}: already in {self.label()} (line {self.find(new) + 1})")

        i = self.find(old)
        if i is not None:
            e = self.entries[i]
            e.name = new
            e.attrs.update(extra)
            self.lines[i] = e.render()
            return f"{self.label()} line {i + 1}: renamed"

        m = DEFAULT.match(old)
        if not m or not insert_default:
            sys.exit(f"{old}: not in {self.label()} and not a splat default name; add its line by hand")
        addr = int(m.group(2), 16)

        for i, e in self.entries.items():
            if e.addr == addr:
                sys.exit(f"{old}: address 0x{addr:08X} is already registered as {e.name} "
                         f"({self.label()} line {i + 1})")

        attrs = {}
        if m.group(1) == "func":
            attrs["type"] = "func"
        lo, hi = targets.image(self.target)
        if addr < 0x80000000 or not (lo <= addr < hi):
            attrs["absolute"] = "True"
        attrs.update(extra)
        e = Entry(new, addr, attrs)

        # Insert before the first non-absolute line with a higher address (keeps the file in order).
        pos = len(self.lines)
        for i in sorted(self.entries):
            other = self.entries[i]
            if other.addr >= 0x80000000 and other.addr > addr:
                pos = i
                break
        self.lines.insert(pos, e.render())
        shifted = {}
        for i, ent in self.entries.items():
            shifted[i + 1 if i >= pos else i] = ent
        shifted[pos] = e
        self.entries = shifted
        return f"{self.label()}: added {e.render()}"

    def write(self):
        self.path.write_text("\n".join(self.lines) + "\n")


def files_under(patterns):
    """C files and headers under the given folders (globs allowed in the folder names)."""
    out = set()
    for pat in patterns:
        for d in ROOT.glob(pat):
            if d.is_dir():
                out.update(p for ext in ("c", "h") for p in d.glob(f"**/*.{ext}"))
    return out


def executable_headers():
    """include/ minus the overlay folders: what the two executables can include."""
    overlay = files_under(OVERLAY_DIRS)
    return {p for p in ROOT.glob("include/**/*.h") if p not in overlay}


def owner(path):
    """The overlay whose own folder holds path (src/r3_st05/x.c -> r3_st05), else None."""
    rel = path.relative_to(ROOT).parts
    if len(rel) > 1 and rel[0] in ("src", "include") and targets.is_overlay(rel[1]):
        return rel[1]
    return None


def plan(target, old, registries):
    """(registries to update, text files to rewrite, notes to rewrite, notes to only list,
    targets reached) for renaming `old` in `target`."""
    reg = registries[target]
    default = DEFAULT.match(old)
    addr = reg.address_of(old) if reg.find(old) is not None else (int(default.group(2), 16) if default else None)
    notes = set(ROOT.glob("notes/**/*.md"))
    regs, files, reached = [reg], set(), {target}

    if not targets.is_overlay(target):
        files = files_under([f"src/{target}"]) | executable_headers()
        if target == targets.HOST:
            # Overlays link against ROCK_NEO's names. Skip an overlay that has the same address in
            # its own range: there the name (a splat default) is the overlay's own symbol.
            for p in files_under(OVERLAY_DIRS):
                ov = owner(p)
                if ov and addr is not None and targets.image(ov)[0] <= addr < targets.image(ov)[1]:
                    continue
                files.add(p)
            # Their assembly (data tables, functions still in asm) names ROCK_NEO's symbols too,
            # from the split: those overlays need a fresh split even if none of their C changes.
            word = re.compile(rf"\b{re.escape(old)}\b")
            for ov in targets.OVERLAYS:
                lo, hi = targets.image(ov)
                if addr is not None and lo <= addr < hi:
                    continue
                if any(word.search(s.read_text()) for s in (ROOT / "asm" / ov).rglob("*.s")):
                    reached.add(ov)
        return regs, files, notes, set(), reached

    files = files_under([f"src/{target}", f"include/{target}"])
    if default:
        return regs, files, set(), notes, reached
    # A named symbol of the shared stage code is registered under that name in every overlay
    # that links the code: rename it in all of them, and in the shared folders.
    for t in targets.OVERLAYS:
        if t != target and registries[t].find(old) is not None:
            regs.append(registries[t])
            reached.add(t)
    if len(regs) > 1:
        files |= files_under([targets.SHARED_SRC, "include/stage_common", "include/shl"])
        for t in reached:
            files |= files_under([f"src/{t}", f"include/{t}"])
    return regs, files, notes, set(), reached


def main():
    targets.default_target()
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target", choices=targets.TARGETS, metavar="target")
    ap.add_argument("old", nargs="?")
    ap.add_argument("new", nargs="?")
    ap.add_argument("attrs", nargs="*")
    ap.add_argument("-f", "--file", help="batch file: one 'OLD NEW [attr ...]' per line")
    ap.add_argument("-n", "--dry-run", action="store_true")
    args = ap.parse_intermixed_args()  # flags may sit between OLD and NEW (rename.py -n OLD NEW)

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

    registries = {t: Registry(t) for t in targets.TARGETS if targets.registry(t).exists()}
    texts = {}
    reached = set()

    for old, new, extra in jobs:
        print(f"{old} -> {new}")
        # The name must stay unique where the linker sees it together: an overlay with ROCK_NEO's
        # names, ROCK_NEO with every overlay's.
        clash = [targets.HOST] if targets.is_overlay(args.target) else []
        if args.target == targets.HOST:
            clash = list(targets.OVERLAYS)
        for t in clash:
            if t in registries and registries[t].find(new) is not None:
                sys.exit(f"{new}: already in {registries[t].label()}; overlays and ROCK_NEO share names")

        if (targets.is_overlay(args.target) and registries[args.target].find(old) is None
                and registries[targets.HOST].find(old) is not None):
            sys.exit(f"{old}: a ROCK_NEO.EXE symbol (overlays link against its registry); "
                     f"rename it with: tools/rename.py {targets.HOST} {old} {new}")
        regs, files, notes, listed, hit = plan(args.target, old, registries)
        reached |= hit
        for reg in regs:
            print("   ", reg.rename(old, new, extra, insert_default=(reg is regs[0])))

        pattern = re.compile(rf"\b{re.escape(old)}\b")
        hits = 0
        for p in sorted(files | notes):
            if p not in texts:
                texts[p] = p.read_text()
            texts[p], count = pattern.subn(new, texts[p])
            if count:
                hits += count
                print(f"    {p.relative_to(ROOT)}: {count}")
                if p in files:
                    reached.update(targets.reached_by([p]))
        if hits == 0:
            print("    (no uses in the sources, headers or notes)")
        for p in sorted(listed):
            if pattern.search(p.read_text()):
                print(f"    {p.relative_to(ROOT)}: mentions {old}; not changed (default names repeat "
                      f"across overlays), edit by hand if it means {args.target}'s")

    if args.dry_run:
        print("\nDry run: nothing written.")
        return

    for reg in registries.values():
        if reg.changed():
            reg.write()
    for p, text in texts.items():
        if text != p.read_text():
            p.write_text(text)
    order = [t for t in targets.TARGETS if t in reached]
    print(f"\nDone. Next: ./tools/rebuild.sh {' '.join(order)}")


if __name__ == "__main__":
    main()
