#include "common.h"
#include "st1e.h"

// Installs the stage's slot routine tables.
void func_801000AC(void)
{
    STAGE_TABLE_3C0      = D_80103DC8;
    STAGE_TABLE_5A4      = D_80103F3C;
    STAGE_TABLE_10C      = D_80103F58;
    STAGE_TABLE_48       = D_8010403C;
    STAGE_TABLE_24       = D_801040C8;
    STAGE_TABLE_50       = D_801040E4;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_8010011C(void)
{
    STAGE_MAP *map;
    sint16 *cells;
    void *spawn;

    map = &STAGE_MAP_TBL[Game_work.value_51];
    Room_model_init(D_80104190[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = map->w;
    STAGE_MAP_WORK_PTR->h     = map->h;
    STAGE_MAP_WORK_PTR->x0    = map->x0;
    STAGE_MAP_WORK_PTR->z0    = map->z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = map->cells;
    STAGE_PL_BYTE(0x44E)      = 0;
    spawn                     = D_80104238[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_8010426C[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_801043A0[D_801043B8[Game_work.value_51]], D_80104288[Game_work.value_51]);
    func_8005DC10(0);
    func_8010028C();
}

void func_8010028C(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_8010029C(void)
{
    D_8010440C[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_801002F0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DDE4(0x4C);
        wp->routine_4++;
    }
}

// Sets the script camera.
void func_8010033C(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 0x1E;
    D_800C356F = mode;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_801003A0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        func_8010033C(3);
        child                     = wp->child_24;
        child->position_fixed.v.z = 0x6500000;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.y = 0;
        child->routine_1          = 4;
        child->routine_2          = 0;
        child->flags_0 |= 2;
        other = wp->child_28;
        other->flags_0 &= ~2;
        other = wp->child_2C;
        other->flags_0 &= ~2;
    }
}

void func_8010043C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        func_8010033C(1);
        child            = wp->child_28;
        child->routine_1 = 0;
        child->routine_2 = 0;
        child->flags_0 |= 2;
        child            = wp->child_2C;
        child->routine_1 = 0;
        child->routine_2 = 0;
        child->flags_0 |= 2;
        other            = wp->child_30;
        other->routine_1 = 2;
        other->routine_2 = 0;
        other->flags_0 |= 2;
    }
    if (wp->frame_10 == 0xBA)
    {
        child = wp->child_2C;
        child->routine_2++;
    }
}

void func_801004F8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;

    if (wp->frame_10 == 0)
    {
        child_2C            = wp->child_2C;
        child_2C->routine_1 = 1;
        child_2C->routine_2 = 0;
        child_30            = wp->child_30;
        child_30->routine_1 = 2;
        child_30->routine_2 = 0;
    }
}

void func_80100530(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;

    if (wp->frame_10 == 0)
    {
        child_2C            = wp->child_2C;
        child_2C->routine_1 = 2;
        child_2C->routine_2 = 0;
        child_30            = wp->child_30;
        child_30->routine_1 = 0;
        child_30->routine_2 = 0;
    }
}

void func_80100568(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_28;

    if (wp->frame_10 == 0)
    {
        child_2C = wp->child_2C;
        child_2C->flags_0 &= ~2;
        child_28 = wp->child_28;
        child_28->routine_2++;
    }
}

void func_801005B0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;

    if (wp->frame_10 == 0)
    {
        child_2C            = wp->child_2C;
        child_2C->routine_1 = 0;
        child_2C->routine_2 = 0;
        child_2C->flags_0 |= 2;
        child_30            = wp->child_30;
        child_30->routine_1 = 2;
        child_30->routine_2 = 0;
    }
    if (wp->frame_10 == 0x8C)
    {
        child_2C = wp->child_2C;
        child_2C->routine_2++;
    }
}

