#include "common.h"
#include "st14.h"

void func_80100CC4(STAGE_ROOM *wp)
{
    D_80115244[wp->routine_4](wp);
}

void func_80100D00(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                wp->reserved09[1] = 0x80;
                Sound_fade_start(0x10);
                wp->routine_5++;
            }
            break;
        case 1:
            if (Sound_fade_flags == 0)
            {
                Player_work.flags_0 &= ~3;
                Obj_work_flag_change(0x10, 0x80);
                Obj_work_flag_change(0x56, 5);
                Obj_work_flag_change(0x28, 0x80);
                func_8001E6C0(0, 0, 0);
                // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
                *(uint32 *)&wp->timer_C = 0;
                D_800BC7F0              = D_80115264;
                wp->tbl_A4              = D_801153E4;
                Scene_obj_ent_open(D_80115250);
                Sce_camera_update();
                Sce_event_update();
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                Cd_xa_play_id(0x2000001B);
                wp->routine_5++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 3:
            if (func_8001D878())
            {
                wp->routine_5++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 4:
            if (D_80098A72 == 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_801152B4;
                wp->tbl_A4    = D_801153F4;
                wp->routine_5 = 0;
                wp->reserved09[1] &= 1;
                wp->routine_4++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
    }
    if (func_8001DE84())
    {
        wp->reserved09[1] |= 1;
    }
}

#ifdef NON_MATCHING
// Only the table call differs: retail sets a0 from s0 in the jalr delay slot (as in r3_st17's
// func_80116D94).
void func_80100EF0(STAGE_ROOM *wp)
{
    if (wp->routine_8 == 0xFF || (wp->tbl_A4[1](wp), func_8001DE84() != 0) || wp->reserved09[1] == 1)
    {
        wp->routine_5 = 0;
        wp->routine_4++;
    }
    Sce_camera_update();
    Sce_event_update();
}
#else
void func_80100EF0(STAGE_ROOM *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        wp->routine_4++;
        wp->routine_5 = 0;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84() != 0 || wp->reserved09[1] == 1)
        {
            wp->routine_4++;
            wp->routine_5 = 0;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}
#endif

void func_80100F7C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    Cd_subcmd(0, 1, 0);
    Obj_work_flag_change(0x56, 0xA);
    func_8003187C(wp->child_24);
    func_801010F4();
    pl = &Player_work;
    func_80042314(pl);
    pl->flags_0 |= 3;
    func_8003697C();
    D_800A395C = 1;
    func_80039820();
    Sound_call(0x28, 0, 0);
    wp->flags_0 = 0;
}

void func_80101024(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 temp_v1;

    temp_v1 = wp->frame_10;
    child   = wp->child_24;
    switch (temp_v1)
    {
        case 0xEB:
            child->routine_1    = 1;
            child->u_C.b.byte_D = 0;
            child->u_E.b.byte_E = 0;
            return;
        case 0x14F:
            child->u_C.b.byte_D++;
            child->u_E.b.byte_E++;
            return;
        case 0x163:
            child->routine_1 = 2;
            child->routine_2 = 0;
            return;
    }
}

void func_801010A0(void)
{
}

void func_801010A8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 temp_v1;

    temp_v1 = wp->frame_10;
    switch (temp_v1)
    {
        case 0x0:
            child               = wp->child_24;
            child->routine_1    = 3;
            child->u_E.b.byte_E = 0;
            return;
        case 0x64:
            child               = wp->child_24;
            child->routine_1    = 4;
            child->u_C.b.byte_D = 0;
            return;
    }
}

void func_801010F4(void)
{
    STAGE_OBJ *wp;

    wp = func_80031498();
    if (wp != NULL)
    {
        wp->flags_0            = 1;
        wp->kind_2             = 0x17;
        wp->position.x         = -0x104;
        wp->position.y         = 0;
        wp->position.z         = -0x15E0;
        wp->value_4            = 0;
        wp->variant_3          = 0;
        wp->u_C.b.byte_C       = 0;
        wp->u_C.b.byte_D       = 0;
        wp->u_E.b.byte_E       = 0;
        wp->u_E.b.byte_F       = 0;
        wp->routine_0          = 0;
        wp->position_fixed.v.x = wp->position.x << 16;
        wp->position_fixed.v.y = wp->position.y << 16;
        wp->position_fixed.v.z = wp->position.z << 16;
        func_8005D620(wp, 0, 0, 0x51, 0x7080);
    }
}
