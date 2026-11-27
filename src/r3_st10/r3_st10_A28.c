#include "common.h"
#include "st10.h"

void func_80100A28(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        wp->routine_4 = 0xFF;
    }
}

void func_80100A44(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_80110074);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A90(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_8011007C);
        wp->routine_4 = 0xFF;
    }
}

sint32 func_80100ADC(void)
{
    if (D_800989F8.routine_4 == 0 && Sce_flag_test(0x21B) && !Sce_flag_test(0x229))
    {
        func_8001EB98(D_801149C0);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100B38(void)
{
    if (Sce_flag_test(0x1E))
    {
        func_8001EB98(&D_801100FC[0]);
        func_8001EB98(&D_801100FC[1]);
        func_8001EB98(&D_801100FC[2]);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100B94(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100BB4(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80100BD4(STAGE_ROOM *wp)
{
    D_80110138[wp->routine_4](wp);
}

void func_80100C10(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    pl = &STAGE_PL;
    switch (wp->routine_6)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0           = D_8011014C;
                wp->tbl_A4           = D_8011013C;
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.fixed_428.x = -0x1000000;
                STAGE_PL.fixed_428.y = -0x10000;
                STAGE_PL.fixed_428.z = -0x1230000;
                STAGE_PL.flags_bd |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                STAGE_PL.value_442 = 0x800;
                STAGE_PL.value_440 = 0;
                STAGE_PL.value_444 = 0;
                STAGE_PL.value_448 = 0x30;
                wp->timer_C        = 0xA;
                wp->routine_6++;
                MojiTaskExec2(1, 0);
            }
            break;
        case 1:
            if (--wp->timer_C < 0)
            {
                STAGE_PL.value_448 = 0x32;
                wp->routine_6++;
            }
            if ((sint32)Moji_flag >= 0)
            {
                D_800A395C  = 1;
                wp->flags_0 = 0;
                func_80042314(pl);
            }
            break;
        case 2:
            if (STAGE_PL.flags_A7 < 0)
            {
                wp->timer_C = (rand() & 0x1F) + 0x10;
                wp->routine_6--;
            }
            if ((sint32)Moji_flag >= 0)
            {
                D_800A395C  = 1;
                wp->flags_0 = 0;
                func_80042314(pl);
            }
            break;
    }
    if (wp->routine_6 != 0 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80100E38(void)
{
    Sce_camera_update();
    Sce_event_update();
}

void func_80100E60(void)
{
}

void func_80100E68(ST10_PL *wp)
{
    STAGE_OBJ *obj;
    STCOM_EFFECT *effect;
    obj = ST10_SCENE_OBJ_24;
    switch (wp->routine_D)
    {
        case 0:
            wp->pos_438.x  = -0x220C;
            wp->pos_438.y  = -0x201;
            wp->pos_438.z  = -0x15B0;
            wp->rot_440.y  = 0x800;
            wp->value_448  = 0x30;
            wp->rot_440.x  = 0;
            wp->rot_440.z  = 0;
            wp->target_184 = NULL;
            wp->be_flag &= ~2;
            wp->fixed_428.x = wp->pos_438.x << 16;
            wp->routine_D++;
            wp->fixed_428.y = wp->pos_438.y << 16;
            wp->fixed_428.z = wp->pos_438.z << 16;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                MojiTaskExec2(0, 6);
                wp->routine_D++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_D++;
            }
            break;
        case 3:
            MojiTaskExec2(0, 7);
            wp->routine_D++;
            break;
        case 4:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_D++;
            }
            break;
        case 5:
            MojiTaskExec2(0, 8);
            wp->routine_D++;
            break;
        case 6:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_D++;
            }
            break;
        case 7:
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->be_flag           = 5;
                effect->id                = 0x80;
                effect->type              = 0x41;
                effect->sprite.position   = obj->position;
                effect->sprite.position.y = obj->position.y - 0x64;
                Close_SHL_WORK(obj);
                wp->routine_D++;
            }
            break;
        case 8:
            wp->routine_D++;
            Sce_event_next();
            break;
    }
}

void func_80101068(ST10_PL *wp)
{
    D_801101E0[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_801010C8(STAGE_ROOM *wp)
{
    STAGE_OBJ *slot;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80110174;
    wp->tbl_A4 = D_801101C8;
    slot       = Scene_obj_ent_open(&D_801101A0[0]);
    slot->flags &= ~0x20;
    slot = Scene_obj_ent_open(&D_801101A0[1]);
    slot->flags &= ~0x20;
    STAGE_PL.routine_0 = 3;
    STAGE_PL.routine_1 = 0;
    STAGE_PL.value_C   = 0;
}

void func_80101178(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801011B8(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_801010C8(wp);
                Sce_camera_update();
                wp->routine_4++;
            }
            break;
        case 1:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_4++;
            }
            if (func_8001DE84() != 0)
            {
                wp->routine_4 = 10;
            }
            // fall through
        case 2:
            func_80101178((STAGE_ROOM_WORK *)wp);
            func_80101068((ST10_PL *)&Player_work);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 2)
            {
                wp->routine_4 = 11;
            }
            break;
        case 10:
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
            D_800A395C = 1;
            func_80039820();
            Close_SHL_WORK(wp->child_24);
            wp->routine_4++;
            break;
        case 11:
            func_80042314(&Player_work);
            D_800A395C = 1;
            STAGE_PL.be_flag |= 2;
            func_8003A264();
            wp->flags_0 = 0;
            break;
    }
}
