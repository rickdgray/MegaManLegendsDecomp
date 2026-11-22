#include "common.h"
#include "st02.h"

// Installs the stage's slot routine tables.
void func_80100048(void)
{
    STAGE_TABLE_3C0 = D_801067A4;
    STAGE_TABLE_5A4 = D_80106844;
    STAGE_TABLE_10C = D_80106864;
    STAGE_TABLE_48  = D_80106868;
    STAGE_TABLE_24  = D_8010688C;
    STAGE_TABLE_50  = D_801068A8;
}

// Sets up the current room: models, map, spawns.
void func_801000B0(void)
{
    STAGE_MAP_WORK *mw;
    void *spawns;

    mw = STAGE_MAP_WORK_PTR;
    func_80022FD4(D_801068E0[Game_work.value_51]);
    spawns    = D_80106940[Game_work.value_51];
    mw->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    mw->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    mw->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    mw->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = STAGE_MAP_TBL[Game_work.value_51].cells;
    mw->info  = STAGE_CELL_INFO;
    mw->exits = D_80106968[Game_work.value_51];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_80106A18[D_80106C18[Game_work.value_51]], D_80106978[Game_work.value_51]);
    func_8005DC10(0);
}

void func_80100204(void)
{
    Sce_flag_on(0x600);
    D_800989FC[0]++;
}

void func_80100238(void)
{
    ST02_MUSIC *p;

    if (D_800989FC[0] == 0)
    {
        func_80100204();
    }
    for (p = D_80106C28; p->flag != 0xFFFF; p++)
    {
        if (Sce_flag_test(p->flag) != 0)
        {
            func_8001DDE4(p->id);
            return;
        }
    }
}

// Sets the script camera.
void func_801002C8(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 2;
    D_800C356F = mode;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

// Draws a translucent full-screen rectangle (abr: the blend mode).
void func_8010032C(uint8 r, uint8 g, uint8 b, uint16 abr)
{
    ST02_TILE *tile;
    DR_MODE *mode;

    tile = (ST02_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->g0   = g;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->r0   = r;
    tile->b0   = b;
    tile->code |= 2;
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(mode, 0, 0, (abr << 5) | 0xF, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
}

void func_80100450(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        D_800BBB00            = 3;
        D_8010A5F0            = 0x60;
        D_8010A5EC            = 0x60;
        D_8010A5E8            = 0x60;
        D_800BBAC8            = 0;
        D_800BBA90[0].flags_0 = 0;
        D_8010A5E4            = 1;
        D_8010A5F4            = 1;
    }
    if (wp->frame_10 == 0xBF)
    {
        child                     = wp->child_30;
        child->position_fixed.v.z = 0x6500000;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.y = 0;
        child->routine_1          = 2;
        child->routine_2          = 0;
        child->flags_0 |= 2;
    }
    if (wp->frame_10 == 0x15D)
    {
        D_8010A5D4->u_C.b.byte_D = 0;
        D_8010A5E4               = 0;
        child                    = wp->child_30;
        child->scale.v.pad       = 0x1884;
    }
}

void func_80100524(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    uint8 level;

    if (wp->frame_10 == 0)
    {
        D_800BBA90[0].flags_0     = 3;
        D_800BBA90[1].flags_0     = 3;
        D_800BBA90[2].flags_0     = 0;
        D_800BBA90[0].fpos_4.y    = 0xF00000;
        D_800BBA90[1].fpos_4.y    = 0xF00000;
        D_8010A5D8                = 0x500000;
        D_8010A5DC                = 0xFF060000;
        child                     = wp->child_30;
        child->routine_1          = 6;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.y = 0;
        child->position_fixed.v.z = 0;
        child->routine_2          = 0;
        child->scale.v.pad        = 0x4210;
        D_8010A5D4->u_C.b.byte_D  = 1;
        D_8010A5E4                = 1;
    }
    if (wp->frame_10 < 0xB4)
    {
        // Model 0 through its symbol (its address kept in a register), model 1 through the
        // fixed address (ordered before the store through D_8010A5D4).
        D_800BBA90[0].fpos_4.y -= 0x15555;
        ST02_MODEL_TBL[1].value_8 -= 0x15555;
        D_8010A5DC += 0x15555;
        D_8010A5D4->position_fixed.f.x.words.integer = D_8010A5DC >> 16;
        D_8010A5E4                                   = 1;
        D_8010A5F4                                   = 1;
        level                                        = wp->frame_10 * 0x60 / 180;
        D_8010A5E8 = D_8010A5EC = D_8010A5F0 = level;
    }
}

void func_8010068C(void)
{
}

void func_80100694(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_8010A5E4                  = 0;
        D_8010A5D4->u_C.b.byte_D    = 0;
        ST02_MODEL_TBL[7].value_22  = 0x80;
        ST02_MODEL_TBL[1].flags_0   = 0;
        ST02_MODEL_TBL[0].flags_0   = 0;
        ST02_MODEL_TBL[7].flags_0   = 3;
        ST02_MODEL_TBL[10].value_22 = 0x100;
        ST02_MODEL_TBL[10].flags_0  = 3;
        ST02_MODEL_TBL[10].value_30 = 1;
        func_80105884(wp->child_30, 1000, 0, -500);
    }
}

void func_80100728(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;
    STAGE_OBJ *temp_v1_2;
    STAGE_OBJ *temp_v1_3;
    STAGE_OBJ *temp_v1_4;
    STAGE_OBJ *temp_v1_5;

    if (wp->frame_10 == 0)
    {
        func_801002C8(1);
        Obj_work_flag_change(0x40, 0x80);
        temp_v1               = wp->child_24;
        temp_v1->flags_0      = (uint8)temp_v1->flags_0 | 2;
        temp_v1_2             = wp->child_28;
        temp_v1_2->flags_0    = (uint8)temp_v1_2->flags_0 | 2;
        temp_v1_3             = wp->child_2C;
        temp_v1_3->flags_0    = (uint8)temp_v1_3->flags_0 | 2;
        temp_v1_4             = wp->child_30;
        temp_v1_4->flags_0    = (uint8)temp_v1_4->flags_0 & 0xFD;
        temp_v1_5             = wp->child_34;
        temp_v1_5->flags_0    = (uint8)temp_v1_5->flags_0 | 2;
        D_800BBA90[0].flags_0 = 3;
        D_800BBAD0            = 0;
        D_800BBA98            = 0;
        D_800BBAB0            = -0x50;
        D_800BBAC8            = 3;
        D_800BBC18            = 0;
        D_800BBCC0            = 0;
    }
}

void func_80100828(void)
{
}

void func_80100830(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    if (wp->frame_10 == 0)
    {
        temp_v1                     = wp->child_24;
        temp_v1->position_fixed.v.z = -0x09000000;
        temp_v1->position_fixed.v.y = -0x01730000;
        temp_v1->position_fixed.v.z = -0x580000;
        temp_v1->routine_1          = 0;
        temp_v1->routine_2          = 0;
    }
}

void func_8010086C(void)
{
}

void func_80100874(STAGE_ROOM *wp)
{
    STAGE_OBJ *var_a1;

    var_a1 = wp->child_24;
    if (wp->frame_10 == 0)
    {
        var_a1->position_fixed.v.x = -0x093F0000;
        var_a1->position_fixed.v.y = -0x610000;
        var_a1->position_fixed.v.z = -0x01600000;
        var_a1->routine_1          = 1;
        var_a1->routine_2          = 0;
        var_a1->rotation.y         = 0;
        var_a1                     = wp->child_28;
        var_a1->routine_1          = 3;
        var_a1->routine_2          = 0;
    }
    if (wp->frame_10 == 0x6C)
    {
        var_a1->routine_1 = 2;
        var_a1->routine_2 = 0;
    }
}

void func_801008D8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0x32)
    {
        child->routine_1 = 3;
        child->routine_2 = 0;
    }
    child = wp->child_28;
    if (wp->frame_10 == 0)
    {
        child->routine_1 = 0;
        child->routine_2 = 0;
    }
}

