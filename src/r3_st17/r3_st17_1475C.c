#include "common.h"
#include "st17.h"

void func_8011475C(STAGE_OBJ *wp)
{
    STAGE_EV *ep;
    sint32 base;
    sint32 i;

    base = (Game_work.value_50 != 2) ? 5 : 0;
    for (i = 0; i < 5; i++)
    {
        ep = func_800316BC();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->kind_2    = 6;
            ep->variant_3 = i;
            ep->step_D    = 0;
            ep->timer_C   = 0;
            ep->value_F   = 1;
            ep->key_1C    = func_8003AC24(D_8011C590[i + base]);
            if (wp->flags_6 & 0x20)
            {
                ep->flags_6 |= 0x20;
            }
        }
    }
    Close_EVE_WORK(wp);
}

void func_80114854(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    sint32 u0;

    u       = func_8002DC84((void *)wp->position_fixed.v.x, 0, 4);
    uv      = func_8002DD1C(u.c, 0);
    u0      = (++wp->u_C.b.byte_C & 0x18) * 8;
    uv.b[0] = u0 + 6;
    uv.b[2] = u0 + 1;
    uv.b[4] = u0 + 0x3D;
    uv.b[6] = u0 + 0x3F;
    func_8002DE04(u.c, 0, uv.w);
}

void func_801148E0(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    sint32 u0;

    u  = func_8002DC84((void *)wp->position_fixed.v.x, 0, 4);
    uv = func_8002DD1C(u.c, 0);
    if (++wp->u_C.b.byte_C == D_8011C5B8[wp->u_C.b.byte_D].hold)
    {
        wp->u_C.b.byte_D++;
        wp->u_C.b.byte_C = 0;
        if (wp->u_C.b.byte_D == 14)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
    u0      = D_8011C5B8[wp->u_C.b.byte_D].frame * 0x30;
    uv.b[0] = u0 + 1;
    uv.b[2] = u0 + 0x2E;
    uv.b[4] = u0 + 1;
    uv.b[6] = u0 + 0x2E;
    func_8002DE04(u.c, 0, uv.w);
}

void func_801149C0(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    sint32 u0;

    u  = func_8002DC84((void *)wp->position_fixed.v.x, 0, 5);
    uv = func_8002DD1C(u.c, 0);
    if (++wp->u_C.b.byte_C == D_8011C5D4[wp->u_C.b.byte_D].hold)
    {
        wp->u_C.b.byte_D++;
        wp->u_C.b.byte_C = 0;
        if (wp->u_C.b.byte_D == 5)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
    u0      = D_8011C5B8[wp->u_C.b.byte_D].frame * 0x30; // the first table's frames
    uv.b[0] = u0 + 0x2E;
    uv.b[2] = u0 + 0x2E;
    uv.b[4] = u0 + 1;
    uv.b[6] = u0 + 1;
    func_8002DE04(u.c, 0, uv.w);
}

void func_80114AA0(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    uint8 u0;

    u  = func_8002DC84((void *)wp->position_fixed.v.x, 0, 6);
    uv = func_8002DD1C(u.c, 0);
    if (++wp->u_C.b.byte_C == D_8011C5E0[wp->u_C.b.byte_D].hold)
    {
        wp->u_C.b.byte_D++;
        wp->u_C.b.byte_C = 0;
        if (wp->u_C.b.byte_D == 9)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
    u0      = D_8011C5B8[wp->u_C.b.byte_D].frame * 0x30; // the first table's frames
    uv.b[0] = u0;
    uv.b[2] = u0 + 0x2F;
    uv.b[4] = u0;
    uv.b[6] = u0 + 0x2F;
    func_8002DE04(u.c, 0, uv.w);
}

void func_80114B80(STAGE_EV *wp)
{
    STAGE_UNPACK u;
    STAGE_UV4 uv;
    sint32 x;
    sint32 y;

    if (++wp->timer_C == D_8011C5F4[wp->step_D].hold)
    {
        wp->step_D++;
        wp->timer_C = 0;
        if (wp->step_D == 0xC)
        {
            wp->step_D = 0;
        }
    }
    x       = (uint8)(D_8011C5F4[wp->step_D].frame % 6) * 0x28;
    y       = (uint8)(D_8011C5F4[wp->step_D].frame / 6) * 0x28;
    u       = func_8002DC84((void *)wp->key_1C, 0, 7);
    uv      = func_8002DD1C(u.c, 0);
    uv.b[0] = x + 0x23;
    uv.b[2] = x + 0x26;
    uv.b[4] = x + 4;
    uv.b[6] = x + 1;
    uv.b[1] = y + 0x54;
    uv.b[3] = y + 0x67;
    uv.b[5] = y + 0x54;
    uv.b[7] = y + 0x67;
    func_8002DE04(u.c, 0, uv.w);
    uv      = func_8002DD1C(u.c, 1);
    uv.b[0] = x + 0x20;
    uv.b[2] = x + 0x23;
    uv.b[4] = x + 7;
    uv.b[6] = x + 4;
    uv.b[1] = y + 0x41;
    uv.b[3] = y + 0x54;
    uv.b[5] = y + 0x41;
    uv.b[7] = y + 0x54;
    func_8002DE04(u.c, 1, uv.w);
}

void func_80114D30(void)
{
}

void func_80114D38(STAGE_OBJ *wp)
{
    if (wp->u_E.b.byte_F == 0)
    {
        func_8011475C(wp);
        return;
    }
    D_8011C60C[wp->variant_3](wp);
}

void func_80114D94(STAGE_OBJ *wp)
{
    D_8011C620[wp->routine_0](wp);
}

void func_80114DD0(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        if (STAGE_SCENE_BYTE(0) != 0)
        {
            return;
        }
        ST17_GAME.value_174 = 0;
        wp->flags_6 |= 0x20;
        switch (D_800989F8.routine_4)
        {
            case 1:
                wp->variant_3 = 0;
                break;
            case 2:
                wp->variant_3 = 1;
                break;
            case 3:
                wp->variant_3 = 2;
                break;
            default:
                wp->routine_0 = 3;
                return;
        }
        wp->position_fixed.v.x = 0;
        wp->routine_2          = 0;
        wp->routine_3          = 0;
        wp->routine_1++;
    }
    D_8011C630[wp->variant_3](wp);
}

void func_80114EC4(STAGE_OBJ *wp)
{
    D_8011C63C[wp->variant_3](wp);
}

void func_80114F00(STAGE_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            Pl00_shot_enable_off(&Player_work);
            STAGE_PL_BYTE(0x449) = 1;
            STAGE_PL_BYTE(0x175) = 0;
            func_8001D854(0x10);
            if (Moji_flag & 0x08000000)
            {
                func_80053AA4(0);
                func_8001D494(0, 1, 0);
            }
            MojiTaskExec2(0, 0x10);
            wp->routine_1++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                Sound_call(0x182, 0, 0);
                Sound_key_off_voice(0x10);
                Game_work.mode_0   = 0xA;
                STAGE_GAME_BYTE(1) = 0;
                wp->routine_0      = 3;
                wp->routine_1      = 0;
                wp->routine_2      = 0;
                wp->routine_3      = 0;
            }
            break;
    }
}

void func_80115014(STAGE_OBJ *wp)
{
    Close_EVE_WORK(wp);
}

