# Recon Notes: Mega Man Legends (USA)

Findings from initial reconnaissance. Each entry is marked **confirmed** (verified directly) or **suspected** (hypothesis with supporting evidence, not yet verified).

## Target

| | |
|---|---|
| Serial | SLUS-00603 |
| Redump | <http://redump.org/disc/2773/> |
| Track 1 SHA-1 | `904489e2e8d06e1c44e60d8925329f9472b2d037` |
| Track 2 SHA-1 | `d9f92af296360772e62caa4cb276de3fa74f5538` |
| Boot executable SHA-1 | see `checksums.sha1` |

## Disc layout

- **Confirmed:** `SYSTEM.CNF` boots `cdrom:\SLUS_006.03;1`.
- **Confirmed:** the data track round-trips. `dumpsxiso` extraction plus the `mkpsxiso` rebuild from `layout/` reproduces Redump Track 1 exactly (207,145 sectors, 0 differences).
- **Suspected:** `SLUS_006.03` is a small loader shim, and `ROCK_NEO.EXE` holds the main game code. Evidence so far: a second executable sits in the disc root, and "Rockman" is the character's Japanese name. Not yet analyzed.
- **Suspected:** `CDDATA/DAT/ST*.BIN` are per-stage files, named by area and sub-area (e.g. `ST04_00B.BIN`). These are overlay candidates.
- `CDDATA/STR/CAPCOM20.STR`: FMV video. Out of scope for code recon.
- `CDDATA/XA/*.XA`: streamed XA audio. Out of scope for code recon.
- Track 2: CD audio.

## Code inventory

From `tools/Count-MipsFunctions.ps1` (counts of `jr ra`; estimates ±10–20%). 53 of 249 extracted files contain code. Total: 12,243 `jr ra`.

| Group | `jr ra` | Share (deduplicated) |
|---|---|---|
| `SLUS_006.03` | 292 | 2.7% |
| `ROCK_NEO.EXE` | 1,630 | 15.1% |
| Stage files `ST*.BIN` (unique) | 8,708 | 80.9% |
| `SUPPORT.BIN`, `ARM*R.BIN` | 134 | 1.2% |
| **Total, duplicates removed** | **10,764** | |

- **Confirmed:** most code lives in the stage overlays, not the main executables.
- **Confirmed:** only top-level stage files contain code (`ST03.BIN`, `ST04.BIN`, ...). Sub-area files (`ST04_00B.BIN`, etc.) have no hits, so they're data.
- **Suspected duplicates** (identical counts, and for `SUPPORT*` identical sizes): `ST03`/`ST03B`, `ST04`/`ST04B`, `ST10`/`ST10B`, `ST11`/`ST11B`, `ST0C`/`ST0CB`/`ST0CC`, `SUPPORT`/`SUPPORT2`. Possibly the same code bundled with different assets. Verify by hashing their code regions.
- **Suspected:** all stage overlays load at the same RAM address, a shared overlay region.
- **Suspected:** `ARM*R.BIN` (4–18 each) are small code modules, perhaps per-weapon behavior. `ARM00L`/`ARM04L` have no code.
- Totals still include PsyQ library code, which isn't a decompilation target. Calibrate against Ghidra's function count for `SLUS_006.03`.

## SLUS_006.03

**Tooling:** Ghidra 12.1.4, ghidra_psx_ldr 2026.10.03, default auto-analysis.

### Findings

