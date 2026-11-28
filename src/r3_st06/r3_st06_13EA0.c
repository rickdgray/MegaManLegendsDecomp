#include "common.h"
#include "st06.h"

void func_80113EA0(ST06_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                MojiTaskExec2(0, 0x12);
                wp->routine_1++;
                Sound_call(0x16F, 0, 0);
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                wp->value_44.half[0] = 0x200;
                wp->u_C.b.byte_C     = -0x60;
                wp->routine_1++;
            }
            break;
        case 2:
            if (--wp->u_C.b.byte_C == 0)
            {
                Sce_event_next();
                wp->u_C.b.byte_C     = 3;
                wp->value_44.half[0] = 0;
                wp->routine_1++;
            }
            if (wp->value_A6 != 0)
            {
                Sound_call2(0x112, &wp->position);
                if (!(rand() & 3))
                {
                    Sound_call2(0x171, &wp->position);
                }
            }
            // fall through
        case 3:
            if (STAGE_SCENE_PTR->u_8.byte[1] == 2)
            {
                MojiTaskExec2(0, 0x14);
                wp->position.x         = 0x1EA;
                wp->position.y         = -1;
                wp->position.z         = -0x1371;
                wp->value_44.half[0]   = 0x140;
                wp->u_C.b.byte_C       = -0x22;
                wp->rotation.y         = 0;
                wp->position_fixed.v.x = wp->position.x << 16;
                wp->position_fixed.v.y = wp->position.y << 16;
                wp->position_fixed.v.z = wp->position.z << 16;
                wp->routine_1++;
            }
            break;
        case 4:
            if (--wp->u_C.b.byte_C == 0)
            {
                wp->routine_0 = 2;
                wp->routine_1 = 0;
            }
            if (wp->value_A6 != 0)
            {
                Sound_call(0x112, 0, 0);
                if (!(rand() & 3))
                {
                    Sound_call(0x171, 0, 0);
                }
            }
            break;
    }
    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
}

void func_801140DC(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801140FC(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_80125464[wp->routine_0](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_2 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_2++;
    }
}

void func_801141EC(ST06_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // retail's frame has room for it

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
    wp->scale.v.pad           = 0x4210;
    wp->position.y            = Obj_ceiling_height_get(wp);
    wp->position_fixed.y      = wp->position.y << 16;
    wp->value_78              = D_80125470;
    wp->value_6E              = 0;
    wp->value_B0              = 0;
    wp->value_B2              = 0;
    wp->data_10               = NULL;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 2, 0);
}
