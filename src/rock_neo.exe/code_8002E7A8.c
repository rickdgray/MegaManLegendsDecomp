#include "common.h"
#include "code_8002E7A8.h"
#include "fastmem.h"
#include "player.h"

// Called only from this file, ahead of their definitions.
void func_80033A28(ATTACH_WORK *wp);
sint32 func_8002FA38(ATTACH_WORK *wp, sint32 *tbl, uint8 *sub); // tbl: count, then ATTACH_ENT[count]
uint32 func_80030628(POS14_WORK *from, POS14_WORK *to, sint16 *shift, VECTOR *out, sint16 angle);
uint32 func_80030418(VIEW_WORK *from, VIEW_WORK *to, sint16 *shift, VECTOR *out);
uint32 func_80030604(POS14_WORK *from, POS14_WORK *to, sint16 *shift, VECTOR *out);
sint16 func_80030D30(SVECTOR *from, SVECTOR *to, sint16 height, sint16 max_dist, sint16 arc);
sint16 func_80030CF0(POS14_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist, sint16 arc);
sint16 func_80030CB8(POS14_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist);
void func_8002F9EC(ATTACH_WORK *wp, uint8 *sub);
void func_8002FA10(ATTACH_WORK *wp, uint8 *sub);
VECTOR *func_80030058(VECTOR *out, sint32 angle, sint32 x, sint32 y, sint32 z);
WORK_10C *func_80031598(void);
sint32 func_8003545C(uint32 value, SLOT_OWNER *owner);

// Small data (.sdata 0x80097CFC-0x80097D0C): reached through $gp in this file.
sint32 D_80097CFC = 0x200;
uint8 D_80097D00  = 0x5f;
uint8 D_80097D01  = 0xaf;
uint8 D_80097D02  = 0x49;
uint8 D_80097D03  = 0x89;
sint32 D_80097D04 = -0x363e05;
sint32 D_80097D08 = 0;

// Small uninitialized statics (.sbss 0x80098560-0x8009865C).
static uint32 D_80098560;
static sint32 D_80098564;
static sint32 D_80098568;
static uint8 D_8009856C[16]; // 0x8009856C-0x8009857B (was four words)
static MATRIX D_8009857C;    // 0x8009857C-0x8009859B
static sint32 D_8009859C[2];
static sint32 D_800985A4[2];
static sint32 D_800985AC[2];
static sint32 D_800985B4[2];
static sint32 D_800985BC[2];
static sint32 D_800985C4[2];
static sint32 D_800985CC[2];
static sint32 D_800985D4[2];
static sint32 D_800985DC[2];
static sint32 D_800985E4[2];
static sint32 D_800985EC[2];
static sint32 D_800985F4[2];
static SVECTOR D_800985FC;
static SVECTOR D_80098604;
static VECTOR D_8009860C;
static VECTOR D_8009861C;
static sint32 D_8009862C[2];
static sint32 D_80098634[2];
static VECTOR D_8009863C;
static VECTOR D_8009864C;

// Clears the work pools and tags each slot with its pool kind (0x10 * pool) ORed with its index.
// The player pool is only reset when `players` is set.
void Work_pools_init(sint32 players)
{
    sint32 kind;
    uint32 i;

    if (players)
    {
        kind = 0;
        func_800177CC(Player_work, (uint8 *)Player_work + 0xBE4);
        for (i = 0; i < 2; i++)
        {
            Player_work[i].unk01 = kind | i;
        }
    }
    kind = 0x10;
    func_800177CC(D_800BFB20, (uint8 *)D_800BFB20 + 0x10BC);
    D_800989F0 = 0;
    D_80098A60 = 0;
    for (i = 0; i < 0x10; i++)
    {
        D_800BFB20[i].kind_1 = kind | i;
    }
    kind = 0x20;
    func_800177CC(D_8009F108, (uint8 *)D_8009F108 + 0x3BFC);
    D_800987E8 = 0;
    D_8009880C = 0;
    for (i = 0; i < 0x10; i++)
    {
        D_8009F108[i].kind_1 = kind | i;
    }
    kind = 0x40;
    func_800177CC(D_800C3580, (uint8 *)D_800C3580 + 0x168C);
    D_80098B20 = 0;
    D_80098B64 = 0;
    for (i = 0; i < 4; i++)
    {
        D_800C3580[i].kind_1 = kind | i;
    }
    kind = 0x60;
    func_800177CC(D_8009CF88, (uint8 *)D_8009CF88 + 0x217C);
    D_800987CC = 0;
    D_80098808 = 0;
    for (i = 0; i < 0x20; i++)
    {
        D_8009CF88[i].kind_1 = kind | i;
    }
    kind = 0x80;
    func_800177CC(D_800A3B40, (uint8 *)D_800A3B40 + 0x11FC);
    D_80098838 = 0;
    D_8009883C = 0;
    D_800988C8 = 0;
    D_800988CC = 0;
    for (i = 0; i < 0x40; i++)
    {
        D_800A3B40[i].kind_1 = kind | i;
    }
    kind = 0xC0;
    func_800177CC(D_800A2D08, (uint8 *)D_800A2D08 + 0x23C);
    D_800987EC = 0;
    D_80098818 = 0;
    for (i = 0; i < 0x10; i++)
    {
        D_800A2D08[i].kind_1 = kind | i;
    }
    kind = 0xE0;
    func_800177CC(D_800BF118, (uint8 *)D_800BF118 + 0x9FC);
    D_800989CC = 0;
    D_80098A4C = 0;
    for (i = 0; i < 0x20; i++)
    {
        D_800BF118[i].kind_1 = kind | i;
    }
    func_800177CC(D_800BBA90, (uint8 *)D_800BBA90 + 0x264);
    func_800177CC((void *)0x8015BC00, (void *)0x8015BFFC);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8002EA50);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", Obj_work_flag_change);

void func_8002F3A8(FLAG_WORK *wp, uint32 f)
{
    if (f & 1)
    {
        wp->flags ^= 1;
    }
    if (f & 4)
    {
        wp->flags ^= 2;
    }
    if (f & 2)
    {
        wp->flags |= 1;
    }
    if (f & 8)
    {
        wp->flags |= 2;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8002F420);

void func_8002F884(MOVE_WORK *wp, SVECTOR *d)
{
    wp->x_14 += d->vx;
    wp->z_18 += d->vz;
    wp->x_1C += d->vx << 16;
    wp->z_24 += d->vz << 16;
    wp->x_2C += d->vx;
    wp->z_30 += d->vz;
    wp->x_34 += d->vx << 16;
    wp->z_3C += d->vz << 16;
}

void func_8002F928(POS_WORK *wp, uint16 *d)
{
    if (wp->flags & 4)
    {
        wp->pos_38[0] += d[0];
        wp->pos_38[2] += d[2];
    }
    else
    {
        wp->pos_1C[0] += d[0];
        wp->pos_1C[2] += d[2];
    }
}

void func_8002F998(uint16 *dst, uint16 *src)
{
    dst[10] += src[0];
    dst[12] += src[2];
}

void Model_work_init(ATTACH_WORK *wp, uint8 *sub)
{
    func_8002FA38(wp, (sint32 *)0x8016C000, sub);
}

void func_8002F9EC(ATTACH_WORK *wp, uint8 *sub)
{
    func_8002FA38(wp, (sint32 *)0x80190000, sub);
}

void func_8002FA10(ATTACH_WORK *wp, uint8 *sub)
{
    func_8002FA38(wp, (sint32 *)0x801F2000, sub);
}

#ifdef NON_MATCHING
// Only register allocation differs: the target keeps the entry pointer in a1 and the loop counter
// in a2; ours has them the other way round (the prologue and everything else match).
sint32 func_8002FA38(ATTACH_WORK *wp, sint32 *tbl, uint8 *sub)
{
    ATTACH_ENT *e;
    sint32 count;
    sint32 kind;
    sint32 i;

    count = *tbl++;
    kind  = func_8002FE74(wp->kind_1);
    e     = (ATTACH_ENT *)tbl;
    if (kind == 0x60 && wp->id_2 >= 0x80)
    {
        kind = 0x10;
    }
    for (i = 0; i < count; i++)
    {
        if (kind == e->kind_0 && wp->id_2 == e->id_1 && (sub == 0 || *sub == e->sub_2))
        {
            switch (kind)
            {
                case 0x40:
                case 0x20:
                    Mem_copy4(e->ptr_4 + 0x10, wp->buf_F8, 0x18);
                    wp->val_9C = *e->ptr_8;
                    wp->ptr_A0 = e->ptr_8 + 1;
                    wp->ptr_88 = e->ptr_4;
                    wp->val_90 = e->val_C;
                    break;
                case 0x10:
                case 0x60:
                    wp->ptr_88 = e->ptr_4;
                    break;
                case 0x80:
                case 0xE0:
                    wp->ptr_14 = e->ptr_4;
                    break;
            }
            return 1;
        }
        e++;
    }
    Entry_missing_trap = 0;
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8002FA38);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8002FBF4);

