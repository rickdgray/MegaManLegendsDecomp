#include "common.h"
#include "cd.h"
#include "rock_neo.exe/system.h"
#include "rock_neo.exe/scene.h"

#ifdef __wasm32__
void func_80031AA4(void);
void func_80051B40(void);
void func_80033EBC(void);
void func_800629E0(void);
void func_8002CFA4(void);
void Obj_work_flag_change(sint32 arg, sint32 flags);
#endif

// Small data reached through $gp
static SCENE_HALF_BYTES D_80098198;

void func_8001D854(uint8 arg)
{
    if (D_80098788 == 0)
    {
        D_80098788 = arg;
    }
}

uint32 func_8001D878(void)
{
    return D_80098AB8 & 0x20;
}

void func_8001D888(sint32 arg)
{
    while (Cd_read_sync2())
    {
        Thread_wait(1);
    }
}

void func_8001D8C0(sint32 arg)
{
    sint32 i;
    uint32 *p;

    if (arg == 0)
    {
        p = (uint32 *)Sce_flag;
        for (i = 0; i < 0x40; i++)
        {
            *p++ = 0;
        }
        func_80067E18();
        func_80067E4C();
    }
    else
    {
        func_800176DC(D_800B6130, Sce_flag, 8);
    }
}

void func_8001D928(sint32 arg)
{
    sint32 i;
    uint32 *p;

    if (arg == 0)
    {
        p = D_800BE438;
        for (i = 15; i >= 0; i--)
        {
            *p++ = 0;
        }
    }
    *(uint32 *)&Scene_work = 0;
    D_800989F8             = 0;
    D_800989FC             = 0;
    D_80098A00             = 0;
}

void func_8001D974(void)
{
    Game_work.flags_53++;
}

void func_8001D990(void)
{
    SCENE_WORK *wp;

    wp = &Scene_work;
    if (wp->routine_0 == 0)
    {
        if (D_800C356C == 0)
        {
            D_80088FA8[Game_work.routine_50]();
        }
    }
    if (wp->routine_0 != 0)
    {
        if (wp->routine_1 != 0xFF)
        {
            D_80089024[wp->routine_1](wp);
        }
        if (wp->routine_0 == 0)
        {
            Sce_flag_on(wp->routine_1 + 0x380);
        }
    }
}

uint32 Sce_flag_test(uint32 flag)
{
    uint8 unused[8];
    sint32 bit;
    uint32 idx;
    sint32 mask;

    bit  = flag & 7;
    idx  = flag >> 3;
    mask = 0x80 >> bit;
    return (Sce_flag[idx] & mask) != 0;
}

void Sce_flag_on(uint32 flag)
{
    uint8 *p;
    sint32 i;
    sint32 mask;

    p = Sce_flag;
    p += flag >> 3;
    mask = 0x80;
    mask >>= flag & 7;
    *p |= mask;
    if (flag - 0x500 < 0x20)
    {
        for (i = 0; i < 0x20; i++)
        {
            if (Player_work.slots_454[i] == 0)
            {
                Player_work.slots_454[i] = flag + 1;
                break;
            }
        }
    }
    if (*((sint8 *)&Player_work + 0x16C) != 0 && flag - 0x53A < 3)
    {
        *((uint8 *)&Player_work + 0x16C) =
            Sce_flag_test(0x53A) + Sce_flag_test(0x53B) + Sce_flag_test(0x53C);
    }
    if (flag - 0x500 < 0x80)
    {
        if (flag - 0x500 < 0x20)
        {
            Sce_flag_on(flag + 0x80);
        }
        else if (flag - 0x520 < 0x20)
        {
            if (flag == 0x528)
            {
                Sce_flag_on(0x582);
                Sce_flag_on(0x583);
                Sce_flag_on(0x584);
                Sce_flag_on(0x585);
                Sce_flag_on(0x586);
                Sce_flag_on(0x587);
                Sce_flag_on(0x5C1);
                Sce_flag_on(0x5C2);
            }
            if (flag == 0x53A)
            {
                Sce_flag_off(0x5BA);
                Sce_flag_on(0x5BB);
            }
            if (flag == 0x53B)
            {
                Sce_flag_off(0x5BB);
                Sce_flag_on(0x5BC);
            }
            if (flag == 0x53C)
            {
                Sce_flag_off(0x5BC);
            }
            return;
        }
        else if (flag - 0x540 < 4)
        {
            Sce_flag_on(flag + 0x80);
        }
        else if (flag - 0x544 < 0x14)
        {
            return;
        }
        else if (flag - 0x558 < 0x28)
        {
            Sce_flag_on(flag + 0x80);
        }
    }
    if (flag == 0x2A)
    {
        Sce_flag_on(0x580);
        Sce_flag_on(0x581);
        Sce_flag_on(0x5C3);
    }
    if (flag == 0x51)
    {
        Sce_flag_on(0x5BA);
        Sce_flag_on(0x588);
        Sce_flag_on(0x589);
    }
}

