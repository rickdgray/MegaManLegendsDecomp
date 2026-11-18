// Software model of the PS1 geometry coprocessor (GTE, COP2), used by the inline-MIPS
// interpreter (mips_asm.c). Register numbering and arithmetic follow the hardware
// (psx-spx "Geometry Transformation Engine"); the error FLAG register is only partly modelled.
#ifndef PORT_GTE_H
#define PORT_GTE_H

#include <stdint.h>

// mvmva operand selectors (and the fields of any GTE command word).
typedef struct
{
    int sf; // shift fraction: 1 = results >> 12
    int mx; // matrix: 0 RT, 1 light, 2 colour, 3 reserved
    int v;  // vector: 0 V0, 1 V1, 2 V2, 3 IR
    int cv; // translation: 0 TR, 1 BK, 2 FC (hardware bug kept out), 3 none
    int lm; // 1 = clamp IR to 0..0x7FFF instead of -0x8000..0x7FFF
} GTE_OP;

void gte_reset(void);

uint32_t gte_read_data(int reg);
void gte_write_data(int reg, uint32_t value);
uint32_t gte_read_ctrl(int reg);
void gte_write_ctrl(int reg, uint32_t value);

void gte_rtps(const GTE_OP *op);
void gte_rtpt(const GTE_OP *op);
void gte_nclip(void);
void gte_avsz3(void);
void gte_avsz4(void);
void gte_dpcs(const GTE_OP *op);
void gte_mvmva(const GTE_OP *op);

// Executes any COP2 command word (the instruction's low 25 bits): every command of the hardware.
void gte_command(uint32_t word);

#endif
