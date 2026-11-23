#include "common.h"
#include "st07.h"

// Installs the stage's slot routine tables.
void func_80100048(void)
{
    STAGE_TABLE_3C0 = D_801054D4;
    STAGE_TABLE_5A4 = D_80105584;
    STAGE_TABLE_10C = D_801055B4;
    STAGE_TABLE_48  = D_801055B8;
    STAGE_TABLE_24  = D_801055F0;
    STAGE_TABLE_50  = D_80105604;
}

// Sets up the current room: models, map, spawns.
void func_801000B0(void)
{
    STAGE_MAP_WORK *mw;
    void *spawns;

    mw = STAGE_MAP_WORK_PTR;
    Room_model_init(D_80105658[Game_work.value_51]);
    spawns    = D_80105728[Game_work.value_51];
    mw->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    mw->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    mw->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    mw->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = STAGE_MAP_TBL[Game_work.value_51].cells;
    mw->info  = STAGE_CELL_INFO;
    mw->exits = D_80105760[Game_work.value_51];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_801058C0[D_80105B00[Game_work.value_51]], D_80105780[Game_work.value_51]);
    func_8005DC10(0);
    func_8010020C();
}

void func_8010020C(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_8010021C(void)
{
    D_80105B40[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100270(STAGE_ROOM *wp)
{
    if ((*((sint8 *)&Game_work + 0x82) & 0x80) && wp->routine_4 == 0)
    {
        func_8001DDE4(0xA);
        wp->routine_4++;
    }
}

void func_801002CC(STAGE_ROOM *wp)
{
    sint32 id;

    if (wp->routine_4 == 0)
    {
        id = 0x16;
        if (STAGE_GAME_VALUE_52 == 6)
        {
            id = 0x24;
        }
        func_8001DDE4(id);
        wp->routine_4++;
    }
}

void func_80100330(STAGE_ROOM *wp)
{
    D_80105B80[wp->routine_4](wp);
}

void func_8010036C(STAGE_ROOM *wp)
{
    sint32 i;

    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0        = D_80105DD0;
            wp->tbl_A4        = D_80105E1C;
            wp->reserved09[1] = 0x80;
            wp->reserved09[2] = 0;
            wp->timer_C       = 0;
            Scene_obj_ent_open(&D_80105B8C);
            for (i = 0; i < 8; i++)
            {
                D_800BBA90[i].flags_0  = D_80106124[i].flags_0;
                D_800BBA90[i].value_20 = D_80106124[i].value_4;
                D_800BBA90[i].value_22 = D_80106124[i].value_6;
            }
            D_800BBA90[7].pos_C.y  = 0xF0;
            D_800BBA90[7].fpos_4.y = 0xF00000;
            D_80108C0C             = 0;
            Cd_xa_play_id(0x20000005);
            wp->routine_5++;
            break;
        case 1:
            wp->tbl_A4[1](wp);
            if (func_8001D878() != 0)
            {
                wp->routine_5++;
            }
            break;
        case 2:
            wp->tbl_A4[1](wp);
            if (wp->reserved09[2] == 10)
            {
                Fade_start(2);
            }
            if (wp->reserved09[2] == 0x1E)
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_80105E2C;
                wp->tbl_A4    = D_801060D4;
                wp->routine_4 = 1;
                wp->routine_5 = 0;
            }
            wp->reserved09[2]++;
            break;
    }
    if (D_800C0C2A & 8)
    {
        wp->reserved09[1] |= 1;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80100598(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            wp->tbl_A4[1](wp);
            if (D_80098A72 == 0)
            {
                wp->reserved09[1] &= 0x7F;
                wp->routine_5++;
            }
            break;
        case 1:
            if (wp->routine_8 == 0xFF)
            {
                Fade_start(0x14);
                wp->routine_4 = 2;
                wp->routine_5 = 0;
                wp->reserved09[1] |= 0x80;
            }
            else
            {
                wp->tbl_A4[1](wp);
                if ((wp->reserved09[1] & 1) && !(wp->reserved09[1] & 0x80))
                {
                    Fade_start(0xA);
                    wp->routine_4 = 2;
                    wp->routine_5 = 0;
                }
            }
            break;
    }
    if (D_800C0C2A & 8)
    {
        wp->reserved09[1] |= 1;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_801006D8(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x56, 0x80);
                func_8003697C();
                Cd_subcmd(0, 1, 0);
                wp->routine_5++;
            }
            if ((wp->reserved09[1] & 1) && !(wp->reserved09[1] & 0x80))
            {
                Sce_camera_update();
            }
            break;
        case 1:
            D_800A395C = 1;
            func_80039820();
            STAGE_GAME_FLAGS_82 &= 0x7F;
            wp->flags_0 = 0;
            D_80098AA8[0].routine_0++;
            D_80098AA8[0].routine_1 = 0;
            func_80012F78(D_80013420);
            break;
    }
}

void func_801007E0(void)
{
    if (D_80108C0C == 0xDE)
    {
        D_800BBA90[2].flags_0 = 0;
        D_800BBA90[4].flags_0 = 0;
        D_800BBA90[5].flags_0 = 0;
        D_800BBA90[6].flags_0 = 0;
    }
    D_80108C0C++;
}

void func_80100834(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_800BBA90[0].flags_0 = 0;
        D_800BBAC8            = 3;
        D_800BBB38            = 3;
        D_800BBC18            = 3;
    }
}

