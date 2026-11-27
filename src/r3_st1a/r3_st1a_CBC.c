#include "common.h"
#include "st1a.h"

void func_80100CBC(void)
{
}

void func_80100CC4(void)
{
}

void func_80100CCC(void)
{
}

void func_80100CD4(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x58) == 0)
            {
                wp->routine_4 = 1;
            }
            else if (Sce_flag_test(0x6C) == 0)
            {
                wp->routine_4 = 2;
            }
            else
            {
                wp->routine_4 = 0xFF;
            }
            break;
        case 1:
            if (Sce_flag_test(0x58) != 0)
            {
                Sce_flag_on(0x58);
                func_8001DDE4(0x45);
                wp->routine_4 = 0xFF;
            }
            break;
        case 2:
            if (Sce_flag_test(0x6C) != 0)
            {
                Sce_flag_on(0x6C);
                Sound_fade_start(0x10);
                Fade_start(0xE);
                func_8001DDE4(0x46);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100DB8(void)
{
}

void func_80100DC0(STAGE_ROOM *wp)
{
    D_8012E94C[wp->routine_4](wp);
}

void func_80100DFC(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                Obj_work_flag_change(0x15E, 0x80);
                wp->reserved09[1]  = 0x80;
                D_801396F4         = Map_cell_get(&D_8012F708);
                D_801396F8         = STAGE_CELL_TBL[D_801396F4].pos.y;
                STAGE_PL.routine_0 = 3;
                STAGE_PL.routine_1 = 0;
                wp->routine_5++;
            }
            break;
        case 1:
            func_8001F580(0xBC, 1, 1);
            wp->routine_5++;
            // fall through
        case 2:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0      = D_8012EB4C;
            wp->tbl_A4      = D_8012F580;
            wp->timer_C     = 0;
            pl->routine_0   = 3;
            pl->routine_1   = 1;
            pl->pos_438.y   = -1;
            pl->fixed_428.y = -1 << 16;
            pl->value_442   = 0x800;
            pl->pos_438.x   = 0;
            pl->pos_438.z   = 0;
            pl->fixed_428.x = 0;
            pl->fixed_428.z = 0;
            pl->value_440   = 0;
            pl->value_444   = 0;
            pl->value_448   = 0x30;
            pl->flags_bd |= 0x10;
            Scene_obj_ent_open(D_8012E958);
            wp->routine_4 = 1;
            wp->routine_5 = 0;
            wp->routine_6 = 0;
            wp->routine_7 = 0;
            Sce_camera_update();
            Sce_event_update();
            break;
    }
}

void func_80100FC4(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
        case 2:
            wp->tbl_A4[1](wp);
            Sce_camera_update();
            break;
        case 1:
        run:
            wp->tbl_A4[1](wp);
            if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
            {
                Fade_start(8);
                wp->routine_4 = 2;
                wp->routine_5 = 0;
            }
            Sce_camera_update();
            break;
        case 3:
            if (wp->routine_8 != 0xFF)
            {
                goto run;
            }
            wp->routine_5 = 0;
            wp->routine_4++;
            Sce_camera_update();
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    Sce_event_update();
}

// Stores match; retail loads the shared constant 0x800 (and case 1's 1) earlier than GCC, which puts each right before its first use.
void func_801010E8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x156, 0x80);
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.pos_438.x   = 0;
                STAGE_PL.pos_438.y   = -1;
                STAGE_PL.pos_438.z   = 0x800;
                STAGE_PL.fixed_428.x = 0;
                STAGE_PL.fixed_428.y = -1 << 16;
                STAGE_PL.fixed_428.z = 0x800 << 16;
                STAGE_PL.value_444   = 0;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0x800;
                STAGE_PL.value_448   = 0;
                STAGE_PL.value_168   = 0;
                STAGE_PL.value_169   = 0;
                pl->be_flag |= TRANS;
                STAGE_PL.flags_bd |= 0x10;
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                Cd_subcmd(0, 1, 0);
                if (wp->reserved09[1] & 1)
                {
                    STAGE_CELL_TBL[D_801396F4].pos.y = D_801396F8;
                    Stage_idx_model_set(D_801396F4, 0x31500);
                }
                func_80042314(pl);
                wp->routine_5++;
            }
            break;
        case 1:
            D_800C356C = 2;
            D_800C356E = 0x1A;
            D_800C356F = 1;
            D_800C3562 = -1;
            D_800C3564 = 0x800;
            D_800C356A = 0x800;
            D_800C3560 = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 1;
            Sound_call(0x2D, 0, 0);
            wp->flags_0 = 0;
            break;
    }
}

void func_80101304(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_6++;
            }
            break;
        case 1:
            if (wp->frame_10 >= 0x96)
            {
                Cd_xa_play_id(0x20000017);
                wp->routine_6++;
            }
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->routine_5 = 1;
                wp->routine_6 = 0;
                wp->reserved09[1] &= 0x7F;
                Sce_event_next();
            }
            break;
    }
}

void func_801013D4(void)
{
}

void func_801013DC(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        Stage_idx_model_set(D_801396F4, 0x70000);
        for (i = 1; i < 11; i++)
        {
            Scene_obj_ent_open(&D_8012E958[i]);
        }
    }
}

void func_80101464(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->be_flag &= ~TRANS;
    }
}

void func_80101494(void)
{
}

void func_8010149C(void)
{
}

void func_801014A4(ST1A_ROOM *wp)
{
    STCOM_EFFECT *fx;
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 0x20; i++)
        {
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->be_flag = MOVE;
                fx->id      = 0x1C;
                fx->type    = 1;
                fx->value_C = 0;
                fx->value_D = i;
            }
        }
        wp->child[3]->be_flag &= ~TRANS;
        for (i = 0xB; i < 0xE; i++)
        {
            Scene_obj_ent_open(&D_8012E958[i]);
        }
    }
}

void func_8010158C(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 4; i < 10; i++)
        {
            wp->child[i]->be_flag &= ~TRANS;
        }
    }
}

void func_801015E4(void)
{
}

void func_801015EC(void)
{
}

void func_801015F4(void)
{
}

void func_801015FC(void)
{
}

void func_80101604(void)
{
}

void func_8010160C(ST1A_ROOM_LIFT *wp)
{
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        obj                     = wp->child_50;
        obj->position.y         = -1;
        obj->position.z         = -0xC0;
        obj->position_fixed.v.y = -1 << 16;
        obj->position.x         = 0;
        obj->position_fixed.v.x = 0;
        obj->position_fixed.v.z = -0xC0 << 16;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = 0;
        wp->routine_6           = 0;
    }
    switch (wp->routine_6)
    {
        case 0:
            if (wp->frame_10 == 0x96)
            {
                wp->routine_6++;
            }
            break;
        case 1:
            STAGE_CELL_TBL[D_801396F4].pos.y += 4;
            wp->slot_28->pos_38.y += 4;
            wp->slot_2C->pos_38.y += 4;
            wp->slot_4C->pos_38.y += 4;
            if (wp->frame_10 == 0x116)
            {
                wp->routine_6++;
            }
            break;
        case 2:
            wp->slot_28->be_flag &= ~TRANS;
            wp->slot_2C->be_flag &= ~TRANS;
            wp->slot_4C->be_flag &= ~TRANS;
            STAGE_CELL_TBL[D_801396F4].pos.y = D_801396F8;
            Stage_idx_model_set(D_801396F4, 0x31500);
            wp->routine_6++;
            break;
    }
}

