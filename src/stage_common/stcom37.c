#include "common.h"
#include "stage_common/stcom37.h"

// Shared stage code, linked into 3 stages: r3_st03, r3_st05 and r3_st06. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom37"

// Routines of a villager: freed, standing, and talking (animation 8 while a message runs).
void stcom37_func_0000(STCOM37_WORK *wp)
{
    func_80031824(wp);
}

void stcom37_func_0020(STCOM37_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->routine_2++;
        wp->anim_AC = 0;
    }
}

void stcom37_func_0040(STCOM37_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            // fall through
        case 1:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            break;
        case 2:
            if (wp->flags_A7 < 0)
            {
                wp->routine_2--;
                wp->anim_AC = 0;
            }
            break;
    }
}
