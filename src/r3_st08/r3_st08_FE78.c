#include "common.h"
#include "st08.h"

#ifdef __wasm32__
void func_80031A4C(void *wp);
#endif

// A shadow under its owner (value_44), scaled by the owner's variant.
void func_8010FE78(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STAGE_OBJ *owner;

    if (((STAGE_OBJ *)wp->value_44)->flags_0 == 0)
    {
        func_80031A4C(wp);
        return;
    }
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 6;
            func_8002F9C4(wp, &wp->variant_3);
            wp->color_40 = 0x808080;
            wp->routine_0++;
            // fall through
        case 1:
            owner = (STAGE_OBJ *)wp->value_44;
            rot   = owner->rotation;
            rot.x = 0;
            rot.z = 0;
            RotMatrixYXZ(&rot, &wp->matrix.m);
            scale.x = 0x600;
            if (owner->variant_3 == 0)
            {
                scale.y = 0x200;
            }
            else
            {
                scale.y = 0x400;
            }
            scale.z = 0x600;
            ScaleMatrix(&wp->matrix.m, &scale);
            wp->pos_38   = owner->position;
            wp->pos_38.y = -1;
            break;
    }
}

// A fixed shadow (removed once the scene byte at +4 reaches 0xB).
void func_8010FFB0(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STCOM_MATRIX *m;

    if (STAGE_SCENE_BYTE(4) == 0xB)
    {
        func_80031A4C(wp);
        return;
    }
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 6;
        func_8002F9C4(wp, &wp->variant_3);
        m            = &wp->matrix.m;
        wp->color_40 = 0x808080;
        rot.x        = 0;
        rot.y        = 0;
        rot.z        = 0;
        RotMatrixYXZ(&rot, m);
        scale.x = 0x200;
        scale.y = 0x200;
        scale.z = 0x200;
        ScaleMatrix(m, &scale);
        wp->pos_38.y = -1;
        wp->pos_38.x = 0;
        wp->pos_38.z = 0x200;
        wp->routine_0++;
    }
}

void func_80110084(STAGE_FX *wp)
{
    D_80114224[wp->variant_3](wp);
}

// Puts the player at (x, y, z) facing `angle`.
void func_801100C0(sint16 x, sint16 y, sint16 z, sint16 angle)
{
    ST08_PL->routine_0   = 3;
    ST08_PL->routine_1   = 1;
    ST08_PL->pos_438.x   = x;
    ST08_PL->pos_438.y   = y;
    ST08_PL->pos_438.z   = z;
    ST08_PL->fixed_428.x = x << 16;
    ST08_PL->fixed_428.y = y << 16;
    ST08_PL->fixed_428.z = z << 16;
    ST08_PL->rot_440.x   = 0;
    ST08_PL->rot_440.y   = angle;
    ST08_PL->rot_440.z   = 0;
    ST08_PL->value_448   = 0;
    ST08_PL->flags_bd |= 0x10;
}

void func_80110150(STAGE_OBJ *wp)
{
    ST08_DROP_SET *set;
    ST08_DROP *drops;
    ST08_10C *ep;
    sint32 i;
    sint32 angle;

    set   = &D_80114374[ST08_GAME_WORD(0x150)];
    drops = set->drops;
    for (i = 0; i < set->count_4; i++, drops++)
    {
        ep = (ST08_10C *)func_80031518();
        if (ep != NULL)
        {
            ep->flags_0    = 1;
            ep->kind_2     = 0x26;
            ep->value_C    = drops->kind_4;
            ep->value_D    = drops->value_5;
            ep->value_E    = 0;
            ep->value_F    = wp->value_1;
            ep->position.x = drops->x;
            ep->position.z = drops->z;
            if (ep->value_C != 0)
            {
                ep->position.y = -(((rand() & 0xF) + 1) * 7 + 0x78);
                ep->speed_CC   = (rand() & 3) * 10 + 100;
            }
            else
            {
                ep->position.y = -(((rand() & 0xF) + 1) * 5 + 0x78);
                ep->speed_CC   = (rand() & 3) * 10 + 50;
            }
            angle            = rand() & 0xF00;
            ep->velocity.v.x = (uint32)(rsin(angle) * ep->speed_CC) >> 12;
            ep->velocity.v.z = (uint32)(rcos(angle) * ep->speed_CC) >> 12;
        }
    }
}

