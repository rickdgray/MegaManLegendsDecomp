#include "common.h"
#include "stage_common/stcom34.h"

// Shared stage code, linked into 3 stages: r3_st0e, r3_st14 and r3_st1a. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom34"

// Four sparks flying out from a work slot, each starting over once it has flown in.
void stcom34_func_0000(STCOM34_WORK *wp)
{
    stcom34_D_0010[wp->routine_0](wp);
}

void stcom34_func_003C(STCOM34_WORK *wp)
{
    STCOM34_SPARK *sparks;
    uint8 i;

    sparks        = wp->spark_28;
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->value_D   = 0;
    wp->value_E   = 0;
    wp->value_F   = 0;
    for (i = 0; i < 4; i++)
    {
        sparks[i].yaw_0    = rand() & 0x1F;
        sparks[i].pitch_1  = rand() & 0xF;
        sparks[i].delay_2  = (rand() & 0x3F) + 1;
        sparks[i].length_3 = stcom34_D_0000[wp->variant_3].length_0 + (rand() & 0x1F);
        sparks[i].speed_4  = stcom34_D_0000[wp->variant_3].speed_2;
        sparks[i].dist_6   = stcom34_D_0000[wp->variant_3].dist_4 + (rand() & 0x3F);
    }
}

void stcom34_func_014C(STCOM34_WORK *wp)
{
    STCOM_SVECTOR a;
    STCOM_SVECTOR b;
    STCOM34_SPARK *sparks;
    STCOM34_OWNER *owner;
    sint32 yaw;
    sint16 pitch;
    sint16 h;
    sint16 v;
    uint8 i;
    uint8 shade;

    sparks = wp->spark_28;
    owner  = func_80036294(wp->owner_C);
    for (i = 0; i < 4; i++)
    {
        if (sparks[i].delay_2 == 0)
        {
            pitch = sparks[i].pitch_1 << 8;
            yaw   = sparks[i].yaw_0;
            h     = (rsin(pitch) * sparks[i].dist_6) >> 12;
            v     = (rcos(pitch) * sparks[i].dist_6) >> 12;
            yaw <<= 7;
            a.x = owner->pos_38.x + ((rsin(yaw) * h) >> 12);
            a.z = owner->pos_38.z + ((rcos(yaw) * h) >> 12);
            a.y = owner->pos_38.y + v;
            h   = (rsin(pitch) * (sparks[i].dist_6 + sparks[i].length_3)) >> 12;
            v   = (rcos(pitch) * (sparks[i].dist_6 + sparks[i].length_3)) >> 12;
            b.x = owner->pos_38.x + ((rsin(yaw) * h) >> 12);
            b.z = owner->pos_38.z + ((rcos(yaw) * h) >> 12);
            b.y = owner->pos_38.y + v;
            if (sparks[i].dist_6 < 0x18)
            {
                shade = sparks[i].dist_6 - 8;
            }
            else
            {
                shade = 0x10;
            }
            stcom34_func_04CC(a, b, shade);
            if (STCOM34_FRAME & 1)
            {
                if (sparks[i].speed_4 != 2)
                {
                    sparks[i].speed_4--;
                }
            }
            sparks[i].dist_6 -= sparks[i].speed_4;
            if (sparks[i].dist_6 < 8)
            {
                sparks[i].yaw_0    = rand() & 0x1F;
                sparks[i].pitch_1  = rand() & 0xF;
                sparks[i].delay_2  = (rand() & 0x3F) + 1;
                sparks[i].length_3 = stcom34_D_0000[wp->variant_3].length_0 + (rand() & 0x1F);
                sparks[i].speed_4  = stcom34_D_0000[wp->variant_3].speed_2;
                sparks[i].dist_6   = stcom34_D_0000[wp->variant_3].dist_4 + (rand() & 0x3F);
            }
        }
        else
        {
            sparks[i].delay_2--;
        }
    }
}

void stcom34_func_04AC(STCOM34_WORK *wp)
{
    func_80031988(wp);
}

// Draws one spark: a line from a to b, its color scaled by `shade`.
void stcom34_func_04CC(STCOM_SVECTOR a, STCOM_SVECTOR b, uint8 shade)
{
    STCOM34_LINE *line;
    sint32 r;
    sint32 g;
    sint32 bl;

    bl   = ((rand() & 7) + 6) * shade;
    g    = ((rand() & 7) + 6) * shade;
    r    = ((rand() & 7) + 6) * shade;
    line = Billboard_line_get();
    // Struct-field reads of the x/y words keep them ordered against the packet stores.
    line->xy1_0   = ((STCOM34_XY *)&b)->xy;
    line->xy0_8   = ((STCOM34_XY *)&a)->xy;
    line->color_C = 0x10101;
    line->color_4 = ((bl & 0xFF) << 16) | 0x52000000 | ((g & 0xFF) << 8) | (r & 0xFF);
    line->z_10    = (b.z << 16) + (uint16)a.z;
    line->mode_18 = 0xE1000020;
}
