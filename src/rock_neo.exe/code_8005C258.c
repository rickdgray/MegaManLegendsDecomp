#include "common.h"
#include "code_8005C258.h"
#include "cd.h"
#include "display.h"
#include "fastmem.h"
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

// Pool variable (stays in assembly), reached through $gp here.
sint32 D_80098AF0;

// Called only from this file, ahead of their definitions.
void func_8005D4F8(void);
void func_8005DCDC(void);
void func_8005DE28(void);

void func_8005C258(void)
{
    Mem_clear(D_800BBD78, D_800BBD78 + 0xD4);
    D_800BBD78[0]    = 3;
    D_800BBD9C       = 3;
    D_80098AF0       = 0;
    D_8009800C       = 5;
    Scene_work.unk00 = 0;
    D_80098008       = 0;
    D_8009801C       = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C2B8);

void func_8005C720(uint8 *wp)
{
    D_8008D7B4[wp[4]](wp);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C75C);

void func_8005C858(void)
{
}

void func_8005C860(void)
{
}

void func_8005C868(uint8 *wp)
{
    D_8008D7C0[wp[4]](wp);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C8A4);

void func_8005C978(uint8 *wp)
{
    D_8008D7C4[wp[4]](wp);
}

void func_8005C9B4(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005C9BC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005CCF4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005CEFC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D0FC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D298);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D39C);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D574);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D620);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D6E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D7C0);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005D8C4);

uint8 func_8005D938(void)
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
    Player_work[0].unk6E = Player_work[0].unkB0;
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
        cur    = Player_work[0].unk6E;
        target = Player_work[0].unkB0;
        if (cur + 2 >= target)
        {
            Player_work[0].unk6E = target;
            return 1;
        }
        Player_work[0].unk6E = cur + 2;
        return 0;
    }
    return Player_work[0].unk6E == Player_work[0].unkB0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005DAEC);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8005C258", func_8005DC10);

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