void func_80115034(STAGE_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            func_80115C24(wp);
            Player_work.position.y       = -0x5C1;
            Player_work.position.z       = -0x100;
            Player_work.position_fixed.y = -0x5C10000;
            Player_work.position_fixed.z = -0x1000000;
            Player_work.position.x       = 0;
            Player_work.position_fixed.x = 0;
            Player_work.rotation.z       = 0;
            Player_work.rotation.x       = 0;
            Player_work.rotation.y       = 0x800;
            pl->flags_0 |= 3;
            Player_work.flags_bd |= 0x40;
            STAGE_PL_OBJ->position_prev       = STAGE_PL_OBJ->position;
            STAGE_PL_OBJ->position_fixed_prev = STAGE_PL_OBJ->position_fixed.v;
            STAGE_PL_OBJ->rotation_prev       = STAGE_PL_OBJ->rotation;
            Player_work.value_76              = 1;
            STAGE_PL_BYTE(0x74)               = 0;
            Player_work.value_C0              = D_80122B48;
            wp->routine_2++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                wp->routine_2++;
            }
            break;
        case 2:
            Player_work.routine_1++;
            wp->routine_2++;
            break;
        case 3:
            D_800C0F96[0]        = 0;
            Player_work.flags_bd = (Player_work.flags_bd & ~0x40) | 0x20;
            wp->routine_0        = 1;
            wp->routine_1        = 0;
            wp->routine_2        = 0;
            wp->routine_3        = 0;
            break;
    }
}

void func_80115274(STAGE_OBJ *wp)
{
    func_80115C24(wp);
    Player_work.flags_0 |= 3;
    Player_work.position.y            = -0x5C1;
    Player_work.position.z            = -0x100;
    Player_work.position_fixed.y      = -0x5C10000;
    Player_work.position.x            = 0;
    Player_work.position_fixed.x      = 0;
    Player_work.position_fixed.z      = -0x1000000;
    Player_work.rotation.z            = 0;
    Player_work.rotation.x            = 0;
    Player_work.rotation.y            = 0x800;
    STAGE_PL_OBJ->position_prev       = STAGE_PL_OBJ->position;
    STAGE_PL_OBJ->position_fixed_prev = STAGE_PL_OBJ->position_fixed.v;
    STAGE_PL_OBJ->rotation_prev       = STAGE_PL_OBJ->rotation;
    Player_work.value_76              = 1;
    STAGE_PL_BYTE(0x74)               = 0;
    Player_work.value_C0              = D_80122B48;
    wp->routine_0                     = 1;
    wp->routine_1                     = 0;
    wp->routine_2                     = 0;
    wp->routine_3                     = 0;
}

void func_801153D0(STAGE_OBJ *wp)
{
    func_80115C24(wp);
    Player_work.flags_0 |= 3;
    Player_work.position.y            = -0x5C1;
    Player_work.position.z            = -0x100;
    Player_work.position_fixed.y      = -0x5C10000;
    Player_work.position.x            = 0;
    Player_work.position_fixed.x      = 0;
    Player_work.position_fixed.z      = -0x1000000;
    Player_work.rotation.z            = 0;
    Player_work.rotation.x            = 0;
    Player_work.rotation.y            = 0x800;
    STAGE_PL_OBJ->position_prev       = STAGE_PL_OBJ->position;
    STAGE_PL_OBJ->position_fixed_prev = STAGE_PL_OBJ->position_fixed.v;
    STAGE_PL_OBJ->rotation_prev       = STAGE_PL_OBJ->rotation;
    Player_work.value_76              = 1;
    STAGE_PL_BYTE(0x74)               = 0;
    Player_work.value_C0              = D_80122B48;
    wp->routine_0                     = 1;
    wp->routine_1                     = 0;
    wp->routine_2                     = 0;
    wp->routine_3                     = 0;
}

