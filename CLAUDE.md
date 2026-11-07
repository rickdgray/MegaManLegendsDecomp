# CLAUDE.md

Matching decompilation of **Mega Man Legends** (PlayStation, USA, SLUS-00603).
"Matching" means the C in `src/` compiles back to the original executables **byte for byte**.
There are two targets, and both rebuild byte-identical:

- `slus_006.03`: `SLUS_006.03`, the boot shim (intro screens, then `LoadExec` of `ROCK_NEO.EXE`).
  One C file, `src/slus_006.03/main.c`; every function is banked or parked.
- `rock_neo.exe`: `ROCK_NEO.EXE`, the main game. Split into Capcom's source files (see
  `notes/rock_neo_files.md`); the first one in C is `src/rock_neo.exe/cd.c`, the rest is assembly.

Background, findings, and open questions live in `notes/` (start with `notes/README.md`; each
executable has its own file: `notes/shim.md`, `notes/rock_neo.md`). **Search, don't read whole
files**: `grep -rn -i "<name>\|<address>" notes/`. Addresses never change, so search by both.

## The one rule

`./tools/build.sh <t>` must print **MATCH** for every target your change can reach. Shared headers
(`include/common.h`, `include/psyq/`, `include/cd.h`) reach both, so after touching one, build
both. Never report a task as done while a build prints MISMATCH. The build's SHA-1 check is the
only authority on whether something matches.

## Principles

1. **The bytes must match.** Non-negotiable; everything else bends to it.
2. **Beyond that, prefer modern readability**: typedefs, named macros, clear structure, Allman
   braces. Antiquated style is not a goal in itself.
3. **Names follow Capcom's own conventions** (see "Names"), and real names win when known.

Capcom's own source, from the Japanese release's `ST1E.BIN`, is on TCRF's "Mega Man Legends/
Source Code" page. Use it as a reference for naming and idioms only; never copy it into the repo.

## Git: read-only

You may **read** history and changes: `git status`, `git diff`, `git log`, `git show`, `git blame`.

**Never write.** No `add`, `commit`, `push`, `pull`, `fetch`, `checkout`, `switch`, `restore`,
`reset`, `revert`, `stash`, `branch`, `merge`, `rebase`, `cherry-pick`, `tag`, `rm`, `mv`,
`clean`, or anything else that changes the repository, its history, or its configuration. The
owner reviews every change and makes all commits and pushes. Leave your work as uncommitted
changes in the working tree, and describe them in your summary (see the end of this file).
`.claude/settings.json` enforces this.

## Scope and stopping

- Work **only on the functions the task names**. Don't start others, even easy ones nearby.
- Budget about **10 build-and-diff cycles per function**. If it doesn't match by then, park it
  (see "Parking a function") and move on to the next named function.
- **Stop and ask** instead of working around a blocker: a needed change to the yaml, flags, or
  `tools/`; a missing tool; a header or naming decision you're unsure about; or a build that
  stopped matching for reasons unrelated to your function.
- When every named function is banked or parked, write the summary and stop.

## Environment

WSL Ubuntu, from the repo root, with the Python venv at `.venv/`. Third-party tools are pinned in
`tools/fetch_tools.sh` and live in `tools/vendor/` (gitignored). Game data lives in `disc/`
(gitignored). **Never copy game data or generated output** (anything from `disc/`, `asm/`,
`assets/`, `build/`, or `expected/`) into `src/`, `include/`, `notes/`, or any other tracked folder.

## Commands

Every script takes the **target** as its first argument: `slus_006.03` (the shim) or
`rock_neo.exe` (the main game). Paths derive from it (see `tools/target.sh`):

