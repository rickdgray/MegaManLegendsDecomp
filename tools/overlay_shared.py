#!/usr/bin/env python3
"""Find code that several stage overlays share: runs of consecutive functions whose bodies and
layout are identical in two or more stages (the same object file linked into each).

Usage:
  tools/overlay_shared.py runs [--min N] [--top N]   list the shared runs, largest saving first
  tools/overlay_shared.py show <stage> <func>        one run in detail: where it sits in every
                                                     stage, and the module-local symbols it uses
  tools/overlay_shared.py carve <name> <stage> <func>
      make the run holding <func> a shared file, src/stage_common/<name>.c: in every stage that
      has it, a subsegment {type: c, name: <name>, dir: ../stage_common} (the stage's C file is
      split around it, the part after becoming <stage>_<offset>.c), and registry names
      <name>_func_<offset in the file>, <name>_D_<offset from its first data symbol> and
      <name>_R_<offset in its rodata> for its functions and the data it uses. Data symbols whose
      distance apart is the same in every stage belong to one object; the object with the most
      symbols is the file's own (D), the others are other objects' (<name>_E_<offset from its
      first symbol>, then E2, ..., in address order), so the names agree across stages even where
      another object's data happens to sit inside the file's own block. Then ./tools/rebuild.sh
      each stage.

Needs every stage split and built (`make split-overlays overlays`): function boundaries come from
build/<t>/<t>.elf, bodies from splat's asm (asm/<t>/nonmatchings/**/<func>.s), falling back to
the chunk's bytes for functions splat wrote as C (empty ones).

Each instruction is compared as splat's text, with every module-local symbol (func_, D_, jtbl_
inside the stage's own address range) replaced by a placeholder and branch labels made relative
to the function, so a function compares equal across stages at different addresses. References
into ROCK_NEO.EXE keep their names and must agree. A run also requires the same spacing between
its functions (the gap after each one is part of its token).

The greedy pass picks the run that saves the most bytes, size x (stages - 1), marks its functions
as used in every stage it occurs in, and repeats on what's left. Function bodies of a run are only
used once, so a 66-function block found in 18 stages isn't counted again inside a longer
two-stage run.
"""

import argparse
import re
import subprocess
import textwrap
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
# A branch label (.L80101D9C) or any identifier; identifiers that name a module-local symbol are
# masked.
# Data symbols further than this from the previous one start another object's data.
DATA_GAP = 0x400
IDENT_RE = re.compile(r"\.L([0-9A-F]{8})\b|\b[A-Za-z_]\w*\b")


def overlay_stages():
    """[(target, load, size)] for the stage overlays in tools/overlays.txt."""
    out = []
    for line in (ROOT / "tools/overlays.txt").read_text().splitlines():
        if not line or line.startswith("#"):
            continue
        f = line.split()
        if f[0].startswith("r3_st"):
            out.append((f[0], int(f[2], 16), int(f[3], 16)))
    return out


def elf_symbols(target):
    """({name: addr} of every symbol, [(addr, size, name)] of FUNC symbols by address), from
    build/<t>/<t>.elf."""
    elf = ROOT / "build" / target / f"{target}.elf"
    if not elf.exists():
        sys.exit(f"{elf} not found: split and build {target} first")
    text = subprocess.run(
        ["mips-linux-gnu-readelf", "-sW", str(elf)],
        capture_output=True, text=True, check=True,
        env={"PATH": f"{ROOT}/tools/vendor/bin:/usr/bin:/bin"},
    ).stdout
    syms, funcs = {}, {}
    for line in text.splitlines():
        f = line.split()
        if len(f) < 8 or not f[0].endswith(":") or f[3] not in ("FUNC", "OBJECT", "NOTYPE"):
            continue
        addr = int(f[1], 16)
        syms[f[7]] = addr
        if f[3] == "FUNC":
            funcs[addr] = (addr, int(f[2]), f[7])
    return syms, sorted(funcs.values())


def shared_ranges(target, load):
    """[(start, end, file)] of the stage's subsegments built from src/stage_common/."""
    rows = []
    for line in (ROOT / "config" / target / f"{target}.yaml").read_text().splitlines():
        m = SUBSEG_RE.match(line)
        if m:
            rows.append((int(m.group(2), 16), m.group(4), False))
        m = re.match(r"^\s*- \{start: (0x[0-9A-Fa-f]+), type: c, name: (\w+), dir: ../stage_common\}", line)
        if m:
            rows.append((int(m.group(1), 16), m.group(2), True))
    return [(load + a, load + rows[k + 1][0] if k + 1 < len(rows) else 1 << 32, f)
            for k, (a, f, shared) in enumerate(rows) if shared]


