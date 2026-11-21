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
    # r3_st17.c, r3_st02.c, r3_st04_5474.c, r3_st04_8FE0.c, r3_st06_D1F8.c, r3_st16.c, r3_st1b_603C.c, r3_st1a_CBC.c
    # r3_st14.c and r3_st00.c pack their
    # jump tables at 4-byte alignment (st17: 0x8010002C, then 0x80100040; st02: jtbl_80100020;
    # st04: 0x80100034, then 0x801000A0; st04_8FE0: 0x8010019C, then 0x801001B0; st06_D1F8: 0x80100348, then 0x80100364; st16: 0x80100004;
    # st1b: jtbl_801000AC after an assembly table; st1a_CBC: 0x8010000C, 0x80100020, 0x8010003C;
    # st00: 0x80100004, 0x80100018, 0x80100038, 0x80100058; st14: 0x80100004, then 0x80100018;
    # st05_2A920: 0x8010080C, 0x80100860,
    # 0x80100874), where cc1's `.align 3` would pad them
    # (jt_align below); r3_st17_1475C.c and r3_st1e need that padding.
    r3_*)  GFLAGS="-G8"; MASPSX_EXTRA=""; DEFINES="-DTARGET_ASM=\"asm/$target\""
           case $(basename "$src" .c) in r3_st17 | r3_st14 | r3_st02 | r3_st04_5474 | r3_st04_8FE0 | r3_st16 | r3_st1b_603C | r3_st03_C66C | r3_st1a_CBC | r3_st00 | r3_st05_2A920) JT_ALIGN=2 ;; r3_st1d | r3_st1b_E5C | r3_st08) JT_FILE_OFFSET=4 ;;
               # r3_st0d and r3_st0d_4C9C: D_801000F0 and D_80100118 sit in .rodata in function
               # order, after jump tables: -G0. r3_st0d.c aligns its tables to 8 bytes within
               # its own .rodata (jtbl_80100054 after a pad word), counting assembly tables.
               r3_st0d) JT_FILE_OFFSET=0; JT_ASM_COUNT=1; GFLAGS="-G0" ;;
               r3_st0d_4C9C) GFLAGS="-G0" ;;
               r3_st05_16DA4 | r3_st06_15F34) JT_FILE_OFFSET=4; JT_ASM_COUNT=1 ;;
               # r3_st06.c: some of its C tables sit 8-aligned within the file (jtbl_8010008C,
               # jtbl_801000A4, jtbl_801001B4, jtbl_801001CC, jtbl_801001E4).
               # func_80105D20's table packs at 4 bytes (jtbl_801000D4, right after jtbl_80100090's file).
               r3_st06) JT_FILE_OFFSET=4; JT_ASM_COUNT=1
                        JT_FILE_ALIGN="func_8010246C func_801026CC func_80107B94 func_80107F24 func_801081B0"
                        JT_FILE_PACKED="func_80105D20" ;;
               # A zero word follows some C tables: jtbl_8010038C (then 0x801003BC) and jtbl_80100330
               # (then 0x80100348).
               r3_st06_1227C) JT_ALIGN=2; JT_PAD_AFTER=func_801125AC ;;
               r3_st06_D1F8) JT_ALIGN=2; JT_PAD_AFTER=func_8010FF90 ;;
               # Its local struct initializers sit in .rodata between its jump tables (D_8010014C): -G0.
               r3_st09_5658) GFLAGS="-G0" ;;
               # r3_st0b.c: its .rodata starts at 0x80100004, after the id word (jtbl_80100030 is 8-aligned
               # in the module, after two assembly tables).
               # func_80101FB4's local initializer sits in .rodata in function order (D_801000B8): -G0.
               r3_st0b) JT_FILE_OFFSET=4; JT_ASM_COUNT=1; GFLAGS="-G0" ;;
               # r3_st0b_9CB0.c: func_8010E36C's local initializer follows the jump tables (D_80100278): -G0.
               # It is the file's last .rodata (10 bytes); retail pads the file's piece to 4 bytes.
               r3_st0b_9CB0) GFLAGS="-G0"; RODATA_ALIGN_END=2 ;;
               # r3_st00_76E8.c: its .rodata starts at 0x8010013C; its later tables sit at 8-byte
               # boundaries in the module, the assembly ones with their own pad words (jtbl_80100210),
               # but those of func_80109180 to func_80109F6C at 8-byte boundaries within the file
               # (jtbl_80100154): two of Capcom's files, each aligning its own tables.
               r3_st00_76E8) JT_FILE_OFFSET=4; JT_ASM_COUNT=1
                             JT_FILE_ALIGN="func_80109180 func_80109638 func_801098F0 func_80109BD8 func_80109F6C" ;;
               # r3_st00_4474.c: func_80105DEC's local initializer sits in .rodata (D_801000CC): -G0.
               r3_st00_4474) GFLAGS="-G0" ;;
               r3_st1a_FDE0) JT_UNALIGNED="func_80113460 func_8011C870 func_8011CE4C func_8011DA38 func_8011DCD8"
                             JT_PACKED="func_80113EE8 func_801146D8 func_80114E90 func_80115B48 func_8011D240 func_8011DE9C" ;;
               r3_st05_11898) JT_PACKED="func_80113E6C" ;;
               # r3_st0b_166EC.c: func_80118D40's table packs at 4 bytes (jtbl_80100364).
               r3_st0b_166EC) JT_PACKED="func_80118D40" ;;
               # r3_st03_3CC4.c: a zero word follows func_80106BBC's table (jtbl_801001E8).
               r3_st03_3CC4) GFLAGS="-G0"; JT_ALIGN=2; JT_PAD_AFTER="func_801065F8 func_80106BBC"; JT_PAD_END=func_80104D04 ;;
               r3_st03_A9A8) GFLAGS="-G0"; JT_ALIGN=2 ;;
               # r3_st03_A594.c: a zero word follows func_8010A5D0's table, the file's last
               # (0x80100260).
               r3_st03_A594) JT_ALIGN=2; JT_PAD_END=func_8010A5D0 ;;
               # r3_st03.c packs its tables at 4 bytes from 0x80100004; a zero word follows
               # func_8010263C's (jtbl_80100054, then 0x8010008C).
               r3_st03) JT_ALIGN=2; JT_PAD_AFTER=func_8010263C ;;
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
CPPFLAGS="-P -undef -nostdinc -I$ROOT/include/$target -I$ROOT/include $DEFINES"
CC1FLAGS="-quiet -O2 -Wimplicit $GFLAGS ${CC1_EXTRA:-}"
MASPSXFLAGS="--aspsx-version=${ASPSX_VERSION:-2.56} --expand-div $MASPSX_EXTRA"
ASFLAGS="-EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -I$ROOT/include"

