# Working with agents

Notes on running Claude Code against this repo. The agent's rules are in `CLAUDE.md`; this file
is for the owner: which model to use, what it costs, how to run batches, and how to review.

## Model tiers

| Model | Use for | Observed |
|---|---|---|
| **Sonnet** | The default for decompiling batches (and `batch_run.py`'s default) | Banks most functions; parks sensibly within the cycle budget; short, accurate reports |
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

Most cost is **context**, re-sent every turn as cache reads, not output. The group A run cost
several times more because the session had carried hours of earlier work.

## Batch runner (`tools/batch_run.py`)

```bash
.venv/bin/python tools/batch_run.py rock_neo.exe src/rock_neo.exe/cd.c [--batch 6] [--model sonnet] \
    [--cap 15] [--max-batches 0] [--dry-run]
```

- Works through a C file's remaining `INCLUDE_ASM` functions, **smallest first**, `--batch` at a
  time, skipping parked ones and ones a previous batch made no progress on (recorded in
  `logs/batch_state.json`).
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
  read-only shell commands, and read-only git); git writes are on its deny list.
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
- "Propose names but don't apply them" keeps naming decisions with the owner.

## Reviewing a run

1. Run `./tools/build.sh` for both targets yourself; don't take the report's word for MATCH.
2. Read `git diff` against the report (and the batch patches, for runner output).
3. Check new headers, names, and registry lines against the conventions.
4. Look for code that matches but isn't plausible (aliases, `pad` locals, redundant statements):
   those become `// HACK` comments plus an entry in the notes.
5. When correcting something, explain why; recurring corrections belong in `CLAUDE.md`.
