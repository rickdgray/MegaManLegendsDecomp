# ROCK_NEO.EXE (main game)

Loaded by the shim with `LoadExec("cdrom:\ROCK_NEO.EXE;1", 0x801fff00, 0)`.

**Status: byte-identical rebuild** (SHA-1 `ffc08fd2b6113e84dc0e75ba63a4feaca0eb1d46`), split into
Capcom's source files ([rock_neo_files.md](rock_neo_files.md)). In C: the `cd` file
(`src/rock_neo.exe/cd.c`); see "Function status". Build with `./tools/rebuild.sh rock_neo.exe`.

## Header and build

- **Confirmed:** load `0x80010000`, `t_size` `0xC9000` (file `0xC9800` = 825,344 bytes, matching the
  file table's entry 1), image end `0x800D9000`, entry `0x80068000` (`start`), stack `0x801FFFF0`
  (overridden by the shim's `LoadExec` to `0x801FFF00`). Header data/BSS fields are zero. Ghidra
  reports PsyQ 4.0.0.
- **Confirmed:** timestamp `Aug 16 1998 12:31:28`, 3 min 48 s before the shim's `12:35:16`: the same
  build session. Also the string `MEGAMAN LEGENDS MASTER VERSION 1998/5/13`.
- **Confirmed: `-G8`** (`gp` = `0x80097864`). How the build reproduces it (`-G8` to `cc1` and
  maspsx, `-G0` to GNU `as`) and what is still untested: [toolchain.md](toolchain.md).

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
- **Capcom source files:** the two code ranges are split into 30 files in the yaml, one of them
  Capcom's hand-written assembly (`asm_fastmem`); evidence and confidence per file in
  [rock_neo_files.md](rock_neo_files.md).
- **The tail's one byte:** `0x04` at `0x800D8800`, the SHL overlay's load address, at the start of
  the file's last sector. **Suspected:** connected to why the BSS is in the file (a link that laid
  out overlay/heap regions after BSS); check the SHL overlay's first byte.
- **Libraries of note:** soft-float `double` routines (`__adddf3` ...); libsnd's sequencer
  (`SsSeqOpen`, MIDI); libgte math; libpad; libcd; and SN host file I/O (`PCopen`, `PCread`), a
  development leftover. `MSC00.OBJ` starts with two data words, then `InitGeom`. libcd's rodata:
  `EVENT` `0x1ED8`, `SYS` `0x202C` (name a guess, as in the shim), `BIOS` `0x20A8`.
- **PsyQ object marker:** some PsyQ objects begin with the 8 bytes `50 73 xx 15  9C xx 40 00`
  (seen at `MSC00`'s start, `0x8007A4E8`, and at `0x8007FEA0` after `GPU_cw`, an unlabeled object
  merged into `SYS_2`). Purpose unknown; useful for placing unlabeled object boundaries.

## References outside the image

splat writes these to `build/rock_neo.exe/undefined_*_auto.txt`, which the link includes.

- **Overlay code and data**, confirming ChrisNonyminus's load addresses ([disc.md](disc.md)): stage
  code (`func_80101D94`), SUPPORT code (`func_801D8130`, `func_801D816C`), stage `HED`
  (`0x80139F04`, `0x8013A004`), `IDX` (`0x8015C000`–`0x8015D7A4`), `MDT` (`0x80164004`–`0x80164008`).
- **The SHL area**, just past the image end: `0x800D9B00`–`0x800DD600`.
- **Thread data, `0x801F8xxx`** (`0x801F8100`–`0x801F8300` referenced so far), just below the
  stack; `Thread_current` is at `0x801F8300` (see "Threads").
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

## Shared code (shim and ROCK_NEO)

- **Confirmed: the CD module is shared.** The shim's CD code and ROCK_NEO's `cd` file compile
  identically for `Cd_init`, `Cd_sync_cb`, `Cd_control_retry`, `Cd_controlb_retry`, `Cd_set_mode`,
  `Cd_read_sync2`, and their offsets and constants agree (`find_dupes.py --imm`), so
  `include/cd.h` is shared. `cd.c` was ported from the shim's C with `find_dupes.py --map`.
- **Two source differences between "identical" functions** (Capcom kept two versions of these
  files):
  - `Cd_cmd_dequeue`'s terminator: the shim stores it to `p[1].type`, ROCK_NEO to `p->type`.
  - `Disp_env_init`: the shim calls `ClearOTag`, ROCK_NEO (`0x8001215C`) `ClearOTagR`.
- **When `--map` pairs two different real names** (a call to `ClearOTag` lining up with
  `ClearOTagR`), the source differs there; port that line by hand.
- Pad structs differ: `Joy1`/`Joy2` are 0x158 apart in the shim, 0x168 in ROCK_NEO.
- **Names:** the shim's former `Cmd_` names were renamed to Capcom's `Cd_` module prefix
  (`Cd_cmd_exec`, `Cd_cmd_dequeue`, ...). `Cd_read_sync2` is a real Capcom name (ChrisNonyminus,
  matched to the TCRF source).

## Sound

- **Confirmed:** `Sound_work` (`0x800AD140`, type `SOUND_WORK`, size `0x24`,
  `include/rock_neo.exe/sound.h`) belongs to the sound module (row 7, `sound`); the `cd` file
  only uses it. Field widths come from the loads and stores; most fields are still `unkXX` (the
  header lists their users). The CD audio volume (`CdlATV atv`, `+0x14`) lives here.
- Flag bits in `flags` (`+0x02`): `SOUND_FLAG_MONO` (`0x0001`, `Cd_set_volume` mixes both inputs to
  both outputs) and `SOUND_FLAG_CD_OFF` (`0x8000`, set when CD audio is stopped: `Cd_stop`,
  `cd_subcmd_xa_stop`, `cd_subcmd_xa_pause`, `cd_subcmd_mute`; cleared when `cd_cmd_xa_play` starts XA).

## Threads

- **Confirmed:** a cooperative thread system on the BIOS's `ChangeTh`. `Thread_wait(n)`
  (`0x80012E98`, in `main`) stores `n` and `1` in the current thread's record (`+0x2`, `+0x0`), then
  calls `ChangeTh(0xFF000000)`: yields to the main thread.
- `Thread_current` (`0x801F8300`, `absolute:True`) points at the running thread's record; the
  `0x801F8xxx` area below it is thread data.
- `Cd_read_sync` waits for the CD queue to drain, calling `Thread_wait(1)` on each pass;
  `Cd_read_sync2` only tests whether the queue is empty.

## CD module

- `Cd_file_tbl` (`0x80082CD0`, `CD_FILE[248]`): **confirmed identical** to the shim's (248 entries;
  [disc.md](disc.md)).
