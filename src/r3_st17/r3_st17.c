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

void func_80100F10(STAGE_OBJ *wp)
{
    sint16 x;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    switch (wp->routine_0)
    {
        case 1:
        case 3:
            break;
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_44.half[0] = -0x10E;
            wp->value_48.half[0] = -0x10E;
            wp->anim_AC          = 1;
            wp->value_78         = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            wp->anim_prev_AD     = 0xFF;
            wp->routine_0++;
            break;
        case 2:
            x                      = wp->position.x + 0xC;
            wp->position.x         = x;
            wp->position_fixed.v.x = x << 0x10;
            break;
        case 4:
            if (wp->u_C.b.byte_C < 0x40)
            {
                wp->rotation.z -= 3;
                wp->u_C.b.byte_C++;
            }
            if (wp->u_C.b.byte_D < 0x3C)
            {
                wp->value_44.half[0] -= 9;
                wp->value_48.half[0] -= 9;
                wp->u_C.b.byte_D++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, wp->value_48.half[0]);
            break;
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, 1, 0x2E);
        wp->anim_prev_AD = wp->anim_AC;
    }
    else if (wp->routine_0 == 4)
    {
        func_80032538(wp);
        Model_parts_mtx_set_yxz(wp);
    }
    else
    {
        func_80032488(wp);
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80101130(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->scale.words[0]          = 0x2000200;
            wp->scale.words[1]          = 0x200;
            wp->scale.v.pad             = 0x4210;
            wp->value_78                = 0;
            wp->value_44.words.fraction = 0;
            wp->value_48.words.fraction = 0xC0;
            func_800322A8(wp, 1, 0x2E);
            wp->routine_0++;
            break;
        case 1:
            func_80032488(wp);
            break;
        case 2:
            Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, 0, (sint16)wp->value_48.words.fraction);
            func_80032488(wp);
            break;
        case 3:
            if (wp->u_C.b.byte_C < 0x40)
            {
                wp->rotation.z += 3;
                wp->u_C.b.byte_C++;
            }
            if (wp->u_C.b.byte_D < 0x3C)
            {
                wp->value_44.words.fraction -= 8;
                wp->value_48.words.fraction += 0x10;
                wp->u_C.b.byte_D++;
            }
            Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, 0, (sint16)wp->value_48.words.fraction);
            // fall through
        case 4:
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010130C(STAGE_OBJ *wp)
{
    sint16 x;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_78         = 0;
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_48.half[0] = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            func_800322A8(wp, 0, 0);
            wp->routine_0++;
            break;
        case 1:
            x                      = wp->position.x - 5;
            wp->position.x         = x;
            wp->position_fixed.v.x = x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            Ride_move(ST17_SCENE_OBJ(&Scene_work, 2), wp);
            // fall through
        case 2:
            func_80032488(wp);
            break;
    }
}

void func_8010147C(STAGE_OBJ *wp)
{
    D_8011AEF0[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

// with the move of wp.
void func_80101534(STAGE_OBJ *wp)
{
    sint32 mode;

    wp->flags_0 |= 2;
    mode = 0;
    switch (Scene_work.u_8.byte[0])
    {
        case 5:
            mode = 1;
            func_80101990(wp);
            break;
        case 7:
            mode = 2;
            func_80101990(wp);
            break;
        case 0:
            wp->rotation.z = 0x20;
            break;
        case 0xA:
            mode           = 3;
            wp->rotation.z = 0x40;
            break;
    }
    wp->position.y = -0x1F40;
    wp->position.x = 0;
    wp->position.z = 0;
    wp->routine_1  = mode + 1;
    func_8002F9EC(wp, (sint32)&wp->variant_3);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    func_800322A8(wp, 0, 0);
}

void func_80101630(STAGE_OBJ *wp)
{
    wp->position.y += D_800BBCF8[ST17_FRAME & 0x3F] >> 10;
    if (wp->u_C.b.byte_C != 0)
    {
        wp->rotation.z -= D_800BBCF8[Scene_work.value_10 & 0x3F] >> 10;
    }
}

void func_801016B4(STAGE_OBJ *wp)
{
    uint16 frame;

    switch (Scene_work.value_10)
    {
        case 0xA:
        case 0x28:
        case 0x46:
            wp->u_C.b.byte_C++;
            break;
        case 0x19:
        case 0x3C:
        case 0x5A:
            wp->u_C.b.byte_C = 0;
            break;
    }
    frame = ST17_FRAME;
    wp->position.y += D_800BBCF8[frame & 0x3F] >> 10;
    if (wp->u_C.b.byte_C != 0)
    {
        wp->rotation.z += D_8011AF0C[frame & 3];
    }
}

void func_801017A0(STAGE_OBJ *wp)
{
    if (Scene_work.value_10 < 0x18)
    {
        wp->rotation.z -= 4;
    }
    else if (Scene_work.value_10 < 0x38)
    {
        wp->rotation.z += 6;
        wp->position.x += 0xA;
    }
    else
    {
        wp->position.x += 0x14;
    }
}

void func_80101808(STAGE_OBJ *wp)
{
    if (Scene_work.value_10 < 0x64)
    {
        wp->position.x += 0x10;
    }
    else if (Scene_work.value_10 < 0x7C)
    {
        wp->rotation.z -= 4;
        wp->position.x += 8;
    }
    else
    {
        wp->position.z -= 0x30;
    }
}

void func_80101870(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = -0x7D0;
        wp->position.x = 0;
        wp->position.z = -0x4B0;
        wp->rotation.x = 0;
        wp->rotation.y = 0;
        wp->rotation.z = 0;
        wp->routine_2++;
    }
    wp->position.z = (uint16)wp->position.z - 0x20;
}

void func_801018BC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = -0x1F40;
        wp->position.x = 0;
        wp->position.z = -0x1B58;
        wp->routine_2++;
    }
    if (Scene_work.value_10 < 0x6E)
    {
        wp->position.y += D_800BBCF8[ST17_FRAME & 0x3F] >> 10;
    }
    else if (Scene_work.value_10 < 0x86)
    {
        wp->rotation.z += 3;
    }
    else if (Scene_work.value_10 < 0xA6)
    {
        wp->rotation.z -= 6;
        wp->position.x -= 0xA;
    }
    else
    {
        wp->position.x -= 0x19;
    }
}

void func_80101990(STAGE_OBJ *wp)
{
    STAGE_FX *ep;
    uint32 i;

    for (i = 0; i < 0x18; i++)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->kind_2    = 0x1A;
            ep->variant_3 = 1;
            ep->value_C   = wp->value_1;
            ep->timer_D   = i;
        }
    }
}

STAGE_OBJ *func_80101A14(STAGE_OBJ *owner, uint8 count, STCOM_SVECTOR *pos)
{
    STAGE_OBJ *wp;
    ST17_RIBBON *rb;
    ST17_STRAND *st;
    uint8 i;
    uint8 j;

    wp = func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    if (count == 0 || count > 6)
    {
        func_80031824(wp);
        return NULL;
    }
    wp->flags_0 = 1;
    wp->flags_6 |= 0x20;
    wp->value_4         = 0;
    *(uint32 *)&wp->u_C = 0;
    wp->kind_2          = 0x12;
    wp->variant_3       = 2;
    wp->value_10        = 0;
    rb                  = ST17_RIBBON_OF(wp);
    rb->type_0          = 3;
    rb->value_1         = 0x3F;
    rb->value_2         = owner->value_1;
    rb->count_3         = count;
    rb->value_B         = 0;
    rb->color_10        = 0x2E808080;
    rb->value_C         = 0;
    for (i = 0; i < count; i++)
    {
        rb->value_4[i] = 7;
        for (j = 0, st = &rb->strand_14[i]; j < 8; j++)
        {
            st->pt[j].pos_0   = pos;
            st->pt[j].value_4 = 0;
            st->pt[j].value_5 = 0;
            st->pt[j].value_6 = 0;
        }
        pos++;
    }
    return wp;
}

STAGE_OBJ *func_80101B58(STAGE_OBJ *owner, sint8 kind, STCOM_SVECTOR *pos)
{
    STAGE_OBJ *wp;
    ST17_RIBBON *rb;
    ST17_STRAND *st;
    uint8 i;
    uint8 j;

    wp = func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    rb                  = ST17_RIBBON_OF(wp);
    wp->flags_0         = 1;
    wp->kind_2          = 0x12;
    wp->value_4         = 0;
    wp->variant_3       = kind;
    *(uint32 *)&wp->u_C = 0;
    switch (kind)
    {
        case 0:
            rb->type_0   = 0;
            rb->count_3  = 3;
            rb->value_B  = 1;
            rb->color_10 = 0x2E808080;
            break;
        case 1:
            rb->type_0   = 1;
            rb->count_3  = 6;
            rb->value_B  = 1;
            rb->color_10 = 0x2E404040;
            break;
        case 3:
            rb->type_0   = 4;
            rb->count_3  = 6;
            rb->value_B  = 2;
            rb->color_10 = 0x2E404040;
            break;
        default:
            func_80031824(wp);
            return NULL;
    }
    rb->value_1 = 0x3F;
    rb->value_2 = owner->value_1;
    rb->value_C = 0;
    for (i = 0; i < rb->count_3; i++)
    {
        rb->value_4[i] = 7;
        for (j = 0, st = &rb->strand_14[i]; j < 8; j++)
        {
            st->pt[j].pos_0   = pos;
            st->pt[j].value_4 = 0;
            st->pt[j].value_5 = 0;
            st->pt[j].value_6 = 0;
        }
        pos++;
    }
    return wp;
}

// Nothing calls it.
void func_80101D04(uint8 *wp, sint32 value)
{
    wp[0x89] = value & 0x3F;
}

void func_80101D10(STAGE_OBJ *wp)
{
    D_8011AF14[wp->variant_3](wp, &wp->model_88);
}

void func_80101D4C(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 rows;

    if (STAGE_GAME_S16(0x5E) / 4 >= STAGE_GAME_S16(0x5C))
    {
        rows = 3;
    }
    else if (STAGE_GAME_S16(0x5E) / 2 >= STAGE_GAME_S16(0x5C))
    {
        rows = 2;
    }
    else
    {
        rows = STAGE_GAME_S16(0x5E) / 4 * 3 >= STAGE_GAME_S16(0x5C);
    }
    for (i = 0; i < rows; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_801022BC(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
}

void func_80101E74(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST17_CELL *cell;

    on = 0;
    for (i = 0; i < 6; i++)
    {
        grid->mode_0 = (i < 3) ? 1 : 2;
        switch (i)
        {
            case 0:
                on = wp->u_C.b.byte_C & 1;
                break;
            case 1:
                on = ((uint8)wp->u_C.b.byte_C >> 1) & 1;
                break;
            case 2:
                on = ((uint8)wp->u_C.b.byte_C >> 2) & 1;
                break;
            case 3:
                on = wp->u_C.b.byte_D & 1;
                break;
            case 4:
                on = ((uint8)wp->u_C.b.byte_D >> 1) & 1;
                break;
            case 5:
                on = ((uint8)wp->u_C.b.byte_D >> 2) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_801022BC(grid, i, j);
            }
            if (grid->count_4[i] < 0x40)
            {
                grid->count_4[i]++;
            }
        }
        else if (grid->count_4[i] >= 8)
        {
            grid->count_4[i] = 7;
            for (j = 0; j < 8; j++)
            {
                cell          = &grid->cell_14[i][j];
                cell->state_4 = 0;
                cell->shade_5 = 0;
                cell->frame_6 = 0;
            }
        }
    }
}

void func_80102038(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST17_CELL *cell;

    on = 0;
    for (i = 0; i < grid->rows_3; i++)
    {
        switch (i)
        {
            case 0:
                on = wp->u_C.b.byte_C & 1;
                break;
            case 1:
                on = ((uint8)wp->u_C.b.byte_C >> 1) & 1;
                break;
            case 2:
                on = ((uint8)wp->u_C.b.byte_C >> 2) & 1;
                break;
            case 3:
                on = ((uint8)wp->u_C.b.byte_C >> 3) & 1;
                break;
            case 4:
                on = ((uint8)wp->u_C.b.byte_C >> 4) & 1;
                break;
            case 5:
                on = ((uint8)wp->u_C.b.byte_C >> 5) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_801022BC(grid, i, j);
            }
            if (grid->count_4[i] < 0x40)
            {
                grid->count_4[i]++;
            }
        }
        else if (grid->count_4[i] >= 8)
        {
            grid->count_4[i] = 7;
            for (j = 0; j < 8; j++)
            {
                cell          = &grid->cell_14[i][j];
                cell->state_4 = 0;
                cell->shade_5 = 0;
                cell->frame_6 = 0;
            }
        }
    }
}

void func_801021F4(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 6; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_801022BC(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
    grid->frame_C++;
}

void func_801022BC(ST17_GRID6 *grid, uint8 row, uint8 col)
{
    ST17_CELL *cell;

    cell = &grid->cell_14[row][col];
    D_8011AF24[grid->mode_0](grid, cell);
    if ((grid->mask_1 >> row) & 1)
    {
        D_8011AF38[grid->kind_B](cell, grid->value_10);
    }
}

void func_80102368(ST17_GRID6 *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0x40 - ((r >> 2) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 4) & 0x1F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 6) & 0x1F);
    }
    else
    {
        cell->shade_5 += 2;
        cell->frame_6--;
        cell->size_8 += 2;
        cell->y_C -= 8 + (r & 7);
        cell->z_E += 0x10 + ((r >> 2) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80102470(ST17_GRID6 *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0xC4 - ((r >> 1) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 2) & 0x3F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 4) & 0x3F);
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A -= 0xC + (r & 7);
        cell->y_C -= 0xC + ((r >> 2) & 7);
        cell->z_E += 0x10 + ((r >> 4) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80102598(ST17_GRID6 *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0xC4 - ((r >> 2) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x + ((r >> 4) & 0x3F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 6) & 0x3F);
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A += 0xC + (r & 7);
        cell->y_C -= 0xC + ((r >> 2) & 7);
        cell->z_E += 0x10 + ((r >> 4) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801026C0(ST17_GRID6 *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0x40 - ((r >> 2) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 4) & 0x1F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 6) & 0x1F);
    }
    else
    {
        cell->shade_5 += 2;
        cell->frame_6--;
        cell->size_8 += 2;
        cell->y_C -= 8 + (r & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801027B0(ST17_GRID6 *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 3);
        cell->size_8  = 7 - ((r >> 2) & 1);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 4) & 3);
        cell->y_C     = cell->origin_0->y - ((r >> 6) & 3);
        cell->z_E     = cell->origin_0->z - ((r >> 8) & 3);
    }
    else if (cell->state_4 == 1)
    {
        cell->shade_5 += 1;
        cell->frame_6 -= 1;
        cell->y_C -= 1;
        if (cell->frame_6 == 0)
        {
            if (grid->frame_C > 0x12C)
            {
                cell->state_4 = 2;
            }
            else
            {
                cell->state_4 = 0;
            }
        }
    }
}

