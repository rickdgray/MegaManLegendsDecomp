#include "common.h"
#include "st1a.h"

void func_80103CB8(STAGE_ROOM *wp)
{
    ST1A_JOINTS_OBJ *obj;
    STCOM_EFFECT *ep;
    uint16 rnd;
    uint8 joint;

    switch (wp->routine_6)
    {
        case 1:
            Fade_start(0xF);
            D_80139710 |= 0x80;
            wp->routine_6++;
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                func_8003187C(wp->child_24);
                Obj_work_flag_change(0x60, 0x80);
                wp->reserved09[1] = 0x3C;
                wp->routine_6++;
                break;
            }
            // fall through
        case 0:
            if (wp->frame_10 >= 0xC9)
            {
                rnd = *(uint16 *)0x1F800002;
                if (!(rnd & 3))
                {
                    obj   = (ST1A_JOINTS_OBJ *)wp->child_24;
                    joint = (rnd >> 2) % 14;
                    ep    = func_80031618();
                    if (ep != NULL)
                    {
                        ep->flags_0         = 5;
                        ep->kind_2          = 0x80;
                        ep->variant_3       = 2;
                        ep->value_D         = 3;
                        ep->value_C         = 0;
                        ep->timer_E         = 0;
                        ep->sprite.position = obj->joints_180[joint];
                    }
                }
            }
            break;
        case 3:
            if (--wp->reserved09[1] == 0)
            {
                wp->routine_6++;
            }
            break;
        case 4:
            Cd_read_comb(0xBF);
            wp->routine_5++;
            wp->routine_6++;
            break;
        case 5:
            if (Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x20010022);
                wp->routine_6++;
            }
            break;
        case 6:
            if (func_8001D878() != 0)
            {
                Fade_start(7);
                Sce_event_next();
                wp->routine_6 = 0;
            }
            break;
    }
}

void func_80103ECC(ST1A_ROOM_FX *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_SVECTOR pos;

    pl = &Player_work;
    switch (wp->routine_6)
    {
        case 0:
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = 0;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.pos_438.z   = 0x5DC;
            STAGE_PL.fixed_428.x = 0;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.fixed_428.z = 0x5DC << 16;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_444   = 0;
            STAGE_PL.value_448   = 0x80;
            STAGE_PL.value_76    = 0;
            STAGE_PL.value_74    = 0;
            pl->flags_0 |= 3;
            STAGE_PL.flags_bd |= 0x10;
            func_80103A14(0);
            func_801039DC(0);
            pos.x     = 0x96;
            pos.y     = -0xC1;
            pos.z     = 0x5DC;
            wp->fx_A0 = func_8012B320(&pos, 0xA, 1, 0x14, -3, 1, 1);
            pos.x     = 0;
            pos.y     = -0xC1;
            pos.z     = 0x898;
            wp->fx_9C = func_8012B320(&pos, 4, 2, 0x14, -3, 1, 0);
            pos.x     = -0x96;
            pos.y     = -0xC1;
            pos.z     = 0x960;
            wp->fx_98 = func_8012B320(&pos, 0xA, 1, 0x14, -3, 1, 0);
            wp->routine_6++;
            break;
        case 1:
            pl->flags_0 &= ~1;
            wp->routine_6++;
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                func_801039DC(4);
                wp->routine_5++;
                D_80139710 &= ~0x80;
                wp->routine_6++;
            }
            break;
    }
    func_80103A4C();
    switch (wp->frame_10)
    {
        case 0x1E:
            func_8012B440(0, 0x50, 0, 0xF, 0x80, 3);
            break;
        case 0x28:
            func_8012B440(0, 0x28, 3, 0x14, 0x60, 4);
            break;
        case 0x2D:
            func_8012B440(0, 0x50, 2, 0x14, 0x80, 4);
            // fall through
        case 0x41:
            func_8012B440(0, 0x32, 1, 0x14, 0x80, 6);
            break;
    }
    if (wp->frame_10 > 0x1E && wp->frame_10 < 0x5A)
    {
        wp->fx_A0->timer_D++;
    }
    else if (wp->frame_10 == 0x5A)
    {
        func_80031988(wp->fx_A0);
    }
}

