#include "common.h"
#include "st1a.h"

void func_80120FEC(STAGE_OBJ *wp)
{
    D_801330DC[wp->routine_0](wp);
}

void func_80121028(ST1A_PIECES *wp)
{
    sint32 i;

    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->work_3    = 0;
    wp->be_flag |= 0x46;
    func_80121164(wp);
    wp->color_B4 = 0x02202020;
    Model_work_init(wp, NULL);
    for (i = 15; i >= 0; i--)
    {
        ((uint32 *)wp->piece_CC)[i] = 0;
    }
    wp->value_78 = (sint32)D_801330D0;
    func_80121418(wp);
}

void func_801210B8(ST1A_PIECES *wp)
{
    sint32 v;
    sint8 f;

    f          = wp->work_3;
    wp->work_3 = (f < 0x40) ? f + 8 : 0x40;
    if (wp->work_2 != 0)
    {
        Close_SHL_WORK(wp);
        return;
    }
    v = func_80121710(wp);
    if (v != 0)
    {
        wp->work_3 = v;
    }
    if (func_801218D0(wp))
    {
        wp->color_B4 = 0x02404040;
    }
    else
    {
        wp->color_B4 = 0x02202020;
    }
    func_80121164(wp);
    func_80121418(wp);
}

void func_80121164(ST1A_PIECES *wp)
{
    STCOM_MATRIX m;
    STCOM_FIXED_VECTOR v;
    STCOM_SVECTOR rot;
    STCOM_SVECTOR pos;
    ST1A_COPY_SRC *owner;

    owner = func_80036294(wp->id_C);
    m     = owner->matrix_8C;
    pos   = owner->position;
    // A cast word store (not struct memory to GCC), so the frame counter load stays after it
    *(sint32 *)&wp->matrix_8C.m.m[0][0] = 0x1000;
    wp->matrix_8C.w[1]                  = 0;
    wp->matrix_8C.w[2]                  = 0x1000;
    wp->matrix_8C.w[3]                  = 0;
    wp->matrix_8C.w[4]                  = 0x1000;
    wp->matrix_8C.m.t[0]                = 0;
    wp->matrix_8C.m.t[1]                = 0;
    wp->matrix_8C.m.t[2]                = 0;
    rot.x                               = 0x400;
    rot.y                               = 0;
    rot.z                               = (STAGE_FRAME & 0xF) << 8;
    RotMatrixYXZ(&rot, &wp->matrix_8C.m);
    v.x = v.y = v.z = 0x1000;
    ScaleMatrix(&wp->matrix_8C.m, &v);
    MulMatrix2(&m, &wp->matrix_8C.m);
    rot.x = 0;
    rot.y = 0;
    rot.z = -0x1000;
    ApplyMatrix(&wp->matrix_8C.m, &rot, &v);
    wp->velocity.x         = v.x * 15;
    wp->velocity.y         = v.y * 15;
    wp->velocity.z         = v.z * 15;
    wp->position_fixed.v.x = (pos.x << 16) + (wp->velocity.x << 8);
    wp->position_fixed.v.y = (pos.y << 16) + (wp->velocity.y << 8);
    wp->position_fixed.v.z = (pos.z << 16) + (wp->velocity.z << 8);
    wp->position_AC.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->position_AC.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->position_AC.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    wp->position_fixed_prev            = wp->position_fixed.v;
    wp->position_prev                  = wp->position;
    wp->velocity.x                     = (uint32)(v.x * 47) >> 1;
    wp->velocity.y                     = (uint32)(v.y * 47) >> 1;
    wp->velocity.z                     = (uint32)(v.z * 47) >> 1;
    v.x = v.y = 0x1400;
    v.z       = wp->work_3 << 6;
    ScaleMatrix(&wp->matrix_8C.m, &v);
}

