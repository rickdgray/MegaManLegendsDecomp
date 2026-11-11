# Notes

Reference notes for the Mega Man Legends (USA, SLUS-00603) matching decompilation. They describe
what is known **now**, organized by topic. The discovery history lives in git.

| File | Covers |
|---|---|
| [disc.md](disc.md) | The disc: target hashes, layout, the file table, code counts, overlay chunk format, load addresses |
| [toolchain.md](toolchain.md) | Compiler and flags (with evidence, including ROCK_NEO's `-G32`), build pipeline, splat configuration, symbol registry, tools, gotchas |
| [shim.md](shim.md) | `SLUS_006.03`, the boot shim: layout, subsystems, function status, open questions |
| [rock_neo.md](rock_neo.md) | `ROCK_NEO.EXE`, the main game: layout, code shared with the shim, sound, threads, the CD module, function status, to-dos |
| [overlays.md](overlays.md) | The code overlays (`ST*`, `ARM*R`, `SUPPORT`): layout, splitting into functions, duplicates across the whole game, shared source files |
| [rock_neo_files.md](rock_neo_files.md) | `ROCK_NEO.EXE`'s split into Capcom's source files: evidence and confidence per file |
| [agents.md](agents.md) | Working with Claude Code: model tiers, measured costs, the batch runner, session hygiene, review checklist |
| `sdk/` | Sony's PsyQ SDK documentation (PDFs: library reference, file formats, hardware). Gitignored, local copy only |

Rules for agents, the header layout, and codegen patterns for writing matching C (wide stores,
chained assignment, separate symbols vs. one struct, `volatile`, ...) live in `CLAUDE.md`, not here.

## Conventions

- **Confirmed:** verified directly (build, disassembly, or emulator).
- **Suspected:** a hypothesis with supporting evidence, not yet verified.
- **Open:** a known unknown, with what would answer it.

## Searching

Names change; addresses don't. Search by both:

```bash
grep -rn -i "Intro_init\|80011da8" notes/
```
