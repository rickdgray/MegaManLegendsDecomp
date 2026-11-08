# SLUS_006.03 (boot shim)

The boot executable. It initializes the system, plays the Capcom intro FMV, shows "now loading...",
and hands off to `ROCK_NEO.EXE` with `LoadExec`. About 40 functions are Capcom's; the rest is the
PsyQ 4.0 library. The rebuild is byte-identical (see [toolchain.md](toolchain.md)).

## Layout

| Region | Range | Notes |
|---|---|---|
| Header | file `0x0`–`0x7FF` | Entry `pc0` = `0x8001262c` (`start`); BSS fields are zero |
| `.rodata` | `0x80010000`–`0x800107e7` | Read-only data comes **first** |
| `.text` | `0x800107e8`–`0x8001d3b3` | Capcom's code (`main` … `Intro_task`, to `0x80012623`), then PsyQ |
| Data | `0x8001d3b4`–`0x80059b3f` | Starts with the build timestamp string |
| BSS | `0x80059b40`–`0x8005da3f` | Size `0x3f00`, zeroed by `start` |
| Heap | from `0x8005da44` | `InitHeap` |

- **Confirmed:** the file image is sector-padded to `0x8005a000`; its last `0x4c0` bytes
  (`0x80059b40`–`0x80059fff`, all zeros) overlap BSS.
- **Confirmed:** `gp` = `0x80059b14` is set but never used (`-G0`).
- **Suspected:** `"CAPCOMAug 16 1998 12:35:16CAPCOM"` at `0x8001d3b4` is `__DATE__`/`__TIME__`,
  the build timestamp of Capcom's object. Compare with `ROCK_NEO.EXE`.

## Startup (PsyQ `2MBYTE.OBJ`)

`start` (`0x8001262c`, PsyQ `__SN_ENTRY_POINT`) zeroes BSS; `stup1` sets up the stack from the 2 MB
RAM size and calls `InitHeap`; `stup0` (`0x800126cc`) calls `main`, then `break 0x1` if it returns.
The words after `stup0` (`0x800126d8`–`0x800126e3`) are `0x00200000` (2 MB) data. Library code;
not decompiled.

## Main loop and system

- `main` (`0x800107e8`): `System_init`, `VSync(0)`, `SetDispMask(1)`, `Intro_init`, then loops
  forever: wait until `Vsync_count` reaches `Vsync_wait`, `PutDispEnv`/`PutDrawEnv`,
  `Movie_frame_upload` (CD module), `DrawOTag`, `Pad_update_all`, swap buffers (`Dbl_buff_idx`, `Disp_env_ptr`), `ClearOTag`, `Intro_task`,
  `Cd_cmd_exec`, `DrawSync(0)`. GCC inserts the `__main` call itself.
- `System_init` (`0x800108ec`): `ResetCallback`, `Cd_init`, `SsInit`, `ResetGraph`,
  `DecDCTReset`, `SetVideoMode(MODE_NTSC)`, pads (`InitPAD` with `Joy1`/`Joy2`, `StartPAD`,
  `ChangeClearPAD`), `ClearImage(&Clear_rect, ...)`, `Disp_env_set(1)` (640 wide),
  `Vsync_wait = 2` (30 fps), `VSyncCallback(Vsync_handler)`, CD audio mixing on
  (`SsSetSerialAttr`/`SsSetSerialVol`).
- `Vsync_handler` increments `Vsync_count` (`0x80059bc0`). **Confirmed:** `Vsync_count` must be
  `volatile` (main spins on it); the scratchpad variables must not be.
- **Scratchpad** (`include/slus_006.03/scratch.h`, literal-address macros): `Dbl_buff_idx` (`0x1F800000`,
  current buffer 0/1), `Vsync_wait` (`0x1F800001`, vsyncs per frame). They must be literal
  addresses: GCC then shares the `lui 0x1f80` between them, as the target does.
