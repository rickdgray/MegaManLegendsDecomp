#!/usr/bin/env python3
"""Progress: how much of the game's Capcom code is reviewed, from functions.csv.

Usage:  tools/progress.py [target ...] [--svg FILE]

Nearly every function matches, so matching is no longer the measure: the C still has to be cleaned
up and read by the owner. A function counts as:
- done: it matches and the owner has reviewed it (functions.csv's Reviewed is Yes);
- matched: it matches but is unreviewed, or its C changed since the review (Reviewed Changed);
- not matched: still assembly, or parked.
Everything is counted in bytes (functions.csv's Size). The shared stage code (Program
stage_common) counts once, as functions.csv lists it.

Prints one line per program (each target, and stage_common) and a total. With targets named, prints
a line per source file of each instead. Without targets, also writes the treemap (default
progress.svg, for the README): one rectangle per program, holding one per source file sized by its
bytes, each split into its done, matched and not-matched shares.

Reads functions.csv only (tools/function_list.py writes it; rebuild.sh runs both).
"""

import argparse
import csv
import sys
from collections import defaultdict
from pathlib import Path
from xml.sax.saxutils import escape

ROOT = Path(__file__).resolve().parent.parent
STATES = ("done", "matched", "todo")
LABELS = {"done": "reviewed", "matched": "matched, not reviewed", "todo": "not matched"}
COLORS = {"done": "#3fb950", "matched": "#d29922", "todo": "#da3633"}
BACKGROUND, BORDER, TEXT, MUTED = "#0d1117", "#30363d", "#e6edf3", "#8b949e"
WIDTH, HEIGHT, HEADER = 1000, 600, 56


def state(row):
    if row["Matched"] != "Yes":
        return "todo"
    return "done" if row["Reviewed"] == "Yes" else "matched"


def load(path):
    """{program: {file: {state: bytes}}}, in functions.csv's order."""
    progs = {}
    with open(path, newline="") as fh:
        for row in csv.DictReader(fh):
            files = progs.setdefault(row["Program"], {})
            files.setdefault(row["File"], defaultdict(int))[state(row)] += int(row["Size"])
    return progs


def total(counts):
    out = defaultdict(int)
    for c in counts:
        for k, v in c.items():
            out[k] += v
    return out


def line(label, c):
    n = sum(c.values())
    pct = lambda k: 100.0 * c[k] / n if n else 0.0
    return (f"  {label:22} {c['done']:>8}/{n:<8} {pct('done'):6.2f}% reviewed   "
            f"{pct('matched'):6.2f}% matched, not reviewed   {pct('todo'):6.2f}% not matched")


# Squarified treemap (Bruls, Huizing and van Wijk): lay out the items along the shorter side,
# a row at a time, adding items to the row while that improves its worst aspect ratio.
def squarify(items, x, y, w, h):
    """[(key, x, y, w, h)] for items [(key, size)], sizes descending, filling the rectangle."""
    items = [(k, s) for k, s in items if s > 0]
    total_size = sum(s for _, s in items)
    if not items or w <= 0 or h <= 0:
        return []
    scale = w * h / total_size
    areas = [(k, s * scale) for k, s in items]
    out = []
    while areas:
        side = min(w, h)
        row, rest = [areas[0]], areas[1:]

        def worst(r):
            s = sum(a for _, a in r)
            return max(max(side * side * a / (s * s), s * s / (side * side * a)) for _, a in r)

        while rest and worst(row + [rest[0]]) <= worst(row):
            row.append(rest.pop(0))
        s = sum(a for _, a in row)
        thick = s / side
        pos = 0.0
        for k, a in row:
            length = a / thick
            if w >= h:      # a column on the left
                out.append((k, x, y + pos, thick, length))
            else:           # a row along the top
                out.append((k, x + pos, y, length, thick))
            pos += length
        if w >= h:
            x, w = x + thick, w - thick
        else:
            y, h = y + thick, h - thick
        areas = rest
    return out


