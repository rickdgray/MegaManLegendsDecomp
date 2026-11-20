#include "common.h"
#include "st05.h"

void func_80124E28(ST05_PROP *wp, sint32 scale)
{
    STCOM_FIXED_VECTOR v;

    RotMatrixYXZ(&wp->rotation, &wp->draw_88.matrix_4.m);
    v.x = (sint16)scale;
    v.y = (sint16)scale;
    v.z = (sint16)scale;
    ScaleMatrix(&wp->draw_88.matrix_4.m, &v);
}

void func_80124E88(ST05_PROP *wp)
{
    sint16 y;

    wp->flags_0 |= 6;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    y                                                = func_80048E6C(wp);
    wp->position.y                                   = y;
    wp->position_fixed.y = wp->position_fixed_prev.y = y << 16;
    wp->position_prev                                = wp->position;
    wp->draw_88.pos_24                               = wp->position;
    wp->rotation.x                                   = 0;
    *(sint32 *)&wp->rotation.z                       = 0; // z and pad
    wp->velocity.words[0]                            = 0;
    wp->velocity.words[1]                            = 0;
    *(sint32 *)&wp->turn_64                          = 0;
    wp->value_70                                     = 0;
    wp->value_74                                     = 0;
    wp->rotation_prev                                = wp->rotation;
    wp->hit_BC                                       = 0;
    func_80124E28(wp, 0x200);
    Model_work_init(wp, &wp->variant_3);
    wp->color_B4 = 0x808080;
    wp->routine_0++;
}

void func_80124F9C(ST05_PROP *wp)
{
    ST05_LINK *link;
    STCOM_SVECTOR pos;
    uint8 c;
    uint16 f;

    link = func_80036294(wp->value_E);
    if (wp->variant_3 < 4)
    {
        if (link->value_C < wp->value_F)
        {
            wp->color_B4 = 0x404040;
        }
        else if (link->value_C == wp->value_F)
        {
            f = STAGE_FRAME;
            if (f & 0x10)
            {
                c = ((f & 0xF) * 8) | 0x80;
            }
            else
            {
                c = -0x10 - (f & 0xF) * 8;
            }
            wp->color_B4 = c | (c << 8) | (c << 16);
        }
        else
        {
            wp->color_B4 = 0x808080;
        }
        func_80051B68(wp, 1, -1, 0);
    }
    else if (wp->hit_BC & 0x22000000)
    {
        Sound_call2(0x168, &Player_work.position);
        link->timer_D = 0x1E;
        wp->routine_1 = 0;
        wp->routine_0++;
    }
    else
    {
        pos = wp->position;
        pos.y -= 0x32;
        func_800341BC(&pos, 0x32, 0, 0x8000, wp->value_1, &wp->hit_BC, 0x8800000, 0, 0x80);
        wp->hit_BC = 0;
    }
}

void func_80125124(ST05_PROP *wp)
{
    wp->velocity.v.z = -(rcos(STCOM_PLAYER_WORK_PTR->rotation.y) * 0x600) >> 12;
    wp->velocity.v.x = -(rsin(STCOM_PLAYER_WORK_PTR->rotation.y) * 0x600) >> 12;
    wp->velocity.v.y = -0x640;
    wp->accel_4C.y   = 0x80;
    if ((wp->hit_BC & 0x20000000) || STAGE_PL.value_44 > 0x258)
    {
        wp->velocity.v.x <<= 1;
        wp->velocity.v.z <<= 1;
    }
    wp->routine_1++;
}

void func_801251FC(ST05_PROP *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->rotation.x += 0x200;
    wp->rotation.y += 0x100;
    func_80124E28(wp, 0x200);
    wp->velocity.v.y += wp->accel_4C.y;
    wp->position_fixed.x += wp->velocity.v.x << 12;
    wp->position_fixed.z += wp->velocity.v.z << 12;
    wp->position_fixed.y += wp->velocity.v.y << 12;
    func_80030150(&wp->position_fixed, &wp->position);
    wp->draw_88.pos_24 = wp->position;
    if (func_8004B414(wp) != 0)
    {
        wp->velocity.v.x = 0;
        wp->velocity.v.y = 0;
        wp->velocity.v.z = 0;
        wp->accel_4C.x   = 0;
        wp->accel_4C.y   = 0;
        wp->accel_4C.z   = 0;
        wp->routine_0++;
    }
}

