#ifndef GTE_INLINE_H
#define GTE_INLINE_H

// GTE (geometry coprocessor) access written as inline assembly. These are our own macros;
// the instruction sequences are what the original compiler's GTE macros expand to.

// Load a coprocessor-2 data register from memory (lwc2 $n, 0(p))
#define GTE_LWC2(n, p) __asm__ volatile("lwc2 $" #n ", 0(%0)" : : "r"(p) : "memory")
// Store a coprocessor-2 data register to memory (swc2 $n, 0(p))
#define GTE_SWC2(n, p) __asm__ volatile("swc2 $" #n ", 0(%0)" : : "r"(p) : "memory")
// Same with an immediate byte offset
#define GTE_LWC2_OFF(n, off, p) __asm__ volatile("lwc2 $" #n ", " #off "(%0)" : : "r"(p) : "memory")
#define GTE_SWC2_OFF(n, off, p) __asm__ volatile("swc2 $" #n ", " #off "(%0)" : : "r"(p) : "memory")
// Move to/from coprocessor-2 registers
#define GTE_CTC2(n, v) __asm__ volatile("ctc2 %0, $" #n : : "r"(v))
#define GTE_MTC2(n, v) __asm__ volatile("mtc2 %0, $" #n : : "r"(v))
#define GTE_CFC2(n, v) __asm__ volatile("cfc2 %0, $" #n : "=r"(v))
#define GTE_MFC2(n, v) __asm__ volatile("mfc2 %0, $" #n : "=r"(v))
#define GTE_NOP2() __asm__ volatile("nop; nop")
// Matrix-vector multiply, rotation matrix * V0
#define GTE_RTV0() __asm__ volatile("mvmva 1, 0, 0, 0, 0")

// Load the translation vector (3 words at p) into control registers 5-7 via $12-$14
#define GTE_SET_TR(p)                                                                          \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); lw $14, 8(%0); ctc2 $12, $5; ctc2 $13, $6; ctc2 $14, $7" \
                     :                                                                         \
                     : "r"(p)                                                                  \
                     : "$12", "$13", "$14")

// Load vector 0 (VXY0, VZ0) from a short vector at p
#define GTE_LDV0(p) __asm__ volatile("lwc2 $0, 0(%0); lwc2 $1, 4(%0)" : : "r"(p) : "memory")
// Store MAC1..MAC3 (data registers 25-27) to three words at p
#define GTE_STLVNL(p) __asm__ volatile("swc2 $25, 0(%0); swc2 $26, 4(%0); swc2 $27, 8(%0)" : : "r"(p) : "memory")

// Load vertices 0-2 (VXY0..VZ2) from three short vectors laid out contiguously at p (8 bytes each)
#define GTE_LDV3C(p)                                                                                \
    __asm__ volatile("lwc2 $0, 0(%0); lwc2 $1, 4(%0); lwc2 $2, 8(%0); lwc2 $3, 12(%0); lwc2 $4, 16(%0); lwc2 $5, 20(%0)" \
                     :                                                                              \
                     : "r"(p)                                                                       \
                     : "memory")
// Perspective transform of vertices 0-2
#define GTE_RTPT() __asm__ volatile("rtpt")
// Store screen XY FIFO entries (data registers 12-14)
#define GTE_STSXY0(p) __asm__ volatile("swc2 $12, 0(%0)" : : "r"(p) : "memory")
#define GTE_STSXY1(p) __asm__ volatile("swc2 $13, 0(%0)" : : "r"(p) : "memory")
#define GTE_STSXY2(p) __asm__ volatile("swc2 $14, 0(%0)" : : "r"(p) : "memory")
// Normal clip of three screen vertices (SXY0, SXY1, SXY2 from a, b, c), result MAC0 stored at p
#define GTE_NCLIP(a, b, c, p)                                                                       \
    __asm__ volatile("mtc2 %0, $12; mtc2 %2, $14; mtc2 %1, $13; nclip; swc2 $24, 0(%3)"             \
                     :                                                                              \
                     : "r"(a), "r"(b), "r"(c), "r"(p)                                               \
                     : "memory")

