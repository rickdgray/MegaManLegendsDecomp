# Shared by the tools/ scripts: source it with the script's arguments, then drop the target:
#   source "$(dirname "$0")/target.sh" "$@"; shift "$TARGET_ARGC"
# The target is optional: when the first argument isn't a target name, it's rock_neo.exe and
# TARGET_ARGC is 0 (nothing to drop). Changes to the repo root and derives every per-target path.
#
# Targets: the executables, named after their disc file in lower case (slus_006.03,
# rock_neo.exe), and the overlays: every other folder in config/ (r3_st05, r3_shl07, r3_sup), each
# a code chunk inside a CDDATA/DAT/*.BIN archive that its yaml names (`archive:`).
#
# Groups: `all`, `executables`, `overlays`. Several targets or a group fill TARGET_LIST; a script
# that loops over them sets MULTI_TARGET_OK=1 before sourcing (build.sh, rebuild.sh, split.sh), and
# any other script refuses them.

cd "$(dirname "${BASH_SOURCE[0]}")/.."

EXECUTABLES=(slus_006.03 rock_neo.exe)
OVERLAYS=()
for _yaml in config/*/*.yaml; do
    _t=$(basename "$(dirname "$_yaml")")
    [[ "$_yaml" == "config/$_t/$_t.yaml" ]] || continue
    [[ " ${EXECUTABLES[*]} " == *" $_t "* ]] && continue
    OVERLAYS+=("$_t")
done
TARGETS="${EXECUTABLES[*]} ${OVERLAYS[*]}"
DEFAULT_TARGET=rock_neo.exe

# Leading arguments that are targets or groups; the first that isn't ends the list.
TARGET_LIST=()
TARGET_ARGC=0
for _arg in "$@"; do
    case "$_arg" in
        all) TARGET_LIST+=("${EXECUTABLES[@]}" "${OVERLAYS[@]}") ;;
        executables) TARGET_LIST+=("${EXECUTABLES[@]}") ;;
        overlays) TARGET_LIST+=("${OVERLAYS[@]}") ;;
        *)
            if [[ " $TARGETS " == *" $_arg "* ]]; then
                TARGET_LIST+=("$_arg")
            elif [[ "$_arg" =~ ^(r3_[A-Za-z0-9_]+|[A-Za-z0-9_]+\.(exe|[0-9][0-9]))$ ]]; then
                # Shaped like a target but not one (a typo such as r3_st5): don't fall back to the default.
                echo "unknown target '$_arg' (targets: ${EXECUTABLES[*]}, the overlays in config/," \
                    "or the groups all, executables, overlays)" >&2
                exit 2
            else
                break
            fi
            ;;
    esac
    TARGET_ARGC=$((TARGET_ARGC + 1))
done
# Each target once, in the order given.
_seen=" "
_unique=()
for _t in "${TARGET_LIST[@]}"; do
    [[ "$_seen" == *" $_t "* ]] && continue
    _seen+="$_t "
    _unique+=("$_t")
done
TARGET_LIST=("${_unique[@]}")
[[ ${#TARGET_LIST[@]} -eq 0 ]] && TARGET_LIST=("$DEFAULT_TARGET")
if [[ ${#TARGET_LIST[@]} -gt 1 && -z "${MULTI_TARGET_OK:-}" ]]; then
    echo "$(basename "$0") takes one target (several targets and the groups all, executables and" \
        "overlays work with build.sh, rebuild.sh and split.sh)" >&2
    exit 2
fi
TARGET=${TARGET_LIST[0]}

# For a script with several targets: runs `$0 <t> ARGS...` for each one in TARGET_LIST, quietly,
# and prints one line per target, "<t>: MATCH" or what went wrong; returns 1 if any failed.
# With EACH_NEEDS_MATCH=1 a target also fails unless its output has a MATCH line (build.sh prints
# MISMATCH but exits 0).
each_target() {
    local script=$1; shift
    local failed=() t out ok
    for t in "${TARGET_LIST[@]}"; do
        ok=
        if out=$("$script" "$t" "$@" 2>&1); then
            ok=1
            if [[ -n "${EACH_NEEDS_MATCH:-}" ]] && ! grep -qx MATCH <<< "$out"; then
                ok=
            fi
        fi
        if [[ -n "$ok" ]]; then
            echo "$t: $(grep -x MATCH <<< "$out" || echo ok)"
        else
            echo "$t: FAILED: $(grep -m 1 -E 'MISMATCH|[Ee]rror|not found|Refus' <<< "$out" || tail -n 1 <<< "$out")"
            failed+=("$t")
        fi
        # Keep the compiler's warnings visible (they'd otherwise be swallowed with the rest).
        grep -E 'warning:|In function' <<< "$out" | sed 's/^/    /' || true
    done
    if [[ ${#failed[@]} -gt 0 ]]; then
        echo "failed: ${failed[*]}" >&2
        return 1
    fi
}

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

# Overlays: the original is the code chunk tools/extract_overlays.py wrote to disc/overlays/,
# copied by split.sh into build/ (splat's target_path). They link against ROCK_NEO.EXE's symbols
# (HOST_REGISTRY, filtered into HOST_SYMS by split.sh) and, unlike executables, aren't padded to a
# whole sector.
IS_OVERLAY=
if [[ " ${OVERLAYS[*]} " == *" $TARGET "* ]]; then
    IS_OVERLAY=1
    CHUNK=disc/overlays/$(sed -n 's/^archive:[[:space:]]*\([^[:space:]]*\).*/\1/p' "$YAML")
    ORIGINAL=$BUILD_DIR/original/$TARGET.bin
    BINARY=$BUILD_DIR/$TARGET.bin
    HOST_REGISTRY=config/rock_neo.exe/symbol_addrs.txt
    HOST_SYMS=$BUILD_DIR/rock_neo_syms.txt
fi