void func_8010086C(STAGE_ROOM *wp)
{
    STAGE_FX *ep;
    sint16 i;

    i = 0;
    if (wp->frame_10 == 0)
    {
        D_800BBB38 = 0;
        D_800BBC18 = 0;
    }
    if (wp->frame_10 == 0x82)
    {
        do
        {
            ep            = (STAGE_FX *)func_80031618();
            ep->flags_0   = 1;
            ep->kind_2    = 8;
            ep->x_1C      = -0x100;
            ep->y_1E      = -0x2A0 - i * 32;
            ep->z_20      = i * 0x3F + 0x118;
            ep->variant_3 = 0;
            ep->value_C   = 0;
            ep->timer_D   = 0;
            ep->routine_1 = 6 - i * 2;
            ep->flags_6 |= 0x20;
            i++;
        } while (i < 4);
    }
}

void func_80100944(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        i     = 1;
        entry = D_80105BA0;
        func_80031824(wp->child_24);
        D_800BBAC8 = 0;
        do
        {
            Scene_obj_ent_open(entry);
            i++;
            entry++;
        } while (i < 4);
        func_80100CD4(1);
    }
}

void func_801009B8(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    STAGE_FX *ep;
    STAGE_FX *fx;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 3; i++)
        {
            func_80031824((&wp->child_24)[i]);
        }
        for (i = 0, ep = D_800A3B40; i < 0x40; i++, ep++)
        {
            func_80031988(ep);
        }
        i     = 4;
        entry = D_80105BDC;
        do
        {
            Scene_obj_ent_open(entry);
            i++;
            entry++;
        } while (i < 7);
        func_80100CD4(2);
    }
    if (wp->frame_10 == 0x82)
    {
        fx            = (STAGE_FX *)func_80031618();
        fx->flags_0   = 1;
        fx->kind_2    = 8;
        fx->variant_3 = 1;
        fx->value_C   = 0;
        fx->timer_D   = 0;
        fx->x_1C      = -18;
        fx->y_1E      = -79;
        fx->z_20      = 200;
        fx->routine_1 = 8;
        fx->flags_6 |= 0x20;
        fx            = (STAGE_FX *)func_80031618();
        fx->flags_0   = 1;
        fx->kind_2    = 8;
        fx->variant_3 = 1;
        fx->value_C   = 0;
        fx->timer_D   = 0;
        fx->x_1C      = 28;
        fx->y_1E      = -79;
        fx->z_20      = 200;
        fx->routine_1 = 4;
        fx->flags_6 |= 0x20;
    }
}

void func_80100B14(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 3; i++)
        {
            func_80031824((&wp->child_24)[i]);
        }
        i     = 7;
        entry = D_80105C18;
        do
        {
            Scene_obj_ent_open(entry);
            i++;
            entry++;
        } while (i < 0xC);
        func_80100CD4(3);
    }
}

void func_80100B98(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    STAGE_FX *ep;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 5; i++)
        {
            func_80031824((&wp->child_24)[i]);
        }
        for (i = 0, ep = D_800A3B40; i < 0x40; i++, ep++)
        {
            func_80031988(ep);
        }
        D_800BBA90[0].flags_0 = 3;
        i                     = 0xC;
        entry                 = D_80105C7C;
        do
        {
            Scene_obj_ent_open(entry);
            i++;
            entry++;
        } while (i < 0xF);
        func_80100CD4(4);
    }
}

void func_80100C4C(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        i = 0xF;
        func_80031824(wp->child_24);
        func_80031824(wp->child_28);
        entry = D_80105CB8;
        func_80031824(wp->child_2C);
        do
        {
            Scene_obj_ent_open(entry);
            i++;
            entry++;
        } while (i < 0x1D);
    }
}

void func_80100CCC(void)
{
}

// Sets the script camera.
void func_80100CD4(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 7;
    D_800C356F = mode;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

// Sets the script camera.
void func_80100D38(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 7;
    D_800C356F = mode;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80100D9C(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;
    STAGE_OBJ *temp_v1_2;
    STAGE_OBJ *temp_v1_3;
    STAGE_OBJ *temp_v1_4;
    STAGE_OBJ *temp_v1_5;
    STAGE_OBJ *temp_v1_6;

    if (wp->frame_10 == 0)
    {
        func_80100D38(7);
        temp_v1              = wp->child_24;
        temp_v1->flags_0     = (uint8)temp_v1->flags_0 | 2;
        temp_v1_2            = wp->child_34;
        temp_v1_2->routine_1 = 1;
        temp_v1_2->routine_2 = 0;
        temp_v1_3            = wp->child_38;
        temp_v1_3->routine_1 = 2;
        temp_v1_3->routine_2 = 0;
        temp_v1_4            = wp->child_3C;
        temp_v1_4->routine_1 = 3;
        temp_v1_4->routine_2 = 0;
        temp_v1_5            = wp->child_40;
        temp_v1_5->routine_1 = 4;
        temp_v1_5->routine_2 = 0;
        temp_v1_6            = wp->child_44;
        temp_v1_6->routine_1 = 8;
        temp_v1_6->routine_2 = 0;
        D_800BBAB0           = -0x80;
        D_800BBB20           = -0x168;
        D_800BBB90           = -0x168;
        D_800BBBC8           = -0x168;
        D_800BBC00           = -0x168;
        D_800BBA90[0].flags_0 |= 3;
        D_800BBB00 |= 3;
        D_800BBB70 |= 3;
        D_800BBBA8 |= 3;
        D_800BBBE0 |= 3;
    }
}

void func_80100ED0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80100D38(5);
        wp->child_24->flags_0 &= 0xFD;
        // Signed here: the and takes -4, not 0xFC.
        *(sint8 *)&D_800BBA90[0].flags_0 &= ~3;
        *(sint8 *)&D_800BBB00 &= ~3;
        D_800BBB70 &= ~3;
        D_800BBBA8 &= ~3;
        D_800BBBE0 &= ~3;
    }
}

