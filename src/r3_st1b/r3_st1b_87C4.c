#include "common.h"
#include "st1b.h"

void func_801087C4(STAGE_WORK *wp)
{
    D_80113E98[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80113E94[0]->id, 0x2A, 0x33, 6));
}

void func_80108820(STAGE_WORK *wp)
{
    D_80113EA0[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80113E9C[0]->id, 0x2A, 0x33, 6));
}

void func_8010887C(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_80113E94_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80113E94[0] += count;
            func_801087C4(wp);
        }
        else if (++D_80113E98[0] == p->count)
        {
            D_80113E94_S = p + 1;
            func_801087C4(wp);
        }
    }
    p     = D_80113E9C_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80113E9C[0] += count;
            func_80108820(wp);
        }
        else if (++D_80113EA0[0] == p->count)
        {
            D_80113E9C_S = p + 1;
            func_80108820(wp);
        }
    }
}

void func_801089A4(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80113EA4.cue_0->u.end != 0xFF && D_80113EA4.cue_0->u.scene == scene->u_8.value_8 && D_80113EA4.cue_0->line == scene->value_1C)
    {
        D_80113E94[0] = D_8010E864[D_80113EA4.cue_0->index];
        func_801087C4(wp);
        D_80113EA4.cue_0++;
    }
    if (D_80113EA4.cue_4->u.end != 0xFF && D_80113EA4.cue_4->u.scene == scene->u_8.value_8 && D_80113EA4.cue_4->line == scene->value_1C)
    {
        D_80113E9C[0] = D_8010E870[D_80113EA4.cue_4->index];
        func_80108820(wp);
        D_80113EA4.cue_4++;
    }
    func_8010887C(wp);
}

void func_80108AEC(STAGE_OBJ *wp)
{
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    if (Scene_work.reserved00[1] == 0x48)
    {
        D_80113EA4.cue_0 = D_8010E87C;
        D_80113EA4.cue_4 = D_8010E89C;
    }
    else
    {
        D_80113EA4.cue_0 = D_8010E8C0;
        D_80113EA4.cue_4 = D_8010E8CC;
    }
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_80108B9C(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x10, 0);
        wp->routine_2++;
    }
}

void func_80108BE8(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x11, 0);
        wp->routine_2++;
    }
}

void func_80108C34(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x12, 0);
        wp->routine_2++;
    }
}

void func_80108C80(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x13, 0);
        wp->routine_2++;
    }
}

void func_80108CCC(STAGE_WORK *wp)
{
    D_8010E8E0[wp->routine_1](wp);
    if (wp->value_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_801089A4(wp);
}

void func_80108D3C(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80108AEC(wp);
    }
    func_80108CCC(wp);
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}

void func_80108D94(STAGE_OBJ *wp)
{
    D_8010E8FC[wp->routine_0](wp);
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(0, 0x33, 0x37, 5));
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(0, 0x33, 0x37, 5));
}

void func_80108E2C(ST1B_VIEW *wp)
{
    wp->value_4E0  = 2;
    wp->value_10   = (sint32)D_8010E8F0;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_44   = 0;
    wp->value_48   = 0;
    wp->value_6E   = 0;
    wp->vec_AC.z   = 0;
    wp->vec_AC.pad = 0;
    wp->value_78   = 0;
    wp->routine_1  = 0;
    wp->be_flag |= 2;
    wp->value_4EA = (sint16)(uint16)wp->rotation.y;
    Model_work_init(wp, NULL);
    wp->value_158  = 0x02000200;
    wp->u_15C.w[0] = 0x42100200;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_80108EDC(ST1B_TALKER *wp)
{
    ST1B_TALK *talk;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    talk                    = &wp->talk;
    if (wp->talk.flags_0 & 2)
    {
        func_801093EC(wp);
    }
    D_8010E908[wp->routine_1](wp);
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
    if (!(talk->flags_0 & 4))
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_80109028(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80109048(STAGE_OBJ *wp)
{
    D_8010E910[wp->routine_2](wp);
}

void func_80109084(STAGE_OBJ *wp)
{
    wp->anim_AC             = 0;
    wp->u_4E0.face16.prev_8 = (sint16)D_8010E91C[rand() & 0xF];
    wp->routine_2++;
}

void func_801090D0(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    temp_v0                 = (uint16)wp->u_4E0.face16.prev_8 - 1;
    wp->u_4E0.face16.prev_8 = temp_v0;
    if ((temp_v0 << 0x10) == 0)
    {
        wp->anim_AC = 9;
        wp->routine_2++;
    }
}

void func_80109104(ST1B_STCOM01_WORK *wp)
{
    if (wp->state_A7 < 0)
    {
        wp->routine_2 = 0;
    }
}

void func_80109120(ST1B_TALKER *wp)
{
    D_8010E92C[wp->talk.routine_3](wp);
}

void func_8010915C(ST1B_TALKER *wp)
{
    ST1B_TALK *talk;
    uint32 turn;
    uint8 anim;
    talk        = &wp->talk;
    anim        = wp->anim_AC;
    wp->anim_AC = 0;
    wp->talk.routine_3++;
    wp->talk.angle_4 = wp->rotation.y;
    wp->talk.anim_2  = anim;
    if (Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800) < 0)
    {
        turn = -Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
    }
    else
    {
        turn = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
    }
    turn >>= 3;
    talk->turn_6 = turn;
    func_80063BC8(&wp->position, 0, 0, wp->value_C);
}

void func_80109228(ST1B_TALKER *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->talk.turn_6)) & 0xFFF;
    if (Moji_flag & 0x200000)
    {
        wp->anim_AC = 9;
        wp->talk.routine_3++;
    }
    if (D_800987B0[0] == 0)
    {
        wp->talk.routine_3 = 3;
        wp->anim_AC        = 0;
        wp->talk.flags_0 &= ~4;
    }
}

