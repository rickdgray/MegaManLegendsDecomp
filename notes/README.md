# Notes

Reference notes for the Mega Man Legends (USA, SLUS-00603) matching decompilation. They describe
what is known **now**, organized by topic. The discovery history lives in git.

| File | Covers |
|---|---|
| [disc.md](disc.md) | The disc: target hashes, layout, file inventory, code counts, overlay chunk format, load addresses |
| [toolchain.md](toolchain.md) | Compiler and flags (with evidence), build pipeline, splat configuration, tools, gotchas |
| [shim.md](shim.md) | `SLUS_006.03`, the boot shim: layout, subsystems, function status, open questions |
| [rock_neo.md](rock_neo.md) | `ROCK_NEO.EXE`, the main game: what's known before starting, and the to-dos |
| [agents.md](agents.md) | Working with Claude Code: model tiers, measured costs, session hygiene, review checklist |

Codegen patterns for writing matching C (wide stores, chained assignment, separate symbols vs.
arrays, `volatile`, ...) live in `CLAUDE.md`, not here.

## Conventions

- **Confirmed:** verified directly (build, disassembly, or emulator).
- **Suspected:** a hypothesis with supporting evidence, not yet verified.
- **Open:** a known unknown, with what would answer it.

## Searching

Names change; addresses don't. Search by both:

```bash
grep -rn -i "Intro_init\|80011da8" notes/
```