class Stage:
    def __init__(self, target, load, size):
        self.target, self.load, self.size = target, load, size
        self.syms, self.funcs = elf_symbols(target)
        self.chunk = (ROOT / "build" / target / "original" / f"{target}.bin").read_bytes()
        # Function asm: asm/<t>/nonmatchings/<file>/ and, for shared files, asm/<t>/stage_common/.
        self.asm = {
            p.stem: p
            for p in (ROOT / "asm" / target).rglob("*.s")
            if p.parent.parent.name in ("nonmatchings", "stage_common")
        }
        self.shared = shared_ranges(target, load)
        self.bodies = [self.body(a, s, n) for a, s, n in self.funcs]
        self.tokens = []
        for i, (a, s, n) in enumerate(self.funcs):
            nxt = self.funcs[i + 1][0] if i + 1 < len(self.funcs) else a + s
            self.tokens.append(hash((self.bodies[i], nxt - (a + s))))

    def local(self, name):
        """Address of a module-local symbol, or None (ROCK_NEO.EXE's, or not a symbol)."""
        addr = self.syms.get(name)
        if addr is not None and self.load <= addr < self.load + self.size:
            return addr
        return None

    def asm_lines(self, name):
        """Instruction and rodata lines of a function's asm file, without splat's comment."""
        out = []
        for line in self.asm[name].read_text().splitlines():
            if "*/" in line:
                out.append(line.split("*/", 1)[1].strip())
            elif line.strip().startswith((".L", "glabel", "dlabel", ".section")):
                out.append(line.strip())
        return out

    def body(self, addr, size, name):
        for lo, hi, file in self.shared:
            if lo <= addr < hi:
                # Carved already: the same source in every stage, C or not.
                return ("shared", file, name)
        if name not in self.asm:
            off = addr - self.load
            return ("raw", self.chunk[off:off + size])

        def sub(m):
            if m.group(1):
                return f".L+{int(m.group(1), 16) - addr:X}"
            return "@" if self.local(m.group(0)) is not None else m.group(0)

        return ("asm", tuple(IDENT_RE.sub(sub, t) for t in self.asm_lines(name)))

    def locals_used(self, i, j):
        """{name: addr} of module-local symbols that functions i..j-1 reference, outside
        themselves, in first-use order."""
        seen = {}
        for a, s, n in self.funcs[i:j]:
            if n not in self.asm:
                continue
            for t in self.asm_lines(n):
                if t.startswith(("glabel", "dlabel")):
                    continue
                for m in IDENT_RE.finditer(t):
                    v = self.local(m.group(0))
                    if v is not None and not (a <= v < a + s):
                        seen.setdefault(m.group(0), v)
        return seen


def common_runs(x, y, minlen):
    """Maximal common substrings (length >= minlen) of token lists x, y: [(i, j, length)]."""
    pos = {}
    for j, t in enumerate(y):
        pos.setdefault(t, []).append(j)
    prev = {}
    out = []
    for i, t in enumerate(x):
        cur = {}
        for j in pos.get(t, ()):
            cur[j] = prev.get(j - 1, 0) + 1
        for j, n in prev.items():
            if n >= minlen and cur.get(j + 1, 0) == 0:
                out.append((i - n, j - n + 1, n))
        prev = cur
    for j, n in prev.items():
        if n >= minlen:
            out.append((len(x) - n, j - n + 1, n))
    return out


