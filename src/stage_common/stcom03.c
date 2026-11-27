#include "common.h"
#include "stage_common/stcom03.h"

// Shared stage code, linked into 12 stages: r3_st00, r3_st09, r3_st0a, r3_st0b, r3_st0c,
// r3_st10, r3_st11, r3_st13, r3_st14, r3_st19, r3_st1a and r3_st1d. Each stage compiles this
// file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names are the
// same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom03"

void stcom03_func_0000(STCOM03_WORK *wp)
{
    stcom03_D_0000[wp->routine_0](wp);
}

void stcom03_func_003C(STCOM03_WORK *wp)
{
    wp->be_flag |= 2;
    switch (wp->type)
    {
        case 0:
            wp->mode_14   = 0x3D48000E;
            wp->value_22  = 0x40;
            wp->value_23  = 0x20;
            wp->size_24   = 0x30;
            wp->routine_0 = 1;
            wp->color_18  = 0x2E808080;
            wp->routine_3 = 3;
            break;
        case 1:
            wp->size_24               = 1;
            wp->mode_14               = 0x3D48000E;
            wp->routine_0             = 2;
            wp->routine_1             = 1;
            wp->value_22              = 0x40;
            wp->value_23              = 0x20;
            *(uint16 *)&wp->routine_2 = 0;
            switch (wp->param_C)
            {
                case 0:
                    wp->color_18 = 0x2E000080;
                    wp->step_26  = 8;
                    break;
                case 1:
                    wp->color_18 = 0x2E008000;
                    wp->step_26  = 0x800;
                    break;
                case 2:
                    wp->color_18 = 0x2E008080;
                    wp->step_26  = 0x808;
                    break;
            }
            break;
        case 2:
            wp->mode_14               = 0x3D48000E;
            wp->value_22              = 0x40;
            wp->routine_1             = wp->type;
            wp->value_23              = 0x20;
            *(uint16 *)&wp->routine_2 = 0;
            wp->routine_0             = 3;
            wp->color_18              = 0x2E000080;
            wp->step_26               = 0x10;
            wp->size_24               = 0x28;
            break;
        case 3:
            wp->mode_14               = 0x3D48002E;
            wp->value_22              = 0xE0;
            wp->value_23              = 0x60;
            wp->routine_0             = 4;
            wp->routine_1             = 0xC;
            *(uint16 *)&wp->routine_2 = 0;
            wp->color_18              = 0x2E808080;
            wp->step_26               = 0;
            {
                // Block-local: retail copies the initializers here, after the stores above.
                uint8 size_tbl[3]  = {0x20, 0x20, 0x08};
                uint8 param_tbl[3] = {0x08, 0x08, 0x02};

                wp->size_24 = size_tbl[wp->param_C];
                wp->param_C = param_tbl[wp->param_C];
                wp->be_flag |= 0x20;
            }
            break;
        case 4:
            wp->mode_14               = 0x3D08000E;
            wp->value_22              = 0xE0;
            wp->value_23              = 0x20;
            wp->routine_0             = 3;
            wp->color_18              = 0x2E000080;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            wp->step_26               = 0;
            wp->size_24               = 0x28;
            wp->be_flag |= 0x20;
            break;
    }
}

void stcom03_func_02CC(STCOM03_WORK *wp)
{
    if (--wp->routine_3 == 0)
    {
        func_80031988(wp);
    }
    else
    {
        wp->color_18 -= 0x202020;
        wp->size_24 += 8;
    }
}

void stcom03_func_0330(STCOM03_WORK *wp)
{
    sint32 unused[1]; // never used; retail reserves its 8-byte frame

    switch (wp->routine_1)
    {
        case 0:
            wp->routine_1 = 1;
            switch (wp->param_C)
            {
                case 0:
                    wp->color_18 = 0x2E000080;
                    wp->step_26  = 8;
                    break;
                case 1:
                    wp->color_18 = 0x2E008000;
                    wp->step_26  = 0x800;
                    break;
                case 2:
                    wp->color_18 = 0x2E008080;
                    wp->step_26  = 0x808;
                    break;
            }
            // fall through
        case 1:
            if (wp->size_24 >= 0x20)
            {
                wp->routine_1 = 2;
                wp->size_24   = 0;
            }
            else
            {
                wp->size_24 += 6;
                wp->color_18 += wp->step_26;
            }
            break;
        case 2:
            break;
    }
}

void stcom03_func_0414(STCOM03_WORK *wp)
{
    sint32 unused[1]; // never used; retail reserves its frame

    if (wp->size_24 <= 0)
    {
        func_80031988(wp);
    }
    else
    {
        wp->size_24 -= 8;
        wp->color_18 -= wp->step_26;
    }
}

void stcom03_func_0468(STCOM03_WORK *wp)
{
    if (wp->routine_1 == 0)
    {
        func_80031988(wp);
    }
    else
    {
        wp->color_18 -= 0xA0A0A;
        wp->size_24 += wp->param_C;
        wp->routine_1--;
    }
}