void func_80100914(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_a1;

    temp_a1 = wp->child_28;
    if (wp->frame_10 == 0x1E)
    {
        temp_a1->routine_1 = 3;
        temp_a1->routine_2 = 0;
    }
    if (wp->frame_10 == 0xB4)
    {
        temp_a1->routine_1 = 4;
        temp_a1->routine_2 = 0;
    }
}

void func_80100950(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    temp_v1 = wp->child_24;
    if (wp->frame_10 == 0)
    {
        temp_v1->routine_1 = 4;
        temp_v1->routine_2 = 0;
    }
}

void func_80100970(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_24;
        child->routine_1    = 5;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 1;
        child               = wp->child_28;
        child->routine_1    = 3;
        child->routine_2    = 0;
        D_800BBAB0          = 0;
    }
    if (wp->frame_10 == 0x4F)
    {
        child               = wp->child_24;
        child->u_C.b.byte_D = 0;
    }
}

void func_801009D4(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_800BBAB0 = -0x50;
    }
}

void func_801009F4(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v0;

    if (wp->frame_10 == 0)
    {
        temp_v0            = wp->child_28;
        temp_v0->routine_1 = 5;
        temp_v0->routine_2 = 0;
        D_800BBAB0         = 0x50;
    }
}

void func_80100A28(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_801002C8(0);
        ST02_MODEL_TBL[7].flags_0   = 3;
        ST02_MODEL_TBL[10].flags_0  = 3;
        ST02_MODEL_TBL[1].flags_0   = 0;
        ST02_MODEL_TBL[0].flags_0   = 0;
        ST02_MODEL_TBL[10].value_4  = 0;
        ST02_MODEL_TBL[10].value_8  = 0;
        ST02_MODEL_TBL[10].value_20 = 0;
        ST02_MODEL_TBL[10].value_22 = 0x100;
        wp->child_24->flags_0 &= ~2;
        wp->child_28->flags_0 &= ~2;
        wp->child_2C->flags_0 &= ~2;
        wp->child_30->flags_0 |= 2;
        wp->child_34->flags_0 &= ~2;
        Obj_work_flag_change(0x40, 0x80);
        func_80105884(wp->child_30, 1000, 0, -500);
    }
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_80100B6C(STAGE_ROOM *wp)
{
    STAGE_XYZ pos;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_801002C8(1);
        ST02_MODEL_TBL[10].flags_0 = 0;
        child                      = wp->child_2C;
        child->flags_0 |= 2;
        child = wp->child_30;
        // Signed here: the and takes -3, not 0xFD (shared with the rise below).
        *(sint8 *)&child->flags_0 &= ~2;
        D_8010A5E4 = 1;
        D_8010A5E8 = D_8010A5EC = D_8010A5F0 = 0x20;
        D_8010A5F4                           = 2;
        Obj_work_flag_change(0x40, 0x80);
        pos.x = -0x7DA;
        pos.y = -0x17;
        pos.z = 0x82A;
        func_80104448(&pos, 0x18, 0, 0x1E, -3, 1);
        pos.x = -0x7BC;
        pos.y = -0x64;
        pos.z = 0x88E;
        func_80104448(&pos, 0x18, 0, 0x1E, -3, 1);
    }
}

void func_80100C90(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_801002C8(0);
        child      = wp->child_2C;
        D_8010A5E4 = 0;
        child->flags_0 &= 0xFD;
        child = wp->child_30;
        child->flags_0 |= 2;
        Obj_work_flag_change(0x40, 0x80);
        ST02_MODEL_TBL[10].flags_0  = 3;
        ST02_MODEL_TBL[10].value_4  = 0;
        ST02_MODEL_TBL[10].value_8  = 0;
        ST02_MODEL_TBL[10].value_20 = 0;
        ST02_MODEL_TBL[10].value_22 = 0x100;
        func_80105884(wp->child_30, 1000, 0, -500);
    }
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_80100D78(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        func_801002C8(1);
        STAGE_MODEL_TBL[1].flags_0  = 3;
        STAGE_MODEL_TBL[0].flags_0  = 3;
        STAGE_MODEL_TBL[10].flags_0 = 0;
        STAGE_MODEL_TBL[7].flags_0  = 0;
        child                       = wp->child_24;
        child->position_fixed.v.x   = -0x09B00000;
        child->position_fixed.v.y   = -0x610000;
        child->position_fixed.v.z   = -0x900000;
        child->flags_0 |= 2;
        child               = wp->child_28;
        child->routine_1    = 6;
        child->routine_2    = 0;
        child->u_C.b.byte_C = 1;
        child->flags_0 |= 2;
        other = wp->child_30;
        other->flags_0 &= 0xFD;
        other = wp->child_34;
        other->flags_0 |= 2;
        Obj_work_flag_change(0x40, 0x80);
    }
    if (wp->frame_10 == 0xC8)
    {
        child               = wp->child_28;
        child->u_C.b.byte_C = 0;
    }
}

void func_80100E74(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v0;

    if (wp->frame_10 == 0)
    {
        temp_v0             = wp->child_24;
        temp_v0->rotation.y = 0x400;
        temp_v0->routine_1  = 6;
        temp_v0->routine_2  = 0;
    }
}

void func_80100EA4(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_800BBC18            = 0;
        D_800BBB00            = 0;
        D_800BBAC8            = 0;
        D_800BBA90[0].flags_0 = 0;
        D_800BBB38            = 3;
    }
}

void func_80100EE4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_24;
        child->flags_0 &= 0xFD;
        child                 = wp->child_28;
        child->routine_1      = 2;
        child->routine_2      = 0;
        D_800BBB38            = 0;
        D_800BBAC8            = 3;
        D_800BBA90[0].flags_0 = 3;
    }
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_80100F80(void)
{
}

void func_80100F88(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_801002C8(0);
        child                      = wp->child_30;
        child->routine_1           = 1;
        child->position_fixed.v.x  = 0;
        child->position_fixed.v.y  = 0;
        child->position_fixed.v.z  = 0;
        child->routine_2           = 0;
        ST02_MODEL_TBL[6].flags_0  = 3;
        ST02_MODEL_TBL[1].flags_0  = 0;
        ST02_MODEL_TBL[0].flags_0  = 0;
        ST02_MODEL_TBL[6].value_8  = 0;
        ST02_MODEL_TBL[6].value_4  = 0;
        ST02_MODEL_TBL[6].value_22 = -0x200;
        child                      = wp->child_24;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_28;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_2C;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_34;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_30;
        child->flags_0 |= 2;
    }
    D_800BBC00[1] -= 6;
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_801010D4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_30;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.y = 0;
        child->position_fixed.v.z = 0;
        child->routine_1          = 3;
        child->routine_2          = 0;
        D_800BBC02                = -0x80;
    }
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_80101154(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        ST02_MODEL_TBL[6].value_8  = 0;
        ST02_MODEL_TBL[6].value_4  = 0;
        ST02_MODEL_TBL[6].value_22 = 0;
        ST02_MODEL_TBL[6].value_20 = -0x400;
        child                      = wp->child_30;
        child->position_fixed.v.x  = 0;
        child->position_fixed.v.y  = 0;
        child->position_fixed.v.z  = 0;
        child->routine_1           = 0;
        child->routine_2           = 0;
        child->rotation.y          = 0;
        Obj_work_flag_change(0x40, 0x80);
    }
    if (wp->frame_10 >= 115)
    {
        D_800BBC00[0] += 11;
        D_800BBC02 += 33;
    }
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_80101240(STAGE_ROOM *wp)
{
    D_800BBC00[0] += 0x16;
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_801012A0(STAGE_ROOM *wp)
{
    if ((ST02_FRAME & 7) == 7)
    {
        func_80105724(wp->child_30, 400, -100, 300, 1);
    }
}

void func_801012E8(STAGE_ROOM *wp)
{
    STAGE_XYZ pos;

    if (wp->frame_10 == 0)
    {
        func_801002C8(1);
        wp->child_2C->flags_0 |= 2;
        Obj_work_flag_change(0x40, 0x80);
        pos.x = -0x7DA;
        pos.y = -0x17;
        pos.z = 0x82A;
        func_80104448(&pos, 0x18, 0, 0x1E, -3, 1);
        pos.x = -0x7BC;
        pos.y = -0x64;
        pos.z = 0x88E;
        func_80104448(&pos, 0x18, 0, 0x1E, -3, 1);
        pos.x = -0x794;
        pos.y = -0x14;
        pos.z = 0x834;
        func_80104448(&pos, 0x18, 0, 0x1E, -3, 1);
    }
    D_8010A5E4 = 1;
    D_8010A5E8 = D_8010A5EC = D_8010A5F0 = 0x20;
    D_8010A5F4                           = 2;
}

void func_80101420(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        child = wp->child_24;
        child->flags_0 |= 2;
        child = wp->child_28;
        child->flags_0 |= 2;
        other = wp->child_34;
        other->flags_0 |= 2;
        child->routine_1 = 0;
        child->routine_2 = 0;
        D_800BBC00[0]    = -0x50;
        D_800BBC02       = 0;
        Obj_work_flag_change(0x40, 0x80);
    }
    D_8010A5E4 = 0;
}

