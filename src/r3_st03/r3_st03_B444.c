#include "common.h"
#include "st03.h"

void func_8010B444(ST03_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // never used: retail's frame reserves it
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_8010B63C(wp);
            wp->routine_0++;
            wp->rotation.y += Muku(&wp->position, &((STAGE_OBJ *)STAGE_SCENE_OBJ(0))->position, wp->rotation.y, 0x800);
            break;
        case 1:
            if (Scene_work.u_8.byte[1] == 3)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB5);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            if (Scene_work.u_8.byte[1] == 5)
            {
                wp->rotation.y += Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
                wp->routine_0++;
            }
            break;
        case 4:
            func_800322A8(wp, 8, 0);
            MojiTaskExec2(0, 0xB7);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 6:
            if (Scene_work.u_8.byte[1] == 7)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB9);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 2:
        case 5:
        case 7:
            if (!(Moji_flag & 0x8000000))
            {
                Sce_event_next();
                wp->routine_0++;
            }
            break;
        case 8:
            if (Scene_work.reserved00[0] == 0)
            {
                wp->routine_0 = wp->routine_1 = wp->routine_2 = wp->routine_3 = 0;
                wp->timer_C                                                   = 0x5C;
                wp->value_D = wp->value_E = wp->value_F = 0;
                wp->value_4                             = 0;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010B63C(ST03_ACTOR *wp)
{
    sint16 temp_v0;

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    temp_v0              = Obj_ceiling_height_get(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

void func_8010B6D0(ST03_OBJ *wp)
{
    wp->variant_3              = 1;
    wp->scale.words[1]         = 0x200;
    wp->scale.words[0]         = 0x02000200;
    wp->value_64               = 0;
    *(uint32 *)&wp->rotation.x = 0;
    *(uint32 *)&wp->rotation.z = 0;
    wp->value_44.value         = 0;
    wp->value_48.value         = 0;
    wp->value_64               = 0;
    wp->value_70               = 0;
    wp->value_74               = 0;
    wp->rotation.y             = 0x800;
    wp->flags_0 |= 2;
    wp->rotation_prev      = wp->rotation;
    wp->position.x         = -0x9C0;
    wp->position.y         = -1;
    wp->position.z         = -0x5277;
    wp->scale.v.pad        = 0x4210;
    wp->position_fixed.v.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.v.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.v.y = wp->position_fixed_prev.y = wp->position.y << 16;
    Model_work_init(wp, &wp->variant_3);
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_8010B7DC(STAGE_OBJ *wp)
{
    if (Player_work.position.z < -0x5153)
    {
        func_8001DDE4(0x1F);
        wp->routine_0++;
    }
    func_80032488(wp);
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    func_80051B68(wp, 1, -1, 0);
}

void func_8010B858(ST03_ACTOR *wp)
{
    if (wp->velocity.v.x != 0)
    {
        if (!(ST03_FRAME & 7))
        {
            Sound_call2(0x10D, &wp->position);
        }
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
        wp->position.y       = Obj_ceiling_height_get(wp);
        wp->position_fixed.y = wp->position.y << 0x10;
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
    if (wp->value_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->value_E, 0);
        wp->value_D = 0;
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_8010B930(STAGE_OBJ *wp)
{
    D_801170B8[wp->routine_0](wp);
}
