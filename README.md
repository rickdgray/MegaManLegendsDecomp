# Mega Man Legends Decompilation

A matching decompilation of **Mega Man Legends** (PlayStation, Capcom, 1998), NTSC-U `SLUS-00603`,
and a native Linux port built from it.

"Matching" means the C in `src/` compiles with the original compiler back to the retail executables
**byte for byte**. The build checks this with SHA-1 against your own dump of the game; nothing is
counted as done unless the bytes are identical.

## Status

| Part | State |
|---|---|
| Boot program `SLUS_006.03` | 34 / 34 functions in C, rebuilds byte-identically |
| Main game `ROCK_NEO.EXE` | 1,132 / 1,132 functions in C, rebuilds byte-identically |
| Stage and weapon overlays (`CDDATA/DAT/*.BIN`) | 44 modules, 8,842 / 8,842 functions in C, all rebuild byte-identically |
| Native Linux port | playable: gamepad and keyboard, sound, movies, memory cards, settings, optional mods |

PsyQ library code (linked as-is) and Capcom's own hand-written assembly routines stay assembly.

Five functions match only with an artificial statement that steers the compiler. Each is marked
`// FAKE MATCH:` in the source; replacements with a more natural form are welcome.

## What you need

Your own copy of the game, dumped by you as BIN/CUE, matching Redump
[disc 2773](http://redump.org/disc/2773/):

| | SHA-1 |
|---|---|
| Track 1 | `904489e2e8d06e1c44e60d8925329f9472b2d037` |
| Track 2 | `d9f92af296360772e62caa4cb276de3fa74f5538` |

**This repository contains no game data**: no executables, overlays, textures, audio, text or
disassembly. Everything the build needs from the game is read from your disc at build time.

## Building

Arch Linux shown; elsewhere you need `mips-linux-gnu` (or `mipsel-linux-gnu`) binutils and
`dumpsxiso` from mkpsxiso.

```sh
yay -S mipsel-linux-gnu-binutils-minimal mkpsxiso-git uv
make setup             # pinned compiler, maspsx, splat, m2c, asm-differ in tools/vendor and .venv

mkdir -p disc/image && cp /path/to/"Mega Man Legends (USA)"* disc/image/
make extract           # unpacks the disc into disc/extracted/ and checks the executables

make                   # split and build both executables; each must print MATCH
make split-overlays    # the 44 overlay modules
make overlays          # each must print MATCH
```

Day to day, per target (`slus_006.03`, `rock_neo.exe`, `r3_st00`, ...):

| Command | |
|---|---|
| `./tools/split.sh <t>` | regenerate `asm/<t>/` and the linker script from `config/<t>/<t>.yaml` |
| `./tools/build.sh <t>` | build and compare with retail: prints MATCH or MISMATCH |
| `./tools/diff.sh <t> <func>` | one function's diff against the last matching build |
| `./tools/m2c.sh <t> <func>` | a first C draft of a function, for study |
| `./tools/rebuild.sh <t>` | split, build and refresh the diff reference (after a rename) |

## Playing the port

The port compiles the same C natively (as a 32-bit program, with the PS1's memory at its real
addresses) and runs it on SDL3. It reads your disc image at run time.

```sh
yay -S lib32-sdl3 cmake ninja
make extract           # once
make play              # builds what is missing and starts the game in a window
make install-desktop   # optional: an application-menu entry
```

- **Controls:** a gamepad maps by position (south/east/west/north = Cross/Circle/Square/Triangle,
  shoulders L1/R1, triggers L2/R2). Keyboard: arrows, X/C/Z/S = Cross/Circle/Square/Triangle,
  Q/W = L2/L1, E/R = R1/R2, Enter = Start, Right Shift = Select. F11 fullscreen, Esc quits.
- **Settings:** `~/.config/megaman-legends/config.ini`, written with commented defaults on first
  start (bindings, including stick directions as buttons; window scale; volume; disc and card
  paths).
- **Saves:** standard 128 KB memory card images in `~/.local/share/megaman-legends/`, readable by
  PS1 emulators.
- **Mods:** at start-up you choose **Vanilla** (the untouched game) or **Mods**. Modded runs use
  their own memory cards, so vanilla saves are never touched. See [docs/mods.md](docs/mods.md).

`make port-smoke` plays a scripted new game headless and checks memory at fixed points;
`make port-compare` runs the same script with native and interpreted overlay code and compares them.

## Layout

```
src/<target>/        C source per executable and overlay module
src/stage_common/    code shared by several stage modules
include/             headers per target, self-written PsyQ declarations, assembler macros
config/              splat configuration and symbol registry per target
port/                the native port: runtime, PsyQ replacements, mods, tests
tools/               build, split and diff scripts
mml.xml              mkpsxiso disc layout (metadata only)
```

`disc/`, `asm/`, `build/` and `expected/` are generated locally and ignored by git.

## Toolchain

- gcc 2.7.2 for PlayStation (`cc1` from [decompals/old-gcc](https://github.com/decompals/old-gcc)),
  [maspsx](https://github.com/mkst/maspsx) standing in for Sony's `aspsx` 2.56, then GNU `as`;
  `-O2 -G8`. This is decomp.me's `PSYQ4.0` preset.
- [splat](https://github.com/ethteck/splat) splits the executables;
  [m2c](https://github.com/matt-kempster/m2c), [asm-differ](https://github.com/simonlindholm/asm-differ)
  and [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) help with matching.
- [mkpsxiso](https://github.com/Lameguy64/mkpsxiso)'s `dumpsxiso` extracts the disc.

## History

This is a fork of [rickdgray/MegaManLegendsDecomp](https://github.com/rickdgray/MegaManLegendsDecomp).
The commits up to 2026-11-06 ("local vars at top") are Rick Gray's: the splat setup, the
toolchain identification, the first matched boot-program functions and the early research.

On 2026-11-06 I took that state and kept going in a private repository. Over the following
eleven days the main game, all 44 stage and weapon overlays and the rest of the boot program
were matched, and the native port and its mods were written. This fork's next commit is that
work, squashed into one: the development history was a long working log, not something worth
publishing.

The upstream project has continued separately since then, and I'd be glad to see the two come
together. Upstream has no license file, so this fork doesn't add one; it's shared under
GitHub's forking terms, and licensing is up to the original author.

## How this was made

AI-assisted tooling helped draft and iterate on C for a large share of the functions. Nothing is
taken on trust: a function counts as matched only when the whole executable rebuilds to retail's
exact bytes, and the port is checked against scripted play-throughs. Names, types and structure
follow Capcom's own naming conventions.

## Credits

- [rickdgray/MegaManLegendsDecomp](https://github.com/rickdgray/MegaManLegendsDecomp): the
  project this one is forked from (see History).
- [ChrisNonyminus/mml1](https://github.com/ChrisNonyminus/mml1): the 2023 attempt, a reference for
  symbols and research.
- The authors of the community tools listed above.

Contributions are welcome; see [CONTRIBUTING.md](CONTRIBUTING.md).

## Legal

Not affiliated with or endorsed by Capcom or Sony. Mega Man Legends is a trademark of Capcom. You
need your own copy of the game to build or play anything here. The original game's code, data and
assets belong to their owners. Please don't ask for or share game files or disc images in issues.
