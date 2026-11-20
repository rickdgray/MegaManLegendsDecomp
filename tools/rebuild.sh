#!/usr/bin/env bash
# Split, build, and refresh expected/ for one or more targets, then format and regenerate
# functions.csv (tools/function_list.py, which needs both executables' ELFs). Use after any rename
# or yaml change (tools/rename.py prints the targets to pass). make_expected.sh refuses if a build
# doesn't match.
# Usage: tools/rebuild.sh [target ...]    (or a group: all, executables, overlays)
#   With several targets, each one's output is kept quiet and one line per target says MATCH or
#   what failed; the run fails if any target does.
set -euo pipefail
MULTI_TARGET_OK=1
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"

if [[ -n "${REBUILD_ONE:-}" ]]; then
    # One target, called by the loop below: no formatting or functions.csv yet.
    rm -rf "$BUILD_DIR"
    ./tools/split.sh "$TARGET"
    ./tools/build.sh "$TARGET"
    ./tools/make_expected.sh "$TARGET"
    exit
fi

status=0
if [[ ${#TARGET_LIST[@]} -gt 1 ]]; then
    REBUILD_ONE=1 EACH_NEEDS_MATCH=1 each_target "$0" || status=1
else
    REBUILD_ONE=1 "$0" "$TARGET" || status=1
fi

./tools/format.sh "${TARGET_LIST[@]}"

if [[ -f build/slus_006.03/slus_006.03.elf && -f build/rock_neo.exe/rock_neo.exe.elf ]]; then
    .venv/bin/python tools/function_list.py \
        || echo "warning: functions.csv not regenerated (open in Excel?)" >&2
else
    echo "note: functions.csv not regenerated; build both executables first" >&2
fi
exit $status
