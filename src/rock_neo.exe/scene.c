#include "common.h"
#include "cd.h"
#include "code_80037FB4.h"
#include "game.h"
#include "pad.h"
#include "player.h"
#include "scene.h"
#include "sound.h"
#include "system.h"

// Small uninitialized statics (.sbss 0x80098198-0x800981A0).
static uint8 D_80098198[8];

// Called only from this file
void func_8001F798(sint32 n);

void Sound_fade_start(sint32 fade)
{
    if (Sound_fade_flags == 0)
    {
        Sound_fade_flags = fade;
    }
}

sint32 func_8001D878(void)
{
    return Cd_stat & 0x20;
}

void Sce_read_sync(void)
{
    while (Cd_read_sync2())
    {
        Thread_wait(1);
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D8C0);

void func_8001D928(sint32 keep)
{
    sint32 i;
    sint32 *p;

    if (keep == 0)
    {
        p = D_800BE438;
        for (i = 0; i < 16; i++)
        {
            *p++ = 0;
        }
    }
    *(uint32 *)&Scene_work.unk00 = 0;
    D_800989F8                   = 0;
    D_800989FC                   = 0;
    D_80098A00                   = 0;
}

void func_8001D974(void)
{
    Game_work.unk053++;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D990);

sint32 Sce_flag_test(sint32 flag)
{
    sint32 bit;
    uint32 idx;
    sint32 mask;
    uint8 unused[8]; // never used; the target has its 8-byte frame

    bit  = flag & 7;
    idx  = (uint32)flag >> 3;
    mask = 0x80;
    return (Sce_flag[idx] & (mask >> bit)) != 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", Sce_flag_on);

void Sce_flag_off(sint32 flag)
{
    uint8 *p;
    sint32 mask;
    sint32 bit;
    sint32 i;

    p = Sce_flag;
    p += (uint32)flag >> 3;
    mask = 0x80;
    bit  = flag & 7;
    *p &= ~(mask >> bit);
    if (flag >= 0x500 && flag < 0x520)
    {
        for (i = 0; i < 32; i++)
        {
            if (Player_work[0].ids_454[i] == flag - 0x4FF)
            {
                Player_work[0].ids_454[i] = 0;
                break;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (Player_work[0].ids_450[i] == flag - 0x4FF)
            {
                Player_work[0].ids_450[i] = 0;
                break;
            }
        }
    }
}

sint16 func_8001DD88(void)
{
    D_80098198[0] = D_80098B60[0];
    D_80098198[1] = D_80098B60[1];
    D_80098B60 += 2;
    return *(sint16 *)D_80098198;
}

sint16 func_8001DDC0(uint8 *p)
{
    D_80098198[0] = p[0];
    D_80098198[1] = p[1];
    return *(sint16 *)D_80098198;
}

void func_8001DDE4(uint8 arg)
{
    SCENE_WORK *sw;
    sint32 i;

    if (Player_work[0].unk6E < 0)
    {
        return;
    }
    sw                   = &Scene_work;
    sw->unk00            = 1;
    Scene_work.ev_09     = 0;
    Scene_work.ev_08     = 0;
    Scene_work.unk01     = arg;
    Scene_work.timer_10  = 0;
    Scene_work.field_0C  = 0;
    Scene_work.timer_1C  = 0;
    Scene_work.timer_18  = 0;
    Scene_work.unk14     = 0;
    Scene_work.unk04     = 0;
    Scene_work.unk0B     = 0;
    Scene_work.unk0A     = 0;
    Scene_work.ev_ptr_A4 = NULL;
    for (i = 15; i >= 0; i--)
    {
        sw->obj_24[i] = NULL;
    }
}

sint32 func_8001DE84(void)
{
    if (Game_work.unk05A != 0 || Sce_flag_test(Scene_work.unk01 + 0x380) != 0)
    {
        if (PAD_ON(Joy1) & PAD_START)
        {
            return 1;
        }
    }
    return 0;
}

void func_8001DEDC(void)
{
}

void func_8001DEE4(void)
{
    sint32 i;

    D_800988E8 = 0;
    for (i = 0; i < 32; i++)
    {
        D_800ACD40[i] = 0;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DF10);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DFEC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E068);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E20C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E390);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E3F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E460);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E4C4);

