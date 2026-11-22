#include "common.h"
#include "st0c.h"

void func_8010012C(STAGE_ROOM *wp)
{
    D_8010BE80[wp->routine_4](wp);
}

void func_80100168(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    ST0C_VIEW *owner;
    ST0C_VIEW *obj;
    ST0C_VIEW **child;
    sint8 i;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0  = D_8010BF2C;
            wp->tbl_A4  = (STAGE_ROOM2_FUNC *)D_8010C078;
            wp->timer_C = 0;
            if (func_80042238(pl) != 0)
            {
                owner                   = (ST0C_VIEW *)Open_SHL_WORK();
                D_801129A0              = owner;
                owner->kind_2           = 0x11;
                owner->position.x       = -0x1AFF;
                i                       = 3;
                owner->flags_0          = 1;
                owner->position.y       = -1;
                owner->variant_3        = 0;
                owner->position_fixed.x = owner->position.x << 16;
                owner->value_4          = 0;
                owner->position.z       = 0x21DF;
                owner->value_5          = 0;
                owner->u_C.b[0]         = 1;
                owner->u_C.b[1]         = 0;
                owner->u_C.b[2]         = 0;
                owner->position_fixed.y = owner->position.y << 16;
                owner->u_C.b[3]         = 0;
                owner->position_fixed.z = owner->position.z << 16;
                child                   = owner->child_CC;
                for (; i >= 0; i--)
                {
                    obj = (ST0C_VIEW *)func_80031418();
                    if (obj != NULL)
                    {
                        obj->flags_0          = D_8010BEDC[i].flags_0;
                        obj->kind_2           = D_8010BEDC[i].kind_2;
                        obj->variant_3        = D_8010BEDC[i].variant_3;
                        obj->value_4          = D_8010BEDC[i].value_4;
                        obj->value_5          = D_8010BEDC[i].value_5;
                        obj->rotation.y       = D_8010BEDC[i].dir_7 * 16;
                        obj->u_C.b[0]         = D_8010BEDC[i].value_8[0];
                        obj->u_C.b[1]         = D_8010BEDC[i].value_8[1];
                        obj->u_C.b[2]         = D_8010BEDC[i].value_8[2];
                        obj->u_C.b[3]         = D_8010BEDC[i].value_8[3];
                        obj->position.x       = D_8010BEDC[i].x_C;
                        obj->position.y       = D_8010BEDC[i].y_E;
                        obj->position.z       = D_8010BEDC[i].z_10;
                        obj->position_fixed.x = obj->position.x << 16;
                        obj->position_fixed.y = obj->position.y << 16;
                        obj->position_fixed.z = obj->position.z << 16;
                        *child                = obj;
                    }
                    child++;
                }
                i = 3;
                do
                {
                    obj = (ST0C_VIEW *)func_80031418();
                    if (obj != NULL)
                    {
                        obj->flags_0          = D_8010BE8C[i].flags_0;
                        obj->kind_2           = D_8010BE8C[i].kind_2;
                        obj->variant_3        = D_8010BE8C[i].variant_3;
                        obj->value_4          = D_8010BE8C[i].value_4;
                        obj->value_5          = D_8010BE8C[i].value_5;
                        obj->rotation.y       = D_8010BE8C[i].dir_7 * 16;
                        obj->u_C.b[0]         = D_8010BE8C[i].value_8[0];
                        obj->u_C.b[1]         = D_8010BE8C[i].value_8[1];
                        obj->u_C.b[2]         = D_8010BE8C[i].value_8[2];
                        obj->u_C.b[3]         = D_8010BE8C[i].value_8[3];
                        obj->position.x       = D_8010BE8C[i].x_C;
                        obj->position.y       = D_8010BE8C[i].y_E;
                        obj->position.z       = D_8010BE8C[i].z_10;
                        obj->position_fixed.x = obj->position.x << 16;
                        obj->position_fixed.y = obj->position.y << 16;
                        obj->position_fixed.z = obj->position.z << 16;
                    }
                } while (--i >= 0);
                wp->routine_5++;
            }
            break;
        case 1:
            Obj_work_flag_change(8, 1);
            wp->routine_5++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 6);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                D_800A395C = 1;
                func_80039820();
                MojiTaskExec2(0, 9);
                wp->routine_5++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x8000000))
            {
                if (!(Moji_flag & 0xFF))
                {
                    wp->routine_5++;
                    pl->routine_0 = 3;
                    pl->routine_1 = 1;
                    pl->pos_438.x = pl->position.x;
                    pl->flags_bd |= 0x10;
                    pl->pos_438.y   = pl->position.y;
                    pl->value_440   = 0;
                    pl->value_442   = 0;
                    pl->value_444   = 0;
                    pl->value_448   = 0;
                    pl->pos_438.z   = pl->position.z;
                    pl->fixed_428.x = pl->pos_438.x << 16;
                    pl->fixed_428.y = pl->pos_438.y << 16;
                    pl->fixed_428.z = pl->pos_438.z << 16;
                }
                else
                {
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            break;
        case 5:
            wp->routine_5++;
            pl->routine_1++;
            break;
        case 6:
            pl->flags_bd |= 0x20;
            D_800C0F96 = pl->value_124;
            wp->routine_5++;
            break;
        case 7:
            if (pl->position.z < 0x1C20)
            {
                D_800C0F96 = 0;
                D_801129A0->flags_0 |= 6;
                func_8001E6C0(0, 0, 0);
                D_800BC7F0    = D_8010BF78;
                wp->tbl_A4    = (STAGE_ROOM2_FUNC *)D_8010C088;
                wp->timer_C   = 0;
                wp->routine_6 = 0xF0;
                wp->routine_5++;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0xA);
                wp->routine_5++;
                pl->pos_438.x   = -0x188C;
                pl->position.x  = -0x188C;
                pl->position.y  = -1;
                pl->pos_438.y   = -1;
                pl->position.z  = 0x18C0;
                pl->pos_438.z   = 0x18C0;
                pl->value_440   = 0x400;
                pl->value_442   = 0;
                pl->value_444   = 0;
                pl->fixed_428.x = pl->position_fixed.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->position_fixed.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->position_fixed.z = pl->pos_438.z << 16;
            }
            break;
        case 9:
            if (!(Moji_flag & 0x8000000))
            {
                D_801129A0->u_C.b[0] = 0;
                Sound_call2(0x17B, &D_801129A0->position);
                wp->routine_5++;
                Sce_event_next();
            }
            break;
        case 10:
            if (wp->routine_6 == 0)
            {
                wp->routine_5++;
            }
            else
            {
                wp->routine_6--;
            }
            break;
        case 11:
            Sound_call2(0x17D, &D_801129A0->position);
            func_80042314(&Player_work);
            Obj_work_flag_change(8, 2);
            D_800A395C = 1;
            func_8003A264();
            wp->flags_0 = 0;
            break;
    }
    func_8001EC0C();
    Sce_event_update();
    if (func_8001DE84() != 0 && wp->routine_5 >= 2)
    {
        Sound_call2(0x188, &D_801129A0->position);
        func_80053AA4(0);
        D_800A395C = 1;
        func_80039820();
        wp->routine_4 = 2;
        wp->routine_5 = 0;
    }
}

