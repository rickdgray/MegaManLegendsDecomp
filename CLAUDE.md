# CLAUDE.md

Matching decompilation of **Mega Man Legends** (PlayStation, USA, SLUS-00603).
"Matching" means the C in `src/` compiles back to the original executable **byte for byte**.
Current target: `SLUS_006.03`, the boot shim (intro screens, then `LoadExec` of `ROCK_NEO.EXE`).

Background, findings, and open questions: `notes/recon.md`. It is long: **search it for the
function's name and the globals it touches** (`grep -n`) instead of reading it whole.

## The one rule

`./tools/build.sh` must print **MATCH**. Never report a task as done while it prints MISMATCH.
The build's SHA-1 check is the only authority on whether something matches.

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

| Command | What it does |
|---|---|
| `./tools/split.sh` | Regenerate `asm/` and the linker script from `slus_006.03.yaml` (clears `asm/` first). |
| `./tools/build.sh` | Build everything and compare SHA-1 with the original. Prints MATCH or MISMATCH. |
| `./tools/diff.sh <Func>` | Per-function diff against `expected/`. Flagged lines are what still differs. |
| `./tools/m2c.sh <Func>` | Draft C for a function with m2c, using all headers as context. |
| `./tools/objdump.sh <Func>` | Real-instruction disassembly (no pseudo-ops) of a function in `build/`. |
| `./tools/make_expected.sh` | Refresh `expected/` from a MATCHING build. Refuses otherwise. |
| `./tools/rebuild.sh` | Split, build, and refresh `expected/` in one step. Use after any rename or yaml change. |
| `./tools/cc.sh <in.c> <out.o>` | Compile one C file with the matching toolchain. |

**After any rename or re-split, refresh `expected/`** (`./tools/rebuild.sh`). Otherwise the
snapshot still has the old names, and `diff.sh` shows an empty target column.

`diff.sh` notes: the score in the header is approximate (it covers more than the function), so
read the flagged lines. It displays pseudo-instructions (`li`, `move`), which can hide encoding
differences such as `addiu` vs `ori`. When the diff is clean, confirm with `build.sh`.

## Workflow: decompiling one function

1. Pick a function still written as `INCLUDE_ASM("asm/nonmatchings/main", Func);` in `src/main.c`.
2. Read its assembly in `asm/nonmatchings/main/Func.s` and any notes in `notes/recon.md`.
3. Run `./tools/m2c.sh Func` for a draft. Treat the draft as a starting point, never as an answer:
   m2c often gets pointer arithmetic in bytes rather than elements, emits `unkXX` fields where a
   struct is incomplete, and writes `if` + `do/while` where the source was a plain `while`.
4. Replace the `INCLUDE_ASM` line with the C, **in place** (function order in the file matters).
5. `./tools/build.sh`, then `./tools/diff.sh Func`. Iterate on the C until the diff is clean
   and the build prints MATCH.
6. If types were needed, add them to the right header in `include/` (see below), not to `main.c`.

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
void Func(void) {
    /* best attempt */
}
#else
INCLUDE_ASM("asm/nonmatchings/main", Func);
#endif
```

Add a line to `notes/recon.md` with what remains different. decomp-permuter will handle these later.

## Toolchain facts (established; do not change without asking)

- gcc 2.7.2 (PSX build, `cc1`) → maspsx `--aspsx-version=2.56 --expand-div` → GNU `as`.
- Compiler flags: `-O2 -G0`. `cc1` defaults to `-G 8`, so `-G0` must always be passed.
- No small data: the code never addresses globals through `$gp`.
- This is equivalent to decomp.me's `PSYQ4.0` preset (gcc 2.7.2 + aspsx 2.56).

## Writing C for this compiler

gcc 2.7.2 is a C89 compiler.

- Comments: `//` is fine and preferred (GCC of this era accepts it as a GNU extension to C89).
- Declare variables at the top of a block.
- No `inline`, no `bool`, no designated initializers, no mixed declarations and code.
- Write the plainest C that produces the bytes. The goal is the source Capcom wrote, not
  "better" code. Some idioms are deliberate and must be preserved; for example,
  `DrawCopyrightWarning` passes `ot[0]` rather than `ot` to `addPrim` (see recon.md).
- **Brace style is Allman** (braces on their own line), 4-space indent, and **always use braces**,
  even for a one-line `if`, loop, or `else` body. After editing, run `clang-format-15 -i` on the C
  and header files you changed (config: `.clang-format`). Never run it on generated files such as
  `include/include_asm.h`.
- **Types:** use Capcom's `uint8`, `sint8`, `uint16`, `sint16`, `uint32`, `sint32` in game code,
  and PsyQ's types (`u_char`, `u_long`, `RECT`, `SVECTOR`, …) for PsyQ structures and prototypes.
  Convert m2c's `s32`/`u8`/etc. when banking.
- Type function pointers with a **typedef**, never inline and never as `void *`. That includes
  dispatch tables: `static SCREEN_FUNC screen_tbl[] = { ... };` (identical bytes to Capcom's
  inline declarations). PsyQ's own callback type keeps its PsyQ name (`CdlCB`).
- Avoid casts and `unkXX` names in banked code where a proper type or field name works.
- **No redundant statements**, unless the build needs them. Try removing anything that looks
  redundant; if the build still matches, leave it out. If removing it breaks the match, it was in
  the original source: keep it, with a short comment. (Example: `InitCd` stores to `D_80059BCA`
  twice.) Note that Ghidra's pseudocode hides dead stores; the assembly is the truth.
