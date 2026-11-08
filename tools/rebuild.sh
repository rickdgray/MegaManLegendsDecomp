#!/usr/bin/env bash
# Split, build, and refresh expected/ for one target. Use after any rename or yaml change.
# make_expected.sh refuses if the build doesn't match.
# Usage: tools/rebuild.sh <target>
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

rm -rf "$BUILD_DIR"
./tools/split.sh "$TARGET"
./tools/build.sh "$TARGET"
./tools/make_expected.sh "$TARGET"
./tools/format.sh "$TARGET"
