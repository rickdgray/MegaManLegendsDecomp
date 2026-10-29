#!/usr/bin/env bash
# Per-function diff against the expected/ snapshot.
# asm-differ's -o mode doesn't accept an end address, so this cuts its output off at the
# function's real end (start + size, from the object's symbol table).
# The header's score still covers everything asm-differ diffed; trust the flagged lines.
# Usage: tools/diff.sh FunctionName [--whole] [extra asm-differ flags]
set -euo pipefail
cd "$(dirname "$0")/.."

if [[ $# -lt 1 ]]; then
    echo "usage: $0 FunctionName [--whole] [diff.py flags]" >&2
    exit 2
fi
fn=$1; shift

whole=0
if [[ "${1:-}" == "--whole" ]]; then whole=1; shift; fi

# Find the function's offset and size in the object that defines it ("F" = function symbol).
found=""
while read -r obj; do
    line=$(mips-linux-gnu-objdump -t "$obj" | awk -v f="$fn" '$NF == f && $3 == "F" { print $1, $5; exit }')
    if [[ -n "$line" ]]; then found=$line; break; fi
done < <(find build -name '*.o')

if [[ -z "$found" ]]; then
    echo "$fn: no function symbol in build/ (run tools/build.sh, check the name)" >&2
    exit 1
fi

read -r start size <<< "$found"
end=$(( 0x$start + 0x$size ))

if (( whole )); then
    exec .venv/bin/python tools/vendor/asm-differ/diff.py -o --no-pager "$fn" "$@"
fi

# Stop printing at the function end, but keep reading so asm-differ can finish writing
# (exiting early would close the pipe and make Python raise BrokenPipeError).
.venv/bin/python tools/vendor/asm-differ/diff.py -o --no-pager "$fn" "$@" | awk -v end="$end" '
    function hex(s,    i, v) {
        v = 0; s = tolower(s)
        for (i = 1; i <= length(s); i++) v = v * 16 + index("0123456789abcdef", substr(s, i, 1)) - 1
        return v
    }
    {
        plain = $0
        gsub(/\033\[[0-9;]*m/, "", plain)          # ignore color codes when testing
        split(plain, f, " ")
        if (f[1] ~ /^[0-9a-f]+:$/ && hex(substr(f[1], 1, length(f[1]) - 1)) >= end) done = 1
        if (!done) print
    }'