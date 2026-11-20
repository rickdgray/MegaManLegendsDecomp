#include "common.h"
#include "st18.h"

// Installs the stage's slot routine tables.
void func_80100004(void)
{
    STAGE_TABLE_3C0      = D_80101DF0;
    STAGE_TABLE_5A4      = D_80101E1C;
    STAGE_TABLE_10C      = D_80101E38;
    STAGE_TABLE_48       = D_80101E3C;
    STAGE_TABLE_24       = D_80101E78;
    STAGE_TABLE_50       = D_80101EA8;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_80100074(void)
{
    void *spawn;
    sint16 *cells;

    func_80022FD4(D_80101F18[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 0;
    spawn                     = D_80101F9C[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_80101FC0[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_80102044[D_801020C4[Game_work.value_51]], D_80101FCC[Game_work.value_51]);
    func_8005DC10(0);
    func_801001D8();
}

void func_801001D8(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_801001E8(void)
{
    D_801020E8[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_8010023C(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DDE4(0x30);
        wp->routine_4++;
    }
}

void func_80100288(void)
{
}

void func_80100290(void)
{
}

void func_80100298(STAGE_EFFECT *wp)
{
    wp->frame_E = 0;
    wp->timer_D = 0;
    wp->flags_0 |= 0x22;
    wp->type_F   = rand() & 3;
    wp->mode_14  = 0x3CC00028;
    wp->w_24     = 0x20;
    wp->color_18 = 0x2C808080;
    wp->h_26     = 0;
    wp->size_3C  = 0;
    wp->routine_0++;
    func_801004C8(wp);
}

void func_80100318(STAGE_EFFECT *wp)
{
    STAGE_MATRIX m;
    STCOM_FIXED_VECTOR v;
    STCOM_FIXED_VECTOR out;

    switch (wp->routine_2)
    {
        case 0:
            if (++wp->timer_D == 0x10)
            {
                wp->routine_2++;
            }
            wp->size_3C += 128.0;
            v.z = wp->value_40 + rsin(wp->timer_D << 6) * 8000;
            v.y = 0;
            v.x = 0;
            STAGE_MATRIX_IDENTITY_SCALAR(m.w);
            RotMatrixY(wp->angle_3E, &m.m);
            ApplyMatrixLV(&m.m, &v, &out);
            wp->x_2C.value = out.x + (wp->u_28.parent->x_1C << 16);
            wp->z_34.value = out.z + (wp->u_28.parent->z_20 << 16);
            wp->y_30.value -= 2621440.0;
            break;
        case 1:
            if (++wp->timer_D == 0x20)
            {
                wp->routine_0++;
            }
            wp->y_30.value -= 2621440.0;
            break;
    }
}

void func_801004C8(STAGE_EFFECT *wp)
{
    uint8 *uv;

    D_80102128[wp->routine_1](wp);
    wp->x_1C = wp->x_2C.value >> 16;
    wp->y_1E = wp->y_30.value >> 16;
    wp->z_20 = wp->z_34.value >> 16;
    wp->h_26 = wp->size_3C >> 8;
    if (++wp->frame_E >= D_80102174[wp->type_F])
    {
        wp->frame_E = 0;
    }
    uv       = D_80102164[wp->type_F];
    wp->u_22 = uv[wp->frame_E * 2];
    wp->v_23 = uv[wp->frame_E * 2 + 1];
}

void func_801005B0(STAGE_EFFECT *wp)
{
    func_80031988(wp);
}

void func_801005D0(STAGE_EFFECT *wp)
{
    wp->timer_D = 5;
    wp->routine_0++;
}

void func_801005E8(STAGE_EFFECT *wp)
{
    STAGE_EFFECT *ep;

    if (--wp->timer_D == 0)
    {
        ep = (STAGE_EFFECT *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0     = 1;
            ep->kind_2      = 0xE;
            ep->variant_3   = wp->variant_3;
            ep->value_C     = 1;
            ep->u_28.parent = wp;
            ep->flags_6 |= 0x20;
            ep->angle_3E   = rand() & 0xFFF;
            ep->value_40   = wp->u_28.value << 16;
            ep->y_30.value = wp->y_1E << 16;
        }
        wp->timer_D = 5;
    }
}

void func_801006A0(STAGE_EFFECT *wp)
{
    func_80031988(wp);
}

void func_801006C0(STAGE_EFFECT *wp)
{
    if (wp->value_C == 0)
    {
        D_80102178[wp->routine_0](wp);
    }
    else
    {
        D_80102184[wp->routine_0](wp);
    }
}

STAGE_EFFECT *func_8010072C(STCOM_SVECTOR *pos, sint16 value, uint8 variant)
{
    STAGE_EFFECT *ep;

    ep = (STAGE_EFFECT *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0xE;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->value_C   = 0;
        ep->variant_3 = variant;
        ep->flags_6 |= 0x20;
        ep->u_28.value = value;
        return ep;
    }
    return NULL;
}

void func_801007C0(STAGE_WORK *wp)
{
    D_801078B8[0] = 0;
    func_8002D320(wp->model_88, 0x110010, func_8002D404(D_801078B4[0]->id, 0x2A, 0x33, 6));
}

void func_8010081C(STAGE_WORK *wp)
{
    D_801078C0[0] = 0;
    func_8002D320(wp->model_88, 0x130012, func_8002D404(D_801078BC[0]->id, 0x2A, 0x33, 6));
}

void func_80100878(STAGE_WORK *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_801078B4_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801078B4[0] += count;
            func_801007C0(wp);
        }
        else if (++D_801078B8[0] == p->count)
        {
            D_801078B4_S = p + 1;
            func_801007C0(wp);
        }
    }
    p     = D_801078BC_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801078BC[0] += count;
            func_8010081C(wp);
        }
        else if (++D_801078C0[0] == p->count)
        {
            D_801078BC_S = p + 1;
            func_8010081C(wp);
        }
    }
}

void func_801009A0(STAGE_WORK *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_801078C4.cue_0->u.end != 0xFF && D_801078C4.cue_0->u.scene == scene->u_8.value_8 &&
        D_801078C4.cue_0->line == scene->value_1C)
    {
        D_801078B4[0] = D_80102348[D_801078C4.cue_0->index];
        func_801007C0(wp);
        D_801078C4.cue_0++;
    }
    if (D_801078C4.cue_4->u.end != 0xFF && D_801078C4.cue_4->u.scene == scene->u_8.value_8 &&
        D_801078C4.cue_4->line == scene->value_1C)
    {
        D_801078BC[0] = D_80102378[D_801078C4.cue_4->index];
        func_8010081C(wp);
        D_801078C4.cue_4++;
    }
    func_80100878(wp);
}

void func_80100AE8(STAGE_WORK *wp)
{
    sint32 i;

    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    D_801078C4.cue_0   = D_801023C8;
    D_801078C4.cue_4   = D_80102418;
    for (i = 0; i < 0x18; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    wp->u_E.angle = 0;
    wp->routine_0++;
}

void func_80100B74(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x10, 0);
        wp->routine_2++;
    }
}

