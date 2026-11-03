#!/usr/bin/env bash
# Rebuild one target from splat's output and C sources, and compare it with the original.
# Run tools/split.sh <target> first: the object list comes from splat's linker script.
# Usage: tools/build.sh <target>
set -euo pipefail
source "$(dirname "$0")/target.sh" "${1:-}"; shift

AS="mips-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -G0 -Iinclude"
LD="mips-linux-gnu-ld -EL"
OBJCOPY="mips-linux-gnu-objcopy"

if [[ ! -f "$LD_SCRIPT" ]]; then
    echo "$LD_SCRIPT not found. Run tools/split.sh $TARGET first." >&2
    exit 1
fi

# 1. Build every object the linker script names, from whichever source it comes from:
#    $BUILD_DIR/<path>.o  <-  <path>.s (asm), <path>.c (C) or <path>.bin (binary blob).
#    Per-function files under nonmatchings/ are pulled into C objects by INCLUDE_ASM.
grep -o "$BUILD_DIR/[^ )]*\.o" "$LD_SCRIPT" | sort -u | while read -r obj; do
    base=${obj#"$BUILD_DIR/"}
    base=${base%.o}
    mkdir -p "$(dirname "$obj")"
    if [[ -f "$base.s" ]]; then
        $AS -o "$obj" "$base.s"
    elif [[ -f "$base.c" ]]; then
        tools/cc.sh "$TARGET" "$base.c" "$obj"
    elif [[ -f "$base.bin" ]]; then
        # The bytes land in a .data section, which is what the linker script pulls in.
        $OBJCOPY -I binary -O elf32-tradlittlemips -B mips "$base.bin" "$obj"
    else
        echo "$obj: no source ($base.s, .c or .bin)" >&2
        exit 1
    fi
done

# 2. Link with splat's linker script (plus its auto-generated symbol files, if present).
#    splat writes those to the repo root (the yaml doesn't set undefined_*_auto_path).
LD_SCRIPTS=()
for f in "$BUILD_DIR/undefined_syms_auto.txt" "$BUILD_DIR/undefined_funcs_auto.txt"; do
    [[ -f "$f" ]] && LD_SCRIPTS+=(-T "$f")
done

# Symbols marked absolute:True (hardware registers, scratchpad) aren't defined by any
# object file. Registry lines ("name = 0xADDR; // ...") are valid linker-script
# assignments once the comment is stripped, so define them that way.
grep 'absolute:True' "$REGISTRY" | sed 's|//.*||' > "$BUILD_DIR/absolute_syms.ld" || true
LD_SCRIPTS+=(-T "$BUILD_DIR/absolute_syms.ld")
$LD "${LD_SCRIPTS[@]}" -T "$LD_SCRIPT" -Map "$MAP" -o "$ELF"

# 3. Convert the ELF to a raw binary.
$OBJCOPY -O binary "$ELF" "$BINARY"

# PS-X EXE files are padded with zeros to a multiple of 2048 bytes (one CD sector).
# BSS occupies no file space, so the binary ends at the last data byte; pad it back out.
truncate -s %2048 "$BINARY"

# 4. Compare.
sha1sum "$ORIGINAL" "$BINARY"
if cmp -s "$ORIGINAL" "$BINARY"; then
    echo "MATCH"
else
    echo "MISMATCH"
    cmp "$ORIGINAL" "$BINARY" | head -n 1 || true
    ls -l "$ORIGINAL" "$BINARY"
fi
