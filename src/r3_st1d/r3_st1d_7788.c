#include "common.h"
#include "st1d.h"

void func_80107788(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_SVECTOR *save;
    sint16 i;
    sint16 rot;

    ext                     = &wp->ext;
    wp->value_AD            = wp->value_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_15C.h[1]          = 0x4210;
    wp->ext.u_2.h           = rand();
    D_80114C7C[wp->routine_0](wp);
    Mem_copy4(&wp->ext.u_34, (void *)0x1F800120, 6);
    func_8003346C(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ext->flags_0 & 4))
    {
        ext->pos_C = wp->vec_180[1];
        func_800341BC(&ext->pos_C, 0x50, 0, 0x8000, wp->value_1, &ext->value_14,
                      ext->value_8 | 0x4880000, 0x800000, 0);
    }
    if ((wp->flags_0 & 1) && !((uint8)wp->value_F & 0x40))
    {
        if (!((uint8)wp->value_F & 2))
        {
            func_80102F24(ext->u_4C.p);
        }
        if ((uint8)wp->value_F & 1)
        {
            if (!((uint8)wp->value_F & 4))
            {
                ((STAGE_OBJ *)ext->effect_50)->routine_1 = 0;
                ((STAGE_OBJ *)ext->piece_54)->routine_1  = 0;
            }
            wp->value_F &= ~1;
        }
        for (i = 0, save = D_8011A6B0; i < 2; i++)
        {
            *save          = wp->position;
            *D_8011A6B8    = wp->position_fixed;
            rot            = wp->rotation.y;
            wp->rotation.y = (ext->u_44.h[1] + rot) & 0xFFF;
            Obj_pos_set(wp, D_80114CA0[i], -0x8A0, 0);
            ((STAGE_FX **)&ext->effect_50)[i]->x_1C = wp->position.x;
            ((STAGE_FX **)&ext->effect_50)[i]->y_1E = wp->position.y;
            ((STAGE_FX **)&ext->effect_50)[i]->z_20 = wp->position.z;
            wp->position                            = *save;
            wp->position_fixed                      = *D_8011A6B8;
            wp->rotation.y                          = rot;
        }
    }
    ext->value_14 = 0;
}

