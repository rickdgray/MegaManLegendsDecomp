#include "common.h"
#include "st05.h"

void func_8012BD2C(STAGE_OBJ50 *wp)
{
    uint8 next;
    uint8 *row;
    sint32 choice;
    sint32 msg;
    sint32 msg2;

    switch (wp->routine_2)
    {
        case 0:
            MojiTaskExec2(0, D_801378BC[wp->value_E * 5]);
            wp->routine_2++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                choice = Moji_flag & 0xFF;
                row    = &D_801378BD[wp->value_E * 5];
                next   = row[choice];
                if (next == 0xFF)
                {
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                    wp->routine_0++;
                    break;
                }
                wp->value_F = next;
                Fade_start(9);
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x18, 0x80);
                func_8012B680(wp);
                wp->routine_2++;
            }
            break;
        case 3:
            Fade_start(1);
            func_8012B544(wp);
            wp->u_C.b.lo = 0;
            wp->value_48 = 0;
            wp->u_C.b.hi = 0;
            wp->routine_2++;
            break;
        case 4:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                msg = Game_work_90[wp->value_F].kind_0 + 0x4E;
                MojiTaskExec2(0, wp->value_F * 4 + msg);
                Sound_fade_start(0x10);
                wp->routine_2++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000) && Sound_fade_flags == 0)
            {
                func_80042314(&Player_work);
                MojiTaskExec2(2, 0x39);
                msg2 = Game_work_90[wp->value_F].kind_0 + 0x64;
                MojiTaskExec2(3, wp->value_F * 4 + msg2);
                Cd_xa_play_id(0x2001000D);
                wp->routine_2 = 0;
                wp->routine_1++;
            }
            break;
    }
}

void func_8012BF74(ST05_RACE *wp)
{
    if (wp->value_D == 0)
    {
        wp->time_48++;
    }
    else
    {
        if ((sint8)(wp->value_D % 7) == 0)
        {
            Sound_call2(0x169, &Player_work.position);
        }
        wp->value_D--;
    }
    switch (func_8012B788(wp) & 0xFF)
    {
        case 1:
            wp->routine_2 = 0;
            wp->routine_1++;
            break;
        case 2:
            Sound_call2(0x16A, &Player_work.position);
            D_80138018 = func_8012BA14((STAGE_OBJ50 *)wp);
            wp->routine_1++;
            if (D_80138018 != 0)
            {
                if (Game_work_90[wp->value_F].kind_0 == 3 && Sce_flag_test(wp->value_F + 0x201) == 0)
                {
                    wp->routine_2 = 3;
                }
                else
                {
                    wp->routine_2 = 2;
                }
            }
            else
            {
                if (Game_work_90[wp->value_F].kind_0 == 3 && Sce_flag_test(wp->value_F + 0x201) == 0)
                {
                    wp->routine_2 = 5;
                }
                else
                {
                    wp->routine_2 = 4;
                }
            }
            break;
        case 3:
            Sound_call2(0x167, &Player_work.position);
            // fall through
        case 0:
            if (wp->time_48 >= D_801379EC[wp->value_F].limit_0[Game_work_90[wp->value_F].kind_0])
            {
                wp->routine_2 = 1;
                wp->routine_1++;
            }
            break;
    }
    if (wp->routine_1 == 2)
    {
        func_80053AA4(2);
        func_80053AA4(3);
        Sound_fade_start(0x40);
    }
}

