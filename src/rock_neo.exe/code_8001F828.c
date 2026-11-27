#include "common.h"
#include "code_8001786C.h"
#include "code_8001F828.h"
#include "code_8002E7A8.h"
#include "code_80037FB4.h"
#include "display.h"
#include "fastmem.h"
#include "game.h"
#include "moji.h"
#include "pad.h"
#include "player.h"
#include "psyq/inline_c.h"
#include "scene.h"
#include "scratch.h"
#include "psyq/libetc.h"
#include "psyq/libgte.h"
#include "sound.h"
#include "stage.h"
#include "sub_scrn.h"
#include "system.h"

// Small data (.sdata 0x80097C3C-0x80097C44): reached through $gp in this file.
sint32 D_80097C3C = 0;
sint8 D_80097C40  = 0;
uint8 D_80097C41  = 0;
sint16 D_80097C42 = 0;

// Small uninitialized statics (.sbss 0x800981BC-0x80098354).
static sint16 D_800981BC[2];
static sint16 D_800981C0[4];
static sint32 D_800981C8[2];
static sint16 D_800981D0[4];
static sint32 D_800981D8[2];
static sint16 D_800981E0[4];
static sint32 D_800981E8;
static sint16 D_800981EC[4];
static sint32 D_800981F4[2];
static sint32 D_800981FC[2];
static sint32 D_80098204;
static sint16 D_80098208[2];
static sint16 D_8009820C[2];
static sint16 D_80098210[4];
static sint32 D_80098218[2];
static sint32 D_80098220[2];
static sint32 D_80098228[2];
static sint32 D_80098230;
static sint16 D_80098234[2];
static sint16 D_80098238[4];
static sint16 D_80098240[4];
static sint32 D_80098248;
static sint16 D_8009824C[4];
static sint32 D_80098254;
static sint16 D_80098258[4];
static sint32 D_80098260[2];
static sint32 D_80098268[2];
static sint16 D_80098270[4];
static sint32 D_80098278;
static sint16 D_8009827C[4];
static sint32 D_80098284[2];
static sint16 D_8009828C[2];
static sint32 D_80098290[2];
static sint32 D_80098298;
static sint32 D_8009829C[2];
static sint32 D_800982A4[2];
static sint32 D_800982AC[2];
static sint32 D_800982B4[2];
static sint32 D_800982BC[2];
static sint32 D_800982C4;
static sint32 D_800982C8[2];
static sint32 D_800982D0[2];
static sint32 D_800982D8[2];
static sint32 D_800982E0;
static sint32 D_800982E4[2];
static sint32 D_800982EC[2];
static sint32 D_800982F4;
static sint16 D_800982F8[2];
static sint16 D_800982FC[4];
static sint32 D_80098304[2];
static sint32 D_8009830C[2];
static sint32 D_80098314[2];
static sint32 D_8009831C[2];
static sint32 D_80098324[2];
static sint32 D_8009832C[2];
static sint32 D_80098334[2];
static sint32 D_8009833C;
static sint8 D_80098340[4];
static sint8 D_80098344[4];
static sint8 D_80098348[4];
static sint8 D_8009834C[8];

// Pool variables (stay in assembly), reached through $gp here: cleared each frame by
// Map_draw.
sint32 D_80098A08;
sint32 D_800989AC;

// Called only from this file
void map_blocks_draw(uint32 *rows, sint32 kind);
void map_blocks_draw2(uint32 *rows, sint32 kind);
void tile_model_draw(uint8 *data, SVECTOR *pos, uint32 id);
sint32 num_format(uint32 flags, sint32 val, char *out, sint32 width);
void room_model_pos_wrap(ROOM_MODEL *m);
u_long *tile_quad_split(void);
u_long *quad_split(void);
void map_tile_draw(sint32 x, sint32 y, uint16 id);
void map_cell_draw(sint32 x, sint32 y, sint32 id, SVECTOR *pos);
void map_tile_queue_draw(void);
void map_view_cols_draw(sint32 x0, sint32 x1, sint32 y0, sint32 y1);
void map_view_rows_draw(sint32 x0, sint32 x1, sint32 y0, sint32 y1);
void tile_model_draw_split(uint8 *data, SVECTOR *pos, uint32 id);
void func_80023EA8(u_long *model);
void func_80024E94(u_long *model, sint32 z);
void func_80024F30(u_long *model);
void func_80025900(u_long *model);
void func_80026B04(u_long *model);
void map_block_masks_draw(void);
void func_800272D0(sint32 cx, sint32 cy, sint32 r0, sint32 r1);

void func_8001F828(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            if (Sce_flag_test(0xC))
            {
                D_800981BC[0] = 0x32;
            }
            else
            {
                D_800981BC[0] = 0x31;
            }
            return;
        case 1:
            D_800981BC[0] = 0x32;
            id            = 0x36;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            D_800981BC[0] = 0x32;
            id            = 0x34;
            break;
        default:
            D_800981BC[0] = 0x32;
            id            = 0x35;
            break;
    }
    D_800981BC[1] = D_800981C0[0] = D_800981C0[1] = id;
}

void func_8001F8DC(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            if (Sce_flag_test(6) && !Sce_flag_test(0x59))
            {
                D_800981D0[0] = 0x3D;
            }
            else
            {
                D_800981D0[0] = 0x3C;
            }
            return;
        case 1:
            D_800981D0[0] = 0x3C;
            id            = 0x3F;
            break;
        case 2:
        case 3:
            D_800981D0[0] = 0x3C;
            id            = 0x40;
            break;
        case 4:
        case 5:
            D_800981D0[0] = 0x3C;
            id            = 0x41;
            break;
        case 11:
            D_800981D0[0] = 0x3C;
            id            = 0x43;
            break;
        default:
            D_800981D0[0] = 0x3C;
            id            = 0x42;
            break;
    }
    D_800981D0[1] = id;
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
        switch (Game_work.sce_no)
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
    D_800981E0[1] = id;
}

void func_8001FA94(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            D_800981EC[1] = 0x59;
            if (Sce_flag_test(0x630))
            {
                D_800981EC[3] = 0x61;
            }
            else
            {
                D_800981EC[3] = 0x5F;
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
    D_800981EC[1] = id;
}

void func_8001FB24(void)
{
    if (Game_work.sce_no == 6)
    {
        D_80098208[0] = D_80098208[1] = D_8009820C[0] = D_8009820C[1] = 0x67;
    }
    else
    {
        D_80098208[0] = D_80098208[1] = D_8009820C[0] = D_8009820C[1] = 0x66;
    }
}

void func_8001FB54(void)
{
    sint16 id;

    switch (Game_work.sce_no)
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
    D_80098210[1] = id;
}

void func_8001FB8C(void)
{
    sint16 id;

    switch (Game_work.sce_no)
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
    D_80098234[1] = id;
}

void func_8001FBC4(void)
{
    sint16 id;

    if (Game_work.sce_no == 5)
    {
        if (Sce_flag_test(0x1C))
        {
            D_80098238[1] = 0x7A;
            D_80098238[3] = 0x7C;
            D_80098240[0] = -1;
            return;
        }
        if (Sce_flag_test(0x1B))
        {
            D_80098238[1] = D_80098238[3] = D_80098240[0] = -1;
            return;
        }
        id = 0x7A;
    }
    else
    {
        id = 0x7B;
    }
    D_80098238[3] = D_80098240[0] = id;
}

void func_8001FC50(void)
{
    sint16 id;

    switch (Game_work.sce_no)
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
    D_8009824C[0] = id;
}

void func_8001FCA4(void)
{
    sint16 id;

    switch (Game_work.sce_no)
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
    D_80098258[1] = id;
}

void func_8001FCE4(void)
{
    sint16 id;

    switch (Game_work.sce_no)
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
    D_80098270[3] = id;
}

void func_8001FD3C(void)
{
    switch (Game_work.sce_no)
    {
        case 1:
            D_8009827C[0] = 0x93;
            break;
        default:
            D_8009827C[0] = 0x94;
            break;
    }
    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
            D_8009827C[1] = 0x95;
            break;
        case 2:
        case 3:
        case 4:
            D_8009827C[1] = 0x96;
            break;
        default:
            D_8009827C[1] = 0x97;
            break;
    }
}

void func_8001FD90(void)
{
    switch (Game_work.sce_no)
    {
        case 1:
            D_8009828C[0] = 0x9D;
            break;
        default:
            D_8009828C[0] = 0x9E;
            break;
    }
    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
            D_8009828C[1] = 0x9F;
            break;
        case 2:
        case 3:
        case 4:
            D_8009828C[1] = 0xA0;
            break;
        default:
            D_8009828C[1] = 0xA1;
            break;
    }
}

void func_8001FDE4(void)
{
    sint16 id;

    switch (Game_work.sce_no)
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
    D_800982F8[1] = D_800982FC[0] = D_800982FC[1] = id;
}

// Capcom's Print (disc/tcrf.txt): printf into the debug text queue (Debug_text_buf), at pos (XYC,
// TEXT_POS): %-flags (- + space 0),
// a width (digits or *), l, and X x d i u o b c s; "$$" is a '$', "$A" to "$\" the font's extra
// characters. Skipped while Debug_text_draw is off, or when D_800987D4 is set and differs from
// D_800987DC.
// fmt is const: its reads may then move above the stores to fmt's stack slot, as in the target.
// Each number reads its argument as (mode & FMT_LONG) ? long : int, both arms the same here: the
// test is folded away later, but it makes the loop optimizer keep FMT_LONG in a register, as the
// target does.
void Print(uint32 pos, const char *fmt, ...)
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
    if (D_800987D4 != 0 && D_800987D4 != D_800987DC)
    {
        return;
    }
    if (Debug_text_ptr >= &Debug_text_buf[DEBUG_TEXT_BUF_SIZE])
    {
        return;
    }
    *Debug_text_ptr++ = (pos & 0x100) >> 8;
    *Debug_text_ptr++ = pos;
    *Debug_text_ptr++ = pos >> 9;
    *Debug_text_ptr++ = (pos >> 17) & 7;
    mode              = 0;
    ap                = (sint32 *)(&fmt + 1);
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
                    mode |= FMT_LEFT;
                    break;
                case '+':
                    mode |= FMT_CHAR('+');
                    break;
                case ' ':
                    mode |= FMT_CHAR(' ');
                    break;
                case '0':
                    mode |= FMT_ZERO_PAD;
                    break;
                case '%':
                    *Debug_text_ptr++ = '%';
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
                mode &= ~FMT_LEFT;
            }
            if (*fmt++ == 'l')
            {
                mode |= FMT_LONG;
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
                    mode &= ~(FMT_SIGNED | FMT_CHAR_MASK);
                    val = (mode & FMT_LONG) ? (ap += 1)[-1] : (ap += 1)[-1];
                    Debug_text_ptr += num_format(mode | FMT_BASE(16), val, Debug_text_ptr, width);
                    break;
                case 'd':
                case 'i':
                    mode |= FMT_SIGNED;
                    val = (mode & FMT_LONG) ? (ap += 1)[-1] : (ap += 1)[-1];
                    if (val < 0)
                    {
                        mode &= ~FMT_CHAR_MASK;
                        mode |= FMT_CHAR('-');
                    }
                    Debug_text_ptr += num_format(mode | FMT_BASE(10), val, Debug_text_ptr, width);
                    break;
                case 'u':
                    val = (mode & FMT_LONG) ? (ap += 1)[-1] : (ap += 1)[-1];
                    Debug_text_ptr += num_format(mode | FMT_BASE(10), val, Debug_text_ptr, width);
                    break;
                case 'o':
                    mode &= ~(FMT_SIGNED | FMT_CHAR_MASK);
                    val = (mode & FMT_LONG) ? (ap += 1)[-1] : (ap += 1)[-1];
                    Debug_text_ptr += num_format(mode | FMT_BASE(8), val, Debug_text_ptr, width);
                    break;
                case 'b':
                    mode &= ~(FMT_SIGNED | FMT_CHAR_MASK);
                    val = (mode & FMT_LONG) ? (ap += 1)[-1] : (ap += 1)[-1];
                    Debug_text_ptr += num_format(mode | FMT_BASE(2), val, Debug_text_ptr, width);
                    break;
                case 'c':
                    *Debug_text_ptr++ = *(char *)((ap += 1) - 1); // the argument's low byte
                    break;
                case 's':
                    s = (char *)(ap += 1)[-1];
                    while ((*Debug_text_ptr++ = *s++) != '\0')
                    {
                        if (width-- == 0)
                        {
                            break;
                        }
                    }
                    Debug_text_ptr--;
                    while (width-- > 0)
                    {
                        *Debug_text_ptr++ = ' ';
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
            // The '$' escape and the plain character share the one fmt++ below.
            if (c == '$')
            {
                val = fmt[1];
                if (val == '$')
                {
                    fmt++;
                    *Debug_text_ptr++ = '$';
                }
                else if ((uint32)(val - 'A') < 0x1C)
                {
                    fmt++;
                    *Debug_text_ptr++ = val + 0x3E; // 'A'..'\' to the font's codes 0x7F..0x9A
                }
            }
            else
            {
                *Debug_text_ptr++ = c;
            }
            fmt++;
        }
    }
    *Debug_text_ptr++ = 0;
}

void func_8002037C(void)
{
    Debug_text_buf[0] = 0;
    Debug_text_ptr    = Debug_text_buf;
    D_800987D4        = 0;
    D_800987DC        = 0;
}

