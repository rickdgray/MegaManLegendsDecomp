// Shoot while skating: the buster (and the special weapon) fire on the Jet Skates.
//
// The player's routines come in pairs, called each frame by func_8003C88C (player.c): a check
// routine D_80089FF8[routine_1] that reads the buttons and changes state, then the state's
// routine D_80089FA4[routine_1]. Every state that can shoot has its check call
// func_80040B68(pl, how): it starts a shot when the fire button is held, the weapon is ready
// (PL_WORK.value175's enable bits) and nothing is firing yet, by setting value174 to the
// shot's kind (0x80 buster, 0x40 special weapon) and the upper-body animation in value104/
// value100. From then on the weapon's handler (func_80042734 / func_800426F8, called by
// func_8003C88C before the check) plays the arm animation, raises value174's 0x20/0x10 bit on
// the firing frame, where func_80035724 spawns the projectile from the arm in Mega Man's facing,
// and clears value174 when the animation ends: rate of fire, energy, sound and direction are
// the game's own.
//
// The skates (routine_1 3) have func_8003FDA8 as their check, which only watches Circle, so
// they never shoot. The mod hooks func_8003FDA8 (reached through the D_80089FF8 table, so the
// hook sees every call) and, after it, while Player_work is skating (value0a 3 or 4: cruising,
// not starting or stopping), does what the jump's check func_800400B8 does in the air: sets the
// enable bit (a jump landing on the skates turns it off) and calls func_80040B68(pl, 2). With
// `how` 2 a weapon that cannot fire on the move (its table's reload byte 0) does not fire, and
// value174 gets bit 4, so the shot only animates the arm layer and leaves the skating body
// animation alone, as a shot in the air does. Of the weapon table (D_80089A84, 12 bytes each,
// reload at +4) the buster (part 1) and specials 2 and 5 fire on the move; parts whose handlers
// move Mega Man themselves (part 0's recoil, specials 3, 4, 7 and 9) have reload 0 and do not fire
// on the skates, so the skates' speed is never touched by a shot.
#include "mods.h"

#include <stddef.h>
#include <stdint.h>

#define FUNC_SKATE_CHECK 0x8003FDA8u // void func_8003FDA8(PL_WORK *pl): D_80089FF8[3]
#define FUNC_SHOT_CHECK  0x80040B68u // sint32 func_80040B68(PL_WORK *pl, sint32 how)

// PL_WORK (include/rock_neo.exe/player.h) offsets.
#define PL_ROUTINE_1 0x09
#define PL_VALUE0A   0x0A
#define PL_VALUE175  0x175 // bit 0: the shot enable (Pl00_shot_enable_on/off)

#define PL_SKATING 3 // routine_1: the Jet Skates

typedef void (*CHECK_FN)(uint32_t pl);

static CHECK_FN orig_check;

static void check_hook(uint32_t addr)
{
    uint8_t *pl;

    orig_check(addr);
    if (addr != MODS_PLAYER_WORK)
    {
        return;
    }
    pl = MODS_PTR(addr);
    if (pl[PL_ROUTINE_1] == PL_SKATING && (pl[PL_VALUE0A] == 3 || pl[PL_VALUE0A] == 4))
    {
        pl[PL_VALUE175] |= 1;
        mods_call(FUNC_SHOT_CHECK, 2, addr, 2, 0, 0); // sint32 func_80040B68(pl, how)
    }
}

static void enable(MOD *m, int on)
{
    (void)m;
    if (on)
    {
        orig_check = (CHECK_FN)mods_hook(FUNC_SKATE_CHECK, (void *)check_hook);
    }
    else
    {
        mods_unhook(FUNC_SKATE_CHECK);
    }
}

MOD mod_skate_shoot = {
    "skate_shoot",
    "Shoot while skating",
    "The buster (and a special weapon that can fire on the move) fires on the Jet Skates, "
    "as in a jump: same shots, rate and energy.",
    NULL,
    0,
    enable,
    NULL,
    NULL,
    NULL,
    0,
};
