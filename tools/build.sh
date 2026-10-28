#!/usr/bin/env bash
# Practice build: rebuild SLUS_006.03 from splat's split assembly and compare hashes.
# Run from the repo root (WSL), after: python -m splat split slus_006.03.yaml
set -euo pipefail

NAME=slus_006.03
TARGET=disc/extracted/SLUS_006.03
OBJ_DIR=build          # must match the .o paths in $NAME.ld

AS="mips-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -G0 -Iinclude"
LD="mips-linux-gnu-ld -EL"
OBJCOPY="mips-linux-gnu-objcopy"

# 1. Assemble every .s file splat produced (code, data, header).
find asm -name '*.s' | while read -r src; do
    obj="$OBJ_DIR/${src%.s}.o"     # asm/foo.s -> build/asm/foo.o (matches $NAME.ld)
    mkdir -p "$(dirname "$obj")"
    $AS -o "$obj" "$src"
done

# 2. Link with splat's linker script (plus its auto-generated symbol files, if present).
LD_SCRIPTS=()
for f in undefined_syms_auto.txt undefined_funcs_auto.txt; do
    [[ -f "$f" ]] && LD_SCRIPTS+=(-T "$f")
done
$LD "${LD_SCRIPTS[@]}" -T "$NAME.ld" -Map "$OBJ_DIR/$NAME.map" -o "$OBJ_DIR/$NAME.elf"

# 3. Convert the ELF to a raw binary.
$OBJCOPY -O binary "$OBJ_DIR/$NAME.elf" "$OBJ_DIR/SLUS_006.03"

# 4. Compare.
sha1sum "$TARGET" "$OBJ_DIR/SLUS_006.03"
if cmp -s "$TARGET" "$OBJ_DIR/SLUS_006.03"; then
    echo "MATCH"
else
    echo "MISMATCH"
    cmp "$TARGET" "$OBJ_DIR/SLUS_006.03" | head -n 1 || true
    ls -l "$TARGET" "$OBJ_DIR/SLUS_006.03"
fi