uint32 func_8002FE74(uint32 a)
{
    if (a < 0x20)
    {
        a &= 0x10;
    }
    else
    {
        a &= 0xE0;
        if (a == 0xA0)
        {
            a = 0x80;
        }
    }
    return a;
}

void func_8002FEA4(TURN_WORK *wp, sint16 x, sint16 y, sint16 z)
{
    VECTOR v;

    func_80030058(&v, wp->angle_56, x, y, z);
    wp->pos_1C.vx += v.vx;
    wp->pos_1C.vy += v.vy;
    wp->pos_1C.vz += v.vz;
    func_80030150(&wp->pos_1C, &wp->svec_14);
}

void func_8002FF34(TURN_WORK *wp, sint16 x, sint16 y, sint16 z)
{
    VECTOR v;

    func_80030058(&v, wp->angle_56, x, y, z);
    wp->pos_428.vx += v.vx;
    wp->pos_428.vy += v.vy;
    wp->pos_428.vz += v.vz;
    func_80030150(&wp->pos_428, &wp->svec_438);
}

void func_8002FFC4(SVECTOR *dst, VECTOR *pos, sint32 angle, sint16 x, sint16 y, sint16 z)
{
    VECTOR v;

    func_80030058(&v, angle, x, y, z);
    pos->vx += v.vx;
    pos->vy += v.vy;
    pos->vz += v.vz;
    func_80030150(pos, dst);
}

#ifdef NON_MATCHING
// Register allocation only: the target keeps the x and z parameters (a2, v1) live next to their
// negated copies (s2, s1); GCC merges each pair into one register, so the prologue order differs.
VECTOR *func_80030058(VECTOR *out, sint32 angle, sint32 x, sint32 y, sint32 z)
{
    VECTOR in;
    VECTOR res;
    long m[8];
    sint32 px;
    sint32 pz;

    px = x;
    pz = z;
    if ((sint16)x < 0)
    {
        px = -x;
        pz = -z;
        angle += 0x800;
    }
    m[0] = 0x1000;
    m[1] = 0;
    m[2] = 0x1000;
    m[3] = 0;
    m[4] = 0x1000;
    m[5] = 0;
    m[6] = 0;
    m[7] = 0;
    RotMatrixY(angle, (MATRIX *)m);
    in.vx = (sint16)pz << 12;
    in.vy = (sint16)y << 12;
    in.vz = -((sint16)px << 12);
    ApplyMatrixLV((MATRIX *)m, &in, &res);
    *out = res;
    return out;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80030058);
#endif

// Rounds a 16.16 fixed-point vector to integers.
void func_80030150(VECTOR *src, SVECTOR *dst)
{
    dst->vx = (src->vx >> 16) + ((src->vx >> 15) & 1);
    dst->vy = (src->vy >> 16) + ((src->vy >> 15) & 1);
    dst->vz = (src->vz >> 16) + ((src->vz >> 15) & 1);
}

void func_800301A8(MATRIX *m, VECTOR *pos, VECTOR *origin)
{
    VECTOR d;
    VECTOR r;

    d.vx = pos->vx - origin->vx;
    d.vy = pos->vy - origin->vy;
    d.vz = pos->vz - origin->vz;
    ApplyMatrixLV(m, &d, &r);
    pos->vx = origin->vx + r.vx;
    pos->vy = origin->vy + r.vy;
    pos->vz = origin->vz + r.vz;
}

long func_80030254(uint16 *a, uint16 *b)
{
    SVECTOR d;

    d.vx = b[10] - a[10];
    d.vy = b[11] - a[11];
    d.vz = b[12] - a[12];
    return SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
}

long Distance_xyz(SVECTOR *a, SVECTOR *b)
{
    SVECTOR d;

    d.vx = b->vx - a->vx;
    d.vy = b->vy - a->vy;
    d.vz = b->vz - a->vz;
    return SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
}

long Distance_xz(SVECTOR *a, SVECTOR *b)
{
    VECTOR d;

    d.vx = b->vx - a->vx;
    d.vz = b->vz - a->vz;
    return SquareRoot0(d.vx * d.vx + d.vz * d.vz);
}

// Squared XZ distance between two points.
sint32 Dist_xz_sq(SVECTOR *from, SVECTOR *to)
{
    sint32 d[3];

    d[0] = to->vx - from->vx;
    d[2] = to->vz - from->vz;
    return d[0] * d[0] + d[2] * d[2];
}

// Rotates the offset from -> to about Y by (0x800 - angle) with the GTE, then returns a mask of the
// sides of the view cone (shift[0..2] = x, y, z half-width as 9 - shift) the point lies outside of.
uint32 func_80030418(VIEW_WORK *from, VIEW_WORK *to, sint16 *shift, VECTOR *out)
{
    long m[8];
    SVECTOR sv;
    long flag;
    uint32 ret;
    sint32 lim;

    m[1]  = 0;
    m[2]  = 0x1000;
    m[3]  = 0;
    m[4]  = 0x1000;
    m[5]  = 0;
    m[6]  = 0;
    m[7]  = 0;
    sv.vx = to->x_C4 - from->x_C4;
    sv.vy = to->y_C6 - from->y_C6;
    sv.vz = to->z_C8 - from->z_C8;
    m[0]  = 0x1000;
    RotMatrixY(0x800 - from->angle_56, (MATRIX *)m);
    SetRotMatrix((MATRIX *)m);
    SetTransMatrix((MATRIX *)m);
    RotTrans(&sv, out, &flag);
    ret = (uint32)out->vx >> 31;
    if (out->vy < 0)
    {
        ret |= 4;
    }
    if (out->vz < 0)
    {
        ret |= 0x10;
    }
    else
    {
        lim = 9 - shift[0];
        if ((out->vx >= 0 && (out->vx << lim) < out->vz) || (out->vx < 0 && (-out->vx << lim) < out->vz))
        {
            ret |= 2;
        }
    }
    lim = 9 - shift[1];
    if (out->vy >= 0)
    {
        lim = out->vy << lim;
    }
    else
    {
        lim = -out->vy << lim;
    }
    if ((out->vz >= 0 && lim < out->vz) || (out->vz < 0 && lim < -out->vz))
    {
        ret |= 8;
    }
    lim = 9 - shift[2];
    if (out->vz >= 0)
    {
        lim = out->vz << lim;
    }
    else
    {
        lim = -out->vz << lim;
    }
    if ((out->vx >= 0 && lim < out->vx) || (out->vx < 0 && lim < -out->vx))
    {
        ret |= 0x20;
    }
    return ret;
}

uint32 func_80030604(POS14_WORK *from, POS14_WORK *to, sint16 *shift, VECTOR *out)
{
    return func_80030628(from, to, shift, out, ((VIEW_WORK *)from)->angle_56);
}

