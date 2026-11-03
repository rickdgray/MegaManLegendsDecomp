#!/usr/bin/env bash
# Run clang-format on one target's C files and the shared headers.
# Usage: tools/format.sh <target>
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

find "$SRC_DIR" -name '*.c' -print0 | xargs -0 -r clang-format-15 -i
# Never format include_asm.h (CLAUDE.md).
find include -name '*.h' ! -name include_asm.h -print0 | xargs -0 -r clang-format-15 -i
