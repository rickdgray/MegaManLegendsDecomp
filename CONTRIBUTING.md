# Contributing

Every function already matches, so contributions are mostly about making the source better to
read: names, types, comments, replacing the `// FAKE MATCH:` forms with natural C, and the port.

## The one rule

`./tools/build.sh <target>` must print **MATCH** for every target your change touches (and
`make overlays` for shared stage code in `src/stage_common/`, which is built into several
modules). The SHA-1 check is the only authority on whether something matches. Comments and
names never change the bytes; types, statement order and expressions often do.

## Never commit game data

Nothing from `disc/`, `asm/`, `assets/`, `build/` or `expected/` goes into tracked files: no
copied assembly, data tables, text or graphics. Write declarations yourself; never copy Sony's
PsyQ headers.

## Style

- gcc 2.7.2 is a C89 compiler: locals at the top of the function, no `inline`, no `bool`, no
  designated initializers, no mixed declarations and code. `//` comments are fine.
- Allman braces, 4-space indent, braces even around one-line bodies. Run `./tools/format.sh <t>`
  (`clang-format-15`, config in `.clang-format`) on what you changed.
- Types: Capcom's `uint8`, `sint8`, `uint16`, `sint16`, `uint32`, `sint32` in game code; PsyQ's
  types (`u_char`, `u_long`, `RECT`, `SVECTOR`, ...) for PsyQ structures and prototypes.
- Function pointers get a typedef ending in `_FUNC`, including dispatch tables.
- Name magic numbers with PsyQ's macros (`getTPage`, `getClut`) or a `#define` when the name folds
  to the same constant.
- No redundant statements unless the build needs them; when it does, say so in a comment.
- Prefer the natural form when several forms match (`for (i = 0; i < n; i++)` before a reversed
  loop).
- Capcom's hand-written assembly routines stay assembly; don't convert them.

## Names

Names follow Capcom's own conventions:

| Kind | Style | Examples |
|---|---|---|
| Global functions | `Capitalized_snake_case` | `Sound_call`, `Cd_read_comb` |
| `static` functions | `lower_snake_case` | `check_block` |
| Global variables | `Capitalized_snake_case` | `Player_work`, `Game_work` |
| `static` variables | `lower_snake_case` | `spd_tbl` |
| Struct types | `ALL_CAPS`, state structs end in `_WORK` | `PL_WORK`, `GAME_WORK` |
| Function-pointer typedefs | `ALL_CAPS_FUNC` | `SCREEN_FUNC` |
| Constants, macros | `ALL_CAPS` | |
| Tables | `_tbl` suffix | `screen_tbl` |
| State fields | `routine_0` ... `routine_3` | |

Unknown names keep splat's defaults (`func_800110E4`, `D_80059C20`) until their purpose is clear.
A rename touches `config/<t>/symbol_addrs.txt`, the sources, and the headers together; run
`./tools/rebuild.sh <t>` afterwards so `expected/` has the new names.

## Headers

`include/` holds only what both executables share with identical declarations (`common.h`,
`psyq/`, `cd.h`). Everything else lives in `include/<target>/`. Inside a header: include guard,
`#include`s, `#define`s, types, `extern`s, then prototypes. A `.c` file declares nothing itself.

## Fake matches

Some functions contain a statement that exists only to steer gcc (a dead conditional store, an
unused assignment). They're tagged `// FAKE MATCH: <what is artificial>`. If you find a natural
form that matches, replace it and drop the tag.

## The port

`make port-smoke` and `make port-compare` must still pass after changes to `src/` or `port/`.
Mods live in `port/mods/` and never change the game's source; see [docs/mods.md](docs/mods.md).
