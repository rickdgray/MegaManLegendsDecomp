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
  small wrappers; the largest is `screen_tile_draw` (`0x124` bytes), also at `ST00` `0x80100614`.
  Stages mostly call ROCK_NEO rather than carrying copies of its code.
- **Not near-copies:** `ST0C`/`ST0D` share 48 exact keys of 219, `ST11`/`ST12` 61 of 162. Equal
  `jr ra` counts were a coincidence.
- The shim's addresses mean nothing elsewhere, so here a shim function only matches when it
  uses no addresses; the retired `find_dupes.py` compared shim ↔ ROCK_NEO with relocations.

## Source files

Boundaries inside the overlays, from two kinds of evidence. The yamls' subsegments are the split
the build uses (and `functions.csv` lists); `tools/overlay_files.py` is the research tool that
proposes boundaries from the raw chunks (method in its docstring). With its current thresholds: 344 shared segments, 263 regions without evidence, 2 files from source.

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
  `0x8002C8CC`; overlays call it 268 times. `Pl_Shadow_Trans`, a sibling with the same prologue, is
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

### File boundaries from jump-table alignment

- **Confirmed:** `cc1` (gcc 2.7.2) writes `.align 3` before each jump table, and retail aligns the
  tables 8 bytes counted from the start of the object's `.rodata`, not in the module. Eight code
  pieces that several overlays share (`tools/overlay_files.py`) hold two or more jump tables and sit
  at both alignments (first table at 0 and at 4 modulo 8 in different overlays), with the same layout
  counted from the first table (for example the piece at `0x80104A08` in `ST00` and its copy in
  `ST09`).
- **So:** where a table is not 8-aligned counted from its yaml file's first `.rodata` byte, a new
  object starts somewhere after the last table before it and no later than the function that owns
  it. The build cannot say where in that range: every position built gives the same bytes, once
  the functions called across the cut are declared (a missing declaration changes the code: a cut of
  `ST05` at `0x8012B544` needs one for `func_8012B484`).
- **Placed by this rule:** the `c` subsegments whose yaml comment names a jump-table alignment
  restart or code shared with another stage. Some cuts sit at an edge of code shared with another
  stage (`tools/overlay_files.py` shows most of those edges; three come from comparing the
  functions one by one, see the second table below: `ST0B` `0x801186E8`, `ST03` `0x8010E0A8`,
  `ST1B` `0x80106E14`), some at a
  routine dispatcher (`tbl[wp->routine_0](wp)`) whose table lists the functions after it, and the
  rest just before the table's function. Other edges and dispatchers lie in some of the ranges and
  were not used, so a `low` position is a choice inside its range, even where its comment names a
  sign at that address. `medium` marks the few cuts where a second sign fixes the place more
  firmly (a copy of the code in another overlay, or a file that starts at the same piece there).
- **Open: `r3_st03_A594.c` keeps its setting.** A zero word follows the jump table of
  `func_8010A5D0` (`0x8010024C`, zero word at `0x80100260`), and no file boundary explains it: the
  table of `func_8010AA28` in the next C file (`r3_st03_A9A8`, `0x80100264`) is 8-aligned counted
  from the first table, as if both functions were in one object. But the three routines of
  `src/stage_common/stcom37.c` (`0x8010A8D4`) lie between the two functions in the code, and the
  actor's two routine tables (`D_80117060`, `D_8011706C`) list those routines together with
  functions before and after them. `ST05` and `ST06` show the same routine-table shape. So
  `stcom37.c` is probably not a file of its own but part of a larger file in each stage. Four
  forms build and match without the setting, and none is used. Three need a decision about the
  layout of shared code: one C file that includes `stcom37.c` (the yaml then does not link a
  file the stage compiles); the three routines in a shared header that `stcom37.c` and the
  stage file both include (code in `include/`); a second copy of the routines inside
  `r3_st03_A594.c` (shared code lives twice). The fourth, the zero word as a yaml `rodata`
  piece, only moves the pad to another place.

#### The range of each cut

A file may start at any function from "earliest" to "latest" (the function that owns the jump
table). "Positions" counts the functions in that range. "Built" says which of them were built and
compared: every position, or the two ends and the chosen one. With no cut the target does not match.
One position needs a declaration to match (`ST05` `0x8012B544`, above). Three rows have one position:
there the tables fix the start, and `low` says only that nothing else supports a file start there.
The builds were made on `9332fde`, one file cut at a time; 17 positions of 10 cuts were built
again on `659b50e` with the same result. The overlay yamls did not change between the two.