void func_80125354(STAGE_OBJ *wp)
{
    D_801322A0[wp->routine_1](wp);
}

void func_80125390(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}

void func_801253B0(STAGE_OBJ *wp)
{
    D_801322A8[wp->routine_0](wp);
}

void func_801253EC(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_80125400(ST05_PROP *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    pl->flags_0 &= ~2;
    wp->position = Player_work.position;
    wp->flags_0 |= 6;
    wp->draw_88.pos_24         = wp->position;
    wp->rotation.x             = 0;
    *(sint32 *)&wp->rotation.z = 0; // z and pad
    wp->velocity.words[0]      = 0;
    wp->velocity.words[1]      = 0;
    *(sint32 *)&wp->turn_64    = 0;
    wp->value_70               = 0;
    wp->value_74               = 0;
    wp->hit_BC                 = 0;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    func_80124E28(wp, 0x100);
    wp->kind_2 = 4;
    Model_work_init(wp, &wp->variant_3);
    wp->kind_2   = 0x1F;
    wp->color_B4 = 0x808080;
    wp->routine_0++;
}

void func_8012551C(ST05_PROP *wp)
{
    wp->rotation = Player_work.rotation;
    wp->position = Player_work.position;
    func_80124E28(wp, 0x100);
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->draw_88.pos_24                               = wp->position;
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80125600(STAGE_OBJ *wp)
{
    D_801322B8[wp->routine_0](wp);
}

void func_8012563C(STAGE_OBJ *wp)
{
    D_801322C4[wp->u_C.b.byte_C](wp);
}

void func_80125678(ST05_OBJ *wp)
{
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    wp->rotation_prev       = wp->rotation;
    D_801323AC[wp->routine_0](wp);
    wp->value_BC = 0;
}

void func_80125724(ST05_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->flags_0 |= 6;
    wp->position.x       = D_8013231C[wp->variant_3].x;
    wp->position.y       = D_8013231C[wp->variant_3].y;
    wp->position.z       = D_8013231C[wp->variant_3].z;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->accel_4C.x       = 0x10;
    wp->turn_64          = 0x40;
    wp->velocity.v.z     = 0;
    wp->velocity.v.y     = 0;
    wp->velocity.v.x     = 0;
    wp->accel_4C.z       = 0;
    wp->accel_4C.y       = 0;
    wp->rotation.x       = 0;
    wp->rotation.z       = 0;
    wp->value_CC         = 0;
    wp->data_78          = NULL;
    wp->position.y       = func_8004920C(&wp->position);
    wp->draw_88.pos_24   = wp->position;
    RotMatrix(&wp->rotation, &wp->draw_88.matrix_4.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->draw_88.matrix_4.m, &scale);
    wp->color_B4 = 0x808080;
    Model_work_init(wp, &wp->variant_3);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80125880(ST05_PROP *wp)
{
    ST05_DRAW *draw;
    STCOM_PL_WORK *pl;
    uint16 angle;
    sint32 msg;
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR scale;
    sint32 dy;

    D_801323C0[wp->routine_1](wp);
    pl   = &Player_work;
    draw = &wp->draw_88;
    if (wp->routine_3 != 0 && wp->variant_3 == 0)
    {
        func_80125FBC(wp);
        func_80125FF8(wp);
    }
    else
    {
        if ((wp->hit_BC & 0x28000000) == 0x08000000 && (wp->hit_BC & 0xFFFFFF))
        {
            wp->value_CC += 0x100;
            if (!(Moji_flag & 0x08000000))
            {
                if (wp->variant_3 == 0)
                {
                    msg         = D_801323A0[wp->value_F];
                    wp->value_F = (wp->value_F + 1) % 6;
                    if (--wp->value_C == 0)
                    {
                        msg            = 0;
                        wp->rotation.z = 0;
                        wp->routine_3  = 1;
                    }
                }
                else
                {
                    msg         = D_801323A8[wp->value_F];
                    wp->value_F = (wp->value_F + 1) % 4;
                    func_8001E3F0(0x1C);
                }
                if (msg != 0)
                {
                    MojiTaskExec2(0, msg);
                }
            }
        }
        if (wp->value_E == 0)
        {
            if (wp->hit_BC & 0x02000000)
            {
                dy = pl->position.y - wp->position.y;
                if (STCOM_ABS(dy) < 0x10)
                {
                    if (wp->variant_3 == 0 && --wp->value_C == 0)
                    {
                        wp->rotation.z = 0;
                        wp->routine_3  = 1;
                    }
                    else
                    {
                        wp->value_E = 0x18;
                    }
                    Sound_call2(0x189, &wp->position);
                }
            }
        }
        else
        {
            if (wp->value_E >= 9)
            {
                wp->rotation.y += D_80132390[wp->value_E & 7];
                func_801267B0((STAGE_OBJ *)wp, 0);
            }
            wp->value_E--;
        }
    }
    Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    draw->pos_24 = wp->position;
    angle        = wp->rotation.y;
    wp->rotation.y += wp->value_CC & 0xFFF;
    RotMatrixYXZ(&wp->rotation, &draw->matrix_4.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&draw->matrix_4.m, &scale);
    if (wp->turn_64 < wp->value_CC)
    {
        wp->value_CC -= wp->turn_64;
    }
    else
    {
        wp->value_CC = 0;
    }
    wp->rotation.y = angle;
    func_80051B68(wp, 1, -1, 0x1000008);
    angle = wp->rotation.y;
    pos   = wp->position;
    pos.y -= 0x50;
    pos.x += (rsin((sint16)angle) * 0) >> 12;
    pos.z += (rcos((sint16)angle) * 0) >> 12;
    func_800341BC(&pos, 0x80, 0, 0x8000, wp->value_1, &wp->hit_BC, 0x8880000, 0, 0x80);
    wp->hit_BC = 0;
}

void func_80125C54(STAGE_OBJ *wp)
{
    func_80052528(wp);
    Close_SHL_WORK(wp);
}

void func_80125C84(void)
{
}

void func_80125C8C(ST05_OBJ *wp)
{
    STCOM_SVECTOR pos;
    sint16 angle;

    func_80051B68(wp, 1, -1, 0);
    angle = wp->rotation.y;
    pos   = wp->position;
    pos.y -= 0x50;
    pos.x += (rsin(angle) * 0) >> 12; // a zero offset along the facing
    pos.z += (rcos(angle) * 0) >> 12;
    func_800341BC(&pos, 0x80, 0, 0x8000, wp->value_1, &wp->value_BC, 0x8880000, 0, 0x80);
    wp->value_BC = 0;
}

void func_80125D5C(STAGE_OBJ *wp)
{
    wp->routine_1 = 1;
}

void func_80125D68(ST05_PROP *wp)
{
    STCOM_SVECTOR target;
    uint8 *row;

    wp->velocity.v.x += wp->accel_4C.x;
    if (wp->velocity.v.x > 0x300)
    {
        wp->velocity.v.x = 0x300;
    }
    row      = D_801322E4[wp->routine_2];
    target.x = D_801322CC[row[0]][0] << 8;
    target.z = D_801322CC[row[0]][1] << 8;
    target.y = wp->position.y;
    wp->rotation.y =
        (wp->rotation.y + Muku(&wp->position, &target, wp->rotation.y, wp->turn_64)) &
        0xFFF;
    if ((sint16)func_80125F34(wp) != 0)
    {
        wp->routine_1 = 2;
    }
}

void func_80125E58(ST05_PROP *wp)
{
    STCOM_SVECTOR target;
    uint8 *row;
    sint32 turn;

    row            = D_801322E4[wp->routine_2];
    target.x       = D_801322CC[row[3]][0] << 8;
    target.z       = D_801322CC[row[3]][1] << 8;
    target.y       = wp->position.y;
    turn           = Muku(&wp->position, &target, wp->rotation.y, wp->turn_64);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0)
    {
        if (++wp->routine_2 >= 0xE)
        {
            wp->routine_2 = 0;
        }
        wp->routine_1 = 1;
    }
}

// Builtin abs() (bgez with an unfilled delay slot). The coordinates are read into locals
// before the first test, as retail loads them.
sint32 func_80125F34(STAGE_OBJ *wp)
{
    sint32 point;
    sint32 x;
    sint32 z;
    sint32 px;
    sint32 pz;

    point = D_801322E4[wp->routine_2][0];
    z     = (sint16)(D_801322CC[point][1] << 8);
    x     = (sint16)(D_801322CC[point][0] << 8);
    px    = wp->position.x;
    pz    = wp->position.z;
    if (abs(x - px) < 0x200 && abs(z - pz) < 0x200)
    {
        return 1;
    }
    return 0;
}

void func_80125FBC(STAGE_OBJ *wp)
{
    D_801323CC[wp->routine_3](wp);
}

void func_80125FF8(STAGE_OBJ *wp)
{
    D_801323E4[wp->u_C.b.byte_C](wp);
}

void func_80126034(void)
{
}

void func_8012603C(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    temp_v0 = (sint16)wp->value_44.words.fraction;
    if (temp_v0 < 0x20)
    {
        wp->value_44.words.fraction = 0;
        wp->value_4C.words.fraction = 0;
        wp->routine_3++;
    }
    else
    {
        wp->value_44.words.fraction = temp_v0 - 0x20;
    }
    if ((sint16)wp->value_44.words.fraction < 0x100)
    {
        if (temp_v0 >= 0x101)
        {
            Sound_call2(0x18B, &wp->position);
        }
    }
    func_801267B0(wp, 1);
}

void func_801260D0(ST05_OBJ *wp)
{
    STAGE_OBJ *part;

    if ((wp->value_BC & 0x08FFFFFF) == 0x08000000)
    {
        part                        = wp->u_B8.part;
        part->value_4C.half[0]      = 0;
        part->value_44.half[0]      = 0;
        wp->u_B8.part->routine_0    = 4;
        wp->value_44.words.fraction = 0x300;
        wp->value_50                = 0;
        wp->value_4C.words.integer  = 0;
        wp->value_4C.words.fraction = 0;
        wp->routine_3++;
        Sound_call2(0x18A, &wp->position);
    }
    func_801267B0((STAGE_OBJ *)wp, 1);
}

void func_80126160(ST05_OBJ *wp)
{
    ST05_OBJ *obj;
    STCOM_EFFECT *mark;
    STCOM_EFFECT *fx;

    if (wp->value_44.half[0] < 0x20 || func_8004B414(wp) != 0)
    {
        obj                 = func_8001EB98(&D_80132354[0]);
        obj->position       = wp->position;
        obj->position_fixed = wp->position_fixed;
        obj->rotation       = wp->rotation;
        obj->rotation.y += STAGE_FRAME & 0x1FF;
        obj->value_44.words.integer = -0xC0;
        obj                         = func_8001EB98(&D_80132354[0]);
        obj->position               = wp->position;
        obj->position_fixed         = wp->position_fixed;
        obj->rotation               = wp->rotation;
        obj->rotation.y -= STAGE_FRAME & 0x1FF;
        obj->value_44.words.integer = -0xC0;
        mark                        = func_8001EB98(&D_80132354[1]);
        mark->sprite.position       = wp->position;
        mark->value_F               = (uint8)wp->rotation.y >> 6;
        obj                         = func_8001EB98(&D_80132354[2]);
        obj->position               = wp->u_B8.part->position;
        obj->position_fixed         = wp->u_B8.part->position_fixed;
        obj->rotation               = wp->u_B8.part->rotation;
        Obj_pos_set(obj, 0, 0, -0xC80);
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0           = 5;
            fx->kind_2            = 0x80;
            fx->variant_3         = 0x41;
            fx->sprite.position   = wp->position;
            fx->sprite.position.y = wp->position.y - 0x64;
            wp->u_B8.fx           = fx;
            wp->value_44.half[0]  = 0;
            wp->flags_0 &= ~2;
            wp->routine_3++;
        }
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + 0x40) & 0xFFF;
        wp->value_44.half[0] -= 0x20;
    }
    func_801267B0((STAGE_OBJ *)wp, 1);
}

