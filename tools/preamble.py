#!/usr/bin/env python3
"""Print a C file's preamble: everything before its first function, INCLUDE_ASM or parked block.

Usage:  tools/preamble.py <file.c>

Under CLAUDE.md's conventions that is the file's #includes, its own small data and pool
definitions, and its "Called only from this file" prototypes: what a single function needs to
compile on its own as it does in the build. Used by tools/permuter_prep.py and tools/ctx.sh.
"""

import re
import sys

# A function definition starts at column 0 with `type name(args)` and `{` on the next line
# (Allman style); prototypes end in `;` and data initializers have no parameter list.
FIRST_DEF = re.compile(
    r"^(?:INCLUDE_ASM\(|#ifdef NON_MATCHING|[A-Za-z_][\w \*]*\b\w+\([^;{]*\)\s*\n\{)",
    re.M,
)


def preamble(text: str) -> str:
    m = FIRST_DEF.search(text)
    return text[: m.start()] if m else text


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    sys.stdout.write(preamble(open(sys.argv[1], encoding="utf-8").read()))