# maspsx (ASPSX 2.56 emulation) writes `sltu rd,rs,<negative constant>` as `li $at,K` +
# `sltu rd,rs,$at`, as ASPSX did, but unlike its other $at expansions without `.set noat`, so GNU as
# warns "used $at without .set noat". Wrap the pair; the bytes are the same. (cc1 never names $at,
# so a `li $at,` line can only come from maspsx.)
NOAT_FIX='/^li\t\$at,/ { print ".set\tnoat"; print; getline; print; print ".set\tat"; next } { print }'

mkdir -p "$(dirname "$obj")"
# cc1 aligns each jump table (in .rdata) to 8 bytes; JT_ALIGN=2 makes that 4 bytes.
# Retail aligns a function's later jump tables to 8 bytes relative to its first one (each
# function's .rodata piece is laid out on its own): st17's func_8010421C pads its second table
# from 0x8010012C to 0x80100130. So the first table of each function gets JT_ALIGN, and a later
# one gets a pad word when the function's tables so far aren't a multiple of 8 bytes.
# JT_FILE_OFFSET instead aligns every table but the file's first to 8 bytes in the module, for a
# file whose .rodata starts that many bytes past an 8-byte boundary (r3_st1d.c's starts at
# 0x80100004, after the id word; its first table stays there, the later ones are padded to
# 0x80100098, 0x801000B0 and 0x801000C8). It counts the file's own .rodata only, so it needs
# every table of the file in C, or the assembly ones first and a multiple of 8 bytes past an
# 8-byte boundary in the module (r3_st1b_E5C.c: jtbl_80100024 in assembly, then jtbl_80100040;
# r3_st08.c: its .rodata starts at 0x8010000C, after the id word and an .sdata initializer).
# JT_ASM_COUNT=1 also counts the .rodata words of each included assembly file and pads before
# one whose tables would start misaligned, so C and assembly tables can alternate (r3_st05_16DA4.c:
# its first table at 0x801004E4, every later one, assembly or C, at an 8-byte boundary;
# r3_st06_15F34.c: jtbl_80100428 between assembly tables, padded to 0x80100448). An
# assembly file that starts its tables with its own `.align 3` is aligned within the file instead
# (r3_st06.c: jtbl_8010008C).
jt_align() {
    if [[ -n ${JT_FILE_OFFSET:-} ]]; then
        awk -v off="$JT_FILE_OFFSET" -v asmcount="${JT_ASM_COUNT:-}" -v root="$ROOT" \
            -v filealign=" ${JT_FILE_ALIGN:-} " -v filepacked=" ${JT_FILE_PACKED:-} " '
            # The words an included assembly file adds to .rodata (its jump tables, with
            # their own trailing pad words).
            function asm_words(path,    line, r, n) {
                r = 0; n = 0; asm_align = 0
                while ((getline line < path) > 0) {
                    if (line ~ /^\.section[ \t]+\.rodata/) r = 1
                    else if (line ~ /^\.section[ \t]+\.text/) r = 0
                    else if (r && n == 0 && line ~ /^\.align[ \t]+3/) asm_align = 1
                    else if (r && line ~ /\.word[ \t]/) n++
                }
                close(path)
                return n
            }
            /^\t\.rdata$/ { rd = 1 }
            /^\t\.text$/ { rd = 0 }
            rd && /^\t\.word\t/ { size += 4 }
            # Local initializers (r3_st0d: func_80100BA4) are halves or bytes.
            rd && /^\t\.half\t/ { size += 2 }
            rd && /^\t\.byte\t/ { size += 1 }
            asmcount && /\.include "asm\// {
                match($0, /"[^"]*"/)
                n = asm_words(root "/" substr($0, RSTART + 1, RLENGTH - 2))
                if (n > 0 && asm_align) {
                    # Its own .align 3: 8 bytes within the file, not the module.
                    if (size % 8) size += 4
                    size += 4 * n
                    seen = 1
                } else if (n > 0) {
                    if (seen && (off + size) % 8) {
                        print "\t.section .rodata # maspsx-keep"
                        print "\t.word 0 # maspsx-keep"
                        print "\t.section .text # maspsx-keep"
                        size += 4
                    }
                    size += 4 * n
                    seen = 1
                }
            }
            /^[A-Za-z_][A-Za-z0-9_]*:$/ { fn = substr($0, 1, length($0) - 1) }
            /^\t\.align\t3$/ {
                print "\t.align\t2"
                # JT_FILE_ALIGN: the functions whose jump tables are aligned to 8 bytes within the
                # file instead, as an assembly file with its own `.align 3` is.
                if (index(filealign, " " fn " ")) { if (size % 8) { print "\t.word\t0"; size += 4 } }
                # JT_FILE_PACKED: the functions whose jump table retail leaves at 4-byte alignment.
                else if (index(filepacked, " " fn " ")) { }
                else if (seen && (off + size) % 8) { print "\t.word\t0"; size += 4 }
                seen = 1
                next
            }
            { print }'
    elif [[ $JT_ALIGN == 3 && ( -n ${JT_UNALIGNED:-} || -n ${JT_PACKED:-} ) ]]; then
        # JT_UNALIGNED: the functions whose jump table retail packs at 4-byte alignment with a zero
        # word after it, among 8-byte aligned ones (r3_st1a_FDE0.c: jtbl_801001A8, jtbl_80100400,
        # jtbl_80100428, jtbl_80100490 and jtbl_801004B8, each followed by its zero word).
        # JT_PACKED: the same without the zero word (r3_st05_11898.c: jtbl_801004B8, its last table;
        # r3_st1a_FDE0.c: jtbl_801001F0, jtbl_80100238, jtbl_80100258, jtbl_801002B0,
        # jtbl_80100450 and jtbl_801004E0).
        awk -v list=" ${JT_UNALIGNED:-} " -v packed=" ${JT_PACKED:-} " '
            /^[A-Za-z_][A-Za-z0-9_]*:$/ { fn = substr($0, 1, length($0) - 1) }
            /^\t\.rdata$/ { rd = 1 }
            /^\t\.text$/ { if (pad) { print "\t.word\t0"; pad = 0 } rd = 0 }
            /^\t\.align\t3$/ && index(list, " " fn " ") { print "\t.align\t2"; pad = 1; next }
            /^\t\.align\t3$/ && index(packed, " " fn " ") { print "\t.align\t2"; next }
            { print }'
    elif [[ $JT_ALIGN == 3 ]]; then cat; else
        awk -v a="$JT_ALIGN" -v padafter=" ${JT_PAD_AFTER:-} " -v padend=" ${JT_PAD_END:-} " '
            /^[A-Za-z_][A-Za-z0-9_]*:$/ { first = 1; size = 0; fn = substr($0, 1, length($0) - 1) }
            /^\t\.rdata$/ { rd = 1 }
            # JT_PAD_END: the functions whose jump table retail follows with a zero word right away
            # (an assembly table or the end of the file comes next).
            /^\t\.text$/ { if (rd && index(padend, " " fn " ")) print "\t.word\t0"; rd = 0 }
            rd && /^\t\.word\t/ { size += 4 }
            /^\t\.align\t3$/ {
                # JT_PAD_AFTER: the functions whose (last) jump table retail follows with a zero word
                # (written before the next C table).
                if (lastfn != "" && index(padafter, " " lastfn " ")) print "\t.word\t0"
                lastfn = fn
                print "\t.align\t" a
                if (!first && size % 8) { print "\t.word\t0"; size += 4 }
                first = 0
                next
            }
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
