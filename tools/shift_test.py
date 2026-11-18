#!/usr/bin/env python3
"""Find what keeps an executable from being shiftable.

Usage: tools/shift_test.py <target> [--delta 0x10000] [--list]

Links the target a second time with every segment's load address moved by DELTA (default
0x10000, so only the high halves of addresses change), using the objects from the last
`tools/build.sh <target>`, and compares the two binaries word by word. A word that refers to
an address inside the program but comes out the same in both links is a *pin*: a fixed
address that would break if anything moved. Each pin is reported with the input section and
symbol it sits in.

Checks, by section kind (from the link map):
  data / rodata  a word whose value is a program address
  text           `lui` with a program high half, and `j`/`jal` to a program address
The rule is the same for all of them: the word should change by the shift and didn't.
Words that change by something other than the shift are reported too ("odd").

The program range is the main executable's addresses including its BSS. Addresses outside it
(hardware, kernel, scratchpad, overlay load areas) are not pins: they stay fixed by design.
Exit status 0 when there are no pins. Nothing in the repo is changed; output goes to
build/<target>/shift/.
"""

import argparse
import bisect
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
os.environ["PATH"] = str(ROOT / "tools" / "vendor" / "bin") + os.pathsep + os.environ["PATH"]


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, cwd=ROOT, text=True, capture_output=True, **kw)


def sections(elf):
    """(name, vma, size, lma) of every section with contents (objcopy -O binary lays them out by LMA)."""
    out = run(["mips-linux-gnu-objdump", "-h", str(elf)]).stdout
    res = []
    lines = out.splitlines()
    for i, line in enumerate(lines):
        m = re.match(r"\s*\d+\s+(\S+)\s+([0-9a-f]{8})\s+([0-9a-f]{8})\s+([0-9a-f]{8})\s+[0-9a-f]{8}", line)
        if m and i + 1 < len(lines) and "CONTENTS" in lines[i + 1] and "ALLOC" in lines[i + 1]:
            name, size, vma, lma = m.groups()
            res.append((name, int(vma, 16), int(size, 16), int(lma, 16)))
    return res


def bss_end(elf):
    """End of the program's own sections (.main and .main_bss). Later segments (sector padding,
    ROCK_NEO.EXE's zero tail with the overlay load area) are fixed memory, not program."""
    out = run(["mips-linux-gnu-objdump", "-h", str(elf)]).stdout
    end = 0
    for m in re.finditer(r"^\s*\d+\s+(\.main\S*)\s+([0-9a-f]{8})\s+(8[0-9a-f]{7})\s", out, re.M):
        end = max(end, int(m.group(3), 16) + int(m.group(2), 16))
    return end


def input_sections(map_path):
    """Sorted (start, end, kind, object) of every input section in the link map."""
    res = []
    text = Path(map_path).read_text()
    for m in re.finditer(r"^ (\.\w+)\s*\n?\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)", text, re.M):
        sec, start, size, obj = m.groups()
        start, size = int(start, 16), int(size, 16)
        if size == 0:
            continue
        kind = "text" if sec == ".text" else "data"
        res.append((start, start + size, kind, obj, sec))
    res.sort()
    return res


