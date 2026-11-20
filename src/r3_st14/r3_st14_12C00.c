#include "common.h"
#include "st14.h"

void func_80112C00(STAGE_OBJ *wp)
{
    D_801161F4[wp->routine_0](wp);
}

void func_80112C3C(STAGE_OBJ *wp)
{
    if (!Sce_flag_test(0x5E))
    {
        if (Sce_flag_test(0x531) || Sce_flag_test(0x532) || Sce_flag_test(0x533))
        {
            STAGE_GAME_U16(0x174) |= 3;
        }
        if (Sce_flag_test(0x5D))
        {
            STAGE_GAME_U16(0x174) |= 0x18;
        }
        if (Sce_flag_test(0x6E))
        {
            STAGE_GAME_U16(0x174) |= 4;
        }
        if (Sce_flag_test(0x41))
        {
            STAGE_GAME_U16(0x174) |= 0x40;
        }
    }
    else
    {
        STAGE_GAME.value_174 = 0x6F;
    }
    if (STAGE_GAME.value_174 == 0x6F)
    {
        wp->routine_0 = 2;
    }
    else
    {
        wp->u_C.b.byte_D = 0;
        wp->routine_0    = 1;
        wp->routine_1    = 0;
        wp->routine_2    = 0;
        wp->routine_3    = 0;
    }
}

void func_80112D70(STAGE_OBJ *wp)
{
    D_80116200[wp->routine_1](wp);
}

void func_80112DAC(STAGE_OBJ *wp)
{
    Close_EVE_WORK(wp);
}

void func_80112DCC(STAGE_OBJ *wp)
{
    sint8 i;

    i = 0; // set before the early return in retail
    if (STAGE_GAME.value_174 == 0x6F)
    {
        wp->routine_0 = 2;
        return;
    }
    wp->u_C.b.byte_C = -1;
    wp->position.x   = Player_work.position.x >> 9;
    wp->position.z   = Player_work.position.z >> 9;
    for (; i < 7; i++)
    {
        wp->u_C.b.byte_C = i;
        if (D_80116208[i](wp) && !((STAGE_GAME.value_174 >> wp->u_C.b.byte_C) & 1))
        {
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            return;
        }
    }
}

void func_80112ECC(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (!(Moji_flag & 0x8000000))
            {
                wp->position.x = Player_work.position.x >> 9;
                wp->position.z = Player_work.position.z >> 9;
                if (wp->u_C.b.byte_D == 1)
                {
                    wp->u_C.b.byte_D = 0;
                    wp->routine_2++;
                }
                else if (func_80113084(wp, &D_80116224[wp->u_C.b.byte_C]))
                {
                    wp->routine_2++;
                }
                else
                {
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                }
            }
            break;
        case 1:
            MojiTaskExec2(4, D_80116248[wp->u_C.b.byte_C]);
            if ((0x48 >> wp->u_C.b.byte_C) & 1)
            {
                STAGE_PL.flags_bd |= 0x40;
            }
            STAGE_GAME_U16(0x174) |= 1 << wp->u_C.b.byte_C;
            wp->routine_2++;
            break;
        case 2:
            if (!(Moji_flag & 0x800000))
            {
                if ((0x48 >> wp->u_C.b.byte_C) & 1)
                {
                    STAGE_PL.flags_bd &= ~0x40;
                }
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

sint32 func_80113084(STAGE_OBJ *wp, ST14_BOX *box)
{
    if ((uint16)((sint8)wp->position.x - box->x) < box->w &&
        (uint16)((sint8)wp->position.z - box->z) < box->h &&
        (box->room == Game_work.value_51 || box->room == -1))
    {
        return 1;
    }
    return 0;
}

sint32 func_80113110(STAGE_OBJ *wp)
{
    return func_80113084(wp, &D_80116224[wp->u_C.b.byte_C]) != 0;
}

sint32 func_80113148(STAGE_OBJ *wp)
{
    if (func_80113084(wp, &D_80116224[wp->u_C.b.byte_C]) && Sce_flag_test(0x41))
    {
        Sce_flag_on(0x5E);
        return 1;
    }
    return 0;
}

sint32 func_801131A4(STAGE_OBJ *wp)
{
    if (func_80113084(wp, &D_80116224[wp->u_C.b.byte_C]))
    {
        Sce_flag_on(0x5D);
        return 1;
    }
    return 0;
}

sint32 func_801131F0(STAGE_OBJ *wp)
{
    if (func_80113084(wp, &D_80116224[wp->u_C.b.byte_C]))
    {
        Sce_flag_on(0x6E);
        return 1;
    }
    return 0;
}

sint32 func_8011323C(STAGE_OBJ *wp)
{
    if (!func_80113084(wp, &D_80116224[wp->u_C.b.byte_C]) || Sce_flag_test(0x521))
    {
        return 0;
    }
    return 1;
}

sint32 func_80113290(STAGE_OBJ *wp)
{
    if ((Sce_flag_test(0x531) != 0) || (Sce_flag_test(0x532) != 0) || (Sce_flag_test(0x533) != 0))
    {
        wp->u_C.b.byte_D = 1;
        return 1;
    }
    return 0;
}

sint32 func_801132F4(void)
{
    if (Sce_flag_test(0x529) && ST14_SCENE_BYTE_0 == 0)
    {
        return 1;
    }
    return 0;
}

sint32 func_80113330(void)
{
    return 1;
}

void func_80113338(STAGE_EV *wp)
{
    STAGE_EV *ev;
    sint32 i;

    for (i = 0x1F; i >= 0; i--)
    {
        ev = func_800317AC(i);
        if (ev != NULL)
        {
            ev->flags_0 = 1;
            ev->kind_2  = 0;
            break;
        }
    }
    Close_EVE_WORK(wp);
}
