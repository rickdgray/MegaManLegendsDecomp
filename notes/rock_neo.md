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
`symbol_addrs_rock_neo.exe.txt`. **Audited (2026-11-15):** of the ~400 names imported from him, the
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
- **Parked:**
  - `Cd_xa_play_id`, `Cd_xa_seek_id`: the target extracts the group and file fields, then scales
    each separately (`srl 28; andi 3; sll 2`, `sll 4; srl 20; sll 2`); GCC's combiner folds both.
    Ruled out: bit-fields, a union over the id, `uint16`/`uint8` locals, and the flags
    `-fno-expensive-optimizations`, `-fno-strength-reduce`, `-fno-rerun-cse-after-loop`,
    `-fno-cse-follow-jumps`. `Cd_xa_play_id` also has a store-order difference after that.
    Permuter queue. Note: the parked `Cd_xa_seek_id` attempt uses `CD_XA_GROUP` (masked `& 3`),
    but the target shifts the group without a mask (`srl 28; sll 2`); use `id >> 28` there.
  - `cd_cmd_read_comb` (banked): `tiles` keeps `col`/`row` at the same offsets as `tim`
    (`pad[6]`); type 10 computes the height before the width; the CLUT row must be the
    `CLUT_BUF_ROW` macro (it re-reads `head->arg[1]` at each use).

`sound` (`src/rock_neo.exe/sound.c`), parked: `Sound_call2` (8-register difference only): the
target keeps the queue pointer in `v0` and the loaded `args[0]` in `v1`, and stores `args[1]`
before the pointer increment (`nop; sw v1,8(v0)`); ours puts the pointer in `v1` and hoists the
`arg2` store to after the global store. Tried: local pointer, `args++`, `&p[1]`, `+= 1`.

`sound`, more parked (banked this round: `pitch_scale`, `fade_step`):
- `Sound_stage_play`: body is right except that the target reloads `Game_work+0x50`/`+0x51` with a
  fresh `lui` each (we keep the base in `s0`, +1 saved reg), and keeps the `id != 0xFFFF` test as
  a value in `v0` (ours: `a1`). Since `Sound_call` takes `uint16 id`, `uint16 id` matches the
  whole `lhu`/`xori 0xFFFF`/call sequence (and makes `id != 0xFFFF` meaningful); only the
  `Game_work+0x50` base kept in `s0` remains. Tried: local func pointer, `ok` flag, `&&` form,
  `sint32` id.
- `Sound_update`: target hoists both table bases (`Sound_call_info_tbl`, `Sound_call_func_tbl`) into `s2`/`s1`
  after the loop pre-test; ours hoists only `Sound_call_func_tbl` and folds `Sound_call_info_tbl` as `lui at`.
  Tried: sized array, local `uint8 (*)[4]`, `SOUND_CALL_INFO` struct (the current attempt).
- `pitch_interp`: target copies `a` (`pitch_scale(x)`) into `s2` right after call 1, keeping `x`
  live in `s0`; ours sinks the copy and reuses `s0`. Signed `/ 128` is right.
- `Sound_seq_stop_all`: banked in the consolidation pass (see `volume_update` below).

`sound`, this round: banked `key_on_tone` (key on one tone: `SpuSetKeyOnWithAttr`), `Sound_stage_slot_set`
(per-stage sound id slots by Sce flags), `voice_check` (voice priority / distance check against
the player). `key_on_tone`'s first parameter is `uint16` (the caller zero-extends). Parked:
- `Sound_stage_check`: same shape as `Sound_stage_play` but with `D_800C356E/F` as the "old" stage. Body
  is right; target keeps `list` in `a0`, `changed` in `a1`, the table base in `v1` (ours `v1`,
  `a0`, `a1`) and loads `Game_work+0x50`, then (after the `addu`) `+0x51`. Tried: declaration
  orders, local for the inner list (hoists the loads: worse), operand order of `!=`, if/else flip.
- `Sound_call_play`: loop is right (`uint16 voice` even reproduces the `andi 0xff`). Target
  computes `bank * VAB_HEAD_SIZE` first and adds it last to `&base[idx]` (`a2 = 0x8014B820`);
  ours folds it into the base. Tried: `VAB_HEAD` struct indexing, local `vab`, two-step pointer,
  `uint32` cast with an `off` local; target also assigns `info`=s2, `tone`=s1, `voice`=s3.
