# Contributing

Contributions are welcome: matching functions, and above all making matched code read like
source a person wrote: real names, real types and structures, and comments that explain how the
game works.

## The one rule

`./tools/build.sh <target>` must print **MATCH** for every target your change touches, and
`make overlays` must pass for changes to shared stage code in `src/stage_common/`, which is built
into several modules. The SHA-1 check is the only authority on whether something matches.
Comments and names never change the bytes; types, statement order and expressions often do.

## Never commit game data

Nothing from `disc/`, `asm/`, `assets/`, `build/` or `expected/` goes into tracked files: no
copied assembly, data tables, text or graphics. Write declarations yourself; never copy Sony's
PsyQ headers.

## Targets

| Target | What it is |
|---|---|
| `slus_006.03` | the boot program |
| `rock_neo.exe` | the main game |
| `r3_st00` … `r3_st1e`, `r3_shl02` … `r3_shl0d`, `r3_sup` | stage, weapon and shop code, loaded from `CDDATA/DAT/*.BIN` (`tools/overlays.txt`) |

Each target has `config/<t>/<t>.yaml` and `config/<t>/symbol_addrs.txt`, sources in `src/<t>/`
and headers in `include/<t>/`. Code that several stages share lives once in `src/stage_common/`
(types in `include/stage_common/`); each stage's yaml links the files it uses.

```sh
make split build                # the two executables
make split-overlays overlays    # the overlays
./tools/diff.sh <t> <func>      # one function against the last matching build
```

Overlays link against `rock_neo.exe`'s registry, so a function or global of the main game has the
same name in every overlay. Rename it in `config/rock_neo.exe/symbol_addrs.txt` and update the
overlay sources that use it.

## Style

- gcc 2.7.2 is a C89 compiler: locals at the top of the function, no `inline`, no `bool`, no
  designated initializers, no mixed declarations and code. `//` comments are fine.
- Allman braces, 4-space indent, braces even around one-line bodies. Run `./tools/format.sh <t>`
  (config in `.clang-format`) on what you changed.
- Types: Capcom's `uint8`, `sint8`, `uint16`, `sint16`, `uint32`, `sint32` in game code; PsyQ's
  types (`u_char`, `u_long`, `RECT`, `SVECTOR`, ...) for PsyQ structures and prototypes.
- No redundant statements unless the build needs them; when it does, say so in a comment.
- Prefer the natural form when several forms match.
- Capcom's hand-written assembly routines stay assembly.

## Names

Names follow Capcom's own conventions:

| Kind | Style | Examples |
|---|---|---|
| Global functions | `Capitalized_snake_case` | `Sound_call`, `Cd_read_comb` |
| `static` functions | `lower_snake_case` | `check_block` |
| Global variables | `Capitalized_snake_case` | `Player_work`, `Game_work` |
| Struct types | `ALL_CAPS`, state structs end in `_WORK` | `PL_WORK`, `GAME_WORK` |
| Constants, macros | `ALL_CAPS` | |
| Tables | `_tbl` suffix | `screen_tbl` |

Unknown names keep splat's defaults (`func_800110E4`, `D_80059C20`) until their purpose is clear.

## Fake matches and non-matching functions

A function that matches only because of a statement that exists to steer gcc (a dead conditional
store, an unused assignment) is tagged `// FAKE MATCH: <what is artificial>`. A function whose C
doesn't match yet keeps its assembly, with the best attempt under `#ifdef NON_MATCHING`. If you
find a natural form that matches, replace it and drop the tag.