void func_80126440(ST05_OBJ *wp)
{
    if (*wp->u_B8.flag == 0)
    {
        D_800A395C = 1;
        func_80039820();
        wp->routine_3++;
    }
}

void func_8012649C(STAGE_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (!func_8003A13C())
    {
        func_80042314(pl);
        pl->flags_0 |= 2;
        wp->routine_0 = 3;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->routine_3 = 0;
    }
}

void func_80126508(STAGE_OBJ *wp)
{
    if (func_80042238(&Player_work))
    {
        Player_work.routine_0 = 3;
        Player_work.routine_1 = 0;
        Player_work.value_C   = 0;
        wp->u_C.b.byte_C++;
    }
}

void func_8012656C(STAGE_OBJ *wp)
{
    ST05_PL_VIEW *pl;
    STCOM_SVECTOR size;
    STCOM_FIXED_VECTOR out;

    pl            = &ST05_PL;
    D_800C0F9A    = 0;
    D_800C0F96[0] = 0;
    switch (ST05_PL.step_C)
    {
        case 0:
            pl->routine_1++;
            pl->step_C++;
            break;
        case 1:
            pl->flags_bd |= 0x20;
            pl->step_C++;
            break;
        case 2:
            size.x = 2;
            size.y = 9;
            size.z = 2;
            if (func_80030604(wp, pl, &size, &out) & 1)
            {
                pl->step_C    = 10;
                D_800C0F96[0] = D_800C0F9A = pl->pad_128 | pl->pad_138;
            }
            else
            {
                pl->step_C    = 20;
                D_800C0F96[0] = D_800C0F9A = pl->pad_12A | pl->pad_138;
            }
            break;
        case 10:
            D_800C0F96[0] = D_800C0F9A = pl->pad_128 | pl->pad_138;
            pl->step_C++;
            goto count;
        case 20:
            D_800C0F96[0] = D_800C0F9A = pl->pad_12A | pl->pad_138;
            pl->step_C++;
            // fall through
        case 11:
        case 21:
        count:
            pl->count_D++;
            break;
    }
    if (pl->count_D >= 0xB)
    {
        *(sint32 *)&pl->step_C = 0;
        wp->u_C.b.byte_C++;
    }
}