- `Sound_init`: all stores right, but the scheduler order differs: target emits `li v1,0x7f`
  before the first store and `li v0,0xf` before the `Sound_fade_flags` store, with the `Sound_fade_flags` /
  `D_80098958` stores ahead of the `0x7F` stores; ours hoists the `0x7F` stores above them and
  loads `0xf` late. Source order of the stores makes no difference; a `vol` local is folded away.
  Also tried (consolidation pass): one chained assignment for the six `0x7F` stores (right order,
  same hoisting).

`main` (`src/rock_neo.exe/main.c`), this round: banked `Disp_env_setup` (display buffers at `0x800C0C48`,
`extern DISP_ENV Disp_env[2]`: the extern symbol is needed, an absolute-address cast loses the shared
base), `Pad_repeat_update`/`func_80012350` (auto-repeat; ROCK_NEO's `PAD_WORK` adds
`rep_state[8]` at +0x38 and `rep_count[8]` at +0x40 to the shim's layout; `mask` is `sint32`), `Thread_open`
(`OpenTh` from the thread record's `sp`/`gp`), `func_800131FC` (thread entry: dispatch through
`D_80080894[D_80098B1C]`, then `Thread_wait(1)`). Parked: `func_80012BC4` (thread table init). The
table base `*(TCB **)0x110` must be written via a `TCB **kp = (TCB **)0x100` local (`kp[4]`) to get
the `li t2,0x100` / `lw 0x10(t2)` split, and `gp` read into a local before the loop. Still different:
target reloads `THREAD_TBL[i].tcb` from memory before storing `->reg[R_SR]` (ours reuses the register), and the
loop counter/giv are scheduled differently. Tried: `uint32` field with a cast, `[0x25]` word index.

Parked: `debug_mem_dump` (`0x80012A5C`, debug dump of 16 eight-byte lines as words/halfwords/bytes
through `func_8001FE38`). **The code is byte-identical** (`uint32 mode`: the switch has no lower-bound
test; addresses as `addr[i * 8 + k]`, since a walking `addr += 8` grows a second pointer giv). Only
the rodata order differs: its 45-byte format string `D_80010040` comes out of `main.o` ahead of
`D_80010000`, which `exception_handler`'s `INCLUDE_ASM` still supplies (`.rodata` 0x800-0x870 = 0x40 +
0x30). A named `const char D_80010040[]` placed after that stub lands first too. Bank it with
`exception_handler`, or once `D_80010000` is defined in C.

