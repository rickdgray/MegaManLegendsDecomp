# ROCK_NEO.EXE: Capcom source-file boundaries

Proposed split of the two Capcom code ranges (`2490`: `0x80011C90`-`0x80067FF7`, `588BC`:
`0x800680BC`-`0x80069037`) into Capcom's original source files. **Mostly suspected, not verified.**
The split is applied in `rock_neo.exe.yaml` (one subsegment per row, all `asm` except `cd`, which is
C); a row's low/medium mark is a comment on its yaml line. File offset = address - `0x8000F800`.

**Bottom line:** 30 proposed files: 1 confirmed (`cd`), 3 high, 9 medium, 17 low confidence. Certain: the range start,
both sides of `2MBYTE.OBJ` (`0x80067FF8`/`0x800680BC`) and the end at `ADDDF3`. 12 starts rest on a single piece of
evidence: 11 of the 17 low rows and row 5 (see the "Single" column). Read each start as "a boundary lies in
this window"; the table gives a best guess inside it.

## What the evidence showed

- **Rodata blocks are not files.** Block `1BD8` holds jump tables for functions on *both* sides of
  `2MBYTE.OBJ` (`func_8006689C` ... `func_80068DAC`), so one splat block can span objects. Block `9E4`
  (jump tables + stage-file path strings) **holds three files' data** (`0x80017C30`, `0x8001BB4C`,
  `0x8001F23C`); the yaml splits it at `0xA44` and `0xAB0` so that `cd`'s part travels with its C.
  Block `156C` holds at least four. So "13 blocks" means *at least* 13 rodata-owning files; a block's
  users give a file's code range only as a lower bound. The table below lists which files own which
  blocks. Files with no switch statements or string literals have no rodata and can't be seen this way.
- **Rodata block -> file** (users from `jlabel` targets and `%hi` references):
  `800` rows 1 (`D_80010000`, `D_80010040`) and 2 (3 jump tables); `8B4` row 3; `938` row 4; `9E4` rows 6
  (`func_80017C30`), 8 (`0xA44`–`0xAAF`: `cd_cmd_read_comb`'s 3 tables, **confirmed**) and 9 (the path strings, reached via `.data` table
  `D_800893BC`); `10C0` row 10; `1294` row 13; `1330` row 15; `136C` row 18; `14D0` row 19;
  `1514` row 21; `1530` row 22; `156C` rows 23, 25, 26, 27; `1BD8` rows 29 and 30.
- **Padding is not a boundary marker here.** Functions are packed back to back; the only extra `nop`s
  after a function are three hand-written routines (`func_800175D8`, `_800175FC`, `_80017668`, which pad to
  8 bytes). Those mark one *assembly* file (row 5, `asm_fastmem`), not Capcom C-file ends. There are 40 eight-byte
  empty functions (`jr ra; nop`); only `func_8001F820` and `func_8003BE38` sit right before a candidate
  boundary, the rest are mid-file, so they are not a reliable end-of-file marker.
- **`Sound_key_off_voice` is not `SsSetNck`.** It is a 0x24-byte Capcom wrapper (`sll`/`sra` to `short`, then a
  tail into `SsUtKeyOffV`, which is a libsnd reverb-type setter inside `UT_GVAD`: it range-checks the
  argument against 0x18). Its neighbours `func_8001B314` (calls `SpuSetKey`) and `func_8001B33C` (calls
  `func_80070114`/`_8007013C`) are the same kind. I found **no library-like function inside the Capcom
  range**; these three are the tail of `sound` (row 7), right before `cd`.
- **Names** (`Sound_`, `Cd_`, `Sce_`, `Moji`, `Sub_screen_`, `Map_screen_`, `Pl00_`) all fall inside the
  files proposed from the other evidence: `Sound_call` (`0x8001A008`) in `sound`, `Cd_read_comb`/`_sync2`
  in `cd`, `Sce_flag_*` in `scene`, `MojiTask*` in `moji`, `Sub_screen_*` (`0x80060E64`-`0x80062490`) in
  `sub_scrn`, `Pl00_shot_enable_*` in `player`. `Map_screen_*` after `Sub_screen_*` is the only prefix change
  I used as a boundary (row 27, low).
