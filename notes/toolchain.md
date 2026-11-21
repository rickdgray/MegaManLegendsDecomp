# Toolchain

## Compiler and flags

**Confirmed for both executables:** gcc 2.7.2 (PSX build) + ASPSX 2.56, `-O2`. Equivalent to
decomp.me's `PSYQ4.0` preset. The shim is compiled with `-G8` (`cc1`'s default), `ROCK_NEO.EXE` with `-G32` (below).

Evidence:
- **GCC version:** on the probe `Cd_cmd_dequeue`, gcc 2.6.0 through 2.7.2 produce identical output
  and the closest result; 2.8.x and newer get progressively worse. Consistent with the PsyQ 4.0
  libraries Ghidra identified. See also "Compiler versions" under Gotchas.
- **Assembler version:** `li v1,5` must assemble to `addiu v1,zero,5`. Plain maspsx defaults give
  `ori`; `--aspsx-version=2.56` gives `addiu`. Another PSX project landed on 2.56 too.
- **Shim, `-G8`:** `cc1`'s default, so what Capcom got by not passing `-G`. The shim never
  addresses globals through `$gp`, not even in library code: maspsx gets no `-G`. Until
  2026-11-20 the build passed `-G0`; the whole shim matches either way, but `Movie_start` only
  with `-G8`: the value changes GCC's cost estimates, and with `-G8` it rebuilds `&Cd_result` before
  each `Cd_controlb_retry` call, as the target does, instead of keeping it in a saved register
  (found in CoastRedWood's fork).
- **Not needed:** `-mips1 -mcpu=3000` (the `cc1` defaults: R3000, ISA 1, `-mgas -msoft-float`).
- Flags that made no difference on probes: `-f[no-]schedule-insns`, `-O1`.
- **Untested** for ROCK_NEO: the flags ChrisNonyminus guessed (`-funsigned-char -fpeephole
  -ffunction-cse -fpcc-struct-return -fcommon`). `-funsigned-char` matters wherever plain `char`
  appears; nothing banked so far uses plain `char`.

### ROCK_NEO's `-G32`

- **Confirmed: `$gp` is used.** `gp` = `0x80097864`, and a raw disassembly has 697 `(gp)` accesses
  (the shim has 1). See [rock_neo.md](rock_neo.md) for the layout.
- **Confirmed: the limit is between 28 and 32 bytes; the build uses `-G32`.** GCC puts a string
  literal no larger than the limit in `.sdata`, and a larger one in `.rodata`:
  - `main`: literals up to 28 bytes in `.sdata` (`"%08x %04x %04x %04x %04x"`), a 45-byte one
    in `.rodata`.
  - `code_8006430C`: the 20-byte memory-card names in `.sdata`.
  - `scene`: the 33-byte stage paths in `.rodata`.
  `main` also reaches a 24-byte object through `$gp` (`D_80097864`). One value for every file fits
  all of it. (`-G8` was assumed at first, from `cc1`'s default; nothing had tested the value.)
- **Confirmed: ASPSX used `$gp` only for small data defined in the same file.** A global sits in
  `.sdata`/`.sbss` and is reached through `$gp` only from the file that defines it; an `extern` of
  any size gets `lui` + `%lo`. GNU `as` given `-G` instead uses `$gp` for every `.extern` that
  `cc1` declares within the limit, which is wrong.
- **So `cc.sh` passes `-G32` to `cc1` and to maspsx, and always `-G0` to GNU `as`.** maspsx, knowing
  the limit, writes `%gp_rel` itself for the file's own small data; GNU `as` then adds nothing.
  Proven on the first ROCK_NEO C, the `cd` file: every global it touches is an `extern` and
  comes out `lui`-based, matching.
- maspsx's `--dont-force-G0` is **not** passed. It only matters when maspsx runs the assembler
  itself (`--run-assembler`, where it otherwise forces `-G0`); `cc.sh` runs GNU `as` separately.
- **Confirmed: a C file that defines its own small data gets `$gp`**, with maspsx doing for ASPSX
  2.56 what the original shows:
  - Initialized small globals (`.sdata`) and `static`s (`.lcomm` → `.sbss`) are `$gp`-relative,
    with an offset too.
  - Taking an address (`la`) and indexing stay `lui`-based.
  - A common with an offset is `lui`-based.
  - String literals up to 32 bytes go to `.sdata`, larger ones to `.rodata`.
  All checked on probe files and in the real build (rock_neo_files.md, "Small data in C").
- **maspsx `--use-comm-section` (ROCK_NEO).** It keeps a tentative definition (`sint32 x;`) a common,
  as ASPSX left it for the linker's pool. Without it, maspsx defines the symbol locally in the
  file's `.sbss`.
- **maspsx `--max-comm-alignment 4` (ROCK_NEO).** maspsx gives each common GNU `as`'s implicit
  alignment (size rounded up to a power of two, capped at 16). psylink didn't align the pool that
  way (`D_80098AA8`, 16 bytes, at `0x80098AA8`; byte variables at odd addresses), and the
  pool's assembly definitions are 4-aligned, so every multi-word common defined in C made `ld`
  warn (first: `moji`'s `D_800989E0[4]`). The bytes never depend on it (the assembly definition
  wins); the flag only stops the false warning.

## Pipeline

`tools/cc.sh`: `cpp -P -undef -nostdinc -Iinclude/<target> -Iinclude` → `cc1 -quiet -O2 -G0` →
`maspsx --aspsx-version=2.56 --expand-div` →
`mips-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`.
For `rock_neo.exe`: `cc1 ... -G32`, `maspsx ... -G32 --use-comm-section`, `as ... -G0`. Overrides for experiments only:
`CC1_EXTRA`, `CC1`, `ASPSX_VERSION` (see the script's header).

Assembly from splat is assembled with `-EL -march=r3000 -mtune=r3000 -no-pad-sections -G0
-Iinclude`. Binary blobs (`assets/<t>/*.bin`) are wrapped with `objcopy -I binary`. The linked ELF
is `objcopy`'d to a raw binary and padded to a multiple of 2048 bytes (one CD sector).

Pinned in `tools/fetch_tools.sh` (into gitignored `tools/vendor/`): old-gcc release 0.17
(`gcc-2.7.2-psx`, sha256 `500a459b…`), maspsx, m2c, asm-differ, decomp-permuter (by commit).
Environment: WSL Ubuntu, GNU binutils 2.38 (`mips-linux-gnu`), splat 0.50.1 / spimdisasm 1.42.4,
Python venv in `.venv/`.

Header search order (`include/<target>/` if any, before `include/`) and the rule for shared headers are in
`CLAUDE.md` ("Types and headers").

## splat configuration

Settings that took debugging, in `config/slus_006.03/slus_006.03.yaml` (ROCK_NEO's own are in
[rock_neo.md](rock_neo.md)):

- **Alignment:** `ld_align_section_vram_end: False` and `ld_align_segment_vram_end: False`. The
  defaults insert `ALIGN(., 16)` after each section and shift the code.
- **Code start:** `create_config` guessed it too early. Jump tables decode as valid instructions;
  check where the first real function begins.
- **BSS:** the last subsegment of the code segment is
  `{ start: <end of data>, type: bss, name: ..., vram: <bss start> }` with zero file bytes, so
  splat infers its size from the segment's `bss_size`. The explicit `vram` is required (without
  it, no `.s` is written). Don't also put `bss_size` on the subsegment (error when inferable).
  `ld_bss_is_noload: True`.
- **Sector padding:** a separate top-level `bin` segment covering the file's zero tail.
- **C files:** `include_asm_macro_style: maspsx_hack`; `include/common.h` must include
  `include_asm.h`. A C file's read-only data is a `.rodata` subsegment with the same name (that's
  how a jump table travels with its function).
- **PsyQ library split:** one `asm` subsegment per library object, each paired with its own
  `rodata` subsegment of the same name. Boundaries come from the PSX loader's
  `NAME_OBJ_<offset>` labels in Ghidra (object start = label address − offset). Plate comments
  ("Possible X.OBJ/...") are unreliable. Small unlabeled objects get merged into the previous
  one, which is safe for matching.
- **8-byte rule:** an object's read-only data starts on an 8-byte boundary. Fix "jumptables not
  aligned properly file-wise" by moving that object's rodata start to the 8-byte boundary right
  after the previous object's last referenced item.

## Symbol registry (`config/<target>/symbol_addrs.txt`)

- The repo is the source of truth for names; each target's `config/<target>/symbol_addrs.txt` is
  hand-maintained (no comments, just splat attributes). Renaming touches the registry,
  `src/<target>/`, `include/` and `notes/` (`tools/rename.py` does all four); then re-split. The
  overlays link against ROCK_NEO's registry, so a ROCK_NEO rename also rewrites the overlay
  sources and needs their re-split: `rename.py` prints the `rebuild.sh` line with every target.
- Names that exist only in C or headers don't exist for the assembly. **PsyQ functions called
  from C need registry entries too** (e.g. `SsQuit`).
- **`absolute:True`** marks addresses outside the target's image (shim `0x80010000`–`0x8005DA40`,
  ROCK_NEO `0x80010000`–`0x800D9000`): scratchpad (`System_timer` `0x1F800002`), hardware
  registers, and RAM no executable section covers (ROCK_NEO's `Thread_current` `0x801F8300`).
  `build.sh` turns those lines into linker definitions; `rename.py` adds the attribute itself
  for such addresses.
- **Literal addresses in C.** For those addresses the original source used constants, not symbols:
  the shim's scratchpad (`scratch.h`), ROCK_NEO's threads (`system.h`), the stage `IDX` table at
  `0x8015C000` and the scratchpad map window (`stage.h`). Two signs in the assembly: the address
  is built with `lui`/`ori` (a symbol gives `lui %hi` + `%lo(sym)`), and indexed accesses come out
  as `addu $at,reg,$at` (maspsx's order for a constant; a symbol gives `addu $at,$at,reg`).
  Write them as macros named like variables (`#define Thread_current (*(THREAD_WORK **)0x801F8300)`).
  The registry entry stays, for the code still in assembly. Addresses inside the image (`.data`,
  `.bss`) stay `extern` symbols.
- `size:` matters for data (where a variable ends), rarely for functions (`stup0` ends in `break`,
  so it needs `size:0xC`).

## Tools

Every script takes the target as an optional first argument (`<t>`: `rock_neo.exe`, the default when left out, `slus_006.03`, or an overlay such as `r3_st05`: every folder in `config/` other than the executables', its yaml naming the archive that holds the chunk (`archive:`) and any archives with the same bytes (`duplicates:`); `tools/targets.py` and `tools/target.sh` both read the list from there). A name shaped like a target that isn't one (`r3_st5`) is an error, not the default. `build.sh`, `rebuild.sh`, `split.sh` and `format.sh` also take several targets or a group: `all`, `executables`, `overlays`. `progress.py` takes several targets or a group too, and without one reports every target (one line each, with a total that counts the shared stage code once). `ctx.sh`, `permute.sh` and `permuter_prep.py` take any one target, an overlay included.
`tools/target.sh` derives the paths from it: `config/<t>/<t>.yaml`, `config/<t>/symbol_addrs.txt`, `src/<t>/`,
`asm/<t>/`, `build/<t>/` (linker script, ELF, map, objects, `undefined_*_auto.txt`),
`assets/<t>/`, `expected/<t>/`, and the final binary `build/<t>/<T>`, named like the disc file
(`build/slus_006.03/SLUS_006.03`). Exceptions: `fetch_tools.sh`, `dupe_scan.py` and the
PowerShell scripts aren't per-target. Run the Python tools with `.venv/bin/python`.

| Script | Does |
|---|---|
| `tools/split.sh <t>` | Clears `asm/<t>/` and re-runs splat |
| `tools/build.sh <t> [<t> ...]` | Builds the objects the linker script names and compares SHA-1. **The authority on matching**. Several targets: one MATCH/MISMATCH line each, fails if any doesn't match |
| `tools/reach.py [PATH ...] [--command]` | Which targets a change can reach (the working tree's uncommitted changes, or the given files), so you know what to build: `config/<t>/`, `src/<t>/` → t; ROCK_NEO's registry → it and every overlay; `src/stage_common/<f>.c` → the overlays whose yaml links it; a header → the targets whose C includes it; `tools/`, `*.inc` → everything. `--command` prints the `build.sh` line |
| `tools/make_expected.sh <t>` | Snapshots a matching `build/<t>/` into `expected/<t>/build/<t>/`; refuses otherwise |
| `tools/rebuild.sh <t> [<t> ...]` | Split + build + refresh `expected/<t>/` + format, then regenerate `functions.csv` (if every target's ELF exists); use after renames and yaml changes. Several targets: quiet, one MATCH/FAILED line each |
| `tools/diff.sh <t> <Func>` | asm-differ against `expected/<t>/`, cut at the function's end |
| `tools/objdump.sh <t> <Func\|file.o>` | Real-instruction disassembly with relocations |
| `tools/m2c.sh <t> <Func>` | m2c draft with all headers as context (`--target mipsel-gcc-c`) |
| `tools/cc.sh <t> <in.c> <out.o>` | Compile one file with the target's matching toolchain |
| `tools/format.sh <t>` | clang-format on `src/<t>/` and `include/`; an overlay also formats `src/stage_common/` |
| `tools/rename.py <t> OLD NEW [attr]` / `<t> -f FILE` | Renames in `config/<t>/symbol_addrs.txt`, `src/<t>/`, `include/`, `notes/`; `-n` for a dry run. New registry lines get `type:func` (for `func_`) and `absolute:True` (outside the image). ROCK_NEO renames also rewrite the overlay sources; a shared stage-code name is renamed in every overlay registry that has it; an overlay's splat default name stays in that overlay (every stage loads at `0x80100000`, so the same default name means another function elsewhere) and notes mentioning it are only listed. Refuses a name ROCK_NEO and the overlays would both define. Ends with the `rebuild.sh` line to run |
| `tools/permuter_prep.py <t> <Func> [--src FILE]` | Builds `permuter/<t>/<Func>/` from a parked `NON_MATCHING` block in `FILE` (e.g. `src/rock_neo.exe/cd.c`; without it, searches every C file the target compiles, an overlay's shared stage files included). `base.c` is the file's preamble plus the draft |
| `tools/preamble.py FILE` | Prints a C file's preamble: everything before its first function, `INCLUDE_ASM` or parked block (includes, its own small data and pool definitions, file-local prototypes). Used by `permuter_prep.py` and `ctx.sh` |
| `tools/extract.sh [--force]` | Once per clone: `dumpsxiso` extracts the disc into `disc/extracted/` (skipped when the executables are there, unless `--force`), `extract_overlays.py` writes the overlays' chunks to `disc/overlays/`, then every hash is checked against its yaml's `sha1:` (executables, overlays, duplicate archives). `make extract` |
| `tools/extract_overlays.py [--tsv FILE]` | Writes each `CDDATA/DAT/*.BIN` archive's code chunk to `disc/overlays/<ARCHIVE>.BIN` and lists load address, size, `jr ra` count, SHA-1 and identical groups ([disc.md](disc.md), "Code overlays"). Not per-target |
| `tools/dupe_scan.py [--tsv FILE] [--runs] [--list N]` | Duplicate functions across both executables and every overlay (splits the overlays into functions itself): exact and shape groups, savings in functions and bytes, runs shared between programs; `--tsv` writes one row per function ([overlays.md](overlays.md)). Build both targets and run `extract_overlays.py` first |
| `tools/function_list.py [-o FILE]` | Every Capcom function in the game (both executables and every distinct overlay) as a CSV: Program (the target, or `stage_common` for the shared stage files, listed once), File (the yaml subsegment), Confidence (the first word of its yaml comment), Function (default `func_` name), Name (blank if not renamed), Decompiled (has C, matching or parked), Matched, Reviewed, Score, Depth. Build every target first (`make`); `rebuild.sh` runs it |
| `tools/func_metrics.py [--top N]` | Score (estimated difficulty: weighted instruction features, formula in its docstring) and Depth (longest chain of calls into functions with no C yet; 0 = ready) for every Capcom function of every target (from the ELFs and yamls); prints a summary and how the score separates parked from matched functions |
| `tools/overlay_files.py [--overlay ST03]` | Research tool, not used by the other tools: its own proposed split of the overlays into source files (from the raw chunks, not the yamls): confirmed by Capcom's source, common files shared between overlays, and regions with no evidence yet ([overlays.md](overlays.md), "Source files") |
| `tools/progress.py [<t> ...]` | Bytes and functions of Capcom code compiled from matching C: per source file for one target, one line per target for several or a group (default `all`). Excludes PsyQ objects and hand-written assembly (subsegments named `asm_...`). Build first |
| `tools/batch_run.py <t> <file.c ...> | --all` | Unattended decompilation batches; see [agents.md](agents.md) |
| `tools/review.py <t> NAME...` | The owner marks functions reviewed (`reviewed.txt`, keyed by address); `--changed` lists reviewed functions whose C was edited since, `--remove` drops reviews. Feeds `functions.csv`'s Reviewed column (Yes / Changed) and `progress.py`. Agents may not run it |
| `tools/callers.py <t> NAME...` | Who uses a function (other files, data tables, and for ROCK_NEO the overlays: their C and assembly, plus a raw scan of `disc/overlays/` for the duplicate archives), and so global or static naming. Works for overlay targets (their own files plus the shared stage code they link) |

Permuter: `.venv/bin/python tools/vendor/decomp-permuter/permuter.py permuter/<t>/<Func> -j N`.
Its output is preprocessed C; port the *change* into `src/<t>/<file>.c`, don't paste it. Apply
partial improvements to the draft and re-run `permuter_prep.py` to continue from the better base.

## GTE (coprocessor 2) code

GCC can't emit GTE instructions; Capcom's C used PsyQ's inline macros (`inline_c.h`: `gte_ldv0`,
`gte_rtps`, ...; volatile inline asm, which DMPSX patched into real opcodes at the time). Ours are
self-written in `include/psyq/inline_c.h`, under Sony's names, each with the exact sequence found in
the game (registers, nops, order), and added only as a function needs one. GNU `as` assembles the
COP2 mnemonics directly (`ctc2`, `lwc2`, `mfc2`, `swc2`, and commands as `cop2 0x...`, e.g. RTPS =
`cop2 0x0180001`). Since the macros are volatile, their order in C is their order in the binary;
plain loads and stores between them can still move. First user: `func_80035508`.

## `$at` and `.set noat`

`$at` (register 1) is the assembler's scratch register for expanding pseudo-instructions. Under
`.set at` (the default) GNU `as` warns when code names it; `.set noat` says the code manages it.
maspsx writes ASPSX's `li $at,K` + `sltu rd,rs,$at` (for `sltu` with a negative constant) without
`.set noat`, unlike its other `$at` expansions; `cc.sh` wraps such pairs with an `awk` filter. The
bytes don't change; the build has no assembler warnings.

## Gotchas

- **Scores are line edit distances, not closeness.** asm-differ's header score (and the
  permuter's) counts weighted differing lines between the two listings. A draft one register swap
  away from matching can score worse than one missing a whole statement, and `diff.sh`'s score
  also covers more than the function. Use scores only to compare attempts at the same function;
  read the flagged lines to judge how close it is.
- **asm-differ** imports its bundled example `diff_settings.py` (from the script's own folder)
  ahead of ours; `fetch_tools.sh` deletes it. Ours reads the target's paths from `DIFF_*`
  environment variables that `diff.sh` exports, so run asm-differ through `diff.sh`. In `-o` mode
  it won't take an end address, hence `diff.sh`'s cut-off. It shows pseudo-instructions (`li`),
  which can hide `ori`/`addiu` differences; confirm with `build.sh`.
- **decomp.me's** Compilation tab normalizes pseudo-instructions too; its objdiff tab is byte-level.
- **`expected/`** keeps old names after a rename; refresh it, or `diff.sh` shows an empty target.
- **Shell:** an awk program in single quotes can't contain apostrophes, even in comments. An
  `awk ... exit` mid-pipe can SIGPIPE the writer and kill a `pipefail` script; read all input.
- **WSL on `/mnt/c`:** set `git config core.fileMode false` and keep `.gitattributes`
  (`* text=auto eol=lf`), or WSL git sees mode and line-ending changes Windows git doesn't.
- **Ghidra** hides dead stores in its pseudocode, and can't see parameters of BIOS call stubs
  (they pass `a0`–`a3` straight through). The assembly is the truth.
- **Ghidra's PsyQ matcher** gives every empty function (`jr ra; nop`) the same bogus match
  (`VM_VIB.OBJ/SsUtVibrateOff`). Ignore matches on empty functions.
- **`-fno-expensive-optimizations` (tested, rejected as the toolchain setting):** a three-call
  probe showed it makes GCC rebuild a repeated constant address before each call, as the target
  does in `Movie_start`, and `Movie_start` matches with it. But it breaks 8 banked functions across
  every region (`Disp_env_set`; `cd_cmd_play_movie`, `Movie_dct_out_callback`, `Cd_sync_cb`;
  `intro_copyright`, `intro_wait_idle`, `intro_play_movie`, `intro_launch_game`), so it's a
  proxy for one cost decision, not Capcom's setting, and not evidence of a separately compiled
  module. It doesn't affect `Movie_frame_upload`, `Cd_cmd_dequeue`, or `Intro_init`.
  Method: build the same source with and without the flag, and compare per-function instruction
  words in the two objects (pass flags as `CC1_EXTRA=... ./tools/build.sh slus_006.03`, never a
  bare shell variable).
- **Compiler versions (decomp.me, `Movie_start`):** gcc 2.6.0 through 2.7.2.3 give identical
  output (all with the `s0` difference); 2.5.7 is worse, with a different allocation order; 2.8.x
  and later are very different. ASPSX version makes no difference. Confirms the gcc 2.7.2 family
  and rules out a toolchain explanation for the parked functions: their differences are in the
  source.
