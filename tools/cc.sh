#!/usr/bin/env bash
# Compile one C file with the PsyQ 4.0-equivalent toolchain:
#   cpp -> gcc 2.7.2-psx cc1 -> maspsx (ASPSX 2.56) -> GNU as
# Usage: tools/cc.sh [target] src/<target>/foo.c build/<target>/src/<target>/foo.o
#
# Optional overrides, for toolchain experiments only (the matching build uses none):
#   CC1_EXTRA="-fno-foo"      extra cc1 flags, appended after the defaults
#   CC1=/path/to/other/cc1    a different compiler build
#   ASPSX_VERSION=2.67        a different assembler version for maspsx to emulate
set -euo pipefail

# The target is optional (rock_neo.exe when the first argument isn't a target name).
case "${1:-}" in
    slus_006.03 | rock_neo.exe) target=$1; shift ;;
    *) target=rock_neo.exe ;;
esac
src=${1:-}
obj=${2:-}
ROOT=$(cd "$(dirname "$0")/.." && pwd)

if [[ -z "$src" || -z "$obj" ]]; then
    echo "usage: $0 [target] <in.c> <out.o>" >&2
    exit 2
fi

# Per-target code-generation flags. GFLAGS goes to cc1; MASPSX_EXTRA to maspsx. GNU as always
# gets -G0: ASPSX addresses $gp only for symbols in the file's own .sdata/.sbss (maspsx, given
# -G32, emits those as explicit %gp_rel), never for .extern symbols. GNU as with -G would also
# use $gp for every small .extern, which ROCK_NEO's code does not do.
# ROCK_NEO's limit is 32 bytes: string literals of 20-28 bytes sit in .sdata, a 33-byte one
# (scene's paths) in .rodata (notes/toolchain.md).
# --use-comm-section: a tentative definition (`sint32 x;`, no `extern`) stays a common symbol, as
# ASPSX left it for the linker's pool (0x80098788-); without it maspsx defines it locally in the
# file's .sbss. The pool itself stays assembly, and its definition wins over the common.
# --max-comm-alignment 4: maspsx gives a common GNU as's implicit alignment (size rounded up to a
# power of two, up to 16), but psylink packed the pool without that (D_80098AA8, 16 bytes,
# sits at 0x80098AA8). The asm definition is 4-aligned, so a multi-word common (moji's
# D_800989E0[4]) made ld warn "alignment 4 ... is smaller than 16". The bytes never depended on it.
case "$target" in
    slus_006.03)  GFLAGS="-G0"; MASPSX_EXTRA="" ;;
    rock_neo.exe) GFLAGS="-G32"; MASPSX_EXTRA="-G32 --use-comm-section --max-comm-alignment 4" ;;
    *)
        echo "usage: $0 <target> <in.c> <out.o>   (target: slus_006.03, rock_neo.exe)" >&2
        exit 2
        ;;
esac

CC1=${CC1:-$ROOT/tools/vendor/gcc-2.7.2-psx/cc1}
MASPSX=$ROOT/tools/vendor/maspsx/maspsx.py

# Per-target headers first, then the shared ones (only headers proven identical in both programs).
CPPFLAGS="-P -undef -nostdinc -I$ROOT/include/$target -I$ROOT/include"
CC1FLAGS="-quiet -O2 -Wimplicit $GFLAGS ${CC1_EXTRA:-}"
MASPSXFLAGS="--aspsx-version=${ASPSX_VERSION:-2.56} --expand-div $MASPSX_EXTRA"
ASFLAGS="-EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -I$ROOT/include"

# maspsx (ASPSX 2.56 emulation) writes `sltu rd,rs,<negative constant>` as `li $at,K` +
# `sltu rd,rs,$at`, as ASPSX did, but unlike its other $at expansions without `.set noat`, so GNU as
# warns "used $at without .set noat". Wrap the pair; the bytes are the same. (cc1 never names $at,
# so a `li $at,` line can only come from maspsx.)
NOAT_FIX='/^li\t\$at,/ { print ".set\tnoat"; print; getline; print; print ".set\tat"; next } { print }'

mkdir -p "$(dirname "$obj")"
cpp $CPPFLAGS "$src" \
    | "$CC1" $CC1FLAGS \
    | python3 "$MASPSX" $MASPSXFLAGS \
    | awk "$NOAT_FIX" \
    | mips-linux-gnu-as $ASFLAGS -o "$obj"
