#include "common.h"
#include "st13.h"

void func_801002E8(void)
{
    STAGE_TABLE_3C0 = D_8011607C;
    STAGE_TABLE_5A4 = D_8011621C;
    STAGE_TABLE_10C = D_80116264;
    STAGE_TABLE_48  = D_801162B4;
    STAGE_TABLE_24  = D_80116304;
    STAGE_TABLE_50  = D_8011638C;
}

void func_80100350(void)
{
    sint16 *cells;
    void *spawn;

    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    if (Game_work.value_51 < 10)
    {
        STAGE_PL_BYTE(0x44E) = 1;
    }
    else
    {
        STAGE_PL_BYTE(0x44E) = 0;
        Sce_flag_off(0x642);
    }
    spawn                     = D_80116AF0[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_80116F78[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_801171E0[D_80117220[Game_work.value_51]], D_80116FB0[Game_work.value_51]);
    func_8005DC10(D_80115C64[Game_work.value_51]);
    func_801004D8();
}

void func_801004D8(void)
{
    func_8001E4C4(D_80117490, D_80117498[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_8010051C(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80117354[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_80117314[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_801005BC(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            ST13_GAME_HALF(0x194) = 0;
            if (!Sce_flag_test(0x642))
            {
                ST13_GAME_HALF(0x196) = 0;
                ST13_GAME_HALF(0x198) = 0;
                ST13_GAME_HALF(0x19A) = 0;
                Sce_flag_on(0x642);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x7B0))
            {
                func_8001DDE4(0);
            }
            break;
    }
}

void func_80100664(STAGE_OBJ *wp)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
        return;
    }
    if ((wp->value_4 == 0) && (Sce_flag_test(0x4C) == 0))
    {
        func_8001E460(3, 1, 0);
        wp->value_4 = 0xFF;
    }
}

void func_801006DC(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            if (!Sce_flag_test(0x21))
            {
                func_8001E460(2, 1, 0);
                wp->routine_4++;
            }
            else
            {
                wp->routine_4 = 0xFF;
            }
            break;
        case 1:
            if (Sce_flag_test(0x4C))
            {
                func_8001E460(2, 0, 0);
                wp->routine_4++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x44))
            {
                func_8001DDE4(0x38);
                wp->routine_4++;
            }
            break;
    }
}

void func_801007D0(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100800(void)
{
}

void func_80100808(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_80117294);
        wp->routine_4 = 0xFF;
    }
}

void func_80100854(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8011729C);
        func_80100988();
        wp->value_4 = 0xFF;
    }
}