void func_801266F0(ST05_OBJ *wp)
{
    if (wp->routine_3 >= 4)
    {
        func_8001E6C0(0, 0, 0);
        Sce_camera_work.pos_10 = wp->position.x << 16;
        Sce_camera_work.pos_14 = (wp->position.y - 0x12C) << 16;
        Sce_camera_work.pos_18 = wp->position.z << 16;
        Sce_camera_work.rot_40 = (wp->rotation.y + 0x600) << 16;
        Sce_camera_work.rot_44 = 0x01000000;
        Sce_camera_work.rot_48 = 0x03000000;
        wp->u_C.b.byte_C++;
    }
}

void func_801267B0(STAGE_OBJ *wp, uint8 kind)
{
    STCOM_EFFECT *fx;
    STCOM_PL_WORK *pl;
    sint16 dx;
    sint16 dz;

    pl = &Player_work;
    if (wp->u_C.b.byte_D != 0)
    {
        wp->u_C.b.byte_D--;
        return;
    }
    fx = func_80031618();
    if (fx != NULL)
    {
        if (kind == 0)
        {
            dx = Player_work.position.x - wp->position.x;
            if (dx >> 4)
            {
                if (dx < 0)
                {
                    dx = -100;
                }
                else
                {
                    dx = 100;
                }
            }
            dz = pl->position.z - wp->position.z;
            if (dz >> 4)
            {
                if (dz < 0)
                {
                    dz = -100;
                }
                else
                {
                    dz = 100;
                }
            }
            fx->flags_0         = 3;
            fx->kind_2          = 0x83;
            fx->variant_3       = 0;
            fx->sprite.pos_8[0] = wp->position.x + dx;
            fx->sprite.pos_8[1] = wp->position.y - 0x50;
            fx->sprite.pos_8[2] = wp->position.z + dz;
            wp->u_C.b.byte_D    = 2;
        }
        else
        {
            fx->flags_0         = 1;
            fx->kind_2          = 0xB;
            fx->variant_3       = 3;
            fx->value_C         = 0;
            fx->value_D         = 0;
            fx->timer_E         = 0x14;
            fx->value_F         = 8;
            fx->sprite.pos_8[0] = wp->position.x;
            fx->sprite.pos_8[1] = wp->position.y - 0x50;
            fx->sprite.pos_8[2] = wp->position.z - 0x28;
            fx->routine_1       = 4;
            wp->u_C.b.byte_D    = 8;
        }
    }
}

