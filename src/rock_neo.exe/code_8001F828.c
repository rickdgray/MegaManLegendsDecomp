#include "common.h"
#include "rock_neo.exe/code_8001f828.h"
#include "rock_neo.exe/debug.h"
#include "rock_neo.exe/gte_inline.h"

// Small data reached through $gp
sint32 D_80097C3C;
sint8 D_80097C40;
sint16 D_800981BC, D_800981BE, D_800981C0, D_800981C2;
sint16 D_800981D0, D_800981D2, D_800981E2;
sint16 D_800981EE, D_800981F2, D_8009823A, D_8009823E, D_80098240;
sint16 D_80098208, D_8009820A, D_8009820C, D_8009820E;
sint16 D_80098212, D_80098236, D_8009824C, D_8009825A, D_80098276;
sint16 D_8009827C, D_8009827E, D_8009828C, D_8009828E;
sint16 D_800982FA, D_800982FC, D_800982FE;
sint8 D_80098340, D_80098344, D_80098348, D_8009834C;
sint32 D_80098A08, D_800989AC;

void func_8001F828(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
            if (Sce_flag_test(0xC))
            {
                D_800981BC = 0x32;
            }
            else
            {
                D_800981BC = 0x31;
            }
            return;
        case 1:
            D_800981BC = 0x32;
            id         = 0x36;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            D_800981BC = 0x32;
            id         = 0x34;
            break;
        default:
            D_800981BC = 0x32;
            id         = 0x35;
            break;
    }
    D_800981BE = D_800981C0 = D_800981C2 = id;
}

void func_8001F8DC(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
            if (Sce_flag_test(6) && !Sce_flag_test(0x59))
            {
                D_800981D0 = 0x3D;
            }
            else
            {
                D_800981D0 = 0x3C;
            }
            return;
        case 1:
            D_800981D0 = 0x3C;
            id         = 0x3F;
            break;
        case 2:
        case 3:
            D_800981D0 = 0x3C;
            id         = 0x40;
            break;
        case 4:
        case 5:
            D_800981D0 = 0x3C;
            id         = 0x41;
            break;
        case 11:
            D_800981D0 = 0x3C;
            id         = 0x43;
            break;
        default:
            D_800981D0 = 0x3C;
            id         = 0x42;
            break;
    }
    D_800981D2 = id;
}

void func_8001F9AC(void)
{
    sint16 id;

    if (Sce_flag_test(0x204) && !Sce_flag_test(0x206))
    {
        id = 0x4F;
    }
    else if (Sce_flag_test(0x212) && !Sce_flag_test(0x213))
    {
        id = 0x4E;
    }
    else if (Sce_flag_test(0x200))
    {
        id = 0x4C;
    }
    else
    {
        switch (C8001F828_GAME_52)
        {
            case 0:
                if (Sce_flag_test(2) && !Sce_flag_test(1))
                {
                    id = 0x4B;
                }
                else
                {
                    id = 0x4A;
                }
                break;
            case 1:
                id = 0x4D;
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                id = 0x50;
                break;
            case 6:
            case 7:
                id = 0x51;
                break;
            case 11:
                id = 0x53;
                break;
            default:
                id = 0x52;
                break;
        }
    }
    D_800981E2 = id;
}

void func_8001FA94(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
            D_800981EE = 0x59;
            if (Sce_flag_test(0x630))
            {
                D_800981F2 = 0x61;
            }
            else
            {
                D_800981F2 = 0x5F;
            }
            return;
        case 1:
            id = 0x5A;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x5B;
            break;
        default:
            id = 0x5C;
            break;
    }
    D_800981EE = id;
}

void func_8001FB24(void)
{
    if (C8001F828_GAME_52 == 6)
    {
        D_80098208 = D_8009820A = D_8009820C = D_8009820E = 0x67;
    }
    else
    {
        D_80098208 = D_8009820A = D_8009820C = D_8009820E = 0x66;
    }
}

void func_8001FB54(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x69;
            break;
        case 6:
        case 7:
            id = 0x6A;
            break;
        default:
            id = 0x6B;
            break;
    }
    D_80098212 = id;
}

void func_8001FB8C(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
        case 1:
            id = 0x76;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x77;
            break;
        default:
            id = 0x78;
            break;
    }
    D_80098236 = id;
}

void func_8001FBC4(void)
{
    sint16 id;

    if (C8001F828_GAME_52 == 5)
    {
        if (Sce_flag_test(0x1C))
        {
            D_8009823A = 0x7A;
            D_8009823E = 0x7C;
            D_80098240 = -1;
            return;
        }
        if (Sce_flag_test(0x1B))
        {
            D_8009823A = D_8009823E = D_80098240 = -1;
            return;
        }
        id = 0x7A;
    }
    else
    {
        id = 0x7B;
    }
    D_8009823E = D_80098240 = id;
}

void func_8001FC50(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 1:
        case 2:
        case 3:
            if (!Sce_flag_test(0x30))
            {
                id = 0x82;
                break;
            }
            // fall through
        case 0:
        default:
            id = 0x81;
            break;
    }
    D_8009824C = id;
}

void func_8001FCA4(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            id = 0x85;
            break;
        case 5:
            id = 0x86;
            break;
        default:
            id = 0x87;
            break;
    }
    D_8009825A = id;
}

void func_8001FCE4(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
            id = 0x8E;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x8F;
            break;
        case 6:
        case 7:
            id = 0x90;
            break;
        default:
            id = 0x91;
            break;
    }
    D_80098276 = id;
}

void func_8001FD3C(void)
{
    switch (C8001F828_GAME_52)
    {
        case 1:
            D_8009827C = 0x93;
            break;
        default:
            D_8009827C = 0x94;
            break;
    }
    switch (C8001F828_GAME_52)
    {
        case 0:
        case 1:
            D_8009827E = 0x95;
            break;
        case 2:
        case 3:
        case 4:
            D_8009827E = 0x96;
            break;
        default:
            D_8009827E = 0x97;
            break;
    }
}

void func_8001FD90(void)
{
    switch (C8001F828_GAME_52)
    {
        case 1:
            D_8009828C = 0x9D;
            break;
        default:
            D_8009828C = 0x9E;
            break;
    }
    switch (C8001F828_GAME_52)
    {
        case 0:
        case 1:
            D_8009828E = 0x9F;
            break;
        case 2:
        case 3:
        case 4:
            D_8009828E = 0xA0;
            break;
        default:
            D_8009828E = 0xA1;
            break;
    }
}

void func_8001FDE4(void)
{
    sint16 id;

    switch (C8001F828_GAME_52)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            id = 0xC3;
            break;
        case 4:
            id = 0xC4;
            break;
        case 11:
            id = 0xC4;
            break;
        default:
            return;
    }
    D_800982FA = D_800982FC = D_800982FE = id;
}

// Debug printf into the D_800BEAD8 text buffer (%-flags, width, l, X/x/d/i/u/o/b/c/s, $-escapes).
// fmt is `const char *`: its reads are then unchanging, so sched may move them above the stores
// to fmt's stack slot (the digit loop and the 'l' test load before storing fmt + 1, as retail).
// Each numeric case reads its argument as `(mode & 0x10000000) ? long : int` (both arms the
// same on this target); those tests are folded away later but make loop.c hoist 0x10000000
// into s1 instead of the 0xF7FFF00F mask, as retail does. %c reads the argument's low byte.
// The flag and conversion characters are their own chars; the '$' escape and the plain
// character share one trailing fmt++, so jump2 doesn't merge the '$' arms' equal last stores.
void func_8001FE38(uint32 flags, const char *fmt, ...)
{
    sint32 *ap;
    uint32 mode;
    sint32 width;
    sint32 val;
    char *s;
    char c;
    char flag;
    char conv;

    if (Moji_flag & 0x400000)
    {
        return;
    }
    if (D_80098824)
    {
        return;
    }
    if (*(sint8 *)&D_800987D4 != 0 && *(sint8 *)&D_800987D4 != *(sint8 *)&D_800987DC)
    {
        return;
    }
    if (D_8009893C >= D_800BEF88)
    {
        return;
    }
    *D_8009893C++ = (flags & 0x100) >> 8;
    *D_8009893C++ = flags;
    *D_8009893C++ = flags >> 9;
    *D_8009893C++ = (flags >> 17) & 7;
    mode          = 0;
    ap            = (sint32 *)(&fmt + 1);
    while (*fmt)
    {
        c = *fmt;
        if (c == '%')
        {
            flag = fmt[1];
            fmt += 2;
            switch (flag)
            {
                case '-':
                    mode |= 0x80000000;
                    break;
                case '+':
                    mode |= 0x2B0;
                    break;
                case ' ':
                    mode |= 0x200;
                    break;
                case '0':
                    mode |= 0x40000000;
                    break;
                case '%':
                    *D_8009893C++ = '%';
                    continue;
                default:
                    fmt--;
                    break;
            }
            if (*fmt >= '0' && *fmt <= '9')
            {
                width = 0;
                while (*fmt >= '0' && *fmt <= '9')
                {
                    width *= 10;
                    width += *fmt++ - '0';
                }
            }
            else if (*fmt == '*')
            {
                width = (ap += 1)[-1];
                fmt++;
            }
            else
            {
                width = -1;
                mode &= 0x7FFFFFFF;
            }
            if (*fmt++ == 'l')
            {
                mode |= 0x10000000;
            }
            else
            {
                fmt--;
            }
            conv = *fmt;
            fmt++;
            switch (conv)
            {
                case 'X':
                case 'x':
                    mode &= 0xF7FFF00F;
                    val = (mode & 0x10000000) ? (ap += 1)[-1] : (ap += 1)[-1];
                    D_8009893C += func_800207F8(mode | 0xF, val, D_8009893C, width);
                    break;
                case 'd':
                case 'i':
                    mode |= 0x08000000;
                    val = (mode & 0x10000000) ? (ap += 1)[-1] : (ap += 1)[-1];
                    if (val < 0)
                    {
                        mode &= ~0xFF0;
                        mode |= 0x2D0;
                    }
                    D_8009893C += func_800207F8(mode | 9, val, D_8009893C, width);
                    break;
                case 'u':
                    val = (mode & 0x10000000) ? (ap += 1)[-1] : (ap += 1)[-1];
                    D_8009893C += func_800207F8(mode | 9, val, D_8009893C, width);
                    break;
                case 'o':
                    mode &= 0xF7FFF00F;
                    val = (mode & 0x10000000) ? (ap += 1)[-1] : (ap += 1)[-1];
                    D_8009893C += func_800207F8(mode | 7, val, D_8009893C, width);
                    break;
                case 'b':
                    mode &= 0xF7FFF00F;
                    val = (mode & 0x10000000) ? (ap += 1)[-1] : (ap += 1)[-1];
                    D_8009893C += func_800207F8(mode | 1, val, D_8009893C, width);
                    break;
                case 'c':
                    *D_8009893C++ = *(char *)((ap += 1) - 1);
                    break;
                case 's':
                    s = (char *)(ap += 1)[-1];
                    while ((*D_8009893C++ = *s++) != '\0')
                    {
                        if (width-- == 0)
                        {
                            break;
                        }
                    }
                    D_8009893C--;
                    while (width-- > 0)
                    {
                        *D_8009893C++ = ' ';
                    }
                    break;
                default:
                    fmt--;
                    break;
            }
            mode = 0;
        }
        else
        {
            if (c == '$')
            {
                val = fmt[1];
                if (val == '$')
                {
                    fmt++;
                    *D_8009893C++ = '$';
                }
                else if ((uint32)(val - 'A') < 0x1C)
                {
                    fmt++;
                    *D_8009893C++ = val + 0x3E;
                }
            }
            else
            {
                *D_8009893C++ = c;
            }
            fmt++;
        }
    }
    *D_8009893C++ = 0;
}

void func_8002037C(void)
{
    D_800BEAD8[0] = 0;
    D_8009893C    = D_800BEAD8;
    D_800987D4    = 0;
    D_800987DC    = 0;
}

void func_800203A8(void)
{
    uint8 *p;
    C8001F828_SPRT8 *sp;
    DR_MODE *dm;
    sint32 x;
    sint32 x0;
    sint32 y;
    uint8 col;
    uint8 c;
    sint32 hi;

    if (Moji_flag & 0x400000)
    {
        return;
    }
    if (D_80098824)
    {
        return;
    }
    if (D_800C0D8E[0] & 1)
    {
        if (D_800C0D8E[2] & 0x10)
        {
            D_80097C40 = 0;
            D_800987DC++;
        }
        else if (D_800C0D8E[0] & 0x10)
        {
            if (D_80097C40 >= 0x10)
            {
                D_800987DC++;
            }
            else
            {
                D_80097C40++;
            }
        }
        else if (D_800C0D8E[2] & 0x40)
        {
            D_80097C40 = 0;
            D_800987DC--;
        }
        else if (D_800C0D8E[0] & 0x40)
        {
            if (D_80097C40 >= 0x10)
            {
                D_800987DC--;
            }
            else
            {
                D_80097C40++;
            }
        }
        if ((sint8)D_800987DC >= 0x1F)
        {
            D_800987DC = 0;
        }
        if ((sint8)D_800987DC < 0)
        {
            D_800987DC = 0x1E;
        }
    }
    if (D_8009893C == D_800BEAD8)
    {
        return;
    }
    if (++D_80098348 == 10)
    {
        D_80098348 = 0;
        if (++D_8009834C == 5)
        {
            D_8009834C = 0;
        }
    }
    p = D_800BEAD8;
    while (p < D_8009893C)
    {
        hi  = *p++;
        x   = *p++ | (hi << 8);
        y   = *p++;
        col = *p++;
        x0  = x;
        for (;;)
        {
            switch (*p)
            {
                case 0:
                    D_80098340 = 0;
                    p++;
                    goto next;
                case 7:
                    D_80098340 ^= 1;
                    D_80098344 = D_8009834C;
                    p++;
                    continue;
                case 8:
                    x -= 8;
                    break;
                case 9:
                    x += 32;
                    break;
                case 10:
                    x = x0;
                    // fall through
                case 11:
                    y += 8;
                    break;
                case 12:
                case 13:
                    break;
                case 32:
                    x += 8;
                    break;
                default:
                    if (D_80098340 == 0)
                    {
                        c = col;
                    }
                    else
                    {
                        c = D_80089888[D_80098344];
                        if (++D_80098344 == 5)
                        {
                            D_80098344 = 0;
                        }
                    }
                    if (*p >= 0x5F)
                    {
                        *p -= 0x5F;
                        c += 8;
                    }
                    else
                    {
                        *p -= 0x21;
                    }
                    sp                 = (C8001F828_SPRT8 *)C8001F828_PRIM_PTR;
                    C8001F828_PRIM_PTR = (uint8 *)(sp + 1);
                    setlen(sp, 3);
                    sp->code = 0x74;
                    sp->r0   = 0x80;
                    sp->g0   = 0x80;
                    sp->b0   = 0x80;
                    sp->x0   = x;
                    sp->y0   = y;
                    sp->u0   = ((*p & 1) << 3) - 0x10;
                    sp->v0   = (*p & 0xFE) << 2;
                    sp->clut = D_80097C44[c];
                    x += 8;
                    addPrim(&D_80098934->layer[0], sp);
                    break;
            }
            p++;
        }
    next:;
    }
    dm                 = (DR_MODE *)C8001F828_PRIM_PTR;
    C8001F828_PRIM_PTR = (uint8 *)(dm + 1);
    SetDrawMode(dm, 0, 0, 0x1F, NULL);
    addPrim(&D_80098934->layer[0], dm);
    D_8009893C = D_800BEAD8;
}

