#!/usr/bin/env python3
"""Place the natively compiled game at its retail addresses, and resolve what it lacks.

Usage:
  gen_link.py --elf <retail.elf> --out-dir <dir> --ld <out.ld> --stubs <out.c>
              [--report <out.txt>] --place <obj>... [--scan <obj>...] [--defined <lib>...]

The matching build's ELF (build/<t>/<t>.elf) gives
the retail address of every symbol. Natively:

  - Every **function** that the placed objects define and that has a retail address gets that
    address as its symbol value. The object is rewritten (objcopy) so its definition is weak,
    an alias `port_native_<name>` names the native code, and the linker script assigns
    `<name> = <retail address>`. At boot the runtime writes a jump at each retail address to the
    native code (the stub table in --stubs, `port_stub_table`). So `&func` in C, a function
    pointer in retail data, and a literal address all agree, and all of them call the native
    code.
  - Every **global data object** the placed objects define with a retail address: weakened and
    assigned its retail address the same way. The runtime loads the retail executable image at
    0x80010000, so the bytes there are the object's initial value (the C matches, so they are the
    same values the C gives).
  - **File statics** with a retail address: references inside their own object are already
    section-relative, so the section itself (one per object with -fdata-sections) is placed at
    the retail address in a non-allocated output section (OVERLAY type): its symbols get the
    retail address but nothing is loaded there (the PS1 RAM is mapped by the runtime).
  - Everything still **missing** (used, defined nowhere): retail data becomes an absolute
    symbol; a retail function gets a reporting stub `port_native_<name>` placed the same way as
    a defined function. C library names (memcpy, ...) are left to the host libc.

Objects listed with --scan (test programs, the host main) are linked but not placed; their
undefined symbols count. --defined lists libraries whose definitions satisfy symbols as they are
(the platform runtime).
"""

import argparse
import os
import re
import shutil
import subprocess
import sys

# PsyQ's libc entries with host equivalents of the same behaviour.
LIBC = {
    "memcpy", "memset", "memmove", "memcmp", "memchr", "bcopy", "bzero", "bcmp",
    "strcpy", "strncpy", "strcat", "strncat", "strcmp", "strncmp", "strlen", "strchr",
    "strrchr", "sprintf", "printf", "puts", "abs", "labs", "toupper", "tolower", "atoi",
}

SPLAT_NAME = re.compile(r"(D|func)_([0-9A-Fa-f]{8})")

# PsyQ names that are also host C library functions with other meanings (the BIOS file calls on
# memory-card paths, PsyQ's own generator). The game objects are rewritten to call psyq_<name>,
# which the port defines; the host keeps the real ones. Without the rename, the absolute retail
# symbol would also capture the host's own calls (and a shared library's, once exported).
RENAME = {"open", "close", "read", "write", "format", "rand"}
PREFIX = "psyq_"


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True, check=True).stdout


def read_symbols(path):
    """Symbols of a relocatable object: list of dicts (name, value, type, bind, section)."""
    sections = {}
    for line in run(["readelf", "-SW", path]).splitlines():
        m = re.match(r"\s*\[\s*(\d+)\]\s+(\S+)", line)
        if m:
            sections[m.group(1)] = m.group(2)
    syms = []
    for line in run(["readelf", "-sW", path]).splitlines():
        parts = line.split()
        if len(parts) < 8 or not parts[0].endswith(":") or parts[1] == "Value":
            continue
        value, kind, bind, ndx, name = parts[1], parts[3], parts[4], parts[6], parts[7]
        syms.append({
            "name": name,
            "value": int(value, 16),
            "type": kind,
            "bind": bind,
            "ndx": ndx,
            "section": sections.get(ndx),
        })
    return syms


def nm_lib(path):
    defined, undefined = set(), set()
    for line in run(["nm", "-P", "-A", path]).splitlines():
        parts = line.split()
        if len(parts) < 3:
            continue
        name, kind = parts[1], parts[2]
        if kind == "U":
            undefined.add(name)
        elif kind not in ("w", "v"):
            defined.add(name)
    return defined, undefined


