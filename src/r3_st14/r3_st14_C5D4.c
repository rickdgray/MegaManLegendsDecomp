#include "common.h"
#include "st14.h"

void func_8010C5D4(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_6        = rand();
    D_80115C1C[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else if (wp->ctl.flags_4 & 0x10)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_prev_AD, wp->value_A4);
    }
    if (ctl->flags_4 & 8)
    {
        func_8010DDD0(wp);
    }
}

void func_8010C70C(ST14_ACTOR *wp)
{
    wp->u_E.b.byte_F = 1;
    wp->rotation.x   = 0;
    wp->rotation.z   = 0;
    wp->value_64     = 0;
    wp->flags_0 |= 2;
    func_8002F9C4(wp, &wp->variant_3);
    wp->scale.words[0]      = 0x2000200;
    wp->scale.words[1]      = 0x200;
    wp->ctl.flags_4         = 0x5A;
    *(sint32 *)&wp->ctl.u_8 = 0; // a cast store: the union field lets the table load move above it
    *(sint32 *)&wp->ctl.u_C = 0;
    func_80036478(wp->ctl.u_28.track, D_80098844[wp->kind_2]->value_F, -0x60);
    wp->ctl.hit_18    = 0;
    wp->ctl.value_1C  = 0;
    wp->ctl.u_28.w[1] = 0;
    wp->ctl.value_3E  = 0;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 * 16;
    wp->data_78                                      = D_80115C4C;
    wp->routine_0                                    = 1;
    wp->routine_1                                    = 1;
    *(uint16 *)&wp->routine_2                        = 0;
    func_800322A8(wp, 1, 0);
    wp->scale.v.pad    = 0x4210;
    wp->velocity.v.x   = 0x180;
    wp->velocity.v.z   = 0;
    wp->velocity.v.y   = 0;
    wp->accel.words[0] = 0;
    wp->accel.words[1] = 0;
}

void func_8010C830(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;
    sint32 side;

    ctl = &wp->ctl;
    if (func_8003648C(wp->ctl.u_28.track, wp))
    {
        wp->ctl.flags_4 |= 0x20;
    }
    else
    {
        wp->ctl.flags_4 &= ~0x20;
    }
    if (ctl->flags_4 & 2)
    {
        func_8010DEF8(wp);
    }
    D_80115C2C[wp->routine_1](wp);
    side = 0;
    if (wp->position_prev.x < -0x500 && wp->position.x >= -0x500)
    {
        side = 1;
    }
    if (wp->position_prev.x > -0x300 && wp->position.x <= -0x300)
    {
        side = 2;
    }
    if (wp->position_prev.x > 0x100 && wp->position.x <= 0x100)
    {
        side = 3;
    }
    if (wp->position_prev.x < -0x100 && wp->position.x >= -0x100)
    {
        side = 4;
    }
    if (side != 0)
    {
        func_8010D984(wp, side - 1);
    }
    if (ctl->flags_4 & 1)
    {
        func_8010DB28(wp);
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_4 &= ~1;
    }
    if (ctl->u_C.h.timer_E != 0)
    {
        ctl->u_C.h.timer_E--;
    }
    ctl->hit_18 = 0;
}

void func_8010C9CC(ST14_ACTOR *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            wp->velocity.v.x = 0;
            wp->velocity.v.y = 0;
            wp->velocity.v.z = 0;
            wp->anim_AC      = 4;
            wp->routine_3++;
            break;
        case 1:
            wp->velocity.v.y += 0x40;
            func_8002FEA4(wp, 0, wp->velocity.v.y, 0);
            if (wp->position.y >= -1)
            {
                func_8010D890(&wp->joint_180[0]);
                func_8010D890(&wp->joint_180[1]);
                func_8010D890(&wp->joint_180[7]);
                func_8010D890(&wp->joint_180[8]);
                func_80047148_2(wp, &wp->joint_180[0]);
                func_80031824(wp);
            }
            break;
    }
}

void func_8010CAA4(STAGE_OBJ *wp)
{
    wp->anim_AC = 0;
}

void func_8010CAAC(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;
    sint32 dir;

    ctl = &wp->ctl;
    dir = func_8010DA30(wp, 2, 8);
    switch (wp->routine_3)
    {
        case 0:
            wp->ctl.u_8.h[0] = 0x1E;
            wp->anim_AC      = 0;
            wp->routine_3    = 1;
            break;
        case 1:
            if (--wp->ctl.u_8.h[0] == 0)
            {
                wp->routine_3 = 2;
            }
            break;
        case 2:
            if (wp->ctl.flags_4 & 0x20)
            {
                wp->ctl.flags_4 |= 0x80;
                if (dir & 2)
                {
                    wp->ctl.flags_4 |= 0x100;
                }
            }
            ctl->flags_4 |= 1;
            break;
    }
}