- **Pads:** `Joy1` (`0x8005b570`) and `Joy2` (`0x8005b6c8`) are separate globals of an all-byte
  struct (the target copies it with `lwl`/`lwr`, so 1-byte alignment). `Pad_update`,
  `Pad_update_all`. **Open:** the 32-bit field at `+0x34`, set to `0x4001` in `System_init`
  (find its reader).
- `Disp_adjust`: debug screen-position adjuster (D-pad moves the display by 8 pixels).
- **Open:** `D_80059BBC` (cleared in `System_init`).

## Display

- `Disp_env[2]` (`0x8005b5a8`, type `DISP_ENV`, `0x90` bytes each): `DISPENV disp` (`0x00`),
  `DRAWENV draw` (`0x14`), `u_long ot[8]` (`0x70`). `Disp_env_ptr` (`0x80059bcc`) points at the
  current one.
- `Disp_env_set(mode)`: buffer 0 draws at VRAM y=0 and displays y=256, buffer 1 the reverse;
  height 240; width from `disp_width_tbl` = {320, 640}.
- `Disp_env_init(buf)`: `ClearOTag(buf->ot, 8)`, clear to black, no dithering.
- **Open:** `ot[7]` holds `0x0004814c` during the warning screen, so something else is linked into
  the last slot each frame.

## Intro sequence

- `Intro_task` calls `intro_tbl[Intro_routine_0]()` each frame. `Intro_routine_0` (`0x80059c50`)
  is the screen, `Intro_routine_1` (`0x80059c51`) the screen's state. **Confirmed:** separate byte
  globals (a struct broke the match); `Intro_init` sets both with one cast 32-bit store.
- `Intro_init` starts at screen 2, so **screens 0 and 1 are dead code** (confirmed in PCSX-Redux).
  It also builds screen 0's image.

| # | Function | What it does |
|---|---|---|
| 0 | `intro_copyright` | Dead. Fade in (+4/frame to 128), hold 100 frames, fade out. `Intro_bright` (`0x80059c54`), `Intro_timer` (`0x80059c55`) |
| 1 | `intro_wait_idle` | Dead. `Disp_env_set(0)`, then waits for `Cd_read_sync2()` to clear |
| 2 | `intro_play_movie` | `Cd_cmd_set_movie(0xd0, 0x91, 0x2008)`, waits: the FMV |
| 3 | `intro_launch_game` | "now loading...", then `DrawSync`, `SsQuit`, `StopPAD`, `_96_init`, `LoadExec(rock_neo_path, 0x801fff00, 0)` |

- **Screen 0's image** is an anti-piracy warning ("The unauthorised reproduction...", British
  spelling; **suspected** PAL leftover). Forcing `Intro_routine_0 = 0` plays it. It's a 640×256
  8-bit TIM (`copyright_tim`, `0x8001dfa4`; CLUT to VRAM (0,240), pixels to (640,0)), drawn by
  `intro_copyright_draw(brightness)` as 80 `SPRT`s per buffer (`copyright_sprt[2][80]`) in 5
  texture-page strips (`copyright_dr_mode[2][5]`). Its `addPrim` passes `ot[0]`'s **value**,
  not its address (three loads), so its primitives land in slot 1.
- **Screen 3's banner** is a 144×32 4-bit TIM (`loading_tim`, `0x800461c4`) at (160,200), drawn
  with `loading_sprt[2]` and `loading_dr_mode[2]`.
- Screens 1 and 2 each have an unused `RECT rect;` local (frame `0x20`), a leftover from copying
  the screen template.

## Movie

- **Ring buffer** (`MOVIE_RING_BUF`, 4 slots of `0x8000`, `MOVIE_SLOT(i)`): each slot holds one
  frame as a table of its sectors' `StHEADER`s (indexed by `secCount`), followed by all the
  sectors' frame data (`STR_DATA_WORDS` longs each). `Movie_sector_cb` fills the slot at
  `Movie_write_idx` and marks it in `Movie_buf_ready` when the last sector arrives;
  `Movie_buf_get(&data, &hdrs)` returns the header table and the start of the data for the
  slot at `Movie_buf_idx`.

