// Faster skates: Mega Man moves faster on the Jet Skates.
//
// The skates are the player's routine_1 3 (Player_work's state table D_80089FA4[3],
// func_8003D1E0 in src/rock_neo.exe/player.c): entered by holding Circle (PL_WORK.value134) with
// the skates owned (flags16b & 2), it sets a forward speed in value44 (0x340 cruising, 0x400 with
// Up, 0x280 with Down; 0x300 when landing from a jump onto the skates) and a sideways one in
// value48, and moves through func_80041E90(pl, x, y, z), which turns those local speeds into a
// world step with func_8002FEA4(wp, x, y, z) (code_8002E7A8.c). Walking and running
// (routine_1 2, value44 0x200), jumping, enemies and everything else reach func_8002FEA4 from
// other routines.
//
// The mod hooks func_8003D1E0 and func_8002FEA4: while the skates' routine runs for
// Player_work, a step of Player_work has its x and z multiplied. The stored speeds are untouched
// (the skates' own slowing down, value44 -= 0x28 a frame, works on them), so only the distance
// covered on skates changes. (Not func_80041E90: the native build inlines it into the routine,
// so a hook there would never see these calls; func_8002FEA4 is in another file and is a real
// call. docs/mods.md has the general rule.)
#include "mods.h"

#include <stddef.h>
#include <stdint.h>

#define FUNC_PL_SKATE 0x8003D1E0u // void func_8003D1E0(PL_WORK *pl): routine_1 3, the skates
#define FUNC_STEP     0x8002FEA4u // void func_8002FEA4(FIXED_POS_WORK *wp, sint16 x, y, z)

typedef void (*SKATE_FN)(uint32_t pl);
// The 16-bit speeds arrive as 32-bit words; passed on sign-extended.
typedef void (*STEP_FN)(uint32_t wp, uint32_t x, uint32_t y, uint32_t z);

static const char *const speeds[]   = {"1.5x", "2x", "3x"};
static const int32_t numerators[]   = {3, 2, 3}; // speed = step * num / den
static const int32_t denominators[] = {2, 1, 1};

static MOD_SETTING settings[] = {
    {"speed", "Speed", speeds, 3, 1, 1},
};

static SKATE_FN orig_skate;
static STEP_FN orig_step;
static int skating; // inside func_8003D1E0 for Player_work

static void skate_hook(uint32_t pl)
{
    skating += pl == MODS_PLAYER_WORK;
    orig_skate(pl);
    skating -= pl == MODS_PLAYER_WORK;
}

static int32_t scale(int32_t v)
{
    int i = settings[0].value;

    v = v * numerators[i] / denominators[i];
    // func_8002FEA4 takes 16-bit speeds.
    return v > 0x7FFF ? 0x7FFF : v < -0x7FFF ? -0x7FFF : v;
}

static void step_hook(uint32_t wp, uint32_t sx, uint32_t sy, uint32_t sz)
{
    int32_t x = (int16_t)sx, y = (int16_t)sy, z = (int16_t)sz;

    if (skating && wp == MODS_PLAYER_WORK)
    {
        x = scale(x);
        z = scale(z);
    }
    orig_step(wp, (uint32_t)x, (uint32_t)y, (uint32_t)z);
}

static void enable(MOD *m, int on)
{
    (void)m;
    if (on)
    {
        orig_skate = (SKATE_FN)mods_hook(FUNC_PL_SKATE, (void *)skate_hook);
        orig_step  = (STEP_FN)mods_hook(FUNC_STEP, (void *)step_hook);
        if (orig_skate == NULL || orig_step == NULL)
        {
            mods_unhook(FUNC_PL_SKATE);
            mods_unhook(FUNC_STEP);
        }
    }
    else
    {
        mods_unhook(FUNC_PL_SKATE);
        mods_unhook(FUNC_STEP);
        skating = 0;
    }
}

MOD mod_fast_skates = {
    "fast_skates",
    "Faster skates",
    "Mega Man skates faster on the Jet Skates (hold Circle). Walking, running and enemies "
    "are unchanged.",
    settings,
    1,
    enable,
    NULL,
    NULL,
    NULL,
    0,
};
