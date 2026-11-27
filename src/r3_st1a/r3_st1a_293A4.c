#include "common.h"
#include "st1a.h"

void func_801293A4(STAGE_OBJ *wp)
{
    D_80138D74[wp->type](wp);
}

void func_801293E0(STAGE_OBJ *wp)
{
    D_80138D88[wp->routine_0](wp);
}

void func_8012941C(STAGE_FX *wp)
{
    STAGE_OBJ50 *owner;

    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->frame_E   = 0;
    wp->type_F    = 0;
    wp->be_flag |= TRANS;
    wp->timer_D -= 3;
    owner        = func_80036294(wp->work_0);
    wp->x_1C     = owner->pos_38.x + D_80138D24[wp->timer_D * 3];
    wp->y_1E     = owner->pos_38.y + D_80138D26[wp->timer_D * 3];
    wp->z_20     = owner->pos_38.z + D_80138D28[wp->timer_D * 3];
    wp->u_22     = D_80138D5C[wp->type_F * 2];
    wp->v_23     = D_80138D5D[wp->type_F * 2];
    wp->color_18 = 0x2E808080;
    wp->mode_14  = 0x3D080029;
    wp->w_24     = 0x10;
}

void func_80129544(STAGE_FX *wp)
{
    wp->u_22 = D_80138D5C[wp->type_F * 2];
    wp->v_23 = D_80138D5D[wp->type_F * 2];
    if (++wp->type_F >= 8)
    {
        wp->routine_0 = 2;
    }
}