- **Confirmed:** `gp = 0x80059b14` (Ghidra's `assume gp` value). Needed later for splat.
- **Confirmed:** PsyQ startup code identified by loader signatures (`stup0`, `stup1`).
- **Confirmed:** `stup0` at `0x800126cc` calls `main` (`jal main`). If `main` ever returns, it hits `break 0x1`, a deliberate trap.
- **Confirmed:** links PsyQ `2MBYTE.OBJ` (standard 2 MB memory configuration). The loader labeled the block `2MBYTE_OBJ_B4` at `0x800126d8`.
  - `0x800126d8`: word `0x00200000` (2 MB). 0 references.
  - `0x800126dc`: word `0x00200000`, read by `stup1` at `0x80012670`.
  - **Suspected:** `0x800126e0`: the raw bytes `00 00 20 00` also read as `0x00200000`. Still undefined in Ghidra.
- **Confirmed:** a single `gp` value across the program (Register Manager shows one set value).
- [ ] Compare `gp` with the `gp0` field in the EXE header (offset `0x14`).
- **Confirmed:** string `"cdrom:\ROCK_NEO.EXE;1"` at `0x80059b24`, which is `gp + 0x10`. The `cdrom:` device prefix is BIOS file-path style, which suggests a BIOS-level load call (e.g. `LoadExec`) rather than PsyQ's CD library. **Suspected** until the code using it is read.
- Many Address Table bookmarks. These are suspected pointer tables (jump tables, function tables, or string tables). To review: what do they point to?

### `main`

- **Confirmed:** standard PsyQ double-buffered render loop. After init (`__main`, `FUN_800108ec`, `VSync(0)`, `SetDispMask(1)`, `FUN_80011da8`), it loops forever. Each iteration waits on a frame counter, then runs `PutDispEnv` → `PutDrawEnv` → `FUN_80011680` → `DrawOTag` → `FUN_80010be0` → buffer swap → `ClearOTag` → `FUN_800125e8` → `FUN_80011730` → `DrawSync(0)`.
- **Confirmed:** two display buffers, each `0x90` bytes, at `0x8005b5a8` and `0x8005b638`. The offsets match a classic PsyQ buffer struct:
  ```c
  typedef struct {
      DISPENV  disp;   // 0x00, 0x14 bytes
      DRAWENV  draw;   // 0x14, 0x5C bytes
      u_long   ot[8];  // 0x70, 8-entry ordering table
  } DB;                // 0x90
  ```
  `DAT_80059bcc` is the current-buffer pointer. Ghidra mistyped it as `DISPENV *`.
  **Applied in Ghidra:** struct named `DisplayBuffer`. The pointer is retyped `DisplayBuffer *`, and `0x8005b5a8` is typed `DisplayBuffer[2]`.
- **Confirmed:** the buffers live in uninitialized memory (no bytes in the file; filled at runtime).
- **Confirmed:** `FUN_800109f8(mode)` sets up both buffers with `SetDefDrawEnv` / `SetDefDispEnv`. Buffer 0 draws at VRAM y=0 and displays y=256 (`0x100`). Buffer 1 is the reverse. Height is 240 (`0xf0`). Width is read from a `short` table at `0x8001d3d8`, indexed by `mode`. It then calls `FUN_80010ac4` on each buffer.
- **Confirmed:** `FUN_800109f8` is called from 4 sites (`0x80010984` in `FUN_800108ec`, plus `0x80012200`, `0x8001228c`, `0x80012350`), so the shim changes display width at runtime.
- **Confirmed:** the width table at `0x8001d3d8` is `short[2]` = {320, 640}, named `g_screenWidths`. So mode 0 = 320×240 and mode 1 = 640×240. It ends where `DAT_8001d3dc` begins (separate xref from `FUN_80011940`).
- **Suspected:** the string `"CAPCOMAug 16 1998 12:35:16CAPCOM"` at `0x8001d3b4` comes from `__DATE__`/`__TIME__`, giving this translation unit's build timestamp. Compare with any similar string in `ROCK_NEO.EXE`.
- **Confirmed:** `g_curBuffer` (`0x80059bcc`, `DisplayBuffer *`) is NULL in the file and set at runtime. Writes: `FUN_800108ec` @ `0x800109a0` (init) and `main` @ `0x800108ac` (swap). Reads: 3 in `main`, plus `FUN_80011f88` @ `0x80011ff8` and `0x80012554`, which is outside any defined function. Check whether Ghidra missed a function there.
- **Confirmed:** handoff to the game is `LoadExec("cdrom:\ROCK_NEO.EXE;1", 0x801fff00, 0)` at `0x8001252c`. The stack is set to `0x801fff00` with size 0.
- **Confirmed:** that call sits in code Ghidra did not define as a function (`UndefinedFunction_80012300`). It has no direct `jal` callers seen yet. **Suspected:** reached via a function pointer. To do: create the function, find what references it (memory search `00 23 01 80`).
- **Confirmed:** function created at `0x80012300` (`FUN_80012300`). Its only outside reference is a pointer `(*)` from data at `0x8001dfa0`. **Suspected:** a table of function pointers. Check neighbors before naming.
- **Confirmed:** `FUN_80012300` is a 3-state machine on `DAT_80059c51`:
  - State 0: `SetupDisplay(0)` (320×240). Uploads a 16-color CLUT to VRAM (0,241) from `DAT_800461d8`, and a 4-bit 144×32 image to VRAM (640,256) from `DAT_80046204`. Fills two `SPRT` primitives at `0x8005a970` (stride 0x14). Calls `SetDrawMode` on two `DR_MODE` at `0x80059b40` (stride 0xc) with tpage `0x1a`.
  - State 1: advances to 2 (one-frame wait).
  - State 2: `DrawSync(0)`, `FUN_8001b6e8()`, `StopPAD()`, `_96_init()`, `LoadExec(ROCK_NEO)`.
  - Every call: `addPrim` of this buffer's `SPRT` and then `DR_MODE` into `g_curBuffer->ot[0]`.
- **Confirmed:** `SPRT` field values cross-check. `code` 0x64, `rgb` 128, position (160,200), `uv` (0,0), `clut` 0x3c40 = (0,241), size 144×32. Tpage `0x1a` = (640,256), 4-bit. **Suspected:** the image is a "loading" banner.
- **Confirmed:** `0x8001df94` is a 4-entry table referenced by `FUN_800125e8` @ `0x80012604`: `0x80012094`, `0x800121d8`, `0x80012264`, `FUN_80012300`. **Suspected:** an array of function pointers (screen/step dispatch), since the targets lie outside `FUN_800125e8`. Confirm with `jalr` vs `jr` at the use site. If so, create functions at the first three entries.
- **Confirmed:** `0x8001df7c` is a 6-entry switch jump table for `FUN_80011730` (five entries → `LAB_800110e4`, one → `LAB_80011194`).
- **Confirmed:** Memory Map: `RAM` `80000000`–`8000ffff` (BIOS/kernel), `CODE` `80010000`–`80059fff` (EXE file image, `0x4a000` bytes, initialized), `RAM` `8005a000`–`801fffff` (uninitialized), plus scratchpad (`CACHE`) and hardware register blocks. The loader marked `CODE` read-only. It also holds writable globals, so W enabled on both `CODE` and upper `RAM`. To do: split `CODE` at the end of instructions once known.
- **Confirmed:** the file image ends at `0x8005a000`. BSS begins there (`SPRT`s at `0x8005a970`, display buffers at `0x8005b5a8`). To do: cross-check with header BSS fields at `0x28`/`0x2c`.
- **Confirmed:** `0x8001df94` is a function-pointer table, `g_screenFuncs[4]`, called via `jalr` from `FUN_800125e8` (the dispatcher: `(*g_screenFuncs[DAT_80059c50])()`). Functions created at all four entries.
- **Confirmed:** `DAT_80059c50` = screen index (incremented by each screen when done). `DAT_80059c51` = per-screen state (reset to 0 on advance). Suggested names `g_screenIndex`, `g_screenState`.
- Screens:
  - 0 `FUN_80012094`: fade in (+4/frame to 128), hold 100 frames, fade out (−4, ends on unsigned wrap). Brightness in `DAT_80059c54`, hold counter in `DAT_80059c55`. Passes brightness to `FUN_80011f88`, which reads `g_curBuffer`. **Suspected:** Capcom logo.
  - 1 `FUN_800121d8`: `SetupDisplay(0)`, then polls `FUN_80011d8c()` until 0.
  - 2 `FUN_80012264`: same, but first calls `FUN_80011d5c(0xd0, 0x91, 0x2008)`. **Unknown:** what screens 1–2 wait on (sound/movie/disc?).
  - 3 `FUN_80012300`: loading image, then `LoadExec(ROCK_NEO)`.
- **Confirmed (emulator):** visible boot order: Sony Computer Entertainment logo (fades) → PlayStation logo → pre-rendered video ending on the Capcom logo → "now loading..." → main menu. **Suspected:** both logos are BIOS, shown before the shim starts. The Sony fade is the BIOS's, not `Screen_FadeImage`.
- **Confirmed:** screen 3's "now loading..." banner position matches the `SPRT` (144×32 at (160,200) on 320×240, bottom right).
- **Unknown:** what `Screen_FadeImage` (screen 0) shows. To do: watch `g_screenIndex` (`0x80059c50`) in PCSX-Redux/DuckStation through boot.
- **Confirmed:** `FUN_80011d8c` returns `DAT_80059c08 != &DAT_8005b348`. **Suspected:** a busy check (read pointer vs end, or queue head vs sentinel); proposed name `IsBusy`. To do: find writers of `DAT_80059c08`. Expected `FUN_80011d5c` (start) and a per-frame function, possibly `FUN_80011730` (has a switch table). **Suspected:** the shim plays the video itself (imports `LIBPRESS.H`, the MDEC decoder).
- **Confirmed:** `DAT_80059c08` writers: `FUN_80011004` (W only), `FUN_80011d5c` (R+W), `FUN_800117ac` (R+W). Reader: `IsBusy`. **Confirmed:** it's the write pointer of an array-based command queue at `0x8005b348` (`g_cmdQueue`). Entries are 16 bytes: `int type` (0 = end), `int arg1`, `int arg2`, `short arg3`, padding. `FUN_80011004` (called from init `FUN_800108ec`) points the write pointer at the queue start. `FUN_80011d5c(a1, a2, a3)` appends a type-5 command and advances 16 bytes. `FUN_800117ac` removes the front entry (shifts all down), clears `DAT_80059c20`/`DAT_80059c24`, and moves the pointer back 16. `IsBusy` = queue not empty.
- **Confirmed (emulator):** `g_screenIndex` 0 → (1, two frames) → 2 during video → 3 during loading screen. Screen 1 drains any earlier queued commands; with an empty queue it takes two frames. Screen 2 queues type 5 with (0xd0, 0x91, 0x2008) and waits; this is the video.
- **Suspected:** `FUN_80011730` (called each frame from `main`) runs the front command. Its 6-entry switch table sends index 5 to `LAB_80011194`, likely video playback. To do: read it, decode the type-5 arguments, find the queue length (next label after `0x8005b348`). Proposed names: `FUN_80011d5c` → `QueuePlayMovie` (suspected), `FUN_800117ac` → `DequeueCommand`, `DAT_80059c08` → `g_cmdWritePtr` (`Command *`).
- **Confirmed:** `g_cmdQueue` = `Command[16]` at `0x8005b348`–`0x8005b447`. Init zeroes the `type` word of 16 entries (offset `0xf0` down to 0, step `0x10`). `Command` must be `0x10` bytes (the pointer moves 16). A 14-byte struct made the decompiler emit `&p[1].type + 2` and `&p[-2].arg3` instead of `++`/`--`.
- **Suspected:** `DequeueCommand` uses struct assignment (`*p = p[1]`) in the original source. It copies `arg3` and padding as one 32-bit word. Matters for matching.
- **Confirmed:** `FUN_80011004` calls `CdInit()` in a retry loop, then sets up the queue. It sets `g_cmdWritePtr` and `DAT_80059c38` to the queue start. **Suspected:** `FUN_80011c84(0xe, &DAT_80059bcb, &DAT_80059c40)` is `CdControl(CdlSetmode, ...)` (CdlSetmode = 0x0e) or a wrapper Ghidra didn't match. **Suspected:** the queue holds CD commands, with type 5 = play a stream from disc (the video). Proposed name `FUN_80011004` → `InitCd`.
- **Unknown:** what is visible while `g_screenIndex` = 0. Watching memory during the PlayStation logo is inconclusive: the index is 0 in the file image and may read 0 before the shim is loaded. To do: breakpoint on `Screen_FadeImage` (`0x80012094`), or read `FUN_80011f88`.
- **Confirmed (PCSX-Redux):** after `LoadExec`, `ROCK_NEO.EXE` occupies the shim's memory. At `0x80012094` there's a function epilogue plus `jal 0x8007a060`, not `Screen_FadeImage`. So ROCK_NEO's load range covers `0x80012094` and extends past `0x8007a060`. **Suspected:** load address `0x80010000` (check header). The "now loading..." image stays visible after the handoff until ROCK_NEO redraws (VRAM persists).
- **Confirmed (PCSX-Redux, fresh boot with breakpoint on `0x80012094`):** `Screen_FadeImage` never executes. The breakpoint is known to work (it fired in ROCK_NEO). Memory at that address over time: zeros (Sony logo) → BIOS scratch data (Sony logo) → zeros (PS logo) → shim code (PS logo; matches Ghidra) → unchanged through the video, no hit. The shim is loaded and runs while the BIOS PlayStation logo is still displayed.
- **Confirmed:** `FUN_80011da8` (called once from `main` before the loop; proposed name `InitIntro`) sets `g_screenIndex` = 2, so **screens 0 (`Screen_FadeImage`) and 1 are dead code**. The intro starts at the video. The earlier observation of index 0 was pre-init RAM.
- **Confirmed (PCSX-Redux):** that write is a 32-bit `sw` at `0x80011dc8` (`lui at,0x8006` / `sw v0,-0x63b0(at)`), covering `g_screenIndex`, `g_screenState`, and the next two bytes (index = 2, the rest 0). `_DAT_80059c54 = 0` is likely the same pattern for brightness and hold counter. **Suspected:** the source wrote a 32-bit value there, so these bytes are probably fields of one struct (GCC 2.x doesn't merge byte stores). Matters for matching.
- **Confirmed:** `InitIntro` builds the unused screen 0 image: a 640×256 8-bit full-screen image. 256-color CLUT from `DAT_8001dfb8` → VRAM (0,240) (clut `0x3c00`). Pixels from `DAT_8001e1c4` → VRAM (640,0), 320×256 units. It is drawn as 80 `SPRT`s (32×64) per buffer in 5 texture-page strips, with arrays `SPRT[80]` at `0x80059c78` and `0x8005a2b8`, `DR_MODE[5]` at `0x8005a8f8` and `0x8005a934`. Tpages `(10+i) | 0x80` = VRAM x 640–896, 8-bit. Width 640 = `SetupDisplay` mode 1, unused by live screens.
- **Confirmed (VRAM viewer):** the cut screen 0 image is an anti-piracy/copyright warning ("The unauthorised reproduction of all or any part of this product..."). **Suspected:** the PAL/European warning (British spelling), disabled in the US build by starting at index 2.
- **Confirmed (PCSX-Redux):** before loading the shim, the BIOS (loop at `0xbfc0d864`) zeroes RAM from `0xa0010000` up to the stack pointer, via the uncached `0xa0` mirror. Write breakpoints fire on it because they watch physical memory.
- **Confirmed (PCSX-Redux):** forcing `g_screenIndex` = 0 after `InitIntro` plays the cut warning screen (fade in, hold, fade out), apparently in 640-wide mode.
- **Confirmed:** `SPRT[80]` at `0x80059c78` ends at `0x8005a2b7`, crossing the `CODE`/`RAM` block boundary at `0x8005a000`, so Ghidra can't define it. **Suspected:** `0x8005a000` is only the end of the sector-padded file image (`0x4a000` = multiple of 0x800), not the real BSS start. BSS begins at or before `0x80059c78` (neighboring globals like `g_curBuffer` and `g_cmdWritePtr` are zero in the file). Header BSS start/size at `0x28`/`0x2c` are zero (**confirmed**).
- **Confirmed:** `stup0` (`0x800126cc`) is only the tail of PsyQ startup: `jal main`, then `break 0x1`. Ghidra decodes the following data as code, hence the bad-instruction warnings. The `0x00200000` words after it are the 2MB RAM size, read by `stup1` @ `0x80012670`. The startup calls `InitHeap` with `a0` ≈ `0x8005da44`. Heap starts at `0x8005da44`.
- **Confirmed:** entry point `start` = `0x8001262c` (PsyQ `__SN_ENTRY_POINT`). It zeroes BSS **`0x80059b40`–`0x8005da3f` (size `0x3f00`)**, then `stup1` sets up the stack from the 2MB value and calls `InitHeap`, then `stup0` calls `main`. The file image's last `0x4c0` bytes (`0x80059b40`–`0x80059fff`) are sector padding overlapping BSS. The first BSS variable is the `DR_MODE[2]` at `0x80059b40`. Initialized data ends just before (e.g. `ROCK_NEO` string at `0x80059b24`). `__main` (`0x80012624`) is empty (`jr ra`). Header `pc0` (offset `0x10`) = `0x8001262c`, matching `start` (**confirmed**). Done: split `CODE` at `0x80059b40`, marked the upper piece (`0x4c0` bytes) uninitialized, and merged it into `RAM`. The padding at file offsets `0x4a340`–`0x4a7ff` is all zeros (**confirmed**).
- **Confirmed:** read-only data comes **first**: `.rodata` = `0x80010000`–`0x800107e7` (switch tables, incl. `switchD_800111cc` at `0x80010000`, plus PsyQ Spu strings and tables). `.text` = `0x800107e8`–`0x8001d3b3`, starting with `main`, so Capcom's own object is linked first. splat `create_config` guessed the code start as `0x80010768`; fixed to file offset `0xFE8`. The last function is `FUN_8001d2e4`, ending just before the build-timestamp string at `0x8001d3b4`. Data follows (`g_screenWidths`, function tables, images). Several Spu library functions end in `j` (tail calls). To do (optional): sweep for `08 00 e0 03` above `0x8001d3b4`.
- **Confirmed:** no gp-relative accesses anywhere after startup, including PsyQ library code. The whole shim was built with `-G0` (matching build must use it). `gp` is set but unused, so `.sdata` is not applicable. The `ROCK_NEO` string at `gp + 0x10` is ordinary data. To do: repeat this test for `ROCK_NEO.EXE`.
- **Confirmed:** 602 functions in Ghidra vs 292 `jr ra` from the scan (the scan undercounts about 2×). 561 matched as PsyQ library (93%), 31 unnamed `FUN_`, ~10 named manually. So Capcom's own code is **at most ~41 functions**; some `FUN_` may be unmatched library code (e.g. `FUN_80011c84`). **Suspected:** the undercount comes from BIOS call stubs (`li t2,0xa0/0xb0/0xc0; jr t2; li t1,N`), which have no `jr ra`, plus tail calls. To do: check `LoadExec`'s body. Implication: `ROCK_NEO.EXE` (also linked with PsyQ) will be undercounted too. `ST*.BIN` overlay counts are probably closer to accurate.
- **Confirmed:** 6 switch statements (Symbol Tree → Namespaces, `switchD_<addr>`). `switchD_800111cc` has cases 0–5 + default; **suspected** to be the command-queue runner.
- **Shim recon exit criteria: met.**
- **Shim layout:** `.rodata` `0x80010000`–`0x800107e7` · `.text` `0x800107e8`–`0x8001d3b3` · data `0x8001d3b4`–`0x80059b3f` (`.rdata`/`.data` split left for splat) · BSS `0x80059b40`–`0x8005da3f` · heap from `0x8005da44`.
- Startup (`start`, `stup1`, `stup0`) is PsyQ `2MBYTE.OBJ` library code. Left as-is, not decompiled.
- **Confirmed:** `FUN_80011f88(u_char)` = `DrawFadeImage(brightness)`, the draw half of the cut warning screen. It uses `g_bufferIndex` to pick this frame's 80 `SPRT`s and 5 `DR_MODE`s. For each strip it sets 16 sprites' RGB to the brightness and `addPrim`s them, then `addPrim`s the strip's `DR_MODE` (drawn first). The two `SPRT[80]` arrays are one `[2][80]` array, and the `DR_MODE`s one `[2][5]`.
- Renamed: `DrawFadeImage` → `DrawCopyrightWarning`. Sprites typed `SPRT[2][80]` (`0x80059c78`), draw modes `DR_MODE[2][5]` (`0x8005a8f8`).
- **Confirmed (Listing):** `DrawCopyrightWarning`'s `addPrim` really does a double dereference: three loads (`g_curBuffer`, `+0x70`, then through that value). Screen 3's `addPrim` does two. Offset `0x70` is still the inline `ot[8]` (per `InitDisplayBuffer`).
- **Confirmed (mechanism) / suspected (exact source):** the source passes `ot[0]`'s value instead of its address, e.g. `addPrim(cdb->ot[0], p)` vs screen 3's `addPrim(cdb->ot, p)`. It works because `ClearOTag` links each entry to the next, so `ot[0]` holds `&ot[1]` (24-bit; low addresses mirror RAM). The warning's primitives land in slot 1. Matters for matching: the C must reproduce the third load.
- **Confirmed (PCSX-Redux):** during the warning screen, buffer 0's `ot[0]` (`0x8005b618`) = `0x0005b61c` (`&ot[1]`), and `ot[1]` = `0x0005a928` = `&DR_MODE[0][4]` (last primitive added). The warning draws in slot 1. `ot[2]`–`ot[6]` chain forward (`ClearOTag`). **Open:** `ot[7]` = `0x0004814c`, so something else is linked into the last slot each frame.
- **Confirmed (PCSX-Redux):** during the video the word at `0x80059c50` reads `0x00000102` (index 2, state 1).
- To do (optional): play screen 0 with a write breakpoint on `0x80059c50`. Reboot, let `InitIntro`'s store complete, set the byte to 0, resume. **Suspected:** init's `SetupDisplay` call at `0x80010984` uses mode 1 (640 wide) for this screen.
- Note: emulator memory views use physical addresses. `0x80xxxxxx` (and `0xa0xxxxxx`) → `0x00xxxxxx`. Scratchpad `0x1f800000` is unchanged.
- Named: `FUN_800125e8` → `RunIntroSequence`, screen 0 → `Screen_FadeImage`, screen 3 → `Screen_LaunchGame`. `DAT_80059c50` → `g_screenIndex`, `DAT_80059c51` → `g_screenState`.
- [ ] Type `g_screenFuncs` as `ScreenFunc *[4]` (`typedef void (*ScreenFunc)(void)`). Identify `FUN_80011d5c`, `FUN_80011d8c`, `FUN_80011f88`.
- [x] Retyped `0x8005a970` as `SPRT[2]`.
- [ ] Retype `0x80059b40` as `DR_MODE[2]`. Rename `DAT_80059c51` → `g_loadState`. Identify `FUN_8001b6e8`.
- **Confirmed:** `FUN_80010ac4(DisplayBuffer *buf)` = `InitDisplayBuffer` (retyped; decompiler output matches field-for-field). It calls `ClearOTag(buf->ot, 8)`, sets `disp.screen.y = 0`, `draw.dtd = 0`, `draw.dfe = 0`, `draw.isbg = 1`, and background RGB = 0,0,0 (clear to black, no dithering). Offsets derived from the PsyQ `DISPENV`/`DRAWENV` layouts. `DRAWENV` (0x5c bytes at 0x14) ends exactly at `ot` (0x70), consistent with the struct.
- **Confirmed:** uses the scratchpad (fast on-chip RAM at `0x1F800000`). `0x1f800000` holds the current buffer index (toggles 0/1). `0x1f800001` is compared against the frame counter, so it's likely the number of vsyncs to wait per frame.
- **Suspected:** `DAT_80059bc0` is a vsync counter, incremented by a `VSyncCallback` handler (probably registered in `FUN_800108ec`).
- **Suspected:** the shim draws something simple, such as a logo or loading screen, before handing off. An 8-entry ordering table is far too small for the full 3D game. The loop never exits because the handoff (e.g. `LoadExec`) never returns. It replaces the running program.

### Analysis issues

- `0x800126d8`: "Bad Instruction / unable to resolve constructor." Ghidra created a function over `2MBYTE.OBJ` data. With 0 references, it's data, not code. **Fixed:** function deleted, bytes defined as `dword`.

## Exit criteria: ready for splat

Recon is done for an executable when splat has what it needs to produce a byte-identical rebuild from assembly. Naming and struct work are *not* required. They happen progressively during decompilation.

| | SLUS_006.03 | ROCK_NEO.EXE | Overlays |
|---|---|---|---|
| Header fields (load address, entry, sizes) | [ ] | [ ] | — |
| `gp` value | [x] | [ ] | — |
| Rough code / data / BSS boundaries | [ ] | [ ] | [ ] |
| PsyQ library functions identified | [ ] | [ ] | — |
| Which files are code, and their load addresses | — | [ ] | [ ] |

Compiler identification (PsyQ version → GCC version and flags) isn't needed for the splat step, since splat only assembles. It's needed for the m2c step after it.

## Open questions

- [ ] Entry point address from the EXE header
- [ ] Address of `main`
- [ ] Does `main` load and execute `ROCK_NEO.EXE`? Check `Defined Strings` for `ROCK_NEO` and its cross-references.
- [ ] PsyQ version (Edit → Options → Program Information). **Suspected 4.0:** the Data Type Manager shows types tagged `psyq400`, and the loader imported headers `LIBCD.H`, `LIBETC.H`, `LIBGPU.H`, `LIBGS.H`, `LIBGTE.H`, `LIBPRESS.H`, `LIBSPU.H`, `TYPES.H`.
- [ ] Total function count, and how many are PsyQ-signature matches
- [ ] Meaning of the loader's `_B4` suffix on `2MBYTE_OBJ_B4`
- [ ] `2MBYTE.OBJ` holds two `0x00200000` words. Expected layout is RAM size plus a smaller stack size. Which is which, and why is the second value also 2 MB?

## Build: SLUS_006.03

- **Confirmed:** byte-identical rebuild from splat assembly (SHA-1 `888039c514ae2349db9d1b28892c943e2dc92739`). splat 0.50.1 / spimdisasm 1.42.4, GNU binutils 2.38 (`mips-linux-gnu`), WSL Ubuntu. Script: `tools/build.sh`.
- Assembler flags: `-EL -march=r3000 -mtune=r3000 -no-pad-sections -G0 -Iinclude`. Objects at `build/asm/<name>.o` (as named in the linker script).
- yaml fixes vs `create_config`: code start `0xF68` → `0xFE8` (rodata ends at `main`), and `ld_align_section_vram_end: False` / `ld_align_segment_vram_end: False`. The default `ALIGN(., 16)` after each section added 8+4+4 bytes (code shifted 8, file 16 bytes too long). `SUBALIGN(2)` was already present and correct.
- splat hint: rodata file split at `0xF6C` (vram `0x8001076c`, start of SpuSetCommonAttr's tables). Not yet applied.
- **Done:** `symbol_addrs.txt` exported from Ghidra (`tools/ghidra/ExportSplatSymbols.java`): 569 functions + globals. GTEMAC pseudo-addresses excluded. Addresses below `0x80000000` (hardware registers, scratchpad) tagged `absolute:True` and defined for `ld` via `build/absolute_syms.ld` (generated in `build.sh`). Duplicate `memclr` (`0x800130d8`, `0x80013380`); the second is left unnamed.
- **Done:** BSS. `main` segment has `bss_size: 0x3f00`. The last subsegment is `{ start: 0x4A340, type: bss, name: 4A340, vram: 0x80059B40 }`: zero file bytes, so splat infers size `0x3f00`. The explicit `vram` was needed; without it no `.s` was generated. Do not also put `bss_size` on the subsegment (hard error when inferable). The file's padding is a separate top-level `[0x4A340, bin, sector_padding]` segment; `build.sh` wraps `assets/*.bin` into objects with `objcopy -I binary`. `ld_bss_is_noload: True`. ELF: `.main` `0x49b40` (`0x80010000`–`0x80059b3f`), `.main_bss` NOLOAD `0x3f00` (`0x80059b40`–`0x8005da3f`), `.sector_padding` `0x4c0` at file `0x4a340`. MATCH. Last BSS label `D_8005B8AC` is a single `0x2194`-byte block.
- **Done:** rodata split at `0xF6C` (vram `0x8001076c`, SpuSetCommonAttr's object).
- **Open (harmless):** `missing .end` warning at `stup0`. The function ends with `break`, so the disassembler absorbs the following `0x00200000` words. Fix later with `size:0xC` for `stup0` in a hand-maintained symbols file.
- Not yet: further rodata/data object splits.

## Compiler identification

- Probe 1: `DequeueCommand` on decomp.me (maspsx, `-O2 -G0`). gcc 2.6.0 through 2.7.2-psx produce identical output and are the closest. 2.8.x and newer get progressively worse. **Suspected:** the GCC ≤2.7.2 family (consistent with PsyQ 4.0). This probe can't separate 2.6.x from 2.7.2; needs a second probe (switch, constant multiply, or more complex loop).
- **Suspected:** `Command` = `{ int type; CommandArgs args; }` with `CommandArgs = { int arg1; int arg2; short arg3; }` (12 bytes). The target copies `type` alone, then the 12-byte args as one block (3 `lw` + 3 `sw`). Possibly a union of per-command-type args in the original.
- Best so far: `while (p->type != 0) { p->type = p[1].type; p->args = p[1].args; p++; }`, instruction-for-instruction aligned. Remaining: the loop pointer is based at `p+4` (target `p+0xc`), the `p++` is scheduled after the stores (target before), and register numbering. Candidate for decomp-permuter if source variants don't close it.
- `DequeueCommand` **parked** as non-matching (score 530 with gcc 2.7.2). An index-based loop scored far worse (<25%), so the pointer loop is the right shape. Flags made no difference: `-mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker`, `-f[no-]schedule-insns`, `-O1`. Remaining diff (loop-pointer base, `p++` placement, registers) left for decomp-permuter.
- `QueuePlayMovie` **matches** (decomp.me, gcc 2.7.2 `-O2 -G0`; the only diff is `5` vs `0x5` immediate formatting). Confirms `Command` offsets: `type` 0x0, int args 0x4/0x8, short at 0xc (`sh`). Doesn't distinguish nested vs flat args.
- **Strongly suspected toolchain: gcc 2.7.2 + ASPSX 2.56** (decomp.me preset `PSYQ4.0`, `-O2 -G0`). `QueuePlayMovie` matches 100% in objdiff under it. Plain gcc 2.7.2 with default maspsx emitted `ori v1,zero,5` for `li` where the original has `addiu v1,zero,5`, so the assembler version matters. Consistent with the PsyQ 4.0 libraries and with another PSX project's `--aspsx-version=2.56`. Local pipeline: `cc1` (gcc-2.7.2-psx) → `maspsx --aspsx-version=2.56` → `mips-linux-gnu-as`. Confirm with more matches.
- `DequeueCommand` unchanged under `PSYQ4.0` (expected: its remaining diffs are compiler-side, not assembler).
- Lesson: decomp.me's Compilation tab normalizes pseudo-instructions (`li`). Use **objdiff** for the real byte-level score.
- `InitDisplayBuffer` **matches** under `PSYQ4.0` (field stores in source order; confirms `DisplayBuffer` / `DRAWENV` / `DISPENV` offsets). Second match for gcc 2.7.2 + ASPSX 2.56.
- Plan: headers by subsystem (`include/common.h`, `include/psyq/libgpu.h` with self-written declarations, `include/display.h`, `include/cmd.h`). Generate `ctx.c` with `cpp -P -Iinclude` for decomp.me and m2c rather than hand-maintaining one file.
- `SetupDisplay` **matches** under `PSYQ4.0`, written with `g_screenWidths[mode]` in each of the four calls. Confirms the reload theory: the address is computed once, the value is reloaded after every call. Third match for gcc 2.7.2 + ASPSX 2.56.
- decomp.me tally (shim): matched `QueuePlayMovie`, `InitDisplayBuffer`, `SetupDisplay`. Parked `DequeueCommand`.

## Build: C pipeline (shim)

- **Confirmed:** MATCH with Capcom code as a C file. yaml: `[0x800, .rodata, main]` (jump table `0x800`–`0x818`, migrated into `func_80011194.s`), `[0x818, rodata, 818]`, `[0xF6C, rodata, F6C]`, `[0xFE8, c, main]` (`main` … `RunIntroSequence`, `0x800107e8`–`0x80012623`), `[0x2E24, asm, 2E24]` (PsyQ from `__main`). `include_asm_macro_style: maspsx_hack`. `include/common.h` must `#include "include_asm.h"` (splat's generated `main.c` includes `common.h`).
- Toolchain (`tools/cc.sh`): `cpp -P -undef -nostdinc` → gcc-2.7.2-psx `cc1 -quiet -O2 -G0` → `maspsx --aspsx-version=2.56 --expand-div` → `mips-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`. Pinned in `tools/fetch_tools.sh`: old-gcc 0.17 (sha256 `500a459b…`), maspsx `4ffa8b51`, m2c `c632946b`. The cc1 banner reports defaults `-mgas -msoft-float`, R3000, ISA 1, **-G 8** (so `-G0` must be passed).
- `test/smoke.c` (`QueuePlayMovie`) compiles locally to the same 12 instructions as the PSYQ4.0 match, including `addiu v1,zero,5`.
- `symbol_addrs_manual.txt`: hand-maintained overrides; the exporter skips these names. `stup0 size:0xC` cleared the `missing .end` warning.
- **Open:** splat hint "rodata `818` may belong to `2E24`" (`v_wait` → `D_80010018`). Root cause: `2E24` lumps all PsyQ objects together. Fix by splitting it into per-object `asm` subsegments (names from Ghidra's `Possible X.OBJ/...` comments), each paired with its own `.rodata`.
- **Confirmed:** banked `SetupDisplay`, `InitDisplayBuffer`, `QueuePlayMovie` as C in `src/main.c` (includes `display.h`, `cmd.h`). Build MATCH. Negative test: `type = 6` in `QueuePlayMovie` → MISMATCH at file byte 9573 (offset `0x2564` = vram `0x80011d64`, the `li v1,5` immediate). The build verifies the C. splat auto-writes empty functions as C (e.g. `func_800110E4`).