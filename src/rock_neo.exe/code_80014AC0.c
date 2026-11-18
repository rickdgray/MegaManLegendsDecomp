#include "common.h"
#include "code_8002E7A8.h"
#include "code_80014AC0.h"
#include "code_800133D8.h"
#include "game.h"
#include "sound.h"

void func_80014AC0(WORK_3C0 *wp, SCRIPT_WORK *sp)
{
    wp->routine_0 |= 2;
    Model_work_init((MODEL_WORK *)wp, 0);
    *(uint32 *)&wp->vec_158.vx = 0x04000400;
    *(uint32 *)&wp->vec_158.vz = 0x42100400;
    wp->hit_78                 = &D_800979FC;
    // ang.vx and ang.vz are cleared again below by the word stores; the build needs both.
    wp->ang.vx             = 0;
    wp->ang.vz             = 0;
    wp->field_64           = 0;
    *(uint32 *)&wp->spd.vx = 0;
    *(uint32 *)&wp->spd.vz = 0;
    *(uint32 *)&wp->add.vx = 0;
    *(uint32 *)&wp->add.vz = 0;
    *(uint32 *)&wp->ang.vx = 0;
    *(uint32 *)&wp->ang.vz = 0;
    wp->field_10           = 0;
    sp->data               = D_800820E0[wp->field_C][wp->type_3];
    if (sp->data == NULL)
    {
        wp->routine_8 = 2;
        return;
    }
    sp->pos       = 0;
    sp->wait      = 0;
    sp->add_8     = 0;
    sp->direct_12 = 0;
    wp->idx_AC    = 0xFF;
    sp->field_13  = 0xFF;
    sp->add_A     = 0;
    sp->add_C     = 0;
    sp->add_E     = 0;
    wp->routine_8++;
    func_800150E0(wp, sp);
}

void script_exec(WORK_3C0 *wp, SCRIPT_WORK *sp)
{
    while (sp->data[sp->pos] != 0)
    {
        switch (sp->data[sp->pos])
        {
            case 1:
                wp->pos.vx   = sp->data[sp->pos + 1];
                wp->pos.vy   = sp->data[sp->pos + 2];
                wp->pos.vz   = sp->data[sp->pos + 3];
                wp->pos_l.vx = wp->pos.vx << 16;
                wp->pos_l.vy = wp->pos.vy << 16;
                wp->pos_l.vz = wp->pos.vz << 16;
                sp->pos += 4;
                break;
            case 2:
                wp->pos.vx   = sp->data[sp->pos + 1];
                wp->pos_l.vx = wp->pos.vx << 16;
                sp->pos += 2;
                break;
            case 3:
                wp->pos.vy   = sp->data[sp->pos + 1];
                wp->pos_l.vy = wp->pos.vy << 16;
                sp->pos += 2;
                break;
            case 4:
                wp->pos.vz   = sp->data[sp->pos + 1];
                wp->pos_l.vz = wp->pos.vz << 16;
                sp->pos += 2;
                break;
            case 5:
                wp->idx_AC = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 6:
                wp->spd.vx = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 7:
                wp->add.vx = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 8:
                wp->spd.vy = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 9:
                wp->add.vy = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 10:
                wp->spd.vz = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 11:
                wp->add.vz = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 12:
                wp->ang.vy = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 13:
                sp->add_8 = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 14:
                sp->field_13 = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 15:
                sp->direct_12 = 0;
                sp->pos += 1;
                break;
            case 16:
                sp->direct_12 = 1;
                sp->pos += 1;
                break;
            case 17:
                wp->slot_D  = 1;
                wp->field_E = sp->data[sp->pos + 1];
                wp->timer_F = 0;
                sp->pos += 2;
                break;
            case 18:
                wp->slot_D = 0;
                sp->pos += 1;
                break;
            case 19:
                wp->vec_158.vx = sp->data[sp->pos + 1];
                wp->vec_158.vy = sp->data[sp->pos + 2];
                wp->vec_158.vz = sp->data[sp->pos + 3];
                sp->pos += 4;
                break;
            case 20:
                wp->vec_158.vx = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 21:
                wp->vec_158.vy = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 22:
                wp->vec_158.vz = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 23:
                sp->add_A = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 24:
                sp->add_C = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 25:
                sp->add_E = sp->data[sp->pos + 1];
                sp->pos += 2;
                break;
            case 27:
                wp->routine_8 = 2;
                return;
            case 26:
                sp->pos = sp->data[sp->pos + 1];
                break;
        }
    }
    sp->wait = sp->data[sp->pos + 1] - 1;
    sp->pos += 2;
}

