#include "common.h"
#include "rock_neo.exe/code_8002e7a8.h"
#include "rock_neo.exe/game.h"

#ifdef __wasm32__
void Sound_call(sint16 id, uint32 arg1, uint32 arg2);
#endif

// Small data reached through $gp
sint32 D_80097CFC;
uint8 D_80097D02;
uint8 D_80097D03;
sint32 D_80097D08;
uint32 D_80098560, D_80098564, D_80098568;
MATRIX *D_80098A80;
// Small data only addressed here, never loaded: owning them makes GCC rebuild each address per use
PL_HEIGHT_INFO D_80097D0C;
PL_HEIGHT_INFO D_80097D18;

// Work area of the turn-toward helper (func_80033F04), reached through $gp. Only
// D_8009857C, D_800985FC..D_80098604 and D_8009860C..D_8009864C (except D_8009862C) are
// referenced in retail; the others fill the layout between them.
static MATRIX D_8009857C;
static MATRIX D_8009859C;
static MATRIX D_800985BC;
static MATRIX D_800985DC;
static SVECTOR D_800985FC;
static SVECTOR D_80098604;
static VEC32_PAD_WORK D_8009860C;
static VEC32_PAD_WORK D_8009861C;
static VEC32_PAD_WORK D_8009862C;
static VEC32_PAD_WORK D_8009863C;
static VEC32_PAD_WORK D_8009864C;

void func_8002E7A8(sint32 mode)
{
    uint32 i;
    uint32 id;

    if (mode != 0)
    {
        id = 0;
        func_800177CC(&Player_work, (uint8 *)&Player_work + 0xBE4);
        for (i = 0; i < 2; i++)
        {
            Player_slots[i].id_1 = id | i;
        }
    }
    id = 0x10;
    func_800177CC(D_800BFB20, (uint8 *)D_800BFB20 + 0x10BC);
    D_800989F0 = 0;
    D_80098A60 = 0;
    for (i = 0; i < 16; i++)
    {
        D_800BFB20[i].reserved01 = id | i;
    }
    id = 0x20;
    func_800177CC(D_8009F108, (uint8 *)D_8009F108 + 0x3BFC);
    D_800987E8 = 0;
    D_8009880C = 0;
    for (i = 0; i < 16; i++)
    {
        D_8009F108[i].reserved01 = id | i;
    }
    id = 0x40;
    func_800177CC(D_800C3580, (uint8 *)D_800C3580 + 0x168C);
    D_80098B20 = 0;
    D_80098B64 = 0;
    for (i = 0; i < 4; i++)
    {
        D_800C3580[i].reserved01 = id | i;
    }
    id = 0x60;
    func_800177CC(D_8009CF88, (uint8 *)D_8009CF88 + 0x217C);
    D_800987CC = 0;
    D_80098808 = 0;
    for (i = 0; i < 32; i++)
    {
        D_8009CF88[i].reserved01 = id | i;
    }
    id = 0x80;
    func_800177CC(D_800A3B40, (uint8 *)D_800A3B40 + 0x11FC);
    D_80098838 = 0;
    D_8009883C = 0;
    D_800988C8 = 0;
    D_800988CC = 0;
    for (i = 0; i < 64; i++)
    {
        D_800A3B40[i].reserved01 = id | i;
    }
    id = 0xC0;
    func_800177CC(D_800A2D08, (uint8 *)D_800A2D08 + 0x23C);
    D_800987EC = 0;
    D_80098818 = 0;
    for (i = 0; i < 16; i++)
    {
        D_800A2D08[i].reserved01 = id | i;
    }
    id = 0xE0;
    func_800177CC(D_800BF118, (uint8 *)D_800BF118 + 0x9FC);
    D_800989CC = 0;
    D_80098A4C = 0;
    for (i = 0; i < 32; i++)
    {
        D_800BF118[i].reserved01 = id | i;
    }
    func_800177CC(D_800BBA90, D_800BBA90 + 0x264);
    func_800177CC((void *)0x8015BC00, (void *)0x8015BFFC);
}

void func_8002EA50(SPAWN_ENTRY *e, sint32 spawn_player)
{
    SPAWN_SLOT *pl;
    SPAWN_SLOT *o;
    SPAWN_FX *fx;
    SPAWN_LINK *lk;

    while ((sint8)e->flags_0 != -1)
    {
        switch (e->kind_1)
        {
            case 0:
                if (spawn_player != 0)
                {
                    pl = (SPAWN_SLOT *)&Player_work2;
                    D_8009888C |= 0x80000000U >> e->w2.b.byte_3;
                    if (e->w2.b.byte_3 == 0)
                    {
                        pl--;
                    }
                    pl->flags_0  = e->flags_0;
                    pl->half_2   = e->w2.half;
                    pl->half_4   = e->half_4;
                    pl->word_c   = e->word_8;
                    pl->word_8   = 0;
                    pl->fx_1c[0] = pl->fx_34[0] = e->x_c << 16;
                    pl->fx_1c[1] = pl->fx_34[1] = e->y_e << 16;
                    pl->fx_1c[2] = pl->fx_34[2] = e->z_10 << 16;
                    pl->pos_2c                  = *(SVECTOR *)&e->x_c;
                    pl->pos_14                  = pl->pos_2c;
                    pl->rot_54.vx = pl->rot_5c.vx = 0;
                    pl->rot_54.vy = pl->rot_5c.vy = e->byte_7 << 4;
                    pl->rot_54.vz = pl->rot_5c.vz = 0;
                }
                break;
            case 0x20:
                o = (SPAWN_SLOT *)func_80031418();
                goto fill_slot;
            case 0x40:
                o = (SPAWN_SLOT *)func_80031498();
                goto fill_slot;
            case 0x60:
                // The room is read through Game_work itself, not the Spawn_game view: GCC then
                // can't relate its address to mark_78's, so that address stays a short-lived
                // register that loop.c doesn't hoist (retail rebuilds it each time).
                if (e->w2.b.id_2 != 0x11 || (SPAWN_GAME.mark_78.flag != 0 &&
                                             ((sint32)(SPAWN_GAME.mark_78.word << 8) >> 16) ==
                                                 *(sint16 *)&Game_work.routine_50))
                {
                    o = (SPAWN_SLOT *)func_80031518();
                fill_slot:
                    if (o != NULL)
                    {
                        o->flags_0  = e->flags_0;
                        o->half_2   = e->w2.half;
                        o->half_4   = e->half_4;
                        o->word_c   = e->word_8;
                        o->fx_1c[0] = o->fx_34[0] = e->x_c << 16;
                        o->fx_1c[1] = o->fx_34[1] = e->y_e << 16;
                        o->fx_1c[2] = o->fx_34[2] = e->z_10 << 16;
                        o->pos_2c                 = *(SVECTOR *)&e->x_c;
                        o->pos_14                 = o->pos_2c;
                        o->rot_54.vx = o->rot_5c.vx = 0;
                        o->rot_54.vy = o->rot_5c.vy = e->byte_7 << 4;
                        o->rot_54.vz = o->rot_5c.vz = 0;
                    }
                }
                break;
            case 0x80:
                fx = (SPAWN_FX *)func_80031618();
                goto fill_fx;
            case 0xC0:
                lk = (SPAWN_LINK *)func_800316BC();
                if (lk != NULL)
                {
                    lk->flags_0 = e->flags_0;
                    lk->half_2  = e->w2.half;
                    lk->half_4  = e->half_4;
                    lk->word_c  = e->word_8;
                    lk->pos_14  = *(SVECTOR *)&e->x_c;
                }
                break;
            case 0xE0:
                fx = (SPAWN_FX *)func_80031734();
            fill_fx:
                if (fx != NULL)
                {
                    fx->flags_0 = e->flags_0;
                    fx->half_2  = e->w2.half;
                    fx->half_4  = e->half_4;
                    fx->word_c  = e->word_8;
                    fx->pos_38  = *(SVECTOR *)&e->x_c;
                    fx->x_1c    = e->x_c;
                    fx->y_1e    = e->y_e;
                    fx->z_20    = e->z_10;
                }
                break;
        }
        e++;
    }
}

// Same instructions as retail; only register assignment differs (retail: slot s0, flags&0x80 s1,
// i s2, flags s3, bits s4; here i s0, slot s1, flags&0x80 s2, bits s3, flags s4).
void Obj_work_flag_change(sint32 mask, sint32 flags)
{
    uint32 bits;
    sint32 i;
    sint32 j;
    uint8 *flag_slot;
    uint8 *pl;
    GAME_WORK_3C0 *s3c0;
    GAME_WORK_5A4 *s5a4;
    GAME_WORK_10C *s10c;
    GAME_WORK_48 *s48;
    GAME_WORK_24 *s24;
    GAME_WORK_50 *s50;

    if (mask & 1)
    {
        pl   = (uint8 *)&Player_work;
        bits = D_8009888C;
        for (i = 0; i < 2; i++, pl += 0x5F4)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flags & 0x80)
                {
                    D_8009888C &= ~(0x80000000U >> i);
                    *pl = 0;
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)pl, flags);
                }
            }
        }
    }
    if (mask & 2)
    {
        s3c0 = D_8009F108;
        bits = D_800987E8;
        for (i = 0; i < 16; i++, s3c0++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flags & 0x80)
                {
                    func_80052528(s3c0);
                    func_80031824(s3c0);
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)s3c0, flags);
                }
            }
        }
    }
    if (mask & 4)
    {
        s5a4 = D_800C3580;
        bits = D_80098B20;
        for (i = 0; i < 4; i++, s5a4++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flags & 0x80)
                {
                    func_80052528(s5a4);
                    func_8003187C(s5a4);
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)s5a4, flags);
                }
            }
        }
    }
    if (mask & 8)
    {
        s10c = D_800BFB20;
        bits = D_800989F0;
        for (i = 0; i < 16; i++, s10c++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flags & 0x80)
                {
                    func_80052528(s10c);
                    func_80031930(s10c);
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)s10c, flags);
                }
            }
        }
    }
    if (mask & 16)
    {
        s10c = D_8009CF88;
        bits = D_800987CC;
        for (i = 0; i < 32; i++, s10c++)
        {
            if ((sint32)(bits << i) < 0 || (s10c->flags & 3))
            {
                if (flags & 0x80)
                {
                    func_80052528(s10c);
                    func_800318D8(s10c);
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)s10c, flags);
                }
            }
        }
    }
    if (mask & 0x20)
    {
        s48 = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            bits = (&D_80098838)[i];
            for (j = 0; j < 32; j++, s48++)
            {
                if ((sint32)(bits << j) < 0 && s48->kind >= 0x80)
                {
                    if (flags & 0x80)
                    {
                        func_80031988(s48);
                    }
                    else
                    {
                        func_8002F3A8((BYTE_WORK *)s48, flags);
                    }
                }
            }
        }
    }
    if (mask & 0x40)
    {
        s48 = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            bits = (&D_80098838)[i];
            for (j = 0; j < 32; j++, s48++)
            {
                if ((sint32)(bits << j) < 0 && s48->kind < 0x80)
                {
                    if (flags & 0x80)
                    {
                        func_80031988(s48);
                    }
                    else
                    {
                        func_8002F3A8((BYTE_WORK *)s48, flags);
                    }
                }
            }
        }
    }
    if (mask & 128)
    {
        s24  = D_800A2D08;
        bits = D_800987EC;
        for (i = 0; i < 16; i++, s24++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flags & 0x80)
                {
                    Close_EVE_WORK(s24);
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)s24, flags);
                }
            }
        }
    }
    if (mask & 256)
    {
        s50  = D_800BF118;
        bits = D_800989CC;
        for (i = 0; i < 32; i++, s50++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flags & 0x80)
                {
                    func_80052528(s50);
                    func_80031A4C(s50);
                }
                else
                {
                    func_8002F3A8((BYTE_WORK *)s50, flags);
                }
            }
        }
    }
    if (mask & 0x200)
    {
        flag_slot = D_800BBA90;
        for (i = 0; i < 11; i++, flag_slot += 0x38)
        {
            if (*flag_slot & 3)
            {
                if (flags & 0x80)
                {
                    *flag_slot = 0;
                }
                else
                {
                    if (flags & 1)
                    {
                        *flag_slot ^= 1;
                    }
                    if (flags & 4)
                    {
                        *flag_slot ^= 2;
                    }
                    if (flags & 2)
                    {
                        *flag_slot |= 1;
                    }
                    if (flags & 8)
                    {
                        *flag_slot |= 2;
                    }
                }
            }
        }
    }
}

void func_8002F3A8(BYTE_WORK *wp, uint32 flags)
{
    if (flags & 1)
    {
        wp->byte_6 ^= 1;
    }
    if (flags & 4)
    {
        wp->byte_6 ^= 2;
    }
    if (flags & 2)
    {
        wp->byte_6 |= 1;
    }
    if (flags & 8)
    {
        wp->byte_6 |= 2;
    }
}

void func_8002F420(sint32 flag, GAME_DELTA *delta)
{
    sint32 i;
    sint32 j;
    uint32 mask;
    GAME_WORK_3C0 *slot3c0;
    GAME_WORK_5A4 *slot5a4;
    GAME_WORK_10C *slot10c;
    GAME_WORK_48 *slot48;
    GAME_WORK_24 *slot24;
    GAME_WORK_50 *slot50;

    if (flag & 2)
    {
        slot3c0 = D_8009F108;
        mask    = D_800987E8;
        for (i = 0; i < 16; i++, slot3c0++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (slot3c0->active & 0x20)
                {
                    if (delta != NULL)
                    {
                        func_8002F884((SYNC_POS_WORK *)slot3c0, (uint16 *)delta);
                    }
                }
                else
                {
                    func_80031824(slot3c0);
                }
            }
        }
    }
    if (flag & 4)
    {
        slot5a4 = D_800C3580;
        mask    = D_80098B20;
        for (i = 0; i < 4; i++, slot5a4++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (slot5a4->active & 0x20)
                {
                    if (delta != NULL)
                    {
                        func_8002F884((SYNC_POS_WORK *)slot5a4, (uint16 *)delta);
                    }
                }
                else
                {
                    func_8003187C(slot5a4);
                }
            }
        }
    }
    if (flag & 8)
    {
        slot10c = D_800BFB20;
        mask    = D_800989F0;
        for (i = 0; i < 16; i++, slot10c++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (slot10c->active & 0x20)
                {
                    if (delta != NULL)
                    {
                        func_8002F884((SYNC_POS_WORK *)slot10c, (uint16 *)delta);
                    }
                }
                else
                {
                    func_80031930(slot10c);
                }
            }
        }
    }
    if (flag & 16)
    {
        slot10c = D_8009CF88;
        mask    = D_800987CC;
        for (i = 0; i < 32; i++, slot10c++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (slot10c->active & 0x20)
                {
                    if (delta != NULL)
                    {
                        func_8002F884((SYNC_POS_WORK *)slot10c, (uint16 *)delta);
                    }
                }
                else
                {
                    func_800318D8(slot10c);
                }
            }
        }
    }
    if (flag & 32)
    {
        slot48 = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            mask = (&D_80098838)[i];
            for (j = 0; j < 32; j++, slot48++)
            {
                if ((sint32)(mask << j) < 0 && slot48->kind >= 0x80)
                {
                    if (slot48->active & 0x20)
                    {
                        if (delta != NULL)
                        {
                            func_8002F928((MOVE_WORK *)slot48, (uint16 *)delta);
                        }
                    }
                    else
                    {
                        func_80031988(slot48);
                    }
                }
            }
        }
    }
    if (flag & 64)
    {
        slot48 = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            mask = (&D_80098838)[i];
            for (j = 0; j < 32; j++, slot48++)
            {
                if ((sint32)(mask << j) < 0 && slot48->kind < 0x80)
                {
                    if (slot48->active & 0x20)
                    {
                        if (delta != NULL)
                        {
                            func_8002F928((MOVE_WORK *)slot48, (uint16 *)delta);
                        }
                    }
                    else
                    {
                        func_80031988(slot48);
                    }
                }
            }
        }
    }
    if (flag & 128)
    {
        slot24 = D_800A2D08;
        mask   = D_800987EC;
        for (i = 0; i < 16; i++, slot24++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (slot24->active & 0x20)
                {
                    if (delta != NULL)
                    {
                        func_8002F998((POS_WORK *)slot24, (uint16 *)delta);
                    }
                }
                else
                {
                    Close_EVE_WORK(slot24);
                }
            }
        }
    }
    if (flag & 256)
    {
        slot50 = D_800BF118;
        mask   = D_800989CC;
        for (i = 0; i < 32; i++, slot50++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (slot50->active & 0x20)
                {
                    if (delta != NULL)
                    {
                        func_8002F928((MOVE_WORK *)slot50, (uint16 *)delta);
                    }
                }
                else
                {
                    func_80031A4C(slot50);
                }
            }
        }
    }
}

