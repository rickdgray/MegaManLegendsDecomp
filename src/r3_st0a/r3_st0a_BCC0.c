#include "common.h"
#include "st0a.h"

#ifdef __wasm32__
void func_80036478(void *track, uint8 arg1, uint32 arg2);
#endif

void func_8010BCC0(ST0A_VIEW *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_AC.b[1]           = wp->u_AC.b[0];
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 0x42;
            func_8002F9C4(wp, NULL);
            wp->value_158  = 0x02800280;
            wp->u_15C.w[0] = 0x280;
            wp->u_15C.h[1] = 0x4210;
            wp->value_78   = 0;
            wp->u_AC.b[0]  = 0;
            wp->u_AC.b[1]  = 0xFF;
            wp->value_500  = 0;
            wp->routine_0++;
            break;
        case 1:
            wp->u_AC.b[1] = 0xFF;
            break;
        case 2:
            break;
        case 3:
            if (wp->value_500 < 0x40)
            {
                wp->position.x -= 4;
                wp->position_fixed.x = wp->position.x << 16;
                wp->rotation.y += 0x20;
            }
            wp->value_500++;
            break;
    }
    if (wp->u_AC.b[0] != wp->u_AC.b[1])
    {
        func_800322A8(wp, wp->u_AC.b[0], 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010BE60(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    sint32 i;

    ext = &wp->ext;
    D_80116208[wp->routine_0](wp);
    ext->hit_C.hit_8  = 0;
    ext->hit_48.hit_8 = 0;
    ext->hit_58.hit_8 = 0;
    for (i = 0; i < 6; i++)
    {
        ext->hit_88[i].hit_8 = 0;
    }
}

void func_8010BECC(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    sint32 i;
    sint16 life;

    ext = &wp->ext;
    wp->flags_0 |= 0x42;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0] = 0x2800280;
    wp->scale.words[1] = 0x280;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 15; i++)
    {
        wp->joint_180[i].pad = 0x4210;
    }
    *(sint32 *)&wp->value_64 = 0;
    wp->value_64             = 0xC;
    wp->value_66             = 0x400;
    wp->rotation.y           = 0xC00;
    wp->rotation.x           = 0;
    wp->rotation.z           = 0;
    wp->value_44.value       = 0;
    wp->value_48.value       = 0;
    ext->flags_0             = 0x180C;
    ext->flags_F2            = 0;
    *(sint32 *)&ext->timer_4 = 0;
    *(sint32 *)&ext->value_8 = 0;
    ext->hit_C.hit_8         = 0;
    ext->hit_C.value_C       = 0;
    ext->hit_48.hit_8        = 0;
    ext->hit_48.value_C      = 0;
    ext->hit_58.hit_8        = 0;
    ext->hit_58.value_C      = 0;
    ext->obj_80[0]           = NULL;
    ext->obj_80[1]           = NULL;
    ext->value_40            = 0;
    ext->value_F6            = 0;
    for (i = 0; i < 2; i++)
    {
        ext->spark_E8[i] = NULL;
    }
    for (i = 0; i < 6; i++)
    {
        ext->hit_88[i].hit_8   = 0;
        ext->hit_88[i].value_C = 0;
    }
    func_80036478(ext->track_24, 0, -0x320);
    ext->angle_42 = 0xC00;
    ext->value_44 = (wp->rotation.y + 0xC00) & 0xFFF;
    ext->value_46 = ext->value_F4 = D_8009884C[wp->kind_2]->value_E << 5;
    ext->value_F0                 = 0;
    life                          = D_8009884C[wp->kind_2]->life_8 << 5;
    wp->life_6E                   = life;
    wp->value_78                  = 0;
    wp->value_10                  = 0;
    wp->life_max_B0               = life;
    wp->life_prev_B2              = life;
    ext->value_F8                 = wp->life_6E;
    wp->routine_0                 = 1;
    wp->routine_1                 = 0;
    *(uint16 *)&wp->routine_2     = 0;
    func_800322A8(wp, 0, 0);
    func_8010C0A0(wp);
}