- **Command types** (`cd_cmd_tbl[type]`, run by `Cd_cmd_exec`, the counterpart of the shim's
  `Cd_cmd_exec`):

| Type | Handler | Queued by | Does |
|---|---|---|---|
| 0, 3, 5 | `cd_cmd_nop` (empty) | | 0 ends the queue; 5 is the shim's movie, unused here |
| 1 | `cd_cmd_read` | `Cd_read(file, dest)` | Read file `arg1` into the buffer at `arg2` (`Cd_read_start_buf`), 150-tick timeout |
| 2 | `cd_cmd_subcmd` | `Cd_subcmd` | Second-level dispatch: `cd_subcmd_tbl[args.arg2]()` (below) |
| 4 | `cd_cmd_xa_play` | `Cd_xa_play`, `Cd_xa_play_id` | XA read: `CdlSetfilter` (file 1, channel `arg2 >> 24 & 0x1F`), `CdlSetloc`, `CdlReadS`, wait for status bit 0x20, ramp volume up |
| 6 | `cd_cmd_read_comb` | `Cd_read_comb(file)` | Read sectors and dispatch them by type (`LoadImage`, VAB upload, ...); not decompiled |
| 7 | `cd_cmd_seek` | `Cd_seek(sector)` | `CdlSeekL` to sector `arg2`; timeout sets error bit 0x02 |

- **`cd_subcmd_tbl`** is a second-level dispatch table for type 2, indexed by `args.arg2`: 0 empty
  (`cd_subcmd_nop`); 1, 2 stop CD audio, wait for `Cd_sync_done`, set `Cd_xa_state` to 1 / 2
  (`cd_subcmd_xa_stop`, `cd_subcmd_xa_pause`); 3 toggle CD audio off/on, saving and restoring
  `Sound_work.unk06` (`cd_subcmd_mute`).