void func_801028D0(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;

    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = 0x3D480040;
    p->uv_14   = 0x4E005F;
    p->uv_1C   = 0x1F40;
    p->uv_24   = 0x1F5F;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_80102974(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011AF44[cell->frame_6 >> 2];
    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = u | 0x3D480000;
    p->uv_14   = (u + 0x1F) | 0x4E0000;
    p->uv_1C   = u | 0x1F00;
    p->uv_24   = (u + 0x1F) | 0x1F00;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_80102A44(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_8011AF44[cell->frame_6 >> 2];
        p          = Billboard_get();
        p->code_4  = color - cell->shade_5 * 0x10101;
        p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
        p->z_10    = cell->z_E;
        p->uv_C    = u | 0x3D480000;
        p->uv_14   = (u + 0x1F) | 0x2E0000;
        p->uv_1C   = u | 0x1F00;
        p->uv_24   = (u + 0x1F) | 0x1F00;
        p->size_18 = cell->size_8;
        p->pad_20  = 8;
    }
}

void func_80102B28(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene                   = &Scene_work;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            wp->variant_3 = 1;
            wp->flags_0 |= 2;
            Model_work_init(wp, &wp->variant_3);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            wp->anim_AC        = 0;
            wp->rotation.z     = -0x13F;
            wp->routine_0++;
            break;
        case 1:
            if (ST17_SCENE_BYTE(scene, 7) == 1)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->rotation.z += 0x3F;
            if (ST17_SCENE_BYTE(scene, 7) == 2)
            {
                wp->routine_0++;
            }
            break;
        case 3:
            wp->rotation.z = 0x1F4;
            if (ST17_SCENE_BYTE(scene, 7) == 3)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            wp->rotation.z -= 0xAB;
            if (ST17_SCENE_BYTE(scene, 7) == 4)
            {
                wp->routine_0++;
            }
            break;
        case 5:
            wp->variant_3 = 0;
            Model_work_init(wp, &wp->variant_3);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->value_78       = 0;
            wp->anim_AC        = 0;
            wp->anim_prev_AD   = 0xFF;
            wp->routine_0++;
            // fall through
        case 6:
            wp->rotation.z -= 0xAB;
            break;
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    Model_parts_mtx_set_yxz(wp);
}

void func_80102D3C(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            wp->variant_3 = 1;
            wp->flags_0 |= 2;
            Model_work_init(wp, &wp->variant_3);
            wp->scale.words[0] = 0x2000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            wp->anim_AC        = 0;
            wp->u_C.b.byte_C   = 0;
            wp->u_C.b.byte_D   = 1;
            wp->u_E.b.byte_E   = 0x38;
            wp->u_E.b.byte_F   = 0;
            wp->routine_0++;
            // fall through
        case 1:
            wp->rotation.z = D_8011AF58[wp->u_E.b.byte_E] - 0x222;
            wp->u_E.b.byte_E++;
            if (wp->u_E.b.byte_F < 2)
            {
                if (wp->u_E.b.byte_E == 0x44)
                {
                    wp->u_E.b.byte_E = 0;
                    wp->u_E.b.byte_F++;
                }
            }
            else if (wp->u_E.b.byte_E == 0x67)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_AC      = 8;
            wp->u_C.b.byte_C = 0;
            wp->u_C.b.byte_D = 0;
            wp->routine_0++;
            break;
        case 3:
            if (wp->value_A4 == 8)
            {
                wp->variant_3 = 0;
                Model_work_init(wp, &wp->variant_3);
                wp->scale.words[0] = 0x2000200;
                wp->scale.words[1] = 0x200;
                wp->scale.v.pad    = 0x4210;
                wp->value_78       = 0;
                wp->anim_AC        = 8;
                wp->anim_prev_AD   = 0xFF;
                wp->u_C.b.byte_C   = 8;
                wp->routine_0++;
            }
            break;
        case 4:
            break;
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        if (wp->u_C.b.byte_D == 0)
        {
            func_800322A8(wp, wp->anim_AC, wp->u_C.b.byte_C);
            return;
        }
        func_80032304(wp, wp->anim_AC, wp->u_C.b.byte_C);
    }
    else
    {
        if (wp->u_C.b.byte_D == 0)
        {
            func_80032488(wp);
            return;
        }
        func_80032538(wp);
    }
    Model_parts_mtx_set_yxz(wp);
}

void func_80102FD8(STAGE_OBJ *wp)
{
    D_8011B028[wp->routine_1](wp);
}

void func_80103014(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->flags_0        = (uint8)wp->flags_0 | 2;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    wp->routine_1++;
}

void func_80103084(STAGE_OBJ *wp)
{
    switch (Scene_work.value_10)
    {
        case 0x14:
        case 0x50:
            func_800322A8(wp, 2, 0);
            break;
        case 0x64:
            func_800322A8(wp, 3, 0);
            break;
    }
    func_80032488(wp);
}

void func_80103108(STAGE_OBJ *wp)
{
    ST17_PART28 *part;
    sint16 index;
    sint32 flag;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    part                    = (ST17_PART28 *)&wp->owner_308;
    part->random_6          = rand();
    D_8011B030[wp->routine_0](wp, part);
    if (wp->anim_AC == 0)
    {
        if (wp->value_44.half[0] == 0)
        {
            if (part->value_C == -1)
            {
                if (wp->rotation.z != 0)
                {
                    if (wp->rotation.z > 0)
                    {
                        wp->rotation.z -= 8;
                    }
                    else
                    {
                        wp->rotation.z += 8;
                    }
                }
                if (wp->rotation.z == 0)
                {
                    if (!(wp->u_C.b.byte_D & 1))
                    {
                        part->value_C = (part->random_6 >> 4) & 3;
                    }
                    else
                    {
                        part->value_C = ((part->random_6 >> 6) & 3) + 0x12;
                    }
                }
            }
            else
            {
                index          = part->value_C % 36;
                wp->rotation.z = D_8011B060[index];
                part->value_C  = (part->value_C + 1) & 0x7FFF;
            }
        }
        else
        {
            if (wp->value_44.half[0] < 0)
            {
                if (wp->rotation.z >= -0x5F)
                {
                    wp->rotation.z -= 8;
                }
            }
            else if (wp->rotation.z < 0x60)
            {
                wp->rotation.z += 8;
            }
            part->value_C = -1;
        }
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        Model_parts_mtx_set_yxz(wp);
    }
    else if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    flag = (part->flags_4 << 3) & 0x80;
    func_800341BC(ST17_JOINT(wp), 0xDC, 0, 0x8000, wp->value_1, &part->hit_28, part->value_8 | 0x5880000, 0x800000, flag);
    part->hit_28.value_0 = 0;
}

void func_801033E4(STAGE_OBJ *wp, ST17_PART28 *part)
{
    sint16 life;

    part->flags_4  = 0;
    part->timer_E  = 0;
    part->value_10 = 0;
    part->timer_A  = 0;
    part->value_C  = -1;
    part->value_8  = D_80098844[wp->kind_2]->value_A;
    part->vx_12 = part->vy_14 = part->vz_16 = part->value_18 = 0;
    part->value_1A                                           = 0;
    part->value_1C                                           = 0;
    part->value_1E                                           = 0;
    part->value_20 = part->value_22 = part->value_24 = 0;
    part->hit_28.value_0                             = 0;
    part->hit_28.value_4                             = 0;
    Track_set(part->track_30, 0, 0);
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]      = 0x02000200;
    wp->scale.words[1]      = 0x42100200;
    wp->anim_prev_AD        = 0xFF;
    ST17_OBJ_WORD(wp, 0x64) = 0;
    wp->anim_AC             = 0;
    wp->value_48.half[0]    = 0;
    wp->value_44.half[1]    = 0;
    wp->value_44.half[0]    = 0;
    life                    = D_80098844[wp->kind_2]->life_C * 16;
    wp->value_78            = (sint32)D_8011B054;
    wp->routine_0           = 1;
    wp->routine_1           = 0;
    wp->routine_2           = 0;
    wp->routine_3           = 0;
    wp->life_6E             = life;
    wp->life_max_B0         = life;
    wp->life_prev_B2        = life;
}

void func_80103520(STAGE_OBJ *wp, ST17_PART28 *part)
{
    uint16 flags;

    if (part->flags_4 & 2)
    {
        func_8010483C(wp, part);
    }
    switch (wp->anim_AC)
    {
        case 0:
            if (part->flags_4 & 0x20)
            {
                wp->anim_AC = 2;
            }
            else if (part->flags_4 & 4)
            {
                wp->anim_AC = 1;
            }
            break;
        case 1:
            flags = part->flags_4;
            if (flags & 0x10)
            {
                part->flags_4 = flags & ~4;
                wp->anim_AC   = 0;
            }
            else if (flags & 0x20)
            {
                wp->anim_AC = 2;
            }
            else if (wp->value_A7 == -1)
            {
                if (flags & 4)
                {
                    wp->anim_AC      = 1;
                    wp->anim_prev_AD = 0xFF;
                }
                else
                {
                    wp->anim_AC = 0;
                }
            }
            break;
        case 2:
            if (wp->value_A7 == -1)
            {
                wp->anim_AC = 3;
            }
            break;
    }
    D_8011B03C[wp->routine_1](wp, part);
    if (part->flags_4 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1 = 1;
                break;
            case 1:
                wp->routine_0 = 2;
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        part->flags_4 &= ~1;
    }
}

// The second argument is the work slot's +0x308, which starts with the owner's pointer.
void func_801036B4(STAGE_OBJ *wp, STAGE_OBJ **owner)
{
    (*owner)->u_C.b.byte_C |= 1 << wp->u_C.b.byte_C;
    func_80031824(wp);
}

void func_801036EC(STAGE_OBJ *wp, ST17_PART28 *part)
{
    func_8003648C(part->track_30, wp);
    D_8011B044[wp->routine_2](wp, part);
    if (wp->anim_AC == 1)
    {
        part->flags_4 &= ~8;
    }
    if (part->flags_4 & 8)
    {
        if (!(part->timer_A & 3))
        {
            func_80104900(wp, part);
        }
        part->timer_A++;
    }
    else
    {
        part->timer_A = 0;
    }
}

void func_801037B4(STAGE_OBJ *wp, ST17_PART28 *part)
{
    ST17_MARK *ep;

    switch (wp->routine_2)
    {
        case 0:
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 5;
                ep->kind_2    = 0x80;
                ep->variant_3 = 0x41;
                ep->pos_38    = wp->position;
            }
            part->timer_E = 0;
            if (wp->position.z < 0x400)
            {
                wp->value_44.half[1] = 0;
                if (wp->position.x < 0)
                {
                    wp->value_44.half[0] = -0x100;
                }
                else
                {
                    wp->value_44.half[0] = 0x100;
                }
                wp->value_48.half[0] = -0x80;
                wp->value_44.half[1] = 0;
                wp->routine_2        = 1;
            }
            else
            {
                part->flags_4 |= 0x20;
                wp->value_44.half[1] = 0x80;
                wp->value_48.half[0] = -0x200;
                wp->value_44.half[0] = 0;
                wp->routine_2        = 2;
            }
            break;
        case 1:
            Obj_pos_set(wp, wp->value_48.half[0], 0, wp->value_44.half[0]);
            if (STCOM_ABS(wp->position.x) > 0x600 || wp->position.z >= 0x400)
            {
                ep = func_80031618();
                if (ep != NULL)
                {
                    ep->flags_0   = 5;
                    ep->kind_2    = 0x80;
                    ep->variant_3 = 0x41;
                    ep->pos_38    = wp->position;
                }
                part->flags_4 |= 0x20;
                wp->value_44.half[1] = 0x80;
                wp->value_48.half[0] = -0x200;
                wp->value_44.half[0] = 0;
                wp->routine_2        = 2;
            }
            break;
        case 2:
            wp->value_44.half[1] += 4;
            if (part->timer_E == 0x3C)
            {
                wp->value_48.half[0] = -0x400;
            }
            part->timer_E++;
            Obj_pos_set(wp, wp->value_48.half[0], wp->value_44.half[1], 0);
            if (wp->position.y >= -0x7F)
            {
                part->flags_4 |= 1;
            }
            break;
    }
}

