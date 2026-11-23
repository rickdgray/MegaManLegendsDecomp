#include "common.h"
#include "code_8001F828.h"
#include "code_8002E7A8.h"
#include "code_80048620.h"
#include "code_8005C258.h"
#include "fastmem.h"
#include "game.h"
#include "psyq/inline_c.h"
#include "psyq/libetc.h"
#include "player.h"
#include "sound.h"
#include "stage.h"
#include "system.h"

// Called only from this file, ahead of their definitions.
void Model_pose_unpack(MODEL_WORK *wp);
sint32 func_8002FA38(MODEL_WORK *wp, sint32 *tbl, uint8 *sub); // tbl: count, then ATTACH_ENT[count]
uint32 func_80030628(MODEL_WORK *from, MODEL_WORK *to, sint16 *shift, VECTOR *out, sint16 angle);
uint32 func_80030418(VIEW_WORK *from, VIEW_WORK *to, sint16 *shift, VECTOR *out);
uint32 func_80030604(MODEL_WORK *from, MODEL_WORK *to, sint16 *shift, VECTOR *out);
sint16 func_80030D30(SVECTOR *from, SVECTOR *to, sint16 height, sint16 max_dist, sint16 arc);
sint16 func_80030CF0(MODEL_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist, sint16 arc);
sint16 func_80030CB8(MODEL_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist);
void func_8002F9EC(MODEL_WORK *wp, uint8 *sub);
void func_8002FA10(MODEL_WORK *wp, uint8 *sub);
VECTOR *func_80030058(VECTOR *out, sint32 angle, sint16 x, sint16 y, sint16 z);
PL_SHL_WORK *func_80031598(void);
sint32 func_8003545C(uint32 value, SLOT_OWNER *owner);
void func_800309E0(SVECTOR *from, SVECTOR *to, SVECTOR *out, sint16 *time, sint16 speed, sint16 max, sint16 grav);
void func_800331A0(PL_WORK *wp, sint32 n, SVECTOR *rot, SVECTOR *off);
void func_800333A0(void);
void matrix_push(MATRIX *src);
void matrix_pop(MATRIX *dst);
void hit_pair_check(uint32 *pi, uint32 *pj);
void lock_on_search(void);
MODEL_WORK *func_800358F0(PL_WORK *pl);
void func_80035508(void);
void pl_shot_spawn(SVECTOR *pos, sint32 found, PL_WORK *pl, sint32 idx, sint32 flag);
sint32 func_8003081C(SVECTOR *from, SVECTOR *to, sint16 *shift, sint16 angle);
void func_8002F3A8(MODEL_WORK *wp, uint32 f);
void func_80036C50(uint8 id, SLOT_OWNER *owner);
sint32 func_80036D40(SLOT_ENT *t);

// Small data (.sdata 0x80097CFC-0x80097D0C): reached through $gp in this file.
sint32 D_80097CFC      = 0x200;
uint8 D_80097D00       = 0x5f;
uint8 D_80097D01       = 0xaf;
uint8 D_80097D02       = 0x49;
uint8 D_80097D03       = 0x89;
sint32 D_80097D04      = -0x363e05;
MODEL_WORK *D_80097D08 = NULL;

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

// Pool variable (tentative definition): top of the matrix stack in D_800BC728.
MATRIX *D_80098A80;

// Clears the work pools and tags each slot with its pool kind (0x10 * pool) ORed with its index.
// The player pool is only reset when `players` is set.
void Work_pools_init(sint32 players)
{
    sint32 kind;
    uint32 i;

    if (players)
    {
        kind = 0;
        Mem_clear(Player_work, (uint8 *)Player_work + 0xBE4);
        for (i = 0; i < 2; i++)
        {
            Player_work[i].unk01 = kind | i;
        }
    }
    kind = 0x10;
    Mem_clear(D_800BFB20, (uint8 *)D_800BFB20 + 0x10BC);
    D_800989F0 = 0;
    D_80098A60 = 0;
    for (i = 0; i < 0x10; i++)
    {
        D_800BFB20[i].kind_1 = kind | i;
    }
    kind = 0x20;
    Mem_clear(D_8009F108, (uint8 *)D_8009F108 + 0x3BFC);
    D_800987E8 = 0;
    D_8009880C = 0;
    for (i = 0; i < 0x10; i++)
    {
        D_8009F108[i].kind_1 = kind | i;
    }
    kind = 0x40;
    Mem_clear(D_800C3580, (uint8 *)D_800C3580 + 0x168C);
    D_80098B20 = 0;
    D_80098B64 = 0;
    for (i = 0; i < 4; i++)
    {
        D_800C3580[i].kind_1 = kind | i;
    }
    kind = 0x60;
    Mem_clear(D_8009CF88, (uint8 *)D_8009CF88 + 0x217C);
    D_800987CC = 0;
    D_80098808 = 0;
    for (i = 0; i < 0x20; i++)
    {
        D_8009CF88[i].kind_1 = kind | i;
    }
    kind = 0x80;
    Mem_clear(D_800A3B40, (uint8 *)D_800A3B40 + 0x11FC);
    D_80098838 = 0;
    D_8009883C = 0;
    D_800988C8 = 0;
    D_800988CC = 0;
    for (i = 0; i < 0x40; i++)
    {
        D_800A3B40[i].kind_1 = kind | i;
    }
    kind = 0xC0;
    Mem_clear(D_800A2D08, (uint8 *)D_800A2D08 + 0x23C);
    D_800987EC = 0;
    D_80098818 = 0;
    for (i = 0; i < 0x10; i++)
    {
        D_800A2D08[i].kind_1 = kind | i;
    }
    kind = 0xE0;
    Mem_clear(D_800BF118, (uint8 *)D_800BF118 + 0x9FC);
    D_800989CC = 0;
    D_80098A4C = 0;
    for (i = 0; i < 0x20; i++)
    {
        D_800BF118[i].kind_1 = kind | i;
    }
    Mem_clear(D_800BBA90, (uint8 *)D_800BBA90 + 0x264);
    Mem_clear(D_8015BC00, D_8015BC00 + 0x3FC);
}

#ifdef NON_MATCHING
// Opens the objects of a room's spawn table (ended by routine_0 == -1), each in the pool its kind_1
// names, and copies the entry into it. Players (kind 0) are only set up when `players` is set.
// Differs only in the 0x60 case: GCC relates &Game_work.stage_no to &Game_work.unk078, keeps one
// base for both in a saved register (s2, hoisted out of the loop; one more saved register), where
// the target builds Game_work+0x78 in v1 each time and reaches 0x50 with its own lui. Reading
// 0x78 through a second declaration of Game_work (`__asm__("Game_work")`, CoastRedWood's draft)
// matches, so the original reached one of the two through another symbol.
void Obj_spawn_tbl_set(SPAWN_ENT *e, sint32 players)
{
    PL_WORK *pl;
    MODEL_WORK *o;
    WORK_48 *fx;
    EVE_WORK *ev;

    while (e->routine_0 != -1)
    {
        switch (e->kind_1)
        {
            case 0x00:
                if (players != 0)
                {
                    pl = &Player_work[1];
                    D_8009888C |= 0x80000000U >> e->type_3;
                    if (e->type_3 == 0)
                    {
                        pl--;
                    }
                    pl->unk00                 = e->routine_0;
                    *(uint16 *)&pl->id_2      = *(uint16 *)&e->id_2;
                    *(uint16 *)&pl->flag_4    = *(uint16 *)&e->flag_4;
                    pl->field_C               = e->field_8;
                    *(uint32 *)&pl->routine_8 = 0;
                    pl->pos_l.vx = pl->old_l.vx = e->pos.vx << 16;
                    pl->pos_l.vy = pl->old_l.vy = e->pos.vy << 16;
                    pl->pos_l.vz = pl->old_l.vz = e->pos.vz << 16;
                    pl->old                     = e->pos;
                    pl->pos                     = pl->old;
                    pl->ang.vx = pl->old_ang.vx = 0;
                    pl->ang.vy = pl->old_ang.vy = e->ang_7 << 4;
                    pl->ang.vz = pl->old_ang.vz = 0;
                }
                break;
            case 0x20:
                o = (MODEL_WORK *)func_80031418();
                goto fill_model;
            case 0x40:
                o = (MODEL_WORK *)func_80031498();
                goto fill_model;
            case 0x60:
                if (e->id_2 != 0x11 ||
                    (Game_work.unk078.b.flag != 0 && ((sint32)(Game_work.unk078.word << 8) >> 16) == *(sint16 *)&Game_work.stage_no))
                {
                    o = (MODEL_WORK *)Open_SHL_WORK();
                fill_model:
                    if (o != NULL)
                    {
                        o->routine_0          = e->routine_0;
                        *(uint16 *)&o->id_2   = *(uint16 *)&e->id_2;
                        *(uint16 *)&o->flag_4 = *(uint16 *)&e->flag_4;
                        o->field_C            = e->field_8;
                        o->pos_l.vx = o->old_l.vx = e->pos.vx << 16;
                        o->pos_l.vy = o->old_l.vy = e->pos.vy << 16;
                        o->pos_l.vz = o->old_l.vz = e->pos.vz << 16;
                        o->old                    = e->pos;
                        o->pos                    = o->old;
                        o->ang.vx = o->old_ang.vx = 0;
                        o->ang.vy = o->old_ang.vy = e->ang_7 << 4;
                        o->ang.vz = o->old_ang.vz = 0;
                    }
                }
                break;
            case 0x80:
                fx = func_80031618();
                goto fill_efc;
            case 0xC0:
                ev = Open_EVE_WORK();
                if (ev != NULL)
                {
                    ev->routine_0          = e->routine_0;
                    *(uint16 *)&ev->id_2   = *(uint16 *)&e->id_2;
                    *(uint16 *)&ev->flag_4 = *(uint16 *)&e->flag_4;
                    ev->field_C            = e->field_8;
                    ev->pos                = e->pos;
                }
                break;
            case 0xE0:
                fx = (WORK_48 *)func_80031734();
            fill_efc:
                if (fx != NULL)
                {
                    fx->routine_0          = e->routine_0;
                    *(uint16 *)&fx->id_2   = *(uint16 *)&e->id_2;
                    *(uint16 *)&fx->flag_4 = *(uint16 *)&e->flag_4;
                    fx->field_C            = e->field_8;
                    fx->efc.model.pos      = e->pos;
                    fx->efc.sprite.pos[0]  = e->pos.vx;
                    fx->efc.sprite.pos[1]  = e->pos.vy;
                    fx->efc.sprite.pos[2]  = e->pos.vz;
                }
                break;
        }
        e++;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002E7A8", Obj_spawn_tbl_set);
#endif

// For each pool picked in `mask` (1 Player_work, 2 WORK_3C0, 4 WORK_5A4, 8 PL_SHL_WORK, 0x10
// SHL_WORK, 0x20 and 0x40 WORK_48 of id 0x80 and up / below 0x80, 0x80 EVE_WORK, 0x100 WORK_50,
// 0x200 the room models): closes every live slot when `flag` has WORK_KILL, else changes its flags
// bits 0-1 by `flag` (func_8002F3A8).
void Obj_work_flag_change(sint32 mask, sint32 flag)
{
    uint32 bits;
    sint32 i;
    sint32 j;
    PL_WORK *pl;
    WORK_3C0 *w3;
    WORK_5A4 *w5;
    PL_SHL_WORK *ps;
    SHL_WORK *sh;
    WORK_48 *fx;
    EVE_WORK *ev;
    WORK_50 *w50;
    ROOM_MODEL *rm;

    if (mask & 1)
    {
        pl   = Player_work;
        bits = D_8009888C;
        for (i = 0; i < 2; i++, pl++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flag & WORK_KILL)
                {
                    D_8009888C &= ~(0x80000000U >> i);
                    pl->unk00 = 0;
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)pl, flag);
                }
            }
        }
    }
    if (mask & 2)
    {
        w3   = D_8009F108;
        bits = D_800987E8;
        for (i = 0; i < 16; i++, w3++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flag & WORK_KILL)
                {
                    func_80052528(w3);
                    func_80031824(w3);
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)w3, flag);
                }
            }
        }
    }
    if (mask & 4)
    {
        w5   = D_800C3580;
        bits = D_80098B20;
        for (i = 0; i < 4; i++, w5++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flag & WORK_KILL)
                {
                    func_80052528(w5);
                    func_8003187C(w5);
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)w5, flag);
                }
            }
        }
    }
    if (mask & 8)
    {
        ps   = D_800BFB20;
        bits = D_800989F0;
        for (i = 0; i < 16; i++, ps++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flag & WORK_KILL)
                {
                    func_80052528(ps);
                    func_80031930(ps);
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)ps, flag);
                }
            }
        }
    }
    if (mask & 0x10)
    {
        sh   = D_8009CF88;
        bits = D_800987CC;
        for (i = 0; i < 32; i++, sh++)
        {
            if ((sint32)(bits << i) < 0 || (sh->routine_0 & 3))
            {
                if (flag & WORK_KILL)
                {
                    func_80052528(sh);
                    Close_SHL_WORK(sh);
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)sh, flag);
                }
            }
        }
    }
    if (mask & 0x20)
    {
        fx = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            bits = (&D_80098838)[i];
            for (j = 0; j < 32; j++, fx++)
            {
                if ((sint32)(bits << j) < 0 && fx->id_2 >= 0x80)
                {
                    if (flag & WORK_KILL)
                    {
                        func_80031988(fx);
                    }
                    else
                    {
                        func_8002F3A8((MODEL_WORK *)fx, flag);
                    }
                }
            }
        }
    }
    if (mask & 0x40)
    {
        fx = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            bits = (&D_80098838)[i];
            for (j = 0; j < 32; j++, fx++)
            {
                if ((sint32)(bits << j) < 0 && fx->id_2 < 0x80)
                {
                    if (flag & WORK_KILL)
                    {
                        func_80031988(fx);
                    }
                    else
                    {
                        func_8002F3A8((MODEL_WORK *)fx, flag);
                    }
                }
            }
        }
    }
    if (mask & 0x80)
    {
        ev   = D_800A2D08;
        bits = D_800987EC;
        for (i = 0; i < 16; i++, ev++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flag & WORK_KILL)
                {
                    Close_EVE_WORK(ev);
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)ev, flag);
                }
            }
        }
    }
    if (mask & 0x100)
    {
        w50  = D_800BF118;
        bits = D_800989CC;
        for (i = 0; i < 32; i++, w50++)
        {
            if ((sint32)(bits << i) < 0)
            {
                if (flag & WORK_KILL)
                {
                    func_80052528(w50);
                    func_80031A4C(w50);
                }
                else
                {
                    func_8002F3A8((MODEL_WORK *)w50, flag);
                }
            }
        }
    }
    if (mask & 0x200)
    {
        rm = D_800BBA90;
        for (i = 0; i < 11; i++, rm++)
        {
            if (rm->flags_0 & 3)
            {
                if (flag & WORK_KILL)
                {
                    rm->flags_0 = 0;
                }
                else
                {
                    if (flag & 1)
                    {
                        rm->flags_0 ^= 1;
                    }
                    if (flag & 4)
                    {
                        rm->flags_0 ^= 2;
                    }
                    if (flag & 2)
                    {
                        rm->flags_0 |= 1;
                    }
                    if (flag & 8)
                    {
                        rm->flags_0 |= 2;
                    }
                }
            }
        }
    }
}

