# Working with agents

Notes on running Claude Code against this repo. The agent's rules are in `CLAUDE.md`; this file
is for the owner: which model to use, what it costs, how to run batches, and how to review.

## Model tiers

| Model | Use for | Observed |
|---|---|---|
| **Sonnet** | Was the batch default until the 2026-11-12 comparison (below) | Banks most functions; parks sensibly within the cycle budget; short, accurate reports |
| **Haiku** | Mechanical work: renames, doc edits, rename plans | Reliable on explicit instructions; stops and reports when a step breaks the build |
| **Opus** | Hard functions that Sonnet parks, alongside the permuter; porting work | Easy shim functions, and the first ROCK_NEO port (below) |

## Measured costs

| Run | Model | Session | Result | Cost |
|---|---|---|---|---|
| `Cd_read_sync2`, `Intro_task`, `Cd_init` (easy, shim) | Opus | Fresh | 3 banked | $1.02 (~$0.34/function) |
| 5 screen/CD functions (shim) | Haiku | Fresh | 2 banked, 3 parked | $0.22 |
| Same 5 functions | Sonnet | Fresh | 4 banked, 1 parked | $0.51 (~$0.13/banked) |
| Group A, intro screens (4) | Sonnet | **9.5 h old** | 3 banked, 1 parked | $3.97 |
| `Intro_init` retry (hard) | Sonnet | Fresh | Re-parked, closer | $0.27 |
| Group C, main and init (6) | Sonnet | Fresh | 6 banked | $1.07 (~$0.18/function) |
| First ROCK_NEO port (the `cd` file from the shim) | Opus | Fresh | Ported | $1.76 |
| Six-function batch | Sonnet | Fresh (batch runner) | | $0.28 |
| `batch_run.py` on `cd.c` (`logs/batch_20261106_001300/`, 4 batches) | Sonnet | Fresh per batch | 10 banked, 3 parked, `cd_cmd_read_comb` skipped | $2.83 |
| Opus vs Sonnet, one file each (`logs/batch_20261112_105004`, `_131130`) | Opus / Sonnet | Fresh per batch | Opus 68 banked of 91 ($0.16/function, 11 of 22 at Score 100+); Sonnet 34 of 48 ($0.20, 3 of 11). Sonnet's headers needed far more cleanup. **Opus is the batch default since.** | $15.16 / $9.58 |
| ROCK_NEO pilot: `code_80037534`, `code_80037FB4`, `main`, `code_8005C258` (`logs/batch_20261111_*`, 13 batches) | Sonnet | Fresh per batch | 63 banked, 8 parked (3 banked later by hand) | $7.55 (~$0.11/function); up to 135 turns / 15 min per batch |

Most cost is **context**, re-sent every turn as cache reads, not output. The group A run cost
several times more because the session had carried hours of earlier work.

## Batch runner (`tools/batch_run.py`)

```bash
.venv/bin/python tools/batch_run.py rock_neo.exe src/rock_neo.exe/cd.c [more.c ...] [--batch 6] \
    [--model sonnet] [--cap 15] [--max-batches 0] [--timeout 30] [--dry-run]
.venv/bin/python tools/batch_run.py rock_neo.exe --all ...     # every C file of the target
```

- Works through the given C files' remaining `INCLUDE_ASM` functions, `--batch` at a time,
  skipping parked ones and ones a previous batch made no progress on (recorded in
  `logs/batch_state.json`). **Order: Depth, then Score**, from a `functions.csv` regenerated (into
  the log folder) after every kept batch, so callees come before their callers. A batch stays in
  one file: the best function overall, then that file's next best at the same depth.
- `--timeout` (minutes) stops a batch's session (the whole process group); its leftovers are
  still built, and kept if they match. A killed session reports no cost.
- Each batch is a **fresh headless session** (`claude -p ... --permission-mode acceptEdits`) with
  a fixed prompt pointing at `CLAUDE.md`, `notes/`, and the shim's C.
- After each batch it **builds both targets**. If both MATCH, the changes stay in the working tree
  and a patch is saved to `logs/batch_<timestamp>/NNN_changes.patch`; otherwise the files are
  restored from the **snapshot** taken before the batch (`src`, `include`, `notes`, both
  registries and yamls, `CLAUDE.md`, `renames.txt`) and its functions are marked failed. It never
  runs git: **snapshots and patches instead of commits**; you review and commit.
- Stops when nothing is left, at the cost cap, after two failed batches in a row, or after
  `--max-batches`. Per batch, `logs/` keeps the prompt, raw JSON, report and summary.
- Headless sessions can't answer permission prompts, so the commands they need are on the
  **allow list in `.claude/settings.json`** (the `tools/` scripts, `.venv/bin/python tools/`,
  `cc.sh`, `rename.py -n`, `mips-linux-gnu-objdump`, `xxd`, read-only shell commands, and
  read-only git); git writes are on its deny list. Anything else is denied, so `CLAUDE.md`'s "Tool
  use (unattended runs)" tells agents how to work inside it: one command per call (the pilot's
  denials were mostly `cd …;` prefixes and `for` loops), Edit/Write for every file change (not
  `sed -i` or python heredocs), and `logs/scratch/` instead of `/tmp`.
- Start from a clean, committed tree so the per-batch changes are easy to review.

## Session hygiene

- **Start a fresh session per batch** (`/clear`; the batch runner does this itself). Each batch
  only needs `CLAUDE.md` and its own work.
- **Disable unused MCP servers**; their tool definitions ride along with every request (about 23%
  of tokens before they were turned off).
- **Don't commit while an agent is working.** It sees HEAD move under it (it handled this well,
  but it costs turns).
- Start from a clean, committed tree with a fresh `expected/` (`./tools/rebuild.sh <t>`).

## Writing batch prompts

- Name the functions, in order; group related ones so each gives context for the next.
- Put helpers before the functions that call them.
- Add hints for traps you already know (e.g. GCC inserts `__main` itself; an older name the
  notes use for a function; the other program's C for a shared function).
- Agents apply names they're sure of (splat defaults only) with `rename.py`, after the
  functions; the batch runner re-splits when a registry changed, and logs each kept batch's names
  to `NNN_renames.txt` and `logs/renames_applied.txt` for review, with a warning for any function
  name whose style doesn't fit its callers (global vs static; both models got this wrong). Already-named symbols and
  registry fixes still go to `renames.txt` for the owner.

## Reviewing a run

1. Run `./tools/build.sh` for both targets yourself; don't take the report's word for MATCH.
2. Read `git diff` against the report (and the batch patches, for runner output).
3. Check new headers, names, and registry lines against the conventions.
4. Look for code that matches but isn't plausible (aliases, `pad` locals, redundant statements):
   those become `// HACK` comments plus an entry in the notes.
5. When correcting something, explain why; recurring corrections belong in `CLAUDE.md`.