void func_801039E0(STAGE_OBJ *wp, ST17_PART28 *part)
{
    if (wp->routine_3 != 0 && wp->routine_3 < 6 && part->owner_0->u_E.b.byte_E > 0)
    {
        wp->routine_3 = 6;
    }
    switch (wp->routine_3)
    {
        case 0:
            wp->value_44.half[0] = 0;
            part->timer_E        = 0;
            part->value_10       = 0;
            wp->routine_3++;
            // fall through
        case 1:
            if (part->owner_0->routine_1 == 2)
            {
                wp->routine_3++;
            }
            break;
        case 2:
            wp->position.z -= 0x80;
            if (++part->timer_E == 0x60)
            {
                wp->position.y = 0;
                switch (wp->u_C.b.byte_C)
                {
                    case 1:
                        wp->position.z = 0xA00;
                        break;
                    case 0:
                        wp->position.z = 0x800;
                        break;
                    case 2:
                        wp->position.z = 0xA00;
                        break;
                    case 3:
                    case 4:
                        wp->position.z = 0xC00;
                        break;
                }
                if (wp->u_C.b.byte_C == 0)
                {
                    part->timer_E  = 0;
                    part->value_10 = 0x10;
                }
                else if (wp->u_C.b.byte_C == 1 || wp->u_C.b.byte_C == 2)
                {
                    part->timer_E  = 8;
                    part->value_10 = 8;
                }
                else
                {
                    part->timer_E  = 0x10;
                    part->value_10 = 0;
                }
                wp->routine_3++;
            }
            break;
        case 3:
            if (part->timer_E != 0)
            {
                part->timer_E--;
            }
            else
            {
                wp->routine_3++;
            }
            break;
        case 4:
            wp->position.y -= 0x10;
            if (wp->position.y < -0x7FF)
            {
                wp->position.y = -0x800;
                wp->routine_3++;
            }
            else if (wp->value_44.half[1] >= 3)
            {
                wp->value_44.half[1]--;
            }
            break;
        case 5:
            if (part->value_10 == 0)
            {
                wp->routine_3 = 8;
            }
            else
            {
                part->value_10--;
            }
            break;
        case 6:
            if (part->owner_0->u_E.b.byte_E == 2)
            {
                wp->routine_3++;
            }
            break;
        case 7:
            wp->position.y = 0;
            switch (wp->u_C.b.byte_C)
            {
                case 1:
                    wp->position.z = 0xA00;
                    break;
                case 0:
                    wp->position.z = 0x800;
                    break;
                case 2:
                    wp->position.z = 0xA00;
                    break;
                case 3:
                case 4:
                    wp->position.z = 0xC00;
                    break;
            }
            wp->position.y = -0x800;
            wp->routine_3++;
            break;
        case 8:
            if (part->owner_0->routine_1 == 3)
            {
                part->timer_E        = 0x80;
                wp->value_44.half[1] = 4;
                switch (wp->u_C.b.byte_C)
                {
                    case 0:
                        wp->value_44.half[0] = 0;
                        wp->value_48.half[0] = 0;
                        break;
                    case 1:
                        wp->value_44.half[0] = 4;
                        wp->value_48.half[0] = 0;
                        break;
                    case 2:
                        wp->value_44.half[0] = -4;
                        wp->value_48.half[0] = 4;
                        break;
                    case 3:
                        wp->value_44.half[0] = 8;
                        wp->value_48.half[0] = 4;
                        break;
                    case 4:
                        wp->value_44.half[0] = -8;
                        wp->value_48.half[0] = 8;
                        break;
                }
                wp->routine_3++;
            }
            break;
        case 9:
            if (part->timer_E == 0)
            {
                wp->value_44.half[0] = 0;
                wp->value_48.half[0] = 0;
                wp->value_44.half[1] = 0;
                wp->routine_3++;
            }
            else
            {
                wp->position.x += wp->value_44.half[0];
                wp->position.y += wp->value_44.half[1];
                wp->position.z += wp->value_48.half[0];
                part->timer_E--;
            }
            break;
        case 10:
            part->flags_4 |= 2;
            wp->value_48.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_44.half[0] = 0;
            part->vz_16          = 0;
            part->vy_14          = 0;
            part->vx_12          = 0;
            part->timer_E        = 0;
            part->value_10       = wp->u_C.b.byte_C * 64;
            wp->routine_3++;
            break;
        case 11:
            if (part->value_10 == 0)
            {
                Sound_call2(0x1A0, &wp->position);
                wp->value_48.half[0] = 0;
                part->value_1C       = part->random_6 & 0xF00;
                wp->routine_3        = 0;
                wp->routine_2++;
            }
            else
            {
                wp->value_48.half[0] = -8;
                part->value_10--;
            }
            wp->position.z += wp->value_48.half[0];
            break;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

// func_8010421C has two jump tables, so retail starts them 8-aligned.
ST17_RODATA_PAD(pad_8010421C)

void func_80103E6C(STAGE_OBJ *wp, ST17_PART28 *part)
{
    sint16 dir;

    switch (wp->routine_3)
    {
        case 0:
            part->timer_E  = 0;
            part->value_10 = 0;
            part->value_1A = 0;
            part->vz_16    = 0;
            part->value_18 = 0;
            if (part->random_6 & 1)
            {
                part->value_1E = (part->random_6 >> 2) & 7;
            }
            else
            {
                part->value_1E = -((part->random_6 >> 4) & 7);
            }
            wp->routine_3++;
            // fall through
        case 1:
            if (part->timer_E < 0x140)
            {
                switch (part->timer_E)
                {
                    case 0:
                        part->vz_16    = -1;
                        part->value_18 = 0x14;
                        break;
                    case 0x20:
                        part->vz_16 = 0;
                        break;
                    case 0x40:
                        part->value_18 = 0;
                        break;
                    case 0x60:
                        part->value_18 = -0x14;
                        break;
                    case 0x80:
                        part->vz_16 = 1;
                        break;
                    case 0xA0:
                        part->flags_4 |= 0x40;
                        break;
                    case 0xC0:
                        part->vz_16 = 0;
                        break;
                    case 0xE0:
                        part->value_18 = 0;
                        break;
                    case 0x100:
                        part->value_18 = 0x14;
                        break;
                    case 0x120:
                        part->vz_16 = -1;
                        break;
                }
                part->value_1C += part->value_1E;
                part->timer_E++;
            }
            else
            {
                part->vz_16    = 0;
                part->value_18 = 0;
                part->flags_4 |= 0x40;
                if (wp->u_E.b.byte_E < 3 && wp->u_E.b.byte_F != 0)
                {
                    wp->routine_2++;
                }
                wp->routine_3 = 0;
            }
            break;
    }
    wp->value_48.half[0] += part->vz_16;
    wp->position.z += wp->value_48.half[0];
    part->value_1A += part->value_18;
    wp->position.x = (part->value_1A * rsin(part->value_1C)) >> 12;
    wp->position.y = ((part->value_1A * rcos(part->value_1C)) >> 12) - 0x600;
    dir            = -1;
    if (wp->position_prev.x < wp->position.x)
    {
        dir = 1;
    }
    wp->value_44.half[0] = dir;
    if (part->flags_4 & 0x40)
    {
        if (part->timer_E == 0xA1)
        {
            wp->position.y = -0x600;
            wp->position.x = 0;
            wp->position.z = -0x800;
        }
        else
        {
            wp->position.y = -0x600;
            wp->position.x = 0;
            wp->position.z = 0x800;
        }
        part->flags_4 &= ~0x40;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (wp->position.z < 0x300)
    {
        part->flags_4 &= ~8;
    }
    else if ((part->random_6 & 1) && wp->position.y < -0x600)
    {
        part->flags_4 |= 8;
    }
    if (ST17_DIST(wp) < 0x90000)
    {
        if (!(part->flags_4 & 0x80))
        {
            part->flags_4 |= 0x80;
            Sound_call2(0x150, &wp->position);
        }
    }
    if (ST17_DIST(wp) > 0x240000)
    {
        part->flags_4 &= ~0x80;
    }
}

void func_8010421C(STAGE_OBJ *wp, ST17_PART28 *part)
{
    switch (wp->routine_3)
    {
        case 0:
            part->value_10 = 0;
            part->timer_E  = 0;
            part->flags_4 &= ~8;
            wp->value_48.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_44.half[0] = 0;
            wp->routine_3++;
            // fall through
        case 1:
            if (part->timer_E < 0x40)
            {
                switch (part->timer_E)
                {
                    case 0:
                        part->vx_12 = (wp->u_C.b.byte_D == 0) ? -1 : 1;
                        part->vy_14 = -1;
                        part->vz_16 = 2;
                        break;
                    case 0xC:
                        part->vz_16 = 0;
                        break;
                    case 0x10:
                        part->vx_12 = 0;
                        part->vy_14 = 0;
                        break;
                    case 0x20:
                        part->vy_14 = 1;
                        break;
                    case 0x30:
                        part->vx_12 = (wp->u_C.b.byte_D == 0) ? 1 : -1;
                        part->vy_14 = 0;
                        break;
                    case 0x34:
                        part->vz_16 = -2;
                        break;
                }
                part->timer_E++;
            }
            else
            {
                part->vx_12 = 0;
                part->vy_14 = 0;
                part->vz_16 = 0;
                part->owner_0->u_E.b.byte_F--;
                wp->routine_3++;
            }
            break;
        case 2:
            if (part->owner_0->u_E.b.byte_F <= 0)
            {
                part->timer_E = 0;
                wp->routine_3++;
            }
            break;
        case 3:
            if (part->timer_E < 0x28)
            {
                switch (part->timer_E)
                {
                    case 0:
                        part->vy_14 = (wp->u_C.b.byte_D == 0) ? 1 : -1;
                        break;
                    case 8:
                        part->vy_14 = 0;
                        break;
                    case 0x20:
                        part->vy_14 = (wp->u_C.b.byte_D == 0) ? -1 : 1;
                        break;
                }
                part->timer_E++;
            }
            else
            {
                part->vy_14 = 0;
                wp->routine_3++;
            }
            break;
        case 4:
            wp->routine_3 = 0;
            wp->routine_2++;
            break;
    }
    wp->value_44.half[0] += part->vx_12;
    wp->value_44.half[1] += part->vy_14;
    wp->value_48.half[0] += part->vz_16;
    wp->position.x += wp->value_44.half[0];
    wp->position.z += wp->value_48.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position_fixed.v.z = wp->position.z << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.x = wp->position.x << 16;
}

void func_80104498(STAGE_OBJ *wp, ST17_PART28 *part)
{
    switch (wp->routine_3)
    {
        case 0:
            part->timer_E = 0;
            part->vx_12   = 0;
            part->vy_14   = 0;
            part->vz_16   = 0;
            if (wp->position.x < 0)
            {
                part->value_20 = 0x300;
                part->value_22 = wp->position.y - 0x200;
            }
            else
            {
                part->value_20 = -0x300;
                part->value_22 = wp->position.y + 0x200;
            }
            part->value_24 = wp->position.z;
            part->value_1A = part->random_6 & 1;
            wp->routine_3++;
            // fall through
        case 1:
            if (part->value_1A == 0)
            {
                func_80104BBC(wp, part);
            }
            else
            {
                func_80104D78(wp, part);
            }
            break;
        case 2:
            if (part->timer_E < 0x50)
            {
                switch (part->timer_E)
                {
                    case 0:
                        if (wp->position.x < 0)
                        {
                            part->vx_12    = 1;
                            part->vy_14    = 0;
                            part->value_20 = 0x300;
                            part->value_22 = wp->position.y - 0x200;
                        }
                        else
                        {
                            part->vx_12    = -1;
                            part->vy_14    = 0;
                            part->value_20 = -0x300;
                            part->value_22 = wp->position.y + 0x200;
                        }
                        part->value_24 = wp->position.z;
                        break;
                    case 8:
                        part->flags_4 |= 8;
                        break;
                    case 0x20:
                        part->vx_12 = 0;
                        if (wp->position.x < 0)
                        {
                            part->vy_14 = -1;
                        }
                        else
                        {
                            part->vy_14 = 1;
                        }
                        break;
                    case 0x30:
                        if (wp->position.x < 0)
                        {
                            part->vx_12 = 1;
                        }
                        else
                        {
                            part->vx_12 = -1;
                        }
                        part->vy_14 = 0;
                        break;
                    case 0x40:
                        if (wp->position.x < 0)
                        {
                            part->vy_14 = -1;
                        }
                        else
                        {
                            part->vy_14 = 1;
                        }
                        break;
                    case 0x48:
                        part->flags_4 &= ~8;
                        break;
                }
                part->timer_E++;
            }
            else
            {
                part->vx_12   = 0;
                part->vy_14   = 0;
                part->vz_16   = 0;
                part->timer_E = 0;
                part->flags_4 |= 0x40;
                wp->routine_3 = 0;
            }
            break;
    }
    wp->value_44.half[0] += part->vx_12;
    wp->value_44.half[1] += part->vy_14;
    wp->value_48.half[0] += part->vz_16;
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (part->flags_4 & 0x40)
    {
        wp->position.x = part->value_20;
        wp->position.y = part->value_22;
        wp->position.z = part->value_24;
        part->flags_4 &= ~0x40;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (ST17_DIST(wp) < 0x90000)
    {
        if (!(part->flags_4 & 0x80))
        {
            part->flags_4 |= 0x80;
            Sound_call2(0x150, &wp->position);
        }
    }
    if (ST17_DIST(wp) > 0x240000)
    {
        part->flags_4 &= ~0x80;
    }
}

void func_8010483C(STAGE_OBJ *wp, ST17_PART28 *part)
{
    uint32 hit;
    sint32 damage;

    hit    = part->hit_28.value_0;
    damage = hit & 0xFFFFFF;
    if (damage != 0)
    {
        if (hit & 0x18000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                part->flags_4 = (part->flags_4 & ~0xA) | 0x11;
            }
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
        part->flags_4 |= 4;
    }
    else
    {
        part->flags_4 &= ~4;
    }
}

void func_80104900(STAGE_OBJ *wp, ST17_PART28 *part)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR v;
    STCOM_FIXED_VECTOR offset;
    ST17_SHOT *shot;
    sint32 spawned;

    spawned = 0;
    func_80030058(&fixed, wp->rotation.y, 0x600, 0, 0);
    func_80030150(&fixed, &v);
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0 = 3;
        shot->kind_2  = 1;
        shot->value_4 = 0;
        shot->value_F = 0x34;
        func_80030058(&offset, wp->rotation.y, 0xC80, 0xD00, 0x440);
        shot->position_fixed.v = offset;
        shot->position_fixed.v.x += wp->position_fixed.v.x;
        shot->position_fixed.v.y += wp->position_fixed.v.y;
        shot->position_fixed.v.z += wp->position_fixed.v.z;
        func_80030150(&shot->position_fixed.v, &shot->position);
        spawned                = 1;
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = 0;
        shot->value_48.half[0] = v.z << 8;
        shot->value_48.half[1] = 0;
        shot->value_50         = 0;
        shot->value_4C.half[1] = 0;
        shot->value_4C.half[0] = 0;
        func_80104B34((STAGE_XYZ *)&shot->position);
    }
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0 = 3;
        shot->kind_2  = 1;
        shot->value_4 = 0;
        shot->value_F = 0x34;
        func_80030058(&offset, wp->rotation.y, 0xC80, 0xD00, -0x440);
        shot->position_fixed.v = offset;
        shot->position_fixed.v.x += wp->position_fixed.v.x;
        shot->position_fixed.v.y += wp->position_fixed.v.y;
        shot->position_fixed.v.z += wp->position_fixed.v.z;
        func_80030150(&shot->position_fixed.v, &shot->position);
        spawned                = 1;
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = 0;
        shot->value_48.half[0] = v.z << 8;
        shot->value_48.half[1] = 0;
        shot->value_50         = 0;
        shot->value_4C.half[1] = 0;
        shot->value_4C.half[0] = 0;
        func_80104B34((STAGE_XYZ *)&shot->position);
    }
    if (spawned)
    {
        Sound_call2(0xD0, &shot->position);
    }
}

void func_80104B34(STAGE_XYZ *pos)
{
    STCOM23_PACKET *p;

    p          = Billboard_get();
    p->code_4  = 0x2C808080;
    p->xy_8    = (uint16)pos->x | (pos->y << 16);
    p->z_10    = pos->z;
    p->uv_1C   = 0x5FC0;
    p->uv_24   = 0x5FDF;
    p->size_18 = 0x40;
    p->uv_C    = 0x3D0840C0;
    p->uv_14   = 0xE40DF;
    p->pad_20  = 8;
}

void func_80104BBC(STAGE_OBJ *wp, ST17_PART28 *part)
{
    if (part->timer_E < 0x8A)
    {
        switch (part->timer_E)
        {
            case 0:
                part->vx_12 = 0;
                part->vy_14 = 0;
                part->vz_16 = -4;
                break;
            case 0x15:
                part->vz_16 = 0;
                break;
            case 0x30:
                part->vz_16 = 4;
                part->flags_4 |= 8;
                break;
            case 0x5A:
                part->vz_16 = 0;
                part->flags_4 &= ~8;
                part->vy_14 = (wp->position.x < 0) ? 1 : -1;
                break;
            case 0x75:
                part->vz_16 = -4;
                break;
            case 0x31:
                part->vx_12 = (wp->position.x < 0) ? 4 : -4;
                break;
            case 0x49:
                part->vx_12 = (wp->position.x > 0) ? -4 : 4;
                break;
            case 0x41:
            case 0x59:
                part->vx_12 = 0;
                break;
            case 0x6A:
                part->vy_14 = 0;
                break;
            case 0x7A:
                part->vy_14 = (wp->position.x < 0) ? -1 : 1;
                break;
        }
        part->timer_E++;
    }
    else
    {
        part->vx_12   = 0;
        part->vy_14   = 0;
        part->vz_16   = 0;
        part->timer_E = 0;
        part->flags_4 |= 0x40;
        wp->routine_3++;
    }
}

void func_80104D78(STAGE_OBJ *wp, ST17_PART28 *part)
{
    if (part->timer_E < 0x8A)
    {
        switch (part->timer_E)
        {
            case 0:
                part->vx_12 = 0;
                part->vy_14 = 0;
                part->vz_16 = -3;
                break;
            case 0x20:
                part->vz_16 = 0;
                break;
            case 0x25:
                part->vz_16 = 3;
                part->flags_4 |= 8;
                break;
            case 0x65:
                part->vz_16 = 0;
                part->flags_4 &= ~8;
                break;
            case 0x6A:
                part->vy_14 = 0;
                part->vz_16 = -3;
                break;
            case 0x31:
                part->vx_12 = (wp->position.x < 0) ? 4 : -4;
                break;
            case 0x49:
                part->vx_12 = (wp->position.x > 0) ? -4 : 4;
                break;
            case 0x41:
            case 0x59:
                part->vx_12 = 0;
                break;
            case 0x5A:
                part->vy_14 = (wp->position.x < 0) ? 1 : -1;
                break;
            case 0x7A:
                part->vy_14 = (wp->position.x < 0) ? -1 : 1;
                break;
        }
        part->timer_E++;
    }
    else
    {
        part->vx_12   = 0;
        part->vy_14   = 0;
        part->vz_16   = 0;
        part->timer_E = 0;
        part->flags_4 |= 0x40;
        wp->routine_3++;
    }
}

void func_80104F38(STAGE_OBJ *wp)
{
    D_8011B0A8[wp->routine_1](wp);
    if (wp->u_C.b.byte_C != 0)
    {
        func_80032488(wp);
    }
}

void func_80104F98(STAGE_OBJ *wp)
{
    STCOM_EFFECT *fx;
    uint8 i;
    uint8 j;

    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_C   = 0;
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 2; j++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0   = 1;
                    fx->kind_2    = 0x1A;
                    fx->variant_3 = 0;
                    fx->value_C   = wp->value_1;
                    fx->value_D   = i + 1;
                }
            }
        }
    }
    if (Scene_work.value_10 == 0xF)
    {
        wp->u_C.b.byte_C++;
    }
}