### Movie playback (`cd_cmd_play_movie`, command type 5)

Arguments: `arg1` = index into `Cd_file_tbl` (disc position, default end frame); `arg2` = last frame
to play (`Movie_end_frame`); `arg3` = pad buttons that skip the movie (tested against Joy1's
"on" bits). One step per frame, driven by `Cd_cmd_routine`:

| State | Does |
|---|---|
| 0 | Stop the drive if needed; clear both display buffers (320×480); build `Movie_rect_tbl`, two sets of twenty 16×240 column rects (y = 0 and y = 256) |
| 1 | Wait for `Cd_sync_done`, then `Cd_set_mode(CdlModeSpeed \| CdlModeRT \| CdlModeSF)`: double speed, XA-ADPCM audio, subheader filter |
| 2 | Countdown on `Cd_wait`; then reset the MDEC, `Movie_start(arg1)`, 60 fps (`Vsync_wait = 1`), ramp CD volume 0→127, wait for the first frame (timeout `MOVIE_TIMEOUT`), and start variable-length decoding it into `MOVIE_VLC(Movie_frame_idx)` |
| 3 | Per frame: wait for the next frame; decide whether this is the last (skip button, `frameCount == Movie_end_frame`, or an error); decode the previous frame's VLC data through the MDEC into `MOVIE_IMG` in 16-pixel columns (`DecDCTout`, `MOVIE_SLICE_WORDS`), uploaded by `Movie_dct_out_callback`; VLC-decode the new frame into the other buffer (`Movie_frame_idx ^= 1`); spin until `Movie_dct_busy` clears |
| 4 | Remove the MDEC callback, stop the drive |
| 5 | Dequeue the command, back to 30 fps |

- A CD timeout sets `CD_ERR_TIMEOUT`, resets the drive, sets `Cd_mode = 0xFF`, and restarts at state 0.
- Decoding is double-buffered: the MDEC decodes one frame while the CPU VLC-decodes the next.
- `Movie_dct_busy` is set before decoding and cleared from the MDEC interrupt callback, so it is
  `volatile` (the target reloads it in the wait loop).

## CD command queue

- `Cd_cmd_queue` (`0x8005b348`): `CD_CMD[16]`, `0x10` bytes each: `sint32 type` (0 = end of queue,
  5 = play movie), then `CD_CMD_ARGS`, a union with one layout per command type, copied as one 12-byte block (the shim
  only uses `movie`: `file`, `end_frame`, `uint16 skip`). `Cd_cmd_write_ptr` (`0x80059c08`) is the next free slot;
  `Cd_cmd_exec_ptr` (`0x80059c38`) the command being run.
- `Cd_file_tbl` (`0x8001D3DC`, `CD_FILE[248]`): the disc's file table; the last entry is the CD
  audio track. See [disc.md](disc.md).
- `Cd_init`: `CdInit` retry loop, `Cd_controlb_retry(CdlSetmode, &Cd_mode, Cd_result)`, clears the
  queue. Stores 0 to `D_80059BCA` **twice** (required for the match).
- `Cd_control_retry` / `Cd_controlb_retry(com, param, result)`: wait on `CdSync`, then retry
  `CdControl` / `CdControlB`. `Cd_set_mode(mode)`: sets `Cd_wait = 2` if the speed bit flips.
  `Cd_sync_cb`: `CdSync` callback (complete → `Cd_sync_done = 1`, else sets `CD_ERR_SYNC`).
- **Each command type has its own argument layout.** The shim's movie command stores a 16-bit skip
  mask at +0xC (`movie.skip`), where ROCK_NEO's commands store 32-bit values there (`xa.end`,
  `subcmd.arg3`).