// Same as func_80030418, with the view angle passed in and the positions at 0x14.
uint32 func_80030628(POS14_WORK *from, POS14_WORK *to, sint16 *shift, VECTOR *out, sint16 angle)
{
    long m[8];
    SVECTOR sv;
    long flag;
    uint32 ret;
    sint32 lim;

    m[1]  = 0;
    m[2]  = 0x1000;
    m[3]  = 0;
    m[4]  = 0x1000;
    m[5]  = 0;
    m[6]  = 0;
    m[7]  = 0;
    sv.vx = to->x_14 - from->x_14;
    sv.vy = to->y_16 - from->y_16;
    m[0]  = 0x1000;
    sv.vz = to->z_18 - from->z_18;
    RotMatrixY(0x800 - angle, (MATRIX *)m);
    SetRotMatrix((MATRIX *)m);
    SetTransMatrix((MATRIX *)m);
    RotTrans(&sv, out, &flag);
    ret = (uint32)out->vx >> 31;
    if (out->vy < 0)
    {
        ret |= 4;
    }
    if (out->vz < 0)
    {
        ret |= 0x10;
    }
    else
    {
        lim = 9 - shift[0];
        if ((out->vx >= 0 && (out->vx << lim) < out->vz) || (out->vx < 0 && (-out->vx << lim) < out->vz))
        {
            ret |= 2;
        }
    }
    lim = 9 - shift[1];
    if (out->vy >= 0)
    {
        lim = out->vy << lim;
    }
    else
    {
        lim = -out->vy << lim;
    }
    if ((out->vz >= 0 && lim < out->vz) || (out->vz < 0 && lim < -out->vz))
    {
        ret |= 8;
    }
    lim = 9 - shift[2];
    if (out->vz >= 0)
    {
        lim = out->vz << lim;
    }
    else
    {
        lim = -out->vz << lim;
    }
    if ((out->vx >= 0 && lim < out->vx) || (out->vx < 0 && lim < -out->vx))
    {
        ret |= 0x20;
    }
    return ret;
}

#ifdef NON_MATCHING
// Rotates the offset from -> to about Y by (0x800 - angle) with the GTE; returns 0x10 if the
// point is behind (z < 0), else 2 if |x| << (9 - *shift) is less than z (inside the view cone).
// Remaining differences: the target stores m[0] late (after the sv setup) and shares one slt/bnez
// to `ori a2,a2,2` between the x >= 0 and x < 0 paths; GCC folds ret |= 2 into li 2.
sint32 func_8003081C(SVECTOR *from, SVECTOR *to, sint16 *shift, sint16 angle)
{
    long m[8];
    SVECTOR sv;
    VECTOR out;
    long flag;
    sint32 ret;
    sint32 sh;

    m[0]  = 0x1000;
    m[1]  = 0;
    m[2]  = 0x1000;
    m[3]  = 0;
    m[4]  = 0x1000;
    m[5]  = 0;
    m[6]  = 0;
    m[7]  = 0;
    sv.vx = to->vx - from->vx;
    sv.vy = to->vy - from->vy;
    sv.vz = to->vz - from->vz;
    RotMatrixY(0x800 - angle, (MATRIX *)m);
    SetRotMatrix((MATRIX *)m);
    SetTransMatrix((MATRIX *)m);
    RotTrans(&sv, &out, &flag);
    ret = 0;
    if (out.vz < 0)
    {
        ret = 0x10;
    }
    else
    {
        sh = 9 - *shift;
        if (out.vx >= 0)
        {
            if ((out.vx << sh) < out.vz)
            {
                ret |= 2;
            }
        }
        else
        {
            if ((-out.vx << sh) < out.vz)
            {
                ret |= 2;
            }
        }
    }
    return ret;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8003081C);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80030934);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80030968);

// Launch velocity (out, three components) and flight time (*time) from `from` to `to` at `speed`;
// `max` caps the horizontal distance when nonzero, `grav` is the drop per half-distance.
void func_800309E0(SVECTOR *from, SVECTOR *to, SVECTOR *out, sint16 *time, sint16 speed, sint16 max, sint16 grav)
{
    VECTOR d;
    VECTOR v;
    sint32 dist;
    sint32 dist_xz;

    d.vx    = to->vx - from->vx;
    d.vy    = to->vy - from->vy;
    d.vz    = to->vz - from->vz;
    dist    = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    dist_xz = SquareRoot0(d.vx * d.vx + d.vz * d.vz);
    if (max != 0 && dist_xz >= max)
    {
        dist_xz = max;
    }
    if (dist != 0 && speed != 0)
    {
        v.vx = (speed * d.vx << 8) / dist;
        if (dist_xz != 0)
        {
            v.vy = speed * (d.vy << 8) / dist_xz - grav * (dist_xz >> 1) / speed;
        }
        else
        {
            v.vy = speed * (d.vy << 8);
        }
        v.vz    = (speed * d.vz << 8) / dist;
        out->vx = v.vx;
        out->vy = v.vy;
        out->vz = v.vz;
        *time   = dist / speed;
    }
    else
    {
        out->vx = 0;
        out->vy = 0;
        out->vz = 0;
        *time   = 0;
    }
}

sint16 func_80030CB8(POS14_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist)
{
    return func_80030CF0(from, to, height, max_dist, 0x100);
}

sint16 func_80030CF0(POS14_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist, sint16 arc)
{
    return func_80030D30((SVECTOR *)&from->x_14, (SVECTOR *)&to->x_C4, height, max_dist, arc);
}

sint16 func_80030D30(SVECTOR *from, SVECTOR *to, sint16 height, sint16 max_dist, sint16 arc)
{
    VECTOR d;
    SVECTOR unused;
    sint32 dist;
    sint32 y;
    sint16 angle;

    d.vx = to->vx - from->vx;
    d.vy = to->vy - from->vy;
    d.vz = to->vz - from->vz;
    dist = SquareRoot0(d.vx * d.vx + d.vz * d.vz);
    if (max_dist != 0 && dist >= max_dist)
    {
        dist = max_dist;
    }
    if (height != 0)
    {
        if (dist != 0)
        {
            y     = height * (d.vy << 8) / dist - arc * (dist >> 1) / height;
            d.vy  = y;
            angle = 0x400 - ratan2(height << 8, y);
        }
        else
        {
            angle = -0x400;
            if (to->vy > from->vy)
            {
                angle = 0x400;
            }
        }
    }
    else
    {
        angle = 0;
    }
    return angle;
}

void func_80030EE8(POS14_WORK *wp, SVECTOR *target, sint16 speed)
{
    VECTOR d;
    VECTOR v;
    sint32 dist;

    d.vx = target->vx - (sint16)wp->x_14;
    d.vy = target->vy - (sint16)wp->y_16;
    d.vz = target->vz - (sint16)wp->z_18;
    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    if (dist != 0)
    {
        v.vx        = (speed * d.vx << 8) / dist;
        v.vy        = (speed * d.vy << 8) / dist;
        v.vz        = (speed * d.vz << 8) / dist;
        wp->vx_44   = v.vx;
        wp->vy_46   = v.vy;
        wp->vz_48   = v.vz;
        wp->time_4A = dist / speed;
    }
    else
    {
        wp->vx_44   = 0;
        wp->vy_46   = 0;
        wp->vz_48   = 0;
        wp->time_4A = 0;
    }
    wp->ax_4C = 0;
    wp->ay_4E = 0;
    wp->az_50 = 0;
}

sint32 Angle_xz_vector(VECTOR *from, VECTOR *to)
{
    sint32 dx;
    sint32 dz;
    sint32 ang;

    dz = (to->vz - from->vz) >> 12;
    dx = to->vx - from->vx;
    if (dz > 0)
    {
        ang = catan(dx / dz) + 0x800;
    }
    else if (dz < 0)
    {
        ang = (0x1000 - catan(-dx / dz)) & 0xFFF;
    }
    else
    {
        ang = 0x400;
        if (dx >= 0)
        {
            ang = 0xC00;
        }
    }
    return ang;
}

sint32 Angle_xz_svector(SVECTOR *from, SVECTOR *to)
{
    sint32 dx;
    sint32 dz;
    sint32 ang;

    dz = (to->vz - from->vz) << 4;
    dx = (to->vx - from->vx) << 16;
    if (dz > 0)
    {
        ang = catan(dx / dz) + 0x800;
    }
    else if (dz < 0)
    {
        ang = (0x1000 - catan(-dx / dz)) & 0xFFF;
    }
    else
    {
        ang = 0x400;
        if (dx >= 0)
        {
            ang = 0xC00;
        }
    }
    return ang;
}

sint32 func_80031268(SVECTOR *from, SVECTOR *to)
{
    return ratan2(to->vx - from->vx, to->vz - from->vz) + 0x800;
}

