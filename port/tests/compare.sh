#!/bin/sh
# Runs the smoke script twice on the game-paced clock, once with the native overlay code and once
# with every overlay function on the interpreter (PORT_OVERLAY_NATIVE=0), and compares the two:
# the script's checkpoint and mark lines, VRAM dumps at fixed blanks and at the stop, and the
# sound of the whole run. A native overlay function that behaves differently from its retail
# bytes shows up as a difference. Exit status 0 when the
# runs agree. Arguments go to both runs of mml.
set -eu
root=$(cd "$(dirname "$0")/../.." && pwd)
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
export XDG_CONFIG_HOME="$tmp/config" XDG_DATA_HOME="$tmp/data"
at=5000,8000,10000,11000,12000,13000,14000
for native in 1 0; do
    PORT_OVERLAY_NATIVE=$native "$root/build/port/mml" --headless --deterministic --vblanks 40000 \
        --script "$root/port/tests/smoke.script" --card1 "$tmp/card$native.mcd" \
        --dump "$tmp/vram$native.ppm" --dump-at "$at" --wav "$tmp/sound$native.wav" "$@" \
        2> "$tmp/log$native" || { echo "port-compare: run with PORT_OVERLAY_NATIVE=$native failed"; exit 1; }
    grep "script:" "$tmp/log$native" > "$tmp/script$native"
done
grep "overlays:" "$tmp/log1" | head -1
status=0
cmp -s "$tmp/script1" "$tmp/script0" || { echo "port-compare: script lines differ"; status=1; }
for v in $(echo "$at" | tr , ' '); do
    cmp -s "$tmp/vram1-$v.ppm" "$tmp/vram0-$v.ppm" || { echo "port-compare: VRAM differs at blank $v"; status=1; }
done
cmp -s "$tmp/vram1.ppm" "$tmp/vram0.ppm" || { echo "port-compare: VRAM differs at the stop"; status=1; }
cmp -s "$tmp/sound1.wav" "$tmp/sound0.wav" || { echo "port-compare: sound differs"; status=1; }
if [ "$status" -eq 0 ]; then
    echo "port-compare: native and interpreted runs agree"
fi
exit "$status"
