#include "common.h"
#include "rock_neo.exe/code_8003a3b4.h"

// Light state, reached through $gp
LIGHT_CVEC D_80098858[3];
LIGHT_SVEC D_80098870[3];
LIGHT_VEC D_80098900;

void func_8003A3B4(void)
{
    sint32 i;
    sint32 off;
    sint32 j;
    sint32 slot_off;
    uint32 key;
    uint32 *slot;

    for (i = 0, off = 0; i < 0x800; i++, off += 12)
    {
        if (*(uint32 *)(0x8015C008 + off) != 0)
        {
            slot_off = off;
            for (j = 0; j < 0x1000; j += 8)
            {
                key = *(uint32 *)(0x8013A004 + j);
                if (key == 0)
                {
                    break;
                }
                slot = *(uint32 **)(0x8015C008 + slot_off);
                if ((key & 0xFFFFFF) == ((uint32)slot & 0xFFFFFF))
                {
                    *(uint16 *)(0x8015C006 + slot_off) = *(uint16 *)(slot[6] + 2);
                    break;
                }
            }
        }
    }
    func_8003A480();
    func_8003A538();
}

void func_8003A480(void)
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
    D_80098900.vx    = 0xA0;
    D_80098900.vy    = 0xA0;
    D_80098900.vz    = 0xA0;
}

void func_8003A538(void)
{
    LIGHT_MATRIX m;
    uint32 k;
    uint32 *part;
    uint32 *hdr;
    uint32 i;
    uint32 j;
    uint32 n;
    uint32 w;

    SetBackColor(D_80098900.vx, D_80098900.vy, D_80098900.vz);
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
    for (k = 0; LIGHT_MODEL_TBL[k] != 0; k += 2)
    {
        part = (uint32 *)(LIGHT_MODEL_TBL[k] & 0xFFFFFF);
        for (i = 6; i < 12; i++)
        {
            hdr = (uint32 *)(part[i] & 0xFFFFFF);
            w   = *hdr;
            hdr = (uint32 *)((uint8 *)hdr + (((w & 0xFF) << 2) + 4));
            n   = (w & 0x3F00) >> 7;
            for (j = 0; j < n; j += 2)
            {
                func_8003A918(&hdr[j]);
            }
        }
    }
}

void func_8003A744(void)
{
    LIGHT_MATRIX m;
    uint32 *part;
    uint32 *hdr;
    uint32 i;
    uint32 j;
    uint32 n;
    uint32 w;

    SetBackColor(D_80098900.vx, D_80098900.vy, D_80098900.vz);
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
    part = LIGHT_PLAYER_PARTS;
    for (i = 6; i < 12; i++)
    {
        hdr = (uint32 *)(part[i] & 0xFFFFFF);
        w   = *hdr;
        hdr = (uint32 *)((uint8 *)hdr + (((w & 0xFF) << 2) + 4));
        n   = (w & 0x3F00) >> 7;
        for (j = 0; j < n; j += 2)
        {
            func_8003A918(&hdr[j]);
        }
    }
}

// Face normals of a model's quads: each vertex packs signed bytes (y negated), the normal
// is scaled under 0x6883 before VectorNormal, and NormalColorCol gives the face colour.
void func_8003A918(uint32 *prim)
{
    LIGHT_SVEC v[3];
    LIGHT_CVEC col;
    LIGHT_CVEC out;
    LIGHT_VEC a;
    LIGHT_VEC b;
    LIGHT_VEC o;
    LIGHT_VEC s;
    uint32 *poly;
    sint32 count;
    sint32 w;
    sint32 flags;
    sint32 m;
    sint32 shift;

    count = prim[1] >> 24;
    poly  = (uint32 *)(prim[1] & 0xFFFFFF);
    col.r = 0x80;
    col.g = 0x80;
    col.b = 0x80;
    while (count--)
    {
        flags = poly[0];
        if ((flags << 5) >= 0 || (flags << 7) < 0)
        {
            w       = poly[1];
            v[0].vx = (sint8)w;
            v[0].vz = (sint8)(w >> 16);
            v[1].vx = (sint8)(w >> 24);
            v[0].vy = -(uint8)(w >> 8);
            w       = poly[2];
            v[1].vy = -(uint8)w;
            v[1].vz = (sint8)(w >> 8);
            v[2].vx = (sint8)(w >> 16);
            v[2].vy = -(uint8)(w >> 24);
            w       = poly[3];
            v[2].vz = (sint8)w;
            a.vx    = v[1].vx - v[0].vx;
            a.vy    = v[1].vy - v[0].vy;
            a.vz    = v[1].vz - v[0].vz;
            b.vx    = v[2].vx - v[0].vx;
            b.vy    = v[2].vy - v[0].vy;
            b.vz    = v[2].vz - v[0].vz;
            OuterProduct0(&a, &b, &o);
            m = LIGHT_MAX_ABS(o.vx, o.vy);
            if (m < 0)
            {
                m = -m;
            }
            if (m > LIGHT_ABS(o.vz))
            {
                m = LIGHT_MAX_ABS(o.vx, o.vy);
            }
            else
            {
                m = o.vz;
            }
            if (m < 0)
            {
                m = -m;
            }
            shift = 0;
            while (m >= 0x6883)
            {
                m >>= 1;
                shift++;
            }
            s.vx = o.vx >> shift;
            s.vy = o.vy >> shift;
            s.vz = o.vz >> shift;
            VectorNormal(&s, &a);
            v[0].vx = a.vx;
            v[0].vy = a.vy;
            v[0].vz = a.vz;
            NormalColorCol(&v[0], &col, &out);
            poly[0] = (*(uint32 *)&out & 0xFFFFFF) | (poly[0] & 0xFF000000);
        }
        poly += 4;
    }
}