void func_801017F4(void)
{
}

void func_801017FC(void)
{
}

void func_80101804(void)
{
}

void func_8010180C(void)
{
}

void func_80101814(void)
{
}

void func_8010181C(void)
{
}

void func_80101824(void)
{
}

void func_8010182C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.y         = -1;
        child->position.z         = -0x200;
        child->position_fixed.v.y = -0x10000;
        child->position_fixed.v.z = -0x02000000;
        child->position.x         = 0;
        child->position_fixed.v.x = 0;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x800;
        wp->routine_6             = 0;
    }
}

void func_80101884(void)
{
}

void func_8010188C(void)
{
}

void func_80101894(void)
{
}

void func_8010189C(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;
    sint8 i;

    if (wp->frame_10 == 0)
    {
        obj                     = wp->child_50;
        obj->position.y         = -1;
        obj->position.z         = 0x400;
        obj->position_fixed.v.y = 0xFFFF0000;
        obj->position.x         = 0;
        obj->position_fixed.v.x = 0;
        obj->position_fixed.v.z = 0x04000000;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = 0;
        for (i = 0xE; i < 0x12; i++)
        {
            Scene_obj_ent_open(&D_8012E958[i]);
        }
    }
}

void func_8010194C(void)
{
}

void func_80101954(ST1A_ROOM *wp)
{
    uint8 i;
    STAGE_OBJ *obj;
    STCOM_EFFECT *ep;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 4; i++)
        {
            obj = wp->child[i + 14];
            ep  = func_80031618();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = 0x1C;
                ep->type    = 3;
                ep->value_C = obj->work_id;
                ep->value_D = 0;
            }
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = 0x1C;
                ep->type    = 4;
                ep->value_C = obj->work_id;
                ep->value_D = i;
                ep->timer_E = 0;
            }
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = 0x1C;
                ep->type    = 4;
                ep->value_C = obj->work_id;
                ep->value_D = i;
                ep->timer_E = 1;
            }
        }
    }
    if (wp->frame_10 >= 5)
    {
        func_801022DC(wp, 0);
    }
}

void func_80101A8C(STAGE_ROOM *wp)
{
    if (wp->frame_10 >= 5)
    {
        func_801022DC(wp, 0);
    }
}

void func_80101AC0(STAGE_ROOM *wp)
{
    STCOM_EFFECT *ep;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            child       = wp->child_24;
            ep->be_flag = MOVE;
            ep->id      = 0x1C;
            ep->type    = 2;
            ep->value_C = child->work_id;
            ep->value_D = 0;
        }
    }
    func_801022DC(wp, 0);
}

void func_80101B38(STAGE_ROOM *wp)
{
    func_801022DC(wp, 1);
}

void func_80101B58(STAGE_ROOM *wp)
{
    func_801022DC(wp, 2);
}

void func_80101B78(STAGE_ROOM *wp)
{
    STCOM_EFFECT *ep;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            child       = wp->child_24;
            ep->be_flag = MOVE;
            ep->id      = 0x1C;
            ep->type    = 2;
            ep->value_C = child->work_id;
            ep->value_D = 1;
        }
    }
    func_801022DC(wp, 0);
}

void func_80101BF0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint16 temp_v0;

    child                     = wp->child_50;
    temp_v0                   = (uint16)child->position.z + 3;
    child->position.z         = temp_v0;
    child->position_fixed.v.z = temp_v0 << 0x10;
}

void func_80101C14(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->routine_6 = 0;
    }
    switch (wp->routine_6)
    {
        case 0:
            Obj_work_flag_change(0x156, 0x80);
            Cd_subcmd(0, 1, 0);
            wp->reserved09[1] |= 0x80;
            wp->routine_6++;
            break;
        case 1:
            func_8001F580(0xBD, 1, 1);
            wp->routine_5 = 2;
            wp->routine_6++;
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_6++;
            }
            break;
        case 3:
            if (wp->frame_10 >= 0x78)
            {
                Cd_xa_play_id(0x20000018);
                wp->routine_6++;
            }
            break;
        case 4:
            if (func_8001D878() != 0)
            {
                wp->routine_5 = 3;
                wp->routine_6 = 0;
                wp->reserved09[1] &= 0x7F;
                Sce_event_next();
            }
            break;
    }
}

void func_80101D40(STAGE_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 1)
    {
        for (i = 0; i < 7; i++)
        {
            Scene_obj_ent_open(&D_8012EAC0[i]);
        }
    }
}

void func_80101DB8(void)
{
}

void func_80101DC0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position.x         = -0x1EA;
        child->position.z         = -0x99C;
        child->position_fixed.v.x = -0x01EA0000;
        child->position_fixed.v.z = -0x099C0000;
        child->position.y         = -1;
        child->position_fixed.v.y = -0x10000;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x9C8;
        child                     = wp->child_2C;
        child->position.x         = -0x19E;
        child->position.z         = -0x950;
        child->position_fixed.v.x = -0x019E0000;
        child->position.y         = -1;
        child->position_fixed.v.y = -0x10000;
        child->position_fixed.v.z = -0x09500000;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0;
    }
}

void func_80101E54(ST1A_ROOM *wp)
{
    uint8 i;
    STAGE_OBJ *obj;
    STCOM_EFFECT *ep;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 4; i++)
        {
            obj = wp->child[i + 3];
            ep  = func_80031618();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = 0x1C;
                ep->type    = 3;
                ep->value_C = obj->work_id;
                ep->value_D = 0;
            }
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = 0x1C;
                ep->type    = 4;
                ep->value_C = obj->work_id;
                ep->value_D = i;
                ep->timer_E = 0;
            }
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = 0x1C;
                ep->type    = 4;
                ep->value_C = obj->work_id;
                ep->value_D = i;
                ep->timer_E = 1;
            }
        }
        child                     = wp->child[1];
        child->position.x         = 0x227;
        child->position.z         = -0x15A;
        child->position_fixed.v.x = 0x227 << 16;
        child->position_fixed.v.z = -0x15A << 16;
        child->position.y         = -1;
        child->position_fixed.v.y = -1 << 16;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x4AA;
        child                     = wp->child[2];
        child->position.x         = 0x182;
        child->position.z         = -0x300;
        child->position_fixed.v.x = 0x182 << 16;
        child->position_fixed.v.z = -0x300 << 16;
        child->position.y         = -1;
        child->position_fixed.v.y = -1 << 16;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x400;
    }
    func_801022DC(wp, 1);
}

void func_80101FFC(STAGE_ROOM *wp)
{
    if (wp->frame_10 < 0x55)
    {
        func_801022DC(wp, 1);
    }
}

void func_80102030(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        obj                     = wp->child_28;
        obj->position.x         = 0x300;
        obj->position.y         = -1;
        obj->position.z         = -0x100;
        obj->position_fixed.v.x = 0x03000000;
        obj->position_fixed.v.y = 0xFFFF0000;
        obj->position_fixed.v.z = 0xFF000000;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = 0x300;
        obj                     = wp->child_2C;
        obj->position.x         = 0x200;
        obj->position.y         = -1;
        obj->position.z         = -0x2C0;
        obj->position_fixed.v.x = 0x02000000;
        obj->position_fixed.v.y = 0xFFFF0000;
        obj->position_fixed.v.z = 0xFD400000;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = 0x500;
    }
}