void func_801050C8(STAGE_OBJ *wp)
{
    sint8 step;
    uint8 anim;
    sint16 z;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 0x42;
        Model_work_init(wp, NULL);
        wp->scale.words[0]   = 0x0C000C00;
        wp->scale.words[1]   = 0xC00;
        wp->scale.v.pad      = 0x4210;
        wp->value_78         = 0;
        wp->anim_AC          = 0;
        wp->anim_prev_AD     = 0xFF;
        wp->value_48.half[0] = 0;
        wp->routine_1        = 0;
        wp->routine_0++;
    }
    step = wp->u_C.b.byte_C;
    if (step < 5)
    {
        if (wp->position.z > step * 0x3B0 + 0x1E00)
        {
            wp->value_48.half[0] = -((5 - step) * 4);
        }
        else if (wp->value_48.half[0] < 0)
        {
            wp->value_48.half[0] += 8;
            if (wp->value_48.half[0] > 0)
            {
                wp->value_48.half[0] = 0;
            }
        }
    }
    z                      = wp->position.z + wp->value_48.half[0];
    wp->position.z         = z;
    wp->position_fixed.v.z = z << 16;
    anim                   = wp->anim_AC;
    if (anim != wp->anim_prev_AD)
    {
        func_800322A8(wp, anim, 0);
        return;
    }
    func_80032488(wp);
}

void func_8010526C(ST17_SPARK *wp)
{
    ST17_SPARK *owner;

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

void func_801052F8(ST17_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_8010526C(wp);
}

void func_8010532C(STAGE_FX *wp)
{
    func_80031988(wp);
}

void func_8010534C(ST17_SPARK *wp)
{
    D_8011B0AC[wp->routine_0](wp);
}

void func_80105388(ST17_SPARK *wp)
{
    ST17_SPARK *ep;
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
                func_8010534C(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_801054D0(ST17_SPARK *wp)
{
    if (wp->variant_3 == 1)
    {
        func_8010534C(wp);
    }
    else if (wp->routine_0 != 2)
    {
        func_80105388(wp);
    }
    else
    {
        func_80031988(wp);
    }
}

ST17_SPARK *func_80105530(STCOM_SVECTOR *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag)
{
    ST17_SPARK *ep;
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
            func_80105388(ep);
        }
    }
    return ep;
}

void func_80105638(STAGE_FX *wp)
{
    STCOM_SVECTOR v;
    ST17_PUFF *puff;
    STCOM23_PACKET *p;
    uint32 shade;
    sint32 u;
    sint32 i;

    switch (wp->routine_0)
    {
        case 0:
            wp->u_28.count = 0;
            wp->routine_0++;
            // fall through
        case 1:
            wp->u_28.count++;
            for (i = 0; i < 32; i++)
            {
                puff  = &D_8011B0B8[i];
                v.x   = (uint32)(puff->pos_0.x + puff->step_8.x * wp->u_28.count) >> 4;
                v.y   = ((uint32)(puff->pos_0.y + puff->step_8.y * wp->u_28.count) >> 4) - 0x1B1C;
                v.z   = (uint32)(puff->pos_0.z + puff->step_8.z * wp->u_28.count) >> 4;
                v.pad = (uint32)(puff->pos_0.pad + puff->step_8.pad * wp->u_28.count) >> 4;
                shade = (uint32)(puff->shade_10 + puff->fade_12 * wp->u_28.count) >> 4;
                if (shade < 0x80)
                {
                    p          = Billboard_get();
                    p->code_4  = 0x2E808080 - shade * 0x10101;
                    p->xy_8    = (uint16)v.x | (v.y << 16);
                    p->z_10    = v.z;
                    u          = ((puff->tile_14 << 5) + 0x20) & 0xFF;
                    p->pad_20  = 0;
                    p->uv_C    = u | 0x3D480000;
                    p->uv_14   = (u + 0x1F) | 0x4E0000;
                    p->uv_1C   = u | 0x1F00;
                    p->uv_24   = (u + 0x1F) | 0x1F00;
                    p->size_18 = v.pad;
                }
            }
            break;
    }
}

void func_80105830(ST17_PIECE *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;
    ST17_PIECE_DATA *data;
    uint16 frame;
    sint16 size;

    data = &D_8011B3B8[wp->index_C];
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 6;
            wp->variant_3 = data->variant_20;
            Model_work_init(wp, &wp->variant_3);
            wp->color_40 = 0x808080;
            wp->frame_E  = 0;
            wp->value_D  = 0;
            wp->routine_0++;
            // fall through
        case 1:
            frame        = ++wp->frame_E;
            wp->pos_38.x = (data->pos_0.x + data->step_8.x * frame) >> 4;
            wp->pos_38.y = ((data->pos_0.y + data->step_8.y * frame) >> 4) - 0x1B1C;
            wp->pos_38.z = (data->pos_0.z + data->step_8.z * frame) >> 4;
            rot.x        = data->rot_10.x + ((data->spin_18.x * frame) << 7);
            rot.y        = data->rot_10.y + ((data->spin_18.y * frame) << 7);
            rot.z        = data->rot_10.z + ((data->spin_18.z * frame) << 7);
            RotMatrixYXZ(&rot, &wp->matrix.m);
            size = (data->pos_0.pad + data->step_8.pad * frame) >> 4;
            if (size < 0)
            {
                size = 0;
            }
            scale.x = size;
            scale.y = size;
            scale.z = size;
            ScaleMatrix(&wp->matrix.m, &scale);
            break;
    }
}

void *func_80105A0C(STAGE_OBJ *wp, sint8 kind, STCOM_SVECTOR *rot)
{
    ST17_MODEL_SLOT *slot;
    ST17_MODEL_REC *model;
    ST17_JOINT_KEY *key;
    uint8 i;
    uint8 j;

    slot = func_80031498();
    if (slot == NULL)
    {
        return NULL;
    }
    slot->flags_0   = 1;
    slot->kind_2    = 3;
    slot->value_4   = 0;
    slot->variant_3 = kind;
    slot->value_C   = 0;
    slot->value_10  = 0;
    slot->flags_6 |= 0x20;
    model = &slot->model_88;
    switch (kind)
    {
        case 0:
            model->color_14 = 0x2E404040;
            model->id_0     = 0;
            model->value_E  = 1;
            model->count_2  = 9;
            break;
        case 1:
            model->color_14 = 0x2E404040;
            model->id_0     = 3;
            model->value_E  = 1;
            model->count_2  = 9;
            break;
        case 2:
            model->id_0     = 4;
            model->value_E  = 2;
            model->color_14 = 0x2E808080;
            model->count_2  = 9;
            break;
        case 3:
            model->id_0     = 5;
            model->color_14 = 0x2E808080;
            model->value_E  = 3;
            model->count_2  = 9;
            break;
        default:
            func_8003187C(slot);
            return NULL;
    }
    model->value_C  = 0x3FF;
    model->value_1  = wp->value_1;
    model->value_12 = 0;
    if (kind == 0)
    {
        for (i = 0; i < model->count_2; i++)
        {
            model->mode_3[i] = 7;
            for (j = 0; j < 8; j++)
            {
                key = &model->key_18[i][j];
                switch (i)
                {
                    case 0:
                        key->rot_0 = &rot[2];
                        break;
                    case 3:
                        key->rot_0 = &rot[14];
                        break;
                    case 6:
                        key->rot_0 = &rot[15];
                        break;
                    case 1:
                        key->rot_0 = &rot[0];
                        break;
                    case 4:
                        key->rot_0 = &rot[10];
                        break;
                    case 7:
                        key->rot_0 = &rot[12];
                        break;
                    case 2:
                        key->rot_0 = &rot[1];
                        break;
                    case 5:
                        key->rot_0 = &rot[11];
                        break;
                    case 8:
                        key->rot_0 = &rot[13];
                        break;
                }
                key->value_4 = 0;
                key->value_5 = 0;
                key->value_6 = 0;
            }
        }
    }
    else
    {
        for (i = 0; i < model->count_2; i++)
        {
            model->mode_3[i] = 7;
            for (j = 0; j < 8; j++)
            {
                key          = &model->key_18[i][j];
                key->rot_0   = rot;
                key->value_4 = 0;
                key->value_5 = 0;
                key->value_6 = 0;
            }
            rot++;
        }
    }
    return slot;
}

void func_80105CF8(STAGE_10C *wp, sint32 angle)
{
    wp->matrix_8C.m.m[1][1] = angle & 0x3FF;
}

void func_80105D04(STAGE_OBJ *wp)
{
    D_8011B4FC[wp->variant_3](wp, &wp->model_88);
}

void func_80105D40(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;

    on = 0;
    for (i = 0; i < 9; i++)
    {
        switch (i % 3)
        {
            case 0:
                on           = wp->u_C.b.byte_C & 1;
                grid->mode_0 = 0;
                break;
            case 1:
                on           = ((uint8)wp->u_C.b.byte_C >> 1) & 1;
                grid->mode_0 = 1;
                break;
            case 2:
                on           = ((uint8)wp->u_C.b.byte_C >> 2) & 1;
                grid->mode_0 = 2;
                break;
        }
        if (on)
        {
            n = grid->count_3[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_80106120(grid, i, j);
            }
            if (grid->count_3[i] < 0x40)
            {
                grid->count_3[i]++;
            }
        }
    }
    grid->frame_12++;
}