| Target | New file | Earliest | Latest | Positions | Built | Confidence |
|---|---|---|---|---|---|---|
| `r3_st00` | `r3_st00_10C4` | `0x80100598` | `0x801010C4` | 23 | both ends | low |
| `r3_st00` | `r3_st00_A68C` | `0x8010A2D4` | `0x8010A9C8` | 5 | both ends | medium |
| `r3_st02` | `r3_st02_3704` | `0x80101FD8` | `0x80103D8C` | 89 | both ends | low |
| `r3_st03` | `r3_st03_48E0` | `0x801041C8` | `0x801048E0` | 8 | both ends | low |
| `r3_st03` | `r3_st03_B444` | `0x8010B2CC` | `0x8010B444` | 3 | every position | low |
| `r3_st03` | `r3_st03_DE18` | `0x8010D020` | `0x8010DE18` | 19 | every position | low |
| `r3_st03` | `r3_st03_E0A8` | `0x8010E014` | `0x8010E198` | 3 | every position | low |
| `r3_st04` | `r3_st04_61D8` | `0x80106048` | `0x801061D8` | 3 | both ends | low |
| `r3_st04` | `r3_st04_9FA0` | `0x8010967C` | `0x8010A044` | 15 | every position | medium |
| `r3_st04` | `r3_st04_A248` | `0x8010A248` | `0x8010A32C` | 4 | every position | low |
| `r3_st05` | `r3_st05_13E6C` | `0x801137AC` | `0x80113E6C` | 3 | every position | low |
| `r3_st05` | `r3_st05_19BE0` | `0x80117130` | `0x8011A194` | 45 | both ends | low |
| `r3_st05` | `r3_st05_2B078` | `0x8012AFA0` | `0x8012B314` | 6 | every position | low |
| `r3_st05` | `r3_st05_2BD2C` | `0x8012B44C` | `0x8012BD2C` | 11 | every position | low |
| `r3_st06` | `r3_st06_1DAC` | `0x80101A38` | `0x80101DAC` | 4 | every position | low |
| `r3_st06` | `r3_st06_2430` | `0x8010205C` | `0x8010246C` | 10 | every position | low |
| `r3_st06` | `r3_st06_3438` | `0x80102878` | `0x80103438` | 24 | every position | low |
| `r3_st06` | `r3_st06_5D20` | `0x80103710` | `0x80105D20` | 67 | every position | low |
| `r3_st06` | `r3_st06_6618` | `0x80106618` | `0x80106618` | 1 | every position | low |
| `r3_st06` | `r3_st06_7B94` | `0x80107418` | `0x80107B94` | 13 | every position | low |
| `r3_st06` | `r3_st06_E4C4` | `0x8010D7E8` | `0x8010E4C4` | 18 | every position | low |
| `r3_st06` | `r3_st06_EE38` | `0x8010EA84` | `0x8010EE38` | 5 | every position | low |
| `r3_st06` | `r3_st06_FF90` | `0x8010EF94` | `0x8010FF90` | 13 | every position | low |
| `r3_st06` | `r3_st06_1146C` | `0x80110A54` | `0x8011146C` | 10 | every position | low |
| `r3_st06` | `r3_st06_1335C` | `0x801129A4` | `0x8011335C` | 15 | every position | low |
| `r3_st06` | `r3_st06_13EA0` | `0x801134B8` | `0x80113EA0` | 15 | every position | low |
| `r3_st06` | `r3_st06_142A8` | `0x801140DC` | `0x801142A8` | 4 | every position | low |
| `r3_st06` | `r3_st06_17290` | `0x8011710C` | `0x80117290` | 3 | both ends | low |
| `r3_st08` | `r3_st08_1FA4` | `0x80101F84` | `0x80102498` | 10 | every position | low |
| `r3_st0b` | `r3_st0b_1234` | `0x80100A64` | `0x80101270` | 16 | both ends | low |
| `r3_st0b` | `r3_st0b_186E8` | `0x80117830` | `0x80118D40` | 38 | both ends | low |
| `r3_st14` | `r3_st14_CC4` | `0x8010098C` | `0x80100D00` | 7 | every position | low |
| `r3_st16` | `r3_st16_C84` | `0x80100970` | `0x80100C84` | 9 | every position | low |
| `r3_st17` | `r3_st17_F10` | `0x80100828` | `0x80100F10` | 9 | every position | low |
| `r3_st17` | `r3_st17_1130` | `0x80101130` | `0x80101130` | 1 | every position | low |
| `r3_st17` | `r3_st17_1A14` | `0x8010130C` | `0x80101E74` | 16 | every position | medium |
| `r3_st17` | `r3_st17_2D3C` | `0x80102D3C` | `0x80102D3C` | 1 | every position | low |
| `r3_st17` | `r3_st17_39E0` | `0x80102FD8` | `0x801039E0` | 10 | every position | low |
| `r3_st17` | `r3_st17_5638` | `0x80104498` | `0x80105A0C` | 19 | every position | low |
| `r3_st17` | `r3_st17_6B70` | `0x80105CF8` | `0x80106B70` | 18 | every position | low |
| `r3_st17` | `r3_st17_702C` | `0x80106E94` | `0x8010702C` | 4 | every position | low |
| `r3_st17` | `r3_st17_8BD4` | `0x8010787C` | `0x80108BD4` | 22 | every position | low |
| `r3_st17` | `r3_st17_9334` | `0x8010919C` | `0x80109334` | 4 | every position | low |
| `r3_st17` | `r3_st17_C36C` | `0x8010971C` | `0x8010C36C` | 55 | every position | low |
| `r3_st1a` | `r3_st1a_3CB8` | `0x80101D40` | `0x80103CB8` | 47 | every position | low |
| `r3_st1a` | `r3_st1a_523C` | `0x80103ECC` | `0x80105278` | 18 | every position | low |
| `r3_st1a` | `r3_st1a_13460` | `0x80111BF0` | `0x80113460` | 33 | both ends | low |
| `r3_st1a` | `r3_st1a_17910` | `0x801165AC` | `0x80117BCC` | 41 | both ends | low |
| `r3_st1a` | `r3_st1a_1C870` | `0x8011BA74` | `0x8011C870` | 10 | both ends | low |
| `r3_st1b` | `r3_st1b_22D4` | `0x80101EFC` | `0x801022D4` | 8 | every position | low |
| `r3_st1b` | `r3_st1b_6E14` | `0x80106A34` | `0x80106F04` | 13 | every position | low |
| `r3_st1d` | `r3_st1d_2F24` | `0x80102D5C` | `0x801033E4` | 6 | both ends | medium |