// Draws the debug text queue (Debug_text_buf) in the 8x8 font, unless Moji_flag bit 0x400000 or
// D_80098824 is set (MojiTaskExec's test); controller 2's SELECT + up/down steps D_800987DC (0-30).
void Debug_text_draw(void)
{
    uint8 *p;
    SPRT_8 *sp;
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
    if (PAD_NOW(Joy2) & PAD_SELECT)
    {
        if (PAD_ON(Joy2) & PAD_UP)
        {
            D_80097C40 = 0;
            D_800987DC++;
        }
        else if (PAD_NOW(Joy2) & PAD_UP)
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
        else if (PAD_ON(Joy2) & PAD_DOWN)
        {
            D_80097C40 = 0;
            D_800987DC--;
        }
        else if (PAD_NOW(Joy2) & PAD_DOWN)
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
        if (D_800987DC >= 0x1F)
        {
            D_800987DC = 0;
        }
        if (D_800987DC < 0)
        {
            D_800987DC = 0x1E;
        }
    }
    if (Debug_text_ptr == Debug_text_buf)
    {
        return;
    }
    if (++D_80098348[0] == 10)
    {
        D_80098348[0] = 0;
        if (++D_8009834C[0] == 5)
        {
            D_8009834C[0] = 0;
        }
    }
    p = Debug_text_buf;
    while (p < Debug_text_ptr)
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
                    D_80098340[0] = 0;
                    p++;
                    goto next;
                case 7:
                    D_80098340[0] ^= 1;
                    D_80098344[0] = D_8009834C[0];
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
                case ' ':
                    x += 8;
                    break;
                default:
                    if (D_80098340[0] == 0)
                    {
                        c = col;
                    }
                    else
                    {
                        c = D_80089888[D_80098344[0]];
                        if (++D_80098344[0] == 5)
                        {
                            D_80098344[0] = 0;
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
                    sp           = (SPRT_8 *)Map_prim_ptr;
                    Map_prim_ptr = (POLY_FT4 *)(sp + 1);
                    setSprt8(sp);
                    setRGB0(sp, 0x80, 0x80, 0x80);
                    sp->x0   = x;
                    sp->y0   = y;
                    sp->u0   = ((*p & 1) << 3) - 0x10;
                    sp->v0   = (*p & 0xFE) << 2;
                    sp->clut = D_80097C44[c];
                    x += 8;
                    addPrim(&Disp_env_ptr->ot[0], sp);
                    break;
            }
            p++;
        }
    next:;
    }
    dm           = (DR_MODE *)Map_prim_ptr;
    Map_prim_ptr = (POLY_FT4 *)(dm + 1);
    SetDrawMode(dm, 0, 0, 0x1F, NULL);
    addPrim(&Disp_env_ptr->ot[0], dm);
    Debug_text_ptr = Debug_text_buf;
}

// Formats val into out (no terminator) by flags (FMT_*), padded to width; returns the length
// written. buf[32] gives the target's frame; orig is reused as the pad count of the other two paths.
sint32 num_format(uint32 flags, sint32 val, char *out, sint32 width)
{
    char buf[32];
    sint16 n;
    sint16 orig;
    uint32 base;
    uint32 prefix;

    if ((flags & FMT_SIGNED) && val < 0)
    {
        val = ~val + 1;
    }
    n    = 0;
    base = (flags & FMT_BASE_MASK) + 1;
    do
    {
        buf[n++] = Num_digit_tbl[(uint32)val % base];
        val      = (uint32)val / base;
    } while (val != 0);
    prefix = flags & FMT_CHAR_MASK;
    if (prefix != 0)
    {
        buf[n++] = prefix >> 4;
        flags |= FMT_HAS_CHAR;
    }
    if (width - n > 0)
    {
        if (flags & FMT_LEFT)
        {
            orig = n;
            while (n > 0)
            {
                n--;
                *out++ = buf[n];
            }
            while (n++ < width - orig)
            {
                *out++ = ' ';
            }
            return width;
        }
        orig = width - n;
        if (flags & FMT_ZERO_PAD)
        {
            if (flags & FMT_HAS_CHAR)
            {
                n--;
                *out++ = buf[n];
            }
            while (orig-- > 0)
            {
                *out++ = '0';
            }
        }
        else
        {
            while (orig-- > 0)
            {
                *out++ = ' ';
            }
        }
        while (n > 0)
        {
            n--;
            *out++ = buf[n];
        }
        return width;
    }
    width = 0;
    while (n > 0)
    {
        n--;
        width++;
        *out++ = buf[n];
    }
    return width;
}

void func_80020A40(void)
{
    D_80097C3C = 0;
}

// Passes every nonempty cell of the map window to map_cell_draw, then drops from the near block
// mask the blocks the far mask has, and draws the tiles map_tile_draw queued.
void map_window_draw(void)
{
    SVECTOR pos;
    sint32 x;
    sint32 y;
    sint32 y0;
    sint32 x0;
    sint32 x1;
    sint32 y1;
    sint32 id;

    D_8009886C = 0;
    gte_SetTransVector(&Scratch_trans);
    y0      = Map_org_y;
    y1      = Map_end_y;
    x0      = Map_org_x;
    x1      = Map_end_x;
    pos.pad = 0x320;
    for (y = y0; y < y1; y++)
    {
        pos.vz = (y << 9) - 0x7F00;
        for (x = x0; x < x1; x++)
        {
            pos.vx = (x << 9) - 0x7F00;
            id     = (Map_cells + (x - Map_org_x))[(y - Map_org_y) * Map_w];
            if (id != 0)
            {
                map_cell_draw(x, y, id, &pos);
            }
        }
    }
    func_8001782C(Map_block_mask, Map_block_mask + MAP_BLOCK_ROWS);
    map_tile_queue_draw();
}

// Draws the map around the camera: sets Scratch_fog_1 by scale, clips a window of cells ahead of the
// camera (by its yaw and pitch) to the map, sets Map_view (the cells around the camera position and
// the slopes of the view's two edges), scans the window between the edges (map_view_cols_draw or
// map_view_rows_draw by the yaw's quadrant), then draws Map_view's own cells, and ends as
// map_window_draw does. The ABS terms call rcos/rsin twice each. The locals are reused across roles
// (cx: yaw sine, window centre x, the view half-size, the yaw - 0x100; cz: yaw cosine, window centre
// z; w: the window's distance and half-size, the camera's cell, then the cell id).
void map_view_draw(void)
{
    SVECTOR pos;
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
    gte_SetTransVector(&Scratch_trans);
    if ((Scratch_fog_2 & 4) && Scratch_scale_shift < 3U)
    {
        Scratch_fog_1 = D_80097C84[Scratch_scale_shift];
    }
    else
    {
        Scratch_fog_1 = D_80097C78[Scratch_scale_shift];
    }
    cx = rsin(D_800A3958.work.ang.vy);
    cz = rcos(D_800A3958.work.ang.vy);
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
    w  = ABS(rcos(D_800A3958.work.ang.vx)) * 2;
    cx = ((Scratch_cam_pos.vx + (cx * w) / 4096) / 512) + 0x40;
    cz = ((Scratch_cam_pos.vz + (cz * w) / 4096) / 512) + 0x40;
    w  = ABS(rcos(D_800A3958.work.ang.vx)) / 256;
    x0 = cx - w;
    if (x0 < Map_org_x)
    {
        x0 = Map_org_x;
    }
    x1 = cx + w;
    if (Map_end_x < x1)
    {
        x1 = Map_end_x;
    }
    y0 = cz - w;
    if (y0 < Map_org_y)
    {
        y0 = Map_org_y;
    }
    y1 = cz + w;
    if (Map_end_y < y1)
    {
        y1 = Map_end_y;
    }
    cx          = ABS(rsin(D_800A3958.work.ang.vx) / 352);
    w           = (D_800A3958.work.pos[0].vx + 0x100) / 512;
    Map_view_x0 = w - cx + 0x3D;
    if (Map_view_x0 < Map_org_x)
    {
        Map_view_x0 = Map_org_x;
    }
    Map_view_x1 = w + cx + 0x43;
    if (Map_end_x < Map_view_x1)
    {
        Map_view_x1 = Map_end_x;
    }
    w           = (D_800A3958.work.pos[0].vz + 0x100) / 512;
    Map_view_y0 = w - cx + 0x3D;
    if (Map_view_y0 < Map_org_y)
    {
        Map_view_y0 = Map_org_y;
    }
    Map_view_y1 = w + cx + 0x43;
    if (Map_end_y < Map_view_y1)
    {
        Map_view_y1 = Map_end_y;
    }
    yaw = D_800A3958.work.ang.vy;
    cx  = yaw - 0x100;
    cx &= 0xFFF;
    b = (yaw + 0x100) & 0xFFF;
    c = rsin(cx) + 1;
    d = rsin(b) + 1;
    e = rcos(cx) + 1;
    f = rcos(b) + 1;
    if (!((D_800A3958.work.ang.vy - 0x200) & 0x400))
    {
        Map_view.edge_0 = (e << 12) / -c;
        Map_view.edge_1 = (f << 12) / -d;
        map_view_cols_draw(x0, x1, y0, y1);
    }
    else
    {
        Map_view.edge_0 = (c << 12) / -e;
        Map_view.edge_1 = (d << 12) / -f;
        map_view_rows_draw(x0, x1, y0, y1);
    }
    x0      = Map_view.x0;
    x1      = Map_view.x1;
    y0      = Map_view.y0;
    y1      = Map_view.y1;
    pos.pad = 0x258;
    for (y = y0; y < y1; y++)
    {
        pos.vz = (y << 9) - 0x7F00;
        for (x = x0; x < x1; x++)
        {
            pos.vx = (x << 9) - 0x7F00;
            w      = (Map_cells + (x - Map_org_x))[(y - Map_org_y) * Map_w];
            if (w != 0)
            {
                map_cell_draw(x, y, w, &pos);
            }
        }
    }
    func_8001782C(Map_block_mask, Map_block_mask + MAP_BLOCK_ROWS);
    map_tile_queue_draw();
}

// map_view_rows_draw with the axes swapped: passes to map_cell_draw the nonempty cells of columns
// x0..x1 between the view's two edges (clipped to y0..y1), except those inside Map_view's
// rectangle. Used when the camera faces along x.
void map_view_cols_draw(sint32 x0, sint32 x1, sint32 y0, sint32 y1)
{
    SVECTOR pos;
    sint32 d0;
    sint32 d1;
    sint32 k;
    sint32 cam_z;
    sint32 x;
    sint32 y;
    sint32 ys;
    sint32 ye;
    sint32 inside;
    sint32 ofs;
    sint32 row;
    sint32 id;

    if ((D_800A3958.work.ang.vy - 0x200) & 0x800)
    {
        d0 = Map_view.edge_0;
        d1 = Map_view.edge_1;
        k  = (Scratch_cam_pos.vx + 0x100) / 512 - x0 + 0x41;
    }
    else
    {
        d0 = Map_view.edge_1;
        d1 = Map_view.edge_0;
        k  = (Scratch_cam_pos.vx + 0x100) / 512 - x0 + 0x3E;
    }
    cam_z   = (Scratch_cam_pos.vz + 0x100) / 512;
    pos.pad = 0x190;
    for (x = x0; x < x1; x++, k--)
    {
        ys = cam_z + (k * d0) / 4096 + 0x3D;
        ye = cam_z + (k * d1) / 4096 + 0x42;
        if (ys < y0)
        {
            ys = y0;
        }
        else if (y1 < ys)
        {
            ys = y1;
        }
        if (ye < y0)
        {
            ye = y0;
        }
        else if (y1 < ye)
        {
            ye = y1;
        }
        inside = 0;
        if (!(x < Map_view.x0))
        {
            inside = x < Map_view.x1;
        }
        y      = ys;
        pos.vx = (x << 9) - 0x7F00;
        ofs    = x - Map_org_x;
        row    = (y - Map_org_y) * Map_w;
        for (; y < ye; y++)
        {
            if (!inside || y < Map_view.y0 || !(y < Map_view.y1))
            {
                pos.vz = (y << 9) - 0x7F00;
                id     = (Map_cells + ofs)[row];
                if (id != 0)
                {
                    map_cell_draw(x, y, id, &pos);
                }
            }
            ofs += Map_w;
        }
    }
}

// Passes to map_cell_draw the nonempty cells of rows y0..y1 between the view's two edges (clipped
// to x0..x1), except those inside Map_view's rectangle. Used when the camera faces along y.
void map_view_rows_draw(sint32 x0, sint32 x1, sint32 y0, sint32 y1)
{
    SVECTOR pos;
    sint32 xs;
    sint32 xe;
    sint32 x;
    sint32 y;
    sint32 k;
    sint32 ofs;
    sint32 row;
    sint32 inside;
    sint32 cam_z;
    sint32 d0;
    sint32 d1;
    sint32 cam_x;
    sint32 id;

    if ((D_800A3958.work.ang.vy - 0x200) & 0x800)
    {
        d0    = Map_view.edge_0;
        cam_z = Scratch_cam_pos.vz;
        d1    = Map_view.edge_1;
        k     = (cam_z + 0x100) / 512 - y0 + 0x3E;
    }
    else
    {
        d0    = Map_view.edge_1;
        cam_z = Scratch_cam_pos.vz;
        d1    = Map_view.edge_0;
        k     = (cam_z + 0x100) / 512 - y0 + 0x41;
    }
    cam_x   = (Scratch_cam_pos.vx + 0x100) / 512;
    pos.pad = 0x190;
    for (y = y0; y < y1; y++, k--)
    {
        xs = cam_x + (k * d0) / 4096 + 0x3D;
        xe = cam_x + (k * d1) / 4096 + 0x42;
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
        inside = 0;
        if (!(y < Map_view.y0))
        {
            inside = y < Map_view.y1;
        }
        x      = xs;
        pos.vz = (y << 9) - 0x7F00;
        ofs    = x - Map_org_x;
        row    = (y - Map_org_y) * Map_w;
        for (; x < xe; x++, ofs++)
        {
            if (!inside || x < Map_view.x0 || !(x < Map_view.x1))
            {
                pos.vx = (x << 9) - 0x7F00;
                id     = (Map_cells + ofs)[row];
                if (id != 0)
                {
                    map_cell_draw(x, y, id, &pos);
                }
            }
        }
    }
}