void func_80100F8C(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;
    STAGE_OBJ *child;
    STAGE_OBJ *obj;
    ST07_MOVER *mover;

    if (wp->frame_10 == 0)
    {
        func_80100D38(6);
        child               = wp->child_28;
        child->routine_1    = 1;
        child->routine_2    = 0;
        child->u_C.b.byte_C = 1;
        child->flags_0 |= 2;
        child            = wp->child_2C;
        child->routine_2 = 0;
        child->routine_1 = 0;
        child->flags_0 |= 2;
        obj            = wp->child_30;
        obj->routine_2 = 0;
        obj->routine_1 = 0;
        obj->flags_0 |= 2;
        wp->child_34->flags_0 |= 2;
        obj            = wp->child_38;
        obj->routine_1 = 2;
        obj->routine_2 = 0;
        obj->flags_0 |= 2;
        wp->child_3C->flags_0 |= 2;
        wp->child_40->flags_0 |= 2;
        wp->child_44->flags_0 |= 2;
        pos.x = 0xB8;
        pos.y = -0x6E;
        pos.z = 0x12C;
        func_80104E7C(&pos);
        pos.x = 0x46;
        pos.z = 0x10E;
        func_80104E7C(&pos);
        pos.x = 0x3F;
        pos.z = 0xB4;
        func_80104E7C(&pos);
        pos.z = 0x28;
        func_80104E7C(&pos);
        pos.x = 0xC8;
        pos.z = 0x8C;
        func_80104E7C(&pos);
        mover            = (ST07_MOVER *)wp->child_48;
        mover->pos_38.x  = 0xF0;
        mover->pos_38.y  = -0x46;
        mover->routine_1 = 2;
        mover->pos_38.z  = 0x7C;
    }
    if (wp->frame_10 == 0x1E)
    {
        child               = wp->child_28;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 0x5A)
    {
        obj            = wp->child_40;
        obj->routine_1 = 4;
        obj->routine_2 = 0;
    }
}

void func_8010117C(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;
    STAGE_OBJ *temp_v1_2;

    if (wp->frame_10 == 0)
    {
        temp_v1            = wp->child_28;
        temp_v1->routine_1 = 2;
        temp_v1->routine_2 = 0;
    }
    if (wp->frame_10 == 0x96)
    {
        temp_v1_2            = wp->child_28;
        temp_v1_2->routine_1 = 3;
        temp_v1_2->routine_2 = 0;
    }
}

void func_801011C4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child->flags_0   = (uint8)child->flags_0 | 2;
    }
    if (wp->frame_10 == 0xA)
    {
        other            = wp->child_38;
        other->routine_2 = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        other            = wp->child_40;
        other->routine_1 = 4;
        other->routine_2 = 0;
    }
    if (wp->frame_10 == 0x41)
    {
        other            = wp->child_34;
        other->routine_1 = 1;
        other->routine_2 = 0;
    }
}

void func_80101258(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;
    STAGE_OBJ *temp_v1_2;

    if (wp->frame_10 == 0)
    {
        temp_v1            = wp->child_28;
        temp_v1->routine_1 = 4;
        temp_v1->routine_2 = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        temp_v1_2            = wp->child_28;
        temp_v1_2->routine_1 = 5;
        temp_v1_2->routine_2 = 0;
    }
}

void func_801012A0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    ST07_MOVER *mover;

    if (wp->frame_10 == 0)
    {
        wp->child_3C->value_110 = 10;
        child                   = wp->child_44;
        child->u_C.b.byte_C     = 1;
        child->routine_1        = 6;
        child->routine_2        = 0;
        mover                   = (ST07_MOVER *)wp->child_48;
        mover->pos_38.x         = 0x180;
        mover->pos_38.y         = -200;
        mover->pos_38.z         = 0;
        mover->routine_1        = 0;
    }
    if (wp->frame_10 == 30)
    {
        mover            = (ST07_MOVER *)wp->child_48;
        mover->pos_38.x  = -0x80;
        mover->pos_38.y  = -200;
        mover->pos_38.z  = 0;
        mover->routine_1 = 1;
        mover->routine_2 = 0;
    }
    if (wp->frame_10 == 40)
    {
        child               = wp->child_44;
        child->value_110    = 9;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 60)
    {
        child            = wp->child_38;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
}

void func_8010136C(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    sint32 i;

    func_8001E6C0(0, 0, 0);
    i          = 0;
    entry      = D_80106164;
    D_800BC7F0 = D_8010622C;
    wp->tbl_A4 = D_80106354;
    do
    {
        Scene_obj_ent_open(entry);
        i++;
        entry++;
    } while (i < 0xA);
}

void func_801013F0(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101430(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                pl->flags_0 &= 0xFC;
                Cd_xa_play_id(0x20000008);
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x19;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                Fade_start(2);
                wp->routine_4++;
            }
            break;
        case 3:
            func_8010136C(wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(10);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_801013F0(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 5 && D_80098A72 == 0)
            {
                D_800C356C = 2;
                D_800C356E = 6;
                if (func_8003B2D4(6, 0x205) == 3)
                {
                    D_800C356F = 1;
                }
                else
                {
                    D_800C356F = 4;
                }
                D_800C3564  = -0x1C2;
                D_800C356A  = 0x800;
                D_800C3571  = 0xFF;
                D_800C3560  = 0;
                D_800C3562  = 0;
                D_800C356D  = 0;
                D_800C3570  = 2;
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                pl->flags_0 |= 1;
                func_80042314(pl);
                Sce_flag_on(0x19);
            }
            break;
    }
}

