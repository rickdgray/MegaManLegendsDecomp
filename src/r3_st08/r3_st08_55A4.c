#include "common.h"
#include "st08.h"

void func_801055A4(ST08_ACTOR *wp)
{
    ST08_HIT *hit;
    STAGE_OBJ50 *ep;

    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->position.z        = 0x328;
    wp->position.x        = (wp->variant_3 ^ 1) << 8;
    hit                   = &wp->hit;
    wp->turn_64           = 0;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->turn_64           = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->value_F           = 0;
    wp->hit.flags_0       = 0;
    wp->rotation.v.y      = 0x400;
    wp->hit.value_2       = 0x400;
    wp->hit.timer_4       = 0;
    if (wp->variant_3 == 0)
    {
        wp->scale.words[0] = 0x5000500;
        wp->scale.words[1] = 0x500;
        wp->position.y     = -0x64;
    }
    else
    {
        wp->scale.words[0] = 0x3000300;
        wp->scale.words[1] = 0x300;
        wp->position.y     = -0x96;
    }
    wp->position_prev    = wp->position;
    wp->scale.v.pad      = 0x4210;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    func_800322A8(wp, 0, 0);
    ep = (STAGE_OBJ50 *)func_80031734();
    if (ep != NULL)
    {
        ep->flags_0  = 1;
        ep->kind_2   = 0x1F;
        ep->value_44 = (sint32)wp;
    }
    hit->value_8 = 0;
    wp->routine_1++;
}

void func_80105718(ST08_ACTOR *wp)
{
    ST08_HIT *hit;
    STCOM_SVECTOR pos;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    hit                     = &wp->hit;
    if (ST08_SCENE.value_4 == 5)
    {
        switch (wp->value_F)
        {
            case 0:
                wp->position.x -= 10;
                if (wp->position.x < -0x100)
                {
                    wp->value_E = 0;
                    wp->value_F++;
                }
                break;
            case 1:
                wp->position.x = ((rcos(++wp->value_E * 0x80 + 0x400) * 40) >> 12) - 0x100;
                wp->position.z = ((rsin((wp->value_E + 8) * 0x80) * 40) >> 12) + 0x300;
                hit->value_2 -= 0x80;
                if (wp->value_E >= 0x10)
                {
                    hit->value_2   = 0xC00;
                    wp->position.z = 0x2D8;
                    wp->value_F++;
                }
                break;
            case 2:
                wp->position.x += 10;
                if (wp->position.x > 0x100)
                {
                    wp->value_E = 0;
                    wp->value_F++;
                }
                break;
            case 3:
                wp->position.x = ((rcos(++wp->value_E * 0x80 + 0xC00) * 40) >> 12) + 0x100;
                wp->position.z = ((rsin((wp->value_E + 0x18) * 0x80) * 40) >> 12) + 0x300;
                hit->value_2 -= 0x80;
                if (wp->value_E >= 0x10)
                {
                    hit->value_2   = 0x400;
                    wp->position.z = 0x328;
                    wp->value_F    = 0;
                }
                break;
        }
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.z = wp->position.z << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->rotation.v       = *(STCOM_SVECTOR *)hit; // the hit block starts with the rotation
        if (wp->value_D != 0)
        {
            if (--wp->value_D & 1)
            {
                wp->rotation.v.y = (sint16)(wp->rotation.v.y + 0x100) + (wp->variant_3 ^ 1) * 48;
            }
            else
            {
                wp->rotation.v.y = (sint16)(wp->rotation.v.y - 0x100) - (wp->variant_3 ^ 1) * 48;
            }
        }
        if (hit->value_8 & 0x8000000)
        {
            if (wp->variant_3 == 0)
            {
                Scene_work.value_A += ST08_SCENE.value_B + 1;
            }
            else if (Scene_work.value_A < 2)
            {
                Scene_work.value_A = 0;
            }
            else
            {
                Scene_work.value_A = (uint8)(Scene_work.value_A - 1) - ST08_SCENE.value_B;
            }
            wp->value_D = 0x10;
        }
    }
    else
    {
        wp->value_D    = 0;
        wp->rotation.v = *(STCOM_SVECTOR *)&wp->hit;
    }
    pos = wp->position;
    pos.y -= 0x28;
    func_800341BC(&pos, 0x4B, 0, 0x8000, wp->value_1, &hit->value_8, 0x4800000, 0, 0x80);
    hit->value_8 = 0;
    func_80032488(wp);
    Model_Shadow_Trans(wp, 0x50, 0x200, 0);
}