void func_801014BC(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v1;

    if (wp->frame_10 == 0)
    {
        temp_v1                     = wp->child_24;
        temp_v1->routine_1          = 7;
        temp_v1->position_fixed.v.x = -0x09400000;
        temp_v1->position_fixed.v.y = -0x610000;
        temp_v1->routine_2          = 0;
        temp_v1->position_fixed.v.z = -0x019E0000;
        temp_v1->rotation.y         = 0;
    }
}

void func_80101500(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_800BBA90[6].flags_0  = 0;
        D_800BBA90[8].flags_0  = 3;
        D_800BBA90[8].fpos_4.x = 0;
        D_800BBA90[8].fpos_4.y = 0xAE0000;
        D_800BBA90[8].value_22 = 0x18;
        D_800BBA90[9].flags_0  = 3;
        D_800BBA90[9].fpos_4.x = 0;
        D_800BBA90[9].fpos_4.y = 0xAE0000;
        D_800BBA90[9].value_22 = 0x10;
    }
    if (wp->frame_10 == 0x28)
    {
        D_8010A5E0 = 2;
    }
}

void func_80101588(STAGE_ROOM *wp)
{
    if (wp->timer_C == 0)
    {
        D_800BBC88 = 0;
        D_800BBC50 = 0;
    }
}

void func_801015B0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_801002C8(0);
        ST02_MODEL_TBL[4].flags_0  = 3;
        ST02_MODEL_TBL[4].value_4  = 0x01400000;
        ST02_MODEL_TBL[5].value_4  = 0x01400000;
        ST02_MODEL_TBL[4].value_8  = 0;
        ST02_MODEL_TBL[5].flags_0  = 3;
        ST02_MODEL_TBL[5].value_8  = 0;
        ST02_MODEL_TBL[5].value_20 = -0xE8B;
        ST02_MODEL_TBL[4].value_20 = -0xE8B;
        ST02_MODEL_TBL[5].value_22 = 0;
        ST02_MODEL_TBL[4].value_22 = 0;
        child                      = wp->child_30;
        child->position_fixed.v.x  = 0;
        child->position_fixed.v.y  = 0;
        child->position_fixed.v.z  = 0;
        child->routine_1           = 4;
        child->routine_2           = 0;
        child->flags_0 |= 2;
        child = wp->child_24;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_28;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_2C;
        *(sint8 *)&child->flags_0 &= ~2;
        child = wp->child_34;
        *(sint8 *)&child->flags_0 &= ~2;
        D_8010A5E0 = 0;
    }
    if (wp->frame_10 < 0x16)
    {
        D_800BBA90[4].value_22 += 0xFE;
        ST02_MODEL_TBL[5].value_22 += 0xFE;
    }
    if (wp->frame_10 == 0x16)
    {
        ST02_MODEL_TBL[5].value_20 = 0xE8B;
        ST02_MODEL_TBL[4].value_20 = 0xE8B;
    }
    if (wp->frame_10 == 0x2C)
    {
        ST02_MODEL_TBL[5].value_20 = 0;
        ST02_MODEL_TBL[4].value_20 = 0;
        ST02_MODEL_TBL[5].value_22 = 0;
        ST02_MODEL_TBL[4].value_22 = 0;
    }
}

void func_8010176C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_801002C8(2);
        D_800BBA90[6].flags_0     = 3;
        D_800BBA90[4].flags_0     = 0;
        D_800BBA90[5].flags_0     = 0;
        D_800BBA90[6].value_22    = 0;
        child                     = wp->child_30;
        child->position_fixed.v.x = 0x7D00000;
        child->position_fixed.v.y = -0x5780000;
        child->position_fixed.v.z = -0x17700000;
        child->routine_1          = 5;
        child->routine_2          = 0;
        Obj_work_flag_change(0x40, 0x80);
    }
}

void func_80101800(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        func_801002C8(1);
        child            = wp->child_24;
        child->routine_1 = 8;
        child->routine_2 = 0;
        child->flags_0 |= 2;
        child            = wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 0;
        child->flags_0 |= 2;
        other = wp->child_34;
        other->flags_0 |= 2;
        D_8010A5E0 = 1;
    }
}

void func_8010189C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 9;
        child->routine_2 = 0;
        child            = wp->child_28;
        child->routine_1 = 9;
        child->routine_2 = 0;
        D_8010A5E0       = 0;
    }
}

void func_801018DC(STAGE_ROOM *wp)
{
    STAGE_XYZ pos;

    if (wp->frame_10 == 0)
    {
        // The same object three times (retail).
        wp->child_28->flags_0 &= ~2;
        wp->child_28->flags_0 &= ~2;
        wp->child_28->flags_0 &= ~2;
        pos.x = 300;
        pos.y = -500;
        pos.z = 0x1900;
        func_80104448(&pos, 0x30, 1, 0x1E, -3, 1);
        pos.x = -300;
        pos.y = -400;
        pos.z = 0x1900;
        func_80104448(&pos, 0x30, 1, 0x1E, -2, 1);
        func_801002C8(3);
    }
    if (wp->frame_10 == 0x3B)
    {
        Obj_work_flag_change(0x40, 0x80);
    }
}

void func_801019DC(STAGE_ROOM *wp)
{
    STAGE_XYZ pos;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_801002C8(1);
        child                     = wp->child_2C;
        child->routine_1          = 2;
        child->position_fixed.v.x = -0x07980000;
        child->position_fixed.v.z = 0x08000000;
        child->routine_2          = 0;
        child->position_fixed.v.y = 0;
        child->rotation.y         = 0x130;
        child->flags_0 |= 2;
        pos.x = -0x7EE;
        pos.y = -0x17;
        pos.z = 0x802;
        func_80104448(&pos, 0x10, 0, 0x1E, -2, 1);
        pos.x = -0x76C;
        pos.y = -0xA;
        pos.z = 0x7EE;
        func_80104448(&pos, 0x10, 0, 0x1E, -2, 1);
        pos.x = -0x7C6;
        pos.y = 0;
        pos.z = 0x866;
        func_80104448(&pos, 0x10, 0, 0x1E, -2, 1);
    }
    D_8010A5E4 = 1;
    D_8010A5E8 = D_8010A5EC = D_8010A5F0 = 0x20;
    D_8010A5F4                           = 2;
}

void func_80101B2C(STAGE_ROOM *wp)
{
    // Never used; it reserves retail's frame.
    STAGE_XYZ unused;
    STAGE_FX *fx;
    STAGE_EV *ev;
    sint32 i;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80106C30;
    func_8001EAE8(&D_80107328[0]);
    func_8001EAE8(&D_80107328[1]);
    func_8001EAE8(&D_80107328[2]);
    func_8001EAE8(&D_80107328[3]);
    func_8001EAE8(&D_80107328[4]);
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        D_8010A5D4  = (STAGE_OBJ *)fx;
        fx->flags_0 = 1;
        fx->kind_2  = 1;
        fx->value_C = 1;
        fx->timer_D = 1;
        fx->x_1C    = 0x50;
        fx->y_1E    = 0x40;
    }
    ev = Open_EVE_WORK();
    if (ev != NULL)
    {
        ev->flags_0 = 1;
        ev->kind_2  = 6;
        ev->value_F = 0;
        ev->flags_6 |= 0x20;
    }
    for (i = 0; i < 4; i++)
    {
        ev = Open_EVE_WORK();
        if (ev != NULL)
        {
            ev->flags_0   = 1;
            ev->kind_2    = 4;
            ev->variant_3 = i + 10;
            ev->flags_6 |= 0x20;
        }
    }
    D_8010A5E0 = 0;
    wp->tbl_A4 = D_8010738C;
}

