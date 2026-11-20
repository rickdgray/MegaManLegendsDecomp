#!/usr/bin/env bash
# Run clang-format on one target's C files and the shared headers. An overlay also formats the
# shared stage code (src/stage_common/), which is compiled into it.
# Usage: tools/format.sh [target]
set -euo pipefail
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"

find "$SRC_DIR" -name '*.c' -print0 | xargs -0 -r clang-format-15 -i
if [[ -n "$IS_OVERLAY" ]]; then
    find src/stage_common -name '*.c' -print0 | xargs -0 -r clang-format-15 -i
fi
# Never format include_asm.h (CLAUDE.md).
find include -name '*.h' ! -name include_asm.h -print0 | xargs -0 -r clang-format-15 -i
