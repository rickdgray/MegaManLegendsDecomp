#!/usr/bin/env python3
"""Record that a person has reviewed a function's C, and notice when it changes afterwards.

Usage:
    tools/review.py <target> NAME [NAME ...]    mark functions reviewed (or re-approve changed ones)
    tools/review.py <target> --remove NAME ...  drop reviews
    tools/review.py <target> --changed          list reviewed functions whose C changed since
    tools/review.py <target> --list             list every review

The owner's tool: agents never mark reviews (CLAUDE.md, .claude/settings.json).

reviewed.txt (repo root, tracked) holds one line per review:
    <target> <address> <fingerprint> <date> <name at review time>
Keyed by address, so a review survives renames. The fingerprint is a hash of the function's C
text with whitespace collapsed (re-alignment by clang-format doesn't count as a change; any edit to
code or comments does). functions.csv's Reviewed column shows Yes while the text is unchanged,
Changed once it differs, and blank otherwise. Only banked functions (C outside NON_MATCHING) can
be reviewed.
"""

import datetime
import hashlib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
REVIEWED = ROOT / "reviewed.txt"
HEADER = "# target  address  fingerprint  date  name-at-review   (tools/review.py; the owner's reviews)\n"

NM_BLOCK = re.compile(r"^#ifdef NON_MATCHING\b.*?^#endif[^\n]*\n", re.S | re.M)
DEF_START = re.compile(r"^[A-Za-z_][^;{}#/\n]*?\b\w+\s*\(")
DEF_HEAD = re.compile(r"^[A-Za-z_][^;{}#/\n]*?\b(\w+)\s*\([^;{}]*\)\s*$")


def registry(target):
    """({name: address}, {address: name}) from symbol_addrs_<target>.txt."""
    by_name, by_addr = {}, {}
    for line in (ROOT / f"symbol_addrs_{target}.txt").read_text().splitlines():
        m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            by_name[m.group(1)] = int(m.group(2), 16)
            by_addr[int(m.group(2), 16)] = m.group(1)
    return by_name, by_addr


def address(target, name, by_name):
    m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", name)
    return int(m.group(1), 16) if m else by_name.get(name)


def banked_functions(target):
    """{name: C text} for every function with banked C (definitions outside NON_MATCHING)."""
    out = {}
    for c in sorted((ROOT / "src" / target).glob("*.c")):
        lines = NM_BLOCK.sub("", c.read_text()).splitlines()
        i = 0
        while i < len(lines) - 1:
            # A definition's head may wrap over several lines (long parameter lists).
            head, j = lines[i], i
            if DEF_START.match(head):
                while head.count("(") > head.count(")") and j + 1 < len(lines) and j - i < 6:
                    j += 1
                    head += " " + lines[j].strip()
            m = DEF_HEAD.match(head)
            if m and j + 1 < len(lines) and lines[j + 1].strip() == "{":
                end = j + 1
                while end < len(lines) and lines[end] != "}":
                    end += 1
                out[m.group(1)] = "\n".join(lines[i:end + 1])
                i = end
            i += 1
    return out


def fingerprint(text):
    return hashlib.sha1(re.sub(r"\s+", " ", text).strip().encode()).hexdigest()[:12]


def load():
    """[(target, address, fingerprint, date, name)] from reviewed.txt."""
    entries = []
    if REVIEWED.exists():
        for line in REVIEWED.read_text().splitlines():
            parts = line.split()
            if len(parts) >= 5 and not line.startswith("#"):
                entries.append((parts[0], int(parts[1], 16), parts[2], parts[3], parts[4]))
    return entries


def save(entries):
    entries = sorted(entries, key=lambda e: (e[0], e[1]))
    REVIEWED.write_text(HEADER + "".join(f"{t} 0x{a:08X} {fp} {d} {n}\n" for t, a, fp, d, n in entries))


def status(target):
    """{address: 'Yes' | 'Changed'} for the target's reviewed functions (Changed also when the C
    is gone, e.g. the function was un-banked)."""
    _, by_addr = registry(target)
    funcs = banked_functions(target)
    result = {}
    for t, addr, fp, _, _ in load():
        if t != target:
            continue
        name = by_addr.get(addr, f"func_{addr:08X}")
        text = funcs.get(name)
        result[addr] = "Yes" if text is not None and fingerprint(text) == fp else "Changed"
    return result


def main():
    args = sys.argv[1:]
    if len(args) < 2:
        sys.exit(__doc__)
    target, rest = args[0], args[1:]
    if not (ROOT / f"symbol_addrs_{target}.txt").exists():
        sys.exit(f"unknown target {target!r}")
    by_name, by_addr = registry(target)
    entries = load()

    if rest[0] in ("--list", "--changed"):
        st = status(target)
        for t, addr, fp, d, n in entries:
            if t == target and (rest[0] == "--list" or st[addr] == "Changed"):
                now = by_addr.get(addr, f"func_{addr:08X}")
                renamed = f" (now {now})" if now != n else ""
                print(f"{st[addr]:8} 0x{addr:08X} {n}{renamed}  reviewed {d}")
        return

    if rest[0] == "--remove":
        drop = {address(target, n, by_name) for n in rest[1:]}
        kept = [e for e in entries if not (e[0] == target and e[1] in drop)]
        save(kept)
        print(f"removed {len(entries) - len(kept)} review(s)")
        return

    funcs = banked_functions(target)
    today = datetime.date.today().isoformat()
    marked = 0
    for name in rest:
        addr = address(target, name, by_name)
        if addr is None:
            print(f"{name}: not in the registry and not a func_ name; skipped")
            continue
        current = by_addr.get(addr, f"func_{addr:08X}")
        text = funcs.get(current)
        if text is None:
            print(f"{name}: no banked C (still assembly, or parked); skipped")
            continue
        entries = [e for e in entries if not (e[0] == target and e[1] == addr)]
        entries.append((target, addr, fingerprint(text), today, current))
        marked += 1
    save(entries)
    print(f"marked {marked} function(s) reviewed")


if __name__ == "__main__":
    main()
