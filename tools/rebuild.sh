#!/usr/bin/env bash
# Split, build, and refresh expected/ for one or more targets. Use after any rename or yaml change
# (tools/rename.py prints the targets to pass). make_expected.sh refuses if a build doesn't match.
# Then regenerates functions.csv (tools/function_list.py), which needs both executables' ELFs.
# Usage: tools/rebuild.sh [target ...]
#   With several targets, each one's split output is kept quiet and one line per target says
#   MATCH or what failed; the run fails if any target does.
set -euo pipefail
cd "$(dirname "$0")/.."

rebuild_one() {
    (
        source tools/target.sh "$1"
        rm -rf "$BUILD_DIR"
        ./tools/split.sh "$TARGET"
        ./tools/build.sh "$TARGET"
        ./tools/make_expected.sh "$TARGET"
        ./tools/format.sh "$TARGET"
    )
}

if [[ $# -le 1 ]]; then
    rebuild_one "${1:-rock_neo.exe}"
else
    failed=()
    for t in "$@"; do
        if out=$(rebuild_one "$t" 2>&1); then
            echo "$t: MATCH"
        else
            echo "$t: FAILED ($(echo "$out" | grep -E 'MISMATCH|rror|Refusing' | head -n 1))"
            failed+=("$t")
        fi
    done
    if [[ ${#failed[@]} -gt 0 ]]; then
        echo "failed: ${failed[*]}" >&2
        exit 1
    fi
fi

if [[ -f build/slus_006.03/slus_006.03.elf && -f build/rock_neo.exe/rock_neo.exe.elf ]]; then
    .venv/bin/python tools/function_list.py \
        || echo "warning: functions.csv not regenerated (open in Excel?)" >&2
else
    echo "note: functions.csv not regenerated; build both executables first" >&2
fi
