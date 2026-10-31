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
  `func_80011680` (CD module), `DrawOTag`, `Pad_update_all`, swap buffers (`Dbl_buff_idx`, `Disp_env_ptr`), `ClearOTag`, `Intro_task`,
  `Cmd_exec`, `DrawSync(0)`. GCC inserts the `__main` call itself.
- `System_init` (`0x800108ec`): `ResetCallback`, `Cd_init`, `SsInit`, `ResetGraph`,
  `DecDCTReset`, `SetVideoMode(MODE_NTSC)`, pads (`InitPAD` with `Joy1`/`Joy2`, `StartPAD`,
  `ChangeClearPAD`), `ClearImage(&Clear_rect, ...)`, `Disp_env_set(1)` (640 wide),
  `Vsync_wait = 2` (30 fps), `VSyncCallback(Vsync_handler)`, CD audio mixing on
  (`SsSetSerialAttr`/`SsSetSerialVol`).
- `Vsync_handler` increments `Vsync_count` (`0x80059bc0`). **Confirmed:** `Vsync_count` must be
  `volatile` (main spins on it); the scratchpad variables must not be.
- **Scratchpad** (`include/scratch.h`, literal-address macros): `Dbl_buff_idx` (`0x1F800000`,
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
| 1 | `intro_wait_idle` | Dead. `Disp_env_set(0)`, then waits for `Cmd_busy_check()` to clear |
| 2 | `intro_play_movie` | `Cmd_set_movie(0xd0, 0x91, 0x2008)`, waits: the FMV |
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

## CD command queue

- `Cmd_queue` (`0x8005b348`): `CMD[16]`, `0x10` bytes each: `sint32 type` (0 = end of queue,
  5 = play movie), then `CMD_ARGS` (`arg1`, `arg2`, `sint16 arg3`; copied as one 12-byte block,
  possibly a union per command type). `Cmd_write_ptr` (`0x80059c08`) is the next free slot;
  `Cmd_exec_ptr` (`0x80059c38`) the command being run.
- `Cd_init`: `CdInit` retry loop, `Cd_control_retry(CdlSetmode, &Cd_mode, Cd_result)`, clears the
  queue. Stores 0 to `D_80059BCA` **twice** (required for the match).
- `Cd_control_retry(com, param, result)`: waits on `CdSync`, then retries `CdControlB`.
- `Cmd_set_movie(a1, a2, a3)` appends a type-5 command; `Cmd_dequeue` shifts the queue down one;
  `Cmd_busy_check` = queue not empty.
- `Cmd_exec`: if `D_80059BDC` is set, drops the current command and resets the drive; then calls
  `cmd_tbl[Cmd_exec_ptr->type]()`. `cmd_tbl[6]`: types 0–4 → `cmd_nop`, type 5 →
  `cmd_play_movie` (a 6-case switch; jump table at `0x80010000`).
- **Suspected:** this module is shared with `ROCK_NEO.EXE`, where types 1–4 do real work.
- **Open:** `D_80059C20`/`D_80059C24` (per-command progress, cleared on dequeue), `D_80059BDC`
  (abort flag?), the movie arguments `(0xd0, 0x91, 0x2008)`.

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
`Vsync_handler`, `Disp_adjust`, `Cd_init`, `Cd_control_retry`, `cmd_nop`, `Cmd_exec`,
`Cmd_set_movie`, `Cmd_busy_check`, `Intro_task`, `intro_copyright`, `intro_copyright_draw`,
`intro_wait_idle`, `intro_play_movie`, `intro_launch_game`.

Parked (`NON_MATCHING`, on the permuter):

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
    slow here (~10 outputs per night vs ~50 for `Cmd_dequeue`), so a good server job.
- `Cmd_dequeue`: best draft is a single-pointer `for` loop:
  `for (p = Cmd_queue; p->type != 0; p++) { p->type = p[1].type; p->args = p[1].args; }`,
  then `p[1].type = 0`. Instruction-for-instruction aligned (asm-differ 530). Remaining: GCC's
  derived loop pointer is based at `p + 4` (target `p + 0xc`), `p++` is scheduled after the args
  stores (target: before), and register numbering.
  - Permuter (10 h, from the older `while` draft): best 150 (permuter scale), only via implausible
    disguises (constant index variables, always-true `if`s). All of them make the `type` copy and
    the `args` copy reach `p[1]` through *different* expressions.
  - Ruled out: two pointers `dst`/`src` (the target stores args through the derived pointer, so
    one source pointer), a `next` pointer (worse), `*p = p[1]`, index form, reversed copy order.
  - **Suspected:** `p + 0xc` is `&p->args.arg3`, so the original may touch `arg3`'s word directly,
    e.g. through a union view of `CMD_ARGS`. Revisit when group B shows how `CMD_ARGS` is used.
  - `permuter/Cmd_dequeue/` regenerated from the `for` loop draft.

Not started (group B, the CD module): `func_800110EC`, `func_8001115C`, `cmd_play_movie`,
`func_80011614`, `func_80011680`, `func_80011830`, `func_80011860`, `func_800118CC`,
`func_80011940`, `func_80011A64`, `func_80011C1C`, `func_80011CEC`.

## Hacks to revisit

- `D_80059B4C` aliases `loading_dr_mode[1]`. The target reaches the second draw mode through a
  separate symbol (a fresh `lui`), but the per-frame code indexes both by `Dbl_buff_idx`. Find a
  non-aliasing shape (perhaps a struct holding the sprites and draw modes); permuter candidate.

## Open questions

- `2MBYTE.OBJ` holds two `0x00200000` words; which is the RAM size and which the stack setting?
- Meaning of the loader's `_B4` suffix on `2MBYTE_OBJ_B4`.