void func_8010061C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_28;
    STAGE_OBJ *child_2C;

    if (wp->frame_10 == 0)
    {
        child_28 = wp->child_28;
        child_28->routine_2++;
        child_2C = wp->child_2C;
        child_2C->flags_0 &= ~2;
    }
}

void func_80100664(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child->flags_0 |= 2;
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
        other            = wp->child_30;
        other->routine_1 = 2;
        other->routine_2 = 0;
    }
    if (wp->frame_10 == 0xBE)
    {
        child = wp->child_28;
        child->routine_2++;
    }
}

void func_801006E0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_28;

    if (wp->frame_10 == 0)
    {
        child_28                     = wp->child_28;
        child_28->routine_1          = 2;
        child_28->position_fixed.v.x = 0xFF8D0000;
        child_28->position_fixed.v.z = 0xFEE50000;
        child_28->routine_2          = 0;
        child_28->rotation.y         = 0xCE4;
    }
}

void func_80100720(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;
    STAGE_OBJ *child_28;

    if (wp->frame_10 == 0)
    {
        child_2C            = wp->child_2C;
        child_2C->routine_1 = 1;
        child_2C->routine_2 = 0;
        child_30            = wp->child_30;
        child_30->routine_1 = 2;
        child_30->routine_2 = 0;
    }
    if (wp->frame_10 == 0x23)
    {
        child_28 = wp->child_28;
        child_28->routine_2++;
    }
}

void func_80100780(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;

    if (wp->frame_10 == 0)
    {
        child_2C            = wp->child_2C;
        child_2C->routine_1 = 3;
        child_2C->routine_2 = 0;
        child_30            = wp->child_30;
        child_30->routine_1 = 1;
        child_30->routine_2 = 0;
    }
}

void func_801007B8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    STAGE_50 *ep;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        func_8010033C(2);
        child                     = wp->child_24;
        child->routine_1          = 1;
        child->position_fixed.v.x = 0xEC780000;
        child->routine_2          = 0;
        child->position_fixed.v.y = 0xF98E0000;
        child->position_fixed.v.z = 0;
        child->rotation.y         = 0;
        child->flags_0 |= 2;
        child = wp->child_30;
        child->flags_0 &= ~2;
        other = wp->child_28;
        other->flags_0 &= ~2;
        other = wp->child_2C;
        other->flags_0 &= ~2;
        for (i = 0; i < 0xB; i++)
        {
            ep = func_80031734();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->variant_3 = i;
                ep->kind_2    = 0x2A;
                ep->flags_6 |= 0x20;
            }
        }
    }
    if (wp->frame_10 == 0xBD)
    {
        child            = wp->child_24;
        child->routine_1 = 0;
        child->routine_2 = 0;
        Obj_work_flag_change(0x100, 0x80);
    }
}

void func_801008F0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_34;
    STAGE_OBJ *child_38;
    STAGE_OBJ *child_3C;
    STAGE_OBJ *child_40;
    STAGE_OBJ *child_48;
    STAGE_OBJ *child_4C;

    if (wp->frame_10 == 0)
    {
        child_34 = wp->child_34;
        child_34->flags_0 |= 2;
        child_38 = wp->child_38;
        child_38->flags_0 |= 2;
        child_3C = wp->child_3C;
        child_3C->flags_0 |= 2;
        child_40 = wp->child_40;
        child_40->flags_0 |= 2;
        child_48 = wp->child_48;
        child_48->flags_0 |= 2;
        child_4C = wp->child_4C;
        child_4C->flags_0 |= 2;
    }
}

