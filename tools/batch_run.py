#!/usr/bin/env python3
"""Decompile a C file's remaining INCLUDE_ASM functions in unattended batches.

Usage:
    tools/batch_run.py rock_neo.exe src/rock_neo.exe/cd.c [--batch 6] [--model sonnet]
                       [--cap 15] [--max-batches 0] [--dry-run]

Each batch: pick the next functions (smallest first; skipping parked ones and ones a previous batch
failed on), snapshot the files an agent can change, run Claude Code headless in a fresh session,
then build BOTH targets. If both MATCH, the batch's changes stay in the working tree and a patch of
them is saved in the log folder; otherwise the snapshot is restored and its functions are recorded
as failed. Stops when nothing is left, when the cost cap (USD) is reached, after two failed batches
in a row, or after --max-batches. Logs go to logs/batch_<timestamp>/.

The runner never runs git: you review the working tree (and the per-batch patches) and commit
yourself. Start from a clean tree so the changes are easy to review.
"""

import argparse
import datetime
import json
import re
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TARGETS = ["slus_006.03", "rock_neo.exe"]
STATE = ROOT / "logs" / "batch_state.json"
# Everything an agent may change; snapshotted before each batch and restored if it fails.
TRACKED = ["src", "include", "notes", "symbol_addrs_slus_006.03.txt", "symbol_addrs_rock_neo.exe.txt",
           "slus_006.03.yaml", "rock_neo.exe.yaml", "CLAUDE.md", "renames.txt"]

PROMPT = """Decompile these functions in `{cfile}`, in this order: {funcs}.
Follow `CLAUDE.md`. Search `notes/` for each function's address and the globals it touches;
`notes/rock_neo.md` and `notes/rock_neo_files.md` describe this executable. Shared declarations
are in `include/` (e.g. `include/rock_neo.exe/sound.h` has SOUND_WORK, whose fields are mostly still
unkXX: propose field names in renames.txt as their uses become clear).
Don't work on any other function. Park anything that doesn't match within its budget, as
`CLAUDE.md` describes. Append name proposals to `renames.txt` in the repo root (don't apply them).
Don't run git commands. Finish with the usual summary."""


def run(cmd, **kw):
    return subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, **kw)


def remaining(cfile):
    """INCLUDE_ASM functions in file order, excluding those inside a NON_MATCHING block."""
    funcs, in_nm = [], False
    for line in (ROOT / cfile).read_text().splitlines():
        s = line.strip()
        if s.startswith("#ifdef NON_MATCHING"):
            in_nm = True
        elif s.startswith("#endif") and in_nm:
            in_nm = False
        m = re.match(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\);', s)
        if m and not in_nm:
            funcs.append((m.group(2), m.group(1)))
    return funcs

def parked_names(cfile):
    """Functions whose INCLUDE_ASM sits inside a NON_MATCHING block (i.e. parked)."""
    names, in_nm = set(), False
    for line in (ROOT / cfile).read_text().splitlines():
        s = line.strip()
        if s.startswith("#ifdef NON_MATCHING"):
            in_nm = True
        elif s.startswith("#endif") and in_nm:
            in_nm = False
        m = re.match(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\);', s)
        if m and in_nm:
            names.add(m.group(2))
    return names

def size_of(asm_dir, name):
    """Function size in bytes, from splat's `nonmatching NAME, 0xSIZE` line (else count instructions)."""
    path = ROOT / asm_dir / f"{name}.s"
    if not path.exists():
        return 1 << 30
    text = path.read_text()
    m = re.search(rf"nonmatching\s+{re.escape(name)},\s*(0x[0-9A-Fa-f]+)", text)
    if m:
        return int(m.group(1), 16)
    return 4 * len(re.findall(r"^\s*/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/", text, re.M))


def build_ok():
    """Build every target; True only if all print MATCH."""
    results = {}
    for t in TARGETS:
        r = run(["./tools/build.sh", t])
        results[t] = "MATCH" in r.stdout and "MISMATCH" not in r.stdout
    return all(results.values()), results


def snapshot(dest):
    """Copy the agent-changeable files to dest."""
    if dest.exists():
        shutil.rmtree(dest)
    dest.mkdir(parents=True)
    for item in TRACKED:
        src = ROOT / item
        if src.is_dir():
            shutil.copytree(src, dest / item)
        elif src.exists():
            shutil.copy2(src, dest / item)


def restore(snap):
    """Put the snapshot back, removing anything the batch added."""
    for item in TRACKED:
        live, saved = ROOT / item, snap / item
        if live.is_dir():
            shutil.rmtree(live)
        elif live.exists():
            live.unlink()
        if saved.is_dir():
            shutil.copytree(saved, live)
        elif saved.exists():
            shutil.copy2(saved, live)


def patch(snap, out):
    """Unified diff of the batch's changes (snapshot -> working tree)."""
    chunks = []
    for item in TRACKED:
        r = subprocess.run(["diff", "-ruN", str(snap / item), str(ROOT / item)], capture_output=True, text=True)
        chunks.append(r.stdout.replace(str(snap) + "/", "a/").replace(str(ROOT) + "/", "b/"))
    out.write_text("".join(chunks))


