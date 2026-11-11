#!/usr/bin/env python3
"""Extract every code overlay from the disc's chunk archives and group identical ones.

Usage:  tools/extract_overlays.py [--out disc/overlays] [--tsv FILE]

Scans each CDDATA/DAT/*.BIN archive for chunk headers (see notes/disc.md, "Overlay chunk format")
at every 0x800 boundary, and keeps the code chunks: type 0 with a `progbin\\*.bin` name. All code
in the archives is in these chunks; no other chunk type contains a `jr ra`.

Each code chunk's contents (header stripped, exactly `size` bytes) are written to
OUT/<ARCHIVE>.bin, e.g. disc/overlays/ST08.BIN holds ST08.BIN's `R3_ST08.BIN`. OUT must stay
under disc/ (gitignored game data).

Prints one row per chunk: archive, chunk name, load address, size, `jr ra` count, SHA-1, and the
group it belongs to. Chunks with identical contents share a group; the group is named after its
first archive. For chunks of equal size but different contents, it also prints how many 32-bit
words differ. --tsv writes the same rows tab-separated.
"""

import argparse
import hashlib
import struct
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DAT = ROOT / "disc/extracted/CDDATA/DAT"
SECTOR = 0x800
JR_RA = 0x03E00008


def code_chunks(path):
    """Yield (offset, load address, chunk name, contents) for each code chunk in an archive."""
    data = path.read_bytes()
    for off in range(0, len(data) - SECTOR + 1, SECTOR):
        raw = data[off + 0x40 : off + SECTOR].split(b"\0")[0]
        if not raw.startswith(b"..\\"):
            continue
        name = raw.decode("latin-1")
        kind, size, _sectors, load = struct.unpack_from("<4I", data, off)
        if kind != 0 or "progbin" not in name.lower() or not name.lower().endswith(".bin"):
            continue
        body = data[off + SECTOR : off + SECTOR + size]
        if len(body) != size:
            sys.exit(f"{path.name}: chunk {name} at {off:#x} runs past the end of the file")
        yield off, load, name.split("\\")[-1], body


def count_jr_ra(body):
    words = struct.unpack_from(f"<{len(body) // 4}I", body)
    return sum(1 for w in words if w == JR_RA)


def differing_words(a, b):
    n = len(a) // 4
    wa = struct.unpack_from(f"<{n}I", a)
    wb = struct.unpack_from(f"<{n}I", b)
    return sum(1 for x, y in zip(wa, wb) if x != y)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--out", default="disc/overlays", help="output folder, under disc/")
    ap.add_argument("--tsv", help="also write the table to this file")
    args = ap.parse_args()

    out = (ROOT / args.out).resolve()
    if (ROOT / "disc").resolve() not in out.parents:
        sys.exit("--out must be inside disc/ (game data is never written to tracked folders)")
    if not DAT.is_dir():
        sys.exit(f"missing {DAT.relative_to(ROOT)}; extract the disc first")
    out.mkdir(parents=True, exist_ok=True)

    rows = []
    for archive in sorted(DAT.glob("*.BIN")):
        chunks = list(code_chunks(archive))
        if len(chunks) > 1:
            sys.exit(f"{archive.name}: {len(chunks)} code chunks; expected at most one")
        for off, load, name, body in chunks:
            (out / archive.name).write_bytes(body)
            rows.append(
                {
                    "archive": archive.name,
                    "offset": off,
                    "chunk": name,
                    "load": load,
                    "size": len(body),
                    "jr_ra": count_jr_ra(body),
                    "sha1": hashlib.sha1(body).hexdigest(),
                    "body": body,
                }
            )

    groups = defaultdict(list)
    for r in rows:
        groups[r["sha1"]].append(r)
    for members in groups.values():
        for r in members:
            r["group"] = members[0]["archive"]
            r["copies"] = len(members)

    header = ["archive", "chunk", "load", "size", "jr_ra", "sha1", "group"]
    lines = ["\t".join(header)]
    for r in rows:
        lines.append(
            "\t".join(
                [
                    r["archive"],
                    r["chunk"],
                    f"{r['load']:#010x}",
                    f"{r['size']:#x}",
                    str(r["jr_ra"]),
                    r["sha1"],
                    r["group"] if r["copies"] > 1 else "-",
                ]
            )
        )

    print(f"{'archive':<13} {'chunk':<14} {'load':<10} {'size':>8} {'jr ra':>5}  {'sha1':<40}  group")
    for r in rows:
        group = r["group"] if r["copies"] > 1 else ""
        print(
            f"{r['archive']:<13} {r['chunk']:<14} {r['load']:#010x} {r['size']:>#8x} "
            f"{r['jr_ra']:>5}  {r['sha1']}  {group}"
        )

    unique = list(groups.values())
    total = sum(r["jr_ra"] for r in rows)
    unique_total = sum(m[0]["jr_ra"] for m in unique)
    print(
        f"\n{len(rows)} code chunks, {len(unique)} distinct; "
        f"{total} jr ra in all, {unique_total} in distinct chunks"
    )
    for members in unique:
        if len(members) > 1:
            print(f"  identical: {', '.join(m['archive'] for m in members)}")

    by_size = defaultdict(list)
    for members in unique:
        by_size[members[0]["size"]].append(members[0])
    near = [(s, m) for s, m in by_size.items() if len(m) > 1]
    if near:
        print("same size, different contents:")
        for size, members in near:
            for i, a in enumerate(members):
                for b in members[i + 1 :]:
                    n = differing_words(a["body"], b["body"])
                    print(f"  {a['archive']} / {b['archive']}: {n} of {size // 4} words differ")

    if args.tsv:
        Path(args.tsv).write_text("\n".join(lines) + "\n")
        print(f"wrote {args.tsv}")
    print(f"extracted to {out.relative_to(ROOT)}/")


if __name__ == "__main__":
    main()
