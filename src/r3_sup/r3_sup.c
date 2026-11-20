#include "common.h"
#include "sup.h"

void func_801D8130(void)
{
    Mem_clear((void *)0x801EF000, (void *)0x801EFFFC);
    Mem_clear(&D_801DC208, &D_801DC208.value_a0);
}

sint16 func_801D816C(void)
{
    D_801DC174[D_801DC208.routine_0]();
    return D_801DC208.value_08;
}

void func_801D81B0(void)
{
    switch (D_801DC208.routine_1)
    {
        case 0:
        default:
            D_801DC208.routine_1++;
            SUP_OBJ_0->value_0               = 0x112003;
            D_801DC208.value_1c              = 0x180;
            D_801DC208.value_24              = 0x80;
            D_801DC208.vec_0c.vx             = 0x40;
            D_801DC208.vec_0c.vy             = -0x96;
            D_801DC208.value_20              = 0;
            D_801DC208.vec_0c.vz             = 0;
            *(uint32 *)&SUP_OBJ_0->routine_0 = 0;
            SUP_OBJ_0->value_4               = 0x30000;
            *(uint32 *)&SUP_OBJ_1->routine_0 = 0;
            SUP_OBJ_1->value_0               = 0x52003;
            SUP_OBJ_1->value_4               = 0x30000;
            func_801DBC5C(D_801DC138[Game_work.area_50.b.stage]);
            func_8001B314();
            break;
        case 1:
            if (Sound_fade_flags == 0)
            {
                D_801DC208.routine_1 = 0;
                D_801DC208.routine_0++;
                Sound_call(0x2B, 1, 0);
            }
            break;
    }
}

void func_801D82DC(void)
{
    if (D_801DC208.routine_1 == 0)
    {
        if (Sce_flag_test(0x24))
        {
            *(uint32 *)&D_801DC208.routine_0 = 5;
            Sce_flag_off(0x24);
            func_801D8490();
            return;
        }
        D_801DC208.routine_1++;
        MojiTaskExec(0, SUP_SCRIPT, 1);
    }
    if (Moji_flag >= 0)
    {
        *(uint32 *)&D_801DC208.routine_0 = D_801DC190[Moji_flag & 0xFF];
    }
    func_801D8490();
}

void func_801D8390(void)
{
    switch (D_801DC208.routine_1)
    {
        case 0:
            MojiTaskExec(0, SUP_SCRIPT, 0x1C);
            D_801DC208.routine_1++;
            break;
        case 1:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_1++;
            }
            break;
        case 2:
            D_801DC208.value_08 = 1;
            break;
    }
    func_801D8490();
}

void func_801D8448(void)
{
    if (Moji_flag >= 0)
    {
        D_801DC208.value_08 = (sint8)D_801DC208.value_a0;
    }
    func_801D8490();
}

void func_801D8490(void)
{
    sint32 index;
    SUP_LINK *link;

    func_801D8594();
    func_801D86C4();
    func_801D8524();
    func_801D8564();
    index = SUP_DISPLAY_INDEX;
    link  = Disp_env_ptr;
    setaddr(D_800A4D40[index], getaddr(&link->tag));
    setaddr(&link->tag, &D_800A4D40[index][0x1000] - 1);
}

void func_801D8524(void)
{
    func_80023728(&D_801DC208.vec_0c, D_801DC208.value_1c, D_801DC208.value_20,
                  D_801DC208.value_24);
}

void func_801D8564(void)
{
    func_80028F90(SUP_OBJ_0);
    func_80028F90(SUP_OBJ_1);
}

void func_801D8594(void)
{
    D_801DC19C[SUP_OBJ_0->routine_0](SUP_OBJ_0);
}

void func_801D85D4(SUP_OBJ *op)
{
    op->rot.vz = 0;
    op->pos.vx = op->old_pos.vx = -0x30;
    op->pos.vy = op->old_pos.vy = -0x48;
    op->fpos.vx = op->old_fpos.vx = op->pos.vx << 16;
    op->pos.vz = op->old_pos.vz = 0x22;
    op->rot.vx                  = 0;
    op->fpos.vy = op->old_fpos.vy = op->pos.vy << 16;
    op->fpos.vz = op->old_fpos.vz = op->pos.vz << 16;
    op->rot.vy                    = -0x150;
    Model_work_init(op, 0);
    op->value_158 = 0x2000200;
    op->value_15c = 0x42100200;
    func_800322A8(op, 1, 0);
    op->routine_0++;
}

void func_801D869C(SUP_OBJ *op)
{
    func_80032488(op);
}

void func_801D86BC(SUP_OBJ *op)
{
}

void func_801D86C4(void)
{
    D_801DC1A8[SUP_OBJ_1->routine_0](SUP_OBJ_1);
}

void func_801D8704(SUP_OBJ *op)
{
    op->old_pos.vx = op->pos.vx = 0x40;
    op->old_pos.vy = op->pos.vy = 0;
    op->pos.vz = op->old_pos.vz = 0x60;
    op->rot.vy                  = 0;
    op->rot.vz                  = 0;
    op->rot.vx                  = 0;
    op->fpos.vx = op->old_fpos.vx = op->pos.vx << 16;
    op->fpos.vy = op->old_fpos.vy = op->pos.vy << 16;
    op->fpos.vz = op->old_fpos.vz = op->pos.vz << 16;
    Model_work_init(op, 0);
    op->value_158 = 0x2000200;
    op->value_15c = 0x42100200;
    func_800322A8(op, 0, 0);
    op->routine_0++;
    D_801DC208.anim_94 = 0;
}

void func_801D87CC(SUP_OBJ *op)
{
    if (D_801DC208.anim_94)
    {
        func_800322A8(op, D_801DC208.anim_94, 0);
        D_801DC208.anim_94 = 0;
    }
    else
    {
        func_80032488(op);
    }
}

void func_801D881C(SUP_OBJ *op)
{
}