sint32 func_801008A8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0 && Sce_flag_test(0x238))
    {
        if (Sce_flag_test(0x239))
        {
            func_801009C8();
        }
        else
        {
            Sce_flag_on(0x239);
            func_8001EB98(D_8011738C);
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100920(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x239) != 0))
    {
        func_801009C8();
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100968(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80100988(void)
{
    sint32 var_s0;

    var_s0 = 0x621;
    do
    {
        Sce_flag_off(var_s0 & 0xFFFF);
        var_s0++;
    } while ((uint32)(var_s0 & 0xFFFF) < 0x63BU);
}

void func_801009C8(void)
{
    uint8 state;
    uint8 *count;
    uint8 base;
    uint8 i;
    state = (Sce_flag_test(0x23B) << 1) | Sce_flag_test(0x23A);
    switch (state)
    {
        case 0:
            if (STAGE_GAME_COUNT_62 >= 11)
            {
                Sce_flag_on(0x23A);
                Sce_flag_off(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
        case 1:
            if (STAGE_GAME_COUNT_62 >= 21)
            {
                Sce_flag_off(0x23A);
                Sce_flag_on(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
        case 2:
            if (STAGE_GAME_COUNT_62 >= 31)
            {
                Sce_flag_on(0x23A);
                Sce_flag_on(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
    }
    if (Game_work.value_51 == 0xD)
    {
        count = &D_801174FC[state];
        base  = 9;
    }
    else
    {
        count = &D_801174F8[state];
        base  = 1;
    }
    for (i = 0; i < *count; i++)
    {
        func_8001EB98(&D_8011738C[base + i]);
    }
}

void func_80100B70(STAGE_OBJ *wp)
{
    D_80117500[wp->routine_0](wp);
}

void func_80100BAC(ST13_STCOM27_WORK *wp)
{
    wp->scale.v.x   = 0x200;
    wp->scale.v.y   = 0x200;
    wp->scale.v.z   = 0x200;
    wp->scale.v.pad = 0x4210;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->velocity.z  = 0;
    wp->velocity.y  = 0;
    wp->velocity.x  = 0;
    wp->accel.z     = 0;
    wp->accel.y     = 0;
    wp->accel.x     = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    func_80036478(wp->ctl.track_0, 7, -0x60);
    wp->data_78 = D_8011750C;
    wp->life_6E = wp->life_max_B0 = D_8009884C[wp->kind_2]->life_8 << 4;
    wp->damage_B2                 = 0;
    wp->jump_74                   = 0;
    wp->ctl.sees_10               = 0;
    wp->ctl.flags_14              = 0;
    wp->ctl.hit_20                = 0;
    wp->ctl.value_24              = 0;
    wp->ctl.kind_30               = 0;
    func_800322A8(wp, 3, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80100CA0(ST13_STCOM27_WORK *wp)
{
    ST13_STCOM27_CTL *ctl;

    ctl                     = &wp->ctl;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->jump_prev_75        = wp->jump_74;
    func_80100DDC(wp);
    if (wp->value_C == 0)
    {
        ctl->sees_10 = 1;
    }
    else
    {
        ctl->sees_10 = func_8003648C(ctl->track_0, wp);
    }
    D_80117518[wp->routine_1](wp);
    if (wp->routine_0 != 2)
    {
        func_8010103C(wp);
        func_80100FA4(wp);
        if (wp->flags_0 & 2)
        {
            Model_Shadow_Trans(wp, 0x118, 0x200, 0);
        }
    }
}

void func_80100DDC(ST13_STCOM27_WORK *wp)
{
    ST13_STCOM27_CTL *ctl;
    sint32 damage;
    sint32 knock;
    sint32 dir;

    ctl = &wp->ctl;
    if (wp->value_D != 0)
    {
        if (!(STAGE_FRAME & 3) && wp->damage_B2 != 0)
        {
            wp->damage_B2--;
        }
        damage = ctl->hit_20 & 0xFFFFFF;
        if (damage != 0)
        {
            knock = 0;
            if (wp->routine_1 == 6)
            {
                Sound_call2(0xA3, &wp->position);
                return;
            }
            wp->life_6E -= damage;
            wp->damage_B2 += damage;
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
            if (wp->life_6E <= 0)
            {
                wp->life_6E = 0;
                knock       = 1;
            }
            else if (wp->damage_B2 >= D_8009884C[wp->kind_2]->value_9 * 16)
            {
                knock = 1;
            }
            if (knock)
            {
                func_800322A8(wp, 0xB, 0);
                wp->damage_B2 = 0;
                ctl->kind_30  = 0;
                dir           = func_80031F84(&wp->position, &ctl->from_28, wp->rotation.y, 0);
                if (dir & 0xFFFF0000)
                {
                    wp->rotation.y = dir;
                }
                else
                {
                    wp->rotation.y = (dir + 0x800) & 0xFFF;
                }
                wp->velocity.x = -0x400;
                wp->velocity.y = -0x100;
                wp->accel.y    = 0x40;
                wp->jump_74    = 1;
                Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
                wp->routine_1 = 6;
                wp->routine_2 = 0;
                wp->velocity.y += wp->accel.y;
            }
        }
    }
}

void func_80100FA4(ST13_STCOM27_WORK *wp)
{
    if (wp->value_D != 0)
    {
        wp->ctl.hit_20 = 0;
        wp->ctl.pos_18 = wp->position;
        wp->ctl.pos_18.y -= 0x80;
        func_800341BC(&wp->ctl.pos_18, 0x80, 0, 0x8000, wp->index_1, &wp->ctl.hit_20, wp->ctl.kind_30 | 0x4080000, 0x800000, 0);
    }
}

void func_8010103C(ST13_STCOM27_WORK *wp)
{
    ST13_STCOM27_CTL *ctl;
    sint32 ground;
    wp->ctl.flags_14 = 0;
    ctl              = &wp->ctl;
    if (Obj_map_push_out(wp) & 0xF00)
    {
        wp->ctl.flags_14 |= 1;
    }
    if (wp->jump_74 == 0)
    {
        ground = Obj_ceiling_height_get(wp);
        if (ground != wp->position_prev.y)
        {
            if (wp->jump_prev_75 == 0)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->ctl.flags_14 |= 4;
            }
        }
        else
        {
            wp->position.y            = ground;
            wp->position_fixed_prev.y = ground << 16; // retail stores the saved copy here
        }
        ctl->flags_14 |= 2;
    }
}

void func_80101134(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80101174(wp);
        return;
    }
    func_801011FC(wp);
}

void func_80101174(ST13_VIEW *wp)
{
    sint32 change;

    change = 0;
    if (wp->u_C.b[1] != 0)
    {
        change = wp->value_4F0 != 0;
    }
    if (wp->value_6E != wp->value_B0)
    {
        change = 1;
    }
    if (change)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801011FC(ST13_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_80101BD8(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010123C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_8010127C(wp);
        return;
    }
    func_801012E8(wp);
}

void func_8010127C(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
}

void func_801012E8(ST13_STCOM27_WORK *wp)
{
    STCOM_PL_WORK *pl;
    ST13_STCOM27_CTL *ctl;
    sint32 seen;
    sint16 turn;

    pl             = &Player_work;
    ctl            = &wp->ctl;
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x20)) & 0xFFF;
    seen           = func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, pl->rotation.y, 0x800);
    if (wp->flags_6 & 0x80)
    {
        if (ctl->count_38 < 30)
        {
            ctl->count_38++;
        }
    }
    else
    {
        ctl->count_38 = 0;
    }
    if (ctl->timer_36 != 0)
    {
        ctl->timer_36--;
    }
    else if (ctl->count_38 >= 30 && wp->dist_80 <= 0x9C400 && seen)
    {
        if ((rand() & 0xF) < 7)
        {
            func_80101C4C((STAGE_OBJ *)wp);
        }
        else
        {
            func_80101C94((ST13_VIEW *)wp);
        }
        return;
    }
    if (--ctl->timer_34 == 0)
    {
        if (ctl->sees_10 == 0)
        {
            func_80101BF8((ST13_OBJ *)wp);
            Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
            return;
        }
        ctl->timer_34 = 0x3C;
    }
    turn = wp->rotation.y - wp->rotation_prev.y;
    if (turn < 0)
    {
        turn = -turn;
    }
    if (turn <= 0x10)
    {
        func_80101B28((STAGE_OBJ *)wp, 2);
    }
    else if (wp->rotation.y > wp->rotation_prev.y)
    {
        func_80101B28((STAGE_OBJ *)wp, 7);
    }
    else
    {
        func_80101B28((STAGE_OBJ *)wp, 8);
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    if (wp->value_A4 == 2)
    {
        Sound_call2(0x1B8, &wp->position);
    }
}

void func_8010150C(STAGE_OBJ *wp)
{
    sint32 step;
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x40)) & 0xFFF;
    if (wp->u_4E0.face16.eyes_10 != NULL && (wp->flags_6 & 0x80))
    {
        if (rand() & 1)
        {
            func_80101C4C(wp);
            return;
        }
        func_80101BD8((ST13_OBJ *)wp);
        Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
        return;
    }
    func_80032488(wp);
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
    step = wp->value_A4 == 5;
    if (wp->value_A4 == 0x13)
    {
        step = 1;
    }
    if (step)
    {
        Sound_call2(0x1B7, &wp->position);
    }
}

void func_8010160C(void)
{
}

#ifdef __wasm32__
void func_80101704(ST13_ACTOR *wp);
#endif

void func_80101614(ST13_ACTOR *wp)
{
    STAGE_10C *obj;
    switch (wp->routine_2)
    {
        case 0:
            func_80101704(wp);
            break;
        case 1:
            obj = Open_SHL_WORK();
            if (obj != NULL)
            {
                obj->flags_0            = 1;
                obj->kind_2             = 5;
                obj->variant_3          = 0;
                obj->value_F            = wp->value_1;
                obj->position           = wp->value_188;
                obj->position_fixed.v.x = obj->position.x << 16;
                obj->position_fixed.v.y = obj->position.y << 16;
                obj->position_fixed.v.z = obj->position.z << 16;
            }
            Sound_call2(0x1BA, &wp->position);
            wp->routine_2++;
            break;
        case 2:
        default:
            func_801017DC((ST13_OBJ *)wp);
            break;
    }
}

void func_80101704(ST13_ACTOR *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
        return;
    }
    if (wp->value_A4 == 3)
    {
        wp->velocity.v.x = -0x600;
    }
    if (wp->value_A4 == 9)
    {
        wp->velocity.v.x = -0x400;
    }
    if (wp->value_A4 == 0xB)
    {
        wp->velocity.v.x = 0;
    }
    func_80032488(wp);
    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
}

void func_801017DC(ST13_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_80101BD8(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010181C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_8010185C(wp);
        return;
    }
    func_801018E4(wp);
}

void func_8010185C(ST13_VIEW *wp)
{
    if (wp->u_A4.b[3] != 0)
    {
        func_800322A8(wp, 0xA, 0);
        wp->value_510 = 0;
        if (rand() & 1)
        {
            wp->u_518.h[1] = 0x20;
        }
        else
        {
            wp->u_518.h[1] = -0x20;
        }
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
        Obj_pos_set(wp, wp->value_44, wp->value_46, wp->value_48);
    }
}

void func_801018E4(ST13_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_80101B84(wp);
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + wp->value_51A) & 0xFFF;
        func_80032488(wp);
    }
}

void func_80101938(STAGE_OBJ *wp)
{
    D_80117534[wp->routine_2](wp);
}

void func_80101974(ST13_STCOM27_WORK *wp)
{
    STCOM_EFFECT *effect;
    if (wp->jump_74 == 0)
    {
        Sound_call2(0x1BC, &wp->position);
        if (wp->life_6E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0;
                effect->sprite.position = wp->position;
            }
#ifdef __wasm32__
            func_80047148(wp, &wp->position);
#else
            func_80047148(wp, &wp->position, effect);
#endif
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
        }
        else
        {
            func_800322A8(wp, 0xC, 0);
            wp->routine_2++;
        }
    }
    else
    {
        wp->jump_74 = 1;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        wp->velocity.y += wp->accel.y;
        func_80032488(wp);
    }
}

void func_80101A84(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 0xDU, 0);
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
}

