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
| 6 | `CD_CMD_READ_COMB` | `cd_cmd_read_comb` | `Cd_read_comb(file)` | Read a combined file through the ring (below); parked |
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
`symbol_addrs_rock_neo.exe.txt`. His layout and `gp` are confirmed (above); his file starts were
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

`cd` (`src/rock_neo.exe/cd.c`): every function is banked except three parked ones.

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
    Permuter queue.
  - `cd_cmd_read_comb`: score 330, register allocation only: `buf`/`x` swapped (`a2`/`a3`) in the
    header case, and size/destination (`a0`/`a2`) in the three byte-copy loops. Found on the way:
    `tiles` keeps `col`/`row` at the same offsets as `tim` (`pad[6]`); type 10 computes the
    height before the width; the CLUT row must be the `CLUT_BUF_ROW` macro (it re-reads
    `head->arg[1]` at each use; an inline function is worse). Ruled out: declaration orders.
    Permuter running.

`sound` (`src/rock_neo.exe/sound.c`), parked: `Sound_call2` (8-register difference only): the
target keeps the queue pointer in `v0` and the loaded `args[0]` in `v1`, and stores `args[1]`
before the pointer increment (`nop; sw v1,8(v0)`); ours puts the pointer in `v1` and hoists the
`arg2` store to after the global store. Tried: local pointer, `args++`, `&p[1]`, `+= 1`.

`sound`, more parked (banked this round: `pitch_scale`, `fade_step`):
- `func_80019D18`: body is right except that the target reloads `Game_work+0x50`/`+0x51` with a
  fresh `lui` each (we keep the base in `s0`, +1 saved reg), and keeps the `id != 0xFFFF` test as
  a value in `v0` (ours: `a1`). `sint16 id` removes the extra `sll/sra`. Tried: local func
  pointer, `ok` flag, `&&` form, `uint16`/`sint32` id.
- `Sound_update`: target hoists both table bases (`Sound_call_info_tbl`, `Sound_call_func_tbl`) into `s2`/`s1`
  after the loop pre-test; ours hoists only `Sound_call_func_tbl` and folds `Sound_call_info_tbl` as `lui at`.
  Tried: sized array, local `uint8 (*)[4]`, `SOUND_CALL_INFO` struct (the current attempt).
- `pitch_interp`: target copies `a` (`pitch_scale(x)`) into `s2` right after call 1, keeping `x`
  live in `s0`; ours sinks the copy and reuses `s0`. Signed `/ 128` is right.
- `Sound_seq_stop_all`: target has two separately-based induction pointers (`Sound_seq_chan_tbl` and
  `D_80098AFC`) and `-1` in `s3`; ours derives `+4` from one base. Registry has `D_80098AFC`
  as its own symbol: maybe the source indexed two arrays.

`sound`, this round: banked `key_on_tone` (key on one tone: `SpuSetKeyOnWithAttr`), `Sound_stage_slot_set`
(per-stage sound id slots by Sce flags), `voice_check` (voice priority / distance check against
the player). `key_on_tone`'s first parameter is `uint16` (the caller zero-extends). Parked:
- `Sound_stage_check`: same shape as `func_80019D18` but with `D_800C356E/F` as the "old" stage. Body
  is right; target keeps `list` in `a0`, `changed` in `a1`, the table base in `v1` (ours `v1`,
  `a0`, `a1`) and loads `Game_work+0x50`, then (after the `addu`) `+0x51`. Tried: declaration
  orders, local for the inner list (hoists the loads: worse), operand order of `!=`, if/else flip.
- `Sound_call_play`: loop is right (`uint16 voice` even reproduces the `andi 0xff`). Target
  computes `bank * VAB_HEAD_SIZE` first and adds it last to `&base[idx]` (`a2 = 0x8014B820`);
  ours folds it into the base. Tried: `VAB_HEAD` struct indexing, local `vab`, two-step pointer,
  `uint32` cast with an `off` local; target also assigns `info`=s2, `tone`=s1, `voice`=s3.
- `Sound_init`: all stores right, but the scheduler order differs: target emits `li v1,0x7f`
  before the first store and `li v0,0xf` before the `D_80098788` store, with the `D_80098788` /
  `D_80098958` stores ahead of the `0x7F` stores; ours hoists the `0x7F` stores above them and
  loads `0xf` late. Source order of the stores makes no difference; a `vol` local is folded away.

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
- `calc_vol` angle needs `angle = a - f(); angle &= 0xFFF;` as two statements; `Game_work.unk058` is sint8 at 0x58.
- `volume_update` PARKED (NON_MATCHING in sound.c): only the sequence-volume loop differs. Target
  strength-reduces into two pointers from separate `lui`s (s3 = Sound_seq_chan_tbl, s0 = D_80098AFC, s4 = -1, s2 = i, s1 = work);
  our pointer/indexed variants give different register assignment.
