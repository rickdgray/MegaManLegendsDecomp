#!/bin/sh
# Runs the long smoke test (smoke.script) headless on the game-paced clock. Settings, memory
# cards and dumps go to a temporary directory. Exit status: 0 when every checkpoint passes.
# Arguments go to mml (e.g. --dump /tmp/s.ppm for VRAM at the stop, --verbose).
set -eu
root=$(cd "$(dirname "$0")/../.." && pwd)
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
export XDG_CONFIG_HOME="$tmp/config" XDG_DATA_HOME="$tmp/data"
status=0
"$root/build/port/mml" --headless --deterministic --vblanks 40000 \
    --script "$root/port/tests/smoke.script" --card1 "$tmp/card1.mcd" "$@" 2> "$tmp/log" || status=$?
grep -E "script:|stopping|watchdog|unhandled|abort" "$tmp/log" || true
if [ "$status" -eq 0 ]; then
    echo "port-smoke: passed"
else
    echo "port-smoke: FAILED (exit $status)"
fi
exit "$status"