def find_runs(stages, minlen):
    """Greedy shared runs: [(bytes, [(stage, first index)], length)]."""
    used = [set() for _ in stages]
    index = []
    for s in stages:
        first = {}
        for i, t in enumerate(s.tokens):
            first.setdefault(t, []).append(i)
        index.append(first)

    def occurrences(seq):
        occ = []
        for k, s in enumerate(stages):
            for i in index[k].get(seq[0], ()):
                if tuple(s.tokens[i:i + len(seq)]) == seq and not used[k].intersection(
                    range(i, i + len(seq))
                ):
                    occ.append((k, i))
                    break
        return occ

    def nbytes(seq, a, i):
        f = stages[a].funcs
        return f[i + len(seq) - 1][0] + f[i + len(seq) - 1][1] - f[i][0]

    def masked(k):
        # Used functions become unique tokens, so no new candidate spans them.
        return [("used", i) if i in used[k] else t for i, t in enumerate(stages[k].tokens)]

    runs = []
    while True:
        # Candidates: maximal pairwise common runs among the functions not yet taken.
        toks = [masked(k) for k in range(len(stages))]
        cands = {}
        for a in range(len(stages)):
            for b in range(a + 1, len(stages)):
                for i, j, n in common_runs(toks[a], toks[b], minlen):
                    cands[tuple(stages[a].tokens[i:i + n])] = (a, i)
        scored = []
        for seq, (a, i) in cands.items():
            occ = occurrences(seq)
            if len(occ) >= 2:
                scored.append((nbytes(seq, a, i) * (len(occ) - 1), seq))
        if not scored:
            return runs
        # Take candidates best first while their score still holds; a candidate that lost
        # occurrences to an earlier pick waits for the next round (its leftovers become new
        # candidates there).
        scored.sort(key=lambda c: -c[0])
        for score, seq in scored:
            occ = occurrences(seq)
            if len(occ) < 2 or nbytes(seq, *occ[0]) * (len(occ) - 1) < score:
                continue
            for k, i0 in occ:
                used[k].update(range(i0, i0 + len(seq)))
            runs.append((nbytes(seq, *occ[0]), [(stages[k], i0) for k, i0 in occ], len(seq)))


def cmd_runs(args):
    stages = [Stage(*s) for s in overlay_stages()]
    runs = sorted(find_runs(stages, args.min), key=lambda r: -r[0] * (len(r[1]) - 1))
    total = sum(b * (len(o) - 1) for b, o, n in runs)
    print(f"# {len(runs)} shared runs of {args.min}+ functions; carving all saves 0x{total:X} bytes")
    print("# saved  bytes  funcs  stages  first occurrence (stage start) [file]  other stages")
    for b, occ, n in runs[: args.top or None]:
        (s0, i0), rest = occ[0], occ[1:]
        others = " ".join(f"{s.target[3:]}:{s.funcs[i][0]:08X}" for s, i in rest)
        print(
            f"{b * (len(occ) - 1):7X} {b:6X} {n:5d} {len(occ):6d}  "
            f"{s0.target}:{s0.funcs[i0][0]:08X} ({s0.funcs[i0][2]}) [{carve_host(s0, i0)}]  {others}"
        )


def cmd_show(args):
    stages = [Stage(*s) for s in overlay_stages()]
    runs = find_runs(stages, args.min)
    for b, occ, n in runs:
        for s, i in occ:
            if s.target == args.stage and args.func in [f[2] for f in s.funcs[i:i + n]]:
                print(f"# run of {n} functions, 0x{b:X} bytes, in {len(occ)} stages")
                for s2, i2 in occ:
                    a, _, name = s2.funcs[i2]
                    last = s2.funcs[i2 + n - 1]
                    print(
                        f"{s2.target} 0x{a - s2.load:X}-0x{last[0] + last[1] - s2.load:X} "
                        f"{name}..{last[2]}"
                    )
                    print("    locals: " + " ".join(s2.locals_used(i2, i2 + n)))
                return
    sys.exit(f"{args.func} in {args.stage} isn't part of a shared run")


# --- carve: move one shared run into src/stage_common/<name>.c ---------------------------------

SUBSEG_RE = re.compile(r"^(\s*)- \[(0x[0-9A-Fa-f]+), ([.\w]+), ([\w./]+)\](.*)$")
EMPTY_FUNC_RE = re.compile(r"^void (\w+)\(void\)\n\{\n\}$")
INCLUDE_ASM_RE = re.compile(r'^INCLUDE_ASM\("[^"]*", (\w+)\);$')


def c_blocks(path):
    """A splat-scaffolding C file as (header blocks, [(function name, block text)])."""
    header, funcs = [], []
    for block in path.read_text().strip("\n").split("\n\n"):
        m = INCLUDE_ASM_RE.match(block) or EMPTY_FUNC_RE.match(block)
        if m:
            funcs.append((m.group(1), block))
        elif funcs:
            sys.exit(f"{path}: unexpected block after the functions:\n{block}")
        else:
            header.append(block)
    return header, funcs