void func_801D8824(void)
{
    switch (D_801DC208.routine_1)
    {
        case 0:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = SUP_OBJ_1->pos.vx;
            D_801DC208.value_48 = SUP_OBJ_1->pos.vy - 0x76;
            D_801DC208.value_4c = SUP_OBJ_1->pos.vz;
            D_801DC208.value_54 = 0x100;
            D_801DC208.value_58 = D_801DC208.value_20;
            D_801DC208.value_5c = D_801DC208.value_24;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_1++;
            break;
        case 2:
            MojiTaskExec(0, SUP_SCRIPT, 5);
            D_801DC208.anim_94 = 8;
            D_801DC208.routine_1++;
            break;
        case 3:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_1 = Moji_flag + 4;
            }
            break;
        case 4:
            func_801D8DC0();
            break;
        case 5:
            func_801D8E84();
            break;
        case 6:
            func_801DB1E0();
            break;
        case 7:
            if (Game_work.area_50.h == 0xB13)
            {
                D_801DC208.routine_1 += 2;
            }
            else
            {
                func_801DB5B8();
            }
            break;
        case 8:
        default:
            D_801DC208.routine_1++;
            break;
        case 9:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = 0x40;
            D_801DC208.value_48 = -0x96;
            D_801DC208.value_4c = 0;
            D_801DC208.value_54 = 0x180;
            D_801DC208.value_58 = 0;
            D_801DC208.value_5c = 0x80;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_1++;
            break;
        case 1:
        case 10:
            if (--D_801DC208.value_0a == 0)
            {
                D_801DC208.routine_1++;
            }
            func_801D8B68();
            break;
        case 11:
            *(uint32 *)&D_801DC208.routine_0 = 1;
            break;
    }
    if (D_801DC208.value_08 >= 0)
    {
        func_801D8490();
    }
}

void func_801D8B68(void)
{
    D_801DC208.vec_0c.vx = (D_801DC208.vec_28.vx * D_801DC208.value_0a +
                            D_801DC208.value_44 * (16 - D_801DC208.value_0a)) >>
                           4;
    D_801DC208.vec_0c.vy = (D_801DC208.vec_28.vy * D_801DC208.value_0a +
                            D_801DC208.value_48 * (16 - D_801DC208.value_0a)) >>
                           4;
    D_801DC208.vec_0c.vz = (D_801DC208.vec_28.vz * D_801DC208.value_0a +
                            D_801DC208.value_4c * (16 - D_801DC208.value_0a)) >>
                           4;
    D_801DC208.value_1c  = (D_801DC208.value_38 * D_801DC208.value_0a +
                            D_801DC208.value_54 * (16 - D_801DC208.value_0a)) >>
                           4;
    D_801DC208.value_20  = (D_801DC208.value_3c * D_801DC208.value_0a +
                            D_801DC208.value_58 * (16 - D_801DC208.value_0a)) >>
                           4;
    D_801DC208.value_24  = (D_801DC208.value_40 * D_801DC208.value_0a +
                            D_801DC208.value_5c * (16 - D_801DC208.value_0a)) >>
                           4;
}

void func_801D8CC8(sint32 i)
{
    D_801DC208.vec_28   = D_801DC208.vec_0c;
    D_801DC208.value_38 = D_801DC208.value_1c;
    D_801DC208.value_3c = D_801DC208.value_20;
    D_801DC208.value_40 = D_801DC208.value_24;
    D_801DC208.value_44 = D_801DC1B4[i].value_0;
    D_801DC208.value_48 = D_801DC1B4[i].value_2;
    D_801DC208.value_4c = D_801DC1B4[i].value_4;
    D_801DC208.value_54 = D_801DC1B4[i].value_6;
    D_801DC208.value_58 = D_801DC1B4[i].value_8;
    D_801DC208.value_5c = D_801DC1B4[i].value_a;
    D_801DC208.value_0a = 0x10;
}

void func_801D8DC0(void)
{
    switch (D_801DC208.routine_2)
    {
        case 0:
            MojiTaskExec(0, SUP_SCRIPT, 0xA);
            D_801DC208.anim_94 = 8;
            D_801DC208.routine_2++;
            break;
        case 1:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_2++;
            }
            break;
        case 2:
            D_801DC208.routine_2++;
            break;
        case 3:
            *(uint32 *)&D_801DC208.routine_0 = 0x203;
            break;
    }
}

void func_801D8E84(void)
{
    switch (D_801DC208.routine_2)
    {
        case 0:
            MojiTaskExec(0, SUP_SCRIPT, 0xF);
            MojiTaskExec(1, SUP_SCRIPT, 0x10);
            D_801DC208.anim_94 = 8;
            D_801DC208.routine_2++;
            break;
        case 1:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_2 = Moji_flag + 2;
            }
            break;
        case 2:
            func_801D8F68();
            break;
        case 3:
            func_801DAB58();
            break;
        case 4:
            *(uint32 *)&D_801DC208.routine_0 = 0x203;
            break;
    }
}

void func_801D8F68(void)
{
    SUP_OBJ *op;

    op = SUP_OBJ_1;
    switch (D_801DC208.routine_3)
    {
        case 0:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = SUP_OBJ_1->pos.vx - 0x40;
            D_801DC208.value_48 = SUP_OBJ_1->pos.vy - 0x76;
            D_801DC208.value_4c = SUP_OBJ_1->pos.vz;
            D_801DC208.value_54 = 0xE0;
            D_801DC208.value_58 = D_801DC208.value_20;
            D_801DC208.value_5c = D_801DC208.value_24;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_3++;
            break;
        case 1:
            if (--D_801DC208.value_0a == 0)
            {
                D_801DC208.routine_3++;
            }
            func_801D8B68();
            op->rot.vy += 0x24;
            break;
        case 2:
            D_801DC208.value_64    = -0xD0;
            D_801DC208.value_66    = 8;
            D_801DC208.scale_68.vy = 0x1000;
            D_801DC208.scale_68.vx = 0;
            D_801DC208.scale_68.vz = 0;
            D_801DC208.scale_78.vx = 0x100;
            D_801DC208.scale_78.vy = 0x100;
            D_801DC208.scale_78.vz = 0x100;
            D_801DC208.rot_88.vz   = 0;
            D_801DC208.rot_88.vy   = 0;
            D_801DC208.rot_88.vx   = 0;
            func_801D9388();
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_3++;
            break;
        case 3:
            D_801DC208.scale_68.vx += 0x100;
            D_801DC208.scale_68.vz += 0x100;
            D_801DC208.value_64 += 0xD;
            if (D_801DC208.value_64 >= 0)
            {
                D_801DC208.routine_3++;
                MojiTaskExec(0, SUP_SCRIPT, 0x64);
                D_801DC208.anim_94  = 8;
                D_801DC208.value_90 = 0;
            }
            func_801D9504();
            break;
        case 4:
            if (Cd_read_sync2() == 0)
            {
                switch (D_801DC208.value_90)
                {
                    case 0:
                    default:
                        func_801D952C();
                        break;
                    case 1:
                        D_801DC208.routine_3 = 6;
                        break;
                    case 2:
                        D_801DC208.routine_3 = 7;
                        break;
                }
            }
            func_801D9504();
            break;
        case 6:
            func_801D9504();
            if (Moji_flag < 0)
            {
                break;
            }
            // fall through
        case 5:
            D_801DC208.routine_3++;
            break;
        case 7:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = SUP_OBJ_1->pos.vx;
            D_801DC208.value_48 = SUP_OBJ_1->pos.vy - 0x76;
            D_801DC208.value_4c = SUP_OBJ_1->pos.vz;
            D_801DC208.value_54 = 0x100;
            D_801DC208.value_58 = D_801DC208.value_20;
            D_801DC208.value_5c = D_801DC208.value_24;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_3++;
            break;
        case 8:
            if (--D_801DC208.value_0a == 0)
            {
                D_801DC208.routine_3++;
            }
            func_801D8B68();
            op->rot.vy -= 0x24;
            break;
        case 9:
            *(uint32 *)&D_801DC208.routine_0 = 0x503;
            break;
    }
}