// Inserts `score` into a three-entry ranking (lowest first); returns its place, or 3.
uint8 func_80110314(ST08_RANK *tbl, uint32 score)
{
    sint32 i;
    sint32 j;
    sint32 k;

    for (i = 0; i < 3; i++)
    {
        if (tbl[i].score >= score)
        {
            if (i < 2)
            {
                for (j = 2; j > i; j--)
                {
                    tbl[j].score = tbl[j - 1].score;
                    for (k = 0; k < 4; k++)
                    {
                        tbl[j].value[k] = tbl[j - 1].value[k];
                    }
                }
            }
            tbl[i].score = score;
            return i;
        }
    }
    return 3;
}

void func_801103A8(STAGE_OBJ50 *wp)
{
    uint32 t;
    sint32 value;

    if (ST08_GAME_WORD(0x150) == 3)
    {
        t     = (D_8011422C[3].value_4 - ((uint32)wp->value_48 & ~3)) / 15;
        value = D_8011422C[3].value_0;
        value += t * t;
    }
    else
    {
        value = D_8011422C[ST08_GAME_WORD(0x150)].value_0;
    }
    func_8005C224(value);
}

// Whether the time is up or no slot of kind 0x26 is still running.
uint8 func_80110434(STAGE_OBJ50 *wp)
{
    ST08_SLOT10C *p;
    sint32 i;

    if ((uint32)wp->value_48 >= D_8011422C[ST08_GAME_WORD(0x150)].value_4)
    {
        return 1;
    }
    for (i = 0, p = D_8009CF88; i < 0x20; i++, p++)
    {
        if (p->flags_0 != 0 && p->kind_2 == 0x26 && p->value_C != 0)
        {
            return 0;
        }
    }
    return 1;
}