void func_80104238(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    switch (wp->frame_10)
    {
        case 0:
            pl            = &Player_work;
            wp->routine_6 = 0;
            pl->flags_0 |= 1;
            func_80103A14(4);
            func_801039DC(1);
            break;
        case 15:
            func_80103A14(1);
            break;
    }
    func_80103A4C();
}

void func_801042B0(ST1A_ROOM_FX *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80103B34(2, 0, 0, 0, 0);
        Scene_obj_ent_open(&D_8012FF78);
    }
    else if (wp->frame_10 < 0x40)
    {
        wp->fx_9C->timer_D++;
        wp->fx_98->timer_D++;
    }
    else if (wp->frame_10 == 0x40)
    {
        func_80031988(wp->fx_9C);
        func_80031988(wp->fx_98);
    }
}

void func_80104370(void)
{
}

void func_80104378(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;

    obj = wp->child_24;
    if (wp->frame_10 == 0)
    {
        func_80103B34(0xB, 0, 0, 0, 0);
        Player_work.flags_0 &= ~2;
        Scene_obj_ent_open(D_8012FF8C);
        obj->position.y         = -0x64;
        obj->position.x         = 0;
        obj->position.z         = -0xC8;
        obj->value_44.half[1]   = -0x18;
        obj->position_fixed.v.x = obj->position.x << 16;
        obj->position_fixed.v.y = obj->position.y << 16;
        obj->position_fixed.v.z = obj->position.z << 16;
    }
}

void func_8010441C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_6)
    {
        case 0:
            wp->child_28->flags_0 &= ~2;
            wp->child_24->flags_0 &= ~2;
            wp->child_24->value_44.half[1] = 0;
            func_80103B34(2, 0, -0xC1, 0x780, 0x800);
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.pos_438.z   = 0x780;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.fixed_428.z = 0x780 << 16;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.pos_438.x   = 0;
            STAGE_PL.fixed_428.x = 0;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_444   = 0;
            STAGE_PL.value_448   = 0x81;
            STAGE_PL.value_76    = 0;
            STAGE_PL.value_74    = 0;
            pl->flags_0 |= 3;
            STAGE_PL.flags_bd |= 0x10;
            func_80103A14(2);
            func_801039DC(2);
            wp->routine_6++;
            break;
        case 1:
            STAGE_PL.flags_bd |= 0x10;
            STAGE_PL.pos_438.z += 0xA;
            STAGE_PL.fixed_428.z = STAGE_PL.pos_438.z << 16;
            if (wp->frame_10 == 0x10)
            {
                STAGE_PL.value_448 = 0x82;
            }
            else if (wp->frame_10 == 0x1C)
            {
                wp->routine_6++;
            }
            break;
        case 2:
            if (wp->frame_10 == 0x28)
            {
                func_801039DC(5);
            }
            break;
    }
    func_80103A4C();
}

void func_80104630(STAGE_ROOM *wp)
{
    ST1A_OBJ *obj;

    obj = (ST1A_OBJ *)wp->child_24;
    switch (wp->frame_10)
    {
        case 0:
            wp->routine_6 = 0;
            func_80103B34(0xB, 0, 0, 0, 0);
            Player_work.flags_0 &= ~2;
            wp->child_28->flags_0 |= 2;
            obj->position.y       = -0x12C;
            obj->position.z       = -0x96;
            obj->value_44.half[1] = -0x18;
            obj->position.x       = 0;
            obj->value_44.half[0] = 0;
            obj->flags_0 |= 2;
            obj->position_fixed.v.x = obj->position.x << 16;
            obj->position_fixed.v.y = obj->position.y << 16;
            obj->position_fixed.v.z = obj->position.z << 16;
            break;
        case 0x6E:
            obj->value_44.half[0] = -0x18;
            // fall through
        case 0x50:
            obj->value_44.half[1] = 0;
            break;
    }
}