void func_80100998(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_50;
        child->flags_0 |= 2;
        child                     = wp->child_44;
        child->rotation.y         = 0x800;
        child->position_fixed.v.x = 0xF4480000;
        child->flags_0 |= 2;
    }
    if (wp->frame_10 == 0xD2)
    {
        child            = wp->child_50;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_44;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80100A14(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_44;
    STAGE_OBJ *child_24;

    if (wp->frame_10 == 0)
    {
        child_44                     = wp->child_44;
        child_44->rotation.y         = 0x4B0;
        child_44->position_fixed.v.x = 0xF1DC0000;
        child_24                     = wp->child_24;
        child_24->routine_1          = 2;
        child_24->position_fixed.v.x = 0xFC180000;
        child_24->position_fixed.v.y = 0xE8900000;
        child_24->position_fixed.v.z = 0xD5080000;
        child_24->routine_2          = 0;
        child_24->rotation.y         = 0xF0A;
    }
    if (wp->frame_10 == 0x59)
    {
        child_24            = wp->child_24;
        child_24->routine_1 = 0;
        child_24->routine_2 = 0;
    }
}

void func_80100A90(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *child_34;
    STAGE_OBJ *child_38;
    STAGE_OBJ *child_3C;
    STAGE_OBJ *child_40;
    STAGE_OBJ *child_48;
    STAGE_OBJ *child_4C;
    STAGE_OBJ *child_44;
    STAGE_OBJ *child_50;
    STAGE_OBJ *child_24;
    STAGE_OBJ *child_28;
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;

    if (wp->frame_10 == 0)
    {
        func_8010033C(1);
        child_34 = wp->child_34;
        child_34->flags_0 &= ~2;
        child_38 = wp->child_38;
        child_38->flags_0 &= ~2;
        child_3C = wp->child_3C;
        child_3C->flags_0 &= ~2;
        child_40 = wp->child_40;
        child_40->flags_0 &= ~2;
        child_48 = wp->child_48;
        child_48->flags_0 &= ~2;
        child_4C = wp->child_4C;
        child_4C->flags_0 &= ~2;
        child_44 = wp->child_44;
        child_44->flags_0 &= ~2;
        child_50 = wp->child_50;
        child_50->flags_0 &= ~2;
        child_24 = wp->child_24;
        child_24->flags_0 &= ~2;
        child                     = wp->child_28;
        child->routine_1          = 3;
        child->routine_2          = 0;
        child->position_fixed.v.x = 0xFFA10000;
        child->flags_0 |= 2;
        child->position_fixed.v.y = 0xFFA40000;
        child                     = wp->child_2C;
        child->routine_1          = 1;
        child->routine_2          = 0;
        child->flags_0 |= 2;
        child_28            = wp->child_30;
        child_28->routine_1 = 2;
        child_28->routine_2 = 0;
        child_28->flags_0 |= 2;
    }
    if (wp->frame_10 == 0x78)
    {
        child            = wp->child_28;
        child->routine_2 = 3;
    }
}

void func_80100C2C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_2C;
    STAGE_OBJ *child_30;

    if (wp->frame_10 == 0)
    {
        child_2C            = wp->child_2C;
        child_2C->routine_1 = 4;
        child_2C->routine_2 = 0;
        child_30            = wp->child_30;
        child_30->routine_1 = 2;
        child_30->routine_2 = 0;
    }
}

void func_80100C64(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_28;

    if (wp->frame_10 == 0)
    {
        child_28                     = wp->child_28;
        child_28->routine_1          = 4;
        child_28->position_fixed.v.x = 0xFFB90000;
        child_28->routine_2          = 0;
        child_28->position_fixed.v.y = 0xFF9F0000;
    }
}

void func_80100C9C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_2C;
        child->routine_1    = 5;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 1;
        child               = wp->child_30;
        child->routine_1    = 3;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x3C)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_D = 0;
        child               = wp->child_30;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x55)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        child               = wp->child_30;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x67)
    {
        child               = wp->child_30;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x69)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x71)
    {
        child               = wp->child_30;
        child->u_E.b.byte_E = 0;
        child->routine_1    = 4;
    }
}

