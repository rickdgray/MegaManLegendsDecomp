#include "common.h"
#include "psyq/abs.h"
#include "psyq/libgte.h"
#include "stage.h"

// Called only from this file
void light_init(void);
void func_8003A538(void);
void func_8003A918(uint32 *p);

// Pool (.sbss) variables this file reaches through $gp.
CVECTOR D_80098858[3];
SVECTOR D_80098870[3];
sint32 D_80098900[3];

void func_8003A3B4(void)
{
    sint32 i;
    sint32 j;

    for (i = 0; i < 0x800; i++)
    {
        if (Stage_idx_tbl[i].ptr == NULL)
        {
            continue;
        }
        for (j = 0; j < HED_ENT_MAX; j++)
        {
            if (Stage_hed_tbl[j].model == 0)
            {
                break;
            }
            if ((Stage_hed_tbl[j].model & 0xFFFFFF) == ((uint32)Stage_idx_tbl[i].ptr & 0xFFFFFF))
            {
                Stage_idx_tbl[i].val = Stage_idx_tbl[i].ptr->unk18[1];
                break;
            }
        }
    }
    light_init();
    func_8003A538();
}

void light_init(void)
{
    D_80098870[0].vx = 0x93C;
    D_80098870[0].vy = 0x93C;
    D_80098870[0].vz = 0x93C;
    D_80098870[1].vx = 0x93C;
    D_80098870[1].vy = 0x93C;
    D_80098870[1].vz = -0x93C;
    D_80098858[0].r  = 0xA0;
    D_80098858[0].g  = 0xA0;
    D_80098858[0].b  = 0xA0;
    D_80098858[1].r  = 0x60;
    D_80098858[1].g  = 0x60;
    D_80098858[1].b  = 0x60;
    D_80098870[2].vx = 0;
    D_80098870[2].vy = 0;
    D_80098870[2].vz = 0;
    D_80098858[2].r  = 0;
    D_80098858[2].g  = 0;
    D_80098858[2].b  = 0;
    D_80098900[0]    = 0xA0;
    D_80098900[1]    = 0xA0;
    D_80098900[2]    = 0xA0;
}

void func_8003A538(void)
{
    MATRIX m;
    sint32 ent;
    STG_MODEL *model;
    uint32 *part;
    uint32 head;
    uint32 lod;
    uint32 n;
    uint32 i;

    SetBackColor(D_80098900[0], D_80098900[1], D_80098900[2]);
    m.m[0][0] = D_80098870[0].vx;
    m.m[0][1] = D_80098870[0].vy;
    m.m[0][2] = D_80098870[0].vz;
    m.m[1][0] = D_80098870[1].vx;
    m.m[1][1] = D_80098870[1].vy;
    m.m[1][2] = D_80098870[1].vz;
    m.m[2][0] = D_80098870[2].vx;
    m.m[2][1] = D_80098870[2].vy;
    m.m[2][2] = D_80098870[2].vz;
    SetLightMatrix(&m);
    m.m[0][0] = D_80098858[0].r << 4;
    m.m[1][0] = D_80098858[0].g << 4;
    m.m[2][0] = D_80098858[0].b << 4;
    m.m[0][1] = D_80098858[1].r << 4;
    m.m[1][1] = D_80098858[1].g << 4;
    m.m[2][1] = D_80098858[1].b << 4;
    m.m[0][2] = D_80098858[2].r << 4;
    m.m[1][2] = D_80098858[2].g << 4;
    m.m[2][2] = D_80098858[2].b << 4;
    SetColorMatrix(&m);
    for (ent = 0; Stage_hed_tbl[ent].model != 0; ent++)
    {
        model = (STG_MODEL *)(Stage_hed_tbl[ent].model & 0xFFFFFF);
        for (lod = STG_LOD_WORD; lod < STG_LOD_WORD + STG_LOD_NUM; lod++)
        {
            part = (uint32 *)(model->lod[lod - STG_LOD_WORD] & 0xFFFFFF);
            head = *part;
            part += (head & 0xFF) + 1;
            n = (head & 0x3F00) >> 7;
            for (i = 0; i < n; i += 2)
            {
                func_8003A918(&part[i]);
            }
        }
    }
}

