#include "common.h"
#include "code_8005C258.h"
#include "cd.h"
#include "code_80037534.h"
#include "code_800425FC.h"
#include "display.h"
#include "fastmem.h"
#include "game.h"
#include "pad.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"
#include "sub_scrn.h"

// Small data (.sdata 0x80098004-0x80098038): reached through $gp in this file.
sint32 D_80098004    = 0;
sint32 D_80098008    = 0;
sint32 D_8009800C    = 0;
sint32 D_80098010    = 0;
sint32 D_80098014    = 8;
sint32 D_80098018    = 0x60;
sint32 D_8009801C    = 0;
uint8 D_80098020[12] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5}; // life_gauge_draw: blink sprite per anim_8
uint8 D_8009802C[8]  = {0, 1, 1, 2, 2, 3, 3, 4};             // life_gauge_draw: face per timer_9 (flag_D 3)
sint32 D_80098034    = 6;

// Small uninitialized statics (.sbss 0x800986F8-0x80098700).
static sint16 D_800986F8[2];
static sint16 D_800986FC[2];

// Pool variables (stay in assembly), reached through $gp here.
sint32 D_8009878C; // arg0 of func_8005DC10's last match
sint32 D_80098794; // index of that D_8008D19C record
uint8 *D_8009882C; // its hidden_4
uint32 D_80098AF0; // open slots of 2-4
sint32 D_80098B18; // gauges drawn this frame: bit 0 life_gauge_draw, 1 weapon_gauge_draw, 2 the others

// Called only from this file, ahead of their definitions.
void func_8005D298(SLOT_SPRITE *spr, sint16 x, sint16 y, uint16 size);
void func_8005D39C(SLOT_SPRITE *spr, sint16 x, sint16 y, uint16 size, sint32 color);
void func_8005D4F8(void);
void area_map_explore(void);
void area_map_corner_draw(void);
void func_8005C720(SLOT_WORK *wp);
void func_8005C868(SLOT_WORK *wp);
void func_8005C978(SLOT_WORK *wp);
void life_gauge_draw(SLOT_WORK *wp);
void weapon_gauge_draw(SLOT_WORK *wp);
void owner_life_gauge_draw(SLOT_WORK *wp);
void func_8005D0FC(SLOT_WORK *wp);
void area_map_draw(DVECTOR *pos, DVECTOR *size, DVECTOR *cell, RECT *rect);
void func_8005E9F8(RECT *rect);
void func_8005EAA8(RECT *rect);

void func_8005C258(void)
{
    Mem_clear(D_800BBD78, (uint8 *)D_800BBD78 + 0xD4);
    D_800BBD78[0].state_0 = 3;
    D_800BBD9C            = 3;
    D_80098AF0            = 0;
    D_8009800C            = 5;
    Scene_work.unk00      = 0;
    D_80098008            = 0;
    D_8009801C            = 0;
}

