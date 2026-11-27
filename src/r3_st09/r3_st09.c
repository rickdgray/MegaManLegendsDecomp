#include "common.h"
#include "st09.h"

void func_80100330(void)
{
    STAGE_TABLE_3C0 = D_8011CCBC;
    STAGE_TABLE_5A4 = D_8011CDCC;
    STAGE_TABLE_10C = D_8011CDD8;
    STAGE_TABLE_48  = D_8011CE28;
    STAGE_TABLE_24  = D_8011CE68;
    STAGE_TABLE_50  = D_8011CEF0;
}

// Sets up the current room: map, spawns.
void func_80100398(void)
{
    STAGE_PL_VIEW *pl;
    sint32 room;
    void *spawn;
    sint16 *cells;

    room                      = Game_work.value_51;
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[room].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[room].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[room].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[room].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[room].cells;
    pl                        = &STAGE_PL;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    switch (room)
    {
        case 0:
            if (STAGE_GAME_VALUE_52 >= 7)
            {
                D_8011D4B2 = 0x1B;
            }
            else
            {
                D_8011D4B2 = 3;
            }
            break;
        case 1:
            if (STAGE_GAME_VALUE_52 >= 7)
            {
                D_8011D542 = 0x1B;
            }
            else
            {
                D_8011D542 = 3;
            }
            break;
        case 2:
            if (Sce_flag_test(6) && !Sce_flag_test(0x2C))
            {
                D_8011D67B = 1;
            }
            else
            {
                D_8011D67B = 0;
            }
            break;
    }
    pl->value_44E   = 1;
    spawn           = D_8011D488[Game_work.value_51];
    STAGE_MAP_EXITS = D_8011DAAC[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_8011DC38[D_8011DC90[Game_work.value_51]], D_8011DAD0[Game_work.value_51]);
    func_8005DC10(D_8011BBB4[Game_work.value_51]);
    func_801005F4();
}