Parked: `exception_handler` (`0x8001246C`, the exception handler that `func_80012938` installs with
`OpenEvent`; never returns). It copies the current TCB (`TCB_CURRENT`, the `TCBH` entry that 0x108 points to),
then each frame prints the exception name (`names[(cause >> 2) & 0xF]`, the initialized local whose
copy is `D_80010000`), the break code (`*(u32 *)epc >> 6`: 0x1C00 = break 7, divide by zero; 0x1800
= break 6, overflow), the labels `D_80080730[37]` and the registers. Select on controller 2 cycles
`mode` (0 = registers, 1-3 = `debug_mem_dump` mode - 1); triangle toggles the dump address between
main RAM and the scratchpad. The NON_MATCHING C is 3 instructions long. Found so far: the label
table base needs a `DEBUG_TEXT *msg` local set before the loop, the break code and the register
column are one local (`n`, in `s1`), and `for (i = 0, n = 0; ...)` gives the target's init order.
Still different: the target keeps `D_800979A4` in `s0` for the last five prints (ours reloads it
with `lui`/`addiu` each time; a `char *fmt` local gets hoisted out of the outer loop instead), and it
schedules the hoisted scratchpad base `lui 0x1F80` ahead of `msg`'s `la`.

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
until `Cell_stack_idx` is 0). Parked: `func_80037594` (target reads `Player_work+0x172` with its own `lui`,
then builds `&Player_work` again; ours folds both into one base), `func_80037818` (target keeps arg in a2,
`li a0,4` in the delay slot, then `move a0,zero` on the fall-through; the address, `&Stage_idx_tbl[arg0].val`,
matches. Also tried `?:` (becomes `sltu`/`sll`) and an if/else with two calls).
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
`3988..` / `3994..`): five slots of a table. `func_8003A218` (parked, `NON_MATCHING`): shortest
distance mod 0x1000 from arg0 to `D_800A3968`; GCC inverts the `a < b` test and swaps the two
branch bodies, `>=`, swapped names and `-=` forms were also tried.

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
`owner->mask_4` temp). Parked `func_80036B40` (`NON_MATCHING`): copies the 0x28-byte block at
`D_800BC7F8` to `D_8009A350` after `SetFarColor`/`SetFogNear`; the copy is right, but the target keeps
`&D_800BC818` in s0 from the start (also the copy end pointer) while ours rebuilds `D_800BC818-0x20`.
Parked `func_80035724` (`NON_MATCHING`; spawns a `SHL_WORK` slot from `PL_WORK`, claims a slot with
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
(scratchpad fog setup, `SetFogNear(D_800BC81C, 0x180)`). Parked `func_80036B00` (`NON_MATCHING`): copies
`D_8009A370..74` into an `SVECTOR`; the target does load/store pair by pair, GCC hoists the later loads
above the earlier stores (struct, `sint16 *`, `*v++` and `volatile` forms tried).
Banked `Angle_diff_clamp` (signed angle difference on a 0x1000 circle, clamped to +-limit; `r = limit`
first, and the else-branch test written `limit > 0x1000 - d`). Parked (`NON_MATCHING`): `func_800323FC`
(steps a `KEY_ENT` table; target loads `lbu 0x101` before `lw 0xFC` and keeps `ctl` in a2 with a copy in a1)
and the four slot allocators `func_80031418`, `Open_SHL_WORK`, `Open_EVE_WORK`, `func_80031734` (pool
bitmask scan; only the store order differs: the target keeps the stores in source order around the mask
update). A scratch test with the mask as a struct member (`MEM_IN_STRUCT_P`, so the store aliases the
`wp->` stores) gave exactly the target order, so the mask words (`D_800987CC/E8/EC`, `D_800989CC`) are
probably members of a pool struct; a scalar `uint32` lets the scheduler hoist the `wp->` stores.

Banked `func_80031324` (initialises a child object from slot n of a parent: copies the 32-byte block at
parent+0x240+n*32, position from parent+0x180+n*8, takes and clears the id at parent+0xF9+n*4; the id
field is `sint8` so the `-1` store is `li -1`) and `func_8003545C` (claims a free bit of `D_80098798`,
24 slots, records it in owner+4 and stores the value in `D_800BE478[slot]`). Parked (`NON_MATCHING`):
`func_80031498` and `func_80031598` (two more pool allocators with the same store-order issue as above),
`func_80031CA4` (clamped angle step toward a target; target keeps the `limit` parameter in s2 and a copy
in s1, GCC merges them) and `func_80030058` (rotates an offset (x, y, z) by an angle into a VECTOR; same
param/copy pair issue for x and z). Also parked (`NON_MATCHING`): `func_80031DCC`, `func_80031E60`,
`func_80031EF0` (two-sector angle test, 1 if within +-half1 of center1 and +-half2 of center2; target
keeps the result in v0 and a copy of the angle in v1, GCC uses a scratch register), `Muku`
(`func_80031CA4` on `Angle_xz_svector`, same s2/s1 issue), `func_8003081C` (GTE view-cone test:
RotMatrixY/RotTrans, returns 0x10 behind, 2 inside; target stores `m[0]` late and shares one `ori 2`
between the x >= 0 / x < 0 paths) and `func_80031F84` (direction quantizer vs a base angle, returns
angle | side << 16; only the prologue order differs).

`code_8002E7A8.c` (batch 5): banked `func_80030CB8` (`func_80030CF0` with arc 0x100), `func_80030EE8`
(velocity (+0x44..0x4A) toward a target at speed `s`: `d * s << 8 / dist`, time = dist / s; the three stores
must be written vx, vy, vz, time) and `func_80033F04` (rotates unit vector `a` toward `b`: two
`OuterProduct12`, a scratchpad-like static matrix, `ApplyMatrix` twice, `VectorNormalS` of the closer result;
`angle` must be `sint32` and the `>> 16` chained `D_800985FC.vz = D_80098604.vz = ...`, else GCC keeps `limit`
in an extra s-register). The `D_8009857C`..`D_80098654` statics are now `MATRIX`/`SVECTOR`/`VECTOR` objects.
`Player_work.pos` is an `SVECTOR` (the 8-byte copy in `func_8003606C` only compiles with the unaligned
`lwl`/`lwr` per-access form from a struct member, not from a cast pointer). Parked (`NON_MATCHING`):
`func_8003606C` (squared xz distance, `<< 2`, of every object in three pools to each of the two players, -1 when
over 0x10000000, stored at +0x80/+0x84; the target keeps `D_8009F108` in t6 across the outer loop, computes the
next-object pointer first (`a3 = a1 + size`) with the counter increment in the branch delay slot; ours moves the
pointer add into the delay slot and the counter to the loop tail; needs an unused 8-byte `SVECTOR` local) and
`func_80033A28` (unpacks 75 twelve-bit values from the 0x20-word block at `0x1F800180` into 25 `SVECTOR`s at
`0x1F800120`; the code is identical, only the register assignment differs: target d=a1, s=a2, counter=t0, ours
d=a3, s=t0, counter=a2). `func_80035508` stays assembly (GTE; needs the repo-wide GTE decision above).

`code_8002E7A8.c` (consolidation): the player and every pool slot share one object header (routine_0,
kind_1, flags at 6, position at 0x14, 16.16 position at 0x1C, angle at 0x56, model data at 0x88/0x90-0xAC,
keyframes at 0xF8-0x106). `Obj_work_flag_change` and `func_8002F420` apply `func_8002F3A8`/`func_8002F884`/
`func_8002F928` to several pools, `func_8002FA38` writes by kind, so `FLAG_WORK`, `MOVE_WORK`, `POS_WORK`,
`ATTACH_WORK`, `TURN_WORK` and `POS14_WORK` stay views until that header has a type. Merged: the keyframe and
joint views into `PL_WORK` (`tbl_F8`..`unk106`, `owner_188`, `base_mtx`, `joint_mtx[15]`, `joint_pos[15]`,
`pos_1C`, `pos_428`, `svec_438`), `OBJ_10C` into `SHL_WORK`, `func_8002F998`'s pointer into `EVE_WORK`.
`func_800323FC` is down to the order of its first two loads (lbu time before lw ent_FC) after reusing the
parameter as the copy of ctl.

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
`func_8002FA38`, `func_80032538`, `func_80033A28`, `func_80035724`, `func_8003606C` (unchanged).

`code_8005C258.c` (small functions): banked `func_8005DCB4` (calls `func_8005DCDC`, `func_8005DE28`),
`func_8005D9EC` (`Player_work+0x6E = +0xB0`, then `func_8005D9C4`), `func_8005D844` (arms slot
`D_800BBE2C`..`E46`), `func_8005D98C`, `func_8005C720` (dispatch through `D_8008D7B4[wp[4]]`).
Parked `func_8005D4F8` (`NON_MATCHING`): the target loads and stores `D_800BBD85` through one `lui`+`addiu`
base register (`$v1`), but GCC folds `&D_800BBD85` into `lui`+`%lo` on each access; a pointer local and
a `volatile` pointer both fold the same way. The store to `D_800BBD81` uses its own `lui`. So `D_800BBD81`, `D_800BBD85`, ... are separate globals,
not fields of one struct (declared in `code_8005C258.h`). `func_8005C720`'s `wp` is the 9-byte object at
`D_800BBD78` (byte +4 indexes `D_8008D7B4`); it stays `uint8 *` until that object's layout is known.

`code_800456D8.c`: banked `func_80045918`/`func_8004594C` (`WORK_48.timer_B` countdown, then `routine_8`
+= 2 / += 1), `func_80045A7C` (`Sound_call2(0xCF, &wp->pos_38)` then `func_80031988`), `func_80047318`
(`D_8008A708[wp->routine_8](wp)`). Parked `func_80045FE4` and `func_80046008` (identical, `NON_MATCHING`):
the target is `func_8002FE74(wp->kind_1)` followed by `move v1,v0`; GCC drops the dead copy for a
`void` function with a local, and a `return` form emits no move either (also tried `register`).
Also banked: `func_80047D9C`/`func_80048354` (`D_8008A724`/`D_8008A76C[wp->routine_8](wp)`), `func_800485E4`
(`D_8008A778[wp->flag_4](wp)`), `func_80048268`, `func_80046848` (`WORK_48.flag_3` picks sound 0x9E/0x9D).
Parked `func_80047C84` (`NON_MATCHING`): copies `D_8008A6C8..CF` into `WORK_48`; the target does the
`field_14` word load/store third, GCC always delays the `lw`/`sw` to the end (v1), whatever the
statement order or the type of `field_14` (`uint32`, `sint16[2]`, cast).
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
local) and `func_8004602C` (per-frame draw of the effect: `D_8008A6A8[routine_8]`, then one `func_8002D464` primitive
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
`field_2C/2E/30`, collide with `func_8004B5CC(&pos, &old, 1, HIT_ENT *)`, halve the vertical speed on a floor hit
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
step function), installed as `Scene_work+0xA4` by `event_scene_init` (from `func_80068DAC`, a `D_80089024`
scene routine called with `&Scene_work`). `Sce_event_update` advances it when `Scene_work.timer_10` reaches the
entry's frame and resets the timer. Entry bytes 0 and 1 are copied to `Scene_work.ev_08`/`ev_09`;
`timer_18` restarts when `ev_08` changes and `timer_1C` when either changes. `Sce_event_set(table, arg)`
(called only from overlays ST15/ST1B/ST1E) installs a table and sets `D_800BC7F0 = arg`; `Sce_event_timer_clear`
(many overlays) clears the timers and both bytes. Banked steps `func_8006885C`, `func_8006888C` (calls stage code
`func_80101D94` at frame 10), `func_800688BC`, `func_800688E4`, `func_80068BC0`, `func_80068CB8`: at frame 0
each sets `field_9` (and clears `field_A`) of one of `Scene_work.obj_24[0..2]`. `obj_24` is `void *[16]`:
`func_8001E968` fills it from four pools by the kind byte of each object entry, and this scene's entries
(`D_8008FF88`, opened by `event_scene_init`) make `[0]` a `WORK_3C0`, `[1]`/`[2]` `WORK_5A4`, `[3]` a `WORK_50`.
The object must be read into a local of that type: the byte stores alias the array.
Entries are typed `EVENT_ENT` (`scene.h`); `event_step_call` (0x80068D64) runs the current entry's function
unless `ev_08` is 0xFF. Also banked: steps `func_80068344`, `func_80068728` (sets `obj_24[3]->field_E` and
`Scene_work.field_64`), `func_80068760`, and `event_scene_init` (the scene's setup: resets the camera
with `func_8001E6C0(0, 0, 0)`, installs camera script `D_8008FFD8` in `Sce_camera_work.arg_C0` (a `uint32 *`
command list stepped by `func_8001EC0C`) and event table `D_8009039C`, opens the four `SCENE_OBJ_ENT`s of
`D_8008FF88` with `func_8001EAE8`, clears `field_64`); `func_800680BC(arg)` resets the bytes/halfwords `D_800C3560`-`D_800C3571`
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
`func_80017C30(2)`; 3 `event_scene_init` and falls through to 4 (ends when `D_80098A72 == 0` and the
event table reached its 0xFF entry or `func_8001DE84` says START skipped, `func_80017C30(10)`) and 5:
the per-frame work (`event_step_call`, `screen_tile_draw(field_68, 6C, 70, 74)` while `field_64`, the
camera, `Sce_event_update`, the empty `func_80068DA4` at `timer_14 == 0x4680`, 5 minutes). In 5 with
`D_80098A72 == 0` it sets the `D_800C3560`.. block for the next stage (0x1B, 6), clears `unk00`, pauses
the CD (`Cd_subcmd(0, 1, 0)`), restores the player (`func_80042314`), `func_8001E390(0x2EB)`,
`Sce_flag_on(0x55)`, `func_8001D974`. So `screen_tile_draw` takes `uint8` r, g, b (the caller loads
the low bytes of the `uint32` fields with `lbu`), and the stores only match with `D_800C356C = 2`
written first (its constant is loaded before the others; its store stays in place).

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