void func_80105EC8(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 9; i++)
    {
        n = grid->count_3[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80106120(grid, i, j);
        }
        if (grid->count_3[i] < 0x40)
        {
            grid->count_3[i]++;
        }
    }
    grid->frame_12++;
}

void func_80105F90(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 9; i++)
    {
        n = grid->count_3[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80106120(grid, i, j);
        }
        if (grid->count_3[i] < 0x40)
        {
            grid->count_3[i]++;
        }
    }
    grid->frame_12++;
}

void func_80106058(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 7; i++)
    {
        n = grid->count_3[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80106120(grid, i, j);
        }
        if (grid->count_3[i] < 0x40)
        {
            grid->count_3[i]++;
        }
    }
    grid->frame_12++;
}

void func_80106120(ST17_GRID *grid, uint8 row, uint8 col)
{
    ST17_CELL *cell;

    cell = &grid->cell_18[row][col];
    D_8011B50C[grid->mode_0](grid, cell);
    if ((grid->mask_C >> row) & 1)
    {
        D_8011B524[grid->kind_E](cell, grid->value_14);
    }
}

void func_801061CC(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x100 - ((r >> 2) & 7);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        if (cell->frame_6 > 0x34)
        {
            cell->y_C += 8 + ((r >> 4) & 3);
        }
        cell->z_E += 0x10 + ((r >> 6) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801062CC(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x100 - ((r >> 2) & 7);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A -= 0xC + (r & 7);
        cell->y_C -= 0xC + ((r >> 2) & 7);
        cell->z_E += 0x10 + ((r >> 4) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801063D8(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x100 - ((r >> 2) & 7);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A += 0xC + (r & 7);
        cell->y_C -= 0xC + ((r >> 2) & 7);
        cell->z_E += 0x10 + ((r >> 4) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801064E4(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0x12C - ((r >> 2) & 0x1F);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x + ((r >> 4) & 0xF);
        cell->y_C     = cell->origin_0->y - ((r >> 6) & 0x1F);
        cell->z_E     = cell->origin_0->z + ((r >> 8) & 0x1F);
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A += 0xA + ((r >> 2) & 7);
        cell->y_C -= 0xA + ((r >> 4) & 7);
        cell->z_E += 0x2A + ((r >> 6) & 0xF);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80106618(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0xC8 - ((r >> 2) & 0x1F);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y - ((r >> 6) & 0x1F);
        cell->z_E     = cell->origin_0->z - ((r >> 8) & 0x1F);
    }
    else if (cell->state_4 == 1)
    {
        cell->shade_5 += 2;
        cell->frame_6--;
        cell->size_8 += 2;
        cell->y_C -= 2 + ((r >> 4) & 7);
        cell->z_E += 0x18 + ((r >> 6) & 0xF);
        if (cell->frame_6 == 0)
        {
            if (grid->frame_12 > 0xB4)
            {
                cell->state_4 = 2;
            }
            else
            {
                cell->state_4 = 0;
            }
        }
    }
}

void func_80106760(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x50 - ((r >> 2) & 0x1F);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 2;
        cell->frame_6 -= 1;
        cell->size_8 += 4;
        cell->y_C -= 2 + ((r >> 4) & 7);
        cell->z_E += 0x18;
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80106848(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;

    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = 0x3D480040;
    p->uv_14   = 0x4E005F;
    p->uv_1C   = 0x1F40;
    p->uv_24   = 0x1F5F;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_801068EC(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011B534[cell->frame_6 >> 2];
    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = u | 0x3D480000;
    p->uv_14   = (u + 0x1F) | 0x4E0000;
    p->uv_1C   = u | 0x1F00;
    p->uv_24   = (u + 0x1F) | 0x1F00;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_801069BC(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_8011B534[cell->frame_6 >> 2];
        p          = Billboard_get();
        p->code_4  = color - cell->shade_5 * 0x10101;
        p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
        p->z_10    = cell->z_E;
        p->uv_C    = u | 0x3D480000;
        p->uv_14   = (u + 0x1F) | 0x4E0000;
        p->uv_1C   = u | 0x1F00;
        p->uv_24   = (u + 0x1F) | 0x1F00;
        p->size_18 = cell->size_8;
        p->pad_20  = 8;
    }
}

void func_80106AA0(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011B534[cell->frame_6 >> 2];
    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = u | 0x3D480000;
    p->uv_14   = (u + 0x1F) | 0x4E0000;
    p->uv_1C   = u | 0x1F00;
    p->uv_24   = (u + 0x1F) | 0x1F00;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_80106B70(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 4;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            face->value_2      = 0;
            func_80106E94(wp, face, 0);
            func_80106EBC(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0xA)
            {
                func_80106EBC(wp, face, 2);
                wp->routine_0++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x2D)
            {
                func_80106E94(wp, face, 2);
                func_80106EBC(wp, face, 0);
            }
            else if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                func_80106E94(wp, face, 1);
                func_80106EBC(wp, face, 1);
                wp->anim_AC = 5;
                wp->routine_0++;
            }
            break;
        case 3:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0xA)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 5)
            {
                if (scene->value_10 == 1)
                {
                    func_80106EBC(wp, face, 3);
                }
                else if (scene->value_10 == 0x1E)
                {
                    func_80106E94(wp, face, 3);
                }
            }
            switch (wp->value_A4)
            {
                case 3:
                    ST17_SCENE_BYTE(scene, 7) = 1;
                    break;
                case 0x11:
                    ST17_SCENE_BYTE(scene, 7) = 2;
                    break;
                case 0x19:
                    ST17_SCENE_BYTE(scene, 7) = 3;
                    break;
                case 0x20:
                    ST17_SCENE_BYTE(scene, 7) = 4;
                    break;
            }
            break;
    }
    func_80106EE4(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80106E94(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B5A4[index];
}

void func_80106EBC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B5B4[index];
}

void func_80106EE4(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_8010702C(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 6;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            face->value_2      = 0x37;
            face->timer_0      = 0;
            func_801072E0(wp, face, 0);
            func_80107308(wp, face, 0);
            wp->routine_0++;
            // fall through
        case 1:
            if (face->timer_0 == 0x92)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_AC   = 7;
            face->value_2 = 0;
            wp->routine_0++;
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            wp->anim_AC = 8;
            wp->routine_0++;
            break;
        case 5:
            break;
    }
    face->timer_0++;
    switch (Scene_work.value_10)
    {
        case 0x1E:
            func_80107308(wp, face, 1);
            break;
        case 0x37:
            func_80107308(wp, face, 1);
            break;
        case 0x87:
            func_801072E0(wp, face, 1);
            func_80107308(wp, face, 0);
            break;
        case 0x91:
            func_80107308(wp, face, 1);
            break;
        case 0x2D:
        case 0xAF:
            func_80107308(wp, face, 0);
            break;
    }
    func_80107330(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801072E0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B5F8[index];
}

void func_80107308(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B600[index];
}

void func_80107330(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_80107478(STAGE_LIPS *lips, sint32 index)
{
    lips->index_4 = 0;
    lips->mouth_8 = D_8011B618[index];
    lips->count_5 = 0;
}

void func_80107498(STAGE_LIPS *lips, sint32 index)
{
    lips->index_6 = 0;
    lips->eyes_C  = D_8011B63C[index];
    lips->count_7 = 0;
}

void func_801074B8(STAGE_OBJ *wp, STAGE_LIPS *lips)
{
    if (lips->count_5 == 0)
    {
        if (lips->mouth_8[lips->index_4] != 0x7E)
        {
            if (lips->mouth_8[lips->index_4] == 0x7F)
            {
                lips->index_4 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(lips->mouth_8[lips->index_4], 0x33, 0x37, 5));
            lips->count_5 = lips->mouth_8[lips->index_4 + 1];
            lips->index_4 += 2;
        }
    }
    else
    {
        lips->count_5--;
    }
    if (lips->count_7 == 0)
    {
        if (lips->eyes_C[lips->index_6] != 0x7E)
        {
            if (lips->eyes_C[lips->index_6] == 0x7F)
            {
                lips->index_6 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(lips->eyes_C[lips->index_6], 0x33, 0x37, 5));
            lips->count_7 = lips->eyes_C[lips->index_6 + 1];
            lips->index_6 += 2;
        }
    }
    else
    {
        lips->count_7--;
    }
}

void func_8010761C(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_LIPS *lips;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    lips                    = &wp->u_4E0.lips;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]          = 0x2000200;
            wp->scale.words[1]          = 0x200;
            wp->scale.v.pad             = 0x4210;
            wp->value_78                = 0;
            wp->value_44.words.fraction = 0;
            wp->value_44.words.integer  = 0;
            wp->value_48.words.fraction = 0;
            wp->u_C.b.byte_C            = 0;
            wp->u_C.b.byte_D            = 0;
            func_80107478(lips, 0);
            func_80107498(lips, 0);
            func_800322A8(wp, 1, 0);
            wp->routine_0++;
            break;
        case 2:
            wp->value_48.words.fraction = 0x20;
            wp->routine_0++;
            // fall through
        case 3:
            Obj_pos_set(wp, (sint16)wp->value_48.words.fraction, 0, 0);
            func_80032488(wp);
            break;
        case 1:
        case 4:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            break;
    }
    if (scene->u_8.byte[1] == 6)
    {
        if (scene->value_10 == 0x2D)
        {
            func_80107478(lips, 1);
        }
        else if (scene->value_10 == 0x35)
        {
            func_80107478(lips, 0);
        }
        else if (scene->value_10 == 0x41)
        {
            func_80107498(lips, 2);
        }
        else if (scene->value_10 == 0x96)
        {
            func_80107498(lips, 0);
        }
        else if (scene->value_10 == 0xA0)
        {
            func_80107478(lips, 1);
        }
        else if (scene->value_10 == 0xA8)
        {
            func_80107478(lips, 0);
        }
        else if (scene->value_10 == 0xC8)
        {
            func_80107478(lips, 1);
        }
        else if (scene->value_10 == 0xD0)
        {
            func_80107478(lips, 0);
        }
        else if (scene->value_10 == 0xDA)
        {
            func_80107498(lips, 1);
        }
        else if (scene->value_10 == 0xE6)
        {
            func_80107498(lips, 0);
        }
        func_801074B8(wp, lips);
    }
}

void func_8010787C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011B648[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    func_80107AEC(wp, face);
}

void func_801078F0(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->flags_0        = (uint8)wp->flags_0 | 2;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    func_80107AA4(wp, &wp->u_4E0.face16, 6);
    wp->u_C.b.byte_D = 0;
    wp->routine_1++;
}

void func_80107970(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    switch (Scene_work.value_10)
    {
        case 0x1E:
            func_800322A8(wp, 2, 0);
            func_80107AA4(wp, face, 0);
            break;
        case 0x2D:
            func_80107AA4(wp, face, 1);
            break;
        case 0x5F:
            func_80107AA4(wp, face, 2);
            break;
        case 0x64:
            func_80107AA4(wp, face, 3);
            break;
        case 0x78:
            func_800322A8(wp, 3, 0);
            break;
        case 0x8C:
            func_80107AA4(wp, face, 4);
            break;
        case 0xBE:
            func_80107AA4(wp, face, 5);
            break;
    }
}

void func_80107AA4(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011B700[index];
    face->eyes_10               = D_8011B71C[index];
}

void func_80107AEC(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_0, 0x33, 0x37, 5));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_6, 0x33, 0x37, 5));
    }
    face->prev_8 = face->shape_6;
}

void func_80107C38(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]     = 0x02000200;
            wp->scale.words[1]     = 0x200;
            wp->scale.v.pad        = 0x4210;
            wp->anim_AC            = 1;
            wp->value_78           = 0;
            wp->anim_prev_AD       = 0xFF;
            wp->u_4E0.face.value_2 = 0;
            func_80107EA8(wp, face, 0);
            func_80107ED0(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (Scene_work.u_8.byte[1] == 3 && Scene_work.value_10 == 0xA)
            {
                func_80107EA8(wp, face, 2);
                wp->routine_0++;
            }
            break;
        case 2:
            switch (Scene_work.value_10)
            {
                case 0x1E:
                    func_80107ED0(wp, face, 2);
                    break;
                case 0x32:
                    func_80107EA8(wp, face, 2);
                    break;
                case 0x46:
                    func_80107ED0(wp, face, 2);
                    break;
                case 0x8C:
                    func_80107EA8(wp, face, 2);
                    // fall through
                case 0x3C:
                    func_80107ED0(wp, face, 1);
                    break;
            }
            break;
    }
    func_80107EF8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80107EA8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B774[index];
}

void func_80107ED0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B780[index];
}

void func_80107EF8(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_80108040(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]     = 0x02000200;
            wp->scale.words[1]     = 0x200;
            wp->scale.v.pad        = 0x4210;
            wp->anim_AC            = 1;
            wp->value_78           = 0;
            wp->anim_prev_AD       = 0xFF;
            wp->u_4E0.face.value_2 = 0;
            func_8010832C(wp, face, 1);
            func_80108354(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (Scene_work.u_8.byte[1] == 3)
            {
                if (Scene_work.value_10 == 0x37)
                {
                    func_8010832C(wp, face, 3);
                }
                else if (Scene_work.value_10 == 0x41)
                {
                    func_80108354(wp, face, 2);
                    wp->routine_0++;
                }
            }
            break;
        case 2:
            if (Scene_work.u_8.byte[1] == 3 && Scene_work.value_10 == 0x73)
            {
                func_80108354(wp, face, 0);
            }
            else if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                wp->anim_AC = 2;
                func_8010832C(wp, face, 1);
                func_80108354(wp, face, 1);
                wp->routine_0++;
            }
            break;
        case 3:
            switch (Scene_work.value_10)
            {
                case 0xA:
                case 0x28:
                    func_80108354(wp, face, 3);
                    break;
                case 0x1E:
                case 0x4B:
                    func_80108354(wp, face, 1);
                    break;
                case 0x5A:
                    func_8010832C(wp, face, 3);
                    break;
            }
            break;
    }
    func_8010837C(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010832C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B7F4[index];
}

