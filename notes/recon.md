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
- **Confirmed:** the buffers live in uninitialized memory (no bytes in the file; filled at runtime). `FUN_800108ec` and `FUN_800109f8` write into buffer fields (`draw.clip`, `disp.disp`). **Suspected:** this is display/draw environment setup, e.g. `SetDefDispEnv` / `SetDefDrawEnv`.
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