// Sets the script camera.
void func_80101678(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 7;
    D_800C356F = mode;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_801016DC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_80101678(7);
        child            = wp->child_24;
        child->flags_0   = (uint8)child->flags_0 | 2;
        child            = wp->child_34;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_38;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_3C;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_40;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_44;
        child->routine_1 = 1;
        child->routine_2 = 0;
        D_800BBAB0       = -0x80;
        D_800BBB20       = -0x168;
        D_800BBB90       = -0x168;
        D_800BBBC8       = -0x168;
        D_800BBC00       = -0x168;
        D_800BBA90[0].flags_0 |= 3;
        D_800BBB00 |= 3;
        D_800BBB70 |= 3;
        D_800BBBA8 |= 3;
        D_800BBBE0 |= 3;
    }
}

void func_80101810(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80101678(5);
        wp->child_24->flags_0 &= 0xFD;
        // Signed here: the and takes -4, not 0xFC.
        *(sint8 *)&D_800BBA90[0].flags_0 &= ~3;
        *(sint8 *)&D_800BBB00 &= ~3;
        D_800BBB70 &= ~3;
        D_800BBBA8 &= ~3;
        D_800BBBE0 &= ~3;
    }
}

void func_801018CC(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_80101678(6);
        child               = wp->child_28;
        child->routine_1    = 6;
        child->routine_2    = 0;
        child->u_C.b.byte_C = 1;
        child->flags_0 |= 2;
        child               = wp->child_2C;
        child->routine_1    = 2;
        child->routine_2    = 0;
        child->u_C.b.byte_C = 1;
        child->flags_0 |= 2;
        wp->child_30->flags_0 |= 2;
        wp->child_34->flags_0 |= 2;
        wp->child_38->flags_0 |= 2;
        wp->child_3C->flags_0 |= 2;
        wp->child_40->flags_0 |= 2;
        wp->child_44->flags_0 |= 2;
        pos.x = 0xB8;
        pos.y = -0x6E;
        pos.z = 0x12C;
        func_80104E7C(&pos);
        pos.x = 0x46;
        pos.z = 0x10E;
        func_80104E7C(&pos);
        pos.x = 0x3F;
        pos.z = 0xB4;
        func_80104E7C(&pos);
        pos.z = 0x28;
        func_80104E7C(&pos);
        pos.x = 0xC8;
        pos.z = 0x8C;
        func_80104E7C(&pos);
    }
}

void func_80101A54(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 0x50)
    {
        child            = wp->child_28;
        child->routine_1 = 7;
        child->routine_2 = 0;
    }
}

void func_80101A98(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_2C;
        child->routine_1 = 3;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x140)
    {
        child            = wp->child_2C;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

void func_80101AFC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_30;
        child->flags_0 &= 0xFD;
        child               = wp->child_28;
        child->routine_1    = 8;
        child->routine_2    = 0;
        child->u_C.b.byte_C = 1;
        child               = wp->child_2C;
        child->routine_1    = 5;
        child->routine_2    = 0;
    }
    child = wp->child_2C;
    if (*child->anim_98 == 9)
    {
        child               = wp->child_28;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 0xA)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_C = 1;
    }
    if (wp->frame_10 == 0xC1)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_C = 0;
    }
}

void func_80101BB8(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    if (wp->frame_10 == 0)
    {
        temp_v1            = wp->child_2C;
        temp_v1->routine_1 = 6;
        temp_v1->routine_2 = 0;
    }
}

void func_80101BE0(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    if (wp->frame_10 == 0)
    {
        temp_v1            = wp->child_28;
        temp_v1->routine_1 = 9;
        temp_v1->routine_2 = 0;
    }
}

void func_80101C08(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    if (wp->frame_10 == 0)
    {
        temp_v1            = wp->child_28;
        temp_v1->routine_1 = 0xA;
        temp_v1->routine_2 = 0;
    }
}

void func_80101C30(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0xB;
        child->routine_2 = 0;
        other            = wp->child_30;
        other->flags_0 |= 2;
        other               = wp->child_38;
        other->rotation.y   = 0x955;
        other               = wp->child_3C;
        other->rotation.y   = 0x555;
        child               = wp->child_2C;
        child->u_C.b.byte_C = 1;
        child->routine_1    = 7;
        child->routine_2    = 0;
    }
    if (wp->frame_10 == 0x78)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_C = 0;
        other               = wp->child_34;
        other->value_110    = 9;
        other->routine_1    = 7;
        other->routine_2    = 0;
    }
    if (wp->frame_10 == 0x7B)
    {
        other            = wp->child_38;
        other->value_110 = 9;
        other->routine_1 = 7;
        other->routine_2 = 0;
        other            = wp->child_3C;
        other->value_110 = 9;
        other->routine_1 = 7;
        other->routine_2 = 0;
    }
    if (wp->frame_10 == 0x81)
    {
        other            = wp->child_40;
        other->value_110 = 9;
        other->routine_1 = 7;
        other->routine_2 = 0;
    }
    if (wp->frame_10 == 0x83)
    {
        other            = wp->child_44;
        other->value_110 = 9;
        other->routine_1 = 7;
        other->routine_2 = 0;
    }
}