def retail_symbols(elf):
    """(globals, locals): name -> (addr, kind). Locals that occur twice are dropped."""
    glob, loc, dup = {}, {}, set()
    for line in run(["readelf", "-sW", elf]).splitlines():
        parts = line.split()
        if len(parts) < 8 or not parts[0].endswith(":"):
            continue
        value, kind, bind, name = parts[1], parts[3], parts[4], parts[7]
        if kind not in ("FUNC", "OBJECT", "NOTYPE") or "." in name:
            continue
        addr = int(value, 16)
        if addr == 0:
            continue
        is_global = bind in ("GLOBAL", "WEAK")
        table = glob if is_global else loc
        if not is_global and name in loc and loc[name][0] != addr:
            dup.add(name)
        # A name can appear as both FUNC and OBJECT; FUNC wins.
        if name not in table or kind == "FUNC":
            table[name] = (addr, kind)
    for name in dup:
        del loc[name]
    return glob, loc


def retail_address(name, table, want_func):
    """Retail address of `name` if it is a function (want_func) or data (not want_func)."""
    if name.startswith(PREFIX) and name[len(PREFIX):] in RENAME:
        name = name[len(PREFIX):]
    if name in table:
        addr, kind = table[name]
        return addr if (kind == "FUNC") == want_func else None
    m = SPLAT_NAME.fullmatch(name)
    if m and (m.group(1) == "func") == want_func:
        return int(m.group(2), 16)
    return None


DIE = re.compile(r"^\s*<(\d+)><([0-9a-f]+)>: Abbrev Number: \d+ \((DW_TAG_\w+)\)")
ATTR = re.compile(r"^\s*<[0-9a-f]+>\s+(DW_AT_\w+)\s*: (.*)$")
# How a narrow return value is extended into v0, as MIPS GCC returns it.
EXTEND_CAST = {(1, False): "(uint8_t)", (1, True): "(int8_t)",
               (2, False): "(uint16_t)", (2, True): "(int16_t)"}