void func_8001E550(void)
{
    SCENE_CAM_WORK *cp;
    WORK_10C *obj;
    VECTOR pos;
    VECTOR tgt;

    cp = &D_800BC730;
    if (cp->follow_03 == 0)
    {
        pos.vx = (cp->pos_10.vx + cp->ofs_A0.vx) >> 16;
        pos.vy = (cp->pos_10.vy + cp->ofs_A0.vy) >> 16;
        pos.vz = (cp->pos_10.vz + cp->ofs_A0.vz) >> 16;
    }
    else
    {
        obj           = Scene_work.obj_24[cp->obj_09];
        cp->pos_10.vx = obj->x_1C + cp->ofs_B0.vx;
        cp->pos_10.vy = obj->y_20 + cp->ofs_B0.vy;
        cp->pos_10.vz = obj->z_24 + cp->ofs_B0.vz;
        pos.vx        = cp->pos_10.vx >> 16;
        pos.vy        = cp->pos_10.vy >> 16;
        pos.vz        = cp->pos_10.vz >> 16;
    }
    if (cp->mode_08 == 0)
    {
        func_80038324(&pos, cp->ang_40.vz >> 16, cp->ang_40.vx >> 16, cp->ang_40.vy >> 16);
    }
    else
    {
        tgt.vx = (cp->tgt_70.vx + cp->ofs_A0.vx) >> 16;
        tgt.vy = (cp->tgt_70.vy + cp->ofs_A0.vy) >> 16;
        tgt.vz = (cp->tgt_70.vz + cp->ofs_A0.vz) >> 16;
        func_800384A4(&pos, &tgt);
    }
}

void func_8001E6C0(sint32 x, sint32 y, sint32 z)
{
    D_800BC730.ofs_A0.vx = x << 16;
    D_800A395C           = 3; // after the first store: first, its li comes before x's sll
    D_800BC730.ofs_A0.vy = y << 16;
    D_800BC730.ofs_A0.vz = z << 16;
    D_800BC730.vel_20.vx = D_800BC730.vel_20.vy = D_800BC730.vel_20.vz = 0;
    D_800BC730.angvel_50.vx = D_800BC730.angvel_50.vy = D_800BC730.angvel_50.vz = 0;
    D_800BC730.tgtvel_80.vx = D_800BC730.tgtvel_80.vy = D_800BC730.tgtvel_80.vz = 0;
    D_800BC730.mode_08                                                          = 0;
    D_800BC730.pos_10.vx                                                        = D_800A39A0.vx << 16;
    D_800BC730.pos_10.vy                                                        = D_800A39A0.vy << 16;
    D_800BC730.pos_10.vz                                                        = D_800A39A0.vz << 16;
    D_800BC730.ang_40.vx                                                        = (D_800A3968 & 0xFFF) << 16;
    D_800BC730.ang_40.vy                                                        = (D_800A396C & 0xFFF) << 16;
    D_800BC730.ang_40.vz                                                        = (D_800A3964 & 0xFFF) << 16;
    func_800398E0(0);
}

void func_8001E7E4(sint32 x, sint32 y, sint32 z)
{
    D_800BC730.pos_10.vx = x << 16;
    D_800BC730.pos_10.vy = y << 16;
    D_800BC730.pos_10.vz = z << 16;
}

void func_8001E810(sint32 x, sint32 y, sint32 z)
{
    D_800BC730.ang_40.vx = x << 16;
    D_800BC730.ang_40.vy = y << 16;
    D_800BC730.ang_40.vz = z << 16;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E83C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E968);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001EAE8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001EB98);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001EC0C);