def symbols(elf):
    out = run(["mips-linux-gnu-nm", "-n", str(elf)]).stdout
    addrs, names = [], []
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3 and p[1] not in "aA":
            addrs.append(int(p[0], 16))
            names.append(p[2])
    return addrs, names


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target")
    ap.add_argument("--delta", type=lambda s: int(s, 0), default=0x10000)
    ap.add_argument("--list", action="store_true", help="print every pin, not just the summary")
    args = ap.parse_args()
    t, delta = args.target, args.delta

    build = ROOT / "build" / t
    ld_script = build / f"{t}.ld"
    elf_a = build / f"{t}.elf"
    map_a = build / f"{t}.map"
    out = build / "shift"
    out.mkdir(exist_ok=True)

    # The shifted linker script: every explicit segment address moves by delta.
    script = ld_script.read_text()
    shifted = re.sub(
        r"^(\s*\.\w+\s+)0x([0-9A-Fa-f]{8})(\s*:)",
        lambda m: f"{m.group(1)}0x{int(m.group(2), 16) + delta:08X}{m.group(3)}",
        script,
        flags=re.M,
    )
    if shifted == script:
        sys.exit("no segment addresses found in " + str(ld_script))
    (out / f"{t}.ld").write_text(shifted)

    extra = []
    for f in ("auto_syms.ld", "absolute_syms.ld"):  # written by tools/build.sh
        if (build / f).exists():
            extra += ["-T", str(build / f)]
    if (ROOT / f"linker_syms_{t}.ld").exists():
        extra += ["-T", str(ROOT / f"linker_syms_{t}.ld")]
    elf_b = out / f"{t}.elf"
    run(["mips-linux-gnu-ld", "-EL", *extra, "-T", str(out / f"{t}.ld"), "-Map", str(out / f"{t}.map"), "-o", str(elf_b)])
    bin_a, bin_b = out / "a.bin", out / "b.bin"
    run(["mips-linux-gnu-objcopy", "-O", "binary", str(elf_a), str(bin_a)])
    run(["mips-linux-gnu-objcopy", "-O", "binary", str(elf_b), str(bin_b)])
    a, b = bin_a.read_bytes(), bin_b.read_bytes()

    secs = sections(elf_a)
    main_secs = [s for s in secs if s[1] >= 0x80000000]
    lo = min(s[1] for s in main_secs)
    hi = bss_end(elf_a)
    file_base = min(s[3] for s in secs)  # objcopy -O binary starts at the lowest LMA

    inputs = input_sections(map_a)
    starts = [s[0] for s in inputs]
    sym_addrs, sym_names = symbols(elf_a)

    def where(addr):
        i = bisect.bisect_right(starts, addr) - 1
        sec = inputs[i] if i >= 0 and addr < inputs[i][1] else None
        j = bisect.bisect_right(sym_addrs, addr) - 1
        sym = f"{sym_names[j]}+0x{addr - sym_addrs[j]:X}" if j >= 0 else "?"
        return sec, sym

    def in_prog(v):
        return lo <= v < hi

    pins = []
    odd = []
    for name, vma, size, off in secs:  # the header too (its entry point and load address)
        start = off - file_base
        if start < 0 or start >= len(a):
            continue  # NOBITS (bss)
        for i in range(start, min(start + size, len(a), len(b)) - 3, 4):
            wa = int.from_bytes(a[i:i + 4], "little")
            wb = int.from_bytes(b[i:i + 4], "little")
            addr = vma + (i - start)
            sec, sym = where(addr)
            kind = sec[2] if sec else "data"
            what = None
            if kind == "text":
                op = wa >> 26
                if op == 0x0F and ((wa >> 21) & 31) == 0:  # lui
                    h = (wa & 0xFFFF) << 16
                    if in_prog(h) or in_prog(h - 0x8000) or in_prog(h + 0x7FFF):
                        if wa == wb:
                            what = f"lui 0x{wa & 0xFFFF:04X}"
                        elif (wb & 0xFFFF) - (wa & 0xFFFF) != delta >> 16:
                            odd.append((addr, sym, sec, wa, wb))
                elif op in (2, 3):  # j, jal
                    tgt = 0x80000000 | ((wa & 0x3FFFFFF) << 2)
                    if in_prog(tgt) and wa == wb:
                        what = f"{'jal' if op == 3 else 'j'} 0x{tgt:08X}"
            else:
                if in_prog(wa):
                    if wa == wb:
                        what = f".word 0x{wa:08X}"
                    elif wb - wa != delta:
                        odd.append((addr, sym, sec, wa, wb))
            if what:
                pins.append((addr, sym, sec, what))

    by_obj = Counter((p[2][3] if p[2] else "?") for p in pins)
    print(f"{t}: program 0x{lo:08X}-0x{hi:08X}, shifted by 0x{delta:X}")
    print(f"pins: {len(pins)}   odd: {len(odd)}")
    for obj, n in by_obj.most_common():
        print(f"  {n:5d}  {obj.replace(str(ROOT) + '/', '')}")
    if args.list:
        for addr, sym, sec, what in pins:
            print(f"0x{addr:08X}  {sym:40s} {what}")
        for addr, sym, sec, wa, wb in odd:
            print(f"odd 0x{addr:08X}  {sym:40s} 0x{wa:08X} -> 0x{wb:08X}")
    (out / "pins.txt").write_text(
        "".join(f"0x{addr:08X}  {sym}  {what}  {(sec[3] if sec else '?')}\n" for addr, sym, sec, what in pins)
    )
    sys.exit(1 if pins else 0)


if __name__ == "__main__":
    main()