| Target `<t>` | Path |
|---|---|
| splat config | `<t>.yaml` |
| symbol registry | `symbol_addrs_<t>.txt` |
| C sources | `src/<t>/` |
| assembly | `asm/<t>/` |
| build output, linker script, map | `build/<t>/` |
| final binary (keeps the disc file's name) | `build/<t>/<T>`, e.g. `build/slus_006.03/SLUS_006.03` |
| diff reference | `expected/<t>/` |

| Command | What it does |
|---|---|
| `./tools/split.sh <t>` | Regenerate `asm/<t>/` and the linker script from `<t>.yaml` (clears `asm/<t>/` first). |
| `./tools/build.sh <t>` | Build everything and compare SHA-1 with the original. Prints MATCH or MISMATCH. |
| `./tools/diff.sh <t> <Func>` | Per-function diff against `expected/<t>/`. Flagged lines are what still differs. |
| `./tools/m2c.sh <t> <Func>` | Draft C for a function with m2c, using all headers as context. |
| `./tools/objdump.sh <t> <Func>` | Real-instruction disassembly (no pseudo-ops) of a function in `build/<t>/`. |
| `./tools/make_expected.sh <t>` | Refresh `expected/<t>/` from a MATCHING build. Refuses otherwise. |
| `./tools/rebuild.sh <t>` | Split, build, and refresh `expected/<t>/` in one step. Use after any rename or yaml change. |
| `./tools/cc.sh <t> <in.c> <out.o>` | Compile one C file with the target's matching toolchain. |
| `./tools/format.sh <t>` | `clang-format-15 -i` on `src/<t>/` and `include/`. |

The owner's tools (`find_dupes.py`, `progress.py`, `batch_run.py`, `rename.py`,
`permuter_prep.py`) are described in `notes/toolchain.md`.

**After any rename or re-split, refresh `expected/`** (`./tools/rebuild.sh <t>`). Otherwise the
snapshot still has the old names, and `diff.sh` shows an empty target column.

`diff.sh` notes: the score in the header is a line edit distance (over more than the function),
not a measure of how close you are, so read the flagged lines. It displays pseudo-instructions
(`li`, `move`), which can hide encoding differences such as `addiu` vs `ori`. When the diff is
clean, confirm with `build.sh`.

## Workflow: decompiling one function

`<file>` is the C file's name: `main` in the shim, `cd` for `src/rock_neo.exe/cd.c`.

1. Pick a function still written as `INCLUDE_ASM("asm/<t>/nonmatchings/<file>", Func);` in
   `src/<t>/<file>.c`.
2. Read its assembly in `asm/<t>/nonmatchings/<file>/Func.s` and search `notes/` for it. If the
   other program has the same function (the CD module is in both; see "Shared code" in
   `notes/rock_neo.md`), start from its C.
3. Run `./tools/m2c.sh <t> Func` for a draft. Treat the draft as a starting point, never
   as an answer: m2c often gets pointer arithmetic in bytes rather than elements, emits `unkXX`
   fields where a struct is incomplete, and writes `if` + `do/while` where the source was a plain
   `while`.
4. Replace the `INCLUDE_ASM` line with the C, **in place** (function order in the file matters).
5. `./tools/build.sh <t>`, then `./tools/diff.sh <t> Func`. Iterate on the C until the diff is
   clean and the build prints MATCH.
6. If types were needed, add them to the right header (see "Types and headers"), not to the `.c`
   file.

### Reading a diff

- Missing or extra instructions: the source *shape* is wrong (statements, loops, types).
- Different store or load width (`sb`/`sh`/`sw`, `lb`/`lbu`): a field or variable type is wrong.
- Same instructions, different registers or order: register allocation or scheduling. Try
  statement order, declaration order, or temporaries. These are the hardest; see "Parking".
- A frame pointer, stack spills, and a global reloaded before every statement: the build isn't
  optimizing. Check flags before touching the code.

### Parking a function

If a function is close but won't match after reasonable effort, **don't force it**. Keep the
assembly and record the best attempt:

```c
#ifdef NON_MATCHING
void Func(void)
{
    // best attempt
}
#else
INCLUDE_ASM("asm/<t>/nonmatchings/<file>", Func);
#endif
```

Update the executable's notes file ("Function status" in `notes/shim.md` or `notes/rock_neo.md`)
with what remains different. decomp-permuter will handle these later.

## Toolchain facts (established; do not change without asking)

- gcc 2.7.2 (PSX build, `cc1`) → maspsx `--aspsx-version=2.56 --expand-div` → GNU `as`, at `-O2`.
  Equivalent to decomp.me's `PSYQ4.0` preset (gcc 2.7.2 + aspsx 2.56).
- `slus_006.03`: `-G0`. `cc1` defaults to `-G 8`, so `-G0` must always be passed. The shim never
  addresses globals through `$gp`.
- `rock_neo.exe`: `-G8` to `cc1` and maspsx, `-G0` to GNU `as`. `extern` globals of any size are
  still addressed with `lui` + `%lo`; only small data *defined in the same file* would use `$gp`.
  Details and evidence: `notes/toolchain.md`.

## Writing C for this compiler

gcc 2.7.2 is a C89 compiler.

- Comments: `//` is fine and preferred (GCC of this era accepts it as a GNU extension to C89).
- **Declarations:** all local variables at the top of the function, never block-local, for
  consistency. (Scope doesn't change GCC 2.7's output; the build is the check.)
