#!/usr/bin/env bash
# Regenerate splat's output for one target from scratch. asm/[target]/ is fully generated, so
# it is safe to delete. Does not touch src/ (splat never overwrites existing C files).
# Usage: tools/split.sh [target] [splat flags]
set -euo pipefail
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"

rm -rf "$ASM_DIR"

if [[ -n "$IS_OVERLAY" ]]; then
    # The chunk's contents are splat's input (target_path) and the build's reference.
    .venv/bin/python tools/overlay_chunks.py extract "$ARCHIVE" "$TARGET.bin" "$ORIGINAL"
    # ROCK_NEO.EXE's symbols, minus any that fall inside this overlay (e.g. its load address).
    .venv/bin/python tools/overlay_syms.py "$HOST_REGISTRY" "$ORIGINAL" "$YAML" > "$HOST_SYMS"
fi
exec .venv/bin/python -m splat split "$YAML" "$@"
