#include "common.h"
#include "st1c.h"

// The first of scene flags 0x54B to 0x552 that is set, or 0xFF.
uint8 func_80102DF8(void)
{
    sint32 i;

    for (i = 0; i < 8; i++)
    {
        if (Sce_flag_test(i + 0x54B))
        {
            return i;
        }
    }
    return 0xFF;
}

void func_80102E3C(ST1C_OBJ *wp)
{
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    wp->value_64               = 0;
    wp->rotation_prev.v.x      = 0;
    wp->rotation.v.x           = 0;
    wp->rotation.words[1]      = 0;
    wp->rotation_prev.words[1] = 0;
    wp->velocity.words[0]      = 0;
    wp->velocity.words[1]      = 0;
    wp->value_64               = 0;
    wp->value_70               = 0;
    wp->value_74               = 0;
    wp->scale.words[0]         = 0x02000200;
    wp->scale.words[1]         = 0x42100200;
    wp->rotation_prev.v        = wp->rotation.v;
    wp->position_prev          = wp->position;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    func_800322A8(wp, 0, 0);
    wp->data_78 = NULL;
    wp->data_10 = D_80104460;
    wp->routine_0++;
}

void func_80102F50(ST1C_OBJ *wp)
{
    if (Player_work.target_184 == wp)
    {
        Player_work.flags_bd |= 0x40;
        if (Sce_flag_test(0x40) == 0)
        {
            wp->routine_1++;
        }
        else
        {
            wp->routine_1 = 2;
        }
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80102FD0(ST1C_OBJ *wp)
{
    STCOM_FIXED_VECTOR pos;
    STCOM_PL_WORK *pl;
    uint8 done;

    pl   = &Player_work;
    done = 0;
    switch (wp->routine_2)
    {
        case 0:
            pos.x = wp->position.x;
            pos.y = wp->position.y - 0x92;
            pos.z = wp->position.z;
            func_80039FAC(&pos, 0xD4, 0, 0);
            pl->be_flag &= ~TRANS;
            wp->routine_2++;
            break;
        case 1:
            if (func_8003A13C() == 0)
            {
                func_80063BC8(&wp->position, 1, 0, 1);
                func_800322A8(wp, 8, 0);
                done = 1;
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                pl->be_flag |= TRANS;
                wp->routine_2++;
            }
            break;
        case 3:
            if (func_8003A13C() == 0)
            {
                Player_work.flags_bd &= ~0x40;
                func_800322A8(wp, 0, 0);
                Sce_flag_on(0x40);
                done          = 1;
                wp->routine_2 = 0;
                wp->routine_1--;
            }
            break;
    }
    if (done == 0)
    {
        func_80032488(wp);
    }
}

void func_80103178(ST1C_OBJ *wp)
{
    STCOM_FIXED_VECTOR pos;
    sint32 slot;
    STCOM_PL_WORK *pl;
    uint8 done;

    pl   = &Player_work;
    done = 0;
    switch (wp->routine_2)
    {
        case 0:
            pos.x = wp->position.x;
            pos.y = wp->position.y - 0x92;
            pos.z = wp->position.z;
            func_80039FAC(&pos, 0xD4, 0, 0);
            pl->be_flag &= ~TRANS;
            wp->routine_2++;
            break;
        case 1:
            if (func_8003A13C() == 0)
            {
                if (func_80102DF8() == 0xFF)
                {
                    wp->timer_C   = 1;
                    wp->routine_2 = 3;
                }
                else
                {
                    func_800322A8(wp, 0xB, 0);
                    wp->timer_C = 0x1E;
                    wp->routine_2++;
                }
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                wp->timer_C = 0xF;
                func_800322A8(wp, 0xC, 0);
                wp->routine_2++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                func_800322A8(wp, 8, 0);
                slot = func_80102DF8();
                if (slot == 0xFF)
                {
                    func_80063BC8(&wp->position, 1, 0, 2);
                }
                else
                {
                    func_80063BC8(&wp->position, 1, 0, slot + 3);
                }
                wp->routine_2++;
            }
            break;
        case 4:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                slot = func_80102DF8();
                if (slot != 0xFF && *(uint8 *)&Moji_flag == 0)
                {
                    Sce_flag_on(slot + 0x38);
                    Sce_flag_off(slot + 0x54B);
                    func_8001E3F0(0x19);
                }
                pl->be_flag |= TRANS;
                wp->routine_2++;
            }
            break;
        case 5:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x40;
                func_800322A8(wp, 0, 0);
                Sce_flag_on(0x40);
                done          = 1;
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
    if (done == 0)
    {
        func_80032488(wp);
    }
}

void func_80103400(STAGE_OBJ *wp)
{
    D_8010446C[wp->routine_1](wp);
}

void func_8010343C(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010345C(STAGE_OBJ *wp)
{
    D_80104478[wp->routine_0](wp);
    if ((uint8)wp->be_flag & TRANS)
    {
        Model_Shadow_Trans(wp, 0x3C, 0x200, 0);
    }
}

void func_801034C8(ST1C_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            wp->be_flag |= TRANS | MODEL;
            wp->type = D_801044C4[wp->index_C];
            Model_work_init(wp, &wp->type);
            if (wp->index_C == 5)
            {
                wp->color_40 = 0x2808080;
            }
            else
            {
                wp->color_40 = 0x808080;
            }
            wp->pos_38.x = D_80104484[wp->index_C].x;
            wp->pos_38.y = D_80104484[wp->index_C].y;
            wp->pos_38.z = D_80104484[wp->index_C].z;
            wp->model_10 = D_801044CC;
            wp->routine_0++;
            // fall through
        case 1:
            rot.x = 0;
            rot.y = D_80104484[wp->index_C].pad;
            rot.z = 0;
            RotMatrixYXZ(&rot, &wp->matrix);
            scale.x = 0x200;
            scale.y = 0x200;
            scale.z = 0x200;
            ScaleMatrix(&wp->matrix, &scale);
            if (pl->target_184 == wp)
            {
                func_80063BC8(&wp->pos_38, 0, 0, wp->index_C + 0x3C);
            }
            break;
    }
}
