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

void func_80102F24(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_SVECTOR *save;

    wp->value_AD            = wp->value_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_15C.h[1]          = 0x4210;
    wp->ext.u_2.h           = rand();
    D_80114BA0[wp->routine_0](wp);
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
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    ext->u_4C.i = 0;
    save        = D_8011A698;
    do
    {
        *save                = wp->position;
        D_8011A6A0           = wp->position_fixed;
        wp->u_64.h[0]        = wp->rotation.y;
        wp->position         = wp->vec_180[2];
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->position_fixed.z = wp->position.z << 16;
        wp->rotation.y       = (ext->u_3C.h[0] + wp->rotation.y) & 0xFFF;
        Obj_pos_set(wp, 0, -0x200, D_80114BF8[ext->u_4C.i]);
        ext->u_44.fx[ext->u_4C.i]->x_1C = wp->position.x;
        ext->u_44.fx[ext->u_4C.i]->y_1E = wp->position.y;
        ext->u_44.fx[ext->u_4C.i]->z_20 = wp->position.z;
        wp->position                    = *save;
        wp->position_fixed              = D_8011A6A0;
        wp->rotation.y                  = wp->u_64.h[0];
        ext->u_4C.i++;
    } while (ext->u_4C.i < 2);
    if ((wp->flags_0 & 2) && (ext->flags_0 & 4))
    {
        ext->pos_C = wp->vec_180[0];
        ext->pos_C.y += 30;
        func_800341BC(&ext->pos_C, 0x50, 0, 0x8000, wp->value_1, &ext->value_14, ext->value_8 | 0x4880000, 0x800000, 0);
    }
    ext->value_14 = 0;
}

void func_8010329C(ST1D_VIEW *wp)
{
    // D_80098844 is declared with stcom16's shorter record; this one reads its byte 0xF.
    sint16 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_64.w[0]  = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158               = 0x02000200;
    wp->u_15C.w[0]              = 0x200;
    wp->ext.flags_0             = 0x26;
    *(sint32 *)&wp->ext.u_4     = 0;
    *(sint32 *)&wp->ext.value_8 = 0;
    wp->ext.value_14            = 0;
    wp->ext.value_18            = 0;
    Track_reset(wp->ext.u_24.track, ((ST1D_KIND *)D_80098844[wp->kind_2])->value_F, -0x60);
    wp->ext.u_34.h[0]         = 0;
    wp->ext.u_34.h[1]         = 0;
    wp->ext.u_3C.h[0]         = 0;
    wp->ext.u_38.h[0]         = 4;
    wp->ext.obj_40            = func_80036294(wp->value_D);
    wp->ext.u_44.fx[0]        = (STAGE_FX *)func_80036294(wp->ext.obj_40->u_C.b.byte_D);
    wp->ext.u_44.fx[1]        = (STAGE_FX *)func_80036294(wp->ext.obj_40->u_E.b.byte_E);
    life                      = D_80098844[wp->kind_2]->life_8 << 4;
    wp->data_78               = D_80114BEC;
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

void func_801033E4(ST1D_VIEW *wp)
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
        func_80105318(wp);
    }
    wp->u_64.h[0] = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x40);
    if (((ext->u_3C.h[0] + wp->u_64.h[0] + 0x500) & 0xFFF) < 0xA00)
    {
        ext->u_3C.h[0] += wp->u_64.h[0];
    }
    D_80114BB4[wp->routine_1](wp);
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
                ext->effect_50->flags_0         = 5;
                ext->effect_50->kind_2          = 0x80;
                ext->effect_50->variant_3       = 0x41;
                ext->effect_50->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80031988(ext->u_44.fx[0]);
            func_80031988(ext->u_44.fx[1]);
            ext->obj_40->u_E.b.byte_F |= 2;
            func_80047228(wp, &wp->vec_180[0], 0);
            Sound_call2(0xA1, &wp->vec_180[0]);
        }
    }
}

void func_801036B0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext = &wp->ext;
    if (wp->ext.flags_0 & 2)
    {
        func_80105318(wp);
    }
    wp->ext.u_3C.h[0] = (wp->ext.u_3C.h[0] - 0x80 - wp->ext.u_2.b[0]) & 0xFFF;
    D_80114BB4[wp->routine_1](wp);
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
                ext->effect_50->flags_0         = 5;
                ext->effect_50->kind_2          = 0x80;
                ext->effect_50->variant_3       = 0x41;
                ext->effect_50->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80031988(ext->u_44.fx[0]);
            func_80031988(ext->u_44.fx[1]);
            ext->obj_40->u_E.b.byte_F |= 2;
            func_80047228(wp, &wp->vec_180[0], 1);
            Sound_call2(0xA1, &wp->vec_180[0]);
        }
    }
}

