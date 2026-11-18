#include "common.h"

// Shared stage code, linked into 3 stages: r3_st0a, r3_st0e and r3_st1a. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom39"

// Three empty handlers (room routines that do nothing).
void stcom39_func_0000(void)
{
}

void stcom39_func_0008(void)
{
}

void stcom39_func_0010(void)
{
}
