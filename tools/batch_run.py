#!/usr/bin/env python3
"""Decompile C files' remaining INCLUDE_ASM functions in unattended batches.

Usage:
    tools/batch_run.py rock_neo.exe src/rock_neo.exe/cd.c [more .c files...]
    tools/batch_run.py rock_neo.exe --all
                       [--batch 6] [--model opus] [--cap 15] [--max-batches 0]
                       [--timeout 30] [--dry-run]

Each batch: pick the next functions, snapshot the files an agent can change, run Claude Code
headless in a fresh session, then build BOTH targets. If both MATCH, the batch's changes stay in
the working tree and a patch of them is saved in the log folder; otherwise the snapshot is
restored and its functions are recorded as failed.

Order: by Depth, then Score, from a functions.csv regenerated before each batch (see
func_metrics.py: Depth 0 = every callee already has C), so each function's callees come first.
A batch never spans files: it takes the best function among all the given files, then the next
best ones in that same file. Functions missing from the CSV go last, smallest first.

Agents may apply names they're sure of (CLAUDE.md, "Names"). When a batch changed a registry, the
runner re-splits that target (rebuild.sh) before building, and again after reverting the batch.
--consolidate runs one cleanup session per file instead (merge view structs, fix header placement,
retry parked functions), with the same snapshot / build / keep-or-revert handling.

A kept batch's names go to NNN_renames.txt and logs/renames_applied.txt (registry lines - / +).

Stops when nothing is left, when the cost cap (USD) is reached, after two failed batches in a row,
or after --max-batches. A batch that runs past --timeout minutes is stopped; what it left is still
built and kept if it matches. Logs go to logs/batch_<timestamp>/.

The runner never runs git: you review the working tree (and the per-batch patches) and commit
yourself. Start from a clean tree so the changes are easy to review.
"""

import argparse
import csv
import datetime
import json
import os
import re
import shutil
import signal
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TARGETS = ["slus_006.03", "rock_neo.exe"]
STATE = ROOT / "logs" / "batch_state.json"
SCRATCH = ROOT / "logs" / "scratch"     # agents' scratch files (CLAUDE.md, "Tool use")
# Everything an agent may change; snapshotted before each batch and restored if it fails.
TRACKED = ["src", "include", "notes", "symbol_addrs_slus_006.03.txt", "symbol_addrs_rock_neo.exe.txt",
           "slus_006.03.yaml", "rock_neo.exe.yaml", "CLAUDE.md", "renames.txt"]
NO_RANK = (1 << 30, 1 << 30)

PROMPT = """Decompile these functions in `{cfile}`, in this order: {funcs}.
Follow `CLAUDE.md`, including "Tool use (unattended runs)": one command per Bash call, file
changes only through Edit and Write, scratch files in `logs/scratch/`.
Search `notes/` for each function's address and the globals it touches
(`notes/README.md` lists which notes file covers what). Reuse the types and prototypes already in
`include/`, and add new ones to the right header there. Name struct fields as their uses become
clear.
Don't work on any other function. Park anything that doesn't match within its budget, as
`CLAUDE.md` describes. Then apply the names you're sure of, as `CLAUDE.md`'s "Names" section
describes (one `tools/rename.py` call per name, then one `./tools/rebuild.sh`).
Don't run git commands. Finish with the usual summary."""

CONSOLIDATE_PROMPT = """Consolidation pass for `{cfile}`, after its functions were decompiled in batches.
Don't decompile new functions. Follow `CLAUDE.md`, including "Tool use (unattended runs)", and
above all "Types and headers" ("One struct per object, not one per view", "Declarations live in
headers") and "Names". The build must print MATCH for both targets after every step; revert a step
that doesn't match rather than forcing it.

1. Structs. For each struct the file's code uses that was written for one function's view of an
   object (a partial struct, mostly padding, a comment like "object with ..."), find where the
   object comes from: the function that returns it, the pool array it indexes, the global it is,
   or what the callers pass (search the callers' assembly too). If it is an existing type, merge
   the view into it: move its fields into that type's padding, switch every user over, delete the
   view. Merge two views of the same object the same way. Leave a view whose origin you can't
   establish, with a comment saying what you checked.
2. Fields: give fields their natural type (an 8-byte position copied as a unit is an SVECTOR, not a
   union of views). Name fields whose job is now clear.
3. Headers: every declaration in the header of the file that defines or owns it; prototypes of
   functions called only from this file in the .c file; header order (defines, types, externs,
   prototypes). Use existing literal-address macros instead of raw addresses, and add macros for
   raw addresses outside the image.
4. Parked functions (`#ifdef NON_MATCHING`) in `{cfile}` whose types you changed: retry each, up to
   5 build-and-diff cycles; bank the ones that match, update the note of the ones that don't.
5. Apply function names you're now sure of, as `CLAUDE.md`'s "Names" section describes.

Don't run git commands. Report: structs merged (view -> type), views kept and why, parked functions
retried (banked or not), names applied, anything that needs the owner."""


