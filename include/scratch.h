#ifndef SCRATCH_H
#define SCRATCH_H

#include "common.h"

// Scratchpad variables should be accessed through literal addresses, as encrouged by PsyQ's documentation.
#define Dbl_buff_idx (*(uint8 *)0x1F800000)
#define Vsync_wait (*(uint8 *)0x1F800001)

#endif // SCRATCH_H