void func_80108354(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B804[index];
}

void func_8010837C(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_801084C4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_4 = 0;
    lips->mouth_8 = D_8011B820[index];
    lips->count_5 = 0;
}

void func_801084E4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_6 = 0;
    lips->eyes_C  = D_8011B83C[index];
    lips->count_7 = 0;
}

void func_80108504(STAGE_OBJ *wp, STAGE_LIPS *lips)
{
    if (lips->count_5 == 0)
    {
        if (lips->mouth_8[lips->index_4] != 0x7E)
        {
            if (lips->mouth_8[lips->index_4] == 0x7F)
            {
                lips->index_4 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(lips->mouth_8[lips->index_4], 0x33, 0x37, 5));
            lips->count_5 = lips->mouth_8[lips->index_4 + 1];
            lips->index_4 += 2;
        }
    }
    else
    {
        lips->count_5--;
    }
    if (lips->count_7 == 0)
    {
        if (lips->eyes_C[lips->index_6] != 0x7E)
        {
            if (lips->eyes_C[lips->index_6] == 0x7F)
            {
                lips->index_6 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(lips->eyes_C[lips->index_6], 0x33, 0x37, 5));
            lips->count_7 = lips->eyes_C[lips->index_6 + 1];
            lips->index_6 += 2;
        }
    }
    else
    {
        lips->count_7--;
    }
}

void func_80108668(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_LIPS *lips;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    lips                    = &wp->u_4E0.lips;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_78         = 0;
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_48.half[0] = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            func_801084C4(lips, 0);
            func_801084E4(lips, 0);
            func_800322A8(wp, 3, 0);
            wp->routine_0++;
            break;
        case 1:
        case 3:
            func_80032488(wp);
            break;
        case 2:
            break;
    }
    if (scene->value_10 == 0xA)
    {
        func_801084E4(lips, 1);
    }
    else if (scene->value_10 == 0x55)
    {
        func_801084E4(lips, 0);
        func_801084C4(lips, 1);
    }
    else if (scene->value_10 == 0x69)
    {
        func_801084E4(lips, 1);
    }
    else if (scene->value_10 == 0x96)
    {
        func_801084E4(lips, 0);
    }
    else if (scene->value_10 == 0xA0 || scene->value_10 == 0xAA)
    {
        func_801084C4(lips, 1);
    }
    func_80108504(wp, lips);
}

void func_80108864(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    temp_v1                 = wp->routine_0;
    switch (temp_v1)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]          = 0x02000200;
            wp->scale.words[1]          = 0x200;
            wp->scale.v.pad             = 0x4210;
            wp->value_78                = 0;
            wp->value_44.words.fraction = 0;
            wp->value_44.words.integer  = 0;
            wp->value_48.words.fraction = 0;
            wp->u_C.b.byte_C            = 0;
            wp->u_C.b.byte_D            = 0;
            func_800322A8(wp, 1, 0);
            wp->routine_0++;
            return;
        case 2:
            func_80032488(wp);
        case 1:
            return;
    }
}

void func_80108998(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 = (uint8)wp->flags_0 | 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->value_78       = 0;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
        return;
    }
    func_80032488(wp);
}

void func_80108A28(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    D_8011B844[wp->routine_0](wp, &Scene_work, face);
    func_801091EC(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_4E0.face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80108B28(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 9;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->timer_0      = 0;
    face->value_2      = 0;
    func_8010919C(wp, face, 6);
    func_801091C4(wp, face, 9);
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80108BD4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            if (wp->value_A4 == 0xE)
            {
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xE;
                wp->routine_1++;
            }
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0)
            {
                switch (scene->value_10)
                {
                    case 0x14:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0x28:
                        func_801091C4(wp, face, 0xB);
                        break;
                    case 0x5F:
                        func_801091C4(wp, face, 0);
                        break;
                    case 0x78:
                        func_8010919C(wp, face, 1);
                        func_801091C4(wp, face, 0xA);
                        break;
                    case 0x8C:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0x96:
                        func_801091C4(wp, face, 0xA);
                        break;
                    case 0xC8:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0xDC:
                        func_8010919C(wp, face, 3);
                        func_801091C4(wp, face, 2);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0xA;
                face->value_2 = 0;
                func_8010919C(wp, face, 2);
                func_801091C4(wp, face, 6);
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                if (face->timer_0 < 0x1E)
                {
                    face->timer_0++;
                }
                else
                {
                    face->timer_0 = 0;
                    wp->routine_1++;
                }
            }
            break;
        case 4:
            wp->anim_AC   = 0xB;
            face->value_2 = 0;
            func_8010919C(wp, face, 0);
            func_801091C4(wp, face, 0xB);
            wp->routine_1++;
            break;
        case 5:
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_8010919C(wp, face, 8);
                        func_801091C4(wp, face, 4);
                        break;
                    case 0x19:
                        func_801091C4(wp, face, 0xB);
                        break;
                    case 0x30:
                        func_801091C4(wp, face, 4);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0xC;
                face->value_2 = 0;
                func_8010919C(wp, face, 2);
                func_801091C4(wp, face, 0xC);
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (face->timer_0 < 0xA)
            {
                face->timer_0++;
            }
            else
            {
                func_8010919C(wp, face, 4);
                face->timer_0 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 4)
            {
                switch (scene->value_10)
                {
                    case 0x19:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0x37:
                        func_801091C4(wp, face, 0xC);
                        break;
                    case 0x55:
                        func_8010919C(wp, face, 2);
                        func_801091C4(wp, face, 5);
                        break;
                    case 0x7D:
                        func_801091C4(wp, face, 0xC);
                        break;
                    case 0xC3:
                        func_801091C4(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0xD;
                face->value_2 = 0;
                func_8010919C(wp, face, 5);
                func_801091C4(wp, face, 7);
                wp->routine_1++;
            }
            break;
        case 8:
            if (wp->value_A4 == 0xE)
            {
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xE;
                func_8010919C(wp, face, 7);
                func_801091C4(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 9:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x32:
                    func_8010919C(wp, face, 5);
                    func_801091C4(wp, face, 7);
                    break;
                case 0x3C:
                    func_801091C4(wp, face, 0xD);
                    break;
                case 0x64:
                    func_801091C4(wp, face, 7);
                    break;
                case 0x78:
                    func_8010919C(wp, face, 7);
                    func_801091C4(wp, face, 0xD);
                    wp->routine_1++;
                    break;
            }
            break;
        case 10:
            if (wp->value_A4 == 0x20)
            {
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0x20;
                wp->routine_1++;
            }
            break;
        case 11:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0xAA)
            {
                func_8010919C(wp, face, 5);
                func_801091C4(wp, face, 7);
            }
            else if (scene->value_10 == 0xC8)
            {
                func_8010919C(wp, face, 7);
                func_801091C4(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 12:
            if (scene->value_10 == 0xF3)
            {
                func_8010919C(wp, face, 5);
                func_801091C4(wp, face, 8);
            }
            break;
    }
}

void func_8010919C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B954[index];
}

void func_801091C4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B978[index];
}

void func_801091EC(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x2A, 0x40, 6));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x2A, 0x40, 6));
    }
    face->prev_10 = face->shape_F;
}

void func_80109334(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 1;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            face->value_2      = 0;
            func_8010971C(wp, face, 5);
            func_80109744(wp, face, 5);
            wp->routine_0++;
            break;
        case 1:
            if (wp->value_A4 == 0x1D)
            {
                func_8010971C(wp, face, 6);
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0x1D;
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0x32)
            {
                func_80109744(wp, face, 0xA);
            }
            else if (scene->value_10 == 0x5A)
            {
                func_8010971C(wp, face, 0);
                func_80109744(wp, face, 6);
                wp->routine_0++;
            }
            else if (scene->value_10 == 0xA0)
            {
                wp->routine_0++;
            }
            break;
        case 3:
            switch (scene->u_8.byte[1])
            {
                case 1:
                    break;
                case 2:
                    if (scene->value_10 == 1)
                    {
                        wp->anim_AC   = 2;
                        face->value_2 = 0;
                        func_80109744(wp, face, 0);
                        wp->routine_0++;
                    }
                    break;
            }
            break;
        case 4:
            switch (scene->value_10)
            {
                case 0xA:
                    func_8010971C(wp, face, 7);
                    func_80109744(wp, face, 7);
                    break;
                case 0x3C:
                    func_8010971C(wp, face, 8);
                    func_80109744(wp, face, 8);
                    break;
                case 0x82:
                    func_8010971C(wp, face, 2);
                    func_80109744(wp, face, 2);
                    wp->anim_AC   = 3;
                    face->value_2 = 0;
                    wp->routine_0++;
                    break;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 2)
            {
                if (scene->value_10 == 0x96)
                {
                    func_8010971C(wp, face, 8);
                    func_80109744(wp, face, 8);
                }
                else if (scene->value_10 == 0xC8)
                {
                    func_8010971C(wp, face, 2);
                    func_80109744(wp, face, 2);
                }
            }
            else if (scene->u_8.byte[1] == 3)
            {
                if (scene->value_10 == 1)
                {
                    wp->anim_AC   = 4;
                    face->value_2 = 0;
                    wp->routine_0++;
                }
            }
            break;
        case 6:
            if (scene->value_10 == 1)
            {
                func_8010971C(wp, face, 9);
                func_80109744(wp, face, 9);
            }
            else if (scene->value_10 == 0x3C)
            {
                func_8010971C(wp, face, 4);
                func_80109744(wp, face, 4);
            }
            break;
    }
    func_8010976C(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010971C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011BA68[index];
}

void func_80109744(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011BA90[index];
}

void func_8010976C(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x2A, 0x40, 6));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x2A, 0x40, 6));
    }
    face->prev_10 = face->shape_F;
}

void func_801098B4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_4 = 0;
    lips->mouth_8 = D_8011BACC[index];
    lips->count_5 = 0;
}

void func_801098D4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_6 = 0;
    lips->eyes_C  = D_8011BAEC[index];
    lips->count_7 = 0;
}

void func_801098F4(STAGE_OBJ *wp, STAGE_LIPS *lips)
{
    if (lips->count_5 == 0)
    {
        if (lips->mouth_8[lips->index_4] != 0x7E)
        {
            if (lips->mouth_8[lips->index_4] == 0x7F)
            {
                lips->index_4 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(lips->mouth_8[lips->index_4], 0x2A, 0x40, 6));
            lips->count_5 = lips->mouth_8[lips->index_4 + 1];
            lips->index_4 += 2;
        }
    }
    else
    {
        lips->count_5--;
    }
    if (lips->count_7 == 0)
    {
        if (lips->eyes_C[lips->index_6] != 0x7E)
        {
            if (lips->eyes_C[lips->index_6] == 0x7F)
            {
                lips->index_6 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(lips->eyes_C[lips->index_6], 0x2A, 0x40, 6));
            lips->count_7 = lips->eyes_C[lips->index_6 + 1];
            lips->index_6 += 2;
        }
    }
    else
    {
        lips->count_7--;
    }
}

void func_80109A58(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_LIPS *lips;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    lips                    = &wp->u_4E0.lips;
    if (Scene_work.u_8.byte[1] != 2)
    {
        return;
    }
    if (Scene_work.value_10 == 1)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0]   = 0x02000200;
        wp->scale.words[1]   = 0x200;
        wp->scale.v.pad      = 0x4210;
        wp->value_78         = 0;
        wp->value_44.half[0] = 0;
        wp->value_44.half[1] = 0;
        wp->value_48.half[0] = 0;
        wp->u_C.b.byte_C     = 0;
        wp->u_C.b.byte_D     = 0;
        func_801098B4(lips, 0);
        func_801098D4(lips, 0);
        func_800322A8(wp, 5, 0);
    }
    else if ((Scene_work.value_10 >= 0x16 && Scene_work.value_10 < 0x3E) || Scene_work.value_10 >= 0x1AF)
    {
        func_80032488(wp);
    }
    switch (scene->value_10)
    {
        case 0x14:
        case 0x69:
        case 0x12C:
        case 0x1AE:
        case 0xB4:
            func_801098D4(lips, 1);
            break;
        case 0x10E:
        case 0x4B:
        case 0x1F4:
            func_801098B4(lips, 1);
            // fall through
        case 0xA5:
        case 0x17C:
            func_801098D4(lips, 0);
            break;
        case 0x19A:
            func_801098B4(lips, 1);
            break;
    }
    func_801098F4(wp, lips);
}

void func_80109CA4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011BAF4[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    func_8010A3A8(wp, face);
}

void func_80109D18(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    face = &wp->u_4E0.face16;
    switch (Scene_work.u_8.byte[0])
    {
        case 2:
            func_800322A8(wp, 1, 0);
            wp->routine_1 = 1;
            break;
        case 4:
            wp->position.z = 0xFA;
            func_800322A8(wp, 3, 0);
            wp->routine_1 = 3;
            break;
        case 8:
            wp->position.z = 0xF0;
            func_800322A8(wp, 4, 0);
            wp->routine_1 = 4;
            break;
        case 0xB:
            func_800322A8(wp, 7, 0);
            wp->routine_1 = 5;
            wp->u_C.b.byte_D++;
            break;
    }
    func_8010A364(wp, face, 0);
    wp->routine_2 = 0;
    wp->u_C.b.byte_D++;
}

void func_80109E5C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
        func_8010A364(wp, face, 0);
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x14:
            wp->u_C.b.byte_D++;
            break;
        case 0x23:
            func_8010A364(wp, face, 1);
            break;
        case 0x122:
            func_8010A364(wp, face, 2);
            break;
    }
}

void func_80109F28(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        func_8010A364(wp, face, 3);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x19:
            func_8010A364(wp, face, 4);
            break;
        case 0x55:
            func_8010A364(wp, face, 5);
            break;
    }
}

void func_80109FD4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_8010A364(wp, face, 6);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 0x37)
    {
        func_8010A364(wp, face, 7);
    }
}

