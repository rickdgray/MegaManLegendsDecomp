#ifndef PSYQ_INLINE_C_H
#define PSYQ_INLINE_C_H

/*
 * GTE (geometry coprocessor, COP2) inline macros, as Capcom's code used them: the names of PsyQ's
 * inline_c.h, each expanding to the instruction sequence found in the game. Self-written, not a
 * copy of Sony's header: add a macro only when a function needs it, and check its sequence
 * (registers, nops, order) against that function's assembly.
 *
 * GCC 2.7 can't schedule across these (they are volatile asm), so their order in C is the order
 * in the binary. Scratch registers are $12-$14 (t4-t6), declared as clobbered.
 *
 * Register numbers: data registers 0/1 = VXY0/VZ0, 14 = SXY2, 19 = SZ3; control registers 0-4 =
 * rotation matrix, 5-7 = translation vector.
 */

#include "psyq/libgte.h"

// Load the rotation matrix of r0 (MATRIX *) into the GTE.
#define gte_SetRotMatrix(r0)                                                                                                               \
    __asm__ volatile("lw $12, 0(%0)\n\t"                                                                                                   \
                     "lw $13, 4(%0)\n\t"                                                                                                   \
                     "ctc2 $12, $0\n\t"                                                                                                    \
                     "ctc2 $13, $1\n\t"                                                                                                    \
                     "lw $12, 8(%0)\n\t"                                                                                                   \
                     "lw $13, 12(%0)\n\t"                                                                                                  \
                     "lw $14, 16(%0)\n\t"                                                                                                  \
                     "ctc2 $12, $2\n\t"                                                                                                    \
                     "ctc2 $13, $3\n\t"                                                                                                    \
                     "ctc2 $14, $4"                                                                                                        \
                     :                                                                                                                     \
                     : "r"(r0)                                                                                                             \
                     : "$12", "$13", "$14")

// Load the translation vector of r0 (MATRIX *, t[] at +0x14) into the GTE.
#define gte_SetTransMatrix(r0)                                                                                                             \
    __asm__ volatile("lw $12, 20(%0)\n\t"                                                                                                  \
                     "lw $13, 24(%0)\n\t"                                                                                                  \
                     "ctc2 $12, $5\n\t"                                                                                                    \
                     "lw $14, 28(%0)\n\t"                                                                                                  \
                     "ctc2 $13, $6\n\t"                                                                                                    \
                     "ctc2 $14, $7"                                                                                                        \
                     :                                                                                                                     \
                     : "r"(r0)                                                                                                             \
                     : "$12", "$13", "$14")

// Load vector 0 from r0 (SVECTOR *).
#define gte_ldv0(r0)                                                                                                                       \
    __asm__ volatile("lwc2 $0, 0(%0)\n\t"                                                                                                  \
                     "lwc2 $1, 4(%0)"                                                                                                      \
                     :                                                                                                                     \
                     : "r"(r0))

// Rotate, translate and perspective-transform vector 0 (RTPS). The two nops let the loads settle.
#define gte_rtps()                                                                                                                         \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x0180001")

// Load vectors 0-2 from r0 (SVECTOR[3]).
#define gte_ldv3c(r0)                                                                                                                      \
    __asm__ volatile("lwc2 $0, 0(%0)\n\t"                                                                                                  \
                     "lwc2 $1, 4(%0)\n\t"                                                                                                  \
                     "lwc2 $2, 8(%0)\n\t"                                                                                                  \
                     "lwc2 $3, 12(%0)\n\t"                                                                                                 \
                     "lwc2 $4, 16(%0)\n\t"                                                                                                 \
                     "lwc2 $5, 20(%0)"                                                                                                     \
                     :                                                                                                                     \
                     : "r"(r0))

// Load the color RGBC from r0 (CVECTOR *).
#define gte_ldrgb(r0) __asm__ volatile("lwc2 $6, 0(%0)" : : "r"(r0))

// Rotate and translate vector 0 (MVMVA: rotation matrix, V0, translation; result in MAC1-3).
#define gte_rt()                                                                                                                           \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x0480012")

// Rotate, translate and perspective-transform vectors 0-2 (RTPT).
#define gte_rtpt()                                                                                                                         \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x0280030")

// Depth-cue the color RGBC by IR0 (DPCS).
#define gte_dpcs()                                                                                                                         \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x0780010")

// Store MAC1-3 to r0 (VECTOR *).
#define gte_stlvnl(r0)                                                                                                                     \
    __asm__ volatile("swc2 $25, 0(%0)\n\t"                                                                                                 \
                     "swc2 $26, 4(%0)\n\t"                                                                                                 \
                     "swc2 $27, 8(%0)"                                                                                                     \
                     :                                                                                                                     \
                     : "r"(r0)                                                                                                             \
                     : "memory")

// Store the screen XY of vertex 0 (SXY0) / vertex 1 (SXY1) to r0 (DVECTOR *).
#define gte_stsxy0(r0) __asm__ volatile("swc2 $12, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy1(r0) __asm__ volatile("swc2 $13, 0(%0)" : : "r"(r0) : "memory")

// Store the color FIFO's newest entry (RGB2) to r0 (CVECTOR *).
#define gte_strgb(r0) __asm__ volatile("swc2 $22, 0(%0)" : : "r"(r0) : "memory")

// Load the screen XYs of three vertices from r0, r1, r2 (long *), in PsyQ's order: SXY0, SXY2,
// SXY1.
#define gte_ldsxy3(r0, r1, r2)                                                                                                             \
    __asm__ volatile("lwc2 $12, 0(%0)\n\t"                                                                                                 \
                     "lwc2 $14, 0(%2)\n\t"                                                                                                 \
                     "lwc2 $13, 0(%1)"                                                                                                     \
                     :                                                                                                                     \
                     : "r"(r0), "r"(r1), "r"(r2))

