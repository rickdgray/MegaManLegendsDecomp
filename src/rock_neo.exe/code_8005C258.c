#include "common.h"
#include "code_8005C258.h"
#include "cd.h"
#include "code_80037534.h"
#include "display.h"
#include "fastmem.h"
#include "game.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"
#include "sub_scrn.h"

// Small data (.sdata 0x80098004-0x80098038): reached through $gp in this file.
sint32 D_80098004 = 0;
sint32 D_80098008 = 0;
sint32 D_8009800C = 0;
sint32 D_80098010 = 0;
sint32 D_80098014 = 8;
sint32 D_80098018 = 0x60;
sint32 D_8009801C = 0;
uint8 D_80098020  = 0;
uint8 D_80098021  = 0;
sint16 D_80098022 = 0x101;
sint32 D_80098024 = 0x3030202;
sint32 D_80098028 = 0x5050404;
uint8 D_8009802C  = 0;
uint8 D_8009802D  = 1;
sint16 D_8009802E = 0x201;
sint32 D_80098030 = 0x4030302;
sint32 D_80098034 = 6;

// Small uninitialized statics (.sbss 0x800986F8-0x80098700).
static sint16 D_800986F8[2];
static sint16 D_800986FC[2];

// Pool variables (stay in assembly), reached through $gp here.
sint32 D_8009878C; // arg0 of func_8005DC10's last match
sint32 D_80098794; // index of that D_8008D19C record
sint32 D_8009882C; // its val_4
uint32 D_80098AF0; // open slots of 2-4

// Called only from this file, ahead of their definitions.
void func_8005D4F8(void);
void func_8005DCDC(void);
void func_8005DE28(void);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C2B8);

void func_8005C720(SLOT_WORK *wp)
{
    D_8008D7B4[wp->routine_4](wp);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C75C);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C9BC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005CCF4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005CEFC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D0FC);

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

#ifdef NON_MATCHING
void func_8005D4F8(void)
{
    if (D_800BBD84[1] == 0)
    {
        D_800BBD84[1] = 2;
        D_800BBD81    = 0x1C;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D4F8);
#endif

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

uint8 func_8005D95C(void)
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
// and its val_4, and sets D_80098004 to 3.
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
                D_8009882C = D_8008D19C[i].val_4;
                return;
            }
        }
    }
}

void func_8005DCB4(void)
{
    func_8005DCDC();
    func_8005DE28();
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005DCDC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005DE28);

void func_8005DF3C(void)
{
    D_800986F8[0] = 0;
    D_800986FC[0] = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005DF4C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005E144);

void func_8005E9F8(SCREEN_RECT *rect)
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005EAA8);

void func_8005EBA4(sint16 value)
{
    D_800BBD94 = value;
}

void func_8005EBB4(sint16 value)
{
    D_800BBD96 = value;
}

sint16 func_8005EBC4(void)
{
    return D_800BBD94;
}

sint16 func_8005EBD4(void)
{
    return D_800BBD96;
}

void func_8005EBE4(void)
{
    *(uint32 *)&Sub_screen_work.routine_0 = 0;
    Sub_screen_work.rb_parts_no[0]        = Player_work[0].rb_parts_equip_data[0];
    Sub_screen_work.rb_parts_no[1]        = Player_work[0].rb_parts_equip_data[1];
    Sub_screen_work.rb_parts_no[2]        = Player_work[0].rb_parts_equip_data[2];
    Sub_screen_work.unkB                  = Player_work[0].unk170;
}