void func_8002F3A8(MODEL_WORK *wp, uint32 f)
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

// For each pool picked in `flag` (2 WORK_3C0, 4 WORK_5A4, 8 PL_SHL_WORK, 0x10 SHL_WORK, 0x20 and
// 0x40 WORK_48 of id 0x80 and up / below 0x80, 0x80 EVE_WORK, 0x100 WORK_50): every live slot
// whose flags bit 5 is set is moved by d (when given), every other one is closed.
void func_8002F420(sint32 flag, SVECTOR *d)
{
    sint32 i;
    sint32 j;
    uint32 mask;
    WORK_3C0 *w3;
    WORK_5A4 *w5;
    PL_SHL_WORK *ps;
    SHL_WORK *sh;
    WORK_48 *fx;
    EVE_WORK *ev;
    WORK_50 *w50;

    if (flag & 2)
    {
        w3   = D_8009F108;
        mask = D_800987E8;
        for (i = 0; i < 16; i++, w3++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (w3->flags & 0x20)
                {
                    if (d != NULL)
                    {
                        func_8002F884((MODEL_WORK *)w3, d);
                    }
                }
                else
                {
                    func_80031824(w3);
                }
            }
        }
    }
    if (flag & 4)
    {
        w5   = D_800C3580;
        mask = D_80098B20;
        for (i = 0; i < 4; i++, w5++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (w5->flags & 0x20)
                {
                    if (d != NULL)
                    {
                        func_8002F884((MODEL_WORK *)w5, d);
                    }
                }
                else
                {
                    func_8003187C(w5);
                }
            }
        }
    }
    if (flag & 8)
    {
        ps   = D_800BFB20;
        mask = D_800989F0;
        for (i = 0; i < 16; i++, ps++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (ps->flags & 0x20)
                {
                    if (d != NULL)
                    {
                        func_8002F884((MODEL_WORK *)ps, d);
                    }
                }
                else
                {
                    func_80031930(ps);
                }
            }
        }
    }
    if (flag & 0x10)
    {
        sh   = D_8009CF88;
        mask = D_800987CC;
        for (i = 0; i < 32; i++, sh++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (sh->flags & 0x20)
                {
                    if (d != NULL)
                    {
                        func_8002F884((MODEL_WORK *)sh, d);
                    }
                }
                else
                {
                    Close_SHL_WORK(sh);
                }
            }
        }
    }
    if (flag & 0x20)
    {
        fx = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            mask = (&D_80098838)[i];
            for (j = 0; j < 32; j++, fx++)
            {
                if ((sint32)(mask << j) < 0 && fx->id_2 >= 0x80)
                {
                    if (fx->flags & 0x20)
                    {
                        if (d != NULL)
                        {
                            func_8002F928(fx, d);
                        }
                    }
                    else
                    {
                        func_80031988(fx);
                    }
                }
            }
        }
    }
    if (flag & 0x40)
    {
        fx = D_800A3B40;
        for (i = 0; i < 2; i++)
        {
            mask = (&D_80098838)[i];
            for (j = 0; j < 32; j++, fx++)
            {
                if ((sint32)(mask << j) < 0 && fx->id_2 < 0x80)
                {
                    if (fx->flags & 0x20)
                    {
                        if (d != NULL)
                        {
                            func_8002F928(fx, d);
                        }
                    }
                    else
                    {
                        func_80031988(fx);
                    }
                }
            }
        }
    }
    if (flag & 0x80)
    {
        ev   = D_800A2D08;
        mask = D_800987EC;
        for (i = 0; i < 16; i++, ev++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (ev->flags & 0x20)
                {
                    if (d != NULL)
                    {
                        func_8002F998(ev, d);
                    }
                }
                else
                {
                    Close_EVE_WORK(ev);
                }
            }
        }
    }
    if (flag & 0x100)
    {
        w50  = D_800BF118;
        mask = D_800989CC;
        for (i = 0; i < 32; i++, w50++)
        {
            if ((sint32)(mask << i) < 0)
            {
                if (w50->flags & 0x20)
                {
                    if (d != NULL)
                    {
                        func_8002F928((WORK_48 *)w50, d);
                    }
                }
                else
                {
                    func_80031A4C(w50);
                }
            }
        }
    }
}

// Moves the position and the previous position (both forms) by d in x and z.
void func_8002F884(MODEL_WORK *wp, SVECTOR *d)
{
    wp->pos.vx += d->vx;
    wp->pos.vz += d->vz;
    wp->pos_l.vx += d->vx << 16;
    wp->pos_l.vz += d->vz << 16;
    wp->old.vx += d->vx;
    wp->old.vz += d->vz;
    wp->old_l.vx += d->vx << 16;
    wp->old_l.vz += d->vz << 16;
}

// Also called on the slots of D_800BF118 (WORK_50) by func_8002F420.
void func_8002F928(WORK_48 *wp, SVECTOR *d)
{
    if (wp->routine_0 & 4)
    {
        wp->efc.model.pos.vx += d->vx;
        wp->efc.model.pos.vz += d->vz;
    }
    else
    {
        wp->efc.sprite.pos[0] += d->vx;
        wp->efc.sprite.pos[2] += d->vz;
    }
}

void func_8002F998(EVE_WORK *wp, SVECTOR *d)
{
    wp->pos.vx += d->vx;
    wp->pos.vz += d->vz;
}

void Model_work_init(MODEL_WORK *wp, uint8 *sub)
{
    func_8002FA38(wp, Stage_ebd_0, sub);
}

void func_8002F9EC(MODEL_WORK *wp, uint8 *sub)
{
    func_8002FA38(wp, Stage_ebd_1, sub);
}

void func_8002FA10(MODEL_WORK *wp, uint8 *sub)
{
    func_8002FA38(wp, Support_ebd, sub);
}

sint32 func_8002FA38(MODEL_WORK *wp, sint32 *tbl, uint8 *sub)
{
    ATTACH_ENT *e;
    sint32 count;
    sint32 kind;
    sint32 i;

    count = *tbl++;
    kind  = func_8002FE74(wp->kind_1);
    if (kind == 0x60 && wp->id_2 >= 0x80)
    {
        kind = 0x10;
    }
    for (i = 0, e = (ATTACH_ENT *)tbl; i < count; i++, e++)
    {
        if (kind == e->kind_0 && wp->id_2 == e->id_1 && (sub == NULL || *sub == e->sub_2))
        {
            switch (kind)
            {
                case 0x20:
                case 0x40:
                    Mem_copy4(e->ptr_4 + 0x10, wp->slot_F8, 0x18);
                    wp->ofs_9C     = (SVECTOR *)*e->ptr_8;
                    wp->ptr_A0     = e->ptr_8 + 1;
                    wp->data_88    = e->ptr_4;
                    wp->seq_tbl_90 = e->seq_tbl_C;
                    break;
                case 0x10:
                case 0x60:
                    wp->data_88 = e->ptr_4;
                    break;
                case 0x80:
                case 0xE0:
                    // Not model objects (WORK_48, WORK_50): their data pointer is the word at 0x14.
                    *(uint8 **)&wp->pos = e->ptr_4;
                    break;
            }
            return 1;
        }
    }
    Entry_missing_trap = 0;
    return 0;
}

