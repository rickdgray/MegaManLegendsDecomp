#include "common.h"
#include "st0e.h"

void func_80102064(ST0E_VIEW *wp)
{
    wp->position_prev           = wp->position;
    wp->position_fixed_prev.x   = wp->position_fixed.x;
    wp->position_fixed_prev.y   = wp->position_fixed.y;
    wp->position_fixed_prev.z   = wp->position_fixed.z;
    wp->position_fixed_prev.pad = wp->position_fixed.pad;
    wp->rotation_prev           = wp->rotation;
    wp->u_15C.h[1]              = 0x4200;
    D_801102E0[wp->routine_0](wp);
}

void func_80102104(ST0E_ACTOR *wp)
{
    sint32 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    life               = D_80098844[wp->kind_2]->life_8;
    wp->routine_0      = 1;
    wp->value_6E       = life;
    wp->scale.v.pad    = 0x4210;
    wp->value_74       = 1;
    wp->data_78        = D_801102C8;
    wp->value_B0       = life;
    wp->value_B2       = life;
    wp->data_10        = D_801102C8;
    wp->anim_AC        = 0;
    func_800322A8(wp, 0, 0);
    wp->velocity.v.y = 0;
    wp->velocity.v.x = 0;
    wp->velocity.v.z = 0;
    wp->value_4E     = 0x30;
    func_801021D4(wp);
}

void func_801021D4(ST0E_ACTOR *wp)
{
    STAGE_PL_VIEW *pl;
    STCOM_EFFECT *fx;
    ST0E_10C *obj;
    sint32 ground;

    pl = &STAGE_PL;
    if (wp->position.x > 0)
    {
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0         = 5;
            fx->kind_2          = 0x80;
            fx->variant_3       = 0x40;
            fx->sprite.position = wp->value_188;
        }
        func_8010D9F8(0, 1, 2, &wp->value_188);
        func_8010D9F8(0, 2, 2, &wp->value_188);
        func_8010D9F8(0, 3, 4, &wp->value_188);
        obj = (ST0E_10C *)Open_SHL_WORK();
        if (obj != NULL)
        {
            obj->flags_0   = 1;
            obj->kind_2    = 0x2A;
            obj->variant_3 = 1;
            obj->position  = wp->position;
            obj->byte_C    = 3;
        }
        func_80052528(wp);
        wp->routine_0 = 2;
        return;
    }
    if (Sce_flag_test(0x60C))
    {
        if (wp->routine_1 == 0)
        {
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->value_4E;
            Obj_map_push_out(wp);
            ground = Obj_ceiling_height_get(wp);
            if (ground - wp->position_prev.y < 0x10)
            {
                wp->position.y       = ground;
                wp->position_fixed.y = ground << 16;
                wp->value_74         = 0;
                wp->routine_1        = 1;
                Sound_call2(0x187, &wp->position);
            }
        }
        else
        {
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            Obj_map_push_out(wp);
        }
    }
    func_80032488(wp);
    wp->data_78 = D_801102D4;
    Front_hit_event(wp);
    wp->data_78 = D_801102C8;
    func_80051B68(wp, 1, 0, 0);
    if (wp->routine_1 != 0)
    {
        if (Obj_ceiling_height_get(wp) != wp->position_prev.y)
        {
            wp->velocity.v.y += 0xC;
        }
        else if (wp->velocity.v.y != 0)
        {
            Sound_call2(0x187, &wp->position);
            wp->velocity.v.y = 0;
        }
    }
    switch (wp->routine_2)
    {
        case 0:
            if (pl->target_184 == wp)
            {
                pl->target_184 = NULL;
                wp->routine_2  = 2;
            }
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_2++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0x1A);
                wp->routine_2 = 3;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                pl->target_184 = NULL;
                wp->routine_2  = 0;
            }
            break;
    }
}

void func_80102518(STAGE_OBJ *wp)
{
    if (STAGE_PL.target_184 == wp)
    {
        STAGE_PL.target_184 = NULL;
    }
    func_80031824(wp);
}
