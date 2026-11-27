#include "common.h"
#include "st1d.h"

void func_80102F24(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_SVECTOR *save;

    wp->value_AD            = wp->value_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_15C.h[1]          = 0x4210;
    wp->ext.u_2.h           = rand();
    D_80114BA0[wp->routine_0](wp);
    ext = &wp->ext;
    if (wp->value_AD != wp->value_AC)
    {
        func_80032304(wp, wp->value_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    STAGE_SP_13A = ext->u_3C.h[0];
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    ext->u_4C.i = 0;
    save        = D_8011A698;
    do
    {
        *save                = wp->position;
        D_8011A6A0           = wp->position_fixed;
        wp->u_64.h[0]        = wp->rotation.y;
        wp->position         = wp->vec_180[2];
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->position_fixed.z = wp->position.z << 16;
        wp->rotation.y       = (ext->u_3C.h[0] + wp->rotation.y) & 0xFFF;
        Obj_pos_set(wp, 0, -0x200, D_80114BF8[ext->u_4C.i]);
        ext->u_44.fx[ext->u_4C.i]->x_1C = wp->position.x;
        ext->u_44.fx[ext->u_4C.i]->y_1E = wp->position.y;
        ext->u_44.fx[ext->u_4C.i]->z_20 = wp->position.z;
        wp->position                    = *save;
        wp->position_fixed              = D_8011A6A0;
        wp->rotation.y                  = wp->u_64.h[0];
        ext->u_4C.i++;
    } while (ext->u_4C.i < 2);
    if ((wp->flags_0 & 2) && (ext->flags_0 & 4))
    {
        ext->pos_C = wp->vec_180[0];
        ext->pos_C.y += 30;
        func_800341BC(&ext->pos_C, 0x50, 0, 0x8000, wp->value_1, &ext->value_14, ext->value_8 | 0x4880000, 0x800000, 0);
    }
    ext->value_14 = 0;
}

void func_8010329C(ST1D_VIEW *wp)
{
    // D_80098844 is declared with stcom16's shorter record; this one reads its byte 0xF.
    sint16 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_64.w[0]  = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158               = 0x02000200;
    wp->u_15C.w[0]              = 0x200;
    wp->ext.flags_0             = 0x26;
    *(sint32 *)&wp->ext.u_4     = 0;
    *(sint32 *)&wp->ext.value_8 = 0;
    wp->ext.value_14            = 0;
    wp->ext.value_18            = 0;
    Track_reset(wp->ext.u_24.track, ((ST1D_KIND *)D_80098844[wp->kind_2])->value_F, -0x60);
    wp->ext.u_34.h[0]         = 0;
    wp->ext.u_34.h[1]         = 0;
    wp->ext.u_3C.h[0]         = 0;
    wp->ext.u_38.h[0]         = 4;
    wp->ext.obj_40            = func_80036294(wp->value_D);
    wp->ext.u_44.fx[0]        = (STAGE_FX *)func_80036294(wp->ext.obj_40->u_C.b.byte_D);
    wp->ext.u_44.fx[1]        = (STAGE_FX *)func_80036294(wp->ext.obj_40->u_E.b.byte_E);
    life                      = D_80098844[wp->kind_2]->life_8 << 4;
    wp->data_78               = D_80114BEC;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->value_6E              = life;
    wp->value_B0              = life;
    wp->value_B2              = life;
    func_800322A8(wp, 0, 0);
    wp->u_15C.h[1] = 0x4210;
}

void func_801033E4(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if (func_800364B0(wp->ext.u_24.track, wp, (wp->rotation.y + wp->ext.u_3C.h[0]) & 0xFFF))
    {
        wp->ext.flags_0 |= 0x100;
    }
    else
    {
        wp->ext.flags_0 &= ~0x100;
    }
    if (ext->flags_0 & 2)
    {
        func_80105318(wp);
    }
    wp->u_64.h[0] = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x40);
    if (((ext->u_3C.h[0] + wp->u_64.h[0] + 0x500) & 0xFFF) < 0xA00)
    {
        ext->u_3C.h[0] += wp->u_64.h[0];
    }
    D_80114BB4[wp->routine_1](wp);
    if (ext->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 6:
                wp->routine_1 = 8;
                break;
            case 7:
                wp->routine_1 = 9;
                break;
            case 4:
                wp->routine_1 = 1;
                break;
            case 12:
                wp->routine_1 = 3;
                break;
            case 0:
            case 3:
            case 11:
            case 13:
                if (!(ext->flags_0 & 0x100))
                {
                    wp->routine_1 = 0;
                    break;
                }
                // fall through
            case 8:
            case 9:
                wp->routine_1 = 4;
                break;
            default:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ext->flags_0 &= ~1;
    }
    if (ext->u_34.h[0] != 0)
    {
        ext->u_34.h[0]--;
    }
    if (ext->value_A != 0)
    {
        ext->value_A--;
    }
    if (ext->u_34.h[1] != 0)
    {
        ext->u_34.h[1]--;
    }
    if (ext->flags_0 & 0x800)
    {
        if (--ext->u_38.h[0] < 0)
        {
            ext->effect_50 = func_80031618();
            if (ext->effect_50 != NULL)
            {
                ext->effect_50->flags_0         = 5;
                ext->effect_50->kind_2          = 0x80;
                ext->effect_50->variant_3       = 0x41;
                ext->effect_50->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80031988(ext->u_44.fx[0]);
            func_80031988(ext->u_44.fx[1]);
            ext->obj_40->u_E.b.byte_F |= 2;
            func_80047228(wp, &wp->vec_180[0], 0);
            Sound_call2(0xA1, &wp->vec_180[0]);
        }
    }
}

void func_801036B0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if (wp->ext.flags_0 & 2)
    {
        func_80105318(wp);
    }
    wp->ext.u_3C.h[0] = (wp->ext.u_3C.h[0] - 0x80 - wp->ext.u_2.b[0]) & 0xFFF;
    D_80114BB4[wp->routine_1](wp);
    if (wp->ext.flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 6:
                wp->routine_1 = 8;
                break;
            case 7:
                wp->routine_1 = 9;
                break;
            default:
                wp->routine_1 = 2;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ext->flags_0 &= ~1;
    }
    if (ext->value_A != 0)
    {
        ext->value_A--;
    }
    if (ext->flags_0 & 0x800)
    {
        if (--ext->u_34.h[1] < 0)
        {
            ext->effect_50 = func_80031618();
            if (ext->effect_50 != NULL)
            {
                ext->effect_50->flags_0         = 5;
                ext->effect_50->kind_2          = 0x80;
                ext->effect_50->variant_3       = 0x41;
                ext->effect_50->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80031988(ext->u_44.fx[0]);
            func_80031988(ext->u_44.fx[1]);
            ext->obj_40->u_E.b.byte_F |= 2;
            func_80047228(wp, &wp->vec_180[0], 1);
            Sound_call2(0xA1, &wp->vec_180[0]);
        }
    }
}

void func_80103870(ST1D_VIEW *wp)
{
    func_80031824(wp);
    func_80031988(wp->ext.u_44.fx[0]);
    func_80031988(wp->ext.u_44.fx[1]);
}

void func_801038B0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 0;
            wp->ext.u_4.h[0] = 30;
            wp->ext.value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_80103920(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext              = &wp->ext;
    wp->ext.u_58.obj = STAGE_PL_OBJ;
    if (wp->ext.value_14 & 0x2000000)
    {
        wp->ext.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2     = 1;
            wp->value_AC      = 1;
            wp->ext.value_8   = 0;
            wp->ext.u_34.h[1] = (wp->ext.u_2.h & 0x1F) + 0x10;
            if (wp->variant_3 == 0)
            {
                wp->ext.u_34.h[0] = 300;
            }
            // fall through
        case 1:
            if (wp->value_A6 == 2)
            {
                Sound_call2(0xB6, &wp->position);
            }
            wp->u_64.h[0]  = Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + wp->u_64.h[0]) & 0xFFF;
            Obj_pos_set(wp, 0x100, 0, 0);
            ext->u_5C.w          = Obj_map_push_out(wp);
            y                    = Obj_ceiling_height_get(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position.y            = wp->position_prev.y;
                wp->position_fixed.y      = wp->position_fixed_prev.y;
                break;
            }
            if (ext->u_5C.w & 0xF00)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 11;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (wp->variant_3 == 0 && ext->u_34.h[0] == 0)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if ((uint32)wp->value_80 <= 0x1FFFF)
            {
                wp->routine_1             = 12;
                *(uint16 *)&wp->routine_2 = 0;
                if ((uint8)wp->value_A4 < 15)
                {
                    ext->flags_0 |= 8;
                }
                else
                {
                    ext->flags_0 &= ~8;
                }
                break;
            }
            if (wp->variant_3 == 0 && ext->u_34.h[1] == 0 &&
                func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x100, &ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y,
                              0x100))
            {
                switch (func_801052A0(wp))
                {
                    case 0:
                        ext->flags_0 |= 0x40;
                        // fall through
                    case 1:
                        wp->routine_1             = 12;
                        *(uint16 *)&wp->routine_2 = 0;
                        ext->flags_0 |= 0x200;
                        if ((uint8)wp->value_A4 < 15)
                        {
                            ext->flags_0 |= 8;
                        }
                        else
                        {
                            ext->flags_0 &= ~8;
                        }
                        break;
                }
            }
            if (wp->variant_3 == 1 && ext->u_34.h[0] == 0 &&
                func_80031DCC(&wp->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x18, &ext->u_58.obj->position_fixed.v,
                              ext->u_58.obj->rotation.y, 0x300))
            {
                ext->piece_54 = (STAGE_PIECE *)Open_SHL_WORK();
                if (ext->piece_54 != NULL)
                {
                    ext->piece_54->flags_0        = 1;
                    ext->piece_54->kind_2         = 9;
                    ext->piece_54->variant_3      = 0;
                    ext->piece_54->position       = wp->position;
                    ext->piece_54->position_fixed = wp->position_fixed;
                    func_8002FFC4(&ext->piece_54->position, &ext->piece_54->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF,
                                  0x6E0, -0xD00, 0);
                    ext->piece_54->angle_64 = wp->rotation.y;
                    ext->u_34.h[0]          = 60;
                    ext->obj_40->u_E.b.byte_F |= 1;
                    ext->u_44.fx[0]->routine_1 = 0;
                    ext->u_44.fx[1]->routine_1 = 0;
                }
            }
            break;
    }
}