void func_801020C4(ST1A_ROOM *wp)
{
    sint8 i;
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        obj                     = wp->child[1];
        obj->position.x         = -0xC0;
        obj->position.z         = -0x140;
        obj->position_fixed.v.x = -0xC0 << 16;
        obj->position_fixed.v.z = -0x140 << 16;
        obj->position.y         = -1;
        obj->position_fixed.v.y = -1 << 16;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = 0xE00;
        obj                     = wp->child[2];
        obj->position.x         = 0x3C;
        obj->position.z         = -0x200;
        obj->position_fixed.v.x = 0x3C << 16;
        obj->position_fixed.v.z = -0x200 << 16;
        obj->position.y         = -1;
        obj->position_fixed.v.y = -1 << 16;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = 0x800;
        for (i = 3; i < 7; i++)
        {
            wp->child[i]->be_flag &= ~TRANS;
        }
    }
}

void func_80102198(void)
{
}

void func_801021A0(void)
{
}

void func_801021A8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.y         = -1;
        child->position.z         = 0x200;
        child->position_fixed.v.y = -0x10000;
        child->position_fixed.v.z = 0x02000000;
        child->position.x         = 0;
        child->position_fixed.v.x = 0;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x800;
    }
}

void func_801021FC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position.x         = -0x1F;
        child->position.y         = -1;
        child->position.z         = -0x200;
        child->position_fixed.v.x = -0x1F0000;
        child->position_fixed.v.y = -0x10000;
        child->position_fixed.v.z = -0x02000000;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x800;
        child                     = wp->child_2C;
        child->position.x         = 0x1F;
        child->position.y         = -1;
        child->position.z         = -0x200;
        child->position_fixed.v.x = 0x1F0000;
        child->position_fixed.v.y = -0x10000;
        child->position_fixed.v.z = -0x02000000;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x800;
    }
}

void func_80102288(void)
{
}

void func_80102290(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0xDC)
    {
        Fade_start(0xA);
        wp->routine_2 |= 0x80;
    }
}

void func_801022DC(void *wp, sint32 arg)
{
    ST1A_TILE *tile;
    DR_MODE *mode;
    uint32 v;

    v = D_8012F710[arg][rand() & 7];
    if (v != 0)
    {
        tile = (ST1A_TILE *)*STAGE_PACKET_PTR;
        setlen(tile, 3);
        tile->code = 0x60;
        tile->w    = 0x140;
        tile->y0   = 0;
        tile->x0   = 0;
        tile->h    = 0xF0;
        tile->r0 = tile->g0 = tile->b0 = v & 0x7F;
        tile->code |= 2;
        mode = (DR_MODE *)++*STAGE_PACKET_PTR;
        SetDrawMode(mode, 0, 0, (((v >> 7) + 1) << 5) | 0xF, NULL);
        ++*STAGE_PACKET_PTR;
        addPrim(&Disp_env_ptr->ot_74, tile);
        addPrim(&Disp_env_ptr->ot_74, mode);
    }
}

void func_80102438(sint32 index)
{
    D_80139700.shape_0 = D_80139700.prev_1 = D_80139700.index_2 = 0;
    D_80139700.mouth_8                                          = D_8012F74C[index];
}

void func_80102470(sint32 index)
{
    D_80139700.shape_3 = D_80139700.prev_4 = D_80139700.index_5 = 0;
    D_80139700.eyes_C                                           = D_8012F794[index];
}

void func_801024A8(void)
{
    ST1A_PL_FACE *pl;
    ST1A_FACE2 *face;

    pl   = (ST1A_PL_FACE *)&Player_work;
    face = &D_80139700;
    if (face->mouth_8[face->index_2 + 1] != 0x7E)
    {
        if (face->mouth_8[face->index_2 + 1] == 0x7F)
        {
            face->index_2 = 0;
        }
        else
        {
            face->index_2++;
        }
    }
    face->prev_1 = face->shape_0 = face->mouth_8[face->index_2];
    if (face->eyes_C[face->index_5 + 1] != 0x7E)
    {
        if (face->eyes_C[face->index_5 + 1] == 0x7F)
        {
            face->index_5 = 0;
        }
        else
        {
            face->index_5++;
        }
    }
    face->prev_4 = face->shape_3 = face->eyes_C[face->index_5];
    pl->mouth_168                = face->shape_0;
    pl->eyes_169                 = face->shape_3;
}

void func_80102590(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 0x1A;
    D_800C356F = arg0;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_801025F4(sint32 x, sint32 y, sint16 radius, sint16 shade)
{
    ST1A_POLY_G3 *p;
    DR_MODE *mode;
    sint32 i;

    for (i = 0; i < 24; i++)
    {
        p = *ST1A_POLY_G3_PTR;
        setlen(p, 6);
        p->code = 0x30;
        SetSemiTrans(p, 1);
        p->x0 = x;
        p->y0 = y;
        p->x1 = x + (radius * rcos(i * 0xAA) >> 12);
        p->y1 = y + (radius * rsin(i * 0xAA) >> 12);
        p->x2 = x + (radius * rcos((i + 1) * 0xAA) >> 12);
        p->y2 = y + (radius * rsin((i + 1) * 0xAA) >> 12);
        p->r0 = shade;
        p->r1 = 0;
        p->r2 = 0;
        p->g0 = 0;
        p->g1 = 0;
        p->g2 = 0;
        p->b0 = 0;
        p->b1 = 0;
        p->b2 = 0;
        ++*ST1A_POLY_G3_PTR;
        addPrim(&Disp_env_ptr->ot_74, p);
    }
    mode = *ST1A_MODE_PTR;
    SetDrawMode(mode, 0, 0, 0x2F, NULL);
    ++*ST1A_MODE_PTR;
    addPrim(&Disp_env_ptr->ot_74, mode);
}

void func_8010282C(ST1A_ROOM_FX *wp, uint8 variant)
{
    STAGE_FX *ep;

    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag = MOVE;
        ep->id      = 0x20;
        ep->type    = variant;
        ep->flags |= 0x20;
        wp->fx_A0 = ep;
    }
}

void func_8010288C(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            Cd_read_comb(0x13);
            D_801396FC |= 0x80;
            wp->routine_5++;
            wp->routine_6++;
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                D_801396FC &= ~0x80;
                wp->routine_5++;
                wp->routine_6++;
            }
            break;
        case 2:
            if (wp->frame_10 >= 0xB4)
            {
                Cd_xa_play_id(0x2001001F);
                D_801396FC |= 0x80;
                wp->routine_5--;
                wp->routine_6++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                D_801396FC &= ~0x80;
                wp->routine_6 = 0;
                wp->routine_5++;
                Sce_event_next();
            }
            break;
    }
}

void func_801029E8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;
    sint32 temp_v1;

    temp_v1 = wp->frame_10;
    switch (temp_v1)
    {
        case 0:
            child            = wp->child_24;
            child->routine_1 = 0;
            return;
        case 30:
        case 40:
            other = wp->child_24;
            other->routine_1++;
            return;
    }
}