void func_80101D5C(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    sint32 i;

    func_8001E6C0(0, 0, 0);
    i          = 0;
    entry      = D_80106394;
    D_800BC7F0 = D_80106448;
    wp->tbl_A4 = D_801065E4;
    do
    {
        Scene_obj_ent_open(entry);
        i++;
        entry++;
    } while (i < 0xA);
}

void func_80101DE0(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101E20(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                pl->flags_0 &= 0xFC;
                Cd_xa_play_id(0x20000011);
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x19;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                Fade_start(2);
                wp->routine_4++;
            }
            break;
        case 3:
            func_80101D5C(wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(10);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80101DE0(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 5 && D_80098A72 == 0)
            {
                D_800C356C  = 2;
                D_800C356E  = 0xD;
                D_800C3560  = 0x708;
                D_800C3562  = -0x81;
                D_800C3564  = 0x50;
                D_800C356A  = 0x800;
                D_800C356F  = 0;
                D_800C356D  = 0;
                D_800C3571  = 0xFF;
                D_800C3570  = 2;
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                pl->flags_0 |= 1;
                func_80042314(&Player_work);
                Sce_flag_on(0x54);
            }
            break;
    }
}

void func_8010205C(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_8010212C(wp);
        wp->routine_0++;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_8010663C[wp->u_C.b.byte_C](wp);
}

void func_8010212C(STAGE_OBJ *wp)
{
    sint16 y;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    if (wp->u_E.b.byte_E == 1)
    {
        wp->scale.words[0] = 0x4000400;
        wp->scale.words[1] = 0x400;
    }
    else
    {
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
    }
    if (wp->u_E.b.byte_F == 1)
    {
        wp->scale.v.pad = 0x318C;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    wp->value_78           = 0;
    y                      = wp->position.y + Obj_ceiling_height_get(wp);
    wp->position.y         = y;
    wp->routine_1          = 0;
    wp->position_fixed.v.y = y << 16;
}

void func_801021DC(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
        return;
    }
    func_80032488(wp);
}

void func_80102238(STAGE_OBJ *wp)
{
    sint32 size;

    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    size = 0x28;
    if (wp->scale.v.x == 0x400)
    {
        size = 0x50;
    }
    Model_Shadow_Trans(wp, size, 0x200, 0);
}

void func_801022B8(STAGE_OBJ *wp)
{
    if (STAGE_SCENE_WORD(0x10) < 0x14)
    {
        wp->position.z -= 3;
        wp->position_fixed.v.z += -0x39581;
    }
    else if (STAGE_SCENE_WORD(0x10) < 0x28)
    {
        wp->position.x++;
        wp->position.z--;
        wp->position_fixed.v.x += 0x19581;
        wp->position_fixed.v.z -= 0x19581;
    }
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_8010239C(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, 0x80, 0, 0);
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_8010241C(STAGE_OBJ *wp)
{
    if (STAGE_SCENE_WORD(0x10) < 0x14)
    {
        wp->position.z -= 3;
        wp->position_fixed.v.z += -0x39581;
        wp->position.x -= 3;
        wp->position_fixed.v.x += -0x39581;
    }
    else if (STAGE_SCENE_WORD(0x10) < 0x28)
    {
        wp->position.z--;
        wp->position_fixed.v.z += -0x19581;
    }
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x50, 0x200, 0);
}

void func_80102500(STAGE_OBJ *wp)
{
    if (STAGE_SCENE_WORD(0x10) >= 0x4C)
    {
        Obj_pos_set(wp, 0x100, 0, 0);
    }
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x50, 0x200, 0);
}

void func_80102590(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else if (STAGE_SCENE_PTR->value_10 > 0x50)
    {
        if (STAGE_SCENE_PTR->value_10 < 0x7D)
        {
            Obj_pos_set(wp, 0x80, 0, 0);
            func_80032488(wp);
        }
        else if (STAGE_SCENE_PTR->value_10 < 0x8B)
        {
            Obj_pos_set(wp, 0x80, 0, 0);
            if (STAGE_SCENE_PTR->value_10 == 0x7D)
            {
                func_800322A8(wp, 0x13, 0);
            }
            else
            {
                func_80032488(wp);
            }
        }
        else
        {
            func_80032488(wp);
        }
    }
    else
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_80102678(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, 0x40, 0, 0);
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, wp->u_C.b.byte_D, 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_801026F8(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0, 0);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
    func_80102A24(wp);
}

void func_80102760(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_801027AC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801027F8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->value_110 = 9;
        wp->value_100 = 0xC;
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_80102854(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->value_110 = 9;
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_801028A8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_801028F4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80102940(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_8010298C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        wp->routine_2++;
    }
}

void func_801029D8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        wp->routine_2++;
    }
}

void func_80102A24(STAGE_OBJ *wp)
{
    D_801066A0[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    if (wp->u_C.b.byte_C == 0)
    {
        func_80032488(wp);
    }
}

void func_80102A90(STAGE_EFFECT *wp)
{
    func_80031824(wp);
}

void func_80102AB0(STAGE_OBJ *wp)
{
    D_801066C4[wp->routine_0](wp);
}

void func_80102AEC(STAGE_OBJ *wp)
{
    D_801066D0[wp->variant_3](wp);
}

void func_80102B28(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
        return;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    func_80032488(wp);
}

void func_80102C18(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0, 0);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
    func_80102CCC(wp);
}