// Three groups of 13 sprites. The middle group's flag test reads D_801DC0C8[i - 13]; the
// separate arms for the other two groups (merged later by cross-jumping) keep the loop large
// enough that loop.c doesn't strength-reduce that read into its own pointer.
void func_801D9388(void)
{
    SUP_SPR *sp;
    SUP_SPR *tbl;
    sint32 i;

    tbl = SUP_SPR_TBL;
    for (i = 0; i < 40; i++)
    {
        sp          = &tbl[i];
        sp->value_0 = 7;
        sp->value_1 = 0xE0;
        sp->value_2 = 0x11;
        sp->value_3 = D_801DBF48[i].pad;
        if (i >= 13 && i < 26)
        {
            if (!Sce_flag_test(D_801DC0C8[i - 13] + 0x4C0))
            {
                sp->value_3 = 5;
            }
            else
            {
                sp->value_3 = D_801DBF48[i].pad;
            }
        }
        else if (i >= 26)
        {
            sp->value_3 = D_801DBF48[i].pad;
        }
        else
        {
            sp->value_3 = D_801DBF48[i].pad;
        }
        sp->routine.w = 0;
        sp->pos       = D_801DBF48[i];
        sp->color_40  = 0x808080;
        sp->mtx.w[0]  = 0x200;
        sp->mtx.w[1]  = 0;
        sp->mtx.w[2]  = 0x200;
        sp->mtx.w[3]  = 0;
        sp->mtx.w[4]  = 0x200;
        func_8002FA10(sp, &sp->value_3);
        sp->routine.b[0]++;
    }
    D_801DC208.value_60 = D_801DC0A4[Player_work.value_172];
    D_801DC208.value_0a = 0;
    D_801DC208.value_92 = 0;
}

void func_801D9504(void)
{
    func_801D9C74();
}

void func_801D9524(void)
{
}

void func_801D952C(void)
{
    if (D_801DC208.value_0a != 0)
    {
        return;
    }
    if (Joy1.held & 0x10)
    {
        D_801DC208.value_92 = -1;
    }
    if (Joy1.held & 0x40)
    {
        D_801DC208.value_92 = 1;
    }
    D_801DC268 += D_801DC208.value_92;
    if (D_801DC268 >= 13)
    {
        D_801DC268 = 0;
    }
    if (D_801DC268 < 0)
    {
        D_801DC268 = 12;
    }
    if (!Sce_flag_test(D_801DC0C8[D_801DC268] + 0x4C0))
    {
        D_801DC208.value_0a = D_801DC208.value_92 * 16;
        return;
    }
    if (D_801DC208.value_92 != 0)
    {
        D_801DC208.value_0a = D_801DC208.value_92 * 16;
        D_801DC208.value_92 = 0;
        func_80053AA4(0);
        MojiTaskExec(0, SUP_SCRIPT, D_801DC088[D_801DC268][0]);
        D_801DC208.rot_88.vz = 0;
        D_801DC208.rot_88.vy = 0;
        D_801DC208.rot_88.vx = 0;
    }
    if (Joy1.pressed & 0x1000)
    {
        D_801DC208.value_90 = 2;
        func_80053AA4(0);
    }
    if (Joy1.pressed & 0x4008)
    {
        func_80053AA4(0);
        MojiTaskExec(0, SUP_SCRIPT, 0x65);
        Sound_call(0x88, 0, 0);
        D_801DC208.anim_94    = 8;
        D_801DC208.value_90   = 1;
        Player_work.value_172 = D_801DC0C8[D_801DC268];
        func_80037594();
        if (Player_work.value_44e > 0)
        {
            Obj_work_flag_change(8, 0x80);
            Player_work.value_170 = Player_work.value_172;
            if (Player_work.value_170 > 0)
            {
                Player_work.value_44f = 1;
            }
            else
            {
                Player_work.value_44f = 0;
            }
            func_8001F5E4();
        }
    }
}

// The price row is reached as a pointer (`D_8008D8EC + kind * 20`): indexing the flat table
// with `kind * 20 + level` folds into (kind * 20 + level) * 2 instead of retail's row + level * 2.
void func_801D9794(void)
{
    if (D_801DC208.value_0a != 0)
    {
        return;
    }
    if (Joy1.held & 0x10)
    {
        D_801DC208.value_92 = -1;
    }
    if (Joy1.held & 0x40)
    {
        D_801DC208.value_92 = 1;
    }
    D_801DC208.value_60 += D_801DC208.value_92;
    if (D_801DC208.value_60 >= 13)
    {
        D_801DC208.value_60 = 0;
    }
    if (D_801DC208.value_60 < 0)
    {
        D_801DC208.value_60 = 12;
    }
    if (!Sce_flag_test(D_801DC0C8[D_801DC208.value_60] + 0x4C0))
    {
        D_801DC208.value_0a = D_801DC208.value_92 * 16;
        return;
    }
    if (D_801DC208.value_92 != 0)
    {
        D_801DC208.value_0a = D_801DC208.value_92 * 16;
        D_801DC208.value_92 = 0;
        func_80053AA4(0);
        func_8005C24C(D_801DC208.value_60);
        MojiTaskExec(0, SUP_SCRIPT, 0x83);
        D_801DC208.rot_88.vz = 0;
        D_801DC208.rot_88.vy = 0;
        D_801DC208.rot_88.vx = 0;
    }
    if (Joy1.pressed & 0x1000)
    {
        D_801DC208.value_90 = 2;
        D_801DC208.routine_3++;
        func_80053AA4(0);
        func_80053AA4(1);
    }
    if (Joy1.pressed & 0x4008)
    {
        func_80053AA4(0);
        func_8005C224(
            (D_8008D8EC +
             D_801DC208.value_60 * 20)[Player_work.level_4f4[D_801DC0C8[D_801DC208.value_60]][0]] *
            10);
        MojiTaskExec(0, SUP_SCRIPT, 0x99);
        D_801DC208.anim_94  = 8;
        D_801DC208.value_90 = 1;
    }
}