void func_801008FC(STAGE_ROOM *wp)
{
    if (!(Moji_flag & 0x8000000))
    {
        if (wp->routine_5 == 0)
        {
            func_80017C30(10);
            wp->routine_5++;
        }
        else if (wp->routine_5 == 1)
        {
            D_800C356C         = 1;
            D_800C356E         = 3;
            D_800C3560         = -0xCA0;
            D_800C3562         = -1;
            D_800C3564         = 0x600;
            D_800C356A         = 0xC00;
            D_800C3571         = 0xFF;
            D_800C356F         = 1;
            D_800C356D         = 0;
            D_800C3570         = 2;
            Game_work.value_79 = 3;
            Game_work.value_7A = 1;
            wp->routine_5++;
        }
        else if (D_800C356C == 2 && D_80098A72 == 0)
        {
            D_800C356C++;
            wp->flags_0 = 0;
            func_80042314(&Player_work);
        }
    }
    func_8001EC0C();
    Sce_event_update();
}

void func_80100A40(STAGE_ROOM *wp)
{
    ST0C_VIEW *obj;
    obj                       = D_801129A0;
    STAGE_PL.position.x       = -0x188C;
    STAGE_PL.position.y       = -1;
    STAGE_PL.pos_438.y        = -1;
    STAGE_PL.pos_438.x        = -0x188C;
    STAGE_PL.position.z       = 0x18C0;
    STAGE_PL.pos_438.z        = 0x18C0;
    STAGE_PL.position_fixed.x = -0x188C0000;
    STAGE_PL.fixed_428.x      = -0x188C0000;
    STAGE_PL.position_fixed.y = -0x10000;
    STAGE_PL.fixed_428.y      = -0x10000;
    STAGE_PL.position_fixed.z = 0x18C00000;
    STAGE_PL.fixed_428.z      = 0x18C00000;
    STAGE_PL.value_440        = 0x400;
    STAGE_PL.value_442        = 0;
    STAGE_PL.value_444        = 0;
    obj->flags_0 |= 6;
    D_801129A0->routine_1        = 3;
    D_801129A0->u_C.b[0]         = 0;
    D_801129A0->position.x       = -0x1ADA;
    D_801129A0->position.y       = -1;
    D_801129A0->position.z       = 0x149B;
    D_801129A0->rotation.x       = 0;
    D_801129A0->position_fixed.x = D_801129A0->position.x << 16;
    D_801129A0->position_fixed.y = D_801129A0->position.y << 16;
    D_801129A0->position_fixed.z = D_801129A0->position.z << 16;
    D_801129A0->rotation.y       = 0x5B;
    D_801129A0->rotation.z       = 0;
    obj->value_EC                = 2;
    D_801129A0->value_44         = 0x140;
    func_80042314(&Player_work);
    Obj_work_flag_change(8, 2);
    wp->flags_0 = 0;
}