void func_8010A04C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    switch (Scene_work.value_10)
    {
        case 0x2D:
        case 1:
            func_8010A364(wp, face, 8);
            break;
        case 5:
            func_8010A364(wp, face, 9);
            wp->u_C.b.byte_D = 0;
            break;
        case 0x50:
            func_800322A8(wp, 5, 0);
            wp->u_C.b.byte_D = 0;
            break;
        case 0x78:
            func_800322A8(wp, 6, 0);
            func_8010A364(wp, face, 8);
            wp->u_C.b.byte_D = 0;
            break;
        case 0xB4:
            func_8010A364(wp, face, 9);
            wp->u_C.b.byte_D++;
            break;
    }
}

void func_8010A168(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_8010A364(wp, &wp->u_4E0.face16, 10);
        wp->routine_2++;
    }
}

void func_8010A1B4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    switch (Scene_work.value_10)
    {
        case 0x32:
        case 0xA5:
        case 0x1E0:
            func_8010A364(wp, face, 0xC);
            break;
        case 0x5A:
            func_8010A364(wp, face, 0xD);
            break;
        case 0xB9:
            func_800322A8(wp, 7, 0);
            wp->u_C.b.byte_D = 0;
            break;
        case 0xC8:
            func_8010A364(wp, face, 0xE);
            break;
        case 0x104:
            func_8010A364(wp, face, 0xE);
            break;
        case 0xEB:
        case 0x136:
            func_8010A364(wp, face, 0xF);
            break;
        case 0x140:
            func_800322A8(wp, 8, 0);
            func_8010A364(wp, face, 0xA);
            wp->u_C.b.byte_D = 0;
            break;
        case 0x168:
            func_8010A364(wp, face, 0xD);
            break;
        case 1:
        case 0x1AE:
            func_8010A364(wp, face, 0xB);
            break;
    }
}

void func_8010A364(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index)
{
    face->prev_2 = face->prev_8 = -1;
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->mouth_C                 = D_8011BC88[index];
    face->eyes_10                 = D_8011BC88[index];
}

void func_8010A3A8(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_0, 0x2A, 0x40, 6));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_6, 0x2A, 0x40, 6));
    }
    face->prev_8 = face->shape_6;
}

void func_8010A4F4(STAGE_OBJ *wp)
{
    D_8011BCD4[wp->routine_0](wp);
}

void func_8010A530(STAGE_OBJ *wp)
{
    ST17_HW *hw;
    sint16 life;
    uint32 i;

    wp->scale.v.x        = 0x200;
    wp->scale.v.y        = 0x200;
    wp->scale.v.z        = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->rotation.x       = 0;
    wp->rotation.y       = 0x400;
    wp->rotation.z       = 0;
    wp->value_48.half[0] = 0;
    wp->value_44.half[1] = 0;
    wp->value_44.half[0] = 0;
    wp->value_50         = 0;
    wp->value_4C.half[1] = 0;
    wp->value_4C.half[0] = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    hw = ST17_HW_OF(wp);
    func_8005D4D4();
    wp->u_C.b.byte_C       = 0;
    wp->value_78           = 0;
    life                   = D_8009884C[wp->kind_2]->life_8 * 16;
    wp->life_prev_B2       = 0;
    ST17_VALUE_74(wp)      = 1;
    hw->vec_8.x            = 0;
    hw->vec_8.y            = 0;
    hw->vec_8.z            = 0;
    wp->life_max_B0        = life;
    wp->life_6E            = life;
    hw->vec_10             = hw->vec_8;
    hw->value_0            = wp->rotation.y + 0x400;
    wp->position.x         = hw->vec_8.x;
    wp->position.z         = hw->vec_8.z - 0xE00;
    wp->position.y         = hw->vec_8.y - 0x800;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    for (i = 0; i < 8; i++)
    {
        D_80122AC8[i].value_0 = 0;
        D_80122AC8[i].value_4 = 0;
    }
    hw->timer_2 = 0x80;
    hw->value_4 = 0x3C;
    hw->value_6 = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_8010A6D0(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    func_8010A7E4(wp);
    D_8011BCE0[wp->routine_1](wp);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->routine_0 != 2 && wp->routine_1 != 3)
    {
        func_8010A884(wp);
    }
}

void func_8010A7E4(STAGE_OBJ *wp)
{
    sint32 i;
    sint32 damage;

    if (wp->routine_1 == 3)
    {
        return;
    }
    for (i = 0; i < 8; i++)
    {
        damage = D_80122AC8[i].value_0 & 0xFFFFFF;
        if (damage != 0)
        {
            goto hit;
        }
    }
    return;
hit:
    wp->life_6E -= damage;
    Sound_call(0xA0, 0, 0);
    wp->scale.v.pad = 0x7FFF;
    if (wp->life_6E <= 0)
    {
        func_8010B68C(wp);
    }
}

void func_8010A884(STAGE_OBJ *wp)
{
    uint32 i;

    for (i = 0; i < 8; i++)
    {
        D_80122AC8[i].value_0 = 0;
        D_80122A88[i]         = ST17_JOINT(wp)[D_8011BCF0[i]];
        if (i == 0)
        {
            func_800341BC(&D_80122A88[0], D_8011BCF8[0], 0, 0x8000, wp->value_1, &D_80122AC8[0], 0x4080000, 0, 0);
        }
        else
        {
            func_800341BC(&D_80122A88[i], D_8011BCF8[i], 0, 0x8000, wp->value_1, &D_80122AC8[i], 0x4080000, 0, 0x80);
        }
    }
}

void func_8010A9CC(STAGE_OBJ *wp)
{
    STAGE_FACE *face;
    sint16 rot;
    sint16 angle;

    face                   = &wp->u_4E0.face;
    rot                    = (wp->rotation.y - 0xC) & 0xFFF;
    angle                  = (rot - 0x400) & 0xFFF;
    wp->rotation.y         = rot;
    wp->u_4E0.face.timer_0 = angle;
    wp->position.x         = (uint32)(rsin(angle) * 7) >> 3;
    wp->position.y         = wp->u_4E0.face16.index_A - 0x800;
    wp->position.z         = (uint32)(rcos(wp->u_4E0.face.timer_0) * 7) >> 3;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (wp->u_4E0.face16.index_4 == 0)
    {
        if (wp->u_4E0.face16.shape_6 == 2)
        {
            wp->u_4E0.face16.index_4 = 0xC8;
            wp->u_4E0.face16.shape_6 = 0;
        }
        else
        {
            wp->u_4E0.face16.index_4 = 0xF;
            wp->u_4E0.face16.shape_6++;
        }
        func_8010BE04(wp);
        Sound_call(0x1A3, 0, 0);
    }
    else
    {
        wp->u_4E0.face16.index_4--;
    }
    if (face->value_2 == 0)
    {
        if (!(rand() & 0x3F))
        {
            if (rand() & 1)
            {
                func_8010B5DC(wp);
            }
            else
            {
                func_8010B58C(wp);
            }
        }
    }
    else
    {
        face->value_2--;
    }
}

void func_8010AB3C(STAGE_OBJ *wp)
{
    D_8011BD08[wp->routine_2](wp);
}

void func_8010AB78(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR fixed;

    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (ST17_HW_OF(wp)->timer_2 == 0)
    {
        wp->anim_AC              = 1;
        ST17_HW_OF(wp)->vec_1A   = wp->position;
        ST17_HW_OF(wp)->angle_22 = (wp->rotation.y - 0x400) & 0xFFF;
        fixed.x                  = ST17_HW_OF(wp)->vec_1A.x << 16;
        fixed.y                  = ST17_HW_OF(wp)->vec_1A.y << 16;
        fixed.z                  = ST17_HW_OF(wp)->vec_1A.z << 16;
        func_8002FFC4(&ST17_HW_OF(wp)->vec_1A, &fixed, ST17_HW_OF(wp)->angle_22, 0x7000, 0, 0);
        ST17_HW_OF(wp)->timer_2  = 0x40;
        ST17_HW_OF(wp)->value_4  = 0;
        ST17_HW_OF(wp)->angle_22 = (ST17_HW_OF(wp)->angle_22 + 0x800) & 0xFFF;
        wp->routine_2++;
    }
    else
    {
        ST17_HW_OF(wp)->timer_2--;
    }
}

void func_8010AC6C(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR fixed;
    ST17_HW *hw;

    hw = ST17_HW_OF(wp);
    if (wp->anim_AC == 1 && wp->value_A7 != 0)
    {
        wp->anim_AC = 3;
    }
    if (hw->timer_2 == 0x14)
    {
        wp->anim_AC = 2;
    }
    if (wp->anim_AC == 2 && wp->value_A7 != 0)
    {
        wp->anim_AC = 0;
    }
    if (hw->timer_2 == 0)
    {
        wp->anim_AC = 0;
        Sound_call(0x1A4, 0, 0);
        hw->timer_2 = 0x58;
        hw->value_4 = 0;
        wp->routine_2++;
        return;
    }
    pos     = hw->vec_1A;
    fixed.x = pos.x << 16;
    fixed.y = pos.y << 16;
    fixed.z = pos.z << 16;
    func_8002FFC4(&pos, &fixed, hw->angle_22, 0x7000, 0, 0);
    hw->angle_22         = (hw->angle_22 - 0x20) & 0xFFF;
    wp->position         = pos;
    wp->position_fixed.v = fixed;
    wp->rotation.y       = (wp->rotation.y - 0x20) & 0xFFF;
    hw->timer_2--;
}

void func_8010AE0C(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR fixed;

    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (ST17_HW_OF(wp)->timer_2 == 0)
    {
        wp->anim_AC              = 1;
        ST17_HW_OF(wp)->vec_1A   = wp->position;
        ST17_HW_OF(wp)->angle_22 = (wp->rotation.y - 0x400) & 0xFFF;
        fixed.x                  = ST17_HW_OF(wp)->vec_1A.x << 16;
        fixed.y                  = ST17_HW_OF(wp)->vec_1A.y << 16;
        fixed.z                  = ST17_HW_OF(wp)->vec_1A.z << 16;
        func_8002FFC4(&ST17_HW_OF(wp)->vec_1A, &fixed, ST17_HW_OF(wp)->angle_22, 0x7000, 0, 0);
        ST17_HW_OF(wp)->timer_2  = 0x40;
        ST17_HW_OF(wp)->angle_22 = (ST17_HW_OF(wp)->angle_22 + 0x800) & 0xFFF;
        wp->routine_2++;
    }
    else
    {
        func_8010B968(wp);
        ST17_HW_OF(wp)->timer_2--;
    }
}

void func_8010AF08(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR fixed;
    ST17_HW *hw;

    hw = ST17_HW_OF(wp);
    if (wp->anim_AC == 1 && wp->value_A7 != 0)
    {
        wp->anim_AC = 3;
    }
    if (hw->timer_2 == 0x14)
    {
        wp->anim_AC = 2;
    }
    if (wp->anim_AC == 2 && wp->value_A7 != 0)
    {
        wp->anim_AC = 0;
    }
    if (hw->timer_2 == 0)
    {
        wp->anim_AC = 0;
        hw->timer_2 = 0x18;
        wp->routine_2++;
        return;
    }
    pos     = hw->vec_1A;
    fixed.x = pos.x << 16;
    fixed.y = pos.y << 16;
    fixed.z = pos.z << 16;
    func_8002FFC4(&pos, &fixed, hw->angle_22, 0x7000, 0, 0);
    hw->angle_22         = (hw->angle_22 - 0x20) & 0xFFF;
    wp->position         = pos;
    wp->position_fixed.v = fixed;
    wp->rotation.y       = (wp->rotation.y - 0x20) & 0xFFF;
    hw->timer_2--;
}

void func_8010B094(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    temp_v0 = wp->u_4E0.hw.timer_2;
    if (temp_v0 == 0)
    {
        func_8010B520(wp);
        return;
    }
    wp->u_4E0.hw.timer_2 = temp_v0 - 1;
}

void func_8010B0F4(STAGE_OBJ *wp)
{
    D_8011BD1C[wp->routine_2](wp);
}

void func_8010B130(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (wp->value_A7 != 0)
    {
        wp->anim_AC          = 4;
        wp->u_4E0.hw.timer_2 = 0x22;
        wp->routine_2++;
    }
}

void func_8010B190(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.timer_2 == 0)
    {
        wp->anim_AC = 7;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (wp->u_4E0.hw.timer_2 >= 3)
    {
        wp->rotation.y = ((uint16)wp->rotation.y - 0x20) & 0xFFF;
    }
    wp->u_4E0.hw.timer_2 = (uint16)wp->u_4E0.hw.timer_2 - 1;
}

void func_8010B224(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        wp->value_44.words.fraction = 0x400;
        wp->value_44.words.integer  = 0x900;
        wp->value_48.words.fraction = 0;
        wp->u_4E0.hw.timer_2        = 0x20;
        Sound_call(0x1A7, 0, 0);
        wp->routine_2++;
    }
}

void func_8010B290(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.timer_2 == 0)
    {
        wp->u_4E0.hw.timer_2 = 0x5A;
        wp->u_4E0.hw.value_4 = 0;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    wp->u_4E0.hw.timer_2 = (uint16)wp->u_4E0.hw.timer_2 - 1;
}

void func_8010B300(STAGE_OBJ *wp)
{
    sint16 count;
    sint16 y;

    count = wp->u_4E0.hw.timer_2;
    if (count == 0)
    {
        wp->value_44.words.fraction = 0x500;
        wp->value_44.words.integer  = 0x180;
        wp->u_4E0.hw.timer_2        = 0x40;
        Sound_call(0x1A8, 0, 0);
        wp->routine_2++;
        return;
    }
    y                      = wp->position.y + D_8011BD38[count & 0xF];
    wp->position.y         = y;
    wp->position_fixed.v.y = y << 16;
    func_8010BC00(wp);
    wp->u_4E0.hw.timer_2--;
}

void func_8010B3B4(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.timer_2 == 0)
    {
        wp->anim_AC = 8;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    wp->u_4E0.hw.timer_2 = (uint16)wp->u_4E0.hw.timer_2 - 1;
}