void func_801D99CC(void)
{
    sint32 redraw;
    sint32 msg;
    sint32 price;
    uint8 level;

    redraw = 0;
    if (D_801DC208.value_9c)
    {
        redraw = 1;
    }
    else
    {
        if (Joy1.pressed & 0x10)
        {
            D_801DC208.value_96--;
            redraw = 1;
        }
        if (Joy1.pressed & 0x40)
        {
            D_801DC208.value_96++;
            redraw = 1;
        }
        if (D_801DC208.value_96 < 0)
        {
            D_801DC208.value_96 = 4;
        }
        if (D_801DC208.value_96 >= 5)
        {
            D_801DC208.value_96 = 0;
        }
    }
    level = *(Player_work.level_4f4[D_801DC0C8[D_801DC208.value_60]] + D_801DC208.value_96);
    price = ((uint16(*)[5][4])D_8008D8EC)[D_801DC208.value_60][D_801DC208.value_96][level] * 10;
    if (redraw)
    {
        func_80053AA4(0);
        switch (D_801DC208.value_96)
        {
            case 0:
            default:
                msg = 0x99;
                break;
            case 1:
                msg = D_801DC1E4[D_801DC208.value_60];
                break;
            case 2:
                msg = 0x9C;
                break;
            case 3:
                msg = 0x9D;
                break;
            case 4:
                msg = D_801DC1F4[D_801DC208.value_60];
                break;
        }
        func_8005C224(price);
        MojiTaskExec(0, SUP_SCRIPT, msg);
    }
    if (Joy1.pressed & 0x1000)
    {
        D_801DC208.routine_3++;
        D_801DC208.value_90 = 2;
        func_80053AA4(0);
    }
    if ((Moji_flag & 0x20000) && (Joy1.pressed & 0x4008))
    {
        func_80053AA4(0);
        if (Money_check(-price))
        {
            MojiTaskExec(0, SUP_SCRIPT, 0x85);
            D_801DC208.value_90 = 1;
        }
        else
        {
            D_801DC208.value_98 = price;
            MojiTaskExec(0, SUP_SCRIPT, 0x86);
            D_801DC208.value_90 = 3;
        }
        D_801DC208.anim_94 = 8;
    }
}