void func_80104740(STAGE_ROOM *wp)
{
    ST1A_OBJ *obj;

    obj = (ST1A_OBJ *)wp->child_24;
    switch (wp->frame_10)
    {
        case 0:
            obj->position.y           = -0x190;
            obj->position.z           = -0x50;
            obj->u_F8.part[0].value_3 = -1;
            obj->u_F8.part[2].value_3 = -1;
            obj->u_F8.part[3].value_3 = -1;
            obj->value_44.half[1]     = 4;
            obj->position.x           = 0;
            obj->value_44.half[0]     = 0;
            obj->flags_0 |= 2;
            obj->position_fixed.v.x = obj->position.x << 16;
            obj->position_fixed.v.y = obj->position.y << 16;
            obj->position_fixed.v.z = obj->position.z << 16;
            break;
        case 30:
            obj->value_44.half[1] = 0;
            break;
    }
}

void func_801047D0(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;

    switch (wp->routine_6)
    {
        case 0:
            func_80031A4C(wp->child_28);
            func_80031824(wp->child_24);
            Scene_obj_ent_open(&D_8012FFA0);
            wp->routine_6++;
            break;
        case 1:
            if (wp->frame_10 < 0x96)
            {
                pos.x = -0xF9;
                pos.y = -1;
                pos.z = -0x12;
                STAGE_CELL_TBL[Map_cell_get(&pos)].pos.x -= 2;
                pos.x = 0xF9;
                pos.y = -1;
                pos.z = -0x12;
                STAGE_CELL_TBL[Map_cell_get(&pos)].pos.x += 2;
            }
            else
            {
                wp->routine_6++;
            }
            break;
    }
}

void func_801048F8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 temp_a1;

    temp_a1 = wp->frame_10;
    child   = wp->child_24;
    switch (temp_a1)
    {
        case 0x0:
            wp->routine_6 = 0;
            return;
        case 0x96:
            child->value_44.words.fraction = 0x50;
            child->u_C.b.byte_C            = 1;
            child->u_C.b.byte_D            = 0x15;
            return;
    }
}

void func_8010493C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            wp->child_24->flags_0 &= ~2;
            func_80103B34(2, 0, -0xC1, 0x898, 0x800);
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.pos_438.z   = 0x898;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.fixed_428.z = 0x898 << 16;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.pos_438.x   = 0;
            STAGE_PL.fixed_428.x = 0;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_444   = 0;
            STAGE_PL.value_448   = 0x83;
            STAGE_PL.value_76    = 0;
            STAGE_PL.value_74    = 0;
            pl->flags_0 |= 3;
            STAGE_PL.flags_bd |= 0x10;
            func_80103A14(3);
            func_801039DC(3);
            break;
        case 0x3C:
            func_801039DC(6);
            break;
    }
    func_80103A4C();
    func_80103B9C(0x50);
}

void func_80104A80(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;
    STCOM_SVECTOR pos;

    obj = wp->child_24;
    if (wp->frame_10 == 0)
    {
        func_80103B34(0xB, 0, 0, 0, 0);
        obj->position.y       = -1;
        obj->position.z       = -0x15E;
        obj->u_C.b.byte_C     = 1;
        obj->u_C.b.byte_D     = 0x14;
        obj->position.x       = 0;
        obj->value_44.half[0] = 0;
        obj->flags_0 |= 2;
        obj->position_fixed.v.x = obj->position.x << 16;
        obj->position_fixed.v.y = obj->position.y << 16;
        obj->position_fixed.v.z = obj->position.z << 16;
    }
    pos.x = -0xF9;
    pos.y = -1;
    pos.z = -0x12;
    STAGE_CELL_TBL[Map_cell_get(&pos)].pos.x += 3;
    pos.x = 0xF9;
    pos.y = -1;
    pos.z = -0x12;
    STAGE_CELL_TBL[Map_cell_get(&pos)].pos.x -= 3;
}

