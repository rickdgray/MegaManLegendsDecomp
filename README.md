# Mega Man Legends Decompilation

An WIP decompilation of **Mega Man Legends** (PlayStation, USA).

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
- [x] Recon: code/data boundaries, PsyQ version (`SLUS_006.03`, `ROCK_NEO.EXE`); the 44 code overlays (`ST*`, `ARM*R`, `SUPPORT`) mapped into functions (not yet split or built)
- [x] Split with splat; rebuild matches original byte-for-byte (`SLUS_006.03` and `ROCK_NEO.EXE` **match**)
- [ ] Decompilation (m2c, permuter, agent-assisted batches): every `SLUS_006.03` function is matched; `ROCK_NEO.EXE` is split into Capcom's source files, all of them C, with the functions not yet decompiled still included as assembly. `tools/progress.py` and `functions.csv` have the numbers
- [ ] Naming and documentation

## Code style

Naming and type conventions follow Capcom's own style, as seen in fragments of the game's [original source that shipped on the Japanese release (`ST1E.BIN`)](https://tcrf.net/Mega_Man_Legends/Source_Code). That covers `Capitalized_snake_case` globals, `lower_snake_case` statics, `ALL_CAPS` types such as `PL_WORK`, `_tbl` tables, `routine_N` state fields, and the `uint8`/`sint32` type names. Where the original's real name for something is known, it's used.

Formatting is modern (Allman braces, always-braced blocks, typedefs for function pointers), since formatting never affects the compiled output. All C in this repository is reconstructed from the binary; no original source code is included.

## Setup

### 1. Rip and verify the disc

Rip the disc to BIN/CUE and verify each track's hash against the Redump entry above. Place the image in `disc/image/`.

### 2. Set up the environment

In WSL Ubuntu, install the MIPS binutils and clang-format, create the Python venv, and fetch the pinned tools (`fetch_tools.sh` prints the extra `pip install` lines for m2c and asm-differ):

```bash
sudo apt install binutils-mips-linux-gnu clang-format-15
python3 -m venv .venv
.venv/bin/pip install "splat64[mips]==0.50.1" spimdisasm==1.42.4
./tools/fetch_tools.sh
```

Also install `dumpsxiso` from [mkpsxiso](https://github.com/Lameguy64/mkpsxiso); the Windows `dumpsxiso.exe` works from WSL (`DUMPSXISO=dumpsxiso.exe`).

### 3. Extract the game data

Once, in a fresh clone:

```bash
make extract        # tools/extract.sh
```

This extracts Track 1's filesystem into `disc/extracted/` (the two executables and `CDDATA/`, plus the layout XML `mml.xml` used to rebuild the disc), writes each overlay's code chunk from the `CDDATA/DAT/*.BIN` archives to `disc/overlays/`, and checks every hash against the `sha1:` line of its yaml: both executables, each overlay, and the archives holding a duplicate of an overlay's chunk. A mismatch means the dump differs from Redump.

### 4. Build

Split and build every target (the two executables and the 44 overlays); each prints MATCH or MISMATCH:

```bash
make                # tools/split.sh all, then tools/build.sh all
```

Every script also takes one target or a group (`all`, `executables`, `overlays`): `./tools/build.sh rock_neo.exe`, `./tools/rebuild.sh overlays`. After the first split, `./tools/build.sh <target>` rebuilds without re-splitting.

The toolchain and its setup are documented in [`notes/toolchain.md`](notes/toolchain.md).

## Repository layout

```
├── CLAUDE.md                  # rules and patterns for writing matching C (read by agents and people)
├── config/<target>/           # per target: <target>.yaml (splat config, with its SHA-1) and
│                              #   symbol_addrs.txt (symbol registry)
├── functions.csv              # every function with its status (decompiled, matched, reviewed)
├── reviewed.txt               # functions a person has reviewed (tools/review.py)
├── diff_settings.py           # asm-differ settings (tools/diff.sh)
├── mml.xml                    # mkpsxiso disc layout (metadata only)
├── src/<target>/              # decompiled C
├── include/                   # headers shared by both executables; include/<target>/ for the rest
├── notes/                     # findings and research notes (start with notes/README.md)
├── tools/                     # build, diff and helper scripts
├── disc/                      # (gitignored) your disc image and extracted files
├── asm/, assets/, build/, expected/   # (gitignored) generated from disc/
└── logs/, permuter/           # (gitignored) batch-run logs and permuter work
```

## Tools

| Tool | Version | Purpose |
|---|---|---|
| [Ghidra](https://github.com/NationalSecurityAgency/ghidra) | 12.1.4 | Analysis and decompilation reference |
| [ghidra_psx_ldr](https://github.com/lab313ru/ghidra_psx_ldr) | 2026.10.03 | PS-X EXE loader and PsyQ signatures |
| [mkpsxiso](https://github.com/Lameguy64/mkpsxiso) | | Disc extraction and rebuilding (`tools/Compare-Track1.ps1` compares a rebuilt Track 1 with the original) |

The matching toolchain (gcc 2.7.2-psx, maspsx, splat, m2c, asm-differ, decomp-permuter) is pinned in `tools/fetch_tools.sh`; see [`notes/toolchain.md`](notes/toolchain.md).

## Legal

This project is not affiliated with or endorsed by Capcom or Sony. Mega Man Legends is a trademark of Capcom. No copyrighted game code or assets are distributed in this repository.