// Runs the gauges each frame. D_8009800C slides them in from the screen edges over 10 frames (1)
// when Scene_work.unk00 returns to 0, out again (3, 4) when it changes from nonzero, and gives
// them their default places back (5); then calls each open slot's handler and draw function.
void Gauge_update(void)
{
    sint32 off;
    uint32 i;

    func_8005C868(&D_800BBD78[1]);
    if (D_800BBD94 > 0)
    {
        D_800BBD94--;
    }
    if (D_800BBD96 > 0)
    {
        D_800BBD96--;
    }
    D_80098B18 = 0;
    if (D_80098008 != Scene_work.unk00)
    {
        if (D_80098008 != 0)
        {
            D_8009800C = 3;
        }
        else
        {
            D_8009800C = 0;
        }
    }
    D_80098008 = Scene_work.unk00;
    switch (D_8009800C)
    {
        case 0:
        default:
            D_80098010              = 10;
            D_8009800C              = 1;
            D_800BBD78[0].has_pos_E = 1;
            D_800BBD78[1].has_pos_E = 1;
            D_800BBD78[2].has_pos_E = 1;
            D_800BBD78[3].has_pos_E = 1;
            D_800BBD78[4].has_pos_E = 1;
            D_800BBD78[5].has_pos_E = 1;
            D_800BBD78[0].x_14      = 8;
            D_800BBD78[0].y_16      = 0x88;
            D_800BBD78[1].x_14      = 0x118;
            D_800BBD78[1].y_16      = 0xBE;
            D_800BBD78[2].x_14      = 0x120;
            D_800BBD78[3].x_14      = 0x120;
            D_800BBD78[2].y_16      = 0x10;
            D_800BBD78[3].y_16      = 0x10;
            D_800BBD78[4].y_16      = 0x10;
            D_800BBD78[5].y_16      = 0x18;
            D_800BBD78[4].x_14      = 0x120;
            D_800BBD78[5].x_14      = 0;
            D_80098014              = 8;
            D_80098018              = 0x60;
            D_8009801C              = 1;
            break;
        case 1:
            if (D_80098010-- != 0)
            {
                off                = (10 - D_80098010) * 8;
                D_800BBD78[0].x_14 = 8 - off;
                D_800BBD78[1].x_14 = off + 0x118;
                D_800BBD78[2].x_14 = off + 0x120;
                D_800BBD78[3].x_14 = off + 0x120;
                D_800BBD78[4].x_14 = off + 0x120;
                D_800BBD78[5].x_14 = -off;
                D_80098014         = 8 - off;
            }
            else
            {
                D_8009800C = 2;
            }
            break;
        case 3:
            D_80098010              = 10;
            off                     = 0x50;
            D_8009800C              = 4;
            D_800BBD78[0].has_pos_E = 1;
            D_800BBD78[1].has_pos_E = 1;
            D_800BBD78[2].has_pos_E = 1;
            D_800BBD78[3].has_pos_E = 1;
            D_800BBD78[4].has_pos_E = 1;
            D_800BBD78[5].has_pos_E = 1;
            D_800BBD78[0].x_14      = 8 - off;
            D_800BBD78[0].y_16      = 0x88;
            D_800BBD78[1].x_14      = off + 0x118;
            D_800BBD78[1].y_16      = 0xBE;
            D_800BBD78[2].x_14      = off + 0x120;
            D_800BBD78[2].y_16      = 0x10;
            D_800BBD78[3].x_14      = off + 0x120;
            D_800BBD78[3].y_16      = 0x10;
            D_800BBD78[4].y_16      = 0x10;
            D_800BBD78[4].x_14      = off + 0x120;
            D_800BBD78[5].x_14      = -off;
            D_800BBD78[5].y_16      = 0x18;
            D_80098014              = 8 - off;
            break;
        case 4:
            if (D_80098010-- != 0)
            {
                off                = D_80098010 * 8;
                D_800BBD78[0].x_14 = 8 - off;
                D_800BBD78[1].x_14 = off + 0x118;
                D_800BBD78[2].x_14 = off + 0x120;
                D_800BBD78[3].x_14 = off + 0x120;
                D_800BBD78[4].x_14 = off + 0x120;
                D_800BBD78[5].x_14 = -off;
                D_80098014         = 8 - off;
            }
            else
            {
                D_8009800C = 5;
            }
            break;
        case 5:
            D_800BBD78[0].has_pos_E = 0;
            D_800BBD78[1].has_pos_E = 0;
            D_800BBD78[2].has_pos_E = 0;
            D_800BBD78[3].has_pos_E = 0;
            D_800BBD78[4].has_pos_E = 0;
            D_800BBD78[5].has_pos_E = 0;
            D_8009801C              = 0;
            break;
        case 2:
            return;
    }
    if (D_800BBD78[0].state_0 & 1)
    {
        func_8005C720(&D_800BBD78[0]);
    }
    if (D_800BBD78[0].state_0 & 2)
    {
        life_gauge_draw(&D_800BBD78[0]);
    }
    if (Player_work[0].unk171 != 0 && (D_800BBD78[1].state_0 & 2))
    {
        weapon_gauge_draw(&D_800BBD78[1]);
    }
    for (i = 0; i < 3; i++)
    {
        if (D_800BBD78[i + 2].state_0 & 1)
        {
            func_8005C978(&D_800BBD78[i + 2]);
        }
        if (D_800BBD78[i + 2].state_0 & 2)
        {
            owner_life_gauge_draw(&D_800BBD78[i + 2]);
        }
    }
    if (D_800BBD78[5].state_0 & 2)
    {
        func_8005D0FC(&D_800BBD78[5]);
    }
}

void func_8005C720(SLOT_WORK *wp)
{
    D_8008D7B4[wp->routine_4](wp);
}

// Slot 0's handler 0: while flag_D is 1 or 2, counts frames (x_18), frames with kind_C set
// (idle_A) and frames the player stands still (still_B); calls func_8005D528 once any runs out.
void func_8005C75C(SLOT_WORK *wp)
{
    PL_WORK *pl;

    if (wp->count_F == 0)
    {
        pl = &Player_work[0];
        if ((uint8)(wp->flag_D - 1) < 2)
        {
            wp->x_18++;
            if (wp->kind_C != 0)
            {
                wp->idle_A++;
            }
            else
            {
                wp->idle_A = 0;
            }
            // vx and vy compared as one word
            if (*(sint32 *)&pl->pos.vx == *(sint32 *)&pl->old.vx && pl->pos.vz == pl->old.vz)
            {
                wp->still_B++;
            }
            else
            {
                wp->still_B = 0;
            }
        }
        if (wp->x_18 >= 150 || wp->still_B >= 90 || (wp->idle_A >= 60 && wp->still_B >= 60))
        {
            func_8005D528();
        }
    }
}

void func_8005C858(void)
{
}

void func_8005C860(void)
{
}

void func_8005C868(SLOT_WORK *wp)
{
    D_8008D7C0[wp->routine_4](wp);
}

void func_8005C8A4(SLOT_WORK *wp)
{
    PL_WORK *pl;
    sint32 max;
    sint32 wait;

    pl   = &Player_work[0];
    max  = Player_weapon_bullet_calc(pl, 1);
    wait = (pl->rec[Player_work[0].unk171].idx[1] != 7) ? 0x11 : 0;
    if (Player_work[0].unk171 == 1)
    {
        if (Player_work[0].rec[1].val == 0)
        {
            if (max < 2)
            {
                return;
            }
        }
        else if (max <= 0)
        {
            return;
        }
        wp->count_F++;
        if (wp->count_F < wait)
        {
            return;
        }
        wp->count_F             = 0;
        pl->rec[pl->unk171].val = max;
    }
}

void func_8005C978(SLOT_WORK *wp)
{
    D_8008D7C4[wp->routine_4](wp);
}

void func_8005C9B4(void)
{
}