void func_8002F884(SYNC_POS_WORK *wp, uint16 *delta)
{
    wp->x_14 += delta[0];
    wp->y_18 += delta[2];
    wp->fixed_1c += (sint16)delta[0] << 16;
    wp->fixed_24 += (sint16)delta[2] << 16;
    wp->x_2c += delta[0];
    wp->y_30 += delta[2];
    wp->fixed_34 += (sint16)delta[0] << 16;
    wp->fixed_3c += (sint16)delta[2] << 16;
}

void func_8002F928(MOVE_WORK *wp, uint16 *delta)
{
    if (wp->flags & 4)
    {
        wp->x_38 += delta[0];
        wp->z_3C += delta[2];
    }
    else
    {
        wp->x_1C += delta[0];
        wp->z_20 += delta[2];
    }
}

void func_8002F998(POS_WORK *wp, uint16 *delta)
{
    wp->x_14 += delta[0];
    wp->y_18 += delta[2];
}

void func_8002F9C4(void *wp, sint32 arg)
{
    func_8002FA38((RES_OWNER *)wp, (sint32 *)0x8016C000, (uint8 *)arg);
}

void func_8002F9EC(void *wp, sint32 arg)
{
    func_8002FA38((RES_OWNER *)wp, (sint32 *)0x80190000, (uint8 *)arg);
}

void func_8002FA10(void *wp, sint32 arg)
{
    func_8002FA38((RES_OWNER *)wp, (sint32 *)0x801F2000, (uint8 *)arg);
}

sint32 func_8002FA38(RES_OWNER *wp, sint32 *dir, uint8 *key)
{
    RES_ENTRY *e;
    sint32 count;
    sint32 i;
    sint32 kind;

    count = *dir++;
    kind  = func_8002FE74(wp->id_1);
    if (kind == 0x60 && wp->sub_2 >= 0x80)
    {
        kind = 0x10;
    }
    for (i = 0, e = (RES_ENTRY *)dir; i < count; i++, e++)
    {
        if (kind == e->kind_0 && wp->sub_2 == e->id_1 && (key == NULL || *key == e->sub_2))
        {
            switch (kind)
            {
                case 0x20:
                case 0x40:
                    func_80017684(e->data_4 + 0x10, wp->head_f8, 0x18);
                    wp->word_9c = *e->tbl_8;
                    wp->tbl_a0  = e->tbl_8 + 1;
                    wp->data_88 = e->data_4;
                    wp->word_90 = e->word_c;
                    break;
                case 0x10:
                case 0x60:
                    wp->data_88 = e->data_4;
                    break;
                case 0x80:
                case 0xE0:
                    wp->data_14 = e->data_4;
                    break;
            }
            return 1;
        }
    }
    DEBUG_TRAP = 0;
    return 0;
}

void func_8002FBF4(void)
{
    sint32 i;
    sint32 j;
    uint32 mask;
    GAME_WORK_3C0 *p3c0;
    GAME_WORK_5A4 *p5a4;
    GAME_WORK_10C *p10c;
    GAME_WORK_48 *p48;
    GAME_WORK_50 *p50;

    p3c0 = D_8009F108;
    mask = D_800987E8;
    for (i = 0; i < 16; i++)
    {
        if ((sint32)(mask << i) < 0 && ((LINK88_VIEW *)p3c0)->link_88 <= 0x8018FFFF)
        {
            func_80052528(p3c0);
            func_80031824(p3c0);
        }
        p3c0++;
    }
    p5a4 = D_800C3580;
    mask = D_80098B20;
    for (i = 0; i < 4; i++)
    {
        if ((sint32)(mask << i) < 0 && ((LINK88_VIEW *)p5a4)->link_88 <= 0x8018FFFF)
        {
            func_80052528(p5a4);
            func_8003187C(p5a4);
        }
        p5a4++;
    }
    p10c = D_800BFB20;
    mask = D_800989F0;
    for (i = 0; i < 16; i++)
    {
        if ((sint32)(mask << i) < 0 && ((LINK88_VIEW *)p10c)->link_88 <= 0x8018FFFF)
        {
            func_80052528(p10c);
            func_80031930(p10c);
        }
        p10c++;
    }
    p10c = D_8009CF88;
    mask = D_800987CC;
    for (i = 0; i < 32; i++)
    {
        if ((sint32)(mask << i) < 0 && ((LINK88_VIEW *)p10c)->link_88 <= 0x8018FFFF)
        {
            func_80052528(p10c);
            func_800318D8(p10c);
        }
        p10c++;
    }
    p48 = D_800A3B40;
    for (i = 0; i < 2; i++)
    {
        mask = (&D_80098838)[i];
        for (j = 0; j < 32; j++)
        {
            if ((sint32)(mask << j) < 0 && ((LINK14_VIEW *)p48)->link_14 <= 0x8018FFFF)
            {
                func_80031988(p48);
            }
            p48++;
        }
    }
    p50  = D_800BF118;
    mask = D_800989CC;
    for (i = 0; i < 32; i++)
    {
        if ((sint32)(mask << i) < 0 && ((LINK14_VIEW *)p50)->link_14 <= 0x8018FFFF)
        {
            func_80052528(p50);
            func_80031A4C(p50);
        }
        p50++;
    }
}

uint32 func_8002FE74(uint32 val)
{
    if (val < 0x20)
    {
        val &= 0x10;
    }
    else
    {
        val &= 0xE0;
        if (val == 0xA0)
        {
            val = 0x80;
        }
    }
    return val;
}

void func_8002FEA4(FIXED_POS_WORK *wp, sint16 x, sint16 y, sint16 z)
{
#ifdef __wasm32__
    // func_80030058 copies four words, including the vector's padding word.
    sint32 delta[4];
#else
    sint32 delta[3];
#endif

    func_80030058(delta, wp->angle_56, x, y, z);
    wp->fixed_1c[0] += delta[0];
    wp->fixed_1c[1] += delta[1];
    wp->fixed_1c[2] += delta[2];
    func_80030150(wp->fixed_1c, wp->pos_14);
}

void func_8002FF34(FIXED_POS_BIG *wp, sint16 x, sint16 y, sint16 z)
{
#ifdef __wasm32__
    // func_80030058 copies four words, including the vector's padding word.
    sint32 delta[4];
#else
    sint32 delta[3];
#endif

    func_80030058(delta, wp->angle_56, x, y, z);
    wp->fixed_428[0] += delta[0];
    wp->fixed_428[1] += delta[1];
    wp->fixed_428[2] += delta[2];
    func_80030150(wp->fixed_428, wp->pos_438);
}

void func_8002FFC4(sint16 *out, sint32 *fixed, sint32 angle, sint16 x, sint16 y, sint16 z)
{
#ifdef __wasm32__
    // func_80030058 copies four words, including the vector's padding word.
    sint32 delta[4];
#else
    sint32 delta[3];
#endif

    func_80030058(delta, angle, x, y, z);
    fixed[0] += delta[0];
    fixed[1] += delta[1];
    fixed[2] += delta[2];
    func_80030150(fixed, out);
}

sint32 *func_80030058(sint32 *out, sint32 angle, sint16 x, sint16 y, sint16 z)
{
    sint32 v[4];
    sint32 res[4];
    sint32 mtx[8];

    if (x < 0)
    {
        x = -x;
        z = -z;
        angle += 0x800;
    }
    mtx[0] = 0x1000;
    mtx[1] = 0;
    mtx[2] = 0x1000;
    mtx[3] = 0;
    mtx[4] = 0x1000;
    mtx[5] = 0;
    mtx[6] = 0;
    mtx[7] = 0;
    RotMatrixY(angle, (MATRIX *)mtx);
    v[0] = (z << 16) >> 4;
    v[1] = (y << 16) >> 4;
    v[2] = -((x << 16) >> 4);
    ApplyMatrixLV((MATRIX *)mtx, v, res);
    *(VEC4_WORK *)out = *(VEC4_WORK *)res;
    return out;
}

void func_80030150(sint32 *in, sint16 *out)
{
    out[0] = (in[0] >> 16) + ((in[0] >> 15) & 1);
    out[1] = (in[1] >> 16) + ((in[1] >> 15) & 1);
    out[2] = (in[2] >> 16) + ((in[2] >> 15) & 1);
}

void func_800301A8(MATRIX *m, sint32 *wp, sint32 *base)
{
    sint32 delta[4];
    sint32 out[4];

    delta[0] = wp[0] - base[0];
    delta[1] = wp[1] - base[1];
    delta[2] = wp[2] - base[2];
    ApplyMatrixLV(m, delta, out);
    wp[0] = base[0] + out[0];
    wp[1] = base[1] + out[1];
    wp[2] = base[2] + out[2];
}

