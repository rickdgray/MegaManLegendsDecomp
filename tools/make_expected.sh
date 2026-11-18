#!/usr/bin/env bash
# Snapshot a MATCHING build of one target as the reference for per-function diffs
# (asm-differ -o). Refuses to run unless the built binary is byte-identical to the original.
# asm-differ looks for the reference object at expected/<target>/<object path>, so the
# snapshot keeps the build's own path: expected/<target>/build/<target>/...
# Usage: tools/make_expected.sh <target>
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

if ! cmp -s "$ORIGINAL" "$BINARY"; then
    echo "Refusing: $BINARY does not match $ORIGINAL. Run tools/build.sh $TARGET and fix it first." >&2
    exit 1
fi

rm -rf "$EXPECTED_DIR"
mkdir -p "$EXPECTED_DIR/build"
cp -r "$BUILD_DIR" "$EXPECTED_DIR/$BUILD_DIR"
echo "$EXPECTED_DIR/ refreshed from a matching build."