void func_80102C80(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_80102CCC(STAGE_OBJ *wp)
{
    D_801066D4[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_80102D28(STAGE_EFFECT *wp)
{
    func_8003187C(wp);
}

void func_80102D48(STAGE_OBJ *wp)
{
    D_801066D8[wp->routine_0](wp);
}

void func_80102D84(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->position.y += Obj_ceiling_height_get(wp);
        wp->position_fixed.v.y = wp->position.y << 16;
        func_800322A8(wp, 0x13, 0);
        wp->routine_0++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80102EA8(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->position.y += Obj_ceiling_height_get(wp);
        wp->position_fixed.v.y = wp->position.y << 16;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80102FCC(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0, 0);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
    func_80103080(wp);
}

void func_80103034(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_80103080(STAGE_OBJ *wp)
{
    D_801066E4[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_801030DC(STAGE_EFFECT *wp)
{
    func_8003187C(wp);
}

void func_801030FC(STAGE_OBJ *wp)
{
    D_801066E8[wp->routine_0](wp);
}

void func_80103138(STAGE_OBJ *wp)
{
    D_80108C14[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(D_80108C10[0]->id, 0x33, 0x37, 5));
}

void func_80103194(STAGE_OBJ *wp)
{
    D_80108C1C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(D_80108C18[0]->id, 0x33, 0x37, 5));
}

void func_801031F0(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_80108C10_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80108C10[0] += count;
            func_80103138(wp);
        }
        else if (++D_80108C14[0] == p->count)
        {
            D_80108C10_S = p + 1;
            func_80103138(wp);
        }
    }
    p     = D_80108C18_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80108C18[0] += count;
            func_80103194(wp);
        }
        else if (++D_80108C1C[0] == p->count)
        {
            D_80108C18_S = p + 1;
            func_80103194(wp);
        }
    }
}

void func_80103318(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80108C20.cue_0->u.end != 0xFF && D_80108C20.cue_0->u.scene == scene->u_8.value_8 && D_80108C20.cue_0->line == scene->value_1C)
    {
        D_80108C10[0] = D_80106720[D_80108C20.cue_0->index];
        func_80103138(wp);
        D_80108C20.cue_0++;
    }
    if (D_80108C20.cue_4->u.end != 0xFF && D_80108C20.cue_4->u.scene == scene->u_8.value_8 && D_80108C20.cue_4->line == scene->value_1C)
    {
        D_80108C18[0] = D_801067F4[D_80108C20.cue_4->index];
        func_80103194(wp);
        D_80108C20.cue_4++;
    }
    func_801031F0(wp);
}

void func_80103460(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0, 0);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    if (STAGE_GAME_VALUE_52 == 6)
    {
        D_80108C20.cue_0 = D_8010687C;
        D_80108C20.cue_4 = D_801068AC;
    }
    else
    {
        D_80108C20.cue_0 = D_8010682C;
        D_80108C20.cue_4 = D_80106844;
    }
    wp->routine_0++;
    func_8010377C(wp);
}

void func_8010351C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_80103568(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801035B4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80103600(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_8010364C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_80103698(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_801036E4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80103730(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_8010377C(STAGE_OBJ *wp)
{
    D_801068E8[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    if (wp->u_C.b.byte_C == 0)
    {
        func_80032488(wp);
    }
    func_80103318(wp);
}

void func_801037F0(STAGE_EFFECT *wp)
{
    func_8003187C(wp);
}

void func_80103810(STAGE_OBJ *wp)
{
    D_80106908[wp->routine_0](wp);
}

void func_8010384C(STAGE_OBJ *wp)
{
    ST07_FACE *face;

    face = (ST07_FACE *)&wp->u_4E0.face;
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->position.y += Obj_ceiling_height_get(wp);
        wp->position_fixed.v.y = wp->position.y << 16;
        func_800322A8(wp, 0, 0);
        func_80103A24(wp, face, 0);
        wp->routine_0++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        if (STAGE_SCENE_BYTE(8) == 4)
        {
            if (STAGE_SCENE_BYTE(9) == 1)
            {
                if (STAGE_SCENE_WORD(0x10) == 0xA)
                {
                    func_80103A24(wp, face, 2);
                }
                else if (STAGE_SCENE_WORD(0x10) == 0x5A)
                {
                    func_80103A24(wp, face, 0);
                }
            }
            else if (STAGE_SCENE_BYTE(9) == 2)
            {
                if (STAGE_SCENE_WORD(0x10) == 1)
                {
                    func_80103A24(wp, face, 2);
                }
                else if (STAGE_SCENE_WORD(0x10) == 0x32)
                {
                    func_80103A24(wp, face, 1);
                }
            }
        }
        func_80032488(wp);
    }
    func_80103A6C(wp, face);
}

void func_80103A24(STAGE_OBJ *wp, ST07_FACE *face, sint32 index)
{
    face->index_A = 0;
    face->shape_8 = 0;
    face->index_D = 0;
    face->shape_B = 0;
    face->prev_C  = -1;
    face->prev_9  = -1;
    face->mouth_0 = D_80106944[index];
    face->eyes_4  = D_80106950[index];
}

void func_80103A6C(STAGE_OBJ *wp, ST07_FACE *face)
{
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
    if (face->shape_8 != face->prev_9)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_8, 0x2A, 0x40, 6));
    }
    face->prev_9 = face->shape_8;
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
    face->shape_B = face->eyes_4[face->index_D];
    if (face->shape_B != face->prev_C)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_B, 0x2A, 0x40, 6));
    }
    face->prev_C = face->shape_B;
}