- **ChrisNonyminus's ten starts** (`0x2490`, `0x3BD8`, `0x5DA4`, `0xA0C0`, `0xBBE4`, `0xE054`, `0x2C640`,
  `0x43F88`, `0x4F434`, `0x531E0`) all land exactly on function starts and are used as-is. His
  `scene` (`0xE054`-`0x2C640`, 0x1E000 bytes) and `player` (to `0x43F88`) are far too big for single files:
  the rodata blocks alone put several files in each (rows 10-17 and 18-23).
- **Data clusters.** `.data`/`.sdata`/bss are laid out in link order, so private variables of one file
  form a contiguous run and a boundary often shows as a jump (example: `.data` goes from `0x8008A778` to
  `0x8008A9D4` exactly at `func_80048620`). Used as support only: a run of tiny functions each owning the
  next variable looks like a boundary at every step.
- **Call-graph cost.** For each gap between functions I summed the "private" links crossing it (calls
  to functions with <= 3 callers, variables with 2-4 users, spans <= 60 functions). Cost 0 means a file
  *could* end there; a nonzero cost does not rule a boundary out (Chris's `cd` and `sub_scrn` starts cost
  4.3 and 4.0 because init and few-caller globals are called across files).

## Proposed files

Confidence: **high** = several independent pieces agree; **medium** = two pieces, or Chris plus one
check; **low** = one weak piece (atom edge, window guess). **Single** = the start boundary rests on one
piece of evidence.