void func_801005F4(void)
{
    Sce_flag_on(0x16);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_8010061C(void)
{
    D_8011DD20[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100670(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0xC))
            {
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_80100B20(0);
                wp->routine_4 = 1;
            }
            break;
        case 1:
            if (Sce_flag_test(0x60C))
            {
                func_8001DDE4(0x17);
                STAGE_SCENE_BYTE(4) = 0;
                wp->routine_4       = 0xFF;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_8010071C(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_8010074C(STAGE_ROOM *wp)
{
    D_8011DD64[wp->routine_4](wp);
}

void func_80100788(STAGE_ROOM_WORK *wp)
{
    STAGE_PL_VIEW *pl;
    ST09_STCOM36_OBJ *obj;

    pl  = &STAGE_PL;
    obj = D_8011EA60[0];
    switch (wp->routine_6)
    {
        case 0:
            if (func_80042238(pl))
            {
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0           = D_8011DD8C;
                wp->tbl_A4           = D_8011DD7C;
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.fixed_428.x = 0x58620000;
                STAGE_PL.fixed_428.y = 0xFDBF0000;
                STAGE_PL.fixed_428.z = 0x1D8B0000;
                STAGE_PL.flags_bd |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                STAGE_PL.value_442 = 0xDD4;
                STAGE_PL.value_440 = 0;
                STAGE_PL.value_444 = 0;
                STAGE_PL.value_448 = 0x30;
                wp->timer_C        = 0x1E;
                wp->routine_6++;
                Obj_work_flag_change(0x3FE, 5);
                obj->be_flag |= 3;
                obj->flags |= 3;
            }
            break;
        case 1:
            if (--wp->timer_C == 0)
            {
                wp->timer_C = 0x24;
                wp->routine_6++;
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
            }
            break;
        case 2:
            if (Sce_flag_test(0x60D))
            {
                if (wp->timer_C == 0x24)
                {
                    STAGE_PL.value_448 = 0xD;
                }
                if (wp->timer_C != 0 && --wp->timer_C != 0)
                {
                    STAGE_PL.value_442 =
                        (STAGE_PL.value_442 + Muku(&pl->position, &obj->position, (sint16)STAGE_PL.value_442, 0x20)) & 0xFFF;
                }
                else
                {
                    pl->value_448 = 0x30;
                    wp->routine_6++;
                }
            }
            // fall through
        case 3:
            if (Sce_flag_test(0xC))
            {
                func_80042314(pl);
                wp->flags_0 = 0;
                D_800A395C  = 1;
                Obj_work_flag_change(0x3FE, 0xA);
                obj->be_flag |= 3;
                obj->flags |= 3;
            }
            break;
    }
    if (wp->routine_6 != 0 && wp->routine_6 < 3)
    {
        if (*(uint8 *)wp->tbl_A4 != 0xFF)
        {
            wp->tbl_A4[1](wp);
        }
    }
    if (wp->routine_6 != 0 && wp->routine_6 < 3 && func_8001DE84())
    {
        func_80100BF0();
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        wp->routine_6 = 3;
        Sce_flag_on(0xC);
        pl->fixed_428.x = 0x58620000;
        pl->fixed_428.y = 0xFDBF0000;
        pl->fixed_428.z = 0x1D8B0000;
        func_80030150(&pl->fixed_428, &pl->pos_438);
        pl->value_442 = 0x961;
        pl->value_440 = 0;
        pl->value_444 = 0;
        pl->value_448 = 0x30;
    }
}

void func_80100AF8(void)
{
    Sce_camera_update();
    Sce_event_update();
}

void func_80100B20(sint8 skip)
{
    sint16 i;
    sint32 index;

    D_8011DD60 = 0;
    if (skip == 0)
    {
        for (i = 0; i < 1; i++)
        {
            index = D_8011DD68[i].index_0;
            Scene_obj_ent_open(&D_8011DD68[i]);
            D_8011EA60[index] = STAGE_SCENE_OBJ(index);
            D_8011EA60[index]->flags &= ~0x20;
            D_8011DD60 |= 0x80000000 >> index;
        }
    }
}

void func_80100BF0(void)
{
    ST09_STCOM36_OBJ *obj;
    sint32 kind;
    sint32 i;

    i = 0;
    while (D_8011DD60 != 0)
    {
        if (D_8011DD60 & (0x80000000 >> i))
        {
            obj  = D_8011EA60[i];
            kind = func_8002FE74(obj->slot);
            switch (kind)
            {
                case 0x20:
                    obj->routine_0 = 2;
                    ST09_STCOM36_TABLE_3C0[obj->id][obj->handler](obj);
                    break;
                case 0x60:
                    obj->routine_0 = 2;
                    ST09_STCOM36_TABLE_10C[obj->id](obj);
                    break;
            }
            D_8011DD60 &= ~(0x80000000 >> i);
        }
        i++;
    }
}

void func_80100D14(sint8 index)
{
    ST09_STCOM36_OBJ *obj;
    sint32 kind;
    if (D_8011DD60 & (0x80000000 >> index))
    {
        obj  = D_8011EA60[index];
        kind = func_8002FE74(obj->slot);
        if (kind == 0x20 || kind == 0x60)
        {
            obj->routine_0 = 2;
            ST09_STCOM36_TABLE_3C0[obj->id][obj->handler](obj);
        }
        D_8011DD60 &= ~(0x80000000 >> index);
    }
}

void func_80100DF4(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_SVECTOR *save;

    wp->value_AD            = wp->value_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_15C.h[1]          = 0x4210;
    wp->ext.u_2.h           = rand();
    D_8011DDD4[wp->routine_0](wp);
    ext = &wp->ext;
    if (wp->value_AD != wp->value_AC)
    {
        func_80032304(wp, wp->value_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    STAGE_SP_13A = ext->u_3C.h[0];
    Model_parts_mtx_set_y(wp);
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    ext->u_4C.i = 0;
    save        = D_8011E930;
    do
    {
        *save                = wp->position;
        D_8011E938           = wp->position_fixed;
        wp->u_64.h[0]        = wp->rotation.y;
        wp->position         = wp->vec_190;
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->position_fixed.z = wp->position.z << 16;
        wp->rotation.y       = (ext->u_3C.h[0] + wp->rotation.y) & 0xFFF;
        Obj_pos_set(wp, 0, -0x200, D_8011DE2C[ext->u_4C.i]);
        ext->u_44.fx[ext->u_4C.i]->x_1C = wp->position.x;
        ext->u_44.fx[ext->u_4C.i]->y_1E = wp->position.y;
        ext->u_44.fx[ext->u_4C.i]->z_20 = wp->position.z;
        wp->position                    = *save;
        wp->position_fixed              = D_8011E938;
        wp->rotation.y                  = wp->u_64.h[0];
        ext->u_4C.i++;
    } while (ext->u_4C.i < 2);
    if ((wp->be_flag & 2) && (ext->flags_0 & 4))
    {
        ext->pos_C = wp->vec_180;
        ext->pos_C.y += 30;
        func_800341BC(&ext->pos_C, 0x50, 0, 0x8000, wp->slot, &ext->value_14, ext->value_8 | 0x4880000, 0x800000, 0);
    }
    ext->value_14 = 0;
}

void func_8010116C(ST09_VIEW *wp)
{
    sint16 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_64.w[0]  = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->value_158               = 0x02000200;
    wp->u_15C.w[0]              = 0x200;
    wp->ext.flags_0             = 0x26;
    *(sint32 *)&wp->ext.u_4     = 0;
    *(sint32 *)&wp->ext.value_8 = 0;
    wp->ext.value_14            = 0;
    wp->ext.value_18            = 0;
    Track_reset(wp->ext.u_24.track, D_80098844[wp->id]->value_F, -0x60);
    wp->ext.u_34.h[0]         = 0;
    wp->ext.u_34.h[1]         = 0;
    wp->ext.u_3C.h[0]         = 0;
    wp->ext.u_38.h[0]         = 4;
    wp->ext.obj_40            = func_80036294(wp->u_C.b[1]);
    wp->ext.u_44.fx[0]        = (STAGE_FX *)func_80036294(wp->ext.obj_40->u_C.b.byte_D);
    wp->ext.u_44.fx[1]        = (STAGE_FX *)func_80036294(wp->ext.obj_40->u_E.b.byte_E);
    life                      = D_80098844[wp->id]->life_8 << 4;
    wp->data_78               = D_8011DE20;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->value_6E              = life;
    wp->value_B0              = life;
    wp->value_B2              = life;
    func_800322A8(wp, 0, 0);
    wp->u_15C.h[1] = 0x4210;
}

void func_801012B4(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if (func_800364B0(wp->ext.u_24.track, wp, (wp->rotation.y + wp->ext.u_3C.h[0]) & 0xFFF))
    {
        wp->ext.flags_0 |= 0x100;
    }
    else
    {
        wp->ext.flags_0 &= ~0x100;
    }
    if (ext->flags_0 & 2)
    {
        func_801031E8(wp);
    }
    wp->u_64.h[0] = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x40);
    if (((ext->u_3C.h[0] + wp->u_64.h[0] + 0x500) & 0xFFF) < 0xA00)
    {
        ext->u_3C.h[0] += wp->u_64.h[0];
    }
    D_8011DDE8[wp->routine_1](wp);
    if (ext->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 6:
                wp->routine_1 = 8;
                break;
            case 7:
                wp->routine_1 = 9;
                break;
            case 4:
                wp->routine_1 = 1;
                break;
            case 12:
                wp->routine_1 = 3;
                break;
            case 0:
            case 3:
            case 11:
            case 13:
                if (!(ext->flags_0 & 0x100))
                {
                    wp->routine_1 = 0;
                    break;
                }
                // fall through
            case 8:
            case 9:
                wp->routine_1 = 4;
                break;
            default:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ext->flags_0 &= ~1;
    }
    if (ext->u_34.h[0] != 0)
    {
        ext->u_34.h[0]--;
    }
    if (ext->value_A != 0)
    {
        ext->value_A--;
    }
    if (ext->u_34.h[1] != 0)
    {
        ext->u_34.h[1]--;
    }
    if (ext->flags_0 & 0x800)
    {
        if (--ext->u_38.h[0] < 0)
        {
            ext->effect_50 = func_80031618();
            if (ext->effect_50 != NULL)
            {
                ext->effect_50->be_flag         = 5;
                ext->effect_50->id              = 0x80;
                ext->effect_50->type            = 0x41;
                ext->effect_50->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80031988(ext->u_44.fx[0]);
            func_80031988(ext->u_44.fx[1]);
            ext->obj_40->u_E.b.byte_F |= 2;
            func_80047228(wp, &wp->vec_180, 0);
            Sound_call2(0xA1, &wp->vec_180);
        }
    }
}

void func_80101580(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if (wp->ext.flags_0 & 2)
    {
        func_801031E8(wp);
    }
    wp->ext.u_3C.h[0] = (wp->ext.u_3C.h[0] - 0x80 - wp->ext.u_2.b[0]) & 0xFFF;
    D_8011DDE8[wp->routine_1](wp);
    if (wp->ext.flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 6:
                wp->routine_1 = 8;
                break;
            case 7:
                wp->routine_1 = 9;
                break;
            default:
                wp->routine_1 = 2;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ext->flags_0 &= ~1;
    }
    if (ext->value_A != 0)
    {
        ext->value_A--;
    }
    if (ext->flags_0 & 0x800)
    {
        if (--ext->u_34.h[1] < 0)
        {
            ext->effect_50 = func_80031618();
            if (ext->effect_50 != NULL)
            {
                ext->effect_50->be_flag         = 5;
                ext->effect_50->id              = 0x80;
                ext->effect_50->type            = 0x41;
                ext->effect_50->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80031988(ext->u_44.fx[0]);
            func_80031988(ext->u_44.fx[1]);
            ext->obj_40->u_E.b.byte_F |= 2;
            func_80047228(wp, &wp->vec_180, 1);
            Sound_call2(0xA1, &wp->vec_180);
        }
    }
}

void func_80101740(ST09_VIEW *wp)
{
    func_80031824(wp);
    func_80031988(wp->ext.u_44.fx[0]);
    func_80031988(wp->ext.u_44.fx[1]);
}

void func_80101780(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 0;
            wp->ext.u_4.h[0] = 30;
            wp->ext.value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_801017F0(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext              = &wp->ext;
    wp->ext.u_58.obj = STAGE_PL_OBJ;
    if (wp->ext.value_14 & 0x2000000)
    {
        wp->ext.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2     = 1;
            wp->value_AC      = 1;
            wp->ext.value_8   = 0;
            wp->ext.u_34.h[1] = (wp->ext.u_2.h & 0x1F) + 0x10;
            if (wp->type == 0)
            {
                wp->ext.u_34.h[0] = 300;
            }
            // fall through
        case 1:
            if (wp->u_A4.b[2] == 2)
            {
                Sound_call2(0xB6, &wp->position);
            }
            wp->u_64.h[0]  = Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, 0x10);
            wp->rotation.y = (wp->rotation.y + wp->u_64.h[0]) & 0xFFF;
            Obj_pos_set(wp, 0x100, 0, 0);
            ext->u_5C.w          = Obj_map_push_out(wp);
            y                    = Obj_ceiling_height_get(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position.y            = wp->position_prev.y;
                wp->position_fixed.y      = wp->position_fixed_prev.y;
                break;
            }
            if (ext->u_5C.w & 0xF00)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 11;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (wp->type == 0 && ext->u_34.h[0] == 0)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if ((uint32)wp->value_80 <= 0x1FFFF)
            {
                wp->routine_1             = 12;
                *(uint16 *)&wp->routine_2 = 0;
                if ((uint8)wp->u_A4.b[0] < 15)
                {
                    ext->flags_0 |= 8;
                }
                else
                {
                    ext->flags_0 &= ~8;
                }
                break;
            }
            if (wp->type == 0 && ext->u_34.h[1] == 0 &&
                func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x100, &ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y,
                              0x100))
            {
                switch (func_80103170(wp))
                {
                    case 0:
                        ext->flags_0 |= 0x40;
                        // fall through
                    case 1:
                        wp->routine_1             = 12;
                        *(uint16 *)&wp->routine_2 = 0;
                        ext->flags_0 |= 0x200;
                        if ((uint8)wp->u_A4.b[0] < 15)
                        {
                            ext->flags_0 |= 8;
                        }
                        else
                        {
                            ext->flags_0 &= ~8;
                        }
                        break;
                }
            }
            if (wp->type == 1 && ext->u_34.h[0] == 0 &&
                func_80031DCC(&wp->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x18, &ext->u_58.obj->position_fixed.v,
                              ext->u_58.obj->rotation.y, 0x300))
            {
                ext->piece_54 = (STAGE_PIECE *)Open_SHL_WORK();
                if (ext->piece_54 != NULL)
                {
                    ext->piece_54->be_flag        = 1;
                    ext->piece_54->id             = 9;
                    ext->piece_54->type           = 0;
                    ext->piece_54->position       = wp->position;
                    ext->piece_54->position_fixed = wp->position_fixed;
                    func_8002FFC4(&ext->piece_54->position, &ext->piece_54->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF,
                                  0x6E0, -0xD00, 0);
                    ext->piece_54->angle_64 = wp->rotation.y;
                    ext->u_34.h[0]          = 60;
                    ext->obj_40->u_E.b.byte_F |= 1;
                    ext->u_44.fx[0]->routine_1 = 0;
                    ext->u_44.fx[1]->routine_1 = 0;
                }
            }
            break;
    }
}

void func_80101C3C(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext              = &wp->ext;
    wp->ext.u_58.obj = STAGE_PL_OBJ;
    if (wp->ext.value_14 & 0x2000000)
    {
        wp->ext.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->value_AC    = 2;
            wp->ext.value_8 = D_80098844[wp->id]->value_A;
            // fall through
        case 1:
            if (wp->u_A4.b[2] == 2)
            {
                Sound_call2(0xB6, &wp->position);
            }
            if (!(ext->flags_0 & 0x100))
            {
                ext->flags_0 |= 1;
                break;
            }
            Obj_pos_set(wp, 0x200, 0, 0);
            ext->u_5C.w          = Obj_map_push_out(wp);
            y                    = Obj_ceiling_height_get(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position.y            = wp->position_prev.y;
                wp->position_fixed.y      = wp->position_fixed_prev.y;
                break;
            }
            if ((ext->u_5C.w & 0xF00) || (ext->value_14 & 0x2000000))
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 11;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if ((uint32)wp->value_80 > 0x480000 && func_80031E60(&ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y, 0x800,
                                                                 &wp->position_fixed, wp->rotation.y, 0x400))
            {
                wp->routine_1             = 13;
                *(uint16 *)&wp->routine_2 = 0;
                if (wp->u_A4.b[2] == 1)
                {
                    ext->flags_0 |= 8;
                }
                else
                {
                    ext->flags_0 &= ~8;
                }
            }
            break;
    }
}

void func_80101E84(ST09_VIEW *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->routine_2   = 1;
        wp->value_AC    = 0;
        wp->ext.value_8 = 0;
    }
}

void func_80101EA8(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext              = &wp->ext;
    wp->ext.u_58.obj = STAGE_PL_OBJ;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 5;
            wp->u_64.h[1]    = Muku(&wp->position, &wp->ext.u_58.obj->position, wp->rotation.y, 0x800) >> 2;
            wp->ext.u_4.h[0] = 4;
            wp->ext.value_8  = 0;
            wp->ext.obj_40->u_E.b.byte_F |= 1;
            wp->ext.u_44.fx[0]->routine_1 = 0;
            wp->ext.u_44.fx[1]->routine_1 = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y,
                                                    wp->u_64.h[1] < 0 ? -wp->u_64.h[1] : wp->u_64.h[1])) &
                             0xFFF;
            break;
    }
}

void func_80101FC8(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 5;
            wp->ext.u_4.h[0] = 16;
            wp->ext.value_8  = 0;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + 0x80) & 0xFFF;
            if (--ext->u_4.h[0] <= 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_80102050(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x20;
            ext->value_8  = 0;
            ext->flags_0 &= ~0x20;
            wp->rotation.y &= 0xFFF;
            if (wp->value_6E <= 0)
            {
                ext->flags_0 &= ~4;
            }
            Obj_pos_set(wp, -0x460, 0, 0);
            Obj_map_push_out(wp);
            break;
        case 1:
            wp->routine_2 = 2;
            wp->u_44.h[0] = -0x190;
            wp->u_44.h[1] = 0;
            ext->u_4.h[0] = 3;
            Obj_pos_set(wp, wp->u_44.h[0], -0x960, 0);
            Obj_map_push_out(wp);
            break;
        case 2:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 3;
                wp->u_44.h[1] = 0x158;
            }
            // fall through
        case 3:
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1], 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->value_AC  = 0x21;
                    wp->routine_2 = 4;
                    wp->u_44.h[0] = -0xA0;
                    wp->u_44.h[1] = 0;
                    ext->u_4.h[0] = 6;
                }
            }
            break;
        case 4:
            if (ext->u_4.h[0] != 0)
            {
                ext->u_4.h[0]--;
            }
            wp->u_44.h[1] = (3 - ext->u_4.h[0]) << 4;
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1] << 4, 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->routine_2 = 5;
                    ext->u_4.h[0] = 10;
                }
            }
            break;
        case 5:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_80102288(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x1E;
            ext->value_8  = 0;
            ext->flags_0 &= ~0x20;
            wp->rotation.y &= 0xFFF;
            if (wp->value_6E <= 0)
            {
                ext->flags_0 &= ~4;
            }
            Obj_pos_set(wp, 0x460, 0, 0);
            Obj_map_push_out(wp);
            break;
        case 1:
            wp->routine_2 = 2;
            wp->u_44.h[0] = 0x190;
            wp->u_44.h[1] = 0;
            ext->u_4.h[0] = 3;
            Obj_pos_set(wp, wp->u_44.h[0], -0x960, 0);
            Obj_map_push_out(wp);
            break;
        case 2:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 3;
                wp->u_44.h[1] = 0x158;
            }
            // fall through
        case 3:
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1], 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->value_AC  = 0x1F;
                    wp->routine_2 = 4;
                    wp->u_44.h[0] = 0xA0;
                    wp->u_44.h[1] = 0;
                    ext->u_4.h[0] = 6;
                }
            }
            break;
        case 4:
            if (ext->u_4.h[0] != 0)
            {
                ext->u_4.h[0]--;
            }
            wp->u_44.h[1] = (3 - ext->u_4.h[0]) << 4;
            Obj_pos_set(wp, wp->u_44.h[0], wp->u_44.h[1] << 4, 0);
            if ((ext->u_5C.w = Obj_map_push_out(wp)) != 0)
            {
                if (ext->u_5C.w & 0xF00)
                {
                    wp->u_44.h[0] = 0;
                }
                if (ext->u_5C.w & 0x1000)
                {
                    wp->routine_2 = 5;
                    ext->u_4.h[0] = 10;
                }
            }
            break;
        case 5:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_801024C0(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x1C;
            ext->u_4.h[0] = 7;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            ext->u_4.h[0] = 6;
            // fall through
        case 2:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            ext->u_4.h[0] = 10;
            // fall through
        case 3:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 4;
                ext->u_4.h[0] = 7;
            }
            else
            {
                Obj_pos_set(wp, 0xF0, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                break;
            }
            // fall through
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 0x21;
            }
            break;
    }
}