void func_80101C80(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101CC0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    switch (wp->routine_4)
    {
        case 0:
            pl = &Player_work;
            if (func_80042238(pl) != 0)
            {
                pl->flags_0 &= ~3;
                wp->routine_4++;
            }
            break;
        case 1:
            Cd_xa_play_id(0x20000004);
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x14;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                func_80017C30(2);
                wp->routine_4++;
            }
            break;
        case 4:
            func_80101B2C(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(10);
                wp->routine_4++;
            }
            // fall through
        case 6:
            func_80101C80(wp);
            func_8001EC0C();
            if (D_8010A5E4 != 0)
            {
                func_8010032C(D_8010A5E8, D_8010A5EC, D_8010A5F0, D_8010A5F4);
            }
            switch (D_8010A5E0)
            {
                case 0:
                    D_800BC7D4 = 0;
                    break;
                case 1:
                    D_800BC7D4 = D_801074B4[ST02_FRAME & 3] << 16;
                    break;
                case 2:
                    D_800BC7D0 = D_801074BC[ST02_FRAME & 1] << 16;
                    break;
            }
            Sce_event_update();
            if (wp->routine_4 == 6 && D_80098A72 == 0)
            {
                D_800C356C = 2;
                D_800C356E = 3;
                D_800C356F = 1;
                D_800C3560 = 0;
                D_800C3562 = 0;
                D_800C3564 = 0;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 2;
                Sce_flag_off(0x600);
                Sce_flag_off(0);
                wp->flags_0 = 0;
                func_8001D494_2(0, 1);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}

void func_80101FD8(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x21080200;
    wp->value_78       = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_80102040(STAGE_OBJ *wp)
{
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_80102080(STAGE_OBJ *wp)
{
    wp->value_44.value = 0xFF9C0000;
    wp->value_48.value = 0xF4000000;
    wp->value_4C.value = 0x1000000;
    wp->u_C.b.byte_C   = -0x4C;
    wp->routine_2++;
}

void func_801020B0(STAGE_OBJ *wp)
{
    wp->position_fixed.v.x += -3.555555556 * 0x10000;
    wp->value_44.value += 0.55555556 * 0x10000;
    wp->value_48.value += 4.26666666 * 0x10000;
    wp->value_4C.value += -1.422222222 * 0x10000;
    if (--wp->u_C.b.byte_C == 0)
    {
        wp->routine_2++;
    }
}

void func_801021D0(void)
{
}

void func_801021D8(STAGE_OBJ *wp)
{
    D_801074C0[wp->routine_2](wp);
    wp->rotation.x = wp->value_44.value >> 16;
    wp->rotation.y = wp->value_48.value >> 16;
    wp->rotation.z = wp->value_4C.value >> 16;
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_80102244(STAGE_OBJ *wp)
{
    wp->routine_2++;
}

void func_80102258(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += -0xC977A;
}

void func_80102270(void)
{
}

void func_80102278(STAGE_OBJ *wp)
{
    D_801074CC[wp->routine_2](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_801022CC(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_C = 0x4B;
    wp->rotation.z   = 0;
    wp->rotation.x   = 0;
    wp->rotation.y   = 0;
    wp->routine_2++;
}

void func_801022F0(STAGE_OBJ *wp)
{
    sint8 temp_v0;

    temp_v0          = (uint8)wp->u_C.b.byte_C - 1;
    wp->u_C.b.byte_C = temp_v0;
    if ((temp_v0 << 0x18) == 0)
    {
        wp->routine_2++;
    }
    wp->rotation.y = (uint16)wp->rotation.y + 5;
}

void func_80102330(void)
{
}

void func_80102338(STAGE_OBJ *wp)
{
    D_801074D8[wp->routine_2](wp);
    Obj_pos_set(wp, 0x100, 0, 0);
}

void func_80102394(STAGE_OBJ *wp)
{
    wp->value_48.value = 0x4000000;
    wp->value_4C.value = 0xFF000000;
    wp->value_44.value = 0;
    wp->u_C.b.byte_C   = 1;
    wp->routine_2++;
}

void func_801023C0(STAGE_OBJ *wp)
{
    if (--wp->u_C.b.byte_C == 0)
    {
        wp->u_C.b.byte_C = 0x2D;
        wp->routine_2++;
    }
}

void func_801023F4(STAGE_OBJ *wp)
{
    if (--wp->u_C.b.byte_C == 0)
    {
        wp->u_C.b.byte_C = 0x2D;
        wp->routine_2++;
    }
    wp->value_48.value += -0x17DDDD;
    wp->value_4C.value += 0x111111;
}

void func_80102450(void)
{
}

void func_80102458(STAGE_OBJ *wp)
{
    D_801074E4[wp->routine_2](wp);
    wp->rotation.x = wp->value_44.value >> 16;
    wp->rotation.y = wp->value_48.value >> 16;
    wp->rotation.z = wp->value_4C.value >> 16;
    func_80030150(&wp->position_fixed.v, &wp->position);
    if ((ST02_FRAME & 3) == 3)
    {
        func_80105724(wp, 400, -100, 0, 1);
        func_80105724(wp, -400, -100, 200, 1);
    }
}

void func_80102514(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    wp->value_48.value = 0x8000000;
    wp->value_4C.value = 0;
    wp->u_C.b.byte_C   = 0;
    wp->routine_2++;
}

void func_80102538(STAGE_OBJ *wp)
{
    sint8 count;

    count = ++wp->u_C.b.byte_C;
    if (count >= 70 && (count & 1))
    {
        func_80105724(wp, 0, 500, 400, 0);
        func_80105724(wp, -100, 500, 400, 0);
        func_80105724(wp, 100, 500, 400, 0);
    }
    if (wp->u_C.b.byte_C == 90)
    {
        func_80105C28(wp, 0, 500, 600);
    }
    if (wp->u_C.b.byte_C == 100)
    {
        wp->u_C.b.byte_C = 50;
        wp->routine_2++;
    }
    wp->position_fixed.v.z += 0xA00000;
    wp->position_fixed.v.y += 0xA0000;
}

void func_8010262C(STAGE_OBJ *wp)
{
    if (--wp->u_C.b.byte_C == 0)
    {
        wp->routine_2++;
    }
    wp->position_fixed.v.z += 0xA00000;
    if (wp->u_C.b.byte_C & 1)
    {
        func_80105724(wp, 0, 500, 300, 0);
        func_80105724(wp, -100, 500, 300, 0);
        func_80105724(wp, 100, 500, 300, 0);
    }
}

void func_801026E0(void)
{
}

void func_801026E8(STAGE_OBJ *wp)
{
    D_801074F4[wp->routine_2](wp);
    if ((ST02_FRAME & 3) == 3)
    {
        func_80105724(wp, 400, -100, 0, 1);
        func_80105724(wp, -400, -100, 200, 1);
    }
    wp->rotation.x = wp->value_44.value >> 16;
    wp->rotation.y = wp->value_48.value >> 16;
    wp->rotation.z = wp->value_4C.value >> 16;
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_801027A8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_C = 0;
        wp->routine_2++;
    }
    else
    {
        wp->position_fixed.v.y = rsin(++wp->u_C.b.byte_C << 6) * 0x320;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_80102830(STAGE_OBJ *wp)
{
    D_80107504[wp->routine_1](wp);
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_80102888(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80101FD8(wp);
        return;
    }
    func_80102830(wp);
}

void func_801028C8(STAGE_OBJ *wp)
{
    wp->rotation.z     = 0;
    wp->rotation.x     = 0;
    wp->rotation.y     = 0;
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
    func_80102914(wp);
}

void func_80102914(STAGE_OBJ *wp)
{
    if (wp->u_C.b.byte_C != wp->u_C.b.byte_D)
    {
        Model_work_init(wp, &wp->u_C);
        func_800322A8(wp, 0, 0);
    }
    wp->u_C.b.byte_D = (sint8)(uint8)wp->u_C.b.byte_C;
}

void func_80102970(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_80102990(STAGE_OBJ *wp)
{
    D_80107520[wp->routine_0](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_801029F4(STAGE_OBJ *wp, sint32 index)
{
    D_8010A5F8[0] = D_801075F0[index];
    D_8010A5FC[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_8010A5F8[0]->id, 0x2A, 0x33, 6));
}

void func_80102A68(STAGE_OBJ *wp, sint32 index)
{
    D_8010A600[0] = D_80107614[index];
    D_8010A604[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_8010A600[0]->id, 0x2A, 0x33, 6));
}

void func_80102ADC(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;
    sint16 *cnt;

    count = D_8010A5F8_S->count;
    if (count <= 0)
    {
        D_8010A5FC[0] = 0;
        D_8010A5F8[0] += count;
    }
    cnt = D_8010A5FC;
    (*cnt)++;
    p = D_8010A5F8[0];
    if (*cnt == p->count)
    {
        D_8010A5F8_S = p + 1;
        *cnt         = 0;
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(p[1].id, 0x2A, 0x33, 6));
    }
    count = D_8010A600_S->count;
    if (count <= 0)
    {
        D_8010A604[0] = 0;
        D_8010A600[0] += count;
    }
    cnt = D_8010A604;
    (*cnt)++;
    p = D_8010A600[0];
    if (*cnt == p->count)
    {
        D_8010A600_S = p + 1;
        *cnt         = 0;
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(p[1].id, 0x2A, 0x33, 6));
    }
}

void func_80102C44(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_8010A608.cue_0->u.end != 0xFF && D_8010A608.cue_0->u.scene == scene->u_8.value_8 && D_8010A608.cue_0->line == scene->value_1C)
    {
        func_801029F4(wp, D_8010A608.cue_0->index);
        D_8010A608.cue_0++;
    }
    if (D_8010A608.cue_4->u.end != 0xFF && D_8010A608.cue_4->u.scene == scene->u_8.value_8 && D_8010A608.cue_4->line == scene->value_1C)
    {
        func_80102A68(wp, D_8010A608.cue_4->index);
        D_8010A608.cue_4++;
    }
    func_80102ADC(wp);
}

void func_80102D54(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0x10, 0);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    D_8010A608.cue_0   = D_80107644;
    D_8010A608.cue_4   = D_80107688;
    wp->rotation.y     = 0x800;
    wp->routine_0++;
}

void func_80102DDC(STAGE_OBJ *wp)
{
    func_800322A8(wp, 0x10, 0);
    wp->routine_3 = 0;
    wp->routine_2++;
}

void func_80102E1C(STAGE_OBJ *wp)
{
    wp->position_fixed.v.y += 0x23333;
    if (*wp->anim_98 == 0x1B)
    {
        wp->routine_3++;
    }
    if (wp->routine_3 == 4)
    {
        func_800322A8(wp, 0x11, 0);
        wp->routine_2++;
    }
}

void func_80102EA4(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 7)
    {
        wp->routine_2++;
    }
}

void func_80102ED4(STAGE_OBJ *wp)
{
    wp->position_fixed.v.y += 0x30000;
    if (*wp->anim_98 == 0x11)
    {
        wp->routine_2++;
    }
}

void func_80102F14(void)
{
}

void func_80102F1C(STAGE_OBJ *wp)
{
    D_801076FC[wp->routine_2](wp);
}

void func_80102F58(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x12, 0);
        wp->routine_2++;
    }
}

void func_80102FA4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x13, 0);
        wp->routine_2++;
    }
}