void func_801104C8(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_1;
    switch (temp_v1)
    {
        case 0:
            if (func_80042238((STCOM_PL_WORK *)&Player_work) != 0)
            {
                func_80110150(wp);
                func_8001D854(0x10);
                func_801100C0(0, -1, 0x300, 0);
                wp->routine_1++;
                return;
            }
            return;
        case 1:
            if ((D_80098A72 == 0) && (D_80098788 == 0))
            {
                Sound_call(0x21, 1, 0);
                MojiTaskExec2(0, 0xDU);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_801105AC(STAGE_OBJ50 *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001D854(0x10);
                MojiTaskExec2(0, ST08_GAME_WORD(0x150) + 0x16);
                wp->routine_1++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000) && D_80098788 == 0)
            {
                func_80042314(&Player_work);
                Sound_call2(0x16D, &Player_work.position);
                Sound_work.volume_6 = 0x50;
                func_8001D58C(0x2001000E);
                wp->value_48   = 0;
                wp->u_C.b.lo   = 0;
                MojiTaskExec2(2, 0x1A);
                MojiTaskExec2(3, ST08_GAME_WORD(0x150) + 0x28);
                wp->routine_1++;
            }
            break;
        case 2:
            if (func_80110434(wp))
            {
                wp->routine_1++;
            }
            else
            {
                wp->value_48++;
            }
            break;
        case 3:
            if (func_80042238(&Player_work))
            {
                Sound_call2(0x16D, &Player_work.position);
                func_8001D854(0x40);
                func_80053AA4(2);
                func_80053AA4(3);
                if ((uint32)wp->value_48 >= D_8011422C[ST08_GAME_WORD(0x150)].value_4)
                {
                    MojiTaskExec2(0, 0x20);
                }
                else
                {
                    MojiTaskExec2(0, 0x1F);
                }
                wp->routine_1++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x8000000) && D_80098788 == 0)
            {
                if ((uint32)wp->value_48 >= D_8011422C[ST08_GAME_WORD(0x150)].value_4)
                {
                    MojiTaskExec2(0, 0x10);
                    Sound_call(0x22, 1, 0);
                    D_80118598 = 0xFF;
                    wp->routine_1++;
                    break;
                }
                func_8001E3F0(7);
                if (!Sce_flag_test(0x315))
                {
                    if (ST08_GAME_WORD(0x150) == 3)
                    {
                        func_8005C218(0x5C);
                        MojiTaskExec2(0, 0x12);
                        Sce_flag_on(0x315);
                        Sound_call(0x23, 1, 0);
                        D_80118598 = 0xFF;
                    }
                    else
                    {
                        func_801103A8(wp);
                        MojiTaskExec2(0, 0x11);
                        Sound_call(0x23, 1, 0);
                        D_80118598 = 0xFF;
                    }
                }
                else
                {
                    D_80118598 = func_80110314((ST08_RANK *)&ST08_GAME_WORD(0x144), wp->value_48);
                    if (D_80118598 == 0)
                    {
                        func_801103A8(wp);
                        MojiTaskExec2(0, 0x13);
                        Sound_call(0x24, 1, 0);
                        Sound_call2(0x16E, &Player_work.position);
                    }
                    else
                    {
                        func_801103A8(wp);
                        MojiTaskExec2(0, 0x11);
                        Sound_call(0x23, 1, 0);
                    }
                }
                if ((uint32)ST08_GAME_WORD(0x150) < 3)
                {
                    ST08_GAME_WORD(0x150)++;
                }
                wp->routine_1++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x8000000))
            {
                if (D_80118598 < 3)
                {
                    func_8005C24C(D_80118598 + 0xC);
                    MojiTaskExec2(0, 0x24);
                }
                else
                {
                    MojiTaskExec2(0, 0x1D);
                }
                wp->routine_1++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x8000000) && !func_8001A0A8(0))
            {
                if (Moji_flag & 0xFF)
                {
                    wp->routine_0++;
                    wp->routine_1 = 0;
                }
                else
                {
                    func_80017C30(9);
                    wp->routine_1++;
                }
            }
            break;
        case 7:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x18, 0x80);
                wp->routine_1++;
            }
            break;
        case 8:
            func_80110150((STAGE_OBJ *)wp);
            func_801100C0(0, -1, 0x300, 0);
            func_80017C30(1);
            wp->routine_1++;
            break;
        case 9:
            if (D_80098A72 == 0)
            {
                wp->routine_1 = 0;
            }
            break;
    }
    func_8005C230(wp->value_48);
}

void func_80110A54(STAGE_OBJ50 *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskExec2(0, 0x15);
            wp->routine_1++;
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                D_800C356C = 1;
                D_800C356E = 8;
                D_800C356F = 2;
                D_800C3560 = -0xBE;
                D_800C3562 = -0x41;
                D_800C3564 = 0x296;
                D_800C356A = 0x800;
                D_800C356D = 0;
                D_800C3571 = 0xA;
                D_800C3570 = 2;
                wp->routine_1++;
            }
            break;
        case 2:
            if (D_800C356C == wp->routine_1)
            {
                D_800C356C++;
                func_80042314(&Player_work);
                Sound_work.volume_6 = 0x7F;
                func_80031A4C(wp);
            }
            break;
    }
}

void func_80110BA0(STAGE_WORK *wp)
{
    D_80114394[wp->routine_0](wp);
}

void func_80110BDC(STAGE_OBJ *wp)
{
    D_801143A0[wp->routine_0](wp);
    wp->value_48.value = 0;
}

void func_80110C28(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // never used; it reserves retail's frame

    wp->flags_0 |= 6;
    func_8002F9C4(wp, &wp->variant_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    RotMatrixY(wp->value_F << 10, &wp->matrix.m);
    wp->color_40 = 0x808080;
    wp->model_10 = D_801143A8;
    wp->value_48 = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void func_80110CC0(STAGE_OBJ50 *wp)
{
    func_80051B68(wp, 7, 0, 0);
    if (STCOM_PLAYER_WORK_PTR->target_184 == wp)
    {
        STCOM_PLAYER_WORK_PTR->target_184 = NULL;
    }
    func_800341BC(&wp->pos_38, 0x28, 0, 0x8000, wp->index_1, &wp->value_48, 0x4000000, 0, 0x80);
}