def load_state():
    return json.loads(STATE.read_text()) if STATE.exists() else {"failed": []}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target")
    ap.add_argument("cfile", help="C file to work through, e.g. src/rock_neo.exe/cd.c")
    ap.add_argument("--batch", type=int, default=6, help="functions per batch")
    ap.add_argument("--model", default="sonnet")
    ap.add_argument("--cap", type=float, default=15.0, help="stop once total cost reaches this (USD)")
    ap.add_argument("--max-batches", type=int, default=0, help="0 = no limit")
    ap.add_argument("--dry-run", action="store_true", help="show the batches, run nothing")
    args = ap.parse_args()

    if not args.dry_run:
        r = run(["git", "status", "--porcelain"])     # read-only check
        if r.stdout.strip():
            print("warning: the working tree has uncommitted changes; they'll be mixed into the batch "
                  "results (and restored with a failed batch's snapshot, not lost)", flush=True)

    state = load_state()
    logdir = ROOT / "logs" / f"batch_{datetime.datetime.now():%Y%m%d_%H%M%S}"
    logdir.mkdir(parents=True, exist_ok=True)
    total_cost, failures_in_row, batch_no = 0.0, 0, 0
    summary = []

    while True:
        todo = [(n, d) for n, d in remaining(args.cfile) if n not in state["failed"]]
        if not todo:
            summary.append("nothing left to do")
            break
        todo.sort(key=lambda nd: size_of(nd[1], nd[0]))
        batch = [n for n, _ in todo[:args.batch]]
        batch_no += 1
        prompt = PROMPT.format(cfile=args.cfile, funcs=", ".join(f"`{n}`" for n in batch))

        if args.dry_run:
            print(f"batch {batch_no}: {', '.join(batch)}")
            state["failed"].extend(batch)      # only to advance the dry-run listing
            if args.max_batches and batch_no >= args.max_batches:
                break
            continue

        print(f"[batch {batch_no}] {', '.join(batch)}", flush=True)
        snap = logdir / "snapshot"
        snapshot(snap)
        (logdir / f"{batch_no:03}_prompt.txt").write_text(prompt)
        r = run(["claude", "-p", prompt, "--model", args.model, "--output-format", "json",
                 "--permission-mode", "acceptEdits"])
        (logdir / f"{batch_no:03}_raw.json").write_text(r.stdout + "\n--- stderr ---\n" + r.stderr)
        cost, report = 0.0, r.stdout
        try:
            out = json.loads(r.stdout)
            cost = float(out.get("total_cost_usd", 0.0))
            report = out.get("result", "")
        except json.JSONDecodeError:
            pass
        total_cost += cost
        (logdir / f"{batch_no:03}_report.md").write_text(report)

        ok, results = build_ok()
        after = {n for n, _ in remaining(args.cfile)}
        banked = [n for n in batch if n not in after]   # banked or parked: no longer plain INCLUDE_ASM
        if ok and not banked:
            # Nothing happened to this batch: don't pick the same functions again.
            state["failed"].extend(batch)
            STATE.parent.mkdir(exist_ok=True)
            STATE.write_text(json.dumps(state, indent=2))
            restore(snap)
            failures_in_row += 1
            line = f"batch {batch_no}: NO PROGRESS (functions skipped from now on), ${cost:.2f}"
            print("   " + line, flush=True)
            summary.append(line)
            if failures_in_row >= 2 or total_cost >= args.cap:
                summary.append("stopping")
                break
            continue
        if ok:
            parked = [n for n in batch if n in parked_names(args.cfile)]
            done = [n for n in banked if n not in parked]
            msg = f"{Path(args.cfile).stem}: batch {batch_no} ({len(done)} banked, {len(parked)} parked)\n\n" + \
                  "\n".join(f"- {n}: {'parked' if n in parked else 'banked'}" for n in batch)
            patch(snap, logdir / f"{batch_no:03}_changes.patch")
            (logdir / f"{batch_no:03}_summary.txt").write_text(msg + "\n")
            failures_in_row = 0
            line = (f"batch {batch_no}: KEPT, {len(done)} banked, {len(parked)} parked, "
                    f"${cost:.2f}")
        else:
            restore(snap)
            state["failed"].extend(batch)
            STATE.parent.mkdir(exist_ok=True)
            STATE.write_text(json.dumps(state, indent=2))
            failures_in_row += 1
            line = f"batch {batch_no}: REVERTED (build {results}), ${cost:.2f}"
        print("   " + line, flush=True)
        summary.append(line)

        if total_cost >= args.cap:
            summary.append(f"cost cap reached (${total_cost:.2f})")
            break
        if failures_in_row >= 2:
            summary.append("two failed batches in a row: stopping to avoid a systemic problem")
            break
        if args.max_batches and batch_no >= args.max_batches:
            summary.append("max batches reached")
            break

    shutil.rmtree(logdir / "snapshot", ignore_errors=True)
    summary.append(f"total cost ${total_cost:.2f}")
    (logdir / "summary.txt").write_text("\n".join(summary) + "\n")
    print("\n".join(summary))
    print(f"logs: {logdir.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