void func_8010265C(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x1D;
            ext->u_4.h[0] = 13;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                ext->u_4.h[0] = 3;
            }
            else
            {
                Obj_pos_set(wp, -0x50, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                break;
            }
            // fall through
        case 2:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            ext->u_4.h[0] = 8;
            // fall through
        case 3:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 4;
                ext->u_4.h[0] = 4;
            }
            break;
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 0x21;
            }
            Obj_pos_set(wp, -0x80, 0, 0);
            Obj_map_push_out(wp);
            y                    = Obj_ceiling_height_get(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position.y            = wp->position_prev.y;
                wp->position_fixed.y      = wp->position_fixed_prev.y;
            }
            break;
    }
}

void func_80102844(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    wp->ext.u_58.obj = STAGE_PL_OBJ;
    ext              = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->value_AC  = 0x11;
            ext->u_4.h[0] = 10;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
            }
            else
            {
                wp->u_44.h[1] = 10 - ext->u_4.h[0];
            }
            // fall through
        case 2:
            Obj_pos_set(wp, 0, wp->u_44.h[1] << 7, 0);
            if (!(Obj_map_push_out(wp) & 0x1000))
            {
                break;
            }
            wp->routine_2 = 3;
            wp->value_AC  = 0x12;
            ext->u_4.h[0] = 3;
            // fall through
        case 3:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 4;
            wp->u_64.h[1] = Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, 0x800) / 3;
            ext->u_4.h[0] = 3;
            // fall through
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, STCOM_ABS(wp->u_64.h[1]))) & 0xFFF;
            break;
    }
}

