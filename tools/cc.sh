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
    slus_006.03 | rock_neo.exe | r3_*) target=$1; shift ;;
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
# The shim: -G8, cc1's own default (what Capcom got by not passing -G), and no -G to maspsx, so
# nothing is addressed through $gp. The value still matters: it changes GCC's cost estimates, and
# Movie_start only matches with it (it rebuilds &Cd_result before each call instead of keeping it
# in a saved register). Every other shim function matches with -G0 and -G8 alike.
JT_ALIGN=3
DEFINES=""
case "$target" in
    slus_006.03)  GFLAGS="-G8"; MASPSX_EXTRA="" ;;
    rock_neo.exe) GFLAGS="-G32"; MASPSX_EXTRA="-G32 --use-comm-section --max-comm-alignment 4" ;;
    # Overlay code chunks never address anything through $gp, so maspsx gets
    # no -G, as for the shim. cc1 gets the same default -G8 as the shim.
    # Shared stage code (src/stage_common/) finds this stage's copy of its
    # assembly through TARGET_ASM.
    # Overlay files take cc1's own `.align 3` for their jump tables: where retail restarts the
    # 8-byte alignment, the yaml starts a new file. One file still has its alignment rewritten
    # (jt_align below): r3_st03_A594.c.
    r3_*)  GFLAGS="-G8"; MASPSX_EXTRA=""; DEFINES="-DTARGET_ASM=\"asm/$target\""
           case $(basename "$src" .c) in
               # r3_st0d and r3_st0d_4C9C: D_801000F0 and D_80100118 sit in .rodata in function
               # order, after jump tables: -G0.
               r3_st0d) GFLAGS="-G0" ;;
               r3_st0d_4C9C) GFLAGS="-G0" ;;
               # Its local struct initializers sit in .rodata between its jump tables (D_8010014C): -G0.
               r3_st09_5658) GFLAGS="-G0" ;;
               # r3_st0b_1234.c: func_80101FB4's local initializer sits in .rodata in function order (D_801000B8): -G0.
               r3_st0b_1234) GFLAGS="-G0" ;;
               # r3_st0b_9CB0.c: func_8010E36C's local initializer follows the jump tables (D_80100278): -G0.
               # It is the file's last .rodata (10 bytes); retail pads the file's piece to 4 bytes.
               r3_st0b_9CB0) GFLAGS="-G0"; RODATA_ALIGN_END=2 ;;
               # r3_st00_4474.c: func_80105DEC's local initializer sits in .rodata (D_801000CC): -G0.
               r3_st00_4474) GFLAGS="-G0" ;;
               # r3_st03_48E0.c: func_801048E0's constant sits in .rodata before its jump table (0x80100108): -G0.
               r3_st03_48E0) GFLAGS="-G0" ;;
               # r3_st03_A9A8.c: a local initializer sits in .rodata between its jump tables (0x80100294): -G0.
               r3_st03_A9A8) GFLAGS="-G0" ;;
               # r3_st03_A594.c: a zero word follows func_8010A5D0's table, the file's last (0x80100260).
               # No file boundary explains it: see notes/overlays.md, "File boundaries from jump-table
               # alignment", the open point.
               r3_st03_A594) JT_ALIGN=2; JT_PAD_END=func_8010A5D0 ;;
               # r3_st1a, r3_st1a_26224, r3_st1a_2B8E4: their local initializers sit in .rodata in function order
               # (D_80100004, D_8010069C after jtbl_8010066C, D_801006E4).
               r3_st05_5E2C | r3_st1a | r3_st1a_26224 | r3_st1a_2B8E4) GFLAGS="-G0" ;; esac ;;
    *)
        echo "usage: $0 <target> <in.c> <out.o>   (target: slus_006.03, rock_neo.exe, r3_*)" >&2
        exit 2
        ;;
esac

CC1=${CC1:-$ROOT/tools/vendor/gcc-2.7.2-psx/cc1}
MASPSX=$ROOT/tools/vendor/maspsx/maspsx.py

# Per-target headers first, then the shared ones (only headers proven identical in both programs).
CPPFLAGS="-undef -nostdinc -I$ROOT/include/$target -I$ROOT/include $DEFINES"
CC1FLAGS="-quiet -O2 -Wimplicit $GFLAGS ${CC1_EXTRA:-}"
MASPSXFLAGS="--aspsx-version=${ASPSX_VERSION:-2.56} --expand-div $MASPSX_EXTRA"
ASFLAGS="-EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -I$ROOT/include"

# maspsx (ASPSX 2.56 emulation) writes `sltu rd,rs,<negative constant>` as `li $at,K` +
# `sltu rd,rs,$at`, as ASPSX did, but unlike its other $at expansions without `.set noat`, so GNU as
# warns "used $at without .set noat". Wrap the pair; the bytes are the same. (cc1 never names $at,
# so a `li $at,` line can only come from maspsx.)
NOAT_FIX='/^li\t\$at,/ { print ".set\tnoat"; print; getline; print; print ".set\tat"; next } { print }'

mkdir -p "$(dirname "$obj")"
# cc1 aligns each jump table (in .rdata) to 8 bytes. One file still needs a rewrite (the case table
# above): JT_ALIGN=2 makes that 4 bytes, and JT_PAD_END names the functions whose table is
# followed by a zero word.
jt_align() {
    if [[ $JT_ALIGN == 3 ]]; then cat; else
        awk -v a="$JT_ALIGN" -v padend=" ${JT_PAD_END:-} " '
            /^[A-Za-z_][A-Za-z0-9_]*:$/ { fn = substr($0, 1, length($0) - 1) }
            /^\t\.rdata$/ { rd = 1 }
            /^\t\.text$/ { if (rd && index(padend, " " fn " ")) print "\t.word\t0"; rd = 0 }
            /^\t\.align\t3$/ { print "\t.align\t" a; next }
            { print }'
    fi
}

# RODATA_ALIGN_END=N: pad the file's .rodata to a 2^N-byte multiple at its end (a short local
# initializer as the file's last constant).
rodata_align_end() {
    cat
    if [[ -n ${RODATA_ALIGN_END:-} ]]; then printf '\t.rdata\n\t.align\t%s\n' "$RODATA_ALIGN_END"; fi
}

cpp $CPPFLAGS "$src" \
    | "$CC1" $CC1FLAGS \
    | jt_align \
    | rodata_align_end \
    | python3 "$MASPSX" $MASPSXFLAGS \
    | awk "$NOAT_FIX" \
    | mips-linux-gnu-as $ASFLAGS -o "$obj"