void func_8011552C(STAGE_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            func_80017C30(1);
            Sound_call(0x181, 0, 0);
            func_8011606C(wp);
            wp->u_C.b.byte_D = 0;
            wp->u_C.b.byte_C = 0;
            wp->routine_1++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                wp->u_E.b.byte_E       = 0;
                wp->u_E.b.byte_F       = 5;
                wp->position_fixed.v.x = 0;
                wp->routine_2          = 0;
                wp->routine_3          = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            func_801161C8(wp);
            break;
        case 3:
            func_80116510(wp);
            if (wp->u_C.b.byte_C != wp->u_C.b.byte_D && func_801166C8(wp) != 0)
            {
                if (func_80116900() != 0)
                {
                    wp->routine_1++;
                }
                else
                {
                    wp->routine_0 = 2;
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                }
            }
            wp->u_C.b.byte_D = wp->u_C.b.byte_C;
            break;
        case 4:
            if (++wp->position_fixed.v.x == 0x78)
            {
                pl->flags_bd |= 0x40;
                wp->routine_1++;
            }
            break;
        case 5:
            func_8001D854(0x10);
            func_80017C30(9);
            Sound_call(0x182, 0, 0);
            Sound_call(0x184, 0, 0);
            wp->routine_1++;
            break;
        case 6:
            if (D_80098A72 == 0 && D_80098788 == 0 && func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (Moji_flag & 0x800000)
            {
                func_80053AA4(4);
                func_8001D494(0, 1, 0);
            }
            func_8005D87C();
            pl->value_76 = 0;
            pl->flags_0 &= ~1;
            Sce_flag_on(0x605);
            wp->routine_0 = 3;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

void func_80115780(STAGE_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            Sound_call(0x13, 0, 0);
            Sound_call(0x181, 0, 0);
            Sound_call(0x183, 0, 0);
            func_80017C30(1);
            wp->position_fixed.v.x = 0;
            wp->routine_1++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                pl->flags_bd &= ~0x40;
                MojiTaskExec2(4, 5);
                wp->routine_3 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            func_80116510(wp);
            if (D_80122B50->timer_C == 1)
            {
                if (func_80116900() == 0)
                {
                    wp->routine_0 = 2;
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                    break;
                }
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->position_fixed.v.x == 0)
            {
                MojiTaskExec2(0, 3);
                func_8001D854(0x10);
            }
            else if (wp->position_fixed.v.x == 0x78)
            {
                pl->flags_bd |= 0x40;
                wp->routine_1++;
            }
            wp->position_fixed.v.x++;
            break;
        case 4:
            func_80017C30(9);
            Sound_call(0x182, 0, 0);
            Sound_call(0x184, 0, 0);
            wp->routine_1++;
            break;
        case 5:
            if (D_80098A72 == 0 && D_80098788 == 0 && func_80042238(pl) != 0)
            {
                if (Moji_flag & 0x8000000)
                {
                    func_80053AA4(0);
                    Game_logo_kill(-1);
                }
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_1++;
            }
            break;
        case 6:
            if (Moji_flag & 0x800000)
            {
                func_80053AA4(4);
                func_8001D494(0, 1, 0);
            }
            func_8005D87C();
            func_8005D6E8(D_80122B50);
            pl->value_76 = 0;
            pl->flags_0 &= ~1;
            Sce_flag_on(0x606);
            wp->routine_0 = 3;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

void func_80115A24(STAGE_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            Sound_call(0x14, 0, 0);
            Sound_call(0x181, 0, 0);
            func_80017C30(1);
            wp->routine_1++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                pl->flags_bd &= ~0x40;
                MojiTaskExec2(4, 0xC);
                wp->routine_3 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            func_80116510(wp);
            if (D_80122B50->timer_C == 1)
            {
                if (func_80116900() != 0)
                {
                    pl->flags_bd |= 0x40;
                    wp->routine_1++;
                }
                else
                {
                    wp->routine_0 = 2;
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                }
            }
            break;
        case 3:
            func_80017C30(9);
            Sound_call(0x182, 0, 0);
            wp->routine_1++;
            break;
        case 4:
            if (D_80098A72 == 0 && D_80098788 == 0 && func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_1++;
            }
            break;
        case 5:
            if (Moji_flag & 0x800000)
            {
                func_80053AA4(4);
                func_8001D494(0, 1, 0);
            }
            func_8005D87C();
            func_8005D6E8(D_80122B50);
            pl->value_76 = 0;
            pl->flags_0 &= ~1;
            Sce_flag_on(0x607);
            wp->routine_0 = 3;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

// The identical variant_3 / position.y arms are merged by jump2 after allocation; the branch
// keeps retail's store order (position.x's fixed copy loads before the position.z store).
void func_80115C24(STAGE_OBJ *wp)
{
    ST17_SLOT *op_48;
    ST17_SLOT *op_4C;
    ST17_SLOT *op_50;
    sint32 one;
    uint8 v;

    ST17_GAME.value_5E = D_80098844[10]->life_8 << 5;
    op_48              = (ST17_SLOT *)func_80031418();
    if (op_48 != NULL)
    {
        one               = 1;
        op_48->flags_0    = one;
        op_48->kind_2     = 0xA;
        op_48->value_4    = one;
        v                 = wp->variant_3;
        op_48->position.x = 0;
        if (v != 0)
        {
            op_48->variant_3  = v;
            op_48->position.y = -0x400;
        }
        else
        {
            op_48->variant_3  = v;
            op_48->position.y = -0x400;
        }
        op_48->position.z = 0;
        op_48->rotation.x = op_48->rotation.y = op_48->rotation.z = 0;
        op_48->value_44 = op_48->value_46 = op_48->value_48 = 0;
        op_48->position_fixed.x                             = op_48->position.x << 16;
        op_48->position_fixed.y                             = op_48->position.y << 16;
        op_48->position_fixed.z                             = op_48->position.z << 16;
        op_48->position_prev                                = op_48->position;
        op_48->position_fixed_prev                          = op_48->position_fixed;
        op_48->rotation_prev                                = op_48->rotation;
        op_48->owner_328                                    = wp;
        if (op_48->variant_3 == 0)
        {
            ST17_GAME.value_5C  = ST17_GAME.value_5E;
            op_48->anim_AC      = 0;
            op_48->anim_prev_AD = 0xFF;
            op_48->value_C      = 0;
        }
        else
        {
            Game_work_5C[0] += D_80098844[10]->life_B << 5;
            if (Game_work_5C[0] > ST17_GAME.value_5E)
            {
                Game_work_5C[0] = ST17_GAME.value_5E;
            }
            op_48->anim_AC      = 1;
            op_48->anim_prev_AD = 0xFF;
            op_48->value_C      = 0x2E;
        }
        D_80122B48 = (STAGE_OBJ *)op_48;
    }
    func_8005D844(0, 0, D_80098844[10]->value_A);
    if (wp->variant_3 == 0)
    {
        op_4C = (ST17_SLOT *)func_80031418();
        if (op_4C != NULL)
        {
            op_4C->position.x = 0;
            op_4C->flags_0    = 1;
            op_4C->kind_2     = 0x66;
            op_4C->position.y = -0xC00;
            op_4C->position.z = 0x3070;
            op_4C->variant_3  = 0;
            op_4C->rotation.x = op_4C->rotation.y = op_4C->rotation.z = 0;
            op_4C->value_44 = op_4C->value_46 = op_4C->value_48 = 0;
            op_4C->position_fixed.x                             = op_4C->position.x << 16;
            op_4C->position_fixed.y                             = op_4C->position.y << 16;
            op_4C->position_fixed.z                             = op_4C->position.z << 16;
            op_4C->position_prev                                = op_4C->position;
            op_4C->position_fixed_prev                          = op_4C->position_fixed;
            op_4C->rotation_prev                                = op_4C->rotation;
            op_4C->value_C                                      = 5;
            D_80122B4C                                          = (STAGE_OBJ *)op_4C;
        }
    }
    else
    {
        op_50 = (ST17_SLOT *)func_80031498();
        if (op_50 != NULL)
        {
            op_50->flags_0 = 1;
            if (wp->variant_3 == 1)
            {
                op_50->kind_2     = 0x12;
                op_50->position.y = -0x1A00;
                op_50->variant_3  = 1;
                op_50->position.x = 0;
                op_50->position.z = 0x600;
                op_50->rotation.y = 0;
                op_50->value_B0   = 0;
                op_50->life_6E    = 0;
                func_8005D620(op_50, 0, 0, 0x60, 0x2C004000);
            }
            else
            {
                op_50->kind_2     = 0xF;
                op_50->position.y = -0x800;
                op_50->position.z = 0x800;
                op_50->variant_3  = 0;
                op_50->position.x = 0;
                op_50->rotation.y = 0x400;
                op_50->value_B0   = 0;
                op_50->life_6E    = 0;
                func_8005D620(op_50, 0, 0, 0x50, 0x2C004080);
            }
            op_50->value_4    = 0;
            op_50->rotation.x = op_50->rotation.z = 0;
            op_50->value_44 = op_50->value_46 = op_50->value_48 = 0;
            op_50->position_fixed.x                             = op_50->position.x << 16;
            op_50->position_fixed.y                             = op_50->position.y << 16;
            op_50->position_fixed.z                             = op_50->position.z << 16;
            op_50->position_prev                                = op_50->position;
            op_50->position_fixed_prev                          = op_50->position_fixed;
            op_50->rotation_prev                                = op_50->rotation;
            if (op_50->kind_2 == 0x12)
            {
                op_50->owner_3C0 = wp;
            }
            D_80122B50 = (STAGE_EV *)op_50;
        }
    }
}

void func_8011606C(STAGE_OBJ *wp)
{
    STAGE_OBJ *op;
    sint8 i;

    i = 0;
    do
    {
        op = func_80031418();
        if (op != NULL)
        {
            op->flags_0      = 1;
            op->kind_2       = 0x32;
            op->value_4      = 3;
            op->u_E.b.byte_E = 5;
            op->variant_3    = 0;
            op->u_C.b.byte_C = i;
            op->u_C.b.byte_D = i;
            op->u_E.b.byte_F = 0;
            switch (i)
            {
                case 3:
                    op->position.x = -0x400;
                    op->position.z = 0x2600;
                    break;
                case 1:
                    op->position.x = -0x200;
                    op->position.z = 0x2300;
                    break;
                case 0:
                    op->position.x = 0;
                    op->position.z = 0x2000;
                    break;
                case 2:
                    op->position.x = 0x200;
                    op->position.z = 0x2300;
                    break;
                case 4:
                    op->position.x = 0x400;
                    op->position.z = 0x2600;
                    break;
            }
            op->position.y         = -0x880;
            op->rotation.z         = 0;
            op->rotation.y         = 0;
            op->rotation.x         = 0;
            op->owner_308          = wp;
            op->position_fixed.v.x = op->position.x << 16;
            op->position_fixed.v.y = op->position.y << 16;
            op->position_fixed.v.z = op->position.z << 16;
            D_80122B54[i]          = op;
        }
        i++;
    } while (i < 5);
}

void func_801161C8(STAGE_OBJ *wp)
{
    ST17_PL_KEYS *pl;

    pl = (ST17_PL_KEYS *)&Player_work;
    if (wp->routine_2 < 3 && func_8001DE84() != 0)
    {
        if (Moji_flag & 0x08000000)
        {
            func_80053AA4(0);
            func_8001D494(0, 1, 0);
        }
        Sound_key_off_voice(0x11);
        D_80122B48->anim_AC      = 1;
        D_80122B48->anim_prev_AD = 0xFF;
        D_80122B48->u_C.b.byte_C = 0x2E;
        func_80017C30(9);
        wp->u_E.b.byte_E = 1;
        wp->routine_2    = 3;
    }
    switch (wp->routine_2)
    {
        case 0:
            D_800C0F96[0] = 0;
            if (++wp->position_fixed.v.x == 6)
            {
                MojiTaskExec2(0, 1);
            }
            else if (wp->position_fixed.v.x == 10)
            {
                Sound_call(0x19E, 0, 0);
            }
            else if (wp->position_fixed.v.x == 40)
            {
                wp->routine_2++;
            }
            break;
        case 1:
            D_800C0F96[0] = pl->value_140 | (pl->value_126 | pl->value_13E);
            if (++wp->position_fixed.v.x == 108)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            D_800C0F96[0] = 0;
            if (++wp->position_fixed.v.x == 160)
            {
                Sound_call(0x19F, 0, 0);
            }
            else if (wp->position_fixed.v.x == 180)
            {
                D_80122B48->anim_AC      = 1;
                D_80122B48->anim_prev_AD = 0xFF;
                D_80122B48->u_C.b.byte_C = 0;
            }
            else if (wp->position_fixed.v.x == 320)
            {
                wp->routine_2 = 6;
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                D_800C0F96[0]          = 0;
                wp->position_fixed.v.x = 0;
                wp->u_E.b.byte_E       = 2;
                wp->routine_2++;
            }
            break;
        case 4:
            if (++wp->position_fixed.v.x == 15)
            {
                func_80017C30(1);
                wp->position_fixed.v.x = 0;
                wp->routine_2++;
            }
            break;
        case 5:
            if (D_80098A72 == 0)
            {
                wp->routine_2++;
            }
            break;
        case 6:
            if (Moji_flag & 0x08000000)
            {
                func_80053AA4(0);
                func_8001D494(0, 1, 0);
            }
            MojiTaskExec2(0, 0);
            Sound_call(0x182, 0, 0);
            wp->routine_2++;
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_2++;
            }
            break;
        case 8:
            func_80042314(pl);
            Sound_call(0x12, 0, 0);
            Sound_call(0x19F, 0, 0);
            Sound_call(0x181, 0, 0);
            wp->position_fixed.v.x = 0;
            wp->routine_2          = 0;
            wp->routine_1++;
            break;
    }
}

void func_80116510(STAGE_OBJ *wp)
{
    sint16 life;
    sint16 max;

    life = STAGE_GAME_U16(0x5C);
    max  = STAGE_GAME_U16(0x5E);
    switch (wp->routine_3)
    {
        case 0:
            if (life > max / 4 * 3)
            {
                wp->routine_3 = 1;
            }
            else if (life > max / 2)
            {
                wp->routine_3 = 2;
            }
            else if (life > max / 4)
            {
                wp->routine_3 = 3;
            }
            else
            {
                wp->routine_3 = 5;
            }
            break;
        case 1:
            if (life <= max / 4 * 3)
            {
                MojiTaskExec2(4, 0xD);
                wp->routine_3 = 4;
            }
            break;
        case 2:
            if (life <= max / 2)
            {
                MojiTaskExec2(4, 0xE);
                wp->routine_3 = 4;
            }
            break;
        case 3:
            if (life <= max / 4)
            {
                MojiTaskExec2(4, 0xF);
                wp->routine_3 = 4;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x800000))
            {
                wp->routine_3 = 0;
            }
            break;
        case 5:
            break;
    }
    if (life == 0)
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
    }
}

// Counts the five parts whose byte_C bit is clear and numbers them; 1 when there are none.
sint32 func_801166C8(STAGE_OBJ *wp)
{
    sint8 i;
    sint8 count;
    sint8 n;

    for (i = 0, count = 0; i < 5; i++)
    {
        if (!((wp->u_C.b.byte_C >> i) & 1))
        {
            count++;
        }
    }
    switch (count)
    {
        case 0:
            Sound_call(0x183, 0, 0);
            D_80122B4C->u_C.b.byte_C = 0;
            return 1;
        case 1:
            for (i = 0; i < 5; i++)
            {
                if (!((wp->u_C.b.byte_C >> i) & 1) && D_80122B54[i]->u_E.b.byte_F == 0)
                {
                    D_80122B54[i]->u_C.b.byte_D = 0;
                    D_80122B54[i]->u_E.b.byte_E = 1;
                    D_80122B54[i]->u_E.b.byte_F = 1;
                }
            }
            wp->u_E.b.byte_F = 0;
            break;
        case 2:
            for (i = 0, n = 0; i < 5; i++)
            {
                if (!((wp->u_C.b.byte_C >> i) & 1) && D_80122B54[i]->u_E.b.byte_F == 0)
                {
                    D_80122B54[i]->u_C.b.byte_D = n;
                    n++;
                    D_80122B54[i]->u_E.b.byte_E = 2;
                    D_80122B54[i]->u_E.b.byte_F = 1;
                }
            }
            wp->u_E.b.byte_F = 2;
            break;
        default:
            for (i = 0, n = 0; i < 5; i++)
            {
                if (!((wp->u_C.b.byte_C >> i) & 1))
                {
                    D_80122B54[i]->u_C.b.byte_D = n;
                    n++;
                    D_80122B54[i]->u_E.b.byte_E = count;
                }
            }
            break;
    }
    D_80122B4C->u_C.b.byte_C = count;
    return 0;
}

sint32 func_80116900(void)
{
    if (STAGE_GAME_S16(0x5C) > 0)
    {
        STAGE_GAME_U16(0x174) = 0xFFFF;
        return 1;
    }
    return 0;
}

void func_80116930(STAGE_OBJ *wp)
{
    D_8011C648[wp->variant_3](wp);
}

// `lim` set first puts retail's li a1 in the top delay slot; `shift` taken after the += makes
// CSE copy that address (retail's move a0,v0), which the scan keeps.
void func_8011696C(STAGE_OBJ *wp)
{
    ST17_REC *rec;
    sint32 lim;
    sint16 *shift;

    lim = 0x200;
    if (wp->routine_0 == 0)
    {
        if (STAGE_GAME_S16(0x176) == 0)
        {
            STAGE_GAME_S16(0x176) = -0x200;
            rec                   = ST17_REC_TBL;
        down:
            if (rec->value_4 != 0)
            {
                rec->value_0 -= 0x200;
                rec++;
                goto down;
            }
        }
        wp->routine_0++;
        return;
    }
    STAGE_GAME_S16(0x176) += 0x40;
    shift = &STAGE_GAME_S16(0x176);
    rec   = ST17_REC_TBL;
next:
    if (rec->value_4 != 0)
    {
        if (*shift == lim)
        {
            rec->value_0 -= 0x3C0;
        }
        else
        {
            rec->value_0 += 0x40;
        }
        rec++;
        goto next;
    }
    if (STAGE_GAME_S16(0x176) == 0x200)
    {
        STAGE_GAME_S16(0x176) = -0x200;
    }
}

void func_80116A64(STAGE_EV *wp)
{
    ST17_REC *rec;
    uint16 *shift;

    shift = &STAGE_GAME_U16(0x176);
    rec   = ST17_REC_TBL;
next:
    if (rec->value_4 != 0)
    {
        rec->value_0 -= *shift;
        rec++;
        goto next;
    }
    STAGE_GAME_U16(0x176) = 0;
    Close_EVE_WORK(wp);
}

void func_80116AC8(STAGE_ROOM *wp)
{
    D_80121230[wp->routine_4](wp);
}

void func_80116B04(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x5E, 0x80);
            func_8001E6C0(0, 0, 0);
            wp->reserved09[1] = 0x80;
            // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
            *(uint32 *)&wp->timer_C = 0;
            D_800BC7F0              = D_80121318;
            wp->tbl_A4              = D_801218D0;
            func_8001EAE8(&D_8012123C[0]);
            func_8001EAE8(&D_8012123C[1]);
            func_80117BEC(0, 0);
            D_800BBA90[0].value_20 = 0;
            D_800BBA90[0].flags_0  = 3;
            func_80117BEC(1, 1);
            D_800BBA90[1].value_20 = 0;
            D_800BBAC8             = 3;
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.value_448   = 0x30;
                STAGE_PL.value_76    = 0;
                STAGE_PL.value_74    = 0;
                STAGE_PL.pos_438.x   = 0;
                STAGE_PL.pos_438.y   = 0;
                STAGE_PL.pos_438.z   = 0;
                STAGE_PL.fixed_428.x = 0;
                STAGE_PL.fixed_428.y = 0;
                STAGE_PL.fixed_428.z = 0;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.flags_bd |= 0x10;
                pl->flags_0 &= ~2;
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                func_8001D58C(0x20010002);
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                func_8001F1DC();
                D_800BC7F0             = D_80121368;
                wp->tbl_A4             = D_801218E0;
                D_800BBA90[0].value_20 = 0x8C;
                D_800BBA90[1].value_20 = -0x3C;
                wp->routine_5          = 0;
                wp->routine_6          = 0;
                wp->routine_7          = 0;
                wp->reserved09[1] &= 1;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8001EC0C();
    func_8001F070();
}