sint32 func_80030254(DELTA14_WORK *a, DELTA14_WORK *b)
{
    sint16 d[3];

    d[0] = b->x_14 - a->x_14;
    d[1] = b->y_16 - a->y_16;
    d[2] = b->z_18 - a->z_18;
    return SquareRoot0(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
}

sint32 func_800302E4(DELTA0_WORK *a, DELTA0_WORK *b)
{
    sint16 d[3];

    d[0] = b->x_0 - a->x_0;
    d[1] = b->y_2 - a->y_2;
    d[2] = b->z_4 - a->z_4;
    return SquareRoot0(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
}

sint32 func_80030374(sint16 *a, sint16 *b)
{
    sint32 d[4];

    d[0] = b[0] - a[0];
    d[2] = b[2] - a[2];
    return SquareRoot0(d[0] * d[0] + d[2] * d[2]);
}

sint32 func_800303CC(sint16 *a, sint16 *b)
{
    sint32 d[3];

    d[0] = b[0] - a[0];
    d[2] = b[2] - a[2];
    return d[0] * d[0] + d[2] * d[2];
}

uint32 func_80030418(CLIP_WORK *a, CLIP_WORK *b, SHORT3_WORK *range, sint32 *out)
{
    sint32 mtx[8];
    SVECTOR sv;
    sint32 flag;
    uint32 r;
    sint32 sh;
    sint32 v;

    mtx[1] = 0;
    mtx[2] = 0x1000;
    mtx[3] = 0;
    mtx[4] = 0x1000;
    mtx[5] = 0;
    mtx[6] = 0;
    mtx[7] = 0;
    sv.vx  = b->x_c4 - a->x_c4;
    sv.vy  = b->y_c6 - a->y_c6;
    sv.vz  = b->z_c8 - a->z_c8;
    mtx[0] = 0x1000; // set last, as in func_8003081C
    RotMatrixY(0x800 - a->angle_56, (MATRIX *)mtx);
    SetRotMatrix((MATRIX *)mtx);
    SetTransMatrix((MATRIX *)mtx);
    RotTrans(&sv, out, &flag);
    r = (uint32)out[0] >> 31;
    if (out[1] < 0)
    {
        r |= 4;
    }
    if (out[2] < 0)
    {
        r |= 0x10;
    }
    else
    {
        sh = 9 - range->x;
        if (((out[0] >= 0) ? (out[0] << sh) : (-out[0] << sh)) < out[2])
        {
            r |= 2;
        }
    }
    sh = 9 - range->y;
    v  = (out[1] >= 0) ? (out[1] << sh) : (-out[1] << sh);
    if ((out[2] >= 0 && v < out[2]) || (out[2] < 0 && v < -out[2]))
    {
        r |= 8;
    }
    sh = 9 - range->z;
    v  = (out[2] >= 0) ? (out[2] << sh) : (-out[2] << sh);
    if ((out[0] >= 0 && v < out[0]) || (out[0] < 0 && v < -out[0]))
    {
        r |= 0x20;
    }
    return r;
}

// Returns func_80030628's flags: stage callers test them.
uint32 func_80030604(ANGLE_WORK *wp, sint32 a1, sint32 a2, sint32 a3)
{
    return func_80030628((DELTA14_WORK *)wp, (DELTA14_WORK *)a1, (SHORT3_WORK *)a2, (sint32 *)a3,
                  wp->angle_56);
}

uint32 func_80030628(DELTA14_WORK *a, DELTA14_WORK *b, SHORT3_WORK *range, sint32 *out,
                     sint16 angle)
{
    sint32 mtx[8];
    SVECTOR sv;
    sint32 flag;
    uint32 r;
    sint32 sh;
    sint32 v;

    mtx[1] = 0;
    mtx[2] = 0x1000;
    mtx[3] = 0;
    mtx[4] = 0x1000;
    mtx[5] = 0;
    mtx[6] = 0;
    mtx[7] = 0;
    sv.vx  = b->x_14 - a->x_14;
    sv.vy  = b->y_16 - a->y_16;
    mtx[0] = 0x1000;
    sv.vz  = b->z_18 - a->z_18;
    RotMatrixY(0x800 - angle, (MATRIX *)mtx);
    SetRotMatrix((MATRIX *)mtx);
    SetTransMatrix((MATRIX *)mtx);
    RotTrans(&sv, out, &flag);
    r = (uint32)out[0] >> 31;
    if (out[1] < 0)
    {
        r |= 4;
    }
    if (out[2] < 0)
    {
        r |= 0x10;
    }
    else
    {
        sh = 9 - range->x;
        if (((out[0] >= 0) ? (out[0] << sh) : (-out[0] << sh)) < out[2])
        {
            r |= 2;
        }
    }
    sh = 9 - range->y;
    if (out[1] >= 0)
    {
        v = out[1] << sh;
    }
    else
    {
        v = -out[1] << sh;
    }
    if ((out[2] >= 0 && v < out[2]) || (out[2] < 0 && v < -out[2]))
    {
        r |= 8;
    }
    sh = 9 - range->z;
    if (out[2] >= 0)
    {
        v = out[2] << sh;
    }
    else
    {
        v = -out[2] << sh;
    }
    if ((out[0] >= 0 && v < out[0]) || (out[0] < 0 && v < -out[0]))
    {
        r |= 0x20;
    }
    return r;
}

sint32 func_8003081C(DELTA0_WORK *a, DELTA0_WORK *b, sint16 *shift, sint16 angle)
{
    sint32 mtx[8];
    SVECTOR sv;
    sint32 out[4];
    sint32 flag;
    sint32 result;
    sint32 sh;

    mtx[1] = 0;
    mtx[2] = 0x1000;
    mtx[3] = 0;
    mtx[4] = 0x1000;
    mtx[5] = 0;
    mtx[6] = 0;
    mtx[7] = 0;
    sv.vx  = b->x_0 - a->x_0;
    sv.vy  = b->y_2 - a->y_2;
    sv.vz  = b->z_4 - a->z_4;
    mtx[0] = 0x1000; // set last: this placement gives retail's store scheduling
    RotMatrixY(0x800 - angle, (MATRIX *)mtx);
    SetRotMatrix((MATRIX *)mtx);
    SetTransMatrix((MATRIX *)mtx);
    RotTrans(&sv, out, &flag);
    result = 0;
    if (out[2] < 0)
    {
        result = 0x10;
    }
    else
    {
        sh = 9 - *shift;
        if (((out[0] >= 0) ? (out[0] << sh) : (-out[0] << sh)) < out[2])
        {
            result |= 2;
        }
    }
    return result;
}

void func_80030934(void *a0, void *a1, sint16 a2, sint16 a3)
{
    func_80030968(a0, a1, a2, a3, 0x100);
}

void func_80030968(void *wp, void *other, sint16 a2, sint16 a3, sint16 a4)
{
    func_800309E0((uint8 *)wp + 0x14, (uint8 *)other + 0xC4, (uint8 *)wp + 0x44,
                  (uint8 *)other + 0xCA, a2, a3, a4);
    *(sint16 *)((uint8 *)wp + 0x50) = 0;
    *(sint16 *)((uint8 *)wp + 0x4C) = 0;
    *(sint16 *)((uint8 *)wp + 0x4E) = a4;
}

void func_800309E0(SHORT3_WORK *a, SHORT3_WORK *b, SHORT3_WORK *out, sint16 *size, sint16 e,
                   sint16 f, sint16 g)
{
    sint32 delta[3];
    sint32 res[3];
    sint32 dist3;
    sint32 dist2;
    sint16 es;
    sint16 gs;

    es       = (uint16)e;
    gs       = (uint16)g;
    delta[0] = b->x - a->x;
    delta[1] = b->y - a->y;
    delta[2] = b->z - a->z;
    dist3    = SquareRoot0(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
    dist2    = SquareRoot0(delta[0] * delta[0] + delta[2] * delta[2]);
    if ((sint16)f != 0 && dist2 >= (sint16)f)
    {
        dist2 = (sint16)f;
    }
    if (dist3 != 0 && es != 0)
    {
        res[0] = ((es * delta[0]) << 8) / dist3;
        if (dist2 != 0)
        {
            res[1] = (es * (delta[1] << 8)) / dist2 - (gs * (dist2 >> 1)) / es;
        }
        else
        {
            res[1] = es * (delta[1] << 8);
        }
        res[2] = ((es * delta[2]) << 8) / dist3;
        out->x = res[0];
        out->y = res[1];
        out->z = res[2];
        *size  = dist3 / es;
        return;
    }
    out->x = 0;
    out->y = 0;
    out->z = 0;
    *size  = 0;
}

sint16 func_80030CB8(void *a0, sint32 a1, sint16 a2, sint16 a3)
{
    return func_80030CF0(a0, a1, a2, a3, 0x100);
}

sint32 func_80030CF0(void *a0, sint32 a1, sint16 a2, sint16 a3, sint16 a4)
{
    return (sint16)func_80030D30((uint8 *)a0 + 0x14, (uint8 *)a1 + 0xC4, a2, a3, a4);
}

sint16 func_80030D30(SHORT3_WORK *a, SHORT3_WORK *b, sint16 c, sint16 d, sint16 e)
{
    sint32 delta[3];
    SVECTOR unused; // never used; it sets the frame size
    sint32 dist;
    sint32 lim;
    sint32 angle;
    sint16 ee;

    ee       = (uint16)e;
    delta[0] = b->x - a->x;
    delta[1] = b->y - a->y;
    delta[2] = b->z - a->z;
    dist     = SquareRoot0(delta[0] * delta[0] + delta[2] * delta[2]);
    if (d != 0)
    {
        if (dist >= d)
        {
            dist = d;
        }
    }
    lim = c;
    if (lim != 0)
    {
        if (dist != 0)
        {
            delta[1] = (lim * (delta[1] << 8)) / dist - (ee * (dist >> 1)) / lim;
            angle    = 0x400 - ratan2(lim << 8, delta[1]);
        }
        else
        {
            angle = -0x400;
            if (b->y > a->y)
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

void func_80030EE8(MOVER_WORK *wp, SHORT3_WORK *target, sint16 speed)
{
    sint32 d[3];
    sint32 v[3];
    sint32 dist;

    d[0] = target->x - wp->x_14;
    d[1] = target->y - wp->y_16;
    d[2] = target->z - wp->z_18;
    dist = SquareRoot0(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    if (dist != 0)
    {
        v[0]         = ((speed * d[0]) << 8) / dist;
        v[1]         = ((speed * d[1]) << 8) / dist;
        v[2]         = ((speed * d[2]) << 8) / dist;
        wp->vel_x_44 = v[0];
        wp->vel_y_46 = v[1];
        wp->vel_z_48 = v[2];
        wp->vel_w_4a = dist / speed;
    }
    else
    {
        wp->vel_x_44 = 0;
        wp->vel_y_46 = 0;
        wp->vel_z_48 = 0;
        wp->vel_w_4a = 0;
    }
    wp->v4c = 0;
    wp->v4e = 0;
    wp->v50 = 0;
}

sint32 func_800310CC(VEC32_WORK *a, VEC32_WORK *b)
{
    sint32 dx;
    sint32 dz;
    sint32 angle;

    dz = (b->z - a->z) >> 12;
    dx = b->x - a->x;
    if (dz > 0)
    {
        angle = catan(dx / dz) + 0x800;
    }
    else if (dz < 0)
    {
        angle = (0x1000 - catan(-dx / dz)) & 0xFFF;
    }
    else
    {
        angle = 0x400;
        if (dx >= 0)
        {
            angle = 0xC00;
        }
    }
    return angle;
}

sint32 func_80031198(SHORT3_WORK *a, SHORT3_WORK *b)
{
    sint32 dx;
    sint32 dz;
    sint32 angle;

    dz = (b->z - a->z) << 4;
    dx = (b->x - a->x) << 16;
    if (dz > 0)
    {
        angle = catan(dx / dz) + 0x800;
    }
    else if (dz < 0)
    {
        angle = (0x1000 - catan(-dx / dz)) & 0xFFF;
    }
    else
    {
        angle = 0x400;
        if (dx >= 0)
        {
            angle = 0xC00;
        }
    }
    return angle;
}

sint32 func_80031268(sint16 *a, sint16 *b)
{
    return ratan2(b[0] - a[0], b[2] - a[2]) + 0x800;
}

sint32 func_8003129C(SVECTOR *a, SVECTOR *b)
{
    sint32 dx;
    sint32 dz;

    dx = b->vx - a->vx;
    dz = b->vz - a->vz;
    return (0x1000 - ratan2(SquareRoot0(dx * dx + dz * dz), b->vy - a->vy)) & 0xFFF;
}

void func_80031324(SPAWN_OWNER *owner, SPAWN_CHILD *child, sint16 index)
{
    sint32 next;

    child->blk_8c   = owner->blocks_240[index];
    next            = index + 1;
    child->link_88  = &owner->link_88->tbl_70[next];
    child->word_b4  = 0x808080;
    child->owner_b8 = owner;
    child->x_ac = child->x_14 = owner->pos_180[index].x;
    child->y_ae = child->y_16 = owner->pos_180[index].y;
    child->z_b0 = child->z_18     = owner->pos_180[index].z;
    child->fx_1c                  = (sint16)child->x_14 << 16;
    child->fx_20                  = (sint16)child->y_16 << 16;
    child->fx_24                  = (sint16)child->z_18 << 16;
    child->byte_b                 = owner->slots_f8[index].byte_1;
    owner->slots_f8[index].byte_1 = -1;
}

GAME_WORK_3C0 *func_80031418(void)
{
    sint32 i;
    GAME_WORK_3C0 *wp;
    SLOT_INIT *slot;
    uint32 mask;

    mask = D_800987E8;
    for (i = 0; i < 16; i++)
    {
        wp = &D_8009F108[i];
        if (((sint32)mask << i) >= 0)
        {
            slot = (SLOT_INIT *)wp;
            D_800987E8 |= 0x80000000 >> i;
            slot->word_10 = 0;
            slot->word_78 = 0;
            // Cast stores, unlike field stores, can't be scheduled above the mask update
            *(uint16 *)&slot->half_2    = 0;
            *(sint32 *)&slot->routine_4 = 0;
            *(uint32 *)&slot->word_c    = 0;
            *(uint32 *)&slot->word_8    = 0;
            slot->active_6              = 3;
            *(uint32 *)&slot->word_74   = 0;
            return wp;
        }
    }
    return NULL;
}

GAME_WORK_5A4 *func_80031498(void)
{
    sint32 i;
    GAME_WORK_5A4 *wp;
    SLOT_INIT *slot;
    uint32 mask;

    mask = D_80098B20;
    for (i = 0; i < 4; i++)
    {
        wp = &D_800C3580[i];
        if (((sint32)mask << i) >= 0)
        {
            slot = (SLOT_INIT *)wp;
            D_80098B20 |= 0x80000000 >> i;
            slot->word_10 = 0;
            slot->word_78 = 0;
            // Cast stores, unlike field stores, can't be scheduled above the mask update
            *(uint16 *)&slot->half_2    = 0;
            *(sint32 *)&slot->routine_4 = 0;
            *(uint32 *)&slot->word_c    = 0;
            *(uint32 *)&slot->word_8    = 0;
            slot->active_6              = 3;
            *(uint32 *)&slot->word_74   = 0;
            return wp;
        }
    }
    return NULL;
}

GAME_WORK_10C *func_80031518(void)
{
    sint32 i;
    GAME_WORK_10C *wp;
    SLOT_INIT *slot;
    uint32 mask;

    mask = D_800987CC;
    for (i = 0; i < 32; i++)
    {
        wp = &D_8009CF88[i];
        if (((sint32)mask << i) >= 0)
        {
            slot = (SLOT_INIT *)wp;
            D_800987CC |= 0x80000000 >> i;
            slot->word_10 = 0;
            slot->word_78 = 0;
            // Cast stores, unlike field stores, can't be scheduled above the mask update
            *(uint16 *)&slot->half_2    = 0;
            *(sint32 *)&slot->routine_4 = 0;
            *(uint32 *)&slot->word_c    = 0;
            *(uint32 *)&slot->word_8    = 0;
            slot->active_6              = 3;
            *(uint32 *)&slot->word_74   = 0;
            return wp;
        }
    }
    return NULL;
}

GAME_WORK_10C *func_80031598(void)
{
    sint32 i;
    GAME_WORK_10C *wp;
    SLOT_INIT *slot;
    uint32 mask;

    mask = D_800989F0;
    for (i = 0; i < 16; i++)
    {
        wp = &D_800BFB20[i];
        if (((sint32)mask << i) >= 0)
        {
            slot = (SLOT_INIT *)wp;
            D_800989F0 |= 0x80000000 >> i;
            slot->word_10 = 0;
            slot->word_78 = 0;
            // Cast stores, unlike field stores, can't be scheduled above the mask update
            *(uint16 *)&slot->half_2    = 0;
            *(sint32 *)&slot->routine_4 = 0;
            *(uint32 *)&slot->word_c    = 0;
            *(uint32 *)&slot->word_8    = 0;
            slot->active_6              = 3;
            *(uint32 *)&slot->word_74   = 0;
            return wp;
        }
    }
    return NULL;
}

// player.h declares the result as struct CODE456_WORK *
struct CODE456_WORK *func_80031618(void)
{
    sint32 i;
    sint32 j;
    uint32 bits;
    GAME_WORK_48 *wp;
    SLOT_INIT *slot;

    for (i = 0; i < 2; i++)
    {
        bits = (&D_80098838)[i];
        for (j = 0; j < 0x20; j++)
        {
            if (((sint32)bits << j) >= 0)
            {
                (&D_80098838)[i] |= 0x80000000 >> j;
                wp                          = &D_800A3B40[j + (i << 5)];
                slot                        = (SLOT_INIT *)wp;
                slot->half_2                = 0;
                *(sint32 *)&slot->routine_4 = 0;
                slot->word_c                = 0;
                slot->word_8                = 0;
                slot->active_6              = 3;
                slot->word_10               = 0;
                return (struct CODE456_WORK *)wp;
            }
        }
    }
    return NULL;
}

GAME_WORK_24 *func_800316BC(void)
{
    sint32 i;
    GAME_WORK_24 *wp;
    SLOT_INIT *slot;
    uint32 mask;

    mask = D_800987EC;
    for (i = 0; i < 16; i++)
    {
        wp = &D_800A2D08[i];
        if (((sint32)mask << i) >= 0)
        {
            slot = (SLOT_INIT *)wp;
            D_800987EC |= 0x80000000 >> i;
            slot->word_10 = 0;
            // Cast stores, unlike field stores, can't be scheduled above the mask update
            *(uint16 *)&slot->half_2    = 0;
            *(sint32 *)&slot->routine_4 = 0;
            *(uint32 *)&slot->word_c    = 0;
            *(uint32 *)&slot->word_8    = 0;
            slot->active_6              = 3;
            return wp;
        }
    }
    return NULL;
}

GAME_WORK_50 *func_80031734(void)
{
    sint32 i;
    GAME_WORK_50 *wp;
    SLOT_INIT *slot;
    uint32 mask;

    mask = D_800989CC;
    for (i = 0; i < 32; i++)
    {
        wp = &D_800BF118[i];
        if (((sint32)mask << i) >= 0)
        {
            slot = (SLOT_INIT *)wp;
            D_800989CC |= 0x80000000 >> i;
            slot->word_10 = 0;
            // Cast stores, unlike field stores, can't be scheduled above the mask update
            *(uint16 *)&slot->half_2    = 0;
            *(sint32 *)&slot->routine_4 = 0;
            *(uint32 *)&slot->word_c    = 0;
            *(uint32 *)&slot->word_8    = 0;
            slot->active_6              = 3;
            return wp;
        }
    }
    return NULL;
}

GAME_WORK_50 *func_800317AC(sint32 index)
{
    GAME_WORK_50 *wp;
    SLOT_INIT *slot;

    if (index < 0x20)
    {
        if (((sint32)D_800989CC << index) >= 0)
        {
            wp   = &D_800BF118[index];
            slot = (SLOT_INIT *)wp;
            D_800989CC |= 0x80000000 >> index;
            slot->half_2                = 0;
            *(sint32 *)&slot->routine_4 = 0;
            slot->word_c                = 0;
            slot->word_8                = 0;
            slot->active_6              = 3;
            slot->word_10               = 0;
            return wp;
        }
    }
    return NULL;
}

void func_80031824(GAME_WORK_3C0 *wp)
{
    D_8009880C |= 0x80000000 >> (((uint32)wp - (uint32)D_8009F108) / sizeof(*wp));
    D_8009880C &= D_800987E8;
    wp->flags = 0;
}

void func_8003187C(GAME_WORK_5A4 *wp)
{
    D_80098B64 |= 0x80000000 >> (((uint32)wp - (uint32)D_800C3580) / sizeof(*wp));
    D_80098B64 &= D_80098B20;
    wp->flags = 0;
}

void func_800318D8(GAME_WORK_10C *wp)
{
    D_80098808 |= 0x80000000 >> (((uint32)wp - (uint32)D_8009CF88) / sizeof(*wp));
    D_80098808 &= D_800987CC;
    wp->flags = 0;
}

void func_80031930(GAME_WORK_10C *wp)
{
    D_80098A60 |= 0x80000000 >> (((uint32)wp - (uint32)D_800BFB20) / sizeof(*wp));
    D_80098A60 &= D_800989F0;
    wp->flags = 0;
}

void func_80031988(GAME_WORK_48 *wp)
{
    uint32 i;

    i = ((uint32)wp - (uint32)D_800A3B40) / sizeof(*wp);
    (&D_800988C8)[i >> 5] |= 0x80000000 >> (i & 0x1F);
    (&D_800988C8)[i >> 5] &= (&D_80098838)[i >> 5];
    wp->flags = 0;
}

void Close_EVE_WORK(GAME_WORK_24 *wp)
{
    D_80098818 |= 0x80000000 >> (((uint32)wp - (uint32)D_800A2D08) / sizeof(*wp));
    D_80098818 &= D_800987EC;
    wp->flags = 0;
}

void func_80031A4C(GAME_WORK_50 *wp)
{
    D_80098A4C |= 0x80000000 >> (((uint32)wp - (uint32)D_800BF118) / sizeof(*wp));
    D_80098A4C &= D_800989CC;
    wp->flags = 0;
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

sint16 func_80031BEC(SHORT3_WORK *a, SHORT3_WORK *b, sint32 c, sint32 d)
{
    uint32 v;
    uint32 u;
    sint16 r;

    r = d;
    v = (func_80031198(a, b) - (sint16)c) & 0xFFF;
    if (v < 0x800 && v < (uint32)((sint16)d << 1))
    {
        r = v;
    }
    else if (v >= 0x800 && (u = 0x1000 - v) < (uint32)(r << 1))
    {
        r = u;
    }
    if (v < 0x801)
    {
        return r;
    }
    return -r;
}

sint16 func_80031CA4(SVECTOR *a, SVECTOR *b, sint32 c, sint32 d)
{
    uint32 v;
    uint32 u;
    sint16 r;

    r = d;
    v = (func_8003129C(a, b) - (sint16)c) & 0xFFF;
    if (v < 0x800 && v < (uint32)((sint16)d << 1))
    {
        r = v;
    }
    else if (v >= 0x800 && (u = 0x1000 - v) < (uint32)(r << 1))
    {
        r = u;
    }
    if (v < 0x801)
    {
        return r;
    }
    return -r;
}

sint16 func_80031D5C(sint32 a, sint32 b, sint32 limit)
{
    sint16 r;
    sint16 t;

    r = limit;
    t = a - b;
    if (t < 0)
    {
        t += 0x1000;
    }
    if (t < 0x800)
    {
        if (t < (sint16)limit)
        {
            r = t;
        }
    }
    else if ((sint16)limit > 0x1000 - t)
    {
        r = t - 0x1000;
    }
    else
    {
        r = -limit;
    }
    return r;
}

sint32 func_80031DCC(VEC32_WORK *wp, sint32 a, sint32 b, VEC32_WORK *target, sint32 d, sint32 e)
{
    sint32 angle;
    sint32 lo;
    sint32 hi;

    angle = func_800310CC(wp, target);
    d -= 0x800;
    hi = (e + (angle - d)) & 0xFFF;
    lo = (b + (angle - a)) & 0xFFF;
    if (((sint16)b << 1) >= lo)
    {
        if (((sint16)e << 1) >= hi)
        {
            return 1;
        }
    }
    return 0;
}

sint32 func_80031E60(VEC32_WORK *wp, sint32 a, sint32 b, VEC32_WORK *target, sint32 d, sint32 e)
{
    sint32 angle;
    sint32 lo;
    sint32 hi;

    angle = func_800310CC(wp, target);
    hi    = (e + (angle - d)) & 0xFFF;
    lo    = (b + (angle - a)) & 0xFFF;
    if (((sint16)b << 1) >= lo)
    {
        if (((sint16)e << 1) >= hi)
        {
            return 1;
        }
    }
    return 0;
}

sint32 func_80031EF0(SHORT3_WORK *wp, sint32 a, sint32 b, SHORT3_WORK *target, sint32 d, sint32 e)
{
    sint32 angle;
    sint32 lo;
    sint32 hi;

    angle = func_80031198(wp, target);
    d -= 0x800;
    hi = (e + (angle - d)) & 0xFFF;
    lo = (b + (angle - a)) & 0xFFF;
    if (((sint16)b << 1) >= lo)
    {
        if (((sint16)e << 1) >= hi)
        {
            return 1;
        }
    }
    return 0;
}

// Two calls keep CSE from following block 0 into the angle uses, so angle stays a HImode
// copy that sched1 may move; jump2 then merges the calls.
sint32 func_80031F84(SHORT3_WORK *a, SHORT3_WORK *b, sint16 angle, uint16 mode)
{
    sint32 result;
    sint32 t;
    sint32 s;
    sint32 d;

    result = 0;
    if (!(((uint16 *)b)[3] & 1))
    {
        t = func_80031198(b, &D_80097CF4);
    }
    else
    {
        t = func_80031198(a, b);
    }
    if (mode == 0)
    {
        s = (sint16)t;
        if ((((s - angle) + 0x400) & 0xFFF) < 0x800)
        {
            result = (s + 0x800) & 0xFFF;
        }
        else
        {
            result = (t & 0xFFF) | 0x10000;
        }
    }
    else
    {
        d = (sint16)t - angle;
        if (((d + 0x200) & 0xFFF) < 0x400)
        {
            result = ((sint16)t + 0x800) & 0xFFF;
        }
        else if (((d + 0x600) & 0xFFF) < 0x400)
        {
            result = (((sint16)t - 0x400) & 0xFFF) | 0x30000;
        }
        else if (((d + 0xA00) & 0xFFF) < 0x400)
        {
            result = (t & 0xFFF) | 0x10000;
        }
        else if (((d + 0xE00) & 0xFFF) < 0x400)
        {
            result = (((sint16)t + 0x400) & 0xFFF) | 0x20000;
        }
    }
    return result;
}

void func_800320B8(PL_WORK *pl, sint32 id, sint32 index)
{
    ANIM_SET_WORK *wp = (ANIM_SET_WORK *)pl;
    STEP_WORK *steps;

    switch ((uint32)id >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            steps = ANIM_BANK_D9D00[id];
            break;
        case 4:
        case 5:
            if (wp->alt_170)
            {
                steps = ANIM_BANK_DC780[id];
            }
            else
            {
                steps = ANIM_BANK_DC300[id];
            }
            break;
        case 6:
        case 7:
            if (wp->alt_171)
            {
                steps = ANIM_BANK_DD000[id];
            }
            else
            {
                steps = ANIM_BANK_DCB80[id];
            }
            break;
        case 8:
        default:
            steps = ANIM_BANK_DB800[id];
            break;
    }
    wp->steps_94 = steps;
    wp->cur_98   = &steps[index];
    wp->id_ac    = id;
    wp->word_a4  = steps[index].w0.word;
    func_800329D4(wp, id);
    func_800325D4(wp);
}

void func_800321C8(PL_WORK *pl, sint32 a1, sint32 id, sint32 index)
{
    ANIM_SET_WORK *wp = (ANIM_SET_WORK *)pl;
    STEP_WORK *steps;

    switch ((uint32)id >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            steps = ANIM_BANK_D9D00[id];
            break;
        case 4:
        case 5:
            if (wp->alt_170)
            {
                steps = ANIM_BANK_DC780[id];
            }
            else
            {
                steps = ANIM_BANK_DC300[id];
            }
            break;
        case 6:
        case 7:
            if (wp->alt_171)
            {
                steps = ANIM_BANK_DD000[id];
            }
            else
            {
                steps = ANIM_BANK_DCB80[id];
            }
            break;
        case 8:
        default:
            steps = ANIM_BANK_DB800[id];
            break;
    }
    wp->steps_f8 = steps;
    wp->cur_fc   = &steps[index];
    wp->id_104   = id;
    wp->word_100 = steps[index].w0.word;
}

void func_800322A8(ENEMY_WORK *wp, sint32 a1, sint32 a2)
{
    uint32 *tbl;

    tbl          = wp->tbl_90[a1];
    wp->index_AC = a1;
    wp->tbl_94   = tbl;
    wp->ent_98   = tbl + a2 * 2;
    wp->word_A4  = *wp->ent_98;
    func_80033A28(wp);
    func_8003346C(wp);
}

void func_80032304(ENEMY_WORK *wp, sint32 a1, sint32 a2)
{
    uint32 *tbl;

    tbl          = wp->tbl_90[a1];
    wp->index_AC = a1;
    wp->tbl_94   = tbl;
    wp->ent_98   = tbl + a2 * 2;
    wp->word_A4  = *wp->ent_98;
    func_80033A28(wp);
}

void func_8003234C(STEP_OWNER2 *wp, sint32 arg)
{
    STEP_WORK *step;
    STEP_WORK *next;
    sint8 ctl;

    step = wp->cur_98;
    if (--wp->wa4.b.timer_1 == 0)
    {
        ctl = step->w0.b.ctl_3;
        arg = ctl;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->wa4.b.timer_1 = step->w0.b.time_1;
            }
            else
            {
                step         = &wp->steps_94[ctl & 0x7F];
                wp->cur_98   = step;
                wp->wa4.word = step->w0.word;
            }
        }
        else
        {
            next         = wp->cur_98;
            wp->cur_98   = next + 1;
            wp->wa4.word = next[1].w0.word;
        }
    }
    func_800329D4(wp, arg);
    func_800325D4(wp);
}

// Upper-body script step (player.h's 3-argument prototype; the third is unused). The
// chained cur_fc/step assignment keeps retail's load order (timer byte before cur_fc).
void func_800323FC(PL_WORK *pl, sint32 arg, sint32 unused_arg)
{
    STEP_OWNER *wp = (STEP_OWNER *)pl;
    STEP_WORK *step;
    STEP_WORK *next;
    sint8 ctl;

    wp->half_106 = arg;
    step         = wp->cur_fc;
    if (--wp->w100.b.timer_1 == 0)
    {
        ctl = step->w0.b.ctl_3;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->w100.b.timer_1 = step->w0.b.time_1;
            }
            else
            {
                step = wp->cur_fc = &wp->steps_f8[ctl & 0x7F];
                wp->w100.word     = step->w0.word;
            }
        }
        else
        {
            next          = wp->cur_fc;
            wp->cur_fc    = next + 1;
            wp->w100.word = next[1].w0.word;
        }
    }
}

void func_80032488(STEP_OWNER2 *wp)
{
    STEP_WORK *step;
    STEP_WORK *next;
    sint8 ctl;

    step = wp->cur_98;
    if (--wp->wa4.b.timer_1 == 0)
    {
        ctl = step->w0.b.ctl_3;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->wa4.b.timer_1 = step->w0.b.time_1;
            }
            else
            {
                step         = &wp->steps_94[ctl & 0x7F];
                wp->cur_98   = step;
                wp->wa4.word = step->w0.word;
            }
        }
        else
        {
            next         = wp->cur_98;
            wp->cur_98   = next + 1;
            wp->wa4.word = next[1].w0.word;
        }
    }
    func_80033A28(wp);
    func_8003346C(wp);
}

void func_80032538(STEP_OWNER2 *wp)
{
    STEP_WORK *step;
    STEP_WORK *next;
    sint8 ctl;

    step = wp->cur_98;
    if (--wp->wa4.b.timer_1 == 0)
    {
        ctl = step->w0.b.ctl_3;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->wa4.b.timer_1 = step->w0.b.time_1;
            }
            else
            {
                step         = &wp->steps_94[ctl & 0x7F];
                wp->cur_98   = step;
                wp->wa4.word = step->w0.word;
            }
        }
        else
        {
            next         = wp->cur_98;
            wp->cur_98   = next + 1;
            wp->wa4.word = next[1].w0.word;
        }
    }
    func_80033A28(wp);
}