void Sce_flag_off(uint32 flag)
{
    uint8 *p;
    sint32 i;
    sint32 mask;

    p = Sce_flag;
    p += flag >> 3;
    mask = 0x80;
    mask >>= flag & 7;
    *p &= ~mask;
    if (flag - 0x500 < 0x20)
    {
        for (i = 0; i < 0x20; i++)
        {
            if (Player_work.slots_454[i] == flag - 0x4FF)
            {
                Player_work.slots_454[i] = 0;
                break;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (Player_work.slots_450[i] == flag - 0x4FF)
            {
                Player_work.slots_450[i] = 0;
                break;
            }
        }
    }
}

sint16 func_8001DD88(void)
{
    D_80098198.byte[0] = D_80098B60[0];
    D_80098198.byte[1] = D_80098B60[1];
    D_80098B60 += 2;
    return D_80098198.half;
}

sint16 func_8001DDC0(uint8 *p)
{
    D_80098198.byte[0] = p[0];
    D_80098198.byte[1] = p[1];
    return D_80098198.half;
}

void func_8001DDE4(uint8 arg)
{
    SCENE_WORK *wp;
    sint32 i;

    if (Player_work.value_6E >= 0)
    {
        wp                       = &Scene_work;
        wp->routine_0            = 1;
        Scene_work.flag_9        = 0;
        Scene_work.flag_8        = 0;
        Scene_work.routine_1     = arg;
        Scene_work.work_10       = 0;
        Scene_work.work_C        = 0;
        Scene_work.work_1C       = 0;
        Scene_work.work_18       = 0;
        Scene_work.work_14       = 0;
        Scene_work.cmds_4        = 0;
        Scene_work.reserved0a[1] = 0;
        Scene_work.reserved0a[0] = 0;
        Scene_work.script_A4     = 0;
        for (i = 0xF; i >= 0; i--)
        {
            wp->slot_24[i] = 0;
        }
    }
}

uint32 func_8001DE84(void)
{
    if (Game_work.option_5A != 0 || Sce_flag_test(Scene_work.routine_1 + 0x380) != 0)
    {
        if (D_800C0C2A & 8)
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
    for (i = 31; i >= 0; i--)
    {
        D_800ACDBC[i - 31] = 0;
    }
}

void func_8001DF10(SCENE_CMD_LIST *list)
{
    sint16 i;
    uint32 slot;

    for (i = 0; i < list->count; i++)
    {
        slot = list->cmds_4[i].slot_0;
        func_8001EAE8(&list->cmds_4[i]);
        D_800ACD40[slot] = Scene_work.slot_24[slot];
        D_800ACD40[slot]->flags_6 &= 0xDF;
        D_800988E8 |= 0x80000000 >> slot;
    }
}

void func_8001DFEC(SCENE_CMD_LIST *work, sint32 index)
{
    uint32 slot;

    slot = work->cmds_4[index].slot_0;
    func_8001EAE8(&work->cmds_4[index]);
    D_800ACD40[slot] = Scene_work.slot_24[slot];
    D_800988E8 |= 0x80000000 >> slot;
}

void func_8001E068(void)
{
    SCENE_SLOT *slot;
    sint32 i;

    i = 0;
    while (D_800988E8 != 0)
    {
        if (D_800988E8 & (0x80000000U >> i))
        {
            slot = D_800ACD40[i];
            switch ((sint32)func_8002FE74(slot->id_1))
            {
                case 0x40:
                    slot->routine_8 = 2;
                    SCENE_TBL_5C[slot->kind_2][slot->value_4](slot);
                    break;
                case 0x20:
                    if (slot->kind_2 != 0x10)
                    {
                        slot->routine_8 = 2;
                        SCENE_TBL_58[slot->kind_2][slot->value_4](slot);
                    }
                    else
                    {
                        func_80031824(slot);
                    }
                    break;
                case 0x60:
                    slot->routine_8 = 2;
                    SCENE_TBL_60[slot->kind_2](slot);
                    break;
                case 0xE0:
                    slot->routine_8 = 2;
                    SCENE_TBL_6C[slot->kind_2](slot);
                    break;
            }
            D_800988E8 &= ~(0x80000000U >> i);
        }
        i++;
    }
}

void func_8001E20C(sint8 index)
{
    SCENE_SLOT *slot;

    if (D_800988E8 & (0x80000000U >> index))
    {
        slot = D_800ACD40[index];
        switch ((sint32)func_8002FE74(slot->id_1))
        {
            case 0x40:
                slot->routine_8 = 2;
                SCENE_TBL_5C[slot->kind_2][slot->value_4](slot);
                break;
            case 0x20:
                if (slot->kind_2 != 0x10)
                {
                    slot->routine_8 = 2;
                    SCENE_TBL_58[slot->kind_2][slot->value_4](slot);
                }
                else
                {
                    func_80031824(slot);
                }
                break;
            case 0x60:
                slot->routine_8 = 2;
                SCENE_TBL_60[slot->kind_2](slot);
                break;
            case 0xE0:
                slot->routine_8 = 2;
                SCENE_TBL_6C[slot->kind_2](slot);
                break;
        }
        D_800988E8 &= ~(0x80000000U >> index);
    }
}

void func_8001E390(sint32 arg)
{
    uint32 i;

    for (i = 0x2E0; i < 0x2EC; i++)
    {
        if (arg == i)
        {
            Sce_flag_on(i);
        }
        else
        {
            Sce_flag_off(i);
        }
    }
}

void func_8001E3F0(sint32 arg)
{
    sint16 *value = &Game_work.value_60;

    arg = (sint16)arg * 2;
    *value += *(uint16 *)((uint8 *)D_800891B4 + arg);
    if (*value < 0)
    {
        *value = 0;
    }
    else if (*value >= 0x100)
    {
        *value = 0xFF;
    }
#ifdef __wasm32__
    func_800179FC();
#else
    func_800179FC(arg, value);
#endif
}

void func_8001E460(sint32 arg0, sint32 arg1, sint32 arg2)
{
    if (arg1 != 0)
    {
        Sce_flag_on(arg0 + 0x7E0);
        if (arg2 != 0)
        {
            Sce_flag_on(arg0 + 0x7C0);
            return;
        }
    }
    else
    {
        Sce_flag_off(arg0 + 0x7E0);
    }
    Sce_flag_off(arg0 + 0x7C0);
}

// The flags cursor is a local copy: walking the parameter itself swaps its register with i.
void func_8001E4C4(uint8 *ids, uint8 *flags)
{
    sint32 i;
    uint8 *flag;

    flag = flags;
    for (i = 0; i < 8 && *ids != 0; i++, flag++, ids++)
    {
        if (*flag != 0xFF)
        {
            func_8001E460(*ids, *flag & 1, (*flag >> 1) & 1);
        }
    }
}

void func_8001E550(void)
{
    sint32 pos[3];
    sint32 target[3];
    SCENE_SLOT *slot;
    SCENE_CAM *cam;

    cam = &D_800BC730;
    if (D_800BC730.flag_3 == 0)
    {
        pos[0] = (D_800BC730.pos_10 + D_800BC730.off_A0) >> 16;
        pos[1] = (D_800BC730.pos_14 + D_800BC730.off_A4) >> 16;
        pos[2] = (D_800BC730.pos_18 + D_800BC730.off_A8) >> 16;
    }
    else
    {
        slot              = Scene_work.slot_24[D_800BC730.index_9];
        D_800BC730.pos_10 = slot->pos_1C + D_800BC730.value_B0;
        D_800BC730.pos_14 = slot->pos_20 + D_800BC730.value_B4;
        D_800BC730.pos_18 = slot->pos_24 + D_800BC730.value_B8;
        pos[0]            = D_800BC730.pos_10 >> 16;
        pos[1]            = D_800BC730.pos_14 >> 16;
        pos[2]            = D_800BC730.pos_18 >> 16;
    }
    if (cam->mode_8 == 0)
    {
        func_80038324(pos, cam->rot_48.h.i, cam->rot_40.h.i, cam->rot_44.h.i);
        return;
    }
    target[0] = (cam->pos_70 + cam->off_A0) >> 16;
    target[1] = (cam->pos_74 + cam->off_A4) >> 16;
    target[2] = (cam->pos_78 + cam->off_A8) >> 16;
    ((SCENE_CAM_FUNC)func_800384A4)(pos, target);
}

void func_8001E6C0(sint32 arg0, sint32 arg1, sint32 arg2)
{
    D_800BC7D0 = arg0 << 16;
    D_800A395C = 3;
    D_800BC7D4 = arg1 << 16;
    D_800BC7D8 = arg2 << 16;
    D_800BC750 = D_800BC754 = D_800BC758 = 0;
    D_800BC780 = D_800BC784 = D_800BC788 = 0;
    D_800BC7B0 = D_800BC7B4 = D_800BC7B8 = 0;
    D_800BC738                           = 0;
    D_800BC740                           = D_800A39A0 << 16;
    D_800BC744                           = D_800A39A4 << 16;
    D_800BC748                           = D_800A39A8 << 16;
    D_800BC770                           = (D_800A3968 & 0xFFF) << 16;
    D_800BC774                           = (D_800A396C & 0xFFF) << 16;
    D_800BC778                           = (D_800A3964 & 0xFFF) << 16;
    func_800398E0(0);
}

void func_8001E7E4(sint32 a, sint32 b, sint32 c)
{
    D_800BC740 = a << 16;
    D_800BC744 = b << 16;
    D_800BC748 = c << 16;
}

void func_8001E810(sint32 a, sint32 b, sint32 c)
{
    D_800BC770 = a << 16;
    D_800BC774 = b << 16;
    D_800BC778 = c << 16;
}

sint32 func_8001E83C(sint16 x0, sint16 y0, sint16 x1, sint16 y1)
{
    sint32 dx;
    sint32 dy;
    sint32 quad;

    dx   = x1 - x0;
    dy   = (y1 - y0) << 12;
    quad = 0;
    if (dx < 0)
    {
        dx   = -dx;
        quad = 2;
    }
    if (dy < 0)
    {
        dy = -dy;
        quad += 1;
    }
    if (dx == 0)
    {
        return (1 - quad) << 11;
    }
    if (quad == 0 || quad == 3)
    {
        return D_800891F0[quad] - catan(dy / dx);
    }
    return catan(dy / dx) + D_800891F0[quad];
}

// The type 0xE0 slot shares the table store with the others, and an unknown type jumps to the
// common return: one assignment and one return of slot keep its priority below pos.
SCENE_SLOT *func_8001E968(sint32 index, sint32 kind, sint32 type, SCENE_POS *pos)
{
    SCENE_SLOT *slot;
    SCENE_SLOT *wp;

    slot = 0;
    switch (type)
    {
        case 0x20:
            wp = func_80031418();
            break;
        case 0x40:
            wp = func_80031498();
            break;
        case 0xE0:
            wp = func_80031734();
            if (wp != 0)
            {
                wp->flags_0 = 1;
                wp->kind_2  = kind;
                wp->flags_6 |= 0x20;
                wp->word_38 = *(uint32 *)&pos->x_0;
                slot        = wp;
                wp->word_3C = *(uint32 *)&pos->z_4;
                goto set;
            }
            break;
        case 0x60:
            wp = func_80031518();
            break;
        default:
            goto end;
    }
    if (wp != 0)
    {
        wp->flags_0 = 1;
        wp->kind_2  = kind;
        wp->flags_6 |= 0x20;
        wp->word_14 = *(uint32 *)&pos->x_0;
        wp->half_18 = pos->z_4;
        wp->half_54 = 0;
        wp->half_58 = 0;
        wp->half_56 = pos->w_6;
        wp->pos_1C  = pos->x_0 << 16;
        wp->pos_20  = pos->y_2 << 16;
        slot        = wp;
        wp->pos_24  = pos->z_4 << 16;
    set:
        Scene_work.slot_24[index] = slot;
    }
end:
    return slot;
}

SCENE_SLOT *func_8001EAE8(SCENE_CMD *cmd)
{
    SCENE_SLOT *slot;

    slot = func_8001E968(cmd->slot_0, cmd->kind_1, cmd->type_3, (SCENE_POS *)&cmd->word_C);
    if (slot == 0)
    {
        return 0;
    }
    switch (cmd->type_3)
    {
        case 0x40:
        case 0x20:
        case 0x60:
        case 0xE0:
            slot->value_3 = cmd->value_4;
            slot->value_4 = cmd->value_2;
            slot->word_C  = cmd->word_8;
            break;
    }
    return slot;
}

SCENE_SLOT *func_8001EB98(SCENE_CMD *cmd)
{
    SCENE_SLOT *saved;
    SCENE_SLOT *slot;

    saved = Scene_work.slot_24[cmd->slot_0];
    slot  = func_8001EAE8(cmd);
    slot->flags_6 &= 0xDF;
    Scene_work.slot_24[cmd->slot_0] = saved;
    return slot;
}

void func_8001EC0C(void)
{
    SCENE_CAM *cam;
    SCENE_WORK *sw;
    uint32 cmd;
    sint32 done;

    sw  = &Scene_work;
    cam = &D_800BC730;
    if (*(sint32 *)D_800BC7F0 != -1)
    {
        done = 0;
        do
        {
            cmd = cam->cmd_C0[0];
            switch (cmd >> 24)
            {
                case 0:
                    if (sw->work_14 < (cam->cmd_C0[0] & 0xFFFFFF))
                    {
                        done = 1;
                        break;
                    }
                    cam->cmd_C0++;
                    break;
                case 1:
                    if (sw->flag_8 == (cmd & 0xFF0000) >> 16)
                    {
                        if (sw->work_18 == (cmd & 0xFFFF))
                        {
                            cam->cmd_C0++;
                        }
                        else
                        {
                            done = 1;
                        }
                    }
                    else
                    {
                        done = 1;
                    }
                    break;
                case 2:
                    if (sw->flag_9 == (cmd & 0xFF0000) >> 16)
                    {
                        if (sw->work_1C == (cmd & 0xFFFF))
                        {
                            cam->cmd_C0++;
                        }
                        else
                        {
                            done = 1;
                        }
                    }
                    else
                    {
                        done = 1;
                    }
                    break;
                case 3:
                    cam->mode_8 = 0;
                    cam->cmd_C0++;
                    break;
                case 4:
                    cam->mode_8 = 1;
                    cam->cmd_C0++;
                    break;
                case 5:
                    cam->flag_3 = 0;
                    cam->cmd_C0++;
                    break;
                case 6:
                    cam->flag_3 = 1;
                    cam->cmd_C0++;
                    break;
                case 0x10:
                    cam->flag_3 = 0;
                    cam->pos_10 = cam->cmd_C0[1];
                    cam->pos_14 = cam->cmd_C0[2];
                    cam->pos_18 = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x11:
                    cam->rot_40.w = cam->cmd_C0[1];
                    cam->rot_44.w = cam->cmd_C0[2];
                    cam->rot_48.w = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x12:
                    cam->vel_20 = cam->cmd_C0[1];
                    cam->vel_24 = cam->cmd_C0[2];
                    cam->vel_28 = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x13:
                    cam->rot_vel_50 = cam->cmd_C0[1];
                    cam->rot_vel_54 = cam->cmd_C0[2];
                    cam->rot_vel_58 = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x14:
                    cam->flag_3   = 1;
                    cam->index_9  = (cam->cmd_C0[0] & 0xFF0000) >> 16;
                    cam->value_B0 = cam->cmd_C0[1];
                    cam->value_B4 = cam->cmd_C0[2];
                    cam->value_B8 = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x15:
                    cam->pos_70 = cam->cmd_C0[1];
                    cam->pos_74 = cam->cmd_C0[2];
                    cam->pos_78 = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x16:
                    cam->vel_80 = cam->cmd_C0[1];
                    cam->vel_84 = cam->cmd_C0[2];
                    cam->vel_88 = cam->cmd_C0[3];
                    cam->cmd_C0 += 4;
                    break;
                case 0x20:
                    func_8003697C();
                    cam->cmd_C0++;
                    break;
                case 0x21:
                    func_800369C0();
                    cam->cmd_C0++;
                    break;
                case 0x22:
                    func_80036A1C();
                    cam->cmd_C0++;
                    break;
                case 0xFF:
                    done = 1;
                    break;
            }
        } while (done == 0);
    }
    cam->pos_10 += cam->vel_20;
    cam->pos_14 += cam->vel_24;
    cam->pos_18 += cam->vel_28;
    cam->rot_40.w += cam->rot_vel_50;
    cam->rot_44.w += cam->rot_vel_54;
    cam->rot_48.w += cam->rot_vel_58;
    cam->pos_70 += cam->vel_80;
    cam->pos_74 += cam->vel_84;
    cam->pos_78 += cam->vel_88;
}

void func_8001F070(void)
{
    uint8 *script;
    sint16 time;

    SCENE_WORK_FIXED.work_14++;
    SCENE_WORK_FIXED.work_18++;
    SCENE_WORK_FIXED.work_1C++;
    SCENE_WORK_FIXED.work_10++;
    script = SCENE_WORK_FIXED.script_A4;
    time   = *(sint16 *)(script + 2);
    if (time != -1 && time == SCENE_WORK_FIXED.work_10)
    {
        SCENE_WORK_FIXED.script_A4 = script + 8;
        if (SCENE_WORK_FIXED.flag_8 != script[8])
        {
            SCENE_WORK_FIXED.work_18 = 0;
            SCENE_WORK_FIXED.work_1C = 0;
        }
        SCENE_WORK_FIXED.flag_8 = script[8];
        if (SCENE_WORK_FIXED.flag_9 != script[9])
        {
            SCENE_WORK_FIXED.work_1C = 0;
        }
        SCENE_WORK_FIXED.flag_9  = script[9];
        SCENE_WORK_FIXED.work_10 = 0;
    }
}

void func_8001F158(void)
{
    uint8 *script;

    script = SCENE_WORK_FIXED.script_A4;
    SCENE_WORK_FIXED.script_A4 += 8;
    if (SCENE_WORK_FIXED.flag_8 != script[8])
    {
        SCENE_WORK_FIXED.work_18 = 0;
        SCENE_WORK_FIXED.work_1C = 0;
    }
    SCENE_WORK_FIXED.flag_8 = script[8];
    if (SCENE_WORK_FIXED.flag_9 != script[9])
    {
        SCENE_WORK_FIXED.work_1C = 0;
    }
    SCENE_WORK_FIXED.flag_9  = script[9];
    SCENE_WORK_FIXED.work_10 = 0;
}

void func_8001F1DC(void)
{
    Scene_work.work_10 = 0;
    Scene_work.work_18 = 0;
    Scene_work.work_1C = 0;
    Scene_work.flag_8  = 0;
    Scene_work.flag_9  = 0;
}

void func_8001F20C(uint8 *script, uint32 arg)
{
    D_800BC7F0           = arg;
    Scene_work.script_A4 = script;
    Scene_work.flag_8    = script[0];
    Scene_work.flag_9    = script[1];
}

sint32 func_8001F23C(void)
{
    SCENE_GAME_VIEW *gw;
    sint32 routine;
    sint32 sub;
    sint32 id; // the sound id, then the scene's CD file
    sint32 cur;
    sint32 next;

    routine = SCENE_GAME_FIXED.routine_50;
    sub     = SCENE_GAME_FIXED.routine_51;
    func_8001F740();
    id = D_800896D4[routine];
    func_80019F94(id);
    cur = SCENE_GAME_FIXED.value_68;
    id  = D_800893BC[routine][0];
    gw  = &Game_work;
    if (cur != id)
    {
        SCENE_GAME_FIXED.value_68 = id;
        func_800177CC((void *)0x8015C000, (void *)0x80161FFC);
        Cd_read_comb(id);
        next                      = D_800893BC[routine][sub + 1];
        SCENE_GAME_FIXED.value_6A = next;
        if (next >= 0)
        {
            Cd_read_comb(next);
        }
        func_8001D888(0);
        func_8003A3B4();
        func_8003AD14();
    }
    D_80089714[routine]();
    func_8001D928(SCENE_GAME_FIXED.flags_82 & 1);
    gw->value_62++;
    if ((uint32)((uint8)gw->routine_50 - 5) >= 2 && gw->routine_50 != 0xF)
    {
        gw->flag_65 = 1;
        gw->flag_64 = 1;
    }
    // The routine index is reused as the loop counter (retail keeps both in s1)
    for (routine = 0; routine < 8; routine++)
    {
        ((uint32 *)((uint8 *)gw + 0x174))[routine] = 0;
    }
    func_80017944();
    return 0;
}

sint32 func_8001F3C8(void)
{
    SCENE_GAME_VIEW *gw;
    uint8 *pw;
    sint32 routine;
    sint32 sub;
    sint32 cd;

    routine = SCENE_GAME_FIXED.routine_50;
    sub     = SCENE_GAME_FIXED.routine_51;
    func_8001F740();
    gw = &Game_work;
    pw = (uint8 *)&Player_work;
    if (D_800C356C != -1)
    {
        cd = D_800893BC[routine][sub + 1];
        if (cd >= 0 && SCENE_GAME_FIXED.value_6A != cd)
        {
            Cd_read_comb(cd);
            SCENE_GAME_FIXED.value_6A = cd;
        }
        func_8001F5E4();
        func_8001D888(0);
        Obj_work_flag_change(0x3FE, 0x80);
        func_80031AA4();
    }
    D_80089790[routine]();
    if (Scene_work.routine_0 == 0)
    {
        *(uint8 *)0x1F800074 = 0;
        if (D_800C356C != -1)
        {
            *(uint32 *)(pw + 8) = 0;
            pw[0xBD] &= 0xBF;
        }
    }
    if (((sint8 *)pw)[0x44E] >= 0)
    {
        if (((sint8 *)pw)[0x44E] != 0)
        {
            if (((sint8 *)pw)[0x44F] != 0)
            {
                pw[0x170] = pw[0x172];
            }
            else
            {
                pw[0x170] = 0;
            }
            pw[0x171] = pw[0x173];
        }
        else
        {
            pw[0x170] = 0;
            pw[0x171] = 0;
        }
    }
    func_8002CFA4();
    func_80051B40();
    func_80033EBC();
    func_800629E0();
    ((SCENE_FUNC)func_800179FC)(); // retail passes no arguments here
    ((uint8 *)gw)[0x7E] = 0;
    Sce_flag_off(0x1FF);
    return 0;
}

void func_8001F580(sint16 arg0, sint32 arg1, sint32 arg2)
{
    if (arg1 != 0)
    {
        func_8002FBF4();
    }
    if (arg2 != 0)
    {
        Game_work.value_6A = arg0;
    }
    Cd_read_comb(arg0);
}

void func_8001F5E4(void)
{
    sint32 value;
    sint32 idx;

    value = D_80089200[Player_work.value_16A];
    if (Game_work.value_70 != value)
    {
        Game_work.value_70 = value;
        Cd_read_comb(value);
    }
    value = D_80089204[(sint8)Player_work.value_16B >> 1];
    if (Game_work.value_72 != value)
    {
        Game_work.value_72 = value;
        Cd_read_comb(value);
    }
    idx = Player_work.value_172;
    if (idx >= 2)
    {
        value = D_80089208[idx];
        if (Game_work.value_74 != value)
        {
            Game_work.value_74 = value;
            Cd_read_comb(value);
        }
    }
}

void func_8001F6C4(void)
{
    sint16 *tbl;
    sint32 value;
    uint32 sub;

    tbl   = D_800893BC[D_800C356E];
    value = tbl[0];
    sub   = D_800C356F;
    if (Game_work.value_68 != value || ((value = tbl[sub + 1]) >= 0 && Game_work.value_6A != value))
    {
        func_8001D7AC(value);
    }
}

void func_8001F740(void)
{
    func_8001F798(Game_work.routine_50);
    D_8008980C[Game_work.routine_50]();
}

void func_8001F798(sint32 arg)
{
    sint32 i;

    for (i = 0; i < D_80089248[arg].count; i++)
    {
        D_80089248[arg].dst[i] = D_80089248[arg].src[i];
    }
}

void func_8001F820(void)
{
}
