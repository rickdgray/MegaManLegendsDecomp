#!/usr/bin/env bash
# Run decomp-permuter on one parked function.
#
# Usage: tools/permute.sh <target> <function> [jobs] [-- extra permuter options]
#   e.g. tools/permute.sh rock_neo.exe Cd_seek
#        tools/permute.sh rock_neo.exe Cd_xa_play_id 2
#        tools/permute.sh rock_neo.exe Cd_seek 4 -- --show-errors
#
# Prepares permuter/<target>/<function>/ from the function's NON_MATCHING draft if it doesn't exist
# yet (rerun tools/permuter_prep.py yourself after changing the draft), then runs the permuter with
# --stop-on-zero, logging to run.log in that folder. jobs defaults to all cores; when running
# several functions at once, give each a share. Improvements land in output-<score>-N folders;
# compare one with the base using tools/permuter_diff.sh. Run it inside tmux for long runs.
set -euo pipefail

cd "$(dirname "$0")/.."

if [ $# -lt 2 ]; then
    sed -n '2,13p' "$0" | sed 's/^# \{0,1\}//'
    exit 1
fi

target=$1
func=$2
shift 2

jobs=$(nproc)
if [ $# -gt 0 ] && [ "$1" != "--" ]; then
    jobs=$1
    shift
fi
[ $# -gt 0 ] && [ "$1" = "--" ] && shift

case "$target" in
    slus_006.03 | rock_neo.exe) ;;
    *)
        echo "unknown target: $target (slus_006.03 or rock_neo.exe)" >&2
        exit 1
        ;;
esac

dir="permuter/$target/$func"
if [ ! -d "$dir" ]; then
    echo "$dir doesn't exist; preparing it from the NON_MATCHING draft"
    .venv/bin/python tools/permuter_prep.py "$target" "$func"
fi

echo "permuting $target/$func with $jobs jobs (log: $dir/run.log); Ctrl+C to stop"
.venv/bin/python tools/vendor/decomp-permuter/permuter.py "$dir" -j "$jobs" --stop-on-zero "$@" 2>&1 | tee -a "$dir/run.log"
