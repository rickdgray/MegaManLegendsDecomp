# Mega Man Legends Decompilation

An experimental, work-in-progress decompilation of **Mega Man Legends** (PlayStation, USA).

The long-term goal is a *matching* decompilation: C source that compiles to a byte-identical copy of the original executable, as a foundation for future ports to other platforms.

> **This repository contains no game data.** You must supply your own legally obtained copy of the game. Disc images, extracted files, and anything generated from them are excluded from version control.

## Target

| | |
|---|---|
| Title | Mega Man Legends (USA) |
| Serial | SLUS-00603 |
| Executable | `SLUS_006.03` |
| Redump entry | <http://redump.org/disc/2773/> |
| Track 1 SHA-1 | `904489e2e8d06e1c44e60d8925329f9472b2d037` |
| Track 2 SHA-1 | `d9f92af296360772e62caa4cb276de3fa74f5538` |

Other regions and disc revisions are not supported.

## Status

🔍 **Recon.** Mapping the executable, PsyQ library usage, and overlays.

- [x] Verified clean disc image against Redump
- [x] Extracted filesystem and confirmed boot executable
- [ ] Recon: code/data boundaries, PsyQ version, overlay map (`SLUS_006.03` done; `ROCK_NEO.EXE` and overlays next)
- [ ] Split with splat; rebuild matches original byte-for-byte (`SLUS_006.03` **matches**)
- [ ] Decompilation passes (m2c, permuter, agent-assisted matching): local toolchain matching; first `SLUS_006.03` functions banked
- [ ] Naming and documentation

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

## Repository layout

```
├── checksums.sha1    # SHA-1 of the original executable
├── layout/           # mkpsxiso disc layout (metadata only)
├── notes/            # recon findings and research notes
├── symbols/          # function and data symbols
├── tools/            # helper scripts
└── disc/             # (gitignored) your disc image and extracted files
```

## Tools

| Tool | Version | Purpose |
|---|---|---|
| [Ghidra](https://github.com/NationalSecurityAgency/ghidra) | 12.1.4 | Analysis and decompilation reference |
| [ghidra_psx_ldr](https://github.com/lab313ru/ghidra_psx_ldr) | 2026.10.03 | PS-X EXE loader and PsyQ signatures |
| [mkpsxiso](https://github.com/Lameguy64/mkpsxiso) | | Disc extraction and rebuilding |

## Legal

This project is not affiliated with or endorsed by Capcom or Sony. Mega Man Legends is a trademark of Capcom. No copyrighted game code or assets are distributed in this repository.