def write_c(path, header, funcs, asm_dir, rename=lambda n: n):
    out = list(header)
    for name, block in funcs:
        new = rename(name)
        if block.startswith("INCLUDE_ASM"):
            out.append(f"INCLUDE_ASM({asm_dir}, {new});")
        else:
            out.append(block.replace(name, new))
    path.write_text("\n\n".join(out) + "\n")


def rodata_of(stage, names):
    """Addresses of the rodata symbols migrated into the given functions' asm files."""
    out = []
    for n in names:
        if n in stage.asm:
            out += [stage.syms[t.split()[1]] for t in stage.asm_lines(n) if t.startswith("dlabel")]
    return out


def data_roles(stage, i0, n):
    """[addr] of the data symbols the run funcs[i0:i0+n] uses (not its own rodata, not inside
    itself), in first-use order: the k-th entry is the same symbol's copy in every stage."""
    first, last = stage.funcs[i0], stage.funcs[i0 + n - 1]
    end = stage.funcs[i0 + n][0] if i0 + n < len(stage.funcs) else last[0] + last[1]
    run_ro = set(rodata_of(stage, [f[2] for f in stage.funcs[i0:i0 + n]]))
    return [v for v in stage.locals_used(i0, i0 + n).values()
            if v not in run_ro and not (first[0] <= v < end)]


def data_objects(occ, n):
    """Group the run's data symbols (by role, see data_roles) into objects, the same in every
    stage: two symbols are in one object when their distance apart is the same in every stage.
    Returns [object index] per role, 0 for the file's own data (the object with the most
    symbols), then the others in the first stage's address order; None when the stages
    disagree on the symbols (each stage then falls back to splitting at DATA_GAP)."""
    roles = [data_roles(s, i, n) for s, i in occ]
    if not roles or len({len(r) for r in roles}) != 1:
        return None
    k = len(roles[0])
    if k == 0:
        return []
    parent = list(range(k))

    def find(x):
        while parent[x] != x:
            x = parent[x]
        return x

    for a in range(k):
        for b in range(a + 1, k):
            if len({r[b] - r[a] for r in roles}) == 1:
                parent[find(b)] = find(a)
    groups = {}
    for a in range(k):
        groups.setdefault(find(a), []).append(a)
    ref = roles[0]
    objs = sorted(groups.values(), key=lambda g: (-len(g), min(ref[x] for x in g)))
    own, others = objs[0], sorted(objs[1:], key=lambda g: min(ref[x] for x in g))
    out = [0] * k
    for idx, g in enumerate([own] + others):
        for x in g:
            out[x] = idx
    return out


