# Code overlays

The 44 distinct code overlays in `CDDATA/DAT/*.BIN` (the stages `ST*`, the SHL modules `ARM*R`,
`SUPPORT`): their layout, how they are split into functions, and the duplicates between them and
ROCK_NEO. Extraction and the per-file table: [disc.md](disc.md), "Code overlays".
Tools: `tools/extract_overlays.py`, then `tools/dupe_scan.py` (see [toolchain.md](toolchain.md)).

## Layout

- **Confirmed:** word 0 is the overlay's **ID**: `ST00` = `0x13` ... `ST1E` = `0x31` in order;
  `ARM*R` = `0x5`–`0x10` (`ARM01R` = `0x7`, ..., `ARM10R` = `0x10`).
- **Confirmed:** read-only data (pointer and jump tables) comes next, then the code, then data.
  Same section order as ROCK_NEO (`.rodata`, `.text`, `.data`). `ARM*R` have no rodata: their
  code starts at word 1. The code ends after the last `jr ra`.
- **Confirmed:** most stages' code begins with a setup function that stores pointers to the
  overlay's tables into the scratchpad, `0x1F800058`–`0x1F80006C` (`lui v0`/`addiu v0`/`sw
  v0, 0x58(at)` ...). Exceptions: `ST0C` (starts with a function with a frame), `ST1B` (two
  empty functions first), `SUPPORT`.
- **Open:** how ROCK_NEO finds the setup function; it is not at a fixed offset.
- **Confirmed:** overlays never use `$gp` (no `$gp`-based loads or stores in any of them).

## Splitting into functions

Overlays have no symbols, so `dupe_scan.py` splits them itself:

- **Code start:** the first word of the unbroken run of plausible instructions that ends at the
  first `jr ra`, never before word 1. Rodata pointers (`0x80xxxxxx`) decode as a load based on
  `$zero`, which GCC never emits, and they stop the scan; so do invalid encodings (`ST1A`'s small
  byte tables).
- **Functions:** cut after each `jr ra` and its delay slot, unless a branch earlier in the
  function points further on. **Confirmed** on ROCK_NEO: 1147 of 1151 Capcom function starts
  found, none invented. The four missed are hand-written (`asm_fastmem`, the `2MBYTE.OBJ` stubs).
- Result: exactly one function per `jr ra` in every overlay, **8,842 functions**; 10,023 with
  both executables' Capcom code.
- **Open:** about ten `jal`s in stage code (`ST03`, `ST04`, `ST08`, `ST0B`, `ST0D`, `ST13`, `ST14`,
  `ST1A`, `ST1D`) target the middle of a function, often a delay slot or a round address
  (`0x80102000`, `0x80103000`, `0x8010D9F8` in both `ST13` and `ST14`). Calls into code loaded over
  the stage at a fixed address? They don't affect the split.

## Duplicates

`dupe_scan.py` gives each function two keys (details in its docstring):

- **exact:** identical except for the program's own addresses. ROCK_NEO's code and data (below
  `0x800D8800`) are the same in every program and stay in the key, so the same call into ROCK_NEO
  is required. Local calls compare by the callee's own key. Same exact key = the same C.
- **shape:** opcodes and registers only. Same code with different constants, calls or globals.
  Weak for small functions.

Results (2026-11-10; empty `jr ra; nop` functions, 363 of them, left out):

| | Functions | Bytes | Share of bytes |
|---|---|---|---|
| Not yet matched | 9,574 | `0x245B54` | 100% |
| One per exact group | 6,546 | `0x1C1EB4` | 77% |
| One per shape group | 4,305 | `0x14AA20` | 57% |

- **Confirmed:** 726 exact groups with 2+ members cover 3,755 functions. Members differ only in
  address-bearing instructions (spot-checked: `j`, `jal`, `lui`, loads/stores/`addiu` through them).
- **Shared source files.** Duplicates come in **runs**: the same functions in the same order in
  several stages. These are likely common Capcom files linked into each stage. One block,
  `ST03` `0x801082F8`–`0x8010A45C`, recurs in 18 stages (`ST03`–`ST06`, `ST08`, `ST0A`–`ST0D`, `ST0F`,
  `ST10`–`ST13`, `ST19`, `ST1A`–`ST1C`), split into shorter runs wherever one function differs.
  Up to 46% of a stage's code is in shared runs (`ST1C` 46%, `ST11` 45%, `ST0C` 42%).
  Their edges are strong file-boundary evidence for the overlays. `dupe_scan.py --runs` lists
  them.
- **ROCK_NEO and overlays:** only 6 exact groups span both, covering 185 overlay functions. Most are
  small wrappers; the largest is `func_80068120` (`0x124` bytes), also at `ST00` `0x80100614`.
  Stages mostly call ROCK_NEO rather than carrying copies of its code.
- **Not near-copies:** `ST0C`/`ST0D` share 48 exact keys of 219, `ST11`/`ST12` 61 of 162. Equal
  `jr ra` counts were a coincidence.
- The shim's addresses mean nothing elsewhere, so here a shim function only matches when it
  uses no addresses; `find_dupes.py` covers shim ↔ ROCK_NEO with relocations.