- `Cd_cmd_set_movie(a1, a2, a3)` appends a type-5 command; `Cd_cmd_dequeue` shifts the queue down
  one; `Cd_read_sync2` = queue not empty.
- `Cd_cmd_exec`: if `Cd_error_flags` is set, drops the current command and resets the drive; then
  calls `cd_cmd_tbl[Cd_cmd_exec_ptr->type]()`. `cd_cmd_tbl[6]`: types 0–4 → `cd_cmd_nop`, type 5 →
  `cd_cmd_play_movie` (a 6-case switch on `Cd_cmd_routine`; jump table at `0x80010000`).
- **Confirmed:** this module is shared with `ROCK_NEO.EXE`, where types 1, 2, 4, 6 and 7 do real
  work; see "Shared code" and "CD module" in [rock_neo.md](rock_neo.md).
- `D_80059C24` is only ever cleared (`Cd_init`, `Cd_cmd_dequeue`).
- **Open:** the movie arguments `(0xd0, 0x91, 0x2008)`.

## PsyQ library

Split into 27 objects (`psyq/2MBYTE` … `psyq/S_SK`); see [toolchain.md](toolchain.md). Library
functions called from Capcom code and identified by hand: `SsInit` (`0x8001a864`), `SsQuit`
(`0x8001b6e8`, a wrapper around `SpuQuit` at `0x8001b708`), `SetVideoMode` (`0x800133ac`).

- libcd and libgpu each have a `SYS.OBJ` (`psyq/SYS` at `CdStatus`, `psyq/SYS_2` at
  `ResetGraph`).
- **Open (no build impact):** libcd's debug string tables (command and interrupt names; pointer
  tables in `.data` near `0x80047d5x` and `0x80047d9c`) are used by both `SYS` and `BIOS`;
  currently assigned to `BIOS`.

## Function status

Banked: `main`, `System_init`, `Disp_env_set`, `Disp_env_init`, `Pad_update`, `Pad_update_all`,
`Vsync_handler`, `Disp_adjust`, `Cd_init`, `cd_cmd_nop`, `Movie_buf_get`, `Movie_buf_release`,
`cd_cmd_play_movie`, `Movie_dct_out_callback`, `Cd_cmd_exec`, `Cd_set_volume`, `Cd_stop`,
`Cd_sync_cb`, `Cd_control_retry`, `Cd_controlb_retry`, `Cd_set_mode`, `Cd_cmd_set_movie`,
`Cd_read_sync2`, `intro_copyright_draw`, `intro_copyright`, `intro_wait_idle`, `intro_play_movie`,
`intro_launch_game`, `Intro_task`.

Parked (`NON_MATCHING`; the build keeps `INCLUDE_ASM`):

- `Intro_init`: best draft uses chained assignments for the two sprite buffers, `getClut(0, 240)`,
  and one counter `i` for both the sprite loop and the draw-mode loop (asm-differ 210). Same length
  and instruction stream as the target; only the first loop's `i` and the hoisted constant `4`
  (sprite length) swap `s1`/`s2`, which also costs the second loop one extra `move`.
  - Permuter (10 h): best 175, by moving `rect.x = 0` into the loop (breaks the first `LoadImage`;
    shows that store timing affects allocation, not a fix). Matching the target's store order for
    the first `RECT` changed nothing.
  - Ruled out: a separate counter for the draw-mode loop (`j`): the target keeps both loops'
    counters in the same register (`s2`), so the original reuses one variable.
  - Remaining: an `s1`/`s2` priority tie between `i` and the constant. Long permuter run; it's
    slow here (~10 outputs per night vs ~50 for `Cd_cmd_dequeue`), so a good server job.