void func_8010CB98(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;
    sint32 r;

    ctl = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->routine_3 = 1;
            ctl->u_8.h[0] = ctl->random_6 % 60 + 30;
            break;
        case 1:
            if (--ctl->u_8.h[0] == 0)
            {
                r                = ctl->random_6 & 0xF;
                wp->velocity.v.x = 0x180;
                if (r < 7)
                {
                    ctl->value_3C = 0;
                    wp->routine_3 = 0;
                }
                else if (r < 0xB)
                {
                    ctl->value_3C = 0x20;
                    wp->routine_3 = 0;
                }
                else if (r < 0xF)
                {
                    ctl->value_3C = -0x20;
                    wp->routine_3 = 0;
                }
                else
                {
                    ctl->value_3C    = 0;
                    wp->velocity.v.x = 0;
                    wp->routine_3    = 2;
                }
            }
            break;
        case 2:
            wp->routine_3 = 3;
            wp->anim_AC   = 2;
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->routine_3 = 4;
            }
            break;
        case 4:
            wp->routine_3    = 1;
            wp->velocity.v.x = 0x180;
            wp->anim_AC      = 1;
            wp->rotation.y -= 0x800;
            ctl->u_8.h[0] = 2;
            break;
    }
    wp->rotation.y = (wp->rotation.y + ctl->value_3C) & 0xFFF;
    func_8002FEA4(wp, wp->velocity.v.x, 0, 0);
    if (func_8010DCCC(wp) != 0)
    {
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        ctl->value_3C        = 0;
        wp->velocity.v.x     = 0;
        wp->routine_3        = 2;
    }
    wp->position.y         = -0x200;
    wp->position_fixed.v.y = -0x2000000;
    if (ctl->flags_4 & 0x20)
    {
        ctl->flags_4 |= 1;
    }
}

void func_8010CDB0(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;
    sint32 angle;
    uint32 rot;
    uint32 turn;
    uint32 rot5;

    ctl = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC = 1;
            if (wp->position.x < -0x200)
            {
                if (wp->position.x < -0x800)
                {
                    wp->routine_3 = 5;
                    angle         = 0xC00;
                }
                else
                {
                    angle         = 0x400;
                    wp->routine_3 = 1;
                }
            }
            else if (wp->position.x > 0x400)
            {
                wp->routine_3 = 5;
                angle         = 0x400;
            }
            else
            {
                angle         = 0xC00;
                wp->routine_3 = 1;
            }
            ctl->value_3A = angle;
            ctl->value_38 = wp->rotation.y;
            ctl->u_8.h[0] = ctl->u_8.h[1] = 30;
            if (ctl->value_3A - ctl->value_38 >= 0x800)
            {
                ctl->value_38 += 0x1000;
            }
            else if (ctl->value_38 - ctl->value_3A >= 0x800)
            {
                ctl->value_3A += 0x1000;
            }
            break;
        case 1:
            ctl->u_8.h[0]--;
            wp->rotation.y =
                (ctl->u_8.h[0] * ctl->value_38 + (ctl->u_8.h[1] - ctl->u_8.h[0]) * ctl->value_3A) /
                ctl->u_8.h[1];
            if (ctl->u_8.h[0] == 0)
            {
                rot              = (uint16)ctl->value_3A;
                wp->velocity.v.x = 0x200;
                wp->routine_3    = 2;
                wp->rotation.y   = rot & 0xFFF;
            }
            break;
        case 2:
            func_8002FEA4_int(wp, wp->velocity.v.x, 0, 0);
            if (wp->position.x < -0x200)
            {
                if (wp->position.x < -0xA00)
                {
                    wp->anim_AC   = 2;
                    wp->routine_3 = 3;
                }
            }
            else if (wp->position.x > 0x600)
            {
                wp->anim_AC   = 2;
                wp->routine_3 = 3;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->routine_3 = 4;
            }
            break;
        case 4:
            wp->anim_AC    = 1;
            turn           = (uint16)wp->rotation.y + 0x800;
            wp->routine_3  = 6;
            wp->rotation.y = turn & 0xFFF;
            break;
        case 5:
            ctl->u_8.h[0]--;
            wp->rotation.y =
                (ctl->u_8.h[0] * ctl->value_38 + (ctl->u_8.h[1] - ctl->u_8.h[0]) * ctl->value_3A) /
                ctl->u_8.h[1];
            if (ctl->u_8.h[0] == 0)
            {
                rot5             = (uint16)ctl->value_3A;
                wp->velocity.v.x = 0x200;
                wp->routine_3    = 6;
                wp->rotation.y   = rot5 & 0xFFF;
            }
            break;
        case 6:
            func_8002FEA4_int(wp, wp->velocity.v.x, 0, 0);
            if (wp->position.x < -0x200)
            {
                if (wp->position.x > -0x800)
                {
                    wp->anim_AC   = 8;
                    wp->routine_3 = 7;
                }
            }
            else if (wp->position.x < 0x400)
            {
                wp->anim_AC   = 8;
                wp->routine_3 = 7;
            }
            break;
        case 7:
            func_8002FEA4_int(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 9;
                wp->routine_3 = 8;
            }
            break;
        case 8:
            func_8002FEA4_int(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A7 == -1)
            {
                wp->anim_AC      = 0xA;
                wp->routine_3    = 9;
                wp->velocity.v.y = 0;
            }
            break;
        case 9:
            wp->velocity.v.y += 0x40;
            func_8002FEA4_int(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            if (wp->position.y >= -1)
            {
                wp->position.x         = -0x200;
                wp->position.y         = -1;
                wp->anim_AC            = 0xB;
                wp->routine_3          = 0xA;
                wp->velocity.v.y       = 0;
                wp->velocity.words[1]  = 0;
                wp->position_fixed.v.x = wp->position.x << 16;
                wp->position_fixed.v.y = wp->position.y << 16;
            }
            break;
        case 10:
            wp->velocity.v.x -= 0x20;
            func_8002FEA4_int(wp, wp->velocity.v.x, 0, 0);
            if (wp->velocity.v.x == 0)
            {
                wp->anim_AC = 0;
                ctl->flags_4 |= 1;
            }
            break;
    }
}