void func_80116D94(STAGE_ROOM *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        func_80017C30(0x14);
        wp->routine_5 = 0;
        wp->routine_4++;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84() != 0 || wp->reserved09[1] == 1)
        {
            func_80017C30(8);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    func_8001EC0C();
    func_8001F070();
}

void func_80116E28(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                D_800BBA90[0].flags_0 = 0;
                D_800BBAC8            = 0;
                Obj_work_flag_change(0x5E, 0x80);
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.pos_438.y   = -0x5C1;
                STAGE_PL.fixed_428.y = 0xFA3F0000;
                STAGE_PL.pos_438.x   = 0;
                STAGE_PL.pos_438.z   = 0;
                STAGE_PL.fixed_428.x = 0;
                STAGE_PL.fixed_428.z = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0x800;
                STAGE_PL.value_448   = 0;
                STAGE_PL_BYTE(0x168) = 0;
                STAGE_PL_BYTE(0x169) = 0;
                STAGE_PL.flags_bd |= 0x10;
                func_8001D494(0, 1, 0);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                wp->routine_5++;
            }
            break;
        case 1:
            func_80042314(pl);
            STAGE_PL.value_76 = 0;
            STAGE_PL.flags_bd |= 0x40;
            pl->flags_0 &= ~3;
            wp->routine_5++;
            break;
        case 2:
            D_800C356C  = -1;
            D_800C356E  = 0x17;
            D_800C356F  = 3;
            D_800C3562  = -0x5C1;
            D_800C356A  = 0x800;
            D_800C3560  = 0;
            D_800C3564  = 0;
            D_800C356D  = 0;
            D_800C3571  = 0xFF;
            D_800C3570  = 0xFF;
            wp->flags_0 = 0;
            break;
    }
    if (wp->reserved09[1] != 0)
    {
        func_8001EC0C();
        func_8001F070();
    }
}