void func_80103D6C(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext              = &wp->ext;
    wp->ext.u_58.obj = STAGE_PL_OBJ;
    if (wp->ext.value_14 & 0x2000000)
    {
        wp->ext.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->value_AC    = 2;
            wp->ext.value_8 = D_80098844[wp->kind_2]->value_A;
            // fall through
        case 1:
            if (wp->value_A6 == 2)
            {
                Sound_call2(0xB6, &wp->position);
            }
            if (!(ext->flags_0 & 0x100))
            {
                ext->flags_0 |= 1;
                break;
            }
            Obj_pos_set(wp, 0x200, 0, 0);
            ext->u_5C.w          = Obj_map_push_out(wp);
            y                    = Obj_ceiling_height_get(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position.y            = wp->position_prev.y;
                wp->position_fixed.y      = wp->position_fixed_prev.y;
                break;
            }
            if ((ext->u_5C.w & 0xF00) || (ext->value_14 & 0x2000000))
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 11;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if ((uint32)wp->value_80 > 0x480000 && func_80031E60(&ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y, 0x800,
                                                                 &wp->position_fixed, wp->rotation.y, 0x400))
            {
                wp->routine_1             = 13;
                *(uint16 *)&wp->routine_2 = 0;
                if (wp->value_A6 == 1)
                {
                    ext->flags_0 |= 8;
                }
                else
                {
                    ext->flags_0 &= ~8;
                }
            }
            break;
    }
}