void func_80105B60(STAGE_OBJ *wp)
{
    D_80113AAC[wp->routine_1](wp);
}

// Registers the actor's hit box (30 units under its position) with the hit record at hit + 8.
void func_80105B9C(ST08_ACTOR *wp, ST08_HIT *hit)
{
    STCOM_SVECTOR pos;

    pos = wp->position;
    pos.y -= 0x1E;
    func_800341BC(&pos, 0x1E, 0, 0x8000, wp->value_1, &hit->value_8, 0xC800000, 0x800000, 0x80);
    hit->value_8 = 0;
}

void func_80105C2C(ST08_ACTOR *wp)
{
    wp->position.x        = 0x1F4;
    wp->position.y        = -1;
    wp->position.z        = -0xA0;
    wp->rotation.words[0] = 0;
    wp->rotation.v.y      = 0x400;
    wp->variant_3         = 0;
    wp->turn_64           = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->turn_64           = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->flags_0 |= 2;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->position_prev                                = wp->position;
    wp->rotation_prev                                = wp->rotation.v;
    wp->scale.words[1]                               = 0x200;
    wp->scale.words[0]                               = 0x2000200;
    wp->scale.v.pad                                  = 0x4210;
    Model_work_init(wp, &wp->variant_3);
    func_800322A8(wp, 0, 0);
    wp->hit.value_8 = 0;
    wp->routine_1++;
}