void func_80100D84(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_8010033C(5);
        child = wp->child_2C;
        child->flags_0 &= ~2;
        child = wp->child_28;
        child->flags_0 &= ~2;
        child = wp->child_30;
        child->flags_0 &= ~2;
        child                     = wp->child_24;
        child->routine_1          = 3;
        child->scale.v.z          = 0x20;
        child->scale.v.y          = 0x20;
        child->scale.v.x          = 0x20;
        child->position_fixed.v.x = 0xFED40000;
        child->position_fixed.v.y = 0xFE700000;
        child->routine_2          = 0;
        child->position_fixed.v.z = 0;
        child->rotation.y         = 0xDAC;
        child->flags_0 |= 2;
        // Set but never used.
        pos.z = 0;
        pos.x = 0;
        pos.y = -0xC8;
    }
}

void func_80100E60(STAGE_ROOM *wp)
{
    STAGE_OBJ *child_24;

    if (wp->frame_10 == 0)
    {
        func_8010033C(3);
        child_24                     = wp->child_24;
        child_24->routine_1          = 2;
        child_24->scale.v.z          = 0x200;
        child_24->scale.v.y          = 0x200;
        child_24->scale.v.x          = 0x200;
        child_24->position_fixed.v.y = 0xFEA20000;
        child_24->routine_2          = 0;
        child_24->position_fixed.v.x = 0;
        child_24->position_fixed.v.z = 0xFA00000;
        child_24->rotation.y         = 0;
    }
}

void func_80100ED4(STAGE_ROOM *wp)
{
    STAGE_EFFECT *ep;

    switch (wp->routine_5)
    {
        case 0:
            Fade_start(0xB);
            wp->routine_5++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                wp->child_24->flags_0 &= ~2;
                D_800BBA90[0].flags_0 &= ~3;
                Cd_read_comb(0xCB);
                wp->routine_5++;
            }
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x20010000);
                Sound_work.volume_6 = 0x64;
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                ep = (STAGE_EFFECT *)func_80031618();
                if (ep != NULL)
                {
                    ep->flags_0   = 1;
                    ep->kind_2    = 0x22;
                    ep->variant_3 = 0;
                    ep->flags_6 |= 0x20;
                }
                Fade_start(2);
                wp->routine_5++;
            }
            break;
        case 4:
            break;
        case 5:
            Sound_fade_step_size = 1;
            Sound_fade_start(0x40);
            wp->routine_5++;
            break;
        case 6:
            if (Sound_fade_flags == 0)
            {
                Sound_fade_step_size = 4;
                Sound_work.volume_6  = 0x7F;
                Fade_start(0xB);
                wp->routine_5++;
            }
            break;
        case 7:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
    }
}

void func_80101078(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *entry;
    STAGE_EV *ep;
    sint32 i;

    func_8001E6C0(0, 0, 0);
    Sce_event_set(D_8010496C, D_8010444C);
    for (i = 0, entry = D_8010487C; i < 0xC; i++, entry++)
    {
        Scene_obj_ent_open(entry);
    }
    ep = Open_EVE_WORK();
    if (ep != NULL)
    {
        ep->flags_0 = 1;
        ep->kind_2  = 6;
        ep->value_F = 0;
        ep->flags_6 |= 0x20;
    }
}