void func_80107AF0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STAGE_OBJ *fx;
    STAGE_OBJ *obj;
    ST1D_SPAWN_REC *rec;
    sint32 ground;
    sint16 life;
    sint16 i;

    ext = &wp->ext;
    if (!((uint8)wp->value_F & 0x40))
    {
        for (i = 0; i < 4; i++)
        {
            fx                                 = (STAGE_OBJ *)func_80031618();
            ((STAGE_OBJ **)&ext->effect_50)[i] = fx;
            if (fx != NULL)
            {
                ((STAGE_OBJ **)&ext->effect_50)[i]->flags_0      = 9;
                ((STAGE_OBJ **)&ext->effect_50)[i]->kind_2       = 0xF;
                ((STAGE_OBJ **)&ext->effect_50)[i]->variant_3    = 1;
                ((STAGE_OBJ **)&ext->effect_50)[i]->u_C.b.byte_C = wp->variant_3 >> 4;
            }
            else
            {
                func_80031824(wp);
                // Frees the effects taken so far only when the first one failed (then [-1]).
                while (i == 0)
                {
                    i--;
                    func_80031988(((STAGE_OBJ **)&ext->effect_50)[i]);
                }
                return;
            }
        }
        wp->value_D = ((STAGE_OBJ *)ext->u_58.obj)->value_1;
        wp->value_E = ((STAGE_OBJ *)ext->u_5C.p)->value_1;
        obj         = func_80031418();
        ext->u_4C.p = obj;
        if (obj != NULL)
        {
            rec                                         = &D_80113FC0[wp->value_C];
            ((STAGE_OBJ *)ext->u_4C.p)->flags_0         = rec->flags_0;
            ((STAGE_OBJ *)ext->u_4C.p)->kind_2          = rec->kind_2;
            ((STAGE_OBJ *)ext->u_4C.p)->variant_3       = rec->variant_3;
            ((STAGE_OBJ *)ext->u_4C.p)->value_4         = rec->value_4;
            ((STAGE_OBJ *)ext->u_4C.p)->reserved05      = rec->value_5;
            *(sint32 *)&((STAGE_OBJ *)ext->u_4C.p)->u_C = rec->value_8;
            ((STAGE_OBJ *)ext->u_4C.p)->position = ((STAGE_OBJ *)ext->u_4C.p)->position_prev =
                rec->position;
            ((STAGE_OBJ *)ext->u_4C.p)->position_fixed.v.x =
                ((STAGE_OBJ *)ext->u_4C.p)->position_fixed_prev.x =
                    ((STAGE_OBJ *)ext->u_4C.p)->position.x << 16;
            ((STAGE_OBJ *)ext->u_4C.p)->position_fixed.v.y =
                ((STAGE_OBJ *)ext->u_4C.p)->position_fixed_prev.y =
                    ((STAGE_OBJ *)ext->u_4C.p)->position.y << 16;
            ((STAGE_OBJ *)ext->u_4C.p)->position_fixed.v.z =
                ((STAGE_OBJ *)ext->u_4C.p)->position_fixed_prev.z =
                    ((STAGE_OBJ *)ext->u_4C.p)->position.z << 16;
            ((STAGE_OBJ *)ext->u_4C.p)->rotation.x = ((STAGE_OBJ *)ext->u_4C.p)->rotation_prev.x =
                0;
            ((STAGE_OBJ *)ext->u_4C.p)->rotation.y = ((STAGE_OBJ *)ext->u_4C.p)->rotation_prev.y =
                rec->rotation_7 << 4;
            ((STAGE_OBJ *)ext->u_4C.p)->rotation.z = ((STAGE_OBJ *)ext->u_4C.p)->rotation_prev.z =
                0;
            ((STAGE_OBJ *)ext->u_4C.p)->u_C.b.byte_D = wp->value_1;
        }
        else
        {
            func_80031824(wp);
            for (i = 0; i < 4; i++)
            {
                func_80031988(((STAGE_OBJ **)&ext->effect_50)[i]);
            }
            return;
        }
    }
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->u_64.w[0]  = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158            = 0x02000200;
    wp->u_15C.w[0]           = 0x200;
    ext->u_34.w              = 0;
    ext->u_38.w              = 0;
    ext->u_3C.w              = 0;
    ext->obj_40              = NULL;
    ext->u_44.fx[0]          = NULL;
    ext->u_44.fx[1]          = NULL;
    ext->flags_0             = 6;
    *(sint32 *)&ext->u_4     = 0;
    *(sint32 *)&ext->value_8 = 0;
    ext->value_14            = 0;
    ext->value_18            = 0;
    ext->u_24.w[1]           = 0;
    life                     = D_80098844[wp->kind_2]->life_8 << 4;
    wp->data_78              = D_80114C94;
    wp->value_6E             = life;
    wp->value_B0             = life;
    wp->value_B2             = life;
    ground                   = func_80048E6C(wp);
    wp->position.y           = ground;
    wp->position_fixed.y     = ground << 16;
    wp->routine_0            = 1;
    if ((uint8)wp->value_F & 0x40)
    {
        wp->routine_1 = 2;
    }
    else
    {
        wp->routine_1 = 0;
    }
    *(uint16 *)&wp->routine_2 = 0;
    wp->u_15C.h[1]            = 0x4210;
}

void func_80107EB8(ST1D_VIEW *wp)
{
    sint16 temp_v0;

    if (wp->ext.flags_0 & 2)
    {
        func_801083E4(wp);
    }
    D_80114C88[wp->routine_1](wp);
    temp_v0 = wp->ext.value_A;
    if (temp_v0 != 0)
    {
        wp->ext.value_A = temp_v0 - 1;
    }
    if (!(wp->ext.flags_0 & 8))
    {
        func_80051B68(wp, 3, -1, 0);
    }
}