void func_80126940(STAGE_OBJ *wp)
{
    D_80132400[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_80126990(ST05_SHL *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR v;

    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = D_801323F4;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    if (wp->type_3 & 0x40)
    {
        rot.x = wp->rot_x;
    }
    else
    {
        func_800354E0(wp->bit_d);
        rot.x = func_80039B80();
    }
    rot.y = wp->rot_y & 0xFFF;
    rot.z = 0;
    if (wp->type_3 & 0x40)
    {
        rot.x += ((rand() & 7) - 4) * 2;
        rot.y += ((rand() & 7) - 4) * 2;
    }
    else
    {
        switch (ST05_PL_SBYTE(0x508))
        {
            case 0:
                rot.x += ((rand() & 3) - 2) * 2;
                rot.y += ((rand() & 3) - 2) * 2;
                break;
            case 1:
                rot.x += ((rand() & 7) - 4) * 2;
                rot.y += ((rand() & 7) - 4) * 2;
                break;
            case 2: // shares default; listing it gives retail's compare tree
            default:
                rot.x += ((rand() & 0xF) - 8) * 2;
                rot.y += ((rand() & 0xF) - 8) * 2;
                break;
        }
    }
    RotMatrixYXZ(&rot, &wp->mtx_8c);
    v.y = 0x1000;
    v.z = 0x1000;
    v.x = 0x1000;
    ScaleMatrix(&wp->mtx_8c, &v);
    rot.x = 0;
    rot.y = 0;
    rot.z = -0x1000;
    ApplyMatrix(&wp->mtx_8c, &rot, &v);
    if (!(wp->type_3 & 0x40) && ST05_PL_SBYTE(0x507) >= 3)
    {
        wp->vel.x = (uint32)(v.x * 15) >> 1;
        wp->vel.y = (uint32)(v.y * 15) >> 1;
        wp->vel.z = (uint32)(v.z * 15) >> 1;
    }
    else
    {
        wp->vel.x = (uint32)(v.x * 25) >> 2;
        wp->vel.y = (uint32)(v.y * 25) >> 2;
        wp->vel.z = (uint32)(v.z * 25) >> 2;
    }
    wp->ax     = 0;
    wp->ay     = 0;
    wp->az     = 0;
    wp->hit_7c = 0;
    if (wp->type_3 & 0x40)
    {
        wp->fpos.v.x += wp->vel.x * 0x1C0;
        wp->fpos.v.y += wp->vel.y * 0x1C0;
        wp->fpos.v.z += wp->vel.z * 0x1C0;
    }
    wp->mpos.x = wp->pos.x = wp->fpos.f.x.words.integer;
    wp->mpos.y = wp->pos.y = wp->fpos.f.y.words.integer;
    wp->mpos.z = wp->pos.z = wp->fpos.f.z.words.integer;
    wp->old_fpos           = wp->fpos;
    wp->old_pos            = wp->pos;
    wp->color_b4           = 0x02808080;
    wp->kind_2             = 0x82;
    Model_work_init(wp, 0);
    wp->kind_2  = 0x2E;
    wp->timer_b = func_80037634(&Player_work, 2);
    wp->routine_0++;
    func_80127054(wp, 0);
    func_80126F10(wp);
    Sound_call2(0x120, &wp->pos);
}

void func_80126D98(STAGE_SHOT *wp)
{
    if (func_80037694(wp, 0) || wp->hit_7c)
    {
        if (wp->type_3 & 0x40)
        {
            Close_SHL_WORK(wp);
        }
        else
        {
            func_80031930(wp);
        }
        func_80127054(wp, 1);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    if (wp->timer_b-- != 0)
    {
        wp->fpos.w.x += wp->vel.x << 8;
        wp->fpos.w.y += wp->vel.y << 8;
        wp->fpos.w.z += wp->vel.z << 8;
        wp->draw_pos.x = wp->pos.x = wp->fpos.h.x;
        wp->draw_pos.y = wp->pos.y = wp->fpos.h.y;
        wp->draw_pos.z = wp->pos.z = wp->fpos.h.z;
    }
    else
    {
        if (wp->type_3 & 0x40)
        {
            Close_SHL_WORK(wp);
        }
        else
        {
            func_80031930(wp);
        }
        return;
    }
    func_80126F10(wp);
}

void func_80126F10(STAGE_SHOT *wp)
{
    STCOM_SVECTOR p;
    sint32 flags;

    flags = func_800375D4(&Player_work, 2);
    p.x   = wp->pos.x * 2 - wp->old_pos.x;
    p.y   = wp->pos.y * 2 - wp->old_pos.y;
    p.z   = wp->pos.z * 2 - wp->old_pos.z;
    if (STAGE_PL.value_171 == 0)
    {
        flags = 0x1000;
    }
    if (wp->type_3 & 0x40)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0xA000, wp->value_1, &wp->col_c4, 0x8000005,
                      0, 0x80);
    }
    else if (wp->index_c)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x6000, wp->value_1, &wp->col_c4,
                      flags | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x4000, wp->value_1, &wp->col_c4,
                      flags | 0x8000000, 0, 0x80);
    }
}

