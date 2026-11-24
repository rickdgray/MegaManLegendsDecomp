#include "common.h"
#include "st1e.h"

void func_80102760(STAGE_OBJ *wp)
{
    D_80109904[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80109900[0]->id, 0x33, 0x37, 5));
}

void func_801027BC(STAGE_OBJ *wp)
{
    D_8010990C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80109908[0]->id, 0x33, 0x37, 5));
}

void func_80102818(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_80109900_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80109900[0] += count;
            func_80102760(wp);
        }
        else if (++D_80109904[0] == p->count)
        {
            D_80109900_S = p + 1;
            func_80102760(wp);
        }
    }
    p     = D_80109908_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80109908[0] += count;
            func_801027BC(wp);
        }
        else if (++D_8010990C[0] == p->count)
        {
            D_80109908_S = p + 1;
            func_801027BC(wp);
        }
    }
}

void func_80102940(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80109910.cue_0->u.end != 0xFF && D_80109910.cue_0->u.scene == scene->u_8.value_8 && D_80109910.cue_0->line == scene->value_1C)
    {
        D_80109900[0] = D_80105098[D_80109910.cue_0->index];
        func_80102760(wp);
        D_80109910.cue_0++;
    }
    if (D_80109910.cue_4->u.end != 0xFF && D_80109910.cue_4->u.scene == scene->u_8.value_8 && D_80109910.cue_4->line == scene->value_1C)
    {
        D_80109908[0] = D_801050EC[D_80109910.cue_4->index];
        func_801027BC(wp);
        D_80109910.cue_4++;
    }
    func_80102818(wp);
}

void func_80102A88(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    D_80109910.cue_0   = D_80105164;
    D_80109910.cue_4   = D_801051E8;
    wp->routine_0++;
}

void func_80102AFC(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 1, 0);
            wp->routine_2++;
            break;
        case 1:
            break;
        case 2:
            if (*wp->anim_98 == 0)
            {
                func_800322A8(wp, 2, 0);
                wp->routine_2++;
            }
            break;
        case 3:
            if (*wp->anim_98 == 0x22)
            {
                func_800322A8(wp, 3, 0x23);
                wp->routine_2++;
            }
            break;
        case 4:
            break;
    }
}

void func_80102BB8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_80102C04(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 4, 0);
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 == 0x2C)
            {
                func_80032304(wp, 3, 0x23);
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}

void func_80102C8C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_80102CD8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_80102D24(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        wp->routine_2++;
    }
}

void func_80102D70(STAGE_OBJ *wp)
{
    D_801052D4[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_80102940(wp);
}

void func_80102DE0(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80102A88(wp);
    }
    func_80102D70(wp);
    if (wp->routine_1 != 0 && wp->routine_1 != 5)
    {
        Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
    }
}

void func_80102E4C(ST1E_PANEL *wp)
{
    STAGE_XYZ *xyz;

    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->variant_3);
    wp->color_40 = 0x808080;
    xyz          = &D_801052EC[wp->variant_3];
    wp->pos_38.x = xyz->x;
    wp->pos_38.y = xyz->y;
    wp->pos_38.z = xyz->z;
    wp->routine_0++;
}

void func_80102ED8(ST1E_PANEL *wp)
{
    STCOM_FIXED_VECTOR scale;

    if (wp->routine_0 == 0)
    {
        func_80102E4C(wp);
    }
    wp->matrix.w[0] = 0x1000;
    wp->matrix.w[2] = 0x1000;
    wp->matrix.w[4] = 0x1000;
    wp->matrix.w[1] = 0;
    wp->matrix.w[3] = 0;
    wp->matrix.w[5] = 0;
    wp->matrix.w[6] = 0;
    wp->matrix.w[7] = 0;
    scale.z         = 0x200;
    scale.y         = 0x200;
    scale.x         = 0x200;
    ScaleMatrix(&wp->matrix.m, &scale);
    Pos_Shadow_Trans(&wp->pos_38, 0x32, 0x2AB, 0);
}