void func_8010D1E4(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC   = 0xC;
            wp->routine_3 = 1;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->velocity.v.x = 0x200;
                wp->velocity.v.y = -0x400;
                ctl->u_8.h[0]    = 0x10;
                wp->anim_AC      = 0xD;
                wp->routine_3    = 2;
                Sound_call2(0x194, &wp->position);
            }
            break;
        case 2:
            ctl->u_8.h[0]--;
            func_8002FEA4(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += 0x40;
            if (ctl->u_8.h[0] == 0)
            {
                wp->anim_AC   = 0xE;
                wp->routine_3 = 3;
            }
            break;
        case 3:
            wp->velocity.v.y = 0;
            func_8002FEA4(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A7 == -1)
            {
                wp->velocity.v.x = 0x180;
                wp->anim_AC      = 0xF;
                wp->velocity.v.y = 0;
                wp->routine_3    = 4;
            }
            break;
        case 4:
            func_8002FEA4(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A7 == -1)
            {
                func_80036470(ctl->u_28.track);
                wp->anim_AC = 1;
                ctl->flags_4 |= 1;
            }
            break;
    }
}

void func_8010D374(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_3)
    {
        case 0:
            wp->ctl.vec_48   = wp->position;
            wp->ctl.vec_40   = wp->ctl.vec_48;
            wp->ctl.value_38 = wp->rotation.y;
            if ((wp->ctl.flags_4 & 0x80) && wp->ctl.value_3E < 3)
            {
                wp->ctl.value_3A = func_80031198(&wp->ctl.vec_48, &pl->position);
            }
            else
            {
                ctl->value_3A = (ctl->random_6 & 1) ? 0x400 : 0xC00;
                ctl->vec_48.x = -0x200;
            }
            if (ctl->value_3A - ctl->value_38 >= 0x800)
            {
                ctl->value_38 += 0x1000;
            }
            else if (ctl->value_38 - ctl->value_3A >= 0x800)
            {
                ctl->value_3A += 0x1000;
            }
            ctl->u_8.h[0] = ctl->u_8.h[1] = 30;
            wp->anim_AC                   = 0x10;
            wp->routine_3                 = 1;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->anim_AC      = 0x11;
                wp->velocity.v.y = -0x400;
                wp->routine_3    = 2;
                Sound_call2(0x194, &wp->position);
            }
            break;
        case 2:
            if (wp->velocity.v.y >= 0)
            {
                wp->anim_AC = 0x12;
            }
            wp->ctl.u_8.h[0]--;
            wp->velocity.v.y += 0x40;
            func_8002FEA4(wp, 0, wp->velocity.v.y, 0);
            wp->position.x = (wp->ctl.u_8.h[0] * wp->ctl.vec_40.x +
                              (wp->ctl.u_8.h[1] - wp->ctl.u_8.h[0]) * wp->ctl.vec_48.x) /
                             wp->ctl.u_8.h[1];
            wp->rotation.y = (wp->ctl.u_8.h[0] * wp->ctl.value_38 +
                              (wp->ctl.u_8.h[1] - wp->ctl.u_8.h[0]) * wp->ctl.value_3A) /
                             wp->ctl.u_8.h[1];
            if (wp->ctl.u_8.h[0] == 0)
            {
                wp->position           = wp->ctl.vec_48;
                wp->anim_AC            = 0x13;
                wp->routine_3          = 3;
                wp->position_fixed.v.x = wp->position.x << 16;
                wp->position_fixed.v.y = wp->position.y << 16;
                wp->position_fixed.v.z = wp->position.z << 16;
                wp->rotation.y         = wp->ctl.value_3A & 0xFFF;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->ctl.flags_4 |= 1;
            }
            break;
    }
}

void func_8010D6C0(ST14_ACTOR *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC   = 5;
            wp->routine_3 = 1;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->ctl.u_8.h[0] = 0x3C;
                wp->anim_AC      = 6;
                wp->routine_3    = 2;
            }
            break;
        case 2:
            func_8010DA30(wp, 2, 0x10);
            if (!(wp->ctl.u_8.h[0] & 0xF))
            {
                func_8010D8FC(wp);
            }
            if (--wp->ctl.u_8.h[0] == 0)
            {
                wp->anim_AC   = 7;
                wp->routine_3 = 3;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->ctl.flags_4 |= 1;
            }
            break;
    }
}

void func_8010D7D8(ST14_VILLAGER *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC   = 3;
            wp->routine_3 = 1;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->flags_32C |= 1;
            }
            break;
    }
}

void func_8010D834(ST14_VILLAGER *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC   = 4;
            wp->routine_3 = 1;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->flags_32C |= 1;
            }
            break;
    }
}

void func_8010D890(STCOM_SVECTOR *pos)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0          = 5;
        fx->kind_2           = 0x80;
        fx->variant_3        = 0x42;
        fx->value_38.half[0] = pos->x;
        fx->value_38.half[1] = pos->y;
        fx->value_3C.half[0] = pos->z;
    }
}