// Closes every live object whose model data lies in the stage's first EBD file (below
// Stage_ebd_1), after detaching what rides it (func_80052528). The WORK_48 slots are closed
// without that step.
void func_8002FBF4(void)
{
    sint32 i;
    sint32 j;
    uint32 mask;
    WORK_3C0 *w3;
    WORK_5A4 *w5;
    PL_SHL_WORK *ps;
    SHL_WORK *sh;
    WORK_48 *fx;
    WORK_50 *w50;

    w3   = D_8009F108;
    mask = D_800987E8;
    for (i = 0; i < 16; i++, w3++)
    {
        if ((sint32)(mask << i) < 0 && w3->data_88 < (uint8 *)Stage_ebd_1)
        {
            func_80052528(w3);
            func_80031824(w3);
        }
    }
    w5   = D_800C3580;
    mask = D_80098B20;
    for (i = 0; i < 4; i++, w5++)
    {
        if ((sint32)(mask << i) < 0 && (uint8 *)w5->info_88 < (uint8 *)Stage_ebd_1)
        {
            func_80052528(w5);
            func_8003187C(w5);
        }
    }
    ps   = D_800BFB20;
    mask = D_800989F0;
    for (i = 0; i < 16; i++, ps++)
    {
        if ((sint32)(mask << i) < 0 && ps->code_88 < (uint32)Stage_ebd_1)
        {
            func_80052528(ps);
            func_80031930(ps);
        }
    }
    sh   = D_8009CF88;
    mask = D_800987CC;
    for (i = 0; i < 32; i++, sh++)
    {
        if ((sint32)(mask << i) < 0 && sh->efc.model.data < (uint8 *)Stage_ebd_1)
        {
            func_80052528(sh);
            Close_SHL_WORK(sh);
        }
    }
    fx = D_800A3B40;
    for (i = 0; i < 2; i++)
    {
        mask = (&D_80098838)[i];
        for (j = 0; j < 32; j++, fx++)
        {
            if ((sint32)(mask << j) < 0 && fx->efc.model.data < (uint8 *)Stage_ebd_1)
            {
                func_80031988(fx);
            }
        }
    }
    w50  = D_800BF118;
    mask = D_800989CC;
    for (i = 0; i < 32; i++, w50++)
    {
        if ((sint32)(mask << i) < 0 && w50->efc.model.data < (uint8 *)Stage_ebd_1)
        {
            func_80052528(w50);
            func_80031A4C(w50);
        }
    }
}

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

// Moves the object by (x, y, z) in its own frame (rotated by its facing), then rounds pos_l to pos.
void Obj_pos_set(MODEL_WORK *wp, sint16 x, sint16 y, sint16 z)
{
    VECTOR v;

    func_80030058(&v, wp->ang.vy, x, y, z);
    wp->pos_l.vx += v.vx;
    wp->pos_l.vy += v.vy;
    wp->pos_l.vz += v.vz;
    func_80030150(&wp->pos_l, &wp->pos);
}

void func_8002FF34(TURN_WORK *wp, sint16 x, sint16 y, sint16 z)
{
    VECTOR v;

    func_80030058(&v, wp->ang.vy, x, y, z);
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

// Rotates the offset (x, y, z) (in whole units, << 12) about Y by `angle` into out; a negative x
// is mirrored first (x and z negated, angle turned half a circle).
VECTOR *func_80030058(VECTOR *out, sint32 angle, sint16 x, sint16 y, sint16 z)
{
    VECTOR in;
    VECTOR res;
    long m[8];

    if (x < 0)
    {
        x = -x;
        z = -z;
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
    in.vx = z << 12;
    in.vy = y << 12;
    in.vz = -(x << 12);
    ApplyMatrixLV((MATRIX *)m, &in, &res);
    *out = res;
    return out;
}

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
    sv.vx = to->pos_C4.vx - from->pos_C4.vx;
    sv.vy = to->pos_C4.vy - from->pos_C4.vy;
    sv.vz = to->pos_C4.vz - from->pos_C4.vz;
    m[0]  = 0x1000;
    RotMatrixY(0x800 - from->ang.vy, (MATRIX *)m);
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

uint32 func_80030604(MODEL_WORK *from, MODEL_WORK *to, sint16 *shift, VECTOR *out)
{
    return func_80030628(from, to, shift, out, from->ang.vy);
}

// Same as func_80030418, with the view angle passed in and the positions at 0x14.
uint32 func_80030628(MODEL_WORK *from, MODEL_WORK *to, sint16 *shift, VECTOR *out, sint16 angle)
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
    sv.vx = to->pos.vx - from->pos.vx;
    sv.vy = to->pos.vy - from->pos.vy;
    m[0]  = 0x1000;
    sv.vz = to->pos.vz - from->pos.vz;
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

// Rotates the offset from -> to about Y by (0x800 - angle) with the GTE; returns 0x10 if the
// point is behind (z < 0), else 2 if |x| << (9 - *shift) is less than z (inside the view cone).
sint32 func_8003081C(SVECTOR *from, SVECTOR *to, sint16 *shift, sint16 angle)
{
    long m[8];
    SVECTOR sv;
    VECTOR out;
    long flag;
    sint32 ret;
    sint32 sh;

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
    m[0]  = 0x1000; // stored last in the target
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
        if (((out.vx >= 0) ? (out.vx << sh) : (-out.vx << sh)) < out.vz)
        {
            ret |= 2;
        }
    }
    return ret;
}

// Obj_launch_set with a gravity of 0x100.
void func_80030934(MODEL_WORK *wp, VIEW_WORK *to, sint16 speed, sint16 max)
{
    Obj_launch_set(wp, to, speed, max, 0x100);
}

// Launches wp at to's position (func_800309E0, the flight time to to->pos_C4.pad), with gravity
// grav in add.vy.
void Obj_launch_set(MODEL_WORK *wp, VIEW_WORK *to, sint16 speed, sint16 max, sint16 grav)
{
    func_800309E0(&wp->pos, &to->pos_C4, &wp->spd, &to->pos_C4.pad, speed, max, grav);
    wp->add.vz = 0;
    wp->add.vx = 0;
    wp->add.vy = grav;
}

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

sint16 func_80030CB8(MODEL_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist)
{
    return func_80030CF0(from, to, height, max_dist, 0x100);
}

sint16 func_80030CF0(MODEL_WORK *from, VIEW_WORK *to, sint16 height, sint16 max_dist, sint16 arc)
{
    return func_80030D30(&from->pos, &to->pos_C4, height, max_dist, arc);
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

void func_80030EE8(MODEL_WORK *wp, SVECTOR *target, sint16 speed)
{
    VECTOR d;
    VECTOR v;
    sint32 dist;

    d.vx = target->vx - wp->pos.vx;
    d.vy = target->vy - wp->pos.vy;
    d.vz = target->vz - wp->pos.vz;
    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    if (dist != 0)
    {
        v.vx        = (speed * d.vx << 8) / dist;
        v.vy        = (speed * d.vy << 8) / dist;
        v.vz        = (speed * d.vz << 8) / dist;
        wp->spd.vx  = v.vx;
        wp->spd.vy  = v.vy;
        wp->spd.vz  = v.vz;
        wp->spd.pad = dist / speed;
    }
    else
    {
        wp->spd.vx  = 0;
        wp->spd.vy  = 0;
        wp->spd.vz  = 0;
        wp->spd.pad = 0;
    }
    wp->add.vx = 0;
    wp->add.vy = 0;
    wp->add.vz = 0;
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

void func_80031324(WORK_5A4 *parent, CHILD_WORK *child, sint16 n)
{
    child->mtx_8C    = parent->mtx_240[n];
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
            wp         = &D_8009F108[i];
            wp->box_10 = 0;
            wp->hit_78 = 0;
            D_800987E8 |= 0x80000000 >> i;
            *(uint16 *)&wp->id_2      = 0;
            *(uint32 *)&wp->flag_4    = 0;
            *(uint32 *)&wp->field_C   = 0;
            *(uint32 *)&wp->routine_8 = 0;
            wp->flags                 = 3;
            *(uint32 *)&wp->field_74  = 0;
            return wp;
        }
    }
    return 0;
}

WORK_5A4 *func_80031498(void)
{
    sint32 i;
    WORK_5A4 *wp;
    uint32 used;

    used = D_80098B20;
    for (i = 0; i < 4; i++)
    {
        wp = &D_800C3580[i];
        if ((sint32)(used << i) >= 0)
        {
            D_80098B20 |= 0x80000000 >> i;
            wp->box_10                = 0;
            wp->hit_78                = 0;
            *(uint16 *)&wp->id_2      = 0;
            *(uint32 *)&wp->flag_4    = 0;
            *(uint32 *)&wp->field_C   = 0;
            *(uint32 *)&wp->routine_8 = 0;
            wp->flags                 = 3;
            *(uint32 *)&wp->field_74  = 0;
            return wp;
        }
    }
    return 0;
}

SHL_WORK *Open_SHL_WORK(void)
{
    sint32 i;
    SHL_WORK *wp;
    uint32 used;

    used = D_800987CC;
    for (i = 0; i < 0x20; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp         = &D_8009CF88[i];
            wp->box_10 = 0;
            wp->hit_78 = 0;
            D_800987CC |= 0x80000000 >> i;
            *(uint16 *)&wp->id_2      = 0;
            *(uint32 *)&wp->flag_4    = 0;
            *(uint32 *)&wp->field_C   = 0;
            *(uint32 *)&wp->routine_8 = 0;
            wp->flags                 = 3;
            *(uint32 *)&wp->field_74  = 0;
            return wp;
        }
    }
    return 0;
}

PL_SHL_WORK *func_80031598(void)
{
    sint32 i;
    PL_SHL_WORK *wp;
    uint32 used;

    used = D_800989F0;
    for (i = 0; i < 0x10; i++)
    {
        if ((sint32)(used << i) >= 0)
        {
            wp           = &D_800BFB20[i];
            wp->field_10 = 0;
            wp->hit_78   = 0;
            D_800989F0 |= 0x80000000 >> i;
            *(uint16 *)&wp->id_2      = 0;
            *(uint32 *)&wp->flag_4    = 0;
            *(uint32 *)&wp->field_C   = 0;
            *(uint32 *)&wp->routine_8 = 0;
            wp->flags                 = 3;
            *(uint32 *)&wp->field_74  = 0;
            return wp;
        }
    }
    return 0;
}

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
                *(uint16 *)&wp->id_2      = 0;
                *(uint32 *)&wp->flag_4    = 0;
                wp->field_C               = 0;
                *(uint32 *)&wp->routine_8 = 0;
                wp->flags                 = 3;
                wp->field_10              = 0;
                return wp;
            }
        }
    }
    return 0;
}

EVE_WORK *Open_EVE_WORK(void)
{
    sint32 i;
    EVE_WORK *wp;
    uint32 used;

    used = D_800987EC;
    for (i = 0; i < 0x10; i++)
    {
        wp = &D_800A2D08[i];
        if ((sint32)(used << i) >= 0)
        {
            D_800987EC |= 0x80000000 >> i;
            wp->field_10            = 0;
            *(uint16 *)&wp->id_2    = 0;
            *(uint32 *)&wp->flag_4  = 0;
            *(uint32 *)&wp->field_C = 0;
            *(uint32 *)&wp->field_8 = 0;
            wp->flags               = 3;
            return wp;
        }
    }
    return 0;
}

