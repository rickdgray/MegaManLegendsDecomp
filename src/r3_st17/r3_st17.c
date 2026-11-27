#include "common.h"
#include "st17.h"

// Installs the stage's slot routine tables.
void func_8010052C(void)
{
    STAGE_TABLE_3C0      = D_8011A82C;
    STAGE_TABLE_5A4      = D_8011A9CC;
    STAGE_TABLE_10C      = D_8011AA18;
    STAGE_TABLE_48       = D_8011AAD8;
    STAGE_TABLE_24       = D_8011AB44;
    STAGE_TABLE_50       = D_8011ABB4;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_8010059C(void)
{
    void *spawn;
    sint16 *cells;

    Room_model_init(D_8011ABB8[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 1;
    spawn                     = D_8011AD1C[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_8011AD44[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_8011ADF4[D_8011AE74[Game_work.value_51]], D_8011AD54[Game_work.value_51]);
    func_8005DC10(0);
    func_80100704();
}

void func_80100704(void)
{
}

// Runs the current room's script.
void func_8010070C(void)
{
    D_8011AEA4[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100760(void)
{
}

void func_80100768(void)
{
}

void func_80100770(void)
{
}

void func_80100778(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DDE4(0x34);
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x605) != 0)
            {
                func_8001DDE4(0x35);
                wp->routine_4++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x606) != 0)
            {
                func_8001DDE4(0x36);
                wp->routine_4++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x607) != 0)
            {
                func_8001DDE4(0x37);
                wp->routine_4++;
            }
            break;
        case 4:
            break;
    }
}

void func_80100828(STAGE_OBJ *wp)
{
    uint8 temp_a1;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        wp->routine_0++;
    }
    temp_a1 = wp->anim_AC;
    if (temp_a1 != wp->anim_prev_AD)
    {
        func_800322A8(wp, temp_a1, 0);
        return;
    }
    func_80032488(wp);
}

void func_8010093C(STAGE_OBJ *wp)
{
    D_8011AEE4[wp->routine_1](wp);
}

void func_80100978(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        func_800322A8(wp, wp->variant_3, 0);
        wp->routine_2++;
    }
    switch (wp->u_C.b.byte_C)
    {
        case 1:
            wp->position.x++;
            break;
        case 2:
            wp->position.z -= 6;
            break;
        case 3:
            wp->position.z += 2;
            break;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    func_80032488(wp);
}

void func_80100ACC(STAGE_OBJ *wp)
{
    ST17_PART88 *part;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    part                    = ST17_PART88_OF(wp);
    part->value_6           = rand();
    D_8011AEE8[wp->routine_0](wp, part);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_C.b.byte_C);
    }
    else
    {
        func_80032488(wp);
    }
    func_80051B68(wp, 1, -1, 0);
    wp->anim_prev_AD = wp->anim_AC;
}

void func_80100BD0(STAGE_OBJ *wp, ST17_PART88 *part)
{
    sint8 i;

    wp->flags_0 |= 0x42;
    func_8002F9EC(wp, 0);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_78       = 0;
    part->flags_4      = 1;
    for (i = 0; i < 3; i++)
    {
        part->vec_C[i].x        = wp->position.x;
        part->vec_C[i].y        = wp->position.y;
        part->vec_C[i].z        = 0x200;
        part->pos_24[i].x       = 0;
        part->pos_24[i].y       = wp->position.y - 0xC8;
        part->pos_24[i].z       = (i - 1) * 400 - 200;
        part->hit_3C[i].value_4 = 0;
        part->hit_3C[i].value_0 = 0;
    }
    part->vec_C[0].x -= 0x100;
    part->vec_C[1].x += 0x100;
    func_80101B58(wp, 0, part->vec_C);
    wp->routine_0++;
}

void func_80100CEC(STAGE_OBJ *wp, void *part)
{
    func_80100D2C(wp, part);
    func_80100E5C(wp, part);
}

void func_80100D2C(STAGE_OBJ *wp, ST17_PART88 *part)
{
    sint8 i;
    sint16 damage;
    uint32 hit;

    i      = 0;
    damage = 0;
    while (i < 3)
    {
        hit = part->hit_3C[i].value_0;
        if ((hit & 0xFFFFFF) && (hit & 0x1C000000))
        {
            damage = hit;
        }
        i++;
    }
    if (damage != 0)
    {
        if (part->flags_4 & 1)
        {
            if (ST17_GAME.value_174 == 0)
            {
                Swing_Camera2(0x1E, 0x400, 0x2800, &wp->position);
                ST17_GAME.value_5C -= damage;
                if (ST17_GAME.value_5C <= 0)
                {
                    ST17_GAME.value_5C = 0;
                    part->flags_4 &= ~1;
                }
                Sound_call2(0xA0, &wp->position);
            }
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
}

void func_80100E5C(STAGE_OBJ *wp, ST17_PART88 *part)
{
    sint8 i;

    for (i = 0; i < 3; i++)
    {
        func_800341BC(&part->pos_24[i], 0x140, 0, 0, wp->value_1, &part->hit_3C[i], 0x2000000, 0, 0x80);
        part->hit_3C[i].value_0 = 0;
    }
}