void func_80117058(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0x186:
            wp->child_28->u_C.b.byte_C = 1;
            ST17_MODEL_TBL[0].value_2F = 2;
            break;
        case 0x1E0:
            wp->child_24->u_C.b.byte_C = 1;
            break;
        case 0x212:
            wp->child_28->u_C.b.byte_C = 2;
            break;
    }
}

void func_801170D4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            func_80117A40(0, 1);
            break;
        case 1:
            D_800BBAC8 = 0;
            func_80117BEC(5, 0);
            D_800BBA90[0].flags_0      = 3;
            ST17_MODEL_TBL[0].value_2F = 6;
            func_80031824(wp->child_24);
            func_8003187C(wp->child_28);
            STAGE_PL.value_448   = 0x80;
            STAGE_PL.pos_438.x   = -0x1A4;
            STAGE_PL.pos_438.y   = 0x14;
            STAGE_PL.pos_438.z   = -0x12C;
            STAGE_PL.fixed_428.x = 0xFE5C0000;
            STAGE_PL.fixed_428.y = 0x140000;
            STAGE_PL.fixed_428.z = 0xFED40000;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0x400;
            STAGE_PL.value_444   = 0;
            pl->flags_0 |= 2;
            func_80117AA4(0);
            break;
        case 15:
            func_80117AA4(1);
            break;
        case 30:
            func_80117AA4(1);
            break;
        case 50:
            func_80117AA4(2);
            break;
        case 70:
            func_80117AA4(0);
            break;
    }
    func_80117B08((ST17_PL_FACE *)pl);
}

void func_80117264(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_800BBA90[0].flags_0 = 0;
        Player_work.flags_0 &= ~2;
        func_8001EAE8(D_80121278);
        func_80117A40(0, 2);
    }
}

void func_801172C0(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v0;

    if (wp->frame_10 == 0)
    {
        temp_v0               = wp->child_28;
        temp_v0->routine_1    = 2;
        temp_v0->routine_2    = 0;
        temp_v0->u_C.b.byte_D = (uint8)temp_v0->u_C.b.byte_D + 1;
    }
}

void func_801172F4(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80117BEC(1, 1);
        STAGE_MODEL_TBL[1].flags_0 = 3;
        ST17_MODEL_TBL[1].value_2F = 6;
        func_8003187C(wp->child_24);
        func_8001EAE8(D_801212DC);
        func_80117A40(0, 3);
    }
}

void func_80117370(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->flags_0 &= 0xFD;
        func_8001EAE8(D_80121278);
        func_80117A40(0, 2);
    }
}

void func_801173C4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_24);
        child = wp->child_28;
        child->flags_0 |= 2;
        func_80117A40(0, 3);
    }
}

void func_80117420(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_MODEL_TBL[0].flags_0 = 0;
        func_80117BEC(2, 1);
        STAGE_MODEL_TBL[1].flags_0 = 3;
        func_80031824(wp->child_28);
        func_8001EAE8(D_8012123C);
    }
}