void func_80107F58(ST1D_VIEW *wp)
{
    func_80031824(wp);
    if (!((uint8)wp->value_F & 0x40))
    {
        func_80031988(wp->ext.effect_50);
        func_80031988(wp->ext.piece_54);
        if (!((uint8)wp->value_F & 2))
        {
            func_80031824(wp->ext.u_4C.p);
            func_80031988(wp->ext.u_58.obj);
            func_80031988(wp->ext.u_5C.p);
        }
    }
}

void func_80107FE4(ST1D_VIEW *wp)
{
    sint16 temp_v0;

    wp->ext.value_8      = 0;
    wp->ext.u_44.h[1]    = (wp->ext.u_44.h[1] + 0x40) & 0xFFF;
    temp_v0              = func_80048E6C(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
}

void func_8010802C(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STAGE_PIECE *piece;
    sint16 i;
    sint16 y;

    ext             = &wp->ext;
    wp->ext.value_8 = 0;
    switch (wp->routine_2)
    {
        case 0:
            wp->ext.u_44.h[1] = (wp->ext.u_44.h[1] + 0x40) & 0xFFF;
            if ((wp->rotation.y + wp->ext.u_44.h[1]) & 0x3FF)
            {
                break;
            }
            wp->routine_2    = 1;
            wp->ext.u_4.h[0] = 15;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                i = 0;
                do
                {
                    piece = (STAGE_PIECE *)Open_SHL_WORK();
                    if (piece != NULL)
                    {
                        piece->flags_0        = 1;
                        piece->kind_2         = 9;
                        piece->variant_3      = 1;
                        piece->position       = wp->position;
                        piece->position_fixed = wp->position_fixed;
                        piece->angle_64       = (i ? wp->rotation.y + ext->u_44.h[1] + 0x800
                                                   : wp->rotation.y + ext->u_44.h[1]) &
                                                0xFFF;
                        func_8002FFC4(&piece->position, &piece->position_fixed, piece->angle_64,
                                      0x600, -0x7C0, 0);
                    }
                    i++;
                } while (i < 2);
                wp->routine_2 = 0;
            }
            break;
    }
    y                    = func_80048E6C(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 16;
}

void func_801081D0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_EFFECT *effect;
    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->u_44.h[1] = -30;
            wp->value_4E  = 3;
            effect        = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0x41;
                effect->sprite.position = wp->vec_180[0];
            }
            wp->value_FB     = -1;
            wp->ext.value_8  = 0;
            wp->ext.u_4.h[0] = 10;
            wp->ext.flags_0  = (wp->ext.flags_0 & ~4) | 8;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                wp->flags_0 &= ~2;
                wp->value_F |= 4;
                effect = func_80031618();
                if (effect != NULL)
                {
                    effect->flags_0         = 5;
                    effect->kind_2          = 0x80;
                    effect->variant_3       = 0x40;
                    effect->sprite.position = wp->vec_180[1];
                }
#ifdef __wasm32__
                func_80047148(wp, &wp->vec_180[0]);
#else
                func_80047148(wp, &wp->vec_180[0], effect);
#endif
                if (!(wp->value_F & 0x42))
                {
                    ((STAGE_OBJ *)ext->u_4C.p)->routine_0 = 4;
                }
            }
            else
            {
                Obj_pos_set(wp, 0, wp->u_44.h[1] << 4, 0);
                wp->u_44.h[1] += wp->value_4E;
                func_8004B414(wp);
                break;
            }
            // fall through
        case 2:
            if (!(wp->value_F & 0x40))
            {
                if (wp->value_F & 2)
                {
                    func_80031824(wp);
                    func_80031988(ext->effect_50);
                    func_80031988(ext->piece_54);
                }
            }
            else
            {
                func_80031824(wp);
            }
            break;
    }
}

sint32 func_801083E4(ST1D_VIEW *wp)
{
    sint32 damage;

    damage = wp->ext.value_14 & 0xFFFFFF;
    if (damage)
    {
        if (wp->ext.value_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->ext.flags_0 &= ~2;
                Sound_call2(0xA2, &wp->position);
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->u_15C.h[1] = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