void func_80102A50(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;
    sint32 temp_v1;

    temp_v1 = wp->frame_10;
    switch (temp_v1)
    {
        case 0x0:
            child            = wp->child_24;
            child->routine_1 = 0;
            return;
        case 0x78:
            other = wp->child_24;
            other->routine_1++;
            return;
    }
}

void func_80102A9C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_50 *obj;
    sint32 i;

    pl = &STAGE_PL;
    switch (wp->frame_10)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                obj = func_80031734();
                if (obj != NULL)
                {
                    obj->id       = 0x37;
                    obj->type     = i + 4;
                    obj->pos_38.x = i * 0x400 - 0x200;
                    obj->pos_38.y = -0xC0;
                    obj->pos_38.z = -0x300;
                    obj->be_flag |= MOVE;
                }
            }
            pl->routine_0 = 3;
            pl->routine_1 = 1;
            pl->pos_438.y = -0xC1;
            pl->pos_438.z = 0x898;
            pl->value_442 = 0x800;
            pl->value_448 = 0x84;
            pl->pos_438.x = 0;
            pl->value_440 = 0;
            pl->value_444 = 0;
            pl->value_76  = 0;
            pl->value_74  = 0;
            pl->be_flag |= MOVE | TRANS;
            pl->flags_bd |= 0x10;
            pl->fixed_428.x = pl->pos_438.x << 16;
            pl->fixed_428.y = pl->pos_438.y << 16;
            pl->fixed_428.z = pl->pos_438.z << 16;
            func_80102470(0);
            func_80102438(0);
            break;
        case 0x50:
            func_80102438(3);
            STAGE_PL.value_448 = 0x85;
            break;
    }
    func_801024A8();
}

void func_80102C14(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            wp->child_24->routine_1 = 0;
            func_80102470(1);
            func_80102438(1);
            break;
        case 0x3C:
            wp->child_24->routine_1++;
            break;
        case 0x64:
            func_80102438(4);
            break;
    }
    func_801024A8();
}

void func_80102CA4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 0;
    }
}

void func_80102CC8(ST1A_ROOM_FX *wp)
{
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        func_80102590(0xE);
        D_800BBA90[0].flags_0 = 3;
        D_800BBA9E            = 0xE0;
        D_800BBA9C            = 0;
        D_800BBA94            = 0;
        D_800BBA98            = 0xE00000;
        func_8010282C(wp, 0);
        obj             = Scene_obj_ent_open(&D_8012F7B8);
        obj->rotation.z = 0x140;
        wp->child_24->be_flag &= ~TRANS;
        STAGE_PL_OBJ->be_flag &= ~TRANS;
    }
    else if (wp->frame_10 < 0x168)
    {
        D_800BBA98 += -43690.88512;
    }
}

void func_80102DD8(ST1A_ROOM_FX *wp)
{
    sint16 alpha;

    if (wp->frame_10 == 0)
    {
        func_80031988(wp->fx_A0);
        func_8010282C(wp, 1);
        wp->child_28->rotation.y = 0x80;
        D_800BBA90[0].flags_0    = 0;
        alpha                    = 0;
    }
    else if (wp->frame_10 < 0x20)
    {
        alpha = wp->frame_10 * 8;
    }
    else if (wp->frame_10 < 0x40)
    {
        alpha = 0xFF;
    }
    else if (wp->frame_10 < 0x60)
    {
        alpha = 0xFF - (wp->frame_10 - 0x40) * 8;
    }
    else
    {
        alpha = 0;
    }
    func_801025F4(0xAA, 0x6C, 0x1E, alpha);
}

void func_80102E8C(ST1A_ROOM_FX *wp)
{
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        func_80031988(wp->fx_A0);
        func_8010282C(wp, 2);
        wp->child_28->rotation.y = 0x800;
        obj                      = Scene_obj_ent_open(&D_8012F7CC);
        obj->u_C.b.work_0        = wp->child_28->work_id;
        obj->value_48.value      = 0;
    }
    else
    {
        wp->child_2C->value_48.value += 0x10;
    }
}

void func_80102F20(ST1A_ROOM_FX *wp)
{
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_28);
        func_80031A4C(wp->child_2C);
        func_80031988(wp->fx_A0);
        func_8010282C(wp, 3);
        obj                 = Scene_obj_ent_open(&D_8012F7E0);
        obj->routine_1      = 1;
        obj->value_48.value = 0;
        D_800BBAC8          = 3;
        D_800BBAD4          = 0;
        D_800BBAD6          = 0;
        D_800BBACC          = 0;
        D_800BBAD0          = 0;
    }
    else
    {
        wp->child_28->value_48.value += 0x30;
    }
}

void func_80102FEC(ST1A_ROOM_FX *wp)
{
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        func_80031A4C(wp->child_28);
        func_80031988(wp->fx_A0);
        obj                 = Scene_obj_ent_open(&D_8012F7F4);
        obj->routine_1      = 2;
        obj->value_48.value = 0;
        D_800BBAC8          = 0;
        D_800BBB00          = 3;
        D_800BBB0C          = 0;
        D_800BBB0E          = 0;
        D_800BBB04          = 0;
        D_800BBB08          = 0;
    }
    else
    {
        wp->child_28->value_48.value += 8;
    }
}

void func_801030A8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80031A4C(wp->child_28);
        D_800BBB00 = 0;
        func_80102590(10);
    }
}

void func_801030EC(ST1A_ROOM *wp)
{
    STAGE_OBJ *slot;

    if (wp->frame_10 == 0)
    {
        func_80102590(0xD);
        D_800BBB38 = 3;
        Scene_obj_ent_open(&D_8012F808[0]);
        Scene_obj_ent_open(&D_8012F808[1]);
        Scene_obj_ent_open(&D_8012F808[2]);
        Scene_obj_ent_open(&D_8012F808[3]);
        Scene_obj_ent_open(&D_8012F808[4]);
        Scene_obj_ent_open(&D_8012F808[5]);
        slot            = Scene_obj_ent_open(&D_8012F808[6]);
        slot->routine_1 = 3;
    }
}

void func_8010317C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80031A4C(wp->child_40);
    }
    else if (wp->frame_10 == 0x78)
    {
        Fade_start(8);
    }
}

void func_801031C8(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            D_800BBA90[3].flags_0 = 0;
            func_80031824(wp->child_28);
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            func_80031824(wp->child_34);
            func_80031824(wp->child_38);
            func_80031824(wp->child_3C);
            func_80102590(0xF);
            wp->child_24->be_flag |= TRANS;
            wp->child_24->routine_1  = 0;
            wp->child_24->position.y = -0x15;
            Fade_start(2);
            break;
        case 1:
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.y   = -1;
            STAGE_PL.pos_438.z   = 0x898;
            STAGE_PL.fixed_428.y = -1 << 16;
            STAGE_PL.fixed_428.z = 0x898 << 16;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.pos_438.x   = 0;
            STAGE_PL.fixed_428.x = 0;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_444   = 0;
            STAGE_PL.value_448   = 0x30;
            STAGE_PL.flags_bd |= 0x10;
            break;
    }
}

