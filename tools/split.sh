#!/usr/bin/env bash
# Regenerate splat's output for one target from scratch. asm/<target>/ is fully generated, so
# it is safe to delete. Does not touch src/ (splat never overwrites existing C files).
# Usage: tools/split.sh <target> [splat flags]
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

rm -rf "$ASM_DIR"
exec .venv/bin/python -m splat split "$YAML" "$@"