void func_80102FF0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x14, 0);
        wp->routine_2++;
    }
}

void func_8010303C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x15, 0);
        wp->routine_2++;
    }
}

void func_80103088(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_801030D4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x17, 0);
        wp->routine_2++;
    }
}

void func_80103120(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x18, 0);
        wp->routine_2++;
    }
}

void func_8010316C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x19, 0);
        wp->routine_2++;
    }
}

void func_801031B8(STAGE_OBJ *wp)
{
    func_800322A8(wp, 0x1AU, 0);
    wp->u_C.b.byte_C = 0;
    wp->routine_2++;
}

void func_801031F8(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_C = (uint8)wp->u_C.b.byte_C + 1;
    if (*wp->anim_98 == 0x10)
    {
        wp->routine_2++;
    }
}

void func_80103230(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x268000;
    if (*wp->anim_98 == 0x18)
    {
        wp->routine_2++;
    }
}

void func_80103274(void)
{
}

void func_8010327C(STAGE_OBJ *wp)
{
    D_80107710[wp->routine_2](wp);
}

void func_801032B8(STAGE_OBJ *wp)
{
    D_80107720[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_80103320(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80102D54(wp);
        return;
    }
    func_801032B8(wp);
}

void func_80103360(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 0)
    {
        func_80103320(wp);
        func_80102C44(wp);
    }
}

void func_801033A4(STAGE_OBJ *wp, sint32 index)
{
    D_8010A610[0] = D_8010781C[index];
    D_8010A614[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_8010A610[0]->id, 0x33, 0x37, 5));
}

void func_80103418(STAGE_OBJ *wp, sint32 index)
{
    D_8010A618[0] = D_80107844[index];
    D_8010A61C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_8010A618[0]->id, 0x33, 0x37, 5));
}

// this keeps their address in t0 for both.
void func_8010348C(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;
    sint16 *cnt;

    count = D_8010A610_S->count;
    if (count <= 0)
    {
        D_8010A614[0] = 0;
        D_8010A610[0] += count;
    }
    cnt = D_8010A614;
    (*cnt)++;
    p = D_8010A610[0];
    if (*cnt == p->count)
    {
        D_8010A610_S = p + 1;
        *cnt         = 0;
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(p[1].id, 0x33, 0x37, 5));
    }
    count = D_8010A618_S->count;
    if (count <= 0)
    {
        D_8010A61C[0] = 0;
        D_8010A618[0] += count;
    }
    cnt = D_8010A61C;
    (*cnt)++;
    p = D_8010A618[0];
    if (*cnt == p->count)
    {
        D_8010A618_S = p + 1;
        *cnt         = 0;
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(p[1].id, 0x33, 0x37, 5));
    }
}

void func_801035F4(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_8010A620.cue_0->u.end != 0xFF && D_8010A620.cue_0->u.scene == scene->u_8.value_8 && D_8010A620.cue_0->line == scene->value_1C)
    {
        func_801033A4(wp, D_8010A620.cue_0->index);
        D_8010A620.cue_0++;
    }
    if (D_8010A620.cue_4->u.end != 0xFF && D_8010A620.cue_4->u.scene == scene->u_8.value_8 && D_8010A620.cue_4->line == scene->value_1C)
    {
        func_80103418(wp, D_8010A620.cue_4->index);
        D_8010A620.cue_4++;
    }
    func_8010348C(wp);
}

void func_80103704(STAGE_OBJ *wp)
{
    ((ST02_INIT3_FUNC)Model_work_init)(wp, NULL, 0);
    wp->scale.words[0]               = 0x2000200;
    wp->scale.words[1]               = 0x42100200;
    ((ST02_FACE_PREV *)wp)->prev_147 = -1;
    ((ST02_FACE_PREV *)wp)->prev_143 = -1;
    D_8010A620.cue_0                 = D_80107868;
    D_8010A620.cue_4                 = D_801078D0;
    wp->routine_0++;
}

void func_80103788(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801037D4(STAGE_OBJ *wp)
{
    func_800322A8(wp, 7, 0);
    wp->u_C.b.byte_C = 0x5A;
    wp->routine_2++;
}

void func_80103818(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_C = (uint8)wp->u_C.b.byte_C - 1;
    if (*wp->anim_98 == 0x1C)
    {
        wp->routine_2++;
    }
}

void func_80103850(ST02_CHILD *wp)
{
    if (--wp->timer_C == 0)
    {
        wp->parent_44->routine_0++;
    }
}

void func_8010388C(void)
{
}

void func_80103894(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        wp->routine_2++;
    }
}