def run(cmd, **kw):
    return subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, **kw)


def asm_funcs(cfile, parked):
    """INCLUDE_ASM functions in file order: outside NON_MATCHING blocks, or (parked=True) inside."""
    funcs, in_nm = [], False
    for line in (ROOT / cfile).read_text().splitlines():
        s = line.strip()
        if s.startswith("#ifdef NON_MATCHING"):
            in_nm = True
        elif s.startswith("#endif") and in_nm:
            in_nm = False
        m = re.match(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\);', s)
        if m and in_nm == parked:
            funcs.append((m.group(2), m.group(1)))
    return funcs


def remaining(cfile):
    return asm_funcs(cfile, parked=False)


def parked_names(cfile):
    return {n for n, _ in asm_funcs(cfile, parked=True)}


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


def ranks(target, out):
    """{name: (depth, score)} for the target's pending functions, from a fresh functions.csv.

    Written to `out` (the log folder), not the tracked functions.csv. Needs both builds, which the
    runner has just done (or the tree was clean). Empty if the list can't be made."""
    r = run([".venv/bin/python", "tools/function_list.py", "-o", str(out)])
    if r.returncode != 0 or not out.exists():
        print(f"warning: function_list.py failed, ordering by size: {r.stderr.strip()[-200:]}", flush=True)
        return {}
    result = {}
    with out.open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["Program"] != target or not row["Depth"]:
                continue
            key = (int(row["Depth"]), int(row["Score"] or 0))
            result[row["Name"] or row["Function"]] = key
    return result


def pick(cfiles, failed, rank, size):
    """(cfile, [names]) for the next batch, or (None, []) when nothing is left."""
    todo = []      # (rank, size, file order, name, cfile)
    for i, cf in enumerate(cfiles):
        for n, d in remaining(cf):
            if n not in failed:
                todo.append((rank.get(n, NO_RANK), size_of(d, n), i, n, cf))
    if not todo:
        return None, []
    todo.sort()
    best = todo[0]
    cfile = best[4]
    # Same file, and no deeper than the best one: a deeper function waits for its callees.
    return cfile, [t[3] for t in todo if t[4] == cfile and t[0][0] <= best[0][0]][:size]


def registry_changes(snap):
    """{target: [(old line, new line)...]} for registries that differ from the snapshot."""
    out = {}
    for t in TARGETS:
        name = f"symbol_addrs_{t}.txt"
        before = (snap / name).read_text().splitlines() if (snap / name).exists() else []
        after = (ROOT / name).read_text().splitlines()
        if before != after:
            gone = [l for l in before if l not in set(after)]
            new = [l for l in after if l not in set(before)]
            out[t] = (gone, new)
    return out


def rename_map(renamed):
    """{old name: new name} from registry changes, paired by address."""
    def parse(lines):
        out = {}
        for l in lines:
            m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", l)
            if m:
                out[int(m.group(2), 16)] = m.group(1)
        return out
    result = {}
    for gone, new in renamed.values():
        old_at, new_at = parse(gone), parse(new)
        for addr, name in new_at.items():
            old = old_at.get(addr, f"func_{addr:08X}")     # a new line renames splat's default
            if old != name:
                result[old] = name
    return result


def home_file(target, name):
    """The file that defines function `name`: its C definition, else its splat asm folder."""
    for c in (ROOT / "src" / target).glob("*.c"):
        if re.search(rf"^\w[^;\n]*\b{re.escape(name)}\s*\([^;]*$", c.read_text(), re.M):
            return c.stem
    hits = list((ROOT / "asm" / target / "nonmatchings").glob(f"*/{name}.s"))
    return hits[0].parent.name if hits else None


