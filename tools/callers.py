#!/usr/bin/env python3
"""Who calls or references a function: which files, and so whether its name is global or static.

Usage:  .venv/bin/python tools/callers.py [target] NAME [NAME ...]

NAME is a registered name or a splat default (func_XXXXXXXX). Looks in:
  - the target's C files (for an overlay, also the shared stage code it links) and
    asm/<target>/nonmatchings/<file>/ (other files' code),
  - asm/<target>/data/ (data tables: function pointers),
  - for rock_neo.exe, the overlays: their C and assembly (which name ROCK_NEO's symbols, as they
    link against its registry), and every code chunk in disc/overlays/ (`jal` to the address, or
    the address as a data word), which also covers the duplicate archives that have no target.
Prints the defining file, the outside users, and the style CLAUDE.md's "Names" asks for:
global (Capitalized_snake_case) when anything outside the defining file uses it, else static
(lower_snake_case). Raw word matches in disc/overlays/ can be a coincidence; source hits can't.
"""

import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import targets  # noqa: E402  (tools/targets.py)

ROOT = targets.ROOT
OVERLAYS = ROOT / "disc" / "overlays"


def address(target, name):
    m = re.fullmatch(r"(?:func|D|jtbl)_([0-9A-Fa-f]{8})", name)
    if m:
        return int(m.group(1), 16)
    for line in targets.registry(target).read_text().splitlines():
        m = re.match(rf"\s*{re.escape(name)}\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            return int(m.group(1), 16)
    return None


def home_file(target, name):
    """The file that defines `name`: its C definition, else its splat asm folder."""
    for c in targets.sources(target):
        if re.search(rf"^\w[^;\n]*\b{re.escape(name)}\s*\([^;]*$", c.read_text(), re.M):
            return c.stem
    hits = list((ROOT / "asm" / target / "nonmatchings").glob(f"**/{name}.s"))
    return hits[0].parent.name if hits else None


def overlay_source_users(name, addr):
    """Overlays whose C or assembly names `name` (ROCK_NEO's symbol). An overlay whose own range
    holds the address is skipped: there a default name is its own symbol."""
    word = re.compile(rf"\b{re.escape(name)}\b")
    users = set()
    for ov in targets.OVERLAYS:
        lo, hi = targets.image(ov)
        if addr is not None and lo <= addr < hi:
            continue
        code = (re.sub(r"//[^\n]*|/\*.*?\*/", "", c.read_text(), flags=re.S) for c in targets.sources(ov))
        if any(word.search(t) for t in code) or \
                any(word.search(s.read_text()) for s in (ROOT / "asm" / ov).rglob("*.s")):
            users.add(ov)
    return users


def overlay_users(addr):
    """Overlays that `jal` to addr or hold it as a data word."""
    if addr is None or not OVERLAYS.is_dir():
        return set()
    jal = 0x0C000000 | ((addr & 0x0FFFFFFF) >> 2)
    users = set()
    for p in sorted(OVERLAYS.glob("*")):
        data = p.read_bytes()
        words = struct.unpack_from(f"<{len(data) // 4}I", data)
        if jal in words or addr in words:
            users.add(p.stem)
    return users


def outside_users(target, name, home=None):
    """{file or overlay: kind} for everything outside `home` that names or calls `name`."""
    home = home or home_file(target, name)
    word = re.compile(rf"\b{re.escape(name)}\b")
    users = {}
    for c in targets.sources(target):
        # Comments don't count (e.g. "// Same code as X.").
        code = re.sub(r"//[^\n]*|/\*.*?\*/", "", c.read_text(), flags=re.S)
        if c.stem != home and word.search(code):
            users[c.stem] = "C"
    for s in (ROOT / "asm" / target).rglob("*.s"):
        owner = s.parent.name if "nonmatchings" in s.parts else "data table"
        if owner != home and owner not in users and word.search(s.read_text()):
            users[owner] = "asm"
    if target == targets.HOST:
        addr = address(target, name)
        for ov in overlay_source_users(name, addr):
            users[ov] = "overlay"
        for stem in overlay_users(addr):
            users.setdefault(targets.ARCHIVE_TARGET.get(stem, stem), "overlay binary")
    return users


def main():
    targets.default_target()
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    target = sys.argv[1]
    if target == targets.HOST and not OVERLAYS.is_dir():
        print("warning: disc/overlays/ missing (tools/extract_overlays.py): only the overlays' "
              "sources were checked, not the duplicate archives")
    for name in sys.argv[2:]:
        home = home_file(target, name)
        users = outside_users(target, name, home)
        style = "global (Capitalized_snake_case)" if users else "static (lower_snake_case)"
        listed = ", ".join(f"{u} ({k})" for u, k in sorted(users.items(), key=lambda x: (x[1], x[0])))
        print(f"{name}: defined in {home or '?'}; outside users: {listed or 'none'}\n    -> {style}")


if __name__ == "__main__":
    main()