void func_80121418(ST1A_PIECES *wp)
{
    STCOM_FIXED_VECTOR step;
    STCOM_SVECTOR pos;
    STCOM_SVECTOR prev;
    uint8 i;
    uint8 n;

    step.x = wp->velocity.x << 8;
    step.y = wp->velocity.y << 8;
    step.z = wp->velocity.z << 8;
    for (i = 0; i < wp->work_3 / 8; i++)
    {
        n      = i * 8 + 6;
        pos.x  = (wp->position_fixed.v.x + step.x * n) >> 16;
        pos.y  = (wp->position_fixed.v.y + step.y * n) >> 16;
        pos.z  = (wp->position_fixed.v.z + step.z * n) >> 16;
        n      = i * 8 + 1;
        prev.x = (wp->position_fixed.v.x + step.x * n) >> 16;
        prev.y = (wp->position_fixed.v.y + step.y * n) >> 16;
        prev.z = (wp->position_fixed.v.z + step.z * n) >> 16;
        func_8003430C(&pos, 0x48, &prev, 0x48, 0x200, 0xA000, wp->work_id, (uint32 *)wp->piece_CC + i, 0x9000030, 0, 0x80);
        (wp->piece_CC + i)->words[0] = 0;
        (wp->piece_CC + i)->words[1] = 0;
    }
    if ((wp->work_3 & 7) && i < 8)
    {
        n      = i * 8 + wp->work_3 % 8;
        pos.x  = (wp->position_fixed.v.x + step.x * n) >> 16;
        pos.y  = (wp->position_fixed.v.y + step.y * n) >> 16;
        pos.z  = (wp->position_fixed.v.z + step.z * n) >> 16;
        n      = i * 8;
        prev.x = (wp->position_fixed.v.x + step.x * n) >> 16;
        prev.y = (wp->position_fixed.v.y + step.y * n) >> 16;
        prev.z = (wp->position_fixed.v.z + step.z * n) >> 16;
        func_8003430C(&pos, 0x48, &prev, 0x48, 0x200, 0xA000, wp->work_id, (uint32 *)wp->piece_CC + i, 0x9000030, 0, 0x80);
        (wp->piece_CC + i)->words[0] = 0;
        (wp->piece_CC + i)->words[1] = 0;
    }
}

sint32 func_80121710(ST1A_PIECES *wp)
{
    STCOM_FIXED_VECTOR step;
    STCOM_SVECTOR pos;
    STCOM_SVECTOR prev;
    STCOM_EFFECT *fx;
    uint8 i;

    step.x = wp->velocity.x << 8;
    step.y = wp->velocity.y << 8;
    step.z = wp->velocity.z << 8;
    for (i = 0; i < wp->work_3; i++)
    {
        pos.x  = (wp->position_fixed.v.x + step.x * (uint8)(i + 1)) >> 16;
        pos.y  = (wp->position_fixed.v.y + step.y * (uint8)(i + 1)) >> 16;
        pos.z  = (wp->position_fixed.v.z + step.z * (uint8)(i + 1)) >> 16;
        prev.x = (wp->position_fixed.v.x + step.x * i) >> 16;
        prev.y = (wp->position_fixed.v.y + step.y * i) >> 16;
        prev.z = (wp->position_fixed.v.z + step.z * i) >> 16;
        if (func_80049C54(&pos, &prev, D_801330D0, 0xFFFF))
        {
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->be_flag         = MOVE;
                fx->id              = 0x1E;
                fx->type            = 1;
                fx->sprite.pos_8[0] = prev.x;
                fx->sprite.pos_8[1] = prev.y;
                fx->sprite.pos_8[2] = prev.z;
            }
            return i + 1;
        }
    }
    return 0;
}

