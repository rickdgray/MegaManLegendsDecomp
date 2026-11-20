#!/usr/bin/env bash
# Run clang-format on the targets' C files and the shared headers. An overlay also formats the
# shared stage code (src/stage_common/), which is compiled into it.
# Usage: tools/format.sh [target ...]     (or a group: all, executables, overlays)
set -euo pipefail
MULTI_TARGET_OK=1
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"

dirs=()
for t in "${TARGET_LIST[@]}"; do
    [[ -d "src/$t" ]] && dirs+=("src/$t")
    if [[ " ${OVERLAYS[*]} " == *" $t "* && " ${dirs[*]} " != *" src/stage_common "* ]]; then
        dirs+=(src/stage_common)
    fi
done
if [[ ${#dirs[@]} -gt 0 ]]; then
    find "${dirs[@]}" -name '*.c' -print0 | xargs -0 -r clang-format-15 -i
fi
# Never format include_asm.h (CLAUDE.md).
find include -name '*.h' ! -name include_asm.h -print0 | xargs -0 -r clang-format-15 -i