void func_80103FB4(ST1D_VIEW *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->routine_2   = 1;
        wp->value_AC    = 0;
        wp->ext.value_8 = 0;
    }
}

void func_80103FD8(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext              = &wp->ext;
    wp->ext.u_58.obj = STAGE_PL_OBJ;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 5;
            wp->u_64.h[1]    = Muku(&wp->position, &wp->ext.u_58.obj->position, wp->rotation.y, 0x800) >> 2;
            wp->ext.u_4.h[0] = 4;
            wp->ext.value_8  = 0;
            wp->ext.obj_40->u_E.b.byte_F |= 1;
            wp->ext.u_44.fx[0]->routine_1 = 0;
            wp->ext.u_44.fx[1]->routine_1 = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y,
                                                    wp->u_64.h[1] < 0 ? -wp->u_64.h[1] : wp->u_64.h[1])) &
                             0xFFF;
            break;
    }
}

void func_801040F8(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 5;
            wp->ext.u_4.h[0] = 16;
            wp->ext.value_8  = 0;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + 0x80) & 0xFFF;
            if (--ext->u_4.h[0] <= 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_80104180(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x20;
            ext->value_8  = 0;
            ext->flags_0 &= ~0x20;
            wp->rotation.y &= 0xFFF;
            if (wp->value_6E <= 0)
            {
                ext->flags_0 &= ~4;
            }
            Obj_pos_set(wp, -0x460, 0, 0);
            Obj_map_push_out(wp);
            break;
        case 1:
            wp->routine_2 = 2;
            wp->u_44.h[0] = -0x190;
            wp->u_44.h[1] = 0;
            ext->u_4.h[0] = 3;
            Obj_pos_set(wp, wp->u_44.h[0], -0x960, 0);
            Obj_map_push_out(wp);
            break;
        case 2:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 3;
                wp->u_44.h[1] = 0x158;
            }
            // fall through
        case 3:
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1], 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->value_AC  = 0x21;
                    wp->routine_2 = 4;
                    wp->u_44.h[0] = -0xA0;
                    wp->u_44.h[1] = 0;
                    ext->u_4.h[0] = 6;
                }
            }
            break;
        case 4:
            if (ext->u_4.h[0] != 0)
            {
                ext->u_4.h[0]--;
            }
            wp->u_44.h[1] = (3 - ext->u_4.h[0]) << 4;
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1] << 4, 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->routine_2 = 5;
                    ext->u_4.h[0] = 10;
                }
            }
            break;
        case 5:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_801043B8(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x1E;
            ext->value_8  = 0;
            ext->flags_0 &= ~0x20;
            wp->rotation.y &= 0xFFF;
            if (wp->value_6E <= 0)
            {
                ext->flags_0 &= ~4;
            }
            Obj_pos_set(wp, 0x460, 0, 0);
            Obj_map_push_out(wp);
            break;
        case 1:
            wp->routine_2 = 2;
            wp->u_44.h[0] = 0x190;
            wp->u_44.h[1] = 0;
            ext->u_4.h[0] = 3;
            Obj_pos_set(wp, wp->u_44.h[0], -0x960, 0);
            Obj_map_push_out(wp);
            break;
        case 2:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 3;
                wp->u_44.h[1] = 0x158;
            }
            // fall through
        case 3:
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1], 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->value_AC  = 0x1F;
                    wp->routine_2 = 4;
                    wp->u_44.h[0] = 0xA0;
                    wp->u_44.h[1] = 0;
                    ext->u_4.h[0] = 6;
                }
            }
            break;
        case 4:
            if (ext->u_4.h[0] != 0)
            {
                ext->u_4.h[0]--;
            }
            wp->u_44.h[1] = (3 - ext->u_4.h[0]) << 4;
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1] << 4, 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->routine_2 = 5;
                    ext->u_4.h[0] = 10;
                }
            }
            break;
        case 5:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_801045F0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x1C;
            ext->u_4.h[0] = 7;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            ext->u_4.h[0] = 6;
            // fall through
        case 2:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            ext->u_4.h[0] = 10;
            // fall through
        case 3:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 4;
                ext->u_4.h[0] = 7;
            }
            else
            {
                Obj_pos_set(wp, 0xF0, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                break;
            }
            // fall through
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 0x21;
            }
            break;
    }
}