void func_8001F070(void)
{
    SCENE_WORK *sw;

    sw = &Scene_work;
    sw->unk14++;
    sw->timer_18++;
    sw->timer_1C++;
    sw->timer_10++;
    if (sw->ev_ptr_A4->frame_2 != -1 && sw->ev_ptr_A4->frame_2 == sw->timer_10)
    {
        sw->ev_ptr_A4++;
        if (sw->ev_08 != sw->ev_ptr_A4->ev_0)
        {
            sw->timer_18 = 0;
            sw->timer_1C = 0;
        }
        sw->ev_08 = sw->ev_ptr_A4->ev_0;
        if (sw->ev_09 != sw->ev_ptr_A4->ev_1)
        {
            sw->timer_1C = 0;
        }
        sw->ev_09    = sw->ev_ptr_A4->ev_1;
        sw->timer_10 = 0;
    }
}

// Steps the event table to its next entry (func_8001F070's step, without the frame test).
void func_8001F158(void)
{
    SCENE_WORK *sw;

    sw = &Scene_work;
    sw->ev_ptr_A4++;
    if (sw->ev_08 != sw->ev_ptr_A4->ev_0)
    {
        sw->timer_18 = 0;
        sw->timer_1C = 0;
    }
    sw->ev_08 = sw->ev_ptr_A4->ev_0;
    if (sw->ev_09 != sw->ev_ptr_A4->ev_1)
    {
        sw->timer_1C = 0;
    }
    sw->ev_09    = sw->ev_ptr_A4->ev_1;
    sw->timer_10 = 0;
}

void func_8001F1DC(void)
{
    Scene_work.timer_10 = 0;
    Scene_work.timer_18 = 0;
    Scene_work.timer_1C = 0;
    Scene_work.ev_08    = 0;
    Scene_work.ev_09    = 0;
}

void func_8001F20C(EVENT_ENT *ev, sint32 arg1)
{
    D_800BC730.arg_C0    = arg1;
    Scene_work.ev_ptr_A4 = ev;
    Scene_work.ev_08     = ev->ev_0;
    Scene_work.ev_09     = ev->ev_1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F23C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F3C8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F580);

void func_8001F5E4(void)
{
    sint32 file;

    file = D_80089200[Player_work[0].unk16A];
    if (Game_work.file_070 != file)
    {
        Game_work.file_070 = file;
        Cd_read_comb(file);
    }
    file = D_80089204[(sint8)Player_work[0].unk16B >> 1];
    if (Game_work.file_072 != file)
    {
        Game_work.file_072 = file;
        Cd_read_comb(file);
    }
    if (Player_work[0].tbl_sel >= 2)
    {
        file = D_80089208[Player_work[0].tbl_sel];
        if (Game_work.file_074 != file)
        {
            Game_work.file_074 = file;
            Cd_read_comb(file);
        }
    }
}

void func_8001F6C4(void)
{
    sint16 *list;
    sint32 n;
    sint32 file;

    list = D_800893BC[D_800C356E];
    file = list[0];
    n    = D_800C356F;
    if (Game_work.unk068 == file)
    {
        file = list[n + 1];
        if (file < 0 || Game_work.unk06A == file)
        {
            return;
        }
    }
    Cd_seek_file(file);
}

void func_8001F740(void)
{
    func_8001F798(Game_work.unk050);
    D_8008980C[Game_work.unk050]();
}

void func_8001F798(sint32 n)
{
    sint32 i;

    for (i = 0; i < D_80089248[n].count; i++)
    {
        D_80089248[n].dst[i] = D_80089248[n].src[i];
    }
}

void func_8001F820(void)
{
}

INCLUDE_RODATA("asm/rock_neo.exe/nonmatchings/scene", D_800102B0);

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_80098199\n.set D_80098199, D_80098198+1\n");