// Draws the player's life gauge: a column as tall as life_max with one cell per 16 life (D_8008D5E8,
// D_8008D5FC for the rest), a blinking sprite while kind_C is set (once, when it is 1), and a face
// picked by flag_D (2 and 3 animate it through timer_9, ending at 1 and 0).
#ifdef NON_MATCHING
// Only difference: a nop after case 3's `lb v0,9(s0)`. maspsx pre-scans the whole file, sees
// D_8009802C in this file's .sdata and expands the indexed load as a $gp access (which reads v0
// first); the target has none, as for an extern table (D_8008D7C8 in case 2).
void life_gauge_draw(SLOT_WORK *wp)
{
    sint32 x;
    sint32 y;
    sint32 face;
    sint32 len;
    sint32 life;
    sint32 rest;
    uint32 n;
    uint32 i;

    D_80098B18 |= 1;
    if (wp->has_pos_E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 8;
        y = 136;
    }
    if (++wp->anim_8 >= 12)
    {
        wp->anim_8 = 0;
    }
    if (wp->kind_C != 0)
    {
        func_8005D298(&D_8008D570[D_80098020[wp->anim_8]], x, y, 0);
    }
    if (wp->kind_C == 1)
    {
        wp->kind_C = 0;
    }
    switch (wp->flag_D)
    {
        case 0:
            face = 0;
            break;
        case 1:
            face = 4;
            break;
        case 2:
            face = D_8008D7C8[wp->timer_9];
            if (--wp->timer_9 == 0)
            {
                wp->flag_D = 1;
            }
            break;
        case 3:
            face = D_8009802C[wp->timer_9];
            if (--wp->timer_9 == 0)
            {
                wp->flag_D = 0;
            }
            break;
        default:
            face = 0;
            break;
    }
    len = (Player_work[0].life_max >> 4) * 5 - 10;
    func_8005D298(&D_8008D37C[face][0], x, y - len, 0);
    func_8005D298(&D_8008D37C[face][2], x, y, 0);
    func_8005D298(&D_8008D37C[face][1], x, y - len, D_8008D37C[face][1].w | (len << 8));
    func_8005D298(&D_8008D37C[face][3], x, y, 0);
    life = Player_work[0].life;
    if (life > 0)
    {
        n    = life >> 4;
        rest = life - (n << 4);
        for (i = 0; i < n; i++)
        {
            func_8005D298(&D_8008D5E8, x, y - i * 5, 0);
        }
        if (rest != 0)
        {
            func_8005D298(&D_8008D5FC, x, y - n * 5, 0);
        }
    }
    func_8005D298(&D_8008D37C[face][4], x, y - len, ((len + 16) << 8) | 16);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", life_gauge_draw);
#endif

// Draws the energy gauge of the player's special weapon (rec[weapon_right_no]): its count out of its
// maximum, one pixel per 1 << shift_8 units, rising from (x, y); an unlimited weapon (0x7FFF)
// gets a sprite of its own.
#ifdef NON_MATCHING
// Only difference: the target sets D_80089EAC's address and 0x7FFF into a2/a3 at the top of the
// block after the first call; here combine folds the address into the load (lui/%lo).
void weapon_gauge_draw(SLOT_WORK *wp)
{
    RECT rect; // unused (the frame has room for it)
    PL_WORK *pl;
    sint32 x;
    sint32 y;
    sint32 dy;
    sint32 max;
    sint32 fill;
    sint32 shift;
    sint32 level;
    TBL_ROW **tbl;
    sint32 lim;

    D_80098B18 |= 2;
    pl = &Player_work[0];
    if (wp->has_pos_E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 280;
        y = 190;
    }
    dy = 0;
    if (wp->flag_D != 0)
    {
        dy = wp->y_1A;
    }
    func_8005D298(&D_8008D610, x, y, 0);
    tbl   = D_80089EAC;
    lim   = 0x7FFF;
    shift = D_80089A84[pl->weapon_right_no].shift_8;
    level = pl->rec[pl->weapon_right_no].val - 1;
    max   = tbl[pl->weapon_right_no][pl->rec[pl->weapon_right_no].idx[1]].val[1];
    fill  = ((level + ((1 << shift) >> 16)) << 16) >> shift;
    if (max == lim)
    {
        func_8005D298(&D_8008D674, x, y + dy, 0);
    }
    else
    {
        max = (max << 16) >> shift;
        if (fill != 0)
        {
            func_8005D298(&D_8008D638[0], x, y + dy - fill + 1, D_8008D638[0].w | ((fill - 1) << 8));
            func_8005D298(&D_8008D638[1], x, y + dy - fill, 0);
        }
        func_8005D298(&D_8008D660, x, y + dy - max, D_8008D660.w | (max << 8));
    }
    func_8005D298(&D_8008D624, x, y + dy - max, 0);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", weapon_gauge_draw);
#endif

// Draws the owner's life out of life_max as a gauge growing leftwards from its right end, one
// pixel per 1 << (kind_C >> 4) units, in sprite set kind_C & 0xF; the filled part is drawn
// semi-transparent in color_10.
void owner_life_gauge_draw(SLOT_WORK *wp)
{
    sint32 shift;
    sint32 mask;
    sint32 len;
    sint32 full;
    sint32 set;
    sint32 x;
    sint32 y;

    D_80098B18 |= 4;
    shift = wp->kind_C >> 4;
    mask  = (1 << shift) - 1;
    if (wp->owner_20->life > 0)
    {
        len = (uint32)(wp->owner_20->life + mask) >> shift;
    }
    else
    {
        len = 0;
    }
    full = wp->owner_20->life_max >> shift;
    set  = wp->kind_C & 0xF;
    if (wp->has_pos_E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 288;
        y = 16;
    }
    if (wp->flag_D != 0)
    {
        x += wp->x_18;
        y += wp->y_1A;
    }
    func_8005D298(&D_8008D688[set][0], x, y, 0);
    func_8005D298(&D_8008D688[set][1], x - full, y, 0);
    if (len > 0)
    {
        func_8005D39C(&D_8008D688[set][3], x - len + 1, y, (D_8008D688[set][3].h << 8) | len, wp->color_10);
        func_8005D39C(&D_8008D688[set][4], x - len, y, (D_8008D688[set][4].h << 8) | 1, wp->color_10);
    }
    func_8005D298(&D_8008D688[set][2], x - full, y, (D_8008D688[set][2].h << 8) | full);
}

// Draws the gauge of Game_work.gauge_05C out of gauge_max_05E, one pixel per 1 << kind_C units.
void func_8005D0FC(SLOT_WORK *wp)
{
    sint32 shift;
    sint32 len;
    sint32 full;
    sint32 mask;
    sint32 x;
    sint32 y;

    D_80098B18 |= 4;
    shift = wp->kind_C;
    mask  = (1 << shift) - 1;
    if (Game_work.gauge_05C > 0)
    {
        len = (uint32)(Game_work.gauge_05C + mask) >> shift;
    }
    else
    {
        len = 0;
    }
    full = Game_work.gauge_max_05E >> shift;
    if (wp->has_pos_E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 0;
        y = 24;
    }
    if (wp->flag_D != 0)
    {
        x += wp->x_18;
        y += wp->y_1A;
    }
    func_8005D298(&D_8008D750[0], x, y, 0);
    func_8005D298(&D_8008D750[1], x + full, y, 0);
    if (len > 0)
    {
        func_8005D298(&D_8008D750[3], x - 1, y, (D_8008D750[3].h << 8) | len);
        func_8005D298(&D_8008D750[4], x + len - 1, y, (D_8008D750[4].h << 8) | 1);
    }
    func_8005D298(&D_8008D750[2], x, y, (D_8008D750[2].h << 8) | full);
}

// Draws spr at (x, y) as a POLY_FT4 into OT 2; size, when nonzero, is the size on screen (w in
// the low byte, h in the high one).
void func_8005D298(SLOT_SPRITE *spr, sint16 x, sint16 y, uint16 size)
{
    POLY_FT4 *p;
    sint32 dx;
    sint32 dy;
    sint32 w;
    sint32 h;
    sint32 ww;
    sint32 hh;
    uint8 u;
    uint8 v;

    dx = spr->x_off;
    dy = spr->y_off;
    w  = spr->w;
    h  = spr->h;
    if (size != 0)
    {
        ww = size & 0xFF;
        hh = size >> 8;
    }
    else
    {
        ww = w;
        hh = h;
    }
    u            = spr->u;
    v            = spr->v;
    p            = Map_prim_ptr;
    Map_prim_ptr = p + 1;
    SET_TAG_LEN(p, 9);
    *(u_long *)&p->r0 = spr->color;
    *(u_long *)&p->u0 = *(u_long *)&spr->u;
    p->tpage          = spr->tpage;
    p->x0             = x + dx;
    p->y0             = y + dy;
    p->x1             = x + dx + ww;
    p->y1             = y + dy;
    p->x2             = x + dx;
    p->y2             = y + dy + hh;
    p->x3             = x + dx + ww;
    p->y3             = y + dy + hh;
    p->u1             = u + w;
    p->v1             = v;
    p->u2             = u;
    p->v2             = v + h;
    p->u3             = u + w;
    p->v3             = v + h;
    addPrim(&Disp_env_ptr->ot[2], p);
}

// func_8005D298 with the colour given (0xBBGGRR), drawn semi-transparent.
void func_8005D39C(SLOT_SPRITE *spr, sint16 x, sint16 y, uint16 size, sint32 color)
{
    POLY_FT4 *p;
    sint32 dx;
    sint32 dy;
    sint32 w;
    sint32 h;
    sint32 ww;
    sint32 hh;
    uint8 u;
    uint8 v;

    dx = spr->x_off;
    dy = spr->y_off;
    w  = spr->w;
    h  = spr->h;
    if (size != 0)
    {
        ww = size & 0xFF;
        hh = size >> 8;
    }
    else
    {
        ww = w;
        hh = h;
    }
    u            = spr->u;
    v            = spr->v;
    p            = Map_prim_ptr;
    Map_prim_ptr = p + 1;
    SET_TAG_LEN(p, 9);
    *(u_long *)&p->r0 = (color & 0xFFFFFF) | 0x2C000000; // semi-transparent POLY_FT4
    *(u_long *)&p->u0 = *(u_long *)&spr->u;
    p->tpage          = spr->tpage;
    p->x0             = x + dx;
    p->y0             = y + dy;
    p->x1             = x + dx + ww;
    p->y1             = y + dy;
    p->x2             = x + dx;
    p->y2             = y + dy + hh;
    p->x3             = x + dx + ww;
    p->y3             = y + dy + hh;
    p->u1             = u + w;
    p->v1             = v;
    p->u2             = u;
    p->v2             = v + h;
    p->u3             = u + w;
    p->v3             = v + h;
    addPrim(&Disp_env_ptr->ot[2], p);
}

void func_8005D4C0(void)
{
    D_800BBD84[0] = 1;
}

void func_8005D4D4(void)
{
    D_800BBD84[0] = 2;
}

void func_8005D4E8(void)
{
    D_800BBD84[0] = 0;
}

void func_8005D4F8(void)
{
    if (D_800BBD84[1] == 0)
    {
        D_800BBD84[1] = 2;
        D_800BBD81    = 0x1C;
    }
}

void func_8005D528(void)
{
    if (D_800BBD84[3] != 1)
    {
        if ((uint8)(D_800BBD84[1] - 1) < 2)
        {
            D_800BBD84[1] = 3;
            D_800BBD81    = 6;
        }
    }
}

// Opens a free slot of 2-4 for owner, at (x, y).
void func_8005D574(void *owner, sint16 x, sint16 y, uint8 kind)
{
    uint32 i;

    if (D_80098AF0 < 3)
    {
        for (i = 0; i < 3; i++)
        {
            if (D_800BBD78[i + 2].state_0 == 0)
            {
                goto found;
            }
        }
    }
    return;

found:
    D_80098AF0++;
    D_800BBD78[i + 2].x_18     = x;
    D_800BBD78[i + 2].y_1A     = y;
    D_800BBD78[i + 2].owner_20 = owner;
    D_800BBD78[i + 2].state_0  = 3;
    D_800BBD78[i + 2].kind_C   = kind;
    D_800BBD78[i + 2].flag_D   = 1;
}

// func_8005D574 with a colour word.
void func_8005D620(void *owner, sint16 x, sint16 y, uint8 kind, uint32 color)
{
    uint32 i;

    if (D_80098AF0 < 3)
    {
        for (i = 0; i < 3; i++)
        {
            if (D_800BBD78[i + 2].state_0 == 0)
            {
                goto found;
            }
        }
    }
    return;

found:
    D_80098AF0++;
    D_800BBD78[i + 2].x_18    = x;
    D_800BBD78[i + 2].y_1A    = y;
    D_800BBD78[i + 2].state_0 = 3;
    D_800BBD78[i + 2].flag_D  = 1;
    D_800BBD78[i + 2].kind_C  = kind;
    // Indexed from slot 2: the target recomputes i * 0x24 here instead of reusing the offset.
    (&D_800BBD78[2])[i].color_10 = color;
    D_800BBD78[i + 2].owner_20   = owner;
}

// Closes the slot of 2-4 that owner opened.
void func_8005D6E8(void *owner)
{
    uint32 i;
    uint32 slot;

    for (i = 0, slot = 2; i < 3; i++, slot++)
    {
        if (D_800BBD78[slot].state_0 != 0 && D_800BBD78[slot].owner_20 == owner)
        {
            goto found;
        }
    }
    return;

found:
    D_80098AF0--;
    ((uint32 *)&D_800BBD78[slot])[0] = 0;
    ((uint32 *)&D_800BBD78[slot])[1] = 0;
    ((uint32 *)&D_800BBD78[slot])[2] = 0;
    ((uint32 *)&D_800BBD78[slot])[3] = 0;
    ((uint32 *)&D_800BBD78[slot])[4] = 0;
    ((uint32 *)&D_800BBD78[slot])[5] = 0;
    ((uint32 *)&D_800BBD78[slot])[6] = 0;
    ((uint32 *)&D_800BBD78[slot])[7] = 0;
}

// Closes slots 2-4 (their first eight words).
void func_8005D7C0(void)
{
    uint32 i;

    D_80098AF0 = 0;
    for (i = 0; i < 3; i++)
    {
        ((uint32 *)&D_800BBD78[i + 2])[0] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[1] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[2] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[3] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[4] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[5] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[6] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[7] = 0;
    }
}

void func_8005D844(sint16 a, sint16 b, uint8 c)
{
    D_800BBE2C = 3;
    D_800BBE44 = a;
    D_800BBE46 = b;
    D_800BBE38 = c;
    D_800BBE39 = 1;
}

void func_8005D87C(void)
{
    *(uint32 *)&D_800BBE2C = 0;
    D_800BBE30             = 0;
    D_800BBE34             = 0;
    *(uint32 *)&D_800BBE38 = 0;
    D_800BBE3C             = 0;
    D_800BBE40             = 0;
    *(uint32 *)&D_800BBE44 = 0;
    D_800BBE48             = 0;
}

sint32 func_8005D8C4(sint32 arg0)
{
    if (D_800BBD94 > 0)
    {
    fail:
        return 0;
    }
    switch (D_800BBD84[1])
    {
        case 0:
        case 3:
            if (arg0 == 0)
            {
                goto fail;
            }
            func_8005D4F8();
            D_800BBD82 = 0;
            D_800BBD83 = 0;
            D_800BBD90 = 0;
            break;
    }
    return 1;
}

sint32 func_8005D938(void)
{
    if (D_800BBD94 > 0)
    {
        return 0;
    }
    return D_800BBD84[3];
}

sint32 func_8005D95C(void)
{
    return D_800BBD84[3];
}

void func_8005D96C(void)
{
}

void func_8005D974(void)
{
}

void func_8005D97C(void)
{
    D_800BBDAB = 0;
}

void func_8005D98C(void)
{
    if (D_800BBD94 <= 0)
    {
        D_800BBD84[3] = 1;
        func_8005D4F8();
    }
}

void func_8005D9C4(void)
{
    D_800BBD84[3] = 0;
    func_8005D528();
}

void func_8005D9EC(void)
{
    Player_work[0].life = Player_work[0].life_max;
    func_8005D9C4();
}

sint32 func_8005DA1C(sint32 arg0)
{
    if (arg0 != 0 && D_800BBD84[3] != 0)
    {
        D_800BBD84[3] = 0;
        D_800BBD84[1] = 3;
        D_800BBD81    = 6;
        return 0;
    }
    return D_800BBD84[3] == 0;
}

sint32 func_8005DA78(sint32 arg0)
{
    sint16 cur;
    sint16 target;

    if (arg0 != 0)
    {
        cur    = Player_work[0].life;
        target = Player_work[0].life_max;
        if (cur + 2 >= target)
        {
            Player_work[0].life = target;
            return 1;
        }
        Player_work[0].life = cur + 2;
        return 0;
    }
    return Player_work[0].life == Player_work[0].life_max;
}

// Steps the active weapon's count (rec[tbl_sel].val) by 0x10 up to its maximum, when arg0 is
// set; answers whether it is full (always, for an unlimited weapon).
sint32 Player_weapon_bullet_fill(sint32 arg0)
{
    PL_WORK *pl;
    sint32 max;
    sint16 cur;

    pl  = &Player_work[0];
    max = Player_weapon_bullet_calc(pl, Player_work[0].tbl_sel);
    if (max == 0x7FFF)
    {
        return 1;
    }
    if (arg0 != 0)
    {
        cur = pl->rec[Player_work[0].tbl_sel].val;
        if (cur + 0x10 >= max)
        {
            pl->rec[Player_work[0].tbl_sel].val = max;
            return 1;
        }
        pl->rec[Player_work[0].tbl_sel].val = cur + 0x10;
        return 0;
    }
    return pl->rec[Player_work[0].tbl_sel].val == max;
}

void func_8005DBB4(sint32 mode)
{
    sint32 i;

    if (mode == 0)
    {
        for (i = 0; i < 0x280; i++)
        {
            D_800BC9B8[i] = -1;
        }
    }
    else
    {
        Mem_copy32(&Cd_ring_buf[0][0x1280], D_800BC9B8, sizeof(D_800BC9B8) / 32);
    }
}

// Looks up the current stage and area in D_8008D19C; on a match, keeps arg0, the record's index
// and its hidden_4, and sets D_80098004 to 3.
void func_8005DC10(sint32 arg0)
{
    sint32 i;

    D_80098004 = 0;
    if (arg0 != 0)
    {
        for (i = 0; i < 0x40; i++)
        {
            if (D_8008D19C[i].stage_no == 0xFF)
            {
                return;
            }
            if (D_8008D19C[i].stage_no == Game_work.stage_no && D_8008D19C[i].area_no == Game_work.area_no)
            {
                D_80098004 = 3;
                D_8009878C = arg0;
                D_80098794 = i;
                D_8009882C = D_8008D19C[i].hidden_4;
                return;
            }
        }
    }
}

void func_8005DCB4(void)
{
    area_map_explore();
    area_map_corner_draw();
}

// Marks the 3x3 map cells around the player as explored (clears their D_8009882C bits).
void area_map_explore(void)
{
    CELL_OFS dx;
    CELL_OFS dz;
    uint32 width;
    uint32 height;
    sint32 px;
    sint32 pz;
    sint32 x;
    sint32 z;
    sint32 i;
    uint8 *p;

    dx = D_80098038;
    dz = D_80098044;
    if (D_80098004 & 1)
    {
        width  = D_8008D19C[D_80098794].width;
        px     = (-D_8008D19C[D_80098794].x + Player_work[0].pos.vx) >> 9;
        height = D_8008D19C[D_80098794].height;
        pz     = (-D_8008D19C[D_80098794].z + Player_work[0].pos.vz) >> 9;
        for (i = 0; i < 9; i++)
        {
            x = px + dx.d[i];
            z = pz + dz.d[i];
            if ((uint32)x < width && (uint32)z < height)
            {
                p = D_8009882C + ((sint32)(width * z + x) >> 3);
                *p &= ~(0x80 >> (x & 7));
            }
        }
    }
}

// Draws the 11x11 cells of the area map around the player in a 54x54 box at the corner
// (D_80098014, D_80098018), over a dark square.
void area_map_corner_draw(void)
{
    DVECTOR pos;
    DVECTOR size;
    DVECTOR cell;
    RECT rect;
    sint32 room_x;
    sint32 room_z;

    if (Game_work.unk059 == 0 && (D_80098004 & 2))
    {
        if (D_8009801C == 0)
        {
            D_80098014 = 8;
            D_80098018 = 0x60;
        }
        room_x     = D_8008D19C[D_80098794].x;
        room_z     = D_8008D19C[D_80098794].z;
        pos.vx     = D_80098014;
        cell.vx    = ((Player_work[0].pos.vx - room_x) >> 9) - 5;
        cell.vy    = ((Player_work[0].pos.vz - room_z) >> 9) - 5;
        size.vx    = 11;
        pos.vy     = D_80098018;
        size.vy    = 11;
        rect.w     = 54;
        rect.h     = 54;
        rect.x     = pos.vx + 6;
        D_80098034 = 6;
        rect.y     = pos.vy - 60;
        area_map_draw(&pos, &size, &cell, &rect);
        func_8005E9F8(&rect);
    }
}

void func_8005DF3C(void)
{
    D_800986F8[0] = 0;
    D_800986FC[0] = 0;
}

// Draws the whole area map centred on the screen (6 pixels a cell) over func_8005EAA8's
// background; the d-pad scrolls it by up to 32 pixels each way (D_800986F8, D_800986FC).
void Area_map_screen_draw(void)
{
    DVECTOR pos;
    DVECTOR size;
    DVECTOR cell;
    RECT rect;
    uint16 pad;
    uint32 scale;
    uint32 w;
    uint32 h;
    uint32 mw;
    uint32 mh;

    if (D_80098004 & 2)
    {
        pad = PAD_NOW(Joy1);
        if (pad & PAD_UP)
        {
            D_800986FC[0] -= 2;
        }
        if (pad & PAD_DOWN)
        {
            D_800986FC[0] += 2;
        }
        if (pad & PAD_LEFT)
        {
            D_800986F8[0] -= 2;
        }
        if (pad & PAD_RIGHT)
        {
            D_800986F8[0] += 2;
        }
        if (D_800986F8[0] < -32)
        {
            D_800986F8[0] = -32;
        }
        if (D_800986F8[0] > 32)
        {
            D_800986F8[0] = 32;
        }
        if (D_800986FC[0] < -32)
        {
            D_800986FC[0] = -32;
        }
        if (D_800986FC[0] > 32)
        {
            D_800986FC[0] = 32;
        }
        scale      = 6;
        w          = 320 / scale;
        h          = 240 / scale;
        D_80098034 = scale;
        size.vx = mw = D_8008D19C[D_80098794].width;
        size.vy = mh = D_8008D19C[D_80098794].height;
        cell.vx      = 0;
        cell.vy      = 0;
        rect.x       = 0;
        rect.y       = 0;
        rect.w       = 320;
        rect.h       = 240;
        pos.vx       = D_800986F8[0] + (((w - mw) * scale >> 1) + 1);
        pos.vy       = D_800986FC[0] - (((h - mh) * scale >> 1) - 240);
        area_map_draw(&pos, &size, &cell, &rect);
        func_8005EAA8(&rect);
    }
}

// Draws the area map into rect: the player's arrow at its cell, then, clipped to the screen, the
// size.vx x size.vy explored cells from cell (D_80098034 pixels each, rows rising from pos), each
// textured by its byte of the cell map D_8009878C; then restores the draw area to rect.
void area_map_draw(DVECTOR *pos, DVECTOR *size, DVECTOR *cell, RECT *rect)
{
    POLY_G4 *arrow;
    DR_AREA *area;
    POLY_FT4_WORDS *p;
    RECT clip;
    uint32 width;
    uint32 height;
    sint32 x;
    sint32 y;
    sint32 angle;
    sint32 i;
    sint32 j;
    uint32 cx;
    sint32 left;
    sint32 right;
    sint32 bottom;
    sint32 top;

    if (rect->x + rect->w >= 0)
    {
        arrow        = (POLY_G4 *)Map_prim_ptr;
        width        = D_8008D19C[D_80098794].width;
        height       = D_8008D19C[D_80098794].height;
        Map_prim_ptr = (POLY_FT4 *)(arrow + 1);
        SET_TAG_LEN(arrow, 8);
        G4_WORDS(arrow)->rgbc0 = 0x3800FFFF; // POLY_G4, yellow tip
        G4_WORDS(arrow)->rgb1  = 0xFFFF;
        G4_WORDS(arrow)->rgb2  = 0xFF; // red tail
        G4_WORDS(arrow)->rgb3  = 0xFF;
        angle                  = -Player_work[0].ang.vy;
        x = pos->vx + (((Player_work[0].pos.vx - D_8008D19C[D_80098794].x) >> 9) - cell->vx) * D_80098034 + ((uint32)D_80098034 >> 1);
        y = pos->vy - (((Player_work[0].pos.vz - D_8008D19C[D_80098794].z) >> 9) - cell->vy) * D_80098034 - ((uint32)D_80098034 >> 1);
        arrow->x0 = ((rsin(angle - 0x40) * 6 + 0x800) >> 12) + x;
        arrow->y0 = ((rcos(angle - 0x40) * 6 + 0x800) >> 12) + y;
        arrow->x1 = ((rsin(angle + 0x40) * 6 + 0x800) >> 12) + x;
        arrow->y1 = ((rcos(angle + 0x40) * 6 + 0x800) >> 12) + y;
        arrow->x2 = ((rsin(angle + 0x600) * 4 + 0x800) >> 12) + x;
        arrow->y2 = ((rcos(angle + 0x600) * 4 + 0x800) >> 12) + y;
        arrow->x3 = ((rsin(angle - 0x600) * 4 + 0x800) >> 12) + x;
        arrow->y3 = ((rcos(angle - 0x600) * 4 + 0x800) >> 12) + y;
        addPrim(&Disp_env_ptr->ot[2], arrow);

        area = Map_area_ptr++;
        SetDrawArea(area, &D_80098050[Dbl_buff_idx]);
        addPrim(&Disp_env_ptr->ot[2], area);

        for (j = 0; j < size->vy; j++)
        {
            if ((uint32)(cell->vy + j) < height)
            {
                for (i = 0; i < size->vx; i++)
                {
                    cx = cell->vx + i;
                    // explored: the cell's bit of D_8009882C is clear
                    if (cx < width && (sint8)(D_8009882C[(sint32)(width * (cell->vy + j) + cx) >> 3] << (cx & 7)) >= 0)
                    {
                        p = (POLY_FT4_WORDS *)Map_prim_ptr++;
                        SET_TAG_LEN(p, 9);
                        p->rgbc0 = 0x2EC0C0C0; // semi-transparent POLY_FT4
                        left     = pos->vx + i * D_80098034;
                        right    = left + D_80098034;
                        bottom   = pos->vy - j * D_80098034;
                        top      = bottom - D_80098034;
                        p->xy0   = (top << 16) | (left & 0xFFFF);
                        p->xy1   = (top << 16) | (right & 0xFFFF);
                        p->xy2   = (bottom << 16) | (left & 0xFFFF);
                        p->xy3   = (bottom << 16) | (right & 0xFFFF);
                        switch (*((uint8 *)D_8009878C + (cell->vy + j) * width + (cell->vx + i)))
                        {
                            default:
                            case 0:
                                MAP_CELL_UV(p, 0x09, 0x81);
                                break;
                            case 1:
                                MAP_CELL_UV(p, 0x01, 0x81);
                                break;
                            case 2:
                                MAP_CELL_UV(p, 0x11, 0x81);
                                break;
                            case 3:
                                MAP_CELL_UV(p, 0x19, 0x81);
                                break;
                            case 4:
                                MAP_CELL_UV(p, 0x21, 0x81);
                                break;
                            case 5:
                                MAP_CELL_UV(p, 0x29, 0x81);
                                break;
                            case 6:
                                MAP_CELL_UV(p, 0x31, 0x81);
                                break;
                            case 7:
                                MAP_CELL_UV(p, 0x39, 0x81);
                                break;
                            case 8:
                                MAP_CELL_UV(p, 0x41, 0x81);
                                break;
                            case 9:
                                MAP_CELL_UV(p, 0x49, 0x81);
                                break;
                            case 10:
                                MAP_CELL_UV(p, 0x09, 0x89);
                                break;
                            case 11:
                                MAP_CELL_UV(p, 0x01, 0x89);
                                break;
                            case 12:
                                MAP_CELL_UV(p, 0x11, 0x89);
                                break;
                            case 13:
                                MAP_CELL_UV(p, 0x19, 0x89);
                                break;
                            case 14:
                                MAP_CELL_UV(p, 0x21, 0x89);
                                break;
                            case 15:
                                MAP_CELL_UV(p, 0x29, 0x89);
                                break;
                            case 16:
                                MAP_CELL_UV(p, 0x31, 0x89);
                                break;
                            case 17:
                                MAP_CELL_UV(p, 0x39, 0x89);
                                break;
                            case 18:
                                MAP_CELL_UV(p, 0x41, 0x89);
                                break;
                            case 19:
                                MAP_CELL_UV(p, 0x49, 0x89);
                                break;
                        }
                        addPrim(&Disp_env_ptr->ot[2], p);
                    }
                }
            }
        }

        area   = Map_area_ptr++;
        clip.x = rect->x;
        clip.y = rect->y + (Dbl_buff_idx << 8);
        clip.w = rect->w;
        clip.h = rect->h;
        SetDrawArea(area, &clip);
        addPrim(&Disp_env_ptr->ot[2], area);
    }
}

void func_8005E9F8(RECT *rect)
{
    POLY_F4 *p;

    p            = (POLY_F4 *)Map_prim_ptr;
    Map_prim_ptr = (POLY_FT4 *)(p + 1);
    SET_TAG_LEN(p, 5);
    SET_CODE_RGB(p, 0x2A, 0x80, 0x80, 0x80); // semi-transparent POLY_F4
    p->x0 = p->x2 = rect->x;
    p->x1 = p->x3 = rect->x + rect->w;
    p->y0 = p->y1 = rect->y;
    p->y2 = p->y3 = rect->y + rect->h;
    addPrim(&Disp_env_ptr->ot[2], p);
}

// Fills the screen with two gouraud bands (top and bottom halves) in the colors of D_8009806C.
// rect is unused: Area_map_screen_draw passes the map's rectangle, as to area_map_draw.
void func_8005EAA8(RECT *rect)
{
    POLY_G4 *p;
    sint32 i;

    for (i = 0; i < 2; i++)
    {
        p            = (POLY_G4 *)Map_prim_ptr;
        Map_prim_ptr = (POLY_FT4 *)(p + 1);
        SET_TAG_LEN(p, 8);
        G4_WORDS(p)->rgbc0 = D_8009806C[i][0] | 0x38000000; // POLY_G4
        G4_WORDS(p)->rgb1  = D_8009806C[i][1];
        G4_WORDS(p)->rgb2  = D_8009806C[i][2];
        G4_WORDS(p)->rgb3  = D_8009806C[i][3];
        p->x0 = p->x2 = 0;
        p->x1 = p->x3 = 320;
        p->y0 = p->y1 = i * 120;
        p->y2 = p->y3 = (i + 1) * 120;
        addPrim(&Disp_env_ptr->ot[2], p);
    }
}

void func_8005EBA4(sint16 value)
{
    D_800BBD94 = value;
}

void func_8005EBB4(sint16 value)
{
    D_800BBD96 = value;
}

sint32 func_8005EBC4(void)
{
    return D_800BBD94;
}

sint32 func_8005EBD4(void)
{
    return D_800BBD96;
}

void func_8005EBE4(void)
{
    *(uint32 *)&Sub_screen_work.routine_0 = 0;
    Sub_screen_work.rb_parts_no[0]        = Player_work[0].rb_parts_equip_data[0];
    Sub_screen_work.rb_parts_no[1]        = Player_work[0].rb_parts_equip_data[1];
    Sub_screen_work.rb_parts_no[2]        = Player_work[0].rb_parts_equip_data[2];
    Sub_screen_work.weapon_no             = Player_work[0].weapon_right_no;
}