| # | Start | Offset | End | Size | Name | Conf. | Single | Evidence |
|---|---|---|---|---|---|---|---|---|
| 1 | `0x80011C90` | `0x2490` | `0x800133D8` | 0x1748 | `main` | high | no | Start of the Capcom range; ChrisNonyminus `main` 0x2490; names `main`, `Vsync_handler`; rodata block `800` part 1 (`D_80010000` pointer table, `D_80010040` format string) used by `func_8001246C`/`func_80012A5C`; PCopen/PCread dev leftovers inside. |
| 2 | `0x800133D8` | `0x3BD8` | `0x80014AC0` | 0x16E8 | `Code800133D8` | medium | no | ChrisNonyminus `Code800133D8` 0x3BD8; zero local links cross the gap; block `800` jump tables (`func_800136B8`, `_8001389C`, `_80013CA0`) start right after the 0x70 bytes main needs. Cannot be proven from rodata alone (block `800` is one splat block). |
| 3 | `0x80014AC0` | `0x52C0` | `0x800155A4` | 0xAE4 | `code_80014AC0` | medium | no | Rodata block `8B4` (users `func_80014BCC`, `_800150E0`) needs a new file; `func_8001456C` is only called from file 2 and `func_80014AC0` calls `func_800150E0` (file 3), so the gap is one of two candidates. First user of `.data` 0x800820E0. |
| 4 | `0x800155A4` | `0x5DA4` | `0x800175D8` | 0x2034 | `game` | medium | no | ChrisNonyminus `game` 0x5DA4; sole minimum-cost gap in the block `8B4`/`938` window; `func_800155A4` calls `func_80016BC0`/`_80016BF4` and the helpers `_80016D0C`..`_80017528` are called from `_80015DB4` and the jump-table functions; rodata block `938` (6 jump tables). |
| 5 | `0x800175D8` | `0x7DD8` | `0x8001786C` | 0x294 | `asm_fastmem` | medium | yes | Hand-written assembly (yaml: `HAND-WRITTEN ASSEMBLY`) (no stack frames, swaps `sp` with a scratchpad stack, word-copy/clear loops, `break 1,6`). The only extra `nop` padding in the whole range follows `_800175D8`, `_800175FC`, `_80017668`. Single kind of evidence (code style); end at 0x8001786C is the first function that saves `s` registers (compiler output). |
| 6 | `0x8001786C` | `0x806C` | `0x800198C0` | 0x2054 | `code_8001786C` | low | yes | End of the asm file + window of rodata blocks `938` and `9E4` (the `9E4` jump table user `func_80017C30` must be in a different file than block `938`). Start inside 0x8001786C..0x80017C30 is a guess (all gaps cost 0); may begin as late as 0x80017C30. |
| 7 | `0x800198C0` | `0xA0C0` | `0x8001B3E4` | 0x1B24 | `sound` | high | no | ChrisNonyminus `sound` 0xA0C0; `.data` 0x8008222A is first used exactly at 0x800198C0 (a new data cluster, ten tiny functions each with its own variable); `Sound_call`/`Sound_call2` 0x8001A008/50; gap cost 0. Tail 0x8001B2F0..0x8001B3E4 is three thin libsnd/libspu wrappers (see notes below). |
| 8 | `0x8001B3E4` | `0xBBE4` | `0x8001D854` | 0x2470 | `cd` | **confirmed** | no | ChrisNonyminus `cd` 0xBBE4; `Cd_init` calls `CdInit` and is called only by init; `Cd_read_comb`, `Cd_read_sync2`; the shim's CD module ([rock_neo.md](rock_neo.md), "Shared code") spans it. In C (`src/rock_neo.exe/cd.c`) and matching, with its rodata at `0xA44`–`0xAAF` (`cd_cmd_read_comb`'s three jump tables, inside block `9E4`). |
| 9 | `0x8001D854` | `0xE054` | `0x8001F828` | 0x1FD4 | `scene` | medium | no | ChrisNonyminus `scene` 0xE054; `Sce_flag_test/on/off` at 0x8001DA58..; the stage-file path strings at the end of rodata block `9E4` are reached through the `.data` table `D_800893BC`, used by `func_8001F23C`/`_3C8`/`_6C4` (this file). |
| 10 | `0x8001F828` | `0x10028` | `0x80027678` | 0x7E50 | `code_8001F828` | low | yes | Rodata block `10C0` (5 jump-table functions, first user `func_8001F8DC`) starts a new file; window 0x8001F6C4..0x8001F8DC, all gaps cost 0. The 8-byte empty `func_8001F820` is guessed to end the previous file. `.sdata` 0x80097C3C..0x80097C90 run suggests the file extends to ~0x80027678, possibly several files (see split candidates). |
| 11 | `0x80027678` | `0x17E78` | `0x8002D9A0` | 0x6328 | `code_80027678` | low | yes | Atom edge only: gap cost 0 and `.data` 0x800898D0..0x80089938 first used inside it. Contains `Model_Shadow_Trans` (0x8002C794); `Model_` prefix suggests a model file. |
| 12 | `0x8002D9A0` | `0x1E1A0` | `0x8002E7A8` | 0xE08 | `code_8002D9A0` | low | yes | Atom edge only: gap cost 0; first user of `.sdata` 0x80097CD4; a run of small cost-0 functions up to 0x8002E7A8. |
| 13 | `0x8002E7A8` | `0x1EFA8` | `0x80037440` | 0x8C98 | `code_8002E7A8` | low | yes | Rodata block `1294` (3 jump-table functions at 0x800320B8..0x800329D4) is inside; names `Obj_work_flag_change`, `Close_EVE_WORK` (an `Obj_`/`EVE` file). Both ends are atom edges only; likely several files. |
| 14 | `0x80037440` | `0x27C40` | `0x80037FB4` | 0xB74 | `code_80037440` | low | yes | Atom edge + new `.data` cluster (0x800899E0, 0x80089EAC table used by six tiny 0x30-byte functions). No rodata. |
| 15 | `0x80037FB4` | `0x287B4` | `0x8003A3B4` | 0x2400 | `code_80037FB4` | low | no | Rodata block `1330` (users `func_80038894`, `_80039A60`) + `.sdata` 0x80097D28..0x80097D70 cluster (`func_80038648`..); contains `Swing_Camera2` (0x800398F8), so possibly a camera file. |
| 16 | `0x8003A3B4` | `0x2ABB4` | `0x8003AC24` | 0x870 | `code_8003A3B4` | low | yes | Atom edges only (both gaps cost 0); no data of its own except bss. Could be merged with neighbours. |
| 17 | `0x8003AC24` | `0x2B424` | `0x8003BE40` | 0x121C | `code_8003AC24` | low | yes | Atom edge + `.data` 0x80089F04..0x80089F90 cluster; ends at the 8-byte stub `func_8003BE38`. |
| 18 | `0x8003BE40` | `0x2C640` | `0x800425FC` | 0x67BC | `player` | medium | no | ChrisNonyminus `player` 0x2C640; new `.sdata` cluster begins at 0x8003BE6C (0x80097D90); gap cost 0; `Pl00_shot_enable_off/on`; rodata block `136C` (11 jump-table functions, 0x8003CD4C..0x80042458). End 0x800425FC is a guess within a window of six cost-1.0 gaps (0x800424D4..0x80042770). |
| 19 | `0x800425FC` | `0x32DFC` | `0x8004324C` | 0xC50 | `code_800425FC` | low | no | Rodata block `14D0` (users 0x80042770..0x80042F78); first user of `.data` 0x8008A04C (a new cluster) at 0x800425FC. Start is one of six tied gaps; end 0x8004324C is right after the last jump-table function. |
| 20 | `0x8004324C` | `0x33A4C` | `0x80043F34` | 0xCE8 | `code_8004324C` | low | yes | Window between rodata blocks `14D0` and `1514` (0x80042F78..0x8004441C); many cost-0 gaps. Single guess: edge right after the last `14D0` user. |
| 21 | `0x80043F34` | `0x34734` | `0x800456D8` | 0x17A4 | `code_80043F34` | low | no | Rodata block `1514` (one user, `func_8004441C`); `.data` cluster 0x8008A208.. starts at 0x80043F34 and `.sdata` 0x80097DDC..0x80097E0A. |
| 22 | `0x800456D8` | `0x35ED8` | `0x80048620` | 0x2F48 | `code_800456D8` | low | no | Rodata block `1530` (users `func_80047354`, `_800477A0`); both ends are cost-0 gaps; `.data` 0x8008A2B0..0x8008A778 and `.sdata` 0x80097E64..0x80097F24 are contiguous clusters used only here. |
| 23 | `0x80048620` | `0x38E20` | `0x80053788` | 0xB168 | `code_80048620` | low | no | Rodata block `156C` first five tables (users 0x80048704..0x80051BE4); `.data` jumps from 0x8008A778 to 0x8008A9D4 exactly here (first user 0x80048620). End = Chris `moji`. |
| 24 | `0x80053788` | `0x43F88` | `0x8005C258` | 0x8AD0 | `moji` | medium | no | ChrisNonyminus `moji` 0x43F88; `MojiTaskExec/Exec2/Kill` at 0x8005382C..0x80053A30; gap cost 0. No rodata of its own. End 0x8005C258: cost-0 gap with data/sdata/bss separation; the 0xC-byte setter `func_8005C24C` writes `D_800989D4`, used only by `moji` code, so it stays in this file. |
| 25 | `0x8005C258` | `0x4CA58` | `0x8005EC34` | 0x29DC | `code_8005C258` | low | no | Cost-0 gap (`.data`, `.sdata` and bss clusters all separate there); rodata block `156C` tables for `func_8005C2B8` and `_8005E144`. Chris has no boundary here (he runs `moji` on to 0x4F434). |
| 26 | `0x8005EC34` | `0x4F434` | `0x8006259C` | 0x3968 | `sub_scrn` | medium | no | ChrisNonyminus `sub_scrn` 0x4F434; rodata block `156C` tables for `func_8005ECE0`..`_80060618`; `Sub_screen_*` names (0x80060E64..0x80062490). Conflict: call graph prefers 0x8005EBA4 (two 0x10-byte accessors only called from `_8005ED9C`). |
| 27 | `0x8006259C` | `0x52D9C` | `0x800629E0` | 0x444 | `map_screen` | low | yes | Name prefix changes from `Sub_screen_` to `Map_screen_` (`Map_screen_init` 0x8006259C, `map_screen_set`, `map_cursor_set`); one jump table (`map_cursor_set`). May be one file with `sub_scrn` (Chris has no split). |
| 28 | `0x800629E0` | `0x531E0` | `0x8006430C` | 0x192C | `debug` | medium | no | ChrisNonyminus `debug` 0x531E0; the last named function (`map_cursor_set`) ends exactly at 0x800629E0; gap cost 0; new `.data` cluster 0x8008DBD4..0x8008ECE0 (17 variables). Holds `Game_logo_kill`. |
| 29 | `0x8006430C` | `0x54B0C` | `0x80067FF8` | 0x3CEC | `code_8006430C` | low | yes | Rodata block `1BD8` (first user `func_8006430C`) is a new rodata-owning file; the gap lies in 0x800629E0..0x8006430C. Might be the same file as `debug`. Ends at `2MBYTE.OBJ` (0x80067FF8, certain). |
| 30 | `0x800680BC` | `0x588BC` | `0x80069038` | 0xF7C | `code_800680BC` | high | no | `2MBYTE.OBJ` sits between Capcom objects, so a new file starts here; rodata block `1BD8` last table (`func_80068DAC`). Ends at the first libgcc object `ADDDF3` (0x80069038). `func_800680BC` (0x64 bytes) is probably a separate tiny file from `func_80068120` on. |

