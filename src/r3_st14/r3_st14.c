#include "common.h"
#include "st14.h"

void func_801001E8(void)
{
    STAGE_TABLE_3C0 = D_801144F4;
    STAGE_TABLE_5A4 = D_80114634;
    STAGE_TABLE_10C = D_80114694;
    STAGE_TABLE_48  = D_80114754;
    STAGE_TABLE_24  = D_801147D4;
    STAGE_TABLE_50  = D_8011485C;
}

#ifdef __wasm32__
void func_801003B0(void);
#endif

void func_80100250(void)
{
    void *spawn;
    sint16 *cells;
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 1;
    spawn                     = D_80114C64[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_80114E70[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_80114F4C[D_80114F7C[Game_work.value_51]], D_80114E84[Game_work.value_51]);
    func_8005DC10(D_80113F94[Game_work.value_51]);
    func_801003B0();
}

void func_801003B0(void)
{
    func_8001E4C4(D_80114FFC, D_80115004[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_801003F4(void)
{
    D_80114FB8[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100448(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            STAGE_GAME.value_194 = 0;
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x7B0))
            {
                func_8001DDE4(0);
            }
            break;
    }
}

void func_801004B4(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_801004E4(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100514(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            STAGE_GAME.value_194 = 0;
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x7B0))
            {
                func_8001DDE4(0);
            }
            break;
    }
}

void func_80100580(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x50))
            {
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_8001EAE8(D_80115074);
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x27))
            {
                func_8001DDE4(0x25);
                wp->routine_4++;
            }
            break;
        case 2:
            if (func_801006DC(&D_80114FF8))
            {
                Sce_flag_on(0x41);
                func_8001DDE4(0x28);
                func_8001E4C4(D_80114FFC, D_80115064);
                wp->routine_4++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x50))
            {
                MojiTaskExec2(4, 0x10);
                func_8001E4C4(D_80114FFC, D_8011506C);
                wp->routine_4 = 0xFF;
            }
            break;
        case 0xFF:
            break;
    }
}

// The same test as st1a func_8012C1C0: the player's cell fits in a sint8.
sint32 func_801006DC(ST14_BOX *box)
{
    sint8 x;
    sint8 z;

    x = STAGE_PL.position.x >> 9;
    if ((uint16)(x - box->x) < box->w)
    {
        z = STAGE_PL.position.z >> 9;
        if ((uint16)(z - box->z) < box->h)
        {
            return 1;
        }
    }
    return 0;
}

void func_80100748(STAGE_ROOM *wp)
{
    D_80115088[wp->routine_4](wp);
}

void func_80100784(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                Sound_fade_start(0x10);
                wp->routine_5++;
            }
            break;
        case 1:
            if (Sound_fade_flags == 0)
            {
                Player_work.flags_0 &= ~3;
                Obj_work_flag_change(0x56, 5);
                Obj_work_flag_change(0x28, 0x80);
                func_8001E6C0(0, 0, 0);
                wp->reserved09[1] = 2;
                // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
                *(uint32 *)&wp->timer_C = 0;
                D_800BC7F0              = D_801150BC;
                wp->tbl_A4              = D_80115214;
                func_8001EAE8(&D_80115094[0]);
                func_8001EAE8(&D_80115094[1]);
                func_8001EC0C();
                Sce_event_update();
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_5++;
            }
            func_8001EC0C();
            Sce_event_update();
            break;
        case 3:
            Cd_xa_play_id(0x2001000C);
            func_80017C30(1);
            func_8001EC0C();
            Sce_event_update();
            wp->routine_5++;
            break;
        case 4:
            if (func_8001D878() && D_80098A72 == 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_8011510C;
                wp->tbl_A4    = D_80115224;
                wp->routine_5 = 0;
                wp->reserved09[1] &= 3;
                wp->routine_4++;
            }
            func_8001EC0C();
            Sce_event_update();
            break;
    }
    if (func_8001DE84())
    {
        wp->reserved09[1] |= 1;
    }
}

void func_8010098C(STAGE_ROOM *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        func_80017C30(10);
        wp->routine_5 = 0;
        wp->routine_4++;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (wp->reserved09[1] == 3)
        {
            wp->child_28->routine_0 = 2;
            func_80017C30(8);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
        else if (func_8001DE84())
        {
            if (wp->reserved09[1] & 2)
            {
                wp->child_28->routine_0 = 2;
            }
            func_80017C30(8);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    func_8001EC0C();
    Sce_event_update();
}

void func_80100A54(STAGE_ROOM *wp)
{
    if (D_80098A72 == 0)
    {
        switch (wp->routine_5)
        {
            case 0:
                func_8003187C(wp->child_24);
                wp->routine_5++;
                break;
            case 1:
                Cd_subcmd(0, 1, 0);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_80042314(&Player_work);
                Player_work.flags_0 |= 3;
                wp->routine_5++;
                break;
            case 2:
                Obj_work_flag_change(0x56, 0xA);
                Sce_flag_on(0x529);
                func_8001E3F0(0xE);
                Sound_fade_start(0x20);
                wp->flags_0 = 0;
                func_80017C30(2);
                break;
        }
    }
    if (wp->reserved09[1] != 0)
    {
        func_8001EC0C();
        Sce_event_update();
    }
}

void func_80100B88(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 5:
            child            = wp->child_24;
            child->routine_1 = 1;
            child->routine_2 = 0;
            break;
        case 0x43:
            child            = wp->child_24;
            child->routine_1 = 2;
            child->routine_2 = 0;
            break;
        case 0x8D:
            child            = wp->child_24;
            child->routine_1 = 3;
            child->routine_2 = 0;
            break;
        case 0xCD:
            wp->reserved09[1] &= 1;
            wp->child_28->routine_0 = 2;
            break;
        case 0x9:
        case 0x19:
        case 0x29:
        case 0x39:
        case 0x48:
        case 0x55:
            child = wp->child_24;
            Sound_call2(0x90, &child->position);
            break;
    }
}

void func_80100C94(void)
{
}

void func_80100C9C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_24;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

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
                func_8001EAE8(D_80115250);
                func_8001EC0C();
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
            func_8001EC0C();
            Sce_event_update();
            break;
        case 3:
            if (func_8001D878())
            {
                wp->routine_5++;
            }
            func_8001EC0C();
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
            func_8001EC0C();
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
    func_8001EC0C();
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
    func_8001EC0C();
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
