#!/usr/bin/env bash
# One-time extraction of the game data in a fresh clone (everything lands in disc/, gitignored):
#   1. the disc's filesystem, with dumpsxiso, into disc/extracted/ (SLUS_006.03, ROCK_NEO.EXE,
#      CDDATA/...), also writing the disc layout to mml.xml; skipped when disc/extracted/ already
#      has both executables, unless --force;
#   2. every overlay's code chunk, from the CDDATA/DAT/*.BIN archives into disc/overlays/
#      (tools/extract_overlays.py): split.sh reads an overlay's chunk from there;
#   3. a check of every hash against the sha1 in its yaml: both executables, and each overlay's
#      chunk in its own archive and in the archives its yaml lists as duplicates.
# Usage: tools/extract.sh [--force]
#   CUE=<path> for another image (default: disc/image/Mega Man Legends (USA).cue);
#   DUMPSXISO=<path> for another dumpsxiso (default: dumpsxiso on PATH; dumpsxiso.exe works from WSL).
set -euo pipefail
source "$(dirname "$0")/target.sh"

CUE=${CUE:-"disc/image/Mega Man Legends (USA).cue"}
DUMPSXISO=${DUMPSXISO:-dumpsxiso}

# 1. The disc's filesystem.
if [[ "${1:-}" == --force || ! -f disc/extracted/SLUS_006.03 || ! -f disc/extracted/ROCK_NEO.EXE ]]; then
    if [[ ! -f "$CUE" ]]; then
        echo "$CUE not found: put your disc image in disc/image/ (README, \"Setup\")" >&2
        exit 1
    fi
    if ! command -v "$DUMPSXISO" > /dev/null; then
        echo "$DUMPSXISO not found: install mkpsxiso (README, \"Setup\") or set DUMPSXISO=<path>" >&2
        exit 1
    fi
    "$DUMPSXISO" -x disc/extracted/ -s mml.xml "$CUE"
else
    echo "disc/extracted/ already holds the executables (--force to extract again)"
fi

# 2. The overlays' code chunks.
.venv/bin/python tools/extract_overlays.py > /dev/null
echo "disc/overlays/: $(ls disc/overlays | wc -l) code chunks"

# 3. Hashes.
yaml_sha1() { sed -n 's/^sha1:[[:space:]]*\([0-9a-fA-F]*\).*/\1/p' "$1"; }
bad=0
check() {   # check <file> <expected sha1> <label>
    local got
    got=$(sha1sum "$1" 2> /dev/null | cut -d' ' -f1 || true)
    if [[ "$got" != "$2" ]]; then
        echo "MISMATCH $3: $1 ${got:-missing}, expected $2" >&2
        bad=$((bad + 1))
    fi
}
for t in "${EXECUTABLES[@]}"; do
    check "disc/extracted/${t^^}" "$(yaml_sha1 "config/$t/$t.yaml")" "$t"
done
for t in "${OVERLAYS[@]}"; do
    yaml=config/$t/$t.yaml
    want=$(yaml_sha1 "$yaml")
    check "disc/overlays/$(sed -n 's/^archive:[[:space:]]*\([^[:space:]]*\).*/\1/p' "$yaml")" "$want" "$t"
    for dup in $(sed -n 's/^duplicates:[[:space:]]*\[\(.*\)\].*/\1/p' "$yaml" | tr ',' ' '); do
        check "disc/overlays/$dup" "$want" "$t (duplicate archive $dup)"
    done
done
if [[ $bad -gt 0 ]]; then
    echo "$bad file(s) don't match their yaml's sha1: check the disc image against Redump (README)" >&2
    exit 1
fi
echo "All hashes match: ${#EXECUTABLES[@]} executables, ${#OVERLAYS[@]} overlays and their duplicate archives."
