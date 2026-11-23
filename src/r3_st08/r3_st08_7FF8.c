#include "common.h"
#include "st08.h"

// The first live 0x3C0-byte slot of kind 0x50.
STAGE_ACTOR *func_80107FF8(void)
{
    STAGE_ACTOR *wp;
    sint32 i;

    wp = D_8009F108;
    for (i = 0; i < 0x10; i++, wp++)
    {
        if (wp->flags_0 != 0 && wp->kind_2 == 0x50)
        {
            break;
        }
    }
    return wp;
}

void func_80108040(ST08_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->turn_64      = 0;
    wp->rotation.v.x = wp->rotation_prev.x = 0;
    wp->rotation.words[1]                  = 0;
    *(sint32 *)&wp->rotation_prev.z        = 0;
    wp->velocity.words[0]                  = 0;
    wp->velocity.words[1]                  = 0;
    wp->turn_64                            = 0;
    wp->value_70                           = 0;
    wp->value_74                           = 0;
    wp->scale.words[0]                     = 0x2000200;
    wp->scale.words[1]                     = 0x42100200;
    wp->rotation_prev                      = wp->rotation.v;
    wp->position_prev                      = wp->position;
    wp->index_35A                          = 0;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->anim_358                                     = D_80113B1C[0].anim;
    wp->hold_359                                     = D_80113B1C[wp->index_35A].hold;
    func_800322A8(wp, wp->anim_358, 0);
    wp->data_78                 = NULL;
    wp->data_10                 = D_80113B24;
    *(sint32 *)&wp->hit.flags_0 = 0;
    wp->routine_0++;
}

void func_80108180(ST08_ACTOR *wp)
{
    if (Player_work.target_184 == wp)
    {
        if (Sce_flag_test(0x36))
        {
            func_80063BC8(&wp->position, 0, 0, 0x1A);
        }
        else if (Sce_flag_test(0x549))
        {
            func_8001DDE4(0x57);
            ST08_SCENE_OBJ(0) = wp;
            ST08_SCENE_OBJ(1) = func_80107FF8();
            wp->routine_1     = 2;
        }
        else
        {
            ST08_PL->flags_bd |= 0x40;
            wp->routine_1++;
        }
        return;
    }
    if (wp->hold_359 == 0)
    {
        if (D_80113B1C[++wp->index_35A].anim == 0xFF)
        {
            wp->index_35A = 0;
        }
        wp->anim_358 = D_80113B1C[wp->index_35A].anim;
        wp->hold_359 = D_80113B1C[wp->index_35A].hold;
        func_800322A8(wp, wp->anim_358, 0);
    }
    else
    {
        wp->hold_359--;
        func_80032488(wp);
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801082F0(ST08_ACTOR *wp)
{
    STCOM_FIXED_VECTOR cam;
    ST08_PL_WORK *pl;
    STAGE_ACTOR *other;

    pl = ST08_PL;
    switch (wp->routine_2)
    {
        case 0:
            other = func_80107FF8();
            cam.x = other->position.x + 0x20;
            cam.y = other->position.y - 0x79;
            cam.z = other->position.z + 0x18;
            func_80039FAC(&cam, 0x107, other->rotation.y - 0x800, 0x12);
            pl->flags_0 &= ~2;
            wp->flags_0 &= ~2;
            wp->routine_2++;
            break;
        case 1:
            if (!func_8003A13C())
            {
                func_80063BC8(&wp->position, 1, 0, 0x14);
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                pl->flags_0 |= 2;
                wp->flags_0 |= 2;
                wp->routine_2++;
            }
            break;
        case 3:
            if (!func_8003A13C())
            {
                pl->flags_bd &= ~0x40;
                wp->index_35A = 0;
                wp->anim_358  = D_80113B1C[0].anim;
                wp->hold_359  = D_80113B1C[wp->index_35A].hold;
                func_800322A8(wp, wp->anim_358, 0);
                wp->routine_2 = 0;
                wp->routine_1--;
            }
            break;
    }
}

void func_801084C0(STAGE_ACTOR *wp)
{
    if (wp->velocity.v.x != 0)
    {
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
        wp->position.y       = Obj_ceiling_height_get(wp);
        wp->position_fixed.y = wp->position.y << 16;
    }
    if (wp->value_E == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->value_D, 0);
        wp->value_E = 0;
    }
}

void func_80108540(STAGE_OBJ *wp)
{
    D_80113B30[wp->routine_1](wp);
}

void func_8010857C(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_8010859C(STAGE_OBJ *wp)
{
    D_80113B3C[wp->routine_0](wp);
    if ((uint8)wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x3C, 0x200, 0);
    }
}
