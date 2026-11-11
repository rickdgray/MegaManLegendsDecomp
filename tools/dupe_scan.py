#!/usr/bin/env python3
"""Find duplicate functions across the whole game: both executables and every code overlay.

Usage:  tools/dupe_scan.py [--tsv FILE] [--list N] [--runs]

Needs both executables built (for their function lists) and disc/overlays/ extracted
(tools/extract_overlays.py). Byte-identical overlays (ST03B, ...) are left out; see notes/disc.md.

Functions:
- Executables: FUNC symbols of the Capcom ranges, from build/<t>/<t>.elf (as find_dupes.py).
- Overlays: no symbols, so they are split here. The code starts after the read-only data that
  opens each overlay (pointer tables and the like), at the first word of an unbroken run of
  plausible instructions ending at the first `jr ra`, and never before word 1 (word 0 is the
  overlay's ID). It ends after the last `jr ra`. Functions are cut after each `jr ra` and its
  delay slot, unless a branch earlier in the function still points further on. Calibrated on
  ROCK_NEO: 1147 of its 1151 Capcom function starts found, none invented (the four missed are
  hand-written assembly and the 2MBYTE.OBJ stubs, not compiler output).

Two keys per function, both blind to where the function itself sits:
- exact: every instruction with its immediates. ROCK_NEO's addresses (below 0x800D8800: its code,
  data and BSS) mean the same in every program and are kept. A program's own addresses (an
  overlay's, or anything in the shim) are masked: the `lui` of an address, the immediates used
  through that register, `j` outside the function. A `jal` to the program's own function is
  replaced by that function's key (refined over a few rounds), so two wrappers match only if
  their callees do. Same exact key = same C, same data layout, same calls into ROCK_NEO; the C
  ports as is (own statics may live at other addresses).
- shape: opcodes and registers only (find_dupes.py's tokens). Same shape, different exact key =
  the same code with different constants, calls or globals; port and adjust. For small
  functions a shared shape is weak evidence (every `g();` wrapper has the same one).

Prints a summary (functions, distinct groups, savings in functions and bytes, unmatched functions
with an exact twin already in C), the largest groups, and with --runs the runs of consecutive
duplicates shared between programs (likely one source file linked into each). --tsv writes one
row per function.
"""

import argparse
import hashlib
import struct
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import find_dupes  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
OVERLAYS = ROOT / "disc/overlays"
# Byte-identical copies of another overlay (notes/disc.md, "Code overlays").
COPIES = {"ST03B", "ST04B", "ST0CB", "ST0CC", "ST10B", "ST11B", "SUPPORT2"}
JR_RA = 0x03E00008
SPECIAL_OK = {0, 2, 3, 4, 6, 7, 8, 9, 12, 13, 16, 17, 18, 19, 24, 25, 26, 27,
              32, 33, 34, 35, 36, 37, 38, 39, 42, 43}
OP_OK = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18,
         32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46, 50, 58}


def overlay_base(name):
    if name.startswith("SUPPORT"):
        return 0x801D8000
    if name.startswith("ARM"):
        return 0x800D8800
    return 0x80100000


def is_dataword(w):
    """A pointer into RAM (0x80000000-0x81FFFFFF) decodes as a load based on $zero: never code."""
    return (w >> 24) in (0x80, 0x81) and ((w >> 21) & 31) == 0


def plausible(w):
    """Could GCC 2.7 have emitted this word as an instruction?"""
    if w == 0:
        return True
    op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
    rd, sa, fn = (w >> 11) & 31, (w >> 6) & 31, w & 63
    if op == 0:
        if fn not in SPECIAL_OK:
            return False
        if fn in (8, 9):                    # jr, jalr
            return rt == 0 and sa == 0 and (fn == 9 or rd == 0)
        if fn in (24, 25, 26, 27):          # mult, multu, div, divu
            return rd == 0 and sa == 0
        if fn in (16, 18):                  # mfhi, mflo
            return rs == 0 and rt == 0 and sa == 0 and rd != 0
        if fn in (17, 19):                  # mthi, mtlo
            return rt == 0 and rd == 0 and sa == 0
        if fn in (12, 13):                  # syscall, break
            return True
        if fn in (0, 2, 3):                 # sll, srl, sra
            return rs == 0 and rd != 0 and rt != 0
        return sa == 0 and rd != 0
    if op not in OP_OK:
        return False
    if op == 1:
        return rt in (0, 1, 16, 17)
    if op in (8, 9, 10, 11, 12, 13, 14, 32, 33, 34, 35, 36, 37, 38):
        return rt != 0 and not is_dataword(w)
    if op == 15:
        return rs == 0 and rt != 0
    return True