void func_8010D8FC(ST14_ACTOR *wp)
{
    ST14_PIECE *piece;

    piece = (ST14_PIECE *)func_80031518();
    if (piece != NULL)
    {
        piece->flags_0    = 5;
        piece->kind_2     = 0x28;
        piece->variant_3  = 0;
        piece->position   = wp->joint_180[1];
        piece->rotation.x = wp->rotation.x;
        piece->rotation.y = wp->rotation.y;
    }
    Sound_call2(0x193, &wp->position);
}

// Sound_call2 is called without a prototype here (ST14_SOUND_CALL2).
void func_8010D984(ST14_ACTOR *wp, sint32 side)
{
    STAGE_FX *fx;
    uint8 n;

    n  = side;
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 5;
        fx->kind_2    = 0x17;
        fx->variant_3 = 0;
        fx->value_C   = n;
        if (side & 2)
        {
            fx->value_38.half[0] = 0;
        }
        else
        {
            fx->value_38.half[0] = -0x400;
        }
        fx->value_38.half[1] = wp->position.y - 0x80;
        fx->value_3C.half[0] = wp->position.z;
    }
    ST14_SOUND_CALL2((n & 1) == 0 ? 0x192 : 0x195, &wp->position);
}

sint32 func_8010DA30(ST14_ACTOR *wp, sint32 width, sint32 turn)
{
    STCOM_FIXED_VECTOR out;
    STCOM_SVECTOR size;
    sint32 side;

    ST14_PL.value_C4 = ST14_PL.value_3A8;
    wp->value_C4     = wp->joint_180[0];
    size.y           = 9;
    size.x           = width;
    size.z           = 4;
    side             = func_80030418(wp, &Player_work, &size, &out);
    if (!(side & 2))
    {
        if (side & 1)
        {
            wp->rotation.y = wp->rotation.y - turn;
        }
        else
        {
            wp->rotation.y = wp->rotation.y + turn;
        }
        wp->rotation.y &= 0xFFF;
    }
    return side;
}

void func_8010DB28(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.flags_4 & 0x200)
    {
        wp->ctl.flags_4 &= ~0x200;
        wp->routine_1 = 7;
        return;
    }
    switch (wp->routine_1)
    {
        case 0:
            ctl->flags_4 &= ~4;
            if ((ctl->flags_4 & 0x100) && ctl->value_3E < 3)
            {
                ctl->flags_4 |= 4;
                if (wp->value_80 > 0x40000)
                {
                    wp->routine_1 = 5;
                }
                else if ((ctl->random_6 & 0xF) < 0xD)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 5;
                }
            }
            else
            {
                wp->routine_1 = 4;
            }
            ctl->flags_4 &= ~0x100;
            break;
        case 1:
            wp->routine_1 = 2;
            break;
        case 2:
            ctl->flags_4 |= 0x80;
            wp->routine_1 = 4;
            break;
        case 3:
            wp->routine_1 = 1;
            break;
        case 4:
            if ((ctl->flags_4 & 0x80) && ctl->value_3E < 3)
            {
                ctl->flags_4 |= 4;
                if (wp->value_80 > 0x40000)
                {
                    wp->routine_1 = 5;
                }
                else if ((ctl->random_6 & 0xF) < 0xD)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 5;
                }
            }
            else
            {
                ctl->value_3E = 0;
                wp->routine_1 = 3;
            }
            ctl->flags_4 &= ~0x80;
            break;
        case 5:
        case 6:
            ctl->value_3E++;
            // fall through
        case 7:
            wp->routine_1 = 0;
            break;
    }
}

sint16 func_8010DCCC(ST14_ACTOR *wp)
{
    STCOM_SVECTOR pos;
    sint32 blocked;
    uint16 t;

    pos     = wp->position;
    blocked = 0;
    if ((uint16)(wp->rotation.y - 0x400) >= 0x800)
    {
        pos.z -= 0x100;
    }
    else
    {
        pos.z += 0x100;
    }
    if ((sint16)func_80048EA4(&pos, NULL, 0, wp->value_1) !=
        (sint16)func_80048EA4(&wp->position, NULL, 0, wp->value_1))
    {
        blocked = 1;
    }
    if (wp->position.x < -0x200)
    {
        t = wp->position.x + 0x1100;
    }
    else
    {
        t = wp->position.x - 0x100;
    }
    if (t > 0xC00)
    {
        blocked = 1;
    }
    return blocked;
}

sint32 func_8010DDD0(ST14_ACTOR *wp)
{
    if (wp->routine_1 == 6 && wp->routine_3 == 1)
    {
        wp->ctl.u_C.h.kind_C = D_80098844[wp->kind_2]->value_B;
        wp->ctl.pos_10       = wp->joint_180[8];
        func_800341BC(&wp->ctl.pos_10, 0x80, 0, 0x8000, wp->value_1, &wp->ctl.hit_18,
                      wp->ctl.u_C.h.kind_C | 0x5880000, 0x800000, 0);
    }
    else
    {
        wp->ctl.u_C.h.kind_C = D_80098844[wp->kind_2]->value_A;
        wp->ctl.pos_10       = wp->joint_180[0];
        func_800341BC(&wp->ctl.pos_10, 0x80, 0, 0x8000, wp->value_1, &wp->ctl.hit_18,
                      wp->ctl.u_C.h.kind_C | 0x4880000, 0x800000, 0);
    }
    return 1;
}