// Draws the part shop: frame, part list, the selected part's stats and the rotating models.
// Notes for the match: the 0x60U/0x68U row offsets and the (sint16) on the model height stop
// GCC re-associating the constants; the level table is [kind][8] because a flat byte array
// indexed by `kind * 8 + n` across calls reserves stack temporaries retail does not have.
void func_801D9C74(void)
{
    POLY_FT4 *p;
    SUP_SPR *sp;
    SUP_SPR *tbl;
    sint32 i;
    sint32 j;
    sint32 k;

    tbl = SUP_SPR_TBL;
    i   = D_801DC208.value_60;
    if (D_801DC208.value_0a != 0)
    {
        if (D_801DC208.value_0a > 0)
        {
            D_801DC208.value_0a--;
        }
        else
        {
            D_801DC208.value_0a++;
        }
        if (D_801DC208.value_0a == 0)
        {
            Sound_call(0x87, 0, 0);
        }
    }
    if (D_801DC208.routine_2 == 3 && D_801DC208.routine_3 >= 5 && D_801DC208.routine_3 < 10)
    {
        p                 = (*SUP_PACKET_PTR)++;
        *(u_long *)p      = 0x09000000;
        j                 = D_800BBCF8[(SUP_SCRATCH_02 & 0xF) * 2] >> 5;
        *(u_long *)&p->r0 = 0x2E000000 | (j << 16) | (j << 8) | j;
        p->x0 = p->x2 = D_801DC208.value_64 + 0x11;
        p->x1 = p->x3 = D_801DC208.value_64 + 0x31;
        p->y0 = p->y1 = D_801DC208.value_66 + (D_801DC208.value_96 * 12 + 0x60U);
        p->y2 = p->y3 = D_801DC208.value_66 + (D_801DC208.value_96 * 12 + 0x68U);
        p->u1 = p->u3 = 8;
        p->v0 = p->v1 = 0xF8;
        p->v2 = p->v3 = 0xFF;
        p->clut       = 0x3D09;
        p->u0 = p->u2 = 0;
        p->tpage      = 0xC;
        addPrim(&Disp_env_ptr->ot_78, p);
    }
    if (Sce_flag_test(D_801DC0C8[D_801DC208.value_60] + 0x4C0))
    {
        func_801DA7DC(D_8008D7E8[i][0][(sint8)Player_work.level_4f4[D_801DC0C8[i]][0]], 0, 0);
        func_801DA7DC(D_8008D7E8[i][1][(sint8)Player_work.level_4f4[D_801DC0C8[i]][1]], 12, 0);
        func_801DA7DC(D_8008D7E8[i][2][(sint8)Player_work.level_4f4[D_801DC0C8[i]][2]], 24, 0);
        func_801DA7DC(D_8008D7E8[i][3][(sint8)Player_work.level_4f4[D_801DC0C8[i]][3]], 36, 0);
        func_801DA7DC(D_8008D7E8[i][4][(sint8)Player_work.level_4f4[D_801DC0C8[i]][4]], 48, 0);
        p            = (*SUP_PACKET_PTR)++;
        *(u_long *)p = 0x09000000;
        if (D_801DC208.value_0a < 0)
        {
            j = (D_801DC208.value_0a + 16) * 8;
        }
        else
        {
            j = (16 - D_801DC208.value_0a) * 8;
        }
        *(u_long *)&p->r0 = 0x2C000000 | (j << 16) | (j << 8) | j;
        p->x0 = p->x2 = D_801DC208.value_64 + 0x1A;
        p->x1 = p->x3 = D_801DC208.value_64 + 0x62;
        p->y0 = p->y1 = D_801DC208.value_66 + 0x51;
        p->y2 = p->y3 = D_801DC208.value_66 + 0x58;
        p->u0 = p->u2 = D_801DC158[D_801DC208.value_60][0];
        p->u1 = p->u3 = D_801DC158[D_801DC208.value_60][0] + 0x48;
        p->v0 = p->v1 = D_801DC158[D_801DC208.value_60][1];
        p->v2 = p->v3 = D_801DC158[D_801DC208.value_60][1] + 7;
        p->clut       = 0x3D08;
        p->tpage      = 0xC;
        addPrim(&Disp_env_ptr->ot_78, p);
    }
    if (D_801DC208.routine_2 == 3 && D_801DC208.routine_3 >= 5 && D_801DC208.routine_3 < 8)
    {
        j = (D_8008D7E8[i][D_801DC208.value_96] +
             1)[*(Player_work.level_4f4[D_801DC0C8[i]] + D_801DC208.value_96)];
        if (j != 0)
        {
            func_801DA7DC(j, D_801DC208.value_96 * 12, 1);
        }
    }

    p                 = (*SUP_PACKET_PTR)++;
    *(u_long *)p      = 0x09000000;
    *(u_long *)&p->r0 = 0x2C808080;
    p->x0 = p->x2 = D_801DC208.value_64;
    p->x1 = p->x3 = D_801DC208.value_64 + 0x80;
    p->y0 = p->y1 = D_801DC208.value_66;
    p->y2 = p->y3 = D_801DC208.value_66 + 0x5D;
    p->u0 = p->u2 = 0;
    p->u1 = p->u3 = 0x80;
    p->v0 = p->v1 = 0;
    p->v2 = p->v3 = 0x5D;
    p->clut       = 0x3D09;
    p->tpage      = 0xC;
    addPrim(&Disp_env_ptr->ot_78, p);

    p                 = (*SUP_PACKET_PTR)++;
    *(u_long *)p      = 0x09000000;
    *(u_long *)&p->r0 = 0x2C808080;
    p->x0 = p->x2 = D_801DC208.value_64 + 0x80;
    p->x1 = p->x3 = D_801DC208.value_64 + 0xC8;
    p->y0 = p->y1 = D_801DC208.value_66 + 0x18;
    p->y2 = p->y3 = D_801DC208.value_66 + 0x50;
    p->u1 = p->u3 = 0xC8;
    p->v0 = p->v1 = 0x18;
    p->u0 = p->u2 = 0x80;
    p->v2 = p->v3 = 0x50;
    p->clut       = 0x3D09;
    p->tpage      = 0xC;
    addPrim(&Disp_env_ptr->ot_78, p);

    p                 = (*SUP_PACKET_PTR)++;
    *(u_long *)p      = 0x09000000;
    *(u_long *)&p->r0 = 0x2C808080;
    p->x0 = p->x2 = D_801DC208.value_64 + 8;
    p->x1 = p->x3 = D_801DC208.value_64 + 0x3A;
    p->y0 = p->y1 = D_801DC208.value_66 + 0x5D;
    p->y2 = p->y3 = D_801DC208.value_66 + 0x9C;
    p->u0 = p->u2 = 8;
    p->u1 = p->u3 = 0x3A;
    p->v0 = p->v1 = 0x5D;
    p->v2 = p->v3 = 0x9C;
    p->clut       = 0x3D09;
    p->tpage      = 0xC;
    addPrim(&Disp_env_ptr->ot_78, p);

    for (j = 0; j < 13; j++)
    {
        sp = &tbl[j];
        if (j == i && D_801DC208.value_64 >= 0)
        {
            if (Sce_flag_test(D_801DC0C8[D_801DC208.value_60] + 0x4C0))
            {
                if (D_801DC208.value_0a != 0)
                {
                    if (D_801DC208.value_0a > 0)
                    {
                        k = D_801DC208.value_0a;
                    }
                    else
                    {
                        k = -D_801DC208.value_0a;
                    }
                    k               = (16 - k) * 8;
                    sp[26].color_40 = (k << 16) | (k << 8) | k;
                }
                else
                {
                    sp[26].color_40 = 0x808080;
                }
                sp[26].value_0 = 7;
                RotMatrix(&D_801DC208.rot_88, &sp[26].mtx.m);
                ScaleMatrix(&sp[26].mtx.m, &D_801DC208.scale_78);
                D_801DC208.rot_88.vy += 0x30;
            }
        }
        else
        {
            sp[26].value_0 = 0;
        }
    }

    for (j = 0; j < 13; j++)
    {
        sp = &tbl[j];
        k  = j;
        if (j - i >= 7)
        {
            k = j - 13;
        }
        if (k - i < -6)
        {
            k = j + 13;
        }
        sp->pos.vy = sp[13].pos.vy = (sint16)(D_801DC208.value_0a * 2 - 0x97) - (i - k) * 32;
        sp->mtx.w[0]               = 0x200;
        sp->mtx.w[1]               = 0;
        sp->mtx.w[2]               = 0x200;
        sp->mtx.w[3]               = 0;
        sp->mtx.w[4]               = 0x200;
        RotMatrixY(D_801DC208.value_0a << 8, &sp->mtx.m);
        sp[13].mtx.w[0] = 0x200;
        sp[13].mtx.w[1] = 0;
        sp[13].mtx.w[2] = 0x200;
        sp[13].mtx.w[3] = 0;
        sp[13].mtx.w[4] = 0x200;
        RotMatrixY(D_801DC208.value_0a << 8, &sp[13].mtx.m);
        if (j == i && D_801DC208.value_0a == 0)
        {
            sp[13].color_40 = 0x808080;
        }
        else
        {
            sp[13].color_40 = 0x4040;
        }
    }

    tbl[39].mtx.w[0] = 0x200;
    tbl[39].mtx.w[1] = 0;
    tbl[39].mtx.w[2] = 0x200;
    tbl[39].mtx.w[3] = 0;
    tbl[39].mtx.w[4] = 0x200;
    for (j = 0; j < 40; j++)
    {
        sp = &tbl[j];
        ScaleMatrix(&sp->mtx.m, &D_801DC208.scale_68);
        if (sp->value_0 & 2)
        {
            func_8002A160(&sp->model_14, (sint8)sp->value_0);
        }
    }

    p                 = (*SUP_PACKET_PTR)++;
    *(u_long *)p      = 0x09000000;
    *(u_long *)&p->r0 = 0x2C010101;
    p->x0 = p->x2 = D_801DC208.value_64 + 0x10;
    p->x1 = p->x3 = D_801DC208.value_64 + 0x70;
    p->y0 = p->y1 = D_801DC208.value_66 + 0x10;
    p->y2 = p->y3 = D_801DC208.value_66 + 0x50;
    p->u0 = p->u2 = 0x88;
    p->u1 = p->u3 = 0x90;
    p->v2 = p->v3 = 7;
    p->v0 = p->v1 = 0;
    p->clut       = 0x3D09;
    p->tpage      = 0xC;
    addPrim(SUP_OT + 0x28, p);
}

