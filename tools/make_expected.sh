#!/usr/bin/env bash
# Snapshot a MATCHING build as the reference for per-function diffs (asm-differ -o).
# Refuses to run unless build/SLUS_006.03 is byte-identical to the original.
set -euo pipefail
cd "$(dirname "$0")/.."

TARGET=disc/extracted/SLUS_006.03
BUILT=build/SLUS_006.03

if ! cmp -s "$TARGET" "$BUILT"; then
    echo "Refusing: $BUILT does not match $TARGET. Run tools/build.sh and fix it first." >&2
    exit 1
fi

rm -rf expected
mkdir -p expected
cp -r build expected/build
echo "expected/ refreshed from a matching build."