void func_8010478C(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x1D;
            ext->u_4.h[0] = 13;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                ext->u_4.h[0] = 3;
            }
            else
            {
                Obj_pos_set(wp, -0x50, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                break;
            }
            // fall through
        case 2:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            ext->u_4.h[0] = 8;
            // fall through
        case 3:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 4;
                ext->u_4.h[0] = 4;
            }
            break;
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 0x21;
            }
            Obj_pos_set(wp, -0x80, 0, 0);
            Obj_map_push_out(wp);
            y                    = Obj_ceiling_height_get(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position.y            = wp->position_prev.y;
                wp->position_fixed.y      = wp->position_fixed_prev.y;
            }
            break;
    }
}

void func_80104974(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    wp->ext.u_58.obj = STAGE_PL_OBJ;
    ext              = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x11;
            ext->u_4.h[0] = 10;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
            }
            else
            {
                wp->u_44.h[1] = 10 - ext->u_4.h[0];
            }
            // fall through
        case 2:
            Obj_pos_set(wp, 0, wp->u_44.h[1] << 7, 0);
            if (!(Obj_map_push_out(wp) & 0x1000))
            {
                break;
            }
            wp->routine_2 = 3;
            wp->value_AC  = 0x12;
            ext->u_4.h[0] = 3;
            // fall through
        case 3:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 4;
            wp->u_64.h[1] = Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, 0x800) / 3;
            ext->u_4.h[0] = 3;
            // fall through
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, STCOM_ABS(wp->u_64.h[1]))) & 0xFFF;
            break;
    }
}