void func_800325D4(void *arg)
{
    JOINT_WORK *wp = arg;
    SVECTOR vec;
    VEC32_WORK out;
    SVECTOR *src_a;
    SVECTOR *src_b;
    SVECTOR *src_c;
    SVECTOR *dst;
    SVECTOR *first;

    func_800333A0();
    ((VEC32_WORK *)0x1F8000D4)->x = wp->x_14 << FOG_MODE;
    ((VEC32_WORK *)0x1F8000D4)->y = wp->y_16 << FOG_MODE;
    ((VEC32_WORK *)0x1F8000D4)->z = wp->z_18 << FOG_MODE;
    vec.vx                        = 0;
    vec.vy                        = wp->rot_56 - wp->rot_116;
    vec.vz                        = 0;
    RotMatrix(&vec, (MATRIX *)0x1F8000C0);
    first       = JOINT_SRC_A;
    wp->mtx_1a8 = *(MATRIX *)0x1F8000C0;
    dst         = D_800DD600;
    func_800333B4((MATRIX *)0x1F8000C0);
    func_800331A0(wp, 0, JOINT_SRC_A + 1, JOINT_SRC_A);
    func_800331A0(wp, 8, JOINT_SRC_A + 9, dst + 8);
    func_800333B4((MATRIX *)0x1F8000C0);
    func_800331A0(wp, 9, JOINT_SRC_A + 10, dst + 9);
    func_800331A0(wp, 10, JOINT_SRC_A + 11, dst + 10);
    func_800331A0(wp, 11, JOINT_SRC_A + 12, dst + 11);
    func_8003340C((MATRIX *)0x1F8000C0);
    func_800331A0(wp, 12, JOINT_SRC_A + 13, dst + 12);
    func_800331A0(wp, 13, JOINT_SRC_A + 14, dst + 13);
    func_800331A0(wp, 14, JOINT_SRC_A + 15, dst + 14);
    func_8003340C((MATRIX *)0x1F8000C0);
    switch (wp->mode_106)
    {
        case 0:
        default:
            src_a = JOINT_SRC_A;
            src_b = JOINT_SRC_A;
            src_c = JOINT_SRC_A;
            break;
        case 1:
            src_a = JOINT_SRC_B;
            src_b = JOINT_SRC_B;
            src_c = JOINT_SRC_A;
            break;
        case 2:
            src_a = JOINT_SRC_B;
            src_b = JOINT_SRC_A;
            src_c = JOINT_SRC_B;
            break;
        case 3:
            src_a = JOINT_SRC_B;
            src_b = JOINT_SRC_B;
            src_c = JOINT_SRC_B;
            break;
    }
    func_800331A0(wp, 0, src_a + 1, first);
    func_800333B4((MATRIX *)0x1F8000C0);
    vec = src_a[2];
    vec.vy += wp->spin_b4 * 5;
    func_800331A0(wp, 1, &vec, dst + 1);
    vec.vx = 0;
    vec.vy = -0x96;
    vec.vz = 0;
    ApplyMatrix((MATRIX *)0x1F8000C0, &vec, &out.x);
    wp->pos_420[0] = ((VEC32_WORK *)0x1F8000D4)->x + out.x;
    wp->pos_420[1] = ((VEC32_WORK *)0x1F8000D4)->y + out.y;
    wp->pos_420[2] = ((VEC32_WORK *)0x1F8000D4)->z + out.z;
    func_8003340C((MATRIX *)0x1F8000C0);
    func_800333B4((MATRIX *)0x1F8000C0);
    func_800331A0(wp, 2, src_b + 3, dst + 2);
    func_800331A0(wp, 3, src_b + 4, dst + 3);
    func_800331A0(wp, 4, src_b + 5, dst + 4);
    func_8003340C((MATRIX *)0x1F8000C0);
    func_800333B4((MATRIX *)0x1F8000C0);
    func_800331A0(wp, 5, src_c + 6, dst + 5);
    func_800331A0(wp, 6, src_c + 7, dst + 6);
    func_800331A0(wp, 7, src_c + 8, dst + 7);
    func_8003340C((MATRIX *)0x1F8000C0);
}