#define STAGE_ABS(x) ((x) < 0 ? -(x) : (x))
void func_801029F0(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->value_AC     = 0x13;
            wp->ext.u_4.h[0] = 13;
            wp->ext.value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                wp->value_AC  = 0;
                ext->u_4.h[0] = 6;
            }
            else
            {
                Obj_pos_set(wp, -0xF0, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                break;
            }
            // fall through
        case 2:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            break;
    }
}

void func_80102B4C(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    wp->ext.u_58.obj = STAGE_PL_OBJ;
    ext              = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            if (ext->flags_0 & 8)
            {
                wp->value_AC  = 0x18;
                wp->u_48.h[0] = -0x1C;
            }
            else
            {
                wp->value_AC  = 0x14;
                wp->u_48.h[0] = 0x1C;
            }
            ext->u_4.h[0] = 5;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                wp->value_AC++;
                ext->u_4.h[0] = 10;
                Sound_call2(0xB7, &wp->position);
            }
            else
            {
                Obj_pos_set(wp, 0x200, 0, 0);
                Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
            }
            break;
        case 2:
            ext->u_4.h[0]--;
            wp->u_44.h[1] = (5 - ext->u_4.h[0]) << 2;
            Obj_pos_set(wp, 0, wp->u_44.h[1] << 4, wp->u_48.h[0] << 4);
            if (Obj_map_push_out(wp) & 0x1000)
            {
                Sound_call2(0xB8, &wp->position);
                if ((ext->flags_0 & 0x200) && func_80031DCC(&wp->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x18,
                                                            &ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y, 0x300))
                {
                    ext->flags_0 &= ~0x200;
                    ext->piece_54 = (STAGE_PIECE *)Open_SHL_WORK();
                    if (ext->piece_54 != NULL)
                    {
                        ext->piece_54->be_flag        = 1;
                        ext->piece_54->id             = 9;
                        ext->piece_54->type           = 0;
                        ext->piece_54->position       = wp->position;
                        ext->piece_54->position_fixed = wp->position_fixed;
                        func_8002FFC4(&ext->piece_54->position, &ext->piece_54->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF,
                                      0x6E0, -0xD00, 0);
                        ext->piece_54->angle_64 = wp->rotation.y;
                        ext->obj_40->u_E.b.byte_F |= 1;
                        ext->u_44.fx[0]->routine_1 = 0;
                        ext->u_44.fx[1]->routine_1 = 0;
                    }
                }
                wp->routine_2 = 3;
                wp->value_AC++;
                ext->u_4.h[0] = 4;
            }
            break;
        case 3:
            if (--ext->u_4.h[0] < 0 && (ext->flags_0 & 0x40))
            {
                wp->routine_2 = 4;
                ext->u_4.h[0] = 15;
            }
            // fall through
        case 4:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
                if (ext->flags_0 & 0x40)
                {
                    if (ext->flags_0 & 8)
                    {
                        wp->rotation.y += 0x400;
                    }
                    else
                    {
                        wp->rotation.y -= 0x400;
                    }
                    wp->rotation.y &= 0xFFF;
                }
                ext->flags_0 &= ~0x40;
            }
            break;
    }
}

