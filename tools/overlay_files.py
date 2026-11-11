#!/usr/bin/env python3
"""Split the code overlays into proposed source files.

Usage:  tools/overlay_files.py [--overlay ST03]      (prints the split; function_list.py imports it)

Overlays have no symbols and no yaml yet, so their files are inferred (notes/overlays.md,
"Source files"):

- **source**: located by Capcom's own source (TCRF): CONFIRMED below.
- **shared**: a common file. Each function gets the set of other overlays holding its shape
  (dupe_scan.py's shape key); generic shapes (in more than GENERIC programs, e.g. the 0x3C-byte
  `StXX_*_move` dispatcher) and empty functions take their neighbour's set. Each overlay is cut
  where the set changes. Segments of 3+ functions and 0x200+ bytes with a non-empty set are joined
  across overlays when they hold the same shapes; a group found in 2+ overlays is a common file,
  named after its first occurrence (`shared_ST03_80107BC0` in every overlay that has it). One or two
  unmatched functions between two pieces of the same common file are its variants. Its edges are
  boundaries; it may be several files that are always linked together.
- **unknown**: everything else, one region per stretch between the others (`ST03_80100524`),
  probably several files each.
"""

import argparse
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import dupe_scan  # noqa: E402

GENERIC = 20
MIN_FUNCS, MIN_BYTES = 3, 0x200
EXECUTABLES = ("SLUS", "ROCK_NEO")
# (overlay, first function, end, file): functions matched to Capcom's source fragments.
CONFIRMED = [
    ("ST1A", 0x8012B8E4, 0x8012C2EC, "eve19"),     # both edges: all 12 functions of eve19.c
    ("ST1E", 0x80101554, 0x80101AF0, "EM09_49"),   # end only: the fragment starts mid-file
]


def assign(rows):
    """{(overlay, address): (file, confidence, programs sharing the file)} for overlay functions."""
    shape_progs = defaultdict(set)
    for r in rows:
        shape_progs[r["shape"]].add(r["prog"])
    seqs = defaultdict(list)
    for r in rows:
        if r["prog"] not in EXECUTABLES:
            seqs[r["prog"]].append(r)

    # Segments of equal sharing set, per overlay.
    segs = {}
    for prog, seq in seqs.items():
        tags = []
        for r in seq:
            s = shape_progs[r["shape"]] - {prog}
            neutral = len(s) > GENERIC or r["size"] <= 8
            tags.append(None if neutral else frozenset(s - set(EXECUTABLES)))
        last = next((t for t in tags if t is not None), frozenset())
        out = []
        for r, t in zip(seq, tags):
            t = last if t is None else t
            last = t
            if out and out[-1]["tag"] == t:
                out[-1]["funcs"].append(r)
            else:
                out.append({"tag": t, "funcs": [r]})
        segs[prog] = out

    # Common files: qualifying segments (3+ functions, 0x200+ bytes, shared), joined across
    # overlays when they hold the same function shapes (one file has the same functions
    # everywhere; two files shared by the same overlays don't).
    qual = [(prog, seg) for prog, out in segs.items() for seg in out
            if seg["tag"] and len(seg["funcs"]) >= MIN_FUNCS
            and sum(r["size"] for r in seg["funcs"]) >= MIN_BYTES]
    parent = list(range(len(qual)))

    def find(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i

    by_shape = {}
    for i, (prog, seg) in enumerate(qual):
        for r in seg["funcs"]:
            if len(shape_progs[r["shape"]]) <= GENERIC and r["size"] > 8:
                j = by_shape.setdefault(r["shape"], i)
                parent[find(i)] = find(j)
    groups = defaultdict(list)
    for i, item in enumerate(qual):
        groups[find(i)].append(item)
    common = {}
    for found in groups.values():
        progs = {p for p, _ in found}
        if len(progs) < 2:
            continue
        p0, s0 = min(found, key=lambda x: (x[0], x[1]["funcs"][0]["addr"]))
        name = f"shared_{p0}_{s0['funcs'][0]['addr']:08X}"
        for _, seg in found:
            common[id(seg)] = (name, len(progs))

    result = {}
    for prog, out in segs.items():
        for seg in out:
            file, n = common.get(id(seg), (None, 1))
            for r in seg["funcs"]:
                result[(prog, r["addr"])] = [file, "shared" if file else "unknown", n]
    for prog, lo, hi, file in CONFIRMED:
        for r in seqs.get(prog, []):
            if lo <= r["addr"] < hi:
                result[(prog, r["addr"])] = [file, "source", 1]
    # One or two unmatched functions between two pieces of the same common file: variants of it.
    for prog, seq in seqs.items():
        cells = [result[(prog, r["addr"])] for r in seq]
        i = 0
        while i < len(cells):
            if cells[i][1] != "unknown":
                i += 1
                continue
            j = i
            while j < len(cells) and cells[j][1] == "unknown":
                j += 1
            if 0 < i and j < len(cells) and j - i <= 2 and cells[i - 1][1] == "shared" \
                    and cells[i - 1][0] == cells[j][0]:
                for k in range(i, j):
                    cells[k][:] = cells[i - 1]
            i = j
    # Unknown regions: one per contiguous stretch, named after its first function.
    for prog, seq in seqs.items():
        name = None
        for r in seq:
            cell = result[(prog, r["addr"])]
            if cell[1] == "unknown":
                name = name or f"{prog}_{r['addr']:08X}"
                cell[0] = name
            else:
                name = None
    return {k: tuple(v) for k, v in result.items()}


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--overlay", help="only this overlay (e.g. ST03)")
    args = ap.parse_args()
    rows = dupe_scan.collect()
    files = assign(rows)
    cur = None
    for r in rows:
        if r["prog"] in EXECUTABLES or (args.overlay and r["prog"] != args.overlay):
            continue
        file, conf, n = files[(r["prog"], r["addr"])]
        if (r["prog"], file) != cur:
            if cur:
                print(f"{cur[0]:8} {start:08X}-{end:08X} {count:4}f {cur[1]:24} {kind}"
                      + (f" ({shared} overlays)" if kind == "shared" else ""))
            cur, start, count, kind, shared = (r["prog"], file), r["addr"], 0, conf, n
        end, count = r["addr"] + r["size"], count + 1
    if cur:
        print(f"{cur[0]:8} {start:08X}-{end:08X} {count:4}f {cur[1]:24} {kind}"
              + (f" ({shared} overlays)" if kind == "shared" else ""))


if __name__ == "__main__":
    main()