void func_801038E0(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_80103934(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x22)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_80103988(void)
{
}

void func_80103990(STAGE_OBJ *wp)
{
    D_80107994[wp->routine_2](wp);
}

void func_801039CC(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_80103A20(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80103A74(void)
{
}

void func_80103A7C(STAGE_OBJ *wp)
{
    D_801079A0[wp->routine_2](wp);
}

void func_80103AB8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80103B04(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_80103B50(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        wp->routine_2++;
    }
}

void func_80103B9C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        wp->routine_2++;
    }
}

void func_80103BE8(STAGE_OBJ *wp)
{
    func_800322A8(wp, 9, 0);
    wp->routine_2++;
}

void func_80103C28(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x12)
    {
        wp->routine_2++;
    }
}

void func_80103C58(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x2C0000;
    if (*wp->anim_98 == 0x17)
    {
        wp->routine_2++;
    }
}

void func_80103C98(void)
{
}

void func_80103CA0(STAGE_OBJ *wp)
{
    D_801079AC[wp->routine_2](wp);
}

void func_80103CDC(STAGE_OBJ *wp)
{
    D_801079BC[wp->routine_1](wp);
}

void func_80103D18(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80103704(wp);
    }
    func_80103CDC(wp);
    if (wp->u_C.b.byte_C == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_801035F4(wp);
    func_80103D8C(wp);
}

// One tbl variable for every case: case 7 sets it in one block and indexes it in the next,
// so it stays a register while the other cases fold to lui/%lo.
void func_80103D8C(STAGE_OBJ *wp)
{
    STAGE_OBJ *obj;
    sint16 *tbl;
    sint32 rot;

    obj               = ST02_SCENE_OBJ;
    obj->u_C.b.byte_C = 1;
    switch (wp->anim_AC)
    {
        case 0:
            break;
        case 1:
            tbl             = D_801079E4;
            rot             = -tbl[*wp->anim_98];
            obj->rotation.z = rot;
            break;
        case 2:
            tbl             = D_801079E4;
            rot             = -tbl[*wp->anim_98];
            obj->rotation.z = rot;
            break;
        case 3:
            tbl             = D_801079E4;
            rot             = -tbl[*wp->anim_98];
            obj->rotation.z = rot;
            break;
        case 4:
            tbl             = D_80107A26;
            rot             = -tbl[*wp->anim_98];
            obj->rotation.z = rot;
            break;
        case 5:
            obj->rotation.z = 0x13E;
            break;
        case 6:
            obj->rotation.z = -0x3F;
            break;
        case 7:
            tbl = D_80107A6C;
            if (*wp->anim_98 < 0x1F)
            {
                rot             = -tbl[*wp->anim_98];
                obj->rotation.z = rot;
            }
            else
            {
                obj->u_C.b.byte_C = 0;
                obj->rotation.z -= 0x11C;
            }
            break;
        case 8:
            obj->rotation.z = -0x13E;
            break;
        case 9:
            obj->rotation.z = -0x13E;
            if (*wp->anim_98 >= 0x12)
            {
                obj->u_C.b.byte_C = 0;
            }
            break;
    }
}

void func_80103F08(STAGE_OBJ *wp)
{
    ((ST02_INIT3_FUNC)Model_work_init)(wp, NULL, 0);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_80103F5C(STAGE_OBJ *wp)
{
    sint8 temp_v0;

    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->u_C.b.byte_C = 0;
        wp->routine_2++;
    }
    else
    {
        temp_v0          = (uint8)wp->u_C.b.byte_C + 1;
        wp->u_C.b.byte_C = temp_v0;
        if (temp_v0 == 0x1E)
        {
            wp->routine_1 = 1;
            wp->routine_2 = 0;
        }
        func_80032488(wp);
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_80103FEC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
        if (*wp->anim_98 == 0x47)
        {
            wp->routine_1 = 0;
            wp->routine_2 = 0;
        }
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_80104070(STAGE_OBJ *wp)
{
    func_80030150(&wp->position_fixed.v, &wp->position);
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->u_C.b.byte_C = 0;
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
}

void func_801040D8(STAGE_OBJ *wp)
{
    D_80107AAC[wp->routine_1](wp);
}

void func_80104114(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80103F08(wp);
        return;
    }
    func_801040D8(wp);
}

void func_80104154(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 0)
    {
        func_80104114(wp);
    }
}

void func_80104184(ST02_SPARK *wp)
{
    ST02_SPARK *owner;

    owner = wp->owner_2C;
    if (--wp->timer_D == 0 || owner->routine_0 == 2)
    {
        wp->timer_D = 0;
        wp->routine_0++;
    }
    wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
    wp->w_24 += wp->type_F;
    wp->y_1E += wp->rise_28;
}

void func_80104210(ST02_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_80104184(wp);
}

void func_80104244(STAGE_FX *wp)
{
    func_80031988(wp);
}

void func_80104264(ST02_SPARK *wp)
{
    D_80107AB8[wp->routine_0](wp);
}