def outside_users(target, name, home):
    """Files other than `home` that name `name`: C sources, other files' assembly, data tables."""
    users = set()
    word = re.compile(rf"\b{re.escape(name)}\b")
    for c in (ROOT / "src" / target).glob("*.c"):
        if c.stem != home and word.search(c.read_text()):
            users.add(c.stem)
    for s_ in (ROOT / "asm" / target).rglob("*.s"):
        owner = s_.parent.name if "nonmatchings" in s_.parts else "data"
        if owner != home and word.search(s_.read_text()):
            users.add(owner)
    return users


def naming_warnings(renamed):
    """CLAUDE.md's global vs static rule for applied function names: no callers outside the
    defining file -> lower_snake_case; callers outside (or a data table) -> Capitalized."""
    out = []
    for t, (_, new) in renamed.items():
        for l in new:
            m = re.match(r"\s*(\w+)\s*=.*type:func", l)
            if not m:
                continue
            name = m.group(1)
            home = home_file(t, name)
            if home is None:
                continue
            users = outside_users(t, name, home)
            if name[0].isupper() and not users:
                out.append(f"{name}: only {home} uses it, so static style: {name[0].lower() + name[1:]}?")
            elif name[0].islower() and users:
                out.append(f"{name}: used outside {home} ({', '.join(sorted(users))}), so global style")
    return out


def resplit(targets):
    """rebuild.sh each target whose registry changed: asm/ and expected/ must carry its names."""
    for t in targets:
        r = run(["./tools/rebuild.sh", t])
        if r.returncode != 0:
            print(f"warning: rebuild.sh {t} failed: {r.stderr.strip()[-300:]}", flush=True)


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


def agent(prompt, model, timeout_min):
    """Run Claude Code headless. Returns (stdout, stderr, timed_out). On timeout the whole process
    group is killed (claude and the builds it started)."""
    p = subprocess.Popen(["claude", "-p", prompt, "--model", model, "--output-format", "json",
                          "--permission-mode", "acceptEdits"],
                         cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
                         start_new_session=True)
    try:
        out, err = p.communicate(timeout=timeout_min * 60 if timeout_min else None)
        return out, err, False
    except subprocess.TimeoutExpired:
        os.killpg(p.pid, signal.SIGTERM)
        try:
            out, err = p.communicate(timeout=30)
        except subprocess.TimeoutExpired:
            os.killpg(p.pid, signal.SIGKILL)
            out, err = p.communicate()
        return out or "", err or "", True


def save_state(state):
    STATE.parent.mkdir(exist_ok=True)
    STATE.write_text(json.dumps(state, indent=2))


