#include "common.h"
#include "st1a.h"

void func_8010BF50(ST1A_NPC *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    face                    = &wp->face_348;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            func_8010C1C8(wp, face);
            break;
        case 1:
            if (Scene_work.u_8.byte[1] == 14)
            {
                switch (Scene_work.value_10)
                {
                    case 0x3C:
                    case 0x50:
                    case 0x7D:
                    case 0xB9:
                    case 0x186:
                    case 0x2B2:
                    case 0x334:
                        wp->face_348.value_2 = 1;
                        break;
                    case 0x1E:
                    case 0x46:
                    case 0x6E:
                    case 0xA8:
                    case 0x163:
                    case 0x288:
                    case 0x320:
                    case 0x382:
                        face->value_2 = 0;
                        break;
                }
            }
            else if (Scene_work.u_8.byte[1] == 15)
            {
                wp->routine_0++;
            }
            break;
    }
    func_8010C254(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->timer_0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x24, 0x200, 0);
    }
}

void func_8010C1C8(ST1A_NPC *wp, STAGE_FACE *face)
{
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_78       = 0;
    wp->anim_AC        = 1;
    wp->anim_prev_AD   = 0xFF;
    face->timer_0      = 0;
    face->value_2      = 1;
    wp->routine_0      = 1;
    wp->routine_1      = 0;
    wp->routine_2      = 0;
    wp->routine_3      = 0;
}

void func_8010C254(ST1A_NPC *wp, STAGE_FACE *face)
{
    if (face->value_2 == 0)
    {
        wp->blink_114 = 7;
        return;
    }
    if (!(wp->u_E.b.byte_E & 3))
    {
        wp->blink_114 = wp->blink_114 == 7 ? 8 : 7;
    }
    wp->u_E.b.byte_E++;
}

void func_8010C2B0(ST1A_NPC *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_80131DC8[wp->type](wp, &Scene_work, &wp->face_348);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face_348.timer_0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, D_80131DFC[wp->type], 0x200, 0);
    }
}

void func_8010C3CC(ST1A_NPC *wp, STAGE_FACE *face)
{
    wp->be_flag |= 2;
    wp->id = D_80131DDC[wp->type];
    Model_work_init(wp, NULL);
    wp->id             = 0x30;
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_78       = 0;
    wp->anim_AC        = D_80131DF0[wp->type];
    wp->anim_prev_AD   = 0xFF;
    face->timer_0      = 0;
    wp->routine_0      = 1;
    wp->routine_1      = 0;
    wp->routine_2      = 0;
    wp->routine_3      = 0;
}

void func_8010C484(ST1A_NPC *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            func_8010C3CC(wp, face);
            break;
        case 1:
            if (scene->u_8.byte[1] == 0x11 && scene->value_10 == 1)
            {
                if (wp->type == 0)
                {
                    wp->rotation.y = 0x400;
                    wp->position.x -= 0x28;
                    wp->position_fixed.v.x = wp->position.x << 16;
                }
                else
                {
                    wp->rotation.y = 0x800;
                }
                wp->routine_1++;
            }
            break;
        case 2:
            break;
    }
}

void func_8010C530(ST1A_NPC *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            func_8010C3CC(wp, face);
            wp->face_FC      = 0xC;
            wp->u_C.b.byte_D = 0;
            wp->u_E.b.byte_E = 0x1E;
            wp->u_E.b.byte_F = 0;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 0xA)
            {
                wp->routine_0++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 0x10 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x19;
                face->timer_0 = 0;
                wp->routine_0++;
            }
            break;
        case 5:
            wp->anim_prev_AD = 0xFF;
            func_8010C8A0(wp);
            if (scene->u_8.byte[1] == 0x10 && scene->value_10 == 0x1E)
            {
                wp->routine_0++;
            }
            break;
        case 6:
            func_8010C8A0(wp);
            if (scene->u_8.byte[1] == 0x11 && scene->value_10 == 1)
            {
                wp->routine_0++;
            }
            break;
    }
}

void func_8010C688(ST1A_NPC *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            func_8010C3CC(wp, face);
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 5)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 7 && scene->value_10 == 1)
            {
                wp->anim_AC      = 0x14;
                wp->anim_prev_AD = 0xFF;
                face->timer_0    = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x13 && scene->value_10 == 5)
            {
                wp->face_FC = 0xF;
                wp->routine_0++;
            }
            break;
        case 4:
            break;
    }
}

void func_8010C784(ST1A_NPC *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            func_8010C3CC(wp, face);
            break;
        case 1:
            if (scene->u_8.byte[1] == 0x1B && scene->value_10 == 0x96)
            {
                wp->anim_AC = 8;
                wp->routine_0++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0x1B && scene->value_10 == 0xE6)
            {
                wp->anim_AC = 0x13;
            }
            if (scene->u_8.byte[1] == 0x1D && scene->value_10 == 1)
            {
                wp->anim_AC = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 0x1D && scene->value_10 == 0xCD)
            {
                wp->anim_AC = 8;
                wp->routine_0++;
            }
            break;
        case 4:
            if (wp->value_A7 == -1)
            {
                wp->anim_prev_AD = 0xFF;
                wp->routine_0++;
            }
            break;
        case 5:
            break;
    }
}

void func_8010C8A0(ST1A_NPC *wp)
{
    if (wp->u_C.b.byte_D > 0)
    {
        if (--wp->u_C.b.byte_D == 0)
        {
            wp->u_E.b.byte_E = (rand() & 0x1F) + 0x1E;
        }
    }
    else if (wp->u_E.b.byte_E > 0)
    {
        if (!(wp->u_E.b.byte_F & 3))
        {
            wp->face_FC = wp->face_FC == 0xB ? 1 : 0xB;
        }
        wp->u_E.b.byte_E--;
        wp->u_E.b.byte_F++;
    }
    else
    {
        wp->u_C.b.byte_D = (rand() & 0xF) + 0xF;
    }
}