void func_8010B420(STAGE_OBJ *wp)
{
    wp->rotation.y = (wp->rotation.y - 0x20) & 0xFFF;
    if (wp->value_A7 != 0)
    {
        func_8010B520(wp);
    }
}

void func_8010B458(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    func_8010B7A4(wp);
    face = &wp->u_4E0.face;
    if (wp->routine_2 == 0 && Sound_fade_flags == 0)
    {
        Sound_fade_start(0x10);
        func_8005D4E8();
        wp->routine_2++;
    }
    if (face->value_2 == 0)
    {
        if (wp->routine_2 != 0 && Sound_fade_flags == 0)
        {
            wp->u_C.b.byte_C = 1;
            wp->routine_0    = 2;
            wp->routine_1    = 0;
            wp->routine_2    = 0;
        }
    }
    else
    {
        face->value_2--;
    }
}

void func_8010B520(STAGE_OBJ *wp)
{
    wp->position           = wp->u_4E0.hw.vec_10;
    wp->rotation.y         = wp->u_4E0.hw.value_18;
    wp->u_4E0.hw.timer_2   = 0x80;
    wp->u_4E0.hw.value_4   = 0x1E;
    wp->u_4E0.hw.value_6   = 0;
    wp->routine_1          = 0;
    wp->routine_2          = 0;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010B58C(STAGE_OBJ *wp)
{
    wp->u_4E0.hw.vec_10         = wp->position;
    wp->u_4E0.hw.timer_2        = 0x40;
    wp->value_44.words.fraction = 0x600;
    wp->value_44.words.integer  = 0;
    wp->value_48.words.fraction = 0;
    wp->routine_1               = 1;
    wp->routine_2               = 0;
    wp->u_4E0.hw.value_18       = wp->rotation.y;
}

void func_8010B5DC(STAGE_OBJ *wp)
{
    sint16 angle;

    angle                 = (wp->rotation.y + 0x800) & 0xFFF;
    wp->u_4E0.hw.value_18 = angle;
    wp->u_4E0.hw.value_0  = (angle - 0x400) & 0xFFF;
    wp->u_4E0.hw.vec_10.x = (uint32)(rsin(wp->u_4E0.hw.value_0) * 7) >> 3;
    wp->u_4E0.hw.vec_10.y = wp->u_4E0.hw.vec_8.y - 0x800;
    wp->u_4E0.hw.vec_10.z = (uint32)(rcos(wp->u_4E0.hw.value_0) * 7) >> 3;
    wp->anim_AC           = 5;
    Sound_call(0x1A6, 0, 0);
    wp->value_44.words.integer  = -0x600;
    wp->value_44.words.fraction = 0;
    wp->value_48.words.fraction = 0;
    wp->routine_1               = 2;
    wp->routine_2               = 0;
}

void func_8010B68C(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    ST17_HW *ext;
    uint32 i;

    func_800322A8(wp, 9, 0);
    ext                         = (ST17_HW *)&wp->u_4E0;
    wp->u_4E0.hw.timer_2        = 0x96;
    wp->value_44.words.fraction = 0x280;
    wp->u_4E0.hw.value_4        = 0;
    wp->value_44.words.integer  = 1;
    Sound_key_off_voice(0x11);
    Sound_key_off_voice(0x13);
    for (i = 0; i < 4; i++)
    {
        pos = ST17_JOINT(wp)[D_8011BCC8[i].joint];
        pos.y -= D_8011BCC8[i].drop;
        ext->sparks_24[i] = ((ST17_SPARK5_FUNC)func_80105530)(&pos, 0x80, 1, 0x10, -8);
    }
    wp->routine_1 = 3;
    wp->routine_2 = 0;
}

void func_8010B7A4(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    ST17_HW *ext;
    STCOM_EFFECT *fx;
    uint8 joint;
    uint32 i;

    ext = (ST17_HW *)&wp->u_4E0;
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (wp->u_4E0.hw.value_4 == 0)
    {
        wp->u_4E0.hw.value_4 = D_8011BD48[rand() & 7];
        for (i = 0; i < 3; i++)
        {
            joint = D_8011BD50[rand() & 0xF];
            fx    = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 5;
                fx->kind_2          = 0x80;
                fx->variant_3       = 2;
                fx->sprite.position = ST17_JOINT(wp)[joint];
                fx->value_D         = 2;
            }
        }
    }
    else
    {
        wp->u_4E0.hw.value_4--;
    }
    for (i = 0; i < 4; i++)
    {
        pos = ST17_JOINT(wp)[D_8011BCC8[i].joint];
        pos.y -= D_8011BCC8[i].drop;
        ext->sparks_24[i]->x_1C = pos.x;
        ext->sparks_24[i]->y_1E = pos.y;
        ext->sparks_24[i]->z_20 = pos.z;
    }
}

void func_8010B968(STAGE_OBJ *wp)
{
    sint32 level;

    if (ST17_DIST(wp) <= 0xF42400)
    {
        if (wp->u_4E0.hw.value_4 == 0)
        {
            wp->u_4E0.hw.value_4 = 2;
            level                = ST17_DIST(wp) <= 0x53EC60;
            if (ST17_DIST(wp) <= 0x557300)
            {
                level = 2;
            }
            if (ST17_DIST(wp) <= 0x225510)
            {
                level = 3;
            }
            func_8010BA40(wp, 0, level);
            func_8010BA40(wp, 1, level);
            Sound_call(0x1A5, 0, 0);
        }
        else
        {
            wp->u_4E0.hw.value_4--;
        }
    }
}

void func_8010BA40(STAGE_OBJ *wp, sint32 side, sint32 level)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR v;
    ST17_SHOT *shot;

    if (side == 0)
    {
        func_80030058(&fixed, (wp->rotation.y - D_8011BD64[level]) & 0xFFF, 0x400, 0, 0);
    }
    else
    {
        func_80030058(&fixed, (wp->rotation.y + D_8011BD64[level]) & 0xFFF, 0x400, 0, 0);
    }
    func_80030150(&fixed, &v);
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0            = 3;
        shot->kind_2             = 1;
        shot->value_4            = 0;
        shot->value_F            = 4;
        shot->position.x         = ST17_JOINT(wp)[D_8011BD60[side]].x;
        shot->position.y         = ST17_JOINT(wp)[D_8011BD60[side]].y - 8;
        shot->position.z         = ST17_JOINT(wp)[D_8011BD60[side]].z;
        shot->position_fixed.v.x = shot->position.x << 16;
        shot->position_fixed.v.y = shot->position.y << 16;
        shot->position_fixed.v.z = shot->position.z << 16;
        func_8002FFC4(&shot->position, &shot->position_fixed.v, wp->rotation.y, D_8011BD6C[side].x, 0, D_8011BD6C[side].z);
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = 0x3000;
        shot->value_48.half[0] = v.z << 8;
        shot->value_4C.half[0] = 0;
        shot->value_4C.half[1] = 0;
        shot->value_50         = 0;
    }
}

void func_8010BC00(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.value_4 == 0)
    {
        wp->u_4E0.hw.value_4 = 2;
        func_8010BC84(wp, wp->u_4E0.hw.value_6);
        func_8010BC84(wp, wp->u_4E0.hw.value_6 + 4);
        wp->u_4E0.hw.value_6 = (wp->u_4E0.hw.value_6 + 1) & 3;
        Sound_call(0x1A9, 0, 0);
    }
    else
    {
        wp->u_4E0.hw.value_4--;
    }
}

void func_8010BC84(STAGE_OBJ *wp, sint32 index)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR v;
    ST17_SHOT *shot;

    func_80030058(&fixed, (wp->rotation.y + D_8011BD9C[rand() & 7]) & 0xFFF, 0x400, 0, 0);
    func_80030150(&fixed, &v);
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0            = 3;
        shot->kind_2             = 1;
        shot->value_4            = 0;
        shot->value_F            = 4;
        shot->position.x         = ST17_JOINT(wp)[5].x;
        shot->position.y         = ST17_JOINT(wp)[5].y - D_8011BD94[index & 3];
        shot->position.z         = ST17_JOINT(wp)[5].z;
        shot->position_fixed.v.x = shot->position.x << 16;
        shot->position_fixed.v.y = shot->position.y << 16;
        shot->position_fixed.v.z = shot->position.z << 16;
        func_8002FFC4(&shot->position, &shot->position_fixed.v, wp->rotation.y, D_8011BD74[index].x, 0, D_8011BD74[index].z);
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = D_8011BDAC[rand() & 7];
        shot->value_48.half[0] = v.z << 8;
        shot->value_4C.half[0] = 0;
        shot->value_4C.half[1] = 0;
        shot->value_50         = 0;
    }
}

void func_8010BE04(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    ST17_SHOT *shot;

    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0            = 1;
        shot->variant_3          = 6;
        shot->kind_2             = 0;
        shot->target_B8          = &STAGE_PL_BYTE(0x3A8);
        shot->position.x         = ST17_JOINT(wp)[10].x;
        shot->position.y         = ST17_JOINT(wp)[10].y - 0x100;
        shot->position.z         = ST17_JOINT(wp)[10].z;
        shot->position_fixed.v.x = shot->position.x << 16;
        shot->position_fixed.v.y = shot->position.y << 16;
        shot->position_fixed.v.z = shot->position.z << 16;
        rot.z                    = 0;
        rot.x                    = -(rand() & 0x3FF);
        rot.y                    = rand() & 0xFFF;
        RotMatrixYXZ(&rot, &shot->matrix_8C.m);
        scale.x = scale.y = scale.z = 0x200;
        ScaleMatrix(&shot->matrix_8C.m, &scale);
    }
}

void func_8010BEF0(STAGE_OBJ *wp)
{
    func_8010B7A4(wp);
    func_80032488(wp);
}

void func_8010BF20(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_8011BDBC[wp->routine_0](wp, &Scene_work, (ST17_RIG *)&wp->ext_3C0[0x80]);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_C.b.byte_D);
    }
    else
    {
        func_80032488(wp);
    }
    func_8010C30C(wp, (ST17_RIG *)&wp->ext_3C0[0x80]);
}

void func_8010C014(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->anim_prev_AD     = 0xFF;
    wp->value_78         = 0;
    wp->anim_AC          = 0;
    wp->value_44.half[0] = 0x300;
    wp->value_44.half[1] = 0;
    wp->value_48.half[0] = 0;
    wp->u_C.b.byte_C     = 0;
    wp->u_C.b.byte_D     = 0;
    rig->slot_0          = func_80105A0C(wp, 2, rig->rot_4);
    wp->routine_1        = 0;
    wp->routine_0++;
}

void func_8010C0C0(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 0 && scene->value_10 >= 0x3C)
            {
                Obj_pos_set(wp, 0x100, 0, 0);
            }
            else if (scene->u_8.byte[1] == 1 && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            func_8003187C(rig->slot_0);
            wp->routine_1++;
            break;
        case 2:
            if (scene->u_8.byte[1] == 5)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_8010C1C4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig)
{
    switch (wp->routine_1)
    {
        case 0:
            if (wp->u_C.b.byte_C < 0x20)
            {
                wp->u_C.b.byte_C++;
            }
            else
            {
                wp->u_C.b.byte_C = 0;
                wp->routine_1++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            break;
        case 1:
            if (wp->u_C.b.byte_C > 0x10)
            {
                wp->anim_AC = 5;
            }
            if (wp->u_C.b.byte_C < 0x40)
            {
                wp->value_44.half[0] -= 0xC;
                wp->value_44.half[1] -= 0xC;
                wp->u_C.b.byte_C++;
            }
            else
            {
                wp->routine_1++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            break;
        case 2:
            wp->anim_AC      = 4;
            wp->u_C.b.byte_C = 0;
            wp->u_C.b.byte_D = 0;
            wp->routine_1++;
            break;
        case 3:
            if (scene->value_10 < 0x97)
            {
                wp->value_44.half[1] = 0;
            }
            else
            {
                wp->value_44.half[1] = -0x400;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            break;
    }
}

// form gives index first.
void func_8010C30C(STAGE_OBJ *wp, ST17_RIG *rig)
{
    sint8 i;

    for (i = 0; i < 9; i++)
    {
        rig->rot_4[i] = ST17_JOINT(wp)[i + 1];
    }
}

void func_8010C36C(STAGE_OBJ *wp)
{
    STCOM_MATRIX m;
    STCOM_SVECTOR v;
    STAGE_SCENE_WORK *scene;
    STAGE_OBJ *model;
    sint32 i;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_78         = 0;
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_48.half[0] = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            func_800322A8(wp, 9, 0);
            wp->routine_0++;
            model                       = func_80105A0C(wp, 3, D_80122B08);
            ST17_SCENE_OBJ(scene, 0x1F) = model;
            model->flags_6 |= 0x20;
            break;
        case 1:
            func_80032488(wp);
            break;
        case 3:
            wp->rotation.z = 0x28;
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            wp->routine_0++;
            break;
        case 4:
            if (scene->value_10 & 8)
            {
                wp->rotation.z += 0xA;
            }
            else
            {
                wp->rotation.z -= 0xA;
            }
            if (scene->value_10 == 0x5A)
            {
                wp->value_44.half[0] = -0x14;
                wp->value_44.half[1] = 0x40;
                wp->value_4C.half[1] = 4;
                wp->value_48.half[0] = -0x140;
                wp->value_50         = -4;
                wp->routine_0++;
            }
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            break;
        case 5:
            wp->value_48.half[0] += wp->value_50;
            wp->rotation.z += wp->value_48.half[0] >> 4;
            wp->position.x += wp->value_44.half[0];
            wp->value_44.half[1] += wp->value_4C.half[1];
            wp->position.y += wp->value_44.half[1] >> 4;
            wp->position.z += 0xF;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            break;
    }
    for (i = 0; i < 7; i++)
    {
        RotMatrixYXZ(&wp->rotation, &m);
        ApplyMatrixSV(&m, &D_8011BDC8[i], &v);
        D_80122B08[i].x = wp->position.x + v.x;
        D_80122B08[i].y = wp->position.y + v.y;
        D_80122B08[i].z = wp->position.z + v.z;
    }
}
