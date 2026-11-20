#include "common.h"
#include "st01.h"

// Installs the stage's slot routine tables.
void func_80100030(void)
{
    STAGE_TABLE_3C0 = D_80100C88;
    STAGE_TABLE_5A4 = D_80100CC8;
    STAGE_TABLE_10C = D_80100CCC;
    STAGE_TABLE_48  = D_80100CD0;
    STAGE_TABLE_24  = D_80100CD4;
    STAGE_TABLE_50  = D_80100D58;
}

// Sets up the current room: models, map, spawns.
void func_80100098(void)
{
    STAGE_MAP_WORK *mw;
    void *spawns;

    mw = STAGE_MAP_WORK_PTR;
    func_80022FD4(D_80100D5C[Game_work.value_51]);
    spawns    = D_80100D88[Game_work.value_51];
    mw->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    mw->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    mw->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    mw->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = STAGE_MAP_TBL[Game_work.value_51].cells;
    mw->info  = STAGE_CELL_INFO;
    mw->exits = D_80100DA4[Game_work.value_51];
    func_8002EA50(spawns, D_800C356D);
    func_800371A0(D_80100E20[D_80100EF8[Game_work.value_51]], D_80100DA8[Game_work.value_51]);
    func_8005DC10(0);
}

// Runs the current room's script.
void func_801001EC(void)
{
    D_80100F08[Game_work.value_51](&D_800989F8);
}

void func_8010022C(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_80017C30(8);
            wp->routine_4++;
            // fall through
        case 1:
            if (D_80098A72 == 0)
            {
                func_8001DDE4(0x47);
                D_80098A8C = 0;
                wp->routine_4++;
            }
            break;
        case 2:
            break;
    }
}

void func_801002BC(void)
{
}

void func_801002C4(void)
{
}

void func_801002CC(void)
{
}

void func_801002D4(void)
{
}

void func_801002DC(void)
{
}

void func_801002E4(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        D_800BBA9C[0] = 0x82;
        D_800BBA90[0].flags_0 &= 0xFD;
        STAGE_MODEL_TBL[2].value_20 -= 0x38;
        STAGE_MODEL_TBL[1].value_20 -= 0x10;
        child            = wp->child_24;
        child->routine_1 = 1;
        child->routine_2 = 0;
        wp->timer_C      = 3;
    }
    if (wp->frame_10 == 0x898)
    {
        D_800BBA90[0].flags_0 |= 2;
    }
    if (wp->routine_6 == 0 && wp->frame_10 > 0x898)
    {
        if (--wp->timer_C == 0)
        {
            wp->timer_C = 3;
            if (--D_800BBA9C[0] == -0xB)
            {
                wp->routine_6++;
            }
        }
    }
}

void func_80100400(STAGE_ROOM_WORK *wp)
{
    uint8 *entry;

    func_8001E6C0(0, 0, 0);
    entry      = D_80100F1C;
    D_800BC7F0 = D_80100F30;
    wp->tbl_A4 = D_80100F7C;
    func_8001EAE8(entry);
}

void func_8010045C(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_8010049C(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            Sound_seq_stop_all();
            Cd_xa_play_id(0x2000001E);
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 5;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 4:
            func_80017C30(2);
            func_80100400(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(10);
                wp->routine_4 = 10;
            }
            // fall through
        case 10:
            func_8010045C(wp);
            func_8001EC0C();
            Sce_event_update();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                Obj_work_flag_change(0x56, 0x80);
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                STAGE_GAME_FLAGS_82 &= 0x7F;
                wp->flags_0 = 0;
                D_80098AA8[0].routine_0++;
                D_80098AA8[0].routine_1 = 0;
                func_80012F78(D_80013420);
            }
            break;
    }
}

void func_801006A0(void)
{
}

void func_801006A8(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->timer_C = 4;
            wp->value_D = 5;
            wp->routine_2++;
            break;
        case 1:
            if (--wp->timer_C <= 0)
            {
                wp->timer_C = 4;
                wp->position.x--;
            }
            if (--wp->value_D <= 0)
            {
                wp->position.y++;
                wp->value_D = 5;
                if (wp->position.y >= 0xDC)
                {
                    wp->routine_2++;
                }
            }
            break;
        case 2:
            if (--wp->timer_C <= 0)
            {
                wp->position.x--;
                wp->timer_C = 4;
                if (wp->position.x < -0x121)
                {
                    wp->timer_C = 0x1E;
                    wp->routine_2++;
                }
            }
            break;
        case 3:
            if (--wp->timer_C <= 0)
            {
                func_80031824(wp);
            }
            break;
    }
}

void func_8010080C(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, 0);
        wp->scale.words[0] = 0x200020;
        wp->scale.words[1] = 0x20;
        wp->scale.v.pad    = 0x4210;
        wp->rot_y_56       = 0x400;
        wp->value_78       = 0;
        wp->value_10       = 0;
        wp->flags_0 |= 2;
        wp->routine_0++;
    }
    D_80100F8C[wp->routine_1](wp);
    func_800322A8(wp, 0, 0);
}

void func_801008C0(STAGE_WORK *wp)
{
    D_80101094[wp->routine_0](wp);
}

void func_801008FC(STAGE_WORK *wp)
{
    wp->routine_1    = 0;
    wp->routine_2    = 0;
    wp->routine_3    = 0;
    wp->position.pad = -0xBE;
    wp->routine_0++;
}

void func_80100920(STAGE_WORK *wp)
{
    sint32 i;
    sint32 y;
    sint32 c;

    y = wp->position.pad;
    for (i = 0; i < 0x10; i++)
    {
        c = i << 3;
        func_80100A70(wp, i + 0x20, y + i, 0x2000000 | (c << 16) | (c << 8) | c);
    }
    for (i = 0; i < 0x90; i++)
    {
        func_80100A70(wp, i + 0x30, y + 0x10 + i, 0x2808080);
    }
    for (i = 0; i < 0x10; i++)
    {
        c = (0x10 - i) << 3;
        func_80100A70(wp, i + 0xC0, y + 0xA0 + i, 0x2000000 | (c << 16) | (c << 8) | c);
    }
    if (++wp->routine_3 >= 3)
    {
        wp->routine_3 = 0;
        wp->position.pad++;
    }
    if (wp->position.pad >= 0x400)
    {
        Close_EVE_WORK(wp);
    }
}

// Draws one textured line of the scrolling picture.
void func_80100A70(void *wp, sint32 y, sint32 v, uint32 color)
{
    POLY_FT4 *p;

    if (v < 0)
    {
        return;
    }
    if (v >= 0x400)
    {
        return;
    }
    p                 = (*STAGE_PACKET_PTR)++;
    *(u_long *)p      = 0x09000000;
    *(u_long *)&p->r0 = color | 0x2C000000;
    p->clut           = 0x7C00;
    p->tpage          = ((v >> 8) + 0x15) | 0x20;
    p->u1 = p->u3 = 0xFF;
    p->u0 = p->u2 = 0;
    p->v0 = p->v1 = v;
    p->v2 = p->v3 = v;
    p->x0 = p->x2 = 0x20;
    p->x1 = p->x3 = 0x11F;
    p->y2 = p->y3 = y + 1;
    p->y0 = p->y1 = y;
    addPrim(&Disp_env_ptr->ot_78, p);
}