void func_8010C0A0(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    STCOM_EFFECT *fx;
    sint32 i;
    sint16 y;

    ext                     = &wp->ext;
    pl                      = &STAGE_PL;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    for (i = 0; i < 15; i++)
    {
        wp->joint_180[i].pad = 0x4210;
    }
    ext->value_2 = rand();
    func_8005D4C0();
    if (ext->flags_0 & 0x400)
    {
        if (wp->life_6E - D_8009884C[wp->kind_2]->value_B > 0)
        {
            wp->life_6E -= D_8009884C[wp->kind_2]->value_B;
            ext->flags_0 &= ~0x400;
        }
        else
        {
            ext->hit_C.hit_8 |= 0x10000000 | D_8009884C[wp->kind_2]->value_B;
        }
    }
    if (ext->flags_0 & 0x4000)
    {
        if (wp->life_6E - D_8009884C[wp->kind_2]->value_F > 0)
        {
            wp->life_6E -= D_8009884C[wp->kind_2]->value_F;
            ext->flags_0 &= ~0x4000;
        }
        else
        {
            ext->hit_C.hit_8 |= 0x10000000 | D_8009884C[wp->kind_2]->value_F;
        }
    }
    if (ext->flags_0 & 0x1000)
    {
        func_8010EF3C(wp);
    }
    if (ext->flags_0 & 4)
    {
        func_8010EBE8(wp);
    }
    D_80116218[wp->routine_1](wp);
    y = -2;
    if (STAGE_FRAME & 1)
    {
        y = -1;
    }
    wp->position.y         = y;
    wp->position_fixed.v.y = y << 16;
    if (ext->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
            case 6:
                wp->routine_1 = wp->byte_D;
                break;
            case 3:
                if (wp->byte_F & 4)
                {
                    wp->byte_F &= ~4;
                    wp->routine_1 = 5;
                    ext->flags_0 |= 0x100;
                    break;
                }
                // fall through
            case 4:
            case 5:
            case 10:
                if (ext->flags_0 & 0x100)
                {
                    ext->flags_0 &= ~0x100;
                    if (pl->value_76 != 0 && pl->value_C0 == wp)
                    {
                        wp->routine_1 = 7;
                        break;
                    }
                }
                // fall through
            default:
                func_8010E8A0(wp);
                wp->routine_1 = 6;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ext->flags_0 &= ~1;
    }
    if (ext->value_40 != 0)
    {
        ext->value_40--;
    }
    if (ext->value_A != 0)
    {
        ext->value_A--;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    ST0A_SP_182 = ext->angle_42;
    func_8003346C(wp);
    if (ext->obj_80[0] != NULL)
    {
        func_8010ED90(wp, 3);
    }
    if (ext->obj_80[1] != NULL)
    {
        func_8010ED90(wp, 8);
    }
    if (ext->flags_F2 & 1)
    {
        if (ext->value_F0 == 0)
        {
            Sound_call2(0xF3, &wp->position);
        }
        if (++ext->value_F0 >= 0x1F)
        {
            ext->value_F0 = 1;
            Sound_call2(0xF4, &wp->position);
        }
    }
    else
    {
        ext->value_F0 = 0;
    }
    ext->flags_F2 &= ~1;
    wp->value_44.half[0] = (wp->position.x - wp->position_prev.x) << 4;
    wp->value_44.half[1] = (wp->position.y - wp->position_prev.y) << 4;
    wp->value_48.half[0] = (wp->position.z - wp->position_prev.z) << 4;
    if (ext->flags_0 & 0x200)
    {
        return;
    }
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x200, 0x200, 1);
        func_80051B68(wp, 1, 0, D_8009884C[wp->kind_2]->value_C | 0x1000000);
    }
    if (ext->flags_0 & 0x200)
    {
        return;
    }
    if (wp->flags_0 & 1)
    {
        if (ext->flags_0 & 2)
        {
            ext->hit_C.pos_0 = wp->position;
            ext->fpos_70.x   = ext->hit_C.pos_0.x << 16;
            ext->fpos_70.y   = ext->hit_C.pos_0.y << 16;
            ext->fpos_70.z   = ext->hit_C.pos_0.z << 16;
            func_8002FFC4(&ext->hit_C.pos_0, &ext->fpos_70, wp->rotation.y, 0xD00, -0x3200, 0);
            func_800341BC(&ext->hit_C.pos_0, 0x20, 0, 0x8000, wp->value_1, &ext->hit_C.hit_8,
                          0x4080000, 0, 0x80);
        }
        if (ext->flags_0 & 0x800)
        {
            for (i = 0; i < 6; i++)
            {
                ext->hit_C.pos_0 = wp->position;
                ext->fpos_70.x   = ext->hit_C.pos_0.x << 16;
                ext->fpos_70.y   = ext->hit_C.pos_0.y << 16;
                ext->fpos_70.z   = ext->hit_C.pos_0.z << 16;
                func_8002FFC4(&ext->hit_C.pos_0, &ext->fpos_70,
                              (wp->rotation.y + ext->angle_42) & 0xFFF, D_80116260[i].x << 4,
                              D_80116260[i].y << 4, D_80116260[i].z << 4);
                func_800341BC(&ext->hit_C.pos_0, 0x40, 0, 0x8000, wp->value_1,
                              &ext->hit_88[i].hit_8, D_8009884C[wp->kind_2]->value_D | 0x4080000, 0,
                              0x80);
                if (!(ext->flags_0 & 0x1000) && i < 2)
                {
                    if (ext->flags_0 & 0x8000)
                    {
                        ext->flags_0 &= ~0x8000;
                        fx = func_80031618();
                        if (fx != NULL)
                        {
                            fx->flags_0         = 5;
                            fx->kind_2          = 0x80;
                            fx->variant_3       = 0x42;
                            fx->value_C         = 1;
                            fx->value_D         = 0;
                            fx->sprite.position = ext->hit_C.pos_0;
                        }
                    }
                    ext->spark_E8[i]->x_1C = ext->hit_C.pos_0.x;
                    ext->spark_E8[i]->y_1E = ext->hit_C.pos_0.y;
                    ext->spark_E8[i]->z_20 = ext->hit_C.pos_0.z;
                }
            }
        }
        if (ext->flags_0 & 0x20)
        {
            ext->hit_58.pos_0 = wp->joint_180[8];
            func_800341BC(&ext->hit_58.pos_0, 0x100, 0, 0x8000, wp->value_1, &ext->hit_58.hit_8,
                          D_8009884C[wp->kind_2]->value_A | 0x4000000, 0, 0x80);
        }
        if (ext->flags_0 & 0x40)
        {
            ext->hit_48.pos_0 = wp->joint_180[3];
            func_800341BC(&ext->hit_48.pos_0, 0x100, 0, 0x8000, wp->value_1, &ext->hit_48.hit_8,
                          D_8009884C[wp->kind_2]->value_A | 0x4000000, 0, 0x80);
        }
    }
    if (!(ext->flags_0 & 0x200) && (sint32)Moji_flag >= 0)
    {
        if (!(ext->flags_F2 & 0x40) && ext->value_F8 < wp->life_max_B0 / 4)
        {
            ext->flags_F2 |= 0x70;
            MojiTaskExec2(4, 6);
        }
        if (!(ext->flags_F2 & 0x20) && ext->value_F8 < wp->life_max_B0 / 2)
        {
            ext->flags_F2 |= 0x30;
            MojiTaskExec2(4, 5);
        }
        if (!(ext->flags_F2 & 0x10) && wp->life_max_B0 != ext->value_F8)
        {
            ext->flags_F2 |= 0x10;
            MojiTaskExec2(4, 4);
        }
        if (!(ext->flags_F2 & 8) && ext->value_46 < ext->value_F4 / 4)
        {
            ext->flags_F2 |= 0xE;
            MojiTaskExec2(4, 3);
        }
        if (!(ext->flags_F2 & 4) && ext->value_46 < ext->value_F4 / 2)
        {
            ext->flags_F2 |= 6;
            MojiTaskExec2(4, 2);
        }
        if (!(ext->flags_F2 & 2) && ext->value_F4 != ext->value_46)
        {
            ext->flags_F2 |= 2;
            MojiTaskExec2(4, 1);
        }
    }
}

