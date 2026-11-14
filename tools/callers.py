#!/usr/bin/env python3
"""Who calls or references a function: which files, and so whether its name is global or static.

Usage:  .venv/bin/python tools/callers.py <target> NAME [NAME ...]

NAME is a registered name or a splat default (func_XXXXXXXX). Looks in:
  - src/<target>/*.c and asm/<target>/nonmatchings/<file>/ (other files' code),
  - asm/<target>/data/ (data tables: function pointers),
  - for rock_neo.exe, every code overlay in disc/overlays/ (`jal` to the address, or the address
    as a data word): overlays call into ROCK_NEO, and nothing else shows those calls.
Prints the defining file, the outside users, and the style CLAUDE.md's "Names" asks for:
global (Capitalized_snake_case) when anything outside the defining file uses it, else static
(lower_snake_case). Overlay hits are raw word matches, so one stray hit can be a coincidence.
"""

import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OVERLAYS = ROOT / "disc" / "overlays"


def address(target, name):
    m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", name)
    if m:
        return int(m.group(1), 16)
    for line in (ROOT / f"symbol_addrs_{target}.txt").read_text().splitlines():
        m = re.match(rf"\s*{re.escape(name)}\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            return int(m.group(1), 16)
    return None


def home_file(target, name):
    """The file that defines `name`: its C definition, else its splat asm folder."""
    for c in (ROOT / "src" / target).glob("*.c"):
        if re.search(rf"^\w[^;\n]*\b{re.escape(name)}\s*\([^;]*$", c.read_text(), re.M):
            return c.stem
    hits = list((ROOT / "asm" / target / "nonmatchings").glob(f"*/{name}.s"))
    return hits[0].parent.name if hits else None


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
    for c in (ROOT / "src" / target).glob("*.c"):
        if c.stem != home and word.search(c.read_text()):
            users[c.stem] = "C"
    for s in (ROOT / "asm" / target).rglob("*.s"):
        owner = s.parent.name if "nonmatchings" in s.parts else "data table"
        if owner != home and owner not in users and word.search(s.read_text()):
            users[owner] = "asm"
    if target == "rock_neo.exe":
        for ov in overlay_users(address(target, name)):
            users[ov] = "overlay"
    return users


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    target = sys.argv[1]
    if target == "rock_neo.exe" and not OVERLAYS.is_dir():
        print("warning: disc/overlays/ missing (tools/extract_overlays.py): overlay callers not checked")
    for name in sys.argv[2:]:
        home = home_file(target, name)
        users = outside_users(target, name, home)
        style = "global (Capitalized_snake_case)" if users else "static (lower_snake_case)"
        listed = ", ".join(f"{u} ({k})" for u, k in sorted(users.items(), key=lambda x: (x[1], x[0])))
        print(f"{name}: defined in {home or '?'}; outside users: {listed or 'none'}\n    -> {style}")


if __name__ == "__main__":
    main()