sint32 func_8003129C(SVECTOR *a, SVECTOR *b)
{
    sint32 dx;
    sint32 dz;

    dx = b->vx - a->vx;
    dz = b->vz - a->vz;
    return (0x1000 - ratan2(SquareRoot0(dx * dx + dz * dz), b->vy - a->vy)) & 0xFFF;
}

void func_80031324(CHILD_PARENT *parent, CHILD_WORK *child, sint16 n)
{
    child->blk_8C    = parent->blk_240[n];
    child->ent_88    = (ENT_14 *)((uint8 *)parent->info_88->tbl_70 + (n + 1) * 0x14);
    child->color_B4  = 0x808080;
    child->parent_B8 = parent;
    child->x_AC = child->x_14 = parent->pos_180[n].x;
    child->y_AE = child->y_16 = parent->pos_180[n].y;
    child->z_B0 = child->z_18   = parent->pos_180[n].z;
    child->x_1C                 = (sint16)child->x_14 << 16;
    child->y_20                 = (sint16)child->y_16 << 16;
    child->z_24                 = (sint16)child->z_18 << 16;
    child->child_id             = parent->slot_F8[n].child_id;
    parent->slot_F8[n].child_id = -1;
}

#ifdef NON_MATCHING
// Only the store order differs (see func_800316BC).
WORK_3C0 *func_80031418(void)
{
    sint32 i;
    WORK_3C0 *wp;
    uint32 used;

    used = D_800987E8;
    for (i = 0; i < 0x10; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_8009F108[i];
            wp->field_10 = 0;
            wp->field_78 = 0;
            D_800987E8 |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->flags              = 3;
            wp->field_74           = 0;
            return wp;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031418);
#endif

#ifdef NON_MATCHING
// Only the store order differs (see func_800316BC).
WORK_5A4 *func_80031498(void)
{
    sint32 i;
    WORK_5A4 *wp;
    uint32 used;

    used = D_80098B20;
    for (i = 0; i < 4; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_800C3580[i];
            wp->field_10 = 0;
            wp->field_78 = 0;
            D_80098B20 |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->flags              = 3;
            wp->field_74           = 0;
            return wp;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031498);
#endif

#ifdef NON_MATCHING
// Only the store order differs (see func_800316BC).
WORK_10C *Open_SHL_WORK(void)
{
    sint32 i;
    WORK_10C *wp;
    uint32 used;

    used = D_800987CC;
    for (i = 0; i < 0x20; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_8009CF88[i];
            wp->field_10 = 0;
            wp->field_78 = 0;
            D_800987CC |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->routine_6          = 3;
            wp->field_74           = 0;
            return wp;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", Open_SHL_WORK);
#endif

#ifdef NON_MATCHING
// Only the store order differs (see func_800316BC).
WORK_10C *func_80031598(void)
{
    sint32 i;
    WORK_10C *wp;
    uint32 used;

    used = D_800989F0;
    for (i = 0; i < 0x10; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_800BFB20[i];
            wp->field_10 = 0;
            wp->field_78 = 0;
            D_800989F0 |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->routine_6          = 3;
            wp->field_74           = 0;
            return wp;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031598);
#endif

WORK_48 *func_80031618(void)
{
    sint32 i;
    sint32 j;
    WORK_48 *wp;
    uint32 used;

    for (j = 0; j < 2; j++)
    {
        used = (&D_80098838)[j];
        for (i = 0; i < 0x20; i++)
        {
            if ((sint32)(used << i) >= 0)
            {
                (&D_80098838)[j] |= 0x80000000 >> i;
                wp                        = &D_800A3B40[i + j * 0x20];
                *(uint16 *)&wp->field_2   = 0;
                *(uint32 *)&wp->flag_4    = 0;
                wp->field_C.word          = 0;
                *(uint32 *)&wp->routine_8 = 0;
                wp->routine_6             = 3;
                wp->field_10              = 0;
                return wp;
            }
        }
    }
    return 0;
}

#ifdef NON_MATCHING
// Only the store order differs: the target keeps the stores in source order around the
// D_800987EC update. A test with the mask as a struct member (MEM_IN_STRUCT_P) gave the
// target order, so the mask words probably belong to a pool struct. Same for the other
// allocators (func_80031418, Open_SHL_WORK, func_80031734); func_800317AC matches as is.
EVE_WORK *func_800316BC(void)
{
    sint32 i;
    EVE_WORK *wp;
    uint32 used;

    used = D_800987EC;
    for (i = 0; i < 0x10; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_800A2D08[i];
            wp->field_10 = 0;
            D_800987EC |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->routine_6          = 3;
            return wp;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800316BC);
#endif

#ifdef NON_MATCHING
// Only the store order differs (see func_800316BC).
WORK_50 *func_80031734(void)
{
    sint32 i;
    WORK_50 *wp;
    uint32 used;

    used = D_800989CC;
    for (i = 0; i < 0x20; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_800BF118[i];
            wp->field_10 = 0;
            D_800989CC |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->routine_6          = 3;
            return wp;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031734);
#endif

WORK_50 *func_800317AC(sint32 i)
{
    WORK_50 *wp;

    if (i < 0x20)
    {
        if ((sint32)(D_800989CC << i) >= 0)
        {
            wp = &D_800BF118[i];
            D_800989CC |= 0x80000000 >> i;
            wp->field_2            = 0;
            *(uint32 *)&wp->flag_4 = 0;
            wp->field_C            = 0;
            wp->field_8            = 0;
            wp->routine_6          = 3;
            wp->field_10           = 0;
            return wp;
        }
        return 0;
    }
    return 0;
}

void func_80031824(WORK_3C0 *wp)
{
    D_8009880C |= 0x80000000 >> (((uint32)wp - (uint32)D_8009F108) / sizeof(WORK_3C0));
    D_8009880C &= D_800987E8;
    wp->routine_0 = 0;
}

void func_8003187C(WORK_5A4 *wp)
{
    D_80098B64 |= 0x80000000 >> (((uint32)wp - (uint32)D_800C3580) / sizeof(WORK_5A4));
    D_80098B64 &= D_80098B20;
    wp->routine_0 = 0;
}

void func_800318D8(WORK_10C *wp)
{
    D_80098808 |= 0x80000000 >> (((uint32)wp - (uint32)D_8009CF88) / sizeof(WORK_10C));
    D_80098808 &= D_800987CC;
    wp->routine_0 = 0;
}

void func_80031930(WORK_10C *wp)
{
    D_80098A60 |= 0x80000000 >> (((uint32)wp - (uint32)D_800BFB20) / sizeof(WORK_10C));
    D_80098A60 &= D_800989F0;
    wp->routine_0 = 0;
}

void func_80031988(WORK_48 *wp)
{
    uint32 i;

    i = ((uint32)wp - (uint32)D_800A3B40) / sizeof(WORK_48);
    (&D_800988C8)[i >> 5] |= 0x80000000 >> (i & 0x1F);
    (&D_800988C8)[i >> 5] &= (&D_80098838)[i >> 5];
    wp->routine_0 = 0;
}

void Close_EVE_WORK(EVE_WORK *wp)
{
    D_80098818 |= 0x80000000 >> (((uint32)wp - (uint32)D_800A2D08) / sizeof(EVE_WORK));
    D_80098818 &= D_800987EC;
    wp->routine_0 = 0;
}

void func_80031A4C(WORK_50 *wp)
{
    D_80098A4C |= 0x80000000 >> (((uint32)wp - (uint32)D_800BF118) / sizeof(WORK_50));
    D_80098A4C &= D_800989CC;
    wp->routine_0 = 0;
}

void func_80031AA4(void)
{
    uint32 a;
    uint32 b;
    uint32 c;
    uint32 d;
    uint32 e;
    uint32 f;
    uint32 g;
    uint32 h;

    a          = D_80098A60;
    b          = D_8009880C;
    c          = D_80098B64;
    d          = D_80098808;
    e          = D_800988C8;
    f          = D_800988CC;
    g          = D_80098818;
    h          = D_80098A4C;
    D_80098A60 = 0;
    D_8009880C = 0;
    D_80098B64 = 0;
    D_80098808 = 0;
    D_800988C8 = 0;
    D_800988CC = 0;
    D_80098818 = 0;
    D_80098A4C = 0;
    D_800989F0 &= ~a;
    D_800987E8 &= ~b;
    D_80098B20 &= ~c;
    D_800987CC &= ~d;
    D_80098838 &= ~e;
    D_8009883C &= ~f;
    D_800987EC &= ~g;
    D_800989CC &= ~h;
}

#ifdef NON_MATCHING
// Signed angle from `angle` to the direction from -> to, limited to +-limit.
// Same difference as func_80031CA4: the target keeps limit in s2 and the result in s1 (moved
// before the call); GCC uses one register. Also the target tests d < 0x800 once (a0) and reuses it.
sint16 func_80031BEC(SVECTOR *from, SVECTOR *to, sint16 angle, uint32 limit)
{
    uint32 d;
    uint32 r;

    r = limit;
    d = (Angle_xz_svector(from, to) - angle) & 0xFFF;
    if (d < 0x800)
    {
        if (d < (sint16)limit * 2)
        {
            r = d;
        }
    }
    if (d >= 0x800)
    {
        if (0x1000 - d < (sint16)r * 2)
        {
            r = 0x1000 - d;
        }
    }
    if (d >= 0x801)
    {
        return -r;
    }
    return r;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031BEC);
#endif

#ifdef NON_MATCHING
// Register allocation only: the target keeps the limit parameter in s2 and the result copy in s1;
// GCC merges them into one register here.
sint16 func_80031CA4(SVECTOR *from, SVECTOR *to, sint16 angle, uint32 limit)
{
    uint32 d;
    uint32 r;

    r = limit;
    d = (func_8003129C(from, to) - angle) & 0xFFF;
    if (d < 0x800)
    {
        if (d < (sint16)r * 2)
        {
            r = d;
        }
    }
    else
    {
        if (0x1000 - d < (sint16)limit * 2)
        {
            r = 0x1000 - d;
        }
    }
    if (d >= 0x801)
    {
        return -r;
    }
    return r;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031CA4);
#endif

// Signed angle difference (a - b) on a 0x1000 circle, limited to +-limit.
sint16 Angle_diff_clamp(sint16 a, sint16 b, sint16 limit)
{
    sint16 d;
    sint16 r;

    r = limit;
    d = a - b;
    if (d < 0)
    {
        d += 0x1000;
    }
    if (d < 0x800)
    {
        if (d < limit)
        {
            r = d;
        }
    }
    else
    {
        if (limit > 0x1000 - d)
        {
            r = d - 0x1000;
        }
        else
        {
            r = -limit;
        }
    }
    return r;
}

#ifdef NON_MATCHING
// 1 if the direction from -> to is within +-half1 of center1 and within +-half2 of
// (center2 - 0x800); the angles are on a 0x1000 circle.
// Logic is right; the target keeps the result in v0 (set to 0 right after the call) and
// angle in a copy (v1), while GCC puts the result in a scratch register and reads angle from v0.
sint32 func_80031DCC(VECTOR *from, sint32 center1, sint32 half1, VECTOR *to, sint32 center2, sint32 half2)
{
    sint32 angle;
    sint32 d1;
    sint32 d2;

    angle = Angle_xz_vector(from, to);
    d2    = (half2 + (angle - (center2 - 0x800))) & 0xFFF;
    d1    = (half1 + (angle - center1)) & 0xFFF;
    if ((sint16)half1 * 2 < d1)
    {
        return 0;
    }
    return !((sint16)half2 * 2 < d2);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031DCC);
#endif

#ifdef NON_MATCHING
// Same as func_80031DCC without the 0x800 offset (same register differences).
sint32 func_80031E60(VECTOR *from, sint32 center1, sint32 half1, VECTOR *to, sint32 center2, sint32 half2)
{
    sint32 angle;
    sint32 d1;
    sint32 d2;

    angle = Angle_xz_vector(from, to);
    d2    = (half2 + (angle - center2)) & 0xFFF;
    d1    = (half1 + (angle - center1)) & 0xFFF;
    if ((sint16)half1 * 2 < d1)
    {
        return 0;
    }
    return !((sint16)half2 * 2 < d2);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031E60);
#endif

#ifdef NON_MATCHING
// func_80031DCC on SVECTORs (same register differences).
sint32 func_80031EF0(SVECTOR *from, sint32 center1, sint32 half1, SVECTOR *to, sint32 center2, sint32 half2)
{
    sint32 angle;
    sint32 d1;
    sint32 d2;

    angle = Angle_xz_svector(from, to);
    d2    = (half2 + (angle - (center2 - 0x800))) & 0xFFF;
    d1    = (half1 + (angle - center1)) & 0xFFF;
    if ((sint16)half1 * 2 < d1)
    {
        return 0;
    }
    return !((sint16)half2 * 2 < d2);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031EF0);
#endif

#ifdef NON_MATCHING
// Quantizes the facing of from -> to against `base`: the low 12 bits are an angle, bits 16+ say
// which side (0: none/forward, 1: behind, 2: right, 3: left). to defaults to the zero vector
// (D_80097CF4) when bit 0 of to->pad is clear, in which case `to` becomes the source.
// Only the prologue differs: the target saves s0 and zeroes it (ret = 0) before saving s2 and
// copying a2; GCC does the a2 copy first.
sint32 func_80031F84(SVECTOR *from, SVECTOR *to, sint16 base, uint16 mode)
{
    sint32 ret;
    sint32 ang;
    sint32 d;

    ret = 0;
    if (!(to->pad & 1))
    {
        from = to;
        to   = &D_80097CF4;
    }
    ang = Angle_xz_svector(from, to);
    if (mode == 0)
    {
        if ((((sint16)ang - base + 0x400) & 0xFFF) < 0x800)
        {
            ret = ((sint16)ang + 0x800) & 0xFFF;
        }
        else
        {
            ret = (ang & 0xFFF) | 0x10000;
        }
    }
    else
    {
        d = (sint16)ang - base;
        if (((d + 0x200) & 0xFFF) < 0x400)
        {
            ret = ((sint16)ang + 0x800) & 0xFFF;
        }
        else if (((d + 0x600) & 0xFFF) < 0x400)
        {
            ret = (((sint16)ang - 0x400) & 0xFFF) | 0x30000;
        }
        else if (((d + 0xA00) & 0xFFF) < 0x400)
        {
            ret = (ang & 0xFFF) | 0x10000;
        }
        else if (((d + 0xE00) & 0xFFF) < 0x400)
        {
            ret = (((sint16)ang + 0x400) & 0xFFF) | 0x20000;
        }
    }
    return ret;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80031F84);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800320B8);

void func_800321C8(KEY_WORK *wp, sint32 unused, uint32 set, sint32 idx)
{
    KEY_ENT *base;
    KEY_ENT *ent;

    switch (set >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            base = Key_tbl_a[set];
            break;
        case 4:
        case 5:
            if (wp->alt_170 != 0)
            {
                base = Key_tbl_c_alt[set];
            }
            else
            {
                base = Key_tbl_c[set];
            }
            break;
        case 6:
        case 7:
            if (wp->alt_171 != 0)
            {
                base = Key_tbl_d_alt[set];
            }
            else
            {
                base = Key_tbl_d[set];
            }
            break;
        case 8:
        default:
            base = Key_tbl_b[set];
            break;
    }
    wp->tbl_F8       = base;
    ent              = base + idx;
    wp->ent_FC       = ent;
    wp->set_104      = set;
    wp->cmd_100.word = ent->cmd.word;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800322A8);

void func_80032304(ATTACH_WORK *wp, sint32 idx, sint32 step)
{
    KEY_ENT *ent;

    ent        = ((KEY_ENT **)wp->val_90)[idx];
    wp->idx_AC = idx;
    wp->seq_94 = ent;
    ent        = ent + step;
    wp->ptr_98 = ent;
    wp->cmd_A4 = ent->cmd;
    func_80033A28(wp);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8003234C);

#ifdef NON_MATCHING
// Differs: lw/lbu order at entry, and the target keeps ctl in a2 with a copy in a1.
void func_800323FC(KEY_WORK *wp, sint16 a)
{
    KEY_ENT *ent;
    sint32 ctl;
    uint32 pad[2];

    wp->field_106 = a;
    ent           = wp->ent_FC;
    if (--wp->cmd_100.b.time == 0)
    {
        ctl = ent->cmd.b.ctl;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->cmd_100.b.time = ent->cmd.b.time;
            }
            else
            {
                ent              = wp->tbl_F8 + (ctl & 0x7F);
                wp->ent_FC       = ent;
                wp->cmd_100.word = ent->cmd.word;
            }
        }
        else
        {
            ent              = wp->ent_FC + 1;
            wp->ent_FC       = ent;
            wp->cmd_100.word = ent->cmd.word;
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800323FC);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80032488);

#ifdef NON_MATCHING
// Differs: registers only. The target has ent in v1, ctl in a2 and the copy (jump) in a1.
void func_80032538(ATTACH_WORK *wp)
{
    KEY_ENT *ent;
    sint32 ctl;
    sint32 jump;
    uint32 pad[2];

    ent = wp->ptr_98;
    if (--wp->cmd_A4.b.time == 0)
    {
        ctl  = ent->cmd.b.ctl;
        jump = ctl;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->cmd_A4.b.time = ent->cmd.b.time;
            }
            else
            {
                wp->ptr_98 = wp->seq_94 + (jump & 0x7F);
                wp->cmd_A4 = wp->ptr_98->cmd;
            }
        }
        else
        {
            wp->ptr_98 = wp->ptr_98 + 1;
            wp->cmd_A4 = wp->ptr_98->cmd;
        }
    }
    func_80033A28(wp);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80032538);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800325D4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800329D4);

void func_800331A0(SKEL_WORK *wp, sint32 n, SVECTOR *rot, SVECTOR *off)
{
    VECTOR tmp;
    VECTOR scale;
    SVECTOR unused;
    SVECTOR v;
    MATRIX rm;

    v.vx = off->vx << Scratch_scale_shift;
    v.vy = off->vy << Scratch_scale_shift;
    v.vz = off->vz << Scratch_scale_shift;
    ApplyMatrix(&Scratch_mtx, &v, &tmp);
    RotMatrix(rot, &rm);
    MulMatrix(&Scratch_mtx, &rm);
    Scratch_mtx.t[0] += tmp.vx;
    Scratch_mtx.t[1] += tmp.vy;
    Scratch_mtx.t[2] += tmp.vz;
    v.vx          = wp->x_14 << Scratch_scale_shift;
    v.vy          = wp->y_16 << Scratch_scale_shift;
    v.vz          = wp->z_18 << Scratch_scale_shift;
    wp->pos[n].vx = (Scratch_mtx.t[0] + v.vx * 7 + 4) >> 3;
    wp->pos[n].vy = (Scratch_mtx.t[1] + v.vy * 7 + 4) >> 3;
    wp->pos[n].vz = (Scratch_mtx.t[2] + v.vz * 7 + 4) >> 3;
    wp->mtx[n]    = Scratch_mtx;
    scale.vx      = D_80097CFC << Scratch_scale_shift;
    scale.vy      = scale.vx;
    scale.vz      = scale.vx;
    ScaleMatrix(&wp->mtx[n], &scale);
}

MATRIX *D_80098A80;
extern MATRIX D_800BC728[];

void func_800333A0(void)
{
    D_80098A80 = D_800BC728;
}

// Pushes a matrix onto the matrix stack at D_80098A80.
void Matrix_push(MATRIX *src)
{
    *--D_80098A80 = *src;
}

// Pops a matrix from the matrix stack at D_80098A80.
void Matrix_pop(MATRIX *dst)
{
    *dst = *D_80098A80;
    D_80098A80++;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8003346C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800334C4);

void func_80033500(WORK_5A4 *wp)
{
    sint32 i;

    wp->base.r = wp->base.g = wp->base.b = 0x20;
    for (i = 0; i < 24; i++)
    {
        wp->tbl[i].r = wp->tbl[i].g = wp->tbl[i].b = 0x20;
    }
    wp->flags |= 0x40;
}

void func_8003354C(WORK_3C0 *wp)
{
    sint32 i;

    wp->base.r = wp->base.g = wp->base.b = 0x20;
    for (i = 0; i < 13; i++)
    {
        wp->tbl[i].r = wp->tbl[i].g = wp->tbl[i].b = 0x20;
    }
    wp->flags |= 0x40;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80033598);

// Unpacks 75 twelve-bit values (three per SVECTOR) of the pose selected by wp into the scratchpad.
#ifdef NON_MATCHING
void func_80033A28(ATTACH_WORK *wp)
{
    uint32 *s;
    sint16 *d;
    sint32 i;

    Mem_copy4(((uint32 **)((uint32 ***)wp->ptr_A0)[wp->idx_AC])[wp->ptr_98->cmd.b.b0], Scratch_pose_packed, 0x20);
    d = Scratch_pose_vtx;
    s = Scratch_pose_packed;
    i = 3;
    do
    {
        *d++ = *s & 0xFFF;
        *d++ = (*s & 0xFFF000) >> 12;
        *d++ = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
        s++;
        d++;
        *d++ = (*s & 0xFFF0) >> 4;
        *d++ = (*s & 0x0FFF0000) >> 16;
        *d++ = ((*s & 0xF0000000) >> 28) | (((uint8 *)s)[4] << 4);
        s++;
        d++;
        *d++ = (*s & 0xFFF00) >> 8;
        *d++ = (*s & 0xFFF00000) >> 20;
        s++;
        *d++ = *s & 0xFFF;
        d++;
        *d++ = (*s & 0xFFF000) >> 12;
        *d++ = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
        s++;
        *d++ = (*s & 0xFFF0) >> 4;
        d++;
        *d++ = (*s & 0x0FFF0000) >> 16;
        *d++ = ((*s & 0xF0000000) >> 28) | (((uint8 *)s)[4] << 4);
        s++;
        *d++ = (*s & 0xFFF00) >> 8;
        d++;
        *d++ = (*s & 0xFFF00000) >> 20;
        s++;
        *d++ = *s & 0xFFF;
        *d++ = (*s & 0xFFF000) >> 12;
        d++;
        *d++ = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
        s++;
        *d++ = (*s & 0xFFF0) >> 4;
        *d++ = (*s & 0x0FFF0000) >> 16;
        d++;
        *d++ = ((*s & 0xF0000000) >> 28) | (((uint8 *)s)[4] << 4);
        s++;
        *d++ = (*s & 0xFFF00) >> 8;
        *d++ = (*s & 0xFFF00000) >> 20;
        d++;
        s++;
    } while (--i != 0);
    *d++                            = *s & 0xFFF;
    *d++                            = (*s << 8) >> 20;
    *d++                            = ((uint8 *)s)[3] | ((s[1] & 0xF) << 8);
    *(uint16 *)&Scratch_pose_vtx[0] = ((sint32)(*(uint16 *)&Scratch_pose_vtx[0] << 20)) >> 20;
    *(uint16 *)&Scratch_pose_vtx[1] = ((sint32)(*(uint16 *)&Scratch_pose_vtx[1] << 20)) >> 20;
    *(uint16 *)&Scratch_pose_vtx[2] = ((sint32)(*(uint16 *)&Scratch_pose_vtx[2] << 20)) >> 20;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80033A28);
#endif

void func_80033D80(MATRIX *src, MATRIX *dst, SVECTOR *rot, SVECTOR *v)
{
    VECTOR tmp;
    MATRIX rm;

    Scratch_mtx = *src;
    ApplyMatrix(&Scratch_mtx, v, &tmp);
    Scratch_mtx.t[0] += tmp.vx;
    Scratch_mtx.t[1] += tmp.vy;
    Scratch_mtx.t[2] += tmp.vz;
    RotMatrix(rot, &rm);
    MulMatrix(&Scratch_mtx, &rm);
    *dst = Scratch_mtx;
}

void func_80033EBC(void)
{
    D_800988E0 = 0;
    D_80098798 = 0xFF;
    D_8009A306 = 0;
    D_8009A31A = 0;
    D_8009A32E = 0;
    D_8009A342 = 0;
    D_80098560 = 0;
    D_80098564 = 0;
    D_80098568 = 0;
}

// Rotates unit vector a toward b by `angle` when their dot product (<< 4) is below `limit`
// (the high half of `limit` is the third component of the rotation vectors); result in out.
SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 angle, sint32 limit)
{
    sint32 dot0;

    if (((a->vx * b->vx + a->vy * b->vy + a->vz * b->vz) << 4) >= limit)
    {
        *out = *a;
    }
    else
    {
        D_8009857C.m[0][2] = b->vx;
        D_8009857C.m[1][2] = b->vy;
        D_8009857C.m[2][2] = b->vz;
        D_8009860C.vx      = a->vx;
        D_8009860C.vy      = a->vy;
        D_8009860C.vz      = a->vz;
        D_8009861C.vx      = b->vx;
        D_8009861C.vy      = b->vy;
        D_8009861C.vz      = b->vz;
        OuterProduct12(&D_8009860C, &D_8009861C, &D_8009863C);
        OuterProduct12(&D_8009861C, &D_8009863C, &D_8009864C);
        D_800985FC.vx = angle;
        D_80098604.vx = -angle;
        D_80098604.vy = 0;
        D_800985FC.vy = 0;
        D_800985FC.vz = D_80098604.vz = (uint32)limit >> 16;
        D_8009857C.m[0][1]            = D_8009863C.vx;
        D_8009857C.m[1][1]            = D_8009863C.vy;
        D_8009857C.m[2][1]            = D_8009863C.vz;
        D_8009857C.m[0][0]            = D_8009864C.vx;
        D_8009857C.m[1][0]            = D_8009864C.vy;
        D_8009857C.m[2][0]            = D_8009864C.vz;
        ApplyMatrix(&D_8009857C, &D_800985FC, &D_8009860C);
        dot0 = a->vx * D_8009860C.vx + a->vy * D_8009860C.vy + a->vz * D_8009860C.vz;
        ApplyMatrix(&D_8009857C, &D_80098604, &D_8009861C);
        if (a->vx * D_8009861C.vx + a->vy * D_8009861C.vy + a->vz * D_8009861C.vz >= dot0)
        {
            VectorNormalS(&D_8009861C, &D_800985FC);
        }
        else
        {
            VectorNormalS(&D_8009860C, &D_800985FC);
        }
        *out = D_800985FC;
    }
    return out;
}

// Queues an entry (up to 0x40) and copies v into the slots selected by owner->mask_4.
sint32 func_800341BC(SVECTOR *v, uint32 a1, uint32 a2, uint32 a3, uint32 a4, SLOT_OWNER *owner, uint32 a6, uint32 a7, uint32 a8)
{
    SLOT_REQ *req;
    uint32 n;
    uint32 mask;
    uint32 i;

    n = D_800988E0;
    if (n >= 0x40)
    {
        return 0;
    }
    req           = &D_800A2F48[n];
    req->v        = *v;
    req->v.pad    = (a1 >> 2) | a2 | a3;
    req->flags    = (a4 << 24) | ((uint32)owner & 0x7FFFFF) | a7;
    D_800A32E0[n] = a6;
    i             = owner->mask_4;
    mask          = i & D_80098798;
    D_800988E0++;
    if (mask & 0x80)
    {
        mask &= ~0xFF;
    }
    owner->mask_4 = mask | a8;
    if (mask != 0)
    {
        for (i = 0; i < 0x18; i++)
        {
            if (mask > 0x7FFFFFFF)
            {
                *(SVECTOR *)(D_800BE478[i] + 0xBC) = *v;
            }
            mask <<= 1;
        }
    }
    return 1;
}

// Like func_800341BC, but queues two entries (va, vb) and copies their midpoint to the slots.
sint32 func_8003430C(SVECTOR *va, uint32 pad_a, SVECTOR *vb, uint32 pad_b, uint32 a4, uint32 a5, uint32 a6, SLOT_OWNER *owner, uint32 val,
                     uint32 a9, uint32 a10)
{
    SLOT_REQ *req;
    SVECTOR mid;
    uint32 n;
    uint32 mask;
    uint32 i;

    n = D_800988E0;
    if (n >= 0x3F)
    {
        return 0;
    }
    req           = &D_800A2F48[n];
    req->v        = *va;
    req->v.pad    = (pad_a >> 2) | a4 | a5;
    req->flags    = (a6 << 24) | ((uint32)owner & 0x7FFFFF) | a9;
    D_800A32E0[n] = val;
    n++;
    req           = &D_800A2F48[n];
    req->v        = *vb;
    req->v.pad    = (pad_b >> 2) | a4 | a5;
    req->flags    = (a6 << 24) | ((uint32)owner & 0x7FFFFF) | a9;
    D_800A32E0[n] = val;
    i             = owner->mask_4;
    mask          = i & D_80098798;
    D_800988E0 += 2;
    owner->mask_4 = mask | a10;
    if (mask != 0)
    {
        for (i = 0; i < 0x18; i++)
        {
            if (mask > 0x7FFFFFFF)
            {
                mid.vx                             = (va->vx + vb->vx) >> 1;
                mid.vy                             = (va->vy + vb->vy) >> 1;
                mid.vz                             = (va->vz + vb->vz) >> 1;
                *(SVECTOR *)(D_800BE478[i] + 0xBC) = mid;
            }
            mask <<= 1;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8003450C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800346AC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80034EB8);

// Claims the first free bit of D_80098798 (24 slots), marks it in owner->mask_4 and stores value in D_800BE478[slot].
sint32 func_8003545C(uint32 value, SLOT_OWNER *owner)
{
    sint32 i;
    uint32 bit;

    i = 0;
    if (D_80098798 >= 0xFFFFFF00)
    {
        return -1;
    }
    for (bit = 0x80000000; i < 0x18; i++, bit >>= 1)
    {
        if (!(D_80098798 & bit))
        {
            D_80098798 |= bit;
            owner->mask_4 |= bit;
            D_800BE478[i] = value;
            return i;
        }
    }
    return -1;
}

void func_800354E0(uint32 n)
{
    D_80098798 &= ~(0x80000000 >> n);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80035508);

MATRIX *func_800355F0(MATRIX *out, sint32 n, sint32 yaw)
{
    SVECTOR rot;
    VECTOR pos;
    MATRIX m;
    MATRIX inv;

    rot.vx = -yaw & 0xFFF;
    rot.vy = ((uint16)Player_work[n].unk56 + Player_work[n].unk116 + 0x800) & 0xFFF;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &m);
    TransposeMatrix(&m, &inv);
    pos.vx = -Player_work[n].pos.vx;
    pos.vy = 0x96 - Player_work[n].pos.vy;
    pos.vz = -Player_work[n].pos.vz;
    ApplyMatrixLV(&inv, &pos, (VECTOR *)inv.t);
    *out = inv;
    return out;
}

#ifdef NON_MATCHING
// best attempt: target computes pl + sel * 8 at the end of each branch (after the last position
// store) and reaches the record through it; ours computes it once after the merge, hoisted early.
void func_80035724(sint32 unused0, sint32 unused1, PL_WORK *pl, sint32 idx, sint32 flag)
{
    OBJ_10C *wp;
    sint32 sel;
    SVECTOR unused; // GCC reserves its 8 bytes; the target frame has them

    wp = (OBJ_10C *)func_80031598();
    if (wp != 0)
    {
        wp->flag_3 = 0;
        if (idx >= 0)
        {
            wp->slot_D = func_8003545C((uint32)wp, (SLOT_OWNER *)(D_800A2F48[idx].flags & 0x7FFFFF));
            if (wp->slot_D >= 0)
            {
                wp->flag_3 = 0x80;
            }
        }
        wp->routine_0 = 1;
        if (flag != 0)
        {
            sel         = pl->unk170;
            wp->field_2 = D_80089A8B[sel * 12];
            wp->x_14    = pl->unk3C8[0];
            wp->y_16    = pl->unk3C8[1];
            wp->z_18    = pl->unk3C8[2];
        }
        else
        {
            sel         = pl->unk171;
            wp->field_2 = D_80089A8B[sel * 12];
            wp->x_14    = pl->unk3E0[0];
            wp->y_16    = pl->unk3E0[1];
            wp->z_18    = pl->unk3E0[2];
        }
        if (pl->rec[sel].val != 0x7FFF && sel != 4 && sel != 7 && (uint32)(sel - 0xC) >= 2)
        {
            pl->rec[sel].val = pl->rec[sel].val - 1;
        }
        wp->field_1A = flag;
        wp->x_1C     = wp->x_14 << 16;
        wp->field_C  = pl->unk01;
        wp->y_20     = wp->y_16 << 16;
        wp->z_24     = wp->z_18 << 16;
        wp->field_64 = pl->unk56;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80035724);
#endif

void func_800358E8(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800358F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80035C90);

#ifdef NON_MATCHING
void func_8003606C(void)
{
    SVECTOR pos;
    SVECTOR unused;
    WORK_3C0 *w3;
    WORK_5A4 *w5;
    WORK_10C *w1;
    WORK_3C0 *p3;
    WORK_5A4 *p5;
    WORK_10C *p1;
    uint32 d;
    sint32 dx;
    sint32 dz;
    sint32 k;
    sint32 j;

    for (k = 0; k < 2; k++)
    {
        pos = Player_work[k].pos;
        w3  = D_8009F108;
        for (j = 0; j < 0x10; j++)
        {
            p3 = w3++;
            if (p3->routine_0 | 1)
            {
                dx = (p3->x_14 - pos.vx) >> 1;
                dz = (p3->z_18 - pos.vz) >> 1;
                d  = dx * dx + dz * dz;
                if (d > 0x10000000)
                {
                    p3->dist_80[k] = -1;
                }
                else
                {
                    p3->dist_80[k] = d << 2;
                }
            }
        }
        w5 = D_800C3580;
        for (j = 0; j < 4; j++)
        {
            p5 = w5++;
            if (p5->routine_0 | 1)
            {
                dx = (p5->x_14 - pos.vx) >> 1;
                dz = (p5->z_18 - pos.vz) >> 1;
                d  = dx * dx + dz * dz;
                if (d > 0x10000000)
                {
                    p5->dist_80[k] = -1;
                }
                else
                {
                    p5->dist_80[k] = d << 2;
                }
            }
        }
        w1 = D_8009CF88;
        for (j = 0; j < 0x20; j++)
        {
            p1 = w1++;
            if (p1->routine_0 | 1)
            {
                dx = (p1->x_14 - pos.vx) >> 1;
                dz = (p1->z_18 - pos.vz) >> 1;
                d  = dx * dx + dz * dz;
                if (d > 0x10000000)
                {
                    p1->dist_80[k] = -1;
                }
                else
                {
                    p1->dist_80[k] = d << 2;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8003606C);
#endif

void *func_80036294(uint32 id)
{
    sint32 kind;

    kind = func_8002FE74(id & 0xFF);
    switch (kind)
    {
        case 0x00:
            return &Player_work[id & 0xF];
        case 0x10:
            return &D_800BFB20[id & 0xF];
        case 0x20:
            return &D_8009F108[id & 0x1F];
        case 0x40:
            return &D_800C3580[id & 0x1F];
        case 0x60:
            return &D_8009CF88[id & 0x1F];
        case 0x80:
            return &D_800A3B40[id & 0x3F];
        case 0xC0:
            return &D_800A2D08[id & 0x1F];
        case 0xE0:
            return &D_800BF118[id & 0x1F];
        default:
            return 0;
    }
}

void func_80036470(uint8 *p)
{
    p[7] = 0;
}

void func_80036478(uint8 *p, uint8 a, uint32 b)
{
    p[6]  = a;
    p[15] = b >> 4;
    p[7]  = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_8003648C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_800364B0);

void func_8003697C(void)
{
    Scratch_scale_shift = 0;
    Scratch_fog_0       = 0xE00;
    Scratch_fog_1       = 0xE00;
    SetFogNear(D_800BC81C, 0x180);
}

void func_800369C0(void)
{
    uint32 n;

    Scratch_scale_shift = 1;
    Scratch_fog_0       = 0x680;
    Scratch_fog_1       = 0x680;
    n                   = D_800BC81C * 2;
    if (n >= 0x3333)
    {
        n = D_800BC81C;
    }
    SetFogNear(n, 0x180);
}

void func_80036A1C(void)
{
    uint32 n;

    Scratch_scale_shift = 2;
    Scratch_fog_0       = 0x300;
    Scratch_fog_1       = 0x300;
    n                   = D_800BC81C * 4;
    if (n >= 0x3333)
    {
        n = D_800BC81C;
    }
    SetFogNear(n, 0x180);
}

void func_80036A78(uint16 v)
{
    Scratch_fog_1 = v;
}

void func_80036A88(sint32 r, sint32 g, sint32 b, sint32 n)
{
    SetFarColor(r, g, b);
    SetFogNear(n, 0x180);
    D_8009A370 = r;
    D_8009A371 = g;
    D_8009A372 = b;
    D_8009A374 = n;
}

#ifdef NON_MATCHING
void func_80036B00(SVECTOR *v)
{
    // best attempt: GCC hoists the later loads above the earlier stores
    v->vx  = D_8009A370;
    v->vy  = D_8009A371;
    v->vz  = D_8009A372;
    v->pad = D_8009A374;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80036B00);
#endif

#ifdef NON_MATCHING
// best attempt: the copy is right; the target keeps &D_800BC818 in s0 (set up before the
// SetFarColor loads and reused as the copy end pointer), ours rebuilds it as D_800BC818-0x20.
void func_80036B40(void)
{
    FOG_BLOCK *src = (FOG_BLOCK *)(&D_800BC818 - 0x20);

    SetFarColor(D_800BC818, D_800BC819, D_800BC81A);
    SetFogNear(D_800BC81C, 0x180);
    D_8009A350 = *src;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80036B40);
#endif

#ifdef NON_MATCHING
// best attempt: target keeps &D_8009A306 in a register (a3) for the first compare and the loop;
// ours folds the first compare to lui+%lo and builds the base again for the loop.
void func_80036C50(uint8 id, sint32 val)
{
    SLOT_ENT *e = (SLOT_ENT *)&D_8009A306;
    sint8 *flag;
    uint32 i;

    if (e->id != id && D_8009A31A != id && D_8009A32E != id && D_8009A342 != id && D_80098560 < 4)
    {
        flag = &e->flag;
        for (i = 0; i < 4; i++)
        {
            if (e->id == 0)
            {
                e->id             = id;
                D_8009A310[i].val = val;
                if (*flag != 0)
                {
                    *flag = 0;
                }
                else
                {
                    *flag = 1;
                }
                D_80098560++;
                return;
            }
            e++;
            flag += sizeof(SLOT_ENT);
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80036C50);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", func_80036D40);

// Loads a scene block: 0x20 bytes of src into D_800BADB0, and a 0x28-byte fog block (far color at
// +0x20, near at +0x24, scratchpad byte at +0x23) into the three fog copies.
void func_800371A0(void *src, FOG_BLOCK *fog)
{
    Mem_copy32(src, D_800BADB0, 8);
    D_800BC7F8 = *fog;
    D_8009A350 = D_800BC7F8;
    SetFarColor(fog->b[0x20], fog->b[0x21], fog->b[0x22]);
    SetFogNear(*(uint16 *)&fog->b[0x24], 0x180);
    D_800C0DC0    = *fog;
    Scratch_fog_2 = fog->b[0x23];
}

uint32 func_80037440(void)
{
    sint32 i;
    sint32 sel;
    sint32 idx;
    uint32 id;

    sel                       = Player_work[0].unk170;
    ((uint32 *)D_8009856C)[0] = 0;
    ((uint32 *)D_8009856C)[1] = 0;
    ((uint32 *)D_8009856C)[2] = 0;
    ((uint32 *)D_8009856C)[3] = 0;
    for (i = 0; i < 16; i++)
    {
        if (D_800BFB20[i].routine_0 & 1)
        {
            id = D_800BFB22[i].routine_0 - 0x80; // low byte of field_2
            if ((sint32)id < 16)
            {
                D_8009856C[id]++;
            }
        }
    }
    if (sel == 6)
    {
        idx = (sint8)Player_work[0].rec[6].unk04[0];
    }
    else
    {
        idx = Player_work[0].rec[sel].idx[3];
    }
    if (idx >= 4)
    {
        idx = 3;
    }
    return D_800899E0[idx][sel] > D_8009856C[sel];
}