void func_80104B20(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 0x13;
            wp->ext.u_4.h[0] = 13;
            wp->ext.value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                wp->value_AC  = 0;
                ext->u_4.h[0] = 6;
            }
            else
            {
                Obj_pos_set(wp, -0xF0, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                break;
            }
            // fall through
        case 2:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_80104C7C(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    wp->ext.u_58.obj = STAGE_PL_OBJ;
    ext              = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            if (ext->flags_0 & 8)
            {
                wp->value_AC  = 0x18;
                wp->u_48.h[0] = -0x1C;
            }
            else
            {
                wp->value_AC  = 0x14;
                wp->u_48.h[0] = 0x1C;
            }
            ext->u_4.h[0] = 5;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                wp->value_AC++;
                ext->u_4.h[0] = 10;
                Sound_call2(0xB7, &wp->position);
            }
            else
            {
                Obj_pos_set(wp, 0x200, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
            }
            break;
        case 2:
            ext->u_4.h[0]--;
            wp->u_44.h[1] = (5 - ext->u_4.h[0]) << 2;
            Obj_pos_set(wp, 0, wp->u_44.h[1] << 4, wp->u_48.h[0] << 4);
            if (Obj_map_push_out(wp) & 0x1000)
            {
                Sound_call2(0xB8, &wp->position);
                if ((ext->flags_0 & 0x200) && func_80031DCC(&wp->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x18,
                                                            &ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y, 0x300))
                {
                    ext->flags_0 &= ~0x200;
                    ext->piece_54 = (STAGE_PIECE *)Open_SHL_WORK();
                    if (ext->piece_54 != NULL)
                    {
                        ext->piece_54->flags_0        = 1;
                        ext->piece_54->kind_2         = 9;
                        ext->piece_54->variant_3      = 0;
                        ext->piece_54->position       = wp->position;
                        ext->piece_54->position_fixed = wp->position_fixed;
                        func_8002FFC4(&ext->piece_54->position, &ext->piece_54->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF,
                                      0x6E0, -0xD00, 0);
                        ext->piece_54->angle_64 = wp->rotation.y;
                        ext->obj_40->u_E.b.byte_F |= 1;
                        ext->u_44.fx[0]->routine_1 = 0;
                        ext->u_44.fx[1]->routine_1 = 0;
                    }
                }
                wp->routine_2 = 3;
                wp->value_AC++;
                ext->u_4.h[0] = 4;
            }
            break;
        case 3:
            if (--ext->u_4.h[0] < 0 && (ext->flags_0 & 0x40))
            {
                wp->routine_2 = 4;
                ext->u_4.h[0] = 15;
            }
            // fall through
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
                if (ext->flags_0 & 0x40)
                {
                    if (ext->flags_0 & 8)
                    {
                        wp->rotation.y += 0x400;
                    }
                    else
                    {
                        wp->rotation.y -= 0x400;
                    }
                    wp->rotation.y &= 0xFFF;
                }
                ext->flags_0 &= ~0x40;
            }
            break;
    }
}

