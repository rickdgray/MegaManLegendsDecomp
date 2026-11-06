# ROCK_NEO.EXE (main game)

Loaded by the shim with `LoadExec("cdrom:\ROCK_NEO.EXE;1", 0x801fff00, 0)`.

**Status: byte-identical rebuild** (SHA-1 `ffc08fd2b6113e84dc0e75ba63a4feaca0eb1d46`).
First C: the `cd` file (`src/rock_neo.exe/cd.c`); see "Function status". Built with `./tools/rebuild.sh rock_neo.exe`.

## Header and build

- **Confirmed:** load `0x80010000`, `t_size` `0xC9000` (file `0xC9800` = 825,344 bytes, matching the
  file table's entry 1), image end `0x800D9000`, entry `0x80068000` (`start`), stack `0x801FFFF0`
  (overridden by the shim's `LoadExec` to `0x801FFF00`). Header data/BSS fields are zero. Ghidra
  reports PsyQ 4.0.0.
- **Confirmed:** timestamp `Aug 16 1998 12:31:28`, 3 min 48 s before the shim's `12:35:16`: the same
  build session. Also the string `MEGAMAN LEGENDS MASTER VERSION 1998/5/13`.
- **Confirmed: `-G8`.** `gp` = `0x80097864`; 697 `(gp)` accesses in a raw disassembly vs the shim's
  1. Compiled with `-G8` (cc1's default; the shim passes `-G0`). `cc.sh` passes `-G8` to cc1 and
  maspsx and `-G0` to GNU as: `extern` globals, even small ones, are `lui`-addressed (the `cd`
  file's C matches this way); see [toolchain.md](toolchain.md). Still untested: a C file that
  *defines* small data (maspsx would emit `%gp_rel` for it).

## Layout

| File offset | Address | Contents |
|---|---|---|
| `0x800` | `0x80010000` | Capcom rodata (13 objects' worth; see below) |
| `0x1CB8` | `0x800114B8` | PsyQ rodata (17 objects) |
| `0x2490` | `0x80011C90` | **Capcom code** from `main`, to `0x80067FF7` |
| `0x587F8` | `0x80067FF8` | PsyQ `2MBYTE.OBJ` (`__main`, `start`, `stup1`, `stup0`; `0xC4` bytes) |
| `0x588BC` | `0x800680BC` | **More Capcom code**, to `0x80069037` |
| `0x59838` | `0x80069038` | PsyQ libraries (from `ADDDF3`; 105 objects), to `0x800806C3` |
| `0x70EC4` | `0x800806C4` | Data (timestamp string at `0x800806C8`, as in the shim) |
| `0x80064` | `0x8008F864` | Small data (`gp` − `0x8000`) |
| `0x88958` | `0x80098158` | BSS, `0x2D530` bytes, cleared by `start`; **stored as zeros in the file** |
| `0xB5E88` | `0x800C5688` | Tail, to `0x800D8FFF`: heap start; zeros except `0x04` at `0x800D8800` |

- **Link order:** Capcom's link placed `2MBYTE.OBJ` among its own objects: a second Capcom block
  follows it (uses `Player_work`, `Map_prim_ptr`; Ghidra hadn't disassembled all of it).
- **The tail's one byte:** `0x04` at `0x800D8800`, the SHL overlay's load address, at the start of
  the file's last sector. **Suspected:** connected to why the BSS is in the file (a link that laid
  out overlay/heap regions after BSS); check the SHL overlay's first byte.
- **Capcom file boundaries from rodata alignment** (each object's rodata starts 8-aligned; splat's
  jump-table hints): file offsets `0x8B4`, `0x938`, `0x9E4`, `0x10C0`, `0x1294`, `0x1330`, `0x136C`,
  `0x14D0`, `0x1514`, `0x1530`, `0x156C`, `0x1BD8` (address = offset + `0x8000F800`). At least 13
  Capcom files have rodata; each block's users (from splat's hints) map it to a code range.
- **Libraries of note:** soft-float `double` routines (`__adddf3` ...); libsnd's sequencer
  (`SsSeqOpen`, MIDI); libgte math; libpad; libcd; and SN host file I/O (`PCopen`, `PCread`), a
  development leftover. `MSC00.OBJ` starts with two data words, then `InitGeom`. libcd's rodata:
  `EVENT` `0x1ED8`, `SYS` `0x202C` (name a guess, as in the shim), `BIOS` `0x20A8`.
- Some PsyQ objects begin with an 8-byte marker `50 73 xx 15  9C xx 40 00` (seen at MSC00's start,
  `0x8007A4E8`, and at `0x8007FEA0` after `GPU_cw`, an unlabeled object merged into SYS_2). Purpose
  unknown; useful for placing unlabeled object boundaries.

## References outside the image

splat writes these to `build/rock_neo.exe/undefined_*_auto.txt`, which the link includes.

- **Overlay code and data**, confirming ChrisNonyminus's load addresses ([disc.md](disc.md)): stage
  code (`func_80101D94`), SUPPORT code (`func_801D8130`, `func_801D816C`), stage `HED`
  (`0x80139F04`, `0x8013A004`), `IDX` (`0x8015C000`–`0x8015D7A4`), `MDT` (`0x80164004`–`0x80164008`).
- **The SHL area**, just past the image end: `0x800D9B00`–`0x800DD600`.
- **A fixed buffer near the stack:** `0x801F8100`–`0x801F8300`.
- **`D_87654321`** is the constant `0x87654321`, not an address; a `reloc_addrs` entry can make it a
  plain number later.

## splat settings that took work

- `ld_gp_expression: "0x80097864"`: quoted (splat wants a string); the literal value, since `gp` is
  `0x8000` above the small data, not the classic `0x7FF0`.
- `align: 1` on `main`: splat rounds a segment's end to 16 by default; the original link didn't
  (`main` ends at `0xB5E88`). A fact about the layout, not a hack.
- Per-target `undefined_*_auto_path` and `asset_path`, so the two executables' files stay apart.
- `section_order` lays out a segment **by section type**, so subsegment types decide placement,
  not just file order (see the BSS hack).

## Hacks to revisit

- **BSS typed as `sdata`** (`[0x88958, sdata, 88958]`). splat can't express BSS that occupies file
  bytes: `bss_size` is required, and it then also counts the file range, doubling the size. Typed
  `data`, it was laid out *before* the small data (section order) and broke every `$gp` access;
  typed `sdata`, it lands after it. C globals in that range stay defined in assembly and declared
  `extern` until fixed. **Proper fix**, when C first needs real BSS: a splat extension segment type
  (`extensions_path`) that emits a `NOLOAD` `.bss` accounting for its file bytes, or an upstream
  splat option on `bss` subsegments. Understand first why the original stores BSS in the file
  (likely the overlay layout).

## Prior work: ChrisNonyminus/mml1

A 2023 decompilation attempt on GitHub; no matched C, last commit 2023-07. **No license**, so use its
findings (facts) only; don't copy its files. Its layout and `gp` are now confirmed (above); the rest
is **suspected** until verified.

- **Translation-unit guesses** (file offsets): `main` `0x2490`, `Code800133D8` `0x3BD8`, `game`
  `0x5DA4`, `sound` `0xA0C0`, `cd` `0xBBE4`, `scene` `0xE054`, `player` `0x2C640`, `moji`
  `0x43F88`, `sub_scrn` `0x4F434`, `debug` `0x531E0`. Compare with the rodata boundaries above.
  Its `scommon` `0x88958` and `bss` `0x8B648` are a guess at the small-BSS/BSS split.
- **Names** (~330), many matched to the TCRF source: all `Sub_screen_*` functions
  (`Sub_screen_cancel_check` `0x80060E64` …), `Map_screen_init` `0x8006259C`, `Map_screen_task`
  `0x800625DC`, `Sound_call` `0x8001A008`, `Cd_read_comb` `0x8001D440`, `Cd_read_sync2`
  `0x8001D838`, `Sce_flag_test` `0x8001DA58`, `Model_Shadow_Trans` `0x8002C794`, `MojiTaskKill`
  `0x80053A30`, `main` `0x80011C90`, init `0x80011F04`, vsync callback `0x800123FC`.
- **Globals:** `Player_work` `0x800B51B0` (`0x5F4` bytes, a second at `0x800B57A4`), `Game_work`
  `0x800C1B10` (`0x210`), `Moji_work` `0x800BB6B8`, `Map_screen_work` `0x800987F0`, `Moji_flag`
  `0x80098A58`, `Sce_flag` `0x800BE378`, `Rock_buster_parts_tbl` `0x8008FE64`.
- **Scratchpad:** `System_timer` `0x1F800002`, `Map_prim_ptr` `0x1F800070`.
- **CD file enum:** `Cd_read_comb(id)` takes a file index into the disc's file table
  (`Cd_file_tbl`, see [disc.md](disc.md)); `CDDATA` files from index 3.
- **Flags guessed (unverified):** `-funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return
  -fcommon`. `-funsigned-char` matters wherever plain `char` appears; test it with the first C.

## Function status

`cd` (`src/rock_neo.exe/cd.c`, ported from the shim with `cd_map.txt`):

- **Banked:** `Cd_init`, `Cd_sync_cb`, `Cd_control_retry`, `Cd_controlb_retry`, `Cd_set_mode`,
  `Cd_read_sync2`. Same C as the shim, ROCK_NEO's symbol names.
- **Also banked:** `Cd_pause`, `Cd_read_sync`, `Cd_set_volume` (needs a local
  `uint8 *base = Cd_work;` and `CdMix(base + 0x14)` to hoist the base address; the four
  `D_800AD154..57` bytes are separate globals).
- **Parked:** `Cd_stop`, `func_8001B7B4`: target does `D_800AD142 |= 0x8000` through a
  shared address register (`lui`/`addiu v1`, `sh` reuses it); we emit `lui at` + `sh`. Tried plain
  global, `uint16 *` local (before/after the loop), `Cd_work + 2` cast; `func_8001B7B4` also
  has the `li v0,1` hoisted by the target.
- **Parked:** `Cd_cmd_dequeue`. The shim's draft with `p->type = 0;` for the terminator. Same
  difference as in the shim: GCC bases the second loop pointer at `p+4` (target `p+0xC`, with
  `a2`/`a1` where the draft gets `a3`/`a2`); the tail matches.
- **The `cd` rodata:** its three jump tables (`0xA44`-`0xAB0`, used by `func_8001BB4C`) sit inside
  the `9E4` block, between a `sound` table and `scene`'s path strings, so the yaml splits that
  block at `0xA44` (`.rodata, cd`) and `0xAB0`.
- `func_8001D648`: takes a packed file reference (bits 0-15 entry, 16-27 file, 28-31 group;
  `CD_FILE_ID`) and goes to that entry's sector. The target extracts the middle field and scales
  it as separate steps (`sll 4`, `srl 20`, `sll 2`); GCC folds both a bit-field and plain shifts
  into `srl 14` / `andi 0x3FFC`. Ruled out: bit-field by value, union over the `uint32`. 
  Something in the original hid the chain from combine (a narrower type or cast?). Permuter candidate.

## To do

- **Names:** enter ChrisNonyminus's and the TCRF source's names into
  `symbol_addrs_rock_neo.exe.txt` before decompiling.
- **Compiler check:** the first C function confirms `-G8` / `--dont-force-G0`, and tests
  `-funsigned-char`.
- **Capcom file boundaries:** map the rodata blocks to code ranges; split `2490` into per-file C
  subsegments when decompiling.
- **Ghidra:** create the function at `0x800680BC` (code not disassembled); define `MSC00`'s first
  two words as data.
- Where the stage overlays are loaded from (ties to the SHL byte and the BSS-in-file question).
