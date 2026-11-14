#!/usr/bin/env bash
# Build a decomp.me context file: every declaration and constant a C file's headers provide.
#
# Usage: tools/ctx.sh [target] <file.c> [out]     (out defaults to ctx.c in the repo root)
#   e.g. tools/ctx.sh rock_neo.exe src/rock_neo.exe/cd.c
#
# Only the file's #include lines are preprocessed (its function bodies and INCLUDE_ASM lines would
# not compile on decomp.me), with the target's own include folder first, as tools/cc.sh does.
# -dD keeps the #defines so constants survive; the compiler's built-in macros (__*) are dropped,
# since decomp.me's compiler defines those itself.
set -euo pipefail

cd "$(dirname "$0")/.."

# The target is optional (rock_neo.exe when the first argument isn't a target name).
case "${1:-}" in
    slus_006.03 | rock_neo.exe) target=$1; shift ;;
    *) target=rock_neo.exe ;;
esac

if [ $# -lt 1 ]; then
    echo "usage: $0 [target] <file.c> [out]" >&2
    exit 1
fi

src=$1
out=${2:-ctx.c}

case "$target" in
    slus_006.03 | rock_neo.exe) ;;
    *)
        echo "unknown target: $target (slus_006.03 or rock_neo.exe)" >&2
        exit 1
        ;;
esac

if [ ! -f "$src" ]; then
    echo "no such file: $src" >&2
    exit 1
fi

tmp=$(mktemp --suffix=.c)
trap 'rm -f "$tmp"' EXIT

grep '^#include' "$src" > "$tmp"
mips-linux-gnu-cpp -P -dD -I "include/$target" -I include "$tmp" | grep -v '^#define __' > "$out"

echo "wrote $out ($(wc -l < "$out") lines) from the includes of $src"