- No `inline`, no `bool`, no designated initializers, no mixed declarations and code.
- Write the plainest C that produces the bytes. The goal is the source Capcom wrote, not
  "better" code. Some idioms are deliberate and must be preserved; for example,
  `intro_copyright_draw` passes `ot[0]` rather than `ot` to `addPrim` (see `notes/shim.md`).
- **Brace style is Allman** (braces on their own line), 4-space indent, `case` labels indented
  one level inside their `switch`, and **always use braces**, even for a one-line `if`, loop, or
  `else` body. After editing, run `clang-format-15 -i` on the C and header files you changed
  (config: `.clang-format`). Never run it on generated files such as `include/include_asm.h`.
- **Types:** use Capcom's `uint8`, `sint8`, `uint16`, `sint16`, `uint32`, `sint32` in game code,
  and PsyQ's types (`u_char`, `u_long`, `RECT`, `SVECTOR`, …) for PsyQ structures and prototypes.
  Convert m2c's `s32`/`u8`/etc. when banking.
- Type function pointers with a **typedef**, never inline and never as `void *`. That includes
  dispatch tables: `static SCREEN_FUNC screen_tbl[] = { ... };` (identical bytes to Capcom's
  inline declarations). PsyQ's own callback type keeps its PsyQ name (`CdlCB`).
- **Name magic numbers** when the name folds to the same constant: PsyQ's macros (`getTPage`,
  `getClut`, in `include/psyq/libgpu.h`) or a `#define`. Only with constant arguments: with a
  variable involved, the macro emits real arithmetic and the bytes change. If the build stops
  matching, keep the raw value with a comment explaining it.
- Avoid casts and `unkXX` names in banked code where a proper type or field name works.
- **No redundant statements**, unless the build needs them. Try removing anything that looks
  redundant; if the build still matches, leave it out. If removing it breaks the match, it was in
  the original source: keep it, with a short comment. (Example: `Cd_init` stores to
  `D_80059BCA` twice.) Note that Ghidra's pseudocode hides dead stores; the assembly is the truth.
- **Prefer the natural form when several match.** For example, try `for (i = 0; i < n; i++)`
  before a reversed loop; GCC often reverses loop direction itself.
- **Hand-written assembly stays assembly.** Some subsegments are Capcom's own assembly, not
  compiler output; their yaml lines say `HAND-WRITTEN ASSEMBLY` (e.g. ROCK_NEO's `asm_fastmem`).
  Never convert them to C, decompile their functions, or park them; they're complete as `asm`.
  Call them from C with a prototype like any other function. Signs to recognize one: it reads or
  writes `sp` directly, has no GCC-style prologue, stores `ra` at the bottom of its frame, is
  unrolled by hand, or uses `break`. If you find another, stop and report it rather than
  decompiling.

## Patterns seen in this code

What decompilers show vs. what to write:

- **`if (x) { do { ... } while (x); }`** in m2c or Ghidra output is GCC's rotated form of
  `while (x) { ... }`. Write the `while`.
- **Empty retry loops:** `while (CdSync(1, result) == 0) {}` and the `do {} while` version
  compile identically. Use the `while` form.
- **Small `switch` statements** compile to a compare chain (`beq`/`bne`), not a jump table. If an
  `if`/`else` chain gets the branch layout wrong, try a `switch` with `break`s. If the target has
  no `slti` range check before a jump table, the switch value is unsigned
  (`switch ((uint32)Cd_cmd_routine)`).
- **A stack frame larger than the locals explain** usually means an *unused* local; GCC 2.7
  reserves space for unused aggregates. Ghidra and m2c both hide it. Match the size with the
  most plausible type. Screens 1 and 2 have an unused `RECT rect;` (8 bytes), left over from the
  screen template (the launch-game screen uses one).
- **Duplicate stores** that the build needs are real; see "No redundant statements" above.
- **One wide store over several small fields** is Capcom's habit: `*(uint32 *)&wp->routine_0 = 0;`
  resets `routine_0`…`routine_3` at once. Write it that way when the assembly has one `sw`/`sh`
  spanning several fields.
- **Same symbol vs. different symbols (shared `lui`):** GCC shares the `lui %hi(sym)` of one
  symbol across several accesses (often in a saved `s` register, which grows the frame) and
  reaches fields by offset, but it can't share it between two different symbols, even adjacent
  ones. So a fresh `lui` per access means **separate variables**, and one shared base register
  means **one symbol** (an array or struct). Don't merge adjacent globals into a struct just
  because they sit next to each other. Seen in the shim: `Intro_routine_0`/`_1` (separate; one
  cast 32-bit store in `Intro_init` writes both), `Intro_bright`/`Intro_timer`, and the loading
  screen's two `DR_MODE`s.
- **Revisit parked functions when a struct gets defined.** The reverse case: while the fields of
  a struct are still separate `D_` symbols, GCC emits a `lui` per access where the target shares
  one base, and the function parks. ROCK_NEO's `Cd_stop` and `func_8001B7B4` matched once
  `D_800AD142` became `Sound_work.flags` (`SOUND_WORK`). After defining a struct, re-try the
  functions parked over its fields.
- **Chained assignment stores right to left:** `p->r0 = p->g0 = p->b0 = v;` emits `b0`, then
  `g0`, then `r0`. Use it when the target's store order is reversed like that.
- **Embedded TIM images:** image data in the binary is often a whole TIM file, read at fixed
  offsets (CLUT pixels at +0x14). Name the symbol `*_tim`.
- **`routine_N` state machines and table jumps** (`xxx_tbl[wp->routine_0](wp)`) are the house
  pattern for modes and states. Byte fields `routine_0`…`routine_3` start most `_WORK` structs.
- **GPU primitives:** separate byte stores in the assembly → PsyQ's macros (`setSprt`, `setRGB0`,
  …). A single word store covering several fields → a named macro of ours that expands to that
  one store (e.g. `SET_CODE_RGB(p, code, r, g, b)`). Never an inline function: macros are textual,
  so they can't change register allocation.