void func_8011748C(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            D_800BBAC8 = 0;
            func_80117BEC(3, 0);
            D_800BBA90[0].flags_0      = 3;
            ST17_MODEL_TBL[0].value_2F = 6;
            func_80031824(wp->child_24);
            func_8001EAE8(&D_801212F0[0]);
            func_8001EAE8(&D_801212F0[1]);
            func_80117A40(0, 1);
            break;
        case 30:
            wp->routine_6++;
            break;
        case 80:
            wp->routine_6 = 0;
            D_800BC7D4    = 0;
            break;
    }
    if (wp->routine_6 != 0)
    {
        D_800BC7D4 = D_80121978[ST17_FRAME & 3] << 16;
    }
}

void func_801175B4(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80117BEC(0xC, 0);
        func_80117BEC(6, 1);
        STAGE_MODEL_TBL[1].flags_0 = 3;
        ST17_MODEL_TBL[1].value_2F = 2;
        func_8003187C(wp->child_24);
        func_80031824(wp->child_28);
        func_8001EAE8(D_8012123C);
        func_80117A40(0, 3);
    }
}

void func_80117648(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_MODEL_TBL[0].flags_0 = 0;
        STAGE_MODEL_TBL[1].flags_0 = 0;
        func_80031824(wp->child_24);
        func_8001EAE8(D_80121278);
        func_80117A40(0, 2);
    }
}

void func_801176A8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80117BEC(0xD, 0);
        STAGE_MODEL_TBL[0].flags_0 = 3;
        func_80117BEC(7, 1);
        STAGE_MODEL_TBL[1].flags_0 = 3;
        ST17_MODEL_TBL[1].value_2F = 2;
        func_8003187C(wp->child_24);
        func_8001EAE8(D_80121250);
        func_80117A40(0, 3);
    }
}

void func_80117740(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80117BEC(8, 0);
        STAGE_MODEL_TBL[0].flags_0 = 3;
        ST17_MODEL_TBL[0].value_2F = 2;
        func_80117BEC(9, 1);
        STAGE_MODEL_TBL[1].flags_0 = 3;
        ST17_MODEL_TBL[1].value_2F = 6;
        func_8003187C(wp->child_28);
        func_8001EAE8(D_8012123C);
    }
    if (wp->frame_10 == 0x7C)
    {
        ST17_MODEL_TBL[0].value_2F = 6;
    }
}

void func_801177F0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_MODEL_TBL[0].flags_0 = 0;
        STAGE_MODEL_TBL[1].flags_0 = 0;
        wp->child_24->routine_1    = 5;
        wp->child_24->routine_2    = 0;
    }
}

void func_80117830(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80117BEC(0xB, 0);
        STAGE_MODEL_TBL[0].flags_0 = 3;
        ST17_MODEL_TBL[0].value_2F = 2;
        func_80117BEC(0xA, 1);
        STAGE_MODEL_TBL[1].flags_0 = 3;
        ST17_MODEL_TBL[1].value_2F = 6;
        func_8001EAE8(D_80121250);
        wp->child_24->routine_1 = 6;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x7A)
    {
        ST17_MODEL_TBL[0].value_2F = 6;
    }
}

void func_801178EC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_MODEL_TBL[0].flags_0 = 0;
        STAGE_MODEL_TBL[1].flags_0 = 0;
        wp->child_28->routine_1    = 4;
        wp->child_28->routine_2    = 0;
        func_80031824(wp->child_24);
    }
}

void func_80117948(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_28);
        func_8001EAE8(&D_80121278[0]);
        func_8001EAE8(&D_80121278[1]);
        func_8001EAE8(&D_80121278[2]);
        func_8001EAE8(&D_80121278[3]);
        func_8001EAE8(&D_80121278[4]);
        func_80117A40(0, 2);
    }
}

void func_801179C0(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v0;

    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_28);
        func_80031824(wp->child_2C);
        func_80031824(wp->child_30);
        func_80031824(wp->child_34);
        temp_v0               = wp->child_24;
        temp_v0->routine_1    = 6;
        temp_v0->u_C.b.byte_D = (uint8)temp_v0->u_C.b.byte_D + 1;
    }
}

// Sets the script camera.
void func_80117A40(sint32 unused, uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 0x17;
    D_800C356F = mode;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
}

void func_80117AA4(sint32 index)
{
    D_80122B68.shape_0 = D_80122B68.prev_1 = D_80122B68.index_2 = 0;
    D_80122B68.mouth_8                                          = D_801219B0[index];
    D_80122B68.shape_3 = D_80122B68.prev_4 = D_80122B68.index_5 = 0;
    D_80122B68.eyes_C                                           = D_801219BC[index];
}

void func_80117B08(ST17_PL_FACE *pl)
{
    ST17_FACE2 *face;

    face = &D_80122B68;
    if (face->mouth_8[face->index_2 + 1] != 0x7E)
    {
        if (face->mouth_8[face->index_2 + 1] == 0x7F)
        {
            face->index_2 = 0;
        }
        else
        {
            face->index_2++;
        }
    }
    face->prev_1 = face->shape_0 = face->mouth_8[face->index_2];
    if (face->eyes_C[face->index_5 + 1] != 0x7E)
    {
        if (face->eyes_C[face->index_5 + 1] == 0x7F)
        {
            face->index_5 = 0;
        }
        else
        {
            face->index_5++;
        }
    }
    face->prev_4 = face->shape_3 = face->eyes_C[face->index_5];
    pl->mouth_168                = face->shape_0;
    pl->eyes_169                 = face->shape_3;
}

void func_80117BEC(sint8 index, sint8 model)
{
    D_800BBA90[model].pos_C.x      = D_801219C8[index].x;
    D_800BBA90[model].fpos_4.x     = D_800BBA90[model].pos_C.x << 16;
    D_800BBA90[model].pos_prev_18  = D_800BBA90[model].pos_C;
    D_800BBA90[model].fpos_prev_10 = D_800BBA90[model].fpos_4;
    D_800BBA90[model].value_20     = D_801219C8[index].y;
    D_800BBA90[model].value_22     = D_801219C8[index].z;
}

void func_80117CB0(STAGE_ROOM *wp)
{
    D_80121A38[wp->routine_4](wp);
}

void func_80117CEC(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x5E, 0x80);
            func_8001E6C0(0, 0, 0);
            D_800BC7F0  = D_80121ABC;
            wp->tbl_A4  = D_80121B08;
            wp->timer_C = 0;
            func_8001EAE8(&D_80121A44[0]);
            func_8001EAE8(&D_80121A44[1]);
            wp->reserved09[1] = 0x80;
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->value_76  = 1;
                pl->value_74  = 0;
                pl->flags_bd |= 0x10;
                pl->flags_0 |= 3;
                pl->value_C0    = wp->child_28;
                pl->pos_438.y   = -0x5C1;
                pl->pos_438.z   = -0x100;
                pl->fixed_428.y = 0xFA3F0000;
                pl->fixed_428.z = 0xFF000000;
                pl->value_442   = 0x400;
                pl->pos_438.x   = 0;
                pl->fixed_428.x = 0;
                pl->value_440   = 0;
                pl->value_444   = 0;
                pl->value_448   = 0x30;
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                func_8001D58C(0x20010003);
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8001EC0C();
    func_8001F070();
}

