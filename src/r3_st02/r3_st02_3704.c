#include "common.h"
#include "st02.h"

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
    Pos_Shadow_Trans(&wp->pos_38, 0x1F4, 0x200, 0);
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