void func_8010CB1C(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    sint32 i;

    ext = &wp->ext;
    for (i = 0; i < 2; i++)
    {
        if (ext->spark_E8[i] != NULL)
        {
            ext->spark_E8[i]->routine_2 = 2;
        }
    }
    if (ext->obj_80[0] != NULL)
    {
        func_800318D8(ext->obj_80[0]);
    }
    if (ext->obj_80[1] != NULL)
    {
        func_800318D8(ext->obj_80[1]);
    }
    func_8003187C(wp);
}

void func_8010CBB4(void)
{
}

void func_8010CBBC(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    sint16 angle;

    ext = &wp->ext;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC     = 0;
            wp->ext.timer_4 = 0x3C;
            // fall through
        case 1:
            if (pl->value_76 != 0 && pl->value_C0 == wp)
            {
                if (--ext->timer_4 < 0)
                {
                    wp->byte_D = func_8010E95C(wp);
                    goto turn;
                }
            }
            else if (--ext->timer_4 < 0)
            {
                wp->byte_D = func_8010E95C(wp);
                goto turn;
            }
            else if (ext->value_40 == 0)
            {
                if (ST0A_ABS(STAGE_PL.position.y - wp->position.y) < 0x200)
                {
                    angle = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x80);
                    if (ST0A_ABS(angle) < 0x80 && wp->dist_80 < 0x200000)
                    {
                        wp->byte_D = 2;
                        goto turn;
                    }
                    if (ST0A_ABS(angle) < 0x80 && wp->dist_80 < 0x1200000)
                    {
                        wp->byte_D = 0xB;
                        goto turn;
                    }
                }
                else
                {
                    angle = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x600);
                    if (ST0A_ABS(angle) < 0x600)
                    {
                        wp->byte_D = 1;
                    turn:
                        ext->value_44 = (wp->rotation.y + ext->angle_42) & 0xFFF;
                        ext->flags_0 |= 1;
                    }
                }
            }
            break;
    }
}