sint32 func_8010DEF8(ST14_ACTOR *wp)
{
    ST14_ACTOR_CTL *ctl;
    sint32 hit;
    sint32 damage;

    ctl              = &wp->ctl;
    hit              = wp->ctl.hit_18;
    damage           = hit & 0xFFFFFF;
    wp->life_prev_B2 = wp->life_6E;
    if (damage != 0 && (hit & 0x18000000))
    {
        wp->scale.v.pad = 0x7FFF;
        wp->life_6E -= damage;
        Sound_call2(0xA0, &wp->position);
    }
    damage = wp->life_prev_B2 - wp->life_6E;
    if (damage != 0)
    {
        if (wp->life_6E <= 0)
        {
            if ((uint16)(wp->position.x + 0x400) <= 0x400)
            {
                func_8010D890(&wp->position);
                wp->routine_0             = 2;
                wp->routine_1             = 0;
                *(uint16 *)&wp->routine_2 = 0;
                return 1;
            }
            wp->life_6E = 1;
        }
        if (ctl->flags_4 & 4)
        {
            ctl->u_C.h.timer_E += damage;
            if (ctl->u_C.h.timer_E >= D_80098844[wp->kind_2]->value_9 * 4)
            {
                ctl->u_C.h.timer_E = 0;
                ctl->flags_4 |= 0x201;
            }
        }
    }
    return 1;
}

void func_8010E03C(ST14_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    D_80115C58[wp->routine_1](wp);
    if (wp->value_D == 0)
    {
        func_80032488(wp);
    }
    func_8010E5DC((STAGE_OBJ *)wp, face);
}

void func_8010E0B0(ST14_TALKER *wp)
{
    STAGE_FACE16 *face;
    uint32 i;

    face = &wp->face_500;
    wp->flags_0 |= 2;
    wp->rotation.x = 0;
    if (wp->variant_3 == 0)
    {
        wp->rotation.y = 0xC00;
    }
    else
    {
        wp->rotation.y = 0x800;
    }
    wp->scale.words[0] = 0x02000200;
    wp->rotation.z     = 0;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 24; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    wp->pal[21].color |= 0x8000;
    func_8002F9C4(wp, NULL);
    func_800322A8(wp, 0, 0);
    func_8010E594(wp, face, 0);
    wp->part_100[2].value_3  = 0;
    wp->part_100[5].value_3  = 0;
    wp->part_100[16].value_3 = -1;
    wp->part_100[17].value_3 = -1;
    wp->part_100[18].value_3 = -1;
    wp->part_100[19].value_3 = -1;
    wp->routine_2            = 0;
    wp->value_D++;
}

void func_8010E1AC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (wp->variant_3 == 0)
    {
        wp->position.x += 3;
    }
    else
    {
        wp->position.z += 3;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
}

void func_8010E28C(ST14_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x10, 0);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x4B)
    {
        func_8010E594(wp, face, 1);
    }
}

void func_8010E304(ST14_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x11, 0);
        wp->part_100[2].value_3  = -1;
        wp->part_100[5].value_3  = -1;
        wp->part_100[16].value_3 = 0;
        wp->part_100[17].value_3 = 0;
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0xBF:
            func_8010E594(wp, face, 2);
            break;
        case 0xC9:
            func_8010E594(wp, face, 3);
            break;
        case 0xCD:
            func_8010E594(wp, face, 4);
            wp->part_100[18].value_3 = 0;
            wp->part_100[19].value_3 = 0;
            break;
    }
}

void func_8010E3EC(ST14_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x12, 0);
        func_8010E594(wp, face, 5);
        wp->routine_2++;
    }
}

void func_8010E454(ST14_TALKER *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE16 *face;

    scene = &Scene_work;
    face  = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        if (wp->variant_3 == 0)
        {
            wp->rotation.y = 0x100;
        }
        else
        {
            wp->rotation.y = 0x400;
        }
        func_800322A8(wp, 0x14, 0);
        wp->part_100[5].value_3  = 0;
        wp->part_100[2].value_3  = 0;
        wp->part_100[18].value_3 = -1;
        wp->part_100[17].value_3 = -1;
        wp->part_100[16].value_3 = -1;
        wp->part_100[19].value_3 = -1;
        func_8010E594(wp, face, 8);
        wp->routine_2++;
    }
    switch (scene->value_10)
    {
        case 0x1E:
        case 0xA0:
            func_8010E594(wp, face, 6);
            break;
        case 0x46:
        case 0x7C:
            func_8010E594(wp, face, 7);
            break;
        case 0x5A:
        case 0x8C:
            func_8010E594(wp, face, 8);
            break;
    }
}

void func_8010E594(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_80115D54[index];
    face->eyes_10               = D_80115D78[index];
}

void func_8010E5DC(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        func_8002D320(wp->model_88, 0x110010, func_8002D404(face->shape_0, 0x2A, 0x33, 6));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        func_8002D320(wp->model_88, 0x130012, func_8002D404(face->shape_6, 0x2A, 0x33, 6));
    }
    face->prev_8 = face->shape_6;
}

void func_8010E728(STAGE_OBJ *wp)
{
    D_80115D9C[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_80033A28(wp);
        func_8003346C(wp);
    }
}

