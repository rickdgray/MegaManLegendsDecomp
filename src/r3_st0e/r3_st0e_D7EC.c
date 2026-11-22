#include "common.h"
#include "st0e.h"

void func_8010D7EC(ST0E_GLOW *wp)
{
    STCOM23_PACKET *packet;
    uint32 uv;

    D_80110BF0[wp->routine_0](wp);
    if (wp->variant_3 != 0)
    {
        packet          = Billboard_get();
        packet->code_4  = wp->color_18;
        packet->xy_8    = wp->xy_1C.w;
        packet->z_10    = wp->z_20.w;
        packet->uv_C    = wp->uv_34;
        packet->uv_14   = wp->uv_38;
        uv              = wp->uv_3C;
        packet->uv_1C   = uv & 0xFFFF;
        packet->uv_24   = uv >> 16;
        packet->size_18 = wp->size_24;
    }
}

void func_8010D8AC(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 0)
    {
        wp->flags_0 |= 2;
    }
    wp->position_prev.z = 0x10;
    wp->routine_0++;
}

void func_8010D8E4(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    wp->position_fixed.f.x.words.fraction += wp->position_fixed.f.pad.words.fraction;
    temp_v0                                = (uint16)wp->position_fixed.f.pad.words.integer + (uint16)wp->position_prev.y;
    wp->position_fixed.f.pad.words.integer = temp_v0;
    wp->position_fixed.f.x.words.integer += temp_v0;
    wp->position_fixed.f.y.words.fraction += (uint16)wp->position_prev.x;
    if (wp->position_fixed.f.pad.words.integer >= 0)
    {
        wp->routine_0++;
    }
}

void func_8010D944(ST0E_GLOW *wp)
{
    sint32 gray;

    if (--wp->timer_30 == 0)
    {
        wp->routine_0++;
    }
    gray         = wp->timer_30 * 8;
    wp->color_18 = 0x2E000000 | (gray << 16) | (gray << 8) | gray;
    wp->xy_1C.h.x += wp->vx_28;
    wp->vy_2A += wp->ay_2E;
    wp->xy_1C.h.y += wp->vy_2A;
    wp->z_20.z += wp->vz_2C;
}

void func_8010D9D8(STAGE_OBJ *wp)
{
    func_80031988(wp);
}

void func_8010D9F8(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos)
{
    ST0E_GLOW *fx;
    ST0E_SPARK *spark;
    sint32 angle;
    sint32 step;
    sint32 i;

    angle = rand() & 0xFFF;
    step  = 0x1000 / count;
    for (i = 0; i < count; i++)
    {
        fx = (ST0E_GLOW *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0   = 1;
            fx->kind_2    = 0x11;
            fx->variant_3 = textured;
            fx->value_C   = type;
            fx->color_18  = 0x2E808080;
            fx->xy_1C.h.x = pos->x;
            fx->xy_1C.h.y = pos->y;
            fx->z_20.z    = pos->z;
            if (textured != 0)
            {
                spark     = (ST0E_SPARK *)&D_80110BDC[type];
                fx->uv_34 = spark->tex.uv_8;
                fx->uv_38 = spark->tex.uv_C;
                fx->uv_3C = spark->tex.uv_10;
            }
            else
            {
                spark        = (ST0E_SPARK *)&D_80110B3C[type];
                fx->mode_14  = spark->flat.mode_8;
                fx->z_20.b.u = spark->flat.u_C;
                fx->z_20.b.v = spark->flat.v_D;
            }
            fx->vx_28   = (rsin(angle) * spark->head.speed_0) >> 12;
            fx->vz_2C   = (rcos(angle) * spark->head.speed_0) >> 12;
            fx->vy_2A   = spark->head.vy_2;
            fx->ay_2E   = spark->head.ay_4;
            fx->size_24 = spark->head.size_6;
        }
        angle += step + (rand() & 0x3F);
    }
}

void func_8010DC00(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos, sint32 from, sint32 to)
{
    ST0E_GLOW *fx;
    ST0E_SPARK *spark;
    sint32 angle;
    sint32 step;
    sint32 i;

    angle = from;
    step  = (to - from) / count;
    for (i = 0; i < count; i++)
    {
        fx = (ST0E_GLOW *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0   = 1;
            fx->kind_2    = 0x11;
            fx->variant_3 = textured;
            fx->value_C   = type;
            fx->color_18  = 0x2E808080;
            fx->xy_1C.h.x = pos->x;
            fx->xy_1C.h.y = pos->y;
            fx->z_20.z    = pos->z;
            if (textured != 0)
            {
                spark     = (ST0E_SPARK *)&D_80110BDC[type];
                fx->uv_34 = spark->tex.uv_8;
                fx->uv_38 = spark->tex.uv_C;
                fx->uv_3C = spark->tex.uv_10;
            }
            else
            {
                spark        = (ST0E_SPARK *)&D_80110B3C[type];
                fx->mode_14  = spark->flat.mode_8;
                fx->z_20.b.u = spark->flat.u_C;
                fx->z_20.b.v = spark->flat.v_D;
            }
            fx->vx_28   = (rsin(angle) * spark->head.speed_0) >> 12;
            fx->vz_2C   = (rcos(angle) * spark->head.speed_0) >> 12;
            fx->vy_2A   = spark->head.vy_2;
            fx->ay_2E   = spark->head.ay_4;
            fx->size_24 = spark->head.size_6;
        }
        angle += step + (rand() & 0x3F);
    }
}