// Map cell (x, y) holding id at pos (pad: its radius): when it is in front of the camera within
// Scratch_fog_1 and inside the view's width at its depth, draws it with map_tile_draw (id < 0, a
// tile) or sets block id's bit in Map_block_mask, the near mask (+MAP_BLOCK_ROWS) below depth
// D_1F800004.
void map_cell_draw(sint32 x, sint32 y, sint32 id, SVECTOR *pos)
{
    VECTOR out;
    sint32 r;

    if (id > 0)
    {
        pos->vy = Map_blocks[id].pos.vy;
    }
    else
    {
        pos->vy = -((uint32)(id & 0x1F00) >> 1);
    }
    gte_ldv0(pos);
    gte_rt();
    gte_stlvnl(&out);
    r = out.vz >> 2;
    if (r < Scratch_fog_1)
    {
        if (r < 0)
        {
            r = 0;
        }
        r = ((r * 106) >> 6) + pos->pad;
        if (-r <= out.vx && out.vx <= r)
        {
            if (id < 0)
            {
                map_tile_draw(x, y, id);
                return;
            }
            if (out.vz >= D_1F800004)
            {
                Map_block_mask[id >> 5] |= 0x80000000 >> (id & 0x1F);
            }
            else
            {
                Map_block_mask[MAP_BLOCK_ROWS + (id >> 5)] |= 0x80000000 >> (id & 0x1F);
            }
        }
    }
}