void func_8010CE0C(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    sint16 step;

    ext = &wp->ext;
    pl  = &STAGE_PL;

    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 2;
            wp->routine_2++;
            break;
        case 1:
            step           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 3;
                wp->routine_2++;
                func_8010EE60(wp, 3);
            }
            break;
        case 2:
            step           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            if (ext->obj_80[0] == NULL)
            {
                wp->anim_AC = 4;
                wp->routine_2 += 2;
            }
            else if (ext->obj_80[0]->u_C.b.byte_C != 0)
            {
                wp->anim_AC = 4;
                wp->routine_2++;
                ext->timer_4 = 0xE;
            }
            break;
        case 3:
            if (--ext->timer_4 == 0)
            {
                wp->routine_2++;
                ext->obj_80[0]->u_C.b.byte_C -= 0x80;
                ext->obj_80[0] = NULL;
            }
            break;
        case 4:
            if (wp->value_A7 < 0)
            {
                ext->value_40 = 0x78;
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_8010CFE8(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STCOM_SVECTOR *center;
    uint16 angle;

    center = D_80116248;
    // One loop level around the two copies (a macro body?): it keeps GCC from reusing the
    // copy's destination address for the call after func_80031198.
    do
    {
        wp->ext.pos_68  = *center;
        wp->ext.fpos_70 = D_80116250;
    } while (0);
    angle = wp->value_64 + func_80031198(center, &wp->position);
    func_8002FFC4(&wp->ext.pos_68, &wp->ext.fpos_70, angle & 0xFFF, 0x5000, 0, 0);
    wp->position         = wp->ext.pos_68;
    wp->position_fixed.v = wp->ext.fpos_70;
    wp->ext.angle_42     = (angle + wp->value_66 - wp->rotation.y) & 0xFFF;
    wp->ext.flags_F2 |= 1;
    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 5;
            wp->routine_2++;
            ext->timer_4 = 7;
            ext->flags_0 |= 0x20;
            ext->flags_0 &= ~0x40;
            Sound_call2(0xFC, &wp->position);
            break;
        case 1:
            if (--ext->timer_4 == 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xE;
            }
            break;
        case 2:
            if (--ext->timer_4 == 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0x10;
                ext->flags_0 |= 0x40;
                ext->flags_0 &= ~0x20;
                Sound_call2(0xFC, &wp->position);
            }
            wp->rotation.y = (wp->rotation.y + 0x1E) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - 0x1E) & 0xFFF;
            break;
        case 3:
            if (--ext->timer_4 == 0)
            {
                wp->rotation.y -= 2;
                ext->angle_42 += 2;
                wp->routine_2++;
                ext->timer_4 = 0xA;
            }
            wp->rotation.y = (wp->rotation.y - 0x35) & 0xFFF;
            ext->angle_42  = (ext->angle_42 + 0x35) & 0xFFF;
            break;
        case 4:
            if (--ext->timer_4 == 0)
            {
                wp->routine_2++;
            }
            wp->rotation.y = (wp->rotation.y + 0x2B) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - 0x2B) & 0xFFF;
            break;
        case 5:
            if (wp->value_A7 < 0)
            {
                ext->value_40 = 0x5A;
                ext->flags_0 &= ~0x60;
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_8010D2F4(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;
    sint32 step;

    ext = &wp->ext;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0;
            wp->routine_2++;
            ext->timer_4    = 0xF;
            ext->pos_68.pad = (uint32)ST0A_ABS(func_80031BEC(&pl->position, &wp->position,
                                                             wp->rotation.y, 0x200)) >>
                              4;
            ext->flags_0 |= 0x2000;
            break;
        case 1:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xB;
                ext->flags_0 |= 2;
            }
            if (pl->value_76 == 0 || pl->value_C0 != wp)
            {
                step = func_80031BEC(&pl->position, &wp->position, wp->rotation.y, ext->pos_68.pad);
                wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
                ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            }
            else
            {
                wp->routine_2++;
                ext->timer_4 = 0xB;
                ext->flags_0 |= 2;
                Sound_call2(0xF7, &wp->position);
            }
            break;
        case 2:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xA;
            }
            func_8010E9C8(wp, 0);
            break;
        case 3:
            if (--ext->timer_4 < 0)
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->flags_0          = 1;
                    obj->kind_2           = 0;
                    obj->value_4          = 6;
                    obj->variant_3        = 0;
                    obj->u_C.b.byte_C     = wp->value_1;
                    obj->u_E.b.byte_F     = 1;
                    obj->position         = wp->position;
                    obj->position_fixed.v = wp->position_fixed.v;
                    func_8002FFC4(&obj->position, &obj->position_fixed.v, wp->rotation.y, 0xD00,
                                  -0x2E20, 0);
                    obj->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                }
                wp->routine_2++;
                if (pl->value_76 == 0)
                {
                    ext->timer_4 = 0x69;
                }
                else
                {
                    ext->timer_4 = 0x2D;
                }
            }
            break;
        case 4:
            if (wp->byte_F & 2)
            {
                if (--ext->timer_4 < 0)
                {
                    wp->routine_2++;
                    ext->timer_4 = 0xB;
                    Sound_call2(0xF8, &wp->position);
                }
            }
            break;
        case 5:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                wp->byte_F &= ~2;
                ext->timer_4 = 0xF;
                ext->flags_0 &= ~2;
            }
            func_8010E9C8(wp, 1);
            break;
        case 6:
            if (--ext->timer_4 < 0)
            {
                ext->flags_0 |= 1;
                ext->flags_0 &= ~0x2000;
            }
            break;
    }
}