// The packed 12-bit decoder in func_80033A28's style, with src/dst pointers walked by
// `*dst++ = (*src & mask) >> n;` and the next word read as src[1]. Offset-0 accesses go through a
// register only where one address is used twice (0x1F800198, 0x1F80019C, the root at 0x1F800120).
// The root's x is a plain halfword, not a USVECTOR field: as a scalar it stays ordered after the
// last group's stores, so sched2 places the root pointer as retail does.
void func_800329D4(void *arg, sint32 unused)
{
    ANIM_SET_WORK *wp = arg;
    uint32 ***bank;
    uint32 ***bank2;
    uint8 id;
    uint8 id2;
    uint32 *src;
    uint16 *dst;

    id = wp->id_ac;
    switch ((sint8)id >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            bank = POSE_BANK_DD604;
            break;
        case 4:
        case 5:
            bank = wp->alt_170 ? POSE_BANK_EF600 : POSE_BANK_ED600;
            id -= 0x40;
            break;
        case 6:
        case 7:
            bank = wp->alt_171 ? POSE_BANK_F3600 : POSE_BANK_F1600;
            id -= 0x60;
            break;
        case 8:
        default:
            bank = POSE_BANK_E9600;
            id -= 0x80;
            break;
    }
    id2 = wp->id_104;
    switch ((sint8)id2 >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            bank2 = POSE_BANK_DD604;
            break;
        case 4:
        case 5:
            bank2 = wp->alt_170 ? POSE_BANK_EF600 : POSE_BANK_ED600;
            id2 -= 0x40;
            break;
        case 6:
        case 7:
            bank2 = wp->alt_171 ? POSE_BANK_F3600 : POSE_BANK_F1600;
            id2 -= 0x60;
            break;
        case 8:
        default:
            bank2 = POSE_BANK_E9600;
            id2 -= 0x80;
            break;
    }
    func_80017684(bank[(sint8)id][wp->cur_98->w0.b.id_0], (void *)0x1F800164, 0x12);
    func_80017684(bank2[(sint8)id2][wp->cur_fc->w0.b.id_0], (void *)0x1F8001D0, 0xC);
    dst = (uint16 *)0x1F800120;
    src = (uint32 *)0x1F800164;
    // Lower body: 18 words at 0x1F800164 unpacked into 16 vectors at 0x1F800120
    *dst++ = *src & 0xFFF;
    *dst++ = (*src & 0xFFF000) >> 12;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    dst++;
    *dst++ = (*src & 0xFFF0) >> 4;
    *dst++ = (*src & 0xFFF0000) >> 16;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    dst++;
    *dst++ = (*src & 0xFFF00) >> 8;
    *dst++ = (*src & 0xFFF00000) >> 20;
    src++;
    *dst++ = *src & 0xFFF;
    dst++;
    *dst++ = (*src & 0xFFF000) >> 12;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    *dst++ = (*src & 0xFFF0) >> 4;
    dst++;
    *dst++ = (*src & 0xFFF0000) >> 16;
    *dst++ = 0;
    *dst++ = 0;
    dst++;
    *dst++ = 0;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    *dst++ = (*src & 0xFFF00) >> 8;
    dst++;
    *dst++ = (*src & 0xFFF00000) >> 20;
    src++;
    *dst++ = *src & 0xFFF;
    *dst++ = (*src & 0xFFF000) >> 12;
    dst++;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    *dst++ = 0;
    *dst++ = 0;
    dst++;
    *dst++ = 0;
    *dst++ = (*src & 0xFFF0) >> 4;
    *dst++ = (*src & 0xFFF0000) >> 16;
    dst++;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    *dst++ = (*src & 0xFFF00) >> 8;
    *dst++ = (*src & 0xFFF00000) >> 20;
    src++;
    dst++;
    *dst++ = *src & 0xFFF;
    *dst++ = (*src & 0xFFF000) >> 12;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    dst++;
    *dst++ = (*src & 0xFFF0) >> 4;
    *dst++ = 0;
    *dst++ = 0;
    dst++;
    *dst++ = (*src & 0xFFF0000) >> 16;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    *dst++ = (*src & 0xFFF00) >> 8;
    dst++;
    *dst++ = (*src & 0xFFF00000) >> 20;
    src++;
    *dst++ = *src & 0xFFF;
    *dst++ = (*src & 0xFFF000) >> 12;
    dst++;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    *dst++ = 0;
    *dst++ = 0;
    dst++;
    *dst++ = (*src & 0xFFF0) >> 4;
    *dst++ = (*src & 0xFFF0000) >> 16;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    dst++;
    // Upper body: 12 words at 0x1F8001D0 unpacked into the 9 vectors that follow
    src    = (uint32 *)0x1F8001D0;
    *dst++ = *src & 0xFFF;
    *dst++ = (*src & 0xFFF000) >> 12;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    dst++;
    *dst++ = (*src & 0xFFF0) >> 4;
    *dst++ = (*src & 0xFFF0000) >> 16;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    dst++;
    *dst++ = (*src & 0xFFF00) >> 8;
    *dst++ = (*src & 0xFFF00000) >> 20;
    src++;
    *dst++ = *src & 0xFFF;
    dst++;
    *dst++ = (*src & 0xFFF000) >> 12;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    *dst++ = (*src & 0xFFF0) >> 4;
    dst++;
    *dst++ = (*src & 0xFFF0000) >> 16;
    *dst++ = 0;
    *dst++ = 0;
    dst++;
    *dst++ = 0;
    *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
    src++;
    *dst++ = (*src & 0xFFF00) >> 8;
    dst++;
    *dst++ = (*src & 0xFFF00000) >> 20;
    src++;
    *dst++ = *src & 0xFFF;
    *dst++ = (*src & 0xFFF000) >> 12;
    dst++;
    *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    src++;
    *dst++ = 0;
    *dst++ = 0;
    dst++;
    *dst++ = 0;
    *dst++ = (*src & 0xFFF0) >> 4;
    *dst++ = (*src & 0xFFF0000) >> 16;
    dst++;
    // Root vector components are signed 12-bit values
    *(uint16 *)0x1F800120        = (sint32)(*(uint16 *)0x1F800120 << 20) >> 20;
    ((USVECTOR *)0x1F800120)->vy = (sint32)(((USVECTOR *)0x1F800120)->vy << 20) >> 20;
    ((USVECTOR *)0x1F800120)->vz = (sint32)(((USVECTOR *)0x1F800120)->vz << 20) >> 20;
}

void func_800331A0(JOINT_WORK *wp, sint32 index, void *src, SVECTOR *dst)
{
    VEC32_WORK out;
    VEC32_WORK scale;
    SVECTOR unused; // never read; it sets the frame size
    SVECTOR v;
    MATRIX rot;
    sint32 s;

    v.vx = dst->vx << FOG_MODE;
    v.vy = dst->vy << FOG_MODE;
    v.vz = dst->vz << FOG_MODE;
    ApplyMatrix(JOINT_SCR_MTX, &v, &out.x);
    RotMatrix(src, &rot);
    MulMatrix(JOINT_SCR_MTX, &rot);
    JOINT_SCR_MTX->t[0] += out.x;
    JOINT_SCR_MTX->t[1] += out.y;
    JOINT_SCR_MTX->t[2] += out.z;
    v.vx                  = wp->x_14 << FOG_MODE;
    v.vy                  = wp->y_16 << FOG_MODE;
    v.vz                  = wp->z_18 << FOG_MODE;
    wp->pos_3a8[index].vx = (JOINT_SCR_MTX->t[0] + v.vx * 7 + 4) >> 3;
    wp->pos_3a8[index].vy = (JOINT_SCR_MTX->t[1] + v.vy * 7 + 4) >> 3;
    wp->pos_3a8[index].vz = (JOINT_SCR_MTX->t[2] + v.vz * 7 + 4) >> 3;
    wp->mats_1c8[index]   = *JOINT_SCR_MTX;
    s                     = D_80097CFC << FOG_MODE;
    scale.x               = s;
    scale.y               = s;
    scale.z               = s;
    ScaleMatrix(&wp->mats_1c8[index], &scale);
}

void func_800333A0(void)
{
    D_80098A80 = D_800BC728;
}

void func_800333B4(MATRIX *m)
{
    *--D_80098A80 = *m;
}

void func_8003340C(MATRIX *m)
{
    *m = *D_80098A80;
    D_80098A80++;
}

void func_8003346C(void *wp)
{
    SVECTOR rot;
    MATRIX m;

    rot.vx = 0;
    rot.vy = *(uint16 *)((uint8 *)wp + 0x56);
    rot.vz = 0;
    RotMatrix(&rot, &m);
    func_80033598(wp, &m);
}

void func_800334C4(void *wp)
{
    MATRIX m;

    RotMatrixYXZ((SVECTOR *)((uint8 *)wp + 0x54), &m);
    func_80033598(wp, &m);
}

void func_80033500(uint8 *wp)
{
    sint32 i;

    wp[0x542] = 0x20;
    wp[0x541] = 0x20;
    wp[0x540] = 0x20;
    for (i = 0; i < 0x18; i++)
    {
        wp[0x546 + i * 4] = 0x20;
        wp[0x545 + i * 4] = 0x20;
        wp[0x544 + i * 4] = 0x20;
    }
    wp[6] |= 0x40;
}

void func_8003354C(uint8 *wp)
{
    sint32 i;

    wp[0x38A] = 0x20;
    wp[0x389] = 0x20;
    wp[0x388] = 0x20;
    for (i = 0; i < 0xD; i++)
    {
        wp[0x38E + i * 4] = 0x20;
        wp[0x38D + i * 4] = 0x20;
        wp[0x38C + i * 4] = 0x20;
    }
    wp[6] |= 0x40;
}

// Bone-matrix pass. The bone records are reached as wp + (i * 4 + 0xF8), which keeps retail's
// offset induction variable (added to wp each pass) in both loops.
void func_80033598(BONE_WORK *wp, MATRIX *m)
{
    SVECTOR scale;
    MATRIX tmp;
    VEC32_WORK vec;
    SVECTOR *tbl;
    SVECTOR *base;
    MATRIX *mats;
    uint8 *scale_tbl;
    uint32 count;
    sint8 parent;
    uint32 kind;
    uint32 i;
    uint16 z;
    BONE_REC *bone;

    if (func_8002FE74(wp->id_1) == 0x40)
    {
        mats = wp->mats_240;
    }
    else
    {
        mats = wp->mats_1e8;
    }
    base        = JOINT_SRC_A;
    tbl         = wp->tbl_9c;
    wp->mtx_160 = *m;
    scale.vx    = wp->sx_158 << FOG_MODE;
    scale.vy    = wp->sy_15a << FOG_MODE;
    scale.vz    = wp->sz_15c << FOG_MODE;
    RotMatrix((SVECTOR *)0x1F800128, &tmp);
    MulMatrix0(m, &tmp, mats);
    count = wp->bones_f8[0].parent_1;
    for (i = 1; i < count; i++)
    {
        bone   = (BONE_REC *)((uint8 *)wp + (i * 4 + 0xF8));
        parent = bone->parent_1;
        kind   = bone->kind_2;
        if (parent >= 0)
        {
            if (kind != 0)
            {
                RotMatrix(base + (kind + 1), &tmp);
                MulMatrix0(&mats[parent], &tmp, &mats[i]);
            }
            else
            {
                *(MROT_WORK *)&mats[i] = *(MROT_WORK *)mats;
            }
        }
    }
    if (wp->flags_6 & 0x40)
    {
        if (func_8002FE74(wp->id_1) == 0x40)
        {
            scale_tbl = wp->scale_540;
        }
        else
        {
            scale_tbl = wp->scale_388;
        }
        vec.x = ((wp->sx_158 * scale_tbl[0]) << FOG_MODE) >> 5;
        vec.y = ((wp->sy_15a * scale_tbl[1]) << FOG_MODE) >> 5;
        vec.z = ((wp->sz_15c * scale_tbl[2]) << FOG_MODE) >> 5;
        ScaleMatrix(&wp->mtx_160, &vec);
        for (i = 0; i < count; i++)
        {
            vec.x = ((wp->sx_158 * scale_tbl[i * 4 + 4]) << FOG_MODE) >> 5;
            vec.y = ((wp->sy_15a * scale_tbl[i * 4 + 5]) << FOG_MODE) >> 5;
            vec.z = ((wp->sz_15c * scale_tbl[i * 4 + 6]) << FOG_MODE) >> 5;
            ScaleMatrix(&mats[i], &vec);
        }
    }
    else
    {
        vec.x = scale.vx;
        vec.y = scale.vy;
        vec.z = scale.vz;
        ScaleMatrix(&wp->mtx_160, &vec);
        for (i = 0; i < count; i++)
        {
            ScaleMatrix(&mats[i], &vec);
        }
    }
    ((USVECTOR *)base)->vx = ((USVECTOR *)base)->vx * 8;
    ((USVECTOR *)base)->vy = ((USVECTOR *)base)->vy * 8;
    ((USVECTOR *)base)->vz = ((USVECTOR *)base)->vz * 8;
    ApplyMatrix(&wp->mtx_160, base, &vec.x);
    wp->pos_180[0].x = vec.x + (wp->x_14 << FOG_MODE);
    wp->pos_180[0].y = vec.y + (wp->y_16 << FOG_MODE);
    wp->pos_180[0].z = vec.z + (wp->z_18 << FOG_MODE);
    for (i = 1; i < count; i++)
    {
        bone   = (BONE_REC *)((uint8 *)wp + (i * 4 + 0xF8));
        parent = bone->parent_1;
        kind   = bone->kind_2;
        if (parent >= 0)
        {
            if (kind != 0)
            {
                ApplyMatrix(&mats[parent], &tbl[kind], &vec.x);
                wp->pos_180[i].x = wp->pos_180[parent].x + vec.x;
                wp->pos_180[i].y = wp->pos_180[parent].y + vec.y;
                z                = wp->pos_180[parent].z + vec.z;
            }
            else
            {
                wp->pos_180[i].x = wp->pos_180[0].x;
                wp->pos_180[i].y = wp->pos_180[0].y;
                z                = wp->pos_180[0].z;
            }
            wp->pos_180[i].z = z;
        }
    }
}