void func_8010E800(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->flags_0 |= 2;
        func_8002F9C4(wp, &wp->variant_3);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->rotation.y     = 0x800;
        func_800322A8(wp, 0, 0);
        wp->u_C.b.byte_D++;
        wp->u_E.b.byte_E++;
        wp->routine_2++;
    }
}

void func_8010E8A0(STAGE_OBJ *wp)
{
    if (wp->u_E.b.byte_E == 0)
    {
        wp->position.y -= 6;
    }
}

void func_8010E8C8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (wp->value_A4 == 0x56)
    {
        wp->u_C.b.byte_D++;
    }
}

void func_8010E934(STAGE_OBJ *wp)
{
    if (wp->u_E.b.byte_E == 0)
    {
        wp->position.y += 3;
    }
}

void func_8010E95C(STAGE_OBJ *wp)
{
    if (wp->value_A4 < 0x5E)
    {
        wp->position.y += 5;
    }
    else if (wp->value_A4 < 0x6F)
    {
        wp->position.y -= 1;
    }
    if (wp->value_A4 < 0x67)
    {
        wp->position.z += 0xB;
    }
    else if (wp->value_A4 < 0x6F)
    {
        wp->position.z -= 0x10;
    }
}

void func_8010E9DC(STAGE_OBJ *wp)
{
    D_80115DB0[wp->routine_0](wp);
}

void func_8010EA18(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    uint32 i;

    wp->scale.x    = 0x200;
    wp->scale.y    = 0x200;
    wp->scale.z    = 0x200;
    wp->scale.pad  = 0x4210;
    wp->rotation.x = 0;
    wp->rotation.y = 0x800;
    wp->rotation.z = 0;
    wp->velocity.x = wp->velocity.y = wp->velocity.z = 0;
    wp->accel.x = wp->accel.y = wp->accel.z = 0;
    wp->flags_0 |= 2;
    wp->position_fixed.y = func_80048E6C(wp);
    wp->position.y       = wp->position_fixed.y >> 16;
    func_8002F9C4(wp, NULL);
    ext = &wp->ext;
    func_8005D4D4();
    wp->data_78 = D_80115DBC;
    wp->life_6E = wp->life_max_B0 = D_8009884C[wp->kind_2]->life_8 * 16;
    wp->value_B2                  = 0;
    wp->value_74                  = 0;
    wp->ext.flags_0               = 0;
    wp->ext.value_90              = 0;
    wp->ext.value_92              = 0;
    for (i = 0; i < 6; i++)
    {
        ext->hit_3C[i].flags   = 0;
        ext->hit_3C[i].value_4 = 0;
        ext->value_6C[i]       = 0;
    }
    ext->timer_88   = 0x72;
    ext->target_4.x = -0x100;
    ext->target_4.z = -0x1700;
    ext->count_8A   = 0;
    ext->target_4.y = -1;
    func_800322A8(wp, 0, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_8010EB70(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    uint32 i;

    ext                     = &wp->ext;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.pad           = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->value_75            = wp->value_74;
    func_8010ED0C(wp);
    wp->ext.value_8C = 0;
    for (i = 0; i < 6; i++)
    {
        if (wp->value_80 >= D_80115DE4[i])
        {
            ext->value_8C++;
        }
    }
    ext->value_84 = func_800302E4(&wp->position, &ext->target_4);
    D_80115DC8[wp->routine_1](wp);
    if (wp->routine_0 != 2)
    {
        if (wp->anim_AC != wp->anim_prev_AD)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
        func_8010EFF8(wp);
        func_8010EE98(wp);
        if (wp->flags_0 & 2)
        {
            func_8002C8CC(wp, 0x138, 0x200, 0);
        }
    }
}

void func_8010ED0C(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    sint32 i;
    sint32 damage;

    ext              = &wp->ext;
    wp->ext.value_8E = 0;
    if (!(STAGE_FRAME & 3) && wp->value_B2 != 0)
    {
        wp->value_B2--;
    }
    damage = 0;
    for (i = 1; i < 6; i++)
    {
        damage |= ext->hit_3C[i].flags & 0xFFFFFF;
    }
    if (damage != 0)
    {
        Sound_call2(0xA3, &wp->position);
        return;
    }
    damage = ext->hit_3C[0].flags & 0xFFFFFF;
    if (damage == 0)
    {
        return;
    }
    if (ext->value_90 != 0)
    {
        Sound_call2(0xA3, &wp->position);
        return;
    }
    wp->life_6E -= damage;
    wp->value_B2 += damage;
    Sound_call2(0xA0, &wp->position);
    wp->scale.pad = 0x7FFF;
    if (wp->life_6E <= 0)
    {
        wp->life_6E   = 0;
        ext->value_8E = -1;
        return;
    }
    if (ext->value_92 == 0 && wp->life_6E <= wp->life_max_B0 / 4 * 3)
    {
        MojiTaskExec2(0, 0xF);
        ext->value_92 = 1;
    }
    if (wp->value_B2 >= D_8009884C[wp->kind_2]->value_9 * 16)
    {
        ext->value_8E = 1;
    }
}

void func_8010EE98(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    uint32 i;

    ext = &wp->ext;
    if (wp->ext.value_6C[5] == 0)
    {
        D_80115E0E = 0x48;
    }
    else
    {
        D_80115E0E = 0xC0;
    }
    for (i = 0; i < 6; i++)
    {
        ext->hit_3C[i].flags = 0;
        ext->pos_C[i]        = wp->joint_180[D_80115DFC[i]];
        if (i == 0)
        {
            func_800341BC(&ext->pos_C[0], D_80115E04[0], 0, 0x8000, wp->value_1, &ext->hit_3C[0],
                          ext->value_6C[0] | 0x4080000, 0, 0);
        }
        else
        {
            func_800341BC(&ext->pos_C[i], D_80115E04[i], 0, 0x8000, wp->value_1, &ext->hit_3C[i],
                          ext->value_6C[i] | 0x4080000, 0, 0x80);
        }
    }
}

void func_8010EFF8(ST14_VILLAGER *wp)
{
    sint32 *flags;
    sint32 ground;
    wp->ext.flags_0 = 0;
    flags           = &wp->ext.flags_0;
    if (func_8004B414(wp) & 0xF00)
    {
        wp->ext.flags_0 |= 1;
    }
    if (wp->value_74 == 0)
    {
        ground = func_80048E6C(wp);
        if (ground != wp->position_prev.y)
        {
            if (wp->value_75 == 0)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->ext.flags_0 |= 4;
            }
        }
        else
        {
            wp->position.y            = ground;
            wp->position_fixed_prev.y = ground << 16; // retail stores the saved copy here
        }
        *flags |= 2;
    }
}

void func_8010F0F0(STAGE_OBJ *wp)
{
    func_8010F888(wp);
}

void func_8010F110(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    STCOM_PL_WORK *pl;
    sint32 shake;

    ext = &wp->ext;
    pl  = &Player_work;
    if (func_8010F934(wp) != 0)
    {
        return;
    }
    wp->rotation.y =
        (wp->rotation.y + func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x10)) &
        0xFFF;
    if (wp->ext.value_84 >= 0x600)
    {
        func_8010F900(wp);
        return;
    }
    if (wp->ext.count_8A == 0)
    {
        if (wp->value_80 <= 90000)
        {
            func_8010F8E4(wp);
            return;
        }
    }
    else
    {
        wp->ext.count_8A--;
    }
    if (ext->timer_88 == 0)
    {
        if (wp->life_6E != 0)
        {
            func_8010F8B8(wp);
            return;
        }
        ext->timer_88 = 0x72;
    }
    else
    {
        ext->timer_88--;
    }
    shake = wp->value_A4 == 0xC;
    if (wp->value_A4 == 0x2A)
    {
        shake = 1;
    }
    if (shake)
    {
        Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->position);
        Sound_call2(0x198, &wp->position);
    }
    func_8002FEA4(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
}