WORK_50 *func_80031734(void)
{
    sint32 i;
    WORK_50 *wp;
    uint32 used;

    used = D_800989CC;
    for (i = 0; i < 0x20; i++)
    {
        wp = &D_800BF118[i];
        if ((sint32)(used << i) >= 0)
        {
            D_800989CC |= 0x80000000 >> i;
            wp->box_10                = 0;
            *(uint16 *)&wp->id_2      = 0;
            *(uint32 *)&wp->flag_4    = 0;
            *(uint32 *)&wp->field_C   = 0;
            *(uint32 *)&wp->routine_8 = 0;
            wp->flags                 = 3;
            return wp;
        }
    }
    return 0;
}

WORK_50 *func_800317AC(sint32 i)
{
    WORK_50 *wp;

    if (i < 0x20)
    {
        if ((sint32)(D_800989CC << i) >= 0)
        {
            wp = &D_800BF118[i];
            D_800989CC |= 0x80000000 >> i;
            *(uint16 *)&wp->id_2      = 0;
            *(uint32 *)&wp->flag_4    = 0;
            *(uint32 *)&wp->field_C   = 0;
            *(uint32 *)&wp->routine_8 = 0;
            wp->flags                 = 3;
            wp->box_10                = 0;
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

void Close_SHL_WORK(SHL_WORK *wp)
{
    D_80098808 |= 0x80000000 >> (((uint32)wp - (uint32)D_8009CF88) / sizeof(SHL_WORK));
    D_80098808 &= D_800987CC;
    wp->routine_0 = 0;
}

void func_80031930(PL_SHL_WORK *wp)
{
    D_80098A60 |= 0x80000000 >> (((uint32)wp - (uint32)D_800BFB20) / sizeof(PL_SHL_WORK));
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

// Signed turn from the angle `rot` at pos toward target (Capcom's name, from eve19.c), limited to
// +-speed.
sint16 Muku(SVECTOR *pos, SVECTOR *target, sint32 rot, sint32 speed)
{
    uint32 d;
    uint32 u;
    sint16 r;

    r = speed;
    d = (Angle_xz_svector(pos, target) - (sint16)rot) & 0xFFF;
    if (d < 0x800 && d < (sint16)speed * 2)
    {
        r = d;
    }
    else if (d >= 0x800 && (u = 0x1000 - d) < r * 2)
    {
        r = u;
    }
    if (d < 0x801)
    {
        return r;
    }
    return -r;
}

// Muku on the pitch angle (func_8003129C): turns `rot` toward the direction pos -> target by at
// most `speed`, returning the signed step.
sint16 func_80031CA4(SVECTOR *pos, SVECTOR *target, sint32 rot, sint32 speed)
{
    uint32 d;
    uint32 u;
    sint16 r;

    r = speed;
    d = (func_8003129C(pos, target) - (sint16)rot) & 0xFFF;
    if (d < 0x800 && d < (sint16)speed * 2)
    {
        r = d;
    }
    else if (d >= 0x800 && (u = 0x1000 - d) < r * 2)
    {
        r = u;
    }
    if (d < 0x801)
    {
        return r;
    }
    return -r;
}

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

// 1 if the direction from -> to is within +-half1 of center1 and within +-half2 of
// (center2 - 0x800); the angles are on a 0x1000 circle.
sint32 func_80031DCC(VECTOR *from, sint32 center1, sint32 half1, VECTOR *to, sint32 center2, sint32 half2)
{
    sint32 angle;
    sint32 d1;
    sint32 d2;

    angle = Angle_xz_vector(from, to);
    center2 -= 0x800; // a separate statement: inline in d2's expression the registers differ
    d2 = (half2 + (angle - center2)) & 0xFFF;
    d1 = (half1 + (angle - center1)) & 0xFFF;
    if ((sint16)half1 * 2 >= d1)
    {
        if ((sint16)half2 * 2 >= d2)
        {
            return 1;
        }
    }
    return 0;
}

// Same as func_80031DCC without the 0x800 offset.
sint32 func_80031E60(VECTOR *from, sint32 center1, sint32 half1, VECTOR *to, sint32 center2, sint32 half2)
{
    sint32 angle;
    sint32 d1;
    sint32 d2;

    angle = Angle_xz_vector(from, to);
    d2    = (half2 + (angle - center2)) & 0xFFF;
    d1    = (half1 + (angle - center1)) & 0xFFF;
    if ((sint16)half1 * 2 >= d1)
    {
        if ((sint16)half2 * 2 >= d2)
        {
            return 1;
        }
    }
    return 0;
}

// func_80031DCC on SVECTORs.
sint32 func_80031EF0(SVECTOR *from, sint32 center1, sint32 half1, SVECTOR *to, sint32 center2, sint32 half2)
{
    sint32 angle;
    sint32 d1;
    sint32 d2;

    angle = Angle_xz_svector(from, to);
    center2 -= 0x800;
    d2 = (half2 + (angle - center2)) & 0xFFF;
    d1 = (half1 + (angle - center1)) & 0xFFF;
    if ((sint16)half1 * 2 >= d1)
    {
        if ((sint16)half2 * 2 >= d2)
        {
            return 1;
        }
    }
    return 0;
}

// Quantizes the facing of from -> to against `base`: the low 12 bits are an angle, bits 16+ say
// which side (0: none/forward, 1: behind, 2: right, 3: left). When bit 0 of to->pad is clear,
// the direction is taken from `to` toward the zero vector (D_80097CF4) instead.
sint32 func_80031F84(SVECTOR *from, SVECTOR *to, sint16 base, uint16 mode)
{
    sint32 ret;
    sint32 ang;
    sint32 s;
    sint32 d;

    ret = 0;
    if (!(to->pad & 1))
    {
        ang = Angle_xz_svector(to, &D_80097CF4);
    }
    else
    {
        ang = Angle_xz_svector(from, to);
    }
    if (mode == 0)
    {
        s = (sint16)ang;
        if (((s - base + 0x400) & 0xFFF) < 0x800)
        {
            ret = (s + 0x800) & 0xFFF;
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

// Starts the player's keyframe set `set` at step idx (the table bank by set >> 4, as
// func_800321C8), then unpacks the pose and builds the skeleton.
void func_800320B8(PL_WORK *wp, uint32 set, sint32 idx)
{
    KEY_ENT *base;

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
            if (wp->weapon_right_no != 0)
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
            if (wp->unk171 != 0)
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
    wp->seq_94      = base;
    wp->ptr_98      = &base[idx];
    wp->idx_AC      = set;
    wp->cmd_A4.word = base[idx].cmd.word;
    Pl_pose_unpack(wp);
    Pl_joint_mtx_set(wp);
}

void func_800321C8(PL_WORK *wp, sint32 unused, uint32 set, sint32 idx)
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
            if (wp->weapon_right_no != 0)
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
            if (wp->unk171 != 0)
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

// Starts keyframe sequence idx at step (as func_80032304), then unpacks the pose and builds the
// parts' matrices.
void func_800322A8(MODEL_WORK *wp, sint32 idx, sint32 step)
{
    KEY_ENT *ent;

    ent        = wp->seq_tbl_90[idx];
    wp->idx_AC = idx;
    wp->seq_94 = ent;
    ent        = ent + step;
    wp->ptr_98 = ent;
    wp->cmd_A4 = ent->cmd;
    Model_pose_unpack(wp);
    Model_parts_mtx_set_y(wp);
}

void func_80032304(MODEL_WORK *wp, sint32 idx, sint32 step)
{
    KEY_ENT *ent;

    ent        = wp->seq_tbl_90[idx];
    wp->idx_AC = idx;
    wp->seq_94 = ent;
    ent        = ent + step;
    wp->ptr_98 = ent;
    wp->cmd_A4 = ent->cmd;
    Model_pose_unpack(wp);
}

// Steps the player's keyframe sequence (as func_80032538), then unpacks the pose and builds the
// skeleton.
void func_8003234C(PL_WORK *wp)
{
    KEY_ENT *ent;
    KEY_ENT *next;
    sint8 ctl;

    ent = wp->ptr_98;
    if (--wp->cmd_A4.b.time == 0)
    {
        ctl = ent->cmd.b.ctl;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->cmd_A4.b.time = ent->cmd.b.time;
            }
            else
            {
                ent             = &wp->seq_94[ctl & 0x7F];
                wp->ptr_98      = ent;
                wp->cmd_A4.word = ent->cmd.word;
            }
        }
        else
        {
            next            = wp->ptr_98;
            wp->ptr_98      = next + 1;
            wp->cmd_A4.word = next[1].cmd.word;
        }
    }
    Pl_pose_unpack(wp);
    Pl_joint_mtx_set(wp);
}

void func_800323FC(PL_WORK *wp, sint32 mix)
{
    KEY_ENT *ent;
    KEY_ENT *next;
    sint8 ctl;

    wp->pose_mix = mix;
    ent          = wp->ent_FC;
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
                // chained: keeps the target's load order (the timer byte before ent_FC)
                ent = wp->ent_FC = &wp->tbl_F8[ctl & 0x7F];
                wp->cmd_100.word = ent->cmd.word;
            }
        }
        else
        {
            next             = wp->ent_FC;
            wp->ent_FC       = next + 1;
            wp->cmd_100.word = next[1].cmd.word;
        }
    }
}

// Steps the keyframe sequence (as func_80032538), then unpacks the pose and builds the parts'
// matrices.
void func_80032488(MODEL_WORK *wp)
{
    KEY_ENT *ent;
    KEY_ENT *next;
    sint8 ctl;

    ent = wp->ptr_98;
    if (--wp->cmd_A4.b.time == 0)
    {
        ctl = ent->cmd.b.ctl;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->cmd_A4.b.time = ent->cmd.b.time;
            }
            else
            {
                ent             = &wp->seq_94[ctl & 0x7F];
                wp->ptr_98      = ent;
                wp->cmd_A4.word = ent->cmd.word;
            }
        }
        else
        {
            next            = wp->ptr_98;
            wp->ptr_98      = next + 1;
            wp->cmd_A4.word = next[1].cmd.word;
        }
    }
    Model_pose_unpack(wp);
    Model_parts_mtx_set_y(wp);
}

void func_80032538(MODEL_WORK *wp)
{
    KEY_ENT *ent;
    KEY_ENT *next;
    sint8 ctl;

    ent = wp->ptr_98;
    if (--wp->cmd_A4.b.time == 0)
    {
        ctl = ent->cmd.b.ctl;
        if (ctl < 0)
        {
            if (ctl == -1)
            {
                wp->cmd_A4.b.time = ent->cmd.b.time;
            }
            else
            {
                ent             = &wp->seq_94[ctl & 0x7F];
                wp->ptr_98      = ent;
                wp->cmd_A4.word = ent->cmd.word;
            }
        }
        else
        {
            next            = wp->ptr_98;
            wp->ptr_98      = next + 1;
            wp->cmd_A4.word = next[1].cmd.word;
        }
    }
    Model_pose_unpack(wp);
}