void func_80102F30(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    sint16 y;

    wp->ext.u_58.obj = STAGE_PL_OBJ;
    ext              = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            if (wp->ext.flags_0 & 8)
            {
                wp->value_AC = 0x1B;
            }
            else
            {
                wp->value_AC = 0x17;
            }
            ext->u_4.h[0] = 6;
            ext->value_8  = 0;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                ext->u_4.h[0] = 4;
            }
            else
            {
                Obj_pos_set(wp, 0x180, 0, 0);
                ext->u_5C.w          = Obj_map_push_out(wp);
                y                    = Obj_ceiling_height_get(wp);
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
                {
                    wp->routine_1             = 10;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->position.y            = wp->position_prev.y;
                    wp->position_fixed.y      = wp->position_fixed_prev.y;
                }
                else if (ext->u_5C.w & 0xF00)
                {
                    wp->routine_1             = 11;
                    *(uint16 *)&wp->routine_2 = 0;
                }
                break;
            }
            // fall through
        case 2:
            if (--ext->u_4.h[0] >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->u_64.h[1] = Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, 0x800) / 3;
            ext->u_4.h[0] = 3;
            // fall through
        case 3:
            if (--ext->u_4.h[0] < 0)
            {
                ext->flags_0 |= 1;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &ext->u_58.obj->position, wp->rotation.y, STCOM_ABS(wp->u_64.h[1]))) & 0xFFF;
            break;
    }
}