void func_80117EFC(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8001EC0C();
            if (func_8001D878() != 0)
            {
                func_8001F1DC();
                D_800BC7F0 = D_80121B18;
                wp->tbl_A4 = D_80121F08;
                func_80017C30(1);
                wp->routine_5 = 1;
            }
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                wp->reserved09[1] &= 0x7F;
                wp->routine_5++;
            }
            // fall through
        case 2:
            wp->tbl_A4[1](wp);
            if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
            {
                wp->reserved09[1] |= 2;
                func_80017C30(8);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            func_8001EC0C();
            break;
        case 3:
            wp->tbl_A4[1](wp);
            func_8001EC0C();
            break;
        case 4:
            if (wp->routine_8 != 0xFF)
            {
                wp->tbl_A4[1](wp);
                if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
                {
                    func_80017C30(8);
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            func_8001EC0C();
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8001F070();
}

void func_801180B4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.pos_438.y   = -0x5C1;
                STAGE_PL.fixed_428.y = 0xFA3F0000;
                STAGE_PL.pos_438.x   = 0;
                STAGE_PL.pos_438.z   = 0;
                STAGE_PL.fixed_428.x = 0;
                STAGE_PL.fixed_428.z = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0x800;
                STAGE_PL.value_448   = 0;
                STAGE_PL_BYTE(0x168) = 0;
                STAGE_PL_BYTE(0x169) = 0;
                STAGE_PL.flags_bd |= 0x10;
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_8001D494(0, 1, 0);
                if (wp->reserved09[1] & 2)
                {
                    Cd_read_comb(0xB0);
                }
                wp->routine_5++;
            }
            break;
        case 1:
            func_80042314(pl);
            STAGE_PL.value_76 = 0;
            pl->flags_0 &= ~3;
            Obj_work_flag_change(0x5E, 0x80);
            if (wp->reserved09[1] & 2)
            {
                wp->routine_5 = 2;
            }
            else
            {
                wp->routine_5 = 3;
            }
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_5++;
            }
            break;
        case 3:
            D_800C356C = -1;
            D_800C356E = 0x17;
            D_800C356F = 3;
            D_800C3562 = -0x5C1;
            D_800C356A = 0x800;
            D_800C3560 = 0;
            D_800C3564 = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            STAGE_PL.flags_bd |= 0x40;
            wp->flags_0 = 0;
            break;
    }
}

void func_80118310(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->routine_1 = 1;
        wp->child_28->routine_0 = 2;
    }
}

void func_80118340(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj_28;
    STAGE_OBJ *obj_24;

    if (wp->frame_10 == 0)
    {
        obj_28                     = wp->child_28;
        obj_28->position.y         = -0x400;
        obj_28->position_fixed.v.y = -0x4000000;
        obj_28->position.x         = 0;
        obj_28->position.z         = 0;
        obj_28->position_fixed.v.x = 0;
        obj_28->position_fixed.v.z = 0;
        obj_28->rotation.x         = 0;
        obj_28->rotation.y         = 0;
        obj_28->rotation.z         = 0;
        obj_28->routine_0          = 3;
        STAGE_PL.routine_1         = 1;
        STAGE_PL.pos_438.y         = -0x5C1;
        STAGE_PL.pos_438.z         = -0x100;
        STAGE_PL.fixed_428.y       = 0xFA3F0000;
        STAGE_PL.fixed_428.z       = 0xFF000000;
        STAGE_PL.value_442         = 0x400;
        STAGE_PL.routine_0         = 3;
        STAGE_PL.pos_438.x         = 0;
        STAGE_PL.fixed_428.x       = 0;
        STAGE_PL.value_444         = 0;
        STAGE_PL.value_440         = 0;
        STAGE_PL.value_448         = 0x81;
        STAGE_PL.flags_bd |= 0x10;
        func_80118B44(0);
        func_80118B7C(0);
        obj_24                     = wp->child_24;
        obj_24->position.x         = -0x1000;
        obj_24->position.y         = -0x1400;
        obj_24->position.z         = 0x1000;
        obj_24->position_fixed.v.x = -0x10000000;
        obj_24->position_fixed.v.y = -0x14000000;
        obj_24->position_fixed.v.z = 0x10000000;
        obj_24->rotation.x         = 0;
        obj_24->rotation.y         = 0;
        obj_24->rotation.z         = 0;
        obj_24->routine_1          = 0;
        wp->reserved09[2]          = 0;
        wp->routine_6              = 0;
    }
    else if (wp->frame_10 == 30)
    {
        func_80118B44(2);
        func_80118B7C(2);
    }
    func_801189F0(wp);
    func_80118BB4((ST17_PL_FACE *)&Player_work);
}

void func_801184CC(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 25:
            Player_work.value_448 = 0x82;
            func_80118B7C(3);
            break;
        case 35:
            func_80118B44(2);
            func_80118B7C(1);
            break;
        case 45:
            func_80118B7C(3);
            break;
        case 65:
            func_80118B7C(1);
            break;
    }
    func_801189F0(wp);
    func_80118BB4((ST17_PL_FACE *)&Player_work);
}

void func_80118578(STAGE_ROOM *wp)
{
    STAGE_EV *ep;

    if (wp->frame_10 == 0)
    {
        STAGE_PL_OBJ->flags_0 &= ~2;
        Player_work.value_448 = 0;
        wp->child_28->flags_0 &= ~2;
        wp->child_24->flags_0 &= ~2;
        func_8001EAE8(&D_80121A6C[0]);
        func_8001EAE8(&D_80121A6C[1]);
        func_8011896C(D_800C3558, 1);
    }
    else if (wp->frame_10 == 1)
    {
        ep = func_800316BC();
        if (ep != NULL)
        {
            ep->flags_0 = 1;
            ep->kind_2  = 6;
            ep->value_F = 0;
        }
    }
}

void func_8011864C(void)
{
}

void func_80118654(void)
{
}

void func_8011865C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->routine_6 = 0;
    }
    switch (wp->routine_6)
    {
        case 0:
            Player_work.flags_0 |= 2;
            wp->child_28->flags_0 |= 2;
            wp->child_28->routine_0 = 4;
            wp->child_24->flags_0 |= 2;
            func_8003187C(wp->child_2C);
            func_80031824(wp->child_30);
            wp->child_2C = NULL;
            wp->child_30 = NULL;
            func_8011896C(D_800C3558, 3);
            wp->reserved09[1] |= 0x80;
            Sound_call(0x181, 0, 0);
            Sound_call(0x183, 0, 0);
            wp->routine_6++;
            break;
        case 1:
            if (wp->frame_10 == 20)
            {
                Cd_read_comb(0xB0);
                wp->routine_5 = 3;
                wp->routine_6++;
            }
            break;
        case 2:
            if (wp->frame_10 == 90)
            {
                wp->routine_6++;
            }
            break;
        case 3:
            if (Cd_read_sync2() == 0)
            {
                func_8001D58C(0x20010004);
                wp->routine_6++;
            }
            break;
        case 4:
            if (func_8001D878() != 0)
            {
                Sound_call(0x182, 0, 0);
                Sound_call(0x184, 0, 0);
                wp->routine_6 = 0;
                func_8001F158();
            }
            break;
    }
}

void func_80118818(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        wp->routine_5 = 4;
        wp->reserved09[1] &= 0x7F;
        // Signed: the and takes -3 (shared with the next one), not 0xFD.
        *(sint8 *)&Player_work.flags_0 &= ~2;
        child = wp->child_28;
        child->flags_0 &= ~2;
        func_8003187C(wp->child_24);
        func_8001EAE8(D_80121A94);
        func_8011896C(D_800C3558, 2);
    }
}

void func_801188B0(void)
{
}

void func_801188B8(void)
{
}