void func_80103330(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            pl->be_flag |= TRANS;
            func_80102470(2);
            func_80102438(2);
            wp->child_24->routine_1 = 0;
            break;
        case 0x78:
            func_80102438(5);
            break;
        case 0xF0:
            func_80102470(3);
            break;
        case 0x127:
            func_80102438(5);
            func_80102470(2);
            break;
    }
    func_801024A8();
}

void func_801033FC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;
    sint32 temp_v1;

    temp_v1 = wp->frame_10;
    switch (temp_v1)
    {
        case 0:
            child            = wp->child_24;
            child->routine_1 = 0;
            return;
        case 30:
            other = wp->child_24;
            other->routine_1++;
            return;
    }
}

void func_80103448(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            Sound_call(0x2E, 1, 0);
            pl->be_flag &= ~TRANS;
            Obj_work_flag_change(0x17E, 0x80);
            func_8001E6C0(0, 0, 0);
            func_80102590(2);
            Sce_event_timer_clear();
            D_800BC7F0  = D_8012F894;
            wp->tbl_A4  = D_8012FE48;
            wp->timer_C = 0;
            Scene_obj_ent_open(&D_8012F7A4);
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                Obj_work_flag_change(0x100, 0x80);
                wp->routine_5++;
            }
            break;
        case 2:
            D_801396FC    = 0;
            wp->routine_5 = 0;
            wp->routine_6 = 0;
            wp->routine_7 = 0;
            wp->routine_4++;
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_8010358C(STAGE_ROOM *wp)
{
    sint32 flags;

    switch (wp->routine_5)
    {
        case 0:
            wp->tbl_A4[1](wp);
            flags = D_801396FC;
            flags &= 0x81;
            if (flags == 1)
            {
                D_801396FC |= 2;
                Fade_start(8);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            Sce_camera_update();
            break;
        case 1:
            wp->tbl_A4[1](wp);
            Sce_camera_update();
            break;
        case 2:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            else
            {
                wp->tbl_A4[1](wp);
                if ((D_801396FC & 0x81) == 1)
                {
                    Fade_start(8);
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            Sce_camera_update();
            break;
    }
    if (func_8001DE84() != 0)
    {
        D_801396FC |= 1;
    }
    Sce_event_update();
}

void func_801036F4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                STAGE_PL.routine_0    = 3;
                STAGE_PL.routine_1    = 1;
                STAGE_PL.pos_438.y    = -1;
                STAGE_PL.fixed_428.y  = -1 << 16;
                D_800BBA90[0].flags_0 = 0;
                D_800BBAC8            = 0;
                D_800BBB00            = 0;
                D_800BBB38            = 0;
                STAGE_PL.pos_438.x    = 0;
                STAGE_PL.pos_438.z    = 0;
                STAGE_PL.fixed_428.x  = 0;
                STAGE_PL.fixed_428.z  = 0;
                STAGE_PL.value_444    = 0;
                STAGE_PL.value_440    = 0;
                STAGE_PL.value_442    = 0x800;
                STAGE_PL.value_448    = 0;
                STAGE_PL.value_168    = 0;
                STAGE_PL.value_169    = 0;
                STAGE_PL.flags_bd |= 0x10;
                Cd_subcmd(0, 1, 0);
                if (D_801396FC & 2)
                {
                    Obj_work_flag_change(0x17E, 0x80);
                    Cd_read_comb(0x13);
                }
                wp->routine_5++;
            }
            break;
        case 1:
            if (D_801396FC & 2)
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
            pl->be_flag |= MOVE | TRANS;
            if (!(D_801396FC & 2))
            {
                Obj_work_flag_change(0x17E, 0x80);
            }
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            if (D_801396FC != 0)
            {
                Fade_start(0);
            }
            D_800C356C = -1;
            D_800C3570 = 0xFF;
            D_800C356E = 0x1A;
            D_800C356F = 0xF;
            D_800C3562 = -1;
            D_800C3560 = 0;
            D_800C3564 = 0;
            D_800C356A = 0x800;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            func_8011BC80();
            func_80042314(pl);
            wp->flags_0 = 0;
            break;
    }
}

void func_801039A0(STAGE_ROOM *wp)
{
    D_8012FED8[wp->routine_4](wp);
}

void func_801039DC(sint32 index)
{
    D_80139714.shape_0 = D_80139714.prev_1 = D_80139714.index_2 = 0;
    D_80139714.mouth_8                                          = D_8012FF0C[index];
}

void func_80103A14(sint32 index)
{
    D_80139714.shape_3 = D_80139714.prev_4 = D_80139714.index_5 = 0;
    D_80139714.eyes_C                                           = D_8012FF50[index];
}

void func_80103A4C(void)
{
    ST1A_PL_FACE *pl;
    ST1A_FACE2 *face;

    pl   = (ST1A_PL_FACE *)&Player_work;
    face = &D_80139714;
    if (face->mouth_8[face->index_2 + 1] != 0x7E)
    {
        if (face->mouth_8[face->index_2 + 1] == 0x7F)
        {
            face->index_2 = 0;
        }
        else
        {
            face->index_2++;
        }
    }
    face->prev_1 = face->shape_0 = face->mouth_8[face->index_2];
    if (face->eyes_C[face->index_5 + 1] != 0x7E)
    {
        if (face->eyes_C[face->index_5 + 1] == 0x7F)
        {
            face->index_5 = 0;
        }
        else
        {
            face->index_5++;
        }
    }
    face->prev_4 = face->shape_3 = face->eyes_C[face->index_5];
    pl->mouth_168                = face->shape_0;
    pl->eyes_169                 = face->shape_3;
}

void func_80103B34(uint8 arg0, sint16 arg1, sint16 arg2, sint16 arg3, uint16 arg4)
{
    D_800C356C = -1;
    D_800C356E = 0x1A;
    D_800C356F = arg0;
    D_800C3560 = arg1;
    D_800C3562 = arg2;
    D_800C3564 = arg3;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C356A = (sint16)arg4;
}

void func_80103B9C(uint8 shade)
{
    ST1A_TILE *tile;
    DR_MODE *mode;

    tile = *ST1A_TILE_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->r0   = shade;
    tile->g0   = shade;
    tile->b0   = shade;
    tile->code |= 2;
    mode = (DR_MODE *)++*ST1A_TILE_PTR;
    SetDrawMode(mode, 0, 0, 0x4F, NULL);
    ++*ST1A_MODE_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
}

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
                        ep->be_flag         = MOVE | MODEL;
                        ep->id              = 0x80;
                        ep->type            = 2;
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
            pl->be_flag |= MOVE | TRANS;
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
            pl->be_flag &= ~MOVE;
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
            pl->be_flag |= MOVE;
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
        Player_work.be_flag &= ~TRANS;
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
            wp->child_28->be_flag &= ~TRANS;
            wp->child_24->be_flag &= ~TRANS;
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
            pl->be_flag |= MOVE | TRANS;
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
            Player_work.be_flag &= ~TRANS;
            wp->child_28->be_flag |= TRANS;
            obj->position.y       = -0x12C;
            obj->position.z       = -0x96;
            obj->value_44.half[1] = -0x18;
            obj->position.x       = 0;
            obj->value_44.half[0] = 0;
            obj->be_flag |= TRANS;
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
            obj->be_flag |= TRANS;
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
            child->u_C.b.work_0            = 1;
            child->u_C.b.work_1            = 0x15;
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
            wp->child_24->be_flag &= ~TRANS;
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
            pl->be_flag |= MOVE | TRANS;
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
        obj->u_C.b.work_0     = 1;
        obj->u_C.b.work_1     = 0x14;
        obj->position.x       = 0;
        obj->value_44.half[0] = 0;
        obj->be_flag |= TRANS;
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
            pl->be_flag &= ~TRANS;
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
                pl->be_flag |= MOVE | TRANS;
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