void func_80105060(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    wp->ext.u_58.obj = STAGE_PL_OBJ;
    ext              = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            if (wp->ext.flags_0 & 8)
            {
                wp->value_AC = 0x1B;
            }
            else
            {
                wp->value_AC = 0x17;
            }
            ext->u_4.h[0] = 6;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                ext->u_4.h[0] = 4;
            }
            else
            {
                Obj_pos_set(wp, 0x180, 0, 0);
                ext->u_5C.w          = Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                else if (ext->u_5C.w & 0xF00)
                {
                    wp->routine_1             = 11;
                    *(uint16 *)&wp->routine_2 = 0;
                }
                break;
            }
            // fall through
        case 2:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->u_64.h[1] = Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, 0x800) / 3;
            ext->u_4.h[0] = 3;
            // fall through
        case 3:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, STCOM_ABS(wp->u_64.h[1]))) & 0xFFF;
            break;
    }
}

sint32 func_801052A0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext            = &wp->ext;
    wp->u_64.h[0]  = 0;
    wp->ext.u_4C.i = 0;
    while (1)
    {
        wp->u_64.h[0] += D_80114BFC[ext->u_4C.i];
        if ((ext->u_2.h & 0xF) < wp->u_64.h[0])
        {
            break;
        }
        if (++ext->u_4C.i >= 2)
        {
            break;
        }
    }
    return ext->u_4C.i;
}

sint32 func_80105318(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if ((wp->ext.u_4C.i = wp->ext.value_14 & 0xFFFFFF) != 0)
    {
        if (wp->ext.value_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= wp->ext.u_4C.i;
            if (wp->value_6E <= 0)
            {
                wp->ext.flags_0 = (wp->ext.flags_0 & ~2) | 0x820;
                wp->ext.u_4C.i  = D_80098844[wp->kind_2]->limit_9;
            }
            if (wp->ext.flags_0 & 0x20)
            {
                wp->ext.value_A += wp->ext.u_4C.i;
                if ((wp->ext.value_14 & 0x20000000) || wp->ext.value_A >= D_80098844[wp->kind_2]->limit_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    if (wp->ext.from_1C.pad & 1)
                    {
                        wp->u_64.h[0] = Angle_xz_svector(&wp->position, &wp->ext.from_1C);
                        if (((wp->rotation.y - wp->u_64.h[0] + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->routine_1  = 6;
                            wp->rotation.y = wp->u_64.h[0];
                        }
                        else
                        {
                            wp->routine_1  = 7;
                            wp->rotation.y = (wp->u_64.h[0] + 0x800) & 0xFFF;
                        }
                    }
                    else
                    {
                        wp->u_64.h[0] = Angle_xz_svector(&D_80114C00, &wp->ext.from_1C);
                        if (((wp->u_64.h[0] - wp->rotation.y + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->routine_1  = 7;
                            wp->rotation.y = wp->u_64.h[0];
                        }
                        else
                        {
                            wp->routine_1  = 6;
                            wp->rotation.y = (wp->u_64.h[0] + 0x800) & 0xFFF;
                        }
                    }
                    *(uint16 *)&wp->routine_2 = 0;
                    ext->value_A              = 0;
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
            else if ((wp->ext.value_14 & 0x20000000) || wp->ext.value_A >= D_80098844[wp->kind_2]->limit_9)
            {
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