void func_801092C8(ST1B_TALKER *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->talk.turn_6)) & 0xFFF;
    if (wp->value_A7 < 0)
    {
        wp->anim_AC = 0;
        wp->talk.routine_3--;
    }
    if (D_800987B0[0] == 0)
    {
        wp->talk.routine_3 = 3;
        wp->anim_AC        = 0;
        wp->talk.flags_0 &= ~4;
    }
}

void func_80109358(ST1B_TALKER *wp)
{
    sint16 turn;
    turn = Angle_diff_clamp(wp->talk.angle_4, wp->rotation.y, wp->talk.turn_6);
    if (turn == 0 || Sce_flag_test(0x4E))
    {
        wp->routine_1 = 1;
        wp->anim_AC   = wp->talk.anim_2;
        wp->talk.flags_0 |= 2;
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    }
}

void func_801093EC(ST1B_TALKER *wp)
{
    ST1B_TALKER *target;

    target = STAGE_PL.target_184;
    if (target == wp)
    {
        target->routine_1      = 1;
        target->talk.routine_3 = 0;
        target->talk.flags_0 |= 4;
        target->talk.flags_0 &= ~2;
    }
}

void func_80109420(STAGE_WORK *wp)
{
    D_80113EB0[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80113EAC[0]->id, 0x33, 0x37, 5));
}

void func_8010947C(STAGE_WORK *wp)
{
    D_80113EB8[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80113EB4[0]->id, 0x33, 0x37, 5));
}

void func_801094D8(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_80113EAC_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80113EAC[0] += count;
            func_80109420(wp);
        }
        else if (++D_80113EB0[0] == p->count)
        {
            D_80113EAC_S = p + 1;
            func_80109420(wp);
        }
    }
    p     = D_80113EB4_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80113EB4[0] += count;
            func_8010947C(wp);
        }
        else if (++D_80113EB8[0] == p->count)
        {
            D_80113EB4_S = p + 1;
            func_8010947C(wp);
        }
    }
}

void func_80109600(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80113EBC.cue_0->u.end != 0xFF && D_80113EBC.cue_0->u.scene == scene->u_8.value_8 && D_80113EBC.cue_0->line == scene->value_1C)
    {
        D_80113EAC[0] = D_8010E990[D_80113EBC.cue_0->index];
        func_80109420(wp);
        D_80113EBC.cue_0++;
    }
    if (D_80113EBC.cue_4->u.end != 0xFF && D_80113EBC.cue_4->u.scene == scene->u_8.value_8 && D_80113EBC.cue_4->line == scene->value_1C)
    {
        D_80113EB4[0] = D_8010E9A0[D_80113EBC.cue_4->index];
        func_8010947C(wp);
        D_80113EBC.cue_4++;
    }
    func_801094D8(wp);
}

void func_80109748(STAGE_OBJ *wp)
{
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    if (Scene_work.reserved00[1] == 0x48)
    {
        D_80113EBC.cue_0 = D_8010E9B0;
        D_80113EBC.cue_4 = D_8010E9D0;
    }
    else
    {
        D_80113EBC.cue_0 = D_8010EA14;
        D_80113EBC.cue_4 = D_8010EA28;
    }
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_801097F8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80109844(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
    Obj_pos_set(wp, 0x3D, 0, 0);
}

void func_801098A4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_801098F0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_8010993C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80109988(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 7, 0);
            wp->timer_C = 0x50;
            wp->routine_2++;
            break;
        case 2:
            wp->position_fixed.v.x += 0x3AEE;
            wp->position_fixed.v.y += 0x39DCC;
            if (--wp->timer_C == 0)
            {
                wp->routine_2++;
            }
            break;
        case 3:
            func_800322A8(wp, 8, 0);
            wp->rot_y_56 -= 0x400;
            wp->routine_2++;
            break;
        case 4:
            if (*wp->anim_98 == 0x11)
            {
                wp->timer_C = 0x16;
                wp->routine_2++;
            }
            break;
        case 5:
            if (--wp->timer_C == 0)
            {
                wp->routine_2++;
            }
            wp->position_fixed.v.z -= 0x32000;
            break;
        case 1:
        case 6:
            break;
    }
}

void func_80109AC8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_80109B14(STAGE_WORK *wp)
{
    D_8010EA40[wp->routine_1](wp);
    if (wp->value_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_80109600(wp);
}

void func_80109B84(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80109748(wp);
    }
    func_80109B14(wp);
    if (wp->routine_1 != 0 && wp->routine_1 != 5)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}
