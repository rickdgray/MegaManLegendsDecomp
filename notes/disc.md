# Disc

## Target

| | |
|---|---|
| Title | Mega Man Legends (USA) |
| Serial | SLUS-00603 |
| Redump | <http://redump.org/disc/2773/> |
| Track 1 SHA-1 | `904489e2e8d06e1c44e60d8925329f9472b2d037` |
| Track 2 SHA-1 | `d9f92af296360772e62caa4cb276de3fa74f5538` |
| Boot executable SHA-1 | see `checksums.sha1` |

## Layout

- **Confirmed:** `SYSTEM.CNF` boots `cdrom:\SLUS_006.03;1`, a small shim that shows the intro and
  then `LoadExec`s `cdrom:\ROCK_NEO.EXE;1`, the main game (see [shim.md](shim.md)).
- **Confirmed:** the data track round-trips: `dumpsxiso` extraction plus a `mkpsxiso` rebuild from
  `layout/` reproduces Redump Track 1 exactly (207,145 sectors, 0 differences).
- `CDDATA/DAT/*.BIN`: chunk archives holding stage code and data (format below).
- `CDDATA/STR/CAPCOM20.STR`: the intro FMV, played by the shim.
- `CDDATA/XA/*.XA`: streamed XA audio.
- Track 2: CD audio.

## The game's file table

`SLUS_006.03` and `ROCK_NEO.EXE` carries a table of every file on the disc, `Cd_file_tbl`
(248 entries of 12 bytes: start sector, size, a third word). Files are addressed by index rather
than by name:

| Index | File |
|---|---|
| 0–2 | `SLUS_006.03`, `ROCK_NEO.EXE`, `SYSTEM.CNF` (third word = the file's first 4 bytes: `PS-X`, `BOOT`) |
| 3–237 | `CDDATA` files (third word 0 for ordinary data); `0xD0` = `CAPCOM20.STR` (third word `0x80420100`) |
| 238–246 | XA audio (third word `0x04640001` or `0x01640001`) |
| 247 | **Track 2, CD audio**: sector 207,295 (= 207,145 + the 150-sector pregap), 37,044,000 bytes (15,750 sectors of 2,352, 3:30) |

- **Confirmed:** entries 0–2 match the files' sizes exactly; entry 247 matches the audio track.
- **Unknown:** the third word for movie and XA entries (flags? interleave/channel settings?). Sizes
  of mixed-mode files (STR, XA) don't follow 2048-byte sectors; their unit is unconfirmed.
- ROCK_NEO's `Cd_read_comb(id)` (per ChrisNonyminus/mml1) takes these indices.

## Code inventory

Counts of `jr ra` per file (`tools/Count-MipsFunctions.ps1`). 53 of 249 extracted files contain
code; 12,243 `jr ra` in total, about 10,764 after removing suspected duplicates.

| Group | `jr ra` | Share (deduplicated) |
|---|---|---|
| `SLUS_006.03` | 292 | 2.7% |
| `ROCK_NEO.EXE` | 1,630 | 15.1% |
| Stage files `ST*.BIN` (unique) | 8,708 | 80.9% |
| `SUPPORT.BIN`, `ARM*R.BIN` | 134 | 1.2% |

- **Confirmed:** the count **undercounts executables** about 2× (the shim has 602 functions vs. 292
  `jr ra`): BIOS call stubs (`li t2,0xa0; jr t2; li t1,N`) and tail calls have no `jr ra`. Overlay
  counts are probably closer, since the PsyQ library lives only in the executables.
- **Confirmed:** most code is in the stage files. Only top-level stage files (`ST03.BIN`, ...) have
  code; sub-area files (`ST04_00B.BIN`, ...) are data.
- **Suspected duplicates** (identical counts; `SUPPORT*` also identical sizes): `ST03`/`ST03B`,
  `ST04`/`ST04B`, `ST10`/`ST10B`, `ST11`/`ST11B`, `ST0C`/`ST0CB`/`ST0CC`, `SUPPORT`/`SUPPORT2`.
  Verify by hashing their code chunks.
- **Suspected:** `ARM*R.BIN` (4–18 functions each) are small code modules, perhaps per weapon.
  `ARM00L`/`ARM04L` have no code.

## Overlay chunk format

Source: ChrisNonyminus/mml1 (see [rock_neo.md](rock_neo.md)); **suspected** until verified here.

The `CDDATA/DAT/*.BIN` files are archives of chunks, with no archive-level header:

| Offset (in chunk) | Field |
|---|---|
| `0x0` | Type; `0` = code overlay, loaded into executable memory |
| `0x4` | Size of the contents |
| `0x8` | Unknown |
| `0xC` | Load address (code chunks) |
| `0x10`–`0x3F` | Unknown |
| `0x40`–`0x7FF` | Filename, null-terminated |
| `0x800`– | Contents; the next chunk starts at the next `0x800` boundary |

A stage file holds a code chunk (e.g. `progbin_r3_st08.bin`) plus data chunks
(`MAP_DATA/ST08_MAP.MDT`, `.IDX`, `SCR_DATA/ST08.STG`, `.HED`, `.HD2`).

## Load addresses

Source: ChrisNonyminus/mml1; **suspected** until verified.

| What | Address |
|---|---|
| Stage code (`progbin`) | `0x80100000` |
| SHL code | `0x800D8800` |
| SUPPORT code | `0x801D8000` |
| Stage `HED` | `0x8013A000` |
| `MSG` | `0x80153000` |
| Stage `IDX` | `0x8015C000` |
| Stage `MDT` | `0x80164000` |
| Stage `EBD` | `0x8016C000`, `0x80190000` |
| Stage `STG` | `0x80194000` |
| SUPPORT `EBD` / `STG` | `0x801F2000` / `0x801F6000` |

All stage code shares one region, so stage overlays overlap in memory.
