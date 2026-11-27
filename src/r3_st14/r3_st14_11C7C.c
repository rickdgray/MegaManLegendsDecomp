#include "common.h"
#include "st14.h"

void func_80111C7C(ST14_PROP *wp)
{
    wp->position_prev           = wp->position;
    wp->position_fixed_prev.x   = wp->position_fixed.v.x;
    wp->position_fixed_prev.y   = wp->position_fixed.v.y;
    wp->position_fixed_prev.z   = wp->position_fixed.v.z;
    wp->position_fixed_prev.pad = wp->position_fixed.v.pad;
    wp->rotation_prev           = wp->rotation;
    D_80115EC0[wp->routine_0](wp);
    if ((uint8)wp->be_flag & TRANS)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
}

void func_80111D48(ST14_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->rotation.x = 0;
    wp->rotation.y = 0x800;
    wp->rotation.z = 0;
    wp->be_flag |= TRANS | MODEL;
    wp->model.pos_AC = wp->position;
    RotMatrix(&wp->rotation, &wp->model.matrix_8C);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->model.matrix_8C, &scale);
    wp->model.color_B4 = 0x808080;
    Model_work_init(wp, &wp->type);
    wp->data_78 = NULL;
    wp->data_10 = D_80115EB4;
    wp->routine_0++;
}

void func_80111E10(STAGE_OBJ *wp)
{
    if (STAGE_PL.target_184 == wp && !Sce_flag_test(0x635))
    {
        Sce_flag_on(0x635);
        wp->routine_1 = 0;
        wp->routine_0++;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80111E7C(ST14_PROP *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                Player_work.value_C   = 0;
                func_80063BC8(&wp->position, 2, 0, 0xA);
                Player_work.target_184 = NULL;
                wp->routine_1++;
            }
            break;
        case 1:
            Player_work.value_448 = 0x30;
            wp->routine_1++;
            break;
        case 2:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                wp->routine_1++;
            }
            break;
        case 3:
            if (func_8003A13C() == 0)
            {
                func_80042314(pl);
                pl->be_flag |= TRANS;
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_80111FB8(ST14_PROP *wp)
{
    D_80115ED8[wp->routine_0](wp);
}

void func_80111FF4(ST14_PROP *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;

    wp->data_78 = D_80115ECC;
    wp->hit_BC  = 0;
    wp->hit_C0  = 0;
    wp->hit_C4  = 0;
    wp->hit_C8  = 0;
    wp->be_flag |= TRANS | MODEL;
    rot.x = (wp->angle_64.x + 0x400) & 0xFFF;
    rot.y = wp->angle_64.y & 0xFFF;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->model.matrix_8C);
    scale.z = 0x100;
    scale.x = 0x100;
    scale.y = 0x200;
    ScaleMatrix(&wp->model.matrix_8C, &scale);
    wp->velocity.x = (uint32)(-rsin(wp->angle_64.y) * 25) >> 11;
    wp->velocity.y = 0;
    wp->velocity.z = (uint32)(-rcos(wp->angle_64.y) * 25) >> 11;
    wp->position.x += wp->velocity.x;
    wp->position.y += wp->velocity.y;
    wp->position.z += wp->velocity.z;
    wp->accel.x             = 0;
    wp->accel.y             = 0;
    wp->accel.z             = 0;
    wp->model.pos_AC.x      = wp->position.x;
    wp->model.pos_AC.y      = wp->position.y;
    wp->model.pos_AC.z      = wp->position.z;
    wp->position_fixed.v.x  = wp->position.x << 16;
    wp->position_fixed.v.y  = wp->position.y << 16;
    wp->position_fixed.v.z  = wp->position.z << 16;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    wp->model.color_B4      = 0x2808080;
    Model_work_init(wp, NULL);
    func_801123AC(wp);
    wp->count_F = 0;
    wp->routine_0++;
}

void func_801121D0(ST14_PROP *wp)
{
    ST14_MODEL *model;
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;
    sint32 level;

    model = &wp->model;
    if (func_80037694(wp, 0) || ++wp->count_F == 0x40)
    {
        Close_SHL_WORK(wp);
        return;
    }
    if (wp->count_F < 0x30)
    {
        wp->model.color_B4 = 0x2808080;
    }
    else
    {
        level              = (-0x80 - (wp->count_F - 0x30) * 8) & 0xFF;
        wp->model.color_B4 = 0x2000000 + (level << 16) + (level << 8) + level;
    }
    rot.x = (wp->angle_64.x + 0x400) & 0xFFF;
    rot.y = wp->angle_64.y & 0xFFF;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->model.matrix_8C);
    scale.x = scale.z = (wp->count_F << 5) + 0x200;
    scale.y           = 0x200;
    ScaleMatrix(&wp->model.matrix_8C, &scale);
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    wp->position_fixed.v.x += wp->velocity.x << 16;
    wp->position_fixed.v.y += wp->velocity.y << 16;
    wp->position_fixed.v.z += wp->velocity.z << 16;
    model->pos_AC.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    model->pos_AC.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    model->pos_AC.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    if (wp->count_F < 0x3C)
    {
        func_801123AC(wp);
    }
}

void func_801123AC(ST14_PROP *wp)
{
    func_800341BC(&wp->position, wp->count_F * 3 + 0x40, 0, 0xA000, wp->work_id, &wp->hit_BC, 0x8000020, 0, 0x80);
    wp->hit_BC = 0;
    wp->hit_C0 = 0;
    wp->hit_C4 = 0;
    wp->hit_C8 = 0;
}
