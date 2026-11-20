#include "common.h"
#include "stage_common/stcom38.h"

// Shared stage code, linked into 4 stages: r3_st0a, r3_st10, r3_st19 and r3_st1b. Each stage
// compiles this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the
// names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom38"

// Room handlers: each starts its room's script once.
void stcom38_func_0000(void)
{
}

void stcom38_func_0008(STCOM38_ROOM_WORK *wp)
{
    if (wp->started_4 == 0)
    {
        func_8001DF10(stcom38_D_0000);
        wp->started_4 = 0xFF;
    }
}

void stcom38_func_0054(STCOM38_ROOM_WORK *wp)
{
    if (wp->started_4 == 0)
    {
        func_8001DF10(stcom38_E_0000);
        wp->started_4 = 0xFF;
    }
}

void stcom38_func_00A0(STCOM38_ROOM_WORK *wp)
{
    if (wp->started_4 == 0)
    {
        func_8001DF10(stcom38_E2_0000);
        wp->started_4 = 0xFF;
    }
}
