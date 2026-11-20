#include "common.h"
#include "stage_common/stcom07.h"

// Shared stage code, linked into 10 stages: r3_st03, r3_st04, r3_st05, r3_st06, r3_st08,
// r3_st10, r3_st11, r3_st12, r3_st19 and r3_st1b. Each stage compiles this file against its own
// copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names are the same in every
// stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom07"

void stcom07_func_0000(STCOM07_WORK *wp)
{
    stcom07_D_0000[wp->routine_0](wp);
}

void stcom07_func_003C(STCOM07_WORK *wp)
{
    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->type_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    RotMatrixY(wp->rot_C << 10, &wp->matrix.m);
    wp->color_40 = 0x808080;
    wp->routine_0++;
    wp->quad_44 = func_8002D22C(wp->model_14, 0x10000);
    switch (wp->type_3)
    {
        case 0:
            wp->quad_44[0].tex.words[0] = 0xB7D0B7E7;
            wp->quad_44[0].tex.words[1] = 0xA0D0A0E7;
            wp->quad_44[1].tex.words[0] = 0xA0FFA0E8;
            wp->quad_44[1].tex.words[1] = 0xB7FFB7E8;
            wp->quad_44[2].tex.words[0] = 0xCFD0CFE7;
            wp->quad_44[2].tex.words[1] = 0xB8D0B8E7;
            wp->quad_44[3].tex.words[0] = 0xB8FFB8E8;
            wp->quad_44[3].tex.words[1] = 0xCFFFCFE8;
            break;
        case 1:
            wp->quad_44[0].tex.words[0] = 0xE7D0E7E7;
            wp->quad_44[0].tex.words[1] = 0xD0D0D0E7;
            wp->quad_44[1].tex.words[0] = 0xD0FFD0E8;
            wp->quad_44[1].tex.words[1] = 0xE7FFE7E8;
            wp->quad_44[2].tex.words[0] = 0xFFD0FFE7;
            wp->quad_44[2].tex.words[1] = 0xE8D0E8E7;
            wp->quad_44[3].tex.words[0] = 0xE8FFE8E8;
            wp->quad_44[3].tex.words[1] = 0xFFFFFFE8;
            break;
        case 2:
            wp->quad_44[0].tex.words[0] = 0xA7A0A7B7;
            wp->quad_44[0].tex.words[1] = 0x90A090B7;
            wp->quad_44[1].tex.words[0] = 0x90CF90B8;
            wp->quad_44[1].tex.words[1] = 0xA7CFA7B8;
            wp->quad_44[2].tex.words[0] = 0xBFA0BFB7;
            wp->quad_44[2].tex.words[1] = 0xA8A0A8B7;
            wp->quad_44[3].tex.words[0] = 0xA8CFA8B8;
            wp->quad_44[3].tex.words[1] = 0xBFCFBFB8;
            break;
        case 3:
            wp->quad_44[0].tex.words[0] = 0x87D087E7;
            wp->quad_44[0].tex.words[1] = 0x70D070E7;
            wp->quad_44[1].tex.words[0] = 0x70FF70E8;
            wp->quad_44[1].tex.words[1] = 0x87FF87E8;
            wp->quad_44[2].tex.words[0] = 0x9FD09FE7;
            wp->quad_44[2].tex.words[1] = 0x88D088E7;
            wp->quad_44[3].tex.words[0] = 0x88FF88E8;
            wp->quad_44[3].tex.words[1] = 0x9FFF9FE8;
            break;
    }
}

void stcom07_func_02F4(STCOM07_WORK *wp)
{
    if (func_80048C60(&wp->position) == func_80048C60(&Player_work.position) &&
        Sce_flag_test(0x7B1) != 0)
    {
        wp->timer_B = 24;
        wp->routine_0++;
    }
}

void stcom07_func_0360(STCOM07_WORK *wp)
{
    STCOM_FIXED_VECTOR unused; // never used; retail reserves its frame
    STCOM07_QUAD *quad;
    sint32 i;

    if (wp->timer_B != 0)
    {
        wp->timer_B--;
        wp->matrix.words[1]  = 0;
        wp->matrix.words[3]  = 0;
        wp->matrix.words[0]  = 0x1000;
        wp->matrix.words[2]  = 0x1000;
        wp->matrix.words[4]  = 0x1000;
        wp->matrix.m.m[1][1] = (wp->timer_B << 12) / 24;
        RotMatrixY(wp->rot_C << 10, &wp->matrix.m);
        for (i = 0; i < 4; i++)
        {
            quad = &wp->quad_44[i];
            quad->tex.uv[1] += stcom07_D_001C[i].v0;
            quad->tex.uv[3] += stcom07_D_001C[i].v1;
            quad->tex.uv[5] += stcom07_D_001C[i].v2;
            quad->tex.uv[7] += stcom07_D_001C[i].v3;
        }
    }
    else
    {
        wp->routine_0++;
    }
}

void stcom07_func_0488(STCOM07_WORK *wp)
{
    if (func_80048C60(&wp->position) == func_80048C60(&Player_work.position) &&
        Sce_flag_test(0x7B1) == 0)
    {
        wp->timer_B = 0;
        wp->routine_0++;
    }
}

void stcom07_func_04F4(STCOM07_WORK *wp)
{
    STCOM_FIXED_VECTOR unused; // never used; retail reserves its frame
    STCOM07_QUAD *quad;
    sint32 i;

    if (wp->timer_B < 24)
    {
        wp->timer_B++;
        wp->matrix.words[1]  = 0;
        wp->matrix.words[3]  = 0;
        wp->matrix.words[0]  = 0x1000;
        wp->matrix.words[2]  = 0x1000;
        wp->matrix.words[4]  = 0x1000;
        wp->matrix.m.m[1][1] = (wp->timer_B << 12) / 24;
        RotMatrixY(wp->rot_C << 10, &wp->matrix.m);
        for (i = 0; i < 4; i++)
        {
            quad = &wp->quad_44[i];
            quad->tex.uv[1] -= stcom07_D_001C[i].v0;
            quad->tex.uv[3] -= stcom07_D_001C[i].v1;
            quad->tex.uv[5] -= stcom07_D_001C[i].v2;
            quad->tex.uv[7] -= stcom07_D_001C[i].v3;
        }
    }
    else
    {
        wp->routine_0 = 1;
    }
}

void stcom07_func_0618(STCOM07_WORK *wp)
{
}

void stcom07_func_0620(STCOM07_WORK *wp)
{
}
