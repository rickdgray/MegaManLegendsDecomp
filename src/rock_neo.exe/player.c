#include "common.h"
#include "code_80043F34.h"
#include "game.h"
#include "player.h"

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003BE40);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003BE6C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003C07C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003C2D8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003C418);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003C4EC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003C7B0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003C88C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003CB20);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003CBF8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003CD4C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003D124);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003D1E0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003D6DC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003D7D4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003D960);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003DA34);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003DC5C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003E068);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003E224);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003E4A8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003E6B0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003E860);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003EB08);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003EE68);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003EEC0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F188);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F224);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F288);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F3E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F498);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F4E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F538);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F588);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F5D8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F7F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003F97C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003FDA8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003FE1C);

void func_8003FFA8(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8003FFB0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800400B8);

void func_80040130(void)
{
}

void func_80040138(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040140);

void func_80040170(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040178);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040224);

void func_80040294(void)
{
}

void func_8004029C(void)
{
}

void func_800402A4(void)
{
}

void func_800402AC(void)
{
}

void func_800402B4(void)
{
}

void func_800402BC(void)
{
}

sint32 func_800402C4(PL_WORK *pl)
{
    if (pl->unk11C & pl->keys_124[0])
    {
        if (pl->unk11C & pl->keys_124[8])
        {
            pl->routine_9           = 1;
            *(uint16 *)&pl->field_A = 0;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8004030C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040380);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800403D4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040468);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800404FC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040574);

sint32 func_800405F4(PL_WORK *pl)
{
    if (pl->unk11C & (pl->keys_124[2] | pl->keys_124[3]))
    {
        pl->routine_9           = 4;
        *(uint16 *)&pl->field_A = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040630);

sint32 func_800406A8(PL_WORK *pl)
{
    if (pl->unk11E & pl->keys_124[10])
    {
        pl->routine_9           = 7;
        *(uint16 *)&pl->field_A = 0;
        return 1;
    }
    return 0;
}

sint32 func_800406DC(PL_WORK *pl)
{
    if (pl->unk11E & pl->keys_124[10])
    {
        pl->routine_9           = 8;
        *(uint16 *)&pl->field_A = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040710);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040764);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040818);

sint32 func_80040AEC(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->unk11C;
    if (Game_work.unk083 == 1 || (pad & pl->keys_124[14]))
    {
        pl->routine_9           = 14;
        *(uint16 *)&pl->field_A = 0;
        return 1;
    }
    return 0;
}

sint32 func_80040B34(PL_WORK *pl)
{
    if (pl->unk11C & pl->keys_124[13])
    {
        pl->routine_9           = 5;
        *(uint16 *)&pl->field_A = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040B68);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040E00);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040E9C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80040FA8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041044);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800410D4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041158);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800411DC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800414F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_8004174C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041A44);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041AB0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041B8C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041DDC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041E90);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041EF4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80041F54);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042044);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042094);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042154);

sint32 func_80042208(void)
{
    if (Player_work[0].unk6E >= 0)
    {
        Player_work[0].unk449 = 1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042238);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042314);

void Pl00_shot_enable_off(PL_WORK *pl)
{
    pl->unk174 = 0;
    pl->unk177 = 0;
    pl->unk175 &= ~1;
    pl->set_104      = pl->idx_AC;
    pl->cmd_100.b.b0 = pl->cmd_A4.b.b0;
}

void Pl00_shot_enable_on(PL_WORK *pl)
{
    pl->unk175 |= 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_800423DC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042458);

void func_800424D4(PL_WORK *pl, W48_80_WORK *wp)
{
    wp->routine_0 = 7;
    wp->id_2      = 0x80;
    wp->type_3    = 2;
    wp->pos_38    = pl->joint_pos[pl->field_A >> 1];
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/player", func_80042528);