- `Cd_cmd_exec` resets on an error; while `Cd_play_mode == 2` it polls `CdlNop`/`CdlGetlocP` and
  calls `Cd_xa_play_id` or `Cd_stop` at sector `Cd_xa_end_sector`.
- Error bits in `Cd_error_flags`: 0x01 ring full, 0x02 timeout, 0x04 `CD_ERR_READY`, 0x20 first
  word mismatch, 0x40 wrong sector.
- **`CD_FILE_ID`, a packed file reference** (name proposed; not declared yet): bits 0–15 entry,
  16–27 file, 28–31 group (`Cd_xa_play_id` uses bits 28–29 and passes bit 30 on). Taken by `Cd_xa_seek_id` (go to that entry's sector) and
  `Cd_xa_play_id` (queue a type-4 read of it); the group selects one of the tables
  `Cd_xa_file_tbl[16]` (file indices) and `Cd_xa_track_tbl[16]` (`CD_POS` sector offsets).

## Prior work: ChrisNonyminus/mml1

A 2023 decompilation attempt on GitHub; no matched C, last commit 2023-07. **No license**, so use its
findings (facts) only; don't copy its files. **His names are references, not authority:** use one
when the code supports it, and prefer the TCRF source's and the evidence here. His names are in
`symbol_addrs_rock_neo.exe.txt`. His layout and `gp` are confirmed (above); his file starts were
checked in [rock_neo_files.md](rock_neo_files.md); the rest is **suspected** until verified.

- **Names** (~330), many matched to the TCRF source: all `Sub_screen_*` functions
  (`Sub_screen_cancel_check` `0x80060E64` …), `Map_screen_init` `0x8006259C`, `Map_screen_task`
  `0x800625DC`, `Sound_call` `0x8001A008`, `Cd_read_comb` `0x8001D440`, `Cd_read_sync2`
  `0x8001D838`, `Sce_flag_test` `0x8001DA58`, `Model_Shadow_Trans` `0x8002C794`, `MojiTaskKill`
  `0x80053A30`, `main` `0x80011C90`, init `0x80011F04`, vsync callback `0x800123FC`.
- **Globals:** `Player_work` `0x800B51B0` (`0x5F4` bytes, a second at `0x800B57A4`), `Game_work`
  `0x800C1B10` (`0x210`), `Moji_work` `0x800BB6B8`, `Map_screen_work` `0x800987F0`, `Moji_flag`
  `0x80098A58`, `Sce_flag` `0x800BE378`, `Rock_buster_parts_tbl` `0x8008FE64`.
- **Scratchpad:** `System_timer` `0x1F800002`, `Map_prim_ptr` `0x1F800070`.
- His `scommon` `0x88958` and `bss` `0x8B648` are a guess at the small-BSS/BSS split.
- **Flags guessed:** see [toolchain.md](toolchain.md) (untested).

## Function status

`cd` (`src/rock_neo.exe/cd.c`):

- **Banked:** `Cd_init`, `cd_cmd_nop`, `cd_cmd_read`, `cd_subcmd_nop`, `cd_subcmd_xa_stop`,
  `cd_subcmd_xa_pause`, `cd_subcmd_mute`, `cd_cmd_subcmd`, `cd_cmd_xa_play`, `Cd_seek_sync_cb`,
  `cd_cmd_seek`, `Cd_cmd_exec`, `Cd_pause`, `Cd_stop`, `Cd_sync_cb`, `Cd_read_start_buf`,
  `Cd_ready_cb_buf`, `Cd_read_start_ring`, `Cd_ready_cb_ring`, `Cd_control_retry`, `Cd_controlb_retry`,
  `Cd_set_mode`, `Cd_set_volume`, `Cd_xa_play`, `Cd_read_comb`, `Cd_read`,
  `func_8001D7AC`, `Cd_read_sync`, `Cd_read_sync2`, `Cd_cmd_dequeue`,
  `Cd_subcmd`.
- Notes on banked ones:
  - `Cd_stop`, `cd_subcmd_mute`: parked until `Sound_work` existed (the target's shared
    `lui`/`addiu` base was the struct; see `CLAUDE.md`, "Revisit parked functions").
  - `Cd_set_volume` needs the local `SOUND_WORK *sw = &Sound_work;` and `CdMix(&sw->atv)` to
    hoist the base address.
  - `cd_cmd_read`, `cd_cmd_seek`: unsigned `switch ((uint32)Cd_cmd_routine)` (no `slti`).
  - `cd_cmd_xa_play` needs `Cd_sync_done = *(volatile uint8 *)&Cd_status;` for the original's
    reload. It reads the command's `+0xC` as a whole word (`Cd_xa_end_sector` = sector + (word &
    0xFFFFFF)), so it is `xa.end` (`uint32`) in the `CD_CMD_ARGS` union in `cd.h`, as is `subcmd.arg3`
    (`Cd_subcmd`, `Cd_xa_play_id`). Each command type has its own argument layout; the shim's movie
    command stores a 16-bit skip mask at +0xC instead.
  - `Cd_read_start_buf`, `Cd_read_start_ring` (read starts; ready callbacks `Cd_ready_cb_buf` copying to
    `Cd_read_buf`, and `Cd_ready_cb_ring` filling the 10-sector ring `Cd_ring_buf`): `CdIntToPos` takes
    `Cd_file_sector`, not the table again, since the store could alias `Cd_file_tbl`. `Cd_read_start_ring`
    clears `Cd_ring_ready[10]` through a descending pointer
    (`for (i = 9, p = &Cd_ring_ready[9]; i >= 0; i--) *p-- = 0;`). The callbacks share their error
    tails with `goto` (no `goto`-free form tried).
