# Shared by the tools/ scripts: source it with the script's arguments, then drop the target:
#   source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"
# The target is optional: when the first argument isn't a target name, it's rock_neo.exe and
# TARGET_ARGC is 0 (nothing to drop). Changes to the repo root and derives every per-target path.
# Targets are named after their disc file in lower case: slus_006.03, rock_neo.exe.
# Overlay targets are code chunks inside CDDATA/DAT/*.BIN archives, named after the chunk without
# its .bin (r3_shl07); tools/overlays.txt (from tools/overlay_gen.py) says which archive holds each.

declare -A OVERLAY_ARCHIVE=()
OVERLAY_TARGETS=""
while read -r _t _archive _rest; do
    [[ -z "$_t" || "$_t" == \#* ]] && continue
    OVERLAY_ARCHIVE[$_t]=$_archive
    OVERLAY_TARGETS+=" $_t"
done < "$(dirname "${BASH_SOURCE[0]}")/overlays.txt"

TARGETS="slus_006.03 rock_neo.exe$OVERLAY_TARGETS"
DEFAULT_TARGET=rock_neo.exe

cd "$(dirname "${BASH_SOURCE[0]}")/.."

if [[ -n "${1:-}" ]] && [[ " $TARGETS " == *" $1 "* ]]; then
    TARGET=$1
    TARGET_ARGC=1
elif [[ "${1:-}" =~ ^(r3_[A-Za-z0-9_]+|[A-Za-z0-9_]+\.(exe|[0-9][0-9]))$ ]]; then
    # Shaped like a target but not one (a typo such as r3_st5): don't fall back to the default.
    echo "unknown target '$1' (targets: slus_006.03, rock_neo.exe, overlays in tools/overlays.txt)" >&2
    exit 2
else
    TARGET=$DEFAULT_TARGET
    TARGET_ARGC=0
fi

YAML=config/$TARGET/$TARGET.yaml        # splat config
REGISTRY=config/$TARGET/symbol_addrs.txt  # hand-maintained symbol registry
SRC_DIR=src/$TARGET
ASM_DIR=asm/$TARGET
BUILD_DIR=build/$TARGET                 # must match build_path in $YAML
EXPECTED_DIR=expected/$TARGET
LD_SCRIPT=$BUILD_DIR/$TARGET.ld         # written by splat (ld_script_path)
ELF=$BUILD_DIR/$TARGET.elf
MAP=$BUILD_DIR/$TARGET.map
DISC_NAME=${TARGET^^}                   # slus_006.03 -> SLUS_006.03
ORIGINAL=disc/extracted/$DISC_NAME
BINARY=$BUILD_DIR/$DISC_NAME            # the final binary keeps the disc file's name

# Overlays: the original is the chunk's contents, extracted by split.sh into build/ (game data,
# never tracked). They link against ROCK_NEO.EXE's symbols (HOST_REGISTRY, filtered into
# HOST_SYMS by split.sh) and, unlike executables, aren't padded to a whole sector.
IS_OVERLAY=
if [[ -n "${OVERLAY_ARCHIVE[$TARGET]:-}" ]]; then
    IS_OVERLAY=1
    ARCHIVE=disc/extracted/CDDATA/DAT/${OVERLAY_ARCHIVE[$TARGET]}
    ORIGINAL=$BUILD_DIR/original/$TARGET.bin
    BINARY=$BUILD_DIR/$TARGET.bin
    HOST_REGISTRY=config/rock_neo.exe/symbol_addrs.txt
    HOST_SYMS=$BUILD_DIR/rock_neo_syms.txt
fi