Row 1's start and row 30's end are fixed by the ranges; `0x80067FF8` (end of row 29) is the start of
`2MBYTE.OBJ`. Names: ChrisNonyminus's where he has one, `code_<address>` otherwise (renames are the
owner's call; the `asm_` prefix marks hand-written assembly, which `progress.py` excludes). Names like `Model_`/`Obj_`/`Swing_Camera` are in the
evidence column, not the file names.

### Open conflicts

- **`sub_scrn` start:** Chris says `0x8005EC34`; the call graph prefers `0x8005EBA4` (cost 2.0 vs 4.0).
  The two functions at `0x8005EBA4`/`0x8005EBB4` are tiny accessors only called from `func_8005ED9C`.
  The boundary lies in `0x8005EAA8`-`0x8005ECE0` (`0x8005EAA8` is called from `moji` code).
- **`debug` vs `code_8006430C`:** the rodata window allows both to be one file starting at `0x800629E0`.
- **`code_800680BC` vs `0x80068120`:** `func_800680BC` initialises a handful of bss bytes and ends 0x64
  bytes in; `0x80068120` starts GPU-primitive code. Likely two objects.
- **Rows 10-17** (0x8001F828-0x8003BE40, 0x1C000 bytes) have rodata for only three files; the rest is
  atom edges. Expect 5-10 more boundaries in there.

