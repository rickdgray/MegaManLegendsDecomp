#ifndef STAGE_COMMON_GTE_H
#define STAGE_COMMON_GTE_H

// GTE (geometry coprocessor) access as inline assembly, for the shared stage code. Our own
// macros; the sequences are what the original compiler's GTE macros expand to.

// Load a whole MATRIX (rotation words 0-4, translation words 5-7) from p into control registers
// 0-7, through $12-$14.
#define STCOM_GTE_SET_MATRIX(p)                                                                                                            \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); ctc2 $12, $0; ctc2 $13, $1;"                                                           \
                     "lw $12, 8(%0); lw $13, 12(%0); lw $14, 16(%0);"                                                                      \
                     "ctc2 $12, $2; ctc2 $13, $3; ctc2 $14, $4;"                                                                           \
                     "lw $12, 20(%0); lw $13, 24(%0); ctc2 $12, $5; lw $14, 28(%0);"                                                       \
                     "ctc2 $13, $6; ctc2 $14, $7"                                                                                          \
                     :                                                                                                                     \
                     : "r"(p)                                                                                                              \
                     : "$12", "$13", "$14")

// Load vector 0 (VXY0, VZ0) from a short vector at p.
#define STCOM_GTE_LDV0(p) __asm__ volatile("lwc2 $0, 0(%0); lwc2 $1, 4(%0)" : : "r"(p) : "memory")

// Rotation matrix * V0 plus the translation, into MAC1..MAC3.
#define STCOM_GTE_RTV0TR() __asm__ volatile("nop; nop; mvmva 1, 0, 0, 0, 0")

// Store MAC1..MAC3 (data registers 25-27) to three words at p.
#define STCOM_GTE_STLVNL(p) __asm__ volatile("swc2 $25, 0(%0); swc2 $26, 4(%0); swc2 $27, 8(%0)" : : "r"(p) : "memory")

// Single-vertex perspective transform of V0.
#define STCOM_GTE_RTPS() __asm__ volatile("nop; nop; rtps")

// Store the screen XY of the last transform (data register 14) at p.
#define STCOM_GTE_STSXY(p) __asm__ volatile("swc2 $14, 0(%0)" : : "r"(p) : "memory")

#endif // STAGE_COMMON_GTE_H