sint32 func_801218D0(ST1A_PIECES *wp)
{
    uint8 i;

    i = 0;
    while (i < wp->work_3 / 8)
    {
        if ((wp->piece_CC + i)->words[0] & 0xFF000000)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void func_8012192C(STAGE_OBJ *wp)
{
    D_8013310C[wp->routine_0](wp);
}

// coord is set in identical arms (merged by jump2) so cse2 can't fold the later coord + 4 to
// wp + 0x8C; mat is that address, used by both matrix calls.

void func_80121968(ST1A_DEBRIS *wp)
{
    STCOM_FIXED_VECTOR scale;
    ST1A_COORD *coord;
    STCOM_MATRIX *mat;

    if (wp->type < 2)
    {
        wp->data_78  = D_801330E4;
        wp->value_BC = 0;
        wp->value_C0 = 0;
        wp->hit_C4   = 0;
        wp->value_C8 = 0;
        wp->id       = 0x30;
        wp->be_flag |= TRANS | MODEL;
        Model_work_init(wp, D_80133108);
        wp->scale_6E            = 0;
        wp->id                  = 0x32;
        wp->velocity.x          = 0;
        wp->velocity.y          = D_801330F0[wp->type];
        wp->velocity.z          = 0;
        wp->accel.x             = 0;
        wp->accel.y             = D_801330F8[wp->type];
        wp->accel.z             = 0;
        wp->position_fixed.v.x  = wp->position.x << 16;
        wp->coord_88.pos_24.x   = wp->position.x;
        wp->coord_88.pos_24.y   = wp->position.y;
        wp->coord_88.pos_24.z   = wp->position.z;
        wp->position_fixed.v.y  = wp->position.y << 16;
        wp->position_fixed.v.z  = wp->position.z << 16;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->position_prev       = wp->position;
        wp->color_B4            = 0x2808080;
        wp->routine_0++;
        wp->routine_1 = rand() & 0xF;
        if (wp->routine_1 != 0)
        {
            coord = &wp->coord_88;
        }
        else
        {
            coord = &wp->coord_88;
        }
        do
        {
            wp->coord_88.matrix_4.w[0] = 0x200;
            wp->coord_88.matrix_4.w[1] = 0;
            wp->coord_88.matrix_4.w[2] = 0x200;
            wp->coord_88.matrix_4.w[3] = 0;
            wp->coord_88.matrix_4.w[4] = 0x200;
        } while (0);
        mat = &coord->matrix_4.m;
        RotMatrixY(wp->routine_1 << 8, mat);
        scale.x = scale.y = scale.z = wp->scale_6E;
        ScaleMatrix(mat, &scale);
        func_80122000(wp);
    }
    else
    {
        wp->velocity.x          = (wp->velocity.x * D_801330F4[0]) >> 8;
        wp->velocity.y          = 0;
        wp->velocity.z          = (wp->velocity.z * D_801330F4[0]) >> 8;
        wp->data_78             = D_801330E4;
        wp->accel.x             = 0;
        wp->accel.y             = 0;
        wp->accel.z             = 0;
        wp->value_BC            = 0;
        wp->value_C0            = 0;
        wp->hit_C4              = 0;
        wp->value_C8            = 0;
        wp->coord_88.pos_24.x   = wp->position.x;
        wp->coord_88.pos_24.y   = wp->position.y;
        wp->coord_88.pos_24.z   = wp->position.z;
        wp->position_fixed.v.x  = wp->position.x << 16;
        wp->position_fixed.v.y  = wp->position.y << 16;
        wp->position_fixed.v.z  = wp->position.z << 16;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->position_prev       = wp->position;
        wp->routine_0           = 3;
    }
}

void func_80121C14(ST1A_DEBRIS *wp)
{
    STCOM_FIXED_VECTOR scale;
    ST1A_COORD *coord;
    STCOM_EFFECT *fx;
    uint32 top;

    if (wp->type == 0)
    {
        if (wp->position.y < -0x7D1)
        {
            wp->routine_2 = 8;
            wp->routine_0++;
        }
    }
    else if (wp->position.y >= 0)
    {
        Sound_call2(0x1F9, &wp->position);
        wp->routine_2 = 8;
        wp->routine_0++;
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->be_flag           = MOVE | MODEL;
            fx->id                = 0x1D;
            fx->value_D           = 1;
            fx->timer_E           = 1;
            fx->type              = 2;
            fx->sprite.position.x = wp->position.x;
            fx->sprite.position.y = wp->position.y;
            fx->sprite.position.z = wp->position.z;
        }
    }
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    wp->velocity.y += wp->accel.y;
    if (wp->type == 0)
    {
        if (wp->velocity.y < D_80133100[0])
        {
            wp->velocity.y = D_80133100[0];
        }
    }
    else
    {
        if (wp->velocity.y > D_80133100[wp->type])
        {
            wp->velocity.y = D_80133100[wp->type];
        }
    }
    wp->position.y        = wp->position_fixed.v.y += wp->velocity.y << 10;
    coord                 = &wp->coord_88;
    wp->coord_88.pos_24.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->coord_88.pos_24.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    wp->coord_88.pos_24.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    if ((wp->scale_6E += 0x100) < 0)
    {
        wp->scale_6E = 0;
    }
    if (wp->type != 0)
    {
        top = 0x800;
        if (STAGE_GAME.value_5B >= 2)
        {
            top = 0x900;
        }
        if (wp->scale_6E <= top)
        {
            wp->position_fixed.v.y += 0x400000;
            wp->position_fixed.v.x = Player_work.position.x << 16;
            wp->position_fixed.v.z = Player_work.position.z << 16;
        }
    }
    wp->routine_1++;
    if (wp->scale_6E > 0x1000)
    {
        wp->scale_6E = 0x1000;
    }
    coord->matrix_4.w[0] = 0x200;
    coord->matrix_4.w[1] = 0;
    coord->matrix_4.w[2] = 0x200;
    coord->matrix_4.w[3] = 0;
    coord->matrix_4.w[4] = 0x200;
    RotMatrixY(wp->routine_1 << 8, &coord->matrix_4.m);
    scale.x = scale.y = scale.z = wp->scale_6E;
    ScaleMatrix(&coord->matrix_4.m, &scale);
    func_80122000(wp);
}

// coord is assigned in both arms of the first clamp: the join then starts a new CSE block, so
// the matrix pointer stays coord + 4 (s1/s2) as in retail; the store block pins their order.
void func_80121ED4(ST1A_DEBRIS *wp)
{
    STCOM_FIXED_VECTOR scale;
    ST1A_COORD *coord;
    STCOM_MATRIX *mat;
    sint32 c;

    if (--wp->routine_2 == 0)
    {
        Close_SHL_WORK(wp);
    }
    do
    {
        wp->scale_6E -= 0x200;
        wp->routine_1++;
    } while (0);
    if (wp->scale_6E > 0x1000)
    {
        coord        = &wp->coord_88;
        wp->scale_6E = 0x1000;
    }
    else
    {
        coord = &wp->coord_88;
    }
    if (wp->scale_6E < 0)
    {
        wp->scale_6E = 0;
    }
    do
    {
        wp->coord_88.matrix_4.w[0] = 0x200;
        wp->coord_88.matrix_4.w[1] = 0;
        wp->coord_88.matrix_4.w[2] = 0x200;
        wp->coord_88.matrix_4.w[3] = 0;
        wp->coord_88.matrix_4.w[4] = 0x200;
    } while (0);
    mat = &coord->matrix_4.m;
    RotMatrixY(wp->routine_1 << 8, mat);
    scale.x = scale.z = 0x1000;
    scale.y           = wp->scale_6E;
    if (wp->type == 0)
    {
        coord->pos_24.y -= 0x80;
    }
    ScaleMatrix(mat, &scale);
    c            = (wp->scale_6E << 16) >> 21;
    wp->color_B4 = (c | 0x2000000) | (c << 8) | (c << 16);
}

void func_80122000(ST1A_DEBRIS *wp)
{
    func_800341BC(&wp->position, 0x40, 0, 0xA000, wp->work_id, &wp->hit_C4, 0x4000040, 0, 0x80);
    wp->hit_C4 = 0;
}

void func_80122064(STAGE_OBJ *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = MOVE | MODEL;
        ep->id       = 0x80;
        ep->type     = 2;
        ep->pos_38.x = wp->position.x;
        ep->pos_38.y = wp->position.y;
        ep->pos_38.z = wp->position.z;
    }
}

