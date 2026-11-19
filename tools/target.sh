# Shared by the tools/ scripts: source it with the script's arguments, then drop the target:
#   source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"
# The target is optional: when the first argument isn't a target name, it's rock_neo.exe and
# TARGET_ARGC is 0 (nothing to drop). Changes to the repo root and derives every per-target path.
# Targets are named after their disc file in lower case: slus_006.03, rock_neo.exe.

TARGETS="slus_006.03 rock_neo.exe"
DEFAULT_TARGET=rock_neo.exe

cd "$(dirname "${BASH_SOURCE[0]}")/.."

if [[ -n "${1:-}" ]] && [[ " $TARGETS " == *" $1 "* ]]; then
    TARGET=$1
    TARGET_ARGC=1
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
