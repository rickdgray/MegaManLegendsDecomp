#include "common.h"
#include "code_80014ac0.h"

void func_80014AC0(CODE14_WORK *wp, CODE14_SCRIPT *script)
{
    wp->flags |= 2;
    func_8002F9C4(wp, 0);
    *(uint32 *)&wp->scale.x        = 0x04000400;
    *(uint32 *)&wp->scale.z        = 0x42100400;
    wp->table78                    = D_800979FC;
    wp->rotation.x                 = 0;
    wp->rotation.z                 = 0;
    wp->value64                    = 0;
    *(uint32 *)&wp->velocity_x     = 0;
    *(uint32 *)&wp->velocity_z     = 0;
    *(uint32 *)&wp->acceleration_x = 0;
    *(uint32 *)&wp->acceleration_z = 0;
    *(uint32 *)&wp->rotation.x     = 0;
    *(uint32 *)&wp->rotation.z     = 0;
    wp->value10                    = 0;
    script->commands               = D_800820E0[wp->script_kind][wp->variant];
    if (script->commands == NULL)
    {
        wp->routine08 = 2;
    }
    else
    {
        script->index        = 0;
        script->timer        = 0;
        script->turn         = 0;
        script->fixed_motion = 0;
        wp->anim             = 255;
        script->frame        = 255;
        script->scale_x      = 0;
        script->scale_y      = 0;
        script->scale_z      = 0;
        wp->routine08++;
        func_800150E0(wp, script);
    }
}

void func_80014BCC(CODE14_WORK *wp, CODE14_SCRIPT *script)
{
    while (script->commands[script->index] != 0)
    {
        switch (script->commands[script->index])
        {
            case 1:
                wp->position.x             = script->commands[script->index + 1];
                wp->position.y             = script->commands[script->index + 2];
                wp->position.z             = script->commands[script->index + 3];
                wp->position_fixed.x.value = wp->position.x << 16;
                wp->position_fixed.y.value = wp->position.y << 16;
                wp->position_fixed.z.value = wp->position.z << 16;
                script->index += 4;
                break;
            case 2:
                wp->position.x             = script->commands[script->index + 1];
                wp->position_fixed.x.value = wp->position.x << 16;
                script->index += 2;
                break;
            case 3:
                wp->position.y             = script->commands[script->index + 1];
                wp->position_fixed.y.value = wp->position.y << 16;
                script->index += 2;
                break;
            case 4:
                wp->position.z             = script->commands[script->index + 1];
                wp->position_fixed.z.value = wp->position.z << 16;
                script->index += 2;
                break;
            case 5:
                wp->anim = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 6:
                wp->velocity_x = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 7:
                wp->acceleration_x = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 8:
                wp->velocity_y = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 9:
                wp->acceleration_y = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 10:
                wp->velocity_z = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 11:
                wp->acceleration_z = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 12:
                wp->rotation.y = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 13:
                script->turn = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 14:
                script->frame = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 15:
                script->fixed_motion = 0;
                script->index++;
                break;
            case 16:
                script->fixed_motion = 1;
                script->index++;
                break;
            case 17:
                wp->sound_enabled = 1;
                wp->sound_kind    = script->commands[script->index + 1];
                wp->sound_timer   = 0;
                script->index += 2;
                break;
            case 18:
                wp->sound_enabled = 0;
                script->index++;
                break;
            case 19:
                wp->scale.x = script->commands[script->index + 1];
                wp->scale.y = script->commands[script->index + 2];
                wp->scale.z = script->commands[script->index + 3];
                script->index += 4;
                break;
            case 20:
                wp->scale.x = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 21:
                wp->scale.y = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 22:
                wp->scale.z = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 23:
                script->scale_x = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 24:
                script->scale_y = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 25:
                script->scale_z = script->commands[script->index + 1];
                script->index += 2;
                break;
            case 27:
                wp->routine08 = 2;
                return;
            case 26:
                script->index = script->commands[script->index + 1];
                break;
        }
    }
    script->timer = script->commands[script->index + 1] - 1;
    script->index += 2;
}

