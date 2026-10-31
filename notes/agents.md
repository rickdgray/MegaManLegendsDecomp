# Working with agents

Notes on running Claude Code against this repo. The agent's rules are in `CLAUDE.md`; this file
is for the owner: which model to use, what it costs, and how to review.

## Model tiers

| Model | Use for | Observed |
|---|---|---|
| **Sonnet** | The default for decompiling batches | Banks most functions; parks sensibly within the cycle budget; short, accurate reports |
| **Haiku** | Mechanical work: renames, doc edits, rename plans | Reliable on explicit instructions; stops and reports when a step breaks the build |
| **Opus** | Hard functions that Sonnet parks, alongside the permuter | Only tried on easy functions so far |

## Measured costs

| Run | Model | Session | Result | Cost |
|---|---|---|---|---|
| `IsBusy`, `RunIntroSequence`, `InitCd` (easy) | Opus | Fresh | 3 banked | $1.02 (~$0.34/function) |
| 5 screen/CD functions | Haiku | Fresh | 2 banked, 3 parked | $0.22 |
| Same 5 functions | Sonnet | Fresh | 4 banked, 1 parked | $0.51 (~$0.13/banked) |
| Group A, intro screens (4) | Sonnet | **9.5 h old** | 3 banked, 1 parked | $3.97 |
| `Intro_init` retry (hard) | Sonnet | Fresh | Re-parked, closer | $0.27 |
| Group C, main and init (6) | Sonnet | Fresh | 6 banked | $1.07 (~$0.18/function) |

Most cost is **context**, re-sent every turn as cache reads, not output. The group A run cost
several times more because the session had carried hours of earlier work.

## Session hygiene

- **Start a fresh session per batch** (`/clear`). Each batch only needs `CLAUDE.md` and its own work.
- **Disable unused MCP servers**; their tool definitions ride along with every request (about 23%
  of tokens before they were turned off).
- **Don't commit while an agent is working.** It sees HEAD move under it (it handled this well,
  but it costs turns).
- Start from a clean, committed tree with a fresh `expected/` (`./tools/rebuild.sh`).

## Writing batch prompts

- Name the functions, in order; group related ones so each gives context for the next.
- Put helpers before the functions that call them.
- Add hints for traps you already know (e.g. GCC inserts `__main` itself; an older name the
  notes use for a function).
- "Propose names but don't apply them" keeps naming decisions with the owner.

## Reviewing a run

1. Run `./tools/build.sh` yourself; don't take the report's word for MATCH.
2. Read `git diff` against the report.
3. Check new headers, names, and registry lines against the conventions.
4. Look for code that matches but isn't plausible (aliases, `pad` locals, redundant statements):
   those become `// HACK` comments plus an entry in the notes.
5. When correcting something, explain why; recurring corrections belong in `CLAUDE.md`.
