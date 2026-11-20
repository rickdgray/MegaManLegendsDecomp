#!/usr/bin/env bash
# Rebuild one target from splat's output and C sources, and compare it with the original.
# Run tools/split.sh [target] first: the object list comes from splat's linker script.
# Usage: tools/build.sh [target ...]      (or a group: all, executables, overlays)
#   With several targets (e.g. from `tools/reach.py --command`), each prints one line, MATCH or
#   what failed, and the run fails if any doesn't match.
set -euo pipefail
MULTI_TARGET_OK=1
source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"

if [[ ${#TARGET_LIST[@]} -gt 1 ]]; then
    EACH_NEEDS_MATCH=1 each_target "$0" "$@"
    exit
fi

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
# An overlay also gets ROCK_NEO.EXE's symbols this way (split.sh marks them all absolute).
grep -h 'absolute:True' "$REGISTRY" ${HOST_SYMS:+"$HOST_SYMS"} | sed 's|//.*||' \
    > "$BUILD_DIR/absolute_syms.ld" || true
LD_SCRIPTS+=(-T "$BUILD_DIR/absolute_syms.ld")
# An overlay may still use a splat default name (D_800BC744) for a ROCK_NEO.EXE address that the
# registry covers with a larger named object (Sce_camera_work). Such a name is its own address,
# so define any that no object or registry provides.
if [[ -n "$IS_OVERLAY" ]]; then
    grep -o "$BUILD_DIR/[^ )]*\.o" "$LD_SCRIPT" | sort -u | xargs mips-linux-gnu-nm -u 2>/dev/null \
        | sed -nE 's/^ +U (D|func)_([0-9A-F]{8})$/PROVIDE(\1_\2 = 0x\2);/p' | sort -u \
        > "$BUILD_DIR/default_name_syms.ld"
    LD_SCRIPTS+=(-T "$BUILD_DIR/default_name_syms.ld")
fi
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
