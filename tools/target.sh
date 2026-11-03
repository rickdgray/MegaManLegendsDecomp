# Shared by the tools/ scripts: source it with the target name as $1.
#   source "$(dirname "$0")/target.sh" "$1"; shift
# Changes to the repo root and derives every per-target path from the target name.
# Targets are named after their disc file in lower case: slus_006.03, rock_neo.exe.

TARGETS="slus_006.03 rock_neo.exe"

cd "$(dirname "${BASH_SOURCE[0]}")/.."

TARGET=${1:-}
if [[ -z "$TARGET" ]] || [[ " $TARGETS " != *" $TARGET "* ]]; then
    echo "usage: $0 <target> ...   (target: ${TARGETS// /, })" >&2
    exit 2
fi

YAML=$TARGET.yaml                       # splat config
REGISTRY=symbol_addrs_$TARGET.txt       # hand-maintained symbol registry
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
