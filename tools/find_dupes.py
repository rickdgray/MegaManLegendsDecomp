#!/usr/bin/env python3
"""Find functions in one executable that look like compiled copies of functions in another.

Usage:  tools/find_dupes.py [--min 0.85] [--src slus_006.03] [--dst rock_neo.exe]

Compares Capcom functions of SRC (default: the shim) with Capcom functions of DST (default:
ROCK_NEO.EXE), instruction by instruction. Each instruction is reduced to its opcode, function code
and register fields; immediates and jump targets are ignored, since addresses differ between the two
programs. The similarity score is the share of instructions that line up (difflib), so a -G0 global
access (lui + load) vs a -G8 one ($gp-relative load) costs a little instead of breaking the match.

Function boundaries come from each target's linked ELF (build/<t>/<t>.elf, so build both first);
the bytes come from the original disc files. Shim functions still in INCLUDE_ASM are marked parked.

--imm: for each identical-shape pair, list instructions whose immediates differ, skipping those
with relocations (addresses, which always differ). What's left are struct offsets, sizes, loop
counts and constants: if a pair shows none, its data layouts agree in both programs.

--map FILE: like --names, but lists every correspondence the alignment finds, including symbols
that are unnamed on either side (`D_80059BCA -> D_800988EA`). For porting C between the programs,
and for naming a variable in both at once.

--names FILE: for each identical-shape pair, line the two functions up instruction by instruction
(using relocations from the built objects) and propose SRC's names for DST: the globals SRC
references (field offsets accounted for, so an access to sym+0x10 names sym's base) and the
functions it calls, plus the pair itself. Writes tools/rename.py batch lines to FILE; only DST
symbols that still have default names (func_/D_ or none) are proposed. Conflicts are reported.
"""

import argparse
import difflib
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Per target: disc file, load address, and the ranges of Capcom code to compare.
TARGETS = {
    "slus_006.03": {
        "disc": "disc/extracted/SLUS_006.03",
        "ranges": [(0x800107E8, 0x80012624)],
        "src": "src/slus_006.03",
    },
    "rock_neo.exe": {
        "disc": "disc/extracted/ROCK_NEO.EXE",
        "ranges": [(0x80011C90, 0x80067FF8), (0x800680BC, 0x80069038)],
        "src": "src/rock_neo.exe",
    },
}
VRAM_BASE = 0x80010000
HEADER = 0x800


def functions(target):
    """[(addr, size, name)] for FUNC symbols in the target's Capcom ranges, from the linked ELF."""
    elf = ROOT / "build" / target / f"{target}.elf"
    if not elf.exists():
        sys.exit(f"{elf} not found: build {target} first")
    out = subprocess.run(["mips-linux-gnu-readelf", "-sW", str(elf)], capture_output=True, text=True,
                         check=True).stdout
    syms = {}
    for line in out.splitlines():
        f = line.split()
        if len(f) >= 8 and f[3] == "FUNC":
            addr, size, name = int(f[1], 16), int(f[2], 0), f[7]
            if any(lo <= addr < hi for lo, hi in TARGETS[target]["ranges"]):
                syms[addr] = (size, name)
    # Fill in missing sizes from the next function's address.
    addrs = sorted(syms)
    result = []
    for i, a in enumerate(addrs):
        size, name = syms[a]
        if size == 0 and i + 1 < len(addrs):
            size = addrs[i + 1] - a
        if size >= 8:
            result.append((a, size, name))
    return result


def tokens(data, addr, size):
    """One token per instruction: opcode, registers, function code; immediates and targets dropped."""
    off = addr - VRAM_BASE + HEADER
    toks = []
    for (w,) in struct.iter_unpack("<I", data[off:off + size]):
        op = w >> 26
        if op == 0:                      # R-type: keep rs, rt, rd, shamt-free funct
            toks.append((0, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 63))
        elif op in (2, 3):               # j, jal: target differs between programs
            toks.append((op,))
        elif op == 0x0F:                 # lui: keep the register only
            toks.append((op, (w >> 16) & 31))
        else:                            # I-type: keep rs and rt, drop the immediate
            toks.append((op, (w >> 21) & 31, (w >> 16) & 31))
    return tuple(toks)


def parked(target):
    """Function names still INCLUDE_ASM in the target's C files."""
    names = set()
    for c in (ROOT / TARGETS[target]["src"]).glob("**/*.c"):
        text = c.read_text()
        names.update(re.findall(r'^\s*INCLUDE_ASM\("[^"]*",\s*(\w+)\);', text, re.M))
    return names


DEFAULT = re.compile(r"^(func|D|jtbl)_[0-9A-F]{8}$")


