#include "common.h"
#include "game.h"
#include "psyq/libgpu.h"
#include "display.h"
#include "scratch.h"
#include "system.h"
#include "sound.h"
#include "player.h"
#include "code_8002E7A8.h"
#include "code_8004324C.h"

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800155A4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80015634);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80015734);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80015840);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800158F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80015DB4);

// Puts the player at the area entry: position (and its previous copies) and facing angle; reset
// also clears field_74/75, and in routine_8 3 the saved position is set too.
void player_entry_set(PL_WORK *pl, AREA_ENTRY *entry, sint32 reset)
{
    pl->pos.vx = pl->old.vx = entry->pos.vx;
    pl->pos.vy = pl->old.vy = entry->pos.vy;
    pl->pos.vz = pl->old.vz = entry->pos.vz;
    pl->pos_l.vx = pl->old_l.vx = entry->pos.vx << 16;
    pl->pos_l.vy = pl->old_l.vy = entry->pos.vy << 16;
    pl->pos_l.vz = pl->old_l.vz = entry->pos.vz << 16;
    pl->ang.vy = pl->old_ang.vy = entry->ang_y;
    if (reset)
    {
        pl->field_74 = pl->field_75 = 0;
    }
    if (pl->routine_8 == 3)
    {
        pl->svec_438 = pl->pos;
        pl->pos_428  = pl->pos_l;
        pl->ang_440  = pl->ang;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80015FE8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016160);

void func_80016434(sint32 mode)
{
    if (mode == 2)
    {
        D_800C356C                = 3;
        D_800C356E                = 24;
        D_800C3562                = -1;
        D_800C3570                = 255;
        Game_work.unk078.b.unk079 = 27;
        D_800C356F                = 0;
        D_800C3560                = 0;
        D_800C3564                = 0;
        D_800C356A                = 0;
        D_800C356D                = 0;
        Game_work.unk078.b.unk07A = 1;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800164B4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016528);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_8001663C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016798);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800169AC);

void game_timer_count(void)
{
    if (++Game_work.timer_0c > GAME_TIMER_MAX)
    {
        Game_work.timer_0c = GAME_TIMER_MAX;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016BF4);

// Same code as func_80013F60, on Game_work.
void func_80016D0C(GAME_WORK *gw)
{
    if (D_80098A72 == 0)
    {
        gw->routine_1++;
    }
}

// Same code as func_80013F60, on Game_work.
void func_80016D38(GAME_WORK *gw)
{
    if (D_80098A72 == 0)
    {
        gw->routine_1++;
    }
}

// Waits for the running sound fade to end, then calls func_8001B314.
void func_80016D64(void)
{
    while (Sound_fade_flags != 0)
    {
        Thread_wait(1);
    }
    func_8001B314();
}

// Draws a 256x128 textured quad at (32, 56) from the texture page at VRAM (0, 0), CLUT row 496.
void func_80016DAC(void)
{
    POLY_FT4 *p;

    p            = Map_prim_ptr;
    Map_prim_ptr = p + 1;
    setPolyFT4(p);
    p->tpage = GetTPage(0, 0, 320, 256);
    p->clut  = GetClut(0, 496);
    p->x0    = 32;
    p->y0    = 56;
    p->x1    = 287;
    p->y1    = 56;
    p->x2    = 32;
    p->y2    = 184;
    p->x3    = 287;
    p->y3    = 184;
    p->u0    = 0;
    p->v0    = 0;
    p->u1    = 255;
    p->v1    = 0;
    p->u2    = 0;
    p->v2    = 128;
    p->u3    = 255;
    p->v3    = 128;
    p->r0    = 128;
    p->g0    = 128;
    p->b0    = 128;
    AddPrim(&Disp_env_ptr->ot[2], p);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016E90);

// The pool updates: run the handler of every live slot (routine_0 and flags both with bit 0 set),
// keeping the slot in a global for the handlers. routine_0 is read signed here (lb), where the
// pools' other code reads it unsigned, hence the casts.
void func_80016FD4(void)
{
    for (D_80098820 = D_8009F108; D_80098820 < &D_8009F108[16]; D_80098820++)
    {
        if ((sint8)D_80098820->routine_0 & D_80098820->flags & 1)
        {
            Work_3C0_tbl[D_80098820->id_2][D_80098820->flag_4](D_80098820);
        }
    }
}

void func_80017094(void)
{
    for (D_800989D0 = D_800C3580; D_800989D0 < &D_800C3580[4]; D_800989D0++)
    {
        if ((sint8)D_800989D0->routine_0 & D_800989D0->flags & 1)
        {
            Work_5A4_tbl[D_800989D0->id_2][D_800989D0->flag_4](D_800989D0);
        }
    }
}

void func_80017154(void)
{
    for (D_800988F8 = D_800BFB20; D_800988F8 < &D_800BFB20[16]; D_800988F8++)
    {
        if ((sint8)D_800988F8->routine_0 & D_800988F8->flags & 1)
        {
            D_80089820[D_800988F8->id_2](D_800988F8);
        }
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80017210);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800172F4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800173B4);

void eve_work_exec(void)
{
    for (D_800988F0 = D_800A2D08; D_800988F0 < &D_800A2D08[16]; D_800988F0++)
    {
        if ((sint8)D_800988F0->routine_0 & D_800988F0->flags & 1)
        {
            Eve_work_tbl[D_800988F0->id_2](D_800988F0);
        }
    }
}

void func_80017528(void)
{
    for (D_80098924 = D_800BF118; D_80098924 < &D_800BF118[32]; D_80098924++)
    {
        if ((sint8)D_80098924->routine_0 & D_80098924->flags & 1)
        {
            Work_50_tbl[D_80098924->id_2](D_80098924);
        }
    }
}
