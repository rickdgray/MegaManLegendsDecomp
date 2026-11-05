#!/usr/bin/env bash
# Draft C for one function with m2c. Context is built from every shared header in include/ plus include/<target>/.
# Usage: tools/m2c.sh <target> FunctionName [extra m2c flags]
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

if [[ $# -lt 1 ]]; then
    echo "usage: $0 <target> FunctionName [m2c flags]" >&2
    exit 2
fi
fn=$1; shift

asm=$(find "$ASM_DIR/nonmatchings" -name "$fn.s" | head -n 1)
if [[ -z "$asm" ]]; then
    echo "$fn: no $ASM_DIR/nonmatchings/**/$fn.s (already decompiled, or check the name)" >&2
    exit 1
fi

# Context: include common.h first, then every other header. M2CTX disables INCLUDE_ASM.
mkdir -p "$BUILD_DIR"
{
    echo '#include "common.h"'
    {
        # shared headers (not the other target's folder), then this target's own
        find include -name '*.h' ! -path 'include/slus_006.03/*' ! -path 'include/rock_neo.exe/*' \
            ! -name common.h ! -name include_asm.h
        find "include/$TARGET" -name '*.h'
    } | sort | sed -e "s|^include/$TARGET/|#include \"|" -e 's|^include/|#include "|' -e 's|$|"|'
} > "$BUILD_DIR/ctx_includes.c"
cpp -P -undef -nostdinc -Iinclude/$TARGET -Iinclude -DM2CTX "$BUILD_DIR/ctx_includes.c" > "$BUILD_DIR/ctx.c"

exec .venv/bin/python tools/vendor/m2c/m2c.py --target mipsel-gcc-c --context "$BUILD_DIR/ctx.c" "$@" "$asm"