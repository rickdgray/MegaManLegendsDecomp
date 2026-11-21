#!/usr/bin/env bash
# Build a decomp.me context file: every declaration and constant a C file's headers provide.
#
# Usage: tools/ctx.sh [target] <file.c> [out]     (out defaults to ctx.c in the repo root)
#   e.g. tools/ctx.sh rock_neo.exe src/rock_neo.exe/cd.c
#        tools/ctx.sh r3_st05 src/stage_common/stcom36.c   (a shared file, as that overlay compiles it)
#
# Only the file's preamble is preprocessed (tools/preamble.py: everything before its first function,
# INCLUDE_ASM or parked block, i.e. its #includes, its own small data and pool definitions and its
# file-local prototypes; the function bodies and INCLUDE_ASM lines would not compile on decomp.me),
# with the target's own include folder first, as tools/cc.sh does. The small data definitions
# carry their initial values (game data) into the context.
# -dD keeps the #defines so constants survive; the compiler's built-in macros (__*) are dropped,
# since decomp.me's compiler defines those itself.
set -euo pipefail

# The target is optional (rock_neo.exe when the first argument isn't a target name); target.sh
# also changes to the repo root.
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"
target=$TARGET

if [ $# -lt 1 ]; then
    echo "usage: $0 [target] <file.c> [out]" >&2
    exit 1
fi

src=$1
out=${2:-ctx.c}

if [ ! -f "$src" ]; then
    echo "no such file: $src" >&2
    exit 1
fi

tmp=$(mktemp --suffix=.c)
trap 'rm -f "$tmp"' EXIT

python3 tools/preamble.py "$src" > "$tmp"
mips-linux-gnu-cpp -P -dD -I "include/$target" -I include "$tmp" | grep -v '^#define __' > "$out"

echo "wrote $out ($(wc -l < "$out") lines) from the preamble of $src"
