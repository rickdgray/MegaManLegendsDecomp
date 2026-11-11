#!/usr/bin/env python3
"""Per-function Score (estimated difficulty) and Depth (call order) for every Capcom function.

Usage:  tools/func_metrics.py [--top N]      (prints a summary; function_list.py imports it)

Score: a weighted count from the function's instructions, roughly "instructions, plus a cost for
each thing that makes matching harder":

    instructions + 4 per conditional branch + 12 per loop (backward branch)
    + 15 per jump table (`jr` on a register other than `ra`) + 6 per indirect call (`jalr`)
    + 2 per direct call + 3 per GTE instruction (cop2, lwc2, swc2) + 2 per mult/div
    + 20 if it reads or writes small data through `$gp` and that data isn't in C yet (ROCK_NEO's
      is, see rock_neo_files.md, "Small data in C"; overlays: all, untested)

The weights are a first guess, checked only against the functions done so far (parked ones score
higher than matched ones; --top prints the comparison).

Depth: the longest chain of calls into Capcom functions that have no C yet. 0 = everything it calls
already has C, or it calls nothing (PsyQ and hand-written assembly don't count). Functions that
call each other in a cycle share one depth. Overlays' calls into ROCK_NEO count (ROCK_NEO's
addresses are the same everywhere); indirect calls (`jalr`, tables) are invisible. Functions that
already have C get no depth. Doing functions in increasing depth gives each one its callees'
prototypes first.
"""

import argparse
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dupe_scan  # noqa: E402
import function_list  # noqa: E402
import progress  # noqa: E402

JR_RA = 0x03E00008
W_BRANCH, W_LOOP, W_JTBL, W_JALR, W_CALL, W_GTE, W_MULDIV, W_GP = 4, 12, 15, 6, 2, 3, 2, 20


def counts(ws, base, f, e):
    """Instruction features of ws[f:e], and its direct call targets."""
    c = defaultdict(int)
    calls = []
    for k in range(f, e):
        w = ws[k]
        pc = base + k * 4
        op, rs, rt, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 63
        if w == 0:
            continue
        c["insns"] += 1
        if op in (4, 5, 6, 7) or (op == 1 and rt in (0, 1, 16, 17)):
            c["branch"] += 1
            if dupe_scan.find_dupes.simm16(w) < 0:
                c["loop"] += 1
        elif op == 3:
            c["call"] += 1
            calls.append(0x80000000 | ((w & 0x3FFFFFF) << 2))
        elif op == 0 and fn == 8 and w != JR_RA:
            c["jtbl"] += 1
        elif op == 0 and fn == 9:
            c["jalr"] += 1
        elif op == 0 and fn in (24, 25, 26, 27):
            c["muldiv"] += 1
        elif op in (0x12, 0x32, 0x3A):
            c["gte"] += 1
        if rs == 28 and op in (8, 9, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B):
            c["gp"] = 1
        del pc
    return c, calls


def score(c):
    return (c["insns"] + W_BRANCH * c["branch"] + W_LOOP * c["loop"] + W_JTBL * c["jtbl"]
            + W_JALR * c["jalr"] + W_CALL * c["call"] + W_GTE * c["gte"]
            + W_MULDIV * c["muldiv"] + W_GP * c["gp"])


def metrics():
    """{(program, address): {"score", "depth", "done", ...}} for every Capcom function."""
    info = {}
    edges = {}
    for prog, ws, base, funcs, _local in dupe_scan.programs():
        target = function_list.TARGET_OF.get(prog)
        subs = progress.subsegments(target) if target else []
        attempts = function_list.parked(target) if target else set()
        starts = {base + f * 4 for f, _, _, _ in funcs}
        for f, e, name, matched in funcs:
            addr = base + f * 4
            hand = False
            if target:
                sub = next((s for s in subs if s[0] <= addr < s[1]), None)
                hand = sub is None or sub[2].startswith(("psyq/", "asm_"))
            c, calls = counts(ws, base, f, e)
            if target:
                c["gp"] = 0  # its file defines its small data in C (or it's in the common pool)
            info[(prog, addr)] = {"score": score(c), "features": c, "hand": hand,
                                  "done": hand or matched or name in attempts}
            out = []
            for t in calls:
                if t in starts:
                    out.append((prog, t))
                elif prog not in ("SLUS", "ROCK_NEO") and t < dupe_scan.SHARED_END:
                    out.append(("ROCK_NEO", t))
            edges[(prog, addr)] = out
    pending = {k for k, v in info.items() if not v["done"]}
    graph = {k: [t for t in edges[k] if t in pending] for k in pending}
    for k, d in depths(graph).items():
        info[k]["depth"] = d
    return info