def branch_target(w, pc):
    op = w >> 26
    if op in (4, 5, 6, 7) or (op == 1 and ((w >> 16) & 31) in (0, 1, 16, 17)):
        return pc + 4 + find_dupes.simm16(w) * 4
    if op == 2:
        return (pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
    return None


def text_region(ws):
    """(first, end) word indices of the code in an overlay."""
    jrs = [i for i, w in enumerate(ws) if w == JR_RA]
    first, end = jrs[0], jrs[-1] + 2
    i = first
    while i > 1 and not is_dataword(ws[i - 1]) and plausible(ws[i - 1]):
        i -= 1
    while ws[i] == 0:
        i += 1
    return i, end


def split(ws, base, start, end, call_targets):
    """[(first, end)] word indices of functions in ws[start:end]."""
    funcs, i = [], start
    while i < end:
        while i < end and ws[i] == 0:
            i += 1
        if i >= end:
            break
        f = reach = j = i
        while j < end:
            w = ws[j]
            t = branch_target(w, base + j * 4)
            if t is not None and not (w >> 26 == 2 and t in call_targets):
                ti = (t - base) // 4
                if f <= ti < end:
                    reach = max(reach, ti)
            if w == JR_RA and j + 1 >= reach:
                j += 2
                break
            j += 1
        funcs.append((f, j))
        i = j
    return funcs


SHARED_END = 0x800D8800   # ROCK_NEO's code, data and BSS: the same addresses in every program
ROCK_NEO_GP = 0x80097864


def keys(ws, base, f, e, local, callee_keys):
    """(strict key, shape key) for the function ws[f:e].

    local(addr) says whether an address belongs to this program alone (then it is masked; a call
    to one of its functions is replaced by that function's key from callee_keys) or is shared
    with ROCK_NEO (then it is kept).
    """
    hi = {}                                 # register -> upper half from a lui
    toks = []
    lo, end = base + f * 4, base + e * 4
    for k in range(f, e):
        w = ws[k]
        op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        if op == 3:
            t = 0x80000000 | ((w & 0x3FFFFFF) << 2)
            toks.append(("jal", callee_keys.get(t, "?")) if local(t) else ("jal", t))
        elif op == 2:
            t = (lo & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            toks.append(("j", t - lo) if lo <= t < end else ("j", "out"))
        elif op == 15:
            imm = w & 0xFFFF
            if 0x8000 <= imm <= 0x8020:
                hi[rt] = imm
                toks.append(("lui", rt))
            else:
                hi.pop(rt, None)
                toks.append(w)
        elif op not in (0, 1, 4, 5, 6, 7) and (rs in hi or rs == 28):
            a = ((hi[rs] << 16) if rs != 28 else ROCK_NEO_GP) + find_dupes.simm16(w)
            a &= 0xFFFFFFFF
            toks.append((op, rs, rt, "local" if local(a) else a))
            if op < 0x28:                   # loads and addiu/ori write rt; stores don't
                hi.pop(rt, None)
        else:
            toks.append(w)
            if op == 0 and rd:
                hi.pop(rd, None)
            elif 8 <= op < 0x28:
                hi.pop(rt, None)
    data = b"".join(struct.pack("<I", w) for w in ws[f:e])
    shape = find_dupes.tokens(b"\0" * find_dupes.HEADER + data, find_dupes.VRAM_BASE, len(data))
    h = lambda x: hashlib.sha1(repr(x).encode()).hexdigest()[:12]
    return h(toks), h(shape)


ROUNDS = 4   # call-key refinement rounds: a call chain this deep inside one program is resolved


def in_assembly(target):
    """Names of functions still in assembly (INCLUDE_ASM, parked, or in an asm file): splat's macro
    gives each a NAME.NON_MATCHING symbol in the linked ELF (as progress.py counts)."""
    elf = ROOT / "build" / target / f"{target}.elf"
    out = subprocess.run(["mips-linux-gnu-readelf", "-sW", str(elf)], capture_output=True,
                         text=True, check=True).stdout
    return {f[7].removesuffix(".NON_MATCHING") for f in (l.split() for l in out.splitlines())
            if len(f) >= 8 and f[7].endswith(".NON_MATCHING")}


def programs():
    """[(prog, words, base, [(first, end, name, matched)], local)] for every program."""
    progs = []
    for target, prog in (("slus_006.03", "SLUS"), ("rock_neo.exe", "ROCK_NEO")):
        data = (ROOT / find_dupes.TARGETS[target]["disc"]).read_bytes()
        n = (len(data) - find_dupes.HEADER) // 4
        ws = struct.unpack_from(f"<{n}I", data, find_dupes.HEADER)
        asm = in_assembly(target)
        funcs = []
        for addr, size, name in find_dupes.functions(target):
            f = (addr - find_dupes.VRAM_BASE) // 4
            funcs.append((f, f + size // 4, name, name not in asm))
        # The shim's addresses mean nothing elsewhere; ROCK_NEO's are the shared ones.
        local = (lambda a: True) if prog == "SLUS" else (lambda a: a >= SHARED_END)
        progs.append((prog, ws, find_dupes.VRAM_BASE, funcs, local))
    if not OVERLAYS.is_dir():
        sys.exit("disc/overlays/ not found: run tools/extract_overlays.py first")
    for path in sorted(OVERLAYS.glob("*.BIN")):
        prog = path.stem
        if prog in COPIES:
            continue
        data = path.read_bytes()
        ws = struct.unpack_from(f"<{len(data) // 4}I", data)
        base = overlay_base(prog)
        calls = {0x80000000 | ((w & 0x3FFFFFF) << 2) for w in ws if w >> 26 == 3}
        start, end = text_region(ws)
        funcs = [(f, e, f"func_{base + f * 4:08X}", False)
                 for f, e in split(ws, base, start, end, calls)]
        progs.append((prog, ws, base, funcs, lambda a: a >= SHARED_END))
    return progs


def collect():
    """[dict] one per function: program, address, size, name, keys, matched."""
    rows = []
    for prog, ws, base, funcs, local in programs():
        callee = {}
        for _ in range(ROUNDS):
            new = {}
            for f, e, name, matched in funcs:
                new[base + f * 4] = keys(ws, base, f, e, local, callee)
            callee = {a: k[0] for a, k in new.items()}
        for f, e, name, matched in funcs:
            strict, shape = new[base + f * 4]
            rows.append(dict(prog=prog, addr=base + f * 4, size=(e - f) * 4, name=name,
                             exact=strict, shape=shape, matched=matched))
    return rows


def shared_runs(rows, limit, min_len=4):
    """Print runs of >= min_len consecutive functions whose neighbours are also neighbours
    elsewhere (same exact keys, same order), and each program's share of code inside them."""
    seq = defaultdict(list)
    for r in rows:
        seq[r["prog"]].append(r)
    pair_progs = defaultdict(set)
    for prog, s in seq.items():
        for a, b in zip(s, s[1:]):
            pair_progs[(a["exact"], b["exact"])].add(prog)
    linked = lambda s, i: len(pair_progs[(s[i]["exact"], s[i + 1]["exact"])]) > 1
    runs = defaultdict(list)                # exact keys of the run -> [(prog, first, last)]
    for prog, s in seq.items():
        i = 0
        while i < len(s) - 1:
            if not linked(s, i):
                i += 1
                continue
            j = i
            while j < len(s) - 1 and linked(s, j):
                j += 1
            if j - i + 1 >= min_len:
                runs[tuple(x["exact"] for x in s[i : j + 1])].append((prog, s[i], s[j]))
            i = j + 1
    print(f"\nruns of {min_len}+ functions shared between programs: {len(runs)} distinct")
    size = lambda first, last, prog: sum(x["size"] for x in seq[prog]
                                         if first["addr"] <= x["addr"] <= last["addr"])
    ranked = sorted(runs.items(), key=lambda kv: -len(kv[1]) * size(kv[1][0][1], kv[1][0][2], kv[1][0][0]))
    for keys_, occ in ranked[:limit]:
        prog, first, last = occ[0]
        progs = sorted({o[0] for o in occ})
        print(f"  {len(keys_):3} functions, {size(first, last, prog):#7x} bytes, {len(occ):2} places; "
              f"{prog} {first['addr']:08X}-{last['addr']:08X}; in {' '.join(progs[:12])}"
              f"{' ...' if len(progs) > 12 else ''}")
    covered = Counter()
    for occ in runs.values():
        for prog, first, last in occ:
            covered[prog] += size(first, last, prog)
    print("share of each program's code inside shared runs:")
    shares = [f"{p} {covered[p] / sum(x['size'] for x in seq[p]):.0%}" for p in seq if covered[p]]
    for i in range(0, len(shares), 10):
        print("  " + "  ".join(shares[i : i + 10]))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--tsv", help="write one row per function to this file")
    ap.add_argument("--list", type=int, default=15, help="how many groups and runs to list")
    ap.add_argument("--runs", action="store_true", help="list runs of duplicates shared between programs")
    args = ap.parse_args()

    rows = collect()
    by_exact, by_shape = defaultdict(list), defaultdict(list)
    for r in rows:
        by_exact[r["exact"]].append(r)
        by_shape[r["shape"]].append(r)
    # Name groups after their first member, executables first (rows are in that order).
    for groups, field in ((by_exact, "exact_group"), (by_shape, "shape_group")):
        for members in groups.values():
            first = members[0]
            for r in members:
                r[field] = f"{first['prog']}:{first['addr']:08X}"
                r[field + "_n"] = len(members)

    total = len(rows)
    empty = sum(1 for r in rows if r["size"] <= 8)
    print(f"{total} functions ({sum(r['prog'] not in ('SLUS', 'ROCK_NEO') for r in rows)} in "
          f"overlays), {empty} of them empty (`jr ra; nop`)")
    print(f"distinct exact: {len(by_exact)}   distinct shape: {len(by_shape)}")

    # Remaining work, empty functions left out: one member per group, none of it matched yet.
    todo = [r for r in rows if not r["matched"] and r["size"] > 8]
    todo_bytes = sum(r["size"] for r in todo)
    print(f"\nunmatched, not empty: {len(todo)} functions, {todo_bytes:#x} bytes")
    for groups, field, label in ((by_exact, "exact", "exact"), (by_shape, "shape", "shape")):
        reps = {}
        for r in todo:
            if not any(x["matched"] for x in groups[r[field]]):
                reps.setdefault(r[field], r)
        n = sum(x["size"] for x in reps.values())
        print(f"  one per {label} group: {len(reps):5} functions, {n:#x} bytes "
              f"({n / todo_bytes:.0%} of the bytes)")
    free = [r for r in todo if any(x["matched"] for x in by_exact[r["exact"]])]
    print(f"unmatched, not empty, with an exact twin already in C: {len(free)}")
    for r in free[: args.list]:
        twin = next(x for x in by_exact[r["exact"]] if x["matched"])
        print(f"    {r['prog']}:{r['name']} = {twin['prog']}:{twin['name']} ({r['size']:#x} bytes)")

    multi = [m for m in by_exact.values() if len(m) > 1 and m[0]["size"] > 8]
    print(f"\nexact groups with 2+ members (not empty): {len(multi)}, covering "
          f"{sum(len(m) for m in multi)} functions")
    by_bytes = sorted(multi, key=lambda m: -(len(m) - 1) * m[0]["size"])
    print(f"largest savings (members x size), top {args.list}:")
    for m in by_bytes[: args.list]:
        names = sorted({r["prog"] for r in m})
        print(f"  {m[0]['size']:#7x} bytes x {len(m):3}  {m[0]['prog']}:{m[0]['name']}  in "
              f"{len(names)} programs: {', '.join(names[:8])}{' ...' if len(names) > 8 else ''}")

    if args.runs:
        shared_runs(rows, args.list)

    if args.tsv:
        cols = ["prog", "addr", "size", "name", "matched", "exact_group", "exact_group_n",
                "shape_group", "shape_group_n"]
        with open(args.tsv, "w") as fh:
            fh.write("\t".join(cols) + "\n")
            for r in rows:
                vals = dict(r, addr=f"{r['addr']:08X}", size=f"{r['size']:#x}",
                            matched="yes" if r["matched"] else "")
                fh.write("\t".join(str(vals[c]) for c in cols) + "\n")
        print(f"\nwrote {args.tsv}")


if __name__ == "__main__":
    main()