void func_801042A0(ST02_SPARK *wp)
{
    ST02_SPARK *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->variant_3 = 1;
            ep->flags_6   = wp->flags_6;
            ep->value_C   = 0;
            ep->timer_D   = (rand() & 7) * 2 + 0x40;
            ep->x_1C      = wp->x_1C + (rand() & 0xF);
            ep->y_1E      = wp->y_1E;
            ep->z_20      = wp->z_20 + (rand() & 0xF);
            ep->mode_14   = 0x3D48004E;
            ep->u_22      = ((rand() & 3) << 5) + 0x20;
            ep->v_23      = 0;
            ep->w_24      = wp->width_E;
            ep->type_F    = wp->type_F;
            ep->rise_28   = wp->rise_28;
            ep->owner_2C  = wp;
            for (i = 0; i < wp->count_26; i++)
            {
                func_80104264(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_801043E8(ST02_SPARK *wp)
{
    if (wp->variant_3 == 1)
    {
        func_80104264(wp);
    }
    else if (wp->routine_0 != 2)
    {
        func_801042A0(wp);
    }
    else
    {
        func_80031988(wp);
    }
}

ST02_SPARK *func_80104448(STAGE_XYZ *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag)
{
    ST02_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0;
        ep->variant_3 = 0;
        ep->value_C   = 0;
        ep->width_E   = width;
        ep->type_F    = growth;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->count_26  = count;
        if (flag)
        {
            ep->flags_6 |= 0x20;
        }
        else
        {
            ep->flags_6 &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < count; i++)
        {
            func_801042A0(ep);
        }
    }
    return ep;
}

void func_80104550(STAGE_OBJ *wp)
{
    sint32 i;

    for (i = 9; i >= 0; i--)
    {
        D_8010A628[i].b[0] = 0;
    }
    D_8010A628[0].w[0] = 0x500201;
    D_8010A628[0].w[1] = 0x20204028;
    D_8010A628[1].w[0] = 0x1E0101;
    D_8010A628[1].w[1] = 0x28283808;
    D_8010A628[2].w[0] = -0x13FEFF;
    D_8010A628[2].w[1] = 0x10101004;
    D_8010A628[3].w[0] = -0x1DFDFF;
    D_8010A628[3].w[1] = 0x38383808;
    D_8010A628[4].w[0] = -0x31FEFF;
    D_8010A628[4].w[1] = 0x4040400A;
    D_8010A628[5].w[0] = -0x63FDFF;
    D_8010A628[5].w[1] = 0x20203012;
    D_8010A628[6].w[0] = -0x81FEFF;
    D_8010A628[6].w[1] = 0x1010101A;
    D_8010A628[7].w[0] = -0x95FDFF;
    D_8010A628[7].w[1] = 0x28282824;
    wp->routine_0++;
}

// The cell offset is read once into u; writing v2 and v3 together keeps 0xFF inside the loop.
void func_8010469C(STAGE_OBJ *wp)
{
    POLY_FT4 *p;
    ST02_FLARE *rec;
    sint32 i;
    sint32 x;
    sint32 y;
    sint32 x0;
    sint32 y0;
    sint32 u;

    if (wp->u_C.b.byte_D != 0)
    {
        for (i = 0, rec = D_8010A628; i < 10; rec++, i++)
        {
            if (rec->f.on != 0)
            {
                x = ((sint16)wp->position_fixed.f.x.words.fraction - 0xA0) * rec->f.scale / 100 + 0xA0;
                y = (wp->position_fixed.f.x.words.integer - 0x78) * rec->f.scale / 100 + 0x78;
                p = (*STAGE_PACKET_PTR)++;
                setlen(p, 9);
                p->code = 0x2E;
                p->r0   = rec->f.r;
                p->g0   = rec->f.g;
                p->b0   = rec->f.b;
                x0      = x - rec->f.size;
                p->x0 = p->x2 = x0;
                x0 += rec->f.size * 2;
                p->x1 = p->x3 = x0;
                y0            = y - rec->f.size;
                p->y0 = p->y1 = y0;
                y0 += rec->f.size * 2;
                p->y2 = p->y3 = y0;
                u             = rec->f.cell * 64;
                p->v0 = p->v1 = 0xC0;
                p->u0 = p->u2 = u + 0x40;
                p->u1 = p->u3 = u + 0x7F;
                p->v2 = p->v3 = 0xFF;
                p->clut       = 0x7F48;
                p->tpage      = 0x3B;
                addPrim(&Disp_env_ptr->ot_78, p);
            }
        }
    }
}

void func_80104870(STAGE_OBJ *wp)
{
    if (wp->u_C.b.byte_D != 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80104550(wp);
            return;
        }
        func_8010469C(wp);
    }
}

void func_801048C0(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;

    wp->z_34.value += 0x8000;
    wp->x_2C.half[1] += (wp->value_38.value -= 0x147A) >> 16;
    wp->x_2C.half[0] = (wp->x_2C.half[0] + (wp->z_34.value >> 16)) & 0xFFF;
    if (wp->x_2C.half[1] < 0)
    {
        func_80031988(wp);
        return;
    }
    v.x = (rcos(wp->x_2C.half[0]) * wp->x_2C.half[1]) >> 12;
    v.y = (rsin(wp->x_2C.half[0]) * wp->x_2C.half[1]) >> 12;
    v.z = 0;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY(wp->y_30.half[0], &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = wp->u_28.parent->x_1C + out.x;
    wp->y_1E = wp->u_28.parent->y_1E + out.y;
    wp->z_20 = wp->u_28.parent->z_20 + out.z;
}

void func_80104A04(STAGE_FX *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->routine_0++;
    }
    func_801048C0(wp);
}

void func_80104A4C(STAGE_FX *wp)
{

    wp->frame_E = 0;
    wp->flags_0 |= 2;
    if (Game_work.value_50 == 0x16)
    {
        wp->mode_14 = 0x3CC80027;
    }
    else
    {
        wp->mode_14 = 0x3C880026;
    }
    wp->color_18       = 0x2E808080;
    wp->value_38.value = 0xA0000;
    wp->h_26           = 0;
    wp->z_34.value     = 0;
    wp->value_3C.value = -0x10000;
    wp->routine_0++;
}

void func_80104AB8(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    STAGE_FX *ep;
    sint16 angle;
    sint16 radius;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = out.x + (parent->position_fixed.v.x >> 16);
    wp->y_1E = out.y + (parent->position_fixed.v.y >> 16);
    wp->z_20 = out.z + (parent->position_fixed.v.z >> 16);
    if (wp->z_34.value < 0x900000)
    {
        wp->z_34.value += 0x170A3;
        wp->value_38.value += 0x8000;
        wp->value_3C.value -= 0x147A;
    }
    wp->h_26 = (wp->h_26 + 1) & 3;
    wp->w_24 = wp->z_34.value >> 16;
    wp->u_22 = D_80107AC4[wp->h_26].u;
    wp->v_23 = D_80107AC4[wp->h_26].v;
    if (++wp->frame_E == 4)
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0        = 1;
            ep->kind_2         = 6;
            ep->variant_3      = 0;
            ep->value_C        = 6;
            ep->timer_D        = 1;
            angle              = rand() & 0xFFF;
            radius             = (rand() & 0x1F) + 0x64;
            ep->mode_14        = 0x3C48002E;
            ep->w_24           = 0x12;
            ep->u_22           = 0x80;
            ep->color_18       = 0x2E202020;
            ep->v_23           = 0xA0;
            ep->u_28.parent    = wp;
            ep->x_2C.half[0]   = angle;
            ep->x_2C.half[1]   = radius;
            ep->y_30.half[0]   = rot;
            ep->z_34.value     = wp->value_38.value;
            ep->value_38.value = wp->value_3C.value;
        }
        wp->frame_E = 0;
    }
}

void func_80104CCC(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80104A4C(wp);
        }
        func_80104AB8(wp);
    }
    else
    {
        func_80104A04(wp);
    }
}

void func_80104D30(STAGE_FX *wp)
{
    wp->flags_0 |= 2;
    if (Game_work.value_50 == 0x16)
    {
        wp->mode_14 = 0x3CC80027;
    }
    else
    {
        wp->mode_14 = 0x3C880026;
    }
    wp->color_18 = 0x2E808080;
    wp->h_26     = 0;
    wp->routine_0++;
}

void func_80104D88(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = out.x + (parent->position_fixed.v.x >> 16);
    wp->y_1E = out.y + (parent->position_fixed.v.y >> 16);
    wp->z_20 = out.z + (parent->position_fixed.v.z >> 16);
    if (++wp->h_26 == 4)
    {
        wp->h_26 = 0;
    }
    wp->u_22 = D_80107AD4[wp->h_26].u;
    wp->v_23 = D_80107AD4[wp->h_26].v;
    wp->w_24 = D_80107AD4[wp->h_26].w;
}

void func_80104EC8(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80104D30(wp);
        }
        func_80104D88(wp);
    }
}

void func_80104F1C(STAGE_FX *wp)
{
    sint8 frame;

    frame = ++wp->type_F;
    if (frame == 8)
    {
        func_80031988(wp);
        return;
    }
    wp->color_18 = D_80107AE4[frame];
    wp->w_24 += 0x10;
    if (wp->w_24 > 0x120)
    {
        wp->w_24 = 0x120;
    }
}

void func_80104F9C(STAGE_FX *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->routine_0++;
    }
    func_80104F1C(wp);
}

void func_80104FE4(STAGE_FX *wp)
{
    wp->routine_0++;
}

void func_80104FF8(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    STAGE_FX *ep;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 6;
        ep->variant_3 = 2;
        ep->value_C   = 6;
        ep->timer_D   = 1;
        ep->frame_E   = 0;
        ep->type_F    = 0;
        if (Game_work.value_50 == 0x16)
        {
            ep->mode_14 = 0x3CC80027;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->w_24     = 0x90;
        ep->u_22     = 0xA0;
        ep->v_23     = 0x20;
        ep->x_1C     = out.x + (parent->position_fixed.v.x >> 16);
        ep->y_1E     = out.y + (parent->position_fixed.v.y >> 16);
        ep->z_20     = out.z + (parent->position_fixed.v.z >> 16);
        ep->color_18 = 0x2E808080;
    }
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 6;
        ep->variant_3 = 2;
        ep->value_C   = 6;
        ep->timer_D   = 1;
        ep->frame_E   = 1;
        ep->type_F    = 0;
        if (Game_work.value_50 == 0x16)
        {
            ep->mode_14 = 0x3CC80027;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->w_24     = 0x24;
        ep->u_22     = 0xA0;
        ep->v_23     = 0x20;
        ep->x_1C     = out.x + (parent->position_fixed.v.x >> 16);
        ep->y_1E     = out.y + (parent->position_fixed.v.y >> 16);
        ep->z_20     = out.z + (parent->position_fixed.v.z >> 16);
        ep->color_18 = 0x2E808080;
    }
}

void func_801051EC(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80104FE4(wp);
        }
        func_80104FF8(wp);
    }
    else
    {
        func_80104F9C(wp);
    }
}

void func_80105250(STAGE_FX *wp)
{
}

void func_80105258(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        func_80105250(wp);
    }
    else
    {
        func_80104F9C(wp);
    }
}

void func_80105298(STAGE_FX *wp)
{
    if (wp->routine_0 == 2)
    {
        func_80031988(wp);
    }
    else
    {
        D_80107B04[wp->variant_3](wp);
    }
}