// Builds the player's skeleton: the body matrix from pos and ang.vy, then each joint's matrix and
// position (func_800331A0) from the scratchpad pose and Joint_ofs_tbl, pushing and popping the
// matrix stack per limb. pose_mix picks the second pose for some limbs.
void Pl_joint_mtx_set(PL_WORK *wp)
{
    SVECTOR rot;
    VECTOR out;
    SVECTOR *pose_a;
    SVECTOR *pose_b;
    SVECTOR *pose_c;
    SVECTOR *ofs;
    SVECTOR *root;

    func_800333A0();
    Scratch_mtx.t[0] = wp->pos.vx << Scratch_scale_shift;
    Scratch_mtx.t[1] = wp->pos.vy << Scratch_scale_shift;
    Scratch_mtx.t[2] = wp->pos.vz << Scratch_scale_shift;
    rot.vx           = 0;
    rot.vy           = wp->ang.vy - wp->unk116;
    rot.vz           = 0;
    RotMatrix(&rot, &Scratch_mtx);
    root         = Scratch_pose; // kept in a register for the second joint 0 call
    wp->base_mtx = Scratch_mtx;
    ofs          = Joint_ofs_tbl;
    matrix_push(&Scratch_mtx);
    func_800331A0(wp, 0, &Scratch_pose[1], &Scratch_pose[0]);
    func_800331A0(wp, 8, &Scratch_pose[9], &ofs[8]);
    matrix_push(&Scratch_mtx);
    func_800331A0(wp, 9, &Scratch_pose[10], &ofs[9]);
    func_800331A0(wp, 10, &Scratch_pose[11], &ofs[10]);
    func_800331A0(wp, 11, &Scratch_pose[12], &ofs[11]);
    matrix_pop(&Scratch_mtx);
    func_800331A0(wp, 12, &Scratch_pose[13], &ofs[12]);
    func_800331A0(wp, 13, &Scratch_pose[14], &ofs[13]);
    func_800331A0(wp, 14, &Scratch_pose[15], &ofs[14]);
    matrix_pop(&Scratch_mtx);
    switch (wp->pose_mix)
    {
        case 0:
        default:
            pose_a = Scratch_pose;
            pose_b = Scratch_pose;
            pose_c = Scratch_pose;
            break;
        case 1:
            pose_a = Scratch_pose + 16;
            pose_b = Scratch_pose + 16;
            pose_c = Scratch_pose;
            break;
        case 2:
            pose_a = Scratch_pose + 16;
            pose_b = Scratch_pose;
            pose_c = Scratch_pose + 16;
            break;
        case 3:
            pose_a = Scratch_pose + 16;
            pose_b = Scratch_pose + 16;
            pose_c = Scratch_pose + 16;
            break;
    }
    func_800331A0(wp, 0, &pose_a[1], root);
    matrix_push(&Scratch_mtx);
    rot = pose_a[2];
    rot.vy += wp->turn_B4 * 5;
    func_800331A0(wp, 1, &rot, &ofs[1]);
    rot.vx = 0;
    rot.vy = -0x96;
    rot.vz = 0;
    ApplyMatrix(&Scratch_mtx, &rot, &out);
    wp->pos_420.vx = Scratch_mtx.t[0] + out.vx;
    wp->pos_420.vy = Scratch_mtx.t[1] + out.vy;
    wp->pos_420.vz = Scratch_mtx.t[2] + out.vz;
    matrix_pop(&Scratch_mtx);
    matrix_push(&Scratch_mtx);
    func_800331A0(wp, 2, &pose_b[3], &ofs[2]);
    func_800331A0(wp, 3, &pose_b[4], &ofs[3]);
    func_800331A0(wp, 4, &pose_b[5], &ofs[4]);
    matrix_pop(&Scratch_mtx);
    matrix_push(&Scratch_mtx);
    func_800331A0(wp, 5, &pose_c[6], &ofs[5]);
    func_800331A0(wp, 6, &pose_c[7], &ofs[6]);
    func_800331A0(wp, 7, &pose_c[8], &ofs[7]);
    matrix_pop(&Scratch_mtx);
}

// Unpacks the player's two current poses into Scratch_pose: the pose of keyframe set idx_AC (step
// ptr_98) into [0..15] and the pose of set set_104 (step ent_FC) into [16..24], 12 bits per value
// (the slots left at 0 are angles the pose doesn't carry); the root rotation is sign-extended.
void Pl_pose_unpack(PL_WORK *wp)
{
    uint32 ***tbl;
    uint32 ***tbl2;
    uint8 set;
    uint8 set2;
    uint32 *src;
    uint16 *dst;

    set = wp->idx_AC;
    switch ((sint8)set >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            tbl = Pose_tbl_a;
            break;
        case 4:
        case 5:
            tbl = wp->weapon_right_no ? Pose_tbl_c_alt : Pose_tbl_c;
            set -= 0x40;
            break;
        case 6:
        case 7:
            tbl = wp->unk171 ? Pose_tbl_d_alt : Pose_tbl_d;
            set -= 0x60;
            break;
        case 8:
        default:
            tbl = Pose_tbl_b;
            set -= 0x80;
            break;
    }
    set2 = wp->set_104;
    switch ((sint8)set2 >> 4)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            tbl2 = Pose_tbl_a;
            break;
        case 4:
        case 5:
            tbl2 = wp->weapon_right_no ? Pose_tbl_c_alt : Pose_tbl_c;
            set2 -= 0x40;
            break;
        case 6:
        case 7:
            tbl2 = wp->unk171 ? Pose_tbl_d_alt : Pose_tbl_d;
            set2 -= 0x60;
            break;
        case 8:
        default:
            tbl2 = Pose_tbl_b;
            set2 -= 0x80;
            break;
    }
    Mem_copy4(tbl[(sint8)set][wp->ptr_98->cmd.b.b0], Scratch_pl_pose_packed, 0x12);
    Mem_copy4(tbl2[(sint8)set2][wp->ent_FC->cmd.b.b0], Scratch_pl_pose_packed2, 0xC);
    // A uint16 pointer, not Scratch_pose's fields: the stores are scalars, which keeps the
    // target's scheduling.
    dst    = (uint16 *)Scratch_pose;
    src    = Scratch_pl_pose_packed;
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
    src    = Scratch_pl_pose_packed2;
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
    // The root rotation's components are signed 12-bit values. x as a plain halfword, y and z as
    // fields: that keeps the target's order against the last stores above.
    *(uint16 *)Scratch_pose = (sint32)(*(uint16 *)Scratch_pose << 20) >> 20;
    Scratch_pose->vy        = (sint32)((uint16)Scratch_pose->vy << 20) >> 20;
    Scratch_pose->vz        = (sint32)((uint16)Scratch_pose->vz << 20) >> 20;
}

void func_800331A0(PL_WORK *wp, sint32 n, SVECTOR *rot, SVECTOR *off)
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
    v.vx                = wp->pos.vx << Scratch_scale_shift;
    v.vy                = wp->pos.vy << Scratch_scale_shift;
    v.vz                = wp->pos.vz << Scratch_scale_shift;
    wp->joint_pos[n].vx = (Scratch_mtx.t[0] + v.vx * 7 + 4) >> 3;
    wp->joint_pos[n].vy = (Scratch_mtx.t[1] + v.vy * 7 + 4) >> 3;
    wp->joint_pos[n].vz = (Scratch_mtx.t[2] + v.vz * 7 + 4) >> 3;
    wp->joint_mtx[n]    = Scratch_mtx;
    scale.vx            = D_80097CFC << Scratch_scale_shift;
    scale.vy            = scale.vx;
    scale.vz            = scale.vx;
    ScaleMatrix(&wp->joint_mtx[n], &scale);
}

void func_800333A0(void)
{
    D_80098A80 = D_800BC728;
}

// Pushes a matrix onto the matrix stack at D_80098A80.
void matrix_push(MATRIX *src)
{
    *--D_80098A80 = *src;
}

// Pops a matrix from the matrix stack at D_80098A80.
void matrix_pop(MATRIX *dst)
{
    *dst = *D_80098A80;
    D_80098A80++;
}

// Builds a model object's part matrices, turned by its Y angle only.
void Model_parts_mtx_set_y(MODEL_WORK *wp)
{
    SVECTOR rot;
    MATRIX m;

    rot.vx = 0;
    rot.vy = wp->ang.vy;
    rot.vz = 0;
    RotMatrix(&rot, &m);
    Model_parts_mtx_set(wp, &m);
}

// Builds a model object's part matrices, turned by its full rotation (Y, X, Z order).
void Model_parts_mtx_set_yxz(MODEL_WORK *wp)
{
    MATRIX m;

    RotMatrixYXZ(&wp->ang, &m);
    Model_parts_mtx_set(wp, &m);
}

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

// Builds a model object's part matrices from its body rotation m: the body (mtx_160, part 0) gets
// m times the root pose rotation, each part its parent's matrix times its pose rotation (or the
// root's rotation when part_2 is 0); then scales them (scale_158, per part with the scale table
// when flags bit 6 is set) and places each part at its parent's position plus its offset.
void Model_parts_mtx_set(MODEL_WORK *wp, MATRIX *m)
{
    SVECTOR scale;
    MATRIX rot;
    VECTOR v;
    SVECTOR *ofs;
    SVECTOR *pose;
    MATRIX *mtx;
    RGB_ENT *sc;
    CHILD_SLOT *slot;
    uint32 count;
    sint8 parent;
    uint32 part;
    uint32 i;
    uint16 z;

    if (func_8002FE74(wp->kind_1) == 0x40)
    {
        mtx = ((WORK_5A4 *)wp)->mtx_240;
    }
    else
    {
        mtx = ((WORK_3C0 *)wp)->mtx_1E8;
    }
    pose        = Scratch_pose;
    ofs         = wp->ofs_9C;
    wp->mtx_160 = *m;
    scale.vx    = wp->scale_158.vx << Scratch_scale_shift;
    scale.vy    = wp->scale_158.vy << Scratch_scale_shift;
    scale.vz    = wp->scale_158.vz << Scratch_scale_shift;
    RotMatrix(&Scratch_pose[1], &rot);
    MulMatrix0(m, &rot, mtx);
    count = wp->slot_F8[0].child_id;
    for (i = 1; i < count; i++)
    {
        // The slot's byte offset from wp, not &wp->slot_F8[i]: the target steps the offset
        // (0xFC, +4) and adds wp each pass.
        slot   = (CHILD_SLOT *)((uint8 *)wp + (i * 4 + 0xF8));
        parent = slot->child_id;
        part   = slot->part_2;
        if (parent >= 0)
        {
            if (part != 0)
            {
                RotMatrix(&pose[part + 1], &rot);
                MulMatrix0(&mtx[parent], &rot, &mtx[i]);
            }
            else
            {
                *(MATRIX_ROT *)&mtx[i] = *(MATRIX_ROT *)&mtx[0];
            }
        }
    }
    if (wp->flags & 0x40)
    {
        if (func_8002FE74(wp->kind_1) == 0x40)
        {
            sc = &((WORK_5A4 *)wp)->base;
        }
        else
        {
            sc = &((WORK_3C0 *)wp)->base;
        }
        v.vx = ((wp->scale_158.vx * sc[0].r) << Scratch_scale_shift) >> 5;
        v.vy = ((wp->scale_158.vy * sc[0].g) << Scratch_scale_shift) >> 5;
        v.vz = ((wp->scale_158.vz * sc[0].b) << Scratch_scale_shift) >> 5;
        ScaleMatrix(&wp->mtx_160, &v);
        for (i = 0; i < count; i++)
        {
            v.vx = ((wp->scale_158.vx * sc[i + 1].r) << Scratch_scale_shift) >> 5;
            v.vy = ((wp->scale_158.vy * sc[i + 1].g) << Scratch_scale_shift) >> 5;
            v.vz = ((wp->scale_158.vz * sc[i + 1].b) << Scratch_scale_shift) >> 5;
            ScaleMatrix(&mtx[i], &v);
        }
    }
    else
    {
        v.vx = scale.vx;
        v.vy = scale.vy;
        v.vz = scale.vz;
        ScaleMatrix(&wp->mtx_160, &v);
        for (i = 0; i < count; i++)
        {
            ScaleMatrix(&mtx[i], &v);
        }
    }
    pose->vx = (uint16)pose->vx * 8;
    pose->vy = (uint16)pose->vy * 8;
    pose->vz = (uint16)pose->vz * 8;
    ApplyMatrix(&wp->mtx_160, pose, &v);
    wp->part_180[0].vx = v.vx + (wp->pos.vx << Scratch_scale_shift);
    wp->part_180[0].vy = v.vy + (wp->pos.vy << Scratch_scale_shift);
    wp->part_180[0].vz = v.vz + (wp->pos.vz << Scratch_scale_shift);
    for (i = 1; i < count; i++)
    {
        slot   = (CHILD_SLOT *)((uint8 *)wp + (i * 4 + 0xF8));
        parent = slot->child_id;
        part   = slot->part_2;
        if (parent >= 0)
        {
            if (part != 0)
            {
                ApplyMatrix(&mtx[parent], &ofs[part], &v);
                wp->part_180[i].vx = wp->part_180[parent].vx + v.vx;
                wp->part_180[i].vy = wp->part_180[parent].vy + v.vy;
                z                  = wp->part_180[parent].vz + v.vz;
            }
            else
            {
                wp->part_180[i].vx = wp->part_180[0].vx;
                wp->part_180[i].vy = wp->part_180[0].vy;
                z                  = wp->part_180[0].vz;
            }
            wp->part_180[i].vz = z;
        }
    }
}