void func_80101118(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101158(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                Player_work.flags_0 &= ~3;
                Cd_xa_play_id(0x2000001D);
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x1E;
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
            func_80101078(wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && *(uint8 *)wp->tbl_A4 == 0xFF)
            {
                Fade_start(0xB);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80101118(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 5 && D_80098A72 == 0)
            {
                D_800C356C  = 2;
                D_800C356E  = 0x15;
                D_800C356F  = 0;
                D_800C3560  = 0;
                D_800C3562  = 0;
                D_800C3564  = 0;
                D_800C356A  = 0;
                D_800C356D  = 0;
                D_800C3571  = 0xFF;
                D_800C3570  = 0xFF;
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}

void func_80101350(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_801013FC(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_801014A8(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_80101554(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_80101600(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        wp->routine_0++;
    }
    if (wp->routine_1 == 0)
    {
        if (wp->routine_2 == 0)
        {
            func_800322A8(wp, 0, 0);
            wp->routine_2++;
        }
    }
    else if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_801016EC(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_80101798(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_80101844(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x42100200;
        wp->routine_0++;
    }
    if (wp->routine_1 == 0)
    {
        if (wp->routine_2 == 0)
        {
            func_800322A8(wp, 0, 0);
            wp->routine_2++;
        }
    }
    else if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

STAGE_10C *func_80101930(sint32 *pos, sint16 angle, sint16 speed, uint8 variant)
{
    STAGE_10C *op;

    op = Open_SHL_WORK();
    if (op != NULL)
    {
        op->kind_2    = 0x38;
        op->variant_3 = variant;
        op->flags_0 |= 1;
        op->x_CC      = pos[0];
        op->z_D4      = pos[1];
        op->radius_DC = 0;
        op->angle_DE  = angle;
        op->speed_E0  = speed;
    }
    return op;
}

void func_801019C0(STAGE_10C *wp)
{
    STCOM_FIXED_VECTOR scale;

    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 6;
        Model_work_init(wp, &wp->variant_3);
        wp->color_B4 = 0x808080;
        wp->routine_1++;
    }
    wp->radius_DC += wp->speed_E0;
    wp->position_fixed.v.x = (wp->x_CC << 16) + wp->radius_DC * rsin(wp->angle_DE) * 16;
    wp->position_fixed.v.z = (wp->z_D4 << 16) + wp->radius_DC * rcos(wp->angle_DE) * 16;
    wp->position_fixed.v.y = wp->y_D0 << 16;
    wp->position_AC.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->position_AC.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->position_AC.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    STAGE_MATRIX_IDENTITY(wp->matrix_8C.w);
    scale.z = 0x1000;
    scale.y = 0x1000;
    scale.x = 0x1000;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
}

void func_80101AF0(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_80101B54(void)
{
}

void func_80101B5C(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, 0x80, 0, 0);
}

void func_80101B84(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, 0x100, 0, 0);
}

void func_80101BAC(STAGE_OBJ *wp)
{
    wp->position_fixed.v.y += -0x2C71C;
    wp->rotation.y += 0xA;
    Obj_pos_set(wp, 0x80, 0, 0);
}

void func_80101BF4(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += -0xC977A;
}

void func_80101C0C(STAGE_OBJ *wp)
{
    D_80104A24[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_80101C74(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80101AF0(wp);
    }
    func_80101C0C(wp);
}

void func_80101CB8(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
    func_80101E3C(wp);
}

void func_80101CF8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0x3B);
        wp->routine_2++;
    }
}

void func_80101D44(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80101D90(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_80101DDC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_80101E28(STAGE_OBJ *wp)
{
    wp->rotation.z += 0x11C;
}

void func_80101E3C(STAGE_OBJ *wp)
{
    if (wp->u_E.b.byte_E != wp->u_E.b.byte_F)
    {
        Model_work_init(wp, &wp->u_E.b.byte_E);
    }
    wp->u_E.b.byte_F = wp->u_E.b.byte_E;
    D_80104A38[wp->routine_1](wp);
}

void func_80101EA4(STAGE_EFFECT *wp)
{
    func_80031824(wp);
}

void func_80101EC4(STAGE_OBJ *wp)
{
    D_80104A4C[wp->routine_0](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        if (wp->routine_1 == 4)
        {
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
        }
        else
        {
            func_80032488(wp);
        }
    }
}

void func_80101F54(STAGE_OBJ *wp)
{
    D_801098EC[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_801098E8[0]->id, 0x2A, 0x33, 6));
}

void func_80101FB0(STAGE_OBJ *wp)
{
    D_801098F4[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_801098F0[0]->id, 0x2A, 0x33, 6));
}

void func_8010200C(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_801098E8_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801098E8[0] += count;
            func_80101F54(wp);
        }
        else if (++D_801098EC[0] == p->count)
        {
            D_801098E8_S = p + 1;
            func_80101F54(wp);
        }
    }
    p     = D_801098F0_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801098F0[0] += count;
            func_80101FB0(wp);
        }
        else if (++D_801098F4[0] == p->count)
        {
            D_801098F0_S = p + 1;
            func_80101FB0(wp);
        }
    }
}

void func_80102134(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_801098F8.cue_0->u.end != 0xFF && D_801098F8.cue_0->u.scene == scene->u_8.value_8 && D_801098F8.cue_0->line == scene->value_1C)
    {
        D_801098E8[0] = D_80104C54[D_801098F8.cue_0->index];
        func_80101F54(wp);
        D_801098F8.cue_0++;
    }
    if (D_801098F8.cue_4->u.end != 0xFF && D_801098F8.cue_4->u.scene == scene->u_8.value_8 && D_801098F8.cue_4->line == scene->value_1C)
    {
        D_801098F0[0] = D_80104CA8[D_801098F8.cue_4->index];
        func_80101FB0(wp);
        D_801098F8.cue_4++;
    }
    func_8010200C(wp);
}