void func_801220D0(ST1A_SHOT *wp)
{
    STAGE_OBJ50 *ep;

    if (func_80048EA4(&wp->position, NULL, 0, 0xFFFF) < -0x11)
    {
        Close_SHL_WORK(wp);
        return;
    }
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    wp->position_fixed.v.x += wp->velocity.x << 12;
    wp->position_fixed.v.y += wp->velocity.y << 12;
    wp->position_fixed.v.z += wp->velocity.z << 12;
    wp->position_AC.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->position_AC.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->position_AC.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    ep                                 = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = MOVE | MODEL;
        ep->id       = 0x1D;
        ep->u_C.b.hi = 0;
        if (wp->type == 2)
        {
            ep->value_E = 0;
        }
        else
        {
            ep->value_E = 1;
        }
        ep->type     = 2;
        ep->pos_38.x = wp->position.x;
        ep->pos_38.y = wp->position.y;
        ep->pos_38.z = wp->position.z;
    }
}

void func_8012222C(STAGE_OBJ *wp)
{
    D_80133134[wp->routine_0](wp);
}

void func_80122268(ST1A_DART *wp)
{
    STCOM_MATRIX unused_m; // unused, but retail reserves its frame
    STCOM_SVECTOR unused_v;

    if (wp->type == 0xFF)
    {
        wp->routine_0 = 7;
        wp->routine_3 = 0x80;
        wp->color_B4  = 0x2808080;
        wp->be_flag |= 0x26;
    }
    else if (wp->type == 0xFE)
    {
        wp->routine_0 = 8;
        wp->routine_2 = 0;
        wp->routine_3 = 0x10;
    }
    else if (wp->type == 0xFD)
    {
        wp->routine_0 = 9;
    }
    else if (wp->type == 0xFC)
    {
        Fog_param_get(&wp->position_prev);
        wp->routine_0 = 0xA;
    }
    else
    {
        wp->value_BC[0] = 0;
        wp->value_BC[1] = 0;
        wp->value_BC[2] = 0;
        wp->value_BC[3] = 0;
        wp->data_78     = D_8013311C;
        wp->be_flag |= TRANS | MODEL;
        wp->dir_CC = wp->velocity;
        Model_work_init(wp, &wp->type);
        wp->position            = wp->owner_D4->part_180[15];
        wp->position_AC.x       = wp->position.x;
        wp->position_AC.y       = wp->position.y;
        wp->position_AC.z       = wp->position.z;
        wp->position_fixed.v.x  = wp->position.x << 16;
        wp->position_fixed.v.y  = wp->position.y << 16;
        wp->position_fixed.v.z  = wp->position.z << 16;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->position_prev       = wp->position;
        wp->color_B4            = 0x2808080;
        wp->position_AC.pad     = 0;
        wp->routine_0++;
        wp->routine_3++;
        func_80122CC8(wp);
        Sound_call2(0x1F4, &wp->position);
    }
}