void func_80100BC0(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x11, 0);
        wp->routine_2++;
    }
}

void func_80100C0C(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x12, 0);
        wp->routine_2++;
    }
}

void func_80100C58(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x13, 0);
        wp->routine_2++;
    }
}

void func_80100CA4(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x14, 0);
        wp->routine_2++;
    }
}

void func_80100CF0(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x1B, 0);
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 == 0x35)
            {
                func_800322A8(wp, 0x15, 0);
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}

void func_80100D70(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_80100DCC(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x17, 0);
        wp->routine_2++;
    }
}

void func_80100E18(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x18, 0);
        wp->routine_2++;
    }
}

void func_80100E64(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x19, 0);
        wp->routine_2++;
    }
}

void func_80100EB0(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x1A, 0);
        wp->routine_2++;
    }
}

void func_80100EFC(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x10, 0);
            wp->timer_C            = 0x14;
            wp->rot_y_56           = 0x5DC;
            wp->position_fixed.v.x = 0xFEB60000;
            wp->position_fixed.v.z = 0xFE520000;
            wp->routine_2++;
            break;
        case 1:
            if (--wp->timer_C == 0)
            {
                wp->timer_C = 0x1C;
                wp->routine_2++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                wp->routine_2++;
            }
            wp->rot_y_56 += 0x14;
            break;
    }
    Obj_pos_set(wp, 0x50, 0, 0);
}

void func_80101014(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 2, 0);
            wp->timer_C            = 0x14;
            wp->position_fixed.v.x = 0xFE5C0000;
            wp->rot_y_56           = 0;
            wp->position_fixed.v.z = 0xFF3D0000;
            wp->routine_2++;
            break;
        case 1:
            if (--wp->timer_C == 0)
            {
                wp->timer_C = 0x1C;
                wp->routine_2++;
            }
            break;
        case 2:
            wp->rot_y_56 -= 0x14;
            break;
    }
    Obj_pos_set(wp, 0x50, 0, 0);
}

void func_801010FC(STAGE_WORK *wp)
{
    STAGE_SCENE_FACE *face;

    D_801024A8[wp->routine_1](wp);
    if (wp->value_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_801009A0(wp);
    face = Scene_work.face;
    switch (wp->routine_1)
    {
        case 1:
            if (*wp->anim_98 >= 0x22)
            {
                face->value_C = D_8010214C[*wp->anim_98];
            }
            break;
        case 2:
            if (*wp->anim_98 < 5)
            {
                face->value_C = D_801021C8[*wp->anim_98];
            }
            break;
        case 5:
            if (wp->anim_AC == 0x15 && *wp->anim_98 >= 0x1B)
            {
                face->value_C = D_8010219E[*wp->anim_98];
            }
            break;
    }
    if (wp->value_148[3] != -1)
    {
        if (wp->u_E.blink.direction == 0)
        {
            if (++wp->u_E.blink.level == 0xF)
            {
                wp->u_E.blink.direction = 1;
            }
        }
        else if (--wp->u_E.blink.level == 0)
        {
            wp->u_E.blink.direction = 0;
        }
        wp->pal[20].color = (uint8)wp->u_E.blink.level * 0x421 + 0x4210;
    }
}

void func_801012D8(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80100AE8(wp);
    }
    func_801010FC(wp);
}