#### How the three edges outside `tools/overlay_files.py` were checked

Method: split every overlay into functions and give each function the two keys of
`tools/dupe_scan.py` (exact: the instructions with their immediates, the program's own addresses
masked; shape: opcodes and registers only). Byte-identical overlays are left out, as that tool
does. A shared run is a row of functions that follow each other in both stages with equal shape
keys. Functions of 8 bytes or less, and shapes that occur in more than 20 programs, extend a run
but do not count. A run counts with two or more counted functions of two or more
shapes, `0x200` bytes or more, and at least one exact pair. An edge is where such a run starts or
ends. Run on `659b50e`.

| Stage | Edge | Shared run here | Other stage | Run starts there | Counted functions (exact) | Bytes of the counted functions | At the edge |
|---|---|---|---|---|---|---|---|
| `ST0B` | `0x801186E8` | `0x801186E8`-`0x80119050` | `ST0C` | `0x80101350` | 13 (11) | `0x968` | this run starts; another run shared with `ST0C` (`0x801183FC`-`0x801186E8`, 7 counted functions, 6 exact, `0x24C` bytes) ends, and its copy lies elsewhere in `ST0C` (last function `0x8010B6D8`, where `ST0C` starts the file `stcom32` after it) |
| `ST03` | `0x8010E0A8` | `0x8010E0A8`-`0x8010FA58` | `ST1B` | `0x80106E14` | 23 (12) | `0x1970` | the run starts |
| `ST1B` | `0x80106E14` | `0x80106E14`-`0x801087C4` | `ST03` | `0x8010E0A8` | 23 (12) | `0x1970` | the same run, seen from `ST1B` |