void func_80100BB0(void)
{
    STAGE_TABLE_3C0 = D_8010C0BC;
    STAGE_TABLE_5A4 = D_8010C1FC;
    STAGE_TABLE_10C = D_8010C200;
    STAGE_TABLE_48  = D_8010C2BC;
    STAGE_TABLE_24  = D_8010C2FC;
    STAGE_TABLE_50  = D_8010C300;
}

void func_80100C18(void)
{
    STAGE_PL_VIEW *pl;
    void *spawn;
    func_80022FD4(D_8010C3A4[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    STAGE_MAP_WORK_PTR->cells = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    pl                        = &STAGE_PL;
    if (STAGE_GAME_VALUE_52 == 0)
    {
        if (!Sce_flag_test(0x1A))
        {
            pl->value_44E = 0;
        }
        else
        {
            pl->value_44E = 1;
        }
    }
    else
    {
        if (STAGE_GAME_VALUE_52 < 7)
        {
            D_8010C47E = 3;
        }
        else
        {
            D_8010C47E = 0x1B;
        }
        pl->value_44E = 1;
    }
    spawn                     = D_8010C468[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8010C4D8[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_8010C588[D_8010C788[Game_work.value_51]], D_8010C4E8[Game_work.value_51]);
    func_8005DC10(0);
    func_80100DE8();
}

void func_80100DE8(void)
{
    func_8001DEE4();
    func_8001E4C4(D_8010CB98, D_8010CBA0[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_80100E34(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_8010C888[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_8010C848[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100ED4(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;
    STAGE_OBJ *slot;

    if (wp->routine_4 == 0)
    {
        slot = func_8001EAE8(D_8010CB70);
        slot->flags_6 &= ~0x20;
        pos.x = 0xB00;
        pos.y = 0;
        pos.z = 0x900;
        Stage_idx_model_set(Map_cell_get(&pos), 0xE0100);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F58(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010CB40);
        wp->routine_4 = 0xFF;
    }
}

void func_80100FA4(void)
{
}

void func_80100FAC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010CB40);
        wp->routine_4 = 0xFF;
    }
}

void func_80100FF8(void)
{
}

void func_80101000(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (!Sce_flag_test(0x30))
            {
                func_8001DDE4(0x1E);
                wp->routine_4++;
            }
            else
            {
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x30))
            {
                func_8003786C(0x19D);
                func_8001E4C4(D_8010CB98, D_8010CBC0);
                wp->routine_4 = 0xFF;
            }
            break;
        case 2:
            break;
    }
}

void func_801010AC(void)
{
    if (Sce_flag_test(0x28) != 0)
    {
        func_8001DDE4(0x18);
    }
}

void func_801010DC(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010CB48);
        func_8003786C(0x19D);
        wp->value_4 = 0xFF;
    }
}

void func_80101130(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010CB48);
        func_8003786C(0x19D);
        wp->value_4 = 0xFF;
    }
}