// Unpacks 75 twelve-bit values (three per SVECTOR) of the pose selected by wp into the scratchpad.
// The first SVECTOR's three values are then sign-extended from 12 bits.
void Model_pose_unpack(MODEL_WORK *wp)
{
    uint32 *s;
    uint16 *d;
    sint32 i;

    Mem_copy4(((uint32 **)((uint32 ***)wp->ptr_A0)[wp->idx_AC])[wp->ptr_98->cmd.b.b0], Scratch_pose_packed, 0x20);
    d = (uint16 *)Scratch_pose;
    s = Scratch_pose_packed;
    for (i = 3; i != 0; i--)
    {
        *d++ = *s & 0xFFF;
        *d++ = (*s & 0xFFF000) >> 12;
        *d   = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
        s++;
        d += 2;
        *d++ = (*s & 0xFFF0) >> 4;
        *d++ = (*s & 0xFFF0000) >> 16;
        *d   = ((*s & 0xF0000000) >> 28) | ((s[1] & 0xFF) << 4);
        s++;
        d += 2;
        *d++ = (*s & 0xFFF00) >> 8;
        *d++ = (*s & 0xFFF00000) >> 20;
        s++;
        *d = *s & 0xFFF;
        d += 2;
        *d++ = (*s & 0xFFF000) >> 12;
        *d++ = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
        s++;
        *d = (*s & 0xFFF0) >> 4;
        d += 2;
        *d++ = (*s & 0xFFF0000) >> 16;
        *d++ = ((*s & 0xF0000000) >> 28) | ((s[1] & 0xFF) << 4);
        s++;
        *d = (*s & 0xFFF00) >> 8;
        d += 2;
        *d++ = (*s & 0xFFF00000) >> 20;
        s++;
        *d++ = *s & 0xFFF;
        *d   = (*s & 0xFFF000) >> 12;
        d += 2;
        *d++ = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
        s++;
        *d++ = (*s & 0xFFF0) >> 4;
        *d   = (*s & 0xFFF0000) >> 16;
        d += 2;
        *d++ = ((*s & 0xF0000000) >> 28) | ((s[1] & 0xFF) << 4);
        s++;
        *d++ = (*s & 0xFFF00) >> 8;
        *d   = (*s & 0xFFF00000) >> 20;
        s++;
        d += 2;
    }
    *d++             = *s & 0xFFF;
    *d               = (*s & 0xFFF000) >> 12;
    d[1]             = ((*s & 0xFF000000) >> 24) | ((s[1] & 0xF) << 8);
    Scratch_pose->vx = (sint32)((uint16)Scratch_pose->vx << 20) >> 20;
    Scratch_pose->vy = (sint32)((uint16)Scratch_pose->vy << 20) >> 20;
    Scratch_pose->vz = (sint32)((uint16)Scratch_pose->vz << 20) >> 20;
}

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
    D_800988E0         = 0;
    D_80098798         = 0xFF;
    D_8009A300[0].id_6 = 0;
    D_8009A300[1].id_6 = 0;
    D_8009A300[2].id_6 = 0;
    D_8009A300[3].id_6 = 0;
    D_80098560         = 0;
    D_80098564         = 0;
    D_80098568         = 0;
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

// Per-frame hit pass over the queued requests (D_800A2F48): runs the lock-on search, stores the
// player's target in D_80097D08, then tests every pair whose kinds may meet (bit 0x80 of
// D_80097D00[kind i] << kind j) and whose owners differ in the top byte of flags. Times the pass in
// D_800D9BF4 (before the pairs) and D_800D9BF8 (total), like Obj_draw_all.
void Hit_check_all(void)
{
    uint32 i;
    uint32 j;
    uint32 n;
    uint32 mask;

    D_800D9BE4 = VSync(1);
    mask       = 0xFF000000;
    lock_on_search();
    D_80097D08 = func_800358F0(&Player_work[0]);
    n          = D_800988E0;
    D_800988E0 = 0;
    if (n < 2)
    {
        return;
    }
    D_800D9BF4 = (VSync(1) - D_800D9BE4) & 0xFFFF;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            // v.pad read as halfword 3 of each entry (see lock_on_search); D_80097D00-D_80097D03
            // are read as one table by kind.
            if ((((&D_80097D00)[((uint16 *)D_800A2F48)[i * 6 + 3] >> 13] << (((uint16 *)D_800A2F48)[j * 6 + 3] >> 13)) & 0x80) &&
                ((D_800A2F48[i].flags ^ D_800A2F48[j].flags) & mask))
            {
                hit_pair_check(&i, &j);
            }
        }
    }
    D_800D9BF8 = (VSync(1) - D_800D9BE4) & 0xFFFF;
}

// Hit test between the queued requests D_800A2F48[*pi] and [*pj]: spheres (radius pad & 0x1FF), or
// capsules when pad bits 9-10 are set (the next entry is the other end, tested in eighths, and
// *pi / *pj step past it). On a hit, each side's owner gets the other's top flag byte and, unless
// masked by the kind bits, its damage in hit_0, and, when its word has bit 23, where it was hit.
void hit_pair_check(uint32 *pi, uint32 *pj)
{
    SVECTOR a[2];
    SVECTOR b[2];
    SLOT_OWNER *m;
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
        a[0] = D_800A2F48[*pi].v;
    } while (0);
    b[0]     = D_800A2F48[*pj].v;
    ra       = a[0].pad & 0x1FF;
    rb       = b[0].pad & 0x1FF;
    ta       = (uint16)((rb + ra) * 4); // the radius sum, then the first loop's counter
    cap_a    = (a[0].pad & 0x600) >> 9;
    cap_b    = (b[0].pad & 0x600) >> 9;
    a[0].pad = ra * 4;
    b[0].pad = rb * 4;
    flags    = ta * 2;
    if ((uint32)(a[0].vx - b[0].vx + ta) > flags || (uint32)(a[0].vy - b[0].vy + ta) > flags || (uint32)(a[0].vz - b[0].vz + ta) > flags)
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
        a[1].vx  = D_800A2F48[*pi + 1].v.vx;
        a[1].vy  = D_800A2F48[*pi + 1].v.vy;
        a[1].vz  = D_800A2F48[*pi + 1].v.vz;
        a[1].pad = (D_800A2F48[*pi + 1].v.pad & 0x1FF) * 4;
        step_a   = 8 >> cap_a;
        (*pi)++;
    }
    if (cap_b)
    {
        b[1].vx  = D_800A2F48[*pj + 1].v.vx;
        b[1].vy  = D_800A2F48[*pj + 1].v.vy;
        b[1].vz  = D_800A2F48[*pj + 1].v.vz;
        b[1].pad = (D_800A2F48[*pj + 1].v.pad & 0x1FF) * 4;
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
            word  = D_800A2F48[*pi].flags;
            other = D_800A32E0[*pj];
            m     = (SLOT_OWNER *)(word & 0x7FFFFF);
            flags = m->hit_0;
            flags |= other & 0xFF000000;
            // v.pad read as halfword 3 of each entry (see lock_on_search).
            if ((sint32)((D_800A32E0[*pi] & 0xFF0000) << ((((uint16 *)D_800A2F48)[*pj * 6 + 3] >> 13) + 8)) >= 0)
            {
                flags += other & 0xFFFF;
            }
            m->hit_0 = flags;
            do
            {
                if (word & 0x800000)
                {
                    x = b[0].vx - b[1].vx;
                    y = b[0].vy - b[1].vy;
                    z = b[0].vz - b[1].vz;
                    if (cap_b == 0)
                    {
                        m->vec_8.vx  = (b[0].vx * (8 - tb) + b[1].vx * tb) / 8;
                        m->vec_8.vy  = (b[0].vy * (8 - tb) + b[1].vy * tb) / 8;
                        m->vec_8.vz  = (b[0].vz * (8 - tb) + b[1].vz * tb) / 8;
                        m->vec_8.pad = 1;
                    }
                    else
                    {
                        m->vec_8.vx  = x;
                        m->vec_8.vy  = y;
                        m->vec_8.vz  = z;
                        m->vec_8.pad = 0;
                    }
                }
            } while (0);
            word  = D_800A2F48[*pj].flags;
            other = D_800A32E0[*pi];
            m     = (SLOT_OWNER *)(word & 0x7FFFFF);
            flags = m->hit_0;
            flags |= other & 0xFF000000;
            if ((sint32)((D_800A32E0[*pj] & 0xFF0000) << ((((uint16 *)D_800A2F48)[*pi * 6 + 3] >> 13) + 8)) >= 0)
            {
                flags += other & 0xFFFF;
            }
            m->hit_0 = flags;
            do
            {
                if (word & 0x800000)
                {
                    x = a[0].vx - a[1].vx;
                    y = a[0].vy - a[1].vy;
                    z = a[0].vz - a[1].vz;
                    if (cap_a == 0)
                    {
                        m->vec_8.vx  = (a[0].vx * (8 - tb) + a[1].vx * tb) / 8;
                        m->vec_8.vy  = (a[0].vy * (8 - tb) + a[1].vy * tb) / 8;
                        m->vec_8.vz  = (a[0].vz * (8 - tb) + a[1].vz * tb) / 8;
                        m->vec_8.pad = 1;
                    }
                    else
                    {
                        m->vec_8.vx  = x;
                        m->vec_8.vy  = y;
                        m->vec_8.vz  = z;
                        m->vec_8.pad = 0;
                    }
                }
            } while (0);
            return;
        }
    }
}

