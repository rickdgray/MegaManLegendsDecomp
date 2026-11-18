#!/usr/bin/env python3
"""Rewrite one overlay module's natively compiled assembly for the hybrid runtime.

Usage:
  ovl_rewrite.py --module r3_st02 --elf build/r3_st02/r3_st02.elf
                 --main-elf build/rock_neo.exe/rock_neo.exe.elf --out-dir <dir> --json <out.json>
                 [--exclude [MODULE:]NAME...] [--cc "gcc -m32"] --files a.s b.s ...

Every C file a module links (its own and the
shared stage_common files) is compiled with -S (and -aux-info <same stem>.aux for the return
types); this tool rewrites the assembly of all of them together and assembles the result:

  - A function the module defines in C that has a retail address in the module's ELF (and is
    not parked in the matching build, or is a parked draft not in --exclude) becomes native: its
    definition is renamed `port_ovl_<module>_<name>` (global), and direct calls and jumps to it
    from anywhere in the module use that name, so calls inside the module stay native.
  - Every other reference to it (`$name`, `.long name`: an address taken, stored in a work
    struct or a table that MIPS code reads) is the retail address (`.set name, 0x...`), so
    pointer values agree with retail data and interpreted code. Calls through such an address
    land in overlay RAM, which is not executable, and enter port/runtime/overlay.c's trap; the
    native table (gen_ovl_table.py) then finds the native code again.
  - Data the C defines with a retail address: the native definition is renamed to an unused local
    and the name is `.set` to the retail address (the loaded overlay holds the real data there,
    shared with the interpreted code).
  - Overlay symbols the module does not define in C (INCLUDE_ASM functions, data still in
    assembly): `.set` to the address in the module's ELF. A call then goes to the MIPS code
    through the trap.
  - ROCK_NEO.EXE data (absolute in the module's ELF): `.set` to its retail address. ROCK_NEO.EXE
    functions stay undefined globals, resolved by the main link (retail.ld, stubs, the emulated
    PsyQ thunks). PsyQ names that clash with the host C library become psyq_<name>, as
    gen_link.py does for the executable.
  - Everything module-local loses `.globl`, so the 46 modules never clash; only the renamed
    native functions (and native-only globals, renamed per module) stay global.
  - Functions whose return type is narrower than a word get their result extended before every
    `ret`: MIPS callers expect v0 sign- or zero-extended (GCC 2.7's MIPS ABI), and i386 GCC leaves
    the upper bits of eax undefined. The module is compiled with -fno-optimize-sibling-calls, so
    every return goes through a `ret`.

The JSON lists the native functions (retail address, size, native symbol, direct native callees)
for gen_ovl_table.py, and what was found without a retail address.
"""

import argparse
import json
import os
import re
import shlex
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ovl_elf import Elf  # noqa: E402

SPLAT_NAME = re.compile(r"(D|func)_([0-9A-Fa-f]{8})")
RENAME = {"open", "close", "read", "write", "format", "rand"}
IDENT = re.compile(r"(?<![\w.%])([A-Za-z_]\w*(?:\.\w+)*)")
LABEL = re.compile(r"^([A-Za-z_][\w.$]*):(.*)$")
DIRECT = re.compile(r"^(\s*)(call|jmp|j[a-z]{1,3})(\s+)([A-Za-z_][\w.$]*)\s*$")
RET = re.compile(r"^\s*(rep\s+)?ret\s*$")
SKIP_LINE = re.compile(r"^\s*\.(string|ascii|asciz|file|ident|loc|cfi_\w+)\b")
SYMDIR = re.compile(r"^(\s*)\.(globl|global|local|weak|hidden|type|size|comm|lcomm)(\s+)"
                    r"([A-Za-z_][\w.$]*)(.*)$")

# Return types that need extension, as -aux-info spells them (typedefs from common.h).
EXTEND = {
    "uint8": "movzbl %al, %eax", "u8": "movzbl %al, %eax", "u_char": "movzbl %al, %eax",
    "unsigned char": "movzbl %al, %eax",
    "sint8": "movsbl %al, %eax", "s8": "movsbl %al, %eax", "signed char": "movsbl %al, %eax",
    "char": "movsbl %al, %eax",
    "uint16": "movzwl %ax, %eax", "u16": "movzwl %ax, %eax", "u_short": "movzwl %ax, %eax",
    "unsigned short": "movzwl %ax, %eax", "short unsigned int": "movzwl %ax, %eax",
    "sint16": "movswl %ax, %eax", "s16": "movswl %ax, %eax", "short": "movswl %ax, %eax",
    "signed short": "movswl %ax, %eax", "short int": "movswl %ax, %eax",
}
AUX = re.compile(r"^/\* (\S+):(\d+):([NO])F \*/ (?:extern |static )?(.+?) ?\b([A-Za-z_]\w*) \(")


def splat_address(name):
    m = SPLAT_NAME.fullmatch(name)
    return int(m.group(2), 16) if m else None