- **Initialized local structs:** write them with an initializer (`CHECK_BLOCK d = {...};`), for
  consistency, since some cases require it (GCC emits a read-only data copy). Assign fields one by
  one only if the initializer form doesn't match.
- **`switch` fall-through** (no `break`) is deliberate in places. Keep it, with a `// fall through`
  comment.
- **Reload vs. reuse after a store through a pointer:** after such a store, GCC must reload any
  global the source mentions again (the store might have changed it), but it remembers the value
  it just stored. If the target reloads a global for one use but reuses an older value for
  another, the second use probably reads *through the stored pointer* (`(*hdrs)->nSectors`).
  Matching it can reveal a parameter's real type (`Movie_buf_get`: `StHEADER **hdrs`, not
  `u_long **`).
- **Busy-waits on interrupt flags need `volatile`.** If the target reloads a global on every pass
  of a wait loop, declare it `volatile` (`Vsync_count`, `Movie_dct_busy`). Without it, GCC loads
  it once and spins forever. Don't imitate the reloads with extra `if`s around the loop; GCC
  already tests once before entering a `while` and again at the bottom.
- **Fix semantic differences before blaming scheduling.** A wrong load width or offset (a `lhu`
  where the target has `lw`), or an extra saved register (an extra variable kept alive across
  calls), is a source bug, and it disturbs instruction order and delay slots elsewhere.
  `cd_cmd_play_movie`'s apparent scheduling difference disappeared once its wrong field and wrong
  macro argument were fixed.
- **Shared error exits.** When several paths set something different and then share a tail whose
  store order is preserved across all of them, the source had a label there (`goto error;` /
  `return;` / `error:`): the scheduler can't reorder across a label. A tail that is only a call
  doesn't need one: duplicate it, and GCC's cross-jumping merges the copies.

## Types and headers

