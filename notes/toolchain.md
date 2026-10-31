# Toolchain

## Compiler and flags

**Confirmed for `SLUS_006.03`:** gcc 2.7.2 (PSX build) + ASPSX 2.56, `-O2 -G0`. Equivalent to
decomp.me's `PSYQ4.0` preset. Every banked shim function matches with it.

Evidence:
- **GCC version:** on the probe `Cmd_dequeue`, gcc 2.6.0 through 2.7.2 produce identical output and
  the closest result; 2.8.x and newer get progressively worse. Consistent with the PsyQ 4.0
  libraries Ghidra identified.
- **Assembler version:** `li v1,5` must assemble to `addiu v1,zero,5`. Plain maspsx defaults give
  `ori`; `--aspsx-version=2.56` gives `addiu`. Another PSX project landed on 2.56 too.
- **`-G0`:** the shim never addresses globals through `$gp`, not even in library code.
- **Not needed:** `-mips1 -mcpu=3000` (the `cc1` defaults: R3000, ISA 1, `-mgas -msoft-float`).
  `cc1` defaults to **`-G 8`**, so `-G0` must always be passed.
- Flags that made no difference on probes: `-f[no-]schedule-insns`, `-O1`.

`ROCK_NEO.EXE` was built separately and may differ (it has `.sdata`, so likely `-G8`); see
[rock_neo.md](rock_neo.md).

## Pipeline

`tools/cc.sh`: `cpp -P -undef -nostdinc -Iinclude` → `cc1 -quiet -O2 -G0` →
`maspsx --aspsx-version=2.56 --expand-div` →
`mips-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`.

Assembly from splat is assembled with `-EL -march=r3000 -mtune=r3000 -no-pad-sections -G0
-Iinclude`. Binary blobs (`assets/*.bin`) are wrapped with `objcopy -I binary`. The linked ELF is
`objcopy`'d to a raw binary and padded to a multiple of 2048 bytes (one CD sector).

Pinned in `tools/fetch_tools.sh` (into gitignored `tools/vendor/`): old-gcc release 0.17
(`gcc-2.7.2-psx`, sha256 `500a459b…`), maspsx, m2c, asm-differ, decomp-permuter (by commit).
Environment: WSL Ubuntu, GNU binutils 2.38 (`mips-linux-gnu`), splat 0.50.1 / spimdisasm 1.42.4,
Python venv in `.venv/`.

## splat configuration

Settings that took debugging, in `slus_006.03.yaml`:

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

## Symbol registry (`symbol_addrs.txt`)

- The repo is the source of truth for names; `symbol_addrs.txt` is hand-maintained (no comments,
  just splat attributes). Renaming touches the registry, `src/`, and `include/`; then re-split.
- Names that exist only in C or headers don't exist for the assembly. **PsyQ functions called
  from C need registry entries too** (e.g. `SsQuit`).
- Addresses below `0x80000000` (scratchpad, hardware registers) take `absolute:True`; `build.sh`
  turns those lines into linker definitions.
- `size:` matters for data (where a variable ends), rarely for functions (`stup0` ends in `break`,
  so it needs `size:0xC`).

## Tools

| Script | Does |
|---|---|
| `tools/split.sh` | Clears `asm/` and re-runs splat |
| `tools/build.sh` | Builds and compares SHA-1. **The authority on matching** |
| `tools/make_expected.sh` | Snapshots a matching `build/` into `expected/`; refuses otherwise |
| `tools/rebuild.sh` | Split + build + refresh `expected/`; use after renames and yaml changes |
| `tools/diff.sh <Func>` | asm-differ against `expected/`, cut at the function's end |
| `tools/objdump.sh <Func\|file.o>` | Real-instruction disassembly with relocations |
| `tools/m2c.sh <Func>` | m2c draft with all headers as context (`--target mipsel-gcc-c`) |
| `tools/cc.sh <in.c> <out.o>` | Compile one file with the matching toolchain |
| `tools/permuter_prep.py <Func>` | Builds `permuter/<Func>/` from a parked `NON_MATCHING` block |

Permuter: `.venv/bin/python tools/vendor/decomp-permuter/permuter.py permuter/<Func> -j N`. Its
output is preprocessed C; port the *change* into `main.c`, don't paste it. Apply partial
improvements to the draft and re-run `permuter_prep.py` to continue from the better base.

## Gotchas

- **asm-differ** imports its bundled example `diff_settings.py` (from the script's own folder)
  ahead of ours; `fetch_tools.sh` deletes it. In `-o` mode it won't take an end address, hence
  `diff.sh`'s cut-off. It shows pseudo-instructions (`li`), which can hide `ori`/`addiu`
  differences; confirm with `build.sh`.
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
