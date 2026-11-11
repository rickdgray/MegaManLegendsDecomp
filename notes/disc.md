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

`SLUS_006.03` and `ROCK_NEO.EXE` each carry the same table of every file on the disc,
`Cd_file_tbl` (248 entries of 12 bytes: start sector, size, and head, the value the
file must begin with (checked on reads).; shim `0x8001D3DC`, ROCK_NEO `0x80082CD0`).
Files are addressed by index rather than by name:

| Index | File |
|---|---|
| 0–2 | `SLUS_006.03`, `ROCK_NEO.EXE`, `SYSTEM.CNF` (head = the file's first 4 bytes: `PS-X`, `BOOT`) |
| 3–237 | `CDDATA` files (head 0 for ordinary data); `0xD0` = `CAPCOM20.STR` (head `0x80420100`) |
| 238–246 | XA audio (head `0x04640001` or `0x01640001`) |
| 247 | **Track 2, CD audio**: sector 207,295 (= 207,145 + the 150-sector pregap), 37,044,000 bytes (15,750 sectors of 2,352, 3:30) |

- **Confirmed:** entries 0–2 match the files' sizes exactly; entry 247 matches the audio track.
- **Confirmed:** commands take these indices: the shim's movie command (`0xD0`), and ROCK_NEO's
  `Cd_read_comb(id)` and other queue functions ([rock_neo.md](rock_neo.md), "CD module").

## Code inventory

Counts of `jr ra` per file (from a PowerShell script, `Count-MipsFunctions.ps1`, since removed from `tools/`). 53 of 249 extracted files contain
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
- **Confirmed duplicates** (identical code chunks, by SHA-1): `ST03`/`ST03B`, `ST04`/`ST04B`,
  `ST0C`/`ST0CB`/`ST0CC`, `ST10`/`ST10B`, `ST11`/`ST11B`, `SUPPORT`/`SUPPORT2`. See "Code overlays".
- **Confirmed:** `ARM*R.BIN` hold the SHL modules (`r3_shl02.bin` ... `r3_shl0d.bin`, 4–18
  functions each), loaded at `0x800D8800`; the rest of each file is `PLBIN\PL00R*.PBD` data and a
  sound `.vab`. Perhaps one per weapon. `ARM00L`/`ARM04L` have no code.

## Code overlays

`tools/extract_overlays.py` writes each archive's code chunk to `disc/overlays/<ARCHIVE>.BIN`
(the contents only, `size` bytes) and prints the table below with SHA-1s (`--tsv FILE` for a
file). **Confirmed:** every file with code has exactly one code chunk, always first in the
archive, type 0, named `progbin\r3_*.bin`. No other chunk type contains a `jr ra`.

- **51 code chunks, 44 distinct.** 10,321 `jr ra` in all, **8,842 in the distinct chunks**. That
  equals the stage + SUPPORT/ARM total in "Code inventory" (8,708 + 134), so the earlier
  deduplication was right. Overlays have no BIOS stubs and GCC 2.7 does no tail calls, so this is
  close to the real overlay function count, before function-level duplicates.
- **Not near-copies:** `ST0C`/`ST0D` and `ST11`/`ST12` (equal `jr ra` counts) share only a
  quarter to a third of their functions; see [overlays.md](overlays.md), "Duplicates".
- `ST1E` (103 `jr ra`, `0x9918` bytes) is the overlay whose source is on TCRF.

| Archive | Chunk | Load | Size | `jr ra` | Same as |
|---|---|---|---|---|---|
| `ARM01R` | `r3_shl04.bin` | `0x800D8800` | `0x44C` | 6 | |
| `ARM02R` | `r3_shl02.bin` | `0x800D8800` | `0x81C` | 5 | |
| `ARM03R` | `r3_shl03.bin` | `0x800D8800` | `0x63C` | 6 | |
| `ARM05R` | `r3_shl05.bin` | `0x800D8800` | `0xE04` | 12 | |
| `ARM06R` | `r3_shl06.bin` | `0x800D8800` | `0x8D4` | 9 | |
| `ARM07R` | `r3_shl07.bin` | `0x800D8800` | `0x440` | 4 | |
| `ARM08R` | `r3_shl08.bin` | `0x800D8800` | `0x934` | 6 | |
| `ARM09R` | `r3_shl09.bin` | `0x800D8800` | `0xFF8` | 18 | |
| `ARM10R` | `r3_shl0d.bin` | `0x800D8800` | `0xABC` | 8 | |
| `ARM11R` | `r3_shl0c.bin` | `0x800D8800` | `0x8F4` | 6 | |
| `ARM12R` | `r3_shl0b.bin` | `0x800D8800` | `0x7A0` | 7 | |
| `ARM13R` | `r3_shl0a.bin` | `0x800D8800` | `0x758` | 5 | |
| `ST00` | `R3_ST00.BIN` | `0x80100000` | `0x22700` | 519 | |
| `ST01` | `R3_ST01.BIN` | `0x80100000` | `0x1B5C` | 20 | |
| `ST02` | `R3_ST02.BIN` | `0x80100000` | `0xA678` | 195 | |
| `ST03` | `R3_ST03.BIN` | `0x80100000` | `0x1CB70` | 340 | |
| `ST03B` | `R3_ST03.BIN` | `0x80100000` | `0x1CB70` | 340 | `ST03` |
| `ST04` | `R3_ST04.BIN` | `0x80100000` | `0x11DD8` | 235 | |
| `ST04B` | `R3_ST04.BIN` | `0x80100000` | `0x11DD8` | 235 | `ST04` |
| `ST05` | `R3_ST05.BIN` | `0x80100000` | `0x380C4` | 668 | |
| `ST06` | `r3_st06.bin` | `0x80100000` | `0x2BED0` | 597 | |
| `ST07` | `r3_st07.bin` | `0x80100000` | `0x8C40` | 143 | |
| `ST08` | `r3_st08.bin` | `0x80100000` | `0x1859C` | 311 | |
| `ST09` | `r3_st09.bin` | `0x80100000` | `0x1EAA0` | 335 | |
| `ST0A` | `r3_st0a.bin` | `0x80100000` | `0x1B61C` | 300 | |
| `ST0B` | `r3_st0b.bin` | `0x80100000` | `0x20400` | 433 | |
| `ST0C` | `r3_st0c.bin` | `0x80100000` | `0x129C0` | 219 | |
| `ST0CB` | `r3_st0c.bin` | `0x80100000` | `0x129C0` | 219 | `ST0C` |
| `ST0CC` | `r3_st0c.bin` | `0x80100000` | `0x129C0` | 219 | `ST0C` |
| `ST0D` | `r3_st0d.bin` | `0x80100000` | `0x124F0` | 219 | |
| `ST0E` | `r3_st0e.bin` | `0x80100000` | `0x1100C` | 283 | |
| `ST0F` | `r3_st0f.bin` | `0x80100000` | `0x61C0` | 127 | |
| `ST10` | `r3_st10.bin` | `0x80100000` | `0x14AC4` | 262 | |
| `ST10B` | `r3_st10.bin` | `0x80100000` | `0x14AC4` | 262 | `ST10` |
| `ST11` | `r3_st11.bin` | `0x80100000` | `0xE284` | 162 | |
| `ST11B` | `r3_st11.bin` | `0x80100000` | `0xE284` | 162 | `ST11` |
| `ST12` | `r3_st12.bin` | `0x80100000` | `0xE57C` | 162 | |
| `ST13` | `r3_st13.bin` | `0x80100000` | `0x18D5C` | 384 | |
| `ST14` | `r3_st14.bin` | `0x80100000` | `0x16300` | 316 | |
| `ST15` | `r3_st15.bin` | `0x80100000` | `0x8524` | 68 | |
| `ST16` | `r3_st16.bin` | `0x80100000` | `0xE05C` | 80 | |
| `ST17` | `r3_st17.bin` | `0x80100000` | `0x22BA0` | 402 | |
| `ST18` | `r3_st18.bin` | `0x80100000` | `0x78E4` | 60 | |
| `ST19` | `r3_st19.bin` | `0x80100000` | `0x1F4E4` | 415 | |
| `ST1A` | `r3_st1a.bin` | `0x80100000` | `0x397E4` | 722 | |
| `ST1B` | `r3_st1b.bin` | `0x80100000` | `0x13EC4` | 295 | |
| `ST1C` | `r3_st1c.bin` | `0x80100000` | `0x44D8` | 83 | |
| `ST1D` | `r3_st1d.bin` | `0x80100000` | `0x1A75C` | 250 | |
| `ST1E` | `r3_st1e.bin` | `0x80100000` | `0x9918` | 103 | |
| `SUPPORT` | `r3_sup.bin` | `0x801D8000` | `0x42AC` | 42 | |
| `SUPPORT2` | `r3_sup.bin` | `0x801D8000` | `0x42AC` | 42 | `SUPPORT` |

SHA-1s (of the chunk contents), one per distinct chunk:

```
a1e611c31b5a76324013bbc56e6dd4248226116a  ARM01R.BIN
69ccd56cfd21bbf8d08f83614e248958425dd8d1  ARM02R.BIN
096fb9b441fd9a017151d0c1a577d7721e579006  ARM03R.BIN
0b54c76c966f677c98f49e0f70bea02bab4d3639  ARM05R.BIN
5f1abbc01e1b2faaf759203cf6fd071372a6ff43  ARM06R.BIN
60be6f00303c581fddb25fe5ccab7ed23a644273  ARM07R.BIN
4b9021081a7ea8f57601a25120db9075a1f701bc  ARM08R.BIN
5d342a744b3c8758961034576c3a8adddc0481b0  ARM09R.BIN
7ba1a6244e1738cef9c30649a44bc76d32858caa  ARM10R.BIN
733a45f78af37904c3a0552218657e82396174d1  ARM11R.BIN
cb010b7a7aa5fbef3a2f10a6c2fd85bb00c9fb95  ARM12R.BIN
86c6390352bf31d46b524622e039fcd4741fed1e  ARM13R.BIN
b1cde1d7056c6569b2054ed7503e599f2626bef3  ST00.BIN
d05bdd8e104fb259a9fad844daba9c9af4816df2  ST01.BIN
1304a093115249dcd222af08f302f2360272c4e1  ST02.BIN
c160e9451415275ca42b3f48cd3b7aa5a197b539  ST03.BIN
bea1dd749bfc834037e228a41ed4c590d42553dc  ST04.BIN
ac44dc07b5bd4619a178d05a1a91138a4df77b36  ST05.BIN
8098ec65c7492974965187a493c792d042b8000e  ST06.BIN
485431a0fc45ddec13b2dcb6488bbbc90f8f86f8  ST07.BIN
658a999e11f9af390f0406cf5517ab85ca2fe435  ST08.BIN
621cbc76158dee9b27d8ca13c6e4910615d9d3a8  ST09.BIN
2bb985932e781ff0ac55af52271d1689eea72a49  ST0A.BIN
b89e961562cf4b7e95ffca87e88ecc7ef128fed4  ST0B.BIN
62cc94d8b51a6d8d12b64c573e07ae675fb22d0d  ST0C.BIN
9d2d44730bf670f63b1ac6956fefc23bd5ea51d9  ST0D.BIN
a3d0b31340935623f2490ba41f4a343518125f0d  ST0E.BIN
093217c18de3181213e42211343eb284b39097b8  ST0F.BIN
1af931163eed4211c8b4a989fa06214622c7a7f4  ST10.BIN
0873977ba055c210021ae5e0f674766627a71013  ST11.BIN
922ed469c7a9f8179b9192d604ba22a9d5462c73  ST12.BIN
59bfa292052784d8ac06d1efa29f804f4e435778  ST13.BIN
8d4b1ad0c65bbac60a91ba7d0ae4025acafe9d1b  ST14.BIN
4b89a735472962d078c4ca7983879b4c32b83477  ST15.BIN
f7e66f92aa96b37efa906acd126aabafde380e86  ST16.BIN
ebaa07e52be9d451739a15198c73245a5f46a495  ST17.BIN
8a914c28ce1b0bb7a3b7e07020465008992537c3  ST18.BIN
0d6788ac05bca574bf74369694465177644867b8  ST19.BIN
0e851436f59c5644d9d03f07426bf9723fcfa412  ST1A.BIN
5914dacde34a1ba79a1fb74b044f8faf2daf1f74  ST1B.BIN
50ee82b64e597e347c676eb60085348c05b8b0bd  ST1C.BIN
8971feb1030512464fe0d9fddcdeda237e651410  ST1D.BIN
837974b80886152717fcd5664f9960da31ebfd15  ST1E.BIN
e5f43a4f525c0788a4c790afcd308d5a8d5979a9  SUPPORT.BIN
```

## Overlay chunk format

Source: ChrisNonyminus/mml1 (see [rock_neo.md](rock_neo.md)); **confirmed** as the comb format. Note the packing tool's habit: a group's first header (seen with type 9) carries the size and sector count of the whole group, so a reader stepping by count skips the group, and the in-group entries each have their own header.

The `CDDATA/DAT/*.BIN` files are archives of chunks, with no archive-level header:

| Offset (in chunk) | Field |
|---|---|
| `0x0` | Type; `0` = code overlay, loaded into executable memory |
| `0x4` | Size of the contents |
| `0x8` | Sectors, header included: `1 + ceil(size / 0x800)` (**confirmed** for all 568 type-0 chunks) |
| `0xC` | Load address (type-0 chunks: code and stage data) |
| `0x10`–`0x3F` | Unknown |
| `0x40`–`0x7FF` | Filename, null-terminated |
| `0x800`– | Contents; the next chunk starts at the next `0x800` boundary |

A stage file holds a code chunk (e.g. `progbin_r3_st08.bin`) plus data chunks
(`MAP_DATA/ST08_MAP.MDT`, `.IDX`, `SCR_DATA/ST08.STG`, `.HED`, `.HD2`).

## Load addresses

**Confirmed** from the chunk headers (`0xC`) of every type-0 chunk; they match ChrisNonyminus/mml1.
PBD chunks (player data, in `ARM*R`) load at 19 different addresses in `0x800D9D00`–`0x800FF400`.

| What | Address |
|---|---|
| Stage code (`progbin`) | `0x80100000` |
| SHL code | `0x800D8800` |
| SUPPORT code | `0x801D8000` |
| Stage `HD2` (8 stages) | `0x80139F00` |
| Stage `HED` | `0x8013A000` |
| `MSG` | `0x80153000` (125 chunks); also `0x801F2000`, `0x801E4000` (2 each) |
| Stage `IDX` | `0x8015C000` |
| Stage `MDT` | `0x80164000` |
| Stage `EBD` | `0x8016C000`, `0x80190000` |
| Stage `STG` | `0x80194000` |
| SUPPORT `EBD` / `STG` | `0x801F2000` / `0x801F6000` |

All stage code shares one region, so stage overlays overlap in memory.