def carve_stage(stage, i0, n, name, objects=None):
    """Split one stage's yaml, C file and registry around the shared run funcs[i0:i0+n].
    `objects`: data_objects()'s grouping of the run's data, or None to split at DATA_GAP."""
    t, load = stage.target, stage.load
    first, last = stage.funcs[i0], stage.funcs[i0 + n - 1]
    a = first[0] - load
    b = (stage.funcs[i0 + n][0] if i0 + n < len(stage.funcs) else last[0] + last[1]) - load

    yaml_path = ROOT / "config" / t / f"{t}.yaml"
    lines = yaml_path.read_text().splitlines()
    subs = [(k, SUBSEG_RE.match(l)) for k, l in enumerate(lines) if SUBSEG_RE.match(l)]
    # The C subsegment holding the run, and the one after it.
    cs = [(k, m) for k, m in subs if m.group(3) == "c"]
    host = [x for x in cs if int(x[1].group(2), 16) <= a][-1]
    k_host, m_host = host
    file = m_host.group(4)
    if "/" in file:
        sys.exit(f"{t}: the run is inside {file}, not a stage file")
    indent = m_host.group(1)
    src = ROOT / "src" / t / f"{file}.c"
    header, funcs = c_blocks(src)
    names = [f[2] for f in stage.funcs[i0:i0 + n]]
    order = [f for f, _ in funcs]
    if names[0] not in order or names[-1] not in order:
        sys.exit(f"{t}: {names[0]}..{names[-1]} not all in {src}")
    j0, j1 = order.index(names[0]), order.index(names[-1]) + 1
    if order[j0:j1] != names:
        sys.exit(f"{t}: {src} doesn't list the run's functions in order")
    before, after = funcs[:j0], funcs[j1:]
    rest = f"{t}_{b:X}"

    # Rodata: each part's migrated symbols must sit in order (before < run < after).
    ro = {k: rodata_of(stage, [f for f, _ in part]) for k, part in
          (("before", before), ("run", [(x, None) for x in names]), ("after", after))}
    spans = [(min(v), max(v)) for v in ro.values() if v]
    if any(spans[x][1] >= spans[x + 1][0] for x in range(len(spans) - 1)):
        sys.exit(f"{t}: rodata of the parts interleaves; carve by hand")
    ro_sub = [x for x in subs if x[1].group(3) == ".rodata" and x[1].group(4) == file]

    new = []
    for k, line in enumerate(lines):
        if ro_sub and k == ro_sub[0][0]:
            if ro["before"]:
                new.append(line)
            if ro["run"]:
                new.append(f"{indent}- {{start: 0x{min(ro['run']) - load:X}, type: .rodata, "
                           f"name: {name}, dir: ../stage_common}}")
            if ro["after"]:
                new.append(f"{indent}- [0x{min(ro['after']) - load:X}, .rodata, {rest}]")
        elif k == k_host:
            if before:
                new.append(line)
            new.append(f"{indent}- {{start: 0x{a:X}, type: c, name: {name}, dir: ../stage_common}}"
                       f"  # shared stage code")
            if after:
                new.append(f"{indent}- [0x{b:X}, c, {rest}]")
        else:
            new.append(line)
    yaml_path.write_text("\n".join(new) + "\n")

    asm_of = lambda f: f'"asm/{t}/nonmatchings/{f}"'
    if before:
        write_c(src, header, before, asm_of(file))
    else:
        src.unlink()
    if after:
        write_c(ROOT / "src" / t / f"{rest}.c", ['#include "common.h"'], after, asm_of(rest))

    # Registry: the run's functions and the module-local symbols it uses get the shared names.
    local = stage.locals_used(i0, i0 + n)
    run_ro = set(ro["run"])
    data = sorted(v for v in local.values() if v not in run_ro and not (load + a <= v < load + b))
    cluster_of, clusters = {}, []
    if objects is not None:
        # One cluster per object (see data_objects): the same grouping in every stage.
        roles = data_roles(stage, i0, n)
        clusters = [[] for _ in range(max(objects) + 1)] if objects else []
        for v, k in zip(roles, objects):
            clusters[k].append(v)
            cluster_of[v] = k
        clusters = [sorted(c) for c in clusters]
    else:
        # Data far from the file's own block (a gap over DATA_GAP) belongs to another object,
        # which sits at a different distance in each stage: each such cluster gets its own
        # prefix (E, E2, ...) and offsets from its own first symbol.
        for v in data:
            if not clusters or v - clusters[-1][-1] > DATA_GAP:
                clusters.append([])
            clusters[-1].append(v)
            cluster_of[v] = len(clusters) - 1
    bases = {"R": min(run_ro) if run_ro else 0}
    reg = ROOT / "config" / t / "symbol_addrs.txt"
    text = reg.read_text().rstrip("\n").split("\n")
    text.append(f"// {name} (src/stage_common/{name}.c): this stage's copy, under the shared names.")
    renames = {}
    for f in stage.funcs[i0:i0 + n]:
        renames[f[2]] = f"{name}_func_{f[0] - first[0]:04X}"
        text.append(f"{renames[f[2]]} = 0x{f[0]:08X}; // type:func")
    for sym, v in sorted(local.items(), key=lambda x: x[1]):
        if sym in renames or load + a <= v < load + b:
            continue
        if sym.startswith("func_"):  # outside the run: same name in every stage (check_stages)
            continue
        if v in run_ro:  # its own rodata (migrated)
            kind, base = "R", bases["R"]
        else:  # data: its own block, or another object's (E, E2, ...)
            k = cluster_of[v]
            kind, base = ("D" if k == 0 else "E" if k == 1 else f"E{k}"), clusters[k][0]
        renames[sym] = f"{name}_{kind}_{v - base:04X}"
        text.append(f"{renames[sym]} = 0x{v:08X};")
    reg.write_text("\n".join(text) + "\n")
    return before, renames