void func_80033A28(void *arg)
{
    ANIM_SET_WORK *wp = arg;
    uint32 *src;
    uint16 *dst;
    sint32 i;

    func_80017684((void *)wp->tbl_a0[wp->id_ac][wp->cur_98->w0.b.id_0], (void *)0x1F800180, 0x20);
    dst = (uint16 *)0x1F800120;
    src = (uint32 *)0x1F800180;
    for (i = 3; i != 0; i--)
    {
        *dst++ = *src & 0xFFF;
        *dst++ = (*src & 0xFFF000) >> 12;
        *dst   = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
        src++;
        dst += 2;
        *dst++ = (*src & 0xFFF0) >> 4;
        *dst++ = (*src & 0xFFF0000) >> 16;
        *dst   = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
        src++;
        dst += 2;
        *dst++ = (*src & 0xFFF00) >> 8;
        *dst++ = (*src & 0xFFF00000) >> 20;
        src++;
        *dst = *src & 0xFFF;
        dst += 2;
        *dst++ = (*src & 0xFFF000) >> 12;
        *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
        src++;
        *dst = (*src & 0xFFF0) >> 4;
        dst += 2;
        *dst++ = (*src & 0xFFF0000) >> 16;
        *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
        src++;
        *dst = (*src & 0xFFF00) >> 8;
        dst += 2;
        *dst++ = (*src & 0xFFF00000) >> 20;
        src++;
        *dst++ = *src & 0xFFF;
        *dst   = (*src & 0xFFF000) >> 12;
        dst += 2;
        *dst++ = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
        src++;
        *dst++ = (*src & 0xFFF0) >> 4;
        *dst   = (*src & 0xFFF0000) >> 16;
        dst += 2;
        *dst++ = ((*src & 0xF0000000) >> 28) | ((src[1] & 0xFF) << 4);
        src++;
        *dst++ = (*src & 0xFFF00) >> 8;
        *dst   = (*src & 0xFFF00000) >> 20;
        src++;
        dst += 2;
    }
    *dst++                       = *src & 0xFFF;
    *dst                         = (*src & 0xFFF000) >> 12;
    dst[1]                       = ((*src & 0xFF000000) >> 24) | ((src[1] & 0xF) << 8);
    ((USVECTOR *)0x1F800120)->vx = (sint32)(((USVECTOR *)0x1F800120)->vx << 20) >> 20;
    ((USVECTOR *)0x1F800120)->vy = (sint32)(((USVECTOR *)0x1F800120)->vy << 20) >> 20;
    ((USVECTOR *)0x1F800120)->vz = (sint32)(((USVECTOR *)0x1F800120)->vz << 20) >> 20;
}

void func_80033D80(MATRIX *src, MATRIX *dst, SVECTOR *rot, SVECTOR *vec)
{
    MATRIX *tmp = (MATRIX *)0x1F8000C0;
    sint32 v[4];
    MATRIX m;

    *tmp = *src;
    ApplyMatrix((MATRIX *)0x1F8000C0, vec, v);
    JOINT_SCR_MTX->t[0] += v[0];
    JOINT_SCR_MTX->t[1] += v[1];
    JOINT_SCR_MTX->t[2] += v[2];
    RotMatrix(rot, &m);
    MulMatrix((MATRIX *)0x1F8000C0, &m);
    *dst = *tmp;
}

void func_80033EBC(void)
{
    D_800988E0         = 0;
    D_80098798         = 0xFF;
    D_8009A300[0].kind = 0;
    D_8009A300[1].kind = 0;
    D_8009A300[2].kind = 0;
    D_8009A300[3].kind = 0;
    D_80098560         = 0;
    D_80098564         = 0;
    D_80098568         = 0;
}

SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 len, uint32 limit)
{
    sint32 d0;
    sint32 d1;

    if ((a->vx * b->vx + a->vy * b->vy + a->vz * b->vz) << 4 >= (sint32)limit)
    {
        *out = *a;
    }
    else
    {
        D_8009857C.m[0][2] = b->vx;
        D_8009857C.m[1][2] = b->vy;
        D_8009857C.m[2][2] = b->vz;
        D_8009860C.x       = a->vx;
        D_8009860C.y       = a->vy;
        D_8009860C.z       = a->vz;
        D_8009861C.x       = b->vx;
        D_8009861C.y       = b->vy;
        D_8009861C.z       = b->vz;
        OuterProduct12(&D_8009860C, &D_8009861C, &D_8009863C);
        OuterProduct12(&D_8009861C, &D_8009863C, &D_8009864C);
        D_800985FC.vx = len;
        D_80098604.vx = -len;
        D_800985FC.vy = D_80098604.vy = 0;
        D_800985FC.vz = D_80098604.vz = limit >> 16;
        D_8009857C.m[0][1]            = D_8009863C.x;
        D_8009857C.m[1][1]            = D_8009863C.y;
        D_8009857C.m[2][1]            = D_8009863C.z;
        D_8009857C.m[0][0]            = D_8009864C.x;
        D_8009857C.m[1][0]            = D_8009864C.y;
        D_8009857C.m[2][0]            = D_8009864C.z;
        ApplyMatrix(&D_8009857C, &D_800985FC, &D_8009860C.x);
        d0 = a->vx * D_8009860C.x + a->vy * D_8009860C.y + a->vz * D_8009860C.z;
        ApplyMatrix(&D_8009857C, &D_80098604, &D_8009861C.x);
        d1 = a->vx * D_8009861C.x + a->vy * D_8009861C.y + a->vz * D_8009861C.z;
        if (d1 < d0)
        {
            VectorNormalS((VEC32_WORK *)&D_8009860C, &D_800985FC);
        }
        else
        {
            VectorNormalS((VEC32_WORK *)&D_8009861C, &D_800985FC);
        }
        *out = D_800985FC;
    }
    return out;
}

// Hit-queue push.
sint32 func_800341BC(void *pos, sint32 half, sint32 arg2, sint32 arg3, sint32 id, void *tbl,
                     uint32 flags, sint32 arg7, sint32 arg8)
{
    QUEUE_ENTRY *entry;
    uint32 bits;
    uint32 i;
    uint32 n;
    uint32 old;

    n = D_800988E0;
    if (n >= 0x40)
    {
        return 0;
    }
    entry            = &D_800A2F48[n];
    entry->pos.u     = *(POS4_WORK *)pos;
    entry->pos.u.pad = ((uint32)half >> 2) | arg2 | arg3;
    entry->word_8    = (id << 24) | ((sint32)tbl & 0x7FFFFF) | arg7;
    D_800A32E0[n]    = flags;
    i                = ((MASK_WORK *)tbl)->mask_4;
    bits             = i & D_80098798;
    D_800988E0 += 1;
    if (bits & 0x80)
    {
        bits &= ~0xFF;
    }
    ((MASK_WORK *)tbl)->mask_4 = bits | arg8;
    if (bits != 0)
    {
        for (i = 0; i < 0x18; i++)
        {
            if (bits > 0x7FFFFFFF)
            {
                D_800BE478[i]->pos_bc = *(POS4_WORK *)pos;
            }
            bits <<= 1;
        }
    }
    return 1;
}

// Two-entry hit-queue push (cf. func_800341BC). code_8004324c.h declares a different prototype.
sint32 func_8003430C(POS4_WORK *a, uint32 size_a, POS4_WORK *b, uint32 size_b, sint32 arg5,
                     sint32 arg6, sint32 id, MASK_WORK *tbl, sint32 flags, sint32 arg9,
                     sint32 arg10)
{
    uint32 i;
    QUEUE_ENTRY *entry;
    POS4_WORK mid;
    uint32 n;
    uint32 bits;
    uint32 word;

    n = D_800988E0;
    if (n >= 0x3F)
    {
        return 0;
    }
    entry            = &D_800A2F48[n];
    entry->pos.u     = *a;
    word             = (id << 24) | ((sint32)tbl & 0x7FFFFF) | arg9;
    entry->pos.u.pad = (size_a >> 2) | arg5 | arg6;
    entry->word_8    = word;
    D_800A32E0[n]    = flags;
    n++;
    entry            = &D_800A2F48[n];
    entry->pos.u     = *b;
    entry->pos.u.pad = (size_b >> 2) | arg5 | arg6;
    entry->word_8    = word;
    D_800A32E0[n]    = flags;
    i                = tbl->mask_4; // the counter variable briefly holds the old mask
    bits             = i & D_80098798;
    D_800988E0 += 2;
    tbl->mask_4 = bits | arg10;
    if (bits != 0)
    {
        for (i = 0; i < 0x18; i++)
        {
            if (bits > 0x7FFFFFFF)
            {
                mid.x                 = ((sint16)a->x + (sint16)b->x) >> 1;
                mid.y                 = ((sint16)a->y + (sint16)b->y) >> 1;
                mid.z                 = ((sint16)a->z + (sint16)b->z) >> 1;
                D_800BE478[i]->pos_bc = mid;
            }
            bits <<= 1;
        }
    }
    return 1;
}

void func_8003450C(void)
{
    uint32 i;
    uint32 j;
    uint32 n;
    uint32 mask;

    TIME_START = VSync(1);
    mask       = 0xFF000000;
    func_80034EB8();
    D_80097D08 = func_800358F0(&Player_slots[0]);
    n          = D_800988E0;
    D_800988E0 = 0;
    if (n < 2)
    {
        return;
    }
    TIME_SPLIT = (VSync(1) - TIME_START) & 0xFFFF;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (((D_80097D00[QUEUE_PAD(i) >> 13] << (QUEUE_PAD(j) >> 13)) & 0x80) &&
                ((D_800A2F48[i].word_8 ^ D_800A2F48[j].word_8) & mask))
            {
                func_800346AC(&i, &j);
            }
        }
    }
    TIME_TOTAL = (VSync(1) - TIME_START) & 0xFFFF;
}

// Queue pair hit test (spheres, or capsules swept in eighths). Writing the weights as plain
// (8 - ta)/(8 - tb) lets loop.c hoist one register holding 8 and strength-reduce 8 - tb as retail
// does. Locals are reused as retail's registers show: ta first holds the 16-bit radius sum (the
// truncation keeps the bound as a shift of it instead of folding to (ra + rb) * 8), flags holds the
// bound, and the deltas reuse x, y and z. Both hit blocks read m->flags_0 into flags before or-ing
// the other word in. step_b is set before step_a (delay-slot order). The a[0] load sits one loop
// level deeper (do/while (0), likely a Capcom macro): its extra weight ranks pi above pj.
void func_800346AC(uint32 *pi, uint32 *pj)
{
    SVECTOR a[2];
    SVECTOR b[2];
    HIT_OWNER *m;
    uint32 cap_a;
    uint32 cap_b;
    uint32 word;
    uint32 other;
    uint32 flags;
    uint32 ra;
    uint32 rb;
    sint32 step_a;
    sint32 step_b;
    sint32 ta;
    sint32 tb;
    sint32 x;
    sint32 y;
    sint32 z;
    sint32 r;

    do
    {
        a[0] = D_800A2F48[*pi].pos.s;
    } while (0);
    b[0]     = D_800A2F48[*pj].pos.s;
    ra       = a[0].pad & 0x1FF;
    rb       = b[0].pad & 0x1FF;
    ta       = (uint16)((rb + ra) * 4);
    cap_a    = (a[0].pad & 0x600) >> 9;
    cap_b    = (b[0].pad & 0x600) >> 9;
    a[0].pad = ra * 4;
    b[0].pad = rb * 4;
    flags    = ta * 2;
    if ((uint32)(a[0].vx - b[0].vx + ta) > flags || (uint32)(a[0].vy - b[0].vy + ta) > flags ||
        (uint32)(a[0].vz - b[0].vz + ta) > flags)
    {
        if (cap_a)
        {
            (*pi)++;
        }
        if (cap_b)
        {
            (*pj)++;
        }
        return;
    }
    step_b = 9;
    step_a = 9;
    if (cap_a)
    {
        a[1].vx  = D_800A2F48[*pi + 1].pos.u.x;
        a[1].vy  = D_800A2F48[*pi + 1].pos.u.y;
        a[1].vz  = D_800A2F48[*pi + 1].pos.u.z;
        a[1].pad = (D_800A2F48[*pi + 1].pos.u.pad & 0x1FF) * 4;
        step_a   = 8 >> cap_a;
        (*pi)++;
    }
    if (cap_b)
    {
        b[1].vx  = D_800A2F48[*pj + 1].pos.u.x;
        b[1].vy  = D_800A2F48[*pj + 1].pos.u.y;
        b[1].vz  = D_800A2F48[*pj + 1].pos.u.z;
        b[1].pad = (D_800A2F48[*pj + 1].pos.u.pad & 0x1FF) * 4;
        step_b   = 8 >> cap_b;
        (*pj)++;
    }
    for (ta = 0; ta < 9; ta += step_a)
    {
        for (tb = 0; tb < 9; tb += step_b)
        {
            x = ((a[0].vx * (8 - ta) + a[1].vx * ta) - (b[0].vx * (8 - tb) + b[1].vx * tb)) / 8;
            y = ((a[0].vy * (8 - ta) + a[1].vy * ta) - (b[0].vy * (8 - tb) + b[1].vy * tb)) / 8;
            z = ((a[0].vz * (8 - ta) + a[1].vz * ta) - (b[0].vz * (8 - tb) + b[1].vz * tb)) / 8;
            r = (a[0].pad * (8 - ta) + a[1].pad * ta + b[0].pad * (8 - tb) + b[1].pad * tb) / 8;
            if (r * r < x * x + y * y + z * z)
            {
                continue;
            }
            word  = D_800A2F48[*pi].word_8;
            other = D_800A32E0[*pj];
            m     = (HIT_OWNER *)(word & 0x7FFFFF);
            flags = m->flags_0;
            flags |= other & 0xFF000000;
            if (((D_800A32E0[*pi] & 0xFF0000) << ((QUEUE_PAD(*pj) >> 13) + 8)) >= 0)
            {
                flags += other & 0xFFFF;
            }
            m->flags_0 = flags;
            do
            {
                if (word & 0x800000)
                {
                    x = b[0].vx - b[1].vx;
                    y = b[0].vy - b[1].vy;
                    z = b[0].vz - b[1].vz;
                    if (cap_b == 0)
                    {
                        m->x_8 = (b[0].vx * (8 - tb) + b[1].vx * tb) / 8;
                        m->y_a = (b[0].vy * (8 - tb) + b[1].vy * tb) / 8;
                        m->z_c = (b[0].vz * (8 - tb) + b[1].vz * tb) / 8;
                        m->w_e = 1;
                    }
                    else
                    {
                        m->x_8 = x;
                        m->y_a = y;
                        m->z_c = z;
                        m->w_e = 0;
                    }
                }
            } while (0);
            word  = D_800A2F48[*pj].word_8;
            other = D_800A32E0[*pi];
            m     = (HIT_OWNER *)(word & 0x7FFFFF);
            flags = m->flags_0;
            flags |= other & 0xFF000000;
            if (((D_800A32E0[*pj] & 0xFF0000) << ((QUEUE_PAD(*pi) >> 13) + 8)) >= 0)
            {
                flags += other & 0xFFFF;
            }
            m->flags_0 = flags;
            do
            {
                if (word & 0x800000)
                {
                    x = a[0].vx - a[1].vx;
                    y = a[0].vy - a[1].vy;
                    z = a[0].vz - a[1].vz;
                    if (cap_a == 0)
                    {
                        m->x_8 = (a[0].vx * (8 - tb) + a[1].vx * tb) / 8;
                        m->y_a = (a[0].vy * (8 - tb) + a[1].vy * tb) / 8;
                        m->z_c = (a[0].vz * (8 - tb) + a[1].vz * tb) / 8;
                        m->w_e = 1;
                    }
                    else
                    {
                        m->x_8 = x;
                        m->y_a = y;
                        m->z_c = z;
                        m->w_e = 0;
                    }
                }
            } while (0);
            return;
        }
    }
}

