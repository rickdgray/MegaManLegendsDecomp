#!/usr/bin/env bash
# Compile one C file with the PsyQ 4.0-equivalent toolchain:
#   cpp -> gcc 2.7.2-psx cc1 -> maspsx (ASPSX 2.56) -> GNU as
# Usage: tools/cc.sh src/foo.c build/src/foo.o
set -euo pipefail

src=$1
obj=$2
ROOT=$(cd "$(dirname "$0")/.." && pwd)

CC1=$ROOT/tools/vendor/gcc-2.7.2-psx/cc1
MASPSX=$ROOT/tools/vendor/maspsx/maspsx.py

CPPFLAGS="-P -undef -nostdinc -I$ROOT/include"
CC1FLAGS="-quiet -O2 -G0"                       # cc1 defaults to -G8; -G0 is required
MASPSXFLAGS="--aspsx-version=2.56 --expand-div"
ASFLAGS="-EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -I$ROOT/include"

mkdir -p "$(dirname "$obj")"
cpp $CPPFLAGS "$src" \
    | "$CC1" $CC1FLAGS \
    | python3 "$MASPSX" $MASPSXFLAGS \
    | mips-linux-gnu-as $ASFLAGS -o "$obj"