void func_801295A0(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_801295C0(STAGE_OBJ *wp)
{
    D_80138D94[wp->routine_0](wp);
}

void func_801295FC(STAGE_OBJ *wp)
{
    wp->routine_0                           = 1;
    wp->position_fixed.f.y.words.fraction   = 0x188;
    wp->routine_1                           = 0;
    wp->routine_2                           = 0;
    wp->routine_3                           = 0;
    wp->u_E.b.work_2                        = 0;
    wp->u_E.b.work_3                        = 0;
    wp->position_fixed.f.x.words.fraction   = 0;
    wp->position_fixed.f.x.words.integer    = -0xD4;
    wp->position_fixed.f.pad.words.fraction = (wp->u_C.b.work_1 * 0xC) + 0xF;
}

void func_80129648(STAGE_OBJ *wp)
{
    uint16 temp_v0;

    temp_v0                                 = wp->position_fixed.f.pad.words.fraction - 1;
    wp->position_fixed.f.pad.words.fraction = temp_v0;
    if ((temp_v0 << 0x10) == 0)
    {
        wp->routine_0 = 2;
    }
}

void func_80129670(STAGE_OBJ *wp)
{
    uint16 temp_v0;

    wp->position_fixed.f.x.words.integer = -0xC8 - ((sint32)(rcos((sint16)wp->position_fixed.f.pad.words.fraction * 0x10) * 0xC8) >> 0xC);
    func_80129714(wp);
    temp_v0                                 = wp->position_fixed.f.pad.words.fraction + 1;
    wp->position_fixed.f.pad.words.fraction = temp_v0;
    if ((sint16)temp_v0 >= 0x81)
    {
        wp->routine_0 = 3;
    }
}

void func_801296F4(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80129714(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    uint8 i;
    uint8 u;
    uint8 v;
    sint32 tp;

    u = 0x40;
    v = 0;
    for (i = 0; i < 9; i++)
    {
        pos.x      = i * 50 - 200;
        pos.z      = 0x200;
        pos.y      = wp->position_fixed.f.x.words.integer;
        p          = Billboard_get();
        p->code_4  = 0x2E202020;
        p->uv_C    = (v << 8) | (u | 0x3D480000);
        tp         = (u + 0x1F) | 0x2E0000;
        p->uv_14   = (v << 8) | tp;
        p->uv_1C   = ((v + 0x1F) << 8) | u;
        p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
        p->size_18 = 0x40;
        p->pad_20  = 0;
        p->xy_8    = *(uint32 *)&pos.x;
        p->z_10    = *(uint32 *)&pos.z;
    }
}

void func_80129810(STAGE_OBJ *wp)
{
    D_80138DA4[wp->routine_0](wp);
}

void func_8012984C(STAGE_FX *wp)
{
    STAGE_OBJ *owner;

    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->be_flag |= TRANS;
    wp->frame_E  = D_80138D56[wp->timer_D * 4];
    wp->type_F   = 0;
    owner        = func_80036294(wp->work_0);
    wp->x_1C     = owner->position.x + D_80138D48[wp->timer_D * 3];
    wp->y_1E     = owner->position.y + D_80138D4A[wp->timer_D * 3];
    wp->z_20     = owner->position.z + D_80138D4C[wp->timer_D * 3];
    wp->u_22     = D_80138D5C[wp->type_F * 2];
    wp->v_23     = D_80138D5D[wp->type_F * 2];
    wp->color_18 = 0x2E808080;
    wp->mode_14  = 0x3DC00029;
    wp->w_24     = D_80138D54[wp->timer_D * 2];
}

void func_80129990(STAGE_FX *wp)
{
    wp->u_22 = D_80138D5C[wp->type_F * 2];
    wp->v_23 = D_80138D5D[wp->type_F * 2];
    if (++wp->type_F >= 8)
    {
        wp->type_F = 0;
    }
    if (wp->frame_E != Scene_work.u_8.byte[1])
    {
        wp->routine_0 = 2;
    }
}

void func_80129A04(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80129A24(STAGE_OBJ *wp)
{
    D_80138DB0[wp->routine_0](wp);
}

void func_80129A60(STAGE_FX *wp)
{
    func_80036294((sint32)wp->work_0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0x10;
    wp->frame_E   = 0;
    wp->be_flag |= TRANS;
    wp->type_F  = rand() & 7;
    wp->mode_14 = 0x3DC00029;
    wp->w_24    = 0x40;
    func_80129BD8(wp);
}

void func_80129AE0(STAGE_OBJ *wp)
{
    STAGE_OBJ50 *owner;

    owner = func_80036294(wp->u_C.b.work_0);
    func_80129BD8(wp);
    if (++wp->u_E.b.work_3 >= 8)
    {
        wp->u_E.b.work_3 = 0;
    }
    if (!(owner->be_flag & MOVE))
    {
        func_80031988((STCOM_EFFECT *)wp);
    }
    if (owner->pos_38.y != 0)
    {
        wp->routine_0 = 2;
    }
}

void func_80129B7C(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    func_80036294((sint32)wp->u_C.b.work_0);
    func_80129BD8(wp);
    temp_v0       = wp->routine_3 - 2;
    wp->routine_3 = temp_v0;
    if (!(temp_v0 & 0xFF))
    {
        func_80031988((STCOM_EFFECT *)wp);
    }
}

void func_80129BD8(STAGE_FX *wp)
{
    STAGE_OBJ50 *owner;
    STCOM_SVECTOR cam;
    sint32 angle;
    uint32 c;

    owner    = func_80036294(wp->work_0);
    wp->x_1C = owner->pos_38.x;
    wp->y_1E = owner->pos_38.y;
    wp->z_20 = owner->pos_38.z;
    cam.x    = D_800A39F0.x;
    cam.y    = D_800A39F0.y;
    cam.z    = D_800A39F0.z;
    angle    = ratan2(cam.x - wp->x_1C, cam.z - wp->z_20) & 0xFFF;
    wp->x_1C += (rsin(angle) * 60) >> 12;
    wp->y_1E -= 0xE6;
    wp->z_20 += (rcos(angle) * 60) >> 12;
    wp->u_22     = D_80138D5C[wp->type_F * 2];
    wp->v_23     = D_80138D5D[wp->type_F * 2];
    c            = wp->routine_3 << 3;
    wp->color_18 = 0x2E000000 | (c << 16) | (c << 8) | c;
}

void func_80129D28(STAGE_OBJ *wp)
{
    D_80138DBC[wp->routine_0](wp);
}

void func_80129D64(STAGE_OBJ *wp)
{
    func_80036294((sint32)wp->u_C.b.work_0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0x10;
    wp->be_flag |= 0x22;
    wp->u_E.b.work_3 = rand() & 1;
    func_80129EC4(wp);
}

void func_80129DCC(STAGE_OBJ *wp)
{
    STAGE_OBJ50 *owner;

    owner = func_80036294(wp->u_C.b.work_0);
    func_80129EC4(wp);
    if (++wp->u_E.b.work_3 >= 3)
    {
        wp->u_E.b.work_3 = 0;
    }
    if (!(owner->be_flag & MOVE))
    {
        func_80031988((STCOM_EFFECT *)wp);
    }
    if (owner->pos_38.y != 0)
    {
        wp->routine_0 = 2;
    }
}

void func_80129E68(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    func_80036294((sint32)wp->u_C.b.work_0);
    func_80129EC4(wp);
    temp_v0       = wp->routine_3 - 2;
    wp->routine_3 = temp_v0;
    if (!(temp_v0 & 0xFF))
    {
        func_80031988((STCOM_EFFECT *)wp);
    }
}

void func_80129EC4(STAGE_FX *wp)
{
    STAGE_OBJ50 *owner;
    STAGE_OBJ *target;
    sint32 angle;
    uint32 c;

    owner    = func_80036294(wp->work_0);
    target   = STAGE_SCENE.slot_24[0];
    wp->x_1C = owner->pos_38.x;
    wp->y_1E = owner->pos_38.y;
    wp->z_20 = owner->pos_38.z;
    angle    = ratan2(target->position.x - wp->x_1C, target->position.z - wp->z_20) & 0xFFF;
    wp->x_1C += (rsin(angle) * D_80138DE8[wp->frame_E].radius_2) >> 12;
    wp->y_1E -= D_80138DE8[wp->frame_E].rise_4;
    wp->z_20 += (rcos(angle) * D_80138DE8[wp->frame_E].radius_2) >> 12;
    wp->u_22     = D_80138D6C[wp->type_F].u;
    wp->v_23     = D_80138D6C[wp->type_F].v;
    wp->w_24     = D_80138DE8[wp->frame_E].w_0;
    c            = wp->routine_3 * 6;
    wp->h_26     = D_80138DC8[wp->timer_D];
    wp->color_18 = 0x2E000000 | (c << 16) | (c << 8) | c;
    wp->mode_14  = 0x3DC0002E;
    if (Scene_work.u_8.value_8 == 0x1B00)
    {
        wp->h_26 = D_80138DD8[wp->timer_D];
    }
    if (Scene_work.u_8.value_8 == 0x1C00)
    {
        wp->h_26 = D_80138DD8[wp->timer_D];
    }
}

void func_8012A0DC(STAGE_OBJ *wp)
{
    D_80138EE8[wp->routine_0](wp);
}

void func_8012A118(ST1A_LAMP *wp)
{
    uint32 type;

    wp->be_flag |= TRANS;
    type                 = wp->type & 0xF;
    wp->value_44         = D_80138E10[type][wp->work_1].value_0;
    wp->value_46         = D_80138E10[type][wp->work_1].value_2;
    wp->color_40         = 0x2808080;
    wp->routine_2        = 0;
    wp->pos_38.pad       = 0;
    wp->matrix.words[0]  = 0x1000;
    wp->matrix.words[1]  = 0;
    wp->matrix.words[2]  = 0x1000;
    wp->matrix.words[3]  = 0;
    wp->matrix.words[4]  = 0x1000;
    wp->matrix.words[5]  = 0;
    wp->matrix.words[6]  = 0;
    wp->matrix.words[7]  = 0;
    wp->matrix.m.m[0][0] = wp->matrix.m.m[1][1] = wp->matrix.m.m[2][2] = 0;
    if (wp->type & 0x80)
    {
        type = 4;
    }
    else
    {
        type = wp->type & 0xF;
        if (type >= 7)
        {
            goto outside;
        }
        if (type < 4)
        {
        outside:
            if (-wp->pos_38.y - 1 < 0x1E)
            {
                type = 4;
            }
            else
            {
                type = 5;
            }
        }
    }
    if (wp->work_2 == 0)
    {
        type += 2;
    }
    Model_work_init(wp, (uint8 *)&type);
    wp->routine_0++;
    wp->routine_3 = 0;
    if (wp->work_0 != 0)
    {
        Sound_call2(0xA1, &wp->pos_38);
    }
}

void func_8012A270(STAGE_OBJ50 *wp)
{
    sint32 color;

    D_80138EF4[wp->routine_1](wp);
    if (STAGE_GAME.value_5B >= 2)
    {
        color = D_80138EE0[wp->value_E][wp->u_C.b.hi];
    }
    else
    {
        color = D_80138EE0[wp->value_E][wp->u_C.b.hi] + 0x20;
    }
    func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xA000, wp->work_id, D_801397DC, color | 0x10000000, 0, 0x80);
}

// Packing color within each case preserves the separate brightness clamps.
void func_8012A374(ST1A_LAMP *wp)
{
    sint32 c;
    sint32 low;

    switch (wp->type & 0xF)
    {
        case 0:
        default:
            wp->value_44 += wp->value_46;
            wp->pos_38.pad += wp->value_44;
            if (wp->value_44 <= 0)
            {
                low = D_80138E80[wp->work_1].low_0;
                if (wp->pos_38.pad < low)
                {
                    wp->routine_0++;
                    wp->pos_38.pad = 0;
                    return;
                }
                wp->value_46 = 0;
                wp->value_44 = D_80138E80[wp->work_1].kick_2;
                if (wp->pos_38.pad > D_80138E80[wp->work_1].high_4)
                {
                    c = 0x80;
                }
                else
                {
                    c = ((wp->pos_38.pad - low) << 7) / wp->pos_38.pad;
                }
            }
            else
            {
                c = 0x80;
            }
            if (c < 0)
            {
                c = 0;
            }
            wp->color_40 = (c | 0x2000000) | (c << 8) | (c << 16);
            break;
        case 1:
            wp->value_44 += wp->value_46;
            wp->pos_38.pad += wp->value_44;
            if (wp->pos_38.pad <= 0)
            {
                wp->routine_0++;
                wp->pos_38.pad = 0;
                return;
            }
            low = D_80138EA0[wp->work_1].low_0;
            if (wp->value_44 <= 0 && low >= wp->pos_38.pad)
            {
                c = 0x60 - ((low - wp->pos_38.pad) << 7) / low;
            }
            else
            {
                c = 0x80;
            }
            if (c >= 0x100)
            {
                c = 0xFF;
            }
            if (c < 0)
            {
                c = 0;
            }
            wp->color_40 = (c | 0x2000000) | (c << 8) | (c << 16);
            break;
        case 2:
            wp->value_44 += wp->value_46;
            wp->pos_38.pad += wp->value_44;
            if (wp->value_44 <= 0)
            {
                wp->routine_0++;
                wp->pos_38.pad = 0;
                return;
            }
            if (D_80138EC0[wp->work_1].level_0 < wp->pos_38.pad)
            {
                wp->routine_2 += D_80138EC0[wp->work_1].step_2;
                if (wp->routine_2 <= 0x80)
                {
                    c = 0x80 - wp->routine_2;
                }
                else
                {
                    c = 0;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->color_40 = (c | 0x2000000) | (c << 8) | (c << 16);
            break;
        case 3:
            wp->pos_38.pad = (uint8)wp->work_3 * 2;
            if (wp->work_3 == 0)
            {
                wp->routine_0++;
                wp->pos_38.pad = 0;
                return;
            }
            c            = (uint8)wp->work_1;
            wp->color_40 = (c | 0x2000000) | (c << 8) | (c << 16);
            break;
    }
    if (wp->type & 0x20)
    {
        wp->pos_38.y -= 0x28;
    }
    wp->matrix.words[0]  = 0x1000;
    wp->matrix.words[1]  = 0;
    wp->matrix.words[2]  = 0x1000;
    wp->matrix.words[3]  = 0;
    wp->matrix.words[4]  = 0x1000;
    wp->matrix.words[5]  = 0;
    wp->matrix.words[6]  = 0;
    wp->matrix.words[7]  = 0;
    wp->matrix.m.m[0][0] = wp->matrix.m.m[1][1] = wp->matrix.m.m[2][2] = wp->pos_38.pad;
    RotMatrixY(++wp->routine_3 << 7, &wp->matrix.m);
}

void func_8012A6C4(void)
{
}

void func_8012A6CC(void)
{
}

void func_8012A6D4(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_8012A6F4(STAGE_OBJ *wp)
{
    D_80138F3C[wp->routine_0](wp);
}

void func_8012A730(STAGE_FX *wp)
{
    wp->w_24     = 0x20;
    wp->work_0   = -0x80;
    wp->mode_14  = 0x3D48002C;
    wp->color_18 = 0x2EC06060;
    wp->timer_D  = 0;
    wp->be_flag |= 0x22;
    if (wp->type != 0)
    {
        wp->frame_E = D_80138F18[0].frames_4;
        wp->u_22    = D_80138F18[wp->timer_D].u_0;
        wp->v_23    = D_80138F18[wp->timer_D].v_2;
    }
    else
    {
        wp->frame_E = D_80138F00[0].frames_4;
        wp->u_22    = D_80138F00[wp->timer_D].u_0;
        wp->v_23    = D_80138F00[wp->timer_D].v_2;
    }
    wp->routine_0 = 1;
    wp->routine_3 = 0;
}

void func_8012A824(STAGE_FX *wp)
{
    if (--wp->frame_E == 0)
    {
        if (wp->type != 0)
        {
            wp->w_24 += 8;
            wp->timer_D++;
            wp->frame_E = D_80138F18[wp->timer_D].frames_4;
            wp->u_22    = D_80138F18[wp->timer_D].u_0;
            wp->v_23    = D_80138F18[wp->timer_D].v_2;
        }
        else
        {
            wp->timer_D++;
            wp->frame_E = D_80138F00[wp->timer_D].frames_4;
            wp->u_22    = D_80138F00[wp->timer_D].u_0;
            wp->v_23    = D_80138F00[wp->timer_D].v_2;
        }
    }
    if ((uint8)wp->frame_E == 0x80)
    {
        wp->routine_0 = 2;
    }
}

void func_8012A964(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

// retail builds xy_8 before the uv words (loads y, then x) and keeps the products in a2; ours a3
void func_8012A984(ST1A_SHARDS *wp)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    ST1A_SHARD *rec;
    sint32 i;
    uint8 u0;
    uint8 v0;
    uint8 u1;
    uint8 v1;

    switch (wp->routine_0)
    {
        case 0:
            wp->time_28 = 0;
            wp->routine_0++;
            // fall through
        case 1:
            wp->time_28++;
            rec = D_801393A0[wp->type].list_0;
            for (i = 0; i < D_801393A0[wp->type].count_4; i++, rec++)
            {
                pos.x      = (rec->pos_0.x + rec->vel_8.x * wp->time_28) >> 4;
                pos.y      = (rec->pos_0.y + rec->vel_8.y * wp->time_28) >> 4;
                pos.z      = (rec->pos_0.z + rec->vel_8.z * wp->time_28) >> 4;
                pos.pad    = (rec->pos_0.pad + rec->vel_8.pad * wp->time_28) >> 4;
                u0         = D_80138F48[rec->tex_10].u;
                u1         = u0 + D_80138F48[rec->tex_10].w;
                v0         = D_80138F48[rec->tex_10].v;
                v1         = v0 + D_80138F48[rec->tex_10].h;
                p          = Billboard_get();
                p->code_4  = 0x2C808080 - rec->shade_11 * 0x80808;
                p->xy_8    = (uint16)pos.x | (pos.y << 16);
                p->z_10    = pos.z;
                p->uv_C    = (v0 << 8) | u0 | 0x3E400000;
                p->uv_14   = (v0 << 8) | u1 | 0x70000;
                p->uv_1C   = (v1 << 8) | u0;
                p->pad_20  = 0;
                p->uv_24   = (v1 << 8) | u1;
                p->size_18 = pos.pad;
            }
            break;
    }
}

void func_8012ABE0(ST1A_PUFF *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->be_flag |= TRANS;
            wp->routine_0++;
            // fall through
        case 1:
            if (wp->u_2C.owner->color_18 != 0)
            {
                wp->x_1C -= 2;
            }
            if (--wp->timer_D == 0 || wp->routine_0 == 2)
            {
                wp->timer_D = 0;
                wp->routine_0++;
            }
            wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
            wp->w_24 += wp->type_F;
            wp->y_1E += wp->value_28;
            break;
        case 2:
            func_80031988(wp);
            break;
    }
}

void func_8012AD08(ST1A_PUFF *wp)
{
    ST1A_PUFF *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = (ST1A_PUFF *)func_80031618();
        if (ep != NULL)
        {
            ep->be_flag    = MOVE;
            ep->id         = 0x21;
            ep->type       = 1;
            ep->flags      = wp->flags;
            ep->work_0     = 0;
            ep->timer_D    = (rand() & 7) * 2 - (sint8)(wp->timer_D - 0x40);
            ep->x_1C       = wp->x_1C + (rand() & 0xF);
            ep->y_1E       = wp->y_1E;
            ep->z_20       = wp->z_20 + (rand() & 0xF);
            ep->mode_14    = 0x3D48004E;
            ep->u_22       = (rand() & 3) * 32 + 0x20;
            ep->v_23       = 0;
            ep->w_24       = wp->frame_E;
            ep->type_F     = wp->type_F;
            ep->value_28   = wp->value_28;
            ep->u_2C.owner = wp;
            for (i = 0; i < wp->h_26; i++)
            {
                func_8012ABE0(ep);
            }
            wp->h_26      = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_8012AE60(ST1A_PUFF *wp)
{
    POLY_FT4 *p;

    switch (wp->routine_0)
    {
        case 0:
            p = *STAGE_PACKET_PTR;
            wp->x_1C += wp->value_28;
            wp->u_2C.rise += wp->value_30;
            wp->y_1E += wp->u_2C.rise >> 4;
            wp->h_26 += 0x80;
            if (wp->y_1E > 0x110 || wp->x_1C > 0x160)
            {
                wp->routine_0++;
                return;
            }
            setPolyFT4(p);
            p->x0    = wp->x_1C + ((rcos(wp->h_26) * D_801393C0[wp->work_0].w) >> 13);
            p->y0    = wp->y_1E + ((rsin(wp->h_26) * D_801393C0[wp->work_0].h) >> 13);
            p->x1    = wp->x_1C + ((rcos(wp->h_26 + 0x400) * D_801393C0[wp->work_0].w) >> 13);
            p->y1    = wp->y_1E + ((rsin(wp->h_26 + 0x400) * D_801393C0[wp->work_0].h) >> 13);
            p->x2    = wp->x_1C + ((rcos(wp->h_26 + 0xC00) * D_801393C0[wp->work_0].w) >> 13);
            p->y2    = wp->y_1E + ((rsin(wp->h_26 + 0xC00) * D_801393C0[wp->work_0].h) >> 13);
            p->x3    = wp->x_1C + ((rcos(wp->h_26 + 0x800) * D_801393C0[wp->work_0].w) >> 13);
            p->y3    = wp->y_1E + ((rsin(wp->h_26 + 0x800) * D_801393C0[wp->work_0].h) >> 13);
            p->u0    = D_801393C0[wp->work_0].u;
            p->v0    = D_801393C0[wp->work_0].v;
            p->u1    = p->u0 + D_801393C0[wp->work_0].w;
            p->v1    = p->v0;
            p->u2    = p->u0;
            p->v2    = p->v0 + D_801393C0[wp->work_0].h;
            p->u3    = p->u0 + D_801393C0[wp->work_0].w;
            p->v3    = p->v0 + D_801393C0[wp->work_0].h;
            p->clut  = 0x3E40;
            p->tpage = 7;
            setRGB0(p, 0x80, 0x80, 0x80);
            addPrim(&Disp_env_ptr->ot_74, p);
            ++*STAGE_PACKET_PTR;
            break;
        case 1:
            func_80031988(wp);
            break;
    }
}

void func_8012B284(ST1A_PUFF *wp)
{
    switch (wp->type)
    {
        case 0:
            if (wp->routine_0 != 2)
            {
                func_8012AD08(wp);
                return;
            }
            func_80031988(wp);
            return;
        case 1:
            func_8012ABE0(wp);
            return;
        case 2:
            func_8012AE60(wp);
            return;
    }
}

STAGE_FX *func_8012B320(STCOM_SVECTOR *pos, sint32 frame, sint32 type, sint32 count, sint32 count_28, uint8 attach, uint8 color)
{
    ST1A_PUFF *ep;
    sint32 i;

    ep = (ST1A_PUFF *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = MOVE;
        ep->id       = 0x21;
        ep->type     = 0;
        ep->color_18 = color;
        ep->work_0   = 0;
        ep->timer_D  = 0;
        ep->frame_E  = frame;
        ep->type_F   = type;
        ep->x_1C     = pos->x;
        ep->y_1E     = pos->y;
        ep->z_20     = pos->z;
        ep->h_26     = count;
        if (attach)
        {
            ep->flags |= 0x20;
        }
        else
        {
            ep->flags &= ~0x20;
        }
        ep->value_28 = count_28;
        for (i = 0; i < (sint16)count; i++)
        {
            func_8012AD08(ep);
        }
    }
    return (STAGE_FX *)ep;
}

// Saved registers differ: retail gives s0..s5 to arg2, x, y, arg3, arg4, arg5; GCC to arg3, arg2, x, y first.
STAGE_FX *func_8012B440(sint16 x, sint16 y, uint8 arg2, sint16 arg3, sint16 arg4, sint16 arg5)
{
    STAGE_FX *ep;

    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag    = MOVE;
        ep->id         = 0x21;
        ep->work_0     = arg2;
        ep->x_1C       = x;
        ep->type       = 2;
        ep->y_1E       = y;
        ep->u_28.count = (sint16)arg3;
        ep->h_26       = 0;
        ep->x_2C.value = (sint16)arg4;
        ep->y_30.value = (sint16)arg5;
    }
    return ep;
}