def depths(graph):
    """Longest path to a sink, with strongly connected components collapsed (iterative Tarjan)."""
    index, low, comp = {}, {}, {}
    stack, on_stack, comps = [], set(), []
    counter = 0
    for root in graph:
        if root in index:
            continue
        work = [(root, iter(graph[root]))]
        index[root] = low[root] = counter
        counter += 1
        stack.append(root)
        on_stack.add(root)
        while work:
            v, it = work[-1]
            advanced = False
            for w in it:
                if w not in index:
                    index[w] = low[w] = counter
                    counter += 1
                    stack.append(w)
                    on_stack.add(w)
                    work.append((w, iter(graph[w])))
                    advanced = True
                    break
                if w in on_stack:
                    low[v] = min(low[v], index[w])
            if advanced:
                continue
            work.pop()
            if work:
                low[work[-1][0]] = min(low[work[-1][0]], low[v])
            if low[v] == index[v]:
                members = []
                while True:
                    w = stack.pop()
                    on_stack.discard(w)
                    comp[w] = len(comps)
                    members.append(w)
                    if w == v:
                        break
                comps.append(members)
    # Tarjan emits components callees-first, so one pass in order suffices.
    cdepth = []
    for i, members in enumerate(comps):
        d = 0
        for v in members:
            for w in graph[v]:
                if comp[w] != i:
                    d = max(d, cdepth[comp[w]] + 1)
        cdepth.append(d)
    return {v: cdepth[comp[v]] for v in graph}


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--top", type=int, default=0, help="list the N highest-scoring pending functions")
    args = ap.parse_args()
    info = metrics()
    rows = [v for v in info.values() if not v["hand"]]
    pending = [v for v in rows if not v["done"]]
    by_depth = defaultdict(int)
    for v in pending:
        by_depth[v["depth"]] += 1
    print(f"pending functions: {len(pending)}; by depth: "
          + ", ".join(f"{d}: {n}" for d, n in sorted(by_depth.items())))
    s = sorted(v["score"] for v in pending)
    q = lambda p: s[min(len(s) - 1, int(p * len(s)))]
    print(f"pending scores: median {q(0.5)}, 90th percentile {q(0.9)}, max {s[-1]}")
    # Check against what was done: parked (decompiled, not matched) vs matched.
    for target, prog in (("slus_006.03", "SLUS"), ("rock_neo.exe", "ROCK_NEO")):
        names = function_list.parked(target)
        for k, v in info.items():
            if k[0] == prog:
                v["parked"] = False
        for p, ws, base, funcs, _ in dupe_scan.programs():
            if p != prog:
                continue
            for f, e, name, matched in funcs:
                info[(p, base + f * 4)]["parked"] = name in names
    done = [v for v in rows if v["done"] and not v["hand"]]
    m = sorted(v["score"] for v in done if not v.get("parked"))
    pk = sorted(v["score"] for v in done if v.get("parked"))
    med = lambda x: x[len(x) // 2] if x else 0
    print(f"done so far: matched {len(m)} (median score {med(m)}), parked {len(pk)} (median {med(pk)})")
    if args.top:
        for k, v in sorted(info.items(), key=lambda kv: -kv[1]["score"])[: args.top]:
            print(f"  {k[0]:9} {k[1]:08X} score {v['score']:5} depth {v.get('depth', '-')}")


if __name__ == "__main__":
    main()