STAGE_FX *func_801052F4(STAGE_FX *parent, sint32 x, sint32 y, sint32 z, uint8 variant)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0      = 1;
        fx->kind_2       = 6;
        fx->variant_3    = variant;
        fx->timer_D      = 0;
        fx->u_28.parent  = parent;
        fx->x_2C.half[0] = x;
        fx->x_2C.half[1] = y;
        fx->y_30.half[0] = z;
        return fx;
    }
    return NULL;
}

void func_80105380(STAGE_FX *wp)
{
    sint16 h;

    if (wp->routine_0 == 0)
    {
        wp->mode_14 = 0x3D08002E;
        wp->u_22    = 0x40;
        wp->v_23    = 0;
        wp->w_24    = 0x40;
        wp->flags_0 |= 2;
        wp->h_26 = ((rand() & 0xF) + 0x30) << 8;
        wp->y_1E = 0;
        wp->routine_0++;
    }
    h = wp->h_26;
    h -= 0x80;
    if (h == 0)
    {
        func_80031988(wp);
        return;
    }
    wp->color_18 = ((h >> 8) * 0x10101) | 0x2E000000;
    wp->h_26     = h;
    wp->y_1E--;
    wp->w_24 += 6;
}

void func_80105464(STAGE_FX *wp)
{
    sint16 h;

    if (wp->routine_0 == 0)
    {
        wp->mode_14 = 0x3D48004E;
        wp->flags_0 |= 2;
        wp->u_22 = ((rand() & 3) << 5) + 0x20;
        wp->v_23 = 0;
        wp->w_24 = 0x10;
        wp->h_26 = ((rand() & 0xF) + 0x20) << 8;
        wp->routine_0++;
    }
    h = wp->h_26;
    h -= 0x80;
    wp->w_24 += 8;
    wp->y_1E -= 8;
    if (h == 0)
    {
        func_80031988(wp);
        return;
    }
    wp->h_26     = h;
    wp->color_18 = ((h >> 8) * 0x10101) | 0x2E000000;
}

void func_8010554C(STAGE_FX *wp)
{
    STAGE_OBJ *parent;

    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->w_24 = 0x64;
        wp->routine_0++;
        wp->mode_14  = 0x3C80000F;
        wp->u_22     = 0;
        wp->v_23     = 0xA0;
        wp->color_18 = 0x2E808080;
    }
    if (wp->routine_0 == 2)
    {
        func_80031988(wp);
        return;
    }
    parent   = wp->u_28.object;
    wp->x_1C = (parent->position_fixed.v.x >> 16) + wp->x_2C.value;
    wp->y_1E = (parent->position_fixed.v.y >> 16) + wp->y_30.value;
    wp->z_20 = (parent->position_fixed.v.z >> 16) + wp->z_34.value;
}

void func_80105618(STAGE_FX *wp)
{
    ST02_PIECE piece;
    ST02_PIECE *p;
    sint32 i;

    if (--wp->y_1E <= 0)
    {
        func_80031988(wp);
        return;
    }
    p = D_80107B14;
    for (i = 0; i < 4; i++)
    {
        piece.id = p->id;
        piece.x  = wp->x_1C + p->x;
        piece.y  = wp->y_1E + p->y;
        piece.h  = p->h;
        piece.w  = p->w;
        func_8010592C(&piece);
        p++;
    }
}

void func_801056E8(STAGE_FX *wp)
{
    D_80107B44[wp->variant_3](wp);
}

STAGE_FX *func_80105724(STAGE_OBJ *wp, sint16 x, sint16 y, sint16 z, uint8 mode)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 7;
        fx->variant_3 = mode;
        fx->value_C   = 7;
        fx->timer_D   = 0;
        if (wp != NULL)
        {
            v.x = x + (rand() & 0x7F);
            v.y = y;
            v.z = z + (rand() & 0x7F);
            STAGE_MATRIX_IDENTITY_SCALAR(m.w);
            RotMatrixY(wp->rotation.y, &m.m);
            ApplyMatrixSV(&m.m, &v, &out);
            fx->x_1C = out.x + (wp->position_fixed.v.x >> 16);
            fx->y_1E = out.y + (wp->position_fixed.v.y >> 16);
            fx->z_20 = out.z + (wp->position_fixed.v.z >> 16);
        }
        else
        {
            fx->x_1C = x;
            fx->y_1E = y;
            fx->z_20 = z;
        }
        return fx;
    }
    return NULL;
}

STAGE_FX *func_80105884(STAGE_OBJ *wp, sint32 x, sint32 y, sint32 z)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->u_28.object = wp;
        fx->flags_0     = 1;
        fx->kind_2      = 7;
        fx->variant_3   = 2;
        fx->value_C     = 7;
        fx->flags_6 |= 0x20;
        fx->x_2C.value = (sint16)x;
        fx->y_30.value = (sint16)y;
        fx->z_34.value = (sint16)z;
    }
    return fx;
}

void func_8010592C(ST02_PIECE *piece)
{
    POLY_FT4 *p;
    sint16 pos;
    sint32 u;

    p = (*STAGE_PACKET_PTR)++;
    setlen(p, 9);
    p->code = 0x2E;
    p->r0 = p->g0 = p->b0 = 0x20;
    pos                   = piece->x - (piece->w >> 1);
    p->x0 = p->x2 = pos;
    p->x1 = p->x3 = pos + piece->w;
    pos           = piece->y - (piece->h >> 1);
    p->y0 = p->y1 = pos;
    p->y2 = p->y3 = pos + piece->h;
    u             = piece->id << 5;
    p->v2 = p->v3 = 0x1F;
    p->clut       = 0x3C48;
    p->v0 = p->v1 = 0;
    p->tpage      = 0x2E;

    p->u0 = p->u2 = u + 0x20;
    p->u1 = p->u3 = u + 0x3F;
    addPrim(&Disp_env_ptr->ot_78, p);
}

void func_80105A48(sint16 x, sint16 y, sint16 h)
{
    STAGE_FX *ep;

    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 7;
        ep->variant_3 = 3;
        ep->value_C   = 7;
        ep->x_1C      = x;
        ep->y_1E      = y;
        ep->h_26      = h;
    }
}

void func_80105AB8(ST02_SPINNER *wp)
{
    STCOM_FIXED_VECTOR scale;
    // Never used; they reserve retail's frame.
    STCOM_SVECTOR unused;
    STAGE_MATRIX m;
    STCOM_MATRIX unused2[2];
    uint8 variant;
    sint32 fall;

    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 6;
        variant = 0;
        Model_work_init(wp, &variant);
        wp->angle_E = 0x800;
        wp->roll_10 = 0;
        wp->fall_44 = -0x100000;
        wp->routine_0++;
    }
    STAGE_MATRIX_IDENTITY(m.w);
    RotMatrixZ(wp->roll_10, &m.m);
    RotMatrixY(wp->angle_E, &m.m);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&m.m, &scale);
    wp->matrix = m.m;
    fall       = wp->fall_44 += 0x53A0;
    wp->pos_38.x -= 0x17;
    wp->pos_38.y += fall >> 16;
    wp->pos_38.z -= 0x34;
    wp->angle_E += 0x40;
    wp->roll_10 -= 0x28;
    func_8002CA10(&wp->pos_38, 0x1F4, 0x200, 0);
}

void func_80105C28(STAGE_OBJ *wp, sint32 x, sint32 y, sint32 z)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STAGE_50 *ep;

    ep = func_80031734();
    if (ep != NULL)
    {
        ep->flags_0 = 1;
        ep->kind_2  = 0xD;
        v.x         = x;
        v.y         = y;
        v.z         = z;
        STAGE_MATRIX_IDENTITY_SCALAR(m.w);
        RotMatrixY(wp->rotation.y, &m.m);
        ApplyMatrixSV(&m.m, &v, &ep->pos_38);
        ep->pos_38.x += wp->position_fixed.v.x >> 16;
        ep->pos_38.y += wp->position_fixed.v.y >> 16;
        ep->pos_38.z += wp->position_fixed.v.z >> 16;
        ep->color_40 = 0x808080;
    }
}