- **Parked:**
  - `Cd_xa_seek_id` (`CD_FILE_ID`): the target extracts the middle field and scales it as separate
    steps (`sll 4`, `srl 20`, `sll 2`); GCC folds a bit-field, plain shifts, and a union over the
    `uint32` alike into `srl 14` / `andi 0x3FFC`. Something in the original hid the chain from
    combine (a narrower type or cast?). **Permuter candidate.**
  - `Cd_xa_play_id`: same family. The target keeps `srl 28; andi 3; sll 2` and
    `sll 4; srl 20; sll 2` unfolded, and computes `arg & 0x40000000` early; we fold to
    `srl 26; andi 0xc`. Tried `uint32`, `sint32`, `uint8`/`uint16` temporaries, no temporaries. The target extracts group and file, then scales each separately (srl 28 andi 3 / sll 2; sll 4 / srl 20 / sll 2); GCC's combiner folds both. Same as Cd_xa_seek_id. Ruled out: bit-fields, a union over the id, uint16/uint8 locals, and the flags -fno-expensive-optimizations, -fno-strength-reduce, -fno-rerun-cse-after-loop, -fno-cse-follow-jumps. Also a store-order difference after that.
  - `Cd_seek` (queue a type-7 command, first deleting type-7 entries after the running one):
    right shape and instructions; only registers differ (target: write pointer `a0`, sector `t1`,
    outer `p` `a3`; ours `v1`, `t3`, `t0`). Tried a bound local `end`, declaration orders.
- **Not attempted, blocked:** `cd_cmd_read_comb` (915 lines: ready-sector dispatcher with three jump
  tables). Needs the work struct at `D_800C5604`..`D_800C5638`, `Game_work`'s type
  (`+0x1B8/+0x1BA/+0x1BC/+0x1DA`), `D_80098AD0` (8-byte entries), and registry names for three
  `jal` targets inside `asm_fastmem` (`.L80017684` word copy, `.L800176A4` copy to a VRAM staging
  buffer, `.L800176DC` 0x40-word scratchpad copy). The batch runner skips it.

## To do

- **Compiler:** test `-funsigned-char` with the first plain `char`; test `-G8` with the first C
  file that defines its own small data.
- **`cd_cmd_read_comb`:** declare what it needs (above), then decompile.
- **Ghidra:** create the function at `0x800680BC` (code not disassembled); define `MSC00`'s first
  two words as data.
- Where the stage overlays are loaded from (ties to the SHL byte and the BSS-in-file question).
- **`Cd_ring_buf` (0x800B5DB0, 0x5000) is shared memory.** The CD ring uses all of it (10 slots of
  0x800), but other files keep data at fixed offsets inside it: `code_8006430C` (many fields, words
  and bytes from +0x100 to +0x1EE0), `player`, `scene`, `code_8003AC24`, `code_8005C258`. Since C
  variables can't overlap, the original had one buffer used for different things at different
  times (a union, or casts). Its real owner, and its name, are open until those users are decompiled.