// The launch speed is read once, stored, then sign-extended into the same variable as the accel
// factor. The accel factor is read through an array alias so its load stays after the velocity
// stores (a scalar global load moves above struct stores).
void func_80122448(ST1A_DART *wp)
{
    STCOM_FIXED_VECTOR v;
    STCOM_SVECTOR dir;
    sint32 speed;

    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    if (++wp->routine_2 < 0x1E)
    {
        wp->position_AC.pad += 0x10;
    }
    wp->routine_3++;
    wp->position           = wp->owner_D4->part_180[15];
    wp->position_AC.x      = wp->position.x;
    wp->position_AC.y      = wp->position.y;
    wp->position_AC.z      = wp->position.z;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (wp->fire_C != 0)
    {
        Sound_call2(0x1F5, &wp->position);
        wp->fire_C    = 0;
        wp->routine_2 = 0;
        wp->routine_0 = 5;
        v.x           = STAGE_PL.value_3A8 - wp->position.x;
        v.y           = STAGE_PL.value_3AA - wp->position.y;
        v.z           = STAGE_PL.value_3AC - wp->position.z;
        VectorNormalS(&v, &wp->velocity);
        wp->dir_CC     = wp->velocity;
        dir            = wp->dir_CC;
        wp->life_6E    = D_80133128;
        speed          = (sint16)D_80133128;
        wp->velocity.x = (dir.x * speed) >> 4;
        wp->velocity.y = (dir.y * speed) >> 4;
        wp->velocity.z = (dir.z * speed) >> 4;
        speed          = D_8013312C_A[0];
        wp->accel.x    = (dir.x * speed) >> 4;
        wp->accel.y    = (dir.y * speed) >> 4;
        wp->accel.z    = (dir.z * speed) >> 4;
    }
    func_80122CC8(wp);
}