Also banked in `scene.c`: `func_8001F740` (`func_8001F798(Game_work.unk050)`, then
`D_8008980C[unk050]()`, `STAGE_FUNC`), `func_8001F5E4` (reloads three files with `Cd_read_comb` when
they change: `D_80089200[Player_work[0].unk16A]` → `Game_work.file_070`,
`D_80089204[(sint8)unk16B >> 1]` → `file_072`, and when `tbl_sel >= 2`, `D_80089208[tbl_sel]` →
`file_074`; the `file` local must be `sint32`, a `sint16` reloads the table for the store),
`Sce_flag_off` (clears the bit; for flags 0x500-0x51F also removes `flag - 0x4FF` from
`Player_work[0].ids_454[32]` and `ids_450[3]`; needs `p = Sce_flag; p += flag >> 3;` and `mask`/`bit`
locals assigned in that order), and the camera pair on `Sce_camera_work` (`SCENE_CAM_WORK`, `scene.h`; one
object from 0x800BC730 to at least 0x800BC7F3, which splat splits into many labels; `D_800BC7F0` is its
`arg_C0`): `func_8001E550` hands position and angles (`func_80038324`) or look-at point
(`func_800384A4`, whose second argument is a `VECTOR *`) to the camera code, through a local
`cp = &Sce_camera_work` (CSE turns the accesses before the first join into `%lo(sym+off)`, the later ones
keep the base register, as in the target); the high halfwords at `ang_40 + 2/6/0xA` are plain
`vx >> 16`, which GCC narrows to `lh`. `func_8001E6C0(x, y, z)` resets it from the current camera
(`D_800A39A0`, angles `D_800A3968/396C/3964 & 0xFFF` into vx/vy/vz); `D_800A395C = 3` only schedules
right when written after the first `ofs_A0` store.

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
`func_8005A598` (pick byte 3 or 4 as a message of `mes_file_44` by `Game_work.unk050/051` equal to bytes
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
`id = Player_work[0].ids_454[arg2 + D_8009899C]` if `arg1`, else `ids_450[arg2]` after setting the code's
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
bit `0x20000`). Parked `six_digit_set` (`NON_MATCHING`; six digits of `n` by `D_8008AF24` (100000..1),
leading zeros as `D_8008AF3C[pad]` until a nonzero digit (flag in `.sbss` `D_800986F0[0]`), terminator
`D_8008D028[0]` at [6]). Best attempt (index loop, `uint32 i`) is 4 bytes long: the loop end is built as
`lui/addiu %lo(D_8008AF24+0x18)`, where the target computes `addiu t3,t0,0x18` from the table register.
Tried: a pointer loop (`for`, gets a pre-test; `do/while`), a local table pointer indexed or walked
(`*place++` with `dst[i]` gives the right shape but the end from `dst + 6`), walking both pointers, `sint32 i`.
Banked, matching: the `six_digit_set` text codes `func_80057BFC` (`D_80098AF4`), `func_80057144`
(`money_40 = Game_work.money`, then prints it; the target reloads `money_40`) and `func_800579D8`
(`(Game_work.unk07D - unk07C) * 10`), each writing at `++mes_ptr_14`; `func_800554E4` (scroll command:
like `func_80054700`'s wait, but also `unk_3B++` on the first pass; each frame after the countdown
`scroll_38 -= unk_3A` until `timer_4 * unk_3A < -(unk_3B * 12)`, then `scroll_38 += unk_3B * 12`, clears
`unk_71..73`/`unk_3B`/bit `0x01000000`, `cmd_top_48 = cmd_ptr_6C += 3`, `unk_3C = unk_3E`; `unk_3B` is
`sint8`, `lb`); `func_8005AB78` (window state in `unk_7D`: 0 sets flags `0x06000000`, margins
`unk_B4 = unk_B6 = arg`, `Moji_flag |= 0x200000` and the four `corner_88` points from the margins and
`unk_7E`/`unk_7F` * 12; 2 sets `0x10000000` and clears `0x06000000`; void, in a data table).
Parked `func_80059D20` (`NON_MATCHING`; prints `D_8008AF00[i] - Game_work.unk028[i]` for `i =
D_800BE2F8[arg] < 4`, else `unk062[9 - i] * D_8008AF00[i] - unk028[9 - i]`, at `cmd + 7`, then calls into
`D_8008CE5C[i]`). Only the else branch differs: the target reuses the `i * 4` computed for
`D_8008AF00[i]`; ours recomputes it (best form `(&arr[9])[-i]`, which at least folds the 9 into the
symbol offset as the target does).