// Lock-on search: projects the queued requests (D_800A2F48; a pair flagged in pad bits 9-10 counts
// as its midpoint) whose kind bit is in the player's mask, and picks the one nearest the screen's
// centre column in two windows: a fixed one (target a, kept when unk174 bit 5 is set) and the
// LOCK_BOX of the special level (target b, unk174 bit 4). Each found target, or none, is handed to
// pl_shot_spawn.
void lock_on_search(void)
{
    MATRIX unused;
    sint16 sxy[2];
    SVECTOR pos_a;
    SVECTOR pos_b;
    SVECTOR c;
    sint32 sz;
    sint32 z;
    uint32 n;
    sint32 box;
    uint32 i;
    uint32 j;
    sint32 best_a;
    sint32 best_b;
    sint32 x_a;
    sint32 x_b;
    uint8 mask;

    func_80035508();
    n = D_800988E0;
    if (Player_work[0].weapon_right_no == 8)
    {
        box = Player_work[0].rec[8].sp_perform;
    }
    else
    {
        box = 0;
    }
    for (i = 0; i < 1; i++)
    {
        if (!(Player_work[i].unk00 & 1))
        {
            continue;
        }
        x_b    = 0x7FFFFFFF;
        x_a    = 0x7FFFFFFF;
        best_b = -1;
        best_a = -1;
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_SetTransMatrix(&Scratch_view_mtx);
        if (i != 0)
        {
            mask = D_80097D03;
        }
        else
        {
            mask = D_80097D02;
        }
        gte_ldv0(&Player_work[i].pos);
        gte_rtps();
        gte_stszotz(&sz);
        sz += 50;
        for (j = 0; j < n; j++)
        {
            // v.pad read as halfword 3 of the 6 in each entry: the target reaches it through a
            // base kept in a register, unlike the v.pad test below.
            if (!((mask << (((uint16 *)D_800A2F48)[j * 6 + 3] >> 13)) & 0x80))
            {
                continue;
            }
            if (D_800A2F48[j].v.pad & 0x600)
            {
                c.vx = (D_800A2F48[j].v.vx + D_800A2F48[j + 1].v.vx) >> 1;
                c.vy = (D_800A2F48[j].v.vy + D_800A2F48[j + 1].v.vy) >> 1;
                c.vz = (D_800A2F48[j].v.vz + D_800A2F48[j + 1].v.vz) >> 1;
                j++;
            }
            else
            {
                c = D_800A2F48[j].v;
            }
            if (((SLOT_OWNER *)(D_800A2F48[j].flags & 0x7FFFFF))->mask_4 & 0x80)
            {
                continue;
            }
            gte_ldv0(&c);
            gte_rtps();
            gte_stszotz(&z);
            gte_stsxy(sxy);
            if (!(z > sz))
            {
                continue;
            }
            if (z < 0x500 && (uint16)(sxy[0] - 0x83) < 0x3B && (uint16)(sxy[1] - 1) < 0xEF)
            {
                if (ABS(0xA0 - x_a) > ABS(0xA0 - sxy[0]))
                {
                    best_a = j;
                    x_a    = sxy[0];
                    pos_a  = c;
                }
            }
            if (z > sz && z < D_8008994C[box].z_max && sxy[0] > D_8008994C[box].x_min && sxy[0] < D_8008994C[box].x_max &&
                sxy[1] > D_8008994C[box].y_min && sxy[1] < D_8008994C[box].y_max)
            {
                if (ABS(0xA0 - x_b) > ABS(0xA0 - sxy[0]))
                {
                    best_b = j;
                    x_b    = sxy[0];
                    pos_b  = c;
                }
            }
        }
        if (best_a >= 0)
        {
            if (Player_work[i].unk174 & 0x20)
            {
                pl_shot_spawn(&c, 1, &Player_work[i], best_a, 0);
            }
        }
        else if (Player_work[i].unk174 & 0x20)
        {
            pl_shot_spawn(&c, 0, &Player_work[i], -1, 0);
        }
        if (best_b >= 0)
        {
            if (Player_work[i].unk174 & 0x10)
            {
                pl_shot_spawn(&c, 1, &Player_work[i], best_b, 1);
            }
        }
        else if (Player_work[i].unk174 & 0x10)
        {
            pl_shot_spawn(&c, 0, &Player_work[i], -1, 1);
        }
    }
}

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

// Projects the position (+0xBC) of every claimed slot of D_800BE478 through the view matrix and
// clears it. The screen XY and depth go to locals and are never used (left over, or a debug aid).
void func_80035508(void)
{
    SVECTOR sxy; // only the first word is written (screen x, y); 8 bytes in the frame
    long otz;
    uint32 mask;
    sint32 i;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    mask = D_80098798 & 0xFFFFFF00;
    if (mask != 0)
    {
        for (i = 0; i < 0x18; i++)
        {
            if (mask >= 0x80000000)
            {
                gte_ldv0((SVECTOR *)(D_800BE478[i] + 0xBC));
                gte_rtps();
                *(uint32 *)(D_800BE478[i] + 0xBC) = 0;
                *(uint32 *)(D_800BE478[i] + 0xC0) = 0;
                gte_stszotz(&otz);
                gte_stsxy(&sxy);
            }
            mask <<= 1;
        }
    }
}