def check_stages(occ, n):
    """Exit before anything is written if a stage's copy can't be carved automatically: a
    module-local symbol it uses already has a name, or it calls a module function outside the
    run that the stages don't all have under the same name (the shared C names it directly)."""
    calls = {}
    for s, i in occ:
        a = s.funcs[i][0]
        last = s.funcs[i + n - 1]
        b = s.funcs[i + n][0] if i + n < len(s.funcs) else last[0] + last[1]
        for sym, v in s.locals_used(i, i + n).items():
            if a <= v < b:
                continue
            if not re.match(r"^(func|D|jtbl)_[0-9A-F]{8}$", sym):
                sys.exit(f"{s.target}: {sym} already has a name; carve by hand")
            if sym.startswith("func_"):
                calls.setdefault(s.target, set()).add(sym)
    names = {frozenset(c) for c in calls.values()}
    if calls and (len(names) > 1 or len(calls) < len(occ)):
        sys.exit(f"the run calls module functions outside itself at different addresses: "
                 f"{', '.join(f'{t}: {sorted(c)}' for t, c in calls.items())}; carve by hand")
    for sym in sorted(next(iter(names))) if calls else []:
        print(f"  calls {sym} (outside the run, the same address in every stage)")


def cmd_carve(args):
    name = args.name
    shared = ROOT / "src" / "stage_common" / f"{name}.c"
    if shared.exists():
        sys.exit(f"{shared} already exists")
    stages = [Stage(*s) for s in overlay_stages()]
    runs = find_runs(stages, args.min)
    for b, occ, n in runs:
        hits = [(s, i) for s, i in occ if s.target == args.stage]
        if hits and args.func in [f[2] for f in hits[0][0].funcs[hits[0][1]:hits[0][1] + n]]:
            break
    else:
        sys.exit(f"{args.func} in {args.stage} isn't part of a shared run")
    ref, i_ref = hits[0]
    _, ref_funcs = c_blocks(ROOT / "src" / ref.target / f"{carve_host(ref, i_ref)}.c")
    by_name = dict(ref_funcs)
    run_blocks = [(f[2], by_name[f[2]]) for f in ref.funcs[i_ref:i_ref + n]]
    print(f"{name}: {n} functions, 0x{b:X} bytes, {len(occ)} stages")
    check_stages(occ, n)
    objects = data_objects(occ, n)
    if objects is None:
        print("  the stages disagree on the run's data symbols: splitting each at DATA_GAP")
    for s, i in occ:
        _, renames = carve_stage(s, i, n, name, objects)
        if s is ref:
            ref_renames = renames
        print(f"  {s.target} 0x{s.funcs[i][0] - s.load:X}: {len(renames)} names")
    shared.parent.mkdir(exist_ok=True)
    names = [s.target for s, _ in occ]
    about = textwrap.wrap(
        f"Shared stage code, linked into {len(occ)} stages: {', '.join(names[:-1])} and "
        f"{names[-1]}. Each stage compiles this file against its own copy of the assembly "
        "(TARGET_ASM, set by tools/cc.sh); the names are the same in every stage's registry.",
        96, initial_indent="// ", subsequent_indent="// ")
    header = [
        '#include "common.h"',
        "\n".join(about) + f'\n#define ASM_DIR TARGET_ASM "/stage_common/{name}"',
    ]
    write_c(shared, header, run_blocks, "ASM_DIR", lambda f: ref_renames[f])
    print(f"wrote {shared.relative_to(ROOT)}; now: for each stage, ./tools/rebuild.sh <stage>")


def carve_host(stage, i0):
    """Name of the C subsegment (file) holding funcs[i0] in the stage's yaml."""
    a = stage.funcs[i0][0]
    for lo, hi, file in stage.shared:
        if lo <= a < hi:
            return f"stage_common/{file}"
    host = None
    for line in (ROOT / "config" / stage.target / f"{stage.target}.yaml").read_text().splitlines():
        m = SUBSEG_RE.match(line)
        if m and m.group(3) == "c" and stage.load + int(m.group(2), 16) <= a:
            host = m.group(4)
    return host


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("runs")
    r.add_argument("--min", type=int, default=3, help="shortest run, in functions (default 3)")
    r.add_argument("--top", type=int, default=0, help="print only the first N runs")
    s = sub.add_parser("show")
    s.add_argument("stage")
    s.add_argument("func")
    s.add_argument("--min", type=int, default=3)
    c = sub.add_parser("carve")
    c.add_argument("name", help="the shared file's name, e.g. stcom01")
    c.add_argument("stage")
    c.add_argument("func", help="any function of the run in that stage")
    c.add_argument("--min", type=int, default=3)
    args = p.parse_args()
    {"runs": cmd_runs, "show": cmd_show, "carve": cmd_carve}[args.cmd](args)


if __name__ == "__main__":
    main()