void func_80034EB8(void)
{
    MATRIX unused; // never used; it sets the frame size
    sint16 sxy[2];
    SVECTOR pos_a;
    SVECTOR pos_b;
    SVECTOR c;
    sint32 sz;
    sint32 z;
    uint32 n;
    sint32 zone;
    uint32 i;
    uint32 j;
    sint32 best_a;
    sint32 best_b;
    sint32 best_xa;
    sint32 best_xb;
    uint8 mask;

    func_80035508();
    n = D_800988E0;
    if (Player_work.value170 == 8)
    {
        zone = Player_work.parts[8].value04;
    }
    else
    {
        zone = 0;
    }
    for (i = 0; i < 1; i++)
    {
        if (!(Player_slots[i].flags_0 & 1))
        {
            continue;
        }
        best_xb = 0x7FFFFFFF;
        best_xa = 0x7FFFFFFF;
        best_b  = -1;
        best_a  = -1;
        GTE_SET_MATRIX(0x1F800008);
        if (i != 0)
        {
            mask = D_80097D03;
        }
        else
        {
            mask = D_80097D02;
        }
        GTE_LDV0(&Player_slots[i].pos_14);
        GTE_NOP2();
        GTE_RTPS();
        LOCK_GTE_STSZ3_4(&sz);
        sz += 50;
        for (j = 0; j < n; j++)
        {
            if (!((mask << (QUEUE_PAD(j) >> 13)) & 0x80))
            {
                continue;
            }
            if (D_800A2F48[j].pos.u.pad & 0x600)
            {
                c.vx = (D_800A2F48[j].pos.s.vx + D_800A2F48[j + 1].pos.s.vx) >> 1;
                c.vy = (D_800A2F48[j].pos.s.vy + D_800A2F48[j + 1].pos.s.vy) >> 1;
                c.vz = (D_800A2F48[j].pos.s.vz + D_800A2F48[j + 1].pos.s.vz) >> 1;
                j++;
            }
            else
            {
                c = D_800A2F48[j].pos.s;
            }
            if (((MASK_WORK *)(D_800A2F48[j].word_8 & 0x7FFFFF))->mask_4 & 0x80)
            {
                continue;
            }
            GTE_LDV0(&c);
            GTE_NOP2();
            GTE_RTPS();
            LOCK_GTE_STSZ3_4(&z);
            GTE_STSXY2(sxy);
            if (!(z > sz))
            {
                continue;
            }
            if (z < 0x500 && (uint16)(sxy[0] - 0x83) < 0x3B && (uint16)(sxy[1] - 1) < 0xEF)
            {
                if (LOCK_ABS(0xA0 - best_xa) > LOCK_ABS(0xA0 - sxy[0]))
                {
                    best_a  = j;
                    best_xa = sxy[0];
                    pos_a   = c;
                }
            }
            if (z > sz && z < D_8008994C[zone].z_max && sxy[0] > D_8008994C[zone].x_min &&
                sxy[0] < D_8008994C[zone].x_max && sxy[1] > D_8008994C[zone].y_min &&
                sxy[1] < D_8008994C[zone].y_max)
            {
                if (LOCK_ABS(0xA0 - best_xb) > LOCK_ABS(0xA0 - sxy[0]))
                {
                    best_b  = j;
                    best_xb = sxy[0];
                    pos_b   = c;
                }
            }
        }
        if (best_a >= 0)
        {
            if (Player_slots[i].lock_174 & 0x20)
            {
                func_80035724((sint32)&c, 1, (OWNER35_WORK *)&Player_slots[i], best_a, 0);
            }
        }
        else if (Player_slots[i].lock_174 & 0x20)
        {
            func_80035724((sint32)&c, 0, (OWNER35_WORK *)&Player_slots[i], -1, 0);
        }
        if (best_b >= 0)
        {
            if (Player_slots[i].lock_174 & 0x10)
            {
                func_80035724((sint32)&c, 1, (OWNER35_WORK *)&Player_slots[i], best_b, 1);
            }
        }
        else if (Player_slots[i].lock_174 & 0x10)
        {
            func_80035724((sint32)&c, 0, (OWNER35_WORK *)&Player_slots[i], -1, 1);
        }
    }
}

sint32 func_8003545C(SPAWN_TARGET *value, MASK_WORK *wp)
{
    sint32 i;
    uint32 bit;

    i = 0;
    if (D_80098798 >= 0xFFFFFF00)
    {
        return -1;
    }
    bit = 0x80000000;
    for (; i < 0x18; i++)
    {
        if (!(D_80098798 & bit))
        {
            D_80098798 |= bit;
            wp->mask_4 |= bit;
            D_800BE478[i] = value;
            return i;
        }
        bit >>= 1;
    }
    return -1;
}

void func_800354E0(sint32 bit)
{
    D_80098798 &= ~(0x80000000 >> bit);
}

void func_80035508(void)
{
    sint16 sxy[2];
    sint32 z;
    uint32 bits;
    sint32 i;
    SPAWN_TARGET *t;

    GTE_SET_MATRIX(0x1F800008);
    bits = D_80098798 & ~0xFF;
    if (bits != 0)
    {
        for (i = 0; i < 0x18; i++)
        {
            if (bits > 0x7FFFFFFF)
            {
                t = D_800BE478[i];
                GTE_LDV0(&t->pos_bc);
                GTE_NOP2();
                GTE_RTPS();
                *(uint32 *)&t->pos_bc.x             = 0;
                *(uint32 *)&D_800BE478[i]->pos_bc.z = 0;
                LOCK_GTE_STSZ3_4(&z);
                GTE_STSXY2(sxy);
            }
            bits <<= 1;
        }
    }
}

MATRIX *func_800355F0(MATRIX *out, sint32 index, sint32 angle)
{
    SVECTOR rot;
    sint32 v[4];
    MATRIX m;
    MATRIX mt;

    rot.vx = -angle & 0xFFF;
    rot.vy = (Player_slots[index].rot_56 + Player_slots[index].rot_116 + 0x800) & 0xFFF;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &m);
    TransposeMatrix(&m, &mt);
    v[0] = -Player_slots[index].pos_14.vx;
    v[1] = 0x96 - Player_slots[index].pos_14.vy;
    v[2] = -Player_slots[index].pos_14.vz;
    ApplyMatrixLV(&mt, v, mt.t);
    *out = mt;
    return out;
}

// Lock-on effect spawn. Each arm has its own copy of the counter decrement; GCC cross-jumps
// the two copies into one tail, which gives retail's per-arm address computation.
void func_80035724(sint32 a0, sint32 a1, OWNER35_WORK *owner, sint32 index, sint32 flag)
{
    FX35_WORK *fx;
    sint32 id;
    sint32 slot;

    fx = func_80031598();
    if (fx != NULL)
    {
        fx->flag_3 = 0;
        if (index >= 0)
        {
            slot =
                func_8003545C((SPAWN_TARGET *)fx, (MASK_WORK *)(D_800A2F50[index * 3] & 0x7FFFFF));
            fx->id_d = slot;
            if ((sint8)slot >= 0)
            {
                fx->flag_3 = 0x80;
            }
        }
        fx->flags_0 = 1;
        if (flag != 0)
        {
            id         = owner->idx_170;
            fx->kind_2 = D_80089A8B[id * 12];
            fx->x_14   = owner->pos_3c8[0];
            fx->y_16   = owner->pos_3c8[1];
            fx->z_18   = owner->pos_3c8[2];
            if (owner->ent_4f8[id].b != 0x7FFF && id != 4 && id != 7 && (uint32)(id - 0xC) >= 2)
            {
                owner->ent_4f8[id].b--;
            }
        }
        else
        {
            id         = owner->idx_171;
            fx->kind_2 = D_80089A8B[id * 12];
            fx->x_14   = owner->pos_3e0[0];
            fx->y_16   = owner->pos_3e0[1];
            fx->z_18   = owner->pos_3e0[2];
            if (owner->ent_4f8[id].b != 0x7FFF && id != 4 && id != 7 && (uint32)(id - 0xC) >= 2)
            {
                owner->ent_4f8[id].b--;
            }
        }
        fx->half_1a = flag;
        fx->value_c = owner->byte_1;
        fx->fx_1c   = (sint16)fx->x_14 << 16;
        fx->fx_20   = (sint16)fx->y_16 << 16;
        fx->fx_24   = (sint16)fx->z_18 << 16;
        fx->half_64 = owner->rot_56;
    }
}

void func_800358E8(void)
{
}

sint32 func_800358F0(void *arg)
{
    PICK_PLAYER *pl = arg;
    SVECTOR c;
    SVECTOR pos;
    uint32 flags;
    uint32 best_d;
    uint32 n;
    uint32 i;
    uint32 w;
    uint32 d;
    sint32 best;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    uint8 side;
    uint8 mask;
    uint32 kind;

    for (i = 0; i < 4; i++)
    {
        func_80036D40(&D_8009A300[i]);
    }
    best_d = 4000000;
    side   = pl->side_1;
    n      = D_800988E0;
    best   = -1;
    if (side)
    {
        mask = D_80097D03;
    }
    else
    {
        mask = D_80097D02;
    }
    pos = pl->pos_14;
    for (i = 0; i < n; i++)
    {
        if (!((mask << (QUEUE_PAD(i) >> 13)) & 0x80))
        {
            continue;
        }
        w     = D_800A2F48[i].word_8;
        flags = ((MASK_WORK *)(w & 0x7FFFFF))->mask_4;
        if (flags & 0x80)
        {
            continue;
        }
        if ((kind = w >> 24) >= 0x80)
        {
            continue;
        }
        if (D_800A2F48[i].pos.u.pad & 0x600)
        {
            c.vx = (D_800A2F48[i].pos.s.vx + D_800A2F48[i + 1].pos.s.vx) >> 1;
            c.vy = (D_800A2F48[i].pos.s.vy + D_800A2F48[i + 1].pos.s.vy) >> 1;
            c.vz = (D_800A2F48[i].pos.s.vz + D_800A2F48[i + 1].pos.s.vz) >> 1;
            i++;
        }
        else
        {
            c = D_800A2F48[i].pos.s;
        }
        dx = pos.vx - c.vx;
        if ((uint32)(dx + 2000) > 4000)
        {
            continue;
        }
        dy = pos.vy - c.vy;
        if ((uint32)(dy + 2000) > 4000)
        {
            continue;
        }
        dz = pos.vz - c.vz;
        if ((uint32)(dz + 2000) > 4000)
        {
            continue;
        }
        d = dx * dx + dy * dy + dz * dz;
        if (d > 4000000)
        {
            continue;
        }
        if (!(flags & (side + 1)))
        {
            func_80036C50(D_800A2F48[i].word_8 >> 24,
                          (MASK_WORK *)(D_800A2F48[i].word_8 & 0x7FFFFF));
        }
        else if (d < best_d)
        {
            best   = i;
            best_d = d;
        }
    }
    if (D_80098568)
    {
        D_80098568--;
    }
    if (best >= 0)
    {
        kind = D_800A2F48[best].word_8 >> 24;
        if (kind < 0x80)
        {
            if (D_80098568 == 0)
            {
                if (kind != D_80098564)
                {
                    D_80098568 = 0x18;
                    D_80098564 = kind;
                }
                return (sint32)func_80036294(kind);
            }
            if (kind == D_80098564)
            {
                return (sint32)func_80036294(kind);
            }
        }
    }
    return 0;
}