`code_8002D9A0.c`: banked `func_8002DC84` (overlay accessor: returns a 16-byte `BLK_ENT` from block
`src->blk_tbl[blk]`, entry `idx` after the header; needs one reused `uint32 *p` and one reused word
local) and `billboard_draw` (projects the `BILLBOARD`s queued by `func_8002D464` in `D_800BE6D8`, links
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
Banked by `tools/twins.py` (byte-identical to a matched function; C copied, build-checked):
`func_8004E488` (same code as `func_80054BAC`: `return 0;`), `func_8005B85C` (same code as
`func_8005AB78`), and after the twins run below `func_800181D4`, `func_8005B98C`, `func_80066714`.
Named `func_8001D888` -> `Sce_read_sync`: waits a frame at a time (`Thread_wait(1)`) until
`Cd_read_sync2()` reports the CD queue empty. Same purpose as `Cd_read_sync`, different code (it calls
`Cd_read_sync2` instead of comparing the queue pointers); its caller is in `code_800133D8`
(`func_80013420`), which loads `a0 = 1` in the call's delay slot, so Capcom's version probably took an
argument it never used.

Twins run (one of each all-assembly twin group, then `twins.py --apply`):
- `func_80013F60` (`code_800133D8`; `routine_1++` of `D_80098AA8` unless `D_80098A72`) and its
  game.c copies `func_80016D0C`/`func_80016D38`, the same bytes on `Game_work` (`GAME_WORK.routine_0`/`_1`,
  `func_800155A4` runs `Game_main_tbl[routine_0]` on it). Written by hand, since the types differ.
- `func_800666D8` (`code_8006430C`; runs `D_8008FD20[routine_1]` of its module state `D_80098910`,
  `CODE_8006430C_WORK`); routines 1 and 2 of `D_8008FD10` are the same code.
- `func_800180D4` (`code_8001786C`, `D_800821BC[0]`): once `Dbl_buff_idx` is 1, zeroes both buffers'
  vertical offsets, clip y and the isbg/dfe flags, `MojiTaskKill`, sets three pool words, calls
  `func_800196A0`. `Dbl_buff_idx`/`Vsync_wait` added to ROCK_NEO's `scratch.h` (the shim's names).