// Number formatter. buf[32] gives retail's frame and 'while (n++ < width - orig)' its pad loop;
// orig is reused as the pad count of the other two paths.
sint32 func_800207F8(uint32 flags, sint32 val, uint8 *out, sint32 width)
{
    uint8 buf[32];
    sint16 n;
    sint16 orig;
    uint32 base;
    uint32 prefix;

    if ((flags & 0x08000000) && val < 0)
    {
        val = ~val + 1;
    }
    n    = 0;
    base = (flags & 0xF) + 1;
    do
    {
        buf[n++] = D_80097C64[(uint32)val % base];
        val      = (uint32)val / base;
    } while (val != 0);
    prefix = flags & 0xFF0;
    if (prefix != 0)
    {
        buf[n++] = prefix >> 4;
        flags |= 0x04000000;
    }
    if (width - n > 0)
    {
        if ((sint32)flags < 0)
        {
            orig = n;
            if (n > 0)
            {
                do
                {
                    n--;
                    *out++ = buf[n];
                } while (n > 0);
            }
            while (n++ < width - orig)
            {
                *out++ = 0x20;
            }
            return width;
        }
        orig = width - n;
        if (flags & 0x40000000)
        {
            if (flags & 0x04000000)
            {
                n--;
                *out++ = buf[n];
            }
            while (orig-- > 0)
            {
                *out++ = 0x30;
            }
        }
        else
        {
            while (orig-- > 0)
            {
                *out++ = 0x20;
            }
        }
        if (n > 0)
        {
            do
            {
                n--;
                *out++ = buf[n];
            } while (n > 0);
        }
        return width;
    }
    width = 0;
    if (n > 0)
    {
        do
        {
            n--;
            width++;
            *out++ = buf[n];
        } while (n > 0);
    }
    return width;
}

void func_80020A40(void)
{
    D_80097C3C = 0;
}

// Draws every non-empty tile in the scratchpad window (x 0x40..0x42, y 0x41..0x43). The bounds
// are read before v[3] is set, and y0 is copied into y by the loop.
void func_80020A4C(void)
{
    sint16 v[4];
    sint32 x;
    sint32 y;
    sint32 y0;
    sint32 x0;
    sint32 x1;
    sint32 y1;
    sint32 tile;

    D_8009886C = 0;
    GTE_SET_TR(C8001F828_TR_B);
    y0   = *(uint8 *)0x1F800041;
    y1   = *(uint8 *)0x1F800043;
    x0   = *(uint8 *)0x1F800040;
    x1   = *(uint8 *)0x1F800042;
    v[3] = 0x320;
    for (y = y0; y < y1; y++)
    {
        v[2] = (y << 9) - 0x7F00;
        for (x = x0; x < x1; x++)
        {
            v[0] = (x << 9) - 0x7F00;
            tile = *(sint16 *)(*(sint32 *)0x1F800048 + (x - *(uint8 *)0x1F800040) * 2 +
                               (y - *(uint8 *)0x1F800041) * *(uint16 *)0x1F800044 * 2);
            if (tile != 0)
            {
                func_80021834(x, y, tile, v);
            }
        }
    }
    func_8001782C(0x8015BC00, 0x8015BD00);
    func_800221E0();
}

// Visible tile window from the camera angles. The camera-pitch terms are ABS() macro
// expansions, so each calls rcos/rsin twice as retail does. The camera angles and position are
// fields of the camera block D_800A3958. The locals are reused across roles (cx: yaw sine,
// window centre x, pitch offset, angle a; cz: yaw cosine, window centre z; w: width, span, map
// centre and tile). w ending as the tile argument gives it retail's preference for a2.
void func_80020BB4(void)
{
    sint16 pos[4];
    sint32 cx;
    sint32 cz;
    sint32 w;
    sint32 b;
    sint32 c;
    sint32 d;
    sint32 e;
    sint32 f;
    sint32 x0;
    sint32 x1;
    sint32 y0;
    sint32 y1;
    sint32 x;
    sint32 y;
    sint32 yaw;

    D_8009886C = 0;
    GTE_SET_TR(C8001F828_TR_B);
    if ((*(uint8 *)0x1F800078 & 4) && *(uint8 *)0x1F800074 < 3U)
    {
        C8001F828_S16(0x1F800076) = D_80097C84[*(uint8 *)0x1F800074];
    }
    else
    {
        C8001F828_S16(0x1F800076) = D_80097C78[*(uint8 *)0x1F800074];
    }
    cx = rsin(D_800A3958.work.rot_B8.vy);
    cz = rcos(D_800A3958.work.rot_B8.vy);
    if (cx == 0x1000)
    {
        cx = 0xFFF;
    }
    else if (cx == -0x1000)
    {
        cx = -0xFFF;
    }
    if (cz == 0x1000)
    {
        cz = 0xFFF;
    }
    else if (cz == -0x1000)
    {
        cz = -0xFFF;
    }
    w  = C8001F828_ABS(rcos(D_800A3958.work.rot_B8.vx)) * 2;
    cx = ((C8001F828_S16(0x1F800028) + (cx * w) / 4096) / 512) + 0x40;
    cz = ((C8001F828_S16(0x1F80002C) + (cz * w) / 4096) / 512) + 0x40;
    w  = C8001F828_ABS(rcos(D_800A3958.work.rot_B8.vx)) / 256;
    x0 = cx - w;
    if (x0 < *(uint8 *)0x1F800040)
    {
        x0 = *(uint8 *)0x1F800040;
    }
    x1 = cx + w;
    if (*(uint8 *)0x1F800042 < x1)
    {
        x1 = *(uint8 *)0x1F800042;
    }
    y0 = cz - w;
    if (y0 < *(uint8 *)0x1F800041)
    {
        y0 = *(uint8 *)0x1F800041;
    }
    y1 = cz + w;
    if (*(uint8 *)0x1F800043 < y1)
    {
        y1 = *(uint8 *)0x1F800043;
    }
    cx                        = C8001F828_ABS(rsin(D_800A3958.work.rot_B8.vx) / 352);
    w                         = (D_800A3958.work.pos_48.x + 0x100) / 512;
    C8001F828_S16(0x1F800100) = w - cx + 0x3D;
    if (C8001F828_S16(0x1F800100) < *(uint8 *)0x1F800040)
    {
        C8001F828_S16(0x1F800100) = *(uint8 *)0x1F800040;
    }
    C8001F828_S16(0x1F800104) = w + cx + 0x43;
    if (*(uint8 *)0x1F800042 < C8001F828_S16(0x1F800104))
    {
        C8001F828_S16(0x1F800104) = *(uint8 *)0x1F800042;
    }
    w                         = (D_800A3958.work.pos_48.z + 0x100) / 512;
    C8001F828_S16(0x1F800102) = w - cx + 0x3D;
    if (C8001F828_S16(0x1F800102) < *(uint8 *)0x1F800041)
    {
        C8001F828_S16(0x1F800102) = *(uint8 *)0x1F800041;
    }
    C8001F828_S16(0x1F800106) = w + cx + 0x43;
    if (*(uint8 *)0x1F800043 < C8001F828_S16(0x1F800106))
    {
        C8001F828_S16(0x1F800106) = *(uint8 *)0x1F800043;
    }
    yaw = D_800A3958.work.rot_B8.vy;
    cx  = yaw - 0x100;
    cx &= 0xFFF;
    b = (yaw + 0x100) & 0xFFF;
    c = rsin(cx) + 1;
    d = rsin(b) + 1;
    e = rcos(cx) + 1;
    f = rcos(b) + 1;
    if (!((D_800A3958.work.rot_B8.vy - 0x200) & 0x400))
    {
        C8001F828_S16(0x1F800108) = (e << 12) / -c;
        C8001F828_S16(0x1F80010A) = (f << 12) / -d;
        func_80021258(x0, x1, y0, y1);
    }
    else
    {
        C8001F828_S16(0x1F800108) = (c << 12) / -e;
        C8001F828_S16(0x1F80010A) = (d << 12) / -f;
        func_80021548(x0, x1, y0, y1);
    }
    x0     = C8001F828_S16(0x1F800100);
    x1     = C8001F828_S16(0x1F800104);
    y0     = C8001F828_S16(0x1F800102);
    y1     = C8001F828_S16(0x1F800106);
    pos[3] = 0x258;
    for (y = y0; y < y1; y++)
    {
        pos[2] = (y << 9) - 0x7F00;
        for (x = x0; x < x1; x++)
        {
            pos[0] = (x << 9) - 0x7F00;
            w      = *(sint16 *)(*(sint32 *)0x1F800048 + (x - *(uint8 *)0x1F800040) * 2 +
                                 (y - *(uint8 *)0x1F800041) * *(uint16 *)0x1F800044 * 2);
            if (w != 0)
            {
                func_80021834(x, y, w, pos);
            }
        }
    }
    func_8001782C(0x8015BC00, 0x8015BD00);
    func_800221E0();
}

void func_80021258(sint32 x0, sint32 x1, sint32 y0, sint32 y1)
{
    C8001F828_SVEC sv;
    sint32 d0;
    sint32 d1;
    sint32 k;
    sint32 hy;
    sint32 hx;
    sint32 x;
    sint32 y;
    sint32 xs;
    sint32 xe;
    sint32 fp;
    sint32 ofs;
    sint32 row;
    sint32 tile;

    if ((D_800A3958.work.rot_B8.vy - 0x200) & 0x800)
    {
        d0 = C8001F828_S16(0x1F800108);
        d1 = C8001F828_S16(0x1F80010A);
        k  = (C8001F828_S16(0x1F800028) + 0x100) / 512 - x0 + 0x41;
    }
    else
    {
        d0 = C8001F828_S16(0x1F80010A);
        d1 = C8001F828_S16(0x1F800108);
        k  = (C8001F828_S16(0x1F800028) + 0x100) / 512 - x0 + 0x3E;
    }
    hx     = (C8001F828_S16(0x1F80002C) + 0x100) / 512;
    sv.pad = 0x190;
    for (x = x0; x < x1; x++, k--)
    {
        xs = hx + (k * d0) / 4096 + 0x3D;
        xe = hx + (k * d1) / 4096 + 0x42;
        if (xs < y0)
        {
            xs = y0;
        }
        else if (y1 < xs)
        {
            xs = y1;
        }
        if (xe < y0)
        {
            xe = y0;
        }
        else if (y1 < xe)
        {
            xe = y1;
        }
        fp = 0;
        if (!(x < C8001F828_S16(0x1F800100)))
        {
            fp = x < C8001F828_S16(0x1F800104);
        }
        y     = xs;
        sv.vx = (x << 9) - 0x7F00;
        ofs   = x - C8001F828_U8(0x1F800040);
        row   = (y - C8001F828_U8(0x1F800041)) * *(uint16 *)0x1F800044;
        if (y < xe)
        {
            for (; y < xe; y++)
            {
                if (!fp || y < C8001F828_S16(0x1F800102) || !(y < C8001F828_S16(0x1F800106)))
                {
                    sv.vz = (y << 9) - 0x7F00;
                    tile  = (C8001F828_TILE_PTR + ofs)[row];
                    if (tile != 0)
                    {
                        func_80021834(x, y, tile, &sv.vx);
                    }
                }
                ofs += *(uint16 *)0x1F800044;
            }
        }
    }
}

// Visible-tile scan: walks each map row between the clipped x bounds and draws its tiles.
void func_80021548(sint32 x0, sint32 x1, sint32 y0, sint32 y1)
{
    sint16 pos[4];
    sint32 xs;
    sint32 xe;
    sint32 x;
    sint32 y;
    sint32 k;
    sint32 u;
    sint32 v;
    sint32 ofs;
    sint32 row;
    sint32 fp;
    sint32 cx;
    sint32 d0;
    sint32 d1;
    sint32 hy;
    sint32 tile;

    if ((D_800A3958.work.rot_B8.vy - 0x200) & 0x800)
    {
        d0 = C8001F828_S16(0x1F800108);
        cx = C8001F828_S16(0x1F80002C);
        d1 = C8001F828_S16(0x1F80010A);
        k  = (cx + 0x100) / 512 - y0 + 0x3E;
    }
    else
    {
        d0 = C8001F828_S16(0x1F80010A);
        cx = C8001F828_S16(0x1F80002C);
        d1 = C8001F828_S16(0x1F800108);
        k  = (cx + 0x100) / 512 - y0 + 0x41;
    }
    hy     = (C8001F828_S16(0x1F800028) + 0x100) / 512;
    pos[3] = 0x190;
    for (y = y0; y < y1; y++, k--)
    {
        v  = k * d0;
        u  = k * d1;
        xs = hy + v / 4096 + 0x3D;
        xe = hy + u / 4096 + 0x42;
        if (xs < x0)
        {
            xs = x0;
        }
        else if (x1 < xs)
        {
            xs = x1;
        }
        if (xe < x0)
        {
            xe = x0;
        }
        else if (x1 < xe)
        {
            xe = x1;
        }
        fp = 0;
        if (!(y < C8001F828_S16(0x1F800102)))
        {
            fp = y < C8001F828_S16(0x1F800106);
        }
        x      = xs;
        pos[2] = (y << 9) - 0x7F00;
        ofs    = x - C8001F828_U8(0x1F800040);
        row    = (y - C8001F828_U8(0x1F800041)) * *(uint16 *)0x1F800044;
        for (; x < xe; x++, ofs++)
        {
            if (!fp || x < C8001F828_S16(0x1F800100) || !(x < C8001F828_S16(0x1F800104)))
            {
                pos[0] = (x << 9) - 0x7F00;
                tile   = (C8001F828_TILE_PTR + ofs)[row];
                if (tile != 0)
                {
                    func_80021834(x, y, tile, pos);
                }
            }
        }
    }
}

void func_80021834(sint32 x, sint32 y, sint32 tile, sint16 *pos)
{
    sint32 v[3];
    sint32 depth;
    sint32 row;

    if (tile > 0)
    {
        pos[1] = ((sint16 *)(*(sint32 *)0x1F80004C + tile * 12))[1];
    }
    else
    {
        pos[1] = -((uint32)(tile & 0x1F00) >> 1);
    }
    GTE_LWC2_OFF(0, 0, pos);
    GTE_LWC2_OFF(1, 4, pos);
    GTE_NOP2();
    GTE_RTV0();
    GTE_SWC2_OFF(25, 0, v);
    GTE_SWC2_OFF(26, 4, v);
    GTE_SWC2_OFF(27, 8, v);
    depth = v[2];
    row   = depth >> 2;
    if (row < C8001F828_SCR_76)
    {
        if (row < 0)
        {
            row = 0;
        }
        row = ((row * 106) >> 6) + pos[3];
        if (v[0] >= -row && row >= v[0])
        {
            if (tile < 0)
            {
                func_8002196C(x, y, tile & 0xFFFF);
                return;
            }
            if (depth >= C8001F828_SCR_04)
            {
                ((uint32 *)C8001F828_BUF_A)[tile >> 5] |= 0x80000000U >> (tile & 0x1F);
            }
            else
            {
                ((uint32 *)C8001F828_BUF_B)[tile >> 5] |= 0x80000000U >> (tile & 0x1F);
            }
        }
    }
}

// The id's high bit is tested as (id << 24) < 0 on the uint16 parameter; (sint8)id tests the
// incoming register instead of the copy.
void func_8002196C(sint32 x, sint32 y, uint16 id)
{
    C8001F828_SVEC sv;
    sint32 out[3];
    sint32 *scr;
    uint32 n;
    C8001F828_MODEL_HDR *hdr;
    uint8 *data;

    sv.vx = (x << 9) - 0x7F00;
    sv.vz = (y << 9) - 0x7F00;
    sv.vy = -((uint32)(id & 0x1F00) >> 1);
    GTE_LDV0(&sv);
    scr = (sint32 *)0x1F800130;
    GTE_RTV0();
    if ((id << 24) < 0)
    {
        hdr = C8001F828_MODEL_ENTRIES[(id & 0x7F) >> 2].hdr;
    }
    else
    {
        hdr = (C8001F828_MODEL_HDR *)0x80194000;
    }
    GTE_STLVNL(out);
    if (out[2] > 0x1C20)
    {
        data = *(uint8 **)((uint8 *)hdr + 0x20);
        id &= 0x7FFF;
    }
    else if (out[2] > 0xAF0)
    {
        data = *(uint8 **)((uint8 *)hdr + 0x1C);
        id &= 0x7FFF;
    }
    else if (out[2] > 0x400)
    {
        data = hdr->data;
    }
    else
    {
        n = D_8009886C;
        if (n < 0x80)
        {
            D_800BBE50[n] = (x << 24) | (y << 16) | id;
            D_8009886C    = n + 1;
        }
        return;
    }
    scr[2] = D_800C0DC0[(out[2] / 512) & 0x1F] << 16;
    GTE_SET_TR(C8001F828_TR_A);
    func_80021B14(data + 8, &sv, id);
    GTE_SET_TR(C8001F828_TR_B);
}

