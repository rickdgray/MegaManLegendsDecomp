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