void func_8010523C(STAGE_ROOM *wp)
{
    D_80130514[wp->routine_4](wp);
}

void func_80105278(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_5++;
            }
            break;
        case 1:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                func_8001F580(0xC0, 1, 1);
                func_8005D7C0();
                wp->reserved09[1] = 0x80;
                wp->routine_5++;
            }
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x2000001F);
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                func_8001E6C0(0, 0, 0);
                D_800BC7F0      = D_80130674;
                wp->tbl_A4      = D_80131270;
                wp->timer_C     = 0;
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->pos_438.x   = 0x80;
                pl->pos_438.y   = -1;
                pl->pos_438.z   = 0x580;
                pl->fixed_428.x = 0x80 << 16;
                pl->fixed_428.y = -1 << 16;
                pl->fixed_428.z = 0x580 << 16;
                pl->value_442   = 0x800;
                pl->value_440   = 0;
                pl->value_444   = 0;
                pl->value_448   = 0x30;
                pl->value_170   = 0;
                pl->flags_bd |= 0x10;
                func_80106FBC(0);
                func_80106FF4(0);
                Sce_camera_update();
                Sce_event_update();
                wp->routine_5++;
            }
            break;
        case 4:
            Fade_start(6);
            func_8010702C();
            Sce_camera_update();
            Sce_event_update();
            wp->routine_4 = 1;
            wp->routine_5 = 0;
            wp->routine_6 = 0;
            wp->routine_7 = 0;
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
}

void func_80105488(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 1:
            wp->tbl_A4[1](wp);
            break;
        case 2:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4 = 2;
                wp->routine_5 = 0;
                break;
            }
            // fall through
        case 0:
            wp->tbl_A4[1](wp);
            if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
            {
                Fade_start(8);
                wp->routine_4 = 2;
                wp->routine_5 = 0;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8010702C();
    Sce_camera_update();
    Sce_event_update();
}

void func_80105598(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x156, 0x80);
                func_80042314(&Player_work);
                STAGE_PL.value_AC  = 0;
                STAGE_PL.value_168 = 0;
                STAGE_PL.value_169 = 0;
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                Cd_subcmd(0, 1, 0);
                Sound_work_view.volume_4 = 0x7F;
                wp->routine_5++;
            }
            break;
        case 1:
            D_800C356C = 2;
            D_800C356E = 0x1B;
            D_800C356F = 1;
            D_800C3560 = 0;
            D_800C3562 = 0;
            D_800C3564 = 0;
            D_800C356A = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            func_8001D974();
            wp->flags_0 = 0;
            break;
    }
}

void func_801056D4(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                wp->reserved09[1] &= 0x7F;
                wp->routine_6++;
            }
            break;
        case 1:
            if (wp->frame_10 == 0x5A)
            {
                func_80106FBC(0xD);
            }
            if (wp->frame_10 >= 0x78)
            {
                Scene_obj_ent_open(D_80130520);
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_8010578C(void)
{
}

void func_80105794(void)
{
}

void func_8010579C(STAGE_ROOM *wp)
{
    sint32 mask;

    mask = ~2; // retail ands with -3 held in a register
    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag &= mask;
        wp->child_24->be_flag &= mask;
        Scene_obj_ent_open(&D_80130534[0]);
        D_800BBB38 = 3;
        func_80106F38(0xD);
    }
    func_80107110(3);
}

void func_80105818(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        wp->child[1]->be_flag &= ~TRANS;
        for (i = 2; i < 11; i++)
        {
            Scene_obj_ent_open(&D_80130520[i]);
        }
        D_80139734    = 0;
        wp->routine_6 = 0;
    }
    if (wp->routine_6 == 0)
    {
        if (func_80107110(0) != 0)
        {
            wp->routine_6++;
        }
    }
    else
    {
        func_80107110(1);
    }
}

void func_801058F8(void)
{
    func_80107110(1);
}

void func_80105918(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 2; i < 11; i++)
        {
            wp->child[i]->be_flag &= ~TRANS;
        }
        D_800BBB38 = 0;
        Scene_obj_ent_open(&D_801305FC[0]);
        func_80106F38(0xC);
    }
}

void func_8010599C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_50;
        child->be_flag &= ~TRANS;
        pl = &Player_work;
        pl->be_flag |= TRANS;
        child = wp->child_24;
        child->be_flag |= TRANS;
        func_80106F38(0xF);
    }
}

void func_80105A10(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;

    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = 0x80;
            STAGE_PL.pos_438.y   = -1;
            STAGE_PL.pos_438.z   = 0x6C0;
            STAGE_PL.fixed_428.x = 0x80 << 16;
            STAGE_PL.fixed_428.y = -1 << 16;
            STAGE_PL.fixed_428.z = 0x6C0 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.value_444   = 0;
            STAGE_PL.flags_bd |= 0x10;
            func_80106FBC(0);
            func_80106FF4(1);
            obj                     = wp->child_24;
            obj->position.y         = 8;
            obj->position.z         = 0x740;
            obj->position_fixed.v.y = 8 << 16;
            obj->position_fixed.v.z = 0x740 << 16;
            obj->position.x         = 0x80;
            obj->position_fixed.v.x = 0x80 << 16;
            obj->rotation.z         = 0;
            obj->rotation.x         = 0;
            obj->rotation.y         = 0xCE0;
            break;
        case 10:
            STAGE_PL.value_448 = 0x80;
            func_80106FBC(1);
            func_80106FF4(0xB);
            break;
        case 25:
            func_80106FF4(1);
            break;
        case 30:
            STAGE_PL.value_448 = 0x81;
            func_80106FF4(0xB);
            break;
        case 60:
            func_80106FF4(1);
            break;
    }
}

void func_80105BA8(void)
{
}

void func_80105BB0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->be_flag &= ~TRANS;
    }
}

void func_80105BE0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->be_flag |= TRANS;
    }
}

void func_80105C10(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80106FBC(0);
            func_80106FF4(0);
            STAGE_PL.value_448 = 0x82;
            break;
        case 0x32:
            STAGE_PL.value_448 = 0x83;
            func_80106FBC(0xE);
            func_80106FF4(0xC);
            break;
        case 0xBE:
        case 0x15E:
            func_80106FBC(0xF);
            break;
        case 0x1F4:
            STAGE_PL.value_448 = 0x84;
            func_80106FBC(3);
            func_80106FF4(0xD);
            break;
        case 0x1FE:
            func_80106FF4(3);
            break;
        case 0x208:
            func_80106FF4(0xD);
            break;
        case 0x21E:
            func_80106FF4(3);
            break;
    }
}

void func_80105D30(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0x32:
            Player_work.value_448 = 0x85;
            func_80106FBC(0x16);
            func_80106FF4(0xE);
            break;
        case 0x78:
            Player_work.value_448 = 0x86;
            func_80106FBC(0x17);
            func_80106FF4(0x14);
            break;
    }
}