void func_8010D6C0(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;
    sint32 step;
    sint32 i;

    ext = &wp->ext;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0;
            wp->routine_2++;
            ext->timer_4    = 0xF;
            ext->pos_68.pad = (uint32)ST0A_ABS(func_80031BEC(&pl->position, &wp->position,
                                                             wp->rotation.y, 0x200)) >>
                              4;
            ext->flags_0 |= 0x2000;
            break;
        case 1:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xB;
                ext->flags_0 |= 2;
            }
            if (pl->value_76 == 0 || pl->value_C0 != wp)
            {
                step = func_80031BEC(&pl->position, &wp->position, wp->rotation.y, ext->pos_68.pad);
                wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
                ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            }
            else
            {
                wp->routine_2++;
                ext->timer_4 = 0xB;
                ext->flags_0 |= 2;
                Sound_call2(0xF7, &wp->position);
            }
            break;
        case 2:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xA;
            }
            func_8010E9C8(wp, 0);
            break;
        case 3:
            if (--ext->timer_4 < 0)
            {
                for (i = 0; i < 4; i++)
                {
                    obj = (STAGE_OBJ *)func_80031518();
                    if (obj != NULL)
                    {
                        ext->pos_68    = wp->position;
                        ext->fpos_70.x = wp->position.x << 16;
                        ext->fpos_70.y = wp->position.y << 16;
                        ext->fpos_70.z = wp->position.z << 16;
                        func_8002FFC4(&ext->pos_68, &ext->fpos_70, wp->rotation.y, 0xD00, -0x3200,
                                      0);
                        obj->flags_0  = 1;
                        obj->kind_2   = 3;
                        obj->position = ext->pos_68;
                        obj->rotation.y =
                            (uint16)(wp->rotation.y + ((rand() & 0x3FF) + 0x800)) - 0x200;
                    }
                }
                wp->routine_2++;
                if (pl->value_76 == 0)
                {
                    ext->timer_4 = 0x69;
                }
                else
                {
                    ext->timer_4 = 0x2D;
                }
            }
            break;
        case 4:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xB;
                Sound_call2(0xF8, &wp->position);
            }
            break;
        case 5:
            if (--ext->timer_4 < 0)
            {
                wp->routine_2++;
                ext->timer_4 = 0xF;
                ext->flags_0 &= ~2;
            }
            func_8010E9C8(wp, 1);
            break;
        case 6:
            if (--ext->timer_4 < 0)
            {
                ext->flags_0 |= 1;
                ext->flags_0 &= ~0x2000;
            }
            break;
    }
}

void func_8010DAA8(ST0A_EM *wp)
{
    sint32 i;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0xC;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                wp->anim_AC = 8;
                Sound_call2(0xA1, &wp->position);
                Sound_call2(0xA2, &wp->position);
                wp->ext.flags_0 |= 0x400;
            }
            break;
        case 2:
            if (wp->value_A6 != 0)
            {
                Sound_call2(0x151, &wp->position);
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
            }
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0xB;
                wp->routine_2++;
            }
            for (i = 0; i < 15; i++)
            {
                wp->joint_180[i].pad = 0x7FFF;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                wp->ext.value_40 = 0x78;
                wp->ext.flags_0 |= 1;
            }
            break;
    }
}

void func_8010DC08(ST0A_EM *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0xC;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                wp->anim_AC = 8;
            }
            break;
        case 2:
            if (wp->value_A6 != 0)
            {
                Sound_call2(0x151, &wp->position);
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
            }
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0xB;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                wp->ext.flags_0 |= 1;
            }
            break;
    }
}