void func_8012C1F4(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_3;
    switch (temp_v1)
    {
        case 0:
            if (func_80042238((STCOM_PL_WORK *)&Player_work) != 0)
            {
                MojiTaskExec2(0, 0x32);
                wp->routine_3++;
                return;
            }
            return;
        case 1:
            if (!(Moji_flag & 0x08000000) && (Sound_seq_is_eos(0) == 0))
            {
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C29C(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_3;
    switch (temp_v1)
    {
        case 0:
            if (func_80042238((STCOM_PL_WORK *)&Player_work) != 0)
            {
                MojiTaskExec2(0, 0x34);
                wp->routine_3++;
                return;
            }
            return;
        case 1:
            if (!(Moji_flag & 0x08000000) && (Sound_seq_is_eos(0) == 0))
            {
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C344(STAGE_OBJ50 *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_8012B948(wp);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x35);
                if (Game_work_90[wp->value_F].kind_0 < 3)
                {
                    Game_work_90[wp->value_F].kind_0++;
                }
                wp->routine_3++;
            }
            break;
        case 1:
            if (D_80138018 < 3)
            {
                if (!(Moji_flag & 0x08000000))
                {
                    func_8005C24C(wp->value_F * 3 + D_80138018);
                    MojiTaskExec2(0, 2);
                    wp->routine_3++;
                }
            }
            else
            {
                wp->routine_3 = 3;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->value_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                func_8012B8FC((STAGE_OBJ *)wp);
            }
            break;
    }
}

void func_8012C4F4(STAGE_OBJ *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                Sce_flag_on(wp->u_E.b.byte_F + 0x201);
                func_8005C218(D_801379F8[wp->u_E.b.byte_F].value_14[0]);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x36);
                wp->routine_3++;
            }
            break;
        case 1:
            if (D_80138018 < 3)
            {
                if (!(Moji_flag & 0x08000000))
                {
                    func_8005C24C(wp->u_E.b.byte_F * 3 + D_80138018);
                    MojiTaskExec2(0, 2);
                    wp->routine_3++;
                }
            }
            else
            {
                wp->routine_3 = 3;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->u_E.b.byte_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                Sce_flag_on(wp->u_E.b.byte_F + 0x201);
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C6A0(STAGE_OBJ50 *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_8012B948(wp);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x37);
                if (Game_work_90[wp->value_F].kind_0 < 3)
                {
                    Game_work_90[wp->value_F].kind_0++;
                }
                wp->routine_3++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                func_8005C24C(wp->value_F * 3 + D_80138018);
                MojiTaskExec2(0, 2);
                wp->routine_3++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->value_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                func_8012B8FC((STAGE_OBJ *)wp);
            }
            break;
    }
}

void func_8012C830(STAGE_OBJ *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                Sce_flag_on(wp->u_E.b.byte_F + 0x201);
                func_8005C218(D_801379F8[wp->u_E.b.byte_F].value_14[0]);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x4D);
                wp->routine_3++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                func_8005C24C(wp->u_E.b.byte_F * 3 + D_80138018);
                MojiTaskExec2(0, 2);
                wp->routine_3++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->u_E.b.byte_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C9B0(STAGE_OBJ *wp)
{
    D_80137A80[wp->routine_2](wp);
}

void func_8012C9EC(STAGE_OBJ *wp)
{
    D_80137A98[wp->routine_1](wp);
    func_8005C230(wp->value_48.value);
}

void func_8012CA40(STAGE_OBJ50 *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskExec2(0, 0x38);
            wp->routine_1++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                D_800C356C = 1;
                D_800C356E = 8;
                D_800C356F = 2;
                D_800C3560 = 0x35F;
                D_800C3562 = -0x41;
                D_800C3564 = 0x160;
                D_800C356A = 0xC00;
                D_800C356D = 0;
                D_800C3571 = 0xA;
                D_800C3570 = 2;
                wp->routine_1++;
            }
            break;
        case 2:
            if (D_800C356C == 2)
            {
                D_800C356C++;
                Sound_work.volume_6 = 0x7F;
                Sce_flag_off(0x7E0);
                Sce_flag_off(0x200);
                STAGE_GAME.value_78 = 1;
                func_80042314(&Player_work);
                func_80031A4C(wp);
            }
            break;
    }
}

void func_8012CBA8(STAGE_OBJ *wp)
{
    D_80137AA4[wp->routine_0](wp);
    wp->position = STAGE_PL_OBJ->position_prev;
}