void func_8003A744(void)
{
    MATRIX m;
    STG_MODEL *model;
    uint32 *part;
    uint32 head;
    uint32 lod;
    uint32 n;
    uint32 i;

    model = &Support_stg[1];
    SetBackColor(D_80098900[0], D_80098900[1], D_80098900[2]);
    m.m[0][0] = D_80098870[0].vx;
    m.m[0][1] = D_80098870[0].vy;
    m.m[0][2] = D_80098870[0].vz;
    m.m[1][0] = D_80098870[1].vx;
    m.m[1][1] = D_80098870[1].vy;
    m.m[1][2] = D_80098870[1].vz;
    m.m[2][0] = D_80098870[2].vx;
    m.m[2][1] = D_80098870[2].vy;
    m.m[2][2] = D_80098870[2].vz;
    SetLightMatrix(&m);
    m.m[0][0] = D_80098858[0].r << 4;
    m.m[1][0] = D_80098858[0].g << 4;
    m.m[2][0] = D_80098858[0].b << 4;
    m.m[0][1] = D_80098858[1].r << 4;
    m.m[1][1] = D_80098858[1].g << 4;
    m.m[2][1] = D_80098858[1].b << 4;
    m.m[0][2] = D_80098858[2].r << 4;
    m.m[1][2] = D_80098858[2].g << 4;
    m.m[2][2] = D_80098858[2].b << 4;
    SetColorMatrix(&m);
    for (lod = STG_LOD_WORD; lod < STG_LOD_WORD + STG_LOD_NUM; lod++)
    {
        part = (uint32 *)(model->lod[lod - STG_LOD_WORD] & 0xFFFFFF);
        head = *part;
        part += (head & 0xFF) + 1;
        n = (head & 0x3F00) >> 7;
        for (i = 0; i < n; i += 2)
        {
            func_8003A918(&part[i]);
        }
    }
}

#ifdef NON_MATCHING
// Working hypothesis, kept with the attempt until it matches. The target evaluates the inner
// MAX_ABS twice (once for the outer compare, again for the result), which only a macro does, so
// some macro like this is original. Its exact form isn't known: a ternary ABS on both sides
// expands the inner argument three times (~40 extra instructions); the builtin abs() on both
// compares with slt. Mixing them is the closest so far (one extra move).
#define ABS(x)        ((x) < 0 ? -(x) : (x))
#define MAX_ABS(a, b) (abs(a) > ABS(b) ? (a) : (b))

void func_8003A918(uint32 *p)
{
    SVECTOR v[3];
    CVECTOR col;
    CVECTOR out;
    VECTOR a;
    VECTOR b;
    VECTOR n;
    VECTOR s;
    uint32 *f;
    sint32 count;
    sint32 w;
    sint32 max;
    sint32 shift;

    count = p[1] >> 24;
    f     = (uint32 *)(p[1] & 0xFFFFFF);
    col.r = 0x80;
    col.g = 0x80;
    col.b = 0x80;
    while (count--)
    {
        // Bits 26 and 24 tested as sign bits (a mask test compiles to one combined compare).
        if ((sint32)(f[0] << 5) >= 0 || (sint32)(f[0] << 7) < 0)
        {
            w       = f[1];
            v[0].vx = (sint8)w;
            v[0].vy = -(uint8)(w >> 8);
            v[0].vz = (sint8)(w >> 16);
            v[1].vx = (sint8)(w >> 24);
            w       = f[2];
            v[1].vy = -(uint8)w;
            v[1].vz = (sint8)(w >> 8);
            v[2].vx = (sint8)(w >> 16);
            v[2].vy = -(uint8)(w >> 24);
            w       = f[3];
            v[2].vz = (sint8)w;
            a.vx    = v[1].vx - v[0].vx;
            a.vy    = v[1].vy - v[0].vy;
            a.vz    = v[1].vz - v[0].vz;
            b.vx    = v[2].vx - v[0].vx;
            b.vy    = v[2].vy - v[0].vy;
            b.vz    = v[2].vz - v[0].vz;
            OuterProduct0(&a, &b, &n);
            max = MAX_ABS(MAX_ABS(n.vx, n.vy), n.vz);
            if (max < 0)
            {
                max = -max;
            }
            shift = 0;
            while (max > 0x6882)
            {
                max >>= 1;
                shift++;
            }
            s.vx = n.vx >> shift;
            s.vy = n.vy >> shift;
            s.vz = n.vz >> shift;
            VectorNormal(&s, &a);
            v[0].vx = a.vx;
            v[0].vy = a.vy;
            v[0].vz = a.vz;
            NormalColorCol(&v[0], &col, &out);
            f[0] = (*(uint32 *)&out & 0xFFFFFF) | (f[0] & 0xFF000000);
        }
        f += 4;
    }
}

#undef ABS
#undef MAX_ABS
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003A3B4", func_8003A918);
#endif