void func_801DA7DC(sint32 w, sint32 y, sint32 v)
{
    POLY_FT4 *p;
    sint32 n;
    sint32 top;
    sint32 x;
    sint32 py;

    if (w == 0xFF)
    {
        if (D_801DC208.value_0a == 0 && v == 0)
        {
            top               = y + 0x60;
            p                 = (*SUP_PACKET_PTR)++;
            *(u_long *)p      = 0x09000000;
            *(u_long *)&p->r0 = 0x2C808080;
            p->x0 = p->x2 = D_801DC208.value_64 + 0x4E;
            p->x1 = p->x3 = D_801DC208.value_64 + 0x76;
            p->y0 = p->y1 = D_801DC208.value_66 + top;
            p->y2 = p->y3 = D_801DC208.value_66 + top + 8;
            p->u1 = p->u3 = 0x28;
            p->v0 = p->v1 = 0xE8;
            p->v2 = p->v3 = 0xF0;
            p->clut       = 0x3D09;
            p->u0 = p->u2 = 0;
            p->tpage      = 0xC;
            addPrim(&Disp_env_ptr->ot_78, p);
        }
        w = 0x58;
    }
    if (D_801DC208.value_0a < 0)
    {
        n = D_801DC208.value_0a + 16;
    }
    else
    {
        n = 16 - D_801DC208.value_0a;
    }
    w = w * n / 16;
    if (w >= 4)
    {
        x                 = w + 0x36;
        py                = y + 0x60; // a block-local copy, not y += 0x60 (register allocation)
        p                 = (*SUP_PACKET_PTR)++;
        *(u_long *)p      = 0x09000000;
        *(u_long *)&p->r0 = 0x2C808080;
        p->x0 = p->x2 = D_801DC208.value_64 + 0x36;
        p->x1 = p->x3 = D_801DC208.value_64 + x - 2;
        p->y0 = p->y1 = D_801DC208.value_66 + py;
        p->y2 = p->y3 = D_801DC208.value_66 + py + 8;
        p->u0 = p->u2 = 0x88;
        p->u1 = p->u3 = 0xB8;
        p->v0 = p->v1 = v * 8;
        p->v2 = p->v3 = v * 8 + 8;
        p->clut       = 0x3D09;
        p->tpage      = 0xC;
        addPrim(&Disp_env_ptr->ot_78, p);

        p                 = (*SUP_PACKET_PTR)++;
        *(u_long *)p      = 0x09000000;
        *(u_long *)&p->r0 = 0x2C808080;
        p->x0 = p->x2 = D_801DC208.value_64 + x - 2;
        p->x1 = p->x3 = D_801DC208.value_64 + x;
        p->y0 = p->y1 = D_801DC208.value_66 + py;
        p->y2 = p->y3 = D_801DC208.value_66 + py + 8;
        p->u0 = p->u2 = 0xB8;
        p->u1 = p->u3 = 0xBA;
        p->v0 = p->v1 = v * 8;
        p->v2 = p->v3 = v * 8 + 8;
        p->clut       = 0x3D09;
        p->tpage      = 0xC;
        addPrim(&Disp_env_ptr->ot_78, p);
    }
}

void func_801DAB58(void)
{
    SUP_OBJ *op;

    op = SUP_OBJ_1;
    switch (D_801DC208.routine_3)
    {
        case 0:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = SUP_OBJ_1->pos.vx - 0x40;
            D_801DC208.value_48 = SUP_OBJ_1->pos.vy - 0x76;
            D_801DC208.value_4c = SUP_OBJ_1->pos.vz;
            D_801DC208.value_54 = 0xE0;
            D_801DC208.value_58 = D_801DC208.value_20;
            D_801DC208.value_5c = D_801DC208.value_24;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_3++;
            break;
        case 1:
            if (--D_801DC208.value_0a == 0)
            {
                D_801DC208.routine_3++;
            }
            func_801D8B68();
            op->rot.vy += 0x24;
            break;
        case 2:
            D_801DC208.value_64    = -0xD0;
            D_801DC208.value_66    = 8;
            D_801DC208.scale_68.vy = 0x1000;
            D_801DC208.scale_68.vx = 0;
            D_801DC208.scale_68.vz = 0;
            D_801DC208.scale_78.vx = 0x100;
            D_801DC208.scale_78.vy = 0x100;
            D_801DC208.scale_78.vz = 0x100;
            D_801DC208.rot_88.vz   = 0;
            D_801DC208.rot_88.vy   = 0;
            D_801DC208.rot_88.vx   = 0;
            func_801D9388();
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_3++;
            break;
        case 3:
            D_801DC208.scale_68.vx += 0x100;
            D_801DC208.scale_68.vz += 0x100;
            D_801DC208.value_64 += 0xD;
            if (D_801DC208.value_64 >= 0)
            {
                D_801DC208.routine_3++;
                func_8005C24C(D_801DC208.value_60);
                MojiTaskExec(0, SUP_SCRIPT, 0x83);
                MojiTaskExec(1, SUP_SCRIPT, 0x82);
                D_801DC208.anim_94  = 8;
                D_801DC208.value_90 = 0;
            }
            func_801D9504();
            break;
        case 4:
            MojiTaskExec(3, SUP_SCRIPT, 2);
            func_801D9794();
            func_801DB1C0();
            switch (D_801DC208.value_90)
            {
                case 0:
                    break;
                case 1:
                    MojiTaskExec(1, SUP_SCRIPT, 0x84);
                    D_801DC208.routine_3 = 5;
                    D_801DC208.value_90  = 0;
                    D_801DC208.value_96  = 0;
                    D_801DC208.value_9c  = 1;
                    break;
                case 2:
                    D_801DC208.routine_3 = 10;
                    D_801DC208.value_90  = 0;
                    break;
            }
            break;
        case 5:
            func_801D99CC();
            D_801DC208.value_9c = 0;
            func_801DB1C0();
            switch (D_801DC208.value_90)
            {
                case 0:
                    break;
                case 1:
                    D_801DC208.value_90  = 0;
                    D_801DC208.routine_3 = 6;
                    func_80053AA4(1);
                    break;
                case 2:
                    func_8005C24C(D_801DC208.value_60);
                    MojiTaskExec(0, SUP_SCRIPT, 0x83);
                    MojiTaskExec(1, SUP_SCRIPT, 0x82);
                    D_801DC208.anim_94   = 8;
                    D_801DC208.value_90  = 0;
                    D_801DC208.routine_3 = 4;
                    break;
                case 3:
                    D_801DC208.value_90  = 0;
                    D_801DC208.routine_3 = 7;
                    func_80053AA4(1);
                    break;
            }
            break;
        case 7:
            func_801DB1C0();
            if (!(Moji_flag & 0x8000000))
            {
                if (Moji_flag & 0xFF)
                {
                    MojiTaskExec(1, SUP_SCRIPT, 0x84);
                    D_801DC208.routine_3 = 5;
                    D_801DC208.value_9c  = 1;
                }
                else
                {
                    D_801DC208.routine_3 = 8;
                }
            }
            break;
        case 8:
            (*(Player_work.level_4f4[D_801DC0C8[D_801DC208.value_60]] + D_801DC208.value_96))++;
            Money_add(-D_801DC208.value_98, 0, 0);
            func_801DB1C0();
            func_80037594();
            MojiTaskExec(0, SUP_SCRIPT, 0x87);
            Sound_call(0x89, 0, 0);
            D_801DC208.routine_3++;
            break;
        case 6:
        case 9:
            func_801DB1C0();
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec(1, SUP_SCRIPT, 0x84);
                D_801DC208.routine_3 = 5;
                D_801DC208.value_9c  = 1;
            }
            break;
        case 10:
            func_80053AA4(3);
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = SUP_OBJ_1->pos.vx;
            D_801DC208.value_48 = SUP_OBJ_1->pos.vy - 0x76;
            D_801DC208.value_4c = SUP_OBJ_1->pos.vz;
            D_801DC208.value_54 = 0x100;
            D_801DC208.value_58 = D_801DC208.value_20;
            D_801DC208.value_5c = D_801DC208.value_24;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_3++;
            break;
        case 11:
            if (--D_801DC208.value_0a == 0)
            {
                D_801DC208.routine_3++;
            }
            func_801D8B68();
            op->rot.vy -= 0x24;
            break;
        case 12:
            *(uint32 *)&D_801DC208.routine_0 = 0x503;
            break;
    }
}