void func_80101184(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010CB50);
        func_8003786C(0x19D);
        wp->value_4 = 0xFF;
    }
}

void func_801011D8(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010CB58);
        func_8003786C(0x19D);
        wp->value_4 = 0xFF;
    }
}

void func_8010122C(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010CB60);
        func_8003786C(0x19D);
        wp->value_4 = 0xFF;
    }
}

void func_80101280(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010CB68);
        func_8003786C(0x19D);
        wp->value_4 = 0xFF;
    }
}

sint32 func_801012D4(void)
{
    if (D_800989F8.routine_4 == 0 && Sce_flag_test(0x21B) && !Sce_flag_test(0x22A))
    {
        func_8001EB98(D_8010D874);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101330(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80101350(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356F = arg0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C356E = (uint8)Game_work.value_50;
}

void func_80101398(ST0C_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        wp->value_448 = 0;
        wp->u_C.b.byte_D++;
    }
}

void func_801013C0(ST0C_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    switch (temp_v1)
    {
        case 0:
            wp->value_448    = 0xD;
            wp->u_E.b.byte_E = 0;
            wp->u_C.b.byte_D++;
            return;
        case 1:
            wp->u_E.b.byte_E++;
            wp->value_430 += 0xFFFB0000;
            if (wp->u_E.b.byte_E == 0x1E)
            {
                wp->u_C.b.byte_C = 0;
                wp->u_C.b.byte_D = 0;
            }
            return;
    }
}

void func_8010143C(ST0C_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    switch (temp_v1)
    {
        case 0:
            wp->value_448 = 0xC;
            wp->u_C.b.byte_D++;
            return;
        case 1:
            wp->value_430 += 0x50000;
            return;
    }
}

void func_8010148C(ST0C_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        wp->value_448 = 0x80;
        wp->value_168 = 0;
        wp->value_169 = 0;
        wp->u_C.b.byte_D++;
    }
}

void func_801014BC(ST0C_PL *wp)
{
    D_8010CE3C[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_8010151C(STAGE_ROOM *wp)
{
    ST0C_PL *pl;

    pl = (ST0C_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_80101350(2);
            STAGE_PL.fixed_428.x = 0xFE000000;
            STAGE_PL.fixed_428.z = 0xFE000000;
            STAGE_PL.fixed_428.y = 0xFEFF0000;
        }
        else
        {
            func_80101350(0);
            STAGE_PL.fixed_428.x = 0xC000000;
            STAGE_PL.fixed_428.z = 0x14000000;
            STAGE_PL.fixed_428.y = 0xFFFF0000;
        }
        pl->value_442 = 0x800;
    }
    if (wp->frame_10 == 0xA)
    {
        pl->routine_C = 1;
        pl->value_D   = 0;
    }
}

void func_801015E0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_FX *fx;

    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_80101350(6);
        }
        else
        {
            func_80101350(1);
        }
        child          = wp->child_24;
        child->flags_0 = (uint8)child->flags_0 | 2;
    }
    if (wp->frame_10 == 5)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->x_1C    = 0x85;
            fx->y_1E    = -0x16E;
            fx->timer_D = 0;
            fx->z_20    = -0xC8;
        }
    }
    if (wp->frame_10 == 0x72)
    {
        child            = wp->child_24;
        child->routine_1 = 1;
    }
    if (wp->frame_10 == 0xAC)
    {
        child            = wp->child_24;
        child->routine_1 = 0;
    }
}