void func_800150E0(WORK_3C0 *wp, SCRIPT_WORK *sp)
{
    wp->old_idx_AD = wp->idx_AC;
    sp->field_14   = sp->field_13;
    wp->old        = wp->pos;
    wp->old_l      = wp->pos_l;
    wp->old_ang    = wp->ang;
    if (sp->wait == 0)
    {
        script_exec(wp, sp);
    }
    else
    {
        sp->wait--;
    }
    wp->spd.vx += wp->add.vx;
    wp->spd.vy += wp->add.vy;
    wp->spd.vz += wp->add.vz;
    if (sp->direct_12)
    {
        wp->pos_l.vx += wp->spd.vx << 12;
        wp->pos_l.vy += wp->spd.vy << 12;
        wp->pos_l.vz += wp->spd.vz << 12;
        wp->pos.vx = wp->pos_l.vx >> 16;
        wp->pos.vy = wp->pos_l.vy >> 16;
        wp->pos.vz = wp->pos_l.vz >> 16;
    }
    else
    {
        Obj_pos_set((MODEL_WORK *)wp, wp->spd.vx, wp->spd.vy, wp->spd.vz);
    }
    wp->ang.vy += sp->add_8;
    wp->vec_158.vx += sp->add_A;
    wp->vec_158.vy += sp->add_C;
    wp->vec_158.vz += sp->add_E;
    if (wp->slot_D)
    {
        switch (wp->field_E)
        {
            case 0:
                if (wp->timer_F == 0)
                {
                    Sound_call(0xD6, 0, 0);
                    wp->timer_F = 18;
                }
                else
                {
                    wp->timer_F--;
                }
                break;
            case 1:
                if (wp->timer_F == 0)
                {
                    Sound_call(0xD7, 0, 0);
                    wp->timer_F = 10;
                }
                else
                {
                    wp->timer_F--;
                }
                break;
            case 2:
                if (wp->timer_F == 0)
                {
                    Sound_call(0xD7, 0, 0);
                    wp->timer_F = 8;
                }
                else
                {
                    wp->timer_F--;
                }
                break;
            case 3:
                Sound_call(0xDA, 0, 0);
                wp->slot_D = 0;
                break;
            case 4:
                Sound_call(0xD9, 0, 0);
                wp->slot_D = 0;
                break;
        }
    }
    if (sp->field_13 != sp->field_14)
    {
        wp->field_110 = sp->field_13;
    }
    if (wp->old_idx_AD != wp->idx_AC)
    {
        func_800322A8((MODEL_WORK *)wp, wp->idx_AC, 0);
    }
    else
    {
        func_80032488((MODEL_WORK *)wp);
    }
}

void func_800153CC(WORK_3C0 *wp, SCRIPT_WORK *sp)
{
    func_80031824(wp);
}

void func_800153EC(WORK_3C0 *wp)
{
    D_80082104[wp->routine_8](wp, &wp->script);
}

void func_80015428(CODE_800133D8_WORK *wp)
{
    sint32 i;
    WORK_3C0 *op;

    switch (wp->routine_A)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                for (i = 0; i < 16; i++)
                {
                    op = func_80031418();
                    if (op != NULL)
                    {
                        op->routine_0           = 1;
                        op->type_3              = i;
                        op->id_2                = 0;
                        *(uint16 *)&op->flag_4  = 0;
                        *(uint32 *)&op->field_C = 0;
                        op->field_C             = wp->field_8;
                    }
                }
                wp->timer_6 = 300;
                wp->routine_A++;
            }
            break;
        case 1:
            if (wp->timer_6 == 0)
            {
                Obj_work_flag_change(2, WORK_KILL);
                if (++wp->field_8 >= 9)
                {
                    wp->field_8 = 0;
                }
                wp->routine_A++;
            }
            else
            {
                wp->timer_6--;
            }
            break;
        case 2:
            if (D_80098A72 == 0 && (wp->routine_0 == 4 || wp->routine_0 == 5 || wp->routine_0 == 6))
            {
                wp->routine_A = 0;
            }
            break;
    }
}