| Header | Contents |
|---|---|
| `include/common.h` | Basic typedefs (`s8`…`u32`, `u_char`…`u_long`, Capcom's `uint8`…`sint32`); includes `include_asm.h` |
| `include/psyq/*.h` | Self-written PsyQ declarations (`libgpu.h`: `RECT`, `DRAWENV`, `SPRT`, `addPrim`, …; `libcd.h`, `libsnd.h`, …) |
| `include/cd.h` | CD drive, file table and command queue (shared); includes the target's `cd_local.h` at its end |
| `include/<t>/cd_local.h` | That target's still-unnamed CD variables (names and addresses differ per program) |
| `include/slus_006.03/` | Shim only: `display.h`, `intro.h`, `movie.h`, `pad.h`, `scratch.h`, `system.h` |
| `include/rock_neo.exe/` | ROCK_NEO only: `sound.h` (`SOUND_WORK`), `system.h` (`Thread_wait`) |

**Shared vs. per-target headers.** `include/` holds only what both programs use with identical
declarations: `common.h`, `psyq/`, `cd.h`, and the assembler includes (`*.inc`). Everything else
lives in `include/<t>/`. **A header is shared only when proven identical in both programs**;
until then it belongs to one target, even if the other will probably need it. `cc.sh`, `m2c.sh`
and `permuter_prep.py` search `include/<t>/` before `include/`, so never give a per-target header
the name of a shared one: it would silently shadow it. Unnamed globals go in the target's
`cd_local.h`-style file (included at the end of the shared header), never in a `.c` file: a `.c`
file declares nothing itself. When a variable gets a name in both programs, move it into the
shared header.

Inside a header, order: include guard, `#include`s, `#define` constants, typedefs and structs,
`extern` globals, then function prototypes.

Put each declaration in the header for its subsystem. Create a new subsystem header rather than
growing an unrelated one. **Never copy Sony's PsyQ headers**; write declarations yourself and
check offsets against the binary.

## Names

The repo is the source of truth for names. Each target's `symbol_addrs_<t>.txt` (e.g.
`symbol_addrs_slus_006.03.txt`) is the hand-maintained registry that splat uses when generating
assembly.

**Only the owner renames.** Don't apply names yourself. Write each proposal to `renames.txt` in
the repo root (create it if needed), one per line, in the format `tools/rename.py` reads:

```
# OLD          NEW            [splat attributes]   # why
func_80011940  Movie_start                         # starts playback of Cd_file_tbl[arg1]
D_8001D3DC     Cd_file_tbl    size:0xBA0           # CD_FILE[248]
```

Give `size:` for data when you know it. The owner edits the file and runs
`tools/rename.py <t> -f renames.txt`, which updates `symbol_addrs_<t>.txt`, `src/<t>/`, `include/`
and `notes/` together (it adds `type:func` and `absolute:True` where needed), then
`./tools/rebuild.sh <t>`.
In your report, just say how many proposals you added to `renames.txt`.

Conventions (Capcom's own, from their source):

| Kind | Style | Examples |
|---|---|---|
| Global functions | `Capitalized_snake_case` | `Sound_call`, `Cd_read_comb`, `Setup_display` |
| `static` functions | `lower_snake_case` | `check_block`, `map_cursor_set` |
| Global variables | `Capitalized_snake_case` | `Player_work`, `Disp_env_ptr`, `System_timer` |
| `static` variables | `lower_snake_case` | `spd_tbl`, `eve19_check_flag` |
| Struct types | `ALL_CAPS`, state structs end in `_WORK` | `PL_WORK`, `GAME_WORK`, `MOVE_TBL` |
| Function-pointer typedefs | `ALL_CAPS` ending in `_FUNC` | `SCREEN_FUNC`, `CD_CMD_FUNC` |
| Constants, macros | `ALL_CAPS` | `R0_END`, `FLG_END` |
| Tables | `_tbl` suffix | `screen_tbl`, `Rock_buster_parts_tbl` |
| State fields | `routine_0` … `routine_3` | |

Module prefixes follow Capcom's too: the CD module is `Cd_` in both programs. Acronyms stay
uppercase inside names (`EM_Char_Set`, `Close_EVE_WORK`). Unknown names keep the splat default
(`func_8001D648`, `D_80059C24`) until their purpose is clear; propose a name in `renames.txt`
rather than guessing. Names from other projects (ChrisNonyminus/mml1) are hints, not authority.

## Do not

- Edit anything under `asm/`, `assets/`, `build/`, or `expected/`, or the generated
  `build/<t>/<t>.ld` / `undefined_*_auto.txt`. They are regenerated and edits are lost.
- Change a `<t>.yaml`, toolchain flags, or `tools/` scripts without asking first.
- Refresh `expected/` from a build that doesn't match.
- Upload game code anywhere (e.g. decomp.me) without asking.
- Decompile PsyQ library code (`asm/<t>/psyq/`). It is linked as-is.

## When you finish a task

Leave everything uncommitted. Keep the report short; the owner reads the diff itself.

```
Banked: Cd_pause, Cd_read_sync
Parked: Cd_cmd_dequeue (loop pointer based at p+4, target p+0xc)
Files:  src/rock_neo.exe/cd.c, include/rock_neo.exe/cd_local.h, include/rock_neo.exe/sound.h (new)
Build:  slus_006.03 MATCH, rock_neo.exe MATCH
Decisions needed:
- <only items that need the owner: suspected registry errors, tool bugs, open questions>
Names:  <N> proposals added to renames.txt
```

Don't restate the code or narrate each step.