// Draws map tile (x, y) with the LOD its depth picks: id bits 8-12 give its height, bit 7 takes the
// model from the stage HD2 table (bits 2-6) instead of the stage STG's first record. The two far
// LODs clear id bit 15; a tile nearer than 0x401 is queued in D_800BBE50 instead.
void map_tile_draw(sint32 x, sint32 y, uint16 id)
{
    SVECTOR pos;
    VECTOR out;
    TILE_WORK *tw;
    uint32 n;
    STG_MODEL *model;
    uint8 *data;

    pos.vx = (x << 9) - 0x7F00;
    pos.vz = (y << 9) - 0x7F00;
    pos.vy = -((uint32)(id & 0x1F00) >> 1);
    gte_ldv0(&pos);
    tw = &Tile_work; // set here, between the load and the GTE command
    gte_rt_b();
    // Bit 7 tested on the uint16 copy ((sint8)id tests the incoming register instead).
    if ((id << 24) < 0)
    {
        model = Stage_hd2_tbl[(id & 0x7F) >> 2].model;
    }
    else
    {
        model = Stage_stg;
    }
    gte_stlvnl(&out);
    if (out.vz > 0x1C20)
    {
        data = (uint8 *)model->lod[2];
        id &= 0x7FFF;
    }
    else if (out.vz > 0xAF0)
    {
        data = (uint8 *)model->lod[1];
        id &= 0x7FFF;
    }
    else if (out.vz > 0x400)
    {
        data = (uint8 *)model->lod[0];
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
    tw->fog_08 = D_800C0DC0.b[(out.vz / 512) & 0x1F] << 16;
    gte_SetTransVector(Scratch_view_mtx.t);
    tile_model_draw(data + 8, &pos, id);
    gte_SetTransVector(&Scratch_trans);
}

// Draws a tile model at pos. Each face is a flag word and three words of corners packed as signed
// x/z bytes, all at pos's height; id bit 0 mirrors the model, bit 1 flips it about pos, bit 7
// takes the CLUT from the header and the u/v pairs from the face (for the quad split), bit 15 the
// texture with a per-face shade. Face flag bit 29: a triangle; bit 28: linked right after the
// previous face instead of by depth; bit 30: drawn from both sides.
void tile_model_draw(uint8 *data, SVECTOR *pos, uint32 id)
{
    TILE_WORK *scr;
    u_long *hdr;
    u_long *face;
    u_long *tex;
    u_long *tail;
    u_long *pk;
    u_long *slot;
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
    sint32 sz1; // also holds the face's packed corner words
    sint32 sz2;
    sint32 sz3;
    sint32 zmax;

    scr  = &Tile_work;
    hdr  = (u_long *)data;
    w1   = hdr[1];
    w0   = hdr[0];
    left = w1 >> 24;
    face = (u_long *)((w1 & 0xFFFFFF) + 4);
    tex  = (u_long *)(w0 & 0xFFFFFF);
    sh   = (w0 >> 28) + Scratch_scale_shift;
    if (BIT_TEST(id, 7))
    {
        Tile_work.clut_0C = hdr[-1];
    }
    else
    {
        shade                = *(u_long *)&D_800BADB0[(id * 2) & 0xF8];
        Tile_work.uv_50.w[0] = *(u_long *)&D_800BADB0[((id * 2) & 0xF8) + 4];
        Tile_work.clut_0C    = (shade & 0xFFFF0000) | 0x1D;
        shade &= 0xFF;
    }
    w1            = 0xFFFFFF;
    scr->clut_90  = scr->clut_0C & 0xFFFF0000;
    scr->tpage_94 = scr->clut_0C << 16;
    ox            = pos->vx << Scratch_scale_shift;
    oy            = pos->vy << Scratch_scale_shift;
    oz            = pos->vz << Scratch_scale_shift;
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
        gte_ldv3c(scr->v_70);
        scr->v_70[3].vy = oy;
        gte_rtpt();
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
        gte_nclip();
        flags = face[-1];
        gte_stopz(&opz);
        if (opz <= 0)
        {
            if (!BIT_TEST(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = (u_long *)Map_prim_ptr;
        gte_stsxy3_ft4(pk);
        if (BIT_TEST(flags, 29))
        {
            scr->rgbc4_14 = (flags & 0x03FFFFFF) | 0x24000000;
            gte_stsz3(&sz0, &sz1, &sz2);
            sz3 = sz2;
        }
        else
        {
            gte_ldv0(&scr->v_70[3]);
            gte_rtps();
            scr->rgbc4_14 = (flags & 0x03FFFFFF) | 0x2C000000;
            gte_stsxy(&pk[8]);
            gte_stsz4(&sz0, &sz1, &sz2, &sz3);
        }
        gte_ldrgb(&scr->rgbc4_14);
        if (BIT_TEST(flags, 28))
        {
            scr->ot_48 = tail;
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
            if ((Scratch_fog_2 & 1) && oy >= 0)
            {
                scr->ot_48 = Scratch_ot + 0x7D0;
            }
            else
            {
                scr->ot_48 = Scratch_ot + (sz0 >> 3);
            }
        }
        gte_dpcs_b();
        if ((id << 24) <= 0x7FFFFFFF)
        {
            if ((id << 16) > 0x7FFFFFFF)
            {
                sz2 = tex[0];
                sz3 = tex[1];
                if (left >= 4)
                {
                    level = Tile_work.uv_50.b[7 - left];
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
            sz2             = tex[0];
            scr->uv_50.w[0] = sz2;
            sz3             = tex[1];
            scr->uv_50.w[1] = sz3;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_90 | scr->fog_08;
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_94;
        pk[7] = sz3 & 0xFFFF;
        if (!BIT_TEST(flags, 29))
        {
            pk[9] = (uint32)sz3 >> 16;
            w0    = 0x09000000;
        }
        else
        {
            w0 = 0x07000000;
        }
        if (BIT_TEST(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((u_long)pk & w1) | w0;
        }
        else
        {
            slot  = scr->ot_48;
            pk[0] = w0 | *slot;
            *slot = (u_long)pk & w1;
        }
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        gte_strgb(&pk[1]);
        face += 4;
        tex += 2;
        Map_prim_ptr++;
        continue;
    cull:
        if (!BIT_TEST(flags, 28))
        {
            tail = NULL;
        }
        face += 4;
        tex += 2;
    }
}

// Draws the tiles map_tile_draw queued in D_800BBE50 (too near for it) with tile_model_draw_split,
// from their near LOD.
void map_tile_queue_draw(void)
{
    SVECTOR pos;
    VECTOR out;
    TILE_WORK *tw;
    STG_MODEL *model;
    uint8 *data;
    uint32 i;
    uint32 n;
    uint32 e;
    uint32 id;

    tw = &Tile_work;
    n  = D_8009886C;
    for (i = 0; i < n; i++)
    {
        e      = D_800BBE50[i];
        pos.vx = ((e >> 24) << 9) - 0x7F00;
        pos.vz = (((e >> 16) & 0xFF) << 9) - 0x7F00;
        id     = e & 0xFFFF;
        pos.vy = -((e & 0x1F00) >> 1);
        gte_ldv0(&pos);
        gte_rt();
        if ((sint8)id < 0)
        {
            model = Stage_hd2_tbl[(id & 0x7F) >> 2].model;
        }
        else
        {
            model = Stage_stg;
        }
        data = (uint8 *)model->lod[0];
        gte_stlvnl(&out);
        tw->fog_08 = D_800C0DC0.b[(out.vz / 512) & 0x1F] << 16;
        gte_SetTransVector(Scratch_view_mtx.t);
        tile_model_draw_split(data + 8, &pos, id);
        gte_SetTransVector(&Scratch_trans);
    }
}

// tile_model_draw with the quad split: a face drawn with id bit 7 goes to tile_quad_split (its
// screen XYs kept in sxy_20). A back face without bit 30 is skipped if it is a triangle, and ends
// the whole model if it is a quad.
void tile_model_draw_split(uint8 *data, SVECTOR *pos, uint32 id)
{
    TILE_WORK *scr;
    u_long *hdr;
    u_long *face;
    u_long *tex;
    u_long *tail;
    u_long *pk;
    u_long *slot;
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
    sint32 sz1; // also holds the face's packed corner words
    sint32 sz2;
    sint32 sz3;
    sint32 zmax;

    scr  = &Tile_work;
    hdr  = (u_long *)data;
    w1   = hdr[1];
    w0   = hdr[0];
    left = w1 >> 24;
    face = (u_long *)((w1 & 0xFFFFFF) + 4);
    tex  = (u_long *)(w0 & 0xFFFFFF);
    sh   = (w0 >> 28) + Scratch_scale_shift;
    if (BIT_TEST(id, 7))
    {
        Tile_work.clut_0C = hdr[-1];
    }
    else
    {
        shade                = *(u_long *)&D_800BADB0[(id * 2) & 0xF8];
        Tile_work.uv_50.w[0] = *(u_long *)&D_800BADB0[((id * 2) & 0xF8) + 4];
        Tile_work.clut_0C    = (shade & 0xFFFF0000) | 0x1D;
        shade &= 0xFF;
    }
    w1            = 0xFFFFFF;
    scr->clut_90  = scr->clut_0C & 0xFFFF0000;
    scr->tpage_94 = scr->clut_0C << 16;
    ox            = pos->vx << Scratch_scale_shift;
    oy            = pos->vy << Scratch_scale_shift;
    oz            = pos->vz << Scratch_scale_shift;
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
        gte_ldv3c(scr->v_70);
        scr->v_70[3].vy = oy;
        gte_rtpt();
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
        gte_nclip();
        flags = face[-1];
        gte_stopz(&opz);
        if (opz <= 0)
        {
            if (!BIT_TEST(flags, 30))
            {
                if (BIT_TEST(flags, 29))
                {
                    goto cull;
                }
                return;
            }
            opz = -opz;
        }
        pk = (u_long *)Map_prim_ptr;
        gte_stsxy3_ft4(pk);
        gte_stsxy3c(scr->sxy_20);
        if (BIT_TEST(flags, 29))
        {
            scr->rgbc4_14 = (flags & 0x03FFFFFF) | 0x24000000;
            gte_stsz3(&sz0, &sz1, &sz2);
            sz3 = sz2;
        }
        else
        {
            gte_ldv0(&scr->v_70[3]);
            gte_rtps();
            scr->rgbc4_14 = (flags & 0x03FFFFFF) | 0x2C000000;
            gte_stsxy(&pk[8]);
            gte_stsxy(&scr->sxy_20[3]);
            gte_stsz4(&sz0, &sz1, &sz2, &sz3);
        }
        gte_ldrgb(&scr->rgbc4_14);
        if (BIT_TEST(flags, 28))
        {
            scr->ot_48 = tail;
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
            if ((Scratch_fog_2 & 1) && oy >= 0)
            {
                scr->ot_48 = Scratch_ot + 0x7D0;
            }
            else
            {
                scr->ot_48 = Scratch_ot + (sz0 >> 3);
            }
        }
        gte_dpcs_b();
        if ((id << 24) <= 0x7FFFFFFF)
        {
            if ((id << 16) > 0x7FFFFFFF)
            {
                sz2 = tex[0];
                sz3 = tex[1];
                if (left >= 4)
                {
                    level = Tile_work.uv_50.b[7 - left];
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
            sz2             = tex[0];
            scr->uv_50.w[0] = sz2;
            sz3             = tex[1];
            scr->uv_50.w[1] = sz3;
            pk              = tile_quad_split();
            if (!BIT_TEST(flags, 28))
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
        if (!BIT_TEST(flags, 29))
        {
            pk[9] = (uint32)sz3 >> 16;
            w0    = 0x09000000;
        }
        else
        {
            w0 = 0x07000000;
        }
        if (BIT_TEST(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((u_long)pk & w1) | w0;
        }
        else
        {
            slot  = scr->ot_48;
            pk[0] = w0 | *slot;
            *slot = (u_long)pk & w1;
        }
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        gte_strgb(&pk[1]);
        Map_prim_ptr++;
        goto next;
    cull:
        if (!BIT_TEST(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// Splits the textured quad in Tile_work (corners v_70, u/v pairs uv_50) in four: projects the
// edge midpoints and the centre (two RTPTs), averages their u/v pairs, then builds the four quads
// and the back-face-culled triangles of idx_A0's lists, and links them into ot_48. The primitives
// are built as words (POLY_FT4, POLY_FT3); returns the last quad.
u_long *tile_quad_split(void)
{
    SVECTOR vec[3];
    sint32 clip;
    TILE_WORK *scr;
    u_long *p;
    u_long *last;
    uint8 *idx;
    u_long clut;
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

    scr                = &Tile_work;
    Tile_work.rgbc3_10 = Tile_work.rgbc4_14 & ~0x08000000; // code 0x2C (POLY_FT4) to 0x24 (POLY_FT3)
    ax                 = Tile_work.v_70[0].vx;
    ay                 = Tile_work.v_70[0].vy;
    az                 = Tile_work.v_70[0].vz;
    bx                 = Tile_work.v_70[1].vx;
    by                 = Tile_work.v_70[1].vy;
    bz                 = Tile_work.v_70[1].vz;
    cx                 = Tile_work.v_70[2].vx;
    cy                 = Tile_work.v_70[2].vy;
    cz                 = Tile_work.v_70[2].vz;
    dx                 = Tile_work.v_70[3].vx;
    dy                 = Tile_work.v_70[3].vy;
    dz                 = Tile_work.v_70[3].vz;
    vec[0].vx          = (ax + bx) >> 1;
    vec[0].vy          = (ay + by) >> 1;
    vec[0].vz          = (az + bz) >> 1;
    vec[1].vx = mx = (ax + cx) >> 1;
    vec[1].vy = my = (ay + cy) >> 1;
    vec[1].vz = mz = (az + cz) >> 1;
    vec[2].vx = nx = (dx + bx) >> 1;
    vec[2].vy = ny = (dy + by) >> 1;
    vec[2].vz = nz = (dz + bz) >> 1;
    gte_ldv3c(vec);
    gte_rtpt();
    vec[0].vx = (mx + nx) >> 1;
    vec[0].vy = (my + ny) >> 1;
    vec[0].vz = (mz + nz) >> 1;
    vec[1].vx = (dx + cx) >> 1;
    vec[1].vy = (dy + cy) >> 1;
    vec[1].vz = (dz + cz) >> 1;
    gte_stsxy3(&scr->sxy_20[4], &scr->sxy_20[5], &scr->sxy_20[7]);
    gte_ldv3c(vec);
    gte_rtpt();
    Tile_work.uv_50.b[8]  = (Tile_work.uv_50.b[0] + Tile_work.uv_50.b[2]) >> 1;
    Tile_work.uv_50.b[9]  = (Tile_work.uv_50.b[1] + Tile_work.uv_50.b[3]) >> 1;
    Tile_work.uv_50.b[10] = (Tile_work.uv_50.b[0] + Tile_work.uv_50.b[4]) >> 1;
    Tile_work.uv_50.b[11] = (Tile_work.uv_50.b[1] + Tile_work.uv_50.b[5]) >> 1;
    Tile_work.uv_50.b[14] = (Tile_work.uv_50.b[2] + Tile_work.uv_50.b[6]) >> 1;
    Tile_work.uv_50.b[15] = (Tile_work.uv_50.b[3] + Tile_work.uv_50.b[7]) >> 1;
    Tile_work.uv_50.b[16] = (Tile_work.uv_50.b[4] + Tile_work.uv_50.b[6]) >> 1;
    Tile_work.uv_50.b[17] = (Tile_work.uv_50.b[5] + Tile_work.uv_50.b[7]) >> 1;
    Tile_work.uv_50.b[12] = (Tile_work.uv_50.b[8] + Tile_work.uv_50.b[16]) >> 1;
    Tile_work.uv_50.b[13] = (Tile_work.uv_50.b[11] + Tile_work.uv_50.b[15]) >> 1;
    gte_stsxy0(&scr->sxy_20[6]);
    gte_stsxy1(&scr->sxy_20[8]);
    clut = scr->clut_90 | Tile_work.fog_08;
    idx  = Tile_work.idx_A0;
    for (i = 0; i < 16; i += 4)
    {
        i0 = idx[i];
        i1 = idx[i + 1];
        i2 = idx[i + 2];
        i3 = idx[i + 3];
        Map_prim_ptr++;
        last    = (u_long *)(Map_prim_ptr - 1);
        last[0] = ((u_long)Map_prim_ptr & 0xFFFFFF) | 0x09000000;
        last[2] = scr->sxy_20[i0];
        last[4] = scr->sxy_20[i1];
        last[6] = scr->sxy_20[i2];
        last[8] = scr->sxy_20[i3];
        last[1] = scr->rgbc4_14;
        last[3] = scr->uv_50.h[i0] | clut;
        last[5] = scr->uv_50.h[i1] | scr->tpage_94;
        last[7] = scr->uv_50.h[i2];
        last[9] = scr->uv_50.h[i3];
    }
    p = last;
    i = 16;
    do
    {
        i1 = idx[i];
        i2 = idx[i + 1];
        i3 = idx[i + 2];
        i += 3;
        gte_ldSXY012(scr->sxy_20[i1], scr->sxy_20[i2], scr->sxy_20[i3]);
        gte_nclip();
        gte_stopz(&clip);
        if (clip > 0)
        {
            Map_prim_ptr = (POLY_FT4 *)((POLY_FT3 *)Map_prim_ptr + 1);
            p            = (u_long *)((POLY_FT3 *)Map_prim_ptr - 1);
            p[0]         = ((u_long)Map_prim_ptr & 0xFFFFFF) | 0x07000000;
            p[2]         = scr->sxy_20[i1];
            p[4]         = scr->sxy_20[i2];
            p[6]         = scr->sxy_20[i3];
            p[1]         = scr->rgbc3_10;
            p[3]         = scr->uv_50.h[i1] | clut;
            p[5]         = scr->uv_50.h[i2] | scr->tpage_94;
            p[7]         = scr->uv_50.h[i3];
        }
    } while (i < 28);
    addPrims(scr->ot_48, last - 30, p);
    return last;
}

void Room_model_init(uint16 **hdrs)
{
    ROOM_MODEL *m;
    uint16 *src;
    sint32 i;

    if (D_800C356C == -1)
    {
        if (Scene_work.unk00 != 0)
        {
            return;
        }
    }
    else
    {
        D_80098970 = 0;
        D_80098A78 = 0;
    }
    m                  = D_800BBA90;
    Scratch_model_hdrs = hdrs;
    for (i = 0; i < 11; i++, m++)
    {
        src = Scratch_model_hdrs[i];
        if (src != NULL)
        {
            *(uint16 *)&m->flags_0 = *src++;
            m->wrap_x_24           = *src++;
            m->wrap_y_26           = *src++;
            m->tpage_2A            = *src++;
            m->value_28            = *src++;
            m->speed_x_20          = *src++;
            m->speed_y_22          = 0;
            m->pos_1C.x            = *src++;
            m->pos_1C.y            = *src++;
            m->rgb_2C.h[0]         = *src++;
            m->rgb_2C.h[1]         = *src++;
            m->abr_30.w            = *src;
            src += 6;
            m->map_34 = (u_long *)src;
            if (m->flags_1 != 0)
            {
                m->pos_prev_18 = m->pos_1C;
                m->pos_C       = m->pos_prev_18;
                m->fpos_4.x = m->fpos_prev_10.x = m->pos_1C.x << 16;
                m->fpos_4.y = m->fpos_prev_10.y = m->pos_1C.y << 16;
            }
        }
    }
}

// Moves and draws the room models' screen layers. A model with flags_0 bit 0 moves: by its speeds
// when flags_1 is set, else with the camera (its angles and the distance it moved, summed in
// D_80098A78). One with bit 1 is drawn as a DR_MODE and a screen of 32x32 SPRTs from its tile map,
// linked to the ordering table entry rgb_2C.b[3].
// The packets are written as words (each a SPRT's five). The DR_MODE's tag is stored twice, as in
// the target (it keeps 0x02000000 in a register). The distance and the tile row share dist, and
// work holds the first row's quotient and later the layer's link: GCC then computes y from the
// quotient's register and copies it to dist, as the target does.
void Room_model_update(void)
{
    ROOM_MODEL *m;
    u_long *p;
    u_long *start;
    u_long *next;
    u_long *map;
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
    x          = D_800A3958.work.pos_98.vx;
    t          = D_800A3958.work.pos_A8.vx;
    dx         = x - t;
    y          = D_800A3958.work.pos_98.vz;
    h          = D_800A3958.work.pos_A8.vz;
    dz         = y - h;
    p          = (u_long *)Map_prim_ptr;
    start      = p;
    d2         = dx * dx + dz * dz;
    dist       = SquareRoot0(d2);
    if (dist != 0)
    {
        dist = (d2 / dist + dist) >> 1;
    }
    D_80098970++;
    D_80098A78 -= (dist * rsin(D_800A3958.work.ang.vy - ratan2(dx, dz))) / 24;
    for (m = D_800BBA90; m < D_800BBA90 + 11; m++)
    {
        if (m->flags_0 & 1)
        {
            m->fpos_prev_10 = m->fpos_4;
            m->pos_prev_18  = m->pos_C;
            t               = m->wrap_x_24;
            if (m->flags_1 == 0)
            {
                m->fpos_4.x =
                    (((((D_800A3958.work.ang.vy + m->pos_1C.x + D_80098A78 / (t * t)) * 8) + ((uint32)(m->speed_x_20 * D_80098970) >> 8)) &
                      0x7FFF)
                     << 5) *
                    t * 2;
                a = D_800A3958.work.ang.vx;
                m->fpos_4.y =
                    (m->pos_1C.y << 16) -
                    (((a < 0x800) ? a * 0xF0 / 13 - D_800A3958.work.pos[0].vy : (a - 0x1000) * 0xF0 / 13 - D_800A3958.work.pos[0].vy)
                     << 11);
            }
            else
            {
                m->fpos_4.x += m->speed_x_20 << 8;
                m->fpos_4.y += m->speed_y_22 << 8;
            }
            room_model_pos_wrap(m);
        }
        if (m->flags_0 & 2)
        {
            next    = p + 5;
            p[0]    = 0x02000000;
            mode    = 0xE1000000;
            p[1]    = m->tpage_2A | ((m->abr_30.b[1] << 5) | mode);
            p[0]    = 0x02000000 | ((u_long)next & 0xFFFFFF);
            p[2]    = 0;
            p       = next;
            add     = (uint32)m->value_28 << 14;
            map     = m->map_34;
            t       = m->wrap_x_24;
            v       = m->pos_C.y;
            h       = m->wrap_y_26;
            attr    = m->abr_30.b[0] << 25;
            work    = v / 32;
            dist    = work;
            colbase = m->pos_C.x / 32;
            y       = -(sint16)(v - work * 32);

            for (; y < 0xF0; y += 0x20)
            {
                code = attr | 0x64000000;
                size = 0x200020;
                col  = colbase;
                u    = m->pos_C.x;
                x    = -(sint16)(u - (u / 32) * 32);
                for (; x < 0x140; x += 0x20)
                {
                    ((sint16 *)p)[4] = x; // x0, y0
                    ((sint16 *)p)[5] = y;
                    p[3]             = map[dist * t + col] + add;
                    col++;
                    if (col >= t)
                    {
                        col = 0;
                    }
                    p[0] = (((u_long)p + 0x14) & 0xFFFFFF) | 0x04000000;
                    p[1] = (m->rgb_2C.w & 0xFFFFFF) | code;
                    p[4] = size;
                    p += 5;
                }
                dist++;
                if (dist >= h)
                {
                    dist = 0;
                }
            }
            work = getaddr(&Disp_env_ptr->ot[m->rgb_2C.b[3]]);
            setaddr(p - 5, work);
            setaddr(&Disp_env_ptr->ot[m->rgb_2C.b[3]], start);
            start = p;
        }
    }
    Map_prim_ptr = (POLY_FT4 *)p;
}

// Wraps the model's position into its wrap area (x only when flags_1 is set), then copies the
// whole part into pos_C.
void room_model_pos_wrap(ROOM_MODEL *m)
{
    sint32 lim;

    if (m->flags_1 != 0)
    {
        lim = m->wrap_x_24 << 21;
        while (m->fpos_4.x >= lim)
        {
            m->fpos_4.x -= lim;
        }
        while (m->fpos_4.x < 0)
        {
            m->fpos_4.x += lim;
        }
    }
    lim = m->wrap_y_26 << 21;
    while (m->fpos_4.y >= lim)
    {
        m->fpos_4.y -= lim;
    }
    while (m->fpos_4.y < 0)
    {
        m->fpos_4.y += lim;
    }
    m->pos_C.x = m->fpos_4.x >> 16;
    m->pos_C.y = m->fpos_4.y >> 16;
}

// Unless D_80098824 is set: sets up the camera (func_80037FB4, same arguments), transforms the
// player's position into view space (Quad_pl_view), loads the fog table and the split's vertex
// lists into Quad_work, and draws SUPPORT's block model D_801F6080 at the origin.
void func_80023728(VECTOR *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    QUAD_WORK *qw = &Quad_work;
    SVECTOR pos;

    if (D_80098824 == 0)
    {
        D_1F800075 = D_800C0DE6;
        func_80037FB4(vec, arg1, arg2, arg3);
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_SetTransMatrix(&Scratch_view_mtx);
        pos.vx = Player_work[0].pos.vx;
        pos.vy = Player_work[0].pos.vy;
        pos.vz = Player_work[0].pos.vz;
        gte_ldv0(&pos);
        gte_rt();
        gte_stlvnl(&Quad_pl_view);
        if (Scene_work.unk00 != 0)
        {
            D_1F80007C = 0;
        }
        else
        {
            D_1F80007C = 0x2000000;
        }
        Quad_work.part_z_BC = Quad_near_z + 0x172;
        Mem_copy32(&D_800C0DC0, Quad_fog_tbl, 1);
        Mem_copy32(D_80097C90, Quad_work.idx_20, 1);
        D_1F800004                = 0;
        *(u_long *)&qw->pos_40.vx = 0; // vx and vy at once
        *(u_long *)&qw->pos_40.vz = 0; // vz and pad at once
        func_80024E94(D_801F6080, 0);
        D_1F800004 = 1;
    }
}

// Unless D_80098824 is set, the frame's map pass: draws the map (map_window_draw in draw mode 1,
// map_view_draw otherwise), draws a ring (func_800272D0) round each live D_8009CF88 shot of id 0x33,
// type 0xFE that projects in front of the camera, then sets up Quad_work as func_80023728 does and
// runs map_block_masks_draw. The two draw passes are timed into D_800D9BE8 and D_800D9BEC.
void Map_draw(void)
{
    SVECTOR pos;
    DVECTOR sxy;
    sint32 otz;
    sint32 i;

    if (D_80098824 != 0)
    {
        return;
    }
    D_80098A08 = 0;
    D_800989AC = 0;
    D_1F800075 = D_800C0DE6;
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    Mem_copy32(D_80097C90, &Quad_clut_tbl[2], 1);
    D_800D9BE4 = VSync(1);
    if (D_1F800075 == 1)
    {
        map_window_draw();
    }
    else
    {
        map_view_draw();
    }
    D_800D9BE8 = (VSync(1) - D_800D9BE4) & 0xFFFF;
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    for (i = 0; i < 32; i++)
    {
        if (D_8009CF88[i].id == 0x33 && (D_8009CF88[i].be_flag & MOVE) && D_8009CF88[i].type == 0xFE)
        {
            pos = D_8009CF88[i].efc.model.pos;
            gte_ldv0(&pos);
            gte_rtps();
            gte_stsxy(&sxy);
            gte_stotz(&otz);
            if (otz > 0)
            {
                func_800272D0(sxy.vx, sxy.vy, D_8009CF88[i].routine_2 * 2, D_8009CF88[i].routine_3 * 2);
            }
        }
    }
    pos.vx = Player_work[0].pos.vx;
    pos.vy = Player_work[0].pos.vy;
    pos.vz = Player_work[0].pos.vz;
    gte_ldv0(&pos);
    gte_rt();
    gte_stlvnl(&Quad_pl_view);
    if (Scene_work.unk00 != 0)
    {
        D_1F80007C = 0;
    }
    else
    {
        D_1F80007C = 0x2000000;
    }
    Quad_work.part_z_BC = Quad_near_z + 0x172;
    Mem_copy32(&D_800C0DC0, Quad_fog_tbl, 1);
    Mem_copy32(D_80097C90, Quad_work.idx_20, 1);
    D_800D9BE4 = VSync(1);
    map_block_masks_draw();
    D_800D9BEC = (VSync(1) - D_800D9BE4) & 0xFFFF;
}

void map_block_masks_draw(void)
{
    switch (D_1F800075)
    {
        case 0:
        default:
            D_1F800004 = 0x400;
            map_blocks_draw(Map_block_mask, 0);
            map_blocks_draw(Map_block_mask + MAP_BLOCK_ROWS, 1);
            break;
        case 1:
            D_1F800004 = 0;
            map_blocks_draw(Map_block_mask, 1);
            map_blocks_draw(Map_block_mask + MAP_BLOCK_ROWS, 1);
            break;
        case 2:
            D_1F800004 = 0;
            map_blocks_draw2(Map_block_mask, 2);
            map_blocks_draw2(Map_block_mask + MAP_BLOCK_ROWS, 2);
            break;
        case 3:
            D_1F800004 = 0;
            map_blocks_draw2(Map_block_mask, 3);
            map_blocks_draw2(Map_block_mask + MAP_BLOCK_ROWS, 3);
            break;
    }
}

// Draws a six-part block model with func_80023EA8: of parts 0-3, the two on the camera's side of
// the block (by x and z), then part 4, and part 5 only up to depth D_1F8001BC.
void func_80023CF0(u_long *model, sint32 z)
{
    uint32 count;

    count                    = *(uint8 *)model; // the header's low byte
    Quad_work.clut_tbl_C8[0] = model[1];
    Quad_work.clut_tbl_C8[1] = model[2];
    Quad_work.clut_tbl_C8[2] = model[3];
    model += count + 1;
    if (Scratch_cam_pos.vx < Quad_work.pos_40.vx)
    {
        if (Scratch_cam_pos.vz < Quad_work.pos_40.vz)
        {
            func_80023EA8(&model[0]);
            func_80023EA8(&model[6]);
        }
        else
        {
            func_80023EA8(&model[4]);
            func_80023EA8(&model[6]);
        }
    }
    else
    {
        if (Scratch_cam_pos.vz < Quad_work.pos_40.vz)
        {
            func_80023EA8(&model[0]);
            func_80023EA8(&model[2]);
        }
        else
        {
            func_80023EA8(&model[2]);
            func_80023EA8(&model[4]);
        }
    }
    func_80023EA8(&model[8]);
    if (z <= Quad_work.part_z_BC)
    {
        func_80023EA8(&model[10]);
    }
}

// Draws every part of a block model with func_80023EA8.
void func_80023E1C(u_long *model, sint32 z)
{
    u_long *part;
    uint32 i; // the header word, then the loop counter
    uint32 n;

    i                        = model[0];
    n                        = (i & 0x3F00) >> 7;
    Quad_work.clut_tbl_C8[0] = model[1];
    Quad_work.clut_tbl_C8[1] = model[2];
    Quad_work.clut_tbl_C8[2] = model[3];
    part                     = &model[(i & 0xFF) + 1];
    i                        = 0;
    do
    {
        func_80023EA8(&part[i]);
        i += 2;
    } while (i < n);
}

// Draws a map block model's quads at Quad_work.pos_40: each face's four corners are 12 bytes (x and
// z signed, y unsigned and upwards). Culls back faces (unless flag bit 30), faces off screen and,
// without flag bit 31, faces nearer than 0xC1; sorts the rest by depth (or links them after the
// previous face, bit 28), and hands large or uneven faces to quad_split.
void func_80023EA8(u_long *model)
{
    QUAD_WORK *scr;
    SVECTOR unused; // unused: gives the target's frame size
    u_long *face;
    u_long *tex;
    u_long *tail;
    u_long *pk;
    u_long *slot;
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

    // The header words are reused for the CLUT word and the two loop constants.
    scr             = &Quad_work;
    w1              = model[1];
    w0              = model[0];
    left            = w1 >> 24;
    face            = (u_long *)((w1 & 0xFFFFFF) + 4);
    tex             = (u_long *)(w0 & 0xFFFFFF);
    shift           = Scratch_scale_shift;
    w1              = Quad_clut_tbl[(w0 >> 24) & 0xF];
    Quad_face_count = left;
    scr->clut_58    = w1 & 0xFFFF0000;
    scr->tpage_5C   = w1 << 16;
    sh              = (w0 >> 28) + shift;
    fog_sh          = shift + 9;
    ox              = scr->pos_40.vx << shift;
    oy              = scr->pos_40.vy << shift;
    oz              = scr->pos_40.vz << shift;
    w0              = 0x09000000;
    w1              = 0xFFFFFF;
    tail            = (u_long *)1; // not NULL: a first face linked after the previous one is drawn
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (BIT_TEST(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1                      = face[0];
        scr->u_88.face.vtx[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->u_88.face.vtx[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->u_88.face.vtx[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->u_88.face.vtx[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1                      = face[1];
        scr->u_88.face.vtx[1].vy = oy - ((uint8)sz1 << sh);
        scr->u_88.face.vtx[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->u_88.face.vtx[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->u_88.face.vtx[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1                      = face[2];
        scr->u_88.face.vtx[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        gte_ldv3c(scr->u_88.face.vtx);
        gte_rtpt();
        scr->u_88.face.vtx[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->u_88.face.vtx[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->u_88.face.vtx[3].vz = ((sz1 >> 24) << sh) + oz;
        gte_nclip();
        Quad_face_flags = flags;
        gte_stopz(&opz);
        if (opz <= 0)
        {
            if (!BIT_TEST(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = (u_long *)Map_prim_ptr;
        gte_stsxy3_ft4(pk);
        gte_stsxy3c(scr->sxy_60.w);
        gte_ldv0(&scr->u_88.face.vtx[3]);
        gte_rtps();
        scr->rgbc4_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        gte_stsxy(&pk[8]);
        gte_stsxy(&scr->sxy_60.w[3]);
        gte_stsz4(&sz0, &sz1, &sz2, &sz3);
        // On screen when a corner or the midpoint of a diagonal is.
        if ((x0 = Quad_sxy[0].vx) < 0x140U && (uint16)Quad_sxy[0].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x1 = Quad_sxy[1].vx) < 0x140U && (uint16)Quad_sxy[1].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x2 = Quad_sxy[2].vx) < 0x140U && (uint16)Quad_sxy[2].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x3 = Quad_sxy[3].vx) < 0x140U && (uint16)Quad_sxy[3].vy < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x0 + (sint16)x3) >> 1) < 0x140U && (uint32)((Quad_sxy[0].vy + Quad_sxy[3].vy) >> 1) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x1 + (sint16)x2) >> 1) >= 0x140U || (uint32)((Quad_sxy[1].vy + Quad_sxy[2].vy) >> 1) >= 0xF0U)
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
        if (BIT_TEST(flags, 31))
        {
            if (!BIT_TEST(flags, 27))
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
            if (BIT_TEST(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!BIT_TEST(flags, 28))
        {
            gte_ldrgb(&scr->rgbc4_54);
            gte_dpcs();
            scr->fog_48 = Quad_fog_tbl[(sz0 >> fog_sh) & 0x1F] << 16;
            gte_strgb(&scr->rgbc4_54);
        }
        if (BIT_TEST(flags, 31) && BIT_TEST(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (BIT_TEST(flags, 29) && zmin >= 0x181)
        {
            goto plain;
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            // How far the quad is from a parallelogram.
            dx = ((sint16)scr->sxy_60.h[0].x + (sint16)scr->sxy_60.h[3].x - (sint16)scr->sxy_60.h[1].x - (sint16)scr->sxy_60.h[2].x) >> 1;
            dy = ((sint16)scr->sxy_60.h[0].y + (sint16)scr->sxy_60.h[3].y - (sint16)scr->sxy_60.h[1].y - (sint16)scr->sxy_60.h[2].y) >> 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        if (BIT_TEST(flags, 28))
        {
            scr->ot_3C = tail;
        }
        else
        {
            scr->ot_3C = Scratch_ot + (sz0 >> 3);
        }
        scr->u_88.face.uv[0] = sz2;
        scr->u_88.face.uv[1] = sz3;
        pk                   = quad_split();
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        goto next;
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5C;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (BIT_TEST(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((u_long)pk & w1) | w0;
        }
        else
        {
            slot  = Scratch_ot + (sz0 >> 3);
            pk[0] = w0 | *slot;
            *slot = (u_long)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc4_54;
        Map_prim_ptr++;
        goto next;
    cull:
        if (!BIT_TEST(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// tile_quad_split on Quad_work's layout.
u_long *quad_split(void)
{
    SVECTOR vec[3];
    sint32 clip;
    QUAD_WORK *scr;
    u_long *p;
    u_long *last;
    uint8 *idx;
    u_long clut;
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

    scr                = &Quad_work;
    Quad_work.rgbc3_50 = Quad_work.rgbc4_54 & ~0x08000000; // code 0x2C (POLY_FT4) to 0x24 (POLY_FT3)
    ax                 = Quad_vtx[0].vx;
    ay                 = Quad_vtx[0].vy;
    az                 = Quad_vtx[0].vz;
    bx                 = Quad_vtx[1].vx;
    by                 = Quad_vtx[1].vy;
    bz                 = Quad_vtx[1].vz;
    cx                 = Quad_vtx[2].vx;
    cy                 = Quad_vtx[2].vy;
    cz                 = Quad_vtx[2].vz;
    dx                 = Quad_vtx[3].vx;
    dy                 = Quad_vtx[3].vy;
    dz                 = Quad_vtx[3].vz;
    vec[0].vx          = (ax + bx) >> 1;
    vec[0].vy          = (ay + by) >> 1;
    vec[0].vz          = (az + bz) >> 1;
    vec[1].vx = mx = (ax + cx) >> 1;
    vec[1].vy = my = (ay + cy) >> 1;
    vec[1].vz = mz = (az + cz) >> 1;
    vec[2].vx = nx = (dx + bx) >> 1;
    vec[2].vy = ny = (dy + by) >> 1;
    vec[2].vz = nz = (dz + bz) >> 1;
    gte_ldv3c(vec);
    gte_rtpt();
    vec[0].vx = (mx + nx) >> 1;
    vec[0].vy = (my + ny) >> 1;
    vec[0].vz = (mz + nz) >> 1;
    vec[1].vx = (dx + cx) >> 1;
    vec[1].vy = (dy + cy) >> 1;
    vec[1].vz = (dz + cz) >> 1;
    gte_stsxy3(&scr->sxy_60.w[4], &scr->sxy_60.w[5], &scr->sxy_60.w[7]);
    gte_ldv3c(vec);
    gte_rtpt();
    Quad_work.u_88.uv.b[8]  = (Quad_work.u_88.uv.b[0] + Quad_work.u_88.uv.b[2]) >> 1;
    Quad_work.u_88.uv.b[9]  = (Quad_work.u_88.uv.b[1] + Quad_work.u_88.uv.b[3]) >> 1;
    Quad_work.u_88.uv.b[10] = (Quad_work.u_88.uv.b[0] + Quad_work.u_88.uv.b[4]) >> 1;
    Quad_work.u_88.uv.b[11] = (Quad_work.u_88.uv.b[1] + Quad_work.u_88.uv.b[5]) >> 1;
    Quad_work.u_88.uv.b[14] = (Quad_work.u_88.uv.b[2] + Quad_work.u_88.uv.b[6]) >> 1;
    Quad_work.u_88.uv.b[15] = (Quad_work.u_88.uv.b[3] + Quad_work.u_88.uv.b[7]) >> 1;
    Quad_work.u_88.uv.b[16] = (Quad_work.u_88.uv.b[4] + Quad_work.u_88.uv.b[6]) >> 1;
    Quad_work.u_88.uv.b[17] = (Quad_work.u_88.uv.b[5] + Quad_work.u_88.uv.b[7]) >> 1;
    Quad_work.u_88.uv.b[12] = (Quad_work.u_88.uv.b[8] + Quad_work.u_88.uv.b[16]) >> 1;
    Quad_work.u_88.uv.b[13] = (Quad_work.u_88.uv.b[11] + Quad_work.u_88.uv.b[15]) >> 1;
    gte_stsxy0(&scr->sxy_60.w[6]);
    gte_stsxy1(&scr->sxy_60.w[8]);
    clut = Quad_work.clut_58 | Quad_work.fog_48;
    idx  = Quad_work.idx_20;
    for (i = 0; i < 16; i += 4)
    {
        i0 = idx[i];
        i1 = idx[i + 1];
        i2 = idx[i + 2];
        i3 = idx[i + 3];
        Map_prim_ptr++;
        last    = (u_long *)(Map_prim_ptr - 1);
        last[0] = ((u_long)Map_prim_ptr & 0xFFFFFF) | 0x09000000;
        last[2] = scr->sxy_60.w[i0];
        last[4] = scr->sxy_60.w[i1];
        last[6] = scr->sxy_60.w[i2];
        last[8] = scr->sxy_60.w[i3];
        last[1] = scr->rgbc4_54;
        last[3] = scr->u_88.uv.h[i0] | clut;
        last[5] = scr->u_88.uv.h[i1] | scr->tpage_5C;
        last[7] = scr->u_88.uv.h[i2];
        last[9] = scr->u_88.uv.h[i3];
    }
    p = last;
    i = 16;
    do
    {
        i1 = idx[i];
        i2 = idx[i + 1];
        i3 = idx[i + 2];
        i += 3;
        gte_ldSXY012(scr->sxy_60.w[i1], scr->sxy_60.w[i2], scr->sxy_60.w[i3]);
        gte_nclip();
        gte_stopz(&clip);
        if (clip > 0)
        {
            Map_prim_ptr = (POLY_FT4 *)((POLY_FT3 *)Map_prim_ptr + 1);
            p            = (u_long *)((POLY_FT3 *)Map_prim_ptr - 1);
            p[0]         = ((u_long)Map_prim_ptr & 0xFFFFFF) | 0x07000000;
            p[2]         = scr->sxy_60.w[i1];
            p[4]         = scr->sxy_60.w[i2];
            p[6]         = scr->sxy_60.w[i3];
            p[1]         = scr->rgbc3_50;
            p[3]         = scr->u_88.uv.h[i1] | clut;
            p[5]         = scr->u_88.uv.h[i2] | scr->tpage_5C;
            p[7]         = scr->u_88.uv.h[i3];
        }
    } while (i < 28);
    addPrims(scr->ot_3C, last - 30, p);
    return last;
}

// Draws the map blocks whose bits are set in rows[] (one word per row of 0x20 blocks, MSB first;
// the first row's bit 31 is cleared first), choosing the model's level of detail by depth.
void map_blocks_draw(uint32 *rows, sint32 kind)
{
    QUAD_WORK *qw;
    uint32 *flags;
    MAP_BLOCK *b;
    MAP_BLOCK *row_end;
    MAP_BLOCK *end;
    sint32 bits;
    STG_MODEL *model;
    uint32 *lod;
    VECTOR pos;

    qw    = &Quad_work;
    flags = rows; // a copy of rows: the build needs it for the prologue's order
    b     = Map_blocks;
    end   = b + 0x800;
    *flags &= 0x7FFFFFFF;
    do
    {
        bits = *flags;
        if (bits != 0)
        {
            *flags  = 0;
            row_end = b + 0x20;
            do
            {
                if (bits < 0)
                {
                    model                   = (STG_MODEL *)(b->model & 0xFFFFFF);
                    *(long *)&qw->pos_40.vx = *(long *)&b->pos.vx;
                    *(long *)&qw->pos_40.vz = *(long *)&b->pos.vz;
                    gte_ldv0(&qw->pos_40);
                    gte_rt();
                    gte_stlvnl(&pos);
                    pos.vz >>= Scratch_scale_shift;
                    if (pos.vz > 0x1C20)
                    {
                        lod = &model->lod[2];
                    }
                    else if (pos.vz > 0xAF0)
                    {
                        lod = &model->lod[1];
                    }
                    else
                    {
                        lod = &model->lod[0];
                    }
                    if (qw->pos_40.pad == 0)
                    {
                        lod += 3;
                    }
                    lod = (uint32 *)*lod;
                    Map_block_draw_tbl[kind][(uint32)lod >> 31]((u_long *)((uint32)lod & 0xFFFFFF), pos.vz);
                }
                bits <<= 1;
                b++;
            } while (b < row_end);
        }
        else
        {
            b += 0x20;
        }
        flags++;
    } while (b < end);
}

// func_80023CF0 with func_80024F30, copying all of the model's CLUT words.
void func_80024D4C(u_long *model, sint32 z)
{
    QUAD_WORK *scr;
    uint32 i;
    uint32 count;

    scr   = &Quad_work;
    count = *(uint8 *)model; // the header's low byte
    for (i = 0; i < count; i++)
    {
        scr->clut_tbl_C8[i] = model[i + 1];
    }
    model += count + 1;
    if (Scratch_cam_pos.vx < scr->pos_40.vx)
    {
        if (Scratch_cam_pos.vz < scr->pos_40.vz)
        {
            func_80024F30(&model[0]);
            func_80024F30(&model[6]);
        }
        else
        {
            func_80024F30(&model[4]);
            func_80024F30(&model[6]);
        }
    }
    else
    {
        if (Scratch_cam_pos.vz < scr->pos_40.vz)
        {
            func_80024F30(&model[0]);
            func_80024F30(&model[2]);
        }
        else
        {
            func_80024F30(&model[2]);
            func_80024F30(&model[4]);
        }
    }
    func_80024F30(&model[8]);
    if (z <= Quad_work.part_z_BC)
    {
        func_80024F30(&model[10]);
    }
}

// func_80023E1C with func_80024F30, copying all of the model's CLUT words.
void func_80024E94(u_long *model, sint32 z)
{
    u_long *part;
    uint32 i; // the header word, then the loop counter
    uint32 n;
    uint32 count;

    i     = model[0];
    n     = (i & 0x3F00) >> 7;
    count = i & 0xFF;
    for (i = 0; i < count; i++)
    {
        Quad_work.clut_tbl_C8[i] = model[i + 1];
    }
    part = &model[count + 1];
    i    = 0;
    do
    {
        func_80024F30(&part[i]);
        i += 2;
    } while (i < n);
}

// func_80023EA8 without the on-screen test. A near face (below Quad_near_z) over the screen centre
// takes the colour bits D_1F80007C (the depth range locals are reused for the x and y ranges); a
// face with flag bit 24 starts a new chain at its ordering table entry instead of being drawn.
void func_80024F30(u_long *model)
{
    QUAD_WORK *scr;
    SVECTOR unused; // unused: gives the target's frame size
    u_long *face;
    u_long *tex;
    u_long *tail;
    u_long *pk;
    u_long *slot;
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

    // The header words are reused for the CLUT word and the two loop constants.
    scr             = &Quad_work;
    w1              = model[1];
    w0              = model[0];
    left            = w1 >> 24;
    face            = (u_long *)((w1 & 0xFFFFFF) + 4);
    tex             = (u_long *)(w0 & 0xFFFFFF);
    shift           = Scratch_scale_shift;
    w1              = Quad_clut_tbl[(w0 >> 24) & 0xF];
    Quad_face_count = left;
    scr->clut_58    = w1 & 0xFFFF0000;
    scr->tpage_5C   = w1 << 16;
    sh              = (w0 >> 28) + shift;
    fog_sh          = shift + 9;
    ox              = scr->pos_40.vx << shift;
    oy              = scr->pos_40.vy << shift;
    oz              = scr->pos_40.vz << shift;
    w0              = 0x09000000;
    w1              = 0xFFFFFF;
    tail            = (u_long *)1; // not NULL: a first face linked after the previous one is drawn
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (BIT_TEST(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1                      = face[0];
        scr->u_88.face.vtx[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->u_88.face.vtx[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->u_88.face.vtx[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->u_88.face.vtx[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1                      = face[1];
        scr->u_88.face.vtx[1].vy = oy - ((uint8)sz1 << sh);
        scr->u_88.face.vtx[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->u_88.face.vtx[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->u_88.face.vtx[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1                      = face[2];
        scr->u_88.face.vtx[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        gte_ldv3c(scr->u_88.face.vtx);
        gte_rtpt();
        scr->u_88.face.vtx[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->u_88.face.vtx[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->u_88.face.vtx[3].vz = ((sz1 >> 24) << sh) + oz;
        gte_nclip();
        Quad_face_flags = flags;
        gte_stopz(&opz);
        if (opz <= 0)
        {
            if (!BIT_TEST(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = (u_long *)Map_prim_ptr;
        gte_stsxy3_ft4(pk);
        gte_stsxy3c(scr->sxy_60.w);
        gte_ldv0(&scr->u_88.face.vtx[3]);
        gte_rtps();
        scr->rgbc4_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        gte_stsxy(&pk[8]);
        gte_stsxy(&scr->sxy_60.w[3]);
        gte_stsz4(&sz0, &sz1, &sz2, &sz3);
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
        if (BIT_TEST(flags, 31))
        {
            if (!BIT_TEST(flags, 27))
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
            if (BIT_TEST(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!BIT_TEST(flags, 28))
        {
            gte_ldrgb(&scr->rgbc4_54);
            gte_dpcs();
            scr->fog_48 = Quad_fog_tbl[(sz0 >> fog_sh) & 0x1F] << 16;
            gte_strgb(&scr->rgbc4_54);
        }
        if (BIT_TEST(flags, 31) && BIT_TEST(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (BIT_TEST(flags, 29))
        {
            if (zmin >= 0x181)
            {
                goto plain;
            }
            if (BIT_TEST(flags, 24))
            {
                goto plain;
            }
        }
        if ((sint32)flags > 0 && zmax < Quad_near_z)
        {
            // The x range.
            if (Quad_sxy[0].vx < Quad_sxy[1].vx)
            {
                lo = Quad_sxy[0].vx;
                hi = Quad_sxy[1].vx;
            }
            else
            {
                lo = Quad_sxy[1].vx;
                hi = Quad_sxy[0].vx;
            }
            if (Quad_sxy[2].vx < Quad_sxy[3].vx)
            {
                zmin = Quad_sxy[2].vx;
                zmax = Quad_sxy[3].vx;
            }
            else
            {
                zmin = Quad_sxy[3].vx;
                zmax = Quad_sxy[2].vx;
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
                // The y range.
                if (Quad_sxy[0].vy < Quad_sxy[1].vy)
                {
                    lo = Quad_sxy[0].vy;
                    hi = Quad_sxy[1].vy;
                }
                else
                {
                    lo = Quad_sxy[1].vy;
                    hi = Quad_sxy[0].vy;
                }
                if (Quad_sxy[2].vy < Quad_sxy[3].vy)
                {
                    zmin = Quad_sxy[2].vy;
                    zmax = Quad_sxy[3].vy;
                }
                else
                {
                    zmin = Quad_sxy[3].vy;
                    zmax = Quad_sxy[2].vy;
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
                    scr->rgbc4_54 |= D_1F80007C;
                }
            }
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            // How far the quad is from a parallelogram.
            dx = ((sint16)scr->sxy_60.h[0].x + (sint16)scr->sxy_60.h[3].x - (sint16)scr->sxy_60.h[1].x - (sint16)scr->sxy_60.h[2].x) >> 1;
            dy = ((sint16)scr->sxy_60.h[0].y + (sint16)scr->sxy_60.h[3].y - (sint16)scr->sxy_60.h[1].y - (sint16)scr->sxy_60.h[2].y) >> 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        if (BIT_TEST(flags, 28))
        {
            scr->ot_3C = tail;
        }
        else
        {
            scr->ot_3C = Scratch_ot + (sz0 >> 3);
        }
        scr->u_88.face.uv[0] = sz2;
        scr->u_88.face.uv[1] = sz3;
        pk                   = quad_split();
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        goto next;
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5C;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (BIT_TEST(flags, 28))
        {
            pk[0] = w0;
            addPrim(tail, pk);
        }
        else
        {
            slot  = Scratch_ot + (sz0 >> 3);
            pk[0] = w0 | *slot;
            if (BIT_TEST(flags, 24))
            {
                tail = Scratch_ot + (sz0 >> 3);
                goto next;
            }
            *slot = (u_long)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc4_54;
        Map_prim_ptr++;
        goto next;
    cull:
        if (!BIT_TEST(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// func_80023CF0 with func_80025900.
void func_80025748(u_long *model, sint32 z)
{
    uint32 count;

    count                    = *(uint8 *)model; // the header's low byte
    Quad_work.clut_tbl_C8[0] = model[1];
    Quad_work.clut_tbl_C8[1] = model[2];
    Quad_work.clut_tbl_C8[2] = model[3];
    model += count + 1;
    if (Scratch_cam_pos.vx < Quad_work.pos_40.vx)
    {
        if (Scratch_cam_pos.vz < Quad_work.pos_40.vz)
        {
            func_80025900(&model[0]);
            func_80025900(&model[6]);
        }
        else
        {
            func_80025900(&model[4]);
            func_80025900(&model[6]);
        }
    }
    else
    {
        if (Scratch_cam_pos.vz < Quad_work.pos_40.vz)
        {
            func_80025900(&model[0]);
            func_80025900(&model[2]);
        }
        else
        {
            func_80025900(&model[2]);
            func_80025900(&model[4]);
        }
    }
    func_80025900(&model[8]);
    if (z <= Quad_work.part_z_BC)
    {
        func_80025900(&model[10]);
    }
}

// func_80023E1C with func_80025900.
void func_80025874(u_long *model, sint32 z)
{
    u_long *part;
    uint32 i; // the header word, then the loop counter
    uint32 n;

    i                        = model[0];
    n                        = (i & 0x3F00) >> 7;
    Quad_work.clut_tbl_C8[0] = model[1];
    Quad_work.clut_tbl_C8[1] = model[2];
    Quad_work.clut_tbl_C8[2] = model[3];
    part                     = &model[(i & 0xFF) + 1];
    i                        = 0;
    do
    {
        func_80025900(&part[i]);
        i += 2;
    } while (i < n);
}

// func_80023EA8 that keeps back faces: one seen from behind is drawn only beyond Quad_near_z and
// without flag bit 24, and without bit 30 it is drawn flat in colour 0x010101 at its far depth.
// Near faces over the screen centre take D_1F80007C as in func_80024F30.
void func_80025900(u_long *model)
{
    QUAD_WORK *scr;
    SVECTOR unused; // unused: gives the target's frame size
    u_long *face;
    u_long *tex;
    u_long *tail;
    u_long *pk;
    u_long *slot;
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

    // The header words are reused for the CLUT word and the two loop constants.
    scr             = &Quad_work;
    w1              = model[1];
    w0              = model[0];
    left            = w1 >> 24;
    face            = (u_long *)((w1 & 0xFFFFFF) + 4);
    tex             = (u_long *)(w0 & 0xFFFFFF);
    shift           = Scratch_scale_shift;
    w1              = Quad_clut_tbl[(w0 >> 24) & 0xF];
    Quad_face_count = left;
    scr->clut_58    = w1 & 0xFFFF0000;
    scr->tpage_5C   = w1 << 16;
    sh              = (w0 >> 28) + shift;
    fog_sh          = shift + 9;
    ox              = scr->pos_40.vx << shift;
    oy              = scr->pos_40.vy << shift;
    oz              = scr->pos_40.vz << shift;
    w0              = 0x09000000;
    w1              = 0xFFFFFF;
    tail            = (u_long *)1; // not NULL: a first face linked after the previous one is drawn
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (BIT_TEST(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1                      = face[0];
        scr->u_88.face.vtx[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->u_88.face.vtx[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->u_88.face.vtx[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->u_88.face.vtx[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1                      = face[1];
        scr->u_88.face.vtx[1].vy = oy - ((uint8)sz1 << sh);
        scr->u_88.face.vtx[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->u_88.face.vtx[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->u_88.face.vtx[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1                      = face[2];
        scr->u_88.face.vtx[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        gte_ldv3c(scr->u_88.face.vtx);
        gte_rtpt();
        scr->u_88.face.vtx[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->u_88.face.vtx[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->u_88.face.vtx[3].vz = ((sz1 >> 24) << sh) + oz;
        gte_nclip();
        Quad_face_flags = flags;
        gte_stopz(&opz);
        if (opz == 0)
        {
            goto cull;
        }
        if (opz < 0 && BIT_TEST(flags, 30))
        {
            opz = -opz;
        }
        pk = (u_long *)Map_prim_ptr;
        gte_stsxy3_ft4(pk);
        gte_stsxy3c(scr->sxy_60.w);
        gte_ldv0(&scr->u_88.face.vtx[3]);
        gte_rtps();
        scr->rgbc4_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        gte_stsxy(&pk[8]);
        gte_stsxy(&scr->sxy_60.w[3]);
        gte_stsz4(&sz0, &sz1, &sz2, &sz3);
        // On screen when a corner or the midpoint of a diagonal is.
        if ((x0 = Quad_sxy[0].vx) < 0x140U && (uint16)Quad_sxy[0].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x1 = Quad_sxy[1].vx) < 0x140U && (uint16)Quad_sxy[1].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x2 = Quad_sxy[2].vx) < 0x140U && (uint16)Quad_sxy[2].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x3 = Quad_sxy[3].vx) < 0x140U && (uint16)Quad_sxy[3].vy < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x0 + (sint16)x3) >> 1) < 0x140U && (uint32)((Quad_sxy[0].vy + Quad_sxy[3].vy) >> 1) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x1 + (sint16)x2) >> 1) >= 0x140U || (uint32)((Quad_sxy[1].vy + Quad_sxy[2].vy) >> 1) >= 0xF0U)
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
        if (BIT_TEST(flags, 31))
        {
            if (!BIT_TEST(flags, 27))
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
            if (BIT_TEST(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!BIT_TEST(flags, 28))
        {
            gte_ldrgb(&scr->rgbc4_54);
            gte_dpcs();
            scr->fog_48 = Quad_fog_tbl[(sz0 >> fog_sh) & 0x1F] << 16;
            gte_strgb(&scr->rgbc4_54);
        }
        if (BIT_TEST(flags, 31) && BIT_TEST(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (opz < 0)
        {
            if (Quad_near_z >= zmin)
            {
                goto cull;
            }
            if (BIT_TEST(flags, 24))
            {
                goto cull;
            }
            opz = -opz;
            if (!BIT_TEST(flags, 30))
            {
                scr->rgbc4_54 = 0x2C010101; // POLY_FT4, colour 0x010101
                sz0           = zmax;
                goto plain;
            }
        }
        if (BIT_TEST(flags, 29) && zmin >= 0x181)
        {
            goto plain;
        }
        if ((sint32)flags > 0 && zmax < Quad_near_z)
        {
            // The x range.
            if (Quad_sxy[0].vx < Quad_sxy[1].vx)
            {
                lo = Quad_sxy[0].vx;
                hi = Quad_sxy[1].vx;
            }
            else
            {
                lo = Quad_sxy[1].vx;
                hi = Quad_sxy[0].vx;
            }
            if (Quad_sxy[2].vx < Quad_sxy[3].vx)
            {
                zmin = Quad_sxy[2].vx;
                zmax = Quad_sxy[3].vx;
            }
            else
            {
                zmin = Quad_sxy[3].vx;
                zmax = Quad_sxy[2].vx;
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
                // The y range.
                if (Quad_sxy[0].vy < Quad_sxy[1].vy)
                {
                    lo = Quad_sxy[0].vy;
                    hi = Quad_sxy[1].vy;
                }
                else
                {
                    lo = Quad_sxy[1].vy;
                    hi = Quad_sxy[0].vy;
                }
                if (Quad_sxy[2].vy < Quad_sxy[3].vy)
                {
                    zmin = Quad_sxy[2].vy;
                    zmax = Quad_sxy[3].vy;
                }
                else
                {
                    zmin = Quad_sxy[3].vy;
                    zmax = Quad_sxy[2].vy;
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
                    scr->rgbc4_54 |= D_1F80007C;
                }
            }
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            // How far the quad is from a parallelogram.
            dx = ((sint16)scr->sxy_60.h[0].x + (sint16)scr->sxy_60.h[3].x - (sint16)scr->sxy_60.h[1].x - (sint16)scr->sxy_60.h[2].x) >> 1;
            dy = ((sint16)scr->sxy_60.h[0].y + (sint16)scr->sxy_60.h[3].y - (sint16)scr->sxy_60.h[1].y - (sint16)scr->sxy_60.h[2].y) >> 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        if (BIT_TEST(flags, 28))
        {
            scr->ot_3C = tail;
        }
        else
        {
            scr->ot_3C = Scratch_ot + (sz0 >> 3);
        }
        scr->u_88.face.uv[0] = sz2;
        scr->u_88.face.uv[1] = sz3;
        pk                   = quad_split();
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        goto next;
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5C;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (BIT_TEST(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((u_long)pk & w1) | w0;
        }
        else
        {
            slot  = Scratch_ot + (sz0 >> 3);
            pk[0] = w0 | *slot;
            *slot = (u_long)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc4_54;
        Map_prim_ptr++;
        goto next;
    cull:
        if (!BIT_TEST(flags, 28))
        {
            tail = NULL;
        }
    next:
        face += 4;
        tex += 2;
    }
}

// Same code as quad_split.
u_long *quad_split2(void)
{
    SVECTOR vec[3];
    sint32 clip;
    QUAD_WORK *scr;
    u_long *p;
    u_long *last;
    uint8 *idx;
    u_long clut;
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

    scr                = &Quad_work;
    Quad_work.rgbc3_50 = Quad_work.rgbc4_54 & ~0x08000000; // code 0x2C (POLY_FT4) to 0x24 (POLY_FT3)
    ax                 = Quad_vtx[0].vx;
    ay                 = Quad_vtx[0].vy;
    az                 = Quad_vtx[0].vz;
    bx                 = Quad_vtx[1].vx;
    by                 = Quad_vtx[1].vy;
    bz                 = Quad_vtx[1].vz;
    cx                 = Quad_vtx[2].vx;
    cy                 = Quad_vtx[2].vy;
    cz                 = Quad_vtx[2].vz;
    dx                 = Quad_vtx[3].vx;
    dy                 = Quad_vtx[3].vy;
    dz                 = Quad_vtx[3].vz;
    vec[0].vx          = (ax + bx) >> 1;
    vec[0].vy          = (ay + by) >> 1;
    vec[0].vz          = (az + bz) >> 1;
    vec[1].vx = mx = (ax + cx) >> 1;
    vec[1].vy = my = (ay + cy) >> 1;
    vec[1].vz = mz = (az + cz) >> 1;
    vec[2].vx = nx = (dx + bx) >> 1;
    vec[2].vy = ny = (dy + by) >> 1;
    vec[2].vz = nz = (dz + bz) >> 1;
    gte_ldv3c(vec);
    gte_rtpt();
    vec[0].vx = (mx + nx) >> 1;
    vec[0].vy = (my + ny) >> 1;
    vec[0].vz = (mz + nz) >> 1;
    vec[1].vx = (dx + cx) >> 1;
    vec[1].vy = (dy + cy) >> 1;
    vec[1].vz = (dz + cz) >> 1;
    gte_stsxy3(&scr->sxy_60.w[4], &scr->sxy_60.w[5], &scr->sxy_60.w[7]);
    gte_ldv3c(vec);
    gte_rtpt();
    Quad_work.u_88.uv.b[8]  = (Quad_work.u_88.uv.b[0] + Quad_work.u_88.uv.b[2]) >> 1;
    Quad_work.u_88.uv.b[9]  = (Quad_work.u_88.uv.b[1] + Quad_work.u_88.uv.b[3]) >> 1;
    Quad_work.u_88.uv.b[10] = (Quad_work.u_88.uv.b[0] + Quad_work.u_88.uv.b[4]) >> 1;
    Quad_work.u_88.uv.b[11] = (Quad_work.u_88.uv.b[1] + Quad_work.u_88.uv.b[5]) >> 1;
    Quad_work.u_88.uv.b[14] = (Quad_work.u_88.uv.b[2] + Quad_work.u_88.uv.b[6]) >> 1;
    Quad_work.u_88.uv.b[15] = (Quad_work.u_88.uv.b[3] + Quad_work.u_88.uv.b[7]) >> 1;
    Quad_work.u_88.uv.b[16] = (Quad_work.u_88.uv.b[4] + Quad_work.u_88.uv.b[6]) >> 1;
    Quad_work.u_88.uv.b[17] = (Quad_work.u_88.uv.b[5] + Quad_work.u_88.uv.b[7]) >> 1;
    Quad_work.u_88.uv.b[12] = (Quad_work.u_88.uv.b[8] + Quad_work.u_88.uv.b[16]) >> 1;
    Quad_work.u_88.uv.b[13] = (Quad_work.u_88.uv.b[11] + Quad_work.u_88.uv.b[15]) >> 1;
    gte_stsxy0(&scr->sxy_60.w[6]);
    gte_stsxy1(&scr->sxy_60.w[8]);
    clut = Quad_work.clut_58 | Quad_work.fog_48;
    idx  = Quad_work.idx_20;
    for (i = 0; i < 16; i += 4)
    {
        i0 = idx[i];
        i1 = idx[i + 1];
        i2 = idx[i + 2];
        i3 = idx[i + 3];
        Map_prim_ptr++;
        last    = (u_long *)(Map_prim_ptr - 1);
        last[0] = ((u_long)Map_prim_ptr & 0xFFFFFF) | 0x09000000;
        last[2] = scr->sxy_60.w[i0];
        last[4] = scr->sxy_60.w[i1];
        last[6] = scr->sxy_60.w[i2];
        last[8] = scr->sxy_60.w[i3];
        last[1] = scr->rgbc4_54;
        last[3] = scr->u_88.uv.h[i0] | clut;
        last[5] = scr->u_88.uv.h[i1] | scr->tpage_5C;
        last[7] = scr->u_88.uv.h[i2];
        last[9] = scr->u_88.uv.h[i3];
    }
    p = last;
    i = 16;
    do
    {
        i1 = idx[i];
        i2 = idx[i + 1];
        i3 = idx[i + 2];
        i += 3;
        gte_ldSXY012(scr->sxy_60.w[i1], scr->sxy_60.w[i2], scr->sxy_60.w[i3]);
        gte_nclip();
        gte_stopz(&clip);
        if (clip > 0)
        {
            Map_prim_ptr = (POLY_FT4 *)((POLY_FT3 *)Map_prim_ptr + 1);
            p            = (u_long *)((POLY_FT3 *)Map_prim_ptr - 1);
            p[0]         = ((u_long)Map_prim_ptr & 0xFFFFFF) | 0x07000000;
            p[2]         = scr->sxy_60.w[i1];
            p[4]         = scr->sxy_60.w[i2];
            p[6]         = scr->sxy_60.w[i3];
            p[1]         = scr->rgbc3_50;
            p[3]         = scr->u_88.uv.h[i1] | clut;
            p[5]         = scr->u_88.uv.h[i2] | scr->tpage_5C;
            p[7]         = scr->u_88.uv.h[i3];
        }
    } while (i < 28);
    addPrims(scr->ot_3C, last - 30, p);
    return last;
}

// Same code as map_blocks_draw.
void map_blocks_draw2(uint32 *rows, sint32 kind)
{
    QUAD_WORK *qw;
    uint32 *flags;
    MAP_BLOCK *b;
    MAP_BLOCK *row_end;
    MAP_BLOCK *end;
    sint32 bits;
    STG_MODEL *model;
    uint32 *lod;
    VECTOR pos;

    qw    = &Quad_work;
    flags = rows; // a copy of rows: the build needs it for the prologue's order
    b     = Map_blocks;
    end   = b + 0x800;
    *flags &= 0x7FFFFFFF;
    do
    {
        bits = *flags;
        if (bits != 0)
        {
            *flags  = 0;
            row_end = b + 0x20;
            do
            {
                if (bits < 0)
                {
                    model                   = (STG_MODEL *)(b->model & 0xFFFFFF);
                    *(long *)&qw->pos_40.vx = *(long *)&b->pos.vx;
                    *(long *)&qw->pos_40.vz = *(long *)&b->pos.vz;
                    gte_ldv0(&qw->pos_40);
                    gte_rt();
                    gte_stlvnl(&pos);
                    pos.vz >>= Scratch_scale_shift;
                    if (pos.vz > 0x1C20)
                    {
                        lod = &model->lod[2];
                    }
                    else if (pos.vz > 0xAF0)
                    {
                        lod = &model->lod[1];
                    }
                    else
                    {
                        lod = &model->lod[0];
                    }
                    if (qw->pos_40.pad == 0)
                    {
                        lod += 3;
                    }
                    lod = (uint32 *)*lod;
                    Map_block_draw_tbl[kind][(uint32)lod >> 31]((u_long *)((uint32)lod & 0xFFFFFF), pos.vz);
                }
                bits <<= 1;
                b++;
            } while (b < row_end);
        }
        else
        {
            b += 0x20;
        }
        flags++;
    } while (b < end);
}

// func_80023CF0 with func_80026B04.
void func_8002694C(u_long *model, sint32 z)
{
    uint32 count;

    count                    = *(uint8 *)model; // the header's low byte
    Quad_work.clut_tbl_C8[0] = model[1];
    Quad_work.clut_tbl_C8[1] = model[2];
    Quad_work.clut_tbl_C8[2] = model[3];
    model += count + 1;
    if (Scratch_cam_pos.vx < Quad_work.pos_40.vx)
    {
        if (Scratch_cam_pos.vz < Quad_work.pos_40.vz)
        {
            func_80026B04(&model[0]);
            func_80026B04(&model[6]);
        }
        else
        {
            func_80026B04(&model[4]);
            func_80026B04(&model[6]);
        }
    }
    else
    {
        if (Scratch_cam_pos.vz < Quad_work.pos_40.vz)
        {
            func_80026B04(&model[0]);
            func_80026B04(&model[2]);
        }
        else
        {
            func_80026B04(&model[2]);
            func_80026B04(&model[4]);
        }
    }
    func_80026B04(&model[8]);
    if (z <= Quad_work.part_z_BC)
    {
        func_80026B04(&model[10]);
    }
}

// func_80023E1C with func_80026B04.
void func_80026A78(u_long *model, sint32 z)
{
    u_long *part;
    uint32 i; // the header word, then the loop counter
    uint32 n;

    i                        = model[0];
    n                        = (i & 0x3F00) >> 7;
    Quad_work.clut_tbl_C8[0] = model[1];
    Quad_work.clut_tbl_C8[1] = model[2];
    Quad_work.clut_tbl_C8[2] = model[3];
    part                     = &model[(i & 0xFF) + 1];
    i                        = 0;
    do
    {
        func_80026B04(&part[i]);
        i += 2;
    } while (i < n);
}

// Same code as func_80023EA8.
void func_80026B04(u_long *model)
{
    QUAD_WORK *scr;
    SVECTOR unused; // unused: gives the target's frame size
    u_long *face;
    u_long *tex;
    u_long *tail;
    u_long *pk;
    u_long *slot;
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

    // The header words are reused for the CLUT word and the two loop constants.
    scr             = &Quad_work;
    w1              = model[1];
    w0              = model[0];
    left            = w1 >> 24;
    face            = (u_long *)((w1 & 0xFFFFFF) + 4);
    tex             = (u_long *)(w0 & 0xFFFFFF);
    shift           = Scratch_scale_shift;
    w1              = Quad_clut_tbl[(w0 >> 24) & 0xF];
    Quad_face_count = left;
    scr->clut_58    = w1 & 0xFFFF0000;
    scr->tpage_5C   = w1 << 16;
    sh              = (w0 >> 28) + shift;
    fog_sh          = shift + 9;
    ox              = scr->pos_40.vx << shift;
    oy              = scr->pos_40.vy << shift;
    oz              = scr->pos_40.vz << shift;
    w0              = 0x09000000;
    w1              = 0xFFFFFF;
    tail            = (u_long *)1; // not NULL: a first face linked after the previous one is drawn
    while (left != 0)
    {
        flags = face[-1];
        left--;
        if (BIT_TEST(flags, 28) && tail == NULL)
        {
            face += 4;
            tex += 2;
            continue;
        }
        sz1                      = face[0];
        scr->u_88.face.vtx[0].vx = (((sz1 << 24) >> 24) << sh) + ox;
        scr->u_88.face.vtx[0].vy = oy - (((sz1 >> 8) & 0xFF) << sh);
        scr->u_88.face.vtx[0].vz = (((sz1 << 8) >> 24) << sh) + oz;
        scr->u_88.face.vtx[1].vx = ((sz1 >> 24) << sh) + ox;
        sz1                      = face[1];
        scr->u_88.face.vtx[1].vy = oy - ((uint8)sz1 << sh);
        scr->u_88.face.vtx[1].vz = (((sz1 << 16) >> 24) << sh) + oz;
        scr->u_88.face.vtx[2].vx = (((sz1 << 8) >> 24) << sh) + ox;
        scr->u_88.face.vtx[2].vy = oy - (((sz1 >> 24) & 0xFF) << sh);
        sz1                      = face[2];
        scr->u_88.face.vtx[2].vz = (((sz1 << 24) >> 24) << sh) + oz;
        gte_ldv3c(scr->u_88.face.vtx);
        gte_rtpt();
        scr->u_88.face.vtx[3].vx = (((sz1 << 16) >> 24) << sh) + ox;
        scr->u_88.face.vtx[3].vy = oy - (((sz1 >> 16) & 0xFF) << sh);
        scr->u_88.face.vtx[3].vz = ((sz1 >> 24) << sh) + oz;
        gte_nclip();
        Quad_face_flags = flags;
        gte_stopz(&opz);
        if (opz <= 0)
        {
            if (!BIT_TEST(flags, 30))
            {
                goto cull;
            }
            opz = -opz;
        }
        pk = (u_long *)Map_prim_ptr;
        gte_stsxy3_ft4(pk);
        gte_stsxy3c(scr->sxy_60.w);
        gte_ldv0(&scr->u_88.face.vtx[3]);
        gte_rtps();
        scr->rgbc4_54 = (flags & 0x02FFFFFF) | 0x2C000000;
        gte_stsxy(&pk[8]);
        gte_stsxy(&scr->sxy_60.w[3]);
        gte_stsz4(&sz0, &sz1, &sz2, &sz3);
        // On screen when a corner or the midpoint of a diagonal is.
        if ((x0 = Quad_sxy[0].vx) < 0x140U && (uint16)Quad_sxy[0].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x1 = Quad_sxy[1].vx) < 0x140U && (uint16)Quad_sxy[1].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x2 = Quad_sxy[2].vx) < 0x140U && (uint16)Quad_sxy[2].vy < 0xF0U)
        {
            goto visible;
        }
        if ((x3 = Quad_sxy[3].vx) < 0x140U && (uint16)Quad_sxy[3].vy < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x0 + (sint16)x3) >> 1) < 0x140U && (uint32)((Quad_sxy[0].vy + Quad_sxy[3].vy) >> 1) < 0xF0U)
        {
            goto visible;
        }
        if ((uint32)(((sint16)x1 + (sint16)x2) >> 1) >= 0x140U || (uint32)((Quad_sxy[1].vy + Quad_sxy[2].vy) >> 1) >= 0xF0U)
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
        if (BIT_TEST(flags, 31))
        {
            if (!BIT_TEST(flags, 27))
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
            if (BIT_TEST(flags, 27))
            {
                sz0 = zmax - 0x10;
            }
            else
            {
                sz0 = (zmax + ((sz0 + sz1 + sz2 + sz3) >> 2)) >> 1;
            }
        }
        if (!BIT_TEST(flags, 28))
        {
            gte_ldrgb(&scr->rgbc4_54);
            gte_dpcs();
            scr->fog_48 = Quad_fog_tbl[(sz0 >> fog_sh) & 0x1F] << 16;
            gte_strgb(&scr->rgbc4_54);
        }
        if (BIT_TEST(flags, 31) && BIT_TEST(flags, 27))
        {
            sz0 = 0x3E80;
        }
        sz2 = tex[0];
        sz3 = tex[1];
        if (BIT_TEST(flags, 29) && zmin >= 0x181)
        {
            goto plain;
        }
        if (opz <= 0x200)
        {
            goto plain;
        }
        if (opz <= 0x800)
        {
            // How far the quad is from a parallelogram.
            dx = ((sint16)scr->sxy_60.h[0].x + (sint16)scr->sxy_60.h[3].x - (sint16)scr->sxy_60.h[1].x - (sint16)scr->sxy_60.h[2].x) >> 1;
            dy = ((sint16)scr->sxy_60.h[0].y + (sint16)scr->sxy_60.h[3].y - (sint16)scr->sxy_60.h[1].y - (sint16)scr->sxy_60.h[2].y) >> 1;
            if ((uint32)(dx + 3) < 7U && (uint32)(dy + 3) < 7U)
            {
                goto plain;
            }
        }
        if (BIT_TEST(flags, 28))
        {
            scr->ot_3C = tail;
        }
        else
        {
            scr->ot_3C = Scratch_ot + (sz0 >> 3);
        }
        scr->u_88.face.uv[0] = sz2;
        scr->u_88.face.uv[1] = sz3;
        pk                   = quad_split();
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        goto next;
    plain:
        pk[5] = ((uint32)sz2 >> 16) | scr->tpage_5C;
        pk[7] = sz3 & 0xFFFF;
        pk[9] = (uint32)sz3 >> 16;
        if (BIT_TEST(flags, 28))
        {
            pk[0] = w0 | *tail;
            *tail = ((u_long)pk & w1) | w0;
        }
        else
        {
            slot  = Scratch_ot + (sz0 >> 3);
            pk[0] = w0 | *slot;
            *slot = (u_long)pk & w1;
        }
        pk[3] = (sz2 & 0xFFFF) | scr->clut_58 | scr->fog_48;
        if (!BIT_TEST(flags, 28))
        {
            tail = pk;
        }
        pk[1] = scr->rgbc4_54;
        Map_prim_ptr++;
        goto next;
    cull:
        if (!BIT_TEST(flags, 28))
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

// Draws a ring of textured quads around (cx, cy), radius r0 to r1 in rsin-shaped steps, 16
// segments round, texturing each from the frame buffer just drawn (u/v range-checked before the
// byte stores, so they are full words).
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
            c0 = c;
            s0 = s;
            p  = Map_prim_ptr++;
            SET_TAG_LEN(p, 9);
            SET_CODE_RGB(p, 0x2C, 0x80, 0x80, 0x80);
            c     = D_800BAEB8[i * 4];
            s     = D_800BBD00[i * 4];
            p->x0 = ((c0 * out_prev) >> 12) + cx;
            p->y0 = ((s0 * out_prev) >> 12) + cy;
            p->x1 = ((c * out_prev) >> 12) + cx;
            p->y1 = ((s * out_prev) >> 12) + cy;
            p->x2 = ((c0 * out_cur) >> 12) + cx;
            p->y2 = ((s0 * out_cur) >> 12) + cy;
            p->x3 = ((c * out_cur) >> 12) + cx;
            p->y3 = ((s * out_cur) >> 12) + cy;
            if (p->x0 < 0xA0)
            {
                bias     = 0;
                p->tpage = (Dbl_buff_idx << 4) | 0x100;
                lim      = 0x100;
            }
            else
            {
                bias     = 0x40;
                p->tpage = (Dbl_buff_idx << 4) | 0x101;
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
                                            addPrim(&Disp_env_ptr->ot[2], p);
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

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_800981BC\n"
        ".globl D_800981D0\n"
        ".globl D_800981E0\n"
        ".globl D_800981EC\n"
        ".globl D_800981FC\n"
        ".globl D_80098210\n"
        ".globl D_80098220\n"
        ".globl D_80098234\n"
        ".globl D_80098238\n"
        ".globl D_8009824C\n"
        ".globl D_80098258\n"
        ".globl D_80098268\n"
        ".globl D_80098270\n"
        ".globl D_8009827C\n"
        ".globl D_8009828C\n"
        ".globl D_80098290\n"
        ".globl D_8009829C\n"
        ".globl D_800982BC\n"
        ".globl D_800982C8\n"
        ".globl D_800982D0\n"
        ".globl D_800982D8\n"
        ".globl D_800982E4\n"
        ".globl D_800982EC\n"
        ".globl D_800982F8\n"
        ".globl D_8009830C\n"
        ".globl D_80098314\n"
        ".globl D_80098324\n");