void func_801188C0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8001EAE8(D_80121AA8);
    }
}

void func_801188F8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_38);
    }
}

void func_8011892C(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0x154)
    {
        wp->routine_2 |= 0x80;
        func_80017C30(0xA);
    }
}

// Sets the script camera on the player.
void func_8011896C(void *camera, uint8 mode)
{
    D_800C356F = mode;
    D_800C356C = -1;
    D_800C356E = 0x17;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C3560 = STAGE_PL_S16(0x438);
    D_800C3562 = STAGE_PL_S16(0x43A);
    D_800C3564 = STAGE_PL_S16(0x43C);
    D_800C356A = STAGE_PL_S16(0x442);
}

// Fades in a translucent grey full-screen rectangle, one step a frame up to 30.
void func_801189F0(STAGE_ROOM *wp)
{
    ST17_TILE *tile;
    DR_MODE *mode;

    tile = (ST17_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->code |= 2;
    if (wp->reserved09[2] < 30)
    {
        tile->r0 = tile->g0 = tile->b0 = wp->reserved09[2];
        wp->reserved09[2]++;
    }
    else
    {
        tile->r0 = tile->g0 = tile->b0 = 30;
    }
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(mode, 0, 0, 0x4F, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&D_80098934->ot_74, tile);
    addPrim(&D_80098934->ot_74, mode);
}

void func_80118B44(sint32 index)
{
    D_80122B78.shape_8 = D_80122B78.prev_9 = D_80122B78.index_A = 0;
    D_80122B78.mouth_0                                          = D_80121FBC[index];
}

void func_80118B7C(sint32 index)
{
    D_80122B78.shape_B = D_80122B78.prev_C = D_80122B78.index_D = 0;
    D_80122B78.eyes_4                                           = D_80121FCC[index];
}

void func_80118BB4(ST17_PL_FACE *pl)
{
    ST17_FACE *face;

    face = &D_80122B78;
    if (face->mouth_0[face->index_A + 1] != 0x7E)
    {
        if (face->mouth_0[face->index_A + 1] == 0x7F)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->prev_9 = face->shape_8 = face->mouth_0[face->index_A];
    if (face->eyes_4[face->index_D + 1] != 0x7E)
    {
        if (face->eyes_4[face->index_D + 1] == 0x7F)
        {
            face->index_D = 0;
        }
        else
        {
            face->index_D++;
        }
    }
    face->prev_C = face->shape_B = face->eyes_4[face->index_D];
    pl->mouth_168                = face->shape_8;
    pl->eyes_169                 = face->shape_B;
}

void func_80118C94(STAGE_ROOM *wp)
{
    D_80121FDC[wp->routine_4](wp);
}

void func_80118CD0(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x5E, 0x80);
            func_8001E6C0(0, 0, 0);
            D_800BC7F0  = D_80122088;
            wp->tbl_A4  = D_801220D4;
            wp->timer_C = 0;
            func_8001EAE8(D_80121FE8);
            wp->reserved09[1] = 0x80;
            wp->routine_5++;
            break;
        case 1:
            func_8001EAE8(D_80121FFC);
            wp->routine_5++;
            // fall through
        case 2:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->value_76  = 1;
                pl->value_74  = 0;
                pl->flags_bd |= 0x10;
                pl->flags_0 |= 3;
                pl->value_C0    = wp->child_24;
                pl->pos_438.y   = -0x29C1;
                pl->pos_438.z   = -0x100;
                pl->fixed_428.y = 0xD63F0000;
                pl->fixed_428.z = 0xFF000000;
                pl->value_442   = 0x400;
                pl->pos_438.x   = 0;
                pl->fixed_428.x = 0;
                pl->value_440   = 0;
                pl->value_444   = 0;
                pl->value_448   = 0x30;
                func_80017C30(1);
                wp->routine_5++;
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                func_8001D58C(0x20010006);
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8001EC0C();
    func_8001F070();
}

void func_80118EC0(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8001EC0C();
            if (func_8001D878() != 0)
            {
                func_8001F1DC();
                D_800BC7F0    = D_801220E4;
                wp->tbl_A4    = D_80122628;
                wp->routine_5 = 1;
                wp->reserved09[1] &= 0x7F;
            }
            break;
        case 1:
            wp->tbl_A4[1](wp);
            if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
            {
                wp->reserved09[1] |= 2;
                func_80017C30(8);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            func_8001EC0C();
            break;
        case 2:
            wp->tbl_A4[1](wp);
            func_8001EC0C();
            break;
        case 3:
            if (wp->routine_8 != 0xFF)
            {
                wp->tbl_A4[1](wp);
                if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
                {
                    func_80017C30(8);
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            func_8001EC0C();
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8001F070();
}

void func_80119068(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.pos_438.y   = -0x5C1;
                STAGE_PL.fixed_428.y = 0xFA3F0000;
                STAGE_PL.pos_438.x   = 0;
                STAGE_PL.pos_438.z   = 0;
                STAGE_PL.fixed_428.x = 0;
                STAGE_PL.fixed_428.z = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0x800;
                STAGE_PL.value_448   = 0;
                STAGE_PL.flags_bd |= 0x10;
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_8001D494(0, 1, 0);
                if (wp->reserved09[1] & 2)
                {
                    Cd_read_comb(0xB1);
                }
                wp->routine_5++;
            }
            break;
        case 1:
            func_80042314(pl);
            STAGE_PL.value_76 = 0;
            pl->flags_0 &= ~3;
            Obj_work_flag_change(0x5E, 0x80);
            if (wp->reserved09[1] & 2)
            {
                wp->routine_5 = 2;
            }
            else
            {
                wp->routine_5 = 3;
            }
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_5++;
            }
            break;
        case 3:
            D_800C356C = -1;
            D_800C356E = 0x17;
            D_800C356F = 3;
            D_800C3562 = -0x5C1;
            D_800C356A = 0x800;
            D_800C3560 = 0;
            D_800C3564 = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            STAGE_PL.flags_bd |= 0x40;
            wp->flags_0 = 0;
            break;
    }
}

void func_801192B4(void)
{
}

void func_801192BC(void)
{
}

void func_801192C4(STAGE_ROOM *wp)
{
    STAGE_EV *ep;

    if (wp->frame_10 == 0)
    {
        STAGE_PL_OBJ->flags_0 &= ~2;
        Player_work.value_448 = 0;
        wp->child_24->flags_0 &= ~2;
        wp->child_28->flags_0 &= ~2;
        func_8001EAE8(&D_80122010[0]);
        func_8001EAE8(&D_80122010[1]);
        func_80119838(D_800C3558, 1);
    }
    else if (wp->frame_10 == 1)
    {
        ep = func_800316BC();
        if (ep != NULL)
        {
            ep->flags_0 = 1;
            ep->kind_2  = 6;
            ep->value_F = 0;
        }
    }
}

void func_80119398(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        Player_work.flags_0 |= 2;
        child->flags_0 |= 2;
        child->routine_0++;
        other = wp->child_28;
        other->flags_0 |= 2;
        func_8003187C(wp->child_2C);
        func_80031824(wp->child_30);
        wp->child_2C = NULL;
        wp->child_30 = NULL;
        func_80119838(D_800C3558, 3);
    }
}

void func_80119444(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    if (wp->frame_10 == 0)
    {
        temp_v1 = wp->child_24;
        temp_v1->routine_0++;
    }
}