void func_8010F268(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    STCOM_PL_WORK *pl;
    sint32 i;
    sint32 hit;

    ext = &wp->ext;
    pl  = &Player_work;
    if (wp->value_A7 != 0)
    {
        func_8010F888(wp);
        return;
    }
    if (wp->value_A4 == 0x12)
    {
        wp->velocity.x = 0x400;
    }
    if (wp->value_A4 == 0x15)
    {
        Sound_call2(0x19C, &wp->position);
        wp->velocity.x      = (wp->ext.value_8C + 1) * 0x140;
        wp->ext.value_6C[0] = D_8009884C[wp->kind_2]->value_A | 0x1000000;
        wp->ext.value_6C[1] = D_8009884C[wp->kind_2]->value_A | 0x1000000;
    }
    if (wp->value_A4 == 0x20)
    {
        Sound_call2(0x19D, &wp->position);
        Swing_Camera2(0x1E, 0x64, 0x1388, &wp->position);
    }
    hit = 0;
    for (i = 0; i < 6; i++)
    {
        hit |= ext->hit_3C[i].flags & 0x2000000;
    }
    if (wp->value_A4 == 0x28 || hit != 0)
    {
        wp->velocity.x   = 0;
        ext->value_6C[0] = 0;
        ext->value_6C[1] = 0;
    }
    if (wp->velocity.x != 0)
    {
        wp->rotation.y =
            (wp->rotation.y + func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x30)) &
            0xFFF;
        func_8002FEA4(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    }
}

void func_8010F424(ST14_VILLAGER *wp)
{
    if (func_8010F934(wp) == 0)
    {
        wp->rotation.y = (wp->rotation.y + 8) & 0xFFF;
        if (wp->value_A4 == 0xD)
        {
            Sound_call2(0x199, &wp->position);
            wp->ext.value_6C[5] = D_8009884C[wp->kind_2]->value_B | 0x1000000;
        }
        if (wp->value_A7 != 0)
        {
            wp->ext.value_6C[5] = 0;
            func_8010F888(wp);
        }
    }
}

void func_8010F4C4(ST14_VILLAGER *wp)
{
    if (wp->value_A7 != 0)
    {
        func_8010F888(wp);
    }
}

void func_8010F4F4(ST14_VILLAGER *wp)
{
    STCOM_EFFECT *effect;

    if (wp->value_A7 != 0)
    {
        effect = func_80031618();
        if (effect != NULL)
        {
            effect->flags_0         = 5;
            effect->kind_2          = 0x80;
            effect->variant_3       = 0;
            effect->sprite.position = wp->position;
            effect->value_D         = 2;
        }
#ifdef __wasm32__
        func_80047148(wp, &wp->position);
#else
        func_80047148(wp, &wp->position, effect);
#endif
        func_8005D4E8();
        func_8005D6E8(wp);
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->flags_0 &= ~2;
    }
}

