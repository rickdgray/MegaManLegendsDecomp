#!/usr/bin/env python3
"""Where each target's Capcom code is: its yaml's code subsegments and its ELF's functions.

Shared by function_list.py and func_metrics.py. Build the target first.
"""

import subprocess
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
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