def parse_aux(path):
    """Return types of the functions defined in this file: name -> type text."""
    types = {}
    if not os.path.exists(path):
        return types
    with open(path, encoding="latin-1") as f:
        for line in f:
            m = AUX.match(line)
            if m:
                types[m.group(5)] = re.sub(r"\s+", " ", m.group(4).strip())
    return types


def scan(path):
    """Labels defined in one .s file: name -> {"kind", "global"}, plus all lines."""
    with open(path, encoding="latin-1") as f:
        lines = f.read().split("\n")
    defs, types, globs = {}, {}, set()
    section, previous = ".text", ".text"
    for line in lines:
        s = line.strip()
        if s.startswith(".section"):
            previous, section = section, s.split()[1].split(",")[0]
        elif s in (".text", ".data", ".bss"):
            previous, section = section, s
        elif s == ".previous":
            previous, section = section, previous
        m = SYMDIR.match(line)
        if m:
            d, name = m.group(2), m.group(4)
            if d in ("globl", "global"):
                globs.add(name)
            elif d == "type":
                types[name] = "func" if "function" in m.group(5) else "data"
            elif d in ("comm", "lcomm"):
                defs[name] = {"kind": "data", "section": ".bss"}
            continue
        m = LABEL.match(line)
        if m and not m.group(1).startswith(".L"):
            kind = "func" if section.startswith(".text") else "data"
            defs[m.group(1)] = {"kind": kind, "section": section}
    for name, d in defs.items():
        d["kind"] = types.get(name, d["kind"])
        d["global"] = name in globs
    return lines, defs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--module", required=True)
    ap.add_argument("--elf", required=True)
    ap.add_argument("--main-elf", required=True)
    ap.add_argument("--out-dir", required=True)
    ap.add_argument("--json", required=True)
    ap.add_argument("--exclude", nargs="*", default=[])
    ap.add_argument("--cc", default="gcc -m32", help="assembler driver command (one string)")
    ap.add_argument("--files", nargs="+", required=True)
    args = ap.parse_args()
    mod = args.module
    prefix = "port_ovl_%s_" % mod
    # NAME excludes it in every module (shared stage code), MODULE:NAME in one.
    exclude = {e.split(":")[-1] for e in args.exclude
               if ":" not in e or e.split(":")[0] == mod}

    elf = Elf(args.elf)
    base, image = elf.image()
    retail = {}  # name -> symbol (module image only)
    absolute = {}  # name -> address (ROCK_NEO.EXE, hardware: absolute in the module's ELF)
    parked = set()
    for s in elf.symbols:
        name = s["name"]
        if not name or s["type"] in ("FILE", "SECTION"):
            continue
        if name.endswith(".NON_MATCHING"):
            parked.add(name[:-len(".NON_MATCHING")])
            continue
        if s["abs"]:
            absolute[name] = s["value"]
        elif s["bind"] != "LOCAL" or name not in retail:
            if name not in retail or s["type"] == "FUNC":
                retail[name] = s
    module_funcs = sorted({n for n, s in retail.items() if s["type"] == "FUNC"})
    main_funcs = {s["name"]: s["value"] for s in Elf(args.main_elf).symbols
                  if s["type"] == "FUNC"}

    files = []
    alldefs = {}  # name -> (file, def)
    for path in args.files:
        lines, defs = scan(path)
        files.append((path, lines, defs, parse_aux(os.path.splitext(path)[0] + ".aux")))
        for name, d in defs.items():
            if name in alldefs and (d["global"] or alldefs[name][1]["global"]):
                print("ovl_rewrite: %s: %s defined in %s and %s" % (mod, name, alldefs[name][0],
                      path), file=sys.stderr)
                sys.exit(1)
            alldefs.setdefault(name, (path, d))

    def retail_addr(name, func):
        s = retail.get(name)
        if s is not None:
            return s["value"] if (s["type"] == "FUNC") == func or s["type"] == "NOTYPE" else None
        a = splat_address(name)
        if a is not None and (name.startswith("func_") == func) and \
                base <= a < base + len(image):
            return a
        return None

    native = {}  # name -> retail symbol (native functions of this module)
    report = {"native_only": [], "data_native": [], "data_retail": [], "excluded": [],
              "drafts": []}
    for name, (path, d) in alldefs.items():
        if d["kind"] == "func":
            addr = retail_addr(name, True)
            if addr is None:
                report["native_only"].append(name)
            elif name in exclude:
                report["excluded"].append(name)
            else:
                native[name] = retail.get(name) or {"value": addr, "size": 0}
                if name in parked:
                    report["drafts"].append(name)
        else:
            addr = retail_addr(name, False)
            if addr is None:
                writable = not d["section"].startswith(".rodata")
                report["data_native"].append([name, d["section"], writable])
            else:
                report["data_retail"].append(name)

    # Definitions: name -> new label (None: keep as is).
    def def_name(name, d):
        if d["kind"] == "func":
            if name in native:
                return prefix + name
            if retail_addr(name, True) is None:
                return prefix + name if d["global"] else None
            return "port_dead_" + name  # excluded: the retail code runs
        if retail_addr(name, False) is not None:
            return "port_dead_" + name
        return prefix + name if d["global"] else None

    out = {"module": mod, "elf": os.path.abspath(args.elf), "base": base, "functions": [],
           "module_functions": len(module_funcs), "files": []}
    for path, lines, defs, aux in files:
        sets = {}  # name -> address for `.set`
        new = []
        cur = None  # function whose body we are in (original name)
        callees = {}
        renamed = {n: def_name(n, d) for n, d in defs.items()}

        def resolve(name):
            """A reference: (new name, retail address for `.set` or None)."""
            if name in defs:
                d = defs[name]
            elif name in alldefs and alldefs[name][1]["global"]:
                d = alldefs[name][1]
            else:
                d = None
            if d is not None:
                addr = retail_addr(name, d["kind"] == "func")
                if addr is not None:
                    return name, addr  # native or not, its address is the retail one
                return (prefix + name if d["global"] else name), None
            s = retail.get(name)
            if s is not None:
                return name, s["value"]
            if name in absolute:
                if name in main_funcs:
                    return ("psyq_" + name if name in RENAME else name), None
                return name, absolute[name]
            a = splat_address(name)
            if a is not None and base <= a < base + len(image):
                return name, a
            if name in RENAME:
                return "psyq_" + name, None
            return name, None

        def ref(m):
            name, addr = resolve(m.group(1))
            if addr is not None:
                sets[name] = addr
            return name

        for line in lines:
            m = SYMDIR.match(line)
            if m and m.group(4) in defs:
                d, name = m.group(2), m.group(4)
                nn = renamed[name]
                if d in ("globl", "global"):
                    if nn is not None and nn.startswith(prefix):
                        new.append("%s.globl%s%s" % (m.group(1), m.group(3), nn))
                    continue
                rest = m.group(5)
                if nn is not None:
                    rest = rest.replace(".-" + name, ".-" + nn)
                    if d == "size" and name == cur:
                        cur = None
                new.append("%s.%s%s%s%s" % (m.group(1), d, m.group(3), nn or name, rest))
                continue
            m = LABEL.match(line)
            if m and m.group(1) in defs:
                name = m.group(1)
                if defs[name]["kind"] == "func":
                    cur = name
                    callees.setdefault(name, set())
                new.append("%s:%s" % (renamed[name] or name, m.group(2)))
                continue
            if SKIP_LINE.match(line) or line.lstrip().startswith("#"):
                new.append(line)
                continue
            m = DIRECT.match(line)
            if m:
                target = m.group(4)
                if target in native:
                    if cur is not None:
                        callees[cur].add(target)
                    new.append("%s%s%s%s" % (m.group(1), m.group(2), m.group(3), prefix + target))
                    continue
            if cur in native and RET.match(line):
                ext = EXTEND.get(aux.get(cur, ""))
                if ext:
                    new.append("\t" + ext)
            new.append(IDENT.sub(ref, line))

        bad = [n for n, a in sets.items() if a is None]
        if bad:
            print("ovl_rewrite: %s: no retail address for %s" % (mod, ", ".join(bad)),
                  file=sys.stderr)
            sys.exit(1)
        head = ["# Rewritten by port/tools/ovl_rewrite.py for module %s" % mod]
        head += ["\t.set\t%s, 0x%08X" % (n, a) for n, a in sorted(sets.items())]
        stem = os.path.splitext(os.path.basename(path))[0]
        s_out = os.path.join(args.out_dir, stem + ".ovl.s")
        o_out = os.path.join(args.out_dir, stem + ".ovl.o")
        with open(s_out, "w", encoding="latin-1") as f:
            f.write("\n".join(head + new))
        subprocess.run(shlex.split(args.cc) + ["-c", s_out, "-o", o_out], check=True)
        out["files"].append(o_out)
        for name in defs:
            if name in native:
                s = native[name]
                out["functions"].append({
                    "name": name, "addr": s["value"], "size": s["size"],
                    "native": prefix + name, "draft": name in parked,
                    "ret": aux.get(name, "?"),
                    "callees": sorted(callees.get(name, ())),
                })

    out["functions"].sort(key=lambda e: e["addr"])
    # Undefined symbols left for the main link that ROCK_NEO.EXE does not have.
    und, calls = set(), {}
    for o in out["files"]:
        for line in subprocess.run(["nm", "-u", o], capture_output=True, text=True,
                                   check=True).stdout.splitlines():
            name = line.split()[-1]
            plain = name[5:] if name.startswith("psyq_") and name[5:] in RENAME else name
            if plain in main_funcs:
                calls[name] = main_funcs[plain]
            else:
                und.add(name)
    out["main_functions"] = calls  # ROCK_NEO.EXE functions referenced (for gen_ovl_table.py)
    report["undefined_unknown"] = sorted(und)
    out["report"] = report
    with open(args.json, "w") as f:
        json.dump(out, f, indent=1)


if __name__ == "__main__":
    main()