void func_801DB1C0(void)
{
    func_801D9C74();
}

void func_801DB1E0(void)
{
    switch (D_801DC208.routine_2)
    {
        case 0:
            MojiTaskExec(0, SUP_SCRIPT, 0x14);
            D_801DC208.anim_94 = 8;
            D_801DC208.routine_2++;
            break;
        case 1:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_2 = Moji_flag + 2;
            }
            break;
        case 2:
            func_801DB2AC();
            break;
        case 3:
            *(uint32 *)&D_801DC208.routine_0 = 0x203;
            break;
    }
}

void func_801DB2AC(void)
{
    switch (D_801DC208.routine_3)
    {
        case 0:
            func_80017C30(9);
            D_801DC208.routine_3++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                D_801DC208.routine_3++;
                D_801DC208.count_a1 = 0x3C;
            }
            break;
        case 2:
            if (--D_801DC208.count_a1 == 0)
            {
                D_801DC208.routine_3++;
            }
            break;
        case 3:
            D_801DC208.found_a2 = func_801DB43C();
            func_80017C30(1);
            D_801DC208.routine_3++;
            break;
        case 4:
            if (D_80098A72 == 0)
            {
                D_801DC208.routine_3++;
            }
            break;
        case 5:
            if (D_801DC208.found_a2)
            {
                MojiTaskExec(0, SUP_SCRIPT, 0x15);
            }
            else
            {
                MojiTaskExec(0, SUP_SCRIPT, 0x17);
            }
            D_801DC29C = 8;
            // The one-pass loop keeps the increment after the store, so it merges with case 6's.
            do
            {
                D_801DC208.routine_3++;
            } while (0);
            break;
        case 6:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_3++;
            }
            break;
        case 7:
            *(uint32 *)&D_801DC208.routine_0 = 0x203;
            break;
    }
}

// Clears every complete scenario-flag combination and sets its result flag. The one- and
// two-flag cases jump into the three-flag case's clearing tail, which gives retail's branch
// directions (plain nested ifs invert them).
sint32 func_801DB43C(void)
{
    SUP_KEY key;
    sint32 i;
    sint32 found;

    found           = 0;
    i               = 0;
    *(uint32 *)&key = *(uint32 *)&D_801DBE90[0].key;
    while (key.b[0] != 0xFF)
    {
        if (key.b[2] == 0xFF)
        {
            if (key.b[1] == 0xFF)
            {
                if (Sce_flag_test(key.b[0] | 0x500))
                {
                    goto clear_1;
                }
            }
            else if (Sce_flag_test(key.b[0] | 0x500) && Sce_flag_test(key.b[1] | 0x500))
            {
                goto clear_2;
            }
        }
        else if (Sce_flag_test(key.b[0] | 0x500) && Sce_flag_test(key.b[1] | 0x500) &&
                 Sce_flag_test(key.b[2] | 0x500))
        {
            Sce_flag_off(key.b[2] | 0x500);
        clear_2:
            Sce_flag_off(key.b[1] | 0x500);
        clear_1:
            Sce_flag_off(key.b[0] | 0x500);
            found = 1;
            Sce_flag_on(D_801DBE90[i].flag + 0x2F4);
        }
        i++;
        *(uint32 *)&key = *(uint32 *)&D_801DBE90[i].key;
    }
    Sound_call(found ? 0x8A : 0x8B, 0, 0);
    return found;
}