void func_8010F5AC(STAGE_OBJ *wp)
{
    D_80115E10[wp->routine_2](wp);
}

void func_8010F5E8(ST14_VILLAGER *wp)
{
    func_8010F9AC(wp);
    if (wp->value_A7 != 0)
    {
        wp->anim_AC    = 7;
        wp->velocity.x = 0x300;
        wp->velocity.y = -0x480;
        wp->accel.y    = 0x48;
        wp->value_74   = 1;
        Sound_call2(0x19A, &wp->position);
        wp->routine_2++;
    }
}

void func_8010F660(ST14_VILLAGER *wp)
{
    func_8010F9AC(wp);
    func_8002FEA4(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    wp->velocity.y += wp->accel.y;
    if (wp->value_A7 != 0)
    {
        wp->anim_AC = 8;
        wp->routine_2++;
    }
}

void func_8010F6C8(ST14_VILLAGER *wp)
{
    STCOM_EFFECT *effect;

    func_8010F9AC(wp);
    if (wp->value_74 == 0)
    {
        wp->anim_AC      = 9;
        wp->ext.fx_94    = NULL;
        wp->ext.timer_88 = 0;
        wp->ext.count_8A = 3;
        Sound_call2(0x19B, &wp->position);
        effect = func_80031618();
        if (effect != NULL)
        {
            effect->flags_0         = 5;
            effect->kind_2          = 0x80;
            effect->variant_3       = 6;
            effect->sprite.position = wp->position;
            effect->value_C         = 0;
            effect->value_D         = 0;
            effect->timer_E         = 0;
            effect->value_F         = 1;
            wp->ext.fx_94           = effect;
        }
        wp->routine_2++;
    }
    else
    {
        func_8002FEA4(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        wp->velocity.y += wp->accel.y;
    }
}

void func_8010F7BC(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;

    ext = &wp->ext;
    if (wp->ext.timer_88 == 0)
    {
        if (wp->ext.count_8A != 0)
        {
            wp->ext.count_8A--;
            Swing_Camera2(0x1E, 0x64, D_80115E20[wp->ext.count_8A], &wp->position);
        }
        wp->ext.timer_88 = D_80115E28[wp->ext.count_8A];
    }
    else
    {
        wp->ext.timer_88--;
    }
    if ((sint8)ext->fx_94->flags_0 == 0 && wp->value_A7 != 0)
    {
        func_8010F888(wp);
    }
}

void func_8010F888(ST14_VILLAGER *wp)
{
    wp->anim_AC      = 1;
    wp->velocity.x   = 0x68;
    wp->velocity.y   = 0;
    wp->accel.y      = 0;
    wp->ext.timer_88 = 0x72;
    wp->ext.value_90 = 0;
    wp->routine_1    = 1;
    wp->routine_2    = 0;
}

void func_8010F8B8(ST14_VILLAGER *wp)
{
    wp->anim_AC    = 2;
    wp->velocity.x = wp->velocity.y = wp->velocity.z = 0;
    wp->accel.x = wp->accel.y = wp->accel.z = 0;
    wp->routine_1                           = 2;
    wp->routine_2                           = 0;
}

void func_8010F8E4(ST14_VILLAGER *wp)
{
    wp->anim_AC      = 3;
    wp->ext.count_8A = 0x39;
    wp->routine_1    = 3;
    wp->routine_2    = 0;
}

void func_8010F900(ST14_VILLAGER *wp)
{
    wp->anim_AC      = 6;
    wp->ext.value_90 = 1;
    wp->velocity.x = wp->velocity.y = wp->velocity.z = 0;
    wp->accel.x = wp->accel.y = wp->accel.z = 0;
    wp->routine_1                           = 6;
    wp->routine_2                           = 0;
}

sint32 func_8010F934(ST14_VILLAGER *wp)
{
    ST14_VILLAGER_EXT *ext;
    uint32 i;

    ext = &wp->ext;
    if (ext->value_8E == 0)
    {
        return 0;
    }
    wp->value_B2 = 0;
    for (i = 0; i < 6; i++)
    {
        ext->value_6C[i] = 0;
    }
    ext->value_90 = 1;
    if (ext->value_8E > 0)
    {
        wp->anim_AC   = 5;
        wp->routine_1 = 4;
    }
    else
    {
        wp->anim_AC   = 4;
        wp->routine_1 = 5;
    }
    wp->routine_2 = 0;
    return 1;
}

void func_8010F9AC(STAGE_OBJ *wp)
{
    wp->rotation.y = ((uint16)wp->rotation.y +
                      func_80031BEC(&wp->position, (STCOM_SVECTOR *)&wp->u_4E0.face.mouth_4,
                                    (sint32)wp->rotation.y, 0x80)) &
                     0xFFF;
}

void func_8010F9F8(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        if (D_80098788 == 0)
        {
            func_8001D854(0x10);
            wp->routine_1++;
        }
    }
    else if (D_80098788 == 0)
    {
        Sce_flag_on(0x50);
        Sound_call(0x27, 0, 0);
        func_8003187C(wp);
    }
}
