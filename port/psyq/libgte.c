// PsyQ libgte's InitGeom for the native port. The rest of libgte runs from the retail image
// (psyq_emulated.c); InitGeom also patches the BIOS exception handler and sets COP0's status
// register, which mean nothing here, so it is written out: the GTE control registers it sets.
#include "gte.h"

#include <stdint.h>

void InitGeom(void)
{
    gte_write_ctrl(29, 0x155);             // ZSF3: 1/3 in 1.3.12 (AVSZ3)
    gte_write_ctrl(30, 0x100);             // ZSF4: 1/4 in 1.3.12 (AVSZ4)
    gte_write_ctrl(26, 1000);              // H: projection plane distance
    gte_write_ctrl(27, (uint32_t)-0x1062); // DQA: depth-cue coefficient
    gte_write_ctrl(28, 0x1400000);         // DQB: depth-cue offset
    gte_write_ctrl(24, 0);                 // OFX
    gte_write_ctrl(25, 0);                 // OFY
}