void func_80105DA0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        Scene_obj_ent_open(D_80130610);
    }
}

void func_80105DD8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    sint32 mask;

    if (wp->frame_10 == 0)
    {
        pl                 = &Player_work;
        STAGE_PL.value_448 = 0x30;
        mask               = ~2;
        pl->be_flag &= mask;
        wp->child_54->be_flag &= mask;
        wp->child_28->be_flag |= TRANS;
        D_800BBB38 = 3;
        func_80106F38(0xD);
    }
    func_80107110(3);
}

void func_80105E70(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 2; i < 11; i++)
        {
            wp->child[i]->be_flag |= TRANS;
        }
        D_80139734    = 0;
        wp->routine_6 = 0;
    }
    if (wp->routine_6 == 0 && func_80107110(2) != 0)
    {
        wp->routine_6++;
    }
}

void func_80105F18(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_80139734    = 0;
        wp->routine_6 = 0;
    }
    if ((wp->routine_6 == 0) && (func_80107110(2) != 0))
    {
        wp->routine_6++;
    }
}

void func_80105F88(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 1; i < 11; i++)
        {
            wp->child[i]->be_flag &= ~TRANS;
        }
        D_800BBA90[3].flags_0 = 0;
        wp->child[11]->be_flag |= TRANS;
        func_80106F38(0xC);
    }
}

void func_80106010(void)
{
}

void func_80106018(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child[0]);
        func_80031A4C(wp->child[1]);
        func_80031824(wp->child[2]);
        func_80031824(wp->child[3]);
        for (i = 4; i < 10; i++)
        {
            Close_SHL_WORK(wp->child[i]);
        }
        func_80031824(wp->child[10]);
        func_80031824(wp->child[11]);
        func_80031824(wp->child[12]);
        for (i = 0; i < 13; i++)
        {
            wp->child[i] = NULL;
        }
        Scene_obj_ent_open(&D_80130624);
        wp->child[0]->routine_1      = 2;
        wp->child[0]->value_48.value = 0x500;
        D_800BBA90[2].flags_0        = 3;
        D_800BBA90[2].pos_C.x        = 0;
        D_800BBA90[2].pos_C.y        = 0;
        D_800BBA90[2].fpos_4.x       = 0;
        D_800BBA90[2].fpos_4.y       = 0;
        Cd_subcmd(0, 1, 0);
        wp->routine_6 = 0;
        wp->flags_A |= 0x80;
        func_80106F38(0xE);
    }
    else
    {
        wp->child[0]->value_48.value -= 8;
    }
    switch (wp->routine_6)
    {
        case 0:
            if (wp->frame_10 == 0xA)
            {
                Cd_read_comb(0xC1);
                wp->routine_5 = 1;
                wp->routine_6++;
            }
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_6++;
            }
            break;
        case 2:
            if (wp->frame_10 >= 0xA0)
            {
                Cd_xa_play_id(0x20000021);
                wp->routine_6++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                wp->routine_5 = 2;
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_80106278(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 1:
            wp->reserved09[1] &= 0x7F;
            func_80031A4C(wp->child_24);
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = 0x80;
            STAGE_PL.pos_438.y   = -1;
            STAGE_PL.pos_438.z   = 0x640;
            STAGE_PL.fixed_428.x = 0x80 << 16;
            STAGE_PL.fixed_428.y = -1 << 16;
            D_800BBB00           = 0;
            STAGE_PL.fixed_428.z = 0x640 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0;
            STAGE_PL.value_444   = 0;
            pl->be_flag |= TRANS;
            STAGE_PL.flags_bd |= 0x10;
            func_80106FBC(4);
            func_80106FF4(4);
            STAGE_PL.value_448 = 0x87;
            Scene_obj_ent_open(&D_80130638);
            func_80106F38(0xF);
            break;
        case 0x2D:
            func_80106FF4(0xF);
            break;
        case 0x37:
            func_80106FF4(4);
            break;
        case 0x78:
            func_80106FBC(0x10);
            break;
    }
}

void func_80106400(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80106FBC(4);
            func_80106FF4(4);
            break;
        case 0x1E:
            func_80106FBC(0x10);
            break;
        case 0x2D:
            func_80106FF4(0xF);
            break;
        case 0x46:
            STAGE_PL.value_448 = 0x88;
            break;
        case 0x5F:
            func_80106FF4(4);
            break;
    }
}

void func_801064A8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->be_flag &= ~TRANS;
    }
}

void func_801064D8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            pl->be_flag |= TRANS;
            func_80106FBC(4);
            func_80106FF4(4);
            break;
        case 0x78:
        case 0x136:
        case 0x1EA:
            func_80106FBC(0x10);
            break;
        case 0x262:
            Player_work.value_448 = 0x89;
            func_80106FBC(0x11);
            func_80106FF4(0x10);
            break;
    }
}

void func_8010658C(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80106FBC(5);
            func_80106FF4(5);
            break;
        case 15:
            STAGE_PL.value_448 = 0x8A;
            func_80106FBC(0x12);
            break;
        case 20:
            func_80106FBC(0xC);
            func_80106FF4(6);
            break;
    }
}

void func_80106620(void)
{
}

void func_80106628(STAGE_ROOM *wp)
{
    sint32 mask;

    mask = ~2; // retail ands with -3 held in a register
    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag &= mask;
        wp->child_24->be_flag &= mask;
        Scene_obj_ent_open(&D_8013064C[0]);
        Scene_obj_ent_open(&D_8013064C[1]);
        func_80106F38(0x10);
    }
}

void func_801066A0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            wp->child_28->be_flag &= ~TRANS;
            wp->child_2C->be_flag &= ~TRANS;
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.z   = 0x640;
            STAGE_PL.pos_438.x   = 0x80;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.fixed_428.x = 0x80 << 16;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.fixed_428.z = 0x640 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0;
            STAGE_PL.value_444   = 0;
            pl->be_flag |= TRANS;
            STAGE_PL.flags_bd |= 0x10;
            func_80106FBC(6);
            func_80106FF4(7);
            STAGE_PL.value_448      = 0x80;
            obj                     = wp->child_24;
            obj->position.x         = 0x80;
            obj->position.y         = -0xC1;
            obj->position_fixed.v.x = 0x80 << 16;
            obj->position_fixed.v.y = -0xC1 << 16;
            obj->rotation.z         = 0;
            obj->position.z         = 0x5C0;
            obj->be_flag |= TRANS;
            obj->rotation.x         = 0;
            obj->position_fixed.v.z = 0x5C0 << 16;
            obj->rotation.y         = 0x800;
            func_80106F38(2);
            break;
        case 0x46:
        case 0xB4:
            func_80106FBC(0x13);
            break;
        case 0xFA:
            STAGE_PL.value_448 = 0x8B;
            break;
        case 0xFE:
            func_80106FBC(7);
            break;
        case 0x104:
            func_80106FBC(8);
            break;
        case 0x124:
            func_80106FF4(0x11);
            break;
        case 0x13B:
            func_80106FF4(7);
            break;
        case 0x14A:
            func_80106FBC(0x14);
            func_80106FF4(0x11);
            break;
        case 0x159:
            func_80106FF4(7);
            break;
        case 0x168:
            func_80106FF4(0x11);
            break;
        case 0x186:
            func_80106FF4(7);
            break;
    }
}