def symtab(target):
    """name -> address, and address -> [names], from the target's linked ELF."""
    elf = ROOT / "build" / target / f"{target}.elf"
    out = subprocess.run(["mips-linux-gnu-readelf", "-sW", str(elf)], capture_output=True, text=True,
                         check=True).stdout
    by_name, by_addr = {}, {}
    for line in out.splitlines():
        f = line.split()
        if len(f) >= 8 and f[3] in ("FUNC", "OBJECT", "NOTYPE") and f[6] != "UND":
            addr, name = int(f[1], 16), f[7]
            if "." in name or name.startswith("$"):   # e.g. func_X.NON_MATCHING, section names
                continue
            by_name.setdefault(name, addr)
            by_addr.setdefault(addr, []).append(name)
    return by_name, by_addr


OBJ_FUNC = re.compile(r"^([0-9a-f]+) <([^>]+)>:$")
OBJ_INSN = re.compile(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s")
OBJ_RELOC = re.compile(r"^\s*([0-9a-f]+):\s+(R_MIPS_\w+)\s+(\S+)")


def object_functions(target):
    """name -> (words by instruction index, {index: (reloc type, symbol)}), from build/<t>/**/*.o."""
    funcs = {}
    for obj in sorted((ROOT / "build" / target).glob("**/*.o")):
        out = subprocess.run(["mips-linux-gnu-objdump", "-dr", str(obj)], capture_output=True,
                             text=True).stdout
        cur = None
        for line in out.splitlines():
            m = OBJ_FUNC.match(line)
            if m:
                name = m.group(2).removesuffix(".NON_MATCHING")
                if name.startswith((".L", "L8", "jtbl_")):  # jump labels inside a function
                    continue
                cur = (int(m.group(1), 16), [], {})
                funcs[name] = cur
                continue
            if cur is None:
                continue
            m = OBJ_RELOC.match(line)
            if m:
                idx = (int(m.group(1), 16) - cur[0]) // 4
                cur[2][idx] = (m.group(2), m.group(3))
                continue
            m = OBJ_INSN.match(line)
            if m:
                cur[1].append(int(m.group(2), 16))
    return funcs


def simm16(word):
    v = word & 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def immediate_diffs(pairs, src, dst):
    """Print non-address immediate differences for each identical-shape pair."""
    s_obj, d_obj = object_functions(src), object_functions(dst)
    for dname, sname in pairs:
        if sname not in s_obj or dname not in d_obj:
            print(f"  {dname} / {sname}: not found in objects")
            continue
        _, s_words, s_rel = s_obj[sname]
        _, d_words, d_rel = d_obj[dname]
        diffs = [(i, sw, dw) for i, (sw, dw) in enumerate(zip(s_words, d_words))
                 if sw != dw and i not in s_rel and i not in d_rel]
        if not diffs:
            print(f"  {dname} / {sname}: immediates agree")
            continue
        print(f"  {dname} / {sname}: {len(diffs)} differing immediate(s)")
        for i, sw, dw in diffs:
            print(f"      +0x{i * 4:03X}: {src} {sw:08X} (imm {simm16(sw):#x})   "
                  f"{dst} {dw:08X} (imm {simm16(dw):#x})")


def collect(pairs, src, dst, allow_default):
    """Line up identical-shape pairs: {src name: {dst addr: [evidence]}}, plus DST symbol tables."""
    s_name2addr, _ = symtab(src)
    d_name2addr, d_addr2names = symtab(dst)
    s_obj, d_obj = object_functions(src), object_functions(dst)
    found = {}

    def add(name, addr, why):
        if not name or addr is None or name.startswith((".", "_")):
            return
        if DEFAULT.match(name) and not allow_default:
            return
        found.setdefault(name, {}).setdefault(addr, []).append(why)

    for dname, sname in pairs:
        add(sname, d_name2addr.get(dname), f"pair {dname} = {sname}")
        if sname not in s_obj or dname not in d_obj:
            continue
        _, s_words, s_rel = s_obj[sname]
        _, d_words, d_rel = d_obj[dname]
        for i, (stype, ssym) in s_rel.items():
            if i not in d_rel or i >= len(s_words) or i >= len(d_words):
                continue
            dtype, dsym = d_rel[i]
            if stype == "R_MIPS_26" and dtype == "R_MIPS_26":
                if dsym in d_name2addr:
                    add(ssym, d_name2addr[dsym], f"called from {dname}")
            elif stype in ("R_MIPS_LO16", "R_MIPS_GPREL16") and dtype in ("R_MIPS_LO16", "R_MIPS_GPREL16"):
                if ssym not in s_name2addr or dsym not in d_name2addr:
                    continue
                # Same field offset from the symbol's base in both programs.
                off_s = simm16(s_words[i])
                target_d = d_name2addr[dsym] + simm16(d_words[i])
                add(ssym, target_d - off_s, f"used in {dname}")

    single, conflicts = {}, []
    for sname, addrs in sorted(found.items()):
        if len(addrs) != 1:
            conflicts.append(f"{sname}: " + ", ".join(f"0x{a:08X}" for a in sorted(addrs)))
        else:
            single[sname] = next(iter(addrs.items()))
    return single, conflicts, d_name2addr, d_addr2names


def propose_names(pairs, src, dst):
    """rename.py lines giving DST symbols SRC's names, where DST still has a default name."""
    single, conflicts, d_name2addr, d_addr2names = collect(pairs, src, dst, allow_default=False)
    lines = []
    for sname, (addr, why) in single.items():
        if sname in d_name2addr:
            continue                                    # already named in DST
        names = d_addr2names.get(addr, [])
        if names and not all(DEFAULT.match(n) for n in names):
            continue                                    # DST already has a real name there
        old = next((n for n in names if DEFAULT.match(n)), None) or f"D_{addr:08X}"
        lines.append(f"{old:16} {sname:24} # find_dupes: {why[0]}")
    return lines, conflicts


def symbol_map(pairs, src, dst):
    """Every SRC -> DST correspondence, named or not."""
    single, conflicts, _, d_addr2names = collect(pairs, src, dst, allow_default=True)
    lines = [f"# {src} symbol -> {dst} symbol (address)   evidence"]
    for sname, (addr, why) in single.items():
        names = d_addr2names.get(addr, [])
        dname = next((n for n in names if not DEFAULT.match(n)), None) or \
            next(iter(names), None) or f"D_{addr:08X}"
        tag = "  (unnamed in both)" if DEFAULT.match(sname) and DEFAULT.match(dname) else ""
        lines.append(f"{sname:24} -> {dname:24} 0x{addr:08X}   # {why[0]}{tag}")
    return lines, conflicts


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default="slus_006.03")
    ap.add_argument("--dst", default="rock_neo.exe")
    ap.add_argument("--min", type=float, default=0.85, help="minimum similarity to report (0-1)")
    ap.add_argument("--names", metavar="FILE", help="write name proposals for DST to FILE")
    ap.add_argument("--imm", action="store_true", help="list non-address immediate differences")
    ap.add_argument("--map", metavar="FILE", help="write every SRC -> DST symbol correspondence to FILE")
    args = ap.parse_args()

    src_data = (ROOT / TARGETS[args.src]["disc"]).read_bytes()
    dst_data = (ROOT / TARGETS[args.dst]["disc"]).read_bytes()
    src_funcs = [(a, s, n, tokens(src_data, a, s)) for a, s, n in functions(args.src)]
    dst_funcs = [(a, s, n, tokens(dst_data, a, s)) for a, s, n in functions(args.dst)]
    src_parked = parked(args.src)

    print(f"# {len(src_funcs)} {args.src} functions vs {len(dst_funcs)} {args.dst} functions, "
          f"similarity >= {args.min}")
    print(f"# {'dst addr':10} {'dst name':28} {'size':>6}  {'score':>5}  {'src name':24} status")
    hits = 0
    identical = []
    for da, ds, dn, dt in dst_funcs:
        best = None
        for sa, ss, sn, st in src_funcs:
            # Quick length filter: -G8 can shorten a function, but not by half.
            if not (0.5 * len(st) <= len(dt) <= 1.5 * len(st)):
                continue
            sm = difflib.SequenceMatcher(None, st, dt, autojunk=False)
            if sm.real_quick_ratio() < args.min or sm.quick_ratio() < args.min:
                continue
            r = sm.ratio()
            if r >= args.min and (best is None or r > best[0]):
                best = (r, sn, st == dt)
        if best:
            hits += 1
            r, sn, same = best
            status = "identical shape" if same else "similar"
            if same and ds >= 16:   # skip empty/trivial functions: their match means nothing
                identical.append((dn, sn))
            if sn in src_parked:
                status += ", PARKED in " + args.src
            print(f"  0x{da:08X} {dn:28} {ds:6}  {r:5.2f}  {sn:24} {status}")
    print(f"# {hits} matches")

    if args.imm:
        print("# immediate differences (struct offsets, sizes, constants) in identical-shape pairs")
        immediate_diffs(identical, args.src, args.dst)

    if args.map:
        lines, conflicts = symbol_map(identical, args.src, args.dst)
        Path(args.map).write_text("\n".join(lines) + "\n")
        print(f"# wrote {len(lines) - 1} correspondences to {args.map}")
        for c in conflicts:
            print(f"# conflict (not written): {c}")

    if args.names:
        lines, conflicts = propose_names(identical, args.src, args.dst)
        Path(args.names).write_text("\n".join(lines) + "\n")
        print(f"# wrote {len(lines)} name proposals to {args.names}")
        for c in conflicts:
            print(f"# conflict (not written): {c}")


if __name__ == "__main__":
    main()
