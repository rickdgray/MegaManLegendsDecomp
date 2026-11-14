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
- In C, `Thread_current` and `THREAD_TBL` (`0x801F8100`, 4 records of 0x80) are literal-address
  macros (`system.h`): the target builds them with `lui 0x801f` / `ori 0x8300` and accesses at offset
  0, which only a constant gives. Using the `extern` symbol in `func_80012ECC` gives `%hi`/`%lo`.
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

`main` (`src/rock_neo.exe/main.c`), this round: banked `Disp_env_setup` (display buffers at `0x800C0C48`,
`extern DISP_ENV Disp_env[2]`: the extern symbol is needed, an absolute-address cast loses the shared
base), `Pad_repeat_update`/`func_80012350` (auto-repeat on `PAD_REP`, which extends `PAD_WORK` with
`rep_state[8]` at +0x38 and `rep_count[8]` at +0x40; `mask` is `sint32`), `Thread_open`
(`OpenTh` from the thread record's `sp`/`gp`), `func_800131FC` (thread entry: dispatch through
`D_80080894[D_80098B1C]`, then `Thread_wait(1)`). Parked: `func_80012BC4` (thread table init). The
table base `*(TCB **)0x110` must be written via a `TCB **kp = (TCB **)0x100` local (`kp[4]`) to get
the `li t2,0x100` / `lw 0x10(t2)` split, and `gp` read into a local before the loop. Still different:
target reloads `THREAD_TBL[i].tcb` from memory before storing `->sr` (ours reuses the register), and the
loop counter/giv are scheduled differently. Tried: `uint32` field with a cast, `[0x25]` word index.

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
`D_800BFB20[n]` by id into `D_8009856C[16]`; `D_800BFB22` is declared as a second `WORK_10C` array so
the access keeps its own `lui`), `Angle_xz_vector`, `Angle_xz_svector` (`catan` of the x/z delta).
Parked `func_80036C50` (`NON_MATCHING`; 4-entry table at `D_8009A306`, stride 0x14): the target keeps
`&D_8009A306` in a3 for the first compare and the loop; ours folds the first compare to `lui`+`%lo` and
rebuilds the base for the loop (local pointer, `e++`/flag pointer, index forms tried).

`code_8002E7A8.c` (batch 3): banked `func_800331A0` (joint matrix/position update on the player, `PL_WORK.joint_mtx`/`joint_pos`: scratchpad
matrix + `ApplyMatrix`/`RotMatrix`/`MulMatrix`/`ScaleMatrix`; the byte at `0x1F800074` is a shift count,
also written as `Scratch_scale_shift`; needs an unused 8-byte local), `func_800341BC` and `func_8003430C`
(queue one/two `SLOT_REQ` entries in `D_800A2F48[0x40]`, count in `D_800988E0`, value in `D_800A32E0[n]`,
then copy the vector or the midpoint into `D_800BE478[slot] + 0xBC` for each slot bit of
`owner->mask_4 & D_80098798`; the register match needs a separate `mask` local and `i` used as the
`owner->mask_4` temp). Parked `func_80036B40` (`NON_MATCHING`): copies the 0x28-byte block at
`D_800BC7F8` to `D_8009A350` after `SetFarColor`/`SetFogNear`; the copy is right, but the target keeps
`&D_800BC818` in s0 from the start (also the copy end pointer) while ours rebuilds `D_800BC818-0x20`.
Parked `func_80035724` (`NON_MATCHING`; spawns a `WORK_10C` slot from `PL_WORK`, claims a slot with
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
keeps the result in v0 and a copy of the angle in v1, GCC uses a scratch register), `func_80031BEC`
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
`pos_1C`, `pos_428`, `svec_438`), `OBJ_10C` into `WORK_10C`, `func_8002F998`'s pointer into `EVE_WORK`.
`func_800323FC` is down to the order of its first two loads (lbu time before lw ent_FC) after reusing the
parameter as the copy of ctl.

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
calls `func_80043294`/`func_80043340` with `D_8008A678`/`D_8008A680[Game_work 0x5B][field_A]`; `field_A` is kept in a
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