void func_8010693C(ST1A_ROOM *wp)
{
    sint32 mask;

    mask = ~2; // retail ands with -3 held in a register
    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag &= mask;
        wp->child[0]->be_flag &= mask;
        wp->child[1]->be_flag |= TRANS;
        wp->child[2]->be_flag |= TRANS;
        func_80106F38(0x10);
    }
}

void func_801069CC(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            func_8003187C(wp->child_28);
            func_80031824(wp->child_2C);
            wp->child_28 = NULL;
            wp->child_2C = NULL;
            pl->be_flag |= TRANS;
            func_80106FBC(6);
            func_80106FF4(8);
            STAGE_PL.value_448 = 0x80;
            wp->child_24->be_flag |= TRANS;
            func_80106F38(2);
            break;
        case 0x2D:
        case 0x4B:
            func_80106FF4(0x11);
            break;
        case 0x3C:
        case 0x5F:
            func_80106FF4(8);
            break;
        case 0x69:
            func_80106FBC(0x13);
            break;
    }
}

void func_80106AFC(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 1:
            func_80106FBC(9);
            func_80106FF4(9);
            STAGE_PL.value_448 = 0x80;
            break;
        case 0x14:
            STAGE_PL.value_448 = 0x8C;
            break;
    }
}

void func_80106B50(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag &= ~TRANS;
        child                     = wp->child_24;
        child->position.y         = -0xC1;
        child->position.z         = 0x620;
        child->position_fixed.v.y = 0xFF3F0000;
        child->position_fixed.v.z = 0x06200000;
        child->position.x         = 0;
        child->position_fixed.v.x = 0;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x800;
        child->be_flag |= TRANS;
    }
}

void func_80106BC8(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;

    pl = &STAGE_PL;
    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.pos_438.z   = 0x640;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.pos_438.x   = 0;
            STAGE_PL.fixed_428.x = 0;
            STAGE_PL.fixed_428.z = 0x640 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0;
            STAGE_PL.value_444   = 0;
            pl->be_flag |= TRANS;
            STAGE_PL.flags_bd |= 0x10;
            wp->routine_6 = 0;
            break;
        case 0xB:
            STAGE_PL.value_448 = 0x8D;
            break;
        case 0x14:
            func_80106FBC(0x14);
            func_80106FF4(0x12);
            break;
        case 0x1E:
            func_80106FBC(0xA);
            func_80106FF4(0xA);
            break;
        case 0x3E:
            STAGE_PL.value_448 = 0x8E;
            break;
        case 0x50:
            func_80106FBC(0x15);
            break;
        case 0x8C:
            func_80106FBC(0x15);
            func_80106FF4(0x13);
            break;
        case 0x98:
            func_80106FF4(0xA);
            break;
        case 0xA4:
            func_80106FBC(0xB);
            STAGE_PL.value_448 = 0x8F;
            break;
        case 0xA9:
            wp->routine_6 = 1;
            break;
    }
    if (wp->routine_6 == 1)
    {
        pl->pos_438.z -= 0x10;
        pl->fixed_428.z = pl->pos_438.z << 16;
        obj             = wp->child_24;
        obj->position.z -= 0x10;
        obj->position_fixed.v.z = obj->position.z << 16;
    }
}

void func_80106E1C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;

    pl  = &STAGE_PL;
    obj = wp->child_24;
    if (wp->frame_10 == 2)
    {
        STAGE_PL.value_448 = 1;
    }
    if (wp->frame_10 == 0x5A)
    {
        Fade_start(0xA);
        wp->reserved09[1] |= 0x80;
    }
    if (wp->frame_10 >= 0x5A && Sound_work_view.volume_4 > 0)
    {
        Sound_work_view.volume_4 -= 5;
        if (Sound_work_view.volume_4 < 0)
        {
            Sound_work_view.volume_4 = 0;
        }
    }
    pl->pos_438.z -= 0x10;
    pl->fixed_428.z         = pl->pos_438.z << 16;
    obj->position.y         = D_801315A0[(wp->frame_10 - 2) & 0xF] - 0xC1;
    obj->position_fixed.v.y = obj->position.y << 16;
    obj->position.z -= 0x10;
    obj->position_fixed.v.z = obj->position.z << 16;
}

void func_80106F38(sint32 index)
{
    D_800C356F = index;
    D_800C356C = -1;
    D_800C356E = 0x17;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C3560 = STAGE_PL.pos_438.x;
    D_800C3562 = STAGE_PL.pos_438.y;
    D_800C3564 = STAGE_PL.pos_438.z;
    D_800C356A = STAGE_PL.value_442;
}

void func_80106FBC(sint32 index)
{
    D_80139724.shape_8 = D_80139724.prev_9 = D_80139724.index_A = 0;
    D_80139724.mouth_0                                          = D_801314EC[index];
}

void func_80106FF4(sint32 index)
{
    D_80139724.shape_B = D_80139724.prev_C = D_80139724.index_D = 0;
    D_80139724.eyes_4                                           = D_8013154C[index];
}

void func_8010702C(void)
{
    STAGE_FACE2 *face;

    face = &D_80139724;
    if (face->mouth_0[face->index_A + 1] != 0x7E)
    {
        if (face->mouth_0[face->index_A + 1] == 0x7F)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_8 = face->mouth_0[face->index_A];
    face->prev_9  = face->shape_8;
    if (face->eyes_4[face->index_D + 1] != 0x7E)
    {
        if (face->eyes_4[face->index_D + 1] == 0x7F)
        {
            face->index_D = 0;
        }
        else
        {
            face->index_D++;
        }
    }
    face->shape_B = face->prev_C = face->eyes_4[face->index_D];
    STAGE_PL.value_168           = face->shape_8;
    STAGE_PL.value_169           = face->shape_B;
}

sint32 func_80107110(sint32 arg)
{
    ST1A_TILE *tile;
    DR_MODE *mode;
    sint32 done;

    tile = (ST1A_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->code |= 2;
    done = 0;
    switch (arg)
    {
        case 0:
            if (D_80139734 < 25)
            {
                tile->r0 = tile->g0 = tile->b0 = D_80139734 * 2;
            }
            else
            {
                done     = 1;
                tile->r0 = tile->g0 = tile->b0 = 0x32;
            }
            if (D_80139734 < 0xFF)
            {
                D_80139734++;
            }
            break;
        case 1:
            tile->r0 = tile->g0 = tile->b0 = 0x32;
            break;
        case 2:
            if (D_80139734 < 25)
            {
                tile->r0 = tile->g0 = tile->b0 = 0x32 - D_80139734 * 2;
            }
            else
            {
                done     = 1;
                tile->r0 = tile->g0 = tile->b0 = 0;
            }
            if (D_80139734 < 0xFF)
            {
                D_80139734++;
            }
            break;
        case 3:
            tile->r0 = tile->g0 = tile->b0 = 0x30;
            break;
    }
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    if (arg != 3)
    {
        SetDrawMode(mode, 0, 0, 0x4F, NULL);
    }
    else
    {
        SetDrawMode(mode, 0, 0, 0x2F, NULL);
    }
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
    return done;
}
