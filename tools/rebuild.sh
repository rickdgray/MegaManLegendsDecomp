#!/usr/bin/env bash
# Split, build, and refresh expected/ for one target. Use after any rename or yaml change.
# make_expected.sh refuses if the build doesn't match.
# Then regenerates functions.csv (tools/function_list.py), which needs both targets' ELFs.
# Usage: tools/rebuild.sh <target>
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

rm -rf "$BUILD_DIR"
./tools/split.sh "$TARGET"
./tools/build.sh "$TARGET"
./tools/make_expected.sh "$TARGET"
./tools/format.sh "$TARGET"

if [[ -f build/slus_006.03/slus_006.03.elf && -f build/rock_neo.exe/rock_neo.exe.elf ]]; then
    .venv/bin/python tools/function_list.py \
        || echo "warning: functions.csv not regenerated (open in Excel?)" >&2
else
    echo "note: functions.csv not regenerated; build both targets first" >&2
fi