MATRIX *func_800355F0(MATRIX *out, sint32 n, sint32 yaw)
{
    SVECTOR rot;
    VECTOR pos;
    MATRIX m;
    MATRIX inv;

    rot.vx = -yaw & 0xFFF;
    rot.vy = ((uint16)Player_work[n].ang.vy + Player_work[n].unk116 + 0x800) & 0xFFF;
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

// Spawns a player shot (from the right or left weapon's joint, by flag), locked on to target idx of
// D_800A2F48 when idx >= 0, and uses up one round of that weapon unless it is unlimited.
void pl_shot_spawn(SVECTOR *pos, sint32 found, PL_WORK *pl, sint32 idx, sint32 flag)
{
    PL_SHL_WORK *wp;
    sint32 sel;
    sint32 slot;

    wp = func_80031598();
    if (wp != NULL)
    {
        wp->type_3 = 0;
        if (idx >= 0)
        {
            slot       = func_8003545C((uint32)wp, (SLOT_OWNER *)(D_800A2F48[idx].flags & 0x7FFFFF));
            wp->slot_D = slot;
            if ((sint8)slot >= 0)
            {
                wp->type_3 = 0x80;
            }
        }
        wp->routine_0 = 1;
        // Each arm has its own copy of the decrement: GCC cross-jumps them into one tail.
        if (flag != 0)
        {
            sel        = pl->weapon_right_no;
            wp->id_2   = D_80089A8B[sel * 12];
            wp->pos.vx = pl->joint_pos[4].vx;
            wp->pos.vy = pl->joint_pos[4].vy;
            wp->pos.vz = pl->joint_pos[4].vz;
            if (pl->rec[sel].val != 0x7FFF && sel != 4 && sel != 7 && (uint32)(sel - 0xC) >= 2)
            {
                pl->rec[sel].val--;
            }
        }
        else
        {
            sel        = pl->unk171;
            wp->id_2   = D_80089A8B[sel * 12];
            wp->pos.vx = pl->joint_pos[7].vx;
            wp->pos.vy = pl->joint_pos[7].vy;
            wp->pos.vz = pl->joint_pos[7].vz;
            if (pl->rec[sel].val != 0x7FFF && sel != 4 && sel != 7 && (uint32)(sel - 0xC) >= 2)
            {
                pl->rec[sel].val--;
            }
        }
        wp->pos.pad  = flag;
        wp->field_C  = pl->unk01;
        wp->pos_l.vx = wp->pos.vx << 16;
        wp->pos_l.vy = wp->pos.vy << 16;
        wp->pos_l.vz = wp->pos.vz << 16;
        wp->field_64 = pl->ang.vy;
    }
}

void func_800358E8(void)
{
}

// Runs the four homing points, then scans the queued requests (D_800A2F48) whose kind bit is in the
// player's mask for the nearest within 2000 on each axis: one whose owner lacks the player's bit
// gets a homing point (func_80036C50), the others compete. The nearest one's object is returned
// (the lock-on target, D_80097D08); a new kind is held for 0x18 frames before another may replace it.
MODEL_WORK *func_800358F0(PL_WORK *pl)
{
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
    side   = pl->unk01;
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
    pos = pl->pos;
    for (i = 0; i < n; i++)
    {
        // v.pad read as halfword 3 of each entry (see lock_on_search).
        if (!((mask << (((uint16 *)D_800A2F48)[i * 6 + 3] >> 13)) & 0x80))
        {
            continue;
        }
        w     = D_800A2F48[i].flags;
        flags = ((SLOT_OWNER *)(w & 0x7FFFFF))->mask_4;
        if (flags & 0x80)
        {
            continue;
        }
        if ((kind = w >> 24) >= 0x80)
        {
            continue;
        }
        if (D_800A2F48[i].v.pad & 0x600)
        {
            c.vx = (D_800A2F48[i].v.vx + D_800A2F48[i + 1].v.vx) >> 1;
            c.vy = (D_800A2F48[i].v.vy + D_800A2F48[i + 1].v.vy) >> 1;
            c.vz = (D_800A2F48[i].v.vz + D_800A2F48[i + 1].v.vz) >> 1;
            i++;
        }
        else
        {
            c = D_800A2F48[i].v;
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
            func_80036C50(D_800A2F48[i].flags >> 24, (SLOT_OWNER *)(D_800A2F48[i].flags & 0x7FFFFF));
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
        kind = D_800A2F48[best].flags >> 24;
        if (kind < 0x80)
        {
            if (D_80098568 == 0)
            {
                if (kind != D_80098564)
                {
                    D_80098568 = 0x18;
                    D_80098564 = kind;
                }
                return func_80036294(kind);
            }
            if (kind == D_80098564)
            {
                return func_80036294(kind);
            }
        }
    }
    return 0;
}

// Picks the live WORK_3C0 or WORK_5A4 object (dist_80[0] at most max_dist) most straight ahead of
// the player (facing ang.vy + unk116), on the inner side of the edge direction turned by arc and
// with a facing dot product of at least min_dot; a WORK_5A4 wins over a WORK_3C0 only with a
// larger dot product. Returns it, or 0.
void *front_obj_search(PL_WORK *pl, sint32 arc, uint32 max_dist, sint32 min_dot)
{
    SVECTOR unused[5];
    SVECTOR pos;
    SVECTOR fwd;
    SVECTOR unused2;
    SVECTOR edge;
    SVECTOR norm;
    SVECTOR other;
    SVECTOR mark;
    VECTOR delta;
    WORK_3C0 *w3;
    WORK_5A4 *w5;
    void *found;
    sint32 best;
    sint32 dot;
    sint32 hit;
    uint32 i;

    found   = NULL;
    best    = 0;
    fwd.vx  = -rsin(pl->ang.vy + pl->unk116);
    fwd.vy  = 0;
    fwd.vz  = -rcos(pl->ang.vy + pl->unk116);
    edge.vx = -rsin(pl->ang.vy + pl->unk116 + arc);
    edge.vy = 0;
    edge.vz = -rcos(pl->ang.vy + pl->unk116 + arc);
    pos     = pl->pos;
    hit     = -1;
    for (i = 0; i < 16; i++)
    {
        w3 = &D_8009F108[i];
        if ((w3->routine_0 & 3) && max_dist >= w3->dist_80[0])
        {
            other    = w3->pos;
            delta.vy = 0;
            delta.vx = other.vx - pos.vx;
            delta.vz = other.vz - pos.vz;
            VectorNormalS(&delta, &norm);
            if (edge.vx * norm.vx + edge.vz * norm.vz >= 0)
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
        mark     = D_8009F108[hit].pos;
        mark.pad = 1;
        found    = &D_8009F108[hit];
    }
    hit = -1;
    for (i = 0; i < 4; i++)
    {
        w5 = &D_800C3580[i];
        if ((w5->routine_0 & 3) && max_dist >= w5->dist_80[0])
        {
            other    = w5->pos;
            delta.vy = 0;
            delta.vx = other.vx - pos.vx;
            delta.vz = other.vz - pos.vz;
            VectorNormalS(&delta, &norm);
            if (edge.vx * norm.vx + edge.vz * norm.vz >= 0)
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
        mark     = D_800C3580[hit].pos;
        mark.pad = 1;
        found    = &D_800C3580[hit];
    }
    return found;
}

// Squared xz distance (<< 2) of every object in the three pools to each player, in dist_80;
// -1 when too far.
void Obj_player_dist_set(void)
{
    SVECTOR pos;
    SVECTOR unused; // never used; the target's frame has its 8 bytes
    WORK_3C0 *p3;
    WORK_5A4 *p5;
    SHL_WORK *p1;
    uint32 d;
    sint32 dx;
    sint32 dz;
    sint32 k;
    sint32 j;

    for (k = 0; k < 2; k++)
    {
        pos = Player_work[k].pos;
        for (j = 0; j < 0x10;)
        {
            p3 = &D_8009F108[j++];
            if (p3->routine_0 | 1)
            {
                dx = (p3->pos.vx - pos.vx) >> 1;
                dz = (p3->pos.vz - pos.vz) >> 1;
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
        for (j = 0; j < 4;)
        {
            p5 = &D_800C3580[j++];
            if (p5->routine_0 | 1)
            {
                dx = (p5->pos.vx - pos.vx) >> 1;
                dz = (p5->pos.vz - pos.vz) >> 1;
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
        for (j = 0; j < 0x20;)
        {
            p1 = &D_8009CF88[j++];
            if (p1->routine_0 | 1)
            {
                dx = (p1->pos.vx - pos.vx) >> 1;
                dz = (p1->pos.vz - pos.vz) >> 1;
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

// Steps tracker t of object wp toward the player, at the object's facing angle.
sint32 func_8003648C(TRACK_WORK *t, MODEL_WORK *wp)
{
    return func_800364B0(t, wp, wp->ang.vy);
}

sint32 func_800364B0(TRACK_WORK *t, MODEL_WORK *wp, sint32 angle)
{
    SVECTOR step;
    SVECTOR prev;
    SVECTOR pl;
    VECTOR delta;

    if (wp->dist_80[0] >= (uint32)(D_800899AC[t->kind].range << 20))
    {
    fail:
        t->state = 0;
        return 0;
    }
    switch (t->state)
    {
        case 0:
        default:
            step.vz = 0;
            step.vy = 0;
            step.vx = 0;
            if (func_80030628(wp, (MODEL_WORK *)&Player_work[0], &step.vx, &delta, angle) & 0x10)
            {
                return 0;
            }
            t->state  = 1;
            t->x      = wp->pos.vx;
            t->y      = wp->pos.vy + (t->height << 24 >> 20);
            t->z      = wp->pos.vz;
            t->vel[0] = Player_work[0].pos.vx - t->x;
            t->vel[1] = Player_work[0].pos.vy - t->y;
            t->vel[2] = Player_work[0].pos.vz - t->z;
            t->timer  = D_800899AC[t->kind].start;
            break;
        case 1:
            pl       = Player_work[0].pos;
            delta.vx = pl.vx - t->x;
            if ((uint32)(delta.vx + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.vy = pl.vy - t->y;
            if ((uint32)(delta.vy + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.vz = pl.vz - t->z;
            if ((uint32)(delta.vz + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            VectorNormalS(&delta, &prev);
            func_80033F04(&step, &prev, (SVECTOR *)t->vel, 0x165, 0x0FF069DA);
            t->vel[0] = step.vx;
            t->vel[1] = step.vy;
            t->vel[2] = step.vz;
            prev.vx   = t->x;
            prev.vy   = t->y;
            prev.vz   = t->z;
            step.vx   = step.vx * 25 >> 10;
            step.vy   = step.vy * 25 >> 10;
            step.vz   = step.vz * 25 >> 10;
            t->x      = prev.vx + step.vx;
            t->y      = prev.vy + step.vy;
            t->z      = prev.vz + step.vz;
            if (func_80049C54((SVECTOR *)t, (SVECTOR *)t, &D_80097D0C, 0xFFFF) != 0)
            {
                goto fail;
            }
            prev.vx += step.vx >> 1;
            prev.vy += step.vy >> 1;
            prev.vz += step.vz >> 1;
            if (func_80049C54(&prev, &prev, &D_80097D0C, 0xFFFF) != 0)
            {
                goto fail;
            }
            if (--t->timer == 0)
            {
                goto fail;
            }
            if ((uint16)(t->x - pl.vx + 100) >= 200)
            {
                return 0;
            }
            if ((uint16)(t->y - pl.vy + 100) >= 200)
            {
                return 0;
            }
            if ((uint16)(t->z - pl.vz + 100) >= 200)
            {
                return 0;
            }
            if (D_1F800075 == 2)
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
            step.vz = 9;
            step.vy = 9;
            step.vx = 9;
            if (func_80030628(wp, (MODEL_WORK *)&Player_work[0], &step.vx, &delta, angle) & 0x10)
            {
                if (--t->timer == 0)
                {
                    goto fail;
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
    D_8009A350.far_r = r;
    D_8009A350.far_g = g;
    D_8009A350.far_b = b;
    D_8009A350.near  = n;
}

void Fog_param_get(sint16 *out)
{
    out[0] = D_8009A350.far_r;
    out[1] = D_8009A350.far_g;
    out[2] = D_8009A350.far_b;
    out[3] = D_8009A350.near;
}

// Applies the loaded fog block D_800BC7F8 (far colour, fog near) and makes it the current one.
void fog_block_apply(void)
{
    SetFarColor(D_800BC7F8.far_r, D_800BC7F8.far_g, D_800BC7F8.far_b);
    SetFogNear(D_800BC7F8.near, 0x180);
    D_8009A350 = D_800BC7F8;
}

// Claims a free homing point for the object of id `id` (owner told of the hit), unless one
// already targets it or all four are busy.
void func_80036C50(uint8 id, SLOT_OWNER *owner)
{
    uint32 i;

    if (D_8009A300[0].id_6 == id || D_8009A300[1].id_6 == id || D_8009A300[2].id_6 == id || D_8009A300[3].id_6 == id)
    {
        return;
    }
    if (D_80098560 >= 4)
    {
        return;
    }
    for (i = 0; i < 4; i++)
    {
        if (D_8009A300[i].id_6 == 0)
        {
            D_8009A300[i].id_6     = id;
            D_8009A300[i].owner_10 = owner;
            if (D_8009A300[i].flag_F)
            {
                D_8009A300[i].flag_F = 0;
            }
            else
            {
                D_8009A300[i].flag_F = 1;
            }
            D_80098560++;
            return;
        }
    }
}

// Steps homing point t (a slot of D_8009A300): 1 when it reaches its target object (bit 0 of the
// owner's mask_4 is then set and the slot freed), else 0.
sint32 func_80036D40(SLOT_ENT *t)
{
    SVECTOR step;
    SVECTOR prev;
    SVECTOR tp;
    VECTOR delta;
    MODEL_WORK *tg;
    SLOT_OWNER *owner;
    PL_WORK *pl;

    if (t->id_6 == 0)
    {
        return 0;
    }
    tg = func_80036294(t->id_6);
    if ((sint8)tg->routine_0 == 0) // read with lb
    {
        goto clear;
    }
    pl = &Player_work[0];
    if (tg->dist_80[0] > 0x2EFFFFF)
    {
        goto fail;
    }
    switch (t->state_7)
    {
        case 0:
        default:
            step.vx = step.vy = step.vz = 9;
            prev.vx                     = D_800A39F0;
            prev.vy                     = D_800A39F4;
            prev.vz                     = D_800A39F8;
            if (!(func_8003081C(&prev, &tg->pos, &step.vx, Player_work[0].ang.vy) & 2))
            {
                return 0;
            }
            if (!(tg->flags & 0x80) && tg->kind_1 < 0x60)
            {
                return 0;
            }
            t->state_7 = 1;
            t->x       = pl->pos.vx;
            t->y       = pl->pos.vy - 100;
            t->z       = pl->pos.vz;
            if (t->flag_F)
            {
                t->vel[0]  = tg->pos.vx - t->x;
                t->vel[1]  = tg->pos.vy - t->y;
                t->vel[2]  = tg->pos.vz - t->z;
                t->timer_E = 50;
            }
            else
            {
                t->vel[1]  = -0x1000;
                t->vel[0]  = 0;
                t->vel[2]  = 0;
                t->timer_E = 15;
            }
            return 0;
        case 1:
            tp       = tg->pos;
            delta.vx = tp.vx - t->x;
            if ((uint32)(delta.vx + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.vy = tp.vy - t->y;
            if ((uint32)(delta.vy + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            delta.vz = tp.vz - t->z;
            if ((uint32)(delta.vz + 0x687E) > 0xD0FC)
            {
                goto fail;
            }
            VectorNormalS(&delta, &prev);
            func_80033F04(&step, &prev, (SVECTOR *)t->vel, 0x424, 0x0F746EA4);
            t->vel[0] = step.vx;
            t->vel[1] = step.vy;
            t->vel[2] = step.vz;
            prev.vx   = t->x;
            prev.vy   = t->y;
            prev.vz   = t->z;
            step.vx   = step.vx * 25 >> 10;
            step.vy   = step.vy * 25 >> 10;
            step.vz   = step.vz * 25 >> 10;
            t->x      = prev.vx + step.vx;
            t->y      = prev.vy + step.vy;
            t->z      = prev.vz + step.vz;
            if (func_80049C54((SVECTOR *)t, (SVECTOR *)t, &D_80097D18, 0xFFFF))
            {
                goto fail;
            }
            prev.vx += step.vx >> 1;
            prev.vy += step.vy >> 1;
            prev.vz += step.vz >> 1;
            if (func_80049C54(&prev, &prev, &D_80097D18, 0xFFFF))
            {
                goto fail;
            }
            if (--t->timer_E == 0)
            {
            fail:
                t->state_7 = 0;
            clear:
                t->id_6 = 0;
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
            owner      = t->owner_10;
            t->state_7 = 0;
            t->id_6    = 0;
            D_80098560--;
            owner->mask_4 |= 1;
            return 1;
    }
}

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

    sel                       = Player_work[0].weapon_right_no;
    ((uint32 *)D_8009856C)[0] = 0;
    ((uint32 *)D_8009856C)[1] = 0;
    ((uint32 *)D_8009856C)[2] = 0;
    ((uint32 *)D_8009856C)[3] = 0;
    for (i = 0; i < 16; i++)
    {
        if (D_800BFB20[i].routine_0 & 1)
        {
            id = D_800BFB22[i].routine_0 - 0x80; // low byte of id_2
            if ((sint32)id < 16)
            {
                D_8009856C[id]++;
            }
        }
    }
    if (sel == 6)
    {
        idx = Player_work[0].rec[6].sp_perform;
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