// Single-vertex perspective transform, normal clip of the current SXY FIFO (MAC0 stored at p)
#define GTE_RTPS() __asm__ volatile("rtps")
#define GTE_NCLIP_STORE(p) __asm__ volatile("nclip; swc2 $24, 0(%0)" : : "r"(p) : "memory")
// Store the screen Z FIFO (data registers 16-19)
#define GTE_STSZ0(p) __asm__ volatile("swc2 $16, 0(%0)" : : "r"(p) : "memory")
#define GTE_STSZ1(p) __asm__ volatile("swc2 $17, 0(%0)" : : "r"(p) : "memory")
#define GTE_STSZ2(p) __asm__ volatile("swc2 $18, 0(%0)" : : "r"(p) : "memory")
#define GTE_STSZ3(p) __asm__ volatile("swc2 $19, 0(%0)" : : "r"(p) : "memory")
// Depth-cue the colour word at p (RGB in data register 6), result RGB2 (data register 22) stored at p
#define GTE_DPCS(p) __asm__ volatile("lwc2 $6, 0(%0); dpcs; swc2 $22, 0(%0)" : : "r"(p) : "memory")

// Load a whole MATRIX (rotation words 0-4 at +0, translation words 5-7 at +0x14) from p into
// control registers 0-7, going through $12-$14 as the original macro does
#define GTE_SET_MATRIX(p)                                                                       \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); ctc2 $12, $0; ctc2 $13, $1;"                \
                     "lw $12, 8(%0); lw $13, 12(%0); lw $14, 16(%0);"                           \
                     "ctc2 $12, $2; ctc2 $13, $3; ctc2 $14, $4;"                                \
                     "lw $12, 20(%0); lw $13, 24(%0); ctc2 $12, $5; lw $14, 28(%0);"            \
                     "ctc2 $13, $6; ctc2 $14, $7"                                               \
                     :                                                                          \
                     : "r"(p)                                                                   \
                     : "$12", "$13", "$14")
// Store MAC1..MAC3 into a three-word array on the stack (addressed directly, not through a register)
#define GTE_STMAC123_M(a)                                                                       \
    __asm__ volatile("swc2 $25, %0; swc2 $26, %1; swc2 $27, %2" : "=m"((a)[0]), "=m"((a)[1]), "=m"((a)[2]))
// Depth-cue: load colour word at p into RGB, run dpcs (after the required two nops)
#define GTE_DPCS_RUN() __asm__ volatile("dpcs")

// Store screen XY FIFO entries 0-2 (data registers 12-14) to three addresses in one statement
#define GTE_STSXY3(p0, p1, p2)                                                                  \
    __asm__ volatile("swc2 $12, 0(%0); swc2 $13, 0(%1); swc2 $14, 0(%2)"                         \
                     :                                                                          \
                     : "r"(p0), "r"(p1), "r"(p2)                                                \
                     : "memory")

// GTE_SET_MATRIX as its two halves: rotation (words 0-4) and translation (words 5-7)
#define GTE_SET_ROT_MATRIX(p)                                                                   \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); ctc2 $12, $0; ctc2 $13, $1;"                \
                     "lw $12, 8(%0); lw $13, 12(%0); lw $14, 16(%0);"                           \
                     "ctc2 $12, $2; ctc2 $13, $3; ctc2 $14, $4"                                 \
                     :                                                                          \
                     : "r"(p)                                                                   \
                     : "$12", "$13", "$14")
#define GTE_SET_TRANS_MATRIX(p)                                                                 \
    __asm__ volatile("lw $12, 20(%0); lw $13, 24(%0); ctc2 $12, $5; lw $14, 28(%0);"            \
                     "ctc2 $13, $6; ctc2 $14, $7"                                               \
                     :                                                                          \
                     : "r"(p)                                                                   \
                     : "$12", "$13", "$14")

#endif