void func_801226A8(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_801226BC(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_801226D0(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_801226E4(ST1A_DART *wp)
{
    STCOM_SVECTOR out;
    STCOM_SVECTOR dir;
    STCOM_FIXED_VECTOR v;
    STAGE_10C *slot;
    sint32 hit;
    sint32 speed;

    hit = func_80037694((STCOM23_WORK *)wp, 0);
    if (hit != 0 && (hit != 0x7FFF || (wp->value_BC[2] & 0xFF000000)))
    {
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->routine_3 = 0;
        wp->routine_0++;
    }
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    if (!(wp->routine_2 & 7))
    {
        slot = Open_SHL_WORK();
        if (slot != NULL)
        {
            slot->be_flag     = MOVE;
            slot->id          = 0x33;
            slot->type        = 0xFE;
            slot->position_AC = wp->position;
        }
    }
    if (++wp->routine_2 < 10)
    {
        // one more loop level, as a macro body would give: it keeps retail's scheduling
        do
        {
            v.x = wp->target_B8->x - wp->position.x;
            v.y = wp->target_B8->y - wp->position.y;
            v.z = wp->target_B8->z - wp->position.z;
            if ((uint32)(v.x + 0x687E) > 0xD0FC || (uint32)(v.y + 0x687E) > 0xD0FC || (uint32)(v.z + 0x687E) > 0xD0FC)
            {
                v.x >>= 2;
                v.y >>= 2;
                v.z >>= 2;
            }
            VectorNormalS(&v, &dir);
            func_80033F04(&out, &dir, &wp->dir_CC, 0x165, 0x0FF069DA);
            wp->dir_CC     = out;
            speed          = wp->life_6E;
            wp->velocity.x = (out.x * speed) >> 4;
            wp->velocity.y = (out.y * speed) >> 4;
            wp->velocity.z = (out.z * speed) >> 4;
            speed          = wp->life_6E;
        } while (0);
        speed += D_8013312C;
        if (speed >= D_80133130)
        {
            wp->life_6E = D_80133130;
        }
        else
        {
            wp->life_6E = speed;
        }
        wp->position_fixed.v.x += wp->velocity.x << 8;
        wp->position_fixed.v.y += wp->velocity.y << 8;
        wp->position_fixed.v.z += wp->velocity.z << 8;
        wp->position_AC.x = wp->position.x = wp->position_fixed.f.x.words.integer;
        wp->position_AC.y = wp->position.y = wp->position_fixed.f.y.words.integer;
        wp->position_AC.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    }
    else if (wp->routine_2 < 60)
    {
        wp->position_fixed.v.x += wp->velocity.x << 8;
        wp->position_fixed.v.y += wp->velocity.y << 8;
        wp->position_fixed.v.z += wp->velocity.z << 8;
        wp->position_AC.x = wp->position.x = wp->position_fixed.f.x.words.integer;
        wp->position_AC.y = wp->position.y = wp->position_fixed.f.y.words.integer;
        wp->position_AC.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    }
    else
    {
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->routine_3 = 0;
        wp->routine_0++;
    }
    wp->routine_3++;
    func_80122CC8(wp);
    func_80122BC8((ST1A_10C *)wp);
}

void func_80122A24(ST1A_10C *wp)
{
    ST1A_SHOT *shot;
    sint32 i;
    sint32 angle;
    sint32 count;
    uint32 c;
    STCOM_FIXED_VECTOR unused; // unused, but retail reserves its 16 bytes

    if (wp->routine_1 == 0)
    {
        wp->routine_2 = 0x10;
        wp->routine_1++;
        if (wp->position.y >= -0x1E)
        {
            Sound_call2(0x1F6, &wp->position);
            count = 3;
            angle = ratan2(Player_work.position.x - wp->position.x, Player_work.position.z - wp->position.z);
            if (STAGE_GAME.value_5B >= 2)
            {
                count = 5;
            }
            for (i = 0; i < count; i++)
            {
                shot = (ST1A_SHOT *)Open_SHL_WORK();
                if (shot != NULL)
                {
                    shot->be_flag    = MOVE;
                    shot->id         = 0x32;
                    shot->type       = 3;
                    shot->velocity.x = rsin(angle + D_80133160[i]);
                    shot->velocity.y = 0;
                    shot->velocity.z = rcos(angle + D_80133160[i]);
                    shot->position   = wp->position;
                }
            }
        }
    }
    else if (--wp->routine_2 == 0)
    {
        Close_SHL_WORK(wp);
    }
    c            = wp->routine_2 << 3;
    wp->color_B4 = 0x2000000 | c | (c << 8) | (c << 16);
}

void func_80122BC8(ST1A_10C *wp)
{
    if (STAGE_GAME.value_5B >= 2)
    {
        func_800341BC(&wp->position, wp->position_AC.pad / 2, 0, 0xA000, wp->work_id, &wp->value_C4, 0x040A0060, 0, 0x80);
    }
    else
    {
        func_800341BC(&wp->position, wp->position_AC.pad / 2, 0, 0xA000, wp->work_id, &wp->value_C4, 0x040A0040, 0, 0x80);
    }
    wp->value_C4 = 0;
}

void func_80122C5C(STAGE_OBJ *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = MOVE | MODEL;
        ep->id       = 0x80;
        ep->type     = 2;
        ep->pos_38.x = wp->position.x;
        ep->pos_38.y = wp->position.y;
        ep->pos_38.z = wp->position.z;
    }
}

void func_80122CC8(ST1A_DART *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;
    sint32 s;
    sint32 x;
    sint32 z;

    x     = wp->velocity.x;
    z     = wp->velocity.z;
    rot.x = wp->routine_3 << 7;
    rot.y = ratan2(x, z) + 0x800;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->matrix_8C.m);
    s       = wp->position_AC.pad;
    scale.z = s;
    scale.y = s;
    scale.x = s;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
}

void func_80122D44(STAGE_10C *wp)
{
    sint32 a;

    wp->routine_3 -= 0x20;
    a = wp->routine_3;
    if (a <= 0)
    {
        Close_SHL_WORK(wp);
        return;
    }
    wp->color_B4 = 0x2000000 | (a << 16) | (a << 8) | a;
}

void func_80122DA4(STAGE_OBJ *wp)
{
    wp->routine_3 += 8;
    wp->routine_2 += 8;
    if ((uint8)wp->routine_3 >= 0xF0)
    {
        Close_SHL_WORK(wp);
    }
}

// Register only: retail puts each second product (pos * i) in t2, not v0 (score 8). The early
// return (no increment when routine_3 is 0) gives retail's branch to the shared final call.
void func_80122DEC(STAGE_PROP *wp)
{
    sint32 n;
    sint32 i;
    sint32 rest;

    n = wp->routine_3;
    i = wp->routine_2;
    if (n == 0)
    {
        Close_SHL_WORK(wp);
        return;
    }
    rest = n - i;
    func_80036A88((wp->position_prev.x * rest + wp->position.x * i) / n, (wp->position_prev.y * rest + wp->position.y * i) / n,
                  (wp->position_prev.z * rest + wp->position.z * i) / n, (wp->position_prev.pad * rest + wp->position.pad * i) / n);
    if (++wp->routine_2 > wp->routine_3)
    {
        Close_SHL_WORK(wp);
    }
}

// Same as func_80122DEC.
void func_80122FA0(STAGE_PROP *wp)
{
    sint32 n;
    sint32 i;
    sint32 rest;

    n = wp->routine_3;
    i = wp->routine_2;
    if (n == 0)
    {
        Close_SHL_WORK(wp);
        return;
    }
    rest = n - i;
    func_80036A88((wp->position_prev.x * rest + wp->position.x * i) / n, (wp->position_prev.y * rest + wp->position.y * i) / n,
                  (wp->position_prev.z * rest + wp->position.z * i) / n, (wp->position_prev.pad * rest + wp->position.pad * i) / n);
    if (++wp->routine_2 > wp->routine_3)
    {
        Close_SHL_WORK(wp);
    }
}

void func_80123154(ST1A_OBJ *wp)
{
    D_80133170[wp->routine_0](wp);
    wp->value_D0 = 0;
}

// Statement order found by search: retail keeps the color 0x808080 in a1 for both the
// color_B4 store and the call; GCC builds the constant twice (a2 for the store, a1 for the call).
void func_801231A0(ST1A_COPY *wp)
{
    wp->ctl.owner_34      = func_80036294(wp->id_C);
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->be_flag |= 0x26;
    wp->value_64                = 0;
    wp->model_88                = wp->ctl.owner_34->model_88;
    wp->position_AC.pad         = wp->work_1;
    wp->ctl.flags_0             = 0x50;
    wp->ctl.scale_38            = 0x1000;
    *(sint32 *)&wp->ctl.timer_4 = 0;
    *(sint32 *)&wp->ctl.value_8 = 0;
    wp->ctl.value_14            = 0;
    wp->ctl.scale_3C            = 0x1000;
    wp->ctl.scale_40            = 0x1000;
    wp->life_6E                 = 0x400;
    wp->data_78                 = D_8013318C;
    wp->routine_0               = 1;
    wp->routine_1               = 0;
    wp->color_B4                = 0x808080;
    func_80123260(wp);
}

void func_80123260(ST1A_COPY *wp)
{
    ST1A_COPY_CTL *ctl;
    uint16 flags;
    uint16 c;
    uint32 rgb;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation.v;
    ctl                     = &wp->ctl;
    ctl->rand_2             = rand();
    flags                   = ctl->flags_0;
    if (flags & 0x40)
    {
        if (flags & 0x10)
        {
            wp->position           = ctl->owner_34->part_180[wp->work_1];
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            if (!(ctl->owner_34->be_flag & TRANS))
            {
                wp->be_flag &= ~TRANS;
            }
            else
            {
                wp->be_flag |= TRANS;
                c   = ctl->owner_34->part_180[0].pad;
                rgb = (c & 0x1F) << 3;
                rgb |= (c & 0x3E0) << 6;
                rgb |= (c & 0x7C00) << 9;
                if ((ctl->owner_34->flags_F & 2) && (c & 0x8000))
                {
                    wp->color_B4 = rgb | 0x2E000000;
                }
                else
                {
                    wp->color_B4 = rgb;
                }
            }
        }
        else
        {
            wp->position.x         = ctl->owner_34->part_180[wp->work_1].x;
            wp->position.z         = ctl->owner_34->part_180[wp->work_1].z;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
        }
    }
    if (ctl->owner_34->flags_F & 4)
    {
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~0x10;
        wp->position.y -= 0x400;
        wp->position_fixed.v.y = wp->position.y << 16;
        ctl->value_48          = ST1A_ABS(ctl->owner_34->part_180[6].y - 0x400);
    }
    if (ctl->owner_34->flags_F & 0x40)
    {
        wp->routine_1             = 2;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~0x10;
    }
    if ((ctl->owner_34->flags_E & 2) && wp->work_1 < 7)
    {
        wp->routine_1             = 3;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~0x50;
    }
    if ((ctl->owner_34->flags_E & 1) && wp->work_1 >= 8)
    {
        wp->routine_1             = 3;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~0x50;
    }
    D_8013317C[wp->routine_1](wp);
    if (ctl->flags_0 & 0x40)
    {
        wp->matrix_8C = ctl->owner_34->matrix_240[wp->work_1];
    }
    wp->position_AC     = wp->position;
    wp->position_AC.pad = wp->work_1;
    if (ctl->flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
}

void func_8012367C(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}

void func_8012369C(void)
{
}

void func_801236A4(ST1A_COPY *wp)
{
    ST1A_COPY_CTL *ctl;
    STCOM_EFFECT *fx;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            if (!(ctl->owner_34->flags_F & 8))
            {
                wp->be_flag &= ~TRANS;
                break;
            }
            wp->color_B4 = 0x2E000000;
            wp->step_4E  = 8;
            wp->speed_46 = 0;
            ctl->timer_4 = 0;
            wp->be_flag |= TRANS;
            wp->routine_2++;
            // fall through
        case 1:
            ctl->value_48 -= wp->speed_46;
            if (wp->color_B4 < 0x2E808080)
            {
                wp->color_B4 += 0x80808;
            }
            else
            {
                wp->color_B4 = 0x808080;
            }
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->be_flag         = MOVE | MODEL;
                fx->id              = 0x1D;
                fx->type            = 0x42;
                fx->value_D         = 3;
                fx->timer_E         = 0;
                fx->sprite.position = wp->position;
                fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                fx->sprite.position.y += (rand() & 0xFF) - 0x80;
                fx->sprite.position.z += (rand() & 0xFF) - 0x80;
            }
            ctl->timer_4++;
            if (ctl->value_48 < 0)
            {
                if (!(ctl->owner_34->flags_F & 0x20))
                {
                    ctl->owner_34->flags_F |= 0x20;
                    Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                    if (wp->work_1 == 5)
                    {
                        fx = func_80031618();
                        if (fx != NULL)
                        {
                            fx->be_flag           = MOVE | MODEL;
                            fx->id                = 0x80;
                            fx->type              = 6;
                            fx->value_F           = 2;
                            fx->sprite.position   = ctl->owner_34->position;
                            fx->sprite.position.y = Obj_ceiling_height_get(wp);
                            Sound_call2(0x1E0, &wp->position);
                        }
                    }
                }
                wp->routine_2++;
                ctl->timer_4 = 0x10;
            }
            else
            {
                wp->position.y += wp->speed_46;
                wp->position_fixed.v.y = wp->position.y << 16;
                wp->speed_46 += wp->step_4E;
            }
            break;
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2++;
                wp->speed_46 = (ctl->owner_34->part_180[wp->work_1].y - wp->position.y) / 60;
                ctl->timer_4 = 0x3C;
                ctl->owner_34->flags_F |= 0x10;
            }
            break;
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->position.y         = ctl->owner_34->part_180[wp->work_1].y;
                wp->position_fixed.v.y = wp->position.y << 16;
                ctl->flags_0 |= 0x11;
            }
            else
            {
                wp->position.y += wp->speed_46;
                wp->position_fixed.v.y = wp->position.y << 16;
            }
            break;
    }
}