void func_80101ADC(ST13_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        wp->rotation.y -= 0x400;
        func_80101BD8(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80101B28(STAGE_OBJ *wp, sint32 anim)
{
    if (wp->anim_prev_AD != anim)
    {
        func_800322A8(wp, anim, wp->value_A4);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80101B84(ST13_OBJ *wp)
{
    func_800322A8(wp, 0xF, 0);
    wp->value_514        = 0x3C;
    wp->value_44.half[0] = 0x200;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    wp->routine_1        = 1;
    wp->routine_2        = 0;
}

void func_80101BD8(ST13_OBJ *wp)
{
    wp->value_516 = 0;
    func_80101B84(wp);
}

void func_80101BF8(ST13_OBJ *wp)
{
    func_800322A8(wp, 1, 0);
    wp->value_514        = 0x78;
    wp->value_44.half[0] = 0x100;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    wp->routine_1        = 2;
    wp->routine_2        = 0;
}

void func_80101C4C(STAGE_OBJ *wp)
{
    func_800322A8(wp, 6, 0);
    wp->value_44.words.fraction = 0;
    wp->value_44.words.integer  = 0;
    wp->value_4C.words.integer  = 0;
    wp->routine_1               = 4;
    wp->routine_2               = 0;
}

void func_80101C94(ST13_VIEW *wp)
{
    func_800322A8(wp, 9, 0);
    wp->value_510  = D_8009884C[wp->kind_2]->value_A | 0x1000000;
    wp->u_514.h[1] = 0x3C;
    wp->value_44   = 0x400;
    wp->value_46   = 0;
    wp->value_4E   = 0;
    Sound_call2(0x1B9, &wp->position);
    wp->routine_1 = 5;
    wp->routine_2 = 0;
}

void func_80101D1C(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80101D3C(STAGE_OBJ *wp)
{
    D_80117540[wp->routine_0](wp);
}

void func_80101D78(ST13_EMITTER *wp)
{
    wp->routine_0   = 1;
    wp->routine_1   = 0;
    wp->routine_2   = 0;
    wp->routine_3   = 0;
    wp->count_C     = 0;
    wp->frame_D     = 0;
    wp->left_E      = 0x18;
    wp->origin_90.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->origin_90.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->origin_90.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    wp->position_fixed_prev          = wp->position_fixed.v;
    wp->position_prev                = wp->position;
    wp->angle_CC                     = ratan2(Player_work.position.x - wp->position.x, Player_work.position.z - wp->position.z);
}

void func_80101E4C(ST13_EMITTER *wp)
{
    ST13_VIEW *owner;
    STAGE_FX *fx;
    owner = (ST13_VIEW *)func_80036294(wp->id_F);
    fx    = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0    = 1;
        fx->kind_2     = 0x13;
        fx->variant_3  = 0;
        fx->value_C    = wp->index_1;
        fx->timer_D    = wp->frame_D;
        fx->u_28.count = wp->angle_CC;
        fx->x_1C       = owner->vec_188.x;
        fx->y_1E       = owner->vec_188.y;
        fx->z_20       = owner->vec_188.z;
        wp->count_C++;
        if (--wp->left_E == 0)
        {
            wp->routine_0++;
        }
    }
    wp->frame_D++;
}

void func_80101F30(STAGE_OBJ *wp)
{
    if (wp->u_C.b.byte_C == 0)
    {
        Close_SHL_WORK(wp);
    }
}