### Further split candidates (cost 0, all low, none counted in the table)

`0x8001326C` (row 1; calls `Cd_read_comb`, a moji function and `GetTPage`), `0x80020A40`/`0x80020A4C` (row 10),
`0x8002DC84`-`0x8002DE5C` (row 12: seven tiny atoms), `0x80037534`-`0x80037694` (row 14: six 0x30-byte
routines sharing `D_80089EAC`), `0x8003C07C`, `0x8003C7B0`, `0x8003C88C`, `0x8003CB20`, `0x8003CD4C`
(row 18, each with its own `.data`), `0x80044998`-`0x80044AB0` and `0x80044D5C`-`0x80044F44` (row 21,
runs of 0xF4-byte look-alikes), `0x800542FC`-`0x80054424` (row 24, fourteen 0x14-byte accessors),
`0x80062CF0`..`0x800638D8` (row 28, five 0x2D0-byte look-alikes), `0x80063EF0`/`0x80063F28` (`Game_logo_kill`),
`0x8006471C`, `0x80067E18` (row 29 tail, before `2MBYTE`), `0x80068120` (row 30).

## Method and limits

Parsed the two `.s` files for functions, `jal`/`j` targets and all symbol/`0x8xxxxxxx` operands
(`symbol_addrs_rock_neo.exe.txt` names resolved to addresses); jump-table owners from `.L` labels in
`asm/rock_neo.exe/data/*.rodata.s`. The scripts were scratch work and are not in the repo. Limits: only
exact symbol references are seen (indexed accesses through a computed base are counted at the symbol, not
at the element), the cost metric treats few-caller globals as local, and `.data` ordering is link order
only within a file's own variables (shared globals live in their defining file, scattered among users).
Next step that would settle most low rows: decompile one or two files and see which functions share static
variables, or locate Capcom's own file list in the TCRF source / debug strings.
