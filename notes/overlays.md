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

## Source files

Boundaries inside the overlays, from two kinds of evidence. `tools/overlay_files.py` computes the
split (method in its docstring) and `functions.csv` carries it (Program, File, Confidence). With the
current thresholds: 344 shared segments, 263 regions without evidence, 2 files from source.

### Confirmed by Capcom's source (TCRF)

The source fragments on TCRF (from the Japanese `ST1E.BIN`, where they are leftover text, not
code) are compiled into US overlays:

- **`eve19.c` = `ST1A` `0x8012B8E4`–`0x8012C2EC`**, both edges. Found by its `eve19_main_tbl`
  (`0x801396CC`: 10 pointers in the source's pattern A B C D D E F D D G) and `eve19_move_tbl`
  just before it (`eve19_main` `0x8012B920`, `eve19_end` `0x8012B95C`). The file's 12 functions, in
  source order, are exactly the 12 there: `StXX_eve19_move` `0x8012B8E4`, `eve19_main`, `eve19_end`,
  `eve19_main_area_00`/`01`/`02`/`05`/`06`/`09` (`0x8012B97C` ... `0x8012C03C`), `eve19_main_dummy`
  `0x8012C1B4`, `check_block` `0x8012C1C0`, `check_swing_camera` `0x8012C228`.
- **`EM09_49.C` ends at `ST1E` `0x80101AF0`.** Its last functions, by size and calls:
  `StXX_em26_49_move` `0x80101554`, `StXX_em2d_49_move` `0x80101600`, `StXX_em34_49_move` `0x801016EC`,
  `StXX_em38_49_move` `0x80101798`, `StXX_em5c_49_move` `0x80101844` (each calls `Model_Shadow_Trans` `0x8002C8CC` with
  `50, 683`), `StXX_set_shl38` `0x80101930` (calls `0x80031518`, so that is `Open_SHL_WORK`),
  `StXX_shl38_move` `0x801019C0` (calls `0x8002F9C4` = `Model_work_init`, `rsin`, `rcos`,
  `ScaleMatrix`, as in the source). Its start is before `0x80101350` (the fragment starts mid-file).
- **Confirmed: `Model_Shadow_Trans` is `0x8002C8CC`** (fixed in the registry, which had it at
  `0x8002C794`). The source calls `Model_Shadow_Trans(wk_p, 50, 683, 0)`, and in `ST1E` those calls go to
  `0x8002C8CC`; overlays call it 268 times. `func_8002C794`, a sibling with the same prologue, is
  called once, from ROCK_NEO, and never from an overlay.
- The 0x3C-byte shape found in 35 programs is the `StXX_*_move` dispatcher
  (`tbl[wp->routine_0](wp)`), one per event or enemy object. Not one per file: `EM09_49.C` has five.

### Common files (shared between overlays)

For each overlay function: the set of other overlays holding its shape (`dupe_scan.py`'s shape key),
with generic shapes (in more than 20 programs, such as the dispatcher) neutral. Each overlay is cut
where that set changes; segments with the same member set are one common file, and it should
appear once in each member, with about the same size.

- **58 common files** of 3+ functions and 0x200+ bytes, each in 2–18 overlays, cover **51% of all
  overlay code** (`0xFEA5C` of `0x1F225C` bytes). Their edges are file boundaries (or a run of files
  always linked together).
- The largest: 66–67 functions, `0x29D4`–`0x2A10` bytes, in 18 stages (`ST03` `0x80107BC0`–`0x8010A594`;
  `ST03`–`ST06`, `ST08`, `ST0A`–`ST0D`, `ST0F`, `ST10`–`ST13`, `ST19`, `ST1A`–`ST1C`). It holds about a
  dozen dispatchers, so it is probably a group of small object files (`StXX_*`) always linked together.
- The other 49% is code found in one overlay only, where this method sees no boundaries.
- **Not evidence:** identical non-trivial functions within one overlay (585 functions in 28
  overlays). The largest pairs are neighbours (`ST09` `0x80113F64`/`0x8011417C`), copy-paste inside
  one file, not a static helper per file.