// Load the screen Zs of three / four vertices (values) into SZ1-SZ3 / SZ0-SZ3.
#define gte_ldsz3(r0, r1, r2)                                                                                                              \
    __asm__ volatile("mtc2 %0, $17\n\t"                                                                                                    \
                     "mtc2 %1, $18\n\t"                                                                                                    \
                     "mtc2 %2, $19"                                                                                                        \
                     :                                                                                                                     \
                     : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldsz4(r0, r1, r2, r3)                                                                                                          \
    __asm__ volatile("mtc2 %0, $16\n\t"                                                                                                    \
                     "mtc2 %1, $17\n\t"                                                                                                    \
                     "mtc2 %2, $18\n\t"                                                                                                    \
                     "mtc2 %3, $19"                                                                                                        \
                     :                                                                                                                     \
                     : "r"(r0), "r"(r1), "r"(r2), "r"(r3))

// Load one input-vector half (a value: XY or Z) into V0-V2. Not Sony names: the Inline
// Programming Reference has no single-register loads for V0-V2 (only gte_ldsz3/gte_ldsz4 for SZ),
// so these are named after gtereg.h's data registers C2_VXY0 ... C2_VZ2.
#define gte_ldVXY0(r0) __asm__ volatile("mtc2 %0, $0" : : "r"(r0))
#define gte_ldVZ0(r0)  __asm__ volatile("mtc2 %0, $1" : : "r"(r0))
#define gte_ldVXY1(r0) __asm__ volatile("mtc2 %0, $2" : : "r"(r0))
#define gte_ldVZ1(r0)  __asm__ volatile("mtc2 %0, $3" : : "r"(r0))
#define gte_ldVXY2(r0) __asm__ volatile("mtc2 %0, $4" : : "r"(r0))
#define gte_ldVZ2(r0)  __asm__ volatile("mtc2 %0, $5" : : "r"(r0))

// Read SZ1 / SZ2 / SZ3 into a variable, one at a time. Not Sony names: Sony's gtemac.h reads the
// FIFO with read_sz_fifo3 (all three at once), but the game interleaves each mfc2 with its store
// (mesh_draw), and gte_stsz3 stores words to memory. Named after gtereg.h's C2_SZ1 ... C2_SZ3.
#define gte_getSZ1(r0) __asm__ volatile("mfc2 %0, $17" : "=r"(r0))
#define gte_getSZ2(r0) __asm__ volatile("mfc2 %0, $18" : "=r"(r0))
#define gte_getSZ3(r0) __asm__ volatile("mfc2 %0, $19" : "=r"(r0))

// RTPT without the leading nops (Sony's "_b" suffix), for code that has already spaced its loads
// (mesh_draw).
#define gte_rtpt_b() __asm__ volatile("cop2 0x0280030")

// Normal clipping (NCLIP): the winding of SXY0-2, into MAC0 (> 0: facing the camera).
#define gte_nclip()                                                                                                                        \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x1400006")

// Average of SZ1-3 / SZ0-3, scaled by ZSF3 / ZSF4, into OTZ (AVSZ3 / AVSZ4).
#define gte_avsz3()                                                                                                                        \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x158002D")
#define gte_avsz4()                                                                                                                        \
    __asm__ volatile("nop\n\t"                                                                                                             \
                     "nop\n\t"                                                                                                             \
                     "cop2 0x168002E")

// Store SXY0-2 to r0 (long[3]).
#define gte_stsxy3c(r0)                                                                                                                    \
    __asm__ volatile("swc2 $12, 0(%0)\n\t"                                                                                                 \
                     "swc2 $13, 4(%0)\n\t"                                                                                                 \
                     "swc2 $14, 8(%0)"                                                                                                     \
                     :                                                                                                                     \
                     : "r"(r0)                                                                                                             \
                     : "memory")

// Store SXY0-2 to the first three vertices of r0 (POLY_FT3 * / POLY_FT4 *).
#define gte_stsxy3_ft3(r0)                                                                                                                 \
    __asm__ volatile("swc2 $12, 8(%0)\n\t"                                                                                                 \
                     "swc2 $13, 16(%0)\n\t"                                                                                                \
                     "swc2 $14, 24(%0)"                                                                                                    \
                     :                                                                                                                     \
                     : "r"(r0)                                                                                                             \
                     : "memory")
#define gte_stsxy3_ft4(r0) gte_stsxy3_ft3(r0)

// Store the ordering-table Z (OTZ) to r0 (long *).
#define gte_stotz(r0) __asm__ volatile("swc2 $7, 0(%0)" : : "r"(r0) : "memory")

// Store the screen XY of the result (SXY2) to r0 (long *).
#define gte_stsxy(r0) __asm__ volatile("swc2 $14, 0(%0)" : : "r"(r0) : "memory")

// Store the ordering-table Z (SZ3 / 4) to r0 (long *).
#define gte_stszotz(r0)                                                                                                                    \
    __asm__ volatile("mfc2 $12, $19\n\t"                                                                                                   \
                     "nop\n\t"                                                                                                             \
                     "sra $12, $12, 2\n\t"                                                                                                 \
                     "sw $12, 0(%0)"                                                                                                       \
                     :                                                                                                                     \
                     : "r"(r0)                                                                                                             \
                     : "$12", "memory")

#endif // PSYQ_INLINE_C_H