void func_80127054(STAGE_SHOT *wp, sint32 arg)
{
    STAGE_SHOT_FX *fx;

    fx = (STAGE_SHOT_FX *)func_80031618();
    if (fx)
    {
        fx->routine_0 = 1;
        fx->kind_2    = 0x85;
        fx->x_1c      = wp->pos.x;
        fx->y_1e      = wp->pos.y;
        fx->z_20      = wp->pos.z;
        fx->vx_30     = wp->vel.x;
        fx->vy_32     = wp->vel.y;
        fx->vz_34     = wp->vel.z;
        if (wp->type_3 == 0x40)
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type_3 == 0x41)
        {
            fx->value_40 = (wp->rot_y - 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type_3 == 0x42)
        {
            fx->value_40 = 0xFFFF;
            fx->flag_3   = arg + 0x10;
        }
        else
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg;
        }
    }
}

void func_80127154(STAGE_OBJ *wp)
{
    D_80132408[wp->routine_0](wp);
}

void func_80127190(ST05_EVENT *wp)
{
    ST05_MODEL *model;

    model = (ST05_MODEL *)func_8003AC24(0x50000);
    if (model == NULL)
    {
        Close_EVE_WORK(wp);
        return;
    }
    model = (ST05_MODEL *)((uint32)model & 0xFFFFFF);
    wp->u_8.routine_0++;
    D_80137F98      = model->part_18[0];
    D_80137F9C      = model->part_18[1];
    wp->color_1C[0] = model->part_18[0]->color_24;
    wp->color_1C[1] = model->part_18[1]->color_24;
}

void func_80127224(ST05_GLOW_EV *wp)
{
    uint32 *colors;
    uint32 a;
    uint32 b;
    sint32 i;

    for (i = 0; i < 2; i++)
    {
        colors = wp->colors_1C[i];
        a      = colors[0];
        b      = colors[1];
        a += 0x10001;
        b += 0x10001;
        if (a > 0xC0C0FEBF)
        {
            a = 0xC080FE80;
            b = 0xC0BFFEBF;
        }
        colors[0] = a;
        colors[1] = b;
        colors[2] = a;
        colors[3] = b;
        colors[4] = a;
        colors[5] = b;
        colors[6] = a;
        colors[7] = b;
    }
}

void func_801272A0(void)
{
}

void func_801272A8(void)
{
}