// Tile model renderer: each face's corners are packed as signed x/z bytes, every corner at the
// model's height; id bit 0 mirrors the model, bit 1 flips it about its position, bit 7 takes the
// CLUT from the header and the UVs from the face (for the quad splitter), bit 15 the texture with
// a per-face shade from 0x1F800187. Faces with bit 29 are triangles; bit 28 chains a face behind
// the previous one instead of depth-sorting it.
void func_80021B14(uint8 *data, C8001F828_SVEC *pos, uint32 id)
{
    C8001F828_TILE_WORK *scr;
    uint32 *hdr;
    uint32 *face;
    uint32 *tex;
    uint32 *tail;
    uint32 *pk;
    uint32 *slot;
    uint32 flags;
    uint32 w0;
    uint32 w1;
    uint32 shade;
    uint32 level;
    uint32 lo;
    uint32 left;
    sint32 sh;
    sint32 ox;
    sint32 oy;
    sint32 oz;
    sint32 opz;
    sint32 sz0;
    sint32 sz1; // the packed face words are kept in sz1-sz3
    sint32 sz2;
    sint32 sz3;
    sint32 zmax;

    scr  = C8001F828_TILEW_PTR;
    hdr  = (uint32 *)data;
    w1   = hdr[1];
    w0   = hdr[0];
    left = w1 >> 24;
    face = (uint32 *)((w1 & 0xFFFFFF) + 4);
    tex  = (uint32 *)(w0 & 0xFFFFFF);
    sh   = (w0 >> 28) + C8001F828_SHIFT;
    if (C8001F828_BIT(id, 7))
    {
        *(uint32 *)0x1F80013C = hdr[-1];
    }
    else
    {
        shade                 = *(uint32 *)((uint8 *)D_800BADB0 + ((id * 2) & 0xF8));
        *(uint32 *)0x1F800180 = *(uint32 *)((uint8 *)D_800BADB0 + ((id * 2) & 0xF8) + 4);
        *(uint32 *)0x1F80013C = (shade & 0xFFFF0000) | 0x1D;
        shade &= 0xFF;
    }
    w1            = 0xFFFFFF;
    scr->clut_90  = scr->clut_0c & 0xFFFF0000;
    scr->tpage_94 = scr->clut_0c << 16;
    ox            = pos->vx << C8001F828_SHIFT;
    oy            = pos->vy << C8001F828_SHIFT;
    oz            = pos->vz << C8001F828_SHIFT;
    while (left != 0)
    {
        sz1             = face[0];
        scr->v_70[0].vy = oy;
        sz2             = face[1];
        left--;
        scr->v_70[1].vy = oy;
        scr->v_70[2].vy = oy;
        sz3             = face[2];
        if (id & 1)
        {
            scr->v_70[0].vz = -(((sz1 << 24) >> 24) << sh);
            scr->v_70[0].vx = ((sz1 << 8) >> 24) << sh;
            scr->v_70[1].vz = -((sz1 >> 24) << sh);
            scr->v_70[1].vx = ((sz2 << 16) >> 24) << sh;
            scr->v_70[2].vz = -(((sz2 << 8) >> 24) << sh);
            scr->v_70[2].vx = ((sz3 << 24) >> 24) << sh;
            scr->v_70[3].vz = -(((sz3 << 16) >> 24) << sh);
            scr->v_70[3].vx = (sz3 >> 24) << sh;
        }
        else
        {
            scr->v_70[0].vx = ((sz1 << 24) >> 24) << sh;
            scr->v_70[0].vz = ((sz1 << 8) >> 24) << sh;
            scr->v_70[1].vx = (sz1 >> 24) << sh;
            scr->v_70[1].vz = ((sz2 << 16) >> 24) << sh;
            scr->v_70[2].vx = ((sz2 << 8) >> 24) << sh;
            scr->v_70[2].vz = ((sz3 << 24) >> 24) << sh;
            scr->v_70[3].vx = ((sz3 << 16) >> 24) << sh;
            scr->v_70[3].vz = (sz3 >> 24) << sh;
        }
        if (id & 2)
        {
            scr->v_70[0].vx = ox - scr->v_70[0].vx;
            scr->v_70[0].vz = oz - scr->v_70[0].vz;
            scr->v_70[1].vx = ox - scr->v_70[1].vx;
            scr->v_70[1].vz = oz - scr->v_70[1].vz;
            scr->v_70[2].vx = ox - scr->v_70[2].vx;
            scr->v_70[2].vz = oz - scr->v_70[2].vz;
        }
        else
        {
            scr->v_70[0].vx += ox;
            scr->v_70[0].vz += oz;
            scr->v_70[1].vx += ox;
            scr->v_70[1].vz += oz;
            scr->v_70[2].vx += ox;
            scr->v_70[2].vz += oz;
        }
        C8001F828_GTE_LDV3C(scr->v_70);
        scr->v_70[3].vy = oy;
        GTE_NOP2();
        GTE_RTPT();
        if (id & 2)
        {
            scr->v_70[3].vx = ox - scr->v_70[3].vx;
            scr->v_70[3].vz = oz - scr->v_70[3].vz;
        }
        else
        {
            scr->v_70[3].vx += ox;
            scr->v_70[3].vz += oz;
        }
        C8001F828_GTE_NCLIP();
        flags = face[-1];
        C8001F828_GTE_STMAC0(&opz);
        if (opz <= 0)
        {
            if (!C8001F828_BIT(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = *(uint32 **)0x1F800070;
        C8001F828_GTE_STSXY3_FT(pk);
        if (C8001F828_BIT(flags, 29))
        {
            scr->rgbc_14 = (flags & 0x03FFFFFF) | 0x24000000;
            C8001F828_GTE_STSZ3(&sz0, &sz1, &sz2);
            sz3 = sz2;
        }
        else
        {
            GTE_LDV0(&scr->v_70[3]);
            C8001F828_GTE_RTPS();
            scr->rgbc_14 = (flags & 0x03FFFFFF) | 0x2C000000;
            GTE_STSXY2(&pk[8]);
            C8001F828_GTE_STSZ4(&sz0, &sz1, &sz2, &sz3);
        }
        GTE_LWC2(6, &scr->rgbc_14);
        if (C8001F828_BIT(flags, 28))
        {
            scr->link_48 = tail;
        }
        else
        {
            if (sz0 < sz1)
            {
                zmax = sz1;
            }
            else
            {
                zmax = sz0;
            }
            if (sz2 < sz3)
            {
                sz0 = sz3;
            }
            else
            {
                sz0 = sz2;
            }
            if (sz0 < zmax)
            {
                sz0 = zmax;
            }
            if ((*(uint8 *)0x1F800078 & 1) && oy >= 0)
            {
                scr->link_48 = (uint32 *)(*(uint32 *)0x1F80003C + 0x1F40);
            }
            else
            {
                scr->link_48 = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            }
        }
        GTE_DPCS_RUN();
        if ((id << 24) <= 0x7FFFFFFF)
        {
            if ((id << 16) > 0x7FFFFFFF)
            {
                sz2 = tex[0];
                sz3 = tex[1];
                if (left >= 4)
                {
                    level = *(uint8 *)(0x1F800187 - left);
                    goto blend;
                }
            }
            else
            {
                sz2 = 0x1F0000;
                sz3 = 0x1F1F1F00;
            }
            level = shade;
        blend:
            lo    = level & 7;
            level = (lo << 5) | ((level >> 3) << 13) | (lo << 21) | ((level >> 3) << 29);
            sz2 += level;
            sz3 += level;
        }
        else
        {
            sz2           = tex[0];
            scr->uv_50[0] = sz2;
            sz3           = tex[1];
            scr->uv_50[1] = sz3;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_90 | scr->fog_08;
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_94;
        pk[7] = sz3 & 0xFFFF;
        if (!C8001F828_BIT(flags, 29))
        {
            pk[9] = (uint32)sz3 >> 16;
            w0    = 0x09000000;
        }
        else
        {
            w0 = 0x07000000;
        }
        if (C8001F828_BIT(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((uint32)pk & w1) | w0;
        }
        else
        {
            slot  = scr->link_48;
            pk[0] = w0 | *slot;
            *slot = (uint32)pk & w1;
        }
        if (!C8001F828_BIT(flags, 28))
        {
            tail = pk;
        }
        GTE_SWC2(22, &pk[1]);
        face += 4;
        tex += 2;
        *(uint32 *)0x1F800070 += 0x28;
        continue;
    cull:
        if (!C8001F828_BIT(flags, 28))
        {
            tail = NULL;
        }
        face += 4;
        tex += 2;
    }
}

// The model table is read through its fixed address (C8001F828_MODEL_ENTRIES at 0x80139F00, hdr
// at +4): retail's addu at,v0,at. Indexing a base of 0x80139F04 directly, the offset-0 load is
// built with li instead.
void func_800221E0(void)
{
    uint32 i;
    uint32 count;
    uint32 e;
    uint32 id;
    uint32 slot;
    C8001F828_SVEC sv;
    sint32 out[3];
    C8001F828_MODEL_HDR *hdr;
    uint8 *data;
    sint32 *scr;

    scr   = (sint32 *)0x1F800130;
    count = D_8009886C;
    for (i = 0; i < count; i++)
    {
        e     = D_800BBE50[i];
        sv.vx = ((e >> 24) << 9) - 0x7F00;
        sv.vz = (((e >> 16) & 0xFF) << 9) - 0x7F00;
        id    = e & 0xFFFF;
        sv.vy = -((e & 0x1F00) >> 1);
        GTE_LDV0(&sv);
        GTE_NOP2();
        GTE_RTV0();
        if ((sint8)id < 0)
        {
            slot = (e >> 2) & 0x1F;
            hdr  = C8001F828_MODEL_ENTRIES[slot].hdr;
        }
        else
        {
            hdr = (C8001F828_MODEL_HDR *)0x80194000;
        }
        data = hdr->data;
        GTE_STLVNL(out);
        scr[2] = D_800C0DC0[(out[2] / 512) & 0x1F] << 16;
        GTE_SET_TR(C8001F828_TR_A);
        func_8002235C(data + 8, &sv, id);
        GTE_SET_TR(C8001F828_TR_B);
    }
}

// Variant of func_80021B14 whose bit-7 faces go to the quad splitter (func_80022A94) instead of
// being drawn directly. A back face without bit 30 is culled when it is a triangle (bit 29); a
// back-facing quad ends the whole list (retail returns there).
void func_8002235C(uint8 *data, C8001F828_SVEC *pos, uint32 id)
{
    C8001F828_TILE_WORK *scr;
    uint32 *hdr;
    uint32 *face;
    uint32 *tex;
    uint32 *tail;
    uint32 *pk;
    uint32 *slot;
    uint32 flags;
    uint32 w0;
    uint32 w1;
    uint32 shade;
    uint32 level;
    uint32 lo;
    uint32 left;
    sint32 sh;
    sint32 ox;
    sint32 oy;
    sint32 oz;
    sint32 opz;
    sint32 sz0;
    sint32 sz1; // the packed face words are kept in sz1-sz3
    sint32 sz2;
    sint32 sz3;
    sint32 zmax;

    scr  = C8001F828_TILEW_PTR;
    hdr  = (uint32 *)data;
    w1   = hdr[1];
    w0   = hdr[0];
    left = w1 >> 24;
    face = (uint32 *)((w1 & 0xFFFFFF) + 4);
    tex  = (uint32 *)(w0 & 0xFFFFFF);
    sh   = (w0 >> 28) + C8001F828_SHIFT;
    if (C8001F828_BIT(id, 7))
    {
        *(uint32 *)0x1F80013C = hdr[-1];
    }
    else
    {
        shade                 = *(uint32 *)((uint8 *)D_800BADB0 + ((id * 2) & 0xF8));
        *(uint32 *)0x1F800180 = *(uint32 *)((uint8 *)D_800BADB0 + ((id * 2) & 0xF8) + 4);
        *(uint32 *)0x1F80013C = (shade & 0xFFFF0000) | 0x1D;
        shade &= 0xFF;
    }
    w1            = 0xFFFFFF;
    scr->clut_90  = scr->clut_0c & 0xFFFF0000;
    scr->tpage_94 = scr->clut_0c << 16;
    ox            = pos->vx << C8001F828_SHIFT;
    oy            = pos->vy << C8001F828_SHIFT;
    oz            = pos->vz << C8001F828_SHIFT;
    while (left != 0)
    {
        sz1             = face[0];
        scr->v_70[0].vy = oy;
        sz2             = face[1];
        left--;
        scr->v_70[1].vy = oy;
        scr->v_70[2].vy = oy;
        sz3             = face[2];
        if (id & 1)
        {
            scr->v_70[0].vz = -(((sz1 << 24) >> 24) << sh);
            scr->v_70[0].vx = ((sz1 << 8) >> 24) << sh;
            scr->v_70[1].vz = -((sz1 >> 24) << sh);
            scr->v_70[1].vx = ((sz2 << 16) >> 24) << sh;
            scr->v_70[2].vz = -(((sz2 << 8) >> 24) << sh);
            scr->v_70[2].vx = ((sz3 << 24) >> 24) << sh;
            scr->v_70[3].vz = -(((sz3 << 16) >> 24) << sh);
            scr->v_70[3].vx = (sz3 >> 24) << sh;
        }
        else
        {
            scr->v_70[0].vx = ((sz1 << 24) >> 24) << sh;
            scr->v_70[0].vz = ((sz1 << 8) >> 24) << sh;
            scr->v_70[1].vx = (sz1 >> 24) << sh;
            scr->v_70[1].vz = ((sz2 << 16) >> 24) << sh;
            scr->v_70[2].vx = ((sz2 << 8) >> 24) << sh;
            scr->v_70[2].vz = ((sz3 << 24) >> 24) << sh;
            scr->v_70[3].vx = ((sz3 << 16) >> 24) << sh;
            scr->v_70[3].vz = (sz3 >> 24) << sh;
        }
        if (id & 2)
        {
            scr->v_70[0].vx = ox - scr->v_70[0].vx;
            scr->v_70[0].vz = oz - scr->v_70[0].vz;
            scr->v_70[1].vx = ox - scr->v_70[1].vx;
            scr->v_70[1].vz = oz - scr->v_70[1].vz;
            scr->v_70[2].vx = ox - scr->v_70[2].vx;
            scr->v_70[2].vz = oz - scr->v_70[2].vz;
        }
        else
        {
            scr->v_70[0].vx += ox;
            scr->v_70[0].vz += oz;
            scr->v_70[1].vx += ox;
            scr->v_70[1].vz += oz;
            scr->v_70[2].vx += ox;
            scr->v_70[2].vz += oz;
        }
        C8001F828_GTE_LDV3C(scr->v_70);
        scr->v_70[3].vy = oy;
        GTE_NOP2();
        GTE_RTPT();
        if (id & 2)
        {
            scr->v_70[3].vx = ox - scr->v_70[3].vx;
            scr->v_70[3].vz = oz - scr->v_70[3].vz;
        }
        else
        {
            scr->v_70[3].vx += ox;
            scr->v_70[3].vz += oz;
        }
        C8001F828_GTE_NCLIP();
        flags = face[-1];
        C8001F828_GTE_STMAC0(&opz);
        if (opz <= 0)
        {
            if (!C8001F828_BIT(flags, 30))
            {
                if (C8001F828_BIT(flags, 29))
                {
                    goto cull;
                }
                return;
            }
            opz = -opz;
        }
        pk = *(uint32 **)0x1F800070;
        C8001F828_GTE_STSXY3_FT(pk);
        C8001F828_GTE_STSXY3C(scr->xy_20);
        if (C8001F828_BIT(flags, 29))
        {
            scr->rgbc_14 = (flags & 0x03FFFFFF) | 0x24000000;
            C8001F828_GTE_STSZ3(&sz0, &sz1, &sz2);
            sz3 = sz2;
        }
        else
        {
            GTE_LDV0(&scr->v_70[3]);
            C8001F828_GTE_RTPS();
            scr->rgbc_14 = (flags & 0x03FFFFFF) | 0x2C000000;
            GTE_STSXY2(&pk[8]);
            GTE_STSXY2(&scr->xy_20[3]);
            C8001F828_GTE_STSZ4(&sz0, &sz1, &sz2, &sz3);
        }
        GTE_LWC2(6, &scr->rgbc_14);
        if (C8001F828_BIT(flags, 28))
        {
            scr->link_48 = tail;
        }
        else
        {
            if (sz0 < sz1)
            {
                zmax = sz1;
            }
            else
            {
                zmax = sz0;
            }
            if (sz2 < sz3)
            {
                sz0 = sz3;
            }
            else
            {
                sz0 = sz2;
            }
            if (sz0 < zmax)
            {
                sz0 = zmax;
            }
            if ((*(uint8 *)0x1F800078 & 1) && oy >= 0)
            {
                scr->link_48 = (uint32 *)(*(uint32 *)0x1F80003C + 0x1F40);
            }
            else
            {
                scr->link_48 = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            }
        }
        GTE_DPCS_RUN();
        if ((id << 24) <= 0x7FFFFFFF)
        {
            if ((id << 16) > 0x7FFFFFFF)
            {
                sz2 = tex[0];
                sz3 = tex[1];
                if (left >= 4)
                {
                    level = *(uint8 *)(0x1F800187 - left);
                    goto blend;
                }
            }
            else
            {
                sz2 = 0x1F0000;
                sz3 = 0x1F1F1F00;
            }
            level = shade;
        blend:
            lo    = level & 7;
            level = (lo << 5) | ((level >> 3) << 13) | (lo << 21) | ((level >> 3) << 29);
            sz2 += level;
            sz3 += level;
        }
        else
        {
            sz2           = tex[0];
            scr->uv_50[0] = sz2;
            sz3           = tex[1];
            scr->uv_50[1] = sz3;
            pk            = func_80022A94();
            if (!C8001F828_BIT(flags, 28))
            {
                tail = pk;
            }
            face += 4;
            tex += 2;
            continue;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_90 | scr->fog_08;
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_94;
        pk[7] = sz3 & 0xFFFF;
        if (!C8001F828_BIT(flags, 29))
        {
            pk[9] = (uint32)sz3 >> 16;
            w0    = 0x09000000;
        }
        else
        {
            w0 = 0x07000000;
        }
        if (C8001F828_BIT(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((uint32)pk & w1) | w0;
        }
        else
        {
            slot  = scr->link_48;
            pk[0] = w0 | *slot;
            *slot = (uint32)pk & w1;
        }
        if (!C8001F828_BIT(flags, 28))
        {
            tail = pk;
        }
        GTE_SWC2(22, &pk[1]);
        *(uint32 *)0x1F800070 += 0x28;
        goto next;
    cull:
        if (!C8001F828_BIT(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// Quad splitter: transforms the edge midpoints and centre of the quad (two RTPTs), derives
// their UVs, then emits four textured quads and up to four back-face-culled triangles, and
// links the new chain into the ordering table. The UVs are averaged per vertex in order
// (4, 5, 7, 8, then the centre). Each primitive is taken by advancing the buffer pointer at
// 0x1F800070 first and stepping back, which gives retail's copy of the old pointer. The
// triangle loop reuses three of the quad loop's four index variables, and is a do-while.
uint32 *func_80022A94(void)
{
    C8001F828_SVEC vec[3];
    sint32 clip;
    C8001F828_SPLIT2 *scr;
    uint32 *p;
    uint32 *last;
    uint8 *idx;
    uint32 clut;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;
    sint32 i;
    sint32 ax;
    sint32 ay;
    sint32 az;
    sint32 bx;
    sint32 by;
    sint32 bz;
    sint32 cx;
    sint32 cy;
    sint32 cz;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 mx;
    sint32 my;
    sint32 mz;
    sint32 nx;
    sint32 ny;
    sint32 nz;

    scr                   = C8001F828_SPLIT2_PTR;
    *(uint32 *)0x1F800140 = *(uint32 *)0x1F800144 & 0xF7FFFFFF;
    ax                    = C8001F828_SPLIT2_V[0].vx;
    ay                    = C8001F828_SPLIT2_V[0].vy;
    az                    = C8001F828_SPLIT2_V[0].vz;
    bx                    = C8001F828_SPLIT2_V[1].vx;
    by                    = C8001F828_SPLIT2_V[1].vy;
    bz                    = C8001F828_SPLIT2_V[1].vz;
    cx                    = C8001F828_SPLIT2_V[2].vx;
    cy                    = C8001F828_SPLIT2_V[2].vy;
    cz                    = C8001F828_SPLIT2_V[2].vz;
    dx                    = C8001F828_SPLIT2_V[3].vx;
    dy                    = C8001F828_SPLIT2_V[3].vy;
    dz                    = C8001F828_SPLIT2_V[3].vz;
    vec[0].vx             = (ax + bx) >> 1;
    vec[0].vy             = (ay + by) >> 1;
    vec[0].vz             = (az + bz) >> 1;
    vec[1].vx = mx = (ax + cx) >> 1;
    vec[1].vy = my = (ay + cy) >> 1;
    vec[1].vz = mz = (az + cz) >> 1;
    vec[2].vx = nx = (dx + bx) >> 1;
    vec[2].vy = ny = (dy + by) >> 1;
    vec[2].vz = nz = (dz + bz) >> 1;
    GTE_LDV3C(vec);
    GTE_NOP2();
    GTE_RTPT();
    vec[0].vx = (mx + nx) >> 1;
    vec[0].vy = (my + ny) >> 1;
    vec[0].vz = (mz + nz) >> 1;
    vec[1].vx = (dx + cx) >> 1;
    vec[1].vy = (dy + cy) >> 1;
    vec[1].vz = (dz + cz) >> 1;
    GTE_STSXY3(&scr->xy_20[4], &scr->xy_20[5], &scr->xy_20[7]);
    GTE_LDV3C(vec);
    GTE_NOP2();
    GTE_RTPT();
    C8001F828_SPLIT2_UV[8]  = (C8001F828_SPLIT2_UV[0] + C8001F828_SPLIT2_UV[2]) >> 1;
    C8001F828_SPLIT2_UV[9]  = (C8001F828_SPLIT2_UV[1] + C8001F828_SPLIT2_UV[3]) >> 1;
    C8001F828_SPLIT2_UV[10] = (C8001F828_SPLIT2_UV[0] + C8001F828_SPLIT2_UV[4]) >> 1;
    C8001F828_SPLIT2_UV[11] = (C8001F828_SPLIT2_UV[1] + C8001F828_SPLIT2_UV[5]) >> 1;
    C8001F828_SPLIT2_UV[14] = (C8001F828_SPLIT2_UV[2] + C8001F828_SPLIT2_UV[6]) >> 1;
    C8001F828_SPLIT2_UV[15] = (C8001F828_SPLIT2_UV[3] + C8001F828_SPLIT2_UV[7]) >> 1;
    C8001F828_SPLIT2_UV[16] = (C8001F828_SPLIT2_UV[4] + C8001F828_SPLIT2_UV[6]) >> 1;
    C8001F828_SPLIT2_UV[17] = (C8001F828_SPLIT2_UV[5] + C8001F828_SPLIT2_UV[7]) >> 1;
    C8001F828_SPLIT2_UV[12] = (C8001F828_SPLIT2_UV[8] + C8001F828_SPLIT2_UV[16]) >> 1;
    C8001F828_SPLIT2_UV[13] = (C8001F828_SPLIT2_UV[11] + C8001F828_SPLIT2_UV[15]) >> 1;
    GTE_STSXY0(&scr->xy_20[6]);
    GTE_STSXY1(&scr->xy_20[8]);
    clut = scr->clut_90 | *(uint32 *)0x1F800138;
    idx  = (uint8 *)0x1F8001D0;
    for (i = 0; i < 16; i += 4)
    {
        i0 = idx[i];
        i1 = idx[i + 1];
        i2 = idx[i + 2];
        i3 = idx[i + 3];
        *(uint32 *)0x1F800070 += 40;
        last    = *(uint32 **)0x1F800070 - 10;
        last[0] = (*(uint32 *)0x1F800070 & 0xFFFFFF) | 0x09000000;
        last[2] = scr->xy_20[i0];
        last[4] = scr->xy_20[i1];
        last[6] = scr->xy_20[i2];
        last[8] = scr->xy_20[i3];
        last[1] = scr->tpage_14;
        last[3] = scr->uv_50[i0] | clut;
        last[5] = scr->uv_50[i1] | scr->tpage_94;
        last[7] = scr->uv_50[i2];
        last[9] = scr->uv_50[i3];
    }
    p = last;
    i = 16;
    do
    {
        i1 = idx[i];
        i2 = idx[i + 1];
        i3 = idx[i + 2];
        i += 3;
        C8001F828_GTE_NCLIP_NOP(scr->xy_20[i1], scr->xy_20[i2], scr->xy_20[i3]);
        C8001F828_GTE_STMAC0(&clip);
        if (clip > 0)
        {
            *(uint32 *)0x1F800070 += 32;
            p    = *(uint32 **)0x1F800070 - 8;
            p[0] = (*(uint32 *)0x1F800070 & 0xFFFFFF) | 0x07000000;
            p[2] = scr->xy_20[i1];
            p[4] = scr->xy_20[i2];
            p[6] = scr->xy_20[i3];
            p[1] = scr->tpage_10;
            p[3] = scr->uv_50[i1] | clut;
            p[5] = scr->uv_50[i2] | scr->tpage_94;
            p[7] = scr->uv_50[i3];
        }
    } while (i < 28);
    addPrims(scr->link_48, last - 30, p);
    return last;
}

void func_80022FD4(uint16 **tbl)
{
    C8001F828_MODEL_BODY *b;
    C8001F828_MODEL *m;
    uint16 *src;
    sint32 i;

    if (D_800C356C == -1)
    {
        if (Scene_work.routine_0 != 0)
        {
            return;
        }
    }
    else
    {
        D_80098970 = 0;
        D_80098A78 = 0;
    }
    m                       = D_800BBA90;
    *(uint16 ***)0x1F800054 = tbl;
    for (i = 0; i < 11; i++, m++)
    {
        src = (*(uint16 ***)0x1F800054)[i];
        if (src != 0)
        {
            b           = &m->body;
            m->id.w     = *src++;
            b->w24      = *src++;
            b->w26      = *src++;
            b->w2a      = *src++;
            b->w28      = *src++;
            b->w20      = *src++;
            b->w22      = 0;
            b->xy_1c.x  = *src++;
            b->xy_1c.y  = *src++;
            b->w2c.h.lo = *src++;
            b->w2c.h.hi = *src++;
            b->w30.w    = *src;
            src += 6;
            b->next = src;
            if (m->id.b.flag != 0)
            {
                b->xy_18 = b->xy_1c;
                b->xy_c  = b->xy_18;
                m->x_4 = b->x_10 = b->xy_1c.x << 16;
                b->y_8 = b->y_14 = b->xy_1c.y << 16;
            }
        }
    }
}

// Camera-relative tile layers. The camera words are fields of the camera block D_800A3958
// (pos_98, vec_A8, rot_B8, pos_48.y): through the block GCC keeps &pos_98.x in a saved register
// and reaches rot_B8.vy (+0x22) and the others from it, as retail does with s5. The y offset's
// sign test is a conditional whose two arms each subtract pos_48.y (jump2 merges the tails).
// The tile header stores p[0] twice (0x02000000, then with the link): that keeps 0x02000000 in
// s8 as retail. Retail reuses its locals: the camera differences go through x, t, y and h, and
// the distance and the tile row share one variable (s1, live across the calls). The DR_MODE
// code 0xE1000000 is a local, and each row sets `code = attr | 0x64000000`.
// The first row goes through `work`, which later holds the layer's link (the addPrims macro
// written out). That later use is what keeps the quotient in its own register: cse.c's
// make_regs_eqv makes the copy's destination (dist) canonical only when it is referenced after
// the copy's source, so with `work` referenced last, y is computed from the quotient (v0) and
// dist gets a copy, as in retail. A dead `work = 0;` after the loop matches too.
void func_80023144(void)
{
    C8001F828_MODEL *m;
    uint32 *p;
    uint32 *start;
    uint32 *next;
    uint32 *map;
    sint32 dx;
    sint32 dz;
    sint32 d2;
    sint32 dist;
    sint32 t;
    sint32 a;
    sint32 col;
    sint32 colbase;
    sint32 x;
    sint32 y;
    sint32 v;
    sint32 u;
    uint32 mode;
    sint32 h;
    uint32 add;
    uint32 attr;
    uint32 code;
    uint32 size;
    sint32 work;

    if (D_80098824 != 0)
    {
        return;
    }
    D_800D9BD8 = VSync(1);
    x          = D_800A3958.work.pos_98.x;
    t          = D_800A3958.work.vec_A8.x;
    dx         = x - t;
    y          = D_800A3958.work.pos_98.z;
    h          = D_800A3958.work.vec_A8.z;
    dz         = y - h;
    p          = *(uint32 **)0x1F800070;
    start      = p;
    d2         = dx * dx + dz * dz;
    dist       = SquareRoot0(d2);
    if (dist != 0)
    {
        dist = (d2 / dist + dist) >> 1;
    }
    D_80098970++;
    D_80098A78 -= (dist * rsin(D_800A3958.work.rot_B8.vy - ratan2(dx, dz))) / 24;
    for (m = D_800BBA90; m < D_800BBA90 + 11; m++)
    {
        if (m->id.b.lo & 1)
        {
            m->body.x_10  = m->x_4;
            m->body.y_14  = m->body.y_8;
            m->body.xy_18 = m->body.xy_c;
            t             = (sint16)m->body.w24;
            if (m->id.b.flag == 0)
            {
                m->x_4 =
                    (((((D_800A3958.work.rot_B8.vy + m->body.xy_1c.x + D_80098A78 / (t * t)) * 8) +
                       ((uint32)((sint16)m->body.w20 * D_80098970) >> 8)) &
                      0x7FFF)
                     << 5) *
                    t * 2;
                a           = D_800A3958.work.rot_B8.vx;
                m->body.y_8 = (m->body.xy_1c.y << 16) -
                              (((a < 0x800) ? a * 0xF0 / 13 - D_800A3958.work.pos_48.y
                                            : (a - 0x1000) * 0xF0 / 13 - D_800A3958.work.pos_48.y)
                               << 11);
            }
            else
            {
                m->x_4 += (sint16)m->body.w20 << 8;
                m->body.y_8 += (sint16)m->body.w22 << 8;
            }
            func_8002366C((C8001F828_LAYER *)m);
        }
        if (m->id.b.lo & 2)
        {
            next    = p + 5;
            p[0]    = 0x02000000;
            mode    = 0xE1000000;
            p[1]    = m->body.w2a | ((m->body.w30.b.hi << 5) | mode);
            p[0]    = 0x02000000 | ((uint32)next & 0xFFFFFF);
            p[2]    = 0;
            p       = next;
            add     = (uint32)m->body.w28 << 14;
            map     = (uint32 *)m->body.next;
            t       = (sint16)m->body.w24;
            v       = m->body.xy_c.y;
            h       = (sint16)m->body.w26;
            attr    = m->body.w30.b.lo << 25;
            work    = v / 32;
            dist    = work;
            colbase = m->body.xy_c.x / 32;
            y       = -(sint16)(v - work * 32);

            for (; y < 0xF0; y += 0x20)
            {
                code = attr | 0x64000000;
                size = 0x200020;
                col  = colbase;
                u    = m->body.xy_c.x;
                x    = -(sint16)(u - (u / 32) * 32);
                for (; x < 0x140; x += 0x20)
                {
                    ((sint16 *)p)[4] = x;
                    ((sint16 *)p)[5] = y;
                    p[3]             = map[dist * t + col] + add;
                    col++;
                    if (col >= t)
                    {
                        col = 0;
                    }
                    p[0] = (((uint32)p + 0x14) & 0xFFFFFF) | 0x04000000;
                    p[1] = (m->body.w2c.w & 0xFFFFFF) | code;
                    p[4] = size;
                    p += 5;
                }
                dist++;
                if (dist >= h)
                {
                    dist = 0;
                }
            }
            work = getaddr(&D_80098934->layer[m->body.w2c.b.layer]);
            setaddr(p - 5, work);
            setaddr(&D_80098934->layer[m->body.w2c.b.layer], start);
            start = p;
        }
    }
    *(uint32 **)0x1F800070 = p;
}

void func_8002366C(C8001F828_LAYER *lp)
{
    sint32 lim;

    if (lp->wrap_x_on != 0)
    {
        lim = lp->wrap_x << 21;
        while (lp->x.w >= lim)
        {
            lp->x.w -= lim;
        }
        while (lp->x.w < 0)
        {
            lp->x.w += lim;
        }
    }
    lim = lp->wrap_y << 21;
    while (lp->y.w >= lim)
    {
        lp->y.w -= lim;
    }
    while (lp->y.w < 0)
    {
        lp->y.w += lim;
    }
    lp->prev_x = lp->x.w >> 16;
    lp->prev_y = lp->y.w >> 16;
}

// Takes the camera arguments and passes them through to func_80037FB4 unchanged: a0-a3 stay
// live, so reload puts the GTE pointer constants in t0 as retail does.
void func_80023728(C8001F828_CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    C8001F828_SCRVEC *scr = C8001F828_SCRV;
    C8001F828_SVEC pos;

    if (D_80098824 == 0)
    {
        C8001F828_SCR_75 = D_800C0DE6;
        func_80037FB4(vec, arg1, arg2, arg3);
        GTE_SET_MATRIX(0x1F800008);
        pos.vx = C8001F828_PL_POS(0);
        pos.vy = C8001F828_PL_POS(1);
        pos.vz = C8001F828_PL_POS(2);
        GTE_LDV0(&pos);
        GTE_NOP2();
        GTE_RTV0();
        GTE_STLVNL(0x1F8001B8);
        if (Scene_work.routine_0)
        {
            C8001F828_SCR_7C = 0;
        }
        else
        {
            C8001F828_SCR_7C = 0x2000000;
        }
        C8001F828_SCR_1BC = C8001F828_SCR_1C0 + 0x172;
        func_800176DC(D_800C0DC0, (void *)0x1F800100, 1);
        func_800176DC(D_80097C90, (void *)0x1F800120, 1);
        C8001F828_SCR_04 = 0;
        scr->vxy         = 0;
        scr->vz.w        = 0;
        func_80024E94((uint32 *)0x801F6080, 0);
        C8001F828_SCR_04 = 1;
    }
}

void func_800238B4(void)
{
    C8001F828_SVEC pos;
    sint16 sxy[2];
    sint32 otz;
    sint32 i;

    if (D_80098824 != 0)
    {
        return;
    }
    D_80098A08       = 0;
    D_800989AC       = 0;
    C8001F828_SCR_75 = D_800C0DE6;
    GTE_SET_MATRIX(0x1F800008);
    func_800176DC(D_80097C90, (void *)0x1F8001D0, 1);
    C8001F828_TIME_START = VSync(1);
    if (C8001F828_SCR_75 == 1)
    {
        func_80020A4C();
    }
    else
    {
        func_80020BB4();
    }
    C8001F828_TIME_A = (VSync(1) - C8001F828_TIME_START) & 0xFFFF;
    GTE_SET_MATRIX(0x1F800008);
    for (i = 0; i < 32; i++)
    {
        if (D_8009CF88[i].kind_2 == 0x33 && (D_8009CF88[i].flags_0 & 1) &&
            D_8009CF88[i].sub_3 == 0xFE)
        {
            pos = D_8009CF88[i].pos_ac;
            GTE_LDV0(&pos);
            GTE_NOP2();
            GTE_RTPS();
            GTE_STSXY2(sxy);
            GTE_SWC2(7, &otz);
            if (otz > 0)
            {
                func_800272D0(sxy[0], sxy[1], D_8009CF88[i].w_a * 2, D_8009CF88[i].h_b * 2);
            }
        }
    }
    pos.vx = C8001F828_PL_POS(0);
    pos.vy = C8001F828_PL_POS(1);
    pos.vz = C8001F828_PL_POS(2);
    GTE_LDV0(&pos);
    GTE_NOP2();
    GTE_RTV0();
    GTE_STLVNL(0x1F8001B8);
    if (Scene_work.routine_0)
    {
        C8001F828_SCR_7C = 0;
    }
    else
    {
        C8001F828_SCR_7C = 0x2000000;
    }
    C8001F828_SCR_1BC = C8001F828_SCR_1C0 + 0x172;
    func_800176DC(D_800C0DC0, (void *)0x1F800100, 1);
    func_800176DC(D_80097C90, (void *)0x1F800120, 1);
    C8001F828_TIME_START = VSync(1);
    func_80023C08();
    C8001F828_TIME_B = (VSync(1) - C8001F828_TIME_START) & 0xFFFF;
}

void func_80023C08(void)
{
    switch (C8001F828_SCR_75)
    {
        case 0:
        default:
            C8001F828_SCR_04 = 0x400;
            func_80024BAC(C8001F828_BUF_A, 0);
            func_80024BAC(C8001F828_BUF_B, 1);
            break;
        case 1:
            C8001F828_SCR_04 = 0;
            func_80024BAC(C8001F828_BUF_A, 1);
            func_80024BAC(C8001F828_BUF_B, 1);
            break;
        case 2:
            C8001F828_SCR_04 = 0;
            func_800267AC(C8001F828_BUF_A, 2);
            func_800267AC(C8001F828_BUF_B, 2);
            break;
        case 3:
            C8001F828_SCR_04 = 0;
            func_800267AC(C8001F828_BUF_A, 3);
            func_800267AC(C8001F828_BUF_B, 3);
            break;
    }
}

void func_80023CF0(uint8 *list, sint32 limit)
{
    C8001F828_SCR100 *sc;
    uint32 count;

    sc          = (C8001F828_SCR100 *)0x1F800100;
    count       = list[0];
    sc->copy[0] = ((C8001F828_LIST *)list)->param[0];
    sc->copy[1] = ((C8001F828_LIST *)list)->param[1];
    sc->copy[2] = ((C8001F828_LIST *)list)->param[2];
    list += count * 4 + 4;
    if (C8001F828_SCR_28 < (sint16)sc->w40)
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80023EA8(list);
            func_80023EA8(list + 0x18);
        }
        else
        {
            func_80023EA8(list + 0x10);
            func_80023EA8(list + 0x18);
        }
    }
    else
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80023EA8(list);
            func_80023EA8(list + 8);
        }
        else
        {
            func_80023EA8(list + 8);
            func_80023EA8(list + 0x10);
        }
    }
    func_80023EA8(list + 0x20);
    if (!(C8001F828_SCR_1BC < limit))
    {
        func_80023EA8(list + 0x28);
    }
}

// The header word and the loop counter share a variable (retail keeps both in s1).
void func_80023E1C(uint32 *list)
{
    uint32 i;
    uint32 *p;
    uint32 n;
    C8001F828_SCR100 *sc;

    sc          = (C8001F828_SCR100 *)0x1F800100;
    i           = list[0];
    n           = (i & 0x3F00) >> 7;
    sc->copy[0] = list[1];
    sc->copy[1] = list[2];
    sc->copy[2] = list[3];
    p           = &list[(i & 0xFF) + 1];
    i           = 0;
    do
    {
        func_80023EA8(&p[i]);
        i += 2;
    } while (i < n);
}

// Textured quad list renderer: unpacks each face's four corners (12 signed bytes, x/z signed,
// y unsigned) into the scratchpad, transforms them (RTPT, then RTPS for the fourth), culls back
// faces and faces off screen, depth-sorts into the ordering table (or chains behind the
// previous face when bit 28 is set), and hands large faces to the quad splitter. The header
// words are reused for the CLUT word and the two loop constants (retail keeps each in one
// register), the skip path has its own increments, and sz1 doubles as the face word.
void func_80023EA8(void *list)
{
    C8001F828_QUAD_WORK *scr;
    C8001F828_SVEC unused;
    uint32 *hdr;
    uint32 *face;
    uint32 *tex;
    uint32 *tail;
    uint32 *pk;
    uint32 *slot;
    uint32 flags;
    sint32 fog_sh;
    uint32 w0;
    uint32 w1;
    sint32 left;
    sint32 shift;
    sint32 sh;
    sint32 ox;
    sint32 oy;
    sint32 oz;
    sint32 opz;
    sint32 sz0;
    sint32 sz1; // also holds each packed face word in turn
    sint32 sz2;
    sint32 sz3;
    sint32 zmin;
    sint32 zmax;
    sint32 lo;
    sint32 hi;
    sint32 dx;
    sint32 dy;
    uint16 x0;
    uint16 x1;
    uint16 x2;
    uint16 x3;

    scr                   = C8001F828_QUAD_PTR;
    hdr                   = list;
    w1                    = hdr[1];
    w0                    = hdr[0];
    left                  = w1 >> 24;
    face                  = (uint32 *)((w1 & 0xFFFFFF) + 4);
    tex                   = (uint32 *)(w0 & 0xFFFFFF);
    shift                 = C8001F828_SHIFT;
    w1                    = C8001F828_SCR_C8((w0 >> 24) & 0xF);
    *(uint32 *)0x1F8001FC = left;
    *(uint32 *)0x1F800158 = w1 & 0xFFFF0000;
    *(uint32 *)0x1F80015C = w1 << 16;
    sh                    = (w0 >> 28) + shift;
    fog_sh                = shift + 9;
    ox                    = C8001F828_S16(0x1F800140) << shift;
    oy                    = C8001F828_S16(0x1F800142) << shift;
    oz                    = C8001F828_S16(0x1F800144) << shift;
    w0                    = 0x09000000;
    w1                    = 0xFFFFFF;
    tail                  = (uint32 *)1;
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (C8001F828_BIT(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1             = face[0];
        scr->v_98[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->v_98[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->v_98[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->v_98[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1             = face[1];
        scr->v_98[1].vy = oy - ((uint8)sz1 << sh);
        scr->v_98[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->v_98[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->v_98[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1             = face[2];
        scr->v_98[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        C8001F828_GTE_LDV3C(scr->v_98);
        GTE_NOP2();
        GTE_RTPT();
        scr->v_98[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->v_98[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->v_98[3].vz = ((sz1 >> 24) << sh) + oz;
        C8001F828_GTE_NCLIP();
        *(uint32 *)0x1F80014C = flags;
        C8001F828_GTE_STMAC0(&opz);
        if (opz <= 0)
        {
            if (!C8001F828_BIT(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = *(uint32 **)0x1F800070;
        C8001F828_GTE_STSXY3_FT(pk);
        C8001F828_GTE_STSXY3C(scr->xy_60.w);
        GTE_LDV0(&scr->v_98[3]);
        C8001F828_GTE_RTPS();
        scr->rgbc_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        GTE_STSXY2(&pk[8]);
        GTE_STSXY2(&scr->xy_60.w[3]);
        C8001F828_GTE_STSZ4(&sz0, &sz1, &sz2, &sz3);
        // On screen when a corner or the midpoint of a diagonal is
        if ((x0 = C8001F828_U16(0x1F800160)) < 0x140U && C8001F828_U16(0x1F800162) < 0xF0U)
        {
            goto visible;
        }
        if ((x1 = C8001F828_U16(0x1F800164)) < 0x140U && C8001F828_U16(0x1F800166) < 0xF0U)
        {
            goto visible;
        }
        if ((x2 = C8001F828_U16(0x1F800168)) < 0x140U && C8001F828_U16(0x1F80016A) < 0xF0U)
        {
            goto visible;
        }
        if ((x3 = C8001F828_U16(0x1F80016C)) < 0x140U && C8001F828_U16(0x1F80016E) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x0 + (sint16)x3) >> 1) < 0x140U &&
            (uint32)((C8001F828_S16(0x1F800162) + C8001F828_S16(0x1F80016E)) >> 1) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x1 + (sint16)x2) >> 1) >= 0x140U ||
            (uint32)((C8001F828_S16(0x1F800166) + C8001F828_S16(0x1F80016A)) >> 1) >= 0xF0U)
        {
            goto cull;
        }
    visible:
        if (sz0 < sz1)
        {
            lo = sz0;
            hi = sz1;
        }
        else
        {
            lo = sz1;
            hi = sz0;
        }
        if (sz2 < sz3)
        {
            zmin = sz2;
            zmax = sz3;
        }
        else
        {
            zmin = sz3;
            zmax = sz2;
        }
        if (lo < zmin)
        {
            zmin = lo;
        }
        if (zmax < hi)
        {
            zmax = hi;
        }
        if ((sint32)flags < 0)
        {
            if (!C8001F828_BIT(flags, 27))
            {
                sz0 = zmax;
            }
        }
        else
        {
            if (zmax < 0xC1)
            {
                goto cull;
            }
            if (C8001F828_BIT(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!C8001F828_BIT(flags, 28))
        {
            GTE_LWC2(6, &scr->rgbc_54);
            C8001F828_GTE_DPCS();
            scr->fog_48 = *(uint8 *)(0x1F800100 + ((sz0 >> fog_sh) & 0x1F)) << 16;
            GTE_SWC2(22, &scr->rgbc_54);
        }
        if ((sint32)flags < 0 && C8001F828_BIT(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (C8001F828_BIT(flags, 29) && zmin >= 0x181)
        {
            goto plain;
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            dx = ((sint16)scr->xy_60.h[0].x + (sint16)scr->xy_60.h[3].x -
                  (sint16)scr->xy_60.h[1].x - (sint16)scr->xy_60.h[2].x) >>
                 1;
            dy = ((sint16)scr->xy_60.h[0].y + (sint16)scr->xy_60.h[3].y -
                  (sint16)scr->xy_60.h[1].y - (sint16)scr->xy_60.h[2].y) >>
                 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        {
            if (C8001F828_BIT(flags, 28))
            {
                scr->link_3c = tail;
            }
            else
            {
                scr->link_3c = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            }
            scr->uv_88[0] = sz2;
            scr->uv_88[1] = sz3;
            pk            = func_8002466C();
            if (!C8001F828_BIT(flags, 28))
            {
                tail = pk;
            }
            goto next;
        }
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5c;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (C8001F828_BIT(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((uint32)pk & w1) | w0;
        }
        else
        {
            slot  = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            pk[0] = w0 | *slot;
            *slot = (uint32)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!C8001F828_BIT(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc_54;
        *(uint32 *)0x1F800070 += 0x28;
        goto next;
    cull:
        if (!C8001F828_BIT(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// Quad splitter: transforms the edge midpoints and centre of the quad (two RTPTs), derives
// their UVs, then emits four textured quads and up to four back-face-culled triangles, and
// links the new chain into the ordering table. The UVs are averaged per vertex in order
// (4, 5, 7, 8, then the centre). Each primitive is taken by advancing the buffer pointer at
// 0x1F800070 first and stepping back, which gives retail's copy of the old pointer. The
// triangle loop reuses three of the quad loop's four index variables, and is a do-while.
uint32 *func_8002466C(void)
{
    C8001F828_SVEC vec[3];
    sint32 clip;
    C8001F828_SPLIT *scr;
    uint32 *p;
    uint32 *last;
    uint8 *idx;
    uint32 clut;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;
    sint32 i;
    sint32 ax;
    sint32 ay;
    sint32 az;
    sint32 bx;
    sint32 by;
    sint32 bz;
    sint32 cx;
    sint32 cy;
    sint32 cz;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 mx;
    sint32 my;
    sint32 mz;
    sint32 nx;
    sint32 ny;
    sint32 nz;

    scr                   = C8001F828_SPLIT_PTR;
    *(uint32 *)0x1F800150 = *(uint32 *)0x1F800154 & 0xF7FFFFFF;
    ax                    = C8001F828_SPLIT_V[0].vx;
    ay                    = C8001F828_SPLIT_V[0].vy;
    az                    = C8001F828_SPLIT_V[0].vz;
    bx                    = C8001F828_SPLIT_V[1].vx;
    by                    = C8001F828_SPLIT_V[1].vy;
    bz                    = C8001F828_SPLIT_V[1].vz;
    cx                    = C8001F828_SPLIT_V[2].vx;
    cy                    = C8001F828_SPLIT_V[2].vy;
    cz                    = C8001F828_SPLIT_V[2].vz;
    dx                    = C8001F828_SPLIT_V[3].vx;
    dy                    = C8001F828_SPLIT_V[3].vy;
    dz                    = C8001F828_SPLIT_V[3].vz;
    vec[0].vx             = (ax + bx) >> 1;
    vec[0].vy             = (ay + by) >> 1;
    vec[0].vz             = (az + bz) >> 1;
    vec[1].vx = mx = (ax + cx) >> 1;
    vec[1].vy = my = (ay + cy) >> 1;
    vec[1].vz = mz = (az + cz) >> 1;
    vec[2].vx = nx = (dx + bx) >> 1;
    vec[2].vy = ny = (dy + by) >> 1;
    vec[2].vz = nz = (dz + bz) >> 1;
    GTE_LDV3C(vec);
    GTE_NOP2();
    GTE_RTPT();
    vec[0].vx = (mx + nx) >> 1;
    vec[0].vy = (my + ny) >> 1;
    vec[0].vz = (mz + nz) >> 1;
    vec[1].vx = (dx + cx) >> 1;
    vec[1].vy = (dy + cy) >> 1;
    vec[1].vz = (dz + cz) >> 1;
    GTE_STSXY3(&scr->xy_60[4], &scr->xy_60[5], &scr->xy_60[7]);
    GTE_LDV3C(vec);
    GTE_NOP2();
    GTE_RTPT();
    C8001F828_SPLIT_UV[8]  = (C8001F828_SPLIT_UV[0] + C8001F828_SPLIT_UV[2]) >> 1;
    C8001F828_SPLIT_UV[9]  = (C8001F828_SPLIT_UV[1] + C8001F828_SPLIT_UV[3]) >> 1;
    C8001F828_SPLIT_UV[10] = (C8001F828_SPLIT_UV[0] + C8001F828_SPLIT_UV[4]) >> 1;
    C8001F828_SPLIT_UV[11] = (C8001F828_SPLIT_UV[1] + C8001F828_SPLIT_UV[5]) >> 1;
    C8001F828_SPLIT_UV[14] = (C8001F828_SPLIT_UV[2] + C8001F828_SPLIT_UV[6]) >> 1;
    C8001F828_SPLIT_UV[15] = (C8001F828_SPLIT_UV[3] + C8001F828_SPLIT_UV[7]) >> 1;
    C8001F828_SPLIT_UV[16] = (C8001F828_SPLIT_UV[4] + C8001F828_SPLIT_UV[6]) >> 1;
    C8001F828_SPLIT_UV[17] = (C8001F828_SPLIT_UV[5] + C8001F828_SPLIT_UV[7]) >> 1;
    C8001F828_SPLIT_UV[12] = (C8001F828_SPLIT_UV[8] + C8001F828_SPLIT_UV[16]) >> 1;
    C8001F828_SPLIT_UV[13] = (C8001F828_SPLIT_UV[11] + C8001F828_SPLIT_UV[15]) >> 1;
    GTE_STSXY0(&scr->xy_60[6]);
    GTE_STSXY1(&scr->xy_60[8]);
    clut = *(uint32 *)0x1F800158 | *(uint32 *)0x1F800148;
    idx  = (uint8 *)0x1F800120;
    for (i = 0; i < 16; i += 4)
    {
        i0 = idx[i];
        i1 = idx[i + 1];
        i2 = idx[i + 2];
        i3 = idx[i + 3];
        *(uint32 *)0x1F800070 += 40;
        last    = *(uint32 **)0x1F800070 - 10;
        last[0] = (*(uint32 *)0x1F800070 & 0xFFFFFF) | 0x09000000;
        last[2] = scr->xy_60[i0];
        last[4] = scr->xy_60[i1];
        last[6] = scr->xy_60[i2];
        last[8] = scr->xy_60[i3];
        last[1] = scr->tpage_54;
        last[3] = scr->uv_88[i0] | clut;
        last[5] = scr->uv_88[i1] | scr->tpage_5c;
        last[7] = scr->uv_88[i2];
        last[9] = scr->uv_88[i3];
    }
    p = last;
    i = 16;
    do
    {
        i1 = idx[i];
        i2 = idx[i + 1];
        i3 = idx[i + 2];
        i += 3;
        C8001F828_GTE_NCLIP_NOP(scr->xy_60[i1], scr->xy_60[i2], scr->xy_60[i3]);
        C8001F828_GTE_STMAC0(&clip);
        if (clip > 0)
        {
            *(uint32 *)0x1F800070 += 32;
            p    = *(uint32 **)0x1F800070 - 8;
            p[0] = (*(uint32 *)0x1F800070 & 0xFFFFFF) | 0x07000000;
            p[2] = scr->xy_60[i1];
            p[4] = scr->xy_60[i2];
            p[6] = scr->xy_60[i3];
            p[1] = scr->tpage_50;
            p[3] = scr->uv_88[i1] | clut;
            p[5] = scr->uv_88[i2] | scr->tpage_5c;
            p[7] = scr->uv_88[i3];
        }
    } while (i < 28);
    addPrims(scr->link_3c, last - 30, p);
    return last;
}

void func_80024BAC(void *p, sint32 mode)
{
    uint32 *flags;
    uint32 *rec;
    uint32 *row_end;
    uint32 *fp;
    uint32 bits;
    uint32 *ofs;
    uint32 *data;
    uint32 *q;
    sint32 out[3];
    sint32 z;
    C8001F828_SCRVEC *sc;

    sc    = C8001F828_SCRV;
    flags = p;
    rec   = *(uint32 **)0x1F80004C;
    fp    = rec + 0x1800;
    *flags &= 0x7FFFFFFF;
    do
    {
        bits = *flags;
        if (bits != 0)
        {
            *flags  = 0;
            row_end = rec + 0x60;
            q       = rec + 1;
            do
            {
                if ((sint32)bits < 0)
                {
                    data     = (uint32 *)(q[1] & 0xFFFFFF);
                    sc->vxy  = rec[0];
                    sc->vz.w = q[0];
                    GTE_LDV0(&sc->vxy);
                    GTE_NOP2();
                    GTE_RTV0();
                    GTE_STLVNL(out);
                    z      = out[2] >> C8001F828_SHIFT;
                    out[2] = z;
                    if (z >= 0x1C21)
                    {
                        ofs = data + 8;
                    }
                    else if (z >= 0xAF1)
                    {
                        ofs = data + 7;
                    }
                    else
                    {
                        ofs = data + 6;
                    }
                    if (sc->vz.h.flag == 0)
                    {
                        ofs += 3;
                    }
                    // The entry word replaces its pointer in one variable, as retail reuses the register
                    ofs = (uint32 *)*ofs;
                    D_80089890[mode][(uint32)ofs >> 31]((uint32)ofs & 0xFFFFFF, out[2]);
                }
                bits <<= 1;
                rec += 3;
                q += 3;
            } while (rec < row_end);
        }
        else
        {
            rec += 0x60;
        }
        flags++;
    } while (rec < fp);
}

void func_80024D4C(uint8 *list, sint32 limit)
{
    C8001F828_SCR100 *sc;
    uint32 i;
    uint32 count;

    sc    = (C8001F828_SCR100 *)0x1F800100;
    count = list[0];
    for (i = 0; i < count; i++)
    {
        sc->copy[i] = ((uint32 *)list)[i + 1];
    }
    list += count * 4 + 4;
    if (C8001F828_SCR_28 < (sint16)sc->w40)
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80024F30(list);
            func_80024F30(list + 0x18);
        }
        else
        {
            func_80024F30(list + 0x10);
            func_80024F30(list + 0x18);
        }
    }
    else
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80024F30(list);
            func_80024F30(list + 8);
        }
        else
        {
            func_80024F30(list + 8);
            func_80024F30(list + 0x10);
        }
    }
    func_80024F30(list + 0x20);
    if (!(C8001F828_SCR_1BC < limit))
    {
        func_80024F30(list + 0x28);
    }
}

// The only caller passes a second argument (0) that this function never reads.
void func_80024E94(uint32 *list, sint32 mode)
{
    uint32 i;
    uint32 n;
    uint32 count;
    uint32 *p;
    uint32 *src;
    uint32 *dst;
    uint32 unused[2]; // unused local; reserves the 8 bytes of frame

    i     = list[0];
    n     = (i & 0x3F00) >> 7;
    count = i & 0xFF;
    i     = 0;
    if (count != 0)
    {
        src = list;
        dst = (uint32 *)0x1F800100;
        do
        {
            dst[0x32] = src[1];
            src++;
            i++;
            dst++;
        } while (i < count);
        i = 0;
    }
    p = &list[count + 1];
    do
    {
        func_80024F30(p);
        i += 2;
        p += 2;
    } while (i < n);
}

// Variant of func_80023EA8 without the on-screen test: near faces covering the screen centre
// add the colour at 0x1F80007C (the z extent locals are reused for the x and y extents), and
// with bit 24 a face starts a new chain at its ordering-table slot.
void func_80024F30(void *list)
{
    C8001F828_QUAD_WORK *scr;
    C8001F828_SVEC unused;
    uint32 *hdr;
    uint32 *face;
    uint32 *tex;
    uint32 *tail;
    uint32 *pk;
    uint32 *slot;
    uint32 flags;
    sint32 fog_sh;
    uint32 w0;
    uint32 w1;
    sint32 left;
    sint32 shift;
    sint32 sh;
    sint32 ox;
    sint32 oy;
    sint32 oz;
    sint32 opz;
    sint32 sz0;
    sint32 sz1; // also holds each packed face word in turn
    sint32 sz2;
    sint32 sz3;
    sint32 zmin;
    sint32 zmax;
    sint32 lo;
    sint32 hi;
    sint32 dx;
    sint32 dy;

    scr                   = C8001F828_QUAD_PTR;
    hdr                   = list;
    w1                    = hdr[1];
    w0                    = hdr[0];
    left                  = w1 >> 24;
    face                  = (uint32 *)((w1 & 0xFFFFFF) + 4);
    tex                   = (uint32 *)(w0 & 0xFFFFFF);
    shift                 = C8001F828_SHIFT;
    w1                    = C8001F828_SCR_C8((w0 >> 24) & 0xF);
    *(uint32 *)0x1F8001FC = left;
    *(uint32 *)0x1F800158 = w1 & 0xFFFF0000;
    *(uint32 *)0x1F80015C = w1 << 16;
    sh                    = (w0 >> 28) + shift;
    fog_sh                = shift + 9;
    ox                    = C8001F828_S16(0x1F800140) << shift;
    oy                    = C8001F828_S16(0x1F800142) << shift;
    oz                    = C8001F828_S16(0x1F800144) << shift;
    w0                    = 0x09000000;
    w1                    = 0xFFFFFF;
    tail                  = (uint32 *)1;
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (C8001F828_BIT(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1             = face[0];
        scr->v_98[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->v_98[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->v_98[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->v_98[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1             = face[1];
        scr->v_98[1].vy = oy - ((uint8)sz1 << sh);
        scr->v_98[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->v_98[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->v_98[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1             = face[2];
        scr->v_98[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        C8001F828_GTE_LDV3C(scr->v_98);
        GTE_NOP2();
        GTE_RTPT();
        scr->v_98[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->v_98[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->v_98[3].vz = ((sz1 >> 24) << sh) + oz;
        C8001F828_GTE_NCLIP();
        *(uint32 *)0x1F80014C = flags;
        C8001F828_GTE_STMAC0(&opz);
        if (opz <= 0)
        {
            if (!C8001F828_BIT(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = *(uint32 **)0x1F800070;
        C8001F828_GTE_STSXY3_FT(pk);
        C8001F828_GTE_STSXY3C(scr->xy_60.w);
        GTE_LDV0(&scr->v_98[3]);
        C8001F828_GTE_RTPS();
        scr->rgbc_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        GTE_STSXY2(&pk[8]);
        GTE_STSXY2(&scr->xy_60.w[3]);
        C8001F828_GTE_STSZ4(&sz0, &sz1, &sz2, &sz3);
        if (sz0 < sz1)
        {
            lo = sz0;
            hi = sz1;
        }
        else
        {
            lo = sz1;
            hi = sz0;
        }
        if (sz2 < sz3)
        {
            zmin = sz2;
            zmax = sz3;
        }
        else
        {
            zmin = sz3;
            zmax = sz2;
        }
        if (lo < zmin)
        {
            zmin = lo;
        }
        if (zmax < hi)
        {
            zmax = hi;
        }
        if ((sint32)flags < 0)
        {
            if (!C8001F828_BIT(flags, 27))
            {
                sz0 = zmax;
            }
        }
        else
        {
            if (zmax < 0xC1)
            {
                goto cull;
            }
            if (C8001F828_BIT(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!C8001F828_BIT(flags, 28))
        {
            GTE_LWC2(6, &scr->rgbc_54);
            C8001F828_GTE_DPCS();
            scr->fog_48 = *(uint8 *)(0x1F800100 + ((sz0 >> fog_sh) & 0x1F)) << 16;
            GTE_SWC2(22, &scr->rgbc_54);
        }
        if ((sint32)flags < 0 && C8001F828_BIT(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (C8001F828_BIT(flags, 29))
        {
            if (zmin >= 0x181)
            {
                goto plain;
            }
            if (C8001F828_BIT(flags, 24))
            {
                goto plain;
            }
        }
        // Near faces covering the screen centre take the extra colour at 0x1F80007C
        if ((sint32)flags > 0 && zmax < *(sint32 *)0x1F8001C0)
        {
            if (C8001F828_S16(0x1F800160) < C8001F828_S16(0x1F800164))
            {
                lo = C8001F828_S16(0x1F800160);
                hi = C8001F828_S16(0x1F800164);
            }
            else
            {
                lo = C8001F828_S16(0x1F800164);
                hi = C8001F828_S16(0x1F800160);
            }
            if (C8001F828_S16(0x1F800168) < C8001F828_S16(0x1F80016C))
            {
                zmin = C8001F828_S16(0x1F800168);
                zmax = C8001F828_S16(0x1F80016C);
            }
            else
            {
                zmin = C8001F828_S16(0x1F80016C);
                zmax = C8001F828_S16(0x1F800168);
            }
            if (lo < zmin)
            {
                zmin = lo;
            }
            if (zmax < hi)
            {
                zmax = hi;
            }
            if (zmax >= 0x97 && zmin < 0xAA)
            {
                if (C8001F828_S16(0x1F800162) < C8001F828_S16(0x1F800166))
                {
                    lo = C8001F828_S16(0x1F800162);
                    hi = C8001F828_S16(0x1F800166);
                }
                else
                {
                    lo = C8001F828_S16(0x1F800166);
                    hi = C8001F828_S16(0x1F800162);
                }
                if (C8001F828_S16(0x1F80016A) < C8001F828_S16(0x1F80016E))
                {
                    zmin = C8001F828_S16(0x1F80016A);
                    zmax = C8001F828_S16(0x1F80016E);
                }
                else
                {
                    zmin = C8001F828_S16(0x1F80016E);
                    zmax = C8001F828_S16(0x1F80016A);
                }
                if (lo < zmin)
                {
                    zmin = lo;
                }
                if (zmax < hi)
                {
                    zmax = hi;
                }
                if (zmax >= 0x79 && zmin < 0xA0)
                {
                    scr->rgbc_54 |= *(uint32 *)0x1F80007C;
                }
            }
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            dx = ((sint16)scr->xy_60.h[0].x + (sint16)scr->xy_60.h[3].x -
                  (sint16)scr->xy_60.h[1].x - (sint16)scr->xy_60.h[2].x) >>
                 1;
            dy = ((sint16)scr->xy_60.h[0].y + (sint16)scr->xy_60.h[3].y -
                  (sint16)scr->xy_60.h[1].y - (sint16)scr->xy_60.h[2].y) >>
                 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        {
            if (C8001F828_BIT(flags, 28))
            {
                scr->link_3c = tail;
            }
            else
            {
                scr->link_3c = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            }
            scr->uv_88[0] = sz2;
            scr->uv_88[1] = sz3;
            pk            = func_8002466C();
            if (!C8001F828_BIT(flags, 28))
            {
                tail = pk;
            }
            goto next;
        }
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5c;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (C8001F828_BIT(flags, 28))
        {
            pk[0] = w0;
            addPrim(tail, pk);
        }
        else
        {
            slot  = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            pk[0] = w0 | *slot;
            if (C8001F828_BIT(flags, 24))
            {
                tail = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
                goto next;
            }
            *slot = (uint32)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!C8001F828_BIT(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc_54;
        *(uint32 *)0x1F800070 += 0x28;
        goto next;
    cull:
        if (!C8001F828_BIT(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

void func_80025748(uint8 *list, sint32 limit)
{
    C8001F828_SCR100 *sc;
    uint32 count;

    sc          = (C8001F828_SCR100 *)0x1F800100;
    count       = list[0];
    sc->copy[0] = ((C8001F828_LIST *)list)->param[0];
    sc->copy[1] = ((C8001F828_LIST *)list)->param[1];
    sc->copy[2] = ((C8001F828_LIST *)list)->param[2];
    list += count * 4 + 4;
    if (C8001F828_SCR_28 < (sint16)sc->w40)
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80025900(list);
            func_80025900(list + 0x18);
        }
        else
        {
            func_80025900(list + 0x10);
            func_80025900(list + 0x18);
        }
    }
    else
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80025900(list);
            func_80025900(list + 8);
        }
        else
        {
            func_80025900(list + 8);
            func_80025900(list + 0x10);
        }
    }
    func_80025900(list + 0x20);
    if (!(C8001F828_SCR_1BC < limit))
    {
        func_80025900(list + 0x28);
    }
}

// The header word and the loop counter share a variable (retail keeps both in s1).
void func_80025874(uint32 *list)
{
    uint32 i;
    uint32 *p;
    uint32 n;
    C8001F828_SCR100 *sc;

    sc          = (C8001F828_SCR100 *)0x1F800100;
    i           = list[0];
    n           = (i & 0x3F00) >> 7;
    sc->copy[0] = list[1];
    sc->copy[1] = list[2];
    sc->copy[2] = list[3];
    p           = &list[(i & 0xFF) + 1];
    i           = 0;
    do
    {
        func_80025900(&p[i]);
        i += 2;
    } while (i < n);
}

// Variant of func_80023EA8 that keeps back faces: a face seen from behind is drawn only
// beyond the depth at 0x1F8001C0, and without bit 30 it is drawn flat in colour 0x010101 at
// its far depth. Near faces covering the screen centre add the colour at 0x1F80007C as in
// func_80024F30.
void func_80025900(void *list)
{
    C8001F828_QUAD_WORK *scr;
    C8001F828_SVEC unused;
    uint32 *hdr;
    uint32 *face;
    uint32 *tex;
    uint32 *tail;
    uint32 *pk;
    uint32 *slot;
    uint32 flags;
    sint32 fog_sh;
    uint32 w0;
    uint32 w1;
    sint32 left;
    sint32 shift;
    sint32 sh;
    sint32 ox;
    sint32 oy;
    sint32 oz;
    sint32 opz;
    sint32 sz0;
    sint32 sz1;
    sint32 sz2;
    sint32 sz3;
    sint32 zmin;
    sint32 zmax;
    sint32 lo;
    sint32 hi;
    sint32 dx;
    sint32 dy;
    uint16 x0;
    uint16 x1;
    uint16 x2;
    uint16 x3;

    scr                   = C8001F828_QUAD_PTR;
    hdr                   = list;
    w1                    = hdr[1];
    w0                    = hdr[0];
    left                  = w1 >> 24;
    face                  = (uint32 *)((w1 & 0xFFFFFF) + 4);
    tex                   = (uint32 *)(w0 & 0xFFFFFF);
    shift                 = C8001F828_SHIFT;
    w1                    = C8001F828_SCR_C8((w0 >> 24) & 0xF);
    *(uint32 *)0x1F8001FC = left;
    *(uint32 *)0x1F800158 = w1 & 0xFFFF0000;
    *(uint32 *)0x1F80015C = w1 << 16;
    sh                    = (w0 >> 28) + shift;
    fog_sh                = shift + 9;
    ox                    = C8001F828_S16(0x1F800140) << shift;
    oy                    = C8001F828_S16(0x1F800142) << shift;
    oz                    = C8001F828_S16(0x1F800144) << shift;
    w0                    = 0x09000000;
    w1                    = 0xFFFFFF;
    tail                  = (uint32 *)1;
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (C8001F828_BIT(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1             = face[0];
        scr->v_98[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->v_98[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->v_98[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->v_98[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1             = face[1];
        scr->v_98[1].vy = oy - ((uint8)sz1 << sh);
        scr->v_98[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->v_98[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->v_98[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1             = face[2];
        scr->v_98[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        C8001F828_GTE_LDV3C(scr->v_98);
        GTE_NOP2();
        GTE_RTPT();
        scr->v_98[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->v_98[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->v_98[3].vz = ((sz1 >> 24) << sh) + oz;
        C8001F828_GTE_NCLIP();
        *(uint32 *)0x1F80014C = flags;
        C8001F828_GTE_STMAC0(&opz);
        if (opz == 0)
        {
            goto cull;
        }
        if (opz < 0 && C8001F828_BIT(flags, 30))
        {
            opz = -opz;
        }
        pk = *(uint32 **)0x1F800070;
        C8001F828_GTE_STSXY3_FT(pk);
        C8001F828_GTE_STSXY3C(scr->xy_60.w);
        GTE_LDV0(&scr->v_98[3]);
        C8001F828_GTE_RTPS();
        scr->rgbc_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        GTE_STSXY2(&pk[8]);
        GTE_STSXY2(&scr->xy_60.w[3]);
        C8001F828_GTE_STSZ4(&sz0, &sz1, &sz2, &sz3);
        // On screen when a corner or the midpoint of a diagonal is
        if ((x0 = C8001F828_U16(0x1F800160)) < 0x140U && C8001F828_U16(0x1F800162) < 0xF0U)
        {
            goto visible;
        }
        if ((x1 = C8001F828_U16(0x1F800164)) < 0x140U && C8001F828_U16(0x1F800166) < 0xF0U)
        {
            goto visible;
        }
        if ((x2 = C8001F828_U16(0x1F800168)) < 0x140U && C8001F828_U16(0x1F80016A) < 0xF0U)
        {
            goto visible;
        }
        if ((x3 = C8001F828_U16(0x1F80016C)) < 0x140U && C8001F828_U16(0x1F80016E) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x0 + (sint16)x3) >> 1) < 0x140U &&
            (uint32)((C8001F828_S16(0x1F800162) + C8001F828_S16(0x1F80016E)) >> 1) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x1 + (sint16)x2) >> 1) >= 0x140U ||
            (uint32)((C8001F828_S16(0x1F800166) + C8001F828_S16(0x1F80016A)) >> 1) >= 0xF0U)
        {
            goto cull;
        }
    visible:
        if (sz0 < sz1)
        {
            lo = sz0;
            hi = sz1;
        }
        else
        {
            lo = sz1;
            hi = sz0;
        }
        if (sz2 < sz3)
        {
            zmin = sz2;
            zmax = sz3;
        }
        else
        {
            zmin = sz3;
            zmax = sz2;
        }
        if (lo < zmin)
        {
            zmin = lo;
        }
        if (zmax < hi)
        {
            zmax = hi;
        }
        if ((sint32)flags < 0)
        {
            if (!C8001F828_BIT(flags, 27))
            {
                sz0 = zmax;
            }
        }
        else
        {
            if (zmax < 0xC1)
            {
                goto cull;
            }
            if (C8001F828_BIT(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!C8001F828_BIT(flags, 28))
        {
            GTE_LWC2(6, &scr->rgbc_54);
            C8001F828_GTE_DPCS();
            scr->fog_48 = *(uint8 *)(0x1F800100 + ((sz0 >> fog_sh) & 0x1F)) << 16;
            GTE_SWC2(22, &scr->rgbc_54);
        }
        if ((sint32)flags < 0 && C8001F828_BIT(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (opz < 0)
        {
            if (*(sint32 *)0x1F8001C0 >= zmin)
            {
                goto cull;
            }
            if (C8001F828_BIT(flags, 24))
            {
                goto cull;
            }
            opz = -opz;
            if (!C8001F828_BIT(flags, 30))
            {
                scr->rgbc_54 = 0x2C010101;
                sz0          = zmax;
                goto plain;
            }
        }
        if (C8001F828_BIT(flags, 29) && zmin >= 0x181)
        {
            goto plain;
        }
        // Near faces covering the screen centre take the extra colour at 0x1F80007C
        if ((sint32)flags > 0 && zmax < *(sint32 *)0x1F8001C0)
        {
            if (C8001F828_S16(0x1F800160) < C8001F828_S16(0x1F800164))
            {
                lo = C8001F828_S16(0x1F800160);
                hi = C8001F828_S16(0x1F800164);
            }
            else
            {
                lo = C8001F828_S16(0x1F800164);
                hi = C8001F828_S16(0x1F800160);
            }
            if (C8001F828_S16(0x1F800168) < C8001F828_S16(0x1F80016C))
            {
                zmin = C8001F828_S16(0x1F800168);
                zmax = C8001F828_S16(0x1F80016C);
            }
            else
            {
                zmin = C8001F828_S16(0x1F80016C);
                zmax = C8001F828_S16(0x1F800168);
            }
            if (lo < zmin)
            {
                zmin = lo;
            }
            if (zmax < hi)
            {
                zmax = hi;
            }
            if (zmax >= 0x97 && zmin < 0xAA)
            {
                if (C8001F828_S16(0x1F800162) < C8001F828_S16(0x1F800166))
                {
                    lo = C8001F828_S16(0x1F800162);
                    hi = C8001F828_S16(0x1F800166);
                }
                else
                {
                    lo = C8001F828_S16(0x1F800166);
                    hi = C8001F828_S16(0x1F800162);
                }
                if (C8001F828_S16(0x1F80016A) < C8001F828_S16(0x1F80016E))
                {
                    zmin = C8001F828_S16(0x1F80016A);
                    zmax = C8001F828_S16(0x1F80016E);
                }
                else
                {
                    zmin = C8001F828_S16(0x1F80016E);
                    zmax = C8001F828_S16(0x1F80016A);
                }
                if (lo < zmin)
                {
                    zmin = lo;
                }
                if (zmax < hi)
                {
                    zmax = hi;
                }
                if (zmax >= 0x79 && zmin < 0xA0)
                {
                    scr->rgbc_54 |= *(uint32 *)0x1F80007C;
                }
            }
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            dx = ((sint16)scr->xy_60.h[0].x + (sint16)scr->xy_60.h[3].x -
                  (sint16)scr->xy_60.h[1].x - (sint16)scr->xy_60.h[2].x) >>
                 1;
            dy = ((sint16)scr->xy_60.h[0].y + (sint16)scr->xy_60.h[3].y -
                  (sint16)scr->xy_60.h[1].y - (sint16)scr->xy_60.h[2].y) >>
                 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        {
            if (C8001F828_BIT(flags, 28))
            {
                scr->link_3c = tail;
            }
            else
            {
                scr->link_3c = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            }
            scr->uv_88[0] = sz2;
            scr->uv_88[1] = sz3;
            pk            = func_8002466C();
            if (!C8001F828_BIT(flags, 28))
            {
                tail = pk;
            }
            goto next;
        }
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5c;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (C8001F828_BIT(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((uint32)pk & w1) | w0;
        }
        else
        {
            slot  = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            pk[0] = w0 | *slot;
            *slot = (uint32)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!C8001F828_BIT(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc_54;
        *(uint32 *)0x1F800070 += 0x28;
        goto next;
    cull:
        if (!C8001F828_BIT(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// Quad splitter: transforms the edge midpoints and centre of the quad (two RTPTs), derives
// their UVs, then emits four textured quads and up to four back-face-culled triangles, and
// links the new chain into the ordering table. The UVs are averaged per vertex in order
// (4, 5, 7, 8, then the centre). Each primitive is taken by advancing the buffer pointer at
// 0x1F800070 first and stepping back, which gives retail's copy of the old pointer. The
// triangle loop reuses three of the quad loop's four index variables, and is a do-while.
uint32 *func_8002626C(void)
{
    C8001F828_SVEC vec[3];
    sint32 clip;
    C8001F828_SPLIT *scr;
    uint32 *p;
    uint32 *last;
    uint8 *idx;
    uint32 clut;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;
    sint32 i;
    sint32 ax;
    sint32 ay;
    sint32 az;
    sint32 bx;
    sint32 by;
    sint32 bz;
    sint32 cx;
    sint32 cy;
    sint32 cz;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 mx;
    sint32 my;
    sint32 mz;
    sint32 nx;
    sint32 ny;
    sint32 nz;

    scr                   = C8001F828_SPLIT_PTR;
    *(uint32 *)0x1F800150 = *(uint32 *)0x1F800154 & 0xF7FFFFFF;
    ax                    = C8001F828_SPLIT_V[0].vx;
    ay                    = C8001F828_SPLIT_V[0].vy;
    az                    = C8001F828_SPLIT_V[0].vz;
    bx                    = C8001F828_SPLIT_V[1].vx;
    by                    = C8001F828_SPLIT_V[1].vy;
    bz                    = C8001F828_SPLIT_V[1].vz;
    cx                    = C8001F828_SPLIT_V[2].vx;
    cy                    = C8001F828_SPLIT_V[2].vy;
    cz                    = C8001F828_SPLIT_V[2].vz;
    dx                    = C8001F828_SPLIT_V[3].vx;
    dy                    = C8001F828_SPLIT_V[3].vy;
    dz                    = C8001F828_SPLIT_V[3].vz;
    vec[0].vx             = (ax + bx) >> 1;
    vec[0].vy             = (ay + by) >> 1;
    vec[0].vz             = (az + bz) >> 1;
    vec[1].vx = mx = (ax + cx) >> 1;
    vec[1].vy = my = (ay + cy) >> 1;
    vec[1].vz = mz = (az + cz) >> 1;
    vec[2].vx = nx = (dx + bx) >> 1;
    vec[2].vy = ny = (dy + by) >> 1;
    vec[2].vz = nz = (dz + bz) >> 1;
    GTE_LDV3C(vec);
    GTE_NOP2();
    GTE_RTPT();
    vec[0].vx = (mx + nx) >> 1;
    vec[0].vy = (my + ny) >> 1;
    vec[0].vz = (mz + nz) >> 1;
    vec[1].vx = (dx + cx) >> 1;
    vec[1].vy = (dy + cy) >> 1;
    vec[1].vz = (dz + cz) >> 1;
    GTE_STSXY3(&scr->xy_60[4], &scr->xy_60[5], &scr->xy_60[7]);
    GTE_LDV3C(vec);
    GTE_NOP2();
    GTE_RTPT();
    C8001F828_SPLIT_UV[8]  = (C8001F828_SPLIT_UV[0] + C8001F828_SPLIT_UV[2]) >> 1;
    C8001F828_SPLIT_UV[9]  = (C8001F828_SPLIT_UV[1] + C8001F828_SPLIT_UV[3]) >> 1;
    C8001F828_SPLIT_UV[10] = (C8001F828_SPLIT_UV[0] + C8001F828_SPLIT_UV[4]) >> 1;
    C8001F828_SPLIT_UV[11] = (C8001F828_SPLIT_UV[1] + C8001F828_SPLIT_UV[5]) >> 1;
    C8001F828_SPLIT_UV[14] = (C8001F828_SPLIT_UV[2] + C8001F828_SPLIT_UV[6]) >> 1;
    C8001F828_SPLIT_UV[15] = (C8001F828_SPLIT_UV[3] + C8001F828_SPLIT_UV[7]) >> 1;
    C8001F828_SPLIT_UV[16] = (C8001F828_SPLIT_UV[4] + C8001F828_SPLIT_UV[6]) >> 1;
    C8001F828_SPLIT_UV[17] = (C8001F828_SPLIT_UV[5] + C8001F828_SPLIT_UV[7]) >> 1;
    C8001F828_SPLIT_UV[12] = (C8001F828_SPLIT_UV[8] + C8001F828_SPLIT_UV[16]) >> 1;
    C8001F828_SPLIT_UV[13] = (C8001F828_SPLIT_UV[11] + C8001F828_SPLIT_UV[15]) >> 1;
    GTE_STSXY0(&scr->xy_60[6]);
    GTE_STSXY1(&scr->xy_60[8]);
    clut = *(uint32 *)0x1F800158 | *(uint32 *)0x1F800148;
    idx  = (uint8 *)0x1F800120;
    for (i = 0; i < 16; i += 4)
    {
        i0 = idx[i];
        i1 = idx[i + 1];
        i2 = idx[i + 2];
        i3 = idx[i + 3];
        *(uint32 *)0x1F800070 += 40;
        last    = *(uint32 **)0x1F800070 - 10;
        last[0] = (*(uint32 *)0x1F800070 & 0xFFFFFF) | 0x09000000;
        last[2] = scr->xy_60[i0];
        last[4] = scr->xy_60[i1];
        last[6] = scr->xy_60[i2];
        last[8] = scr->xy_60[i3];
        last[1] = scr->tpage_54;
        last[3] = scr->uv_88[i0] | clut;
        last[5] = scr->uv_88[i1] | scr->tpage_5c;
        last[7] = scr->uv_88[i2];
        last[9] = scr->uv_88[i3];
    }
    p = last;
    i = 16;
    do
    {
        i1 = idx[i];
        i2 = idx[i + 1];
        i3 = idx[i + 2];
        i += 3;
        C8001F828_GTE_NCLIP_NOP(scr->xy_60[i1], scr->xy_60[i2], scr->xy_60[i3]);
        C8001F828_GTE_STMAC0(&clip);
        if (clip > 0)
        {
            *(uint32 *)0x1F800070 += 32;
            p    = *(uint32 **)0x1F800070 - 8;
            p[0] = (*(uint32 *)0x1F800070 & 0xFFFFFF) | 0x07000000;
            p[2] = scr->xy_60[i1];
            p[4] = scr->xy_60[i2];
            p[6] = scr->xy_60[i3];
            p[1] = scr->tpage_50;
            p[3] = scr->uv_88[i1] | clut;
            p[5] = scr->uv_88[i2] | scr->tpage_5c;
            p[7] = scr->uv_88[i3];
        }
    } while (i < 28);
    addPrims(scr->link_3c, last - 30, p);
    return last;
}

void func_800267AC(void *p, sint32 mode)
{
    uint32 *flags;
    uint32 *rec;
    uint32 *row_end;
    uint32 *fp;
    uint32 bits;
    uint32 *ofs;
    uint32 *data;
    uint32 *q;
    sint32 out[3];
    sint32 z;
    C8001F828_SCRVEC *sc;

    sc    = C8001F828_SCRV;
    flags = p;
    rec   = *(uint32 **)0x1F80004C;
    fp    = rec + 0x1800;
    *flags &= 0x7FFFFFFF;
    do
    {
        bits = *flags;
        if (bits != 0)
        {
            *flags  = 0;
            row_end = rec + 0x60;
            q       = rec + 1;
            do
            {
                if ((sint32)bits < 0)
                {
                    data     = (uint32 *)(q[1] & 0xFFFFFF);
                    sc->vxy  = rec[0];
                    sc->vz.w = q[0];
                    GTE_LDV0(&sc->vxy);
                    GTE_NOP2();
                    GTE_RTV0();
                    GTE_STLVNL(out);
                    z      = out[2] >> C8001F828_SHIFT;
                    out[2] = z;
                    if (z >= 0x1C21)
                    {
                        ofs = data + 8;
                    }
                    else if (z >= 0xAF1)
                    {
                        ofs = data + 7;
                    }
                    else
                    {
                        ofs = data + 6;
                    }
                    if (sc->vz.h.flag == 0)
                    {
                        ofs += 3;
                    }
                    // The entry word replaces its pointer in one variable, as retail reuses the register
                    ofs = (uint32 *)*ofs;
                    D_80089890[mode][(uint32)ofs >> 31]((uint32)ofs & 0xFFFFFF, out[2]);
                }
                bits <<= 1;
                rec += 3;
                q += 3;
            } while (rec < row_end);
        }
        else
        {
            rec += 0x60;
        }
        flags++;
    } while (rec < fp);
}

void func_8002694C(uint8 *list, sint32 limit)
{
    C8001F828_SCR100 *sc;
    uint32 count;

    sc          = (C8001F828_SCR100 *)0x1F800100;
    count       = list[0];
    sc->copy[0] = ((C8001F828_LIST *)list)->param[0];
    sc->copy[1] = ((C8001F828_LIST *)list)->param[1];
    sc->copy[2] = ((C8001F828_LIST *)list)->param[2];
    list += count * 4 + 4;
    if (C8001F828_SCR_28 < (sint16)sc->w40)
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80026B04(list);
            func_80026B04(list + 0x18);
        }
        else
        {
            func_80026B04(list + 0x10);
            func_80026B04(list + 0x18);
        }
    }
    else
    {
        if (C8001F828_SCR_2C < (sint16)sc->w44)
        {
            func_80026B04(list);
            func_80026B04(list + 8);
        }
        else
        {
            func_80026B04(list + 8);
            func_80026B04(list + 0x10);
        }
    }
    func_80026B04(list + 0x20);
    if (!(C8001F828_SCR_1BC < limit))
    {
        func_80026B04(list + 0x28);
    }
}

// The header word and the loop counter share a variable (retail keeps both in s1).
void func_80026A78(uint32 *list)
{
    uint32 i;
    uint32 *p;
    uint32 n;
    C8001F828_SCR100 *sc;

    sc          = (C8001F828_SCR100 *)0x1F800100;
    i           = list[0];
    n           = (i & 0x3F00) >> 7;
    sc->copy[0] = list[1];
    sc->copy[1] = list[2];
    sc->copy[2] = list[3];
    p           = &list[(i & 0xFF) + 1];
    i           = 0;
    do
    {
        func_80026B04(&p[i]);
        i += 2;
    } while (i < n);
}

// Byte-identical twin of func_80023EA8.
void func_80026B04(void *list)
{
    C8001F828_QUAD_WORK *scr;
    C8001F828_SVEC unused;
    uint32 *hdr;
    uint32 *face;
    uint32 *tex;
    uint32 *tail;
    uint32 *pk;
    uint32 *slot;
    uint32 flags;
    sint32 fog_sh;
    uint32 w0;
    uint32 w1;
    sint32 left;
    sint32 shift;
    sint32 sh;
    sint32 ox;
    sint32 oy;
    sint32 oz;
    sint32 opz;
    sint32 sz0;
    sint32 sz1; // also holds each packed face word in turn
    sint32 sz2;
    sint32 sz3;
    sint32 zmin;
    sint32 zmax;
    sint32 lo;
    sint32 hi;
    sint32 dx;
    sint32 dy;
    uint16 x0;
    uint16 x1;
    uint16 x2;
    uint16 x3;

    scr                   = C8001F828_QUAD_PTR;
    hdr                   = list;
    w1                    = hdr[1];
    w0                    = hdr[0];
    left                  = w1 >> 24;
    face                  = (uint32 *)((w1 & 0xFFFFFF) + 4);
    tex                   = (uint32 *)(w0 & 0xFFFFFF);
    shift                 = C8001F828_SHIFT;
    w1                    = C8001F828_SCR_C8((w0 >> 24) & 0xF);
    *(uint32 *)0x1F8001FC = left;
    *(uint32 *)0x1F800158 = w1 & 0xFFFF0000;
    *(uint32 *)0x1F80015C = w1 << 16;
    sh                    = (w0 >> 28) + shift;
    fog_sh                = shift + 9;
    ox                    = C8001F828_S16(0x1F800140) << shift;
    oy                    = C8001F828_S16(0x1F800142) << shift;
    oz                    = C8001F828_S16(0x1F800144) << shift;
    w0                    = 0x09000000;
    w1                    = 0xFFFFFF;
    tail                  = (uint32 *)1;
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (C8001F828_BIT(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1             = face[0];
        scr->v_98[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->v_98[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->v_98[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->v_98[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1             = face[1];
        scr->v_98[1].vy = oy - ((uint8)sz1 << sh);
        scr->v_98[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->v_98[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->v_98[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1             = face[2];
        scr->v_98[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        C8001F828_GTE_LDV3C(scr->v_98);
        GTE_NOP2();
        GTE_RTPT();
        scr->v_98[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->v_98[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->v_98[3].vz = ((sz1 >> 24) << sh) + oz;
        C8001F828_GTE_NCLIP();
        *(uint32 *)0x1F80014C = flags;
        C8001F828_GTE_STMAC0(&opz);
        if (opz <= 0)
        {
            if (!C8001F828_BIT(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = *(uint32 **)0x1F800070;
        C8001F828_GTE_STSXY3_FT(pk);
        C8001F828_GTE_STSXY3C(scr->xy_60.w);
        GTE_LDV0(&scr->v_98[3]);
        C8001F828_GTE_RTPS();
        scr->rgbc_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        GTE_STSXY2(&pk[8]);
        GTE_STSXY2(&scr->xy_60.w[3]);
        C8001F828_GTE_STSZ4(&sz0, &sz1, &sz2, &sz3);
        // On screen when a corner or the midpoint of a diagonal is
        if ((x0 = C8001F828_U16(0x1F800160)) < 0x140U && C8001F828_U16(0x1F800162) < 0xF0U)
        {
            goto visible;
        }
        if ((x1 = C8001F828_U16(0x1F800164)) < 0x140U && C8001F828_U16(0x1F800166) < 0xF0U)
        {
            goto visible;
        }
        if ((x2 = C8001F828_U16(0x1F800168)) < 0x140U && C8001F828_U16(0x1F80016A) < 0xF0U)
        {
            goto visible;
        }
        if ((x3 = C8001F828_U16(0x1F80016C)) < 0x140U && C8001F828_U16(0x1F80016E) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x0 + (sint16)x3) >> 1) < 0x140U &&
            (uint32)((C8001F828_S16(0x1F800162) + C8001F828_S16(0x1F80016E)) >> 1) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x1 + (sint16)x2) >> 1) >= 0x140U ||
            (uint32)((C8001F828_S16(0x1F800166) + C8001F828_S16(0x1F80016A)) >> 1) >= 0xF0U)
        {
            goto cull;
        }
    visible:
        if (sz0 < sz1)
        {
            lo = sz0;
            hi = sz1;
        }
        else
        {
            lo = sz1;
            hi = sz0;
        }
        if (sz2 < sz3)
        {
            zmin = sz2;
            zmax = sz3;
        }
        else
        {
            zmin = sz3;
            zmax = sz2;
        }
        if (lo < zmin)
        {
            zmin = lo;
        }
        if (zmax < hi)
        {
            zmax = hi;
        }
        if ((sint32)flags < 0)
        {
            if (!C8001F828_BIT(flags, 27))
            {
                sz0 = zmax;
            }
        }
        else
        {
            if (zmax < 0xC1)
            {
                goto cull;
            }
            if (C8001F828_BIT(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!C8001F828_BIT(flags, 28))
        {
            GTE_LWC2(6, &scr->rgbc_54);
            C8001F828_GTE_DPCS();
            scr->fog_48 = *(uint8 *)(0x1F800100 + ((sz0 >> fog_sh) & 0x1F)) << 16;
            GTE_SWC2(22, &scr->rgbc_54);
        }
        if ((sint32)flags < 0 && C8001F828_BIT(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (C8001F828_BIT(flags, 29) && zmin >= 0x181)
        {
            goto plain;
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            dx = ((sint16)scr->xy_60.h[0].x + (sint16)scr->xy_60.h[3].x -
                  (sint16)scr->xy_60.h[1].x - (sint16)scr->xy_60.h[2].x) >>
                 1;
            dy = ((sint16)scr->xy_60.h[0].y + (sint16)scr->xy_60.h[3].y -
                  (sint16)scr->xy_60.h[1].y - (sint16)scr->xy_60.h[2].y) >>
                 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        {
            if (C8001F828_BIT(flags, 28))
            {
                scr->link_3c = tail;
            }
            else
            {
                scr->link_3c = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            }
            scr->uv_88[0] = sz2;
            scr->uv_88[1] = sz3;
            pk            = func_8002466C();
            if (!C8001F828_BIT(flags, 28))
            {
                tail = pk;
            }
            goto next;
        }
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5c;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (C8001F828_BIT(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((uint32)pk & w1) | w0;
        }
        else
        {
            slot  = (uint32 *)(*(uint32 *)0x1F80003C + (sz0 >> 3) * 4);
            pk[0] = w0 | *slot;
            *slot = (uint32)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!C8001F828_BIT(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc_54;
        *(uint32 *)0x1F800070 += 0x28;
        goto next;
    cull:
        if (!C8001F828_BIT(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

void func_800272C8(void)
{
}

// Ring of textured quads (rsin profile). u/v are full words: retail range-checks the
// unclipped value before the byte store. The packet pointer is read with a post-increment
// (retail's copy to a1); the corners are computed in x0..x3 order; the rsin result feeds the
// out_cur expression directly. The 0x100 limit is a variable set in each tpage arm (retail loads
// it into a0 in both arms and compares with sltu).
void func_800272D0(sint32 cx, sint32 cy, sint32 r0, sint32 r1)
{
    sint32 dr;
    sint32 c;
    sint32 s;
    sint32 c0;
    sint32 s0;
    sint32 step;
    sint32 fp;
    sint32 ang;
    sint32 in_prev;
    sint32 in_cur;
    sint32 out_prev;
    sint32 out_cur;
    uint32 i;
    sint32 bias;
    sint32 page;
    uint32 u;
    uint32 v;
    uint32 lim;
    POLY_FT4 *p;

    c       = 0x1000;
    s       = 0;
    step    = 0;
    out_cur = 0;
    in_cur  = 0;
    dr      = r1 - r0;
    fp      = 0;
    do
    {
        out_prev = out_cur;
        ang      = fp + step;
        out_cur  = ((rsin(ang) * dr) >> 12) + r0;
        in_prev  = in_cur;
        in_cur   = ((ang * dr) >> 10) + r0;
        for (i = 0; i < 16; i++)
        {
            c0                 = c;
            s0                 = s;
            p                  = (*(POLY_FT4 **)0x1F800070)++;
            *(uint32 *)&p->tag = 0x09000000;
            *(uint32 *)&p->r0  = 0x2C808080;
            c                  = D_800BAEB8[i * 4];
            s                  = D_800BBD00[i * 4];
            p->x0              = ((c0 * out_prev) >> 12) + cx;
            p->y0              = ((s0 * out_prev) >> 12) + cy;
            p->x1              = ((c * out_prev) >> 12) + cx;
            p->y1              = ((s * out_prev) >> 12) + cy;
            p->x2              = ((c0 * out_cur) >> 12) + cx;
            p->y2              = ((s0 * out_cur) >> 12) + cy;
            p->x3              = ((c * out_cur) >> 12) + cx;
            p->y3              = ((s * out_cur) >> 12) + cy;
            if (p->x0 < 0xA0)
            {
                bias     = 0;
                p->tpage = (*(uint8 *)0x1F800000 << 4) | 0x100;
                lim      = 0x100;
            }
            else
            {
                bias     = 0x40;
                p->tpage = (*(uint8 *)0x1F800000 << 4) | 0x101;
                lim      = 0x100;
            }
            u = (((c0 * in_prev) >> 12) + cx) - bias;
            if (u < lim)
            {
                p->u0 = u;
                v     = ((s0 * in_prev) >> 12) + cy;
                if (v < lim)
                {
                    p->v0 = v;
                    u     = (((c * in_prev) >> 12) + cx) - bias;
                    if (u < lim)
                    {
                        p->u1 = u;
                        v     = ((s * in_prev) >> 12) + cy;
                        if (v < lim)
                        {
                            p->v1 = v;
                            u     = (((c0 * in_cur) >> 12) + cx) - bias;
                            if (u < lim)
                            {
                                p->u2 = u;
                                v     = ((s0 * in_cur) >> 12) + cy;
                                if (v < lim)
                                {
                                    p->v2 = v;
                                    u     = (((c * in_cur) >> 12) + cx) - bias;
                                    if (u < lim)
                                    {
                                        p->u3 = u;
                                        v     = ((s * in_cur) >> 12) + cy;
                                        if (v < lim)
                                        {
                                            p->v3 = v;
                                            addPrim(&D_80098934->layer[2], p);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        step += 0x10;
        fp += step;
    } while (fp < 0x400);
}