def narrow_returns(obj):
    """Functions defined in obj (DWARF, -g) whose return type is 1 or 2 bytes: name -> cast."""
    dies, order, cur = {}, [], None
    out = run(["readelf", "--debug-dump=info", obj])
    for line in out.splitlines():
        m = DIE.match(line)
        if m:
            cur = {"tag": m.group(3)}
            dies[int(m.group(2), 16)] = cur
            order.append(cur)
            continue
        m = ATTR.match(line)
        if m and cur is not None:
            cur[m.group(1)] = m.group(2).strip()

    def ref(v):
        m = re.match(r"<0x([0-9a-f]+)>", v or "")
        return dies.get(int(m.group(1), 16)) if m else None

    def base(d):
        for _ in range(16):
            if d is None or d["tag"] not in ("DW_TAG_typedef", "DW_TAG_const_type",
                                             "DW_TAG_volatile_type"):
                return d
            d = ref(d.get("DW_AT_type"))
        return None

    result = {}
    for d in order:
        if d["tag"] != "DW_TAG_subprogram" or "DW_AT_declaration" in d or \
                "DW_AT_name" not in d or "DW_AT_type" not in d:
            continue
        t = base(ref(d["DW_AT_type"]))
        if t is None or t["tag"] not in ("DW_TAG_base_type", "DW_TAG_enumeration_type"):
            continue
        size = int(t.get("DW_AT_byte_size", "4").split()[0], 0)
        enc = t.get("DW_AT_encoding", "")
        signed = "signed" in enc and "unsigned" not in enc
        if (size, signed) in EXTEND_CAST:
            result[d["DW_AT_name"].split(": ")[-1]] = EXTEND_CAST[(size, signed)]
    return result


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--elf", required=True)
    ap.add_argument("--out-dir", required=True)
    ap.add_argument("--ld", required=True)
    ap.add_argument("--stubs", required=True)
    ap.add_argument("--report")
    ap.add_argument("--place", nargs="+", required=True)
    ap.add_argument("--scan", nargs="*", default=[])
    ap.add_argument("--defined", nargs="*", default=[])
    args = ap.parse_args()

    glob, loc = retail_symbols(args.elf)
    os.makedirs(args.out_dir, exist_ok=True)

    placed_funcs = {}  # name -> (addr, object)
    placed_data = {}  # name -> (addr, object)
    statics = []  # (name, addr, object basename, section)
    defined, needed = set(), set()
    code = {}  # placed function -> (object, section, offset): aliases share one
    errors = []

    narrow = {}  # placed function -> cast that extends its result (calls via the stub)
    for obj in args.place:
        obj_narrow = narrow_returns(obj)
        weaken, aliases, renames = [], [], []
        for s in read_symbols(obj):
            name, ndx = s["name"], s["ndx"]
            if not name or s["type"] in ("FILE", "SECTION"):
                continue
            if name in RENAME and s["bind"] != "LOCAL":
                renames.append(name)
                name = PREFIX + name
            if ndx == "UND":
                needed.add(name)
                continue
            if s["bind"] == "GLOBAL":
                defined.add(name)
                is_func = s["type"] == "FUNC"
                addr = retail_address(name, glob, is_func)
                if addr is None:
                    continue
                table = placed_funcs if is_func else placed_data
                if name in table:
                    errors.append("%s is defined twice (%s, %s)" % (name, table[name][1], obj))
                    continue
                table[name] = (addr, obj)
                code[name] = (obj, s["section"], s["value"])
                weaken.append(name)
                if is_func and name in obj_narrow:
                    narrow[name] = obj_narrow[name]
                if is_func:
                    aliases.append("port_native_%s=%s:0x%x,global,function"
                                   % (name, s["section"], s["value"]))
            elif s["bind"] == "LOCAL" and s["type"] == "OBJECT":
                addr = loc.get(name, (None,))[0]
                if addr is None:
                    addr = retail_address(name, glob, False)
                if addr is None:
                    continue
                sec = s["section"] or ""
                if not sec.endswith("." + name):
                    errors.append("static %s in %s shares section %s (build with -fdata-sections)"
                                  % (name, obj, sec))
                    continue
                statics.append((name, addr, os.path.basename(obj), sec))
            elif s["bind"] == "LOCAL" and s["type"] == "FUNC" and name in loc:
                print("gen_link: warning: static function %s (%s) is not placed" % (name, obj))
        out = os.path.join(args.out_dir, os.path.basename(obj))
        cmd = ["objcopy"]
        for name in renames:
            cmd += ["--redefine-sym", "%s=%s%s" % (name, PREFIX, name)]
        for name in weaken:
            cmd += ["--weaken-symbol", name]
        for alias in aliases:
            cmd += ["--add-symbol", alias]
        if len(cmd) > 1:
            run(cmd + [obj, out])
        else:
            shutil.copyfile(obj, out)

    for obj in args.scan:
        d, u = nm_lib(obj)
        defined |= d
        needed |= u
    for lib in args.defined:
        d, _ = nm_lib(lib)
        defined |= d
    needed -= defined

    missing_funcs, missing_data, libc, unknown = {}, {}, [], []
    for name in sorted(needed):
        if name in LIBC:
            libc.append(name)
            continue
        addr = retail_address(name, glob, True)
        if addr is not None:
            missing_funcs[name] = addr
            continue
        addr = retail_address(name, glob, False)
        if addr is not None:
            missing_data[name] = addr
            continue
        unknown.append(name)

    # One native function per retail address.
    by_addr = {}
    for name, (addr, _) in placed_funcs.items():
        by_addr.setdefault(addr, []).append(name)
    for name, addr in missing_funcs.items():
        by_addr.setdefault(addr, []).append(name)
    for addr, names in by_addr.items():
        # Several names are fine when they are aliases of one native function (the port defines
        # PsyQ's name and the splat name of a library function until it is renamed).
        if len({code.get(n, n) for n in names}) > 1:
            errors.append("0x%08X has several native functions: %s" % (addr, ", ".join(names)))
    if errors:
        for e in errors:
            print("gen_link: error: " + e, file=sys.stderr)
        sys.exit(1)

    with open(args.ld, "w") as f:
        f.write("/* Generated by port/tools/gen_link.py. */\n")
        f.write("/* Functions: weak native definitions, retail addresses here, jumps at boot. */\n")
        for name, (addr, _) in sorted(placed_funcs.items(), key=lambda kv: kv[1][0]):
            f.write("%s = 0x%08X;\n" % (name, addr))
        f.write("/* Functions with no native code: reporting stubs, placed the same way. */\n")
        for name, addr in sorted(missing_funcs.items(), key=lambda kv: kv[1]):
            f.write("%s = 0x%08X;\n" % (name, addr))
        f.write("/* Data defined in C, weakened: the retail image holds it. */\n")
        for name, (addr, _) in sorted(placed_data.items(), key=lambda kv: kv[1][0]):
            f.write("%s = 0x%08X;\n" % (name, addr))
        f.write("/* Data defined only by the retail image. */\n")
        for name, addr in sorted(missing_data.items(), key=lambda kv: kv[1]):
            f.write("%s = 0x%08X;\n" % (name, addr))
        f.write("/* File statics: their sections at the retail address, not loaded. */\n")
        f.write("SECTIONS\n{\n")
        for name, addr, base, sec in sorted(statics, key=lambda t: t[1]):
            f.write("    .psx%s 0x%08X (OVERLAY) : { *%s(%s) }\n" % (sec, addr, base, sec))
        f.write("}\nINSERT AFTER .bss;\n")

    with open(args.stubs, "w") as f:
        f.write("/* Generated by port/tools/gen_link.py: the retail-address stub table and the\n"
                "   reporting stubs for functions with no native code. */\n")
        f.write("#include \"port_stubs.h\"\n\n")
        f.write("int port_missing(const char *name, unsigned int addr);\n\n")
        for name, addr in sorted(missing_funcs.items(), key=lambda kv: kv[1]):
            f.write('int port_native_%s(void) { return port_missing("%s", 0x%08XU); }\n'
                    % (name, name, addr))
        f.write("\n")
        for name in sorted(placed_funcs):
            f.write("void port_native_%s(void);\n" % name)
        # Results narrower than a word: i386 GCC leaves the upper bits of eax undefined, MIPS
        # callers (the overlays, emulated PsyQ) expect v0 extended as MIPS GCC returns it. The
        # retail address (stub jump, interpreter calls, function pointers) reaches a wrapper
        # that extends; native code calling port_native_<name> directly is unaffected.
        f.write("\n#include <stdint.h>\n\n")
        for name in sorted(narrow):
            f.write("uint32_t port_wrap_%s(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, "
                    "uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8, "
                    "uint32_t a9)\n{\n    return (uint32_t)(int32_t)%s((uint32_t(*)(uint32_t, "
                    "uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, "
                    "uint32_t, uint32_t))port_native_%s)(a0, a1, a2, a3, a4, a5, a6, a7, a8, "
                    "a9);\n}\n" % (name, narrow[name], name))
        f.write("\nconst PORT_STUB port_stub_table[] = {\n")
        for addr in sorted(by_addr):
            name = by_addr[addr][0]
            missing = name in missing_funcs
            entry = [n for n in by_addr[addr] if n in narrow]
            fn = ("port_wrap_" + entry[0]) if entry else ("port_native_" + name)
            f.write('    {0x%08XU, (void (*)(void))%s, "%s", %d},\n'
                    % (addr, fn, name, 1 if missing else 0))
        f.write("};\n")
        f.write("const int port_stub_count = %d;\n" % len(by_addr))

    report = [
        "placed objects: %d" % len(args.place),
        "functions at retail addresses: %d" % len(placed_funcs),
        "global data at retail addresses: %d" % len(placed_data),
        "file statics at retail addresses: %d" % len(statics),
        "retail data symbols (absolute): %d" % len(missing_data),
        "function stubs (no native code): %d" % len(missing_funcs),
        "narrow results extended through the stub: %d" % len(narrow),
        "host libc: %s" % (", ".join(libc) or "-"),
        "left to the host link: %s" % (", ".join(unknown) or "-"),
    ]
    if args.report:
        with open(args.report, "w") as f:
            f.write("\n".join(report) + "\n")
            f.write("\nfunctions with no native code:\n")
            for name, addr in sorted(missing_funcs.items(), key=lambda kv: kv[1]):
                f.write("  %08X %s\n" % (addr, name))
            f.write("\nfile statics:\n")
            for name, addr, base, sec in sorted(statics, key=lambda t: t[1]):
                f.write("  %08X %s (%s)\n" % (addr, name, base))
    print("gen_link: " + "; ".join(report[1:7]))


if __name__ == "__main__":
    main()