void func_8010DD20(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    STCOM_SVECTOR *pos;
    STCOM_FIXED_VECTOR *fpos;
    STCOM_SVECTOR *self;
    sint16 step;
    uint16 angle;
    STCOM_SVECTOR *center;

    ext = &wp->ext;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 1;
            if (wp->ext.flags_0 & 0x80)
            {
                wp->value_64 = -wp->value_64;
                wp->value_66 = -wp->value_66;
            }
            wp->ext.timer_4 = 0x78;
            // fall through
        case 1:
            ext->pos_68  = wp->position;
            ext->fpos_70 = wp->position_fixed.v;
            pos          = &ext->pos_68;
            fpos         = &ext->fpos_70;
            func_8002FFC4(pos, fpos, (wp->rotation.y + ext->angle_42) & 0xFFF, 0x800, 0, 0);
            self           = &wp->position;
            step           = func_80031BEC(self, pos, wp->rotation.y, 0x20);
            center         = D_80116248;
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            ext->pos_68    = *center;
            ext->fpos_70   = D_80116250;
            angle          = wp->value_64 + func_80031198(center, self);
            func_8002FFC4(pos, fpos, angle & 0xFFF, 0x5000, 0, 0);
            ext->flags_F2 |= 1;
            ext->angle_42        = (angle + wp->value_66 - wp->rotation.y) & 0xFFF;
            wp->position         = ext->pos_68;
            wp->position_fixed.v = ext->fpos_70;
            if (pl->value_76 != 0 && pl->value_C0 == wp)
            {
                if (--ext->timer_4 < 0)
                {
                    wp->byte_D = func_8010E95C(wp);
                    goto turn;
                }
            }
            else if (--ext->timer_4 < 0)
            {
                wp->byte_D = func_8010E95C(wp);
                goto turn;
            }
            else if (ext->value_40 == 0)
            {
                if (ST0A_ABS(STAGE_PL.position.y - wp->position.y) < 0x200)
                {
                    step = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x80);
                    if (ST0A_ABS(step) < 0x80 && wp->dist_80 < 0x200000)
                    {
                        wp->byte_D = 2;
                        goto turn;
                    }
                    if (ST0A_ABS(step) < 0x80 && wp->dist_80 < 0x1200000)
                    {
                        wp->byte_D = 0xB;
                        goto turn;
                    }
                }
                else
                {
                    step = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x600);
                    if (ST0A_ABS(step) < 0x600)
                    {
                        wp->byte_D = 1;
                    turn:
                        ext->value_44 = (wp->rotation.y + ext->angle_42) & 0xFFF;
                        ext->flags_0 |= 1;
                    }
                }
            }
            break;
    }
    if (wp->value_A6 != 0)
    {
        Sound_call2(0xF6, &wp->position);
    }
}

void func_8010E164(ST0A_EM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            if (func_80031DCC(&wp->position_fixed, (wp->rotation.y + 0x400) & 0xFFF, 0x400,
                              &pl->position_fixed, STAGE_PL.rotation.y, 0x800))
            {
                wp->anim_AC = 6;
                wp->ext.flags_0 |= 0x40;
                wp->ext.flags_0 &= ~0x20;
            }
            else
            {
                wp->anim_AC = 7;
                wp->ext.flags_0 |= 0x20;
                wp->ext.flags_0 &= ~0x40;
            }
            Sound_call2(0xFC, &wp->position);
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->ext.flags_0 |= 1;
                wp->ext.flags_0 &= ~0x160;
            }
            break;
    }
}

void func_8010E254(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STCOM_EFFECT *fx;
    STCOM_SVECTOR *pos;
    STCOM_FIXED_VECTOR *fpos;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC     = 0xC;
            wp->ext.timer_4 = 5;
            wp->ext.value_6 = 0;
            wp->routine_3   = 0;
            MojiTaskExec2(0, 8);
            wp->ext.flags_F2 |= 0x7E;
            break;
        case 1:
            if (--wp->ext.timer_4 < 0)
            {
                pos             = &wp->ext.pos_68;
                *pos            = wp->position;
                wp->ext.fpos_70 = wp->position_fixed.v;
                fpos            = &wp->ext.fpos_70;
                func_8002FFC4(pos, fpos, wp->rotation.y, 0xD00, -(wp->ext.value_6 << 9), 0);
                func_8002FFC4(pos, fpos, wp->ext.value_6 << 9, D_80116290[wp->routine_3 * 4],
                              D_80116292[wp->routine_3 * 4], 0);
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 0x41;
                    fx->value_C         = 1;
                    fx->value_D         = 0;
                    fx->sprite.position = wp->ext.pos_68;
                }
                if (++wp->ext.value_6 >= 8)
                {
                    if (++wp->routine_3 >= 4)
                    {
                        wp->anim_AC = 8;
                        wp->routine_2++;
                        wp->ext.flags_0 &= ~0x802;
                    }
                    wp->ext.value_6 = 0;
                }
                ext->timer_4 = 2;
            }
            break;
        case 2:
            if (wp->value_A6 != 0)
            {
                Sound_call2(0x151, &wp->position);
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
            }
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 9;
                wp->routine_2++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_1 = 9;
                Sce_flag_on(0x604);
                func_80052528(wp);
                wp->ext.flags_0 = 0x200;
                func_8005D6E8(wp);
            }
            else if (wp->value_A7 < 0)
            {
                wp->anim_AC = 8;
                wp->routine_2--;
            }
            break;
    }
    if (ext->value_F6 >= 8)
    {
        wp->scale.v.pad = 0x7FFF;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    ext->value_F6 = (ext->value_F6 + 1) & 0xF;
}

void func_8010E584(STAGE_OBJ *wp)
{
    wp->anim_AC = 0xA;
}