void func_80103BB4(STAGE_OBJ *wp)
{
    D_80108C2C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80108C28[0]->id, 0x2A, 0x40, 6));
}

void func_80103C10(STAGE_OBJ *wp)
{
    D_80108C34[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80108C30[0]->id, 0x2A, 0x40, 6));
}

void func_80103C6C(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_80108C28_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80108C28[0] += count;
            func_80103BB4(wp);
        }
        else if (++D_80108C2C[0] == p->count)
        {
            D_80108C28_S = p + 1;
            func_80103BB4(wp);
        }
    }
    p     = D_80108C30_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80108C30[0] += count;
            func_80103C10(wp);
        }
        else if (++D_80108C34[0] == p->count)
        {
            D_80108C30_S = p + 1;
            func_80103C10(wp);
        }
    }
}

void func_80103D94(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80108C38.cue_0->u.end != 0xFF && D_80108C38.cue_0->u.scene == scene->u_8.value_8 && D_80108C38.cue_0->line == scene->value_1C)
    {
        D_80108C28[0] = D_80106A38[D_80108C38.cue_0->index];
        func_80103BB4(wp);
        D_80108C38.cue_0++;
    }
    if (D_80108C38.cue_4->u.end != 0xFF && D_80108C38.cue_4->u.scene == scene->u_8.value_8 && D_80108C38.cue_4->line == scene->value_1C)
    {
        D_80108C30[0] = D_80106AC8[D_80108C38.cue_4->index];
        func_80103C10(wp);
        D_80108C38.cue_4++;
    }
    func_80103C6C(wp);
}

void func_80103EDC(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0, 0);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    if (STAGE_GAME_VALUE_52 == 6)
    {
        D_80108C38.cue_0 = D_80106B7C;
        D_80108C38.cue_4 = D_80106B7C;
    }
    else
    {
        D_80108C38.cue_0 = D_80106B0C;
        D_80108C38.cue_4 = D_80106B20;
    }
    wp->routine_0++;
    func_80104320(wp);
}

void func_80103F90(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_80103FDC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80104028(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_80104074(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_801040C0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_8010410C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80104158(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801041A4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_801041F0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_8010423C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_80104288(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_801042D4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_80104320(STAGE_OBJ *wp)
{
    D_80106BCC[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    if (wp->u_C.b.byte_C == 0)
    {
        func_80032488(wp);
    }
    func_80103D94(wp);
}

void func_80104394(STAGE_EFFECT *wp)
{
    func_8003187C(wp);
}

void func_801043B4(STAGE_OBJ *wp)
{
    D_80106BFC[wp->routine_0](wp);
}

void func_801043F0(void)
{
}

void func_801043F8(ST07_MOVER *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->value_44 = 0;
            wp->timer_C  = 0;
            wp->angle_E  = 0xC00;
            wp->routine_2++;
            // fall through
        case 1:
            if ((wp->value_44 += 0x40) >= 0xC0)
            {
                wp->routine_3 = 5;
                wp->routine_2++;
            }
            break;
        case 2:
            if (--wp->routine_3 == 0)
            {
                wp->routine_2++;
            }
            break;
        case 3:
            if ((wp->value_44 -= 0x40) < -0xBF)
            {
                wp->routine_2 = 0;
                wp->routine_3 = 5;
            }
            break;
        case 4:
            if (--wp->routine_3 == 0)
            {
                wp->routine_2 = 1;
            }
            break;
    }
    wp->pos_38.x += 5;
    wp->pos_38.y++;
    if (wp->pos_38.x > 0x180)
    {
        wp->routine_1 = 0;
    }
}

void func_80104520(STAGE_OBJ *wp)
{
    wp->u_C.timer += 0x18;
    wp->u_E.angle += 0x14;
}

void func_8010453C(ST07_MOVER *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STAGE_MATRIX m;
    uint8 variant;

    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 6;
        variant = 0;
        Model_work_init(wp, &variant);
        wp->color_40 = 0x808080;
        wp->value_10 = 0;
        wp->timer_C  = 0;
        wp->angle_E  = 0xC00;
        wp->value_44 = 0;
        wp->value_46 = 0;
        wp->routine_0++;
    }
    else
    {
        D_80106C08[wp->routine_1](wp);
    }
    STAGE_MATRIX_IDENTITY(wp->matrix.words);
    if (wp->routine_1 == 2)
    {
        scale.x = scale.y = scale.z = 0x100;
    }
    else
    {
        scale.x = scale.y = scale.z = 0x200;
    }
    ScaleMatrix(&wp->matrix.m, &scale);
    rot.x = wp->timer_C;
    rot.y = wp->angle_E;
    rot.z = wp->value_44;
    STAGE_MATRIX_IDENTITY(m.w);
    RotMatrix(&rot, &m.m);
    MulMatrix(&wp->matrix.m, &m.m);
}

void func_801046A0(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        D_80106C14[wp->variant_3](wp);
    }
    else
    {
        D_80106C1C[wp->variant_3](wp);
    }
}

void func_8010470C(STAGE_OBJ *wp)
{
    STAGE_FX *ep;

    if (!(wp->routine_1 & 7))
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 3;
            ep->kind_2    = 8;
            ep->timer_D   = 1;
            ep->variant_3 = 0;
            ep->value_C   = 0;
            ep->frame_E   = 0x14;
            ep->z_20      = wp->position_fixed.f.y.words.fraction;
            ep->x_1C      = wp->position_fixed.f.x.words.fraction;
            ep->y_1E      = wp->position_fixed.f.x.words.integer;
            ep->mode_14   = 0x3D48000E;
            ep->color_18  = 0x2E808080;
            ep->u_22      = 0x20;
            ep->v_23      = 0;
            ep->w_24      = (rand() & 7) + 0x10;
        }
    }
    wp->routine_1++;
}

void func_801047E0(STAGE_FX *wp)
{
    if (STAGE_SCENE_BYTE(8) == 1)
    {
        wp->flags_0 |= 2;
    }
    else
    {
        wp->flags_0 &= ~2;
    }
    if (wp->frame_E > 0)
    {
        switch (wp->frame_E)
        {
            case 5:
            case 10:
            case 15:
                wp->u_22 += 0x20;
                break;
        }
        wp->y_1E -= 1 + (sint8)(wp->frame_E / 3);
        wp->w_24 += (sint8)(wp->frame_E / 6) + 1;
        wp->frame_E--;
        return;
    }
    func_80031988(wp);
}

void func_80104904(STAGE_OBJ *wp)
{
    STAGE_FX *ep;

    if (!(wp->routine_1 & 7))
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 3;
            ep->kind_2    = 8;
            ep->variant_3 = 1;
            ep->value_C   = 0;
            ep->timer_D   = 1;
            ep->frame_E   = 0x20;
            ep->z_20      = wp->position_fixed.f.y.words.fraction + (rand() & 3);
            ep->x_1C      = wp->position_fixed.f.x.words.fraction + (rand() & 3);
            ep->y_1E      = wp->position_fixed.f.x.words.integer;
            ep->mode_14   = 0x3D4E002E;
            ep->color_18  = 0x2E404040;
            ep->u_22      = 0x20;
            ep->v_23      = 0;
            ep->w_24      = (rand() & 3) + 0x12;
        }
    }
    wp->routine_1++;
}

