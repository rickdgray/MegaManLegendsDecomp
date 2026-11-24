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
  build session. The timestamp (`build_timestamp`, 0x800806C8, `"CAPCOM"` on both sides) and
  the string `MEGAMAN LEGENDS MASTER VERSION 1998/5/13` (`version_str`, 0x80080704) are `main`'s
  `.data`, around the primitive buffer table `D_800806EC`; nothing reads either string.
- **Confirmed: `-G32`** (`gp` = `0x80097864`; the limit is pinned by string literals). How the
  build reproduces it (`-G32` to `cc1` and maspsx, `-G0` to GNU `as`): [toolchain.md](toolchain.md).

## Layout

| File offset | Address | Contents |
|---|---|---|
| `0x800` | `0x80010000` | Capcom rodata (13 objects' worth; see below) |
| `0x1CB8` | `0x800114B8` | PsyQ rodata (17 objects) |
| `0x2490` | `0x80011C90` | **Capcom code** from `main`, to `0x80067FF7` |
| `0x587F8` | `0x80067FF8` | PsyQ `2MBYTE.OBJ` (`__main`, `start`, `stup1`, `stup0`; `0xC4` bytes) |
| `0x588BC` | `0x800680BC` | **More Capcom code**, to `0x80069037` |
| `0x59838` | `0x80069038` | PsyQ libraries (from `ADDDF3`; 105 objects), to `0x800806C3` |
| `0x70EC4` | `0x800806C4` | Data (timestamp string at `0x800806C8`, as in the shim): Capcom's to about `0x8009039C`, PsyQ's from `0x80090454` |
| `0x88064` | `0x80097864` | Small data (`.sdata`), starting **at** `gp` (see below) |
| `0x88958` | `0x80098158` | BSS, `0x2D530` bytes, cleared by `start`; **stored as zeros in the file** |
| `0xB5E88` | `0x800C5688` | Tail, to `0x800D8FFF`: heap start; zeros except `0x04` at `0x800D8800` |

- **Confirmed: `.sdata` starts at `gp` (`0x80097864`), not at `gp` − `0x8000`.** All 182 variables
  reached through `$gp` lie in `0x80097864`–`0x80098B6C`, the lowest exactly at `gp` (offset 0; no
  negative offsets anywhere). `0x8008F864`–`0x80097863`, once typed `sdata` in the yaml, is ordinary
  `.data`: PsyQ, which never uses `$gp`, has 190 variables there. Initialized small data is
  `0x80097864`–`0x80098157` (40 `$gp` variables), `.sbss` follows from `0x80098158` (142). The bytes
  are the same either way, so matching is unaffected; it matters once data moves into C. The yaml
  now has one `data` subsegment from `0x70EC4` and `sdata` from `0x88064`.
- **Link order:** Capcom's link placed `2MBYTE.OBJ` among its own objects: a second Capcom block
  follows it (uses `Player_work`, `Map_prim_ptr`; Ghidra hadn't disassembled all of it).
- **Capcom source files:** the two code ranges are split into 29 files in the yaml, one of them
  Capcom's hand-written assembly (`asm_fastmem`); evidence and confidence per file in
  [rock_neo_files.md](rock_neo_files.md).
- **Every Capcom file is C** (`src/rock_neo.exe/<file>.c`), with an `INCLUDE_ASM` stub per function
  not yet decompiled (1,040). splat wrote the stubs, and wrote the 35 empty functions (`jr ra; nop`) as
  C itself. Unmigrated rodata uses `INCLUDE_RODATA` (`scene.c`: the path strings `D_800102B0`).
  Each file's small data (`.sdata`, `.sbss`) is defined at the top of its C file, so its `$gp`
  accesses come out right; small commons use tentative definitions (rock_neo_files.md, "Small data
  in C").
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
  `Cd_read_sync2`, and their offsets and constants agree (`find_dupes.py --imm`, since retired), so
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
- **Names synced between both:** `Cd_xa_state`, `Cd_play_mode` with `CD_PLAY_MOVI`E for the shim's
  value 3, `Cd_head_state`, `Cd_ring_write`, `Cd_muted`, `Cd_unused`.

## Sound

- **Confirmed:** `Sound_work` (`0x800AD140`, type `SOUND_WORK`, size `0x24`,
  `include/rock_neo.exe/sound.h`) belongs to the sound module (row 7, `sound`); the `cd` file
  only uses it. Field widths come from the loads and stores; most fields are still unkXX (except serial_vol, the CD audio volume through the SPU, zeroed while muted).
- Flag bits in `flags` (`+0x02`): `SOUND_FLAG_MONO` (`0x0001`, `Cd_set_volume` mixes both inputs to
  both outputs) and `SOUND_FLAG_CD_OFF` (`0x8000`, set when CD audio is stopped: `Cd_stop`,
  `cd_subcmd_xa_stop`, `cd_subcmd_xa_pause`, `cd_subcmd_mute`; cleared when `cd_cmd_xa_play` starts XA).

## Threads

- **Confirmed:** a cooperative thread system on the BIOS's `ChangeTh`. `Thread_wait(n)`
  (`0x80012E98`, in `main`) stores `n` and `1` in the current thread's record (`+0x2`, `+0x0`), then
  calls `ChangeTh(0xFF000000)`: yields to the main thread.
- `Thread_current` (`0x801F8300`, `absolute:True`) points at the running thread's record; the
  `0x801F8xxx` area below it is thread data.
- In C, `Thread_current` and `THREAD_TBL` (`0x801F8100`, 4 records of 0x80) are literal-address
  macros (`system.h`): the target builds them with `lui 0x801f` / `ori 0x8300` and accesses at offset
  0, which only a constant gives. Using the `extern` symbol in `func_80012ECC` gives `%hi`/`%lo`.
- `thread_dispatch` (`0x80012C80`) is the scheduler pass: for each record whose `flags` is 2, 4 or
  0x7F (or 1 with `wait` counted down to 0) it sets `flags` = 0x7F and `ChangeTh`s to it; when
  `unk70` is set it stops callbacks around the switch and restores `Vsync_handler` after. If the
  thread called `func_80012F78(func)`, its thread is reopened at `func`.
- Thread records hold PsyQ's `EXEC` at `+0x14` (`exec.gp` at `+0x44` is OpenTh's gp):
  `Thread_open_file` (`0x80012FEC`) and `Thread_exec_file` (`0x800130D0`) load a PS-X EXE from
  the host PC (`PCopen`/`PCread`/`PCclose`, development leftovers) into it, then open the thread
  at / restart the current thread at `exec.pc0`. `wait` is `sint16` (the countdown tests it with `sll`).
- `Cd_read_sync` waits for the CD queue to drain, calling `Thread_wait(1)` on each pass;
  `Cd_read_sync2` only tests whether the queue is empty.

## Memory card (`code_8006430C`)

- `Card_init` (`0x8006479C`) opens and enables the eight card events (`SwCARD`/`HwCARD` x
  `EvSpIOE`, `EvSpERROR`, `EvSpTIMOUT`, `EvSpNEW`, kept in `.sbss` `0x80098708`-`0x80098724`), then
  `InitCARD(1)`, `StartCARD`, `_bu_init`. `func_8006491C`/`func_80064984` wait for the software/hardware
  event and return 0 (IOE), 1 (TIMOUT), 2 (NEW), 3 (ERROR).
- `func_80064A7C` (connect + `_card_clear` on a new card + `_card_load`), `func_80064B60`,
  `func_80064BB4` (`_card_info` result mapped to small codes), `func_80064FF0` (writes block 0
  from `D_8009AB30` with bytes 0-1 = 0xFF). `card_free_blocks` counts free 8 KB blocks of 15 with
  `firstfile`/`nextfile`; its `strcpy` of `"bu00:*"`/`"bu10:*"` is GCC's inline builtin, and those
  two literals are the file's whole `.sdata` (`0x8009808C`-`0x8009809B`).
- `card_header_set` builds a save block's header sector: `"SC"`, 0x11, 1 block, 64-byte title, icon
  CLUT `D_8008FA3C` at 0x60 and icon image `D_8008F9BC` at 0x80.
- File I/O on a card, by port (device names `D_8008FA5C`, `"bu00:"`/`"bu10:"`): `card_file_write`
  (`0x80064D74`; creates the file in 8 KB blocks if needed; 2 = card too full), `card_file_read`
  (`0x80064EA4`; 3 = read failed), `card_format` (`0x80064F8C`).
- **Save image** (`SAVE_IMAGE`, `Save_image`/`Save_words` over `Cd_ring_buf`, 0x1F00 bytes): six
  checksummed word blocks, each followed by a random key and three sums; `save_sum_set`
  (`0x80065384`) seals it, `save_sum_check` (`0x80065E08`) returns 0 or 3. `Save_image_restore`
  (`0x80065AA8`, called by game's `Game_init`) copies it into `Game_work` and `D_800C3558`;
  `func_80067E6C` sets `Game_work.records_84` for a new game or from image offset 0x1D40.
  `save_image_store` (`0x80065064`, called by `func_80067174`) fills it: the card header, the
  `CARD_SLOT`-style stage byte and play-time text at 0x100, `Game_work`, the player, `Sce_flag`,
  `D_800BD3B8` (0x480) and `D_800BC9B8` (0x1280).
  `func_80067884` resets the five 0x180-byte slots `D_800BAF38` (`CARD_SLOT`).
- `func_8006430C` (`0x8006430C`) is `LOGO_FUNC` 1 (`D_8008DD64`): a logo's sprites in a 6-column
  grid, chosen by three scene flags each (`LOGO_SPRITE.flag_2`). Matched: the frame's unused slot
  at 0x18 (between the spills of `wp` and `start`) comes from a loop flag
  (`cont = (sint16)rec->head_0 >= 0; } while (cont);`, declared right after `rec`). Combine folds
  the flag's two-insn set (`~v >> 31`) into the branch but leaves the pseudo referenced, so reload
  gives it a stack slot. CoastRedWood's fork got the same slot from a FAKE `while (id = ... >= 0)`.
- `func_800679B8`/`func_80067B7C` write `Game_work.timer_0c`/`timer_14` (30 per second) as hh:mm:ss
  into the font strings at `D_80097FD4`/`D_80097FF4` (`moji.h`); `func_800679B8` keeps the digits in
  `D_80098800`-`D_80098805` for `func_80067D10`.

## CD module

Constants, types and variables: `include/cd.h` (shared with the shim). This section is the map.

- `Cd_file_tbl` (`0x80082CD0`, `CD_FILE[248]`): **confirmed identical** to the shim's ([disc.md](disc.md)).
- **Command queue.** Request functions (`Cd_<verb>`) queue a `CD_CMD`; `Cd_cmd_exec` runs
  `cd_cmd_tbl[type]` once per frame. Each command type has its own argument layout, the
  `CD_CMD_ARGS` union's members; `args.word[]` is the raw view, used when entries are moved.

| Type | Constant | Handler | Queued by | Does |
|---|---|---|---|---|
| 0, 3 | `CD_CMD_END`, (none) | `cd_cmd_nop` | | 0 ends the queue; 3 unused |
| 1 | `CD_CMD_READ` | `cd_cmd_read` | `Cd_read(file, buf)` | Read a file into a buffer (`Cd_read_start_buf`) |
| 2 | `CD_CMD_SUBCMD` | `cd_cmd_subcmd` | `Cd_subcmd` | `cd_subcmd_tbl[args.subcmd.sub]()` (below) |
| 4 | `CD_CMD_XA_PLAY` | `cd_cmd_xa_play` | `Cd_xa_play`, `Cd_xa_play_id` | Play an XA track (below) |
| 5 | `CD_CMD_PLAY_MOVIE` | `cd_cmd_nop` | | The shim's movie command; unused here |
| 6 | `CD_CMD_READ_COMB` | `cd_cmd_read_comb` | `Cd_read_comb(file)` | Read a combined file through the ring (below) |
| 7 | `CD_CMD_SEEK` | `cd_cmd_seek` | `Cd_seek(sector)`, `Cd_seek_file`, `Cd_xa_seek_id` | `CdlSeekL`; `Cd_seek` first drops queued seeks |

- **Subcommands** (`cd_subcmd_tbl`, by `args.subcmd.sub`): 0 `cd_subcmd_nop`; 1, 2 stop CD audio,
  wait for `Cd_sync_done`, set `Cd_xa_state` to `CD_XA_STOPPED` / `CD_XA_PAUSED`
  (`cd_subcmd_xa_stop`, `cd_subcmd_xa_pause`); 3 `cd_subcmd_mute` toggles `Cd_muted`, saving and
  restoring `Sound_work.serial_vol` in `Cd_mute_save`.
- **XA playback.** `cd_cmd_xa_play` sets the channel filter (`CD_XA_FILE_NO`, channel from
  `args.xa.start.b.chan`), seeks, starts `CdlReadS`, waits for `CdlStatRead`, fades the volume in.
  `Cd_xa_state`: `CD_XA_PLAYING`, `STOPPED` (next play restarts), `PAUSED` (next play resumes
  without seeking), `OFF` (initial, and set when a data read starts). While `Cd_play_mode` is
  `CD_PLAY_XA`, `Cd_cmd_exec` polls the position (`CdlGetlocP`) into `Cd_xa_sector`; at
  `Cd_xa_end_sector` it replays `Cd_xa_id` if `Cd_xa_flags & CD_XA_LOOP`, else stops.
- **XA track references** (`Cd_xa_play_id`, `Cd_xa_seek_id`): a packed word, bits 0-15 track,
  16-27 file, 28-29 group, 30 loop (`CD_XA_NUM`/`FILE`/`GROUP`, `CD_XA_LOOP`). The group and file
  select a `Cd_file_tbl` index in `Cd_xa_file_tbl`, and a `CD_XA_TRACK` (start, end) in
  `Cd_xa_track_tbl`. `Cd_xa_seek_id` uses the group unmasked (4 bits).
- **Reads.** `Cd_read_start_buf` reads a file into `Cd_read_buf` (`Cd_ready_cb_buf`, checking the
  file's first word against `CD_FILE.head` via `Cd_head_state`); `Cd_read_start_ring` streams into
  the 10-slot ring `Cd_ring_buf` (`Cd_ready_cb_ring` fills `Cd_ring_write`; the reader consumes
  `Cd_ring_read`, clearing `Cd_ring_ready[slot]`). `Cd_ring_buf` is shared memory (see "To do").
- **Combined ("comb") files** (`cd_cmd_read_comb`): one file packs several entries, each a header
  sector (`CD_COMB_HEAD`: type, byte size, sector count, per-type arguments, image data at
  +0x100) and its data sectors. `Cd_head_state` is 0 while a header is expected, else the entry's
  type + 1; `Cd_comb_type` and `Cd_comb_work` (`CD_COMB_WORK`, a union by type) hold the entry.
  Types (`CD_COMB_*`): -1 end; 0 bytes to an address; 1 backgrounds and object textures, CLUT plus tiles;
  3 tiles only; 4, 9 palettes, 10 one image in the header (10: 64 wide); 5 a VAB (header to the VAB
  header buffer and `SsVabOpenHeadSticky`, body with `SsVabTransBodyPartly`; slot 4 is skipped
  if it already holds that bank, unless `D_80098958 & 0x800`); 7, 8 SEPs sound data, copied only when
  the number in `Sound_seq_tbl[i]` changes; 2 and 6 only set the state. **Very likely the format of
  the `CDDATA/DAT/*.BIN` archives** ([disc.md](disc.md), "Overlay chunk format"). 2, 4, 6, 7 never appear
- **CLUT buffer.** Images with x < 0x140 (type 1 CLUTs) or < `CLUT_BUF_COLS` (types 4, 9, 10) go to
  `Clut_buf`, a RAM copy of VRAM rows 0xF0-0xFF and 0x1F0-0x1FF, setting the row's bit in
  `Clut_buf_dirty`. `func_80017734` (asm_fastmem) copies the dirty rows to a second copy
  0x4000 bytes on, in RAM (double buffering?); the upload to VRAM is elsewhere.
- **Errors:** `Cd_error_flags` bits are `CD_ERR_*` in `cd.h` (ring full, command timeout, ready,
  sync, stream timeout, bad data, wrong sector).
- `Cd_unused` is cleared by `Cd_init` and never read, in either program.

## Prior work: ChrisNonyminus/mml1

A 2023 decompilation attempt on GitHub; no matched C, last commit 2023-07. **No license**, so use its
findings (facts) only; don't copy its files. **His names are references, not authority:** use one
when the code supports it, and prefer the TCRF source's and the evidence here. His names are in
`config/rock_neo.exe/symbol_addrs.txt`. **Audited (2026-11-15):** of the ~400 names imported from him, the
non-library ones are either confirmed by `disc/tcrf.txt` or siblings of confirmed names in the same
style (`Sce_flag_off`, `Sce_flag`, `MojiTaskExec`, `Moji_work`, `Scene_work`, `Game_main_tbl`,
`Debug_work`, `main`); the rest went: his file name `Code800133D8` is now `code_800133D8`, its
placeholders `Code800133D8_work`/`_main_tbl` are back to `D_80098AA8`/`D_80080950`, `p_Player_work`
is `Player_work_ptr` (like `Disp_env_ptr`), `Player_work2` is `Player_work[1]` (`Player_work` is
`size:0xBE8`), and the unused `SHL_PROGBIN_LOAD_ADDRESS` is gone. His `Map_prim_ptr` was right
(Capcom's, `POLY_FT4 *`); our `Scratch_prim_ptr` macro took that name. His layout and `gp` are confirmed (above); his file starts were
checked in [rock_neo_files.md](rock_neo_files.md); the rest is **suspected** until verified.

- **Names** (~330), many matched to the TCRF source: all `Sub_screen_*` functions
  (`sub_screen_cancel_check` `0x80060E64` …), `Map_screen_init` `0x8006259C`, `Map_screen_task`
  `0x800625DC`, `Sound_call` `0x8001A008`, `Cd_read_comb` `0x8001D440`, `Cd_read_sync2`
  `0x8001D838`, `Sce_flag_test` `0x8001DA58`, `Model_Shadow_Trans` `0x8002C8CC`, `MojiTaskKill`
  `0x80053A30`, `main` `0x80011C90`, init `0x80011F04`, vsync callback `0x800123FC`.
- **Globals:** `Player_work` `0x800B51B0` (`0x5F4` bytes, a second at `0x800B57A4`), `Game_work`
  `0x800C1B10` (`0x210`), `Moji_work` `0x800BB6B8`, `Map_screen_work` `0x800987F0`, `Moji_flag`
  `0x80098A58`, `Sce_flag` `0x800BE378`, `Rock_buster_parts_tbl` `0x8008FE64`.
- **Scratchpad:** `System_timer` `0x1F800002`, `Map_prim_ptr` `0x1F800070`.
- His `scommon` `0x88958` and `bss` `0x8B648` are a guess at the small-BSS/BSS split.
- **Flags guessed:** see [toolchain.md](toolchain.md) (untested).

## Function status

`cd` (`src/rock_neo.exe/cd.c`): every function is banked except two parked ones.

- **Notes on banked ones:**
  - `Cd_cmd_dequeue`, `Cd_subcmd`, `Cd_seek`: queue entries are copied word by word
    (`args.word[0..2]`), not as structs (credit: the decomp community); `Cd_seek` and
    `Cd_subcmd` test `q + 1 < Cd_cmd_write_ptr` directly, with no `end` local.
  - `Cd_stop`, `cd_subcmd_mute`: parked until `Sound_work` existed (see `CLAUDE.md`, "Revisit
    parked functions").
  - `Cd_set_volume` needs the local `SOUND_WORK *sw = &Sound_work;` for `CdMix(&sw->atv)`.
  - `Cd_ready_cb_buf`, `Cd_ready_cb_ring`: shared exits through `goto error` / `stop`; the ring
    callback's bytes require both labels, and the buf callback mirrors it (it also matches
    without `stop:`). See `CLAUDE.md`, "Shared error exits".
  - `Cd_read_start_ring` clears `Cd_ring_ready` through a descending pointer (an indexed loop
    doesn't match).
  - `Cd_xa_play_id`, `Cd_xa_seek_id` (from CoastRedWood's drafts): the target scales the file
    index with separate shifts (`sll 4; srl 20; sll 2`) because the source narrows `id` in place
    (`id = CD_XA_NUM(id)`) between extracting the file and using it; the combiner can't fold
    across that. One `void *row` local holds the `Cd_xa_file_tbl` row and then the
    `Cd_xa_track_tbl` row (two locals, or a union local, give other registers). In
    `Cd_xa_play_id`, the type store and the `Cd_xa_flags` load go through plain word pointers:
    as struct fields, GCC 2.7's in-struct alias rule lets them move past the `Cd_xa_id` /
    `Cd_xa_start` accesses.
- **Parked:**
  - `cd_cmd_read_comb` (banked): `tiles` keeps `col`/`row` at the same offsets as `tim`
    (`pad[6]`); type 10 computes the height before the width; the CLUT row must be the
    `CLUT_BUF_ROW` macro (it re-reads `head->arg[1]` at each use).

`sound` (`src/rock_neo.exe/sound.c`): banked from CoastRedWood's drafts `Sound_call2` (a local
copy of `Sound_call_ptr` after the `mode` store, `Sound_call_ptr = ++call`), `pitch_interp`
(both calls into locals, then `lo += ...`), `Sound_update` (an `info` local for
`&Sound_call_info_tbl[call->id]`), `Sound_stage_check` (if/else chain that reuses `list` for the
current stage's list), `Sound_call_play` (`VAB_TONE_BUF + bank * VAB_HEAD_SIZE`, then the flat tone
index `prog * 16 + tone`; a `range` local for `unk3`) and `Sound_init` (store order:
`Sound_fade_flags`, `Sound_call_ptr`, `D_80098958`, `mvol`, then the rest). Still parked:
- `Sound_stage_play`: body is right except that the target reloads `Game_work+0x50`/`+0x51` with a
  fresh `lui` each, while ours keeps the `Game_work+0x50` address in `s0` across the stage call
  (+1 saved reg). The fork matched it only by reading `Game_work` through a literal address
  (`(GAME_WORK *)0x800C1B10`), which isn't acceptable for an in-image symbol. `Sound_stage_check`
  reads `D_800C356E` (a plain symbol, no offset) on both sides of its call and gets a fresh `lui`
  each, so the CSE seems specific to `symbol+offset` addresses. Tried: local func pointer, `ok`
  flag, `&&` form, `sint32`/`uint16` id.
- `Sound_seq_stop_all`: banked in the consolidation pass (see `volume_update` below).

`sound`, this round: banked `key_on_tone` (key on one tone: `SpuSetKeyOnWithAttr`), `Sound_stage_slot_set`
(per-stage sound id slots by Sce flags), `voice_check` (voice priority / distance check against
the player). `key_on_tone`'s first parameter is `uint16` (the caller zero-extends).

`main` (`src/rock_neo.exe/main.c`), this round: banked `Disp_env_setup` (display buffers at `0x800C0C48`,
`extern DISP_ENV Disp_env[2]`: the extern symbol is needed, an absolute-address cast loses the shared
base), `Pad_repeat_update`/`func_80012350` (auto-repeat; ROCK_NEO's `PAD_WORK` adds
`rep_state[8]` at +0x38 and `rep_count[8]` at +0x40 to the shim's layout; `mask` is `sint32`), `Thread_open`
(`OpenTh` from the thread record's `sp`/`gp`), `func_800131FC` (thread entry: dispatch through
`D_80080894[D_80098B1C]`, then `Thread_wait(1)`), `thread_init` (`0x80012BC4`, thread table init:
each record's TCB, stack and gp, then the copy of `Thread_api_tbl` to `0x801F8000`). The table base
`*(TCB **)0x110` is written via a `TCB **kp = (TCB **)0x100` local (`kp[4]`) for the `li t2,0x100` /
`lw 0x10(t2)` split, and the `tcb` store comes before the `sp` and `gp` stores, so `tcb` is reloaded
for the `reg[R_SR]` store.

`debug_mem_dump` (`0x80012A5C`, debug dump of 16 eight-byte lines as words/halfwords/bytes
through `Print`) and `exception_handler` are banked together: with both in C, `exception_handler`'s
names table (`D_80010000`) comes first in `main.o`'s `.rodata`, then the byte format. The format is
a `static const char D_80010040[48]` defined between the two functions: the 3 bytes past the
45-byte string pad `.rodata` to 0x870 (the linker script's `SUBALIGN(2)` adds no padding).

`exception_handler` (`0x8001246C`, the exception handler that `func_80012938` installs with
`OpenEvent`; never returns). It copies the current TCB (`TCB_CURRENT`, the `TCBH` entry that 0x108 points to),
then each frame prints the exception name (`names[(cause >> 2) & 0xF]`, the initialized local whose
copy is `D_80010000`), the break code (`*epc >> 6`: 0x1C00 = break 7, divide by zero; 0x1800
= break 6, overflow), the labels `D_80080730[37]` and the registers. Select on controller 2 cycles
`mode` (0 = registers, 1-3 = `debug_mem_dump` mode - 1); triangle toggles the dump address between
main RAM and the scratchpad. What made it match: GCC's `-G32` cost model. A symbol of known size
32 bytes or less counts as cheap `$gp` small data, so GCC neither hoists its address out of a loop
nor keeps it in a register (even though maspsx emits `lui`/`addiu` for it). So `D_80080858` is
declared `[]` (not `[3]`: the target hoists it into `s3`), and `D_800979A4` has a size-less
`extern` ahead of its `.sdata` definition in `main.c` (the target keeps it in `s0` for the last
five prints). `epc` is a `uint32 *` (the target spills it to the stack).

`code_8003AC24`: banked `Stage_hed_model_get` (the `Stage_hed_tbl` entry with a given id: its model word),
`func_8003ACF4` (sets `Stage_idx_tbl[i].ptr`; no callers), `func_8003B278`, `func_8003B2D4`,
`func_8003B360`, `func_8003B420`, `func_8003B4BC`, `func_8003B540`, `func_8003BDC0`.
Parked: `func_8003AD14` (`0x8003AD14`, applies the state rows to `Stage_idx_tbl`: val 0/100/200 for
states 0/1/2, and states 1 and 2 swap the entry's shape for one of the `D_80089F24` HED ids; on stage
6 it also places entries 0x1C7 and 0x1F8, whose `IDX_ENT` x/y/z it sets). Only the registers of the
three loop counters differ (target k/j/i = s3/s4/s5, ours s5/s3/s4); CoastRedWood's fork matched only
with a dead store. The val stores must go through a zero-offset view at `0x8015C006` (the target
hoists that constant into `t0`).
`D_800BD3B8` (`uint32[7][0x80]`) holds a 2-bit state for each of the 0x800 `Stage_idx_tbl` entries,
one row per stage: `D_80089F04[stage_no]` (0x20 bytes) gives the row, or -1. `func_8003B2D4`/`B420`
read a state (`B420`, `B360` for `Game_work.stage_no`; `B360` gives 0 when the entry's `val & 0xFFF`
is 0), `B4BC` raises it by one up to 3, `B540` sets it; `func_8003B278(0)` sets every state to 3,
`func_8003B278(1)` restores the rows from `Cd_ring_buf + 0x480` (shared memory, see "To do").
What the states mean is open. `func_8003BDC0` counts entries 1.. whose shape's `head & 0xFFFF0000`
is one of two kinds and whose `val` is 0, read signed (`lh`: a `(sint16)` cast in the C).
`func_8003BC44` (banked) runs these for stages 5 and 6 only: `func_8003BD0C` on `Game_work.unk028[3]`
(stage 5) or `[0]`-`[2]` (stage 6) with kinds `D_80089F7C`/`F84`/`F88`/`F8C`, and `func_8003BDC0` into
`Game_work.unk062[4]`/`[5]` with `D_80089F80`/`F90` and `0x8FFF0000`.
`func_8003B5B4` (banked) is its counterpart, run once per flag: for stage 5 when `unk062[2]` is set
(cleared), `func_8003B8B0` on `unk028[3]` (200, kind `D_80089F64`, flag 0x240); for stage 6 when
`unk062[3]` is set, `func_8003BA58` on `unk028[0]` (500, `F6C`) and `func_8003B8B0` on `[1]`/`[2]`
(200/250, `F70`/`F74`, flags 0x23E/0x23F). Then, for entries of kind `D_80089F68` (stage 5) or
`F78` (stage 6), state 1→2, 2/3→3, and state 0 (or other) becomes 1 while `unk028[4] / 150`
(`[5] / 180`) allows, each time taking one from `unk062[4]` (`[5]`) and 150 (180) from the word.

`sub_scrn`: banked the item menu's handlers `func_8005F608`, `func_8005F9E8` (unused copy of its
item 2), `func_8005FAE4`, `func_8005FFBC`, `func_8005FDE4` (records the stage and area in
`Game_work.unk078`), `func_8005FBB4` (item 12: asks `func_8005FDE4`, then fades out and moves
the game to stage `unk079`, area `unk07A`), and Capcom's `Sub_screen_gauge_set`, `Sub_screen_basic_param_set`,
`sub_screen_rb_parts_calc`, `Map_screen_task` (the last verbatim from `disc/tcrf.txt`; the
others differ from the Japanese source only in statement order: `Map_prim_ptr` is stored before
`addPrims`, and the first primitive is built before `ft4_buff_ptr1`/`sprt_buff_ptr1` is set).
`SUB_SCREEN_WORK.item_4` is the item menu's choice (index of `D_8008DAF4`, key item numbers),
`mes_no_5` the message `func_8005FAE4` shows. Parked: `func_8005F3D0` (life refill, key item 4):
only its case 1 differs, GCC keeping `&Game_work.unk07C` and `&Player_work[0].life_max` in saved
registers across `MojiTaskExec` where the target rebuilds them with `lui`. The fork's draft
matches with literal addresses (`((GAME_WORK *)0x800C1B10)->unk07C`; `Player_work` can stay a
symbol), which the rules don't allow for in-image symbols. Tried: `x = x - d` for the `-=`, a
local for `unk07C` in the then-branch. The read-then-store of `unk07C` after the call in the
then-branch is what makes GCC cache the address.

`game`: banked the pool updates `func_80017210` (shots, `D_8009CF88`), `func_800172F4` and
`func_800173B4` (effects, `D_800A3B40`, ids below / from 0x80). Parked: `func_80016E90` (two black
POLY_F4 bars around a band of `2 * Game_work.aperture_08` lines, `ot[1]`), the same problem as
`func_8005F3D0`: GCC keeps `&Game_work.aperture_08` in `s1` across `AddPrim` where the target
rebuilds it with `lui` at each of the four reads; everything else matches. The fork's draft matches
with a literal `((GAME_WORK *)0x800C1B10)`. A separate scalar symbol isn't the answer either: GCC
then doesn't reload it after the stores through `p` (the target's reloads show a struct access).

`game`: banked the Game_main_tbl routines 3 (`func_800158F0`), 5 (`func_80016160`, the SUPPORT
overlay's `func_801D8130`/`func_801D816C`) and 6 (`func_800164B4`). Parked: routines 9 and 10,
`func_80016798` and `func_800169AC` (the same code but one `Fade_start` argument). Their only
difference is `Sound_call(0x41)`: the target sets up `a0` alone, leaving `a1`/`a2` as
`Cd_read_sync` left them, so Capcom's game.c called it without the three-argument prototype.
`sound.h`'s prototype can't produce that; waiting on a decision about how to declare it.

`code_80048620` (stage collision): banked `func_80048EA4`, `Ceiling_height_get`, `Obj_floor_height_get`,
`func_80049C54`, `func_8004AF28`, `func_8004F44C`, `front_hit_search`, `func_80052674`. The map-block
walkers need `do { } while (0)` wrappers to get the area pointer's register (GCC weighs references
by loop depth), as `floor_height_get` does. Zeroing the box at `0x1F800124` as plain words
(`D_1F800124_w`) lets the next block's loads move above the stores, as the target has; the `VECTOR`
fields don't. Parked: `func_800497CC` (nearest wall face toward a direction): register allocation
only, `hit`, `best` and `area` in `s4`, `s2`, `s6` where the target has `s2`, `s4`, `s5`, and the
switch's `li v0,1` one slot later. The fork's draft matches only with nine dead `val = 0` stores
(FAKE). Tried: `do/while (0)` levels around the box block (two levels with `hit = area->hits`
innermost is the closest), around the whole area loop, around the hit loop's first half, and
around `hit++`.

Also banked (from the fork's drafts): `func_80048620` (scene step), `map_push_out` (map collision with
push-out retries), `Front_hit_event` (exits and event triggers in front of the player), `solid_push_out`
(the same push-out against a solid object). Findings:
- The push vectors at `0x1F800100` must be indexed (`D_1F800100_h[i]`) in `map_push_out` and
  `solid_push_out`: GCC keeps each element's address in a register, which the target does; the
  `SVECTOR` fields of `D_1F800100` give plain stores (right for `func_800501E8` and the others).
- `func_8004BDC8` takes a third argument, the block test's result, which it never reads: both
  callers set `a2` for it.
- `AREA_ENTRY` (`D_800C3558`) must be over 32 bytes (0x28, up to the WORK_5A4 pool at
  `0x800C3580`): at 0x1A, GCC (`-G32`) treats it as small data and stops keeping its address in a
  register in `Front_hit_event`.
- `func_80048620`: `Player_work->flags_6 |= 3` gives the target's two `lui`s; `Player_work[0].`
  keeps the field's address in a register.

## WORK_48 kinds

A slot of the effect pool `D_800A3B40` (`func_80031618` / `func_80031988`) is an object whose kind is `id_2`: the
pool update (game's `func_800172F4`/`func_800173B4`) calls `handler[id_2]`, from the stage overlay's table (pointer at
scratchpad `0x1F800064`) for ids below 0x80, and from `D_80089858 + id * 4` for 0x80-0x8A (11 ROCK_NEO kinds). As
Capcom does with `EM_WORK` -> `MODEL_WORK`, each ROCK_NEO kind has its own full struct and its handlers take it; the
shared code takes the generic `WORK_48`, and callers cast at the boundary (`func_80031988((WORK_48 *)wp)`).

| Id | Struct | Handler | Family | Kind-specific bytes |
|---|---|---|---|---|
| 0x80 | `W48_80_WORK` | `func_80043F34` | model | `sound_C`/`size_D`/`variant_E`/`level_F`, `hw_44` |
| 0x81 | `W48_81_WORK` | `func_8004495C` | model | `ptr_44` |
| 0x82 | `W48_82_WORK` | `func_80044AB0` | sprite | `field_C` (byte, from the spawner `func_80043E00`) |
| 0x83 | `W48_83_WORK` | `func_80044C58` | sprite | |
| 0x84 | `W48_84_WORK` | `func_80045074` | sprite | `field_C` (byte) |
| 0x85 | `W48_85_WORK` | `func_80045238` | sprite | `add` 0x28, `spd` 0x30, `dir_40` |
| 0x86 | `W48_86_WORK` | `func_8004569C` | model (debris) | `ang_y_C`/`ang_x_E`, speed in the matrix's `t` bytes, `ptr_44` |
| 0x87 | `W48_87_WORK` | `func_8004602C` | model (debris) | same as 0x86 |
| 0x88 | `W48_88_WORK` | `func_80047318` | model, then sprite | `field_C` (byte), `hw_44`; `efc` union (routine 3 animates it as a sprite) |
| 0x89 | `W48_89_WORK` | `func_80047D9C` | sprite | `ang_28[8]`, `idx_38[8]` |
| 0x8A | `W48_8A_WORK` | `func_80048354` | sprite | `field_C`, `idx_D`, `timer_E` (records `W48_8A_REC`) |

The kinds come in two families laid over 0x14-0x43, the two halves of the `EFC` union that `WORK_48.efc` keeps for
the shared code (and `SHL_WORK.efc` at 0x88): `EFC_MODEL` (`data` from `Model_work_init`, `mtx`, `pos`, `rgbc`; bit 2
of `routine_0` set) and `EFC_SPRITE` (`code`, `rgbc`, `pos[3]`, two bytes and two halfwords, kind data from +0x14).
The kinds' own structs write them out at their offsets (`data_14`, `mtx`, `pos_38`, `rgbc_40`; `code_14`, `rgbc_18`,
`pos_1C[3]`, `field_22..26`). `func_8002F928` moves `efc.model.pos` or `efc.sprite.pos` by that bit. The name follows Capcom's shot code (`wk_p->efc.model.m`, `.sv`, `.rgbc`). The debris kinds copy the whole
matrix as a `MATRIX` (`func_80045AB4`), but keep their speed and acceleration in its `t` bytes, so their struct has
`m[3][3]` plus `vx_2C..az_36` and passes `(MATRIX *)wp->m`. `func_80037890` creates kinds 0x80 and 0x83 through one
reused local, so it stays generic. `func_80045CE8` and `func_80046B34` are spawners (of 0x86 and 0x87), not
handlers. The overlays' kinds (below 0x80) use the generic type until they are decompiled. Older entries below use
the names from before this split (`u_18.s`, `u_18.mtx`, `field_C.rec`, `u_44`, `field_2`/`flag_3` = `id_2`/`type_3`).

## Shot pools: SHL_WORK and PL_SHL_WORK

Capcom's `SHL_WORK` (their shot 0x38: `be_flag`, `id`, `type`, `routine_0..2`, `pos_l`, `pos`, `efc.model.m` /
`.sv` / `.rgbc`, and `free[]`, over which `SHL38_FREE` is cast) is the slot of the pool `D_8009CF88[32]`, kind 0x60
(`Open_SHL_WORK` / `Close_SHL_WORK`; the scene code and the overlays). Ours: header, the `MODEL_WORK` layout to 0x87,
an `EFC` at 0x88 and `free[0x54]` at 0xB8, for the overlays' shot kinds to cast their own structs over. ROCK_NEO has
no per-kind code for this pool yet.

`EFC` (model or sprite) is the same type as `WORK_48.efc`: the player's shot stores the sprite one's packed start word
`0x3D48002E` at 0x88, the same value `WORK_48`'s sprite kinds store at 0x14, and the layout after it (code and colour,
position, two bytes, two halfwords) is the same. Where `EFC` starts and that `free` follows it are inferred from that
match and from `EFC_MODEL`'s size (0x30); Capcom's offsets for `SHL_WORK` aren't known.

The player's shots, pool `D_800BFB20[16]` (kind 0x10, `Open_PL_SHL_WORK` / `Close_PL_SHL_WORK`, spawned by `pl_shot_spawn`),
have their own struct, `PL_SHL_WORK`: same layout, with the sprite `EFC` and the free block written out, because a
player's shot keeps its own bytes in both (the flight direction `dir_A4` in the EFC's kind bytes, `tgt_BC` and
`owner_C4` in the free block). Its `id_2` is byte 7 of the player's action record (`D_80089A8B`); the handlers are
`func_800433C0` and `func_800437A8` (`code_8004324C`, tables `D_8008A0CC`/`D_8008A0D8`, `PL_SHL_FUNC`).

The two pools share one "current slot" global, `D_800988F8` (`PL_SHL_WORK *`; `func_80017154` and
`func_80017210`). `func_80017210` calls the stage overlay's table (scratchpad `0x1F800060`,
`Shl_work_tbl`) for ids below 0x80 and `D_80089820[id_2]` for the rest. `D_80089820`'s entries are
scene functions with no parameters, and both loops call them with none: with the slot passed,
`func_80017210`'s two calls are identical and GCC cross-jumps them, which the target doesn't.

`SHL_WORK.field_C` stays a byte: `Open_SHL_WORK` clears 0x0C-0x0F with `*(uint32 *)&wp->field_C = 0`, and with a
`uint32` field the cast folds away and the store is scheduled one slot later.

## To do

- **Compiler:** test `-funsigned-char` with the first plain `char`.
- **Ghidra:** create the function at `0x800680BC` (code not disassembled); define `MSC00`'s first
  two words as data.
- Where the stage overlays are loaded from (ties to the SHL byte and the BSS-in-file question).
- **`Cd_ring_buf` (0x800B5DB0, 0x5000) is shared memory.** The CD ring uses all of it (10 slots of
  0x800), but other files keep data at fixed offsets inside it: `code_8006430C` (many fields, words
  and bytes from +0x100 to +0x1EE0), `player`, `scene`, `code_8003AC24`, `code_8005C258`. Since C
  variables can't overlap, the original had one buffer used for different things at different
  times (a union, or casts). Its real owner, and its name, are open until those users are decompiled.
- Verify the .BIN archives against the comb format; the sound file next (Sound_work’s fields,
  Sound_seq_stop_all and the two other sound wrappers, D_80098958’s bits); Clut_buf’s second copy and
  where the VRAM upload happens

### sound.c: seq/pan/update (Sound_seq_play, Sound_sep_play, calc_vol banked)
- `Sound_seq_play`/`Sound_sep_play` (SEQ/SEP start) tail-call-merge two `SsSeqPlay`/`SsSepPlay` calls
  in an if/else (loop flag 0/1); both use a `SOUND_WORK *work = &Sound_work;` local (AC58 assigns it before `vab_find`).
- `calc_vol` angle needs `angle = a - f(); angle &= 0xFFF;` as two statements; `Game_work.mono` is sint8 at 0x58.
- `volume_update` and `Sound_seq_stop_all` banked (consolidation pass): the sequence-channel loop is
  `chan = Sound_seq_chan_tbl; for (i = 0; i < 4; chan++, i++)`. The pointer increment must come
  *before* `i++` in the for's step; with `i++, chan++` (or `chan++` at the end of the body) the
  delay slot after `SsSeqSetVol` gets `i++` instead. `D_80098AFC` is GCC's second giv
  (`&chan->seq_num`), not a separate array.

`code_80037534` (`src/rock_neo.exe/code_80037534.c`): banked `func_800375D4`, `_80037604`,
`_80037634`, `_80037664` (four field readers of `D_80089EAC[n][owner->rec[n].idx[k]].val[k]`).
`func_8003786C`, `func_80037C14` and `func_80037BB4` were parked over the `addu at,v0,at` operand
order; all three matched once the table was addressed by literal address (see the third pass).

`code_80037534` (second pass): banked `func_80037534` (clears the 16 `TBL_IDX` records of an owner, then
reloads each `val`), `func_80037738`, `func_80037F60` (pops `D_8009A376[Cell_stack_idx]` into `func_80037CD8`
until `Cell_stack_idx` is 0). Later banked: `Player_weapon_bullet_set` (a `PL_WORK *pl = &Player_work[0]` local,
indexed by `pl->tbl_sel` three times, gives the separate `lui` for `tbl_sel`), `func_80037818` (an if/else
with two calls, the old value read into a local before the clearing store).
`PL_WORK` gained `tbl_sel` (0x172) and `rec[16]` (0x4F4); `TBL_IDX` gained `val` (0x06). The functions
that take the record owner are passed `&Player_work`, so their parameter is `PL_WORK *`.

`code_80037534` (third pass): banked `func_80037C50`, `func_8003777C`, `func_80037694`, `func_80037CD8`,
`func_80037890` (3 args: `kind`, count exponent, table index; `func_80037818` passes its `arg0` as the third).
- **`addu at,idx,at` operand order = literal address.** maspsx only emits `addu $at,reg,$at` when the
  operand is a numeric constant > 32767 (`maspsx/__init__.py`, "lhu $2,49344($2)" case); an `extern`
  symbol gives `addu $at,$at,reg`. So the 12-byte table at `0x8015C000` is accessed as
  `((IDX_ENT *)0x8015C000)[n]` (`Stage_idx_tbl` in `stage.h`): the stage's `IDX` file, loaded there
  (`notes/disc.md`). The "table at `0x8015C006`" is the same entries' `val` field: `&Stage_idx_tbl[n].val`
  gives the target's literal `lui`/`ori 0x8015C006` (taking `&Stage_idx_tbl[n]` and adding 6 later does not).
- Scratchpad map window (`Map_org_x/y` 0x40/0x41, `Map_w/h` 0x44/0x46, `Map_cells` 0x48) in `stage.h`.
- `func_80037CD8` needs an unused 8-byte local (frame 0x20).
- `func_80039A38` (`code_80037FB4`) takes one argument and passes it on to `func_800399EC`: its callers
  load an address into `a0`, and nothing in between touches `a0`, so the call has no argument setup. `func_80037890` angle `j * step` is
  strength-reduced by GCC (a separate `ang` accumulator puts its init before the zero-trip test).
- `Cell_stack` (`Cell_stack`) / `Cell_stack_idx` (`Cell_stack_idx`): stack of packed cells, see `renames.txt`.

`code_80037FB4`: `func_80039BBC/C08/C54/CA0/CEC` each copy a `VECTOR` (struct assignment) to one of
`D_800A39A0/B0/C0/D0/E0` and store three ints beside it (`D_800A3964..` / `3970..` / `397C..` /
`3988..` / `3994..`): five slots of a table. `func_8003A218` (matched): shortest
distance mod 0x1000 from its first argument to `D_800A3968`; the match needs the argument masked in
place (`ang &= 0xFFF`), not copied to a new local. Its second argument is unused (`a1` is overwritten).

Camera block `0x800A3958` (0xE4 bytes, `CAMERA_WORK` in `code_80037FB4.h`): `func_80039A60` saves and restores it
whole as `D_8009A478`, and `D_800A395F` is Capcom's `Camera_work.routine_3` (check_swing_camera). The five
`D_800A3964..`/`D_800A39A0..` slots are its `param[5]` and `pos[5]`. Two access forms give different code:
reached through the cast `Camera_work` (`*(CAMERA_WORK *)&D_800A3958`, the block declared as a union) every
field gets its own `lui`; reached directly (`D_800A3958.work.x`) GCC keeps the first field's address in a
register (`func_80039D38`, `func_800384F0`). Plain scalar externs don't work for `func_800394AC`: GCC 2.7 lets a
fixed-address scalar store move past a struct block copy, but not a struct member's. The older banked
functions here, `scene.c` and the overlays still use the separate `D_800A39xx` externs.

`code_80043F34` (batch 20261117 #4, recovered from its session log after the timeout revert): banked
`func_80044D5C`, `func_80044E50`, `func_80044F44` (near-twin per-frame steps of the sprite kinds:
`flag_3` picks how pos_1C, field_24 and the colour word move; `case 2:` shares `default:`), and
`func_800441CC`, matched later from CoastRedWood's draft: its distance test against Player_work reuses one
temporary `t` for the player's x, the y difference and the squared radius, and reads the radius
`pos_38.pad` as `(uint16)` then `(sint16) / 2` (the target's `lhu`); that reuse is what gives the
target's registers (v1 for the coordinate, a1/a0/t0 for the squares). `func_8004441C` (kind 0x80's field_9 handler,
D_8008A214) is matched: per type_3 it grows/shrinks the scale `pos_38.pad` by `hw_44`, fades the colour
(tables `D_8008A1A8`/`D_8008A1C8`, `W48_80_SCALE`, and `D_8008A1E8`, `W48_80_FADE`, by size_D), and ends by
stepping routine_8. The sprite kinds that keep their position in `pos_1C` (`func_80045338`, `func_80045400`,
`func_8004548C`) are kind 0x85 (`W48_85_WORK`): acceleration at 0x28 and speed at 0x30, unlike the debris
kinds 0x86/0x87, where 0x2C is the speed and 0x32 the acceleration (see "WORK_48 kinds").

`code_8003A3B4`: GTE lighting. Banked `func_8003A3B4`: for each of the 0x800 `Stage_idx_tbl` entries
with a `ptr`, finds the `Stage_hed_tbl` entry (the stage HED file, `HED_ENT` = {id, model}, loaded at
`0x8013A000`) whose model has the same low 24 bits and copies `ptr->unk18[1]` into the entry's `val`,
then calls `light_init` and `func_8003A538`. It was parked while the HED list was a `uint32 *` at
`0x8013A004`; with the 8-byte struct the plain `Stage_hed_tbl[j].model` loop matched. `light_init`
(banked) resets three light tables that `func_8003A538`/`func_8003A744` hand to `SetLightMatrix`,
`SetColorMatrix` and `SetBackColor`: `SVECTOR D_80098870[3]` (light directions), `CVECTOR D_80098858[3]`
(light colours, `<< 4` into the colour matrix's columns), `sint32 D_80098900[3]` (back colour). Each is a
pool common, tentative in `code_8003A3B4.c`; `$gp` reaches only element 0, other elements are `sym+off`,
which splat labels separately (`D_80098872`, ...). Both (banked) then walk the six LOD words of
`STG_MODEL`s (`stage.h`): each LOD's header word holds its header length in words - 1 (low byte) and a
part count (bits 8-13), and each 8-byte part goes to `part_faces_light`. `func_8003A744` does this for
`Support_stg[1]` (SUPPORT's STG at `0x801F6000`; record 0 has id `0xFFFFFFFF`), `func_8003A538` for every
model in the stage HED list. The target counts the LOD index 6..11 (the word index; map_blocks_draw also
reads words 6-8), hence `lod[lod - STG_LOD_WORD]`; a 0..5 counter adds an instruction. Banked
`part_faces_light`: for each 16-byte face of `p[1]` (count in the top byte, address in the
low 24 bits) unless bit 26 is set without bit 24, it unpacks three byte vertices (y = `-(uint8)`), takes
the cross product (`OuterProduct0`), shifts it below 0x6883, `VectorNormal`s it and stores the
`NormalColorCol` colour in the face's low 24 bits. The target evaluates "larger magnitude of n.vx,
n.vy" twice: the match (from CoastRedWood's draft) is `max = MAX_ABS(n.vx, n.vy)`, negate if negative,
then `max > ABS(n.vz) ? MAX_ABS(n.vx, n.vy) : n.vz`, negate again (ternary `ABS`/`MAX_ABS` in
`code_8003A3B4.h`); a nested `MAX_ABS(MAX_ABS(..), ..)` doesn't match. The flag test has to be written
as sign tests on a `sint32` copy of `f[0]` (`(flags << 5) >= 0`); a mask test folds into one `and`/`beq`.

`code_8002E7A8.c` (batch 2): banked `func_800355F0` (view matrix from `Player_work[n]`; `Player_work` is
now an array, the target indexes it by symbol; `unk56` read as `(uint16)` for `lhu`), `func_80033D80`
(scratchpad matrix `0x1F8000C0` + `ApplyMatrix`/`RotMatrix`/`MulMatrix`), `func_80037440` (counts
`D_800BFB20[n]` by id into `D_8009856C[16]`; `D_800BFB22` is declared as a second `SHL_WORK` array so
the access keeps its own `lui`), `Angle_xz_vector`, `Angle_xz_svector` (`catan` of the x/z delta).
Parked `func_80036C50` (`NON_MATCHING`; 4-entry table at `D_8009A306`, stride 0x14): the target keeps
`&D_8009A306` in a3 for the first compare and the loop; ours folds the first compare to `lui`+`%lo` and
rebuilds the base for the loop (local pointer, `e++`/flag pointer, index forms tried). Update: with
`base = &D_8009A300[0].id_6` copied to a separate loop pointer (and `flag = base + 9`) only the loop counter
(target t0) and the `D_8009A300[i]` offset (target a3) are swapped.

`code_8002E7A8.c` (batch 3): banked `func_800331A0` (joint matrix/position update on the player, `PL_WORK.joint_mtx`/`joint_pos`: scratchpad
matrix + `ApplyMatrix`/`RotMatrix`/`MulMatrix`/`ScaleMatrix`; the byte at `0x1F800074` is a shift count,
also written as `Scratch_scale_shift`; needs an unused 8-byte local), `func_800341BC` and `func_8003430C`
(queue one/two `SLOT_REQ` entries in `D_800A2F48[0x40]`, count in `D_800988E0`, value in `D_800A32E0[n]`,
then copy the vector or the midpoint into `D_800BE478[slot] + 0xBC` for each slot bit of
`owner->mask_4 & D_80098798`; the register match needs a separate `mask` local and `i` used as the
`owner->mask_4` temp). Parked `fog_block_apply` (`NON_MATCHING`): copies the 0x28-byte block at
`D_800BC7F8` to `D_8009A350` after `SetFarColor`/`SetFogNear`; the copy is right, but the target keeps
`&D_800BC818` in s0 from the start (also the copy end pointer) while ours rebuilds `D_800BC818-0x20`.
Parked `pl_shot_spawn` (`NON_MATCHING`; spawns a `SHL_WORK` slot from `PL_WORK`, claims a slot with
`func_8003545C`): the target computes `pl + sel * 8` at the end of each branch, ours once after the merge.
`func_80035508` (GTE: projects each claimed slot's position at +0xBC through `Scratch_view_mtx`, then
clears it) banked with `psyq/inline_c.h`; its screen XY local is 8 bytes (frame 0x10), and `mask <<= 1`
sits at the end of the body.

`code_8002E7A8.c` (batch 4): banked `func_80036294` (id byte -> pointer into one of eight work pools,
kind from `func_8002FE74`; `kind` must be `sint32` for the `slti` switch), `func_80030D30` (launch
angle from a delta, with an unused 8-byte `SVECTOR` local; `to->vy > from->vy` fixes the reg order),
`func_80030418` and `func_80030628` (view-cone flags: same body, the first reads positions at 0xC4 and
the angle at 0x56, the second takes positions at 0x14 and the angle as the 5th argument). Both need
`m[0] = 0x1000` written after `sv.vz`, and each `|=` test written as `(x >= 0 && ...) || (x < 0 && ...)`,
which gives the shared `ori`; this probably also fixes parked `func_8003081C`. Parked `func_8002FA38`
(`NON_MATCHING`; binds a table entry (kind, id, sub) to an object): only the entry pointer / counter
registers (a1/a2) are swapped. `func_80035508` stays assembly (GTE, same decision as above).

`code_8002E7A8.c` (small functions): banked `func_8002FE74`, `func_80030150` (16.16 vector rounded to
`SVECTOR`), `func_80031268` (`ratan2` of the x/z delta + 0x800), `func_80033EBC`, `func_8003697C`
(scratchpad fog setup, `SetFogNear(D_800BC81C, 0x180)`). `Fog_param_get` (banked in batch 7, below)
copies the far colour and near distance into four halfwords.
Banked `Angle_diff_clamp` (signed angle difference on a 0x1000 circle, clamped to +-limit; `r = limit`
first, and the else-branch test written `limit > 0x1000 - d`). `func_800323FC` and the slot allocators
`Open_EVE_WORK`, `func_80031734` were parked here; banked in batch 7 (below). The model-pool allocators `func_80031418`,
`Open_SHL_WORK` and `Open_PL_SHL_WORK` are banked: they matched once `field_74` (a `sint8`, read with `lb`
everywhere) was cleared with one word store over 0x74-0x77, like their other multi-field clears.

Banked `func_80031324` (initialises a child object from slot n of a parent: copies the 32-byte block at
parent+0x240+n*32, position from parent+0x180+n*8, takes and clears the id at parent+0xF9+n*4; the id
field is `sint8` so the `-1` store is `li -1`) and `func_8003545C` (claims a free bit of `D_80098798`,
24 slots, records it in owner+4 and stores the value in `D_800BE478[slot]`). Parked (`NON_MATCHING`):
`func_80031CA4` (clamped angle step toward a target; target keeps the `limit` parameter in s2 and a copy
in s1, GCC merges them) and `func_80030058` (rotates an offset (x, y, z) by an angle into a VECTOR; same
param/copy pair issue for x and z). Also parked (`NON_MATCHING`): `func_8003081C` (GTE view-cone test:
RotMatrixY/RotTrans, returns 0x10 behind, 2 inside; target stores `m[0]` late and shares one `ori 2`
between the x >= 0 / x < 0 paths) and `func_80031F84` (direction quantizer vs a base angle, returns
angle | side << 16; only the prologue order differs).

`code_8002E7A8.c` (batch 5): banked `func_80030CB8` (`func_80030CF0` with arc 0x100), `func_80030EE8`
(velocity (+0x44..0x4A) toward a target at speed `s`: `d * s << 8 / dist`, time = dist / s; the three stores
must be written vx, vy, vz, time) and `func_80033F04` (rotates unit vector `a` toward `b`: two
`OuterProduct12`, a scratchpad-like static matrix, `ApplyMatrix` twice, `VectorNormalS` of the closer result;
`angle` must be `sint32` and the `>> 16` chained `D_800985FC.vz = D_80098604.vz = ...`, else GCC keeps `limit`
in an extra s-register). The `D_8009857C`..`D_80098654` statics are now `MATRIX`/`SVECTOR`/`VECTOR` objects.
`Player_work.pos` is an `SVECTOR` (the 8-byte copy in `Obj_player_dist_set` only compiles with the unaligned
`lwl`/`lwr` per-access form from a struct member, not from a cast pointer). Parked (`NON_MATCHING`):
`Obj_player_dist_set` (squared xz distance, `<< 2`, of every object in three pools to each of the two players, -1 when
over 0x10000000, stored at +0x80/+0x84; the target keeps `D_8009F108` in t6 across the outer loop, computes the
next-object pointer first (`a3 = a1 + size`) with the counter increment in the branch delay slot; ours moves the
pointer add into the delay slot and the counter to the loop tail; needs an unused 8-byte `SVECTOR` local) and
`Model_pose_unpack` (unpacks 75 twelve-bit values from the 0x20-word block at `0x1F800180` into 25 `SVECTOR`s at
`0x1F800120`; the code is identical, only the register assignment differs: target d=a1, s=a2, counter=t0, ours
d=a3, s=t0, counter=a2). `func_80035508` stays assembly (GTE; needs the repo-wide GTE decision above).

`code_8002E7A8.c` (consolidation): the player and every pool slot share one object header (routine_0,
kind_1, flags at 6, position at 0x14, 16.16 position at 0x1C, angle at 0x56, model data at 0x88/0x90-0xAC,
keyframes at 0xF8-0x106). `Obj_work_flag_change` and `func_8002F420` apply `func_8002F3A8`/`func_8002F884`/
`func_8002F928` to several pools, `func_8002FA38` writes by kind, so `FLAG_WORK`, `MOVE_WORK`, `POS_WORK`,
`ATTACH_WORK`, `TURN_WORK` and `POS14_WORK` stay views until that header has a type. Merged: the keyframe and
joint views into `PL_WORK` (`tbl_F8`..`pose_mix`, `owner_188`, `base_mtx`, `joint_mtx[15]`, `joint_pos[15]`,
`pos_1C`, `pos_428`, `svec_438`), `OBJ_10C` into `SHL_WORK`, `func_8002F998`'s pointer into `EVE_WORK`.

`code_8002E7A8.c` (consolidation 2): the common header now has Capcom's type, `MODEL_WORK` (their source
passes `EM_WORK` to `Model_work_init`, `Obj_pos_set` and `EM_Char_Set` as `(MODEL_WORK *)`; field names from
it: `id`, `type`, `pos` 0x14, `pos_l` 0x1C, `old` 0x2C, `old_l` 0x34, `spd` 0x44 (pad = time), `add` 0x4C,
`ang` 0x54, `ang.vy` the facing). `ATTACH_WORK`, `FLAG_WORK`, `MOVE_WORK` and `POS14_WORK` merged into it;
`POS_WORK` into `WORK_48` (`func_8002F928` only sees `WORK_48`/`WORK_50`). Like Capcom, the pool types keep
their own structs with the same leading layout: `SHL_WORK` (`pos`, `pos_l`, `old`, `old_l`, `ang`),
`WORK_3C0`/`WORK_5A4`/`EVE_WORK` (`pos`) and `PL_WORK` (`pos_1C` -> `pos_l`, `unk56` -> `ang`). Still views:
`TURN_WORK` (`func_8002FF34`, only overlay callers; fields beyond MODEL_WORK at 0x428), `VIEW_WORK`
(position at 0xC4, overlay callers only; SHL_WORK has `owner_C4` there), `CHILD_WORK`
(`func_80031324` has no callers; `CHILD_PARENT` was merged into `WORK_5A4`, see below; `CHILD_WORK` looks like a MODEL_WORK but writes a halfword at 0xAC, where
MODEL_WORK has the byte `idx_AC`). `SLOT_ENT`/`SLOT_VAL` merged into one `SLOT_ENT[4]` at `D_8009A300`
(`func_800358F0` uses that base; the old labels `D_8009A306`/`310`/`31A`/... are fields of it).
Retried with the new types (no new matches): `func_80036C50` (now two registers from matching),
`func_8002FA38`, `func_80032538`, `Model_pose_unpack`, `pl_shot_spawn`, `Obj_player_dist_set` (unchanged).

`code_8002E7A8.c` (batch 6, from CoastRedWood's drafts): banked `Obj_launch_set`, `Pl_joint_mtx_set`,
`front_obj_search`, `Model_parts_mtx_set`, `lock_on_search`, `Pl_pose_unpack`, `func_8002F420`,
`hit_pair_check`. Types found: `SPAWN_ENT` (room spawn table entry), `LOCK_BOX` (`D_8008994C`),
`MATRIX_ROT`; `CHILD_BLK` was the parts' `MATRIX` (`WORK_5A4.mtx_240`, `WORK_3C0.mtx_1E8`); MODEL_WORK
gained `flag_4/5`, `field_C`, `old_ang`, `ofs_9C`, `slot_F8[24]` (the part tree), `scale_158`, `mtx_160`;
`SLOT_OWNER` is 0x10 bytes (`hit_0`, `mask_4`, `vec_8`); `GAME_WORK.unk078` is a union (flag byte, and
bytes 0x79-0x7A read in the word as a halfword). Three need a form GCC can't get from the plain field:
`Pl_joint_mtx_set` a `root` local, `Model_parts_mtx_set` the part slot as `wp + (i * 4 + 0xF8)` (the
target steps the byte offset), `lock_on_search`/`hit_pair_check` `v.pad` as halfword `j * 6 + 3` of
`D_800A2F48` (the target keeps that base in a register).
Parked `Obj_spawn_tbl_set` (`func_8002EA50`, `NON_MATCHING`): only the 0x60 case differs. GCC relates
`&Game_work.stage_no` to `&Game_work.unk078`, hoists one base into a saved register (s2) and reaches 0x50
as `-0x28(s2)`; the target builds `Game_work+0x78` in v1 each time and reaches 0x50 with its own `lui`.
It matches when 0x78 is read through a second declaration of `Game_work`
(`extern GAME_WORK x __asm__("Game_work");`, the draft's way), so the original reached one of the two
through another symbol; that alias is the owner's call.

`code_8002E7A8.c` (batch 7, from CoastRedWood's drafts): banked `Fog_param_get`, `Open_EVE_WORK`,
`func_80031734`, `func_80031498`, `func_800323FC`, `func_80031E60`, `func_80031DCC`, `func_80031EF0`,
`func_80032538`, `Muku`. What fixed them (GCC 2.7's alias rule: a store through a pointer into a struct or
array, `MEM_IN_STRUCT_P`, is taken not to alias a scalar global, so the scheduler moves loads and stores
across it):
- `Fog_param_get` (0x80036B00): `D_8009A370..74` are fields of `D_8009A350` (`FOG_BLOCK.far_r/g/b`,
  `near`; `func_80036A88` sets them); read as struct fields, the loads stay after the earlier stores.
- The allocators: `wp = &pool[i]` before the bit test, the mask update first, then the stores; the word
  clears at 8 and 0xC must be casts over byte fields (`EVE_WORK.field_8..F` are now bytes: the overlays'
  `STAGE_EVENT` reads `timer_C`/`step_D`), since a cast of a `uint32` field folds back to the field.
- `func_800323FC`: the chained `ent = wp->ent_FC = &wp->tbl_F8[...]`; `func_80032538` is
  `func_80032488` without `Model_parts_mtx_set_y`.
- `func_80031DCC`/`func_80031EF0`: `center2 -= 0x800` as its own statement, and the tests nested as
  `half1 * 2 >= d1`, `half2 * 2 >= d2` returning 1. `Muku`: `r` a `sint16`, `else if` with `u = 0x1000 - d`.

`code_8002E7A8.c` (batch 8, from CoastRedWood's drafts): banked every function parked above:
- `func_80031CA4`: `Muku` on the pitch angle (`func_8003129C`), written exactly like `Muku`.
- `func_80030058`: x, y, z are `sint16` parameters (negated in place), `in.vx = z << 12`.
- `func_8003081C`: `m[0] = 0x1000` after `sv.vz`, and one test on `(x >= 0 ? x << sh : -x << sh) < z`.
- `func_80031F84`: two `Angle_xz_svector` calls (`(to, &D_80097CF4)` when `to->pad` bit 0 is clear,
  else `(from, to)`) instead of reassigning the pointers; `s = (sint16)ang` local in the mode-0 arm.
- `fog_block_apply`: reads the far colour and near through `D_800BC7F8.far_r/g/b/near` (the struct it then
  copies), not the separate `D_800BC818..` labels.
- `func_80036C50`: plain `D_8009A300[i].id_6`/`flag_F` indexing, early returns.
- `func_8002FA38`: `e = (ATTACH_ENT *)tbl` in the `for` initializer (after the kind adjustment), `e++` in
  its step. `ATTACH_ENT.ptr_8` points at the `MODEL_WORK.ofs_9C` word followed by the `ptr_A0` table.
- `pl_shot_spawn`: the decrement copied into both arms (cross-jumping merges them), `field_C` stored
  before the `pos_l` words, the slot id kept in a local and tested as `(sint8)`.
- `Obj_player_dist_set`: `p = &pool[j++]` at the top of each loop body.
- `Model_pose_unpack`: `uint16 *d`, with `*d = ...; d += 2` where a pad is skipped, and the final sign
  extension through `Scratch_pose->vx/vy/vz` (literal addresses per field).

`code_8005C258.c` (small functions): banked `func_8005DCB4` (calls `area_map_explore`, `area_map_corner_draw`),
`func_8005D9EC` (`Player_work+0x6E = +0xB0`, then `func_8005D9C4`), `func_8005D844` (arms slot
`D_800BBE2C`..`E46`), `func_8005D98C`, `func_8005C720` (dispatch through `D_8008D7B4[wp[4]]`).
`func_8005D4F8` (once parked: the target reaches `D_800BBD84[1]` through one `lui`+`addiu` base
register, while the store to `D_800BBD81` uses its own `lui`) matched once `D_800BBD84` became an
unknown-size array (see the base-register finding below). `D_800BBD81` and `D_800BBD84[]` are separate
globals, not fields of one struct (declared in `code_8005C258.h`). `func_8005C720`'s `wp` is the 9-byte object at
`D_800BBD78` (byte +4 indexes `D_8008D7B4`); it stays `uint8 *` until that object's layout is known.

Later batch (from CoastRedWood's drafts): banked `func_8005C258` (clears `D_800BBD78` through +0xD4
with `Mem_clear`, i.e. 0xD8 bytes, apparently six 0x24-byte slots), `func_8005C868`/`func_8005C978`
(dispatch through `D_8008D7C0`/`D_8008D7C4`), `func_8005D528`, `func_8005D87C` (clears the eight
words `D_800BBE2C`..`E48`), `func_8005DA1C`, `func_8005DA78` (steps `Player_work.unk6E` by 2 up to
`unkB0`), `func_8005DBB4` (fills `D_800BC9B8` with -1, or restores it from `Cd_ring_buf + 0x1280`),
`func_8005E9F8` (translucent grey `POLY_F4` over a `RECT`), `func_8005EBE4`.
**Base-register finding:** `func_8005DA1C` matched only once `D_800BBD84` became an array of
*unknown size* (`extern uint8 D_800BBD84[];`, `[1]` = old `D_800BBD85`, `[3]` = old `D_800BBD87`): GCC
then keeps `&D_800BBD84[3]` in a register (`lui`+`addiu`), while a scalar or a sized array
(`[4]`) folds to `lui`+`%lo` each time. An extern struct field behaves like the unknown-size array.
`func_8005D4F8` matched the same way (banked).
Third batch (CoastRedWood's drafts): `D_800BBD78` is now `SLOT_WORK[6]` (0x24-byte slots; the
handler tables take a `SLOT_WORK *`). Banked `func_8005D574`/`func_8005D620` (open a free slot of
2-4 for an owner object, counted in `D_80098AF0`), `func_8005D6E8` (close the owner's slot),
`func_8005D7C0` (close all three), `func_8005D298`/`func_8005D39C` (a `SLOT_SPRITE` as a `POLY_FT4`
into OT 2), `func_8005C8A4`, `func_8005D8C4`, `Player_weapon_bullet_fill` (`func_8005DAEC`),
`func_8005DC10` (finds Game_work's stage/area in `D_8008D19C`, `AREA_ENT[0x40]`).
`func_8005D620` matches only with the colour word written as `(&D_800BBD78[2])[i].color_10`: the
target recomputes `i * 0x24` for that store; `D_800BBD78[i + 2]` reuses the offset and is 0x10 short.
Fourth batch (CoastRedWood's drafts): banked `func_8005EAA8` (two full-screen `POLY_G4` bands in the
colours of `D_8009806C`), `func_8005C75C` (slot 0's idle watcher: calls `func_8005D528` after 150
frames, 90 still frames, or 60 frames with `kind_C` set and 60 still), `area_map_explore` (clears the
explored bits of the 3x3 map cells around the player in `D_8009882C`), `func_8005D0FC` (gauge of
`Game_work.gauge_05C`/`gauge_max_05E`), `owner_life_gauge_draw` (the slot owner's life gauge), and
`area_map_draw` (the area map: player arrow, explored cells textured from the cell map `D_8009878C`,
draw-area changes; `D_8008D19C` records are now width/height/explored bitmap/origin).
`func_8005EAA8` and `area_map_draw` need the colour words written through a word-view struct
(`POLY_G4_WORDS`): `*(u_long *)&p->r1` gives the same instructions in a different order, since GCC 2.7
puts struct fields in their own alias class. `area_map_draw` also needs the post-increment form
(`area = Map_area_ptr++;`): the assignment form allocates the loaded pointer differently.
`func_8005E9F8`'s rectangle is PsyQ's `RECT` (`SCREEN_RECT` removed): a plain halfword copy loads a
`short` with `lhu` too, and `area_map_draw` needs the sign (`rect->x + rect->w >= 0`).
Parked `weapon_gauge_draw` (`NON_MATCHING`): the target sets `&D_80089EAC` and 0x7FFF into a2/a3 at the top
of the block after the first call; GCC folds the address into the load (`lui`/`%lo`). The fork matched
it only with a dead conditional store (FAKE) that splits the block there. The `level` local is needed
(without it, `- 1` is reassociated).
Parked `life_gauge_draw` (`NON_MATCHING`): only one extra `nop`, after case 3's `lb v0,9(s0)`. maspsx
pre-scans the whole file, finds `D_8009802C` in this file's `.sdata` and expands the indexed load as a
`$gp` access (whose first instruction reads v0); the target has none, as for the extern `D_8008D7C8`
in case 2. A tool question, not a source one (see the report).

`code_800456D8.c`: banked `func_80045918`/`func_8004594C` (`WORK_48.timer_B` countdown, then `routine_8`
+= 2 / += 1), `func_80045A7C` (`Sound_call2(0xCF, &wp->pos_38)` then `func_80031988`), `func_80047318`
(`D_8008A708[wp->routine_8](wp)`). Parked `func_80045FE4` and `func_80046008` (identical, `NON_MATCHING`):
the target is `func_8002FE74(wp->kind_1)` followed by `move v1,v0`; GCC drops the dead copy for a
`void` function with a local, and a `return` form emits no move either (also tried `register`).
Also banked: `func_80047D9C`/`func_80048354` (`D_8008A724`/`D_8008A76C[wp->routine_8](wp)`), `func_800485E4`
(`D_8008A778[wp->flag_4](wp)`), `func_80048268`, `func_80046848` (`WORK_48.flag_3` picks sound 0x9E/0x9D).
Banked `func_80047C84`: copies `D_8008A6C8..CF` into `WORK_48`. It was parked over the `field_14`
word copy (the target does it third; GCC delayed it to the end), but it matches as written since the
later `WORK_48` type changes.
Parked `func_80047354` (`NON_MATCHING`, spawn/init of a `WORK_48` by `flag_3`): all instructions match except the
tail layout. The target tests `flag_3 & 0x80` with `beqz` (`sub = 0` store, then `j` to the shared `Model_work_init`)
and keeps the `sub = 4/5/6` arms as three separate stubs; ours inverts the 0x80 test and merges the arms. Tried
flat if/else, nested, `goto init`, `sub = flag_3 & 0xF` vs constants.
Banked: `func_800469A4` (matrix at `WORK_48+0x18` with diagonal `field_3E`, `RotMatrixY(field_C.angle)`, angle
+= 0x100; chained store `m00 = m11 = m22`), `func_800459C0`/`func_8004678C` (same matrix with the diagonal
`pos_38.pad >> 1` for m00/m22; `field_2E += field_34`, `pos_38.vy += field_2E`,
`field_3E -= D_80097E64/D_80097EE0[field_A] >> 3`, `routine_8++` once `field_2E >= 0`), `svec_distance`
(distance of two SVECTORs via `SquareRoot0`), `func_80047CD8` (steps through the 8-byte records at
`D_8008A6C8`; separate symbols indexed by `i * 8`). Parked `func_800482A8` (`NON_MATCHING`; Player_work
`unk09 == 3` and `unk11C & unk128/unk12A` pad test, else `routine_8 = 2`; returns 1/0): the target ends the
two AND tests with `beqz`/`li 1`/`move 0`, GCC emits `sltu` for `hit != 0` (tried nested returns, a `hit`
local with `goto fail`, and `== 0` forms).

Batch (`func_80046A0C`, `_8004602C`, `_80047EC8`): banked `func_80046A0C` (proximity test like `func_80045BC8`, then
calls `Money_add`/`func_80043340` with `D_8008A678`/`D_8008A680[Game_work 0x5B][field_A]`; `field_A` is kept in a
local) and `func_8004602C` (per-frame draw of the effect: `D_8008A6A8[routine_8]`, then one `Billboard_get` primitive
filled from the four columns `D_80097EC0/C2/C4/C6`, each its own symbol). Parked `func_80047EC8` (`NON_MATCHING`;
eight spark lines around the player's position at `Player_work+0x400`/`+0x418`): structure matches; the else-branch
angle `- 0x100 + rand` becomes `li 0xff00; addu` (as in `func_80047DD8`), the `y - (sin - 0x10)` is folded to
`y + 0x10 - sin` where the target keeps the `- 0x10` on the sine term, the primitive pointer is copied to `a2`, and one
`addu s0` has swapped operands.

Batch (`func_80047DD8`, `_80045BC8`, `_80046F38`, `_80045CE8`, `_800477A0`, `_80046B34`): banked
`func_80045BC8` (proximity test of the effect at `pos_38` against both players:
`(uint32)(dx + r + 0x32) <= 2r + 0x64` with `r = D_80097E64[field_A + 6]` as `uint32`; the second player is `Player_work[1]`). Parked, all `NON_MATCHING` with the best attempt kept:
- `func_80047DD8`: only `- 0x100 + (rand() & 0xFF)` differs (GCC folds it into `ori 0xff00`; the target does `addiu -0x100`
  then `addu`) and one `addu` operand order. The `Player_work` base is hoisted by taking the result of
  `func_800482A8` in a `uint8` local first, then `pl = Player_work`.
- `func_80046F38` (samples four 32-word tables `D_8008A378` at `(t + 10 * j) & 0x1F` into four rows of five words at
  `D_8009A6C0`, `t` = scratchpad half-word `0x1F800002`, then copies each word of `D_8008A578[6]` into four words of
  `D_8009A710[6][4]`): the table reads match as plain 2D indexing; the target keeps `&D_8009A6C0` in a register
  (+0x14 per row) for column 0 but reaches columns 1-4 with a `lui` each, and keeps loads and stores strictly
  alternating. Scalar externs for those columns let the scheduler reorder (non-struct stores do not alias the
  array loads); `volatile` made it worse.
- `func_80045CE8` (spawns `count` effects round a circle; `weights` bytes pick one of five tables, `kind` picks a row of
  `D_8008A2B0`): whole body matches; only the prologue move order (a2, a3, a1 vs a1, a2, a3) differs. What made the
  body match: `for (...; i++, ang += step)`, signed `switch` value, `(rnd & 3)` written inline (no local), stores
  in the order `field_A`, `field_3E`, `field_C`, `field_C+2`.
- `func_800477A0` (per-frame colour/scale fade of a `WORK_48`, `switch (flag_3 & 0xF)` with cases 0/3/default sharing
  code): prologue, sums and jump table match; the target keeps the five colour tails separate (each ends in a jump
  to one shared `or; sw`) with the channel in a2, GCC cross-jumps them. Separate locals per case did not help.
- `func_80046B34` (two bursts of effects, `spec` packs count/kind of each): only register allocation; the target
  spills the second burst's count and kind and both table pointers (frame 0x70), ours keeps `count2` in a register.
- `func_80047228` (picks `D_800988xx[kind pool][field_2][n].spec`, calls `func_80046B34`): only the last add differs
  (`addu v1,v1,v0` in the target, `addu v0,v0,v1` here). `func_80047148` (same with n = 0) and `func_800456D8` are banked.
`WORK_48` gained `field_2C`..`field_36`, `field_40`, the `u_44` union (`ptr` / `hw[2]`) and `pos_38` (an `SVECTOR`; its `pad` was `field_3E`).
The 8-byte `lwl`/`lwr` position copies are plain `SVECTOR` assignments (GCC copies a 2-aligned struct that way), so
the old `BYTES8` type is gone.

Bouncing-debris routines of `WORK_48` (`code_800456D8.c`): banked `func_80045750` and `func_8004622C` (move by
`field_2C/2E/30`, collide with `Pos_map_push_out(&pos, &old, 1, HIT_ENT *)`, halve the vertical speed on a floor hit
(`0x1000`) and restart the matrix with `RotMatrixY(field_C.angle)`). Parked, `NON_MATCHING`: `func_800465C8` and
`func_80046438` (same shape, ground-follow variant; `D_8008A622` is the +0xA halfword of `D_8008A618`'s 12-byte
records, read through its own symbol). Only a register differs: the target leaves `ground - (D + 1)` in v0 (copy
of the 8 bytes scheduled between the `D` load and the `addiu 1`); this build puts it in v1. `ground - (D + 1)`
written inline folds to `(ground - 1) - D`, so a local `h = D + 1` is needed to get the separate `addiu`.

`code_800456D8.c` (consolidation): `WORK_48`'s 0x18-0x37 is a union `u_18` by kind: `mtx` (the model kinds, with
bit 2 of `routine_0` set, position in `pos_38`; replaces the `(MATRIX *)&field_18` casts and the raw word stores of
`func_80047354`) and `s` (`field_18`, `pos_1C` for the kinds without bit 2, which `func_8002F928`/`POS_WORK` moves,
`field_22..24`, and the debris speed/acceleration `vx_2C..az_36`, which share the bytes of `mtx.t` while the debris
uses `mtx.m`). `HIT_ENT` (`D_8008A310`, `D_8008A618`) is three (min, max) halfword pairs; `D_8008A622` is written as
`D_8008A618[i][j].max_A` (same bytes; only the relocation symbol changes). Retried after the change, no new matches:
`func_80046438`/`func_800465C8` (5 + 1 cycles: `ground - h` inline, copy order, `>` compare; the limit stays in the
wrong register), `func_80047354` (4: if/else-if with its own call, value local `n` stored per case, a call per case;
GCC always cross-jumps the identical `sub` stores the target keeps separate), `func_80045CE8` (clamp order: worse),
`func_80046B34` and `func_80047228` (unchanged).

`code_800456D8.c` (from CoastRedWood's drafts): banked every function parked above except `func_80046B34`,
`func_800477A0` and `func_80047EC8` (banked later, below). What made each match:
- `func_80045FE4`/`func_80046008`: the `move v1,v0` is a dead `switch` on the result that picks a `SPEC_ENT *`
  from the four kind tables and never uses it.
- `func_80047228`: the `+ n` is added in each case (`e = D_8009884C[wp->id_2] + n;`), then `e->spec`.
- `func_800482A8`: returns `uint8`; `pad`/`hit` `uint16` locals, `if (hit) return 1;` and the fail block as the
  `else` of the state test (with the `fail:` label inside it), `return 0` last.
- `func_80047DD8`: no local for the result (`if (func_800482A8(wp) == 0)`, the `uint8` return gives the `andi`), a
  `W48_89_LINES *` to `wp->lines_28` (the two eight-halfword arrays as one struct), and
  `(sint16)(pl->ang.vy - 0x100) + (rand() & 0xFF)`.
- `func_80046438`/`func_800465C8`: a third local `limit = ground - h`, compared as `limit > pos_38.vy`.
- `func_80046F38`: written unrolled through a `uint32 *dst` stepped by 5, and `D_800986D0` must be a scalar
  (`static sint32 D_800986D0; static sint32 D_800986D4;` instead of `[2]`): an array element's store may alias
  `dst[0]` and stays in source order; the scalar's is scheduled after the first load, as in the target.
- `func_80045CE8`: the clamp is `if (num > 16) count = 16; else count = num;` (fixes the prologue order), with
  `continue` for a failed open and an `else if` chain with `acc +=` inside the tests.
- `func_80047354`: a `Model_work_init` call in every arm (the 0x80 test first, each `switch` case, both arms of the
  ceiling test); cross-jumping leaves the separate `sub` stores. The dead `sub = svec_distance(...)` is needed.

Later drafts banked the last three (the file has no parked function left among them):
- `func_80046B34`: the first count's clamp is `if ((spec & 0xFF) > 16) count = 16; else count = spec & 0xFF;`
  (the mask written twice), the second goes through the same `count` (`count = count2; if (count > 16) ...`), all
  locals `uint32`, `continue` on a failed open and on `idx >= 5`; `ptr_44` before `field_A` in the first loop.
- `func_800477A0`: each case's colour as an `if`/`else` that assigns `c` in both arms (no `c = 0x80` before the test),
  `c | 0x02000000 | (c << 8) | (c << 16)`; case 5 is `c = (8 - field_A) * 16`; `routine_8++` before the
  `pos.pad = 0`; `RotMatrixY(++wp->timer_B << 7, ...)`.
- `func_80047EC8`: `W48_89_WORK.pos_1C` is `sint16` and `W48_89_LINES.ang` `uint16`; early `return` on
  `func_800482A8`; `if (++d->idx[i] >= 8)`; the else angle `(sint16)(ang.vy - 0x100) + (rand() & 0xFF)` (as in
  `func_80047DD8`); `y - (sint16)((sin * h >> 12) - 16)` keeps the `- 16` on the sine term; the primitive's words in
  order 0, 1, 2, 3 (`lit ? 0x104080 : 0x10101`), 4, 6.

`code_8004324C.c` (batch 1): banked `func_8004324C` (player `unk174 & 0xC0 || unk177`; must be `if (a || b)
return 1; return 0;`: two separate `if`s fold the second test to `sltu`, a bare `return a || b` uses a temp),
`Money_check` (`-(Game_work.money < -amount)`: -1 when `money` can't cover a negative change; `money` at
`Game_work+0x1C`, capped at 999999 by `Money_add`), `func_800433C0` (`D_8008A0CC[wp->routine_8](wp)` on a
`SHL_WORK` of the `D_800BFB20` pool), `func_800435BC`, `func_80043740` and `func_80043E00` (spawn a `WORK_48`
at the slot's position; in `func_80043E00` the `flag_3`/`field_C` stores are written after the position).
Batch 2: banked `Money_add` (0x80043294; `amount` added to `money`, clamped to 999999 when positive, reset to 0
on underflow when not, which also adds it to `Game_work+0x20`/`+0x24` by `c`; does nothing unless `b == 0`),
`func_80043340` (`Player_work[n].unk6E += amount`, capped at `unkB0`; player 0's losses are added to
`Game_work+0x4C`), `func_800435F8` and `func_80043E78` (queue `x_14`/`pos_2C` with `func_8003430C`; the source
has one call per value of the `0x6000`/`0x4000` argument, and `func_800435F8` repeats that `if` in both arms of
its `field_E` test: the target duplicates the `0x6000` setup). `field_C` is `sint8` (read with `lb`; the
`(uint8)` casts give the `andi`/`lbu` before `func_80036294`), and `func_800375D4` returns `sint32` (the caller
doesn't re-extend it).
`SHL_WORK.field_8` is split into `routine_8`/`field_9`/`field_A`/`timer_B`; `field_C` holds the owning player's
id (`func_80036294` returns a `PL_WORK`: `func_800433FC` reads its `joint_pos[11]`/`[14]`; `+0x198` is that
player's state flag for the slot).
Batch 3: banked `func_800433FC` (frame has 0x18 bytes of unused locals: an `SVECTOR` + `VECTOR`, like
`func_800437F8`'s), `func_800434F0` (calls `func_80036294` twice: once kept for `unk198`, once for the copy of
`pos` to `old`), `func_800437F8` (launch: direction `(0, 0, -0x1000)` rotated by `func_80039B80()`/`field_64`,
speed `dir * D_80097DD4[idx[2]] >> 4`, collision box `hit_78 = &D_80097DA0`; `field_88` is stored twice, the
constant first; `x_90 = pos.vx = pos_l.vx >> 16` is Capcom's chained form, cf. `efc.model.sv` in
`EM09_49.C`). `func_80043DF8` is empty but takes `(wp, &m)`: `func_800437F8` passes both. `func_80037634`
now returns `sint32` (as `func_800375D4`): `func_80043A8C` compares it without re-extending.
Parked `func_80043A8C` (homing flight toward `tgt_BC`, `+0xBC`, the vector `func_80035508` projects): GCC
store-flags the 0/1 argument of `func_80043E00` (`id != 0x7FFF`) into `xori`/`sltu` where the target
branches; if/else, switch, ternary, goto and two calls (not cross-jumped) all tried. The speed multiplies
also differ by a v0/v1 swap (target loads the table byte before `dir.vx`). The rest, including the
`if (...) {...} else { close: ...; return; } func_80043E78(wp);` layout, matches.
Banked `func_800437A8` (the shot's update: `D_8008A0D8[wp->routine_8](wp)`, a table of `func_800437F8` and
`func_80043A8C`, then `func_80051BAC(wp)`, which the player code also calls: it pushes the object on the
list at `D_80098898` when `routine_0 & 3`, and clears `+0x7C`).
`SHL_WORK` fields from these: `spd`/`add` (0x44/0x4C, MODEL_WORK's), `hit_78` (`HIT_ENT *`, read by
`func_80049C24`), `field_7C`, `field_88`, `rgbc_8C`, `x_90`..`z_94`, `field_96`/`97`, `field_9A`, `dir_A4`,
`tgt_BC` (tested as two words, Capcom's `*(uint32 *)&v.vx` idiom).

`code_800680BC.c` (event steps): `D_8009039C` is an event table of 8-byte entries (`u8`, `u8`, `s16` frame,
step function), installed as `Scene_work+0xA4` by `event_scene_init` (from `func_80068DAC`, a `Scene_func_tbl`
scene routine called with `&Scene_work`). `Sce_event_update` advances it when `Scene_work.timer_10` reaches the
entry's frame and resets the timer. Entry bytes 0 and 1 are copied to `Scene_work.ev_08`/`ev_09`;
`timer_18` restarts when `ev_08` changes and `timer_1C` when either changes. `Sce_event_set(table, arg)`
(called only from overlays ST15/ST1B/ST1E) installs a table and sets `D_800BC7F0 = arg`; `Sce_event_timer_clear`
(many overlays) clears the timers and both bytes. Banked steps `func_8006885C`, `func_8006888C` (calls stage code
`func_80101D94` at frame 10), `func_800688BC`, `func_800688E4`, `func_80068BC0`, `func_80068CB8`: at frame 0
each sets `field_9` (and clears `field_A`) of one of `Scene_work.obj_24[0..2]`. `obj_24` is `void *[16]`:
`scene_obj_open` fills it from four pools by the kind byte of each object entry, and this scene's entries
(`D_8008FF88`, opened by `event_scene_init`) make `[0]` a `WORK_3C0`, `[1]`/`[2]` `WORK_5A4`, `[3]` a `WORK_50`.
The object must be read into a local of that type: the byte stores alias the array.
Entries are typed `EVENT_ENT` (`scene.h`); `event_step_call` (0x80068D64) runs the current entry's function
unless `ev_08` is 0xFF. Also banked: steps `func_80068344`, `func_80068728` (sets `obj_24[3]->field_E` and
`Scene_work.field_64`), `func_80068760`, and `event_scene_init` (the scene's setup: resets the camera
with `func_8001E6C0(0, 0, 0)`, installs camera script `D_8008FFD8` in `Sce_camera_work.arg_C0` (a `uint32 *`
command list stepped by `Sce_camera_update`) and event table `D_8009039C`, opens the four `SCENE_OBJ_ENT`s of
`D_8008FF88` with `Scene_obj_ent_open`, clears `field_64`); `func_800680BC(arg)` resets the bytes/halfwords `D_800C3560`-`D_800C3571`
(`D_800C356F = arg`, `D_800C356E = 0x18`); `part_col_step(obj, n)` steps
`WORK_5A4.pos_180[n].col` by 0x421 up to 0x4210 (an RGB555 fade on `obj_24[1]`). It matches only with the
field written at each use: a `sint16 *col = &wp->pos_180[n].col` local adds an `addiu 0x180`. Its 8-byte
frame comes for free: no unused local needed.
Also banked: `func_80068244`, `func_8006849C`, `func_8006890C`, `func_80068998`, `func_80068AB0`,
`func_80068B3C`: call `func_800680BC(0/1/2)` and set or clear bit 1 (sometimes bit 0) of
`obj_24[0..2]->routine_0`. `func_8006849C` tests `Scene_work.field_0C` (0x0C, otherwise only cleared by
`func_8001DDE4`) instead of `timer_10`. Two matching idioms: when two objects clear bit 1, the mask is an
`int` local (`mask = ~2`; a literal folds to `andi 0xFD` at each use, the target loads -3 once), and the
register split shows which objects shared one pointer local (`obj_24[0]` separate, `[1]`/`[2]` one local).
Also banked: steps `func_80068290`, `func_80068388`, `func_800687D8`, `func_80068A24`, `func_80068BE4`,
`func_8006854C` (frames 14-20 run `part_col_step` on ten parts of `obj_24[1]`; frames 90-120 raise
`Scene_work.field_68`/`6C`/`70` by 9, clamped to 0xFF together: probably an RGB fade level).
`func_80068388` writes `obj_24[1]`'s per-part entries (`WORK_5A4.slot_F8[n].field_3`, `pos_180[n].col`).
WORK_5A4 has 24 parts: `slot_F8[24]` (4 bytes), `pos_180[24]` (8 bytes), then 0x300 bytes to `base` at
0x540, which is `CHILD_PARENT.blk_240` as 24 entries of 0x20. **Merged:** `CHILD_PARENT` was a view of
WORK_5A4 (the same parts at the same offsets; `blk_240[24]` fills 0x240-0x53F exactly), so
`func_80031324` takes a `WORK_5A4 *` and WORK_5A4 has `info_88` and `blk_240[24]`.
`screen_tile_draw(r, g, b, abr)` (0x80068120, called by `func_80068DAC`) links a semi-transparent
320x240 `TILE` and a `DR_MODE` (tpage `abr << 5 | 0xF`) into `Disp_env_ptr->ot[1]`. Each primitive
takes 0x28 bytes from the scratchpad pointer `Map_prim_ptr` (0x1F800070, Capcom's name), whatever its size.
`Disp_env_ptr` (0x80098934) is the shim's name for the current `DISP_ENV`.
Banked `func_80068DAC(sw)` (0x80068DAC), the scene's main routine, a switch on `Scene_work.routine_4`:
0 waits for `func_80042238(Player_work)`, clears bits 0-1 of `Player_work[0].unk00` and plays XA
`0x2001000B`; 1 waits for `func_8001D878`, sets `field_0C = 30`; 2 counts `field_0C` down, then
`Fade_start(2)`; 3 `event_scene_init` and falls through to 4 (ends when `D_80098A72 == 0` and the
event table reached its 0xFF entry or `func_8001DE84` says START skipped, `Fade_start(10)`) and 5:
the per-frame work (`event_step_call`, `screen_tile_draw(field_68, 6C, 70, 74)` while `field_64`, the
camera, `Sce_event_update`, the empty `func_80068DA4` at `timer_14 == 0x4680`, 5 minutes). In 5 with
`D_80098A72 == 0` it sets the `D_800C3560`.. block for the next stage (0x1B, 6), clears `unk00`, pauses
the CD (`Cd_subcmd(0, 1, 0)`), restores the player (`func_80042314`), `func_8001E390(0x2EB)`,
`Sce_flag_on(0x55)`, `func_8001D974`. So `screen_tile_draw` takes `uint8` r, g, b (the caller loads
the low bytes of the `uint32` fields with `lbu`), and the stores only match with `D_800C356C = 2`
written first (its constant is loaded before the others; its store stays in place).

`scene.c`: `Sce_flag_init(load)` (0x8001D8C0, from `Game_init`) clears the 0x100 bytes of
`Sce_flag` and sets the new game's (`func_80067E18`, `func_80067E4C`), or copies them from the save image
at 0x380 (`Mem_copy32`, 8 blocks). `Sce_update` (0x8001D990, per frame from `func_800158F0`): while
`Scene_work.unk00` is 0 (no scene) and `D_800C356C` is 0, calls the stage's `D_80088FA8[stage_no]`
(overlay code); while it is set, `Scene_func_tbl[id_01]` (unless 0xFF), and once the routine clears
`unk00`, marks the scene seen (flag 0x380 + `id_01`). So `unk00` is "a scene is running".
`func_8001E390(flag)` sets one flag of 0x2E0-0x2EB and clears the rest; `func_8001E460(n, on, on2)` sets
or clears flags 0x7E0 + n and 0x7C0 + n. `Scene_obj_ent_open` (0x8001EAE8) opens one `SCENE_OBJ_ENT`
with `scene_obj_open`, then copies `type_04`, `flag_02`, `field_08` into the object (a
`SPAWN_ENT`-like entry with the bytes in a different order).
`Scene_obj_list_open` (0x8001DF10, called by the stage overlays) opens every entry of a
`SCENE_OBJ_LIST` {count, entries}, copies each object to `D_800ACD40[index]`, clears its flag bit 5
and sets bit `0x80000000 >> index` of `D_800988E8`, so `func_8001E068` ends them later;
`obj_list_ent_open` (0x8001DFEC, no callers) does the same for entry n without the flag.
`func_8001EB98(ent)` opens one entry but puts back the old `Scene_work.obj_24[index]`, clears the
object's bit 5 and returns it. `func_8001E4C4(ids, flags)` walks up to 8 nonzero ids and calls
`func_8001E460(id, bit 0, bit 1)` for each flags byte other than 0xFF.
`scene.c` (0x8001D928..0x8001F798): banked `func_8001D928(keep)` (clears `D_800BE438[16]` unless `keep`,
then `Scene_work` bytes 0-3 with one word store and `D_800989F8`/`_9FC`/`_A00`; the clear loop only
matches as a walking pointer `*p++ = 0`, the indexed loop comes out descending), `func_8001DDE4(arg)`
(unless `Player_work[0].unk6E < 0`: `unk00 = 1`, `unk01 = arg`, clears the event bytes, timers and
`obj_24[]`; needs a local `sw = &Scene_work` for `unk00` and the `obj_24` loop only, the target's loop base
is `sw + 0x3C` with offset 0x24), `func_8001DE84` (1 if `Joy1` START is pressed and `Game_work.unk05A` or
scene flag `0x380 + Scene_work.unk01` is set; nested `if`s, a single condition gives `sltu`),
`func_8001F6C4` (seeks `Cd_seek_file` to the stage's first file from `D_800893BC[D_800C356E]` unless
`Game_work.unk068` already has it, else to entry `D_800C356F + 1` unless negative or equal to `unk06A`; one
call with a `file` local; `D_800C356F` is read into a local before the first test), `func_8001F798(n)`
(halfword copy job `D_80089248[n]`, `HALF_COPY_ENT`). Parked `Sce_event_next` (`NON_MATCHING`; the event-table
step of `Sce_event_update` without the frame test): only the first four instructions differ. GCC keeps the
address of `Scene_work.ev_ptr_A4` in a register for the load and the store; the target uses `lui` + `%lo`
for each. Experiments: in GCC 2.7 the *first* load/store pair on one constant address in a function gets
the shared address register (also seen for `Game_work.unk053++` in the banked `func_8001D974`, and for
`unk14++` in a reconstruction of `Sce_event_update`, whose target also avoids it). A dead read of another
global before it (`dead = Scene_work.timer_10;`) gives the target's code exactly, so the source probably had
some statement that compiled away; an unused `&Scene_work` local, a parameter, `++` forms, a pre-read of
`ev_08` and a pre-increment inside the condition don't do it. Same probably applies to `Sce_event_update`.
Update: banked `Sce_event_update` (per-frame tick: `unk14`, `timer_18`, `timer_1C`, `timer_10` `++`, then
the step when `ev_ptr_A4->frame_2` (not -1) equals `timer_10`) matches with a local
`SCENE_WORK *sw = &Scene_work` used for every access: the shared address register disappears. Reading
`Scene_work.ev_ptr_A4` into an `EVENT_ENT *` local moves the shared register onto `ev_ptr_A4` instead.
The step has to read `sw->ev_ptr_A4->ev_0` after `sw->ev_ptr_A4++` (old pointer + 8), not a stepped local.
Banked `Sce_event_next` the same way: written exactly as `Sce_event_update`'s step through `sw`, it matches.

Also banked in `scene.c`: `func_8001F23C` (from r3_sup: `Stage_reverb_tbl[stage_no]` reverb; when
`D_800893BC[stage_no][0]` differs from `Game_work.unk068`, clears `Stage_idx_tbl` and loads that file
and the area's, then `func_8003A3B4`/`func_8003AD14`; runs `D_80089714[stage_no]`, bumps halfword
0x62, sets bytes 0x64/0x65 except in stages 5, 6 and 0xF, clears `unk174.w[0..7]`; matches only with
`gw = &Game_work` first and the `cur` copy of `unk068`), `func_8001F740` (`func_8001F798(Game_work.stage_no)`, then
`D_8008980C[stage_no]()`, `STAGE_FUNC`), `func_8001F5E4` (reloads three files with `Cd_read_comb` when
they change: `D_80089200[Player_work[0].unk16A]` → `Game_work.file_070`,
`D_80089204[(sint8)unk16B >> 1]` → `file_072`, and when `tbl_sel >= 2`, `D_80089208[tbl_sel]` →
`file_074`; the `file` local must be `sint32`, a `sint16` reloads the table for the store),
`Sce_flag_off` (clears the bit; for flags 0x500-0x51F also removes `flag - 0x4FF` from
`Player_work[0].rb_parts_sort_data[32]` and `rb_parts_equip_data[3]`; needs `p = Sce_flag; p += flag >> 3;` and `mask`/`bit`
locals assigned in that order), and the camera pair on `Sce_camera_work` (`SCENE_CAM_WORK`, `scene.h`; one
object from 0x800BC730 to at least 0x800BC7F3, which splat splits into many labels; `D_800BC7F0` is its
`arg_C0`): `func_8001E550` hands position and angles (`func_80038324`) or look-at point
(`func_800384A4`, whose second argument is a `VECTOR *`) to the camera code, through a local
`cp = &Sce_camera_work` (CSE turns the accesses before the first join into `%lo(sym+off)`, the later ones
keep the base register, as in the target); the high halfwords at `ang_40 + 2/6/0xA` are plain
`vx >> 16`, which GCC narrows to `lh`. `func_8001E6C0(x, y, z)` resets it from the current camera
(`D_800A39A0`, angles `D_800A3968/396C/3964 & 0xFFF` into vx/vy/vz); `D_800A395C = 3` only schedules
right when written after the first `ofs_A0` store.

Also banked in `scene.c` (from CoastRedWood's drafts): `Angle_xz` (angle from (x0, z0) to (x1, z1):
`catan` of `(dz << 12) / dx` against the quadrant table `Angle_xz_quad_tbl`), `scene_obj_open` (opens a scene
object from the pool its third argument names, stores it in `Scene_work.obj_24[index]`; the 0xE0 /
`WORK_50` case copies the position into `efc.model.pos` as two words; it needs `goto end` when that pool
is full, a `break` leaves the other pools' pointer uninitialized on that path and costs a saved
register), `func_8001E068` / `func_8001E20C` (all / one of the `D_800ACD40` objects: `routine_8 = 2`
and one call of its pool's handler, or `func_80031824` for a `WORK_3C0` of id 0x10; the pool from
`func_8002FE74` must go through a `sint32` local, the switch on the `uint32` return gives `sltiu`
for the target's `slti`), `Sce_flag_on` (sets the bit; buster parts 0x500-0x51F join
`rb_parts_sort_data`, and set their twin flag + 0x80, as do 0x540-0x543 and 0x558-0x57F; key items
`PL_KEY_ITEM_00` + n set or clear the flags listed in the code), and `Sce_camera_update` (steps the camera
script `arg_C0`, then adds the three velocities). `WORK_50` bytes 8-0xB are `routine_8` ... `timer_B`
like the other pools' (was one `field_8` word).
Also from the drafts: `func_8001F580(file, close, set)` (`func_8002FBF4` if `close`, `Game_work.unk06A =
file` if `set`, then `Cd_read_comb(file)`; called by r3_st06, r3_st19, r3_st1a) and `func_8001F3C8`
(from `func_800158F0` and r3_sup: area file `D_800893BC[stage_no][area_no + 1]`, `func_8001F5E4`,
`Sce_read_sync(0)`, `Obj_work_flag_change(0x3FE, WORK_KILL)` unless `D_800C356C` is -1; then
`D_80089790[stage_no]()` and resets: player 0's `routine_8`..`field_B` word, `flags_BD` bit 6,
`weapon_right_no`/`unk171` from `unk44E`/`unk44F`, `Game_work.unk07E`, `Sce_flag_off(0x1FF)`). In `_3C8` the
`gw = &Game_work` and `pw` locals must be assigned *before* `stage_no`/`area_no` are read: assigned
after the call (the draft's order) GCC derives `&Game_work` from the first load's address
(`s0 = &Game_work + 0x50`, `gw = s0 - 0x50`); before, the target's separate `lui`s come out, and the
two address loads still land after the call. `Sce_read_sync` is now defined `()` (no parameter
list), since this file calls it with an argument.

`moji.c` (message control codes): banked `func_800546B0` (`timer_4 = unk_3F = get_le16(arg)`, chained),
`func_80054874` (`Sound_call(get_le16(arg), 0, 0)`), `func_800560D0`, `func_80058D64` (cursor x/y from two
16-bit arguments), `func_800594CC` (the `cmd_ptr_6C` twin of `func_80059530`; `unk_72` is `sint8`, `lb`).
`MOJI_CMD_WORK` was merged into `MOJI_WORK`: `Moji_work` is an array of 0xC4-byte entries
(`func_80053B40` walks it in 0xC4 steps; `func_80058788` gets the entry index as `wp - Moji_work`, an
exact division by 0xC4), and the two views' fields don't overlap. Each entry has two read pointers with
their own call stacks: `mes_ptr_14`/`call_stk_18`/`call_sp_BE` (text) and `cmd_ptr_6C`/`call_stk_4C`/
`call_sp_C0` (commands). Also banked, all matching at once: `func_80054798`, `func_8005497C` and
`func_80054A04` (call into a message of `mes_file_44`, or of `D_8008CACC` when it's NULL), `func_80058788`,
`func_80058DB4` (fills `D_800BE2F8[0..0x7F]` with 0xFF; GCC reverses the loop), `two_digit_set` (two
digits from `D_8008D028`, leading 0 replaced by font code 0x4F).
`func_80054874` zero-extends the id (`andi 0xFFFF`), so `Sound_call`'s `id` is `uint16`, not `sint16`
(`sound.c` still matches). Parked `func_80055C1C` (`NON_MATCHING`; if `flags_0 & 0x10000`, call
`func_80039E18` and clear the bit; then step 1): only the tail differs, the read pointer gets `$v0` where the
target has `$v1` and `li $v0,1` in the load delay slot. Banked later: the cause was the callee's return
type (see the `Money_add` paragraph below); `func_80039E18` is now declared `sint32`.
Also banked, matching at once: `func_80058EA0` (the `func_80058788` twin with flags `0x402800`; sets pool
byte `D_80098851` to 0xFF), `func_80054804` (fails, returns 0, while `Moji_work[arg]` has bit 31 set and
bit 17 clear), `func_80054ADC` and `func_80055BB0` (call `D_8008AAC0[unk_7C]`, a handler table splat
split into several labels), `func_80057DF4` (writes the low bytes of `Game_work.unk084[D_800989D4][2..4]`
into its own command's argument bytes; `sltiu`, so the counter is unsigned) and `func_80056778`.
`func_80055BB0` needs the bit-set path written first.
Also banked, matching: `func_800553F0` (`Sce_flag_off` of the 16-bit argument), `func_80055A78` and
`func_8005A598` (pick byte 3 or 4 as a message of `mes_file_44` by `Game_work.stage_no/area_no` equal to bytes
1/2, or `Game_work.unk060` within [byte 1, byte 2]; 0xFF skips; `cmd_top_48 = cmd_ptr_6C = ...`, chained, so
`cmd_ptr_6C` is stored first), `func_80053AA4` (`MojiTaskKill` for one entry `n`; clears Moji_flag bits
`0x403E0000` and `0x08000000 >> n`), `func_80058C28`/`func_80058CC8` (command/text twins: push, then call into
`D_8008BAA4[flag]` if scene flag `flag` is set, else `D_8008CE58`; both `get_le16` calls cast to `uint16`). Pool bytes `D_800987F8`, `D_80098850`,
`D_80098851` are separate commons (`$gp` at an odd address), now tentative in `moji.c`.
Banked, matching at once: `func_80054700` (wait command: loads `timer_4` (`sint16`, `lh`) from the 16-bit
argument once, under flags_0 bit `0x01000000`, sets bit `0x10000000`, counts down, steps 3 at 0; returns 0),
`func_80055438` (the `func_80055A78` twin choosing byte 3 or 4 by `Sce_flag_test` of the 16-bit argument),
`func_8005721C` (`D_80098930 = D_800BE2F8[D_8009899C + unk_71] + arg`; `D_80098B6C = 1` when scene flag
0x2EE is clear and `Money_check(-D_8008FD3C[D_80098930])`, i.e. the money can't cover that price; pool
bytes `D_80098930`/`D_80098B6C` now tentative in `moji.c`).
Parked, then banked: `func_80057B70`/`func_80057BB4` (`Money_add(±D_80098AF4, 0, 0)`, step 1)
and `func_80057924` (`Money_add` of `-(Game_work.unk07D - unk07C) * 10` or of `-money`, then `unk07C =
unk07D` in each branch (the target duplicates the tail), step 2). Only the tail differs: `cmd_ptr_6C` in `$v0`
where the target has `$v1` with `li $v0,1` in the load delay slot. **Cause: the callee's return type.** With
a `void` prototype GCC 2.7 treats `$v0` as free right after the `jal` and loads the pointer into it; with an
`int`-returning callee (`call_value`) it picks `$v1`. So Capcom's `moji.c` called `Money_add` and
`func_80039E18` as `int` functions (undeclared, implicit `int`), although neither returns a value. Both are now
declared `sint32` (no `return`); all four functions match, as do `Money_add`'s other callers. Watch for this
tail pattern (`$v0`/`$v1` swap right after a call to a `void` function) elsewhere.
Banked, matching: `Moji_init` (moji init: `Cd_read_comb(30)` + `Cd_read_sync`, then for each of the 5
entries clears `flags_0`, `cmd_ptr_6C`, `cmd_top_48` and sets `no_6` to its index (`sint16` counter); clears
pool words `D_80098B2C` (bytes OR'd in per entry by `func_80053B40`, read as bytes at `+1`/`+2` elsewhere),
`Moji_flag` and `D_80098960` (frame counter bumped by `func_80053B40`). Only `cmd_ptr_6C` is stored through a
`&Moji_work[i]` pointer; the other fields by index), `MojiTaskKill` (ORs and clears every entry's `flags_0`,
`mes_no_C2 = 0xFF`, XA stop if bit `0x40000` was set, `Moji_flag = 0`; `MOJI_WORK_MAX` = 5),
`func_80057744` (byte 1 or 2 as message by `Game_work.unk07D == unk07C`, falls back to `D_8008CACC` without
a file; `cmd_ptr_6C = cmd_top_48 = ...`, so `cmd_top_48` is stored first; clears `unk_3E`, `unk_3C`,
`unk_72`), `func_800557B8` (`func_80054700`'s wait, also ending once bit `0x40000` (XA) clears; clears bits
`0x11000000`), and the twins `func_8005958C`/`func_80059660` (push, then call into `D_8008CBA4[id - 1]` with
`id = Player_work[0].rb_parts_sort_data[arg2 + D_8009899C]` if `arg1`, else `rb_parts_equip_data[arg2]` after setting the code's
byte -1 to 0 (or 3 when `Moji_flag & 0x20000` and the next byte equals `unk_71`). The id bytes load with
`lb`: cast to `sint8`, since typing the fields `sint8` breaks `Sce_flag_off`).
Banked, this round: `func_800548C4` (XA wait command: first pass sets bit `0x01000000` and starts
`Cd_xa_play_id(get_le32(arg))`; then once `func_8001D878()` (`Cd_stat & 0x20`) is set, `timer_4 = 5`,
`Moji_flag |= 0x100000`, flags `|= 0x40000` and `&= ~0x01000000` in one expression, step 5; always sets
`0x10000000`, returns 0), `func_800545C8` (the `func_80054700` wait, but at 0 it also sets `timer_4 = 5`,
clears `unk_71..73`, sets `cmd_top_48` to the stepped `cmd_ptr_6C`, `unk_3C = unk_3E`, `Moji_flag |=
0x200000`), `func_80057C2C` (lists the set bits of `Sce_flag[0x63]` (flags 0x318-0x31F) into
`D_800BE2F8`, terminated by 8, then takes `cmd_ptr_6C[count]` as message; 0xFF steps 9. Needs a local
`flag = &Sce_flag[0x63]` assigned first: with `Sce_flag[0x63]` written inline the hoisted address moves
after the counter inits), `func_80058DEC` (text twin over 64 flags from `Sce_flag[0xA8]` (0x540-0x57F),
count in pool word `D_800989A8`, now tentative in `moji.c`; rest of `D_800BE2F8[0..0x7F]` set to 0xFF),
`func_8005861C` (push, then message byte 2, 3 or 4 of the command by `D_8008D8EC[D_800989D4][n]`: `[0]`
zero, `[Player_work[0].rec[r].idx[n]]` zero (r = 0, or `D_800989D4 + 1`), or neither; clears/sets `Moji_flag`
bit `0x20000`). `six_digit_set` (six digits of `n` by `D_8008AF24` (100000..1), leading zeros as
`D_8008AF3C[pad]` until a nonzero digit (flag in `.sbss` `D_800986F0[0]`), terminator `D_8008D028[0]` at
[6]) matched once `D_8008AF24` was declared `[]` instead of `[6]`: a sized 24-byte extern counts as small
data under `-G32`, and GCC then rebuilt the loop end as `lui/addiu %lo(D_8008AF24+0x18)` instead of
`addiu t3,t0,0x18` from the table register. Worth trying on other loops over small extern tables.
Banked, matching: the `six_digit_set` text codes `func_80057BFC` (`D_80098AF4`), `func_80057144`
(`money_40 = Game_work.money`, then prints it; the target reloads `money_40`) and `func_800579D8`
(`(Game_work.unk07D - unk07C) * 10`), each writing at `++mes_ptr_14`; `func_800554E4` (scroll command:
like `func_80054700`'s wait, but also `unk_3B++` on the first pass; each frame after the countdown
`scroll_38 -= unk_3A` until `timer_4 * unk_3A < -(unk_3B * 12)`, then `scroll_38 += unk_3B * 12`, clears
`unk_71..73`/`unk_3B`/bit `0x01000000`, `cmd_top_48 = cmd_ptr_6C += 3`, `unk_3C = unk_3E`; `unk_3B` is
`sint8`, `lb`); `func_8005AB78` (window state in `unk_7D`: 0 sets flags `0x06000000`, margins
`unk_B4 = unk_B6 = arg`, `Moji_flag |= 0x200000` and the four `corner_88` points from the margins and
`unk_7E`/`unk_7F` * 12; 2 sets `0x10000000` and clears `0x06000000`; void, in a data table).
Banked `func_80059D20` (prints `D_8008AF00[i] - Game_work.unk028[i]` for `i = D_800BE2F8[arg] < 4`,
else `unk062[9 - i] * D_8008AF00[i] - unk028[9 - i]`, at `cmd + 7`, then calls into `D_8008CE5C[i]`).
The else branch needs pointer-minus-index, `*(&Game_work.unk028[9] - i)`: `[9 - i]` adds the 9
separately, and `(&arr[9])[-i]` negates before scaling, so the `i * 4` computed for `D_8008AF00[i]`
isn't reused. Also `uint8 i` and the command pointer in a local `p`.

`moji.c`, from CoastRedWood's drafts: banked `func_800553A8` (`Sce_flag_on` of the 16-bit argument,
step 3), `func_800572C8` (buy item `D_80098930`: with scene flag 0x2EE, refund a quarter of its price
and clear its flag; else pay `D_8008FD3C[item]`, item 0x23 raises `life_max` by 0x10 and refills life,
0x24 sets `Game_work.unk07C/7D` to 3, 0x25 increments 7D into 7C (through a pointer: `lui`/`addiu`
then offset 0), then sets its flag), `func_80059728` (buster parts menu: copies equipped part
`Moji_work[1].sel_71` and owned part `Moji_work[2].sel_save_79` into `Moji_flag3`; TRIANGLE/START
leave with message byte 3/4, CROSS with byte 1/2), `func_80055CFC` (text: on/off switch choice
for the byte variable `*D_8008D0D4[arg 3]`; the target reloads and stores `unk_78` where the
`func_80054BEC` twin adds 0x30, kept as `+= 0`), `func_80056D10` (shop list: fills `D_800BE2F8`
with the items of list `D_80098850` whose scene flags are set (and the "seen" flag 0x80 below is
clear), then jumps by the count), `func_80058F18` (scrolling list choice: like `func_800587F8`,
UP/DOWN at the end scroll `D_8009899C` by 2 and set the entry's `Moji_flag3` bit), `func_80054E54`
(menu command: restores `sel_71` from `sel_save_79/7A/7B` by flag bits 0x40/0x20/0x10 of byte 1;
CROSS picks, TRIANGLE (flag 0x8000) or START in `Game_work.routine_0 == 4` cancel to the last
choice; code 0xEA's choices 1-4 run the sub screen sorts), `func_8005ACA8` (window draw: four
`POLY_G4` border shades, the two `POLY_F4` backgrounds, `DR_MODE`s from `Map_prim_ptr`; colour row
`D_8008AF18[unk_7C]`) and `func_80057FF8` (name entry: `chr_86` cycles through `D_8008D0AC`, the
name's three-byte codes sit just before the command (`NAME_SLOT`), copied into
`Game_work.records_84.h[D_800989D4][2..]`). New pool tentatives: `D_800988F4`.
Parked `func_80057A24` (`NON_MATCHING`; push, `Sce_flag_on(D_80098830 | 0x500)`, then call into
`D_8008CBA4[D_80098830]`): the `Money_add` tail pattern, so the target called `Sce_flag_on` as an
`int` function. Declaring it `sint32` in `scene.h` matches this function but breaks `Sce_flag_on`
itself (`scene.c`: with an `int` return `$v0` is live at the exit, so a branch delay slot that the
target fills with a `$v0` computation stays a `nop`, 4 bytes more). Needs a decision on how moji
sees the prototype. (`func_800553A8` and `func_800572C8` also call it and match as `void`.)
Banked `func_8005BC90` (window kind 0 or 4 by `D_80098912`, draws with `func_8005ACA8`, then kind 7)
and `func_80059E74` (number entry, `func_80057FF8`'s twin for digits `D_8008D028`: the number in
`D_800987E0` is capped by `Game_work.money`, or `D_80098AF4` when `Money_check(-D_80098AF4)` fails, and
written back with `six_digit_set`). New pool tentative: `D_800987E0`.
Parked `func_80053B40` (`NON_MATCHING`; the per-frame message runner and text renderer): only the
pad copy differs. The target loads `PAD_ON(Joy1)` after storing `btn_held_B8`; with `PAD_NOW`'s cast
load (not `MEM_IN_STRUCT_P`) the scheduler hoists it above the store. A scratch build with `now`
and `on` as `uint16` members of a struct over `Joy1` matched the whole binary, so ROCK_NEO's
`PAD_WORK` probably had `uint16` button fields (as in CoastRedWood's fork); retyping it changes the
shared `PAD_*` accessors, so it waits for the owner.

`code_80027678.c`: banked `work_48_draw` / `work_50_draw` (draw every slot of `D_800A3B40` /
`D_800BF118` whose `routine_0` and `flags` both have bit 1 (`WORK_DRAW`), through
`D_800898D0[(routine_0 >> 2) & 7](&wp->efc, (sint8)routine_0)`; so `WORK_50` has an `EFC` at 0x14;
called by `Obj_draw_all` with `shl_work_draw` for `D_800BFB20`), `func_8002CFA4` (clears the map
block masks at `0x8015BC00`, the billboard count and some scratchpad state; fog bytes to 0xE00),
the model-data accessors the overlays use on `MODEL_WORK.data_88` (a `PARTS_MODEL`; packed id
`lod << 24 | list << 16 | mesh << 8 | n`, mesh n being entry n + 1 of the level): `Model_face_get`,
`Model_face_uv_set`, `Model_vertex_get`, `Model_mesh_uv_copy` (copy a mesh's face uvs from another
mesh plus a uv offset: face/lip animation) and `Model_uv_cell` (uv offset word of a grid cell), and
`Billboard_get` / `Billboard_line_get` (take 0x28 / 0x20 bytes from `Map_prim_ptr` and list them in
`D_800BE6D8`, at most 0x100). `Model_mesh_uv_copy` matches only with the entries addressed in
integers (`(MESH *)(n * sizeof(MESH) + (uint32)lod[0])`) and the header word read once.

`code_80027678.c`, second round (from CoastRedWood's drafts): banked `shl_work_draw` (the shot pools'
draw loop, like `work_48_draw`), `func_80027F78` (before a player is drawn into its own 512-entry OT
`D_8009BF88` / `D_8009AE48`: projects joint 0, sets `Scratch_rgbc` (dimmed and blinking while either
countdown `func_8005EBC4` / `func_8005EBD4` runs), depth-cues it, sets the fog CLUT bits, and links the
player OT into `D_800A4D40` two depths per entry; `D_80098550` = depth - 0x100 is the player OT's base),
`prim_mesh_tri_draw` / `prim_mesh_quad_draw` (draw a `PRIM_MESH`: faces of pre-built POLY_FT3 / POLY_FT4, one per
display buffer, into that player OT), `prim_mesh_uv_copy` (resets a `PRIM_MESH`'s face uvs from the copy of
the face tables that follows them, plus a uv offset; `func_8002D004` calls it on two fixed meshes at
`0x800F7820` / `0x800F7830`), `shadow_draw` (shadow quad), and the `MESH` drawers `func_8002AEE4`
(Gouraud, corner colours from a table), `func_8002A6E8` (textured, depth-cued; flag 0x40 no culling,
8 no depth cue) and `func_80029608` (the live twin of the dead `mesh_draw`, with mtc2 screen-XY loads).
Findings: `MESH_FACE.idx` is read as bytes (now a `MESH_IDX` union); the vertex copies to
`Scratch_vtx` are `SVECTOR` struct copies (GCC emits `lwl`/`lwr` for their 2-byte alignment); the
countdown getters return `int` (no caller sign-extends). `prim_mesh_tri_draw` / `prim_mesh_quad_draw` reuse the
mesh argument as the primitive cursor. In `prim_mesh_quad_draw` the GTE nops must be statements of their own
(`gte_nop(); gte_nop(); gte_rtpt_b();`): with the one-statement macros the loop is short enough for
loop.c to hoist `0xFFF8FFFF`, which the target doesn't (its threshold weighs savings against the loop's
insn count). Parked `func_800289A0` (`func_80029608` plus a check that the depth is within the first
0x800 entries of `Scratch_ot`): only `m` (t3) and `f` (t2) are swapped (`func_80029608` has them the
other way round); splitting the nops in any loop doesn't change it. Its frame has 16 unused bytes
above `opz`/`otz`, which only a block-local array (declared after their first `&`) reproduces.

`code_80027678.c`, third round (from CoastRedWood's drafts): banked the `EFC` draw functions of
`D_800898D0` (indexed by `routine_0` bits 2-4): `Efc_sprite_draw` (0 and 2: sprite EFC as a
camera-facing POLY_FT4, rolled by `angle` with flag 0x20; `EFC_SPRITE` now has `u`/`v` (read as one
halfword), `size`, `angle` and a signed `pos`), `Efc_model_draw` (1 and 3: model EFC through
`func_8002A6E8`, matrix and position scaled by `Scratch_scale_shift`; flag 0x80 another fog CLUT row)
and `Efc_model_g_draw` (4: model EFC Gouraud-shaded through `func_8002AEE4`, its colour table being the
word right after the `EFC` in the object). Also `pl_body_draw` (draws a player's 5 body parts of
`PRIM_MESH`es, `D_800898EC` / `D_80089928` / `D_80089938` by body variant), `Model_parts_draw` (a
`WORK_3C0` / `WORK_5A4` model part by part through `func_80029608`, RGB555 colours; `CHILD_SLOT`
fields `mesh_0`, `hide_3`), `mesh_gt_vtx_rgb_draw` / `mesh_gt_face_rgb_draw` (MESH as POLY_GT3 / POLY_GT4, colours
per vertex / per corner scaled by an rgb, `RGB_SCALE`; neither tests the winding it computes),
`shadow_draw_all` (draws and empties the shadow queue `Shadow_tbl`, `SHADOW[64]`, filled by
`Pos_Shadow_Trans` / `Model_Shadow_Trans`), `func_8002D004` and `billboard_queue_draw` (billboards like
`billboard_draw`, with an identity matrix built at `0x1F800100`, plus the lines of
`Billboard_line_get`). Findings: in `billboard_queue_draw` the line must be walked as `uint32` words (with a
struct, GCC's alias rules let the scheduler reorder the copies of its ends), and the first GTE
commands need split nops (else loop.c hoists `0x09000000`); `mesh_gt_face_rgb_draw` and `mesh_gt_vtx_rgb_draw`
need their face indices in locals before the vertex copies, and the scaled colour assigned back into
the `rgb` parameter.

`code_8002D9A0.c`: banked `func_8002DC84` (overlay accessor: returns a 16-byte `BLK_ENT` from block
`src->blk_tbl[blk]`, entry `idx` after the header; needs one reused `uint32 *p` and one reused word
local) and `billboard_draw` (projects the `BILLBOARD`s queued by `Billboard_get` in `D_800BE6D8`, links
them as POLY_FT4 into `Scratch_ot[z / 8]`, depth cue and fog CLUT unless flag 8; the list entry is
re-read through `D_800BE6D8[i]` for the flag and `rgbc`, and the three `vz` stores are one chained
assignment). Neither function has a caller in the code or data (dead, or reached some other way).
Parked `mesh_draw` (`NON_MATCHING`; draws a textured `MESH`: RTPT three vertices at a time into
scratchpad sxy/sz arrays, then back-face-culled POLY_FT3/FT4 from its triangle and quad lists). The
target reaches every scratchpad item off one register holding `0x1F800100` (prim pointer at -0x90, OT at
-0xC4, sz array as a hoisted base +0x200). GCC only does that when the source derives them from one
pointer: integer-constant addresses each get their own `lui` (tested), and a scratchpad struct at
`0x1F800000` gives that base instead. The best attempt (the `SXY_*` macros off a local `sxy`) has the
right size. Still different: the sz base is folded into the `lhu` offsets instead of held in its own
register (t6); the target hoists `0x07000000`, `0xFFFFFF` and the OT address into s0/s2/s4 (5 saved
registers, frame 0x38, `otz` at sp+0x14); loop 1 walks copies of the sxy/sz bases; and the face pointer
is a plain `f` with offsets 0/2/4/8 where ours strength-reduces it to `&f->uv[2]`.
Parked `parts_model_draw` (`NON_MATCHING`; draws a `PARTS_WORK`, the 0x560-byte objects `parts_model_draw_all`
walks from `D_800C3580` (4) and `D_8009F108` (16): projects `pos` (culls by depth and screen
bounds), picks a level of detail of `model_80` by z (> 0x708, > 0x2BC), depth-cues the RGB555
colour `col_55E`, then per visible part `gte_MulMatrix0`s the view matrix by `part_mtx[i]`, adds the
rotated `part_pos[i]` to the view translation and calls `mesh_draw`). Everything matches except
the fog CLUT lookup in `D_800C0DC0`: the target builds the address with `lui`/`ori` in `$at`, then
`addu $at,$at,v0` and `lbu 0($at)`, the only such sequence in ROCK_NEO. maspsx gives a constant base
`lui`, `addu $at,v0,$at`, `lbu %lo($at)` (one instruction shorter) and a symbol `%hi`/`%lo`; neither
fits, so matching needs a toolchain change (an ASPSX expansion maspsx doesn't model). Found on the way:
the 0x560 stride conflicts with `WORK_5A4 D_800C3580[]` and `WORK_3C0 D_8009F108[]` (settled: dead
code, see below); the per-part
colour needs a `sint32` local (`lh`, not `lhu`); the `mesh_draw` argument is an integer sum with the
offset first (`addu a0,a0,v0`); `gte_lddp` is passed `&Scratch_dp`, the address, not the value.
Parked `parts_model_draw_all` (`NON_MATCHING`; draws, last to first, the `PARTS_WORK`s with bit 1 of
`flags` set in `Parts_work_tbl0` (0x800C3580, 4) and `Parts_work_tbl1` (0x8009F108, 16), both by
constant address (`lui`/`ori`)). The C (`i = n; while (i != 0) { i--; ... tbl[i] ... }`) gives every
instruction but the two counter loads: the target has `ori $s1,$zero,4` / `ori $s1,$zero,0x10`, where
ASPSX 2.56 gives `addiu`. In all of ROCK_NEO only this function and `parts_model_draw` (`ori $v0,$zero,
0x30`, plus its odd `$at` expansion) use `ori` for a small `li`: these two (0x8002DE5C-) were likely
assembled with another ASPSX version (maspsx's default, pre-2.56, gives `ori`), i.e. a separate
object with its own assembler setting. Matching needs a per-file toolchain change (owner's call).
**`parts_model_draw_all`, `parts_model_draw` and `mesh_draw` are dead code.** Nothing calls
`parts_model_draw_all`: no `jal`, no data table, no stage overlay (`tools/callers.py`), and it is
`parts_model_draw`'s only caller, which is `mesh_draw`'s only caller. Its arrays are not the live
pools: `D_800C3580` and `D_8009F108` hold `WORK_5A4[4]` and `WORK_3C0[16]` (cleared as 0x168C and
0x3BFC bytes and allocated by `func_80031498`/`func_80031418` at those sizes), while the 0x560 stride
would put the 16th entry's end at 0x800A4708, over `Cd_cmd_queue` (0x800A3A40). So `PARTS_WORK` is
the layout of an older build, not a view of `WORK_5A4`/`WORK_3C0`; the stale object would also
explain the two functions' `ori` encodings.
Banked by `tools/twins.py` (since retired; byte-identical to a matched function; C copied, build-checked):
`func_8004E488` (same code as `func_80054BAC`: `return 0;`), `func_8005B85C` (same code as
`func_8005AB78`), and after the twins run below `func_800181D4`, `func_8005B98C`, `func_80066714`.
Named `func_8001D888` -> `Sce_read_sync`: waits a frame at a time (`Thread_wait(1)`) until
`Cd_read_sync2()` reports the CD queue empty. Same purpose as `Cd_read_sync`, different code (it calls
`Cd_read_sync2` instead of comparing the queue pointers); its caller is in `code_800133D8`
(`func_80013420`), which loads `a0 = 1` in the call's delay slot, so Capcom's version probably took an
argument it never used. `func_80013420` is banked calling `Sce_read_sync(1)`; `scene.h` declares
`void Sce_read_sync();` (no parameter list) so the call compiles against the `(void)` definition.

game.c from CoastRedWood's drafts: `game_timer_count` (`Game_work.timer_0c`, capped at
`GAME_TIMER_MAX`, 50 hours of frames), `func_80016434`, `func_80016D64`, `func_80016DAC`,
`player_entry_set` (the player from the area entry `D_800C3558`, `AREA_ENTRY`), and the pool updates
`func_80016FD4` (WORK_3C0), `func_80017094` (WORK_5A4), `func_80017154` (PL_SHL_WORK),
`eve_work_exec` (EVE_WORK), `func_80017528` (WORK_50). The pools' handler tables sit on the
scratchpad at `0x1F800058`-`0x1F80006C` (`Work_3C0_tbl` ..., code_8002E7A8.h; `0x1F800060`/`0x64`
are used by func_80017210/func_800172F4). The loops read `routine_0` signed (`lb`), so they cast.
`func_80017154` calls `D_80089820[id_2]`, a table of scene functions that take nothing
(`func_8001F9AC`, `func_8001F820`): an odd pairing, but it is what the bytes say.
EVE_WORK, WORK_50, WORK_5A4: `field_2` split into `id_2`/`type_3` (the allocators store both at
once with `*(uint16 *)&wp->id_2`; `func_800317AC` still matches).

Twins run (one of each all-assembly twin group, then `twins.py --apply`):
- `func_80013F60` (`code_800133D8`; `routine_1++` of `D_80098AA8` unless `D_80098A72`) and its
  game.c copies `func_80016D0C`/`func_80016D38`, the same bytes on `Game_work` (`GAME_WORK.routine_0`/`_1`,
  `Game_main` runs `Game_main_tbl[routine_0]` on it). Written by hand, since the types differ.
- `func_800666D8` (`code_8006430C`; runs `D_8008FD20[routine_1]` of its module state `D_80098910`,
  `CODE_8006430C_WORK`); routines 1 and 2 of `D_8008FD10` are the same code.
- `func_800180D4` (`code_8001786C`, `D_800821BC[0]`): once `Dbl_buff_idx` is 1, zeroes both buffers'
  vertical offsets, clip y and the isbg/dfe flags, `MojiTaskKill`, sets three pool words, calls
  `func_800196A0`. `Dbl_buff_idx`/`Vsync_wait` added to ROCK_NEO's `scratch.h` (the shim's names).
- `code_8001786C` drafts banked (all matched as adapted): `clut_buf_dirty_copy` (0x8001786C, no callers),
  `Clut_buf_load` (0x800178FC), `Clut_buf_stp_set` (0x80017944), `func_80017994`, `func_80017B24`,
  `func_80017E94`, `func_80018050` (thread body: `D_800821BC[D_800821E0[routine_1][routine_2]]()`
  then `Thread_wait(1)`, forever), `func_800182D4`/`func_8001840C` (`D_800821BC[1]`/`[8]`),
  `func_800196A0`. `Clut_buf` (0x800AD168) holds both copies: `clut_buf_dirty_copy` reaches the
  second (0x800B1168) through Clut_buf's own `lui`, and `Clut_buf_stp_set` matches as a plain
  `Clut_buf[i]` loop with `i` from 0x2000 to 0x3FFF, so `vram.h` declares it `[2 * 32 * 256]`
  (`CLUT_BUF_COPY` is the second copy's index); the registry's `size:0x4000` is the first copy only.
- The screen fade, `code_8001786C`: `Fade_work` (pool, 0x80098A68, `FADE_WORK`, 16 bytes; the
  single labels 0x80098A69..0x80098A76 were its fields). `Fade_start` (0x80017C30) sets it up and opens
  thread 2 (`func_80017E94`, `D_80082140[routine_0]`): `Fade_main` (0x80017ED0) for black (routine_0 0,
  subtractive tile) and white (1, additive) fades, `func_80018050` for wipes (2), whose steps include
  `Wipe_zoom` (0x80018534: the screen as ten `D_80098E70` quads, corners `D_80082194`, zoomed and,
  except routine_3 1, spun by `func_80019760`), `Wipe_spot` (0x80018850), `Wipe_iris` (0x80018BB8), `Wipe_bands` (0x80019210), `Wipe_dim` (0x800194C4).
  `busy` (+0xA) 1 = fade in, -1 = fade out or wipe; it is still `D_80098A72` (game.h) in the other files and
  overlays, so the registry entry has no `size:` (a size would swallow that label). Also banked from drafts:
  `func_800179FC` (darkens two CLUT half rows of `D_8008F168` by `Game_work.unk060`), `func_80019760`
  (rotates `D_8008214C`'s 18 points into `D_80099190`).
- `func_8005A874` (moji window kind 0): opens a window from a flat line `unk_85` (8) pixels a frame, then
  closes it. New `MOJI_WORK.unk_80`/`unk_85`; `unk_A` is `sint16` (`lh`). Matching needed `unk_7D++` at the
  end of state 1's block and `c[0][1] > c[2][1]` (not `<` swapped) in state 2.
- `map_blocks_draw` and its twin `map_blocks_draw2` (matched, from CoastRedWood's drafts): draw the map
  blocks (`Map_blocks`, `MAP_BLOCK`) whose bits are set in a row mask, LOD by depth, through
  `Map_block_draw_tbl[kind][bit 31]`, with the position copied to `Quad_work.pos_40` for the GTE.
  The prologue's order (0x1F800100 in s3 before `rows` in s4) needed a `QUAD_WORK *qw` local set
  first and a local copy of `rows`; the inner loop is a `do`/`while` (a `for` adds an entry test).
  Also needed: the first row's `&= 0x7FFFFFFF` before the loop, `row_end` set inside the `if`, the
  position copied as two words (a struct copy gives `lwl`/`lwr`), the table indexed inline, and the
  drawn word read back into the `lod` local.
- `map_block_masks_draw` (0x80023C08): draws both row masks (`Map_block_mask`, 0x8015BC00 and
  +`MAP_BLOCK_ROWS` words) with `map_blocks_draw` (kinds 0/1, 1/1) or `map_blocks_draw2` (2/2, 3/3) by
  scratch byte `D_1F800075`; mode 0 sets `D_1F800004 = 0x400`, the others 0.
- `func_8001F828` ... `func_8001FDE4` (code_8001F828, called through the `.data` table at 70EC4): each
  stores per-scenario ids (`Game_work.sce_no`, some also `Sce_flag_test`) into this file's `.sbss` id
  slots; the ids' meaning is still unknown, so they keep their splat names.
- Map block quad draws (banked from drafts): `func_80023EA8` and its byte-identical twin
  `func_80026B04`, and the variants `func_80024F30` (no on-screen test; near centre faces OR in
  `D_1F80007C`; flag bit 24 starts a chain) and `func_80025900` (keeps back faces). They reach
  `Quad_work` through one base register, but the flag store (`Quad_face_flags`), the fog table
  (`Quad_fog_tbl`) and the on-screen tests (`Quad_sxy`) by literal address, as the target does.
- `Map_block_draw_tbl` entries (banked from drafts): `func_80023CF0`/`func_80023E1C` (with
  `func_80023EA8`), `func_80024D4C`/`func_80024E94` (`func_80024F30`, copy every CLUT word),
  `func_80025748`/`func_80025874` (`func_80025900`), `func_8002694C`/`func_80026A78`
  (`func_80026B04`). The first of each pair draws two of parts 0-3 by the camera's side of the
  block, part 4, and part 5 up to `Quad_work.part_z_BC`; the second draws every part. The CLUT
  copies must store through `Quad_work.clut_tbl_C8` (a struct field): through the
  `Quad_clut_tbl` pointer macro, GCC 2.7 hoists all three loads above the stores.
- `map_cell_draw` (0x80021834): a map cell in view (`Scratch_fog_1` deep, width by depth plus the
  cell's radius in `SVECTOR.pad`) is drawn by `map_tile_draw` (id < 0) or marked in
  `Map_block_mask` (far) / `+MAP_BLOCK_ROWS` (nearer than `D_1F800004`). `map_tile_queue_draw`
  (0x800221E0) draws the tiles `map_tile_draw` queued in `D_800BBE50`, with `tile_model_draw_split`.
- Banked from drafts: `map_window_draw` (0x80020A4C: every cell of the map window, `Map_org_x`..`Map_end_x`
  by `Map_org_y`..`Map_end_y`, through `map_cell_draw`; then `func_8001782C`, hand-written, drops the far
  mask's blocks from the near mask, and `map_tile_queue_draw`), `map_view_rows_draw` (0x80021548) and
  `map_view_cols_draw` (0x80021258): `map_view_draw`'s scans between the view's two edges
  (`Map_view`, 0x1F800100), skipping its own rectangle. `func_80023728`: camera (`func_80037FB4`), the
  player's view-space position into `Quad_pl_view` (0x1F8001B8, so its z is `Quad_near_z`), fog table and
  split lists into `Quad_work`, then SUPPORT's block model `D_801F6080`; still unnamed (several jobs).
- `Print` (0x8001FE38): Capcom's name (`Print(XYC(x, y, c), fmt, ...)` in disc/tcrf.txt).
  `map_tile_draw` (0x8002196C), `tile_model_draw_split` (0x8002235C), `Room_model_update`
  (0x80023144: moves the room models, draws their SPRT layers) banked from drafts too.
- code_8001F828 drafts banked (all matched as adapted): `func_8001F9AC` (id slot `D_800981E0[1]`, like
  its neighbours), `Room_model_init` (0x80022FD4: fills `D_800BBA90`, `ROOM_MODEL[11]`, from eleven
  model headers; the overlays' `STAGE_MODEL`), `room_model_pos_wrap` (0x8002366C), `num_format`
  (0x800207F8, `FMT_*` flags, digits `Num_digit_tbl`), `Debug_text_draw` (0x800203A8: draws and empties
  `Debug_text_buf` up to `Debug_text_ptr` in the 8x8 font, `SPRT_8`; controller 2 SELECT + up/down steps
  `D_800987DC`), `func_800272D0` (ring of POLY_FT4s textured from the frame buffer),
  `tile_model_draw` (0x80021B14) and the quad splitters `tile_quad_split` (0x80022A94, scratch layout
  `TILE_WORK` at 0x1F800130), `quad_split`/`quad_split2` (0x8002466C/0x8002626C, `QUAD_WORK` at
  0x1F800100). `quad_split` only matches with its corners read through the literal pointer `Quad_vtx`
  (0x1F800198): the target keeps that address in a register for the later store to `uv_88.b[16]`, the
  same byte. The Room_model_init stores of the first halfword cover `flags_0` and `flags_1` at once.
