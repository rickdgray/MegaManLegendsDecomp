#include "common.h"
#include "st1d.h"

void func_80100288(void)
{
    STAGE_TABLE_3C0      = D_801140A4;
    STAGE_TABLE_5A4      = D_80114244;
    STAGE_TABLE_10C      = D_801142A4;
    STAGE_TABLE_48       = D_801142CC;
    STAGE_TABLE_24       = D_8011430C;
    STAGE_TABLE_50       = D_80114394;
    STAGE_PL_BYTE(0x170) = 0;
}

void func_801002F8(void)
{
    void *spawn;
    sint16 *cells;
    Room_model_init(D_80114474[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 1;
    spawn                     = D_80114798[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_80114858[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_80114960[D_801149E0[Game_work.value_51]], D_80114870[Game_work.value_51]);
    func_8005DC10(0);
    func_80100460();
}

void func_80100460(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_80100470(void)
{
    D_80114A28[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_801004C4(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x66))
            {
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_8001E460(0, 1, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x616))
            {
                func_8001E460(0, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100554(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x67))
            {
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_8001E460(0, 1, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x617))
            {
                func_8001E460(0, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_801005E4(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x68))
            {
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_8001E460(0, 1, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x618))
            {
                func_8001E460(0, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100674(void)
{
}

void func_8010067C(void)
{
}

void func_80100684(void)
{
}

void func_8010068C(ST1D_VIEW *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->u_15C.h[1]          = 0x4210;
    wp->value_432           = rand();
    D_80114A68[wp->routine_0](wp);
}

void func_80100720(ST1D_VIEW *wp)
{
    STAGE_OBJ *obj;
    sint16 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158  = 0x02000200;
    wp->u_15C.w[0] = 0x200;
    wp->routine_0  = 1;
    wp->value_AC   = 0;
    func_800322A8(wp, 0, 0);
    wp->u_15C.h[1] = 0x4210;
    wp->data_78    = NULL;
    life           = (D_8009884C[wp->kind_2]->life_8 << 6) + (D_80098844[0x48]->life_8 << 7);
    wp->value_6E   = life;
    wp->value_B0   = life;
    wp->value_B2   = life;
    wp->u_70.b[3]  = D_8009884C[wp->kind_2]->value_A;
    wp->value_C |= 2;
    wp->value_D   = -1;
    wp->value_E   = -1;
    wp->value_42E = 0x3C;
    wp->value_43A = 0xFF;
    wp->value_43C = 7;
    wp->u_44.h[0] = 0xC;
    wp->value_42C = 0;
    wp->value_43B = 0;
    wp->value_422 = 0;
    wp->value_438 = 0;
    wp->value_42A = 0xA00;
    wp->value_438 = 0; // stored twice
    wp->u_64.h[0] = 0;
    obj           = func_80031418();
    if (obj != NULL)
    {
        wp->value_439           = obj->value_1;
        obj->flags_0            = 1;
        obj->kind_2             = 0x59;
        obj->variant_3          = 0;
        obj->value_4            = 0;
        obj->reserved05         = 0;
        obj->rotation.y         = wp->rotation.y;
        obj->u_C.b.byte_C       = wp->value_1;
        obj->u_C.b.byte_D       = 0;
        obj->u_E.b.byte_E       = 0;
        obj->u_E.b.byte_F       = 0;
        obj->position           = wp->position;
        obj->position_fixed.v.x = obj->position.x << 16;
        obj->position_fixed.v.y = obj->position.y << 16;
        obj->position_fixed.v.z = obj->position.z << 16;
    }
    func_8005D620(wp, 0, 0, 0x51, 0x2C580048);
    wp->value_3F8  = 0;
    wp->u_400.w[0] = 0;
    wp->value_408  = 0;
    wp->value_410  = 0;
}

void func_80100920(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STAGE_OBJ *child;
    sint32 damage;
    STCOM_SVECTOR unused; // retail's frame has room for it

    spark = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    if (!(wp->value_C & 2))
    {
        damage = wp->u_400.w[0];
        if (wp->u_400.h[0] != 0)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E < 0)
            {
                wp->value_43B = 2;
                wp->routine_2 = 0;
                wp->value_42C = 0x3C;
            }
            else
            {
                wp->value_434 += damage;
                if (wp->value_434 >= D_8009884C[wp->kind_2]->limit_9)
                {
                    wp->value_434 = 0;
                    wp->value_C |= 0x40;
                    Sound_call2(0xA2, &wp->position);
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
            wp->u_15C.h[1] = 0x7FFF;
        }
        else
        {
            if (wp->value_3F8 & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
            if (wp->value_408 & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
            if (wp->value_410 & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
        }
    }
    else if (wp->value_F != 0)
    {
        wp->u_15C.h[1] = 0x7FFF;
        wp->value_F--;
    }
    else
    {
        if (wp->u_400.w[0] & 0xFFFFFF)
        {
            Sound_call2(0xA3, &wp->position);
        }
        if (wp->value_3F8 & 0xFFFFFF)
        {
            Sound_call2(0xA3, &wp->position);
        }
        if (wp->value_408 & 0xFFFFFF)
        {
            Sound_call2(0xA3, &wp->position);
        }
        if (wp->value_410 & 0xFFFFFF)
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    if (spark->routine_5B != 2 && (wp->value_C & 0x40))
    {
        spark->routine_5B = 1;
    }
    D_80114A74[spark->routine_5B](wp);
    if (spark->routine_5B != 2)
    {
        child           = func_80036294(spark->child_59);
        child->rotation = wp->rotation;
        child->position = wp->position;
        spark->pos_10.x = wp->vec_180[0].x;
        spark->pos_10.y = wp->vec_180[0].y + 0x28;
        spark->pos_10.z = wp->vec_180[0].z;
        spark->pos_0.x  = spark->pos_10.x << 16;
        spark->pos_0.y  = spark->pos_10.y << 16;
        spark->pos_0.z  = spark->pos_10.z << 16;
        func_8002FFC4(&spark->pos_10, &spark->pos_0, wp->rotation.y & 0xFFF, -0x320, 0, 0);
        func_800341BC(&spark->pos_10, 0xC8, 0, 0x8000, wp->value_1, &spark->hit_18[0], wp->u_70.b[3] | 0x04080000, 0, 0x80);
        spark->pos_10.x = wp->value_1E0;
        spark->pos_10.y = wp->value_1E2 + 0x78;
        spark->pos_10.z = wp->value_1E4;
        spark->pos_0.x  = spark->pos_10.x << 16;
        spark->pos_0.y  = spark->pos_10.y << 16;
        spark->pos_0.z  = spark->pos_10.z << 16;
        func_8002FFC4(&spark->pos_10, &spark->pos_0, wp->rotation.y & 0xFFF, -0xB40, 0, 0x820);
        func_800341BC(&spark->pos_10, 0x46, 0, 0x8000, wp->value_1, &spark->hit_18[2], wp->u_70.b[3] | 0x04080000, 0, 0x80);
        spark->pos_10.x = wp->value_1E0;
        spark->pos_10.y = wp->value_1E2 + 0x78;
        spark->pos_10.z = wp->value_1E4;
        spark->pos_0.x  = spark->pos_10.x << 16;
        spark->pos_0.y  = spark->pos_10.y << 16;
        spark->pos_0.z  = spark->pos_10.z << 16;
        func_8002FFC4(&spark->pos_10, &spark->pos_0, wp->rotation.y & 0xFFF, -0xB40, 0, -0x820);
        func_800341BC(&spark->pos_10, 0x46, 0, 0x8000, wp->value_1, &spark->hit_18[3], wp->u_70.b[3] | 0x04080000, 0, 0x80);
        spark->pos_10.x = wp->value_1E0;
        spark->pos_10.y = wp->value_1E2 + 0x78;
        spark->pos_10.z = wp->value_1E4;
        spark->pos_0.x  = spark->pos_10.x << 16;
        spark->pos_0.y  = spark->pos_10.y << 16;
        spark->pos_0.z  = spark->pos_10.z << 16;
        func_8002FFC4(&spark->pos_10, &spark->pos_0, wp->rotation.y & 0xFFF, -0xB40, 0, 0);
        func_800341BC(&spark->pos_10, 0x46, 0, 0x8000, wp->value_1, &spark->hit_18[1], wp->u_70.b[3] | 0x04080000, 0, 0);
        if (!(wp->value_C & 1) && (wp->value_A6 & 2))
        {
            Sound_call2(0x1C3, &wp->position);
        }
    }
    func_80032488(wp);
    spark->hit_18[0].hit = 0;
    spark->hit_18[1].hit = 0;
    spark->hit_18[2].hit = 0;
    spark->hit_18[3].hit = 0;
}

void func_80100E38(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80100E58(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    sint8 count37;
    sint8 count3;
    sint8 i;

    spark   = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    count37 = 0;
    count3  = 0;
    for (i = 0; i < 16; i++)
    {
        if (D_8009F108[i].flags_0 != 0)
        {
            if (D_8009F108[i].kind_2 == 0x37)
            {
                count37++;
            }
            if (D_8009F108[i].kind_2 == 3)
            {
                count3++;
            }
        }
    }
    if (spark->count_4E == 0x3C)
    {
        wp->value_C |= 1;
        D_80114A94[wp->routine_2](wp);
        return;
    }
    D_80114AA8[wp->routine_1](wp);
    if (wp->value_D < 0)
    {
        spark->limit_5C = 9;
    }
    else if (wp->value_E < 0)
    {
        spark->limit_5C = 8;
    }
    if (count37 + count3 < spark->limit_5C)
    {
        spark->count_4E++;
    }
}

void func_80100FE0(STAGE_OBJ *wp)
{
    D_80114A80[wp->routine_3](wp);
}

void func_8010101C(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STAGE_OBJ *child;

    spark = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    if (!(wp->value_C & 1))
    {
        child = func_80036294(wp->value_439);
        Obj_pos_set(wp, wp->u_44.h[0] * 16, 0, 0);
        if (wp->value_42C == 0x140)
        {
            wp->value_42C  = 0;
            child->anim_AC = 0;
            func_800322A8(child, 0, 0);
        }
        else if ((uint16)(wp->value_42C - 0x100) < 0x40)
        {
            wp->value_42C++;
        }
        if (wp->u_64.h[0] == 0)
        {
            if (D_80114AB0[spark->node_58].value_8 == 2)
            {
                if (wp->position.z >= D_80114AB0[spark->node_58].z)
                {
                    if (spark->rand_52.h & 1)
                    {
                        spark->node_58 = 8;
                        func_80102D5C(wp);
                        spark->node_58++;
                        wp->u_64.h[0] = 1;
                        wp->routine_1++;
                        spark->angle_48 = 0x400;
                        child->anim_AC  = 4;
                        func_800322A8(child, 4, 0);
                    }
                    else
                    {
                        func_80102D5C(wp);
                        spark->node_58++;
                        wp->routine_1++;
                        spark->angle_48 = 0xC00;
                        child->anim_AC  = 1;
                        func_800322A8(child, 1, 0);
                    }
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 0)
            {
                if (wp->position.x >= D_80114AB0[spark->node_58].x)
                {
                    func_80102D5C(wp);
                    spark->node_58++;
                    wp->routine_1++;
                    spark->angle_48 = 0;
                    child->anim_AC  = 1;
                    func_800322A8(child, 1, 0);
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 3)
            {
                if (wp->position.z <= D_80114AB0[spark->node_58].z)
                {
                    func_80102D5C(wp);
                    spark->node_58++;
                    wp->routine_1++;
                    spark->angle_48 = 0x400;
                    child->anim_AC  = 1;
                    func_800322A8(child, 1, 0);
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 1 && wp->position.x <= D_80114AB0[spark->node_58].x)
            {
                if (spark->rand_52.h & 1)
                {
                    spark->node_58 = 0xD;
                    return;
                }
                func_80102D5C(wp);
                spark->node_58++;
                wp->routine_1++;
                spark->angle_48 = 0x800;
                child->anim_AC  = 1;
                func_800322A8(child, 1, 0);
            }
            else
            {
                if (D_80114AB0[spark->node_58].value_8 == 7)
                {
                    if (wp->position.x <= D_80114AB0[spark->node_58].x)
                    {
                        func_80102D5C(wp);
                        spark->node_58--;
                        wp->routine_1++;
                        spark->angle_48 = 0x800;
                        child->anim_AC  = 1;
                        func_800322A8(child, 1, 0);
                    }
                }
                else if (D_80114AB0[spark->node_58].value_8 == 4)
                {
                    if (wp->position.z >= D_80114AB0[spark->node_58].z)
                    {
                        func_80102D5C(wp);
                        spark->node_58--;
                        wp->routine_1++;
                        spark->angle_48 = 0xC00;
                        child->anim_AC  = 1;
                        func_800322A8(child, 1, 0);
                    }
                }
                else if (D_80114AB0[spark->node_58].value_8 == 6)
                {
                    if (wp->position.x >= D_80114AB0[spark->node_58].x)
                    {
                        if (spark->rand_52.h & 1)
                        {
                            func_80102D5C(wp);
                            spark->node_58--;
                            wp->routine_1++;
                            spark->angle_48 = 0;
                            child->anim_AC  = 1;
                            func_800322A8(child, 1, 0);
                        }
                        else
                        {
                            spark->node_58 = 2;
                        }
                    }
                }
                else if (D_80114AB0[spark->node_58].value_8 == 5)
                {
                    if (wp->position.z <= D_80114AB0[spark->node_58].z)
                    {
                        if (spark->rand_52.h & 1)
                        {
                            spark->node_58 = 7;
                            func_80102D5C(wp);
                            spark->node_58--;
                            wp->u_64.h[0] = 1;
                            wp->routine_1++;
                            spark->angle_48 = 0xC00;
                            child->anim_AC  = 4;
                            func_800322A8(child, 4, 0);
                        }
                        else
                        {
                            func_80102D5C(wp);
                            spark->node_58--;
                            wp->routine_1++;
                            spark->angle_48 = 0x400;
                            child->anim_AC  = 1;
                            func_800322A8(child, 1, 0);
                        }
                    }
                }
            }
        }
        else
        {
            spark->turn_46 = -0xF;
            if (D_80114AB0[spark->node_58].value_8 == 1)
            {
                if (wp->position.z <= D_80114AB0[spark->node_58].z)
                {
                    if (spark->rand_52.h & 1)
                    {
                        spark->node_58 = 0xF;
                        func_80102D5C(wp);
                        spark->node_58--;
                        wp->u_64.h[0] = 0;
                        wp->routine_1++;
                        spark->angle_48 = 0x400;
                        child->anim_AC  = 1;
                        func_800322A8(child, 1, 0);
                    }
                    else
                    {
                        func_80102D5C(wp);
                        spark->node_58--;
                        wp->routine_1++;
                        spark->angle_48 = 0xC00;
                        child->anim_AC  = 4;
                        func_800322A8(child, 4, 0);
                    }
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 3)
            {
                if (wp->position.x >= D_80114AB0[spark->node_58].x)
                {
                    func_80102D5C(wp);
                    spark->node_58--;
                    wp->routine_1++;
                    spark->angle_48 = 0x800;
                    child->anim_AC  = 4;
                    func_800322A8(child, 4, 0);
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 0)
            {
                if (wp->position.z >= D_80114AB0[spark->node_58].z)
                {
                    func_80102D5C(wp);
                    spark->node_58--;
                    wp->routine_1++;
                    spark->angle_48 = 0x400;
                    child->anim_AC  = 4;
                    func_800322A8(child, 4, 0);
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 2)
            {
                if (wp->position.x <= D_80114AB0[spark->node_58].x)
                {
                    if (spark->rand_52.h & 1)
                    {
                        func_80102D5C(wp);
                        spark->node_58--;
                        wp->routine_1++;
                        spark->angle_48 = 0;
                        child->anim_AC  = 4;
                        func_800322A8(child, 4, 0);
                    }
                    else
                    {
                        spark->node_58 = 0xA;
                    }
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 4)
            {
                if (wp->position.x <= D_80114AB0[spark->node_58].x)
                {
                    func_80102D5C(wp);
                    spark->node_58++;
                    wp->routine_1++;
                    spark->angle_48 = 0;
                    child->anim_AC  = 4;
                    func_800322A8(child, 4, 0);
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 7)
            {
                if (wp->position.z <= D_80114AB0[spark->node_58].z)
                {
                    func_80102D5C(wp);
                    spark->node_58++;
                    wp->routine_1++;
                    spark->angle_48 = 0xC00;
                    child->anim_AC  = 4;
                    func_800322A8(child, 4, 0);
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 5)
            {
                if (wp->position.x >= D_80114AB0[spark->node_58].x)
                {
                    if (spark->rand_52.h & 1)
                    {
                        func_80102D5C(wp);
                        spark->node_58++;
                        wp->routine_1++;
                        spark->angle_48 = 0x800;
                        child->anim_AC  = 4;
                        func_800322A8(child, 4, 0);
                    }
                    else
                    {
                        spark->node_58 = 5;
                    }
                }
            }
            else if (D_80114AB0[spark->node_58].value_8 == 6)
            {
                if (wp->position.z >= D_80114AB0[spark->node_58].z)
                {
                    if (spark->rand_52.h & 1)
                    {
                        spark->node_58 = 0;
                        func_80102D5C(wp);
                        spark->node_58++;
                        wp->u_64.h[0] = 0;
                        wp->routine_1++;
                        spark->angle_48 = 0xC00;
                        child->anim_AC  = 1;
                        func_800322A8(child, 1, 0);
                    }
                    else
                    {
                        func_80102D5C(wp);
                        spark->node_58++;
                        wp->routine_1++;
                        spark->angle_48 = 0x400;
                        child->anim_AC  = 4;
                        func_800322A8(child, 4, 0);
                    }
                }
            }
        }
    }
}

void func_80101904(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STAGE_OBJ *child;
    uint8 dir;

    spark = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    if (!(wp->value_C & 1))
    {
        child = func_80036294(wp->value_439);
        if (wp->u_64.h[0] == 0)
        {
            wp->value_426 = 4;
        }
        else
        {
            *(sint16 *)&wp->value_426 = -4; // a signed store (addiu)
        }
        spark->angle_48 = (spark->angle_48 + spark->turn_46) & 0xFFF;
        spark->timer_4C++;
        if (spark->timer_4C == 0x40)
        {
            if (wp->u_64.h[0] == 0)
            {
                child->anim_AC = 2;
            }
            else
            {
                child->anim_AC = 5;
            }
            func_800322A8(child, child->anim_AC, 0);
        }
        else if (spark->timer_4C == 0x100)
        {
            if (wp->u_64.h[0] == 0)
            {
                child->anim_AC = 3;
            }
            else
            {
                child->anim_AC = 6;
            }
            func_800322A8(child, child->anim_AC, 0);
        }
        if (wp->u_64.h[0] == 0)
        {
            dir = D_80114AB0[spark->node_58].value_8;
            if (dir == 2)
            {
                if (spark->angle_48 < 0xC00)
                {
                    func_80102EC0(wp);
                    spark->node_58++;
                    wp->rotation.y = 0xC00;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 0)
            {
                if (spark->angle_48 >= 0x400)
                {
                    func_80102EC0(wp);
                    spark->node_58++;
                    wp->rotation.y = 0;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 3)
            {
                if (spark->angle_48 >= 0x800)
                {
                    func_80102EC0(wp);
                    spark->node_58++;
                    wp->rotation.y = 0x400;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 1)
            {
                if (spark->angle_48 > 0xC00)
                {
                    func_80102EC0(wp);
                    spark->node_58 = 0;
                    wp->rotation.y = 0x800;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 7)
            {
                if (spark->angle_48 > 0xC00)
                {
                    func_80102EC0(wp);
                    spark->node_58--;
                    wp->rotation.y = 0x800;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 4)
            {
                if (spark->angle_48 < 0xC00)
                {
                    func_80102EC0(wp);
                    spark->node_58--;
                    wp->rotation.y = 0xC00;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 6)
            {
                if (spark->angle_48 > 0x400)
                {
                    func_80102EC0(wp);
                    spark->node_58 = 0xF;
                    wp->rotation.y = 0;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 5)
            {
                if (spark->angle_48 > 0x800)
                {
                    func_80102EC0(wp);
                    spark->node_58--;
                    wp->rotation.y = 0x400;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
        }
        else
        {
            dir = D_80114AB0[spark->node_58].value_8;
            if (dir == 1)
            {
                if (spark->angle_48 < 0x800)
                {
                    func_80102EC0(wp);
                    spark->node_58--;
                    wp->rotation.y = 0xC00;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 3)
            {
                if (spark->angle_48 < 0x400)
                {
                    func_80102EC0(wp);
                    spark->node_58--;
                    wp->rotation.y = 0x800;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 0)
            {
                if (spark->angle_48 > 0x400)
                {
                    func_80102EC0(wp);
                    spark->node_58--;
                    wp->rotation.y = 0x400;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 2)
            {
                if (spark->angle_48 < 0xC00)
                {
                    func_80102EC0(wp);
                    spark->node_58 = 7;
                    wp->rotation.y = 0;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 4)
            {
                if (spark->angle_48 < 0xC00)
                {
                    func_80102EC0(wp);
                    spark->node_58++;
                    wp->rotation.y = 0;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 7)
            {
                if (spark->angle_48 < 0x800)
                {
                    func_80102EC0(wp);
                    spark->node_58++;
                    wp->rotation.y = 0xC00;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 5)
            {
                if (spark->angle_48 < 0x400)
                {
                    func_80102EC0(wp);
                    spark->node_58 = 8;
                    wp->rotation.y = 0x800;
                    wp->routine_1--;
                }
                else
                {
                    func_80102E10(wp);
                }
            }
            else if (dir == 6)
            {
                if (spark->angle_48 <= 0x400)
                {
                    func_80102E10(wp);
                }
                else
                {
                    func_80102EC0(wp);
                    spark->node_58++;
                    wp->rotation.y = 0x400;
                    wp->routine_1--;
                }
            }
        }
    }
}

void func_80101DFC(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STAGE_OBJ *obj;

    spark = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    if (wp->value_D < 0 && wp->value_E < 0)
    {
        wp->value_AC  = 5;
        wp->value_43A = 0xFF;
        func_800322A8(wp, wp->value_AC, 0);
    }
    else
    {
        wp->value_AC = 0;
        func_800322A8(wp, 0, 0);
        if (wp->value_E > 0)
        {
            spark->partner_5A = wp->value_E;
            obj               = func_80036294(wp->value_E);
            obj->u_E.b.byte_E |= 8;
            obj = func_80036294(wp->value_D);
            obj->u_E.b.byte_E |= 4;
        }
        else
        {
            spark->partner_5A = wp->value_D;
            obj               = func_80036294(wp->value_D);
            obj->u_E.b.byte_E |= 8;
        }
    }
    wp->routine_2++;
}

void func_80101F08(ST1D_VIEW *wp)
{
    ST1D_VIEW *obj;

    if (wp->value_43A == 0xFF)
    {
        if (wp->value_A6 & 4)
        {
            Sound_call2(0x1C4, &wp->position);
        }
        if (wp->value_A6 & 1)
        {
            wp->value_C &= ~2;
        }
        if (wp->value_A7 == -1)
        {
            wp->value_AC = 6;
            wp->routine_2++;
            func_800322A8(wp, 6, 0);
        }
    }
    else if (wp->value_E == wp->value_43A || wp->value_D == wp->value_43A)
    {
        obj = (ST1D_VIEW *)func_80036294(wp->value_43A);
        if (obj->value_A6 & 4)
        {
            Sound_call2(0x1C4, &obj->position);
        }
        if (obj->value_A6 & 1)
        {
            obj->value_E &= ~2;
        }
        if (obj->value_A7 == -1)
        {
            wp->routine_2++;
            obj->value_E = (obj->value_E & ~8) | 0x10;
        }
    }
    else
    {
        wp->routine_2++;
    }
}

void func_80102070(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STAGE_OBJ *obj;
    ST1D_VIEW *partner;
    sint8 count37;
    sint8 count3;
    sint8 i;

    count37 = 0;
    count3  = 0;
    spark   = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    if (wp->value_43A == 0xFF)
    {
        if (wp->value_A7 == -1)
        {
            wp->routine_2++;
        }
    }
    else if (wp->value_E == wp->value_43A || wp->value_D == wp->value_43A)
    {
        if (((ST1D_VIEW *)func_80036294(wp->value_43A))->value_A7 == -1)
        {
            wp->routine_2++;
        }
    }
    else
    {
        wp->value_430 = 0x3C;
        wp->routine_2++;
        return;
    }
    if (wp->routine_2 == 3)
    {
        for (i = 0; i < 16; i++)
        {
            if (D_8009F108[i].flags_0 != 0)
            {
                if (D_8009F108[i].kind_2 == 0x37)
                {
                    count37++;
                }
                if (D_8009F108[i].kind_2 == 3)
                {
                    count3++;
                }
            }
        }
        if (count3 + count37 < spark->limit_5C)
        {
            if (spark->partner_5A != 0xFF)
            {
                func_80036294(spark->partner_5A);
            }
            if (count3 == count37)
            {
                if (spark->rand_52.h & 1)
                {
                    obj = func_80031418();
                    if (obj != NULL)
                    {
                        obj->flags_0      = 1;
                        obj->kind_2       = 0x37;
                        obj->variant_3    = 1;
                        obj->value_4      = 0;
                        obj->reserved05   = 0;
                        obj->u_C.b.byte_C = 0;
                        obj->u_C.b.byte_D = 0;
                        obj->u_E.b.byte_E = 0;
                        obj->u_E.b.byte_F = 0;
                        if (spark->partner_5A != 0xFF)
                        {
                            partner         = (ST1D_VIEW *)func_80036294(spark->partner_5A);
                            obj->rotation.y = (partner->rotation.y + 0x800) & 0xFFF;
                            obj->position.x = partner->value_1B8;
                            obj->position.y = partner->value_1BA + 0xC0;
                            obj->position.z = partner->value_1BC;
                        }
                        else
                        {
                            obj->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                            obj->position.x = wp->value_1E0;
                            obj->position.y = wp->value_1E2 + 0xC0;
                            obj->position.z = wp->value_1E4;
                        }
                        obj->position_fixed.v.x = obj->position.x << 16;
                        obj->position_fixed.v.y = obj->position.y << 16;
                        obj->position_fixed.v.z = obj->position.z << 16;
                    }
                }
                else
                {
                    obj = func_80031418();
                    if (obj != NULL)
                    {
                        obj->flags_0      = 1;
                        obj->kind_2       = 3;
                        obj->variant_3    = 0x41;
                        obj->value_4      = 0;
                        obj->reserved05   = 0;
                        obj->u_C.b.byte_C = 0x10;
                        obj->u_C.b.byte_D = 0;
                        obj->u_E.b.byte_E = 0;
                        obj->u_E.b.byte_F = 0;
                        if (spark->partner_5A != 0xFF)
                        {
                            partner         = (ST1D_VIEW *)func_80036294(spark->partner_5A);
                            obj->rotation.y = (partner->rotation.y + 0x800) & 0xFFF;
                            obj->position.x = partner->value_1B8;
                            obj->position.y = partner->value_1BA + 0x100;
                            obj->position.z = partner->value_1BC;
                        }
                        else
                        {
                            obj->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                            obj->position.x = wp->value_1E0;
                            obj->position.y = wp->value_1E2 + 0x100;
                            obj->position.z = wp->value_1E4;
                        }
                        obj->position_fixed.v.x = obj->position.x << 16;
                        obj->position_fixed.v.y = obj->position.y << 16;
                        obj->position_fixed.v.z = obj->position.z << 16;
                    }
                }
            }
            else if (count37 < count3)
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->flags_0      = 1;
                    obj->kind_2       = 0x37;
                    obj->variant_3    = 1;
                    obj->value_4      = 0;
                    obj->reserved05   = 0;
                    obj->u_C.b.byte_C = 0;
                    obj->u_C.b.byte_D = 0;
                    obj->u_E.b.byte_E = 0;
                    obj->u_E.b.byte_F = 0;
                    if (spark->partner_5A != 0xFF)
                    {
                        partner         = (ST1D_VIEW *)func_80036294(spark->partner_5A);
                        obj->rotation.y = (partner->rotation.y + 0x800) & 0xFFF;
                        obj->position.x = partner->value_1B8;
                        obj->position.y = partner->value_1BA + 0xC0;
                        obj->position.z = partner->value_1BC;
                    }
                    else
                    {
                        obj->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                        obj->position.x = wp->value_1E0;
                        obj->position.y = wp->value_1E2 + 0xC0;
                        obj->position.z = wp->value_1E4;
                    }
                    obj->position_fixed.v.x = obj->position.x << 16;
                    obj->position_fixed.v.y = obj->position.y << 16;
                    obj->position_fixed.v.z = obj->position.z << 16;
                }
            }
            else
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->flags_0      = 1;
                    obj->kind_2       = 3;
                    obj->variant_3    = 0x41;
                    obj->value_4      = 0;
                    obj->reserved05   = 0;
                    obj->u_C.b.byte_C = 0x10;
                    obj->u_C.b.byte_D = 0;
                    obj->u_E.b.byte_E = 0;
                    obj->u_E.b.byte_F = 0;
                    if (spark->partner_5A != 0xFF)
                    {
                        partner         = (ST1D_VIEW *)func_80036294(spark->partner_5A);
                        obj->rotation.y = (partner->rotation.y + 0x800) & 0xFFF;
                        obj->position.x = partner->value_1B8;
                        obj->position.y = partner->value_1BA + 0x100;
                        obj->position.z = partner->value_1BC;
                    }
                    else
                    {
                        obj->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                        obj->position.x = wp->value_1E0;
                        obj->position.y = wp->value_1E2 + 0x100;
                        obj->position.z = wp->value_1E4;
                    }
                    obj->position_fixed.v.x = obj->position.x << 16;
                    obj->position_fixed.v.y = obj->position.y << 16;
                    obj->position_fixed.v.z = obj->position.z << 16;
                }
            }
        }
    }
    spark->timer_50 = 0;
}

void func_8010253C(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STAGE_OBJ *obj;

    spark = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    if (wp->value_430 >= 0x3C)
    {
        if (wp->value_43A == 0xFF)
        {
            wp->value_AC = 7;
            func_800322A8(wp, 7, 0);
            wp->value_C |= 2;
        }
        else if (wp->value_E == wp->value_43A || wp->value_D == wp->value_43A)
        {
            obj               = func_80036294(wp->value_43A);
            obj->u_E.b.byte_E = (obj->u_E.b.byte_E & ~0x10) | 0x22;
        }
        spark->timer_50 = 0;
        wp->routine_2++;
    }
    else
    {
        wp->value_430++;
    }
}

void func_80102614(ST1D_VIEW *wp)
{
    ST1D_VIEW *obj;

    if (wp->value_43A == 0xFF)
    {
        if (wp->value_A6 & 8)
        {
            Sound_call2(0x1C5, &wp->position);
        }
        if (wp->value_A7 == -1)
        {
            wp->routine_2 = 0;
            wp->value_42E = 0;
            wp->value_AC  = 1;
            wp->value_C &= ~1;
            func_800322A8(wp, 1, 0);
        }
    }
    else if (wp->value_E == wp->value_43A || wp->value_D == wp->value_43A)
    {
        obj = (ST1D_VIEW *)func_80036294(wp->value_43A);
        if (obj->value_A6 & 8)
        {
            Sound_call2(0x1C5, &obj->position);
        }
        if (obj->value_A7 == -1)
        {
            obj->value_E &= ~0x20;
            wp->routine_2 = 0;
            wp->value_42E = 0;
            wp->value_AC  = 1;
            wp->value_C &= ~1;
            func_800322A8(wp, 1, 0);
            if (wp->value_E == wp->value_43A)
            {
                obj = (ST1D_VIEW *)func_80036294(wp->value_D);
                obj->value_E &= ~4;
            }
        }
    }
    else
    {
        if (wp->value_D > 0)
        {
            obj = (ST1D_VIEW *)func_80036294(wp->value_D);
            obj->value_E &= ~4;
        }
        wp->routine_2 = 0;
        wp->value_42E = 0;
        wp->value_C   = (wp->value_C & ~1) | 0x40;
    }
}

void func_801027AC(ST1D_VIEW *wp)
{
    if (wp->value_43A == 0xFF)
    {
        wp->value_AC = 7;
        wp->value_C |= 2;
        func_800322A8(wp, 7, 0);
        wp->routine_3 = 3;
    }
    else
    {
        wp->value_AC = 2;
        func_800322A8(wp, 2, 0);
        if (wp->value_E == wp->value_43A || wp->value_D == wp->value_43A)
        {
            func_80036294(wp->value_43A)->u_E.b.byte_E = 0x42;
        }
    }
    wp->routine_3++;
}

void func_80102864(ST1D_VIEW *wp)
{
    ST1D_VIEW *obj;
    sint8 done;

    if (wp->value_A6 & 8)
    {
        Sound_call2(0x1C5, &wp->position);
    }
    done = wp->value_A7;
    if (done == -1)
    {
        wp->value_C &= ~1;
        if (wp->value_E == wp->value_43A || wp->value_D == wp->value_43A)
        {
            obj = (ST1D_VIEW *)func_80036294(wp->value_43A);
            if (obj->value_A6 & 8)
            {
                Sound_call2(0x1C5, &obj->position);
            }
            if (obj->value_A7 == done)
            {
                wp->value_AC = 3;
                func_800322A8(wp, 3, 0);
                wp->value_430 = 0;
                wp->u_44.uh[0] *= 2;
                wp->value_426 *= 2;
                obj->value_E &= ~0x40;
                wp->routine_3++;
                wp->value_C |= 0x80;
                if (wp->value_E == wp->value_43A)
                {
                    obj = (ST1D_VIEW *)func_80036294(wp->value_D);
                    obj->value_E &= ~4;
                }
            }
        }
        else
        {
            wp->value_AC = 3;
            func_800322A8(wp, 3, 0);
            wp->value_430 = 0;
            wp->u_44.uh[0] *= 2;
            wp->value_426 *= 2;
            wp->routine_3++;
            wp->value_C |= 0x80;
        }
    }
}

void func_801029F4(ST1D_VIEW *wp)
{
    if (wp->value_430 >= 0x5A)
    {
        wp->value_AC = 4;
        func_800322A8(wp, 4, 0);
        wp->routine_3++;
        return;
    }
    D_80114AA8[wp->routine_1](wp);
    wp->value_430++;
}

void func_80102A84(ST1D_VIEW *wp)
{
    if (wp->value_A7 == -1)
    {
        wp->value_AC = 1;
        func_800322A8(wp, 1, 0);
        wp->u_44.h[0] = 0xC;
        wp->routine_2 = 0;
        wp->routine_3 = 0;
        wp->value_43B = 0;
        wp->value_42E = 0;
        wp->value_C &= 0x3F;
        wp->value_426 = (sint16)wp->value_426 / 2;
    }
}

void func_80102B08(STAGE_OBJ *wp)
{
    if (wp->value_A7 == -1)
    {
        wp->anim_AC = 2;
        func_800322A8(wp, 2, 0);
        wp->routine_3 = 1;
    }
}

void func_80102B54(ST1D_VIEW *wp)
{
    ST1D_SPARK *spark;
    STCOM_EFFECT *fx;
    uint8 joint;

    spark = (ST1D_SPARK *)&wp->reserved3C0[0x20];
    switch (wp->routine_2)
    {
        case 0:
            if (spark->timer_4C != 0)
            {
                if (!(spark->timer_4C & 3))
                {
                    joint            = D_80114B50[spark->rand_52.b & 7].joint_0;
                    spark->offset_38 = D_80114B50[(sint8)(spark->rand_52.b & 7)].offset_2; // indexed again, not reused
                    fx               = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0           = 5;
                        fx->kind_2            = 0x80;
                        fx->variant_3         = 0x40;
                        fx->value_D           = spark->rand_52.b & 3;
                        fx->sprite.position.x = wp->vec_180[joint].x + spark->offset_38.x;
                        fx->sprite.position.y = wp->vec_180[joint].y + spark->offset_38.y;
                        fx->sprite.position.z = wp->vec_180[joint].z + spark->offset_38.z;
                    }
                }
            }
            else
            {
                wp->routine_2++;
            }
            spark->timer_4C--;
            break;
        case 1:
            func_8005D6E8(wp);
            Fade_start(14);
            wp->routine_2++;
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->flags_0 &= ~2;
                wp->routine_2++;
            }
            break;
        case 3:
            Fade_start(6);
            wp->routine_2++;
            break;
        case 4:
            if (D_80098A72 == 0)
            {
                wp->routine_0 = 2;
            }
            break;
    }
}

void func_80102D5C(ST1D_VIEW *wp)
{
    wp->position.x       = D_80114AB0[wp->value_438].x;
    wp->position.z       = D_80114AB0[wp->value_438].z;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.x = wp->position.x << 16;
    wp->value_420        = wp->position.x + D_80114AB0[wp->value_438].value_4;
    wp->value_424        = wp->position.z + D_80114AB0[wp->value_438].value_6;
}

void func_80102E10(ST1D_VIEW *wp)
{
    sint32 temp_lo;

    wp->rotation.y       = ((uint16)wp->rotation.y + wp->value_426) & 0xFFF;
    wp->position.x       = wp->value_420 + ((sint32)(wp->value_42A * rsin((sint32)wp->value_428)) >> 0xC);
    temp_lo              = wp->value_42A * rcos((sint32)wp->value_428);
    wp->position_fixed.x = wp->position.x << 0x10;
    wp->position.z       = wp->value_424 + (temp_lo >> 0xC);
    wp->position_fixed.y = wp->position.y << 0x10;
    wp->position_fixed.z = wp->position.z << 0x10;
}

void func_80102EC0(ST1D_VIEW *wp)
{
    wp->position.x       = D_80114AB0[wp->value_438].x;
    wp->position.z       = D_80114AB0[wp->value_438].z;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position.z << 16;
}