void func_801049F4(STAGE_FX *wp)
{
    if (STAGE_SCENE_BYTE(8) == 3 && STAGE_SCENE_WORD(0x10) > 0)
    {
        wp->flags_0 |= 2;
    }
    else
    {
        wp->flags_0 &= ~2;
    }
    if (wp->frame_E > 0)
    {
        wp->color_18 += -0x20202;
        if (wp->frame_E > 0x10)
        {
            wp->y_1E--;
        }
        else
        {
            wp->y_1E -= 2;
        }
        wp->frame_E--;
        return;
    }
    func_80031988(wp);
}

void func_80104AB4(STAGE_FX *wp)
{
    wp->timer_D = 0;
    wp->mode_14 = 0x3D48002E;
    wp->flags_0 |= 0x22;
    wp->u_22             = ((rand() & 3) << 5) + 0x20;
    wp->v_23             = 0;
    wp->h_26             = 0;
    wp->value_38.value   = 0x80000;
    wp->value_3C.half[1] = 0;
    wp->value_3C.half[0] = 0;
    wp->routine_0++;
    func_80104B34(wp);
}

void func_80104B34(STAGE_FX *wp)
{
    if (wp->routine_1 == 0)
    {
        if (++wp->timer_D == 0x20)
        {
            wp->routine_1++;
        }
    }
    else if (--wp->timer_D == 0)
    {
        wp->routine_0++;
    }
    wp->y_30.value -= 9830.4;
    wp->value_38.value += 6553.6;
    wp->value_3C.half[0] += 128.0;
    wp->value_3C.words.integer += 0x89;
    wp->x_1C     = (wp->x_2C.value + rsin(wp->value_3C.words.integer) * 16) >> 16;
    wp->y_1E     = wp->y_30.value >> 16;
    wp->z_20     = wp->z_34.value >> 16;
    wp->w_24     = wp->value_38.value >> 16;
    wp->color_18 = wp->timer_D * 0x10101 + 0x2E000000;
    wp->h_26     = wp->value_3C.half[0] >> 8;
}

void func_80104CD4(STAGE_EFFECT *wp)
{
    func_80031988(wp);
}

void func_80104CF4(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_D = (rand() & 7) + 0x1E;
    wp->routine_0++;
}

void func_80104D34(STAGE_OBJ *wp)
{
    STAGE_FX *ep;

    if (--wp->u_C.b.byte_D == 0)
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0     = 1;
            ep->kind_2      = 0xD;
            ep->variant_3   = 1;
            ep->value_C     = 0xD;
            ep->u_28.object = wp;
            ep->flags_6 |= 0x20;
            ep->x_2C.value = (sint16)wp->position_fixed.f.x.words.fraction << 16;
            ep->y_30.value = wp->position_fixed.f.x.words.integer << 16;
            ep->z_34.value = (sint16)wp->position_fixed.f.y.words.fraction << 16;
        }
        wp->u_C.b.byte_D = (rand() & 7) + 0x1E;
    }
}

void func_80104DF0(STAGE_EFFECT *wp)
{
    func_80031988(wp);
}

void func_80104E10(STAGE_FX *wp)
{
    if (wp->variant_3 == 0)
    {
        D_80106C24[wp->routine_0](wp);
    }
    else
    {
        D_80106C30[wp->routine_0](wp);
    }
}

STAGE_FX *func_80104E7C(STCOM_SVECTOR *pos)
{
    STAGE_FX *ep;

    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0xD;
        ep->value_C   = 0xD;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->variant_3 = 0;
        ep->flags_6 |= 0x20;
        return ep;
    }
    return NULL;
}