def consolidate(args, cfiles, logdir):
    """One session per file with CONSOLIDATE_PROMPT; kept if both builds match, else reverted."""
    summary, total_cost = [], 0.0
    for n, cfile in enumerate(cfiles, 1):
        prompt = CONSOLIDATE_PROMPT.format(cfile=cfile)
        if args.dry_run:
            print(f"consolidate {n}: {cfile}")
            continue
        print(f"[consolidate {n}] {Path(cfile).stem}", flush=True)
        snap = logdir / "snapshot"
        snapshot(snap)
        tag = f"{n:03}_consolidate"
        (logdir / f"{tag}_prompt.txt").write_text(prompt)
        start = datetime.datetime.now()
        out, err, timed_out = agent(prompt, args.model, args.timeout)
        minutes = (datetime.datetime.now() - start).total_seconds() / 60
        (logdir / f"{tag}_raw.json").write_text(out + "\n--- stderr ---\n" + err)
        cost, report = 0.0, out
        try:
            res = json.loads(out)
            cost = float(res.get("total_cost_usd", 0.0))
            report = res.get("result", "")
        except json.JSONDecodeError:
            pass
        total_cost += cost
        (logdir / f"{tag}_report.md").write_text(report)
        renamed = registry_changes(snap)
        resplit(renamed)
        ok, results = build_ok()
        before = len(asm_funcs(cfile, parked=True))
        if ok:
            patch(snap, logdir / f"{tag}_changes.patch")
            if renamed:
                text = "".join(f"## {t}\n" + "".join(f"- {l}\n" for l in gone) + "".join(f"+ {l}\n" for l in new)
                               for t, (gone, new) in renamed.items())
                warnings = naming_warnings(renamed)
                if warnings:
                    text += "## naming warnings\n" + "".join(f"! {w}\n" for w in warnings)
                (logdir / f"{tag}_renames.txt").write_text(text)
                with (ROOT / "logs" / "renames_applied.txt").open("a") as fh:
                    fh.write(f"# {logdir.name} consolidate {n} ({Path(cfile).stem})\n{text}")
            line = (f"consolidate {n}: KEPT ({Path(cfile).stem}), {before} still parked, "
                    f"${cost:.2f}, {minutes:.0f} min" + (" TIMEOUT" if timed_out else ""))
        else:
            restore(snap)
            resplit(renamed)
            line = f"consolidate {n}: REVERTED ({Path(cfile).stem}, build {results}), ${cost:.2f}, {minutes:.0f} min"
        print("   " + line, flush=True)
        summary.append(line)
        if total_cost >= args.cap:
            summary.append(f"cost cap reached (${total_cost:.2f})")
            break
    shutil.rmtree(logdir / "snapshot", ignore_errors=True)
    if args.dry_run:
        shutil.rmtree(logdir, ignore_errors=True)
        return
    summary.append(f"total cost ${total_cost:.2f}")
    (logdir / "summary.txt").write_text("\n".join(summary) + "\n")
    print("\n".join(summary))
    print(f"logs: {logdir.relative_to(ROOT)}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target")
    ap.add_argument("cfiles", nargs="*", help="C files to work through, e.g. src/rock_neo.exe/cd.c")
    ap.add_argument("--all", action="store_true", help="every C file of the target")
    ap.add_argument("--batch", type=int, default=6, help="functions per batch")
    ap.add_argument("--model", default="opus")
    ap.add_argument("--cap", type=float, default=15.0, help="stop once total cost reaches this (USD)")
    ap.add_argument("--max-batches", type=int, default=0, help="0 = no limit")
    ap.add_argument("--timeout", type=float, default=30.0, help="minutes per batch (0 = no limit)")
    ap.add_argument("--dry-run", action="store_true", help="show the batches, run nothing")
    ap.add_argument("--consolidate", action="store_true",
                    help="one consolidation session per file instead of decompiling (see CONSOLIDATE_PROMPT)")
    args = ap.parse_args()

    if args.all:
        cfiles = sorted(str(p.relative_to(ROOT)) for p in (ROOT / "src" / args.target).glob("*.c"))
    else:
        cfiles = args.cfiles
    if not cfiles:
        ap.error("give C files, or --all")
    for cf in cfiles:
        if not (ROOT / cf).is_file():
            ap.error(f"{cf}: no such file")

    if not args.dry_run:
        r = run(["git", "status", "--porcelain"])     # read-only check
        if r.stdout.strip():
            print("warning: the working tree has uncommitted changes; they'll be mixed into the batch "
                  "results (and restored with a failed batch's snapshot, not lost)", flush=True)
    SCRATCH.mkdir(parents=True, exist_ok=True)

    state = json.loads(STATE.read_text()) if STATE.exists() else {"failed": []}
    # A dry run keeps nothing: its function list goes to the scratch folder.
    logdir = SCRATCH / "dry_run" if args.dry_run else \
        ROOT / "logs" / f"batch_{datetime.datetime.now():%Y%m%d_%H%M%S}"
    logdir.mkdir(parents=True, exist_ok=True)
    total_cost, failures_in_row, batch_no = 0.0, 0, 0
    summary = []
    failed = set(state["failed"])
    if args.consolidate:
        consolidate(args, cfiles, logdir)
        return
    rank = ranks(args.target, logdir / "functions.csv")

    while True:
        cfile, batch = pick(cfiles, failed, rank, args.batch)
        if not batch:
            summary.append("nothing left to do")
            break
        batch_no += 1
        prompt = PROMPT.format(cfile=cfile, funcs=", ".join(f"`{n}`" for n in batch))

        if args.dry_run:
            print(f"batch {batch_no} ({Path(cfile).stem}): "
                  + ", ".join(f"{n} {rank.get(n, ('-', '-'))}" for n in batch))
            failed.update(batch)      # only to advance the dry-run listing
            if args.max_batches and batch_no >= args.max_batches:
                break
            continue

        print(f"[batch {batch_no}] {Path(cfile).stem}: {', '.join(batch)}", flush=True)
        snap = logdir / "snapshot"
        snapshot(snap)
        (logdir / f"{batch_no:03}_prompt.txt").write_text(prompt)
        start = datetime.datetime.now()
        out, err, timed_out = agent(prompt, args.model, args.timeout)
        minutes = (datetime.datetime.now() - start).total_seconds() / 60
        (logdir / f"{batch_no:03}_raw.json").write_text(out + "\n--- stderr ---\n" + err)
        cost, report = 0.0, out
        try:
            res = json.loads(out)
            cost = float(res.get("total_cost_usd", 0.0))
            report = res.get("result", "")
        except json.JSONDecodeError:
            pass        # a killed run has no JSON (and its cost is unknown)
        total_cost += cost
        (logdir / f"{batch_no:03}_report.md").write_text(report)
        tag = f", TIMEOUT after {args.timeout:g} min (cost unknown)" if timed_out else ""

        renamed = registry_changes(snap)
        resplit(renamed)      # renames need a fresh split before the build can match
        ok, results = build_ok()
        if ok:
            batch = [rename_map(renamed).get(n, n) for n in batch]   # follow renamed batch functions
        after = {n for n, _ in remaining(cfile)}
        changed = [n for n in batch if n not in after]   # banked or parked: no longer plain INCLUDE_ASM
        if ok and not changed:
            # Nothing happened to this batch: don't pick the same functions again.
            failed.update(batch)
            state["failed"] = sorted(failed)
            save_state(state)
            restore(snap)
            resplit(renamed)
            failures_in_row += 1
            line = f"batch {batch_no}: NO PROGRESS (functions skipped from now on), ${cost:.2f}, {minutes:.0f} min{tag}"
        elif ok:
            parked = [n for n in batch if n in parked_names(cfile)]
            done = [n for n in changed if n not in parked]
            msg = f"{Path(cfile).stem}: batch {batch_no} ({len(done)} banked, {len(parked)} parked)\n\n" + \
                  "\n".join(f"- {n}: {'parked' if n in parked else 'banked' if n in done else 'untouched'}"
                            for n in batch)
            patch(snap, logdir / f"{batch_no:03}_changes.patch")
            if renamed:
                # The names this batch applied, for review: registry lines removed and added.
                text = "".join(f"## {t}\n" + "".join(f"- {l}\n" for l in gone) + "".join(f"+ {l}\n" for l in new)
                               for t, (gone, new) in renamed.items())
                warnings = naming_warnings(renamed)
                if warnings:
                    text += "## naming warnings\n" + "".join(f"! {w}\n" for w in warnings)
                (logdir / f"{batch_no:03}_renames.txt").write_text(text)
                with (ROOT / "logs" / "renames_applied.txt").open("a") as fh:
                    fh.write(f"# {logdir.name} batch {batch_no} ({Path(cfile).stem})\n{text}")
            (logdir / f"{batch_no:03}_summary.txt").write_text(msg + "\n")
            # A function the agent left untouched was skipped on purpose (its report says why):
            # don't offer it again. After a timeout it may just not have been reached, so keep it.
            untouched = [n for n in batch if n not in changed]
            if untouched and not timed_out:
                failed.update(untouched)
                state["failed"] = sorted(failed)
                save_state(state)
            failures_in_row = 0
            n_ren = sum(len(new) for _, new in renamed.values())
            n_warn = len(naming_warnings(renamed)) if renamed else 0
            warn = f" ({n_warn} naming warnings, see {batch_no:03}_renames.txt)" if n_warn else ""
            line = (f"batch {batch_no}: KEPT ({Path(cfile).stem}), {len(done)} banked, {len(parked)} parked, "
                    f"{n_ren} renamed{warn}, ${cost:.2f}, {minutes:.0f} min{tag}")
            rank = ranks(args.target, logdir / "functions.csv")    # depths change as functions get C
        else:
            restore(snap)
            resplit(renamed)
            failed.update(batch)
            state["failed"] = sorted(failed)
            save_state(state)
            failures_in_row += 1
            line = f"batch {batch_no}: REVERTED (build {results}), ${cost:.2f}, {minutes:.0f} min{tag}"
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

    if args.dry_run:
        shutil.rmtree(logdir, ignore_errors=True)
        return
    shutil.rmtree(logdir / "snapshot", ignore_errors=True)
    summary.append(f"total cost ${total_cost:.2f} (timed-out batches not counted)")
    (logdir / "summary.txt").write_text("\n".join(summary) + "\n")
    print("\n".join(summary))
    print(f"logs: {logdir.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