void func_80104BAC(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            STAGE_PL.value_170 = 0;
            pl->flags_0 &= ~2;
            Obj_work_flag_change(0x7E, 0x80);
            func_8001E6C0(0, 0, 0);
            func_80103B34(0xF, 0, 0, 0, 0);
            D_800BC7F0  = D_8012FFB4;
            wp->tbl_A4  = D_80130000;
            wp->timer_C = 0;
            Scene_obj_ent_open(&D_8012FF64);
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                wp->routine_5++;
            }
            break;
        case 2:
            D_80139710 = 0;
            Cd_xa_play_id(0x20010021);
            wp->routine_5 = 0;
            wp->routine_6 = 0;
            wp->routine_7 = 0;
            wp->routine_4++;
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80104CE8(STAGE_ROOM *wp)
{
    sint32 flags;

    switch (wp->routine_5)
    {
        case 0:
            Sce_camera_update();
            if (func_8001D878() != 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_80130010;
                D_80139710 &= ~0x80;
                wp->tbl_A4 = D_80130498;
                wp->routine_5++;
            }
            break;
        case 1:
            wp->tbl_A4[1](wp);
            flags = D_80139710;
            flags &= 0x81;
            if (flags == 1)
            {
                D_80139710 |= 2;
                Fade_start(8);
                Obj_work_flag_change(0x17E, 0x80);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            Sce_camera_update();
            break;
        case 2:
            wp->tbl_A4[1](wp);
            Sce_camera_update();
            break;
        case 3:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            else
            {
                wp->tbl_A4[1](wp);
                if ((D_80139710 & 0x81) == 1)
                {
                    Fade_start(8);
                    Obj_work_flag_change(0x17E, 0x80);
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            Sce_camera_update();
            break;
    }
    if (func_8001DE84() != 0)
    {
        D_80139710 |= 1;
    }
    Sce_event_update();
}

void func_80104EC8(ST1A_ROOM_A0 *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_SVECTOR pos;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.pos_438.y   = -1;
                STAGE_PL.fixed_428.y = -1 << 16;
                STAGE_PL.pos_438.x   = 0;
                STAGE_PL.pos_438.z   = 0;
                STAGE_PL.fixed_428.x = 0;
                STAGE_PL.fixed_428.z = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0x800;
                STAGE_PL.value_448   = 0;
                STAGE_PL.value_168   = 0;
                STAGE_PL.value_169   = 0;
                pl->flags_0 |= 3;
                STAGE_PL.flags_bd |= 0x10;
                Cd_subcmd(0, 1, 0);
                if (D_80139710 & 2)
                {
                    Cd_read_comb(0xBF);
                }
                wp->routine_5++;
            }
            break;
        case 1:
            if (D_80139710 & 2)
            {
                wp->routine_5 = 2;
            }
            else
            {
                wp->routine_5 = 3;
            }
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(D_80139710 & 2))
            {
                Obj_work_flag_change(0x17E, 0x80);
            }
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            if (D_80139710 != 0)
            {
                Fade_start(0);
            }
            pos.x = -0x100;
            pos.y = 0;
            pos.z = 0xB00;
            Stage_idx_model_set(Stage_map_cell_get(2, &pos), 0x40A00);
            Stage_idx_model_set(Stage_map_cell_get(0xF, &pos), 0x40A00);
            pos.x = 0x100;
            pos.y = 0;
            pos.z = 0xB00;
            Stage_idx_model_set(Stage_map_cell_get(2, &pos), 0x40B00);
            Stage_idx_model_set(Stage_map_cell_get(0xF, &pos), 0x40B00);
            D_800C356C = -1;
            D_800C356E = 0x1A;
            D_800C356F = 0xF;
            D_800C3562 = -1;
            D_800C356A = 0x800;
            D_800C3560 = 0;
            D_800C3564 = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            wp->obj_A0 = func_8011F27C();
            Sound_call(0x2F, 1, 0);
            func_80042314(pl);
            wp->flags_0 = 0;
            break;
    }
}

void func_80105200(STAGE_ROOM *wp)
{
    D_80130508[wp->routine_4](wp);
}