void func_8010E590(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;
    sint16 step;

    ext = &wp->ext;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0xD;
            wp->routine_2++;
            break;
        case 1:
            step           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                func_8010EE60(wp, 3);
                func_8010EE60(wp, 8);
                if (ext->obj_80[0] != NULL)
                {
                    if (ext->obj_80[1] != NULL)
                    {
                        wp->routine_2++;
                    }
                    else
                    {
                        wp->routine_2 += 2;
                    }
                }
                else if (ext->obj_80[1] != NULL)
                {
                    wp->routine_2 += 3;
                }
                else
                {
                    wp->anim_AC = 0xF;
                    wp->routine_2 += 5;
                }
            }
            break;
        case 2:
            step           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            if (ext->obj_80[0]->u_C.b.byte_C != 0 && ext->obj_80[1]->u_C.b.byte_C != 0)
            {
                wp->anim_AC = 0xE;
                wp->routine_2 += 3;
            }
            break;
        case 3:
            step           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            if (ext->obj_80[0]->u_C.b.byte_C != 0)
            {
                wp->anim_AC = 0xE;
                wp->routine_2 += 2;
            }
            break;
        case 4:
            step           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            ext->angle_42  = (ext->angle_42 - step) & 0xFFF;
            if (ext->obj_80[1]->u_C.b.byte_C != 0)
            {
                wp->anim_AC = 0xE;
                wp->routine_2++;
            }
            break;
        case 5:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0xF;
                wp->routine_2++;
                if (ext->obj_80[0] != NULL)
                {
                    ext->obj_80[0]->u_C.b.byte_C -= 0x80;
                    ext->obj_80[0] = NULL;
                }
                if (ext->obj_80[1] != NULL)
                {
                    ext->obj_80[1]->u_C.b.byte_C -= 0x80;
                    ext->obj_80[1] = NULL;
                }
            }
            break;
        case 6:
            if (wp->value_A7 < 0)
            {
                ext->value_40 = 0x78;
                ext->flags_0 |= 1;
            }
            break;
    }
}

sint32 func_8010E8A0(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    STAGE_PL_VIEW *pl;

    ext = &wp->ext;
    pl  = &STAGE_PL;
    if ((STAGE_PL.value_76 != 0 && STAGE_PL.value_C0 == wp) ||
        func_80031DCC(&wp->position_fixed, wp->ext.value_44, 0x400, &pl->position_fixed,
                      STAGE_PL.rotation.y, 0x800))
    {
        ext->flags_0 &= ~0x80;
    }
    else
    {
        wp->ext.flags_0 |= 0x80;
        wp->ext.angle_42 = (wp->ext.angle_42 + 0x800) & 0xFFF;
    }
    return 1;
}

sint32 func_8010E95C(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;

    ext = &wp->ext;
    if (STAGE_PL.value_76 != 0 && STAGE_PL.value_C0 == wp)
    {
        if ((wp->ext.value_2 & 0xF) < 6)
        {
            return 4;
        }
        return 3;
    }
    if ((ext->value_2 & 0xF) < 9)
    {
        return 4;
    }
    return 3;
}

void func_8010E9C8(ST0A_EM *wp, sint32 side)
{
    ST0A_EM_EXT *ext;
    sint16 i;

    ext = &wp->ext;
    for (i = 0; i < 3; i++)
    {
        ext->uv_34  = func_8002D22C(wp->model_88, (i << 24) | 0x10E01);
        ext->vtx_38 = func_8002D2DC(wp->model_88, (i << 24) | 0x10E04);
        ext->vtx_3C = func_8002D2DC(wp->model_88, (i << 24) | 0x10E05);
        if (side == 0)
        {
            ext->vtx_38[1] -= 0x58;
            ext->vtx_3C[1] -= 0x58;
            ext->uv_34[5] += 4;
            ext->uv_34[7] += 4;
        }
        else
        {
            ext->vtx_38[1] += 0x58;
            ext->vtx_3C[1] += 0x58;
            ext->uv_34[5] -= 4;
            ext->uv_34[7] -= 4;
        }
    }
}

sint32 func_8010EB40(void)
{
    ST0A_VIEW *obj;

    obj = func_80031498();
    if (obj != NULL)
    {
        obj->flags_0          = 1;
        obj->kind_2           = 1;
        obj->value_4          = 1;
        obj->u_C.b[0]         = 1;
        obj->u_C.b[3]         = 1;
        obj->variant_3        = 0;
        obj->u_C.b[1]         = 0;
        obj->u_C.b[2]         = 0;
        obj->position_fixed.x = 0xEB000000;
        obj->position_fixed.y = 0xFFFF0000;
        obj->position_fixed.z = 0x1A000000;
        func_80030150(&obj->position_fixed, &obj->position);
        obj->value_B0 = 0;
        obj->value_6E = 0;
        func_8005D620(obj, 0, 0, 0x50, 0x208080);
        return 0;
    }
    return 1;
}