void func_80103870(ST1D_VIEW *wp)
{
    func_80031824(wp);
    func_80031988(wp->ext.u_44.fx[0]);
    func_80031988(wp->ext.u_44.fx[1]);
}

void func_801038B0(ST1D_VIEW *wp)
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

void func_80103920(ST1D_VIEW *wp)
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
            if (wp->variant_3 == 0)
            {
                wp->ext.u_34.h[0] = 300;
            }
            // fall through
        case 1:
            if (wp->value_A6 == 2)
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
            if (wp->variant_3 == 0 && ext->u_34.h[0] == 0)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if ((uint32)wp->value_80 <= 0x1FFFF)
            {
                wp->routine_1             = 12;
                *(uint16 *)&wp->routine_2 = 0;
                if ((uint8)wp->value_A4 < 15)
                {
                    ext->flags_0 |= 8;
                }
                else
                {
                    ext->flags_0 &= ~8;
                }
                break;
            }
            if (wp->variant_3 == 0 && ext->u_34.h[1] == 0 &&
                func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x100, &ext->u_58.obj->position_fixed.v, ext->u_58.obj->rotation.y,
                              0x100))
            {
                switch (func_801052A0(wp))
                {
                    case 0:
                        ext->flags_0 |= 0x40;
                        // fall through
                    case 1:
                        wp->routine_1             = 12;
                        *(uint16 *)&wp->routine_2 = 0;
                        ext->flags_0 |= 0x200;
                        if ((uint8)wp->value_A4 < 15)
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
            if (wp->variant_3 == 1 && ext->u_34.h[0] == 0 &&
                func_80031DCC(&wp->position_fixed, (wp->rotation.y + ext->u_3C.h[0]) & 0xFFF, 0x18, &ext->u_58.obj->position_fixed.v,
                              ext->u_58.obj->rotation.y, 0x300))
            {
                ext->piece_54 = (STAGE_PIECE *)Open_SHL_WORK();
                if (ext->piece_54 != NULL)
                {
                    ext->piece_54->flags_0        = 1;
                    ext->piece_54->kind_2         = 9;
                    ext->piece_54->variant_3      = 0;
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

void func_80103D6C(ST1D_VIEW *wp)
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
            wp->ext.value_8 = D_80098844[wp->kind_2]->value_A;
            // fall through
        case 1:
            if (wp->value_A6 == 2)
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
                if (wp->value_A6 == 1)
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

void func_80103FB4(ST1D_VIEW *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->routine_2   = 1;
        wp->value_AC    = 0;
        wp->ext.value_8 = 0;
    }
}

void func_80103FD8(ST1D_VIEW *wp)
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

void func_801040F8(ST1D_VIEW *wp)
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

void func_80104180(ST1D_VIEW *wp)
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

void func_801043B8(ST1D_VIEW *wp)
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

void func_801045F0(ST1D_VIEW *wp)
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

void func_8010478C(ST1D_VIEW *wp)
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

void func_80104974(ST1D_VIEW *wp)
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

void func_80104B20(ST1D_VIEW *wp)
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

void func_80104C7C(ST1D_VIEW *wp)
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
                        ext->piece_54->flags_0        = 1;
                        ext->piece_54->kind_2         = 9;
                        ext->piece_54->variant_3      = 0;
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

void func_80105060(ST1D_VIEW *wp)
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

sint32 func_801052A0(ST1D_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;

    ext            = &wp->ext;
    wp->u_64.h[0]  = 0;
    wp->ext.u_4C.i = 0;
    while (1)
    {
        wp->u_64.h[0] += D_80114BFC[ext->u_4C.i];
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

sint32 func_80105318(ST1D_VIEW *wp)
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
                wp->ext.u_4C.i  = D_80098844[wp->kind_2]->limit_9;
            }
            if (wp->ext.flags_0 & 0x20)
            {
                wp->ext.value_A += wp->ext.u_4C.i;
                if ((wp->ext.value_14 & 0x20000000) || wp->ext.value_A >= D_80098844[wp->kind_2]->limit_9)
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
                        wp->u_64.h[0] = Angle_xz_svector(&D_80114C00, &wp->ext.from_1C);
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
            else if ((wp->ext.value_14 & 0x20000000) || wp->ext.value_A >= D_80098844[wp->kind_2]->limit_9)
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