void func_801016DC(STAGE_ROOM *wp)
{
    ST0C_PL *pl;

    pl = (ST0C_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_80101350(2);
        }
        else
        {
            func_80101350(0);
        }
        wp->child_24->flags_0 &= ~2;
        pl->routine_C = 3;
        pl->value_D   = 0;
    }
    if (wp->frame_10 == 1)
    {
        pl->flags_0 &= ~1;
    }
    if (wp->frame_10 == 0x14)
    {
        pl->flags_0 |= 1;
    }
}

void func_801017A0(STAGE_ROOM *wp)
{
    ST0C_PL *pl;

    pl = (ST0C_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        wp->child_28->flags_0 = (uint8)wp->child_28->flags_0 | 2;
        wp->child_2C->flags_0 = (uint8)wp->child_2C->flags_0 | 2;
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_80101350(7);
        }
        else
        {
            func_80101350(2);
        }
        pl->fixed_428.x = 0;
        pl->fixed_428.z = 0;
        pl->fixed_428.y = 0;
        pl->value_D     = 0;
        pl->routine_C   = 0;
    }
    if (wp->frame_10 == 0xF)
    {
        wp->child_28->routine_1++;
        wp->child_2C->routine_1++;
    }
    if (wp->frame_10 == 0x46)
    {
        pl->routine_C = 2;
        pl->value_D   = 0;
    }
}

void func_8010189C(STAGE_ROOM *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    Obj_work_flag_change(0x56, 0x80);
    if (STAGE_GAME.value_50 == 0xB)
    {
        D_800BC7F0 = D_8010CD3C;
    }
    else
    {
        D_800BC7F0 = D_8010CC3C;
    }
    wp->tbl_A4 = D_8010CE4C;
    for (i = 0; i < 10; i++)
    {
        func_8001EAE8(&D_8010CC00[i]);
    }
    STAGE_PL.routine_0 = 3;
    STAGE_PL.routine_1 = 1;
    STAGE_PL.value_C   = 0;
}

void func_80101968(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801019A8(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                Sound_fade_start(0x10);
                func_8001B314();
                if (Game_work.value_50 == 0xB)
                {
                    Cd_xa_play_id(0x20010013);
                }
                else
                {
                    Cd_xa_play_id(0x2000000E);
                }
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x17;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            func_8010189C(wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(0xA);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80101968(wp);
            func_801014BC(&Player_work);
            if (D_800C356C_A[0] == -1)
            {
                D_800C3560 = STAGE_PL.fixed_428.x >> 16;
                D_800C3562 = STAGE_PL.fixed_428.y >> 16;
                D_800C3564 = STAGE_PL.fixed_428.z >> 16;
                D_800C356A = STAGE_PL.value_442;
            }
            func_8001EC0C();
            Sce_event_update();
            if (wp->routine_4 == 5 && D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                if (Game_work.value_50 == 0xB)
                {
                    D_800C356C_A[0] = 2;
                    D_800C356E      = 0x14;
                    D_800C3560      = 0x100;
                    D_800C3562      = -1;
                    D_800C3564      = -0x7300;
                    D_800C356F      = 0;
                    D_800C356A      = 0;
                    D_800C356D      = 0;
                    D_800C3571      = 0xFF;
                    D_800C3570      = 2;
                }
                else
                {
                    D_800C356C_A[0] = 2;
                    D_800C356E      = 0xE;
                    D_800C3560      = -0xC6B;
                    D_800C3562      = -0x181;
                    D_800C3564      = 0xB00;
                    D_800C356A      = 0x400;
                    D_800C356F      = 0;
                    D_800C356D      = 0;
                    D_800C3571      = 0xFF;
                    D_800C3570      = 2;
                }
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                STAGE_PL.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}