void func_8010131C(STAGE_WORK *wp)
{
    D_801078D0[0] = 0;
    func_8002D320(wp->model_88, 0x110010, func_8002D404(D_801078CC[0]->id, 0x33, 0x37, 5));
}

void func_80101378(STAGE_WORK *wp)
{
    D_801078D8[0] = 0;
    func_8002D320(wp->model_88, 0x130012, func_8002D404(D_801078D4[0]->id, 0x33, 0x37, 5));
}

void func_801013D4(STAGE_WORK *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_801078CC_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801078CC[0] += count;
            func_8010131C(wp);
        }
        else if (++D_801078D0[0] == p->count)
        {
            D_801078CC_S = p + 1;
            func_8010131C(wp);
        }
    }
    p     = D_801078D4_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801078D4[0] += count;
            func_80101378(wp);
        }
        else if (++D_801078D8[0] == p->count)
        {
            D_801078D4_S = p + 1;
            func_80101378(wp);
        }
    }
}

void func_801014FC(STAGE_WORK *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_801078DC.cue_0->u.end != 0xFF && D_801078DC.cue_0->u.scene == scene->u_8.value_8 &&
        D_801078DC.cue_0->line == scene->value_1C)
    {
        D_801078CC[0] = D_80102618[D_801078DC.cue_0->index];
        func_8010131C(wp);
        D_801078DC.cue_0++;
    }
    if (D_801078DC.cue_4->u.end != 0xFF && D_801078DC.cue_4->u.scene == scene->u_8.value_8 &&
        D_801078DC.cue_4->line == scene->value_1C)
    {
        D_801078D4[0] = D_8010264C[D_801078DC.cue_4->index];
        func_80101378(wp);
        D_801078DC.cue_4++;
    }
    func_801013D4(wp);
}

void func_80101644(STAGE_WORK *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    D_801078DC.cue_0   = D_80102688;
    D_801078DC.cue_4   = D_801026DC;
    wp->routine_0++;
}

void func_801016B8(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80101704(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_80101750(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_8010179C(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_801017E8(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80101834(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_80101880(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        wp->routine_2++;
    }
}

void func_801018CC(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        wp->routine_2++;
    }
}

void func_80101918(STAGE_WORK *wp)
{
    D_801027C8[wp->routine_1](wp);
    if (wp->value_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_801014FC(wp);
}

void func_80101988(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80101644(wp);
    }
    func_80101918(wp);
}

void func_801019CC(STAGE_WORK *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0]     = 0x2000200;
    wp->scale.words[1]     = 0x42100200;
    wp->position_fixed.v.y = 0xFE700000;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_80101A38(void)
{
}

void func_80101A40(STAGE_WORK *wp)
{
    STCOM_SVECTOR pos;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            pos.x = wp->position_fixed.v.x >> 16;
            pos.y = 0;
            pos.z = wp->position_fixed.v.z >> 16;
            func_8010072C(&pos, 0x1F4, 0);
            break;
        case 1:
            wp->position_fixed.v.y += -0x10000;
            break;
        case 2:
            wp->position_fixed.v.y += -0x20000;
            break;
    }
}

void func_80101AE4(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->timer_C = 0;
        wp->routine_2++;
    }
    else
    {
        wp->position_fixed.v.y = rsin(++wp->timer_C << 6) * 0x140 + 0xFC180000;
    }
}

void func_80101B60(STAGE_WORK *wp)
{
    D_801027E8[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032538(wp);
    func_800334C4(wp);
}

void func_80101BC4(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_801019CC(wp);
    }
    func_80101B60(wp);
}

void func_80101C08(STAGE_LIGHT *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR rot;

    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 4;
        Model_work_init(wp, NULL);
        wp->angle_C = 0;
        wp->routine_0++;
    }
    wp->color_40 = wp->level_E * 0x10101;
    rot.x        = 0;
    rot.y        = 0x800;
    rot.z        = wp->angle_C;
    STAGE_MATRIX_IDENTITY(wp->matrix.w);
    STAGE_MATRIX_IDENTITY(m.w);
    RotMatrix(&rot, &m.m);
    MulMatrix(&wp->matrix.m, &m.m);
}

void func_80101CE8(STAGE_EVENT *wp)
{
    STAGE_UNPACK u;
    STAGE_UV4 unused;

    if (++wp->timer_C == 4)
    {
        wp->timer_C = 0;
        if (++wp->step_D == 4)
        {
            Close_EVE_WORK(wp);
            return;
        }
    }
    u = func_8002DC84((void *)wp->key_1C, 0, 5);
    func_8002DE04(u.c, 0, D_801027F4[wp->step_D]);
}

void func_80101D94(void)
{
    STAGE_EVENT *ep;

    ep = Open_EVE_WORK();
    if (ep != NULL)
    {
        ep->flags_0 = 1;
        ep->kind_2  = 0xB;
        ep->step_D  = 0;
        ep->timer_C = 0;
        ep->key_1C  = func_8003AC24(0xC0000);
    }
}
