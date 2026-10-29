#!/usr/bin/env bash
# Draft C for one function with m2c. Context is built from every header in include/.
# Usage: tools/m2c.sh FunctionName [extra m2c flags]
set -euo pipefail
cd "$(dirname "$0")/.."

if [[ $# -lt 1 ]]; then
    echo "usage: $0 FunctionName [m2c flags]" >&2
    exit 2
fi
fn=$1; shift

asm=$(find asm/nonmatchings -name "$fn.s" | head -n 1)
if [[ -z "$asm" ]]; then
    echo "$fn: no asm/nonmatchings/**/$fn.s (already decompiled, or check the name)" >&2
    exit 1
fi

# Context: include common.h first, then every other header. M2CTX disables INCLUDE_ASM.
mkdir -p build
{
    echo '#include "common.h"'
    find include -name '*.h' ! -name common.h ! -name include_asm.h | sort | sed 's|^include/|#include "|; s|$|"|'
} > build/ctx_includes.c
cpp -P -undef -nostdinc -Iinclude -DM2CTX build/ctx_includes.c > build/ctx.c

exec .venv/bin/python tools/vendor/m2c/m2c.py --target mipsel-gcc-c --context build/ctx.c "$@" "$asm"