- `func_8005A874` (moji window kind 0): opens a window from a flat line `unk_85` (8) pixels a frame, then
  closes it. New `MOJI_WORK.unk_80`/`unk_85`; `unk_A` is `sint16` (`lh`). Matching needed `unk_7D++` at the
  end of state 1's block and `c[0][1] > c[2][1]` (not `<` swapped) in state 2.
- Parked `map_blocks_draw` and its twin `map_blocks_draw2` (`NON_MATCHING`, same attempt): draws the map
  blocks (`Map_blocks`, `MAP_BLOCK`) whose bits are set in a row mask, LOD by depth, through
  `Map_block_draw_tbl[kind][bit 31]`. Only the prologue differs: ours copies `rows` (a0) to s4 before setting
  `sxy = 0x1F800100` in s3. Needed: the first row's `&= 0x7FFFFFFF` before the loop, `row_end` set
  inside the `if`, the inner loop as `for (...; bits <<= 1, b++)`, the table indexed inline, and the
  drawn word read back into the `lod` local. Permuter candidate.
- Not attempted: `func_8002466C`/`func_8002626C` (0x540 bytes) and `func_80023EA8`/`func_80026B04`
  (0x7C4): scratchpad polygon subdivision with GTE, every access off one 0x1F800100 base register, the
  same pattern that parks `mesh_draw`.
