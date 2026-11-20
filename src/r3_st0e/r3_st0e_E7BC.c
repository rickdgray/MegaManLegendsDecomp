#include "common.h"
#include "st0e.h"

void func_8010E7BC(STAGE_OBJ *wp)
{
    D_80110C60[wp->routine_0](wp);
}

void func_8010E7F8(STAGE_OBJ *wp)
{
    if (STAGE_GAME_VALUE_52 != 3 || STAGE_GAME.value_174 == 0x3F)
    {
        wp->routine_0 = 2;
    }
    else
    {
        wp->routine_0 = 1;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->routine_3 = 0;
    }
}

void func_8010E844(STAGE_OBJ *wp)
{
    D_80110C6C[wp->routine_1](wp);
}

void func_8010E880(STAGE_OBJ *wp)
{
    Close_EVE_WORK(wp);
}

void func_8010E8A0(STAGE_OBJ *wp)
{
    sint8 i;

    i = 0;
    if (STAGE_GAME_VALUE_52 != 3 || STAGE_GAME.value_174 == 0x3F)
    {
        wp->routine_0 = 2;
        return;
    }
    wp->u_C.b.byte_C = -1;
    wp->position.x   = STAGE_PL.position.x >> 9;
    wp->position.z   = STAGE_PL.position.z >> 9;
    while (i < 6)
    {
        if (func_8010ECB0(wp, &D_80110C90[i]))
        {
            wp->u_C.b.byte_C = i;
            break;
        }
        i++;
    }
    if (wp->u_C.b.byte_C != -1 && !((STAGE_GAME.value_174 >> wp->u_C.b.byte_C) & 1) &&
        D_80110C78[wp->u_C.b.byte_C](wp) && !Sce_flag_test(D_80110CA8[wp->u_C.b.byte_C]))
    {
        if ((3 >> wp->u_C.b.byte_C) & 1)
        {
            wp->routine_1 = 1;
        }
        else
        {
            wp->routine_1 = 2;
        }
        wp->routine_2 = 0;
    }
}

void func_8010EA14(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (!(Moji_flag & 0x8000000))
            {
                wp->position.x = STAGE_PL.position.x >> 9;
                wp->position.z = STAGE_PL.position.z >> 9;
                if (func_8010ECB0(wp, &D_80110C90[wp->u_C.b.byte_C]))
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
            MojiTaskExec2(0, D_80110CC0[wp->u_C.b.byte_C]);
            STAGE_PL.flags_bd |= 0x40;
            STAGE_GAME_U16(0x174) |= 1 << wp->u_C.b.byte_C;
            wp->routine_2++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                STAGE_PL.flags_bd &= 0xBF;
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_8010EB78(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (!(Moji_flag & 0x800000))
            {
                wp->position.x = STAGE_PL.position.x >> 9;
                wp->position.z = STAGE_PL.position.z >> 9;
                if (func_8010ECB0(wp, &D_80110C90[wp->u_C.b.byte_C]))
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
            MojiTaskExec2(4, D_80110CC0[wp->u_C.b.byte_C]);
            STAGE_GAME_U16(0x174) |= 1 << wp->u_C.b.byte_C;
            wp->routine_2++;
            break;
        case 2:
            if (!(Moji_flag & 0x800000))
            {
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

sint32 func_8010ECB0(STAGE_OBJ *wp, ST0E_BOX *box)
{
    if ((uint16)((sint8)wp->position.x - box->x) < box->w &&
        (uint16)((sint8)wp->position.z - box->z) < box->h)
    {
        return 1;
    }
    return 0;
}

sint32 func_8010ED14(void)
{
    if (Sce_flag_test(0x604) && Sce_flag_test(0x605) && Sce_flag_test(0x606))
    {
        return 0;
    }
    return 1;
}

sint32 func_8010ED60(void)
{
    return 1;
}

void func_8010ED68(STAGE_EV *wp)
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
