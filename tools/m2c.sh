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

# Shared stage code's assembly is in $ASM_DIR/stage_common/.
asm=$(find "$ASM_DIR/nonmatchings" "$ASM_DIR/stage_common" -name "$fn.s" 2>/dev/null | head -n 1 || true)
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
            ! -path 'include/r3_*' ! -path 'include/stage_common/*' ! -name common.h ! -name include_asm.h
        if [[ -d "include/$TARGET" ]]; then find "include/$TARGET" -name '*.h'; fi
        # A stage's shared code (src/stage_common/) declares its types in include/stage_common/.
        if [[ "$TARGET" == r3_st* ]]; then find include/stage_common -name '*.h'; fi
        # An overlay calls into ROCK_NEO.EXE: its headers are context too.
        if [[ -n "$IS_OVERLAY" ]]; then find include/rock_neo.exe -name '*.h'; fi
    } | sort | sed -e "s|^include/$TARGET/|#include \"|" -e 's|^include/rock_neo.exe/|#include "|' \
        -e 's|^include/|#include "|' -e 's|$|"|'
} > "$BUILD_DIR/ctx_includes.c"
HOST_INC=${IS_OVERLAY:+-Iinclude/rock_neo.exe}
cpp -P -undef -nostdinc -Iinclude/$TARGET $HOST_INC -Iinclude -DM2CTX "$BUILD_DIR/ctx_includes.c" > "$BUILD_DIR/ctx.c"

exec .venv/bin/python tools/vendor/m2c/m2c.py --target mipsel-gcc-c --context "$BUILD_DIR/ctx.c" "$@" "$asm"