// Interpreter for the game's inline MIPS assembly (GTE macros and the like).
//
// The port build never edits the game's headers. Instead, port/tools/asm_rewrite.py turns every
// `__asm__ volatile("..." : outputs : inputs : clobbers)` statement of the preprocessed source
// into a call of port_asm_run() with the template text and the operand values. The template is
// parsed once and cached in its PORT_ASM_PROG; GTE instructions go to the software GTE (gte.c).
#ifndef PORT_MIPS_ASM_H
#define PORT_MIPS_ASM_H

#include <stdint.h>

typedef struct PORT_ASM_INSN PORT_ASM_INSN;

typedef struct
{
    const char *text;     // the template, as written in the source
    const char *where;    // file:line of the statement, for diagnostics
    int count;            // parsed instructions, -1 until parsed
    PORT_ASM_INSN *insns; // parsed form
} PORT_ASM_PROG;

// Runs the template. ops[] holds the operand values in GCC's numbering (outputs first, then
// inputs); register outputs are written back into ops[], memory operands ("=m") hold the address.
void port_asm_run(PORT_ASM_PROG *prog, uint32_t *ops);

// Called for a `break` instruction (the game's deliberate traps).
void port_asm_break(uint32_t code, const char *where);

#endif
