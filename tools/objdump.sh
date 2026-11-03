#!/usr/bin/env bash
# Disassemble with real instructions (no pseudo-ops like li/move/nop) and relocations.
# Usage: tools/objdump.sh <target> path/to/file.o   (whole object)
#        tools/objdump.sh <target> FunctionName     (one function, from whichever object has it)
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

OBJDUMP="mips-linux-gnu-objdump -d -r -M no-aliases"

if [[ $# -ne 1 ]]; then
    echo "usage: $0 <target> file.o | FunctionName" >&2
    exit 2
fi

if [[ -f "$1" ]]; then
    exec $OBJDUMP "$1"
fi

fn=$1
while read -r obj; do
    if mips-linux-gnu-objdump -t "$obj" | awk -v f="$fn" '$NF == f && $3 == "F" { ok = 1 } END { exit !ok }'; then
        exec $OBJDUMP --disassemble="$fn" "$obj"
    fi
done < <(find "$BUILD_DIR" -name '*.o')

echo "$fn: no function symbol in $BUILD_DIR/ (run tools/build.sh $TARGET, check the name)" >&2
exit 1