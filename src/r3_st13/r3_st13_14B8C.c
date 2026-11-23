#include "common.h"
#include "st13.h"

void func_80114B8C(STAGE_OBJ *wp)
{
    D_80118C48[wp->routine_0](wp);
}

void func_80114BC8(STAGE_OBJ *wp)
{
    STAGE_OBJ *obj;
    uint32 i;
    if (Sce_flag_test(0x53))
    {
        wp->routine_0 = 2;
        return;
    }
    D_80118D50[0] = NULL;
    D_80118D50[1] = NULL;
    D_80118D50[2] = NULL;
    for (i = 0; i < 3; i++)
    {
        obj = func_80031498();
        if (obj != NULL)
        {
            obj->flags_0            = 1;
            obj->kind_2             = 0x11;
            obj->variant_3          = i;
            obj->u_C.b.byte_C       = 0;
            obj->u_C.b.byte_D       = 0;
            obj->position.x         = D_80118C54[i].x;
            obj->position.y         = -1;
            obj->position.z         = D_80118C54[i].z;
            obj->rotation.x         = 0;
            obj->position_fixed.v.z = obj->position.z << 16;
            obj->position_fixed.v.y = obj->position.y << 16;
            obj->rotation.y         = 0;
            obj->rotation.z         = 0;
            obj->position_fixed.v.x = obj->position.x << 16;
            D_80118D50[i]           = obj;
        }
    }
    func_8001E460(0xC, 1, 3);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
}

void func_80114CF0(STAGE_OBJ *wp)
{
    D_80118C60[wp->routine_1](wp);
}

void func_80114D2C(STAGE_OBJ *wp)
{
    if ((uint16)STAGE_PL.position.y > 0xFFD7 && !(STAGE_PL_BYTE(6) & 0x40) && Sound_fade_flags == 0 && func_80042238(&Player_work))
    {
        Sound_call(0x32, 0, 0);
        Sce_flag_on(0x64B);
        func_8005D4D4();
        STAGE_PL.routine_0 = 3;
        STAGE_PL.routine_1 = 1;
        STAGE_PL.flags_bd |= 0x10;
        STAGE_PL.pos_438.x   = STAGE_PL.position.x;
        STAGE_PL.pos_438.y   = STAGE_PL.position.y;
        STAGE_PL.pos_438.z   = STAGE_PL.position.z;
        STAGE_PL.fixed_428.x = STAGE_PL.position.x << 16;
        STAGE_PL.fixed_428.y = STAGE_PL.position.y << 16;
        STAGE_PL.value_448   = 0;
        STAGE_PL.fixed_428.z = STAGE_PL.position.z << 16;
        STAGE_PL.value_440   = STAGE_PL.rotation.x;
        STAGE_PL.value_442   = STAGE_PL.rotation.y;
        STAGE_PL.value_444   = STAGE_PL.rotation.z;
        MojiTaskExec2(0, 0x14);
        wp->routine_1++;
    }
}

void func_80114E98(STAGE_OBJ *wp)
{
    if (!(Moji_flag & 0x8000000))
    {
        func_80042314(&Player_work);
        STAGE_PL.flags_bd &= ~0x40;
        D_80118D50[0]->u_C.b.byte_D = 1;
        D_80118D50[1]->u_C.b.byte_D = 1;
        D_80118D50[2]->u_C.b.byte_D = 1;
        func_8005D620(D_80118D50[0], 0, 0, 0x51, D_80118C74);
        func_8005D620(D_80118D50[1], 0, 0x14, 0x51, D_80118C78);
        func_8005D620(D_80118D50[2], 0, 0x28, 0x51, D_80118C7C);
        wp->routine_1++;
    }
}

void func_80114F98(STAGE_OBJ *wp)
{
    sint16 life;
    uint32 i;
    life = 0;
    for (i = 0; i < 3; i++)
    {
        life |= D_80118D50[i]->life_6E;
    }
    if (life == 0 && Sound_fade_flags == 0)
    {
        Sound_fade_start(0x10);
        Sce_flag_off(0x64B);
        Sce_flag_on(0x53);
        func_8005D4E8();
        MojiTaskExec2(0, 0x15);
        func_8001E460(0xC, 0, 3);
        func_8005D7C0();
        wp->routine_1++;
    }
}

void func_80115060(STAGE_OBJ *wp)
{
    if (Sound_fade_flags == 0)
    {
        Sound_call(0x31, 0, 0);
        wp->routine_1++;
    }
}

void func_801150B0(STAGE_OBJ *wp)
{
    if (!(Moji_flag & 0x08000000))
    {
        wp->routine_0 = 2;
    }
}

void func_801150D4(STAGE_OBJ *wp)
{
    Close_EVE_WORK(wp);
}

void func_801150F4(STAGE_EV *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            if (Sce_flag_test(D_80118C80[wp->variant_3]))
            {
                STAGE_PL_BYTE(0xBD) |= 0x40;
                wp->routine_0++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                Fade_start(0xA);
                Sound_fade_start(0x10);
                wp->routine_0++;
            }
            break;
        case 2:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                D_800C356C = 2;
                D_800C356E = 0x16;
                D_800C356F = (wp->variant_3 == 0) * 2;
                D_800C3560 = 0;
                D_800C3562 = 0;
                D_800C3564 = 0;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 0xFF;
                Close_EVE_WORK(wp);
            }
            break;
    }
}

void func_80115268(STAGE_EV *wp)
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