- **Prefer the natural form when several match.** For example, try `for (i = 0; i < n; i++)`
  before a reversed loop; GCC often reverses loop direction itself.

## Patterns seen in this code

What decompilers show vs. what to write:

- **`if (x) { do { ... } while (x); }`** in m2c or Ghidra output is GCC's rotated form of
  `while (x) { ... }`. Write the `while`.
- **Empty retry loops:** `while (CdSync(1, result) == 0) {}` and the `do {} while` version
  compile identically. Use the `while` form.
- **Small `switch` statements** compile to a compare chain (`beq`/`bne`), not a jump table. If an
  `if`/`else` chain gets the branch layout wrong, try a `switch` with `break`s.
- **A stack frame larger than the locals explain** usually means an *unused* local; GCC 2.7
  reserves space for unused aggregates. Ghidra and m2c both hide it. Match the size with the
  most plausible type. Screens 1 and 2 have an unused `RECT rect;` (8 bytes), left over from the
  screen template (the launch-game screen uses one).
- **Duplicate stores** that the build needs are real; see "No redundant statements" above.
  Ghidra's pseudocode hides dead stores.
- **Counting loops:** GCC often reverses loop direction. Try `for (i = 0; i < n; i++)` first.
- **One wide store over several small fields** is Capcom's habit: `*(uint32 *)&wp->routine_0 = 0;`
  resets `routine_0`…`routine_3` at once. Write it that way when the assembly has one `sw`/`sh`
  spanning several fields.
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

## Types and headers

| Header | Contents |
|---|---|
| `include/common.h` | Basic typedefs (`s8`…`u32`, `u_char`…`u_long`); includes `include_asm.h` |
| `include/psyq/libgpu.h` | Self-written PsyQ GPU types and prototypes (`RECT`, `DRAWENV`, `SPRT`, `addPrim`, …) |
| `include/display.h` | `DisplayBuffer`, display globals, display functions |
| `include/cmd.h` | CD command queue: `Command`, `CommandArgs`, queue globals and functions |

Inside a header, order: include guard, `#include`s, `#define` constants, typedefs and structs,
`extern` globals, then function prototypes.

Put each declaration in the header for its subsystem. Create a new subsystem header rather than
growing an unrelated one. **Never copy Sony's PsyQ headers**; write declarations yourself and
check offsets against the binary.

## Names

The repo is the source of truth for names. `symbol_addrs.txt` is the hand-maintained registry
that splat uses when generating assembly.

Renaming a function or global means changing all of:
1. `symbol_addrs.txt`. Symbols with splat's default names (`func_XXXXXXXX`, `D_XXXXXXXX`) are
   **not listed**; add a new line, e.g. `Cmd_nop = 0x800110E4; // type:func` or
   `Cd_mode = 0x80059BCB; // size:0x1`.
2. Its definition in `src/` (or the name in its `INCLUDE_ASM` line)
3. Any declaration in `include/`

Then `./tools/split.sh` and `./tools/build.sh`. A mismatch shows up as a link error.
Only rename when the owner approves a name; otherwise propose it in the report.

Conventions (Capcom's own, from their source):

| Kind | Style | Examples |
|---|---|---|
| Global functions | `Capitalized_snake_case` | `Sound_call`, `Cd_read_comb`, `Setup_display` |
| `static` functions | `lower_snake_case` | `check_block`, `map_cursor_set` |
| Global variables | `Capitalized_snake_case` | `Player_work`, `Disp_env_ptr`, `System_timer` |
| `static` variables | `lower_snake_case` | `spd_tbl`, `eve19_check_flag` |
| Struct types | `ALL_CAPS`, state structs end in `_WORK` | `PL_WORK`, `GAME_WORK`, `MOVE_TBL` |
| Function-pointer typedefs | `ALL_CAPS` ending in `_FUNC` | `SCREEN_FUNC`, `CMD_FUNC` |
| Constants, macros | `ALL_CAPS` | `R0_END`, `FLG_END` |
| Tables | `_tbl` suffix | `screen_tbl`, `Rock_buster_parts_tbl` |
| State fields | `routine_0` … `routine_3` | |

Acronyms stay uppercase inside names (`EM_Char_Set`, `Close_EVE_WORK`). Unknown names keep the
splat default (`func_800110E4`, `D_80059C20`) until their purpose is clear; propose a name in
your summary rather than guessing.

## Do not

- Edit anything under `asm/`, `assets/`, `build/`, or `expected/`, or the generated
  `slus_006.03.ld` / `undefined_*_auto.txt`. They are regenerated and edits are lost.
- Change `slus_006.03.yaml`, toolchain flags, or `tools/` scripts without asking first.
- Refresh `expected/` from a build that doesn't match.
- Upload game code anywhere (e.g. decomp.me) without asking.
- Decompile PsyQ library code (`asm/psyq/`). It is linked as-is.

## When you finish a task

Leave everything uncommitted. Keep the report short; the owner reads the diff itself.

```
Banked: IsBusy, RunIntroSequence
Parked: DequeueCommand (loop pointer based at p+4, target p+0xc)
Files:  src/main.c, include/cmd.h, include/screen.h (new)
Build:  MATCH
Decisions needed:
- <only items that need the owner: proposed names, suspected registry errors, tool bugs>
```

Don't restate the code or narrate each step.