sint32 func_8010EBE8(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    sint32 i;
    sint32 damage;

    damage = wp->ext.hit_C.hit_8 & 0xFFFFFF;
    ext    = &wp->ext;
    if (damage != 0)
    {
        if (wp->ext.hit_C.hit_8 & 0x20000000)
        {
            return 1;
        }
        if (wp->ext.hit_C.hit_8 & 0x18000000)
        {
            wp->ext.flags_0 |= 0x100;
            wp->ext.flags_0 &= ~0x4400;
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                if (func_80042208())
                {
                    wp->ext.flags_0 &= ~0xC;
                    wp->life_6E               = 0;
                    damage                    = D_8009884C[wp->kind_2]->value_9;
                    wp->routine_1             = 8;
                    *(uint16 *)&wp->routine_2 = 0;
                }
                else
                {
                    wp->life_6E = 1;
                }
            }
            if (ext->flags_0 & 8)
            {
                ext->value_A += damage;
                if ((ext->hit_C.hit_8 & 0x20000000) ||
                    ext->value_A >= D_8009884C[wp->kind_2]->value_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    ext->value_A = 0;
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            for (i = 0; i < 15; i++)
            {
                wp->joint_180[i].pad = 0x7FFF;
            }
            ext->value_F8 = wp->life_6E;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_8010ED90(ST0A_EM *wp, sint32 index)
{
    STAGE_OBJ *obj;
    ST0A_EM_EXT *ext;

    ext             = &wp->ext;
    obj             = ext->obj_80[index >> 3];
    obj->position.x = 0;
    obj->position.y = 0x7D0;
    obj->position.z = 0;
    ApplyMatrix(&wp->mtx_240[index], &obj->position, &obj->position_fixed);
    obj->position.x         = wp->joint_180[index].x + obj->position_fixed.v.x;
    obj->position.y         = wp->joint_180[index].y + obj->position_fixed.v.y;
    obj->position.z         = wp->joint_180[index].z + obj->position_fixed.v.z;
    obj->position_fixed.v.x = obj->position.x << 16;
    obj->position_fixed.v.y = obj->position.y << 16;
    obj->position_fixed.v.z = obj->position.z << 16;
}

sint32 func_8010EE60(ST0A_EM *wp, sint32 index)
{
    STAGE_OBJ *obj;
    ST0A_EM_EXT *ext;

    ext = &wp->ext;
    obj = (STAGE_OBJ *)func_80031518();
    if (obj != NULL)
    {
        ext->obj_80[index >> 3] = obj;
        obj->flags_0            = 1;
        obj->kind_2             = 2;
        obj->value_4            = 0;
        obj->variant_3          = 0;
        obj->u_C.b.byte_D       = 0;
        obj->position           = wp->joint_180[index];
        obj->position_fixed.v.x = obj->position.x << 16;
        obj->position_fixed.v.y = obj->position.y << 16;
        obj->position_fixed.v.z = obj->position.z << 16;
        return 1;
    }
    ext->obj_80[index >> 3] = NULL;
    return 0;
}

sint32 func_8010EF3C(ST0A_EM *wp)
{
    ST0A_EM_EXT *ext;
    sint32 i;
    sint32 sum;
    uint32 kinds;
    uint32 hit;
    ST0A_SPARK_ARGS *args;

    kinds = 0;
    sum   = 0;
    ext   = &wp->ext;
    for (i = 0; i < 6; i++)
    {
        hit = ext->hit_88[i].hit_8;
        sum += hit & 0xFFFFFF;
        kinds |= hit & 0x38000000;
    }
    if (sum != 0)
    {
        if (kinds & 0x38000000)
        {
            ext->value_46 -= sum;
            if (ext->value_46 <= 0)
            {
                if (ext->flags_0 & 0x2000)
                {
                    ext->value_46 = 1;
                }
                else
                {
                    ext->value_46 = 0;
                    ext->flags_0 |= 0x8000;
                    ext->flags_0 &= ~0x1000;
                    wp->value_64 >>= 1;
                    args = D_801161F8;
                    for (i = 0; i < 2; i++)
                    {
                        ext->spark_E8[i] =
                            func_80113C4C((STAGE_XYZ *)&wp->joint_180[11], args[i].width_0,
                                          args[i].growth_1, args[i].count_2, args[i].rise_4, 0);
                    }
                    wp->routine_1             = 0xA;
                    *(uint16 *)&wp->routine_2 = 0;
                    MojiTaskExec2(4, 7);
                    ext->flags_F2 |= 0xE;
                    ext->flags_0 |= 0x4000;
                }
            }
            Sound_call2(0xA2, &wp->position);
            wp->joint_180[11].pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_8010F0D4(STAGE_OBJ *wp)
{
    func_8010CB1C(wp);
}