void func_80123A64(ST1A_COPY *wp)
{
    ST1A_COPY_CTL *ctl;
    sint32 ground;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            ground       = Obj_ceiling_height_get(ctl->owner_34) + 0x20;
            wp->step_4E  = (ctl->owner_34->position.y - ground) / 8;
            ctl->timer_4 = 8;
            // fall through
        case 1:
            if (ctl->timer_4 != 0)
            {
                wp->position.y -= wp->step_4E;
                wp->position_fixed.v.y = wp->position.y << 16;
                ctl->timer_4--;
            }
            else if (ctl->owner_34->flags_F & 0x80)
            {
                wp->routine_2++;
                ctl->timer_4 = 8;
            }
            break;
        case 2:
            if (ctl->timer_4 != 0)
            {
                wp->position.y += wp->step_4E;
                wp->position_fixed.v.y = wp->position.y << 16;
                ctl->timer_4--;
            }
            else
            {
                wp->position.y         = ctl->owner_34->part_180[wp->work_1].y;
                wp->position_fixed.v.y = wp->position.y << 16;
                ctl->flags_0 |= 0x11;
                ctl->owner_34->flags_F |= 0x10;
            }
            break;
    }
}

void func_80123C00(ST1A_COPY *wp)
{
    ST1A_COPY_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->color_B4 = 0x808080;
            wp->speed_4C = 0x60;
            wp->routine_2++;
            ctl->timer_4 = Distance_xz(&ctl->owner_34->position, &Player_work.position) / (wp->speed_4C + 0x10);
            Sound_call2(0x1DA, &wp->position);
            // fall through
        case 1:
            func_8002FFC4(&wp->position, &wp->position_fixed.v, ctl->owner_34->rotation.y, wp->speed_4C * 16, 0, 0);
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2++;
                ctl->timer_4 = 4;
                wp->color_B4 = 0x2E505050;
            }
            break;
        case 2:
            func_8002FFC4(&wp->position, &wp->position_fixed.v, ctl->owner_34->rotation.y, wp->speed_4C * 16, 0, 0);
            wp->color_B4 -= 0x101010;
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2++;
                wp->be_flag &= ~TRANS;
                ctl->owner_34->count_C++;
                Sound_call2(0x1DB, &wp->position);
            }
            break;
        case 3:
            if (ctl->owner_34->flags_E & 4)
            {
                wp->be_flag |= TRANS;
                wp->routine_2++;
                wp->position = ctl->owner_34->part_180[wp->work_1];
                wp->position_fixed.v.x <<= 16;
                wp->position_fixed.v.y <<= 16;
                wp->position_fixed.v.z <<= 16;
                ctl->timer_4 = 4;
                ctl->flags_0 |= 0x40;
            }
            break;
        case 4:
            wp->color_B4 += 0x101010;
            wp->position = ctl->owner_34->part_180[wp->work_1];
            wp->position_fixed.v.x <<= 16;
            wp->position_fixed.v.y <<= 16;
            wp->position_fixed.v.z <<= 16;
            if (--ctl->timer_4 < 0)
            {
                wp->color_B4 = 0x808080;
                ctl->owner_34->flags_F |= 0x10;
                ctl->flags_0 |= 0x11;
            }
            break;
    }
}

void func_80123F24(STAGE_PROP *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->be_flag |= TRANS | MODEL;
        wp->position_AC = wp->position;
        wp->id          = 0x31;
        Model_work_init(wp, &wp->type);
        wp->id       = 0x35;
        wp->color_B4 = 0x808080;
        wp->data_78  = NULL;
        wp->routine_0++;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &D_80133198);
    wp->position_AC = wp->position;
}