void func_801DB5B8(void)
{
    switch (D_801DC208.routine_2)
    {
        case 0:
            Sce_flag_on(0x318);
            Sce_flag_on(0x319);
            Sce_flag_on(0x31A);
            Sce_flag_off(D_801DC138[Game_work.area_50.b.stage] + 0x318);
            MojiTaskExec(0, SUP_SCRIPT, 0x19);
            D_801DC208.anim_94 = 8;
            D_801DC208.routine_2++;
            break;
        case 1:
            if (Moji_flag >= 0)
            {
                Sce_flag_on(D_801DC138[Game_work.area_50.b.stage] + 0x318);
                D_801DC208.value_60 = (uint8)Moji_flag;
                if (D_801DC208.value_60 == 8)
                {
                    D_801DC208.routine_2 = 3;
                }
                else
                {
                    func_8003B140();
                    D_801DC208.routine_2++;
                }
            }
            break;
        case 2:
            switch (D_801DC208.value_60)
            {
                case 0:
                    if (Sce_flag_test(0x55))
                    {
                        Game_work.area_50.b.stage = 0x1B;
                    }
                    else
                    {
                        Game_work.area_50.b.stage = 3;
                    }
                    Game_work.area_50.b.room = 1;
                    break;
                case 1:
                    Game_work.area_50.b.stage = 5;
                    Game_work.area_50.b.room  = 0;
                    break;
                case 2:
                    Game_work.area_50.b.stage = 6;
                    Game_work.area_50.b.room  = 0;
                    break;
                case 3:
                    Game_work.area_50.b.stage = 8;
                    Game_work.area_50.b.room  = 0;
                    break;
                case 4:
                    Game_work.area_50.b.stage = 0xC;
                    Game_work.area_50.b.room  = 0;
                    break;
                case 5:
                    Game_work.area_50.b.stage = 0x19;
                    Game_work.area_50.b.room  = 3;
                    break;
                case 6:
                    Game_work.area_50.b.stage = 0x19;
                    Game_work.area_50.b.room  = 2;
                    break;
                case 7:
                    Game_work.area_50.b.stage = 0x12;
                    Game_work.area_50.b.room  = 0;
                    break;
            }
            Game_work.stage_79 = Game_work.area_50.b.stage;
            Game_work.room_7a  = Game_work.area_50.b.room;
            func_801DB800();
            break;
        case 3:
            *(uint32 *)&D_801DC208.routine_0 = 0x203;
            break;
    }
}

void func_801DB800(void)
{
    switch (D_801DC208.routine_3)
    {
        case 0:
            func_80017C30(0x17);
            Sound_fade_start(0x10);
            D_801DC208.routine_3++;
            break;
        case 1:
            func_80016D64();
            Sound_seq_stop_all();
            func_8001B314();
            D_80098958 |= 0x800;
            D_800C356E = Game_work.area_50.b.stage;
            D_800C356F = Game_work.area_50.b.room;
            Sound_stage_check();
            func_8001F23C();
            func_8001F3C8();
            func_801DBC5C(D_801DC138[Game_work.area_50.b.stage]);
            D_801DC208.value_08 = -1;
            break;
    }
}

void func_801DB8F8(void)
{
    switch (D_801DC208.routine_1)
    {
        case 0:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = SUP_OBJ_0->pos.vx;
            D_801DC208.value_48 = -0x96;
            D_801DC208.value_4c = SUP_OBJ_0->pos.vz;
            D_801DC208.value_54 = 0x100;
            D_801DC208.value_58 = -0x150;
            D_801DC208.value_5c = -0x20;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_1++;
            break;
        case 2:
            MojiTaskExec(0, SUP_SCRIPT, 0x8F);
            D_801DC208.routine_1++;
            break;
        case 3:
            if (Moji_flag >= 0)
            {
                switch (Moji_flag & 0xFF)
                {
                    case 1:
                        D_801DC208.routine_1 = 4;
                        break;
                    case 3:
                        D_801DC208.routine_1 = 9;
                        break;
                    default:
                        D_801DC208.routine_1 = 2;
                        break;
                }
            }
            break;
        case 4:
            func_801DBBE0();
            break;
        case 9:
            D_801DC208.vec_28   = D_801DC208.vec_0c;
            D_801DC208.value_38 = D_801DC208.value_1c;
            D_801DC208.value_3c = D_801DC208.value_20;
            D_801DC208.value_40 = D_801DC208.value_24;
            D_801DC208.value_44 = 0x40;
            D_801DC208.value_48 = -0x96;
            D_801DC208.value_4c = 0;
            D_801DC208.value_54 = 0x180;
            D_801DC208.value_58 = 0;
            D_801DC208.value_5c = 0x80;
            D_801DC208.value_0a = 0x10;
            D_801DC208.routine_1++;
            break;
        case 1:
        case 10:
            if (--D_801DC208.value_0a == 0)
            {
                D_801DC208.routine_1++;
            }
            func_801D8B68();
            break;
        case 11:
            *(uint32 *)&D_801DC208.routine_0 = 1;
            break;
    }
    func_801D8490();
}

void func_801DBBE0(void)
{
    switch (D_801DC208.routine_2)
    {
        case 0:
            D_801DC208.routine_2 += func_800665FC(1);
            break;
        case 1:
            MojiTaskKill();
            D_801DC208.routine_1 = 2;
            D_801DC208.routine_2 = 0;
            break;
    }
}

void func_801DBC5C(sint32 i)
{
    if (Game_work.area_50.h == 0xB13)
    {
        i = 9;
    }
    if (Game_work.area_50.h == 0x61B)
    {
        i = 9;
    }
    Player_work.pos.vx = Player_work.old_pos.vx = D_801DC0E8[i].vx;
    Player_work.fpos.vx = Player_work.old_fpos.vx = Player_work.pos.vx << 16;
    Player_work.pos.vy = Player_work.old_pos.vy = D_801DC0E8[i].vy;
    Player_work.fpos.vy = Player_work.old_fpos.vy = Player_work.pos.vy << 16;
    Player_work.pos.vz = Player_work.old_pos.vz = D_801DC0E8[i].vz;
    Player_work.fpos.vz = Player_work.old_fpos.vz = Player_work.pos.vz << 16;
    Player_work.rot.vx = Player_work.old_rot.vx = 0;
    Player_work.rot.vy = Player_work.old_rot.vy = D_801DC0E8[i].pad;
    Player_work.rot.vz = Player_work.old_rot.vz = 0;
    Player_work.value_74 = Player_work.value_75 = 0;
    Player_work.value_76 = Player_work.value_77 = 0;
}

void func_801DBD78(void)
{
    switch (D_801DC208.routine_1)
    {
        case 0:
            MojiTaskExec(0, SUP_SCRIPT, 0x1E);
            D_801DC208.routine_1++;
            break;
        case 1:
            if (Moji_flag >= 0)
            {
                D_801DC208.routine_1++;
            }
            break;
        case 2:
            D_801DC208.routine_1++;
            break;
        case 3:
            func_801DBC5C(8);
            Player_work.value_170 = Player_work.value_172 = 0xB;
            Player_work.value_171 = Player_work.value_173 = 1;
            Player_work.value_44e                         = 1;
            Player_work.value_44f                         = 1;
            func_8001F5E4();
            func_80037594();
            *(uint32 *)&D_801DC208.routine_0 = 2;
            break;
    }
    func_801D8490();
}