sint32 func_80103170(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext            = &wp->ext;
    wp->u_64.h[0]  = 0;
    wp->ext.u_4C.i = 0;
    while (1)
    {
        wp->u_64.h[0] += D_8011DE30[ext->u_4C.i];
        if ((ext->u_2.h & 0xF) < wp->u_64.h[0])
        {
            break;
        }
        if (++ext->u_4C.i >= 2)
        {
            break;
        }
    }
    return ext->u_4C.i;
}

sint32 func_801031E8(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if ((wp->ext.u_4C.i = wp->ext.value_14 & 0xFFFFFF) != 0)
    {
        if (wp->ext.value_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= wp->ext.u_4C.i;
            if (wp->value_6E <= 0)
            {
                wp->ext.flags_0 = (wp->ext.flags_0 & ~2) | 0x820;
                wp->ext.u_4C.i  = D_80098844[wp->id]->limit_9;
            }
            if (wp->ext.flags_0 & 0x20)
            {
                wp->ext.value_A += wp->ext.u_4C.i;
                if ((wp->ext.value_14 & 0x20000000) || wp->ext.value_A >= D_80098844[wp->id]->limit_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    if (wp->ext.from_1C.pad & 1)
                    {
                        wp->u_64.h[0] = Angle_xz_svector(&wp->position, &wp->ext.from_1C);
                        if (((wp->rotation.y - wp->u_64.h[0] + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->routine_1  = 6;
                            wp->rotation.y = wp->u_64.h[0];
                        }
                        else
                        {
                            wp->routine_1  = 7;
                            wp->rotation.y = (wp->u_64.h[0] + 0x800) & 0xFFF;
                        }
                    }
                    else
                    {
                        wp->u_64.h[0] = Angle_xz_svector(&D_8011DE34, &wp->ext.from_1C);
                        if (((wp->u_64.h[0] - wp->rotation.y + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->routine_1  = 7;
                            wp->rotation.y = wp->u_64.h[0];
                        }
                        else
                        {
                            wp->routine_1  = 6;
                            wp->rotation.y = (wp->u_64.h[0] + 0x800) & 0xFFF;
                        }
                    }
                    *(uint16 *)&wp->routine_2 = 0;
                    ext->value_A              = 0;
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
            else if ((wp->ext.value_14 & 0x20000000) || wp->ext.value_A >= D_80098844[wp->id]->limit_9)
            {
                Sound_call2(0xA2, &wp->position);
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->u_15C.h[1] = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