// Retail sets up the hit pointer (s2) before the position pointer (s0); GCC the other way round.
void func_80105D54(ST08_ACTOR *wp)
{
    ST08_HIT *hit;
    STAGE_10C *obj;
    sint32 angle;

    hit                     = &wp->hit;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    if (hit->value_8 & 0x20000000)
    {
        Sound_call2(0x160, &wp->position);
        STAGE_SCENE_WORD(0x10)++;
        obj = Open_SHL_WORK();
        if (obj != NULL)
        {
            obj->flags_0 = 1;
            obj->kind_2  = 0x21;
        }
        angle                 = Angle_xz_svector(&wp->position, &Player_work.position);
        STAGE_SCENE_BYTE(0xB) = 1;
        wp->velocity.v.x      = (uint32)(rsin(angle) * 25) >> 11;
        wp->velocity.v.y      = -0x10;
        wp->velocity.v.z      = (uint32)(rcos(angle) * 15) >> 9;
        wp->routine_1++;
    }
    else if (wp->position.x > 0)
    {
        wp->position.x -= 0x14;
    }
    else
    {
        wp->position.x = 0;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position.y << 16;
    func_80105B9C(wp, hit);
    func_80032488(wp);
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

// Retail computes &wp->hit early into a2 and the position into a1 (Sound_call2's argument); GCC swaps the two registers and adds a move.
void func_80105F1C(ST08_ACTOR *wp)
{
    ST08_HIT *hit;
    sint16 id;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    hit                     = &wp->hit;
    wp->position.x += wp->velocity.v.x;
    wp->position.y += wp->velocity.v.y;
    wp->position.z += wp->velocity.v.z;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    if (wp->position.z >= 0x400 || (wp->hit.value_8 & 0x4000000))
    {
        id = 0x161;
        if (wp->hit.value_8 & 0x4000000)
        {
            id = 0x162;
        }
        // One-pass block preserves retail's register allocation and scheduling.
        do
        {
            do
            {
                Sound_call2(id, &wp->position);
            } while (0);
        } while (0);
        if (wp->velocity.v.x < 0)
        {
            wp->velocity.v.x = -0x50;
        }
        else
        {
            wp->velocity.v.x = 0x50;
        }
        wp->velocity.v.z = 0;
        wp->velocity.v.y = -0x3C;
        wp->routine_1++;
    }
    else
    {
        func_80105B9C(wp, hit);
    }
    wp->rotation.v.z += 0x400;
    func_80032538(wp);
    func_80033A28(wp);
    ST08_SP_ROT_Z = wp->rotation.v.z;
    func_8003346C(wp);
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_801060C0(ST08_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    wp->position.x += wp->velocity.v.x;
    wp->position.y += wp->velocity.v.y;
    wp->position.z += wp->velocity.v.z;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    if (wp->position.y < -0x257)
    {
        func_80031824(wp);
        return;
    }
    if (wp->velocity.v.x > 0)
    {
        wp->rotation.v.x += 0x400;
    }
    else
    {
        wp->rotation.v.x -= 0x400;
    }
    func_80032538(wp);
    func_80033A28(wp);
    ST08_SP_ROT_X = wp->rotation.v.x;
    func_8003346C(wp);
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_80106218(STAGE_OBJ *wp)
{
    D_80113AB4[wp->routine_1](wp);
}

void func_80106254(ST08_ACTOR *wp)
{
    ST08_HIT *hit;
    STAGE_OBJ50 *ep;

    wp->variant_3 = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->turn_64           = 0;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->turn_64           = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    hit                   = &wp->hit;
    if (rand() & 1)
    {
        wp->position.x   = 0x2BC;
        wp->velocity.v.x = -0x1E;
        wp->rotation.v.y = 0x400;
    }
    else
    {
        wp->position.x   = -0x2BC;
        wp->velocity.v.x = 0x1E;
        wp->rotation.v.y = 0xC00;
    }
    wp->position.y       = -1;
    wp->position.z       = 0x258;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    hit->flags_0                                     = 0;
    hit->value_2                                     = wp->rotation.v.y;
    hit->timer_4                                     = 0;
    wp->scale.words[1]                               = 0x500;
    wp->scale.words[0]                               = 0x5000500;
    wp->position.y                                   = -0x64;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->position_prev                                = wp->position;
    wp->rotation_prev                                = wp->rotation.v;
    wp->scale.v.pad                                  = 0x4210;
    func_800322A8(wp, 0, 0);
    ep = (STAGE_OBJ50 *)func_80031734();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0x1F;
        ep->value_44  = (sint32)wp;
        ep->variant_3 = 0;
    }
    hit->value_8 = 0;
    wp->routine_1++;
}

void func_80106428(ST08_ACTOR *wp)
{
    ST08_HIT *hit;
    STCOM_SVECTOR pos;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    hit                     = &wp->hit;
    if (ST08_SCENE.value_4 == 5)
    {
        if (ST08_SCENE.flags_C & 4)
        {
            wp->scale.v.pad = 0x4210;
        }
        else
        {
            wp->scale.v.pad = 0x7FFF;
        }
        wp->position.x += wp->velocity.v.x;
        if (wp->velocity.v.x < 0)
        {
            if (wp->position.x < -0x2BB)
            {
                func_80031824(wp);
                return;
            }
        }
        else if (wp->position.x >= 0x2BC)
        {
            func_80031824(wp);
            return;
        }
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.z = wp->position.z << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->rotation.v       = *(STCOM_SVECTOR *)hit; // the hit block starts with the rotation
        if (wp->value_D != 0)
        {
            if (--wp->value_D & 1)
            {
                wp->rotation.v.y = (sint16)(wp->rotation.v.y + 0x100) + (wp->variant_3 ^ 1) * 48;
            }
            else
            {
                wp->rotation.v.y = (sint16)(wp->rotation.v.y - 0x100) - (wp->variant_3 ^ 1) * 48;
            }
        }
        if (hit->value_8 & 0x8000000)
        {
            Scene_work.value_A += ST08_SCENE.value_B + 2;
            wp->value_D = 0x10;
        }
    }
    else
    {
        wp->value_D    = 0;
        wp->rotation.v = *(STCOM_SVECTOR *)&wp->hit;
    }
    pos = wp->position;
    pos.y -= 0x14;
    func_800341BC(&pos, 0x4B, 0, 0x8000, wp->value_1, &hit->value_8, 0x4800000, 0, 0x80);
    hit->value_8 = 0;
    func_80032488(wp);
    Model_Shadow_Trans(wp, 0x50, 0x200, 0);
}

void func_801066D8(STAGE_OBJ *wp)
{
    D_80113AC4[wp->routine_1](wp);
}

void func_80106714(STAGE_OBJ *wp)
{
    if (STAGE_SCENE_BYTE(4) == 0xB)
    {
        func_80031824(wp);
    }
    else
    {
        D_80113ACC[wp->routine_0](wp);
    }
}
