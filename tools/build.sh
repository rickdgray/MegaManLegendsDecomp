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
#    An address that splat's asm builds with lui/ori is written as constants
#    (`lui $a0, (0xADDR >> 16)`). Where the target's linker file defines `LUI_ADDR = SYMBOL - 0x8000;`,
#    the asm is assembled from a copy (in build/ only) using `%hi(LUI_ADDR)` and `%lo(SYMBOL)`, so
#    the address follows the layout (tools/shift_test.py).
LUI_SED=()
LUI_GREP=""
if [[ -f "linker_syms_$TARGET.ld" ]]; then
    while read -r addr sym; do
        LUI_SED+=(-e "s/\\(0x$addr >> 16\\)/%hi(LUI_$addr)/g" -e "s/\\(0x$addr & 0xFFFF\\)/%lo($sym)/g")
        LUI_GREP+="${LUI_GREP:+\\|}(0x$addr >> 16)"
    done < <(sed -nE 's/^[[:space:]]*LUI_([0-9A-F]{8})[[:space:]]*=[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*-[[:space:]]*0x8000[[:space:]]*;.*/\1 \2/p' \
        "linker_syms_$TARGET.ld")
fi

grep -o "$BUILD_DIR/[^ )]*\.o" "$LD_SCRIPT" | sort -u | while read -r obj; do
    base=${obj#"$BUILD_DIR/"}
    base=${base%.o}
    mkdir -p "$(dirname "$obj")"
    if [[ "$base" == "$ASM_DIR/header" && -f "linker_syms_$TARGET.ld" ]] \
        && grep -q "EXE_ENTRY" "linker_syms_$TARGET.ld"; then
        # The PS-X EXE header splat writes has literal addresses. Where the target's linker
        # file defines EXE_ENTRY, EXE_TEXT_START and EXE_TEXT_SIZE, assemble a copy (in build/
        # only) that uses them, so the header follows the layout (tools/shift_test.py).
        sed -E -e 's|^\.word 0x[0-9A-Fa-f]{8}( +/\* Initial PC \*/)|.word EXE_ENTRY\1|' \
               -e 's|^\.word 0x[0-9A-Fa-f]{8}( +/\* \.text start \*/)|.word EXE_TEXT_START\1|' \
               -e 's|^\.word 0x[0-9A-Fa-f]{8}( +/\* \.text size \*/)|.word EXE_TEXT_SIZE\1|' \
               "$base.s" > "$BUILD_DIR/header_syms.s"
        $AS -o "$obj" "$BUILD_DIR/header_syms.s"
    elif [[ -f "$base.s" && -n "$LUI_GREP" ]] && grep -q "$LUI_GREP" "$base.s"; then
        sed -E "${LUI_SED[@]}" "$base.s" > "$obj.lui.s"
        $AS -o "$obj" "$obj.lui.s"
    elif [[ -f "$base.s" ]]; then
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
#    They are wrapped in PROVIDE(): a plain assignment in a linker script overrides a label an
#    object already defines (splat lists data labels and alternative entries there too), which
#    would pin it to its retail address. PROVIDE only defines what no object does, so the same
#    addresses result and the defined labels can still move (tools/shift_test.py).
LD_SCRIPTS=()
cat "$BUILD_DIR/undefined_syms_auto.txt" "$BUILD_DIR/undefined_funcs_auto.txt" 2>/dev/null \
    | sed -E 's/^[[:space:]]*([A-Za-z_.$][A-Za-z0-9_.$]*)[[:space:]]*=[[:space:]]*([^;]+);.*/PROVIDE(\1 = \2);/' \
    > "$BUILD_DIR/auto_syms.ld"
LD_SCRIPTS+=(-T "$BUILD_DIR/auto_syms.ld")

# Symbols marked absolute:True (hardware registers, scratchpad) aren't defined by any
# object file. Registry lines ("name = 0xADDR; // ...") are valid linker-script
# assignments once the comment is stripped, so define them that way.
# An overlay also gets ROCK_NEO.EXE's symbols this way (split.sh marks them all absolute).
grep -h 'absolute:True' "$REGISTRY" ${HOST_SYMS:+"$HOST_SYMS"} | sed 's|//.*||' \
    > "$BUILD_DIR/absolute_syms.ld" || true
LD_SCRIPTS+=(-T "$BUILD_DIR/absolute_syms.ld")
# Hand-written symbol definitions that follow the layout (end of BSS and the like).
[[ -f "linker_syms_$TARGET.ld" ]] && LD_SCRIPTS+=(-T "linker_syms_$TARGET.ld")
$LD "${LD_SCRIPTS[@]}" -T "$LD_SCRIPT" -Map "$MAP" -o "$ELF"

# 3. Convert the ELF to a raw binary.
$OBJCOPY -O binary "$ELF" "$BINARY"

# PS-X EXE files are padded with zeros to a multiple of 2048 bytes (one CD sector).
# BSS occupies no file space, so the binary ends at the last data byte; pad it back out.
# An overlay chunk records its exact size, so it isn't padded.
if [[ -z "$IS_OVERLAY" ]]; then
    truncate -s %2048 "$BINARY"
fi

# 4. Compare.
sha1sum "$ORIGINAL" "$BINARY"
if cmp -s "$ORIGINAL" "$BINARY"; then
    echo "MATCH"
else
    echo "MISMATCH"
    cmp "$ORIGINAL" "$BINARY" | head -n 1 || true
    ls -l "$ORIGINAL" "$BINARY"
fi