void func_800150E0(CODE14_WORK *wp, CODE14_SCRIPT *script)
{
    uint16 z;

    wp->anim_prev           = wp->anim;
    script->frame_prev      = script->frame;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    if (script->timer == 0)
    {
        func_80014BCC(wp, script);
    }
    else
    {
        script->timer--;
    }
    wp->velocity_x += wp->acceleration_x;
    wp->velocity_y += wp->acceleration_y;
    z              = wp->velocity_z + wp->acceleration_z;
    wp->velocity_z = z;
    if (script->fixed_motion)
    {
        wp->position_fixed.x.value += (sint16)wp->velocity_x << 12;
        wp->position_fixed.y.value += (sint16)wp->velocity_y << 12;
        wp->position_fixed.z.value += (sint16)wp->velocity_z << 12;
        wp->position.x = (wp->position_fixed.x.value >> 16);
        wp->position.y = (wp->position_fixed.y.value >> 16);
        wp->position.z = (wp->position_fixed.z.value >> 16);
    }
    else
    {
        func_8002FEA4(wp, (sint16)wp->velocity_x, (sint16)wp->velocity_y, (sint16)z);
    }
    wp->rotation.y += script->turn;
    wp->scale.x += script->scale_x;
    wp->scale.y += script->scale_y;
    wp->scale.z += script->scale_z;
    if (wp->sound_enabled)
    {
        switch (wp->sound_kind)
        {
            case 0:
                if (wp->sound_timer == 0)
                {
                    Sound_call(0xD6, 0, 0);
                    wp->sound_timer = 18;
                }
                else
                {
                    wp->sound_timer--;
                }
                break;
            case 1:
                if (wp->sound_timer == 0)
                {
                    Sound_call(0xD7, 0, 0);
                    wp->sound_timer = 10;
                }
                else
                {
                    wp->sound_timer--;
                }
                break;
            case 2:
                if (wp->sound_timer == 0)
                {
                    Sound_call(0xD7, 0, 0);
                    wp->sound_timer = 8;
                }
                else
                {
                    wp->sound_timer--;
                }
                break;
            case 3:
                Sound_call(0xDA, 0, 0);
                wp->sound_enabled = 0;
                break;
            case 4:
                Sound_call(0xD9, 0, 0);
                wp->sound_enabled = 0;
                break;
        }
    }
    if (script->frame != script->frame_prev)
    {
        wp->frame = script->frame;
    }
    if (wp->anim_prev != wp->anim)
    {
        func_800322A8(wp, wp->anim, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_800153CC(GAME_WORK_3C0 *wp)
{
    func_80031824(wp);
}

void func_800153EC(CODE14_WORK *wp)
{
    D_80082104[wp->routine08](wp, &wp->script);
}

void func_80015428(CODE800133D8_STATE *wp)
{
    sint32 i;
    CODE14_WORK *entry;

    switch ((sint16)wp->value0a)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                for (i = 0; i < 16; i++)
                {
                    entry = func_80031418();
                    if (entry != NULL)
                    {
                        entry->flags                   = 1;
                        entry->variant                 = i;
                        entry->kind                    = 0;
                        entry->routine04               = 0;
                        *(uint32 *)&entry->script_kind = 0;
                        entry->script_kind             = wp->index08;
                    }
                }
                wp->timer06 = 300;
                wp->value0a++;
            }
            break;
        case 1:
            if (wp->timer06 == 0)
            {
                Obj_work_flag_change(2, 0x80);
                if (++wp->index08 >= 9)
                {
                    wp->index08 = 0;
                }
                wp->value0a++;
            }
            else
            {
                wp->timer06--;
            }
            break;
        case 2:
            if (D_80098A72 == 0 && ((uint32)(wp->routine_0 - 4) < 2 || (sint8)wp->routine_0 == 6))
            {
                wp->value0a = 0;
            }
            break;
    }
}