void func_8010227C(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    D_801098F8.cue_0   = D_80104CFC;
    D_801098F8.cue_4   = D_80104D8C;
    wp->routine_0++;
}

void func_801022F0(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x10, 0);
            wp->u_C.b.byte_D = 1;
            wp->routine_2++;
            break;
        case 1:
            break;
        case 2:
            wp->u_C.b.byte_D = 0;
            if (*wp->anim_98 == 9)
            {
                wp->u_C.b.byte_D = 1;
                wp->routine_2++;
            }
            break;
        case 3:
            break;
        case 4:
            wp->u_C.b.byte_D = 0;
            break;
    }
}

void func_8010238C(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x11, 0);
            wp->u_C.b.byte_D = 0;
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 == 9)
            {
                wp->u_C.b.byte_D = 1;
                wp->routine_2++;
            }
            break;
        case 2:
            break;
        case 3:
            wp->u_C.b.byte_D = 0;
            if (*wp->anim_98 == 0x14)
            {
                wp->routine_2++;
            }
            break;
        case 4:
            wp->position_fixed.v.x += 0x28000;
            if (*wp->anim_98 == 0x3D)
            {
                wp->routine_2++;
            }
            break;
        case 5:
            break;
    }
}

void func_80102468(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x12, 0);
            wp->u_C.b.byte_D = 0;
            wp->routine_2++;
            break;
        case 1:
            wp->position_fixed.v.x += 0x1B102;
            wp->position_fixed.v.z += -0x9D9A;
            if (*wp->anim_98 == 0x13)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            wp->position_fixed.v.x += 0x12CB3;
            wp->position_fixed.v.z -= 0x6D72;
            if (*wp->anim_98 == 0x1D)
            {
                wp->routine_2++;
            }
            break;
        case 3:
            if (*wp->anim_98 == 0x31)
            {
                wp->u_C.b.byte_D = 1;
                wp->routine_2++;
            }
            break;
        case 4:
            break;
        case 5:
            wp->u_C.b.byte_D = 0;
            break;
    }
}

void func_8010258C(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x13, 0);
            wp->u_C.b.byte_D = 0;
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 == 0x18)
            {
                func_800322A8(wp, 0x14, 0);
                wp->routine_2++;
            }
            break;
        case 2:
            break;
        case 3:
            if (*wp->anim_98 == 0xB)
            {
                func_800322A8(wp, 0x15, 0);
                wp->routine_2++;
            }
            break;
        case 4:
            break;
    }
}

void func_8010264C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_80102698(STAGE_OBJ *wp)
{
    D_80104E1C[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_80102134(wp);
}

void func_80102708(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_8010227C(wp);
    }
    func_80102698(wp);
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}
