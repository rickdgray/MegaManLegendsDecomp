#!/usr/bin/env bash
# Regenerate splat's output from scratch. asm/ is fully generated, so it is safe to delete.
# Does not touch src/ (splat never overwrites existing C files).
set -euo pipefail
cd "$(dirname "$0")/.."

rm -rf asm
exec .venv/bin/python -m splat split slus_006.03.yaml "$@"