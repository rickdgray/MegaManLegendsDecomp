#!/usr/bin/env bash
# Regenerate splat's output for one target from scratch. asm/[target]/ is fully generated, so
# it is safe to delete. Does not touch src/ (splat never overwrites existing C files).
# Usage: tools/split.sh [target ...] [splat flags]   (or a group: all, executables, overlays)
#   With several targets, each one's output is kept quiet and one line per target says how it went.
set -euo pipefail
MULTI_TARGET_OK=1
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"

if [[ ${#TARGET_LIST[@]} -gt 1 ]]; then
    each_target "$0" "$@"
    exit
fi

rm -rf "$ASM_DIR"

if [[ -n "$IS_OVERLAY" ]]; then
    # splat's input (target_path) and the build's reference: the code chunk extract_overlays.py
    # wrote from the archive the yaml names.
    if [[ ! -f "$CHUNK" ]]; then
        echo "$CHUNK not found. Run tools/extract.sh (or tools/extract_overlays.py) first." >&2
        exit 1
    fi
    mkdir -p "$(dirname "$ORIGINAL")"
    cp "$CHUNK" "$ORIGINAL"
    # ROCK_NEO.EXE's symbols, minus any that fall inside this overlay (e.g. its load address).
    .venv/bin/python tools/overlay_syms.py "$HOST_REGISTRY" "$ORIGINAL" "$YAML" > "$HOST_SYMS"
fi
exec .venv/bin/python -m splat split "$YAML" "$@"