void func_80102F68(STAGE_OBJ *wp)
{
    D_801058DC[wp->routine_0](wp);
}

void func_80102FA4(ST1E_SCROLL *wp)
{
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->value_C   = 0;
    wp->value_D   = 0;
    wp->value_E   = 0;
    wp->value_F   = 0;
    wp->pos.frame = 0;
    wp->pos.line  = 0;
    wp->pos.count = 0;
}

void func_80102FD8(ST1E_SCROLL *wp)
{
    ST1E_SCROLL_POS *pos;
    sint16 line;
    sint16 hold;
    sint16 y;
    sint16 top;

    pos  = &wp->pos;
    line = wp->pos.line;
    hold = wp->pos.count;
    y    = 0x102 - wp->pos.frame % 18;
    while (line >= 0 && y >= -0x11)
    {
        top = y - hold * 18;
        func_8010320C(0, D_8010563C[line].ch[0], top);
        func_8010320C(1, D_8010563C[line].ch[1], top);
        func_8010320C(2, D_8010563C[line].ch[2], top);
        hold = D_8010563C[line - 1].hold;
        line--;
        y = top - 18;
    }
    if (++pos->frame % 18 == 0)
    {
        if (D_8010563C[pos->line].hold == 0)
        {
            pos->line++;
            pos->count = 0;
        }
        else if (++pos->count == D_8010563C[pos->line].hold + 1)
        {
            pos->line++;
            pos->count = 0;
        }
    }
    if (pos->line >= 0xA5)
    {
        wp->routine_0 = 2;
    }
}

void func_801031D8(STAGE_EFFECT *wp)
{
    STAGE_SCENE_BYTE(5)++;
    func_80031988(wp);
}

// Draws one glyph of a three-column text line. Each column writes all of its corner
// coordinates itself (jump2 merges the copies); xy holds x0 and then y + 0x10.
void func_8010320C(uint8 column, uint8 ch, sint16 y)
{
    POLY_FT4 *p;
    uint8 u0;
    uint8 v0;
    uint8 u1;
    sint16 x1;
    sint16 xy;

    if (ch != 0)
    {
        u0                = D_80105330[ch].u0;
        v0                = D_80105330[ch].v0;
        u1                = D_80105330[ch].u1;
        p                 = (*STAGE_PACKET_PTR)++;
        *(u_long *)p      = 0x09000000;
        *(u_long *)&p->r0 = 0x2C808080;
        p->clut           = 0x7C00;
        p->tpage          = D_80105330[ch].tpage;
        p->u0             = u0;
        p->v0             = v0;
        p->u1             = u1;
        p->v1             = v0;
        p->u2             = u0;
        p->v2             = v0 + 0xF;
        p->u3             = u1;
        p->v3             = v0 + 0xF;
        switch (column)
        {
            case 0:
                xy    = 0x90 - (u1 - u0);
                p->x0 = xy;
                p->x2 = xy;
                x1    = 0x90;
                xy    = y + 0x10;
                p->y0 = y;
                p->x1 = x1;
                p->y1 = y;
                p->y2 = xy;
                p->x3 = x1;
                p->y3 = xy;
                break;
            case 1:
                xy    = 0x20;
                p->x0 = xy;
                p->x2 = xy;
                x1    = 0x11F;
                xy    = y + 0x10;
                p->y0 = y;
                p->x1 = x1;
                p->y1 = y;
                p->y2 = xy;
                p->x3 = x1;
                p->y3 = xy;
                break;
            case 2:
            default:
                xy    = 0xB0;
                p->x0 = xy;
                p->x2 = xy;
                x1    = 0x12F;
                xy    = y + 0x10;
                p->y0 = y;
                p->x1 = x1;
                p->y1 = y;
                p->y2 = xy;
                p->x3 = x1;
                p->y3 = xy;
                break;
        }
        addPrim(&Disp_env_ptr->ot_78, p);
    }
}
