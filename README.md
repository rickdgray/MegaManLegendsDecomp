# Mega Man Legends Decompilation

An experimental, work-in-progress decompilation of **Mega Man Legends** (PlayStation, USA).

The long-term goal is a *matching* decompilation: C source that compiles to a byte-identical copy of the original executable, as a foundation for future ports to other platforms.

> **This repository contains no game data.** You must supply your own legally obtained copy of the game. Disc images, extracted files, and anything generated from them are excluded from version control.

## Target

| | |
|---|---|
| Title | Mega Man Legends (USA) |
| Serial | SLUS-00603 |
| Executables | `SLUS_006.03` (boot shim), `ROCK_NEO.EXE` (main game) |
| Redump entry | <http://redump.org/disc/2773/> |
| Track 1 SHA-1 | `904489e2e8d06e1c44e60d8925329f9472b2d037` |
| Track 2 SHA-1 | `d9f92af296360772e62caa4cb276de3fa74f5538` |

Other regions and disc revisions are not supported.

## Status

🛠️ **Decompiling.** Both executables rebuild byte-for-byte; C is replacing the assembly one source file at a time.

- [x] Verified clean disc image against Redump
- [x] Extracted filesystem and confirmed boot executable
- [x] Recon: code/data boundaries, PsyQ version (`SLUS_006.03`, `ROCK_NEO.EXE`); overlays not yet
- [x] Split with splat; rebuild matches original byte-for-byte (`SLUS_006.03` and `ROCK_NEO.EXE` **match**)
- [ ] Decompilation (m2c, permuter, agent-assisted batches): `SLUS_006.03` all in C except 5 parked functions; `ROCK_NEO.EXE` split into Capcom's source files, its `cd` file in C. `tools/progress.py` reports the numbers
- [ ] Naming and documentation

## Code style

Naming and type conventions follow Capcom's own style, as seen in fragments of the game's [original source that shipped on the Japanese release (`ST1E.BIN`)](https://tcrf.net/Mega_Man_Legends/Source_Code). That covers `Capitalized_snake_case` globals, `lower_snake_case` statics, `ALL_CAPS` types such as `PL_WORK`, `_tbl` tables, `routine_N` state fields, and the `uint8`/`sint32` type names. Where the original's real name for something is known, it's used.

Formatting is modern (Allman braces, always-braced blocks, typedefs for function pointers), since formatting never affects the compiled output. All C in this repository is reconstructed from the binary; no original source code is included.

## Setup

### 1. Rip and verify the disc

Rip the disc to BIN/CUE and verify each track's hash against the Redump entry above. Place the image in `disc/image/`.

### 2. Extract the filesystem

Extract Track 1 with `dumpsxiso` from [mkpsxiso](https://github.com/Lameguy64/mkpsxiso) into `disc/extracted/`:

```powershell
dumpsxiso -x .\disc\extracted\ -s .\layout\mml.xml ".\disc\image\Mega Man Legends (USA).cue"
```

This also writes the layout XML (`-s`) used to rebuild the disc.

### 3. Verify the executable

```bash
sha1sum -c checksums.sha1
```

### 4. Build

In WSL Ubuntu, fetch the pinned tools and build each target; each build prints MATCH or MISMATCH:

```bash
./tools/fetch_tools.sh
./tools/rebuild.sh slus_006.03
./tools/rebuild.sh rock_neo.exe
```

The toolchain and its setup are documented in [`notes/toolchain.md`](notes/toolchain.md).

## Repository layout

```
├── CLAUDE.md                  # rules and patterns for writing matching C (read by agents and people)
├── checksums.sha1             # SHA-1 of the original executable
├── <target>.yaml              # splat config per executable (slus_006.03, rock_neo.exe)
├── symbol_addrs_<target>.txt  # symbol registry per executable
├── src/<target>/              # decompiled C
├── include/                   # headers shared by both executables; include/<target>/ for the rest
├── layout/                    # mkpsxiso disc layout (metadata only)
├── notes/                     # findings and research notes (start with notes/README.md)
├── tools/                     # build, diff and helper scripts
├── disc/                      # (gitignored) your disc image and extracted files
└── asm/, assets/, build/, expected/   # (gitignored) generated from disc/
```

## Tools

| Tool | Version | Purpose |
|---|---|---|
| [Ghidra](https://github.com/NationalSecurityAgency/ghidra) | 12.1.4 | Analysis and decompilation reference |
| [ghidra_psx_ldr](https://github.com/lab313ru/ghidra_psx_ldr) | 2026.10.03 | PS-X EXE loader and PsyQ signatures |
| [mkpsxiso](https://github.com/Lameguy64/mkpsxiso) | | Disc extraction and rebuilding |

The matching toolchain (gcc 2.7.2-psx, maspsx, splat, m2c, asm-differ, decomp-permuter) is pinned in `tools/fetch_tools.sh`; see [`notes/toolchain.md`](notes/toolchain.md).

## Legal

This project is not affiliated with or endorsed by Capcom or Sony. Mega Man Legends is a trademark of Capcom. No copyrighted game code or assets are distributed in this repository.