void *func_80035C90(SEEK_PLAYER *pl, sint32 arc, uint32 max_dist, sint32 min_dot)
{
    SVECTOR unused0[5]; // unused locals the retail frame reserves
    SVECTOR pos;
    SVECTOR fwd;
    SVECTOR unused1;
    SVECTOR edge;
    SVECTOR norm;
    SVECTOR other;
    SVECTOR mark;
    VEC32_WORK delta;
    SEEK_SLOT *slot;
    void *found;
    sint32 best;
    sint32 dot;
    sint32 hit;
    uint32 i;

    found = NULL;
    best  = 0;

    fwd.vx  = -rsin(pl->rot_56 + pl->rot_116);
    fwd.vy  = 0;
    fwd.vz  = -rcos(pl->rot_56 + pl->rot_116);
    edge.vx = -rsin(pl->rot_56 + pl->rot_116 + arc);
    edge.vy = 0;
    edge.vz = -rcos(pl->rot_56 + pl->rot_116 + arc);
    pos     = *(SVECTOR *)&pl->x_14;

    hit = -1;
    for (i = 0; i < 16; i++)
    {
        slot = (SEEK_SLOT *)&D_8009F108[i];
        if ((slot->flags_0 & 3) && max_dist >= slot->dist_80)
        {
            other   = slot->pos_14;
            delta.y = 0;
            delta.x = other.vx - pos.vx;
            delta.z = other.vz - pos.vz;
            VectorNormalS(&delta, &norm);
            if ((edge.vx * norm.vx + edge.vz * norm.vz) >= 0)
            {
                dot = fwd.vx * norm.vx + fwd.vz * norm.vz;
                if (dot >= min_dot && best < dot)
                {
                    best = dot;
                    hit  = i;
                }
            }
        }
    }
    if (hit >= 0)
    {
        mark     = Seek_3c0[hit].pos_14;
        mark.pad = 1;
        found    = &Seek_3c0[hit];
    }

    hit = -1;
    for (i = 0; i < 4; i++)
    {
        slot = (SEEK_SLOT *)&D_800C3580[i];
        if ((slot->flags_0 & 3) && max_dist >= slot->dist_80)
        {
            other   = slot->pos_14;
            delta.y = 0;
            delta.x = other.vx - pos.vx;
            delta.z = other.vz - pos.vz;
            VectorNormalS(&delta, &norm);
            if ((edge.vx * norm.vx + edge.vz * norm.vz) >= 0)
            {
                dot = fwd.vx * norm.vx + fwd.vz * norm.vz;
                if (dot >= min_dot && best < dot)
                {
                    best = dot;
                    hit  = i;
                }
            }
        }
    }
    if (hit >= 0)
    {
        mark     = Seek_5a4[hit].pos_14;
        mark.pad = 1;
        found    = &Seek_5a4[hit];
    }
    return found;
}

void func_8003606C(void)
{
    sint32 p;
    sint32 i;
    SVECTOR pos;
    DIST_SLOT *e;
    sint32 dx;
    sint32 dz;
    uint32 d;
    SVECTOR unused; // never used; it sets the frame size

    for (p = 0; p < 2; p++)
    {
        pos = Player_slots[p].pos_14;
        for (i = 0; i < 0x10;)
        {
            e = (DIST_SLOT *)&D_8009F108[i++];
            if (e->flags_0 | 1)
            {
                dx = (e->x_14 - pos.vx) >> 1;
                dz = (e->z_18 - pos.vz) >> 1;
                d  = dx * dx + dz * dz;
                if (d > 0x10000000)
                {
                    e->dist_80[p] = -1;
                }
                else
                {
                    e->dist_80[p] = d * 4;
                }
            }
        }
        for (i = 0; i < 4;)
        {
            e = (DIST_SLOT *)&D_800C3580[i++];
            if (e->flags_0 | 1)
            {
                dx = (e->x_14 - pos.vx) >> 1;
                dz = (e->z_18 - pos.vz) >> 1;
                d  = dx * dx + dz * dz;
                if (d > 0x10000000)
                {
                    e->dist_80[p] = -1;
                }
                else
                {
                    e->dist_80[p] = d * 4;
                }
            }
        }
        for (i = 0; i < 0x20;)
        {
            e = (DIST_SLOT *)&D_8009CF88[i++];
            if (e->flags_0 | 1)
            {
                dx = (e->x_14 - pos.vx) >> 1;
                dz = (e->z_18 - pos.vz) >> 1;
                d  = dx * dx + dz * dz;
                if (d > 0x10000000)
                {
                    e->dist_80[p] = -1;
                }
                else
                {
                    e->dist_80[p] = d * 4;
                }
            }
        }
    }
}

void *func_80036294(uint8 id)
{
    switch ((sint32)func_8002FE74(id))
    {
        case 0:
            return (uint8 *)&Player_work + (id & 0xF) * 0x5F4;
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
            return NULL;
    }
}

void func_80036470(BYTE_WORK *wp)
{
    wp->byte_7 = 0;
}

void func_80036478(BYTE_WORK *wp, uint8 arg1, uint32 arg2)
{
    wp->byte_6 = arg1;
    wp->byte_F = arg2 >> 4;
    wp->byte_7 = 0;
}

// Returns the tracker's result: stage callers test it.
sint32 func_8003648C(TRACK_WORK *a0, ANGLE_WORK *a1)
{
    return func_800364B0(a0, (TRACK_TARGET *)a1, a1->angle_56);
}

// Homing tracker update. The failure paths share one block (the fail label at the top), state 0
// breaks to the common return 0, and D_80097D0C is file-owned small data (see func_80036D40).
sint32 func_800364B0(TRACK_WORK *t, TRACK_TARGET *tg, sint32 angle)
{
    SHORT3_WORK range;
    SVECTOR dir;
    PL_SHORT_VECTOR pl;
    VEC32_WORK delta;

    if (tg->dist_80 >= (uint32)(D_800899AC[t->kind].range << 20))
    {
    fail:
        t->state = 0;
        return 0;
    }
    switch (t->state)
    {
        case 0:
        default:
            range.z = 0;
            range.y = 0;
            range.x = 0;
            if (func_80030628((DELTA14_WORK *)tg, (DELTA14_WORK *)&Player_work, &range,
                              (sint32 *)&delta, (sint16)angle) &
                0x10)
            {
                return 0;
            }
            t->state = 1;
            t->x     = tg->x_14;
            t->y     = tg->y_16 + (t->height << 24 >> 20);
            t->z     = tg->z_18;
            t->vel.x = Player_work.position.x - t->x;
            t->vel.y = Player_work.position.y - t->y;
            t->vel.z = Player_work.position.z - t->z;
            t->timer = D_800899AC[t->kind].start;
            break;
        case 1:
            pl      = Player_work.position;
            delta.x = pl.x - t->x;
            if ((uint32)(delta.x + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.y = pl.y - t->y;
            if ((uint32)(delta.y + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.z = pl.z - t->z;
            if ((uint32)(delta.z + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            VectorNormalS(&delta, &dir);
            func_80033F04(&range, &dir, &t->vel, 0x165, 0x0FF069DA);
            t->vel.x = range.x;
            t->vel.y = range.y;
            t->vel.z = range.z;
            dir.vx   = t->x;
            dir.vy   = t->y;
            dir.vz   = t->z;
            range.x  = range.x * 25 >> 10;
            range.y  = range.y * 25 >> 10;
            range.z  = range.z * 25 >> 10;
            t->x     = dir.vx + range.x;
            t->y     = dir.vy + range.y;
            t->z     = dir.vz + range.z;
            if (func_80049C54(t, t, &D_80097D0C, 0xFFFF) != 0)
            {
                goto fail;
            }
            dir.vx += range.x >> 1;
            dir.vy += range.y >> 1;
            dir.vz += range.z >> 1;
            if (func_80049C54(&dir, &dir, &D_80097D0C, 0xFFFF) != 0)
            {
                goto fail;
            }
            if (--t->timer == 0)
            {
                goto fail;
            }
            if ((uint16)(t->x - pl.x + 100) >= 200)
            {
                return 0;
            }
            if ((uint16)(t->y - pl.y + 100) >= 200)
            {
                return 0;
            }
            if ((uint16)(t->z - pl.z + 100) >= 200)
            {
                return 0;
            }
            if (*(uint8 *)0x1F800075 == 2)
            {
                Sound_call(0x9C, 0, 0);
            }
            t->state = 2;
            t->timer = D_800899AC[t->kind].hold;
            return func_8005EBD4() < 1;
        case 2:
            if (func_8005EBD4() > 0)
            {
                t->timer = 0;
                t->state = 0;
                return 0;
            }
            func_8005D4C0();
            range.z = 9;
            range.y = 9;
            range.x = 9;
            if (func_80030628((DELTA14_WORK *)tg, (DELTA14_WORK *)&Player_work, &range,
                              (sint32 *)&delta, (sint16)angle) &
                0x10)
            {
                if (--t->timer == 0)
                {
                    {
                        t->state = 0;
                        return 0;
                    }
                }
                return 1;
            }
            t->timer = D_800899AC[t->kind].hold;
            return 1;
    }
    return 0;
}

void func_8003697C(void)
{
    FOG_MODE = 0;
    FOG_A    = 0xE00;
    FOG_B    = 0xE00;
    SetFogNear(D_800BC81C, 0x180);
}

void func_800369C0(void)
{
    uint32 near;

    FOG_MODE = 1;
    FOG_A    = 0x680;
    FOG_B    = 0x680;
    near     = D_800BC81C << 1;
    if (near >= 0x3333)
    {
        near = D_800BC81C;
    }
    SetFogNear(near, 0x180);
}

void func_80036A1C(void)
{
    uint32 near;

    FOG_MODE = 2;
    FOG_A    = 0x300;
    FOG_B    = 0x300;
    near     = D_800BC81C << 2;
    if (near >= 0x3333)
    {
        near = D_800BC81C;
    }
    SetFogNear(near, 0x180);
}

void func_80036A78(sint32 arg)
{
    *(uint16 *)0x1F800076 = arg;
}

void func_80036A88(sint32 r, sint32 g, sint32 b, sint32 near)
{
    SetFarColor(r, g, b);
    SetFogNear(near, 0x180);
    D_8009A370.r    = r;
    D_8009A370.g    = g;
    D_8009A370.b    = b;
    D_8009A370.near = near;
}

void func_80036B00(sint16 *out)
{
    out[0] = D_8009A370.r;
    out[1] = D_8009A370.g;
    out[2] = D_8009A370.b;
    out[3] = D_8009A370.near;
}

void func_80036B40(void)
{
    SetFarColor(D_800BC7F8.b[0x20], D_800BC7F8.b[0x21], D_800BC7F8.b[0x22]);
    SetFogNear(*(uint16 *)&D_800BC7F8.b[0x24], 0x180);
    D_8009A350 = D_800BC7F8;
}

void func_80036C50(uint8 kind, MASK_WORK *target)
{
    uint32 i;

    if (D_8009A300[0].kind == kind || D_8009A300[1].kind == kind || D_8009A300[2].kind == kind ||
        D_8009A300[3].kind == kind)
    {
        return;
    }
    if (D_80098560 >= 4)
    {
        return;
    }
    for (i = 0; i < 4; i++)
    {
        if (D_8009A300[i].kind == 0)
        {
            D_8009A300[i].kind   = kind;
            D_8009A300[i].target = target;
            if (D_8009A300[i].toggle)
            {
                D_8009A300[i].toggle = 0;
            }
            else
            {
                D_8009A300[i].toggle = 1;
            }
            D_80098560++;
            return;
        }
    }
}

// D_80097D18 is this file's small data (tentative definition above): GCC treats its address
// as cheap and rebuilds it before each func_80049C54 call, as retail does.
sint32 func_80036D40(TRACK_SLOT *t)
{
    SVECTOR range;
    SVECTOR dir;
    SVECTOR tp;
    VEC32_WORK delta;
    HOMING_TARGET *tg;
    MASK_WORK *m;
    PL_WORK *pl;

    if (t->kind == 0)
    {
        return 0;
    }
    tg = func_80036294(t->kind);
    if (tg->flags_0 == 0)
    {
        goto clear;
    }
    pl = &Player_work;
    if (tg->dist_80 > 0x2EFFFFF)
    {
        goto fail;
    }
    switch (t->state)
    {
        case 0:
        default:
            range.vx = range.vy = range.vz = 9;
            dir.vx                         = D_800A39F0.x;
            dir.vy                         = D_800A39F4;
            dir.vz                         = D_800A39F8;
            if (!(func_8003081C((DELTA0_WORK *)&dir, (DELTA0_WORK *)&tg->pos_14, &range.vx,
                                Player_work.rotation.y) &
                  2))
            {
                return 0;
            }
            if (!(tg->flags_6 & 0x80) && tg->id_1 < 0x60)
            {
                return 0;
            }
            t->state = 1;
            t->x     = pl->position.x;
            t->y     = pl->position.y - 100;
            t->z     = pl->position.z;
            if (t->toggle)
            {
                t->vel.x = tg->pos_14.vx - t->x;
                t->vel.y = tg->pos_14.vy - t->y;
                t->vel.z = tg->pos_14.vz - t->z;
                t->timer = 50;
            }
            else
            {
                t->vel.y = -0x1000;
                t->vel.x = 0;
                t->vel.z = 0;
                t->timer = 15;
            }
            return 0;
        case 1:
            tp      = tg->pos_14;
            delta.x = tp.vx - t->x;
            if ((uint32)(delta.x + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.y = tp.vy - t->y;
            if ((uint32)(delta.y + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.z = tp.vz - t->z;
            if ((uint32)(delta.z + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            VectorNormalS(&delta, &dir);
            func_80033F04(&range, &dir, (SVECTOR *)&t->vel, 0x424, 0x0F746EA4);
            t->vel.x = range.vx;
            t->vel.y = range.vy;
            t->vel.z = range.vz;
            dir.vx   = t->x;
            dir.vy   = t->y;
            dir.vz   = t->z;
            range.vx = range.vx * 25 >> 10;
            range.vy = range.vy * 25 >> 10;
            range.vz = range.vz * 25 >> 10;
            t->x     = dir.vx + range.vx;
            t->y     = dir.vy + range.vy;
            t->z     = dir.vz + range.vz;
            if (func_80049C54(t, t, &D_80097D18, 0xFFFF))
            {
                goto fail;
            }
            dir.vx += range.vx >> 1;
            dir.vy += range.vy >> 1;
            dir.vz += range.vz >> 1;
            if (func_80049C54(&dir, &dir, &D_80097D18, 0xFFFF))
            {
                goto fail;
            }
            if (--t->timer == 0)
            {
            fail:
                t->state = 0;
            clear:
                t->kind = 0;
                D_80098560--;
                return 0;
            }
            if ((uint16)(t->x - tp.vx + 100) >= 200)
            {
                return 0;
            }
            if ((uint16)(t->y - tp.vy + 100) >= 200)
            {
                return 0;
            }
            if ((uint16)(t->z - tp.vz + 100) >= 200)
            {
                return 0;
            }
            m        = t->target;
            t->state = 0;
            t->kind  = 0;
            D_80098560--;
            m->mask_4 |= 1;
            return 1;
    }
}

void func_800371A0(uint32 *blocks, uint32 *arg1)
{
    FOGSAVE_WORK *fog = (FOGSAVE_WORK *)arg1;

    func_800176DC(blocks, D_800BADB0, 8);
    D_800BC7F8 = *fog;
    D_8009A350 = D_800BC7F8;
    SetFarColor(fog->b[0x20], fog->b[0x21], fog->b[0x22]);
    SetFogNear(*(uint16 *)&fog->b[0x24], 0x180);
    *(FOGSAVE_WORK *)D_800C0DC0 = *fog;
    FOG_FAR_MODE                = fog->b[0x23];
}