def svg(progs, path):
    out = []
    add = out.append
    everything = total(c for files in progs.values() for c in files.values())
    n = sum(everything.values())
    add(f'<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{HEIGHT}" '
        f'viewBox="0 0 {WIDTH} {HEIGHT}" font-family="-apple-system, Segoe UI, Helvetica, Arial, sans-serif">')
    add(f'<rect width="{WIDTH}" height="{HEIGHT}" fill="{BACKGROUND}"/>')
    add(f'<text x="12" y="24" font-size="16" font-weight="600" fill="{TEXT}">Mega Man Legends: '
        f'{100.0 * everything["done"] / n:.1f}% reviewed</text>')
    lx = 12
    for k in STATES:
        label = f"{LABELS[k]} {100.0 * everything[k] / n:.1f}%"
        add(f'<rect x="{lx}" y="36" width="10" height="10" fill="{COLORS[k]}"/>')
        add(f'<text x="{lx + 14}" y="45" font-size="11" fill="{MUTED}">{escape(label)}</text>')
        lx += 22 + 6.2 * len(label)
    add(f'<text x="{WIDTH - 12}" y="45" font-size="11" fill="{MUTED}" text-anchor="end">'
        f'area: bytes of Capcom code, one block per source file</text>')

    sizes = sorted(((p, sum(sum(c.values()) for c in files.values())) for p, files in progs.items()),
                   key=lambda t: -t[1])
    for prog, px, py, pw, ph in squarify(sizes, 1, HEADER, WIDTH - 2, HEIGHT - HEADER - 1):
        files = progs[prog]
        fsizes = sorted(((f, sum(c.values())) for f, c in files.items()), key=lambda t: -t[1])
        for file, fx, fy, fw, fh in squarify(fsizes, px + 1, py + 1, pw - 2, ph - 2):
            c = files[file]
            fn = sum(c.values())
            tip = (f"{prog} {file}: {fn} bytes, " + ", ".join(
                f"{100.0 * c[k] / fn:.0f}% {LABELS[k]}" for k in STATES if c[k]))
            add(f'<g><title>{escape(tip)}</title>')
            # The file's shares, side by side along its longer edge.
            pos = 0.0
            for k in STATES:
                if not c[k]:
                    continue
                part = c[k] / fn
                if fw >= fh:
                    add(f'<rect x="{fx + pos * fw:.1f}" y="{fy:.1f}" width="{part * fw:.1f}" '
                        f'height="{fh:.1f}" fill="{COLORS[k]}"/>')
                else:
                    add(f'<rect x="{fx:.1f}" y="{fy + pos * fh:.1f}" width="{fw:.1f}" '
                        f'height="{part * fh:.1f}" fill="{COLORS[k]}"/>')
                pos += part
            add(f'<rect x="{fx:.1f}" y="{fy:.1f}" width="{fw:.1f}" height="{fh:.1f}" fill="none" '
                f'stroke="{BACKGROUND}" stroke-width="0.6"/></g>')
        add(f'<rect x="{px:.1f}" y="{py:.1f}" width="{pw:.1f}" height="{ph:.1f}" fill="none" '
            f'stroke="{BACKGROUND}" stroke-width="2"/>')
        # The program's name, where it fits.
        if pw > 7 * len(prog) + 10 and ph > 18:
            add(f'<text x="{px + 5:.1f}" y="{py + 14:.1f}" font-size="11" font-weight="600" '
                f'fill="{TEXT}" stroke="{BACKGROUND}" stroke-width="3" paint-order="stroke">'
                f'{escape(prog)}</text>')
    add("</svg>")
    Path(path).write_text("\n".join(out) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("targets", nargs="*", help="programs to list per source file (functions.csv's Program)")
    ap.add_argument("--csv", default=str(ROOT / "functions.csv"), help="input (default: functions.csv)")
    ap.add_argument("--svg", default=str(ROOT / "progress.svg"), help="treemap (default: progress.svg)")
    args = ap.parse_args()
    if not Path(args.csv).exists():
        sys.exit(f"{args.csv} not found: run tools/function_list.py (needs every target built)")
    progs = load(args.csv)

    if args.targets:
        for t in args.targets:
            if t not in progs:
                sys.exit(f"{t!r} isn't a Program in {args.csv}: one of {', '.join(progs)}")
            print(f"\n{t}")
            print(line("all", total(progs[t].values())))
            for file, c in sorted(progs[t].items(), key=lambda fc: (fc[1]["done"] / sum(fc[1].values()), fc[0])):
                print(line(file, c))
        return

    for prog, files in progs.items():
        print(line(prog, total(files.values())))
    print(line("all", total(c for files in progs.values() for c in files.values())))
    svg(progs, args.svg)
    print(f"wrote {Path(args.svg).name}")


if __name__ == "__main__":
    main()