- `Cd_cmd_dequeue`: best draft is a single-pointer `for` loop:
  `for (p = Cd_cmd_queue; p->type != 0; p++) { p->type = p[1].type; p->args = p[1].args; }`,
  then `p[1].type = 0`. Instruction-for-instruction aligned (asm-differ 530). Remaining: GCC's
  derived loop pointer is based at `p + 4` (target `p + 0xc`), `p++` is scheduled after the args
  stores (target: before), and register numbering. ROCK_NEO's copy parks with the same difference.
  - Permuter (10 h, from the older `while` draft): best 150 (permuter scale), only via implausible
    disguises (constant index variables, always-true `if`s). All of them make the `type` copy and
    the `args` copy reach `p[1]` through *different* expressions.
  - Ruled out: two pointers `dst`/`src` (the target stores args through the derived pointer, so
    one source pointer), a `next` pointer (worse), `*p = p[1]`, index form, reversed copy order.
  - `CD_CMD_ARGS` is now a union (`movie` member); the draft's diff is unchanged (score 530), so
    the union view alone doesn't explain `p + 0xc` (= the `args` word at +0xC, the last of the three).
    ROCK_NEO reads that word as 32 bits in several functions (see [rock_neo.md](rock_neo.md)).
- `Movie_frame_upload`: one line from matching. Draft: `i = 0;`, then `rect` (computed once from
  `Dbl_buff_idx`), then a variable holding 1, then `img` (a walking pointer stepping one column,
  `0x1E00` bytes), then `for (; i < 20; i++)` with `(one - Movie_frame_idx) * 0x25800`. All
  registers and instruction order match; only `addu a1,a1,s1` (target) vs `addu a1,s1,a1` (ours)
  at the image address differs. The variable holding 1 is a marked hack (it makes GCC create the
  constant before the image pointer). Tried: operand order in the source, the variable before
  `rect`, declared last; the indexed form reloads `Dbl_buff_idx` in the loop. History: ablation of
  a permuter output showed its `do`/`while (0)` mattered; `i = 0` before the pointer setup fixed
  all registers.
- `Movie_sector_cb` (`0x80011A64`): body matches; in the last `else` arm (the CD error path) the
  target emits `move a0,zero` first and leaves the branch delay slot as a `nop`, where ours fills
  it. Needs the STR sector header read through a struct pointer assigned after `CdGetSector`, and
  the payload source as a literal `0x800F0020`. A delay-slot difference: candidate for an
  assembler (maspsx `--aspsx-version`) test.
- `Movie_start` (`0x80011940`): body matches exactly. Only difference: the target rebuilds
  `Cd_result`'s address (`lui`/`addiu`) before each of the three `Cd_controlb_retry` calls; our
  compiler keeps it in `s0`. `Cd_status = 1` must come first (it hoists `li s1,1`); the filter
  stores follow `Movie_end_frame`. Tried `&Cd_result[0]`. No source construct found that controls
  this; it's GCC's cost choice between rematerializing a constant and keeping it in a saved
  register.
  - Probe results (three calls passing the same buffer): GCC keeps a symbol's address in a saved
    register, with or without an offset (struct member). A literal address (`(u_char *)0x80059C40`)
    is rebuilt per call like the target, but as `lui`+`ori`; the target's `lui`+`addiu` proves a
    symbol. No effect: `volatile`, an unsized array, no prototype, `do`/`while (0)` wrappers.
    `-fno-expensive-optimizations` reproduces it but breaks other functions; all gcc
    2.6.0–2.7.2.3 builds behave alike ([toolchain.md](toolchain.md)). Next: permuter.

## Hacks to revisit

- `D_80059B4C` aliases `loading_dr_mode[1]`. The target reaches the second draw mode through a
  separate symbol (a fresh `lui`), but the per-frame code indexes both by `Dbl_buff_idx`. Find a
  non-aliasing shape (perhaps a struct holding the sprites and draw modes); permuter candidate.

## Open questions

- `2MBYTE.OBJ` holds two `0x00200000` words; which is the RAM size and which the stack setting?
- Meaning of the loader's `_B4` suffix on `2MBYTE_OBJ